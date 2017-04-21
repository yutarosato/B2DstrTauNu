#include "draws_.h"

#include "draws_roofit_.h"

const Char_t* brname = "eecl";
//const Char_t* brname = "eeclth1";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/* // simple plot (top is signal)
const Int_t nhist = 4;
const Char_t* ctgry     [nhist] = {"0",      "self==-5", "(self==0&&gm_semi<0)||self==2", "(self==0&&gm_semi>0&&(taulep1==0&&taulep2==0))||(self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0))||self==1"};
const Char_t* ctgry_name[nhist] = {"other",                  "D**",  "normalization",     "signal"                                                                                                  };
const Int_t   col       [nhist] = { 4,      9,                                3,         2                                                                                                        };
*/
/* // simple plot (top is D**)
const Int_t nhist = 4;
const Char_t* ctgry     [nhist] = {"0",     "(self==0&&gm_semi<0)||self==2",  "(self==0&&gm_semi>0&&(taulep1==0&&taulep2==0))||(self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0))||self==1",   "self==-5"};
const Char_t* ctgry_name[nhist] = {"other", "normalization",                  "signal",                                                                                                     "D**"     };
const Int_t   col       [nhist] = { 4,      9,                               2,                                                                                                            11        };
*/
/* // normal plot (top is signal)
const Int_t nhist = 8;
const Char_t* ctgry     [nhist] = {"0",     "self==-3", "self==-5", "self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1"  };
const Char_t* ctgry_name[nhist] = {"other", "double D", "D**",      "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had decay)",                  "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,      9,          11,         15,                   3,            5,                                              13,                                              2,         };
*/
/* // normal plot (top is D**)
const Int_t nhist = 8;
const Char_t* ctgry     [nhist] = {"0",     "self==-3", "self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1",   "self==-5"};
const Char_t* ctgry_name[nhist] = {"other", "double D", "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had decay)",                  "sig(falsely rec.)",                             "sig(true)", "D**"     };
const Int_t   col       [nhist] = { 4,      9,          15,                   3,            5,                                              13,                                              2,           11        };
*/
///* // fake D(*) plot
const Int_t nhist = 9;
const Char_t* ctgry     [nhist] = {"0", "!(dst1self==1&&dst2self==1)",    "dst1self==1&&dst2self==1&&self==-3", "dst1self==1&&dst2self==1&&self==-5", "dst1self==1&&dst2self==1&&self==0&&gm_semi<0", "dst1self==1&&dst2self==1&&self==2",    "dst1self==1&&dst2self==1&&self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "dst1self==1&&dst2self==1&&self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "dst1self==1&&dst2self==1&&self==1"  };
const Char_t* ctgry_name[nhist] = {"other", "fakeD(*)", "double D", "D**",      "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had decay)",                  "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,  7,    9,          11,         15,                   3,            5,                                              13,                                              2,         };
//*/
/* // detail plot
const Int_t nhist = 13;
const Char_t* ctgry     [nhist] = {"0",    "self==-7", "self==-2",         "self==-1",          "self==-4",        "self==-6",            "self==-3", "self==-5","self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1"  };
const Char_t* ctgry_name[nhist] = {"other","qq",       "hadronic decay",   "non-reso semilept", "cf from D*D(*)",  "cf from B^{+}B^{-}",  "double D", "D**",     "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had dec)",                    "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,      8,         1,                  14,                  16,                 12,                   9,          11,        15,                   3,            5,                                              13,                                              2          };
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//const Char_t* selection = "nb_mode0_test13_nor>0.8";
//const Char_t* selection = "nb_mode0_test13_nor>0.8&&( (cosdll==cosdl1&&kfd1chi2/kfd1ndf<100&&kfs1chi2/kfs1ndf<100) || (cosdll==cosdl2&&kfd2chi2/kfd2ndf<100&&kfs2chi2/kfs2ndf<100) )";
const Char_t* selection = "nb_mode0_test13_nor>0.8&&( (cosdll==cosdl1&&kfd1chi2/kfd1ndf<100&&kfs1chi2/kfs1ndf<100) || (cosdll==cosdl2&&kfd2chi2/kfd2ndf<100&&kfs2chi2/kfs2ndf<100) )&&(dfl1&&dfl2&&dfl1*dfl2==1)";
//const Char_t* selection = "1";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Bool_t fl_dststmc = !true; // true(gMC+D**MC), false(gMC)
//const Char_t* infile_gmc = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_mode0_test13_nor_setAA_HH/gMC_*s0[0-5]*.root";
//const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_bcs_vtx_mode0_test13_nor/gMC_*s0[0-5]*.root";
//const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_bcs_vtx_mode0_test13_nor/gMC_mixed_*s0[0-5]*.root";
//const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-5]*.root";
const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_noflavorcut_bcs_vtx/gMC_*s0[0-5]*.root";
//const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/merge_cut_noremtrkcut_bcs_vtx/gMC_*s0[0-5]*.root";
//const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/merge_cut_noflavorcut_bcs_vtx/gMC_*s0[0-5]*.root";
const Int_t    nstream      = 6;
const Char_t*  infile_dstst = "/home/belle/syutaro/dstrtaunu/ana/NB/hbk/hbk_mode0_test13_nor/DssMC_*.root";
const Double_t ndstst       = 2.7118;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Double_t xmin = 0.0;
const Int_t    xbin = 24;
//const Int_t    xbin = 8;
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
  std::cout << ndstst                      << " times, "
	    << fl_dststmc                  << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 2, 1 );
  can->Draw();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg  = new TLegend( 0.55,0.65,0.99,0.94 );
  THStack* mh   = new THStack( "mh", Form("%s;E_{ECL} [GeV]",selection) );
  TH1D**   hist       = new TH1D*[nhist];
  TH1D**   hist_gmc   = new TH1D*[nhist];
  TH1D**   hist_dstst = new TH1D*[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist      [ihist] = new TH1D( Form("h%d", ihist), Form("h%d", ihist), xbin, xmin, xmax );
    hist_gmc  [ihist] = new TH1D( Form("hg%d",ihist), Form("hg%d",ihist), xbin, xmin, xmax );
    hist_dstst[ihist] = new TH1D( Form("hd%d",ihist), Form("hd%d",ihist), xbin, xmin, xmax );

    //if( ihist==0 ) c_gmc->Project( Form("hg%d",ihist), Form("%s",brname), Form("(%s)&&(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection, (fl_dststmc ? "self!=-5" : "1")) );
    //else           c_gmc->Project( Form("hg%d",ihist), Form("%s",brname), Form("(%s)&&(%s)&&(%s)",ctgry[ihist],                       selection, (fl_dststmc ? "self!=-5" : "1")) );

    if( ihist==0 ) c_gmc->Project( Form("hg%d",ihist), Form("%s",brname), Form("(%s)&&(%s)&&(%s)&&(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection, (fl_dststmc ? "self!=-5" : "1"), makeCut_pi0mass_d(0.010, 0.010).c_str(), makeCut_pi0mass_dstr(0.010, 0.010).c_str()) );
    else           c_gmc->Project( Form("hg%d",ihist), Form("%s",brname), Form("(%s)&&(%s)&&(%s)&&(%s)&&(%s)",ctgry[ihist],                       selection, (fl_dststmc ? "self!=-5" : "1"), makeCut_pi0mass_d(0.010, 0.010).c_str(), makeCut_pi0mass_dstr(0.010, 0.010).c_str()) );

    if( ihist==0 ) c_dstst->Project( Form("hd%d",ihist), Form("%s",brname), Form("(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection) );
    else           c_dstst->Project( Form("hd%d",ihist), Form("%s",brname), Form("(%s)&&(%s)",ctgry[ihist],                       selection) );
    hist_gmc  [ihist]->Sumw2();
    hist_dstst[ihist]->Sumw2();
    hist_gmc  [ihist]->Scale(1.0/nstream);
    hist_dstst[ihist]->Scale(1.0/ndstst );

    hist[ihist]->Add( hist_gmc[ihist] );
    if( fl_dststmc ) hist[ihist]->Add( hist_dstst[ihist] );
    mh->Add( hist[ihist] );
    std::cout << std::setw( 3) << std::right << ihist                          << " : "
	      << std::setw(35) << std::right << ctgry_name[ihist]              << " : "
	      << std::setw( 8) << std::right << hist      [ihist]->Integral()  << " = "
	      << std::setw( 8) << std::right << hist_gmc  [ihist]->Integral()  << " + "
	      << std::setw( 8) << std::right << hist_dstst[ihist]->Integral()  << std::endl;
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(1);
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist]->SetFillColor(col[ihist]);
    hist[ihist]->SetLineColor(col[ihist]);
  }
  mh->DrawClone("hist");
  for( Int_t ihist=nhist-1; ihist>=0; ihist-- ) leg->AddEntry( hist[ihist], ctgry_name[ihist], "F" );
  leg->DrawClone();

  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist]->Scale( 1.0/hist[ihist]->Integral() );
    hist[ihist]->SetMarkerStyle(1);
    hist[ihist]->SetFillColor(0);
    hist[ihist]->SetLineColor(col[ihist]);
  }
  //++++++++++++++
  can->cd(2);
  THStack* mh1 = new THStack( "mh1", Form("%s (normalized PDF);E_{ECL} [GeV]",selection) );
  mh1->Add( hist[3] );
  mh1->Add( hist[6] );
  mh1->Add( hist[7] );
  //mh1->Add( hist[2] );
  //mh1->Add( hist[4] );
  //mh1->Add( hist[7] );
  //mh1->Add( hist[7] );
  //mh1->Add( hist[9] );
  //mh1->Add( hist[12]);
  mh1->DrawClone("nostack histE");

  can->Print("pic/eecl.eps");
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
