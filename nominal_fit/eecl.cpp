#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

Double_t cal_tmp_weight( TTree* f_chain, Int_t f_ievt ){
  f_chain->GetEntry(f_ievt);
  Double_t weight = 1.0;

  if( f_chain->GetLeaf("rm_dst1")->GetValue()==111 || f_chain->GetLeaf("rm_dst2")->GetValue()==111 ){ // D0 & D+
    if( f_chain->GetLeaf("dst1self")->GetValue()==1 && f_chain->GetLeaf("dst2self")->GetValue()==1 ) weight /= 1.14;
    else                                                                                             weight /= 1.24;
  }else{ // D0 & D0
    if( f_chain->GetLeaf("dst1self")->GetValue()==1 && f_chain->GetLeaf("dst2self")->GetValue()==1 ) weight /= 1.50;
    else                                                                                             weight /= 1.29;
  }
  return weight;
}

const Char_t*  brname   = "eecl";
//const Char_t*  brname   = "eecl_exp";
const Int_t    xbin     = 24;
const Double_t xmin     = 0.0;
const Double_t xmax     = 1.2;
//const Char_t* selection = "1";
//const Char_t* selection = "rempi0_1==1 && remks==0 && remtrk==0";
//const Char_t* selection = "nb_mode0_test13_nor<0.0";
const Char_t* selection = "nb_mode0_test13_nor>0.8";
//const Char_t* selection = "nb_mode0_test13_nor<0.8";
//const Char_t* selection = "nb_mode0_test13_nor>0.0";
//const Char_t* selection = "nb_mode0_test13_nor>0.8 && rempi0_1==1 && remks==0 && remtrk==0";
//const Char_t* selection = "nb_mode0_test13_nor>0.8 && rempi0_1==1 && remks==0 && remtrk==0 && (rm_dst1==111 || rm_dst2==111)";
//const Char_t* selection = "nb_mode0_test13_nor>0.8 && rempi0_1==1";
//const Char_t* selection = "atan(cosdll)<-1.1 && rempi0_1==1 && remks==0 && remtrk==0";
//const Char_t* selection = "nb_mode0_test13_nor>0.8&&!(rm_dst1==111 || rm_dst2==111)";

//const Char_t* selection_mc = "1";
const Char_t*  selection_mc = "ctgrsyst!=7 && ctgrsyst!=8";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///*
const Bool_t fl_dststmc     = true; // true(gMC+D**MC), false(gMC)
const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Int_t    nstream      = 10;
const Char_t*  infile_dstst = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut_bcs_vtx/DssMC_*.root";
const Double_t ndstst       = 2.7118;
const Bool_t   fl_dt        = !true;
const Char_t*  infile_dt    = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/RD_*.root";
//*/
/*
const Bool_t fl_dststmc     = true; // true(gMC+D**MC), false(gMC)
const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut/gMC_*s0[0-9]*.root";
const Int_t    nstream      = 10;
const Char_t*  infile_dstst = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_noremcut/DssMC_*.root";
const Double_t ndstst       = 2.7118;
const Bool_t   fl_dt        = true;
const Char_t*  infile_dt    = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut/RD_*.root";
*/

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

/* // fake D(*) plot (top is D**)
const Int_t nhist = 6;
const Char_t* ctgry     [nhist] = {"0", "!(dst1self==1&&dst2self==1)",    "dst1self==1&&dst2self==1&&self==-3", "dst1self==1&&dst2self==1&&( (self==0&&gm_semi<0) || (self==2) )",    "dst1self==1&&dst2self==1&&( (self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)) || (self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)) || (self==1) )", "dst1self==1&&dst2self==1&&self==-5"  };
const Char_t* ctgry_name[nhist] = {"other", "fakeD(*)", "double D",    "norm",           "sig", "D**" };
const Int_t   col       [nhist] = { 4,  7,    9,                              3,           2,       11  };
*/

///* // fake D(*) plot for JPS
const Int_t nhist = 5;
const Char_t* ctgry     [nhist] = {"0", "!(dst1self==1&&dst2self==1)",  "dst1self==1&&dst2self==1&&self==-5", "dst1self==1&&dst2self==1&&( (self==0&&gm_semi<0) || (self==2) )",    "dst1self==1&&dst2self==1&&( (self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)) || (self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)) || (self==1) )"  };
const Char_t* ctgry_name[nhist] = {"others", "fakeD(*)", "D**", "norm", "sig" };
const Int_t   col       [nhist] = {      9,          7,    11,     15,    2   };
//*/

/* // fake D(*) plot
const Int_t nhist = 6;
const Char_t* ctgry     [nhist] = {"0", "!(dst1self==1&&dst2self==1)",    "dst1self==1&&dst2self==1&&self==-3", "dst1self==1&&dst2self==1&&self==-5", "dst1self==1&&dst2self==1&&( (self==0&&gm_semi<0) || (self==2) )",    "dst1self==1&&dst2self==1&&( (self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)) || (self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)) || (self==1) )"  };
const Char_t* ctgry_name[nhist] = {"other", "fakeD(*)", "double D", "D**",      "norm",           "sig"};
const Int_t   col       [nhist] = { 4,  7,    9,          11,                        3,           2,         };
*/

/* // fake D(*) plot
const Int_t nhist = 9;
const Char_t* ctgry     [nhist] = {"0", "!(dst1self==1&&dst2self==1)",    "dst1self==1&&dst2self==1&&self==-3", "dst1self==1&&dst2self==1&&self==-5", "dst1self==1&&dst2self==1&&self==0&&gm_semi<0", "dst1self==1&&dst2self==1&&self==2",    "dst1self==1&&dst2self==1&&self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "dst1self==1&&dst2self==1&&self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "dst1self==1&&dst2self==1&&self==1"  };
const Char_t* ctgry_name[nhist] = {"other", "fakeD(*)", "double D", "D**",      "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had decay)",                  "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,  7,    9,          11,         15,                   3,            5,                                              13,                                              2,         };
*/

/* // detail plot
const Int_t nhist = 13;
const Char_t* ctgry     [nhist] = {"0",    "self==-7", "self==-2",         "self==-1",          "self==-4",        "self==-6",            "self==-3", "self==-5","self==0&&gm_semi<0", "self==2",    "self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "self==1"  };
const Char_t* ctgry_name[nhist] = {"other","qq",       "hadronic decay",   "non-reso semilept", "cf from D*D(*)",  "cf from B^{+}B^{-}",  "double D", "D**",     "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had dec)",                    "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,      8,         1,                  14,                  16,                 12,                   9,          11,        15,                   3,            5,                                              13,                                              2          };
*/

/* // detail plot with fake D(*)
const Int_t nhist = 14;
const Char_t* ctgry     [nhist] = {"0",  "!(dst1self==1&&dst2self==1)",  "dst1self==1&&dst2self==1&&self==-7", "dst1self==1&&dst2self==1&&self==-2",         "dst1self==1&&dst2self==1&&self==-1",          "dst1self==1&&dst2self==1&&self==-4",        "dst1self==1&&dst2self==1&&self==-6",            "dst1self==1&&dst2self==1&&self==-3", "dst1self==1&&dst2self==1&&self==-5","dst1self==1&&dst2self==1&&self==0&&gm_semi<0", "dst1self==1&&dst2self==1&&self==2",    "dst1self==1&&dst2self==1&&self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)", "dst1self==1&&dst2self==1&&self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)", "dst1self==1&&dst2self==1&&self==1"  };
const Char_t* ctgry_name[nhist] = {"other", "fakeD(*)", "qq",       "hadronic decay",   "non-reso semilept", "cf from D*D(*)",  "cf from B^{+}B^{-}",  "double D", "D**",     "norm(falsely rec.)", "norm(true)", "sig(cf from #tau had dec)",                    "sig(falsely rec.)",                             "sig(true)"};
const Int_t   col       [nhist] = { 4,      7, 8,         1,                  14,                  16,                 12,                   9,          11,        15,                   3,            5,                                              13,                                              2          };
*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Read_Data( calib_file, true );
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

  TChain* c_dt = new TChain("h15");
  std::cout << "[infile Data] "      << infile_dt << " : ";
  std::cout << c_dt->Add(infile_dt)  << " files, ";
  std::cout << c_dt->GetEntries()    << " entries, "
	    << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can" );
  can->Draw();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg  = new TLegend( 0.55,0.65,0.99,0.94 );
  THStack* mh   = new THStack( "mh", Form("%s,%s;E_{ECL} [GeV]",selection,selection_mc) );
  TH1D**   hist       = new TH1D*[nhist];
  TH1D**   hist_gmc   = new TH1D*[nhist];
  TH1D**   hist_dstst = new TH1D*[nhist];
  TH1D*    hist_dt    = new TH1D( "dt", Form("%s;E_{ECL} [GeV]",selection), xbin,xmin, xmax );

  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist      [ihist] = new TH1D( Form("h%d", ihist), Form("h%d", ihist), xbin, xmin, xmax );
    hist_gmc  [ihist] = new TH1D( Form("hg%d",ihist), Form("hg%d",ihist), xbin, xmin, xmax );
    hist_dstst[ihist] = new TH1D( Form("hd%d",ihist), Form("hd%d",ihist), xbin, xmin, xmax );

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    TTree* tmp_tree_gmc;
    if( ihist==0 ) tmp_tree_gmc = c_gmc->CopyTree( Form("(%s)&&(%s)&&(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection, selection_mc, (fl_dststmc ? "( flmcddst==1 || (flmcddst==0 && !(2<ctgrsyst&&ctgrsyst<9)) )" : "( flmcddst==0 )")) );
    else           tmp_tree_gmc = c_gmc->CopyTree( Form("(%s)&&(%s)&&(%s)&&(%s)",ctgry[ihist],                       selection, selection_mc, (fl_dststmc ? "( flmcddst==1 || (flmcddst==0 && !(2<ctgrsyst&&ctgrsyst<9)) )" : "( flmcddst==0 )")) );
    TTree* tmp_tree_dstst;
    if( ihist==0 ) tmp_tree_dstst = c_dstst->CopyTree( Form("(%s)&&(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection, selection_mc) );
    else           tmp_tree_dstst = c_dstst->CopyTree( Form("(%s)&&(%s)&&(%s)",ctgry[ihist],                       selection, selection_mc) );
    
    for( Int_t ievt=0; ievt<tmp_tree_gmc->GetEntries(); ievt++ ){
      Double_t weight     = cal_weight( tmp_tree_gmc, ievt, 1.0 );
      Double_t tmp_weight = 1.0;
      //tmp_weight = cal_tmp_weight( tmp_tree_gmc, ievt ); // tmpppppp
      Double_t val    = tmp_tree_gmc->GetLeaf(brname)->GetValue();
      hist_gmc[ihist]->Fill( val, tmp_weight*weight );
    }
    
    for( Int_t ievt=0; ievt<tmp_tree_dstst->GetEntries(); ievt++ ){
      Double_t weight     = cal_weight( tmp_tree_dstst, ievt, 1.0 );
      Double_t tmp_weight = 1.0;
      //tmp_weight = cal_tmp_weight( tmp_tree_dstst, ievt ); // tmppppppp
      Double_t val    = tmp_tree_dstst->GetLeaf(brname)->GetValue();
      hist_dstst[ihist]->Fill( val, tmp_weight*weight );
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    hist_gmc  [ihist]->Sumw2();
    hist_dstst[ihist]->Sumw2();
    hist_gmc  [ihist]->Scale(1.0/nstream);
    hist_dstst[ihist]->Scale(1.0/ndstst );

    hist[ihist]->Add( hist_gmc[ihist] );
    if( fl_dststmc ) hist[ihist]->Add( hist_dstst[ihist] );

    //mh->Add( hist[ihist] ); // default, comment out for JPS plots, tmppppp
    std::cout << std::setw( 3) << std::right << ihist                          << " : "
	      << std::setw(35) << std::right << ctgry_name[ihist]              << " : "
	      << std::setw( 8) << std::right << hist      [ihist]->Integral()  << " = "
	      << std::setw( 8) << std::right << hist_gmc  [ihist]->Integral()  << " + "
	      << std::setw( 8) << std::right << hist_dstst[ihist]->Integral()  << std::endl;
  }

  // plots for JPS slide
  hist[1]->SetFillStyle(1001); // fake D(*)
  hist[2]->SetFillStyle(1001); // D**
  hist[3]->SetFillStyle(1001); // norm
  mh->Add( hist[1] ); // fake D(*)
  mh->Add( hist[0] ); // other
  mh->Add( hist[2] ); // D**
  mh->Add( hist[3] ); // norm
  mh->Add( hist[4] ); // signal



  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl
	    << "< # of events in E_ECL < 0.50 GeV region >"
	    << std::endl;
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    std::cout << std::setw( 3) << std::right << ihist                              << " : "
	      << std::setw(35) << std::right << ctgry_name[ihist]                  << " : "
	      << std::setw( 8) << std::right << hist      [ihist]->Integral(1,10)  << " = "
	      << std::setw( 8) << std::right << hist_gmc  [ihist]->Integral(1,10)  << " + "
	      << std::setw( 8) << std::right << hist_dstst[ihist]->Integral(1,10)  << std::endl;
  }
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  c_dt->Project( "dt", brname, selection );
  hist_dt->Sumw2();
  hist_dt->SetMinimum(0.0);
  std::cout << "+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  std::cout << hist_dt->Integral() << " entries in data" << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(1);
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist]->SetFillColor(col[ihist]);
    hist[ihist]->SetLineColor(col[ihist]);
  }

  if( !fl_dt ) mh->DrawClone("hist");
  else if( mh->GetMaximum() > hist_dt->GetMaximum() ){
    mh->DrawClone("hist");
    hist_dt->Draw("same");
  }else{
    hist_dt->Draw();
    mh->DrawClone("histsame");
    hist_dt->Draw("same");
  }
  for( Int_t ihist=nhist-1; ihist>=0; ihist-- ) leg->AddEntry( hist[ihist], ctgry_name[ihist], "F" );
  leg->DrawClone();

  ///*
  // plots for JPS slide
  THStack* tmp_mh   = new THStack( "tmp_mh", Form("%s,%s;E_{ECL} [GeV]",selection,selection_mc) );
  TH1D* tmp_h1 = new TH1D(*hist[1]);
  TH1D* tmp_h2 = new TH1D(*hist[2]);
  TH1D* tmp_h3 = new TH1D(*hist[3]);
  tmp_h1->SetFillStyle(3018); // fake D(*)
  tmp_h1->SetFillColor(   4); // fake D(*)
  tmp_h2->SetFillStyle(3006); // D**
  tmp_h2->SetFillColor(  17); // D**
  tmp_h3->SetFillStyle(3017); // norm
  tmp_h3->SetFillColor(   3); // norm
  tmp_mh->Add( tmp_h1  ); // fake D(*)
  tmp_mh->Add( hist[0] ); // other
  tmp_mh->Add( tmp_h2  ); // D**
  tmp_mh->Add( tmp_h3  ); // norm
  tmp_mh->Add( hist[4] ); // signal
  tmp_mh->DrawClone("histsame");
  //*/
  //++++++++++++++

  can->Print("pic/eecl.eps");
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
