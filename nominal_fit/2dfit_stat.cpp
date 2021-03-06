#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//const Double_t corr_fake_d         = 1.0;
//const Double_t corr_corr_d         = 1.0;
const Double_t corr_fake_d         =  629/ 544.0; // for data // tmppppp
//const Double_t corr_fake_d         =  629/ 544.0 * (1.00+0.06); // for data // tmppppp // syststudy
const Double_t corr_corr_d         = 3584/3656.0; // for data // tmppppp
const Char_t*  selection_common_mc = "1";
const Char_t*  selection_common    = "1";
//const Char_t*  selection_common    = "eecl<0.5 && nb_mode0_test13_nor < 0.8";


const Bool_t fl_2sveto = true; // veto D(2S) and D*(2S)

const Char_t* pdf_dir             = "pdf/";
//const Char_t* pdf_dir_syst        = "pdf_syst0/";
const Char_t* pdf_dir_syst        = "pdf_syst1/";

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
//const Char_t* fl_par_pdf = "1p0"; // for PDF // tmpppp
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
const Char_t*  fl_par_dt       = "0p0"; // for samples
//const Char_t*  fl_par_dt       = "1p0"; // for samples // tmpppppp
const Char_t*  weight_table    = "../npmc/table/dstrtaunu_dpi_lep_12_all/est_weight.root";
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
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( !(app.Argc()==4 || app.Argc()==5 ) )
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
  std::cout << "fl_par_pdf = " << fl_par_pdf << std::endl
	    << "fl_par_dt  = " << fl_par_dt  << std::endl;

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

  //Double_t init_l [npdf] = {65.2115, 190.19,   2686.91, 351.731,120.933,  77.636, 19.223,   242.107, 135.362,  59.0079 }; // veto D(*)(2S) // sigMC(10 streams)
  //Double_t init_e [npdf] = {28.6944, 117.972,  1417.35, 195.026, 69.5735, 46.113, 13.1857,  131.051,  80.0091, 37.982  }; // veto D(*)(2S) // sigMC(10 streams)
  //Double_t init_mu[npdf] = {36.5171,  72.2178, 1269.56, 156.705, 51.3592, 31.523,  6.03732, 111.056,  55.3528, 21.0259 }; // veto D(*)(2S) // sigMC(10 streams)

  Double_t init_l [npdf] = {65.609,  186.799,  2686.85, 351.743,121.019,  77.9054,19.2501,  242.107, 135.362,  59.3656 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p0)
  Double_t init_e [npdf] = {29.1262, 116.126,  1417.29, 195.038, 69.362,  46.2029,11.7958,  131.051,  80.0091, 38.2505 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p0)
  Double_t init_mu[npdf] = {36.4828,  70.6731, 1269.56, 156.705, 51.6572, 31.7025, 7.45437, 111.056,  55.3528, 21.1151 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p0)

  //Double_t init_l [npdf] = {65.6184, 187.679,  2686.85, 351.742,121.032,  77.9085,19.3919,  242.107, 135.362,  59.3792 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p1)
  //Double_t init_e [npdf] = {29.1275, 116.537,  1417.29, 195.037, 69.3566, 46.2046,11.8784,  131.051,  80.0091, 38.2604 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p1)
  //Double_t init_mu[npdf] = {36.4909,  71.1428, 1269.56, 156.705, 51.6753, 31.7038, 7.51352, 111.056,  55.3528, 21.1189 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p1)

  //Double_t init_l [npdf] = {65.6198, 187.127,  2686.85, 351.737,121.021,  77.9312,19.2933,  242.107, 135.362,  59.3715 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p2)
  //Double_t init_e [npdf] = {29.1264, 116.124,  1417.29, 195.032, 69.3628, 46.2208,11.7884,  131.051,  80.0091, 38.2583 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p2)
  //Double_t init_mu[npdf] = {36.4934,  71.0028, 1269.56, 156.705, 51.6585, 31.7104, 7.50496, 111.056,  55.3528, 21.1132 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p2)

  //Double_t init_l [npdf] = {65.6295, 186.859,  2686.85, 351.734,121.013,  77.9151,19.3036,  242.107, 135.362,  59.3793 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p3)
  //Double_t init_e [npdf] = {29.1358, 115.991,  1417.29, 195.029, 69.3408, 46.2022,11.7714,  131.051,  80.0091, 38.2634 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p3)
  //Double_t init_mu[npdf] = {36.4937,  70.8679, 1269.56, 156.705, 51.6722, 31.7129, 7.53227, 111.056,  55.3528, 21.1159 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p3)
  
  //Double_t init_l [npdf] = {65.654,  186.252,  2686.85, 351.724,121.03,   77.9023,19.2643,  242.107, 135.362,  59.3945 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p4)
  //Double_t init_e [npdf] = {29.1401, 115.642,  1417.29, 195.019, 69.3397, 46.2133,11.7031,  131.051,  80.0091, 38.2278 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p4)
  //Double_t init_mu[npdf] = {36.5139,  70.6101, 1269.56, 156.705, 51.6907, 31.6891, 7.56127, 111.056,  55.3528, 21.1166 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p4)

  //Double_t init_l [npdf] = {65.676,  184.823,  2686.85, 351.72,  121.037, 77.8935,19.1944,  242.107, 135.362,  59.4201 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p5)
  //Double_t init_e [npdf] = {29.1546, 114.725,  1417.29, 195.014, 69.3283, 46.2083,11.6711,  131.051,  80.0091, 38.3143 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p5)
  //Double_t init_mu[npdf] = {36.5214,  70.0985, 1269.56, 156.705, 51.7087, 31.6846, 7.52334, 111.056,  55.3528, 21.1059 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p5)

  //Double_t init_l [npdf] = {65.6593,  182.94,  2686.85, 351.716,121.06,   77.8734,19.3245,  242.107, 135.362,  59.4539 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p6)
  //Double_t init_e [npdf] = {29.156,  113.829,  1417.29, 195.011, 69.3345, 46.1956,11.838,   131.051,  80.0091, 38.3492 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p6)
  //Double_t init_mu[npdf] = {36.5033,  69.1102, 1269.56, 156.705, 51.7258, 31.6778, 7.48643, 111.056,  55.3528, 21.1048 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p6)

  //Double_t init_l [npdf] = {65.6576, 180.915,  2686.86, 351.72, 121.117,  77.8319,19.2892,  242.107, 135.362,  59.4594 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p7)
  //Double_t init_e [npdf] = {29.1678  113.005,  1417.3,  195.014, 69.3306, 46.1817,11.9141,  131.051,  80.0091, 38.3742 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p7)
  //Double_t init_mu[npdf] = {36.4898,  67.9108, 1269.56, 156.705, 51.7862, 31.6502, 7.37509, 111.056,  55.3528, 21.10852}; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p7)

  //Double_t init_l [npdf] = {65.6172, 178.61,   2686.87, 351.724,121.137,  77.7714,19.3968,  242.107, 135.362,  59.4816 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p8)
  //Double_t init_e [npdf] = {29.1534  112.053,  1417.31, 195.019, 69.3456, 46.1322,12.1084,  131.051,  80.0091, 38.4103 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p8)
  //Double_t init_mu[npdf] = {36.4637,  66.5577, 1269.56, 156.705, 51.7914, 31.6392, 7.2884,  111.056,  55.3528, 21.0713 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p8)

  //Double_t init_l [npdf] = {65.5637, 177.536,  2686.87, 351.739,121.188,  77.7296,19.4439,  242.107, 135.362,  59.4823 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p9)
  //Double_t init_e [npdf] = {29.1223  111.737,  1417.31, 195.034, 69.367,  46.1062,12.2322,  131.051,  80.0091, 38.4237 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p9)
  //Double_t init_mu[npdf] = {36.4413,  65.7992, 1269.56, 156.705, 51.8208, 31.6234, 7.21168, 111.056,  55.3528, 21.0586 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(0p9)

  //Double_t init_l [npdf] = {65.5442, 176.75,   2686.88, 351.745,121.198,  77.7355,19.4611,  242.107, 135.362,  59.4763 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(1p0)
  //Double_t init_e [npdf] = {29.1242  111.614,  1417.32, 195.04,  69.3725, 46.1133,12.3739,  131.051,  80.0091, 38.4293 }; // veto D(*)(2S) // sigMC(40 streams) // npmc(1p0)
  //Double_t init_mu[npdf] = {36.42,    65.1362, 1269.56, 156.705, 51.8252, 31.6222, 7.08722, 111.056,  55.3528, 21.047  }; // veto D(*)(2S) // sigMC(40 streams) // npmc(1p0)
  
  //Double_t init_l [npdf] = {65.609,  186.799,  2686.85, 351.743,121.019 *(1.00+2*0.029), 77.9054,19.2501,  242.107, 135.362,  59.3656 }; // veto D(*)(2S) // sigMC(40 streams) for syststudy (DD)
  //Double_t init_e [npdf] = {29.1262, 116.126,  1417.29, 195.038, 69.362 *(1.00+2*0.029), 46.2029,11.7958,  131.051,  80.0091, 38.2505 }; // veto D(*)(2S) // sigMC(40 streams) for syststudy (DD)
  //Double_t init_mu[npdf] = {36.4828,  70.6731, 1269.56, 156.705, 51.6572*(1.00+2*0.029), 31.7025, 7.45437, 111.056,  55.3528, 21.1151 }; // veto D(*)(2S) // sigMC(40 streams) for syststudy (DD)
  
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
    Int_t systpdf_no = 9; // 2(nor), 3(D**), 5-9(fakeD*) // set pdf_dir_syst = "pdf_syst1"
    //Int_t systpdf_no = 2; // 2(nor), 3(D**), 4(DD)       // set pdf_dir_syst = "pdf_syst0"
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
  RooRealVar**    yield_org     = new RooRealVar*   [npdf];
  RooRealVar**    yield_sub     = new RooRealVar*   [npdf];
  RooFormulaVar** yield_formula = new RooFormulaVar*[npdf];
  RooRealVar*     fakescale     = new RooRealVar( "fakescale", "fakescale", 1.0, 0.0, 5.0 );
  Double_t        ntotfake      = 0.0;
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) ntotfake += init[ipdf];
  }
  
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    yield_org[ipdf] = new RooRealVar( Form("norg%s",pdf_name[ipdf]), Form("N_{%s}",   pdf_name[ipdf]), init[ipdf],  -100, ( init[ipdf]< 30 ? 150 : 5.0*init[ipdf]) );

    if     ( ipdf==1 ) yield_sub[ipdf] = new RooRealVar( "rdstr",                      "R(D*)",          0.25,            0.0,         1.0         );
    else if( ipdf==2 ) yield_sub[ipdf] = new RooRealVar( "nsignor",                    "N_{sig+norm}",   init[1]+init[2], 0.5*init[2], 1.5*init[2] );
    else               yield_sub[ipdf] = new RooRealVar( Form("nsub%s",pdf_name[ipdf]), Form("Nsub_{%s}",pdf_name[ipdf]), 1.0                                       );
    if( pdf_fix[ipdf]==1 ) yield_org[ipdf]->setConstant(true);
  }


  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]!=2 ){ // except fake D(*) components

      if(      ipdf==1 ) yield_formula[ipdf] = new RooFormulaVar( Form("n%s",pdf_name[ipdf]), Form("n%s",pdf_name[ipdf]), Form("@0/(1.0+%f/@1)",convert_factor_rdstr[lep_index[fl_lep]]), RooArgSet(*yield_sub[2],*yield_sub[1]) );
      else if( ipdf==2 ) yield_formula[ipdf] = new RooFormulaVar( Form("n%s",pdf_name[ipdf]), Form("n%s",pdf_name[ipdf]), Form("@0/(1.0+@1/%f)",convert_factor_rdstr[lep_index[fl_lep]]), RooArgSet(*yield_sub[2],*yield_sub[1]) );
      else{
	yield_sub[ipdf]->setConstant(true);
	yield_formula[ipdf] = new RooFormulaVar( Form("n%s",pdf_name[ipdf]),
						 Form("n%s",pdf_name[ipdf]),
						 "@0*@1", RooArgSet(*yield_sub[ipdf],*yield_org[ipdf]) );
      }
    }else{ // treatment of fake D(*) components
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
					       RooArgSet(*yield_formula[pdf_corr[fake_index[0]]],
							 *yield_formula[pdf_corr[fake_index[1]]],
							 *yield_formula[pdf_corr[fake_index[2]]],
							 *yield_formula[pdf_corr[fake_index[3]]],
							 *yield_formula[pdf_corr[fake_index[4]]]
							 )
					       );
      delete[] fake_index;
    }
  }

  
  RooArgList* pdflist   = new RooArgList();
  RooArgList* yieldlist = new RooArgList();
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_dim[ipdf]==0 ) continue;
    if     ( pdf_dim[ipdf]==1 ) pdflist->add( *pdf_roohist_prod[ipdf] );
    else if( pdf_dim[ipdf]==2 ) pdflist->add( *pdf_roohist_2d  [ipdf] );

    yieldlist->add( *yield_formula[ipdf] );
    //if( pdf_fix[ipdf]==2 ) yieldlist->add( *yield_formula[ipdf] );
    //else                   yieldlist->add( *yield        [ipdf] );
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
  //yield_sub[1]->setVal(0.252); // tmpppp
  //yield_sub[1]->setVal(0.301667); // tmpppp
  //yield_sub[1]->setVal(0.40); // tmpppp
  //yield_sub[1]->setConstant(true); // tmpppp
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
  frame_fit_nb_sig_enh_log->SetTitle( "NB with signal E_{ECL} region" );
  /*
  data   ->plotOn( frame_fit_nb_sig_enh_log, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("signal_box_eecl") ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2), ProjectionRange("signal_box_eecl") ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( pdf_fix[ipdf]==2 ) continue;
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_nb_sig_enh_log, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_eecl") ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_nb_sig_enh_log, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_eecl") ); // each-pdf
  }
  */
  ///* stacked-style
  data   ->plotOn( frame_fit_nb_sig_enh_log, Binning(nb_xbin), CutRange("signal_box_eecl"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 2), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(*pdflist) ); // signal
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 3), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor(11), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[3])) ); // D**
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 4), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_nb_sig_enh_log, Binning(nb_xbin), CutRange("signal_box_eecl"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/
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
  /* // for normal fit
  std::cout << std::setw( 5) << std::right << fl_stream
	    << std::setw( 7) << std::right << tag_cnt
	    << std::setw(15) << std::right << convert_factor_rdstr[lep_index[fl_lep]] * yield_formula[1]->getVal()/yield_formula[2]->getVal()
    //<< std::setw(15) << std::right << convert_factor_rdstr[lep_index[fl_lep]] * yield_formula[1]->getVal()/yield_formula[2]->getVal() * sqrt( pow(yield_formula[1]->getError()/yield_formula[1]->getVal(),2) +
    //pow(yield_formula[2]->getError()/yield_formula[2]->getVal(),2)
    //)
	    << std::setw(15) << std::right << convert_factor_rdstr[lep_index[fl_lep]] * yield_formula[1]->getVal()/yield_formula[2]->getVal() * sqrt(
																     pow(yield_formula[1]->getError()/yield_formula[1]->getVal(),2) +
																     pow(yield_formula[2]->getError()/yield_formula[2]->getVal(),2) -
																     2.0*fit_result->correlationMatrix()(1,2)* // correation term
																     yield_formula[1]->getError()/yield_formula[1]->getVal()* // correation term
																     yield_formula[2]->getError()/yield_formula[2]->getVal() // correation term
														   )
	    << std::setw(15) << std::right << yield_formula[1]->getVal()
	    << std::setw(15) << std::right << yield_formula[1]->getError()
	    << std::setw(15) << std::right << yield_formula[2]->getVal()
	    << std::setw(15) << std::right << yield_formula[2]->getError();

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( ipdf==1 || ipdf==2 || pdf_fix[ipdf] ) continue;
    std::cout << std::setw(15) << std::right << yield_formula[ipdf]->getVal()
	      << std::setw(15) << std::right << yield_formula[ipdf]->getError();
  }
  */
  ///* // for R(D*) fit
  std::cout << std::setw( 5) << std::right << fl_stream
	    << std::setw( 7) << std::right << tag_cnt
	    << std::setw(15) << std::right << yield_sub[1]->getVal()
	    << std::setw(15) << std::right << yield_sub[1]->getError()
	    << std::setw(15) << std::right << yield_formula[1]->getVal()
    /*
	    << std::setw(15) << std::right << yield_formula[1]->getVal() * sqrt(
										pow(yield_sub[1]->getError(),2)*pow(1.0+1.0/yield_sub[1]->getVal(),-2)*pow(yield_sub[1]->getVal(),-4) +
										pow(yield_sub[2]->getError(),2)*pow(yield_sub[2]->getVal(),-2) +
										2.0/yield_sub[2]->getVal()/(1.0+1.0/yield_sub[1]->getVal())*fit_result->correlationMatrix()(1,2)*yield_sub[1]->getError()*yield_sub[2]->getError()*pow(yield_sub[1]->getVal(),-2)
										)
	    << std::setw(15) << std::right << yield_formula[2]->getVal()
	    << std::setw(15) << std::right << yield_formula[2]->getVal() * sqrt(
										pow(yield_sub[1]->getError(),2)*pow(1.0+yield_sub[1]->getVal(),-2) +
										pow(yield_sub[2]->getError(),2)*pow(yield_sub[2]->getVal(),-2) -
										2.0/yield_sub[2]->getVal()/(1.0+yield_sub[1]->getVal())*fit_result->correlationMatrix()(1,2)*yield_sub[1]->getError()*yield_sub[2]->getError()
										);
    */
	    << std::setw(15) << std::right << yield_formula[1]->getVal() * sqrt(
										pow(yield_sub[1]->getError(),2)*pow(1.0/convert_factor_rdstr[lep_index[fl_lep]]+1.0/yield_sub[1]->getVal(),-2)*pow(yield_sub[1]->getVal(),-4) +
										pow(yield_sub[2]->getError(),2)*pow(yield_sub[2]->getVal(),-2) +
										2.0/yield_sub[2]->getVal()/(1.0/convert_factor_rdstr[lep_index[fl_lep]]+1.0/yield_sub[1]->getVal())*fit_result->correlationMatrix()(1,2)*yield_sub[1]->getError()*yield_sub[2]->getError()*pow(yield_sub[1]->getVal(),-2)
										)
	    << std::setw(15) << std::right << yield_formula[2]->getVal()
	    << std::setw(15) << std::right << yield_formula[2]->getVal() * sqrt(
										pow(yield_sub[1]->getError(),2)*pow(convert_factor_rdstr[lep_index[fl_lep]]+yield_sub[1]->getVal(),-2) +
										pow(yield_sub[2]->getError(),2)*pow(yield_sub[2]->getVal(),-2) -
										2.0/yield_sub[2]->getVal()/(convert_factor_rdstr[lep_index[fl_lep]]+yield_sub[1]->getVal())*fit_result->correlationMatrix()(1,2)*yield_sub[1]->getError()*yield_sub[2]->getError()
										);

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( ipdf==1 || ipdf==2 || pdf_fix[ipdf] ) continue;
    std::cout << std::setw(15) << std::right << yield_formula[ipdf]->getVal()
      //<< std::setw(15) << std::right << yield_formula[ipdf]->getError();
      ;
  }
  //*/
  std::cout << " HIGEEEEE "
	    << "lep" << fl_lep << "lep"
	    << std::endl;
  std::cout << "==========================================================================================================================================================================" << std::endl;

  std::cout << std::setw(15) << std::right << yield_sub[1]->getVal()
	    << std::setw(15) << std::right << fit_result->minNll()
	    << Form( "   STATSIGNIFICANCE_lep%d", fl_lep )
	    << std::endl;
    
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( !fl_toymc ){
    /*
    if( fl_stream == -999 ){
      // +++++++++++++++++++++++++ Likelihood Scan for simultaneous fitting+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
      RooAbsReal* nll  = pdf_tot->createNLL( *data ); // plain likelihood
      RooAbsReal* pnll = nll->createProfile( *yield_sub[1] ) ; // profile likelihood (all floating parameters except signal yields)
      TCanvas* can_scan = Canvas( "can_scan","can_scan", 2, 1 );
      can_scan->Draw();

      RooPlot* frame_scan1 = yield_sub[1]->frame( Bins(50), Range(yield_sub[1]->getVal()-3.0*yield_sub[1]->getError(),yield_sub[1]->getVal()+3.0*yield_sub[1]->getError()), Title("profile") );
      nll ->plotOn( frame_scan1, LineColor(kBlue), ShiftToZero() );
      pnll->plotOn( frame_scan1,LineColor(kRed) );
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

      RooPlot* frame_scan2 = yield_sub[1]->frame( Bins(50), Range(0.252,yield_sub[1]->getVal()+3.0*yield_sub[1]->getError()), Title("profile") );
      nll ->plotOn( frame_scan2, LineColor(kBlue), ShiftToZero() );
      pnll->plotOn( frame_scan2,LineColor(kRed) );
      frame_scan2->GetXaxis()->CenterTitle();
      frame_scan2->GetYaxis()->CenterTitle();
      frame_scan2->SetTitleOffset( 1.00, "x" );
      frame_scan2->SetTitleOffset( 1.30, "y" );
      frame_scan2->SetTitle( "Likelihood Scan" );
      frame_scan2->SetMinimum(0);
      frame_scan2->SetMaximum(5);

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
  // toy MC part is removed in this codes

  return 0;

}
