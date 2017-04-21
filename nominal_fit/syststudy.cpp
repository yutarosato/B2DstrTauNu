#include "draws_.h"
#include "draws_fit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(!true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(11);
  sty->SetOptStat(0);
  sty->SetTitleSize(0.04,"xyz");
  sty->SetTitleOffset(1.6,"x");
  sty->SetTitleOffset(2.0,"y");
  sty->SetMarkerSize(1.5);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TGraph* graph = new TGraph( "log/syststudy.dat", "%*lg %lg %lg" );
  TH1D*   hist  = new TH1D("syst","syst", 100, 0.24, 0.34 );
  hist->SetXTitle("R(D*)");
  Double_t nominal_value;

  for( Int_t ip=0; ip<graph->GetN(); ip++ ){
    hist->Fill( graph->GetY()[ip] ); /////
    if( graph->GetX()[ip] == 0 ) nominal_value = graph->GetY()[ip];
  }
  TLine* nominal = new TLine( nominal_value, 0.0, nominal_value, hist->GetMaximum() );
  nominal->SetLineColor(3);
  nominal->SetLineWidth(2);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can" );
  can->Draw();
  hist->Draw();
  hist->Fit("gaus");
  nominal->Draw("Lsame");
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Print( "pic/syststudy.eps" );
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
