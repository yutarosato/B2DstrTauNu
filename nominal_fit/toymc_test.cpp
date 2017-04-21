#include "draws_.h"
#include "draws_fit_.h"

const Double_t ymin = 0.0;
const Double_t ymax = 3.0;
const Double_t systR = 0.252*0.05;

//const Int_t   npdf           = 1;
//const Char_t* pdf_name[npdf] = { "sig" };
const Int_t   npdf           = 3;
const Char_t* pdf_name[npdf] = { "sig", "nor", "dstst" };

TGraph* makeSinglePointGraph( Int_t sty, Int_t col,  Double_t x, Double_t y ){
  TGraph* g = new TGraph();
  g->SetPoint(0, x, y);
  g->SetMarkerStyle(sty);
  g->SetMarkerColor(col);
  g->SetMarkerSize(2.0);
  return g;
}

TGraph* makeSensitivity_with_syst( TGraph* graph ){
  TGraph* g = new TGraph( *graph );
  for( Int_t ip=0; ip<graph->GetN(); ip++ ){
    Double_t x = graph->GetX()[ip];
    Double_t y = graph->GetY()[ip];
    y =   sqrt( pow(x*y,2) + pow(systR,2) ) / x;
    g->SetPoint( ip, x, y );
  }
  return g;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(11);
  sty->SetOptStat(0);
  sty->SetTitleSize(0.04,"xyz");
  sty->SetTitleOffset(1.8,"xyz");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TGraphErrors** yield     = new TGraphErrors*[npdf];
  TGraphErrors** pullmean  = new TGraphErrors*[npdf];
  TGraphErrors** pullwidth = new TGraphErrors*[npdf];

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    yield    [ipdf] = new TGraphErrors( Form("log/toymctest_%s.dat",pdf_name[ipdf]), "%*lg %lg %*lg %lg  %lg"                              );
    pullmean [ipdf] = new TGraphErrors( Form("log/toymctest_%s.dat",pdf_name[ipdf]), "%*lg %lg %*lg %*lg %*lg %*lg %*lg %lg  %lg"          );
    pullwidth[ipdf] = new TGraphErrors( Form("log/toymctest_%s.dat",pdf_name[ipdf]), "%*lg %lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %lg" );
    yield    [ipdf]->Sort();
    pullmean [ipdf]->Sort();
    pullwidth[ipdf]->Sort();
    //yield    [ipdf]->Print();
    //pullmean [ipdf]->Print();
    //pullwidth[ipdf]->Print();
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D** wakuyield = new TH1D*[npdf];
  TH1D** wakumean  = new TH1D*[npdf];
  TH1D** wakuwidth = new TH1D*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    wakuyield[ipdf] = new TH1D( Form("yield_%s",     pdf_name[ipdf]), Form("yield (%s)",     pdf_name[ipdf]), 2, 0, yield    [ipdf]->GetX()[yield    [ipdf]->GetN()-1]*1.1 );
    wakumean [ipdf] = new TH1D( Form("pull_mean_%s", pdf_name[ipdf]), Form("pull mean (%s)", pdf_name[ipdf]), 2, 0, pullmean [ipdf]->GetX()[pullmean [ipdf]->GetN()-1]*1.1 );
    wakuwidth[ipdf] = new TH1D( Form("pull_width_%s",pdf_name[ipdf]), Form("pull width (%s)",pdf_name[ipdf]), 2, 0, pullwidth[ipdf]->GetX()[pullwidth[ipdf]->GetN()-1]*1.1 );
    wakuyield[ipdf]->SetMinimum( 0.0);
    wakuyield[ipdf]->SetMaximum( yield[ipdf]->GetX()[yield[ipdf]->GetN()-1]*1.1 );
    wakumean [ipdf]->SetMinimum(-0.3);
    wakumean [ipdf]->SetMaximum( 0.3);
    wakuwidth[ipdf]->SetMinimum( 0.8);
    wakuwidth[ipdf]->SetMaximum( 1.2);
    wakuyield[ipdf]->SetXTitle("N_{sig}^{input}");
    wakumean [ipdf]->SetXTitle("N_{sig}^{input}");
    wakuwidth[ipdf]->SetXTitle("N_{sig}^{input}");
    wakuyield[ipdf]->SetYTitle("N_{sig}^{output}");
    wakumean [ipdf]->SetYTitle("pull mean" );
    wakuwidth[ipdf]->SetYTitle("pull width");
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TF1** func_yield     = new TF1*[npdf];
  TF1** func_pullmean  = new TF1*[npdf];
  TF1** func_pullwidth = new TF1*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    func_yield[ipdf] = new TF1( Form("func_yield_%s",pdf_name[ipdf]), "[0]*x+[1]", 0, yield[ipdf]->GetX()[yield[ipdf]->GetN()-1] );
    func_yield[ipdf]->SetParameters(1.0,0.0);
    func_pullmean[ipdf] = new TF1( Form("func_pullmean_%s",pdf_name[ipdf]), "[0]*x+[1]", 0, pullmean[ipdf]->GetX()[pullmean[ipdf]->GetN()-1] );
    func_pullmean[ipdf]->SetParameters(0.0,1.0);
    func_pullmean[ipdf]->FixParameter (0, 0.0);
    func_pullwidth[ipdf] = new TF1( Form("func_pullwidth_%s",pdf_name[ipdf]), "[0]*x+[1]", 0, pullwidth[ipdf]->GetX()[pullwidth[ipdf]->GetN()-1] );
    func_pullwidth[ipdf]->SetParameters(0.0,1.0);
    func_pullwidth[ipdf]->FixParameter (0, 0.0);
  }
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 3, npdf );
  can->Draw();

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    can->cd(3*ipdf+1);
    wakuyield[ipdf]->Draw();
    yield[ipdf]->Draw("PEsame");
    yield[ipdf]->Fit( Form("func_yield_%s",pdf_name[ipdf]) );

    can->cd(3*ipdf+2);
    wakumean[ipdf]->Draw();
    pullmean[ipdf]->Draw("PEsame");
    pullmean[ipdf]->Fit( Form("func_pullmean_%s",pdf_name[ipdf]) );

    can->cd(3*ipdf+3);
    wakuwidth[ipdf]->Draw();
    pullwidth[ipdf]->Draw("PEsame");
    pullwidth[ipdf]->Fit( Form("func_pullwidth_%s",pdf_name[ipdf]) );
  }

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can2 = Canvas( "can2", "can2", 2, 1 );
  can2->Draw();
  TGraph* sensitivity1 = new TGraph( "log/toymctest_sensitivity.dat", "%lg %lg" );
  sensitivity1->SetName ("sensitivity1");
  sensitivity1->SetTitle("sensitivity as a function of signal yield");
  sensitivity1->Sort();
  sensitivity1->SetMarkerSize(0.6);
  sensitivity1->SetMinimum(0.00);
  sensitivity1->SetMaximum(0.30);
  sensitivity1->GetXaxis()->SetTitle("N_{sig}^{inpu}");
  sensitivity1->GetYaxis()->SetTitle("Relative accuracy");
  sensitivity1->SetLineStyle(2);
  can2->cd(1);
  sensitivity1->Draw("APL");

  TGraph* sensitivity2 = new TGraph();
  std::cout << "convert factor for nsig = " << convert_factor_nsig[0] << std::endl;
  for( Int_t ip=0; ip<sensitivity1->GetN(); ip++ ){
    sensitivity2->SetPoint( sensitivity2->GetN(), convert_factor_nsig[0]*sensitivity1->GetX()[ip], sensitivity1->GetY()[ip] );
  }
  sensitivity2->Sort();
  sensitivity2->SetName ("sensitivity2");
  sensitivity2->SetTitle("sensitivity as a function of R(D*)");
  sensitivity2->SetMarkerSize(0.6);
  sensitivity2->SetMinimum(0.00);
  sensitivity2->SetMaximum(0.30);
  sensitivity2->GetXaxis()->SetTitle("R(D*)");
  sensitivity2->GetYaxis()->SetTitle("Relative accuracy");
  sensitivity2->SetLineStyle(2);
  TGraph* sensitivity2_with_syst = makeSensitivity_with_syst( sensitivity2 );
  sensitivity2_with_syst->SetLineStyle(1);
  can2->cd(2);
  sensitivity2          ->Draw("APL");
  sensitivity2_with_syst->Draw("PLsame");

  TGraph* babar         = makeSinglePointGraph( 29, 4, 0.332, sqrt(pow(0.024,2)+pow(0.018,2))/0.332 ); babar        ->SetName("babar"        ); babar        ->SetTitle("babar"                );
  TGraph* babar_stat    = makeSinglePointGraph( 30, 4, 0.332,                           0.024/0.332 ); babar_stat   ->SetName("babar_stat"   ); babar        ->SetTitle("babar (only stat)"    );
  TGraph* oldbelle      = makeSinglePointGraph( 29, 3, 0.405,                           0.047/0.405 ); oldbelle     ->SetName("oldbelle"     ); oldbelle     ->SetTitle("old belle"            );
  TGraph* newbelle      = makeSinglePointGraph( 29, 2, 0.293, sqrt(pow(0.039,2)+pow(0.015,2))/0.293 ); newbelle     ->SetName("newbelle"     ); newbelle     ->SetTitle("new belle"            );
  TGraph* newbelle_stat = makeSinglePointGraph( 30, 2, 0.293,                           0.039/0.293 ); newbelle_stat->SetName("newbelle_stat"); newbelle_stat->SetTitle("new belle (only stat)");
  TGraph* lhcb          = makeSinglePointGraph( 29, 6, 0.336, sqrt(pow(0.027,2)+pow(0.030,2))/0.336 ); lhcb         ->SetName("lhcb"         ); lhcb         ->SetTitle("lhcb"                 );
  TGraph* lhcb_stat     = makeSinglePointGraph( 30, 6, 0.336,                           0.027/0.336 ); lhcb_stat    ->SetName("lhcb_stat"    ); lhcb_stat    ->SetTitle("lhcb (only stat)"     );
  TLine* sm = new TLine( 0.252, 0.0, 0.252, 0.30 );
  sm->SetLineColor(5);
  sm->SetLineWidth(3);

  TLegend* leg  = new TLegend( 0.50,0.72,0.80,0.92 );
  leg->AddEntry( babar,    "BABAR",              "P" );
  leg->AddEntry( lhcb,     "LHCb",               "P" );
  leg->AddEntry( oldbelle, "Belle",              "P" );
  leg->AddEntry( newbelle, "Belle (new hadtag)", "P" );
  leg->AddEntry( sm,       "SM",                 "L" );

  can2->cd(2);
  babar        ->Draw("Psame");
  babar_stat   ->Draw("Psame");
  lhcb         ->Draw("Psame");
  lhcb_stat    ->Draw("Psame");
  oldbelle     ->Draw("Psame");
  newbelle     ->Draw("Psame");
  newbelle_stat->Draw("Psame");
  sm           ->Draw("Lsame");
  leg->Draw();

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can ->Print( "pic/toymctest_bias.eps"        );
  can2->Print( "pic/toymctest_sensitivity.eps" );

  TFile outfile( "pic/toymctest.root", "RECREATE" );
  can ->Write();
  can2->Write();
  sensitivity1 ->Write();
  sensitivity2 ->Write();
  babar        ->Write();
  babar_stat   ->Write();
  lhcb         ->Write();
  lhcb_stat    ->Write();
  oldbelle     ->Write();
  newbelle     ->Write();
  newbelle_stat->Write();
  sm           ->Write();
  outfile.Close();
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
