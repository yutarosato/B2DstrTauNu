#include "tag_eff.h"

const Double_t ymin = -200.;
const Double_t ymax =  200.;

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

  TH1D* waku = new TH1D( "diff", "Difference of N_{evt}", nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  for( Int_t idec=0; idec<nd_dec; idec++ ) ((TAxis*)waku->GetXaxis())->SetBinLabel( idec+1, d_dec_name[idec] );
  waku->SetMaximum(ymax);
  waku->SetMinimum(ymin);
  //waku->LabelsDeflate("X");
  waku->LabelsOption ("v");
  waku->SetYTitle("MC - Data");

  const Char_t* infile = "dat/tmp_d_%s_%s_%d.dat";
  //const Char_t* infile = "dat/tmp_dstr_%s_%s_%d.dat";
  const Int_t ng = 4;
  const Char_t* type[ng] = {"s1s2","s1b2","b1s2","b1b2"};
  TGraphErrors** g1_mc = new TGraphErrors*[ng];
  TGraphErrors** g1_dt = new TGraphErrors*[ng];
  TGraphErrors** g1    = new TGraphErrors*[ng];
  TGraphErrors** g2_mc = new TGraphErrors*[ng];
  TGraphErrors** g2_dt = new TGraphErrors*[ng];
  TGraphErrors** g2    = new TGraphErrors*[ng];
  for( Int_t ig=0; ig<ng; ig++ ){
    g1_mc[ig] = makeGraph_conv( Form(infile, "mc",type[ig],1), 0,1,2, !true );
    g1_dt[ig] = makeGraph_conv( Form(infile, "dt",type[ig],1), 0,1,2, !true );
    g1   [ig] = makeGraph_diff( g1_mc[ig], g1_dt[ig] );

    g2_mc[ig] = makeGraph_conv( Form(infile, "mc",type[ig],2), 0,1,2, !true );
    g2_dt[ig] = makeGraph_conv( Form(infile, "dt",type[ig],2), 0,1,2, !true );
    g2   [ig] = makeGraph_diff( g2_mc[ig], g2_dt[ig] );
    Deco_Fill( g1[ig]    );
    Deco_Mark( g2[ig], 2 );
  }
  



  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 2, 2, 600, 400 );
  can->Draw();
  for( Int_t ig=0; ig<ng; ig++ ){
    can->cd(ig+1)->SetGridx();
    can->cd(ig+1)->SetGridy();
    can->cd(ig+1);
    waku->SetTitle( Form("comparison of [%s] components",type[ig]) );
    waku->DrawClone();
    can->cd(ig+1);
    //if( g1[ig]->GetN() ) g1[ig]->Draw("EZsame");
    if( g2[ig]->GetN() ) g2[ig]->Draw("PEsame");
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TLegend* leg  = new TLegend( 0.15,0.72,0.35,0.88 );
  leg->AddEntry( g1[0], "g1", "PL" );
  leg->AddEntry( g2[0], "g2", "PL" );
  //leg->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  can->Update();
  can->Print( "pic/ck_calib.eps" );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

