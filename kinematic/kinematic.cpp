#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t*  lep1_brname  = "l1pcm";
const Char_t*  lep2_brname  = "l2pcm";
const Int_t    lep_nbin     =  20;
const Double_t lep_xmin     = 0.0;
const Double_t lep_xmax     = 2.0;
const Char_t*  dstr1_brname = "dst1pcm";
const Char_t*  dstr2_brname = "dst2pcm";
const Int_t    dstr_nbin    =  20;
const Double_t dstr_xmin    = 0.0;
const Double_t dstr_xmax    = 2.0;
const Char_t*  cos1_brname  = "cosdl1";
const Char_t*  cos2_brname  = "cosdl2";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t*  selection_common_mc = "1";
const Char_t*  selection_common    = "eecl<0.5 && nb_mode0_test13_nor > 0.8";

const Bool_t fl_2sveto = true; // veto D(2S) and D*(2S)

const Double_t corr_fake_d = 629/544.0;
const Int_t   npdf                = 10;
const Char_t*  pdf_name  [npdf] = { "other",       "sig",            "nor",         "dstst", "doubled",             "fake_other",                   "fake_sig",                     "fake_nor",                  "fake_dstst",                "fake_doubled" };
//const Double_t pdf_yields[npdf] = { 1.0,  230.924/183.12,  2799.73/2633.94, 115.542/344.816,  1.0, 103.61 /(77.9054*corr_fake_d), 32.285 /(19.2501*corr_fake_d), 342.255/(242.107*corr_fake_d), 60.3231/(135.362*corr_fake_d), 78.953 /(59.3656*corr_fake_d) };//0p0
//const Double_t pdf_yields[npdf] = { 1.0,  223.749/177.352, 2803.76/2633.95, 118.614/344.793,  1.0, 103.155/(77.8319*corr_fake_d), 32.2531/(19.2892*corr_fake_d), 341.565/(242.107*corr_fake_d), 61.717 /(135.362*corr_fake_d), 78.8049/(59.4594*corr_fake_d) };//0p7
//const Double_t pdf_yields[npdf] = { 1.0,  220.16 /173.269, 2806.27/2633.97, 119.442/344.818,  1.0, 102.854/(77.7355*corr_fake_d), 32.718 /(19.4611*corr_fake_d), 341.295/(242.107*corr_fake_d), 62.0393/(135.362*corr_fake_d), 78.6951/(59.4763*corr_fake_d) };//1p0
//const Double_t pdf_yields[npdf] = { 1.0,  230.631/181.906, 2799.56/2633.94, 116.145/344.82,   1.0, 103.521/(77.8918*corr_fake_d), 32.3055/(19.1722*corr_fake_d), 341.999/(242.107*corr_fake_d), 60.5956/(135.362*corr_fake_d), 78.9057/(59.3709*corr_fake_d) };//R2LQ_m0p030
//const Double_t pdf_yields[npdf] = { 1.0,  230.712/182.092, 2799.45/2633.94, 116.104/344.819,  1.0, 103.522/(77.889 *corr_fake_d), 32.353 /(19.2122*corr_fake_d), 342.004/(242.107*corr_fake_d), 60.5774/(135.362*corr_fake_d), 78.9295/(59.3857*corr_fake_d) };//R2LQ_m0p040
//const Double_t pdf_yields[npdf] = { 1.0,  246.14 /210.444, 2789.05/2633.94, 107.363/344.774,  1.0, 105.314/(78.2863*corr_fake_d), 33.1769/(21.0859*corr_fake_d), 344.874/(242.107*corr_fake_d), 56.7041/(135.362*corr_fake_d), 80.2865/(59.682 *corr_fake_d) };//R2LQ_0p340
//const Double_t pdf_yields[npdf] = { 1.0,  245.746/209.799, 2789.38/2633.93, 107.647/344.777,  1.0, 105.263/(78.2721*corr_fake_d), 33.0216/(20.9627*corr_fake_d), 344.811/(242.107*corr_fake_d), 56.8369/(135.362*corr_fake_d), 80.2709/(59.6883*corr_fake_d) };//R2LQ_0p360
//const Double_t pdf_yields[npdf] = { 1.0,  245.417/208.072, 2789.24/2633.93, 108.105/344.778,  1.0, 105.122/(78.2278*corr_fake_d), 33.3485/(21.0404*corr_fake_d), 344.527/(242.107*corr_fake_d), 57.034 /(135.362*corr_fake_d), 80.2264/(59.7016*corr_fake_d) };//R2LQ_0p400
//const Double_t pdf_yields[npdf] = { 1.0,  230.17 /181.759, 2799.58/2633.94, 116.616/344.807,  1.0, 103.51 /(77.9069*corr_fake_d), 32.1424/(19.1038*corr_fake_d), 341.901/(242.107*corr_fake_d), 60.8256/(135.362*corr_fake_d), 78.9123/(59.3935*corr_fake_d) };//S1LQ_m0p040
//const Double_t pdf_yields[npdf] = { 1.0,  240.942/203.166, 2793.98/2633.96, 107.938/344.8,    1.0, 104.808/(78.0685*corr_fake_d), 33.3646/(20.9557*corr_fake_d), 344.781/(242.107*corr_fake_d), 56.8883/(135.362*corr_fake_d), 80.0205/(59.6048*corr_fake_d) };//S1LQ_0p260
//const Double_t pdf_yields[npdf] = { 1.0,  241.32 /201.777, 2792.91/2633.95, 108.59 /344.786,  1.0, 104.749/(78.0877*corr_fake_d), 33.5744/(20.9276*corr_fake_d), 344.371/(242.107*corr_fake_d), 57.188 /(135.362*corr_fake_d), 80.0587/(59.6815*corr_fake_d) };//S1LQ_0p400
const Double_t pdf_yields[npdf] = { 1.0,  248.341/217.696, 2787.7 /2686.84, 105.955/351.689,  1.0, 105.459/(78.2761*corr_fake_d), 33.5756/(21.4158 *corr_fake_d), 345.227/(242.107*corr_fake_d), 56.0471/(135.362*corr_fake_d), 80.4675/(59.7265*corr_fake_d) };//OPT_0p36
//const Double_t pdf_yields[npdf] = { 1.0,  230.816/183.939, 2799.66/2633.94, 115.599/344.817,  1.0, 103.613/(77.8971*corr_fake_d), 32.3041/(19.354 *corr_fake_d), 342.293/(242.107*corr_fake_d), 60.3609/(135.362*corr_fake_d), 78.9739/(59.3732*corr_fake_d) };//OPV1_m2p10
//const Double_t pdf_yields[npdf] = { 1.0,  239.007/185.772, 2792.39/2633.93, 114.055/344.799,  1.0, 103.957/(78.0445*corr_fake_d), 32.9494/(19.2267*corr_fake_d), 341.895/(242.107*corr_fake_d), 59.6425/(135.362*corr_fake_d), 79.3728/(59.5881*corr_fake_d) };//OPV2_1p88
//const Double_t pdf_yields[npdf] = { 1.0,  231.183/183.892, 2799.69/2633.94, 115.099/344.833,  1.0, 103.618/(77.8796*corr_fake_d), 32.5065/(19.4342*corr_fake_d), 342.389/(242.107*corr_fake_d), 60.1132/(135.362*corr_fake_d), 78.9653/(59.3508*corr_fake_d) };//OPS1_1p05

const Int_t    col       [npdf] = {   4,                2,               3,              11,    9,                             7,                             7,                             7,                             7,                             7 };


const Char_t* pdf_selection[npdf] = { "0", // [0] other
				      "(self==1||(self==0&&gm_semi>0&&dst1self==1&&dst2self==1))",                                            // [1] sig 
				      "(self==2||(self==0&&gm_semi<0&&dst1self==1&&dst2self==1))",                                            // [2] nor
				      "(self==-5&&dst1self==1&&dst2self==1)",                                                                 // [3] D**
				      "(self==-3&&dst1self==1&&dst2self==1)",                                                                 // [4] double D
				      "(self< 0 &&!(dst1self==1&&dst2self==1)&&self!=-5&&self!=-3&&!(self==-6&&(gm_ddst1==3||gm_ddst2==3)))", // [5] faked(other)
				      "(self==0 &&!(dst1self==1&&dst2self==1)&&gm_semi>0)",                                                   // [6] faked(sig)
				      "(self==0 &&!(dst1self==1&&dst2self==1)&&gm_semi<0)",                                                   // [7] faked(nor)
				      "((self==-5||(self==-6&&(gm_ddst1==3||gm_ddst2==3)))&&!(dst1self==1&&dst2self==1))",                    // [8] faked(D**)
				      "(self==-3&&!(dst1self==1&&dst2self==1))",                                                              // [9] faked(double D)
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Bool_t   fl_use_dststmc  = true;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut_bcs_vtx/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
const Bool_t   fl_use_npmc     = true;
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/%s_weight_nb_cut_bcs_vtx/npMC_*.root";
const Double_t nstream_npmc    = 40;
//const Char_t*  fl_par_dt       = "0p0"; // for samples
//const Char_t*  fl_par_dt       = "0p7"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "R2_0p360"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "S1_0p260"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "OP_V1_m2p10"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "OP_V2_1p88"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "OP_S1_1p05"; // for samples // tmpppppp
const Char_t*  fl_par_dt       = "OP_T_0p36"; // for samples // tmpppppp
//const Char_t*  weight_table    = "../npmc/table/dstrtaunu_dpi_lep_12_all/est_weight.root"; // old
//const Char_t*  weight_table    = "../npmc/new_table/2hdmII/dstrtaunu_dpi_lep_12_all/est_weight.root";
//const Char_t*  weight_table    = "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppp
//const Char_t*  weight_table    = "../npmc/new_table/S1LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppp
//const Char_t*  weight_table    = "../npmc/new_table/OPS1/dstrtaunu_dpi_lep_12_all/est_weight.root";   // OPS1 // tmppppp
//const Char_t*  weight_table    = "../npmc/new_table/OPS2/dstrtaunu_dpi_lep_12_all/est_weight.root";   // OPS2 // tmppppp
//const Char_t*  weight_table    = "../npmc/new_table/OPV1/dstrtaunu_dpi_lep_12_all/est_weight.root";   // OPV1 // tmppppp
//const Char_t*  weight_table    = "../npmc/new_table/OPV2/dstrtaunu_dpi_lep_12_all/est_weight.root";   // OPV2 // tmppppp
const Char_t*  weight_table    = "../npmc/new_table/OPT/dstrtaunu_dpi_lep_12_all/est_weight.root";    // OPT // tmppppp


const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/RD_*.root";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  //const Char_t*  fl_par_dt    = app.Argv(1); // for init // tmpppp
  //const Char_t*  weight_table = app.Argv(2); // for init // tmpppp
  TStyle* sty = Style(1);
  sty->SetPadGridX(0);
  sty->SetPadGridY(0);
  std::stringstream sTmp;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  // < Construct PDF >
  // <TChain>
  sTmp.str("");
  sTmp.clear();
  sTmp << Form("eecl<%f",eecl_xmax);
  sTmp << " && " << selection_common;
  sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
  sTmp << " && " << makeCut_npmc   ( fl_use_npmc    ).c_str();
  std::cout << "[Cut] " << sTmp.str().c_str() << std::endl;

  TChain* c_gmc = new TChain(treename);
  std::cout << "[infile_gmc] " << infile_gmc << std::endl;
  std::cout << c_gmc->Add(infile_gmc)  << " files, ";
  std::cout << c_gmc->GetEntries()     << " entries, ";
  std::cout << nstream_gmc             << " streams" << std::endl;

  TTree** c_gmc_cut = new TTree*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( ipdf==0 ) c_gmc_cut[ipdf] = c_gmc->CopyTree( Form("(%s)&&(%s)&&(%s)", sTmp.str().c_str(), selection_common_mc, makeCut_remain(pdf_selection,npdf).c_str()) );
    else          c_gmc_cut[ipdf] = c_gmc->CopyTree( Form("(%s)&&(%s)&&(%s)", sTmp.str().c_str(), selection_common_mc,                pdf_selection[ipdf]        ) );
    std::cout << "[Category] "
	      << std::setw(15) << std::right << pdf_name[ipdf]                << " : "
	      << std::setw(15) << std::right << c_gmc_cut[ipdf]->GetEntries() << " entries"
	      << std::endl;
  }
      
  TChain* c_dststmc = new TChain(treename);
  std::cout << "[infile_dststmc] " << infile_dststmc << std::endl;
  std::cout << c_dststmc->Add(infile_dststmc) << " files, ";
  std::cout << c_dststmc->GetEntries()        << " entries, ";
  std::cout << nstream_dststmc                << " streams" << std::endl;

  TTree** c_dststmc_cut = new TTree*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( ipdf==0 ) c_dststmc_cut[ipdf] = c_dststmc->CopyTree( Form("(%s)&&(%s)&&(%s)", sTmp.str().c_str(), selection_common_mc, makeCut_remain(pdf_selection,npdf).c_str()) );
    else          c_dststmc_cut[ipdf] = c_dststmc->CopyTree( Form("(%s)&&(%s)&&(%s)", sTmp.str().c_str(), selection_common_mc,                pdf_selection[ipdf]        ) );
    std::cout << "[Category] "
	      << std::setw(15) << std::right << pdf_name[ipdf]                    << " : "
	      << std::setw(15) << std::right << c_dststmc_cut[ipdf]->GetEntries() << " entries"
	      << std::endl;
  }

  TChain* c_npmc = new TChain(treename);
  std::cout << "[infile_npmc] " << Form(infile_npmc,"0p0") << " : " << fl_par_dt << std::endl;
  std::cout << c_npmc->Add(Form(infile_npmc,"0p0"))        << " files, ";
  std::cout << c_npmc->GetEntries()                        << " entries, ";
  std::cout << nstream_npmc                                << " streams" << std::endl;
  
  TTree** c_npmc_cut = new TTree*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( ipdf==0 ) c_npmc_cut[ipdf] = c_npmc->CopyTree( Form("(%s)&&(%s)&&(%s)", sTmp.str().c_str(), selection_common_mc, makeCut_remain(pdf_selection,npdf).c_str()) );
    else          c_npmc_cut[ipdf] = c_npmc->CopyTree( Form("(%s)&&(%s)&&(%s)", sTmp.str().c_str(), selection_common_mc,                pdf_selection[ipdf]        ) );
    std::cout << "[Category] "
	      << std::setw(15) << std::right << pdf_name[ipdf]                 << " : "
	      << std::setw(15) << std::right << c_npmc_cut[ipdf]->GetEntries() << " entries"
	      << std::endl;
  }

  // NP weight file
  TFile* npweight_file = new TFile( weight_table );
  if( npweight_file->IsZombie() ) std::cerr << "[ABORT] can not find weight-file for " << weight_table << std::endl, abort();
  TGraphErrors* npweight_table = (TGraphErrors*)npweight_file->Get( Form( "np_%s",fl_par_dt) );
  if( npweight_table==NULL ) std::cerr << "[ABORT] can not find weight-table for " << fl_par_dt << std::endl, abort();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TH1D** pdf_hist_lep  = new TH1D*[npdf];
  TH1D** pdf_hist_dstr = new TH1D*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    pdf_hist_lep [ipdf] = new TH1D( Form("mc_hist_lep_%s", pdf_name[ipdf]), Form("mc_hist_lep_%s", pdf_name[ipdf]),  lep_nbin,  lep_xmin,  lep_xmax );
    pdf_hist_dstr[ipdf] = new TH1D( Form("mc_hist_dstr_%s",pdf_name[ipdf]), Form("mc_hist_dstr_%s",pdf_name[ipdf]), dstr_nbin, dstr_xmin, dstr_xmax );
    pdf_hist_lep [ipdf]->Sumw2();
    pdf_hist_dstr[ipdf]->Sumw2();

    for( Int_t ievt=0; ievt<c_gmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_gmc_cut[ipdf], ievt, (Double_t)nstream_gmc );
      if( fl_2sveto &&
	  ( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 ||
	    c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 )
	  ) weight = 0;
      if( c_gmc_cut[ipdf]->GetLeaf(cos1_brname)->GetValue() < c_gmc_cut[ipdf]->GetLeaf(cos2_brname)->GetValue() ){
	pdf_hist_lep [ipdf]->Fill( c_gmc_cut[ipdf]->GetLeaf( lep1_brname)->GetValue(), weight );
	pdf_hist_dstr[ipdf]->Fill( c_gmc_cut[ipdf]->GetLeaf(dstr1_brname)->GetValue(), weight );
      }else{
	pdf_hist_lep [ipdf]->Fill( c_gmc_cut[ipdf]->GetLeaf( lep2_brname)->GetValue(), weight );
	pdf_hist_dstr[ipdf]->Fill( c_gmc_cut[ipdf]->GetLeaf(dstr2_brname)->GetValue(), weight );
      }
    }
    
    for( Int_t ievt=0; ievt<c_dststmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_dststmc_cut[ipdf], ievt, (Double_t)nstream_dststmc );
      if( fl_2sveto &&
	  ( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 ||
	    c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 )
	  ) weight = 0;
      if( c_dststmc_cut[ipdf]->GetLeaf(cos1_brname)->GetValue() < c_dststmc_cut[ipdf]->GetLeaf(cos2_brname)->GetValue() ){
	pdf_hist_lep [ipdf]->Fill( c_dststmc_cut[ipdf]->GetLeaf( lep1_brname)->GetValue(), weight );
	pdf_hist_dstr[ipdf]->Fill( c_dststmc_cut[ipdf]->GetLeaf(dstr1_brname)->GetValue(), weight );
      }else{
	pdf_hist_lep [ipdf]->Fill( c_dststmc_cut[ipdf]->GetLeaf( lep2_brname)->GetValue(), weight );
	pdf_hist_dstr[ipdf]->Fill( c_dststmc_cut[ipdf]->GetLeaf(dstr2_brname)->GetValue(), weight );
      }
    }
    
    for( Int_t ievt=0; ievt<c_npmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_npmc_cut[ipdf], ievt, (Double_t)nstream_npmc );
      if( fl_2sveto &&
	  ( c_npmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 ||
	    c_npmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 )
	  ) weight = 0;
      Double_t val[np::nvar];
      for( Int_t ivar=0; ivar<np::nvar; ivar++ ) val[ivar] = c_npmc_cut[ipdf]->GetLeaf(np::brname[ivar])->GetValue(); // reproduce NP distribution by re-weighted SM distribution
      Int_t gindex = getGIndex( val );
      Double_t npweight  = npweight_table->GetY()[gindex];
      Double_t npweightE = npweight_table->GetErrorY(gindex);
      weight *= npweight; // NP weight
      
      if( c_npmc_cut[ipdf]->GetLeaf(cos1_brname)->GetValue() < c_npmc_cut[ipdf]->GetLeaf(cos2_brname)->GetValue() ){
	pdf_hist_lep [ipdf]->Fill( c_npmc_cut[ipdf]->GetLeaf( lep1_brname)->GetValue(), weight );
	pdf_hist_dstr[ipdf]->Fill( c_npmc_cut[ipdf]->GetLeaf(dstr1_brname)->GetValue(), weight );
      }else{
	pdf_hist_lep [ipdf]->Fill( c_npmc_cut[ipdf]->GetLeaf( lep2_brname)->GetValue(), weight );
	pdf_hist_dstr[ipdf]->Fill( c_npmc_cut[ipdf]->GetLeaf(dstr2_brname)->GetValue(), weight );
      }
    }
  }

  TFile outfile( Form("pdf/kinematic_%s.root",fl_par_dt), "RECREATE" ); // save histgrams BEFORE scaling
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    pdf_hist_lep [ipdf]->Write();
    pdf_hist_dstr[ipdf]->Write();
  }
  outfile.Close();
  abort();
  */
  ///*
  // < Read PDF from Outfile >
  TFile* infile = new TFile( Form("pdf/kinematic_%s.root",fl_par_dt) );
  if( infile->IsZombie() ) std::cerr << Form("[ABORT] can not find infile : pic/kinematic_%s.root",fl_par_dt) << std::endl, abort();
  TH1D** pdf_hist_lep  = new TH1D*[npdf];
  TH1D** pdf_hist_dstr = new TH1D*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    pdf_hist_lep [ipdf] = (TH1D*)infile->Get( Form( "mc_hist_lep_%s", pdf_name[ipdf]) );
    pdf_hist_dstr[ipdf] = (TH1D*)infile->Get( Form( "mc_hist_dstr_%s",pdf_name[ipdf]) );
    if( pdf_hist_lep [ipdf]==NULL ) std::cerr << "[ABORT] can not find histogram lep  : " << ipdf << std::endl, abort();
    if( pdf_hist_dstr[ipdf]==NULL ) std::cerr << "[ABORT] can not find histogram dstr : " << ipdf << std::endl, abort();
  }
  //*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    pdf_hist_lep [ipdf]->Scale( pdf_yields[ipdf] ); // reflect fit result
    pdf_hist_dstr[ipdf]->Scale( pdf_yields[ipdf] ); // reflect fit result
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg     = new TLegend( 0.65,0.59,0.85,0.89 );
  THStack* mh_lep  = new THStack( "mh_lep",  Form("%s;p_{l} [GeV]", selection_common) );
  THStack* mh_dstr = new THStack( "mh_dstr", Form("%s;p_{D*} [GeV]",selection_common) );
  pdf_hist_lep [0]->SetFillColor( col[0] );
  pdf_hist_dstr[0]->SetFillColor( col[0] );
  pdf_hist_lep [0]->SetLineColor( col[0] );
  pdf_hist_dstr[0]->SetLineColor( col[0] );
  mh_lep ->Add( pdf_hist_lep [0] );
  mh_dstr->Add( pdf_hist_dstr[0] );
  for( Int_t ipdf=npdf-1; ipdf>0; ipdf-- ){
    pdf_hist_lep [ipdf]->SetFillColor( col[ipdf] );
    pdf_hist_dstr[ipdf]->SetFillColor( col[ipdf] );
    pdf_hist_lep [ipdf]->SetLineColor( col[ipdf] );
    pdf_hist_dstr[ipdf]->SetLineColor( col[ipdf] );
    mh_lep ->Add( pdf_hist_lep [ipdf] );
    mh_dstr->Add( pdf_hist_dstr[ipdf] );
  }

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){  
    if( ipdf!=0 && ipdf<5 ) leg->AddEntry( pdf_hist_lep[ipdf], pdf_name[ipdf], "F" );
  }
  leg->AddEntry( pdf_hist_lep[5], "Fake D^{(*)}", "F" );  
  leg->AddEntry( pdf_hist_lep[0], pdf_name[0],    "F" );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // < READ Data >
  TChain* c_dt           = new TChain(treename);
  TH1D*   data_hist_lep  = new TH1D( "dt_hist_lep",  "dt_hist_lep",   lep_nbin,  lep_xmin,  lep_xmax );
  TH1D*   data_hist_dstr = new TH1D( "dt_hist_dstr", "dt_hist_dstr", dstr_nbin, dstr_xmin, dstr_xmax );
  data_hist_lep ->Sumw2();
  data_hist_dstr->Sumw2();

  std::cout << "[infile_data] "     << infile_dt  << std::endl;
  std::cout << c_dt->Add(infile_dt) << " files, ";
  std::cout << c_dt->GetEntries()   << " entries"
	    << std::endl;
  sTmp.str("");
  sTmp.clear();
  sTmp << Form("eecl_exp<%f",eecl_xmax);
  sTmp << " && " << selection_common;
  TTree* c_dt_cut  = c_dt ->CopyTree( Form("(%s)", sTmp.str().c_str()) );
  std::cout << "[dt_cut] " << c_dt_cut ->GetEntries() << " events" << std::endl;
  
  for( Int_t ievt=0; ievt<c_dt_cut->GetEntries(); ievt++ ){
    c_dt_cut->GetEntry(ievt);
    if( c_dt_cut->GetLeaf(cos1_brname)->GetValue() < c_dt_cut->GetLeaf(cos2_brname)->GetValue() ){
      data_hist_lep ->Fill( c_dt_cut->GetLeaf( lep1_brname)->GetValue() );
      data_hist_dstr->Fill( c_dt_cut->GetLeaf(dstr1_brname)->GetValue() );
    }else{
      data_hist_lep ->Fill( c_dt_cut->GetLeaf( lep2_brname)->GetValue() );
      data_hist_dstr->Fill( c_dt_cut->GetLeaf(dstr2_brname)->GetValue() );
    }
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // < Construct Total Bkg-Histogram >
  TH1D* pdf_hist_lep_bkg   = new TH1D( "mc_hist_lep_bkg", "mc_hist_lep_bkg",   lep_nbin,  lep_xmin,  lep_xmax );
  TH1D* pdf_hist_dstr_bkg  = new TH1D( "mc_hist_dstr_bkg","mc_hist_dstr_bkg", dstr_nbin, dstr_xmin, dstr_xmax );
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( ipdf==1 ) continue;
    pdf_hist_lep_bkg ->Add( pdf_hist_lep [ipdf] );
    pdf_hist_dstr_bkg->Add( pdf_hist_dstr[ipdf] );
  }

  //+++++++++++++++++++++++++++++++++++
  // < Subtract Bkg (lepton) >
  TH1D* data_hist_lep_sub  = new TH1D( *data_hist_lep  );
  Double_t chi2_lep = 0.0;
  Double_t  ndf_lep = 0.0;
  for( Int_t ibin=0; ibin<lep_nbin; ibin++ ){
    if( data_hist_lep->GetBinContent(ibin+1)==0 ){ // if no data, continue (to be discussed!!!)
      data_hist_lep_sub->SetBinContent( ibin+1, 0.0 );
      continue;
    }else data_hist_lep_sub->SetBinContent( ibin+1,
					   data_hist_lep    ->GetBinContent(ibin+1)
					   -pdf_hist_lep_bkg->GetBinContent(ibin+1)
					   );
    Double_t dev  = pdf_hist_lep[1]->GetBinContent(ibin+1) - data_hist_lep_sub->GetBinContent(ibin+1);
    Double_t err2 = pow( pdf_hist_lep[1]->GetBinError(ibin+1),2 ) + pow( data_hist_lep_sub->GetBinError(ibin+1),2);
    if( err2==0 ) continue;
    chi2_lep += pow(dev,2)/err2;
    ndf_lep  += 1.0;
  }
  //+++++++++++++++++++++++++++++++++++
  // < Subtract Bkg (D*) >
  TH1D* data_hist_dstr_sub = new TH1D( *data_hist_dstr );
  Double_t chi2_dstr = 0.0;
  Double_t  ndf_dstr = 0.0;
  for( Int_t ibin=0; ibin<dstr_nbin; ibin++ ){
    if( data_hist_dstr->GetBinContent(ibin+1)==0 ){ // if no data, continue (to be discussed!!!)
      data_hist_dstr_sub->SetBinContent( ibin+1, 0.0 );
      continue;
    }else data_hist_dstr_sub->SetBinContent( ibin+1,
					    data_hist_dstr    ->GetBinContent(ibin+1)
					    -pdf_hist_dstr_bkg->GetBinContent(ibin+1)
					     );
    Double_t dev  = pdf_hist_dstr[1]->GetBinContent(ibin+1) - data_hist_dstr_sub->GetBinContent(ibin+1);
    Double_t err2 = pow( pdf_hist_dstr[1]->GetBinError(ibin+1),2 ) + pow( data_hist_dstr_sub->GetBinError(ibin+1),2);
    if( err2==0 ) continue;
    chi2_dstr += pow(dev,2)/err2;
    ndf_dstr  += 1.0;
  }

  //+++++++++++++++++++++++++++++++++++
  // < Construct Stacked Histogram>
  THStack* mh_lep2  = new THStack( "mh_lep2",  Form("      #chi^{2}/ndf = %.1f/%d, p = %.2f %%;p_{l} [GeV]", chi2_lep,  (Int_t)ndf_lep, 100*TMath::Prob(chi2_lep, (Int_t)ndf_lep )) );
  THStack* mh_dstr2 = new THStack( "mh_dstr2", Form("      #chi^{2}/ndf = %.1f/%d, p = %.2f %%;p_{D*} [GeV]",chi2_dstr, (Int_t)ndf_dstr,100*TMath::Prob(chi2_dstr,(Int_t)ndf_dstr)) );
  mh_lep2 ->Add( pdf_hist_lep [1]   );
  mh_dstr2->Add( pdf_hist_dstr[1]   );
  mh_lep2 ->Add( data_hist_lep_sub  );
  mh_dstr2->Add( data_hist_dstr_sub );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 2, 2 );
  can->cd(1);
  mh_lep->Draw("hist");
  //mh_lep->SetMaximum( mh_lep->GetMaximum()+7);
  mh_lep->SetMaximum(50); // for paper
  mh_lep->Draw("hist");
  data_hist_lep->Draw("E0same");
  leg->Draw();

  can->cd(2);
  mh_dstr->Draw("hist");
  //mh_dstr->SetMaximum( mh_dstr->GetMaximum()+7);
  mh_dstr->SetMaximum(50); // for paper
  mh_dstr->Draw("hist");
  data_hist_dstr->Draw("E0same");

  can->cd(3);
  mh_lep2->Draw("nostackhist");
  //gPad->DrawFrame( lep_xmin, ( data_hist_lep_sub->GetMinimum()>=0.0 ? 0.0 : data_hist_lep_sub->GetMinimum()-1.5), lep_xmax, 0.8*mh_lep2->GetMaximum(), Form("%s",mh_lep2->GetTitle()) );
  gPad->DrawFrame( lep_xmin, -5, lep_xmax, 30, Form("%s",mh_lep2->GetTitle()) ); // for paper
  pdf_hist_lep[1]->Draw("nohistsame");
  data_hist_lep_sub->Draw("E0same");
  
  can->cd(4);
  mh_dstr2->Draw("nostackhist");
  //gPad->DrawFrame( dstr_xmin, ( data_hist_dstr_sub->GetMinimum()>=0.0 ? 0.0 : data_hist_dstr_sub->GetMinimum()-1.5), dstr_xmax, 0.8*mh_dstr2->GetMaximum(), Form("%s",mh_dstr2->GetTitle()) );
  gPad->DrawFrame( dstr_xmin, -5, dstr_xmax, 30, Form("%s",mh_dstr2->GetTitle()) ); // for paper
  pdf_hist_dstr[1]->Draw("nohistsame");
  data_hist_dstr_sub->Draw("E0same");
  
  can->Update();
  can->Print( Form("pic/kinematic_%s.eps",fl_par_dt) );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << Form("lep : #chi^{2}/ndf = %.1f/%d, p = %.3f %%", chi2_lep,  (Int_t)ndf_lep, 100*TMath::Prob(chi2_lep, (Int_t)ndf_lep )) << std::endl;
  std::cout << Form(" D* : #chi^{2}/ndf = %.1f/%d, p = %.3f %%", chi2_dstr, (Int_t)ndf_dstr,100*TMath::Prob(chi2_dstr,(Int_t)ndf_dstr)) << std::endl;

  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
