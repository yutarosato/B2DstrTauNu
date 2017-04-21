#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);

  const Int_t nhist = 5+3;
  const Char_t* ctgry_name[nhist] = { "Signal",
				      "Normalization",
				      "B #rightarrow D^{**} l #nu",
				      "Others",
				      "Fake D^{(*)}",
				      "Normalization",
				      "B #rightarrow D^{**} l #nu",
				      "Fake D^{(*)}",
  };
  TLegend* leg  = new TLegend( 0.55,0.40,0.99,0.94 );
  TH1D**   hist = new TH1D*[nhist];

  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist] = new TH1D( Form("h%d", ihist), Form("h%d", ihist), 100, 0.0, 1.0 );
    leg->AddEntry( hist[ihist], ctgry_name[ihist], "F" );
  }
  hist[0]->SetFillStyle(1001); hist[0]->SetFillColor( 2);
  hist[1]->SetFillStyle(3017); hist[1]->SetFillColor( 3);
  hist[2]->SetFillStyle(3006); hist[2]->SetFillColor(17);
  hist[3]->SetFillStyle(1001); hist[3]->SetFillColor( 9);
  hist[4]->SetFillStyle(3018); hist[4]->SetFillColor( 4);
  hist[5]->SetFillStyle(1001); hist[5]->SetFillColor(15);
  hist[6]->SetFillStyle(1001); hist[6]->SetFillColor(11);
  hist[7]->SetFillStyle(1001); hist[7]->SetFillColor( 7);


  TCanvas* can = Canvas( "can","can" );
  can->Draw();
  hist[0]->Fill(0.0);
  hist[0]->Draw();
  leg->Draw();
  can->Update();
  //++++++++++++++

  can->Print("pic/leg.eps");
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
