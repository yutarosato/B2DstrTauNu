#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//const Double_t corr_fake_d        = 1.0;
const Double_t corr_fake_d        = 269/331.;
//const Double_t corr_fake_d        = 269/364.;
//const Char_t*  pdf_dir             = "pdf/";
const Char_t*  pdf_dir             = "pdf_radveto/";
//const Char_t*  pdf_dir             = "pdf_rad1pveto/";
//const Char_t*  selection_common_mc = "1";
const Char_t*  selection_common_mc = "(ctgrsyst!=7&&ctgrsyst!=8)"; // veto D(*)(2S) // tmppppppppppppp
//const Char_t*  selection_common_mc = "(ctgrsyst!=5&&ctgrsyst!=7&&ctgrsyst!=8)"; // veto D1' and D(*)(2S) // tmppppppppppppp

const Int_t   npdf                = 10;
const Char_t* pdf_name     [npdf] = { "other", "sig", "nor", "dstst", "doubled", "fake_other", "fake_sig", "fake_nor", "fake_dstst", "fake_doubled" };
Double_t      pdf_nexp     [npdf] = {     1.0,   1.0,   1.0,     1.0,       1.0,          1.0,        1.0,        1.0,          1.0,            1.0 };
const Int_t   col          [npdf] = {       5,     7,     4,       3,         8,            6,          6,          6,            6,              6 };
const Int_t   lsty         [npdf] = {       2,     1,     1,       1,         2,            2,          2,          2,            2,              2 };
const Int_t   pdf_fix      [npdf] = {       1,     1,     0,       0,         1,            2,          2,          2,            2,              2 }; // 0(float), 1(fix), 2(partially-fix for fake D* component)
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
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Bool_t   fl_use_dststmc  = true;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut/gMC_*s0[0-9]*.root";
const Char_t*  infile_gmc_1st  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut/gMC_*s0%d*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_noremcut/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
const Bool_t   fl_use_npmc     = true;
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/0p0_weight_nb_noremcut/npMC_*s0*.root";
const Char_t*  infile_npmc_1st = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/0p0_weight_nb_noremcut/npMC_*s0%d*.root";
const Double_t nstream_npmc    = 10;
const Char_t*  fl_par_dt       = "0p0"; // for samples
const Char_t*  weight_table    = "../npmc/table/dstrtaunu_dpi_lep_12_all/est_weight.root";
const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut/RD_*.root";

const Char_t*  selection_common    = "(rempi0_1==1 && remks==0 && remtrk==0)";
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
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (int)nexp (int)fl_stream (int)fl_lep [(int) #iteration or #tag_cnt]" << std::endl
	      << "      * unit of nexp is percent : (i.e.) 100 is default yield of belle MC" << std::endl
	      << "      *  toy mc  test mode for negative fl_stream " << std::endl
	      << "      *     data fit  mode for fl_stream=-999 "     << std::endl
	      << "      * ensemble test mode for positive fl_stream " << std::endl
	      << "      * fl_lep : 10(e), 1(mu), 0(l)"                << std::endl
	      << "[e.g]" << std::endl
	      << "./2dfit 100 -999 0   # data fit mode                (NEXP STREAMNO LEP           )" << std::endl
	      << "./2dfit 100  0   0   # ensemble mode                (NEXP STREAMNO LEP           )" << std::endl
	      << "./2dfit 100  0   0 1 # ensemble mode for syst study (NEXP STREAMNO LEP TAG       )" << std::endl
	      << "./2dfit 100 -1   1   #  toy  mc mode                (NEXP STREAMNO LEP NITERATION)"
	      << std::endl, abort();
  //pdf_nexp[1]      = atof(app.Argv(1))/100.0;
  pdf_nexp[3]      = atof(app.Argv(1))/100.0;
  pdf_nexp[8]      = atof(app.Argv(1))/100.0;
  Int_t  fl_stream = atoi(app.Argv(2));
  Int_t  fl_lep    = atoi(app.Argv(3));
  Bool_t fl_toymc  = !true;
  Int_t  iteration = 10000;
  Int_t  tag_cnt   = 0;
  std::cout << "fl_par_pdf = " << fl_par_pdf << std::endl
	    << "fl_par_dt  = " << fl_par_dt  << std::endl;

  if( fl_stream==-999 ){
    std::cout << "[data fitting mode]" << std::endl;
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
  //unsigned int seed = time(NULL);
  unsigned int seed_dstst = 20000;
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
  sTmp << Form("eecl_exp<%f",eecl_xmax);
  sTmp << " && " << selection_common;
  sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
  sTmp << " && " << makeCut_npmc   ( fl_use_npmc    ).c_str();
  if( fl_lep ) sTmp << Form(" && ( (cosdll==cosdl1 && rm_l1==%d) || (cosdll==cosdl2 && rm_l2==%d) )",fl_lep,fl_lep);
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
      weight *= pdf_nexp[ipdf];
      if( pdf_dim[ipdf] ){
	mc_hist[ipdf]->Fill( c_gmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_gmc_cut[ipdf]->GetLeaf("eecl_exp" )->GetValue(), weight );
	mc_hist_tot  ->Fill( c_gmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_gmc_cut[ipdf]->GetLeaf("eecl_exp" )->GetValue(), weight );
      }
    }

    for( Int_t ievt=0; ievt<c_dststmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_dststmc_cut[ipdf], ievt, (Double_t)nstream_dststmc );
      weight *= pdf_nexp[ipdf];
      if( pdf_dim[ipdf] ){
	mc_hist[ipdf]->Fill( c_dststmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_dststmc_cut[ipdf]->GetLeaf("eecl_exp" )->GetValue(), weight );
	mc_hist_tot  ->Fill( c_dststmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_dststmc_cut[ipdf]->GetLeaf("eecl_exp" )->GetValue(), weight );
      }
    }
    
    for( Int_t ievt=0; ievt<c_npmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_npmc_cut[ipdf], ievt, (Double_t)nstream_npmc );

      Double_t val[np::nvar];
      for( Int_t ivar=0; ivar<np::nvar; ivar++ ) val[ivar] = c_npmc_cut[ipdf]->GetLeaf(np::brname[ivar])->GetValue(); // reproduce NP distribution by re-weighted SM distribution
      Int_t gindex = getGIndex( val );
      Double_t npweight  = npweight_table->GetY()[gindex];
      Double_t npweightE = npweight_table->GetErrorY(gindex);
      weight *= npweight; // NP weight
      
      weight *= pdf_nexp[ipdf];
      if( pdf_dim[ipdf] ){
	mc_hist[ipdf]->Fill( c_npmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_npmc_cut[ipdf]->GetLeaf("eecl_exp" )->GetValue(), weight );
	mc_hist_tot  ->Fill( c_npmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_npmc_cut[ipdf]->GetLeaf("eecl_exp" )->GetValue(), weight );
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
  //Double_t init_l [npdf] = {65.3345, 18.3569, 212.096, 324.807, 70.9037, 69.0335, 5.58377, 51.8884, 153.003, 84.7574 };
  //Double_t init_e [npdf] = {28.6478, 11.0363, 115.191, 167.495, 39.7499, 41.7237, 3.66362, 27.2302, 93.2806, 55.0325 };
  //Double_t init_mu[npdf] = {36.6867, 7.32066, 96.9051, 157.312, 31.1538, 27.3098, 1.92014, 24.6582, 59.7228, 29.7249 };

  Double_t init_l [npdf] = {65.3345, 18.3569, 212.096, 259.503, 70.4628, 69.0335, 5.58377, 51.8884, 111.865, 82.5129 }; // veto D(*)(2S)
  Double_t init_e [npdf] = {28.6478, 11.0363, 115.191, 133.616, 39.7499, 41.7237, 3.66362, 27.2302, 70.4928, 53.4871 }; // veto D(*)(2S)
  Double_t init_mu[npdf] = {36.6867, 7.32066, 96.9051, 125.866, 30.7129, 27.3098, 1.92014, 24.6582, 41.372,  29.0258 }; // veto D(*)(2S)

  //Double_t init_l [npdf] = {65.3345, 18.3569, 212.096, 183.585, 69.2145, 69.0335, 5.58377, 51.8884, 83.1061, 79.804 }; // veto D(*)(2S) and D1'
  //Double_t init_e [npdf] = {28.6478, 11.0363, 115.191, 92.9098, 39.032, 41.7237, 3.66362, 27.2302, 51.0659, 51.7517 }; // veto D(*)(2S) and D1'
  //Double_t init_mu[npdf] = {36.6867, 7.32066, 96.9051, 90.6747, 30.1825, 27.3098, 1.92014, 24.6582, 32.0402, 28.0523 }; // veto D(*)(2S) and D1'

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
  //*/
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <OBSERVABLES>
  RooRealVar* nb     = new RooRealVar( "nb",   "NB",               nb_xmin,   nb_xmax ); // x 
  RooRealVar* eecl   = new RooRealVar( "eecl", "E'_{ECL} [GeV]", eecl_xmin, eecl_xmax ); // y
  RooRealVar* w      = new RooRealVar( "w",    "w",                    0.0,      10.0 ); // weight
  RooArgSet*  varset = new RooArgSet ( *nb, *eecl     );
  RooArgSet*  varsetw = new RooArgSet( *nb, *eecl, *w );

  nb  ->setBins(   nb_xbin );
  eecl->setBins( eecl_xbin );
  
  //nb  ->setRange( "signal_box_nb",    0.8, 1.0 );
  nb  ->setRange( "signal_box_nb",    0.0, 1.0 );
  eecl->setRange( "signal_box_nb",    0.0, 1.2 );
  //nb  ->setRange( "norm_box_nb",     -1.0, 0.8 );
  nb  ->setRange( "norm_box_nb",     -1.0, 0.0 );
  eecl->setRange( "norm_box_nb",      0.0, 1.2 );
  nb  ->setRange( "signal_box_eecl", -1.0, 1.0 );
  eecl->setRange( "signal_box_eecl",  0.0, 0.5 );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <PDF>
  TFile** pdf_file      = new TFile*[npdf];
  TH2D**  pdf_hist_2d   = new TH2D* [npdf];
  TH1D**  pdf_hist_nb   = new TH1D* [npdf];
  TH1D**  pdf_hist_eecl = new TH1D* [npdf];
  //for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
  for( Int_t ipdf=npdf-1; ipdf>=0; ipdf-- ){
    pdf_file[ipdf] = new TFile( Form("%s/makepdf_%s_lep%d_%s.root", pdf_dir, pdf_name[ipdf], fl_lep, (ipdf==1 ? fl_par_pdf : "0p0") ) );
    /* <for syststudy>
    Int_t systpdf_no = 4; // 2(nor), 3(faked), 4(D**), 5(Double D)
    if( ipdf==systpdf_no ) pdf_file[ipdf] = new TFile( Form("%s/makepdf_%s_lep%d_%s_%d.root", pdf_dir_syst, pdf_name[ipdf], fl_lep, (ipdf==1 ? fl_par_pdf : "0p0"), tag_cnt ) );
    else                   pdf_file[ipdf] = new TFile( Form("%s/makepdf_%s_lep%d_%s.root",    pdf_dir,      pdf_name[ipdf], fl_lep, (ipdf==1 ? fl_par_pdf : "0p0"           ) );
    */

    if( pdf_file[ipdf]->IsZombie() ) std::cerr << "[ABORT] can not find pdf-file for " << pdf_name[ipdf] << std::endl, abort();
    ///*

    pdf_hist_2d  [ipdf] = (TH2D*)pdf_file[ipdf]->Get( Form("nb_eecl_%s_lep%d",          pdf_name[ipdf], fl_lep) );
    //pdf_hist_2d  [ipdf] = (TH2D*)pdf_file[ipdf]->Get( Form("nb_eecl_%s_lep%d_nosmooth", pdf_name[ipdf], fl_lep) ); // testtttt
    //*/
    //if( ipdf==4 ) pdf_hist_2d  [ipdf] = (TH2D*)pdf_file[ipdf]->Get( Form("nb_eecl_%s_lep%d_nosmooth",    pdf_name[ipdf], fl_lep) ); // testtttt
    //else          pdf_hist_2d  [ipdf] = (TH2D*)pdf_file[ipdf]->Get( Form("nb_eecl_%s_lep%d",             pdf_name[ipdf], fl_lep) ); // testtttt

    pdf_hist_nb  [ipdf] = (TH1D*)pdf_file[ipdf]->Get( Form(  "nb_%s_all_nb_lep%d",pdf_name[ipdf],fl_lep) );
    if( ipdf==1 ) pdf_hist_eecl[ipdf] = (TH1D*)pdf_file[   2]->Get( Form("eecl_%s_all_nb_lep%d",pdf_name[   2],fl_lep) ); // normalization PDF is used for signal-PDF.
    else          pdf_hist_eecl[ipdf] = (TH1D*)pdf_file[ipdf]->Get( Form("eecl_%s_all_nb_lep%d",pdf_name[ipdf],fl_lep) );
    //pdf_hist_eecl[ipdf] = (TH1D*)pdf_file[ipdf]->Get( Form("eecl_%s_pos_nb_lep%d",pdf_name[ipdf],fl_lep) ); // for testtttt
    if( pdf_hist_2d  [ipdf]== NULL ) std::cerr << "[ABORT] can not find  2d  histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_nb  [ipdf]== NULL ) std::cerr << "[ABORT] can not find  nb  histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_eecl[ipdf]== NULL ) std::cerr << "[ABORT] can not find eecl histogram for " << pdf_name[ipdf] << std::endl, abort();

    if( pdf_hist_2d  [ipdf]->GetNbinsX()!=  nb_xbin ) std::cerr << "[ABORT] Wrong x( nb ) binning in 2d histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_2d  [ipdf]->GetNbinsY()!=eecl_xbin ) std::cerr << "[ABORT] Wrong y(eecl) binning in 2d histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_nb  [ipdf]->GetNbinsX()!=  nb_xbin ) std::cerr << "[ABORT] Wrong x( nb ) binning in 1d histogram for " << pdf_name[ipdf] << std::endl, abort();
    if( pdf_hist_eecl[ipdf]->GetNbinsX()!=eecl_xbin ) std::cerr << "[ABORT] Wrong x(eecl) binning in 1d histogram for " << pdf_name[ipdf] << std::endl, abort();
  }


  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <for syststudy>
  /*
  Int_t systpdf_no = 5;
  if( tag_cnt ){
    if( pdf_dim[systpdf_no]==2 ){ // 2-dimensional histogram-PDF
      //for( Int_t it=0; it<2; it++ ){
      Double_t rnd_x, rnd_y;
      TH2D* syst_hist = new TH2D( *pdf_hist_2d[systpdf_no] );
      pdf_hist_2d[systpdf_no]->Reset();
      for( Int_t i=0; i<syst_hist->GetEntries(); i++ ){
	//for( Int_t i=0; i<10*syst_hist->GetEntries(); i++ ){ // testtttt
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
  }
  else{
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
    std::cout << "[infile_npmc_1st] " << Form(infile_npmc_1st,fl_stream)  << " : " << fl_par_dt << std::endl;
    std::cout << c_npmc_1st->Add(        Form(infile_npmc_1st,fl_stream)) << " files, ";
    std::cout << c_npmc_1st->GetEntries()                                       << " entries, "
	      << std::endl;
    
    sTmp.str("");
    sTmp.clear();
    sTmp << Form("eecl_exp<%f",eecl_xmax);
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
      eecl->setVal( c_gmc_1st_cut->GetLeaf("eecl_exp" )->GetValue() );
      nb  ->setVal( c_gmc_1st_cut->GetLeaf(  nb_brname)->GetValue() );
      data->add( *varset, weight );
    }
    data->Print();

    gRandom->SetSeed( seed_dstst );
    for( Int_t ievt=0; ievt<c_dststmc_cut->GetEntries(); ievt++ ){
      if( gRandom->Rndm() > 1/nstream_dststmc ) continue; // D** MC samples is scaled to 1 stream using "gRandom->Rndm", which is uniform distribution between 0 and 1
      Double_t weight = cal_weight( c_dststmc_cut, ievt, 1.0 );
      eecl->setVal( c_dststmc_cut->GetLeaf("eecl_exp" )->GetValue() );
      nb  ->setVal( c_dststmc_cut->GetLeaf(  nb_brname)->GetValue() );
      data->add( *varset, weight );
    }

    data->Print();

    for( Int_t ievt=0; ievt<c_npmc_1st_cut->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_npmc_1st_cut, ievt, 1.0 );
      Double_t val[np::nvar];
      for( Int_t ivar=0; ivar<np::nvar; ivar++ ) val[ivar] = c_npmc_1st_cut->GetLeaf(np::brname[ivar])->GetValue(); // reproduce NP distribution by re-weighted SM distribution
      Int_t gindex = getGIndex( val );
      Double_t npweight  = npweight_table->GetY()[gindex];
      Double_t npweightE = npweight_table->GetErrorY(gindex);
      weight *= npweight; // NP weight
      eecl->setVal( c_npmc_1st_cut->GetLeaf("eecl_exp" )->GetValue() );
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
  pdf_tot->plotOn( frame_fit_nb, Components( RooArgSet(*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9]) ), LineStyle(1), LineColor(1), LineWidth(1) ); // fake D*
  */
  /* stacked-style
  data   ->plotOn( frame_fit_nb, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor(17), DrawOption("F"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 2), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal
  
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 3), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 9), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 7), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 4), DrawOption("F"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_nb, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  */
    ///* line-style for paper plot
  data   ->plotOn( frame_fit_nb, Binning(nb_xbin), MarkerColor(1), LineColor(1), LineWidth(1) ); // data


  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor(11), DrawOption("F"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_nb, FillStyle(3006), FillColor(17), DrawOption("F"), Components(*pdflist) ); // D**

  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 2), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal
  
  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor(15), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm
  pdf_tot->plotOn( frame_fit_nb, FillStyle(3017), FillColor( 3), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm

  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 9), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D + other

  pdf_tot->plotOn( frame_fit_nb, FillStyle(1001), FillColor( 7), DrawOption("F"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb, FillStyle(3018), FillColor( 4), DrawOption("F"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  data   ->plotOn( frame_fit_nb, Binning(nb_xbin), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/
  
  frame_fit_nb->Draw();
  
  //+++++++++++++++++++++++++++++

  can_fit->cd(2);
  //can_fit->cd(2)->SetLogy();
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
  pdf_tot->plotOn( frame_fit_nb_sig_enh, Components( RooArgSet(*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9]) ), LineStyle(1), LineColor(1), LineWidth(1), ProjectionRange("signal_box_eecl") ); // fake D*
  */
  /* stacked-style
  data   ->plotOn( frame_fit_nb_sig_enh, Binning(nb_xbin), CutRange("signal_box_eecl"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor(17), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 2), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal
  
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 3), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 4), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_nb_sig_enh, Binning(nb_xbin), CutRange("signal_box_eecl"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  */
  ///* line-style for paper plot
  data   ->plotOn( frame_fit_nb_sig_enh, Binning(nb_xbin), CutRange("signal_box_eecl"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor(11), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(3006), FillColor(17), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 2), DrawOption("F"),  ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal

  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor(15), DrawOption("F"),  ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(3017), FillColor( 3), DrawOption("F"),  ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm

  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D + other

  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb_sig_enh, FillStyle(3018), FillColor( 4), DrawOption("F"), ProjectionRange("signal_box_eecl"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
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
  /* stacked-style
  data   ->plotOn( frame_fit_nb_sig_enh_log, Binning(nb_xbin), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor(17), DrawOption("F"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 2), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal
  
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 3), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 9), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 7), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 4), DrawOption("F"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_nb_sig_enh_log, Binning(nb_xbin), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  */
  ///* line-style for paper plot
  data   ->plotOn( frame_fit_nb_sig_enh_log, Binning(nb_xbin), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor(11), DrawOption("F"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(3006), FillColor(17), DrawOption("F"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 2), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal

  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor(15), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(3017), FillColor( 3), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm

  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 9), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D + other

  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(1001), FillColor( 7), DrawOption("F"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_nb_sig_enh_log, FillStyle(3018), FillColor( 4), DrawOption("F"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
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
  pdf_tot->plotOn( frame_fit_eecl, Components( RooArgSet(*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9]) ), LineStyle(1), LineColor(1), LineWidth(1) ); // fake D*
  */
  /* stacked-style
  data   ->plotOn( frame_fit_eecl, Binning(eecl_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor(17), DrawOption("F"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 2), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal
  
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 3), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 9), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 7), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 4), DrawOption("F"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_eecl, Binning(eecl_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  */
  ///* line-style for paper plot
  data   ->plotOn( frame_fit_eecl, Binning(eecl_xbin), MarkerColor(1), LineColor(1), LineWidth(1) ); // data

  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor(11), DrawOption("F"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(3006), FillColor(17), DrawOption("F"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 2), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal

  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor(15), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(3017), FillColor( 3), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm

  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 9), DrawOption("F"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D + other

  pdf_tot->plotOn( frame_fit_eecl, FillStyle(1001), FillColor( 7), DrawOption("F"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_eecl, FillStyle(3018), FillColor( 4), DrawOption("F"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  data   ->plotOn( frame_fit_eecl, Binning(eecl_xbin), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/
  
  pdf_tot->paramOn( frame_fit_eecl, Format("NELU", AutoPrecision(2)), Layout(0.40, 0.99, 0.99), ShowConstants(true) );
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
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, Components( RooArgSet(*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9]) ), LineStyle(1), LineColor(1), LineWidth(1), ProjectionRange("signal_box_nb") ); // fake D*
  */
  /* stacked-style
  data   ->plotOn( frame_fit_eecl_sig_enh, Binning(eecl_xbin), CutRange("signal_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor(17), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 2), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal
  
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 3), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 4), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_eecl_sig_enh, Binning(eecl_xbin), CutRange("signal_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  */
  ///* line-style for paper plot
  data   ->plotOn( frame_fit_eecl_sig_enh, Binning(eecl_xbin), CutRange("signal_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor(11), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(3006), FillColor(17), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 2), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal
  
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor(15), DrawOption("F"),  ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(3017), FillColor( 3), DrawOption("F"),  ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm

  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D + other

  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, FillStyle(3018), FillColor( 4), DrawOption("F"), ProjectionRange("signal_box_nb"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
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
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, Components( RooArgSet(*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9]) ), LineStyle(1), LineColor(1), LineWidth(1), ProjectionRange("norm_box_nb") ); // fake D*
  */
  /* stacked-style
  data   ->plotOn( frame_fit_eecl_nor_enh, Binning(eecl_xbin), CutRange("norm_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor(17), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 2), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal
  
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 3), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // normalization
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 4), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(*pdf_roohist_2d[0]) ); // other
  data   ->plotOn( frame_fit_eecl_nor_enh, Binning(eecl_xbin), CutRange("norm_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  */
  ///* line-style for paper plot
  data   ->plotOn( frame_fit_eecl_nor_enh, Binning(eecl_xbin), CutRange("norm_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor(11), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(3006), FillColor(17), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(*pdflist) ); // D**
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 2), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2],*pdf_roohist_prod[1])) ); // signal
  
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor(15), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(3017), FillColor( 3), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4],*pdf_roohist_2d[2])) ); // norm
  
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 9), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(*pdf_roohist_2d[0],*pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9],*pdf_roohist_2d[4])) ); // Double D
  
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(1001), FillColor( 7), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, FillStyle(3018), FillColor( 4), DrawOption("F"), ProjectionRange("norm_box_nb"), Components(RooArgSet(                   *pdf_roohist_2d[5],*pdf_roohist_2d[6],*pdf_roohist_2d[7],*pdf_roohist_2d[8],*pdf_roohist_2d[9])) ); // fake D(*)
  data   ->plotOn( frame_fit_eecl_nor_enh, Binning(eecl_xbin), CutRange("norm_box_nb"), MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  //*/
  
  frame_fit_eecl_nor_enh->Draw();
  if     ( fl_stream==-999 ) can_fit->Print( Form("pic/2dfit_%.1f_lep%d_fit.eps",            pdf_nexp[1],fl_lep          ) );
  else if( fl_toymc        ) can_fit->Print( Form("pic/2dfit_%.1f_lep%d_fit.ps",             pdf_nexp[1],fl_lep          ) );
  else if( tag_cnt  ==0    ) can_fit->Print( Form("pic/2dfit_%.1f_lep%d_streamno_%d_fit.ps", pdf_nexp[1],fl_lep,fl_stream) );
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
	    << std::setw(15) << std::right << convert_factor_rdstr[lep_index[fl_lep]] * yield[1]->getVal()/yield[2]->getVal() * sqrt( pow(yield[1]->getError()/yield[1]->getVal(),2) +
														   pow(yield[2]->getError()/yield[2]->getVal(),2)
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

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( !fl_toymc ){
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
	      << std::setw(13) << std::right << init[3]
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
  can_toymc->Print( Form("pic/2dfit_%.1f_lep%d_toy.ps",  pdf_nexp[1],fl_lep) );
  //+++++++++++++++++++++++++++++++++++++++++++++++++

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
