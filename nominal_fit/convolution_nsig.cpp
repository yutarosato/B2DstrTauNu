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

Double_t asym_fourth( const Double_t* x, const Double_t *p ){
  // p[0] : mean
  // p[1] : error_low (2th)
  // p[2] : error_high(2th)
  // p[3] : error_low (4th)
  // p[4] : error_high(4th)
  Double_t f;
  if( x[0] < p[0] ) f = pow( (x[0]-p[0])/p[1], 2 ) + pow( (x[0]-p[0])/p[3], 4 ); // low side
  else              f = pow( (x[0]-p[0])/p[2], 2 ) + pow( (x[0]-p[0])/p[4], 4 ); // high side
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
  const Char_t* xaxisname   = "N_{sig}";
  const Char_t* outname     = "nsig";
  const Double_t xmin       =   0.0;
  const Double_t xmax       = 400.0;
  const Double_t center_val = 230.924;
  const Double_t err_low    = 22.4305;
  const Double_t err_high   = 23.4170;
  const Double_t sm_val     = 0.0;
  TCanvas* can = new TCanvas( "can", "can", 1000, 500 );
  can->Divide(2,1);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(1);
  // FCN = -log(L)
  TGraph* g_n2logL = new TGraph( "tmp_stat_nsig_lep0.dat", "%lg %lg" );
  Convert_n2logL( g_n2logL );
  g_n2logL->Sort();
  
  /*
  TF1* func_n2logL_2nd = new TF1( "func_n2logL_2nd", asym_parabora, xmin, xmax, 3 );
  func_n2logL_2nd->FixParameter( 0, center_val );
  func_n2logL_2nd->SetParameter( 1, err_low    );
  func_n2logL_2nd->SetParameter( 2, err_high   );
  func_n2logL_2nd->SetLineColor(3);
  func_n2logL_2nd->SetLineWidth(2);
  */

  TF1* func_n2logL = new TF1( "func_n2logL", asym_fourth, xmin, xmax, 5 );
  func_n2logL->FixParameter( 0, center_val );
  func_n2logL->SetParameter( 1, err_low    );
  func_n2logL->SetParameter( 2, err_high   );
  func_n2logL->SetParameter( 3, 100000     );
  func_n2logL->SetParameter( 4, 100000     );
  func_n2logL->SetLineColor(3);
  func_n2logL->SetLineWidth(2);
  
  g_n2logL->Fit ("func_n2logL");
  //g_n2logL->Fit ("func_n2logL_2nd");
  Double_t ymax = ( g_n2logL->GetY()[0] > g_n2logL->GetY()[g_n2logL->GetN()-1] ? (Int_t)(1.05*g_n2logL->GetY()[0]+1) : (Int_t)(1.05*g_n2logL->GetY()[g_n2logL->GetN()-1]+1) );
  gPad->DrawFrame( g_n2logL->GetX()[0], 0.0, g_n2logL->GetX()[g_n2logL->GetN()-1], ymax, Form(";%s;%s",xaxisname,"-2#Deltalog(L)") );
  g_n2logL   ->Draw("PLsame");
  func_n2logL->Draw("Lsame");
  //func_n2logL_2nd->Draw("Lsame");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(2);
  can->cd(2)->SetGridx(0);
  can->cd(2)->SetGridy(0);
  gPad->DrawFrame( g_n2logL->GetX()[0], 0.0, g_n2logL->GetX()[g_n2logL->GetN()-1], ymax, Form(";%s;%s",xaxisname,"-2#Deltalog(L)") );
  func_n2logL->Draw("Lsame");
  {
    Double_t nsigma = 5.0;
    while(1){
      if( pow(nsigma,2) > ymax ) break;
      TLine* line = new TLine( g_n2logL->GetX()[0], pow(nsigma,2), g_n2logL->GetX()[g_n2logL->GetN()-1], pow(nsigma,2) );
      line->SetLineColor(4);
      line->SetLineStyle(2);
      line->SetLineWidth(1);
      line->Draw("Lsame");

      TPaveText* tex = new TPaveText( g_n2logL->GetX()[g_n2logL->GetN()-1]+5, pow(nsigma,2)-1.0, g_n2logL->GetX()[g_n2logL->GetN()-1]+30, pow(nsigma,2)+1.0 );
      tex->SetTextColor(kGreen+3);
      tex->SetTextSize(0.04);
      tex->SetFillColor(0);
      tex->AddText( Form("%d#sigma",(Int_t)nsigma) );
      tex->Draw("same");
      nsigma += 3.0;
    }
  }
  TLine* line_sm = new TLine( sm_val, 0.0, sm_val, ymax );
  line_sm->SetLineColor(5);
  line_sm->SetLineWidth(2);
  line_sm->Draw("Lsame");
  TPaveText* tex_sm = new TPaveText( sm_val-20, ymax+5, sm_val+20, ymax + 25 );
  tex_sm->SetTextColor(5);
  tex_sm->SetTextSize(0.04);
  tex_sm->SetFillColor(0);
  tex_sm->AddText( Form("%.2f#sigma",sqrt(func_n2logL->Eval(sm_val))) );
  tex_sm->Draw("same");

  TLegend* leg  = new TLegend( 0.50,0.50,0.70,0.65 );
  leg->AddEntry( func_n2logL, "stat", "L" );
  leg->AddEntry( line_sm,     "null", "L" );
  leg->Draw();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Print( Form("pic/convolution_%s.eps",outname) );

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
