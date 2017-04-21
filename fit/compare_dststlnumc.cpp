#include "draws_.h"

const Char_t* brname = "eecl";
//const Char_t* brname = "eeclth1";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///*
const Int_t nhist = 8;
const Char_t* ctgry     [nhist] = {"0",     "self==-3", "self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1",   "self==-5"};
const Char_t* ctgry_name[nhist] = {"other", "double D", "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had decay)",                  "sig(falsely rec.)",                             "sig(true)", "D**"     };
const Int_t   col       [nhist] = { 4,      9,          15,                   3,            5,                                              13,                                              2,           11        };
//*/
/*
const Int_t nhist = 8;
const Char_t* ctgry     [nhist] = {"0",     "self==-3", "self==-5", "self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1"  };
const Char_t* ctgry_name[nhist] = {"other", "double D", "D**",      "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had decay)",                  "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,      9,          11,         15,                   3,            5,                                              13,                                              2,         };
*/
/*
const Int_t nhist = 13;
const Char_t* ctgry     [nhist] = {"0",    "self==-7", "self==-2",         "self==-1",          "self==-4",        "self==-6",            "self==-3", "self==-5","self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1"  };
const Char_t* ctgry_name[nhist] = {"other","qq",       "hadronic decay",   "non-reso semilept", "cf from D*D(*)",  "cf from B^{+}B^{-}",  "double D", "D**",     "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had dec)",                    "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,      8,         1,                  14,                  16,                 12,                   9,          11,        15,                   3,            5,                                              13,                                              2          };
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t* selection = "nb_mode0_test13_nor>0.8";
//const Char_t* selection = "1";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_mode0_test13_nor/gMC_*s0[0-5]*.root";
const Int_t    nstream      = 6;
const Char_t*  infile_dstst = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_mode0_test13_nor/DssMC_*.root";
const Double_t ndstst       = 2.7118;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Double_t xmin = 0.0;
const Int_t    xbin = 24;
const Double_t xmax = 1.2;
//const Int_t    xbin = 48;
//const Double_t xmax = 2.4;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c_gmc = new TChain("h15");
  std::cout << "[infile gMC] " << infile_gmc << " : ";
  std::cout << c_gmc->Add(infile_gmc)        << " files, ";
  std::cout << c_gmc->GetEntries()           << " entries, ";
  std::cout << nstream                       << " streams" << std::endl;

  TChain* c_dstst = new TChain("h15");
  std::cout << "[infile D**lnu MC] "       << infile_dstst << " : ";
  std::cout << c_dstst->Add(infile_dstst)  << " files, ";
  std::cout << c_dstst->GetEntries()       << " entries, ";
  std::cout << ndstst                      << " streams" << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 4, 2 );
  can->Draw();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TLegend* leg  = new TLegend( 0.55,0.65,0.99,0.94 );
  THStack* mh_gmc     = new THStack( "mh_gmc",   Form("%s (gMC);E_{ECL} [GeV]",      selection) );
  THStack* mh_dstst   = new THStack( "mh_dstst", Form("%s (D**lnu MC);E_{ECL} [GeV]",selection) );
  TH1D**   hist_gmc   = new TH1D*[nhist];
  TH1D**   hist_dstst = new TH1D*[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist_gmc  [ihist] = new TH1D( Form("hg%d",ihist), Form("hg%d",ihist), xbin, xmin, xmax );
    hist_dstst[ihist] = new TH1D( Form("hd%d",ihist), Form("hd%d",ihist), xbin, xmin, xmax );

    if( ihist==0 ) c_gmc->Project( Form("hg%d",ihist), Form("%s",brname), Form("(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection ) );
    else           c_gmc->Project( Form("hg%d",ihist), Form("%s",brname), Form("(%s)&&(%s)",ctgry[ihist],                       selection ) );

    if( ihist==0 ) c_dstst->Project( Form("hd%d",ihist), Form("%s",brname), Form("(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection) );
    else           c_dstst->Project( Form("hd%d",ihist), Form("%s",brname), Form("(%s)&&(%s)",ctgry[ihist],                       selection) );
    hist_gmc  [ihist]->Sumw2();
    hist_dstst[ihist]->Sumw2();
    hist_gmc  [ihist]->Scale(1.0/nstream);
    hist_dstst[ihist]->Scale(1.0/ndstst );

    mh_gmc  ->Add( hist_gmc  [ihist] );
    mh_dstst->Add( hist_dstst[ihist] );
    std::cout << std::setw( 3) << std::right << ihist                          << " : "
	      << std::setw(35) << std::right << ctgry_name[ihist]              << " : "
	      << std::setw( 8) << std::right << hist_gmc  [ihist]->Integral()  << " : "
	      << std::setw( 8) << std::right << hist_dstst[ihist]->Integral()  << std::endl;
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist_gmc  [ihist]->SetFillColor(col[ihist]);
    hist_gmc  [ihist]->SetLineColor(col[ihist]);
    hist_dstst[ihist]->SetFillColor(col[ihist]);
    hist_dstst[ihist]->SetLineColor(col[ihist]);
  }

  for( Int_t ihist=nhist-1; ihist>=0; ihist-- ) leg->AddEntry( hist_gmc[ihist], ctgry_name[ihist], "F" );

  can->cd(1);
  mh_gmc->DrawClone("hist");
  leg->DrawClone();

  can->cd(2);
  mh_dstst->DrawClone("hist");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t nhist_detail = 8;
  TH1D** hist_gmc_detail   = makeHist( "gmc_detail",   24, 0.0, 1.2, nhist_detail );
  TH1D** hist_dstst_detail = makeHist( "dstst_detail", 24, 0.0, 1.2, nhist_detail );
  TLegend* leg_detail = new TLegend( 0.55,0.65,0.99,0.94 );
  //++++++
  c_gmc  ->Project( Form("gmc_detail_%d",  0), Form("%s",brname), Form("(%s)&&(%s)",selection,"self==-5" ) );
  c_gmc  ->Project( Form("gmc_detail_%d",  1), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0)||(gm_ddst2==3&&semi2>0))"                             ) ); // D**      lnu events in gMC
  c_gmc  ->Project( Form("gmc_detail_%d",  2), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0)||(gm_ddst2==3&&semi2>0))&&(fldstst1==1||fldstst2==1)" ) ); // D**(L=1) lnu events in gMC
  c_gmc  ->Project( Form("gmc_detail_%d",  3), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0)||(gm_ddst2==3&&semi2>0))&&(fldstst1==2||fldstst2==2)" ) ); // D**(rad) lnu events in gMC
  c_gmc  ->Project( Form("gmc_detail_%d",  4), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0&& (abs(rootdf1)==10411||abs(rootdf1)==10421) )|| (gm_ddst2==3&&semi2>0&& (abs(rootdf2)==10411||abs(rootdf2)==10421) ) )" ) ); // D**(D0*) lnu events in gMC
  c_gmc  ->Project( Form("gmc_detail_%d",  5), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0&& (abs(rootdf1)==20413||abs(rootdf1)==20423) )|| (gm_ddst2==3&&semi2>0&& (abs(rootdf2)==20413||abs(rootdf2)==20423) ) )" ) ); // D**(D1') lnu events in gMC
  c_gmc  ->Project( Form("gmc_detail_%d",  6), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0&& (abs(rootdf1)==10413||abs(rootdf1)==10423) )|| (gm_ddst2==3&&semi2>0&& (abs(rootdf2)==10413||abs(rootdf2)==10423) ) )" ) ); // D**(D1 ) lnu events in gMC
  c_gmc  ->Project( Form("gmc_detail_%d",  7), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0&& (abs(rootdf1)==  415||abs(rootdf1)==  425) )|| (gm_ddst2==3&&semi2>0&& (abs(rootdf2)==  415||abs(rootdf2)==  425) ) )" ) ); // D**(D2*) lnu events in gMC

  c_dstst->Project( Form("dstst_detail_%d",0), Form("%s",brname), Form("(%s)&&(%s)",selection,"1" ) );
  c_dstst->Project( Form("dstst_detail_%d",1), Form("%s",brname), Form("(%s)&&(%s)",selection,"self==-5" ) );
  c_dstst->Project( Form("dstst_detail_%d",2), Form("%s",brname), Form("(%s)&&(%s)",selection,"(incl1gmc==1||incl2gmc==1)&&(( gm_ddst1==3&&semi1>0)||(gm_ddst2==3&&semi2>0))&&(fldstst1==1||fldstst2==1)" ) ); // D**(L=1) lnu events in gMC
  c_dstst->Project( Form("dstst_detail_%d",3), Form("%s",brname), Form("(%s)&&(%s)",selection,"(incl1gmc==1||incl2gmc==1)&&(( gm_ddst1==3&&semi1>0)||(gm_ddst2==3&&semi2>0))&&(fldstst1==2||fldstst2==2)" ) ); // D**(rad) lnu events in gMC
  c_dstst->Project( Form("dstst_detail_%d",4), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0&& (abs(rootdf1)==10411||abs(rootdf1)==10421) )|| (gm_ddst2==3&&semi2>0&& (abs(rootdf2)==10411||abs(rootdf2)==10421) ) )" ) ); // D**(D0*) lnu events in gMC
  c_dstst->Project( Form("dstst_detail_%d",5), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0&& (abs(rootdf1)==20413||abs(rootdf1)==20423) )|| (gm_ddst2==3&&semi2>0&& (abs(rootdf2)==20413||abs(rootdf2)==20423) ) )" ) ); // D**(D1') lnu events in gMC
  c_dstst->Project( Form("dstst_detail_%d",6), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0&& (abs(rootdf1)==10413||abs(rootdf1)==10423) )|| (gm_ddst2==3&&semi2>0&& (abs(rootdf2)==10413||abs(rootdf2)==10423) ) )" ) ); // D**(D1 ) lnu events in gMC
  c_dstst->Project( Form("dstst_detail_%d",7), Form("%s",brname), Form("(%s)&&(%s)",selection,"(( gm_ddst1==3&&semi1>0&& (abs(rootdf1)==  415||abs(rootdf1)==  425) )|| (gm_ddst2==3&&semi2>0&& (abs(rootdf2)==  415||abs(rootdf2)==  425) ) )" ) ); // D**(D2*) lnu events in gMC

  
  for( Int_t ihist=0; ihist<nhist_detail; ihist++ ){
    hist_gmc_detail  [ihist]->SetLineColor(ihist+1);
    hist_dstst_detail[ihist]->SetLineColor(ihist+1);
  }
  //++++++
  for( Int_t ihist=0; ihist<nhist_detail; ihist++ ){
    hist_gmc_detail  [ihist]->SetMarkerStyle(0);
    hist_dstst_detail[ihist]->SetMarkerStyle(0);
    hist_gmc_detail  [ihist]->Sumw2();
    hist_dstst_detail[ihist]->Sumw2();
    hist_gmc_detail  [ihist]->Scale(1.0/nstream);
    hist_dstst_detail[ihist]->Scale(1.0/ndstst );
    hist_gmc_detail  [ihist]->SetMinimum(0);
    hist_dstst_detail[ihist]->SetMinimum(0);
    hist_gmc_detail  [ihist]->SetMaximum(35);
    hist_dstst_detail[ihist]->SetMaximum(35);

    std::cout << std::setw( 3) << std::right << ihist                                 << " : "
	      << std::setw( 8) << std::right << hist_gmc_detail  [ihist]->Integral()  << " : "
	      << std::setw( 8) << std::right << hist_dstst_detail[ihist]->Integral()  << std::endl;
  }
  leg_detail->AddEntry( hist_gmc_detail[0], "self==-5 / total",    "L" );
  leg_detail->AddEntry( hist_gmc_detail[1], "D** l#nu / self==-5", "L" );
  leg_detail->AddEntry( hist_gmc_detail[2], "D**(L=1) l#nu",       "L" );
  leg_detail->AddEntry( hist_gmc_detail[3], "D**(rad) l#nu",       "L" );
  leg_detail->AddEntry( hist_gmc_detail[4], "D**(D0*) l#nu",       "L" );
  leg_detail->AddEntry( hist_gmc_detail[5], "D**(D1') l#nu",       "L" );
  leg_detail->AddEntry( hist_gmc_detail[6], "D**(D1 ) l#nu",       "L" );
  leg_detail->AddEntry( hist_gmc_detail[7], "D**(D2*) l#nu",       "L" );
  //++++++
  can->cd(3);
  for( Int_t ihist=0; ihist<4; ihist++ ) hist_gmc_detail[ihist]->Draw( ihist ? "histEsame" : "histE" );
  leg_detail->Draw();

  can->cd(4);
  for( Int_t ihist=0; ihist<4; ihist++ ) hist_dstst_detail[ihist]->Draw( ihist ? "histEsame" : "histE" );

  can->cd(5);
  for( Int_t ihist=4; ihist<nhist_detail; ihist++ ) hist_gmc_detail[ihist]->Draw( ihist!=4 ? "histEsame" : "histE" );
  leg_detail->Draw();

  can->cd(6);
  for( Int_t ihist=4; ihist<nhist_detail; ihist++ ) hist_dstst_detail[ihist]->Draw( ihist!=4 ? "histEsame" : "histE" );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  //can->Print("pic/compare_dststlnumc.eps");
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
