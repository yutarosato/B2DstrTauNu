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
    wakuyield[ipdf]->SetXTitle("N_{D**}^{input}");
    wakumean [ipdf]->SetXTitle("N_{D**}^{input}");
    wakuwidth[ipdf]->SetXTitle("N_{D**}^{input}");
    wakuyield[ipdf]->SetYTitle("N_{D**}^{output}");
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
  can ->Print( "pic/toymctest_bias.eps" );
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
