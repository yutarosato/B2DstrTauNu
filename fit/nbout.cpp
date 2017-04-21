#include "draws_.h"
#include "draws_roofit_.h"

const Char_t*  brname = "nb_mode0_test13_nor";
const Double_t NB_cut = -0.6;
//const Double_t NB_cut = 0.0;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/*
const Int_t nhist = 8;
const Char_t* ctgry     [nhist] = {"0",     "self==-3", "self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1",   "self==-5"};
const Char_t* ctgry_name[nhist] = {"other", "double D", "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had decay)",                  "sig(falsely rec.)",                             "sig(true)", "D**"     };
const Int_t   col       [nhist] = { 4,      9,          15,                   3,            5,                                              13,                                              2,           11        };
*/
/*
const Int_t nhist = 8;
const Char_t* ctgry     [nhist] = {"0",     "self==-3", "self==-5", "self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1"  };
const Char_t* ctgry_name[nhist] = {"other", "double D", "D**",      "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had decay)",                  "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,      9,          11,         15,                   3,            5,                                              13,                                              2,         };
*/
///*
const Int_t nhist = 4;
const Char_t* ctgry     [nhist] = {"0",     "self==-5", "(self==0&&gm_semi<0)||self==2",    "(self==0&&gm_semi>0&&(taulep1==0&&taulep2==0))||(self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0))||self==1"  };
const Char_t* ctgry_name[nhist] = {"other bkg", "B #rightarrow D**l#nu bkg",      "normalization",  "signal"};
const Int_t   col       [nhist] = { 4,      9,         3,                   2  };
//*/
/*
const Int_t nhist = 13;
const Char_t* ctgry     [nhist] = {"0",    "self==-7", "self==-2",         "self==-1",          "self==-4",        "self==-6",            "self==-3", "self==-5","self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1"  };
const Char_t* ctgry_name[nhist] = {"other","qq",       "hadronic decay",   "non-reso semilept", "cf from D*D(*)",  "cf from B^{+}B^{-}",  "double D", "D**",     "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had dec)",                    "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,      8,         1,                  14,                  16,                 12,                   9,          11,        15,                   3,            5,                                              13,                                              2          };
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t* selection = "eecl<0.5";
//const Char_t* selection = "eecl<0.5&&dst1self+dst2self==2";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//const Char_t* infile = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_mode0_test13_nor_setAA_HH/gMC_*s0[0-5]*.root";
const Char_t* infile = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_bcs_vtx_mode0_test13_nor/gMC_*s0[0-5]*.root";
const Int_t nstream = 6;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c_gmc = new TChain("h15");
  std::cout << "[infile] " << infile << std::endl;
  std::cout << c_gmc->Add(infile)  << " files, ";
  std::cout << c_gmc->GetEntries() << " entries, ";
  std::cout << nstream             << " streams" << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Double_t NB_max = -0.6;
  Double_t NB_max_gmc = c_gmc->GetMaximum( brname );
  if( NB_max_gmc > NB_max ) NB_max = NB_max_gmc;
  std::cout << "NB_cut     = " << NB_cut     << std::endl;
  std::cout << "NB_max_gmc = " << NB_max_gmc << std::endl;
  std::cout << "NB_max     = " << NB_max     << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 3, 2 );
  can->Draw();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg   = new TLegend( 0.55,0.65,0.99,0.99 );
  THStack* mh1   = new THStack( "mh1", Form("%s;NB",           selection       ) ); // NB
  THStack* mh2   = new THStack( "mh2", Form("%s (NB > %f);NB'",selection,NB_cut) ); // NB'
  TH1D**   hist1 = new TH1D*[nhist]; // NB
  TH1D**   hist2 = new TH1D*[nhist]; // NB'
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist1[ihist] = new TH1D( Form("h1_%d",ihist), Form("h1_%d",ihist), 50,-1.0,1.0 );
    hist2[ihist] = new TH1D( Form("h2_%d",ihist), Form("h2_%d",ihist), 50, -10, 10 );
    if( ihist==0 ) c_gmc->Project( Form("h1_%d",ihist), brname, Form("(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection) );
    else           c_gmc->Project( Form("h1_%d",ihist), brname, Form("(%s)&&(%s)",ctgry[ihist],                       selection) );
    if( ihist==0 ) c_gmc->Project( Form("h2_%d",ihist), Form("log((%s-(%f))/((%f)-%s))",brname,NB_cut,NB_max,brname), Form("(%s)&&(%s)&&(%s>%f)",makeCut_remain(ctgry,nhist).c_str(),selection,brname, NB_cut) );
    else           c_gmc->Project( Form("h2_%d",ihist), Form("log((%s-(%f))/((%f)-%s))",brname,NB_cut,NB_max,brname), Form("(%s)&&(%s)&&(%s>%f)",ctgry[ihist],                       selection,brname, NB_cut) );
    hist1[ihist]->Sumw2();
    hist2[ihist]->Sumw2();
    hist1[ihist]->Scale(1.0/nstream);
    hist2[ihist]->Scale(1.0/nstream);
    mh1->Add( hist1[ihist] );
    mh2->Add( hist2[ihist] );
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  can->cd(1);
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist1[ihist]->SetFillColor(col[ihist]);
    hist1[ihist]->SetLineColor(col[ihist]);
  }
  mh1->DrawClone("hist");
  for( Int_t ihist=nhist-1; ihist>=0; ihist-- ) leg->AddEntry( hist1[ihist], ctgry_name[ihist], "F" );
  leg->DrawClone();
  //++++++++++++++
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist1[ihist]->Scale( 1.0/hist1[ihist]->Integral() );
    hist1[ihist]->SetMarkerStyle(1);
    hist1[ihist]->SetFillColor(0);
    hist1[ihist]->SetLineColor(col[ihist]);
  }
  can->cd(2);
  THStack* mh1_1 = new THStack( "mh1_1", Form("%s (normalized PDF);NB",selection) );
  mh1_1->Add( hist1[4] );
  mh1_1->Add( hist1[7] );
  mh1_1->DrawClone("nostack histE");
  //++++++++++++++
  can->cd(3);
  can->cd(3)->SetLogy(1);
  mh1_1->DrawClone("nostack histE");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(4);
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist2[ihist]->SetFillColor(col[ihist]);
    hist2[ihist]->SetLineColor(col[ihist]);
  }
  mh2->DrawClone("hist");
  //++++++++++++++
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist2[ihist]->Scale( 1.0/hist2[ihist]->Integral() );
    hist2[ihist]->SetMarkerStyle(1);
    hist2[ihist]->SetFillColor(0);
    hist2[ihist]->SetLineColor(col[ihist]);
  }
  can->cd(5);
  THStack* mh2_2 = new THStack( "mh2_2", Form("%s (normalized PDF);NB'",selection) );
  mh2_2->Add( hist1[4] );
  mh2_2->Add( hist1[7] );
  mh2_2->DrawClone("nostack histE");
  //++++++++++++++
  can->cd(6);
  can->cd(6)->SetLogy(1);
  mh2_2->DrawClone("nostack histE");

  can->Print("pic/nbout.eps");
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
