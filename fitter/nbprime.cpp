#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

const Char_t*  brname = "nb_mode0_test13_nor";
const Int_t    xbin   =   30;
const Double_t xmin   = -10.0;
const Double_t xmax   =  10.0;
//const Char_t* selection = "eecl < 0.5";
const Char_t* selection = "1";
const Int_t    ybin =  24;
const Double_t ymin = 0.0;
const Double_t ymax = 1.2;
const Char_t*  ybrname = "eecl";
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
const Int_t nhist = 6;
const Char_t* ctgry     [nhist] = {"0", "!(dst1self==1&&dst2self==1)",    "dst1self==1&&dst2self==1&&self==-3", "dst1self==1&&dst2self==1&&self==-5", "dst1self==1&&dst2self==1&&( (self==0&&gm_semi<0) || (self==2) )",    "dst1self==1&&dst2self==1&&( (self==0&&gm_semi>0&&(taulep1==0&&taulep2==0)) || (self==0&&gm_semi>0&&!(taulep1==0&&taulep2==0)) || (self==1) )"  };
const Char_t* ctgry_name[nhist] = {"other", "fakeD(*)", "double D", "D**",      "norm",           "sig"};
const Int_t   col       [nhist] = { 4,  7,    9,          11,                        3,           2,         };
//*/

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
const Bool_t fl_dststmc     = true; // true(gMC+D**MC), false(gMC)
const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Int_t    nstream      = 10;
//const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-5]*.root";
//const Int_t    nstream      = 6;
const Char_t*  infile_dstst = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut_bcs_vtx/DssMC_*.root";
const Double_t ndstst       = 2.7118;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetPadRightMargin(0.15);
  sty->SetPadLeftMargin (0.15);
  sty->SetOptStat(0);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( app.Argc()!=3  )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (int)fl_th (double)nb_th" << std::endl
	      << "  fl_th : pos(nbmin=nb_th), neg(nbmax=nb_th)" << std::endl, abort();
  Int_t    fl_nb = atoi(app.Argv(1));
  Double_t nb_th = atof(app.Argv(2));
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
 
  Double_t NB_MIN = ( c_gmc->GetMinimum(brname) > c_dstst->GetMinimum(brname) ? c_dstst->GetMinimum(brname) : c_gmc->GetMinimum(brname) );
  Double_t NB_MAX = ( c_gmc->GetMaximum(brname) > c_dstst->GetMaximum(brname) ? c_dstst->GetMaximum(brname) : c_gmc->GetMaximum(brname) );
  if     ( fl_nb > 0 ) NB_MIN = nb_th;
  else if( fl_nb < 0 ) NB_MAX = nb_th;
  std::cout << "NB(MIN) = " << NB_MIN << std::endl
	    << "NB(MAX) = " << NB_MAX << std::endl;
    
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg         = new TLegend( 0.18,0.58,0.45,0.88 );
  THStack* mh          = new THStack( "mh", Form("%s (nbmin = %f, nbmax = %f);NB",selection,NB_MIN,NB_MAX) );
  TH1D**   hist        = new TH1D*[nhist];
  TH1D**   hist_gmc    = new TH1D*[nhist];
  TH1D**   hist_dstst  = new TH1D*[nhist];
  TH2D**   hist2       = new TH2D*[nhist];
  TH2D**   hist2_gmc   = new TH2D*[nhist];
  TH2D**   hist2_dstst = new TH2D*[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist      [ihist] = new TH1D( Form("h%d", ihist), Form("h%d", ihist), xbin, xmin, xmax );
    hist_gmc  [ihist] = new TH1D( Form("hg%d",ihist), Form("hg%d",ihist), xbin, xmin, xmax );
    hist_dstst[ihist] = new TH1D( Form("hd%d",ihist), Form("hd%d",ihist), xbin, xmin, xmax );

    hist2      [ihist] = new TH2D( Form("h2%d", ihist), ctgry_name[ihist],      xbin, xmin, xmax, ybin, ymin, ymax );
    hist2_gmc  [ihist] = new TH2D( Form("h2g%d",ihist), Form("h2g%d",   ihist), xbin, xmin, xmax, ybin, ymin, ymax );
    hist2_dstst[ihist] = new TH2D( Form("h2d%d",ihist), Form("h2d%d",   ihist), xbin, xmin, xmax, ybin, ymin, ymax );
    hist2[ihist]->SetXTitle("NB'");
    hist2[ihist]->SetYTitle("E_{ECL} [GeV]");

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    TTree* tmp_tree_gmc;
    if( ihist==0 ) tmp_tree_gmc = c_gmc->CopyTree( Form("(%s)&&(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection, (fl_dststmc ? "( flmcddst==1 || (flmcddst==0 && !(2<ctgrsyst&&ctgrsyst<9&&taulep1==0&&taulep2==0)) )" : "( flmcddst==0 )")) );
    else           tmp_tree_gmc = c_gmc->CopyTree( Form("(%s)&&(%s)&&(%s)",ctgry[ihist],                       selection, (fl_dststmc ? "( flmcddst==1 || (flmcddst==0 && !(2<ctgrsyst&&ctgrsyst<9&&taulep1==0&&taulep2==0)) )" : "( flmcddst==0 )")) );
    TTree* tmp_tree_dstst;
    if( ihist==0 ) tmp_tree_dstst = c_dstst->CopyTree( Form("(%s)&&(%s)",makeCut_remain(ctgry,nhist).c_str(),selection) );
    else           tmp_tree_dstst = c_dstst->CopyTree( Form("(%s)&&(%s)",ctgry[ihist],                       selection) );
    
    for( Int_t ievt=0; ievt<tmp_tree_gmc->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( tmp_tree_gmc, ievt, 1.0 );
      Double_t val    = tmp_tree_gmc->GetLeaf( brname)->GetValue();
      Double_t yval   = tmp_tree_gmc->GetLeaf(ybrname)->GetValue();
      hist_gmc [ihist]->Fill( log( (val-NB_MIN)/(NB_MAX-val) ),       weight );
      hist2_gmc[ihist]->Fill( log( (val-NB_MIN)/(NB_MAX-val) ), yval, weight );
    }
    
    for( Int_t ievt=0; ievt<tmp_tree_dstst->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( tmp_tree_dstst, ievt, 1.0 );
      Double_t val    = tmp_tree_dstst->GetLeaf( brname)->GetValue();
      Double_t yval   = tmp_tree_dstst->GetLeaf(ybrname)->GetValue();
      hist_dstst [ihist]->Fill( log( (val-NB_MIN)/(NB_MAX-val) ),       weight );
      hist2_dstst[ihist]->Fill( log( (val-NB_MIN)/(NB_MAX-val) ), yval, weight );
    }
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    hist_gmc   [ihist]->Sumw2();
    hist_dstst [ihist]->Sumw2();
    hist_gmc   [ihist]->Scale(1.0/nstream);
    hist_dstst [ihist]->Scale(1.0/ndstst );
    hist2_gmc  [ihist]->Sumw2();
    hist2_dstst[ihist]->Sumw2();
    hist2_gmc  [ihist]->Scale(1.0/nstream);
    hist2_dstst[ihist]->Scale(1.0/ndstst );

    hist [ihist]->Add( hist_gmc [ihist] );
    hist2[ihist]->Add( hist2_gmc[ihist] );
    if( fl_dststmc ){
      hist [ihist]->Add( hist_dstst [ihist] );
      hist2[ihist]->Add( hist2_dstst[ihist] );
    }

    mh->Add( hist[ihist] );
    std::cout << std::setw( 3) << std::right << ihist                          << " : "
	      << std::setw(35) << std::right << ctgry_name[ihist]              << " : "
	      << std::setw( 8) << std::right << hist      [ihist]->Integral()  << " = "
	      << std::setw( 8) << std::right << hist_gmc  [ihist]->Integral()  << " + "
	      << std::setw( 8) << std::right << hist_dstst[ihist]->Integral()  << std::endl;
  }



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
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can1 = Canvas( "can1","can1" );
  can1->Draw();
  can1->cd(1);
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist]->SetFillColor(col[ihist]);
    hist[ihist]->SetLineColor(col[ihist]);
  }
  mh->DrawClone("hist");
  for( Int_t ihist=nhist-1; ihist>=0; ihist-- ) leg->AddEntry( hist[ihist], ctgry_name[ihist], "F" );
  leg->DrawClone();

  //++++++++++++++
  TCanvas* can2 = Canvas( "can2","can2", nhist );
  can2->Draw();
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    can2->cd(ihist+1);
    hist2[ihist]->Draw("COLZ");
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  can1->Print( Form("pic/nbprime_%.4f_%.4f_1.eps",NB_MAX,NB_MIN) );
  can2->Print( Form("pic/nbprime_%.4f_%.4f_2.eps",NB_MAX,NB_MIN) );
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
