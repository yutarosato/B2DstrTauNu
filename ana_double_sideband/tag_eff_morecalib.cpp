#include "tag_eff.h"

const Double_t ymin = 0.0;
//const Double_t ymax = 3.5;
const Double_t ymax = 2.5;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(!true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetTitleOffset(1.0,"y");
  sty->SetOptStat(0);
  sty->SetMarkerSize(1.2);
  sty->SetEndErrorSize(7);
  sty->SetPadTickY(1);
  sty->SetTickLength( 0.005, "Y" );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TH1D* waku = new TH1D( "tageff", "tagging efficiency", nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  for( Int_t idec=0; idec<nd_dec; idec++ ) ((TAxis*)waku->GetXaxis())->SetBinLabel( idec+1, d_dec_name[idec] );
  waku->SetMaximum(ymax);
  waku->SetMinimum(ymin);
  //waku->LabelsDeflate("X");
  waku->LabelsOption ("v");
  waku->SetYTitle("efficiency (data/mc)");


  const Char_t* infile1 = "calib.dat";
  //const Char_t* infile1 = "tmp2.dat";

  TGraphErrors* g_d_double_sig    = makeGraph( infile1, 0, 3, 4 );
  TGraphErrors* g_d_double_bkg    = makeGraph( infile1, 0, 9,10 );

  for( Int_t ip=0; ip<g_d_double_sig->GetN(); ip++ ){
    if( g_d_double_sig->GetX()[ip] < 9.5 ) g_d_double_sig->SetPoint( ip, g_d_double_sig->GetX()[ip], (1.080/1.000)*g_d_double_sig->GetY()[ip] );
    else                                   g_d_double_sig->SetPoint( ip, g_d_double_sig->GetX()[ip], (0.880/0.818)*g_d_double_sig->GetY()[ip] );
  }
  //for( Int_t ip=0; ip<g_d_double_bkg->GetN(); ip++ ){
  //if( g_d_double_bkg->GetX()[ip] < 9.5 ) g_d_double_bkg->SetPoint( ip, g_d_double_bkg->GetX()[ip], (0.770/0.812)*g_d_double_bkg->GetY()[ip] );
  //else                                   g_d_double_bkg->SetPoint( ip, g_d_double_bkg->GetX()[ip], (1.209/1.212)*g_d_double_bkg->GetY()[ip] );
  //}

  g_d_double_sig   ->SetLineWidth( 2); g_d_double_sig   ->SetMarkerColor( 2); g_d_double_sig   ->SetLineColor( 2); g_d_double_sig   ->SetMarkerStyle(24);
  g_d_double_bkg   ->SetLineWidth( 2); g_d_double_bkg   ->SetMarkerColor( 2); g_d_double_bkg   ->SetLineColor( 2); g_d_double_bkg   ->SetMarkerStyle(24);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 2, 1, 700, 500 );
  can->Draw();
  for( Int_t i=0; i<2; i++ ){
    can->cd(i+1)->SetGridx();
    can->cd(i+1)->SetGridy();
    can->cd(i+1);
    if     ( i==0 ) waku->SetTitle( "tagging efficiency (D, sig)" );
    else if( i==1 ) waku->SetTitle( "tagging efficiency (D, bkg)" );
    waku->DrawClone();
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(1); g_d_double_sig->Draw("Psame");
  can->cd(2); g_d_double_bkg->Draw("Psame");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  can->Update();
  can->Print( "pic/tag_eff_morecalib.eps" );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
