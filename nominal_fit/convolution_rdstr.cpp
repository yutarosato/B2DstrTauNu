#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

void Convert_n2logL( TGraph* graph ){

  Double_t ymin = 100000;
  for( Int_t ip=0; ip<graph->GetN(); ip++ ){
    if     ( ip  == 0                 ) ymin = graph->GetY()[ip];
    else if( ymin > graph->GetY()[ip] ) ymin = graph->GetY()[ip];
  }

  for( Int_t ip=0; ip<graph->GetN(); ip++ ) graph->SetPoint( ip, graph->GetX()[ip], 2.0*(graph->GetY()[ip]-ymin) );
  std::cout << "ymin = " << ymin << std::endl;
  
  return;
}

Double_t asym_parabora( const Double_t* x, const Double_t *p ){
  // p[0] : mean
  // p[1] : error_low
  // p[2] : error_high
  Double_t f;
  if( x[0] < p[0] ) f = pow( (x[0]-p[0])/p[1], 2 ); // low side
  else              f = pow( (x[0]-p[0])/p[2], 2 ); // high side
  return f;
}

Double_t makefunc_likelihood( const Double_t*x, const Double_t *p ){
  //f = -2*log(L) -> L = exp(-f/2)
  Double_t f = exp ( -asym_parabora(x,&p[0])/2.0 );
  
  return f;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(!true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(11);
  sty->SetOptStat(0);
  sty->SetTitleSize(0.045,"xyz");
  sty->SetTitleOffset(1.6,"x");
  sty->SetTitleOffset(1.8,"y");
  sty->SetMarkerSize(1.1);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Char_t* xaxisname   = "R(D*)";
  const Char_t* outname     = "rdstr";
  const Double_t xmin       = 0.1;
  const Double_t xmax       = 0.5;
  const Double_t center_val = 0.301667;
  const Double_t err_low    = 0.0297032;
  const Double_t err_high   = 0.0312535;
  const Double_t sm_val     = 0.252;
  TCanvas* can = new TCanvas( "can", "can", 1500, 1000 );
  can->Divide(3,2);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(1);
  // FCN = -log(L)
  TGraph* g_n2logL = new TGraph( "tmp_stat_rdstr_lep0.dat", "%lg %lg" );
  Convert_n2logL( g_n2logL );
  g_n2logL->Sort();

  TF1* func_n2logL = new TF1( "func_n2logL", asym_parabora, xmin, xmax, 3 );
  func_n2logL->FixParameter( 0, center_val );
  func_n2logL->SetParameter( 1, err_low    );
  func_n2logL->SetParameter( 2, err_high   );
  func_n2logL->SetLineColor(3);
  func_n2logL->SetLineWidth(2);
  
  g_n2logL->Fit ("func_n2logL");
  Double_t ymax = ( g_n2logL->GetY()[0] > g_n2logL->GetY()[g_n2logL->GetN()-1] ? (Int_t)(1.05*g_n2logL->GetY()[0]+1) : (Int_t)(1.05*g_n2logL->GetY()[g_n2logL->GetN()-1]+1) );
  gPad->DrawFrame( g_n2logL->GetX()[0], 0.0, g_n2logL->GetX()[g_n2logL->GetN()-1], ymax, Form(";%s;%s",xaxisname,"-2#Deltalog(L)") );
  g_n2logL   ->Draw("PLsame");
  func_n2logL->Draw("Lsame");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(2);
  TF1* func_likelihood = new TF1(" func_likelihood", makefunc_likelihood, xmin, xmax, 3 );
  func_likelihood->SetTitle( Form(";%s;L",xaxisname) );
  func_likelihood->SetParameter( 0, func_n2logL->GetParameter(0) );
  func_likelihood->SetParameter( 1, func_n2logL->GetParameter(1) );
  func_likelihood->SetParameter( 2, func_n2logL->GetParameter(2) );
  func_likelihood->SetLineColor(3);
  func_likelihood->SetLineWidth(2);
  func_likelihood->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooRealVar* t  = new RooRealVar( "t",  xaxisname,  xmin, xmax );
  RooAbsPdf* roofunc_likelihood = bindPdf( func_likelihood, *t );

  // smeared by systematic errors
  RooRealVar*  mean  = new RooRealVar ( "mean",  "mean",   0.0 );
  RooRealVar*  sigma = new RooRealVar ( "sigma", "sigma",  0.0112 );
  RooGaussian* gauss = new RooGaussian( "gauss", "gauss", *t, *mean, *sigma );

  RooFFTConvPdf* roofunc_likelihood_smear = new RooFFTConvPdf( "roofunc_likelihood_smear", "Likelihood (X) gauss_syst", *t, *roofunc_likelihood, *gauss );

  RooPlot* frame = t->frame( Title("likelihood") );
  roofunc_likelihood_smear->plotOn( frame, LineColor(kRed  )                     );
  roofunc_likelihood      ->plotOn( frame, LineColor(kBlue ), LineStyle(kDashed) );

  can->cd(3);
  frame->Draw();
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TF1* func_likelihood_smear = roofunc_likelihood_smear->asTF( RooArgList(*t) );
  TGraph* g_likelihood_smear = new TGraph();
  const Int_t nscan = 10000;
  for( Int_t ip=0; ip<nscan; ip++ ){
    Double_t tmpx = g_n2logL->GetX()[0] + (Double_t)ip*(g_n2logL->GetX()[g_n2logL->GetN()-1] - g_n2logL->GetX()[0])/(Double_t)nscan;
    Double_t tmpy = func_likelihood_smear->Eval(tmpx);
    g_likelihood_smear->SetPoint( ip, tmpx, tmpy/func_likelihood_smear->GetMaximum() );
  }
  can->cd(2);
  g_likelihood_smear->SetLineColor(2);
  g_likelihood_smear->Draw("Lsame");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(4);
  TGraph* g_n2logL_smear = new TGraph();
  for( Int_t ip=0; ip<g_likelihood_smear->GetN(); ip++ ) g_n2logL_smear->SetPoint( ip, g_likelihood_smear->GetX()[ip], -2.0*log(g_likelihood_smear->GetY()[ip]) );
    g_n2logL_smear->SetLineColor(2);
  g_n2logL_smear->SetLineWidth(2);


  TF1* func_n2logL_smear = new TF1( "func_n2logL_smear", asym_parabora, xmin, xmax, 3 );
  func_n2logL_smear->FixParameter( 0, center_val );
  func_n2logL_smear->SetParameter( 1, err_low    );
  func_n2logL_smear->SetParameter( 2, err_high   );
  func_n2logL_smear->SetLineColor(2);
  func_n2logL_smear->SetLineWidth(2);
  func_n2logL_smear->SetLineStyle(1);

  g_n2logL_smear->Fit ("func_n2logL_smear");
  g_n2logL_smear->Draw("AP");
  func_n2logL_smear->Draw("Lsame");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(5);
  can->cd(5)->SetGridx(0);
  can->cd(5)->SetGridy(0);
  gPad->DrawFrame( g_n2logL->GetX()[0], 0.0, g_n2logL->GetX()[g_n2logL->GetN()-1], ymax, Form(";%s;%s",xaxisname,"-2#Deltalog(L)") );
  func_n2logL      ->Draw("Lsame");
  func_n2logL_smear->Draw("Lsame");
  {
    Double_t nsigma = 1.0;
    while(1){
      if( pow(nsigma,2) > ymax ) break;
      TLine* line = new TLine( g_n2logL->GetX()[0], pow(nsigma,2), g_n2logL->GetX()[g_n2logL->GetN()-1], pow(nsigma,2) );
      line->SetLineColor(4);
      line->SetLineStyle(2);
      line->SetLineWidth(1);
      line->Draw("Lsame");
      if( nsigma - (Int_t)nsigma!=0.0 ){
	nsigma += 0.5;
	continue;
      }
      TPaveText* tex = new TPaveText( g_n2logL->GetX()[g_n2logL->GetN()-1]+0.002, pow(nsigma,2)-1.0, g_n2logL->GetX()[g_n2logL->GetN()-1]+0.02, pow(nsigma,2)+1.0 );
      tex->SetTextColor(kGreen+3);
      tex->SetTextSize(0.04);
      tex->SetFillColor(0);
      tex->AddText( Form("%d#sigma",(Int_t)nsigma) );
      tex->Draw("same");
      nsigma += 0.5;
    }
  }
  TLine* line_sm = new TLine( sm_val, 0.0, sm_val, ymax );
  line_sm->SetLineColor(5);
  line_sm->SetLineWidth(2);
  line_sm->Draw("Lsame");
  TPaveText* tex_sm = new TPaveText( sm_val-0.02, ymax+0.2, sm_val+0.02, ymax + 1.3 );
  tex_sm->SetTextColor(5);
  tex_sm->SetTextSize(0.04);
  tex_sm->SetFillColor(0);
  tex_sm->AddText( Form("%.2f#sigma",sqrt(func_n2logL_smear->Eval(sm_val))) );
  tex_sm->Draw("same");

  TLegend* leg  = new TLegend( 0.40,0.45,0.70,0.65 );
  leg->AddEntry( func_n2logL,       "stat",      "L" );
  leg->AddEntry( func_n2logL_smear, "stat+syst", "L" );
  leg->AddEntry( line_sm,           "SM pred.",  "L" );
  leg->Draw();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Print( Form("pic/convolution_%s.eps",outname) );

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
