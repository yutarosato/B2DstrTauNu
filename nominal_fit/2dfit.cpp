#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//const Double_t corr_fake_d         = 1.0;
//const Double_t corr_corr_d         = 1.0;
const Double_t corr_fake_d         =  629/ 544.0; // for data // tmppppp
//const Double_t corr_fake_d         =  629/ 544.0 * (1.00-0.06); // for data // tmppppp // syststudy
const Double_t corr_corr_d         = 3584/3656.0; // for data // tmppppp
const Char_t*  selection_common_mc = "1";
const Char_t*  selection_common    = "1";
//const Char_t*  selection_common    = "eecl<0.5 && nb_mode0_test13_nor < 0.8";


const Bool_t fl_2sveto = true; // veto D(2S) and D*(2S)

const Char_t* pdf_dir             = "pdf/";
const Char_t* pdf_dir_syst        = "pdf_syst0/";
//const Char_t* pdf_dir_syst        = "pdf_syst1/";

const Int_t   npdf                = 10;
const Char_t* pdf_name     [npdf] = { "other", "sig", "nor", "dstst", "doubled", "fake_other", "fake_sig", "fake_nor", "fake_dstst", "fake_doubled" };
Double_t      pdf_nexp     [npdf] = {     1.0,   1.0,   1.0,     1.0,       1.0,          1.0,        1.0,        1.0,          1.0,            1.0 };
const Int_t   col          [npdf] = {       5,     3,     4,       7,         8,            6,          6,          6,            6,              6 };
const Int_t   lsty         [npdf] = {       2,     1,     1,       2,         2,            2,          2,          2,            2,              2 };
const Int_t   pdf_fix      [npdf] = {       1,     0,     0,       0,         1,            2,          2,          2,            2,              2 }; // 0(float), 1(fix), 2(partially-fix for fake D* component)
const Int_t   pdf_corr     [npdf] = {      -1,    -1,    -1,      -1,        -1,            0,          1,          2,            3,              4 }; // correspondence (fake D -> correct D)
const Int_t   pdf_dim      [npdf] = {       2,     1,     2,       2,         2,            2,          2,          2,            2,              2 }; // 0(not use)
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

const Bool_t  roosumw2   = !true; // fixed to be "false"
const Char_t* fl_par_pdf = "0p0"; // for PDF
//const Char_t* fl_par_pdf = "0p8"; // for PDF // tmpppp
//const Char_t* fl_par_pdf = "R2_0p360"; // for PDF // tmpppp
//const Char_t* fl_par_pdf = "S1_m0p030"; // for PDF // tmpppp
//const Char_t* fl_par_pdf = "OP_V1_m2p10"; // for PDF // tmpppp
//const Char_t* fl_par_pdf = "OP_V2_1p88"; // for PDF // tmpppp
//const Char_t* fl_par_pdf = "OP_S1_3p00"; // for PDF // tmpppp
//const Char_t* fl_par_pdf = "OP_S2_5p00"; // for PDF // tmpppp
//const Char_t* fl_par_pdf = "OP_V1_0p50"; // for PDF // tmpppp
//const Char_t* fl_par_pdf = "OP_V2_2p50"; // for PDF // tmpppp
//const Char_t* fl_par_pdf = "OP_T_0p36"; // for PDF // tmpppp
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///*
const Bool_t   fl_use_dststmc  = true;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Char_t*  infile_gmc_1st  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0%d*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut_bcs_vtx/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
const Bool_t   fl_use_npmc     = true;
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/%s_weight_nb_cut_bcs_vtx/npMC_*.root";
const Char_t*  infile_npmc_1st = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/%s_weight_nb_cut_bcs_vtx/npMC_*s0%d*.root";
const Double_t nstream_npmc    = 40;

// [type-II 2HDM] 0p0 0p1 0p2 0p3 0p4 0p5 0p6 0p7 0p8 0p9 1p0
// [   R2-LQ    ] R2_m0p150 R2_m0p100 R2_m0p040 R2_0p000 R2_0p090 R2_0p180 R2_0p260 R2_0p340 R2_0p400
// [   S1-LQ    ] S1_m0p150 S1_m0p100 S1_m0p040 S1_0p000 S1_0p090 S1_0p180 S1_0p260 S1_0p340 S1_0p400
const Char_t*  fl_par_dt       = "0p0"; // for samples (use np_weight_table)
//const Char_t*  fl_par_dt       = "1p0"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "R2_m0p030"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "S1_m0p030"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "OP_S1_3p00"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "OP_S2_5p00"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "OP_V1_0p50"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "OP_V2_2p50"; // for samples // tmpppppp
//const Char_t*  fl_par_dt       = "OP_T_0p36"; // for samples // tmpppppp

//const Char_t*  weight_table    = "../npmc/table/dstrtaunu_dpi_lep_12_all/est_weight.root"; // old
const Char_t*  weight_table    = "../npmc/new_table/2hdmII/dstrtaunu_dpi_lep_12_all/est_weight.root"; // type-II 2HDM
//const Char_t*  weight_table    = "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root";   // R2-LQ // tmppppp
//const Char_t*  weight_table    = "../npmc/new_table/S1LQ/dstrtaunu_dpi_lep_12_all/est_weight.root";   // S1-LQ // tmppppp
//const Char_t*  weight_table    = "../npmc/new_table/OPS1/dstrtaunu_dpi_lep_12_all/est_weight.root";   // OPS1 // tmppppp
//const Char_t*  weight_table    = "../npmc/new_table/OPS2/dstrtaunu_dpi_lep_12_all/est_weight.root";   // OPS2 // tmppppp
//const Char_t*  weight_table    = "../npmc/new_table/OPV1/dstrtaunu_dpi_lep_12_all/est_weight.root";   // OPV1 // tmppppp
//const Char_t*  weight_table    = "../npmc/new_table/OPV2/dstrtaunu_dpi_lep_12_all/est_weight.root";   // OPV2 // tmppppp
//const Char_t*  weight_table    = "../npmc/new_table/OPT/dstrtaunu_dpi_lep_12_all/est_weight.root";   // OPT // tmppppp

const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/RD_*.root";
//*/
/*
const Bool_t   fl_use_dststmc  = true;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut/gMC_*s0[0-9]*.root";
const Char_t*  infile_gmc_1st  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut/gMC_*s0%d*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
const Bool_t   fl_use_npmc     = true;
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/%s_weight_nb_cut/npMC_*.root";
const Char_t*  infile_npmc_1st = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/%s_weight_nb_cut/npMC_*s0%d*.root";
const Double_t nstream_npmc    = 10;
const Char_t*  fl_par_dt       = "0p0"; // for samples
const Char_t*  weight_table    = "../npmc/table/dstrtaunu_dpi_lep_12_all/est_weight.root";
const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut/RD_*.root";
*/
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetTitleOffset(1.0,"z");
  sty->SetPadTickX(1);
  sty->SetPadTickY(1);
  sty->SetTickLength( 0.02, "XY" );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( !(app.Argc()==4 || app.Argc()==5 ) )
  //if( !(app.Argc()==4 || app.Argc()==5 || app.Argc()==6 || app.Argc()==7 ) ) // tmppppppp // for exe_2dfit_init
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (int)nexp (int)fl_stream (int)fl_lep [(int) #iteration or #tag_cnt]" << std::endl
	      << "      * unit of nexp is percent : (i.e.) 100 is default yield of belle MC" << std::endl
	      << "      *  toy mc  test mode for negative fl_stream " << std::endl
	      << "      *     data fit  mode for fl_stream=-999 "     << std::endl
	      << "      * ensemble test mode for positive fl_stream " << std::endl
	      << "      * fl_lep : 10(e), 1(mu), 0(l)"                << std::endl
	      << "[e.g]" << std::endl
	      << "./2dfit 100 -999 0     # data fit mode                (NEXP STREAMNO LEP           )" << std::endl
	      << "./2dfit 100    0 0     # ensemble mode                (NEXP STREAMNO LEP           )" << std::endl
	      << "./2dfit 100    0 0   1 # ensemble mode for syst study (NEXP STREAMNO LEP TAG       )" << std::endl
	      << "./2dfit 100   -1 0 100 #  toy  mc mode                (NEXP STREAMNO LEP NITERATION)"
	      << std::endl, abort();
  pdf_nexp[1]      = atof(app.Argv(1))/100.0;
  Int_t  fl_stream = atoi(app.Argv(2));
  Int_t  fl_lep    = atoi(app.Argv(3));
  Bool_t fl_toymc  = !true;
  Int_t  iteration = 10000;
  Int_t  tag_cnt   = 0;

  if( fl_stream==-999 ){
    std::cout << "[data fitting mode]" << std::endl;
    if( app.Argc()>4 ) tag_cnt = atoi(app.Argv(4));
    std::cout << "tag_cnt is " << tag_cnt << std::endl;
  }else if( fl_stream < 0 ){
    fl_toymc  = true;
    std::cout << "[toy mc test mode]" << std::endl;
    if( app.Argc()>4 ) iteration = atoi(app.Argv(4));
    std::cout << "# of iteration is " << iteration << std::endl;
  }else{
    std::cout << "[ensemble test mode]" << std::endl;
    if( app.Argc()>4 ) tag_cnt = atoi(app.Argv(4));
    std::cout << "tag_cnt is " << tag_cnt << std::endl;
  }
  //const Char_t* fl_par_dt    = app.Argv(5); // tmppppppp // for exe_2dfit_init
  //const Char_t* weight_table = app.Argv(6); // tmppppppp // for exe_2dfit_init

  std::cout << "fl_par_pdf = " << fl_par_pdf << std::endl
	    << "fl_par_dt  = " << fl_par_dt  << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // 10000, 40000
  //unsigned int seed = time(NULL);
  unsigned int seed_dstst = 40000;
    seed_dstst += (unsigned int)( 1000*pdf_nexp[1] + 10000*fl_stream);
  unsigned int seed = seed_dstst;
  seed += (unsigned int)(100000*tag_cnt);
  RooRandom::randomGenerator()->SetSeed( seed );
  gRandom->SetSeed( seed );
  Read_Data( calib_file, true );
  Int_t npar = 0;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_dim[ipdf] && pdf_fix[ipdf]==0 ) npar++;
  }
  Int_t npar_fake = 0;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_dim[ipdf] && pdf_fix[ipdf]==2 ) npar_fake++;
  }
  Int_t tmp_cnt = 1;
  std::stringstream sTmp;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  // <TChain>
  sTmp.str("");
  sTmp.clear();
  sTmp << Form("eecl<%f",eecl_xmax);
  sTmp << " && " << selection_common;
  sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
  sTmp << " && " << makeCut_npmc   ( fl_use_npmc    ).c_str();
  if( fl_lep ) sTmp << Form(" && ( (cosdll==cosdl1 && rm_l1==%d) || (cosdll==cosdl2 && rm_l2==%d) )",fl_lep,fl_lep);
  //sTmp <<" && (abs(rm_d1lun)==421 && abs(rm_d2lun)==421)"; // tmpppppppppppppp
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
  // <READ MC> for inital value counting
  TH2D** mc_hist     = new TH2D*[npdf];
  TH2D*  mc_hist_tot = new TH2D( "mc_hist_tot", "mc_hist_tot", nb_xbin, nb_xmin, nb_xmax, eecl_xbin, eecl_xmin, eecl_xmax );
  Double_t npcurve_yield  = 0.0; // added @20160229
  Double_t npcurve_error2 = 0.0; // added @20160229
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    mc_hist[ipdf] = new TH2D( Form("mc_hist_%s",pdf_name[ipdf]), Form("mc_hist_%s",pdf_name[ipdf]), nb_xbin, nb_xmin, nb_xmax, eecl_xbin, eecl_xmin, eecl_xmax );

    for( Int_t ievt=0; ievt<c_gmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_gmc_cut[ipdf], ievt, (Double_t)nstream_gmc );
      if( fl_2sveto &&
	  ( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 ||
	    c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 )
	  ) weight = 0;
      weight *= pdf_nexp[ipdf];
      if( pdf_dim[ipdf] ){
	mc_hist[ipdf]->Fill( c_gmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_gmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
	mc_hist_tot  ->Fill( c_gmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_gmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
      }
    }

    for( Int_t ievt=0; ievt<c_dststmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_dststmc_cut[ipdf], ievt, (Double_t)nstream_dststmc );
      if( fl_2sveto &&
	  ( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 ||
	    c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 )
	  ) weight = 0;
      weight *= pdf_nexp[ipdf];
      if( pdf_dim[ipdf] ){
	mc_hist[ipdf]->Fill( c_dststmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_dststmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
	mc_hist_tot  ->Fill( c_dststmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_dststmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
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
      
      weight *= pdf_nexp[ipdf];
      if( pdf_dim[ipdf] ){
	mc_hist[ipdf]->Fill( c_npmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_npmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
	mc_hist_tot  ->Fill( c_npmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_npmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
	if( ipdf==1 ){ // added @20160229
	  npcurve_yield += weight;
	  if( npweight > 1.0 ) npcurve_error2 += pow( sqrt( (npweight-1.0)*(weight/npweight)*((Double_t)nstream_npmc) )/((Double_t)nstream_npmc), 2 );
	}
      }
    }

  }

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) mc_hist[ipdf]->Print();
  mc_hist_tot->Print();

  Double_t init[npdf] = {0};
  Double_t init_tot = 0;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    init_tot  += mc_hist[ipdf]->Integral();
    init[ipdf] = mc_hist[ipdf]->Integral();
  }
  std::cout << "[INITIAL VALUE]" << std::endl;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){  
    std::cout << "[Category] "
	      << std::setw(15) << std::right << pdf_name[ipdf] << " : "
	      << std::setw(15) << std::right << init    [ipdf] << " events"
	      << std::endl;
  }
  std::cout << " ---> total " << init_tot << " events" << std::endl;
  std::cout << "[ npcurve ] " << npcurve_yield << " +- " << sqrt(npcurve_error2) << std::endl;
  abort();
  */
  //++++++++++++++++++++++++++++++++
  ///*
  // NP weight file
  TFile* npweight_file = new TFile( weight_table );
  if( npweight_file->IsZombie() ) std::cerr << "[ABORT] can not find weight-file for " << weight_table << std::endl, abort();
  TGraphErrors* npweight_table = (TGraphErrors*)npweight_file->Get( Form( "np_%s",fl_par_dt) );
  if( npweight_table==NULL ) std::cerr << "[ABORT] can not find weight-table for " << fl_par_dt << std::endl, abort();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //Double_t init_l [npdf] = {66.1087, 190.19,   2686.91, 417.42, 121.661,  77.636, 19.223,   242.107, 179.657,  61.0168 }; // sigMC(10 streams)
  //Double_t init_e [npdf] = {29.1507, 117.972,  1417.35, 232.711, 69.8497, 46.113, 13.1857,  131.051, 104.958,  39.3299 }; // sigMC(10 streams)
  //Double_t init_mu[npdf] = {36.958,   72.2178, 1269.56, 184.709, 51.811,  31.523,  6.03732, 111.056,  74.6988, 21.6869 }; // sigMC(10 streams)

  //Double_t init_l [npdf] = {65.2115, 190.19,   2686.91, 351.731, 120.933,  77.636, 19.223,   242.107, 135.362,  59.0079 }; // veto D(*)(2S) // sigMC(10 streams)
  //Double_t init_e [npdf] = {28.6944, 117.972,  1417.35, 195.026,  69.5735, 46.113, 13.1857,  131.051,  80.0091, 37.982  }; // veto D(*)(2S) // sigMC(10 streams)
  //Double_t init_mu[npdf] = {36.5171,  72.2178, 1269.56, 156.705,  51.3592, 31.523,  6.03732, 111.056,  55.3528, 21.0259 }; // veto D(*)(2S) // sigMC(10 streams)

  Double_t init_l [npdf] = {65.609,  186.799,  2686.85, 351.743, 121.019,  77.9054, 19.2501,  242.107, 135.362,  59.3656 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p0)
  Double_t init_e [npdf] = {29.1262, 116.126,  1417.29, 195.038,  69.362,  46.2029, 11.7958,  131.051,  80.0091, 38.2505 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p0)
  Double_t init_mu[npdf] = {36.4828,  70.6731, 1269.56, 156.705,  51.6572, 31.7025,  7.45437, 111.056,  55.3528, 21.1151 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p0)

  //Double_t init_l [npdf] = {65.6184, 187.679,  2686.85, 351.742, 121.032,  77.9085, 19.3919,  242.107, 135.362,  59.3792 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p1)
  //Double_t init_e [npdf] = {29.1275, 116.537,  1417.29, 195.037,  69.3566, 46.2046, 11.8784,  131.051,  80.0091, 38.2604 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p1)
  //Double_t init_mu[npdf] = {36.4909,  71.1428, 1269.56, 156.705,  51.6753, 31.7038,  7.51352, 111.056,  55.3528, 21.1189 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p1)

  //Double_t init_l [npdf] = {65.6198, 187.127,  2686.85, 351.737, 121.021,  77.9312, 19.2933,  242.107, 135.362,  59.3715 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p2)
  //Double_t init_e [npdf] = {29.1264, 116.124,  1417.29, 195.032,  69.3628, 46.2208, 11.7884,  131.051,  80.0091, 38.2583 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p2)
  //Double_t init_mu[npdf] = {36.4934,  71.0028, 1269.56, 156.705,  51.6585, 31.7104, 7.50496, 111.056,  55.3528, 21.1132 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p2)

  //Double_t init_l [npdf] = {65.6295, 186.859,  2686.85, 351.734, 121.013,  77.9151, 19.3036,  242.107, 135.362,  59.3793 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p3)
  //Double_t init_e [npdf] = {29.1358, 115.991,  1417.29, 195.029,  69.3408, 46.2022, 11.7714,  131.051,  80.0091, 38.2634 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p3)
  //Double_t init_mu[npdf] = {36.4937,  70.8679, 1269.56, 156.705,  51.6722, 31.7129,  7.53227, 111.056,  55.3528, 21.1159 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p3)
  
  //Double_t init_l [npdf] = {65.654,  186.252,  2686.85, 351.724, 121.03,   77.9023, 19.2643,  242.107, 135.362,  59.3945 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p4)
  //Double_t init_e [npdf] = {29.1401, 115.642,  1417.29, 195.019,  69.3397, 46.2133, 11.7031,  131.051,  80.0091, 38.2278 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p4)
  //Double_t init_mu[npdf] = {36.5139,  70.6101, 1269.56, 156.705,  51.6907, 31.6891,  7.56127, 111.056,  55.3528, 21.1166 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p4)

  //Double_t init_l [npdf] = {65.676,  184.823,  2686.85, 351.72,  121.037, 77.8935, 19.1944,  242.107, 135.362,  59.4201 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p5)
  //Double_t init_e [npdf] = {29.1546, 114.725,  1417.29, 195.014, 69.3283, 46.2083, 11.6711,  131.051,  80.0091, 38.3143 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p5)
  //Double_t init_mu[npdf] = {36.5214,  70.0985, 1269.56, 156.705, 51.7087, 31.6846,  7.52334, 111.056,  55.3528, 21.1059 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p5)
  
  //Double_t init_l [npdf] = {65.6593,  182.94,  2686.85, 351.716, 121.06,   77.8734, 19.3245,  242.107, 135.362,  59.4539 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p6)
  //Double_t init_e [npdf] = {29.156,  113.829,  1417.29, 195.011,  69.3345, 46.1956, 11.838,   131.051,  80.0091, 38.3492 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p6)
  //Double_t init_mu[npdf] = {36.5033,  69.1102, 1269.56, 156.705,  51.7258, 31.6778,  7.48643, 111.056,  55.3528, 21.1048 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p6)

  //Double_t init_l [npdf] = {65.6576, 180.915,  2686.86, 351.72, 121.117,  77.8319, 19.2892,  242.107, 135.362,  59.4594 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p7)
  //Double_t init_e [npdf] = {29.1678, 113.005,  1417.3,  195.014, 69.3306, 46.1817, 11.9141,  131.051,  80.0091, 38.3742 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p7)
  //Double_t init_mu[npdf] = {36.4898,  67.9108, 1269.56, 156.705, 51.7862, 31.6502,  7.37509, 111.056,  55.3528, 21.10852}; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p7)

  //Double_t init_l [npdf] = {65.6172, 178.61,   2686.87, 351.724, 121.137,  77.7714, 19.3968,  242.107, 135.362,  59.4816 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p8)
  //Double_t init_e [npdf] = {29.1534, 112.053,  1417.31, 195.019,  69.3456, 46.1322, 12.1084,  131.051,  80.0091, 38.4103 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p8)
  //Double_t init_mu[npdf] = {36.4637,  66.5577, 1269.56, 156.705,  51.7914, 31.6392,  7.2884,  111.056,  55.3528, 21.0713 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p8)

  //Double_t init_l [npdf] = {65.5637, 177.536,  2686.87, 351.739, 121.188,  77.7296, 19.4439,  242.107, 135.362,  59.4823 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p9)
  //Double_t init_e [npdf] = {29.1223, 111.737,  1417.31, 195.034,  69.367,  46.1062, 12.2322,  131.051,  80.0091, 38.4237 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p9)
  //Double_t init_mu[npdf] = {36.4413,  65.7992, 1269.56, 156.705,  51.8208, 31.6234,  7.21168, 111.056,  55.3528, 21.0586 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p9)

  //Double_t init_l [npdf] = {65.5442, 176.75,   2686.88, 351.745, 121.198,  77.7355, 19.4611,  242.107, 135.362,  59.4763 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(1p0)
  //Double_t init_e [npdf] = {29.1242, 111.614,  1417.32, 195.04,   69.3725, 46.1133, 12.3739,  131.051,  80.0091, 38.4293 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(1p0)
  //Double_t init_mu[npdf] = {36.42,    65.1362, 1269.56, 156.705,  51.8252, 31.6222,  7.08722, 111.056,  55.3528, 21.047  }; // veto D(*)(2S) // sigMC(40 streams) // npmc(1p0)
  
  //Double_t init_l [npdf] = {65.609,  186.799,  2686.85, 351.743, 121.019 *(1.00-4*0.029), 77.9054, 19.2501,  242.107, 135.362,  59.3656 }; // veto D(*)(2S) // sigMC(40 streams) for syststudy (DD)
  //Double_t init_e [npdf] = {29.1262, 116.126,  1417.29, 195.038,  69.362 *(1.00-4*0.029), 46.2029, 11.7958,  131.051,  80.0091, 38.2505 }; // veto D(*)(2S) // sigMC(40 streams) for syststudy (DD)
  //Double_t init_mu[npdf] = {36.4828,  70.6731, 1269.56, 156.705,  51.6572*(1.00-4*0.029), 31.7025,  7.45437, 111.056,  55.3528, 21.1151 }; // veto D(*)(2S) // sigMC(40 streams) for syststudy (DD)

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //Double_t init_l [npdf] = {65.5026, 184.774,  2686.85, 351.751,121.055,  77.9152, 19.1352,  242.107, 135.362,  59.399  }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p150)
  //Double_t init_e [npdf] = {29.0798, 116.304,  1417.29, 195.046, 69.4251, 46.2426, 11.9429,  131.051,  80.0091, 38.2255 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p150)
  //Double_t init_mu[npdf] = {36.4228,  68.4701, 1269.56, 156.705, 51.6299, 31.6726,  7.19222, 111.056,  55.3528, 21.1736 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p150)

  //Double_t init_l [npdf] = {65.5294, 184.667,  2686.85, 351.748,121.034,  77.9012, 19.129,   242.107, 135.362,  59.3955 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p100)
  //Double_t init_e [npdf] = {29.0846, 115.978,  1417.29, 195.043, 69.4009, 46.2171, 11.8506,  131.051,  80.0091, 38.2367 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p100)
  //Double_t init_mu[npdf] = {36.4448,  68.689,  1269.56, 156.705, 51.6333, 31.6841,  7.27844, 111.056,  55.3528, 21.1588 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p100)

  //Double_t init_l [npdf] = {65.5763,  185.75,  2686.85, 351.746,121.011,  77.889,  19.2122, 242.107, 135.362,  59.3857 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p040)
  //Double_t init_e [npdf] = {29.1157, 115.868,  1417.29, 195.04,  69.3794, 46.2138, 11.8261, 131.051,  80.0091, 38.2487 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p040)
  //Double_t init_mu[npdf] = {36.4606,  69.882,  1269.56, 156.705, 51.6321, 31.6752, 7.38606, 111.056,  55.3528, 21.1371 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p040)

  //Double_t init_l [npdf] = {65.5572,  185.56,  2686.85, 351.747,121.018,  77.8918, 19.1722, 242.107, 135.362,  59.3709 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p030)
  //Double_t init_e [npdf] = {29.1013, 115.705,  1417.29, 195.042, 69.375,  46.2098, 11.7794, 131.051,  80.0091, 38.2455 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p030)
  //Double_t init_mu[npdf] = {36.4558,  69.8557, 1269.56, 156.705, 51.6433, 31.6821, 7.39278, 111.056,  55.3528, 21.1254 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_m0p030)

  //Double_t init_l [npdf] = {65.609,  186.799,  2686.85, 351.743, 121.019,  77.9054, 19.2501,  242.107, 135.362,  59.3656 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p000)
  //Double_t init_e [npdf] = {29.1262, 116.126,  1417.29, 195.038,  69.362,  46.2029, 11.7958,  131.051,  80.0091, 38.2505 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p000)
  //Double_t init_mu[npdf] = {36.4828,  70.6731, 1269.56, 156.705,  51.6572, 31.7025,  7.45437, 111.056,  55.3528, 21.1151 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p000)

  //Double_t init_l [npdf] = {65.7417,  197.638,  2686.85, 351.728, 121.07,   78.0177, 20.0382,  242.107, 135.362,  59.4208 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p090)
  //Double_t init_e [npdf] = {29.1987,  121.977,  1417.29, 195.023,  69.3519, 46.227,  12.2145,  131.051,  80.0091, 38.2997 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p090)
  //Double_t init_mu[npdf] = {36.543,    75.6613, 1269.56, 156.705 , 51.7181, 31.7906,  7.82371, 111.056,  55.3528, 21.121  }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p090)

  //Double_t init_l [npdf] = {65.7412,  212.066,  2686.84, 351.705, 121.192,  78.1902, 20.9475,  242.107, 135.362,  59.5837 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p180)
  //Double_t init_e [npdf] = {29.186,   131.454,  1417.28, 195.00,   69.4216, 46.2954, 12.9004,  131.051,  80.0091, 38.3652 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p180)
  //Double_t init_mu[npdf] = {36.5552,   80.6114, 1269.56, 156.705,  51.7703, 31.8948,  8.0471,  111.056,  55.3528, 21.2184 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p180)

  //Double_t init_l [npdf] = {65.7299,  216.185,  2686.84, 351.695, 121.248,  78.2628, 21.3441,  242.107, 135.362,  59.6713 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p260)
  //Double_t init_e [npdf] = {29.1806,  131.512,  1417.28, 194.989,  69.4969, 46.3556, 13.3207,  131.051,  80.0091, 38.3704 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p260)
  //Double_t init_mu[npdf] = {36.5492,   80.6731, 1269.56, 156.705,  51.7513, 31.9072,  8.02345, 111.056,  55.3528, 21.3008 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p260)

  //Double_t init_l [npdf] = {65.6629,  214.672,  2686.84, 351.7,   121.254,  78.2863, 21.0859,  242.107, 135.362,  59.682  }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p340)
  //Double_t init_e [npdf] = {29.1421,  135.446,  1417.28, 194.994,  69.5359, 46.3888, 13.2965,  131.051,  80.0091, 38.3492 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p340)
  //Double_t init_mu[npdf] = {36.5208,   79.2256, 1269.56, 156.705,  51.7184, 31.8975,  7.78938, 111.056,  55.3528, 21.3327 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p340)

  //Double_t init_l [npdf] = {65.6109,  214.014,  2686.84, 351.703, 121.264,  78.2721, 20.9627,  242.107, 135.362,  59.6883 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p360)
  //Double_t init_e [npdf] = {29.1123,  135.235,  1417.28, 194.997,  69.5335, 46.3939, 13.2939,  131.051,  80.0091, 38.3364 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p360)
  //Double_t init_mu[npdf] = {36.4986,   78.7794, 1269.56, 156.705,  51.7306, 31.8783,  7.66883, 111.056,  55.3528, 21.3519 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p360)
  
  //Double_t init_l [npdf] = {65.5908,  212.252,  2686.84, 351.704, 121.242,  78.2278, 21.0404,  242.107, 135.362,  59.7016 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p400)
  //Double_t init_e [npdf] = {29.1018,  134.385,  1417.28, 194.998,  69.5335, 46.3781, 13.3409,  131.051,  80.0091, 38.3484 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p400)
  //Double_t init_mu[npdf] = {36.489,    77.8678, 1269.56, 156.705,  51.708,  31.8497,  7.69957, 111.056,  55.3528, 21.3531 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(R2_0p400)

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //Double_t init_l [npdf] = {65.562,   183.869,  2686.85, 351.722, 121.046,  77.9327, 19.1458,  242.107, 135.362,  59.4561 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p150)
  //Double_t init_e [npdf] = {29.1031,  115.811,  1417.29, 195.016,  69.3973, 46.2753, 11.8104,  131.051,  80.0091, 38.2766 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p150)
  //Double_t init_mu[npdf] = {36.4588,   68.0579, 1269.56, 156.705,  51.6491, 31.6574,  7.3354,  111.056,  55.3528, 21.1795 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p150)

  //Double_t init_l [npdf] = {65.6035,  183.943,  2686.85, 351.727, 121.035,  77.9282, 19.1101,  242.107, 135.362,  59.4352 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p100)
  //Double_t init_e [npdf] = {29.1361,  115.353,  1417.29, 195.022,  69.3828, 46.2584, 11.7856,  131.051,  80.0091, 38.2662 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p100)
  //Double_t init_mu[npdf] = {36.4674,   68.5901, 1269.56, 156.705,  51.6526, 31.6698,  7.32454, 111.056,  55.3528, 21.1689 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p100)

  //Double_t init_l [npdf] = {65.5872,  185.41,   2686.85, 351.734, 121.029,  77.9069, 19.1038,  242.107, 135.362,  59.3935 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p040)
  //Double_t init_e [npdf] = {29.1155,  115.644,  1417.29, 195.029,  69.373,  46.2318, 11.7487,  131.051,  80.0091, 38.2583 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p040)
  //Double_t init_mu[npdf] = {36.4717,   69.7656, 1269.56, 156.705,  51.6564, 31.6751,  7.35508, 111.056,  55.3528, 21.1352 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p040)

  //Double_t init_l [npdf] = {65.5903,  185.71,   2686.85, 351.738, 121.044,  77.9046, 19.1041,  242.107, 135.362,  59.3844 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p030)
  //Double_t init_e [npdf] = {29.1233,  115.798,  1417.29, 195.032,  69.3652, 46.3652, 11.7259,  131.051,  80.0091, 38.2571 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p030)
  //Double_t init_mu[npdf] = {36.467,    69.9115, 1269.56, 156.705,  51.6784, 31.6775,  7.3782,  111.056,  55.3528, 21.1273 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_m0p030)

  //Double_t init_l [npdf] = {65.609,   186.799,  2686.85, 351.743, 121.019,  77.9054, 19.2501,  242.107, 135.362,  59.3656 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p000)
  //Double_t init_e [npdf] = {29.1262,  116.126,  1417.29, 195.038,  69.362,  46.2029, 11.7958,  131.051,  80.0091, 38.2505 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p000)
  //Double_t init_mu[npdf] = {36.4828,   70.6731, 1269.56, 156.705,  51.6572, 31.7025,  7.45437, 111.056,  55.3528, 21.1151 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p000)  

  //Double_t init_l [npdf] = {65.64,    196.627,  2686.86, 351.751, 121.112,  77.9672, 20.0119,  242.107, 135.362,  59.3998 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p090)
  //Double_t init_e [npdf] = {29.16,    122.014,  1417.3,  195.046,  69.3838, 46.191,  12.3577,  131.051,  80.0091, 38.2879 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p090)
  //Double_t init_mu[npdf] = {36.48,     74.6133, 1269.56, 156.705,  51.7283, 31.7763,  7.65421, 111.056,  55.3528, 21.1119 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p090)

  //Double_t init_l [npdf] = {65.6697,  204.515,  2686.86, 351.743, 121.233,  78.0195, 20.71,    242.107, 135.362,  59.5251 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p180)
  //Double_t init_e [npdf] = {29.1785,  127.803,  1417.3,  195.037,  69.4269, 46.2201, 12.9317,  131.051,  80.0091, 38.3651 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p180)
  //Double_t init_mu[npdf] = {36.4912,   76.7122, 1269.56, 156.705,  51.8062, 31.7994,  7.77834, 111.056,  55.3528, 21.16   }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p180)
  
  //Double_t init_l [npdf] = {65.6663,  207.247,  2686.87, 351.727, 121.291,  78.0685, 20.9557,  242.107, 135.362,  59.6048 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p260)
  //Double_t init_e [npdf] = {29.1842,  130.335,  1417.31, 195.022,  69.4587, 46.2514, 13.2045,  131.051,  80.0091, 38.3955 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p260)
  //Double_t init_mu[npdf] = {36.4821,   76.9121, 1269.56, 156.705,  51.8319, 31.8171,  7.75125, 111.056,  55.3528, 21.2093 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p260)

  //Double_t init_l [npdf] = {65.6607,  206.698,  2686.87, 351.72,  121.335,  78.0931, 21.0816,  242.107, 135.362,  59.6685 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p340)
  //Double_t init_e [npdf] = {29.1726,  130.719,  1417.3,  195.015,  69.4967, 46.2818, 13.3507,  131.051,  80.0091, 38.4193 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p340)
  //Double_t init_mu[npdf] = {36.4881,   75.9978, 1269.56, 156.705,  51.8387, 31.8113,  7.73091, 111.056,  55.3528, 21.2492 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p340)

  //Double_t init_l [npdf] = {65.6306,  206.544,  2686.86, 351.717,  121.309, 78.0906, 20.9858,  242.107, 135.362,  59.6698 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p360)
  //Double_t init_e [npdf] = {29.1655,  130.747,  1417.3,  195.012,  69.4717, 46.2951, 13.2888,  131.051,  80.0091, 38.4312 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p360)
  //Double_t init_mu[npdf] = {36.465,    75.7973, 1269.56, 156.705,  51.8376, 31.7995,  7.69698, 111.056,  55.3528, 21.2386 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p360)

  //Double_t init_l [npdf] = {65.6518,  205.831,  2686.86, 351.712, 121.315,  78.0877, 20.9276,  242.107, 135.362,  59.6815 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p400)
  //Double_t init_e [npdf] = {29.1798,  130.505,  1417.3,  195.007,  69.4895, 46.2961, 13.2859,  131.051,  80.0091, 38.4229 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p400)
  //Double_t init_mu[npdf] = {36.472,    75.326,  1269.56, 156.705,  51.8255, 31.7916,  7.64167, 111.056,  55.3528, 21.2586 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(S1_0p400)

  //Double_t init_l [npdf] = {65.6261,  187.634,  2686.85, 351.744, 121.027,  77.8971, 19.354,   242.107, 135.362,  59.3732 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p10)
  //Double_t init_e [npdf] = {29.1256,  116.556,  1417.29, 195.038,  69.3669, 46.1931, 11.8753,  131.051,  80.0091, 38.2653 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p10)
  //Double_t init_mu[npdf] = {36.5005,   71.077,  1269.56, 156.705,  51.6603, 31.7041,  7.47872, 111.056,  55.3528, 21.1079 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p10)

  //Double_t init_l [npdf] = {65.5992,  189.504,  2686.84, 351.726, 121.128,  78.0445, 19.2267,  242.107, 135.362,  59.5881 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p88)
  //Double_t init_e [npdf] = {29.1338,  119.789,  1417.28, 195.02,   69.5477, 46.4002, 11.8982,  131.051,  80.0091, 38.2723 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p88)
  //Double_t init_mu[npdf] = {36.4653,   69.7154,  1269.56, 156.705, 51.58,   31.6443,  7.32856, 111.056,  55.3528, 21.3158 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p88)

  //Double_t init_l [npdf] = {65.5647,  187.586,  2686.85, 351.76,  121.034,  77.8796, 19.4342,  242.107, 135.362,  59.3508 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_1p05)
  //Double_t init_e [npdf] = {29.1063,  116.835,  1417.29, 195.054,  69.3883, 46.1736, 12.0137,  131.051,  80.0091, 38.2434 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_1p05)
  //Double_t init_mu[npdf] = {36.4584,   70.751,  1269.56, 156.705,  51.6461, 31.706,   7.42054, 111.056,  55.3528, 21.1074 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_1p05)

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //Double_t init_l [npdf] = { 65.601, 178.166,  2686.88, 351.731, 121.163,  77.8049, 19.4316,  242.107, 135.362,  59.5377 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m5p00)
  //Double_t init_e [npdf] = { 29.148, 111.938,  1417.31, 195.025,  69.3407, 46.1632, 12.1556,  131.051,  80.0091, 38.466  }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m5p00)
  //Double_t init_mu[npdf] = { 36.453,  66.2287, 1269.56, 156.705,  51.8225, 31.6417,  7.27599, 111.056,  55.3528, 21.0716 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m5p00)

  //Double_t init_l [npdf] = { 65.629,  179.741,  2686.87, 351.721, 121.129,  77.8369, 19.3424,  242.107, 135.362,  59.5178 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m4p00)
  //Double_t init_e [npdf] = { 29.1405, 112.494,  1417.31, 195.016,  69.3332, 46.1823, 12.0202,  131.051,  80.0091, 38.4367 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m4p00)
  //Double_t init_mu[npdf] = { 36.4885,  67.2475, 1269.56, 156.705,  51.7962, 31.6546,  7.32223, 111.056,  55.3528, 21.0812 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m4p00)

  //Double_t init_l [npdf] = { 65.6649, 181.833, 2686.86, 351.72, 121.094,  77.8631, 19.1942,  242.107, 135.362,  59.4658 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m3p00)
  //Double_t init_e [npdf] = { 29.1568, 113.478, 1417.3,  195.015, 69.3308, 46.1931, 11.7995,  131.051,  80.0091, 38.3727 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m3p00)
  //Double_t init_mu[npdf] = { 36.5081,  68.355, 1269.56, 156.705, 51.7634, 31.6699,  7.39471, 111.056,  55.3528, 21.0931 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m3p00)

  //Double_t init_l [npdf] = { 65.6556, 183.892,  2686.85, 351.722, 121.041,  77.9152, 19.2057,  242.107, 135.362,  59.4372 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m2p00)
  //Double_t init_e [npdf] = { 29.1523, 114.411,  1417.29, 195.016,  69.3223, 46.214,  11.7381,  131.051,  80.0091, 38.3312 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m2p00)
  //Double_t init_mu[npdf] = { 36.5033,  69.4809, 1269.56, 156.705,  51.7182, 31.7012,  7.46763, 111.056,  55.3528, 21.1059 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m2p00)

  //Double_t init_l [npdf] = { 65.6482, 186.124,  2686.85, 351.731, 121.009,  77.9444, 19.2095,  242.107, 135.362,  59.4069 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m1p00)
  //Double_t init_e [npdf] = { 29.1408, 115.634,  1417.29, 195.025,  69.3347, 46.2229, 11.7381,  131.051,  80.0091, 38.2887 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m1p00)
  //Double_t init_mu[npdf] = { 36.5074,  70.4896, 1269.56, 156.705,  51.6747, 31.7216,  7.47135, 111.056,  55.3528, 21.1182 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_m1p00)
  
  //Double_t init_l [npdf] = { 65.609,  186.799,  2686.85, 351.743, 121.019,  77.9054, 19.2501,  242.107, 135.362,  59.3656 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_0p00)
  //Double_t init_e [npdf] = { 29.1262, 116.126,  1417.29, 195.038,  69.362,  46.2029, 11.7958,  131.051,  80.0091, 38.2505 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_0p00)
  //Double_t init_mu[npdf] = { 36.4828,  70.6731, 1269.56, 156.705,  51.6572, 31.7025,  7.45437, 111.056,  55.3528, 21.1151 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_0p00)

  //Double_t init_l [npdf] = { 65.54,   187.466, 2686.86, 351.762, 121.029,  77.8875, 19.3553,  242.107, 135.362,  59.3536 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_1p00)
  //Double_t init_e [npdf] = { 29.0978, 116.898, 1417.3,  195.057,  69.3776, 46.1816, 11.9808,  131.051,  80.0091, 38.2475 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_1p00)
  //Double_t init_mu[npdf] = { 36.4423, 70.568,  1269.56, 156.705,  51.651,  31.7059,  7.37452, 111.056,  55.3528, 21.1061 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_1p00)

  //Double_t init_l [npdf] = { 65.5596, 187.279, 2686.86, 351.763, 121.022,  77.896,  19.4114,  242.107, 135.362,  59.3546 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_1p05)
  //Double_t init_e [npdf] = { 29.1026, 116.777, 1417.29, 195.058,  69.3791, 46.1833, 12.0393,  131.051,  80.0091, 38.2475 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_1p05)
  //Double_t init_mu[npdf] = { 36.457,  70.5018, 1269.56, 156.705,  51.6426, 31.7127,  7.37211, 111.056,  55.3528, 21.1071 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_1p05)

  //Double_t init_l [npdf] = { 65.5234, 186.79,   2686.86, 351.774, 121.051,  77.8451, 19.5137,  242.107, 135.362,  59.3639 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_2p00)
  //Double_t init_e [npdf] = { 29.0857, 116.888,  1417.3,  195.068,  69.3848, 46.1503, 12.2113,  131.051,  80.0091, 38.2608 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_2p00)
  //Double_t init_mu[npdf] = { 36.4377,  69.9017, 1269.56, 156.705,  51.6666, 31.6948,  7.30238, 111.056,  55.3528, 21.1031 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_2p00)

  //Double_t init_l [npdf] = { 65.4835, 186.082,  2686.87, 351.789, 121.067,  77.8231, 19.5109,  242.107, 135.362,  59.3671 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_3p00)
  //Double_t init_e [npdf] = { 29.077,  116.811,  1417.31, 195.083,  69.394,  46.1391, 12.3032,  131.051,  80.0091, 38.2776 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_3p00)
  //Double_t init_mu[npdf] = { 36.4064,  69.2709, 1269.56, 156.705,  51.6732, 31.684,   7.20775, 111.056,  55.3528, 21.0895 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS1_3p00)

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //Double_t init_l [npdf] = { 65.4673, 186.231,  2686.86, 351.784, 121.077,  77.7922, 19.6273,  242.107, 135.362,  59.3364 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_m3p00)
  //Double_t init_e [npdf] = { 29.0571, 116.937,  1417.3,  195.079,  69.4004, 46.1093, 12.2936,  131.051,  80.0091, 38.2481 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_m3p00)
  //Double_t init_mu[npdf] = { 36.4102,  69.2938, 1269.56, 156.705,  51.6763, 31.6829,  7.33372, 111.056,  55.3528, 21.0883 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_m3p00)

  //Double_t init_l [npdf] = { 65.5247, 186.941,  2686.86, 351.771, 121.04,   77.8609, 19.5291,  242.107, 135.362,  59.3309 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_m2p00)
  //Double_t init_e [npdf] = { 29.1059, 117.041,  1417.3,  195.066,  69.3814, 46.1538, 12.1312,  131.051,  80.0091, 38.2353 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_m2p00)
  //Double_t init_mu[npdf] = { 36.4188,  69.9004, 1269.56, 156.705,  51.6581, 31.7071,  7.39783, 111.056,  55.3528, 21.0956 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_m2p00)

  //Double_t init_l [npdf] = { 65.5628, 187.3,    2686.86, 351.764, 121.046,  77.8759, 19.4044,  242.107, 135.362,  59.3602 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_m1p00)
  //Double_t init_e [npdf] = { 29.1066, 116.784,  1417.3,  195.059,  69.3763, 46.1717, 11.9907,  131.051,  80.0091, 38.2516 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_m1p00)
  //Double_t init_mu[npdf] = { 36.4563,  70.5155, 1269.56, 156.705,  51.6695, 31.7042,  7.41375, 111.056,  55.3528, 21.1086 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_m1p00)
  
  //Double_t init_l [npdf] = { 65.609,  186.799,  2686.85, 351.743, 121.019,  77.9054, 19.2501,  242.107, 135.362,  59.3656 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_0p00)
  //Double_t init_e [npdf] = { 29.1262, 116.126,  1417.29, 195.038,  69.362,  46.2029, 11.7958,  131.051,  80.0091, 38.2505 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_0p00)
  //Double_t init_mu[npdf] = { 36.4828,  70.6731, 1269.56, 156.705,  51.6572, 31.7025,  7.45437, 111.056,  55.3528, 21.1151 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_0p00)

  //Double_t init_l [npdf] = { 65.6354, 186.086,  2686.85, 351.729, 121.036,  77.9064, 19.2138,  242.107, 135.362,  59.3976 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_1p00)
  //Double_t init_e [npdf] = { 29.1401, 115.651,  1417.29, 195.023,  69.3539, 46.2053, 11.6891,  131.051,  80.0091, 38.2837 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_1p00)
  //Double_t init_mu[npdf] = { 36.4953,  70.4351, 1269.56, 156.705,  51.6817, 31.701,   7.52471, 111.056,  55.3528, 21.1139 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_1p00)

  //Double_t init_l [npdf] = { 65.6882, 184.124,  2686.85, 351.719, 121.055,  77.9091, 19.2996,  242.107, 135.362,  59.4317 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_2p00)
  //Double_t init_e [npdf] = { 29.176,  114.513,  1417.29, 195.013,  69.3352, 46.2096, 11.7449,  131.051,  80.0091, 38.325  }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_2p00)
  //Double_t init_mu[npdf] = { 36.5122,  69.6102, 1269.56, 156.705,  51.7202, 31.6994,  7.55472, 111.056,  55.3528, 21.1067 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_2p00)

  //Double_t init_l [npdf] = { 65.6729, 181.795, 2686.86, 351.718, 121.071,  77.8732, 19.309,   242.107, 135.362,  59.4624 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_3p00)
  //Double_t init_e [npdf] = { 29.178,  113.366, 1417.3,  195.013,  69.3243, 46.2088, 11.7693,  131.051,  80.0091, 38.3671 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_3p00)
  //Double_t init_mu[npdf] = { 36.4948,  68.428, 1269.56, 156.705,  51.7472, 31.6644,  7.53971, 111.056,  55.3528, 21.0953 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_3p00)

  //Double_t init_l [npdf] = { 65.6337, 179.567,  2686.87, 351.72, 121.129,  77.8104, 19.3064,  242.107, 135.362,  59.4666 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_4p00)
  //Double_t init_e [npdf] = { 29.1497, 112.419,  1417.3,  195.015, 69.3377, 46.1633, 11.8692,  131.051,  80.0091, 38.3861 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_4p00)
  //Double_t init_mu[npdf] = { 36.4841,  67.1476, 1269.56, 156.705, 51.7918, 31.6471,  7.43717, 111.056,  55.3528, 21.0805 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_4p00)

  //Double_t init_l [npdf] = { 65.6166, 177.953,  2686.87, 351.728, 121.165,  77.7585, 19.4135,  242.107, 135.362,  59.4663 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_5p00)
  //Double_t init_e [npdf] = { 29.1533, 111.808,  1417.31, 195.022,  69.3516, 46.1378, 12.1178,  131.051,  80.0091, 38.3999 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_5p00)
  //Double_t init_mu[npdf] = { 36.4633,  66.1457, 1269.56, 156.705,  51.813,  31.6207,  7.29576, 111.056,  55.3528, 21.0664 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPS2_5p00)

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //Double_t init_l [npdf] = { 65.6166, 187.393,  2686.85, 351.741, 121.067,  77.9165, 19.3222,  242.107, 135.362,  59.3563 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p50)
  //Double_t init_e [npdf] = { 29.1432, 116.632,  1417.29, 195.035,  69.3822, 46.2209, 11.857,   131.051,  80.0091, 38.2474 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p50)
  //Double_t init_mu[npdf] = { 36.4733,  70.7606, 1269.56, 156.705,  51.6846, 31.6956,  7.46529, 111.056,  55.3528, 21.109  }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p50)  

  //Double_t init_l [npdf] = { 65.6376, 187.387,  2686.85, 351.741, 121.069,  77.9145, 19.2867,  242.107, 135.362,  59.3747 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p10)
  //Double_t init_e [npdf] = { 29.1422, 116.548,  1417.29, 195.036,  69.3889, 46.2169, 11.8389,  131.051,  80.0091, 38.2678 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p10)
  //Double_t init_mu[npdf] = { 36.4955,  70.8392, 1269.56, 156.705,  51.6806, 31.6976,  7.44784, 111.056,  55.3528, 21.1069 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p10)

  //Double_t init_l [npdf] = { 65.6272, 187.551,  2686.85, 351.739, 121.051,  77.9163, 19.2916,  242.107, 135.362,  59.3621 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p00)
  //Double_t init_e [npdf] = { 29.1412, 116.684,  1417.29, 195.034,  69.386,  46.2211, 11.8012,  131.051,  80.0091, 38.2432 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p00)
  //Double_t init_mu[npdf] = { 36.486,   70.8677, 1269.56, 156.705,  51.6645, 31.6953,  7.49037, 111.056,  55.3528, 21.1189 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m2p00)

  //Double_t init_l [npdf] = { 65.6196, 187.481,  2686.85, 351.741, 121.062,  77.9247, 19.3157,  242.107, 135.362,  59.3634 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m1p50)
  //Double_t init_e [npdf] = { 29.1331, 116.544,  1417.29, 195.035,  69.3832, 46.2243, 11.8449,  131.051,  80.0091, 38.252  }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m1p50)
  //Double_t init_mu[npdf] = { 36.4864,  70.9375, 1269.56, 156.705,  51.6784, 31.7004,  7.47082, 111.056,  55.3528, 21.1114 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m1p50)

  //Double_t init_l [npdf] = { 65.6918, 208.51,   2686.85, 351.719, 121.251,  78.1201, 20.6544,  242.107, 135.362,  59.5606 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m1p00)
  //Double_t init_e [npdf] = { 29.2028, 131.364,  1417.29, 195.013,  69.4258, 46.2753, 12.8694,  131.051,  80.0091, 38.3692 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m1p00)
  //Double_t init_mu[npdf] = { 36.489,   77.1457, 1269.56, 156.705,  51.8254, 31.8448,  7.78501, 111.056,  55.3528, 21.1914 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m1p00)

  //Double_t init_l [npdf] = { 65.6275, 187.305,  2686.85, 351.739, 121.065,  77.9303, 19.259,   242.107, 135.362,  59.3694 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m0p50)
  //Double_t init_e [npdf] = { 29.1502, 116.57,   1417.29, 195.033,  69.3745, 46.2214, 11.7762,  131.051,  80.0091, 38.2552 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m0p50)
  //Double_t init_mu[npdf] = { 36.4773,  70.7351, 1269.56, 156.705,  51.691,  31.7089,  7.48283, 111.056,  55.3528, 21.1142 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_m0p50)

  //Double_t init_l [npdf] = { 65.609,  186.799,  2686.85, 351.743, 121.019,  77.9054, 19.2501,  242.107, 135.362,  59.3656 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_0p00)
  //Double_t init_e [npdf] = { 29.1262, 116.126,  1417.29, 195.038,  69.362,  46.2029, 11.7958,  131.051,  80.0091, 38.2505 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_0p00)
  //Double_t init_mu[npdf] = { 36.4828,  70.6731, 1269.56, 156.705,  51.6572, 31.7025,  7.45437, 111.056,  55.3528, 21.1151 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_0p00)

  //Double_t init_l [npdf] = { 65.6397, 187.134, 2686.85, 351.738, 121.065,  77.9009, 19.2952,  242.107, 135.362,  59.3576 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_0p50)
  //Double_t init_e [npdf] = { 29.1476, 116.41,  1417.29, 195.032,  69.3942, 46.1974, 11.846,   131.051,  80.0091, 38.2449 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_0p50)
  //Double_t init_mu[npdf] = { 36.4921,  70.724, 1269.56, 156.705,  51.671,  31.7035,  7.44921, 111.056,  55.3528, 21.1127 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV1_0p50)

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //Double_t init_l [npdf] = { 65.5737, 183.192,  2686.85, 351.746, 121.02,   77.8582, 19.0364,  242.107, 135.362,  59.3771 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_m0p50)
  //Double_t init_e [npdf] = { 29.1045, 114.569,  1417.29, 195.041,  69.3825, 46.2028, 11.687,   131.051,  80.0091, 38.2367 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_m0p50)
  //Double_t init_mu[npdf] = { 36.4692,  68.6235, 1269.56, 156.705,  51.6371, 31.6554,  7.34936, 111.056,  55.3528, 21.1404 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_m0p50)
  
  //Double_t init_l [npdf] = { 65.609,  186.799,  2686.85, 351.743, 121.019,  77.9054, 19.2501,  242.107, 135.362,  59.3656 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_0p00)
  //Double_t init_e [npdf] = { 29.1262, 116.126,  1417.29, 195.038,  69.362,  46.2029, 11.7958,  131.051,  80.0091, 38.2505 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_0p00)
  //Double_t init_mu[npdf] = { 36.4828,  70.6731, 1269.56, 156.705,  51.6572, 31.7025,  7.45437, 111.056,  55.3528, 21.1151 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_0p00)

  //Double_t init_l [npdf] = { 65.7647, 201.241, 2686.85, 351.72,  121.086,  78.0411, 20.3173,  242.107, 135.362,  59.4203 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_0p50)
  //Double_t init_e [npdf] = { 29.2233, 124.07,  1417.29, 195.015,  69.357,  46.2362, 12.4066,  131.051,  80.0091, 38.2978 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_0p50)
  //Double_t init_mu[npdf] = { 36.5414,  77.171, 1269.56, 156.705,  51.7287, 31.8049,  7.91065, 111.056,  55.3528, 21.1225 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_0p50)

  //Double_t init_l [npdf] = { 65.8897, 218.033,  2686.84, 351.682, 121.304,  78.3483, 21.3613,  242.107, 135.362,  59.7078 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p00)
  //Double_t init_e [npdf] = { 29.3195, 135.782,  1417.27, 194.977,  69.5944, 46.4762, 13.0965,  131.051,  80.0091, 38.3703 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p00)
  //Double_t init_mu[npdf] = { 36.5702,  82.2511, 1269.56, 156.705,  51.7095, 31.8721,  8.26483, 111.056,  55.3528, 21.3375 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p00)

  //Double_t init_l [npdf] = { 65.681,  196.305,  2686.84, 351.714, 121.246,  78.1252, 19.8314,  242.107, 135.362,  59.6634 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p50)
  //Double_t init_e [npdf] = { 29.1962, 124.398,  1417.28, 195.008,  69.6142, 46.4443, 12.288,   131.051,  80.0091, 38.303  }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p50)
  //Double_t init_mu[npdf] = { 36.4848,  71.9074, 1269.56, 156.705,  51.6315, 31.6808,  7.54338, 111.056,  55.3528, 21.3604 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p50)

  //Double_t init_l [npdf] = { 65.608,  189.187,  2686.84, 351.724, 121.139,  78.036,  19.3931,  242.107, 135.362,  59.5778 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p88)
  //Double_t init_e [npdf] = { 29.1559, 119.903,  1417.28, 195.019,  69.5485, 46.4013, 12.0206,  131.051,  80.0091, 38.2617 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p88)
  //Double_t init_mu[npdf] = { 36.4521,  69.2835, 1269.56, 156.705,  51.5903, 31.6347,  7.37247, 111.056,  55.3528, 21.3161 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_1p88)

  //Double_t init_l [npdf] = { 65.6109, 187.851,  2686.85, 351.726, 121.144,  77.9828, 19.3339,  242.107, 135.362,  59.5586 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_2p00)
  //Double_t init_e [npdf] = { 29.1533, 119.164,  1417.28, 195.02,   69.5508, 46.3647, 12.0219,  131.051,  80.0091, 38.2553 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_2p00)
  //Double_t init_mu[npdf] = { 36.4576,  68.6872, 1269.56, 156.705,  51.5936, 31.6181,  7.31197, 111.056,  55.3528, 21.3033 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_2p00)

  //Double_t init_l [npdf] = { 65.5675, 184.675,  2686.85, 351.738, 121.121,  77.9567, 19.2118,  242.107, 135.362,  59.514 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_2p50)
  //Double_t init_e [npdf] = { 29.1163, 117.081,  1417.29, 195.032,  69.5172, 46.3544, 11.9443,  131.051,  80.0091, 38.242 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_2p50)
  //Double_t init_mu[npdf] = { 36.4513,  67.5945, 1269.56, 156.705,  51.6036, 31.6023,  7.26751, 111.056,  55.3528, 21.272 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPV2_2p50)

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  //Double_t init_l [npdf] = { 65.5299, 184.356,  2686.85, 351.732, 121.028,  77.9393, 19.0823,  242.107, 135.362,  59.4239 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_m0p15)
  //Double_t init_e [npdf] = { 29.0836, 115.75,   1417.29, 195.027,  69.4002, 46.2522, 11.7881,  131.051,  80.0091, 38.2432 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_m0p15)
  //Double_t init_mu[npdf] = { 36.4464,  68.6057, 1269.56, 156.705,  51.6278, 31.6871,  7.29425, 111.056,  55.3528, 21.1807 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_m0p15)

  //Double_t init_l [npdf] = { 65.5813, 184.691,  2686.85, 351.742, 121.021,  77.8847, 19.1246,  242.107, 135.362,  59.375  }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_m0p07)
  //Double_t init_e [npdf] = { 29.1105, 115.305,  1417.29, 195.036,  69.3799, 46.2072, 11.7712,  131.051,  80.0091, 38.2354 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_m0p07)
  //Double_t init_mu[npdf] = { 36.4709,  69.3865, 1269.56, 156.705,  51.6409, 31.6774,  7.35339, 111.056,  55.3528, 21.1396 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_m0p07)

  //Double_t init_l [npdf] = { 65.609,  186.799,  2686.85, 351.743, 121.019,  77.9054, 19.2501,  242.107, 135.362,  59.3656 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p00)
  //Double_t init_e [npdf] = { 29.1262, 116.126,  1417.29, 195.038,  69.362,  46.2029, 11.7958,  131.051,  80.0091, 38.2505 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p00)
  //Double_t init_mu[npdf] = { 36.4828,  70.6731, 1269.56, 156.705,  51.6572, 31.7025,  7.45437, 111.056,  55.3528, 21.1151 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p00)

  //Double_t init_l [npdf] = { 65.671,  194.313,  2686.85, 351.744, 121.05,   77.9575, 19.9077,  242.107, 135.362,  59.3853 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p07)
  //Double_t init_e [npdf] = { 29.1764, 120.171,  1417.29, 195.038,  69.3534, 46.1962, 12.1796,  131.051,  80.0091, 38.2762 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p07)
  //Double_t init_mu[npdf] = { 36.4947,  74.1414, 1269.56, 156.705,  51.6967, 31.7613,  7.72812, 111.056,  55.3528, 21.1091 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p07)

  //Double_t init_l [npdf] = { 65.7212, 207.023,  2686.85, 351.729, 121.118,  78.0823, 20.685,   242.107, 135.362,  59.488  }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p15)
  //Double_t init_e [npdf] = { 29.2051, 128.073,  1417.29, 195.024,  69.3822, 46.2273, 12.7025,  131.051,  80.0091, 38.3209 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p15)
  //Double_t init_mu[npdf] = { 36.5161,  78.9505, 1269.56, 156.705,  51.7354, 31.8551,  7.98252, 111.056,  55.3528, 21.1672 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p15)

  //Double_t init_l [npdf] = { 65.7448, 215.363,  2686.85, 351.709, 121.226,  78.1921, 21.2812,  242.107, 135.362,  59.6097 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p22)
  //Double_t init_e [npdf] = { 29.1945, 134.076,  1417.29, 195.004,  69.4475, 46.3035, 13.1787,  131.051,  80.0091, 38.3595 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p22)
  //Double_t init_mu[npdf] = { 36.5503,  81.2865, 1269.56, 156.705,  51.7783, 31.8886,  8.10256, 111.056,  55.3528, 21.2501 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p22)

  //Double_t init_l [npdf] = { 65.7029, 218.463,  2686.85, 351.696, 121.271,  78.2344, 21.5685, 242.107, 135.362,  59.6987 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p30)
  //Double_t init_e [npdf] = { 29.1919, 137.122,  1417.28, 194.991,  69.4901, 46.337, 13.5292,  131.051,  80.0091, 38.378  }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p30)
  //Double_t init_mu[npdf] = { 36.511,   81.3404, 1269.56, 156.705,  51.7812, 31.8974,  8.0393, 111.056,  55.3528, 21.3207 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p30)

  //Double_t init_l [npdf] = { 65.6634, 217.696,  2686.84, 351.689, 121.292,  78.2761, 21.4158,  242.107, 135.362,  59.7265, };//veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p36)
  //Double_t init_e [npdf] = { 29.1676, 137.196,  1417.28, 194.983,  69.5126, 46.3819, 13.5017,  131.051,  80.0091, 38.3799, };//veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p36)
  //Double_t init_mu[npdf] = { 36.4958,  80.5002, 1269.56, 156.705,  51.7789, 31.8942,  7.91409, 111.056,  55.3528, 21.3466, };//veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p36)

  //Double_t init_l [npdf] = { 65.6536, 217.573, 2686.84, 351.691, 121.327,  78.2879, 21.4447,  242.107, 135.362,  59.7293 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p37)
  //Double_t init_e [npdf] = { 29.1524, 137.279, 1417.28, 194.985,  69.5399, 46.4007, 13.5157,  131.051,  80.0091, 38.3778 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p37)
  //Double_t init_mu[npdf] = { 36.5012,  80.294, 1269.56, 156.705,  51.7869, 31.8872,  7.92904, 111.056,  55.3528, 21.3515 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p37)

  //Double_t init_l [npdf] = { 65.6402, 215.156,  2686.84, 351.685, 121.288,  78.2708, 21.2797,  242.107, 135.362,  59.753  }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p45)
  //Double_t init_e [npdf] = { 29.1455, 135.968,  1417.28, 194.98,   69.5439, 46.3953, 13.4609,  131.051,  80.0091, 38.3754 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p45)
  //Double_t init_mu[npdf] = { 36.4947,  79.1877, 1269.56, 156.705,  51.7445, 31.8756,  7.81875, 111.056,  55.3528, 21.3777 }; //veto D(*)(2S) // sigMC(40 streams) // npmc(OPT_0p45)
  
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Double_t init[npdf] = {0};
  if     ( fl_lep== 1 ){ for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) init[ipdf] = init_mu[ipdf]; } // mu
  else if( fl_lep==10 ){ for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) init[ipdf] = init_e [ipdf]; } // e
  else if( fl_lep== 0 ){ for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) init[ipdf] = init_l [ipdf]; } // l
  
  Double_t init_tot = 0;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    init[ipdf] *= pdf_nexp[ipdf];
    init_tot += init[ipdf];
  }
  std::cout << "[INITIAL VALUE]" << std::endl;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){  
    std::cout << "[Category] "
	      << std::setw(15) << std::right << pdf_name[ipdf] << " : "
	      << std::setw(15) << std::right << init    [ipdf] << " events"
	      << std::endl;
  }
  std::cout << " ---> total " << init_tot << " events" << std::endl;


  std::cout << "corr_corr_d = " << corr_corr_d << std::endl
	    << "corr_fake_d = " << corr_fake_d << std::endl
	    << "  (* fake_d will be applied later)" << std::endl;
  std::cout << "[INITIAL VALUE]" << std::endl;
  init_tot = 0;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]!=2 ) init[ipdf] *= corr_corr_d;
    init_tot += init[ipdf];
    std::cout << "[Category] "
	      << std::setw(15) << std::right << pdf_name[ipdf] << " : "
	      << std::setw(15) << std::right << init    [ipdf] << " events"
	      << std::endl;
  }
  std::cout << " ---> total " << init_tot << " events" << std::endl;
  //*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <OBSERVABLES>
  RooRealVar* nb     = new RooRealVar( "nb",   "NB",               nb_xmin,   nb_xmax ); // x 
  RooRealVar* eecl   = new RooRealVar( "eecl", "E_{ECL} [GeV]",  eecl_xmin, eecl_xmax ); // y
  RooRealVar* w      = new RooRealVar( "w",    "w",                    0.0,      10.0 ); // weight
  RooArgSet*  varset = new RooArgSet ( *nb, *eecl     );
  RooArgSet*  varsetw = new RooArgSet( *nb, *eecl, *w );

  nb  ->setBins(   nb_xbin );
  eecl->setBins( eecl_xbin );
  
  nb  ->setRange( "signal_box_nb",    0.8, 1.0 );
  eecl->setRange( "signal_box_nb",    0.0, 1.2 );
  nb  ->setRange( "norm_box_nb",     -1.0, 0.8 );
  eecl->setRange( "norm_box_nb",      0.0, 1.2 );
  nb  ->setRange( "signal_box_eecl", -1.0, 1.0 );
  eecl->setRange( "signal_box_eecl",  0.0, 0.5 );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <PDF>
  TFile** pdf_file      = new TFile*[npdf];
  TH2D**  pdf_hist_2d   = new TH2D* [npdf];
  TH1D**  pdf_hist_nb   = new TH1D* [npdf];
  TH1D**  pdf_hist_eecl = new TH1D* [npdf];

  for( Int_t ipdf=npdf-1; ipdf>=0; ipdf-- ){
    pdf_file[ipdf] = new TFile( Form("%s/makepdf_%s_lep%d_%s.root", pdf_dir, pdf_name[ipdf], fl_lep, (ipdf==1 ? fl_par_pdf : "0p0") ) ); // nominal
    /* <for syststudy : decay modelling, calib factor, D** composition, DD, nor(cos reso)>
    //Int_t systpdf_no = 9; // 2(nor), 3(D**), 5-9(fakeD*) // set pdf_dir_syst = "pdf_syst1"
    Int_t systpdf_no = 2; // 2(nor), 3(D**), 4(DD)       // set pdf_dir_syst = "pdf_syst0"
    if( ipdf==systpdf_no ) pdf_file[ipdf] = new TFile( Form("%s/makepdf_%s_lep%d_%s_%d.root", pdf_dir_syst, pdf_name[ipdf], fl_lep, (ipdf==1 ? fl_par_pdf : "0p0"), tag_cnt ) );
    else                   pdf_file[ipdf] = new TFile( Form("%s/makepdf_%s_lep%d_%s.root",    pdf_dir,      pdf_name[ipdf], fl_lep, (ipdf==1 ? fl_par_pdf : "0p0")          ) );
    */

    if( pdf_file[ipdf]->IsZombie() ) std::cerr << "[ABORT] can not find pdf-file for " << pdf_name[ipdf] << std::endl, abort();
    pdf_hist_2d[ipdf] = (TH2D*)pdf_file[ipdf]->Get( Form("nb_eecl_%s_lep%d", pdf_name[ipdf], fl_lep) );

    pdf_hist_nb  [ipdf] = (TH1D*)pdf_file[ipdf]->Get( Form(  "nb_%s_all_nb_lep%d",pdf_name[ipdf],fl_lep) );
    if( ipdf==1 ) pdf_hist_eecl[ipdf] = (TH1D*)pdf_file[   2]->Get( Form("eecl_%s_all_nb_lep%d",pdf_name[   2],fl_lep) ); // normalization PDF is used for signal-PDF.
    else          pdf_hist_eecl[ipdf] = (TH1D*)pdf_file[ipdf]->Get( Form("eecl_%s_all_nb_lep%d",pdf_name[ipdf],fl_lep) );
    if( pdf_hist_2d  [ipdf]== NULL ) std::cerr << "[ABORT] can not find  2d  histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_nb  [ipdf]== NULL ) std::cerr << "[ABORT] can not find  nb  histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_eecl[ipdf]== NULL ) std::cerr << "[ABORT] can not find eecl histogram for " << pdf_name[ipdf] << std::endl, abort();

    if( pdf_hist_2d  [ipdf]->GetNbinsX()!=  nb_xbin ) std::cerr << "[ABORT] Wrong x( nb ) binning in 2d histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_2d  [ipdf]->GetNbinsY()!=eecl_xbin ) std::cerr << "[ABORT] Wrong y(eecl) binning in 2d histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_nb  [ipdf]->GetNbinsX()!=  nb_xbin ) std::cerr << "[ABORT] Wrong x( nb ) binning in 1d histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_eecl[ipdf]->GetNbinsX()!=eecl_xbin ) std::cerr << "[ABORT] Wrong x(eecl) binning in 1d histogram for " << pdf_name[ipdf] << std::endl, abort();
  }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <for syststudy : MC statistics>
  /*
  Int_t systpdf_no = 1; // 0-9
  if( tag_cnt ){
    if( pdf_dim[systpdf_no]==2 ){ // 2-dimensional histogram-PDF
      //for( Int_t it=0; it<2; it++ ){
      Double_t rnd_x, rnd_y;
      TH2D* syst_hist = new TH2D( *pdf_hist_2d[systpdf_no] );
      pdf_hist_2d[systpdf_no]->Reset();
      for( Int_t i=0; i<syst_hist->GetEntries(); i++ ){
      //for( Int_t i=0; i<4*syst_hist->GetEntries(); i++ ){ // tmppppp
	syst_hist              ->GetRandom2( rnd_x, rnd_y );
	pdf_hist_2d[systpdf_no]->Fill      ( rnd_x, rnd_y );
      }
      TH2D* nosm_hist = new TH2D( *pdf_hist_2d[systpdf_no] );
      nosm_hist->SetName("test");
      nosm_hist->SetTitle("test");
      smooth( pdf_hist_2d[systpdf_no] );
      //if( tag_cnt < 20 ){
      //TFile outfile( Form("pic/testpdf_%d.root", tag_cnt), "RECREATE" ); // test
      //pdf_hist_2d[systpdf_no]->Write();
      //nosm_hist->Write();
      //outfile.Close();
      //}

      delete syst_hist;
      delete nosm_hist;
      //}
    }else if( pdf_dim[systpdf_no]==1 ){ // product of 1-dimentional histogram-PDF

      TH1D* syst_hist_nb   = new TH1D( *pdf_hist_nb  [systpdf_no] );
      TH1D* syst_hist_eecl = new TH1D( *pdf_hist_eecl[systpdf_no] );
      pdf_hist_nb  [systpdf_no]->Reset();
      pdf_hist_eecl[systpdf_no]->Reset();
      for( Int_t i=0; i<syst_hist_nb  ->GetEntries(); i++ ) pdf_hist_nb  [systpdf_no]->Fill( syst_hist_nb  ->GetRandom() );
      //for( Int_t i=0; i<4.0*syst_hist_nb  ->GetEntries(); i++ ) pdf_hist_nb  [systpdf_no]->Fill( syst_hist_nb  ->GetRandom() ); // tmpppp
      for( Int_t i=0; i<syst_hist_eecl->GetEntries(); i++ ) pdf_hist_eecl[systpdf_no]->Fill( syst_hist_eecl->GetRandom() );

      delete syst_hist_nb;
      delete syst_hist_eecl;
    }
      
  }
  */
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooDataHist** pdf_tmp_roohist_2d   = new RooDataHist*[npdf];
  RooDataHist** pdf_tmp_roohist_nb   = new RooDataHist*[npdf];
  RooDataHist** pdf_tmp_roohist_eecl = new RooDataHist*[npdf];
  RooHistPdf**  pdf_roohist_2d       = new RooHistPdf* [npdf];
  RooHistPdf**  pdf_roohist_nb       = new RooHistPdf* [npdf];
  RooHistPdf**  pdf_roohist_eecl     = new RooHistPdf* [npdf];
  RooProdPdf**  pdf_roohist_prod     = new RooProdPdf* [npdf];

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    pdf_tmp_roohist_2d  [ipdf] = new RooDataHist( Form("tmp_hist_2d_%s_lep%d",  pdf_name[ipdf],fl_lep), Form("tmp_hist_2d_%s_lep%d",  pdf_name[ipdf],fl_lep), *varset, pdf_hist_2d  [ipdf] );
    pdf_tmp_roohist_nb  [ipdf] = new RooDataHist( Form("tmp_hist_nb_%s_lep%d",  pdf_name[ipdf],fl_lep), Form("tmp_hist_nb_%s_lep%d",  pdf_name[ipdf],fl_lep), *nb,     pdf_hist_nb  [ipdf] );
    pdf_tmp_roohist_eecl[ipdf] = new RooDataHist( Form("tmp_hist_eecl_%s_lep%d",pdf_name[ipdf],fl_lep), Form("tmp_hist_eecl_%s_lep%d",pdf_name[ipdf],fl_lep), *eecl,   pdf_hist_eecl[ipdf] );
    
    pdf_roohist_2d      [ipdf] = new RooHistPdf( Form( "pdf_2d_%s_lep%d",  pdf_name[ipdf],fl_lep), Form( "pdf_2d_%s_lep%d",  pdf_name[ipdf],fl_lep), *varset, *pdf_tmp_roohist_2d  [ipdf] ); // pdf from 2d-histogram
    pdf_roohist_nb      [ipdf] = new RooHistPdf( Form( "pdf_nb_%s_lep%d",  pdf_name[ipdf],fl_lep), Form( "pdf_nb_%s_lep%d",  pdf_name[ipdf],fl_lep), *nb,     *pdf_tmp_roohist_nb  [ipdf] );
    pdf_roohist_eecl    [ipdf] = new RooHistPdf( Form( "pdf_eecl_%s_lep%d",pdf_name[ipdf],fl_lep), Form( "pdf_eecl_%s_lep%d",pdf_name[ipdf],fl_lep), *eecl,   *pdf_tmp_roohist_eecl[ipdf] );
    pdf_roohist_prod    [ipdf] = new RooProdPdf( Form( "pdf_prod_%s_lep%d",pdf_name[ipdf],fl_lep), Form( "pdf_prod_%s_lep%d",pdf_name[ipdf],fl_lep), RooArgSet(*pdf_roohist_nb[ipdf],*pdf_roohist_eecl[ipdf]) ); // pdf from the product of 1d-histograms

    pdf_roohist_2d  [ipdf]->forceNumInt(kTRUE);
    //pdf_roohist_prod[ipdf]->forceNumInt(kTRUE);
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TOTAL PDF>
  RooRealVar**    yield         = new RooRealVar*   [npdf];
  RooFormulaVar** yield_formula = new RooFormulaVar*[npdf];
  RooRealVar*     fakescale     = new RooRealVar( "fakescale", "fakescale", 1.0, 0.0, 5.0 );
  Double_t        ntotfake      = 0.0;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) ntotfake += init[ipdf];
  }
  
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    yield[ipdf] = new RooRealVar( Form("n%s",pdf_name[ipdf]), Form("N_{%s}",pdf_name[ipdf]), init[ipdf],  -100, ( init[ipdf]< 30 ? 150 : 5.0*init[ipdf]) );
    if( pdf_fix[ipdf]==1 ) yield[ipdf]->setConstant(true);
  }


  // treatment of fake D(*) components

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]!=2 ) continue;
    
    
    Int_t* fake_index = new Int_t[npar_fake];
    Int_t tmp_cnt = 0;
    fake_index[tmp_cnt++] = ipdf;
    for( Int_t ipdf2=0; ipdf2<npdf; ipdf2++ ){
      if( pdf_fix[ipdf2]!=2 ) continue;
      if( ipdf==ipdf2       ) continue;
      fake_index[tmp_cnt++] = ipdf2;
    }
    
    
    
    yield_formula[ipdf] = new RooFormulaVar( Form("n%s",pdf_name[ipdf]),
					     Form("n%s",pdf_name[ipdf]),
					     Form("%f/(@0*%f+@1*%f+@2*%f+@3*%f+@4*%f)*@0*%f",
						  ntotfake*corr_fake_d,
						  init[fake_index[0]]/init[pdf_corr[fake_index[0]]],
						  init[fake_index[1]]/init[pdf_corr[fake_index[1]]],
						  init[fake_index[2]]/init[pdf_corr[fake_index[2]]],
						  init[fake_index[3]]/init[pdf_corr[fake_index[3]]],
						  init[fake_index[4]]/init[pdf_corr[fake_index[4]]],
						  init[ipdf]/init[pdf_corr[ipdf]]),
					     RooArgSet(*yield[pdf_corr[fake_index[0]]],
						       *yield[pdf_corr[fake_index[1]]],
						       *yield[pdf_corr[fake_index[2]]],
						       *yield[pdf_corr[fake_index[3]]],
						       *yield[pdf_corr[fake_index[4]]]
						       )
					     );
    delete[] fake_index;
  }

  
  RooArgList* pdflist   = new RooArgList();
  RooArgList* yieldlist = new RooArgList();
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_dim[ipdf]==0 ) continue;
    if     ( pdf_dim[ipdf]==1 ) pdflist->add( *pdf_roohist_prod[ipdf] );
    else if( pdf_dim[ipdf]==2 ) pdflist->add( *pdf_roohist_2d  [ipdf] );

    if( pdf_fix[ipdf]==2 ) yieldlist->add( *yield_formula[ipdf] );
    else                   yieldlist->add( *yield        [ipdf] );
  }

  RooAddPdf* pdf_tot = new RooAddPdf( "pdf_tot", "pdf_tot", *pdflist, *yieldlist );
  pdf_tot->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <CANVAS for PDF check>
  /*
  TCanvas* can_pdf = Canvas( "can_pdf","can_pdf", npdf, 2 );
  can_pdf->Draw();
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_dim[ipdf]==1 ){
      can_pdf->cd(ipdf     +1); pdf_hist_nb  [ipdf]->Draw();
      can_pdf->cd(ipdf+npdf+1); pdf_hist_eecl[ipdf]->Draw();
    }else{
      can_pdf->cd(ipdf     +1); pdf_hist_2d[ipdf]->ProjectionX( Form("_proj_nb_%d",  ipdf), 1, pdf_hist_2d[ipdf]->GetNbinsY() )->Draw();
      can_pdf->cd(ipdf+npdf+1); pdf_hist_2d[ipdf]->ProjectionY( Form("_proj_eecl_%d",ipdf), 1, pdf_hist_2d[ipdf]->GetNbinsX() )->Draw();
    }
<<  }
  can_pdf->Print( Form("pic/2dfit_%.1f_lep%d_pdf.ps", pdf_nexp[1],fl_lep) );
  */

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <READ Data>
  RooDataSet* data;
  if( fl_stream == -999 ){
    std::cout << "Data Fitting" << std::endl;
    data = new RooDataSet( "data", "data", *varset );
    TChain* c_dt  = new TChain(treename);
    std::cout << "[infile_data] "     << infile_dt  << std::endl;
    std::cout << c_dt->Add(infile_dt) << " files, ";
    std::cout << c_dt->GetEntries()   << " entries"
	      << std::endl;
    sTmp.str("");
    sTmp.clear();
    sTmp << Form("eecl_exp<%f",eecl_xmax);
    sTmp << " && " << selection_common;
    if( fl_lep ) sTmp << Form(" && ( (cosdll==cosdl1 && rm_l1==%d) || (cosdll==cosdl2 && rm_l2==%d) )",fl_lep,fl_lep);
    TTree* c_dt_cut  = c_dt ->CopyTree( Form("(%s)", sTmp.str().c_str()) );
    std::cout << "[dt_cut] " << c_dt_cut ->GetEntries() << " events" << std::endl;
    
    for( Int_t ievt=0; ievt<c_dt_cut->GetEntries(); ievt++ ){
      c_dt_cut->GetEntry(ievt);
      eecl->setVal( c_dt_cut->GetLeaf("eecl_exp" )->GetValue() );
      nb  ->setVal( c_dt_cut->GetLeaf(  nb_brname)->GetValue() );
      data->add( *varset );
    }
    data->Print();
    data->Print("v");
    delete c_dt;
    
  }else if( fl_stream < 0 ){
    std::cout << "Single toy mc sample is generated : " << init_tot << " events" << std::endl;
    // <toy mc sample>
    data = pdf_tot->generate( *varset, init_tot ); // Extended(true)
    data->Print();
  }else{
    // <ensemble test>
    std::cout << "ensemble test start with stream No." << fl_stream << std::endl;
    data = new RooDataSet( "data", "ensemble test", *varsetw, WeightVar("w") );
    TChain* c_gmc_1st  = new TChain(treename);
    TChain* c_dststmc  = new TChain(treename);
    TChain* c_npmc_1st = new TChain(treename);
    std::cout << "[infile_gmc_1st] " << Form(infile_gmc_1st,fl_stream)  << std::endl;
    std::cout << c_gmc_1st->Add(        Form(infile_gmc_1st,fl_stream)) << " files, ";
    std::cout << c_gmc_1st->GetEntries()                                << " entries"
	      << std::endl;
    std::cout << "[infile_dststmc] " << infile_dststmc << std::endl;
    std::cout << c_dststmc->Add(infile_dststmc)        << " files, ";
    std::cout << c_dststmc->GetEntries()               << " entries, ";
    std::cout << nstream_dststmc                       << " streams" << std::endl;
    std::cout << "[infile_npmc_1st] " << Form(infile_npmc_1st,"0p0",fl_stream)  << " : " << fl_par_dt << std::endl;
    std::cout << c_npmc_1st->Add(        Form(infile_npmc_1st,"0p0",fl_stream)) << " files, ";
    std::cout << c_npmc_1st->GetEntries()                                       << " entries, "
	      << std::endl;
    
    sTmp.str("");
    sTmp.clear();
    sTmp << Form("eecl<%f",eecl_xmax);
    sTmp << " && " << selection_common;
    sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
    sTmp << " && " << makeCut_npmc   ( fl_use_npmc    ).c_str();
    if( fl_lep ) sTmp << Form(" && ( (cosdll==cosdl1 && rm_l1==%d) || (cosdll==cosdl2 && rm_l2==%d) )",fl_lep,fl_lep);
    TTree* c_gmc_1st_cut  = c_gmc_1st ->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),selection_common_mc) );
    TTree* c_dststmc_cut  = c_dststmc ->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),selection_common_mc) );
    TTree* c_npmc_1st_cut = c_npmc_1st->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),selection_common_mc) );
    std::cout << "[ gmc_1st_cut] " << c_gmc_1st_cut ->GetEntries() << " events" << std::endl;
    std::cout << "[ dststmc_cut] " << c_dststmc_cut ->GetEntries() << " events" << std::endl;
    std::cout << "[npmc_1st_cut] " << c_npmc_1st_cut->GetEntries() << " events" << std::endl;
    
    for( Int_t ievt=0; ievt<c_gmc_1st_cut->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_gmc_1st_cut, ievt, 1.0 );
      if( fl_2sveto &&
	  ( c_gmc_1st_cut->GetLeaf("ctgrsyst")->GetValue()==7 ||
	    c_gmc_1st_cut->GetLeaf("ctgrsyst")->GetValue()==8 )
	  ) weight = 0;
      eecl->setVal( c_gmc_1st_cut->GetLeaf(eecl_brname)->GetValue() );
      nb  ->setVal( c_gmc_1st_cut->GetLeaf(  nb_brname)->GetValue() );
      data->add( *varset, weight );
    }
    data->Print();

    gRandom->SetSeed( seed_dstst );
    for( Int_t ievt=0; ievt<c_dststmc_cut->GetEntries(); ievt++ ){
      if( gRandom->Rndm() > 1/nstream_dststmc ) continue; // D** MC samples is scaled to 1 stream using "gRandom->Rndm", which is uniform distribution between 0 and 1
      Double_t weight = cal_weight( c_dststmc_cut, ievt, 1.0 );
      if( fl_2sveto &&
	  ( c_dststmc_cut->GetLeaf("ctgrsyst")->GetValue()==7 ||
	    c_dststmc_cut->GetLeaf("ctgrsyst")->GetValue()==8 )
	  ) weight = 0;
      eecl->setVal( c_dststmc_cut->GetLeaf(eecl_brname)->GetValue() );
      nb  ->setVal( c_dststmc_cut->GetLeaf(  nb_brname)->GetValue() );
      data->add( *varset, weight );
    }

    data->Print();

    for( Int_t ievt=0; ievt<c_npmc_1st_cut->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_npmc_1st_cut, ievt, 1.0 );
      if( fl_2sveto &&
	  ( c_npmc_1st_cut->GetLeaf("ctgrsyst")->GetValue()==7 ||
	    c_npmc_1st_cut->GetLeaf("ctgrsyst")->GetValue()==8 )
	  ) weight = 0;
      Double_t val[np::nvar];
      for( Int_t ivar=0; ivar<np::nvar; ivar++ ) val[ivar] = c_npmc_1st_cut->GetLeaf(np::brname[ivar])->GetValue(); // reproduce NP distribution by re-weighted SM distribution
      Int_t gindex = getGIndex( val );
      Double_t npweight  = npweight_table->GetY()[gindex];
      Double_t npweightE = npweight_table->GetErrorY(gindex);
      weight *= npweight; // NP weight
      eecl->setVal( c_npmc_1st_cut->GetLeaf(eecl_brname)->GetValue() );
      nb  ->setVal( c_npmc_1st_cut->GetLeaf(  nb_brname)->GetValue() );
      data->add( *varset, weight );
    }
    data->Print();
    
    data->Print("v");

    delete c_gmc_1st;
    delete c_gmc_1st_cut;
    delete c_dststmc;
    delete c_dststmc_cut;
    delete c_npmc_1st;
    delete c_npmc_1st_cut;
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <CANVAS for ensemble test>
  TCanvas* can_fit = Canvas( "can_fit","can_fit", 3, 2 );
  can_fit->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <FIT>
  std::cout << "*************************** Fit is started "
	    << "***************************" << std::endl;
  //yield[1]->setVal(0.0); // tmpppp
  //yield[1]->setVal(230.924); // tmpppp
  //yield[1]->setConstant(true); // tmppp
  RooFitResult* fit_result = pdf_tot->fitTo( *data, Save(true), SumW2Error(roosumw2), Minos(true), Extended(true) );
  fit_result->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can_fit->cd(1);
  RooPlot* frame_fit_nb = nb->frame();
  frame_fit_nb->SetTitle( "NB" );

  /*
  data   ->plotOn( frame_fit_nb, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2) ); // total-pdf

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) continue;
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_nb, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_nb, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
  }
  */
  ///* stacked-style
  data   ->plotOn( frame_fit_nb, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 2), DrawOption("F"), Components(*pdflist) ); // signal
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 3), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor(11), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3])) ); // D**
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 9), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 7), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 4), DrawOption("F"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_nb, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/
  frame_fit_nb->Draw();
  
  //+++++++++++++++++++++++++++++
  can_fit->cd(2);
  RooPlot* frame_fit_nb_sig_enh = nb->frame();
  frame_fit_nb_sig_enh->SetTitle( "NB with signal E_{ECL} region" );
  /*
  data   ->plotOn( frame_fit_nb_sig_enh, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("signal_box_eecl") ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2), ProjectionRange("signal_box_eecl") ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) continue;
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_nb_sig_enh, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_eecl") ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_nb_sig_enh, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_eecl") ); // each-pdf
  }
  */
  ///* stacked-style
  data   ->plotOn( frame_fit_nb_sig_enh, Binning(nb_xbin), CutRange("signal_box_eecl"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 2), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(*pdflist) ); // signal
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 3), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor(11), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3])) ); // D**
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 4), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_nb_sig_enh, Binning(nb_xbin), CutRange("signal_box_eecl"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/
  frame_fit_nb_sig_enh->Draw();

  //+++++++++++++++++++++++++++++
  can_fit->cd(3);
  can_fit->cd(3)->SetLogy();
  RooPlot* frame_fit_nb_sig_enh_log = nb->frame();
  frame_fit_nb_sig_enh_log->SetTitle( "NB" );
  /*
  data   ->plotOn( frame_fit_nb_sig_enh_log, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2) ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) continue;
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_nb_sig_enh_log, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_nb_sig_enh_log, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
  }
  */
  ///* stacked-style
  data   ->plotOn( frame_fit_nb_sig_enh_log, Binning(nb_xbin), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 2), DrawOption("F"), Components(*pdflist) ); // signal
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 3), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor(11), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3])) ); // D**
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 9), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 7), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 4), DrawOption("F"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_nb_sig_enh_log, Binning(nb_xbin), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/
  if( fl_lep==0 ){
    frame_fit_nb_sig_enh_log->SetMaximum( 4000 ); // for paper plot // tmppppp
    frame_fit_nb_sig_enh_log->SetMinimum(  0.8 ); // for paper plot // tmppppp
  }else if( fl_lep==10 ){
    frame_fit_nb_sig_enh_log->SetMaximum( 2000 ); // for paper plot // tmppppp
    frame_fit_nb_sig_enh_log->SetMinimum(  0.5 ); // for paper plot // tmppppp
  }else if( fl_lep==1 ){
    frame_fit_nb_sig_enh_log->SetMaximum( 2000 ); // for paper plot // tmppppp
    frame_fit_nb_sig_enh_log->SetMinimum(  0.3 ); // for paper plot // tmppppp
  }
  frame_fit_nb_sig_enh_log->Draw();

  //+++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++
  can_fit->cd(4);
  RooPlot* frame_fit_eecl = eecl->frame();
  frame_fit_eecl->SetTitle( "E_{ECL}" );
  /*
  data   ->plotOn ( frame_fit_eecl, Binning(eecl_xbin),   MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn ( frame_fit_eecl, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2) ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) continue;
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_eecl, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_eecl, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
  }
  */

  ///* stacked-style
  data   ->plotOn( frame_fit_eecl, Binning(eecl_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 2), DrawOption("F"), Components(*pdflist) ); // signal
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 3), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor(11), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3])) ); // D**
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 9), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 7), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 4), DrawOption("F"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_eecl, Binning(eecl_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/
  
  //pdf_tot->paramOn( frame_fit_eecl, Format("NELU", AutoPrecision(2)), Layout(0.40, 0.99, 0.99), ShowConstants(true) );
  pdf_tot->paramOn( frame_fit_eecl, Format("NELU", AutoPrecision(2)), Layout(0.40, 0.99, 0.99) );
  frame_fit_eecl->Draw();

  //+++++++++++++++++++++++++++++
  can_fit->cd(5);
  RooPlot* frame_fit_eecl_sig_enh = eecl->frame();
  frame_fit_eecl_sig_enh->SetTitle( "E_{ECL} with signal NB region" );
  /*
  data   ->plotOn( frame_fit_eecl_sig_enh, Binning(eecl_xbin),   MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("signal_box_nb") ); // data
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2), ProjectionRange("signal_box_nb") ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) continue;
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_eecl_sig_enh, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_nb") ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_eecl_sig_enh, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_nb") ); // each-pdf
  }
  */

  ///* stacked-style
  data   ->plotOn( frame_fit_eecl_sig_enh, Binning(eecl_xbin), CutRange("signal_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 2), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(*pdflist) ); // signal
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 3), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor(11), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3])) ); // D**
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 4), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_eecl_sig_enh, Binning(eecl_xbin), CutRange("signal_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/

  frame_fit_eecl_sig_enh->Draw();

  //+++++++++++++++++++++++++++++
  can_fit->cd(6);
  RooPlot* frame_fit_eecl_nor_enh = eecl->frame();
  frame_fit_eecl_nor_enh->SetTitle( "E_{ECL} with norm NB region" );
  /*
  data   ->plotOn( frame_fit_eecl_nor_enh, Binning(eecl_xbin),   MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("norm_box_nb") ); // data
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2), ProjectionRange("norm_box_nb") ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) continue;
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_eecl_nor_enh, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("norm_box_nb") ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_eecl_nor_enh, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("norm_box_nb") ); // each-pdf
  }
  */
  ///* stacked-style
  data   ->plotOn( frame_fit_eecl_nor_enh, Binning(eecl_xbin), CutRange("norm_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 2), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(*pdflist) ); // signal
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 3), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor(11), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3])) ); // D**
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 4), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_eecl_nor_enh, Binning(eecl_xbin), CutRange("norm_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/
  
  frame_fit_eecl_nor_enh->Draw();
  if     ( fl_stream==-999 ) can_fit->Print( Form("pic/2dfit_%.1f_lep%d_fit.eps",            pdf_nexp[1],fl_lep          ) );
  else if( fl_toymc        ) can_fit->Print( Form("pic/2dfit_%.1f_lep%d_fit.ps",             pdf_nexp[1],fl_lep          ) );
  else if( tag_cnt==0      ) can_fit->Print( Form("pic/2dfit_%.1f_lep%d_streamno_%d_fit.ps", pdf_nexp[1],fl_lep,fl_stream) );
  std::cout << "[Result of ensemble fit]" << std::endl
	    << "==========================================================================================================================================================================" << std::endl
	    << std::setw( 5) << std::right << "no"
	    << std::setw( 7) << std::right << "tag_cnt"
	    << std::setw(15) << std::right << "R(D*)"
	    << std::setw(15) << std::right << "(error)"
	    << std::setw(15) << std::right << "Nsig"
	    << std::setw(15) << std::right << "(error)"
	    << std::setw(15) << std::right << "Nnor"
	    << std::setw(15) << std::right << "(error)"
	    << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
  std::cout << std::setw( 5) << std::right << fl_stream
	    << std::setw( 7) << std::right << tag_cnt
	    << std::setw(15) << std::right << convert_factor_rdstr[lep_index[fl_lep]] * yield[1]->getVal()/yield[2]->getVal()
    //<< std::setw(15) << std::right << convert_factor_rdstr[lep_index[fl_lep]] * yield[1]->getVal()/yield[2]->getVal() * sqrt( pow(yield[1]->getError()/yield[1]->getVal(),2) +
    //pow(yield[2]->getError()/yield[2]->getVal(),2)
    //)
	    << std::setw(15) << std::right << convert_factor_rdstr[lep_index[fl_lep]] * yield[1]->getVal()/yield[2]->getVal() * sqrt(
																     pow(yield[1]->getError()/yield[1]->getVal(),2) +
																     pow(yield[2]->getError()/yield[2]->getVal(),2) -
																     2.0*fit_result->correlationMatrix()(1,2)* // correation term
																     yield[1]->getError()/yield[1]->getVal()*  // correation term
																     yield[2]->getError()/yield[2]->getVal()   // correation term
														   )
	    << std::setw(15) << std::right << yield[1]->getVal()
	    << std::setw(15) << std::right << yield[1]->getError()
	    << std::setw(15) << std::right << yield[2]->getVal()
	    << std::setw(15) << std::right << yield[2]->getError();
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( ipdf==1 || ipdf==2 || pdf_fix[ipdf] ) continue;
    std::cout << std::setw(15) << std::right << yield[ipdf]->getVal()
	      << std::setw(15) << std::right << yield[ipdf]->getError();
  }
  std::cout << " HIGEEEEE "
	    << "lep" << fl_lep << "lep"
	    << std::endl;
  std::cout << "==========================================================================================================================================================================" << std::endl;
  
  std::cout << std::setw(15) << std::right << yield[1]->getVal()
	    << std::setw(15) << std::right << fit_result->minNll()
	    << Form( "   STATSIGNIFICANCE_lep%d", fl_lep )
	    << std::endl     << std::endl;

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) std::cout << std::setw(15) << std::right << yield_formula[ipdf]->getVal() << std::endl;
    else                   std::cout << std::setw(15) << std::right << yield[ipdf]->getVal()
				     << std::setw(15) << std::right << yield[ipdf]->getError() << std::endl;
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( !fl_toymc ){
    /*
    if( fl_stream == -999 ){
      // +++++++++++++++++++++++++ Likelihood Scan for simultaneous fitting+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      RooAbsReal* nll  = pdf_tot->createNLL( *data ); // plain likelihood
      RooAbsReal* pnll = nll->createProfile( *yield[1] ) ; // profile likelihood (all floating parameters except signal yields)
      TCanvas* can_scan = Canvas( "can_scan","can_scan", 2, 1 );
      can_scan->Draw();

      RooPlot* frame_scan1 = yield[1]->frame( Bins(50), Range(yield[1]->getVal()-3.0*yield[1]->getError(), yield[1]->getVal()+3.0*yield[1]->getError()), Title("profile") );
      nll ->plotOn( frame_scan1, LineColor(kBlue), ShiftToZero() );
      pnll->plotOn( frame_scan1, LineColor(kRed) );
      frame_scan1->GetXaxis()->CenterTitle();
      frame_scan1->GetYaxis()->CenterTitle();
      frame_scan1->SetTitleOffset( 1.00, "x" );
      frame_scan1->SetTitleOffset( 1.30, "y" );
      frame_scan1->SetTitle( "Likelihood Scan" );
      frame_scan1->SetMinimum(0);
      frame_scan1->SetMaximum(10);

      can_scan->cd(1);
      can_scan->cd(1)->SetGridx();
      can_scan->cd(1)->SetGridy();
      frame_scan1->Draw();

      RooPlot* frame_scan2 = yield[1]->frame( Bins(50), Range(0.0, yield[1]->getVal()+3.0*yield[1]->getError()), Title("profile") );
      nll ->plotOn( frame_scan2, LineColor(kBlue), ShiftToZero() );
      pnll->plotOn( frame_scan2, LineColor(kRed) );
      frame_scan2->GetXaxis()->CenterTitle();
      frame_scan2->GetYaxis()->CenterTitle();
      frame_scan2->SetTitleOffset( 1.00, "x" );
      frame_scan2->SetTitleOffset( 1.30, "y" );
      frame_scan2->SetTitle( "Likelihood Scan" );
      frame_scan2->SetMinimum(0);
      frame_scan2->SetMaximum(150);

      can_scan->cd(2);
      can_scan->cd(2)->SetGridx();
      can_scan->cd(2)->SetGridy();
      frame_scan2->Draw();
      can_scan->Print( Form("pic/2dfit_%.1f_lep%d_fit_scan.eps", pdf_nexp[1],fl_lep) );
    }
    */
    std::cout << "finish" << std::endl;
    if( !gROOT->IsBatch() ) app.Run();
    return 0;
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Iterative TOY MC
  std::cout << "*************************** Iterative TOY MC is started : " << iteration << " iterations "
	    << "***************************" << std::endl;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) yield[ipdf]->setVal( init[ipdf] );
  
  RooMCStudy* mcstudy = new RooMCStudy( *pdf_tot, *varset, Binned(true), Silence(true), Extended(true), FitOptions(Save(true),PrintEvalErrors(0),SumW2Error(roosumw2),Minos(true)) );
  mcstudy->generateAndFit( iteration );

  //for( Int_t i=0; i<iteration; i++ ) mcstudy->fitResult(i)->Print();


  TCanvas* can_toy2 = Canvas( "can_toy2","can_toy2", npar, 3 );
  TH1D** pullhist  = new TH1D*[npdf];
  TH1D** yieldhist = new TH1D*[npdf];
  TH1D** errorhist = new TH1D*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) pullhist [ipdf] = new TH1D( Form("%spull", pdf_name[ipdf]), Form("%spull", pdf_name[ipdf]), 40, -4, 4 );
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) yieldhist[ipdf] = new TH1D( Form("%syield",pdf_name[ipdf]), Form("%syield",pdf_name[ipdf]), 40, 0.5*init[ipdf], 1.5*init[ipdf] );
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ) errorhist[ipdf] = new TH1D( Form("%serror",pdf_name[ipdf]), Form("%serror",pdf_name[ipdf]), 100, 0, 0 );
  mcstudy->fitParDataSet().Print();
  for( Int_t i=0; i<mcstudy->fitParDataSet().numEntries(); i++ ){
    for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
      pullhist [ipdf]->Fill( mcstudy->fitParDataSet().get(i)->getRealValue( Form("n%spull",pdf_name[ipdf])) );
      yieldhist[ipdf]->Fill( mcstudy->fitParDataSet().get(i)->getRealValue( Form("n%s",    pdf_name[ipdf])) );
      errorhist[ipdf]->Fill( mcstudy->fitParDataSet().get(i)->getRealValue( Form("n%serr", pdf_name[ipdf])) );
    }
  }

  can_toy2->cd(1);
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    pullhist[ipdf]->Fit("gaus","L");    
    yieldhist[ipdf]->Fit("gaus","L");
    errorhist[ipdf]->Fit("gaus","L");
  }
  tmp_cnt = 1;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( !(pdf_dim[ipdf] && pdf_fix[ipdf]==!true) ) continue;
    can_toy2->cd(tmp_cnt++);
    pullhist[ipdf]->Draw();
  }
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( !(pdf_dim[ipdf] && pdf_fix[ipdf]==!true) ) continue;
    can_toy2->cd(tmp_cnt++);
    yieldhist[ipdf]->Draw();

  }
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( !(pdf_dim[ipdf] && pdf_fix[ipdf]==!true) ) continue;
    can_toy2->cd(tmp_cnt++);
    errorhist[ipdf]->Draw();
  }
  can_toy2->Print( Form("pic/2dfit_%.1f_lep%d_toy2.ps", pdf_nexp[1],fl_lep) );

  std::cout << "[Result of toy mc study]" << std::endl
	    << "==========================================================================================================================================================================" << std::endl
	    << std::setw( 3) << std::right << "PDF"
	    << std::setw(13) << std::right << "Nsig"
	    << std::setw(13) << std::right << "Nexp"
	    << std::setw(13) << std::right << "Nmeas"
	    << std::setw(13) << std::right << "(error)"
	    << std::setw(13) << std::right << "Nerr"
	    << std::setw(13) << std::right << "(error)"
	    << std::setw(13) << std::right << "pull mean"
	    << std::setw(13) << std::right << "(error)"
	    << std::setw(13) << std::right << "pull width"
	    << std::setw(13) << std::right << "(error)"
	    << std::endl;
  std::cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << std::endl;
	    
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    std::cout << std::setw( 3) << std::right << ipdf
	      << std::setw(13) << std::right << init[1]
	      << std::setw(13) << std::right << init[ipdf]
	      << std::setw(13) << std::right << yieldhist[ipdf]->GetFunction("gaus")->GetParameter(1)
	      << std::setw(13) << std::right << yieldhist[ipdf]->GetFunction("gaus")->GetParError (1)
	      << std::setw(13) << std::right << errorhist[ipdf]->GetFunction("gaus")->GetParameter(1)
	      << std::setw(13) << std::right << errorhist[ipdf]->GetFunction("gaus")->GetParError (1)
	      << std::setw(13) << std::right << pullhist [ipdf]->GetFunction("gaus")->GetParameter(1) // 0(norm), 1(mean), 2(sigma)
	      << std::setw(13) << std::right << pullhist [ipdf]->GetFunction("gaus")->GetParError (1)
	      << std::setw(13) << std::right << pullhist [ipdf]->GetFunction("gaus")->GetParameter(2)
	      << std::setw(13) << std::right << pullhist [ipdf]->GetFunction("gaus")->GetParError (2)
	      << " HOGEEEE "
	      << pdf_name[ipdf]
	      << std::endl;
  }
  std::cout << "==========================================================================================================================================================================" << std::endl;
  std::cout << std::setw(13) << std::right << init[1]
	    << std::setw(13) << std::right << sqrt(
						   pow( errorhist[1]->GetFunction("gaus")->GetParameter(1)/yieldhist[1]->GetFunction("gaus")->GetParameter(1),2) +
						   pow( errorhist[2]->GetFunction("gaus")->GetParameter(1)/yieldhist[2]->GetFunction("gaus")->GetParameter(1),2)
						   )
	    << " HUGEEEEE"
	    << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <CANVAS>
  TCanvas* can_toymc = Canvas( "can_toymc","can_toymc", 3, npar );
  can_toymc->Draw();

  RooPlot** frame_toy_mean = new RooPlot*[npdf];
  RooPlot** frame_toy_err  = new RooPlot*[npdf];
  RooPlot** frame_toy_pull = new RooPlot*[npdf];
  tmp_cnt = 1;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( !(pdf_dim[ipdf] && pdf_fix[ipdf]==!true) ) continue;
    frame_toy_mean[ipdf] = mcstudy->plotParam( *yield[ipdf], Bins(40) );
    frame_toy_err [ipdf] = mcstudy->plotError( *yield[ipdf], Bins(40) );
    frame_toy_pull[ipdf] = mcstudy->plotPull ( *yield[ipdf], Bins(40), FitGauss(true) );    
    can_toymc->cd(tmp_cnt++); frame_toy_mean[ipdf]->Draw();
    can_toymc->cd(tmp_cnt++); frame_toy_err [ipdf]->Draw();
    can_toymc->cd(tmp_cnt++); frame_toy_pull[ipdf]->Draw();
  }

  can_toymc->Print( Form("pic/2dfit_%.1f_lep%d_toy.ps", pdf_nexp[1],fl_lep) );
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
