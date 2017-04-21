#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t* pdf_dir             = "pdf/";
const Char_t* pdf_dir_syst        = "pdf_syst/";
//const Char_t* pdf_dir_syst        = "pdf_syst2/";
const Int_t   npdf                = 6;
const Char_t* pdf_name     [npdf] = { "other", "sig", "nor","faked", "dstst", "doubled" };
Double_t      pdf_nexp     [npdf] = {     1.0,   1.0,   1.0,    1.0,     1.0,       1.0 };
const Int_t   col          [npdf] = {       5,     3,     4,      6,       7,         8 };
const Int_t   lsty         [npdf] = {       2,     1,     1,      2,       2,         2 };
const Bool_t  pdf_fix      [npdf] = {    true, !true, !true,    true,   !true,     true };
const Int_t   pdf_dim      [npdf] = {       2,     1,     2,       2,       2,        2 }; // 0(not use)
const Char_t* pdf_selection[npdf] = { "0", // other
				      "(self==1||(self==0&&gm_semi>0&&dst1self==1&&dst2self==1))", // sig
				      //"(self==1||(self==0&&gm_semi>0&&dst1self==1&&dst2self==1)) && ((cosdll==cosdl1 && abs(rm_d1lun)==411)||(cosdll==cosdl2 && abs(rm_d2lun)==411))", // sig // tmpppppppp
				      "(self==2||(self==0&&gm_semi<0&&dst1self==1&&dst2self==1))", // nor
				      "(self<1&&!(dst1self==1&&dst2self==1))",                     // faked
				      "(self==-5&&dst1self==1&&dst2self==1)",                      // D**
				      "(self==-3&&dst1self==1&&dst2self==1)",                      // double D
};

const Bool_t  roosumw2   = !true; // fixed to be "false"
const Char_t* fl_par_pdf = "0p0"; // for PDF
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
const Double_t nstream_npmc    = 10;
const Char_t*  fl_par_dt       = "0p0"; // for samples
const Char_t*  weight_table    = "../npmc/table/dstrtaunu_dpi_lep_12_all/est_weight.root";
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
	      << "      * ensemble test mode for positive fl_stream " << std::endl
	      << "      * fl_lep : 10(e), 1(mu), 0(l)"                << std::endl
	      << "[e.g]" << std::endl
	      << "./2dfit 100  0 0   # ensemble mode                (NEXP STREAMNO LEP           )" << std::endl
	      << "./2dfit 100  0 0 1 # ensemble mode for syst study (NEXP STREAMNO LEP TAG       )" << std::endl
	      << "./2dfit 100 -1 1   #  toy  mc mode                (NEXP STREAMNO LEP NITERATION)"
	      << std::endl, abort();
  pdf_nexp[1]      = atof(app.Argv(1))/100.0;
  Int_t  fl_stream = atoi(app.Argv(2));
  Int_t  fl_lep    = atoi(app.Argv(3));
  Bool_t fl_toymc  = !true;
  Int_t  iteration = 10000;
  Int_t  tag_cnt   = 0;
  std::cout << "fl_par_pdf = " << fl_par_pdf << std::endl
	    << "fl_par_dt  = " << fl_par_dt  << std::endl;
    
  if( fl_stream < 0 ){
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
    if( pdf_dim[ipdf] && pdf_fix[ipdf]==!true ) npar++;
  }
  Int_t tmp_cnt = 1;
  std::stringstream sTmp;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  // <TChain>
  sTmp.str("");
  sTmp.clear();
  sTmp << Form("eecl<%f",eecl_xmax);
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
    if( ipdf==0 ) c_gmc_cut[ipdf] = c_gmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(), makeCut_remain(pdf_selection,npdf).c_str()) );
    else          c_gmc_cut[ipdf] = c_gmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),                pdf_selection[ipdf]        ) );
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
    if( ipdf==0 ) c_dststmc_cut[ipdf] = c_dststmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(), makeCut_remain(pdf_selection,npdf).c_str()) );
    else          c_dststmc_cut[ipdf] = c_dststmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),                pdf_selection[ipdf]        ) );
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
    if( ipdf==0 ) c_npmc_cut[ipdf] = c_npmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(), makeCut_remain(pdf_selection,npdf).c_str()) );
    else          c_npmc_cut[ipdf] = c_npmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),                pdf_selection[ipdf]        ) );
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
	mc_hist[ipdf]->Fill( c_gmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_gmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
	mc_hist_tot  ->Fill( c_gmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_gmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
      }
    }

    for( Int_t ievt=0; ievt<c_dststmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_dststmc_cut[ipdf], ievt, (Double_t)nstream_dststmc );
      weight *= pdf_nexp[ipdf];
      if( pdf_dim[ipdf] ){
	mc_hist[ipdf]->Fill( c_dststmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_dststmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
	mc_hist_tot  ->Fill( c_dststmc_cut[ipdf]->GetLeaf(nb_brname)->GetValue(), c_dststmc_cut[ipdf]->GetLeaf(eecl_brname)->GetValue(), weight );
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
  */
  //abort();
  //++++++++++++++++++++++++++++++++
  ///*
  // NP weight file
  TFile* npweight_file = new TFile( weight_table );
  if( npweight_file->IsZombie() ) std::cerr << "[ABORT] can not find weight-file for " << weight_table << std::endl, abort();
  TGraphErrors* npweight_table = (TGraphErrors*)npweight_file->Get( Form( "np_%s",fl_par_dt) );
  if( npweight_table==NULL ) std::cerr << "[ABORT] can not find weight-table for " << fl_par_dt << std::endl, abort();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //Double_t init[npdf] = {71.4554, 203.529, 2758.28, 545.124, 193.452, 119.483}; // w/o D** MC ( 6 streams)
  //Double_t init[npdf] = {67.4786, 202.661, 2750.01, 549.026, 191.011, 120.260}; // w/o D** MC (10 streams)
  //Double_t init[npdf] = {71.8168, 203.529, 2758.28, 664.628, 433.7890,119.700}; // w   D** MC ( 6 streams)

  //Double_t init[npdf] = {68.0346, 202.238, 2737.1, 658.591, 435.092, 120.83}; // w   D** MC (10 streams) * [Ks +-10 MeV],  D**taunu @ 20150722
  //Double_t init[npdf] = {68.1229, 202.661, 2750.01, 667.534, 432.765, 120.414}; // w   D** MC (10 streams)
  //Double_t init[npdf] = {68.1229, 202.661, 2750.01, (1.00+0.06)*667.534, 432.765, 120.414}; // w   D** MC (10 streams) for syststudy (fake D*)
  //Double_t init[npdf] = {68.1229, 202.661, 2750.01, (1.00-0.06)*667.534, 432.765, 120.414}; // w   D** MC (10 streams) for syststudy (fake D*)
  //Double_t init[npdf] = {68.1229, 202.661, 2750.01, 667.534, 432.765, 120.414*(1.00+0.029)}; // w   D** MC (10 streams) for syststudy (Double D)
  //Double_t init[npdf] = {68.1229, 202.661, 2750.01, 667.534, 432.765, 120.414*(1.00-0.029)}; // w   D** MC (10 streams) for syststudy (Double D)

  //Double_t init[npdf] = {51.3116, 198.799, 2185.74, 565.095, 356.565, 105.012 }; // w   D** MC (10 streams) // @ test : pD* < 1.8 GeV
  //Double_t init[npdf] = {43.8292, 190.834, 1898.36, 504.542, 317.359,  79.7289}; // w   D** MC (10 streams) // @ test : pD* < 1.7 GeV
  //Double_t init[npdf] = {35.9045, 178.296, 1616.32, 440.383, 268.747,  57.3460}; // w   D** MC (10 streams) // @ test : pD* < 1.6 GeV


  //Double_t init_l [npdf] = {68.0216, 202.238, 2737.1,  656.219, 430.664, 120.83 }; // w   D** MC (10 streams) * [Ks +-10 MeV],  D**taunu @ 20150806
  //Double_t init_e [npdf] = {29.9773, 116.415, 1443.57, 377.091, 240.683, 69.1629}; // w   D** MC (10 streams) * [Ks +-10 MeV],  D**taunu @ 20150806
  //Double_t init_mu[npdf] = {38.0442, 85.8227, 1293.53, 279.128, 189.981, 51.6674}; // w   D** MC (10 streams) * [Ks +-10 MeV],  D**taunu @ 20150806

  //Double_t init_l [npdf] = {66.7259, 198.345,  2686.83, 587.878, 423.392, 120.557 }; // w   D** MC, w/o npmc @ 20150909
  //Double_t init_e [npdf] = {29.418,  114.311,  1417.27, 339.653, 236.223,  69.0352}; // w   D** MC, w/o npmc @ 20150909
  //Double_t init_mu[npdf] = {37.3079,  84.0347, 1269.56, 248.225, 187.17,   51.522 }; // w   D** MC, w/o npmc @ 20150909

  Double_t init_l [npdf] = {66.1087, 190.19,  2686.91,  579.64, 417.42, 121.661 }; // w   D** MC, w  npmc (tanb/mh=0.0)@ 20150909
  Double_t init_e [npdf] = {29.1507, 117.972, 1417.35, 334.638, 232.711, 69.8497}; // w   D** MC, w  npmc (tanb/mh=0.0)@ 20150909
  Double_t init_mu[npdf] = {36.958,   72.2178,1269.56, 245.002, 184.709, 51.8111}; // w   D** MC, w  npmc (tanb/mh=0.0)@ 20150909

  //Double_t init_l [npdf] = {66.0669, 191.578,  2686.9,  579.709,  417.42, 121.676 }; // w   D** MC, w  npmc (tanb/mh=0.1)@ 20150909
  //Double_t init_e [npdf] = {29.1171, 118.862,  1417.34, 334.659,  232.711, 69.8392}; // w   D** MC, w  npmc (tanb/mh=0.1)@ 20150909
  //Double_t init_mu[npdf] = {36.9497,  72.7159, 1269.56, 245.049,  184.709, 51.8372}; // w   D** MC, w  npmc (tanb/mh=0.1)@ 20150909

  //Double_t init_l [npdf] = {66.0821, 191.03,   2686.9,  579.852,  417.413, 121.664 }; // w   D** MC, w  npmc (tanb/mh=0.2)@ 20150909
  //Double_t init_e [npdf] = {29.1324, 118.049,  1417.34, 334.775,  232.704,  69.8401}; // w   D** MC, w  npmc (tanb/mh=0.2)@ 20150909
  //Double_t init_mu[npdf] = {36.9498,  72.9812, 1269.56, 245.077,  184.709,  51.824 }; // w   D** MC, w  npmc (tanb/mh=0.2)@ 20150909

  //Double_t init_l [npdf] = {66.0961, 190.815,   2686.9,  579.904,  417.41, 121.638 }; // w   D** MC, w  npmc (tanb/mh=0.3)@ 20150909
  //Double_t init_e [npdf] = {29.1408, 117.868,  1417.34, 334.702,  232.701,  69.8069}; // w   D** MC, w  npmc (tanb/mh=0.3)@ 20150909
  //Double_t init_mu[npdf] = {36.9553,  72.9473, 1269.56, 245.203,  184.709,  51.831 }; // w   D** MC, w  npmc (tanb/mh=0.3)@ 20150909

  //Double_t init_l [npdf] = {66.0801, 190.53,   2686.89, 579.992,  417.402, 121.657 }; // w   D** MC, w  npmc (tanb/mh=0.4)@ 20150909
  //Double_t init_e [npdf] = {29.1195, 117.702,  1417.33, 334.849,  232.692,  69.8307}; // w   D** MC, w  npmc (tanb/mh=0.4)@ 20150909
  //Double_t init_mu[npdf] = {36.9606,  72.8286, 1269.56, 245.143,  184.709,  51.8259}; // w   D** MC, w  npmc (tanb/mh=0.4)@ 20150909

  //Double_t init_l [npdf] = {66.0973, 189.296,  2686.91, 580.325,  417.396, 121.582 }; // w   D** MC, w  npmc (tanb/mh=0.5)@ 20150909
  //Double_t init_e [npdf] = {29.1211, 116.673,  1417.34, 335.18,   232.687,  69.8078}; // w   D** MC, w  npmc (tanb/mh=0.5)@ 20150909
  //Double_t init_mu[npdf] = {36.9762,  72.6232, 1269.56, 245.145,  184.709,  51.7741}; // w   D** MC, w  npmc (tanb/mh=0.5)@ 20150909

  //Double_t init_l [npdf] = {66.0447, 186.536,  2686.92, 581.237,  417.385,  121.59  }; // w   D** MC, w  npmc (tanb/mh=0.6)@ 20150909
  //Double_t init_e [npdf] = {29.1246, 115.082,  1417.36, 335.941,  232.68775, 69.8162}; // w   D** MC, w  npmc (tanb/mh=0.6)@ 20150909
  //Double_t init_mu[npdf] = {36.9202,  71.4537, 1269.56, 245.296,  184.709,   51.7743}; // w   D** MC, w  npmc (tanb/mh=0.6)@ 20150909

  //Double_t init_l [npdf] = {66.0425, 183.72,  2686.95,  581.823,  417.4,    121.623 }; // w   D** MC, w  npmc (tanb/mh=0.7)@ 20150909
  //Double_t init_e [npdf] = {29.0985, 114.05,  1417.39,  336.685,  232.691,   69.8688}; // w   D** MC, w  npmc (tanb/mh=0.7)@ 20150909
  //Double_t init_mu[npdf] = {36.944,   69.6704,1269.56,  245.137,  184.709,   51.754 }; // w   D** MC, w  npmc (tanb/mh=0.7)@ 20150909

  //Double_t init_l [npdf] = {66.0299, 180.403, 2686.98,  582.542,  417.399,   121.649 }; // w   D** MC, w  npmc (tanb/mh=0.8)@ 20150909
  //Double_t init_e [npdf] = {29.1062, 112.576, 1417.42,  337.443,  232.69,     69.9368}; // w   D** MC, w  npmc (tanb/mh=0.8)@ 20150909
  //Double_t init_mu[npdf] = {36.9238,  67.8272,1269.56,  245.099,  184.709,    51.7119}; // w   D** MC, w  npmc (tanb/mh=0.8)@ 20150909

  //Double_t init_l [npdf] = {65.9421, 178.872, 2687.00,  583.106,  417.419,   121.72  }; // w   D** MC, w  npmc (tanb/mh=0.9)@ 20150909
  //Double_t init_e [npdf] = {29.071,  112.358, 1417.44,  338.087,  232.709,    70.0268}; // w   D** MC, w  npmc (tanb/mh=0.9)@ 20150909
  //Double_t init_mu[npdf] = {36.8711,  66.5141,1269.56,  245.019,  184.709,    51.6936}; // w   D** MC, w  npmc (tanb/mh=0.9)@ 20150909

  //Double_t init_l [npdf] = {65.9303, 176.94,  2687.02,  583.451,  417.43,    121.734 }; // w   D** MC, w  npmc (tanb/mh=1.0)@ 20150909
  //Double_t init_e [npdf] = {29.0656, 111.591, 1417.46,  338.49,   232.72,     70.0464}; // w   D** MC, w  npmc (tanb/mh=1.0)@ 20150909
  //Double_t init_mu[npdf] = {36.8647,  65.349, 1269.56,  244.961,  184.709,    51.6873}; // w   D** MC, w  npmc (tanb/mh=1.0)@ 20150909

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
  RooRealVar** yield = new RooRealVar*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    yield[ipdf] = new RooRealVar( Form("n%s",pdf_name[ipdf]), Form("N_{%s}",pdf_name[ipdf]), init[ipdf],  -100, ( init[ipdf]< 30 ? 150 : 5.0*init[ipdf]) );
    if( pdf_fix[ipdf] ) yield[ipdf]->setConstant(true);
  }

  RooArgList* pdflist   = new RooArgList();
  RooArgList* yieldlist = new RooArgList();
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if     ( pdf_dim[ipdf]==1 ) pdflist->add( *pdf_roohist_prod[ipdf] );
    else if( pdf_dim[ipdf]==2 ) pdflist->add( *pdf_roohist_2d  [ipdf] );
    if( pdf_dim[ipdf] ) yieldlist->add( *yield[ipdf] );
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
  }
  can_pdf->Print( Form("pic/2dfit_%.1f_lep%d_pdf.ps", pdf_nexp[1],fl_lep) );
  */

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <READ Data>
  RooDataSet* data;
  if( fl_stream < 0 ){
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
    std::cout << "[infile_npmc_1st] " << Form(infile_npmc_1st,"0p0",fl_stream)  << " : " << fl_par_dt << std::endl;
    std::cout << c_npmc_1st->Add(        Form(infile_npmc_1st,"0p0",fl_stream)) << " files, ";
    std::cout << c_npmc_1st->GetEntries()                                       << " entries, "
	      << std::endl;
    
    sTmp.str("");
    sTmp.clear();
    sTmp << Form("eecl<%f",eecl_xmax);
    sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
    sTmp << " && " << makeCut_npmc   ( fl_use_npmc    ).c_str();
    if( fl_lep ) sTmp << Form(" && ( (cosdll==cosdl1 && rm_l1==%d) || (cosdll==cosdl2 && rm_l2==%d) )",fl_lep,fl_lep);
    TTree* c_gmc_1st_cut  = c_gmc_1st ->CopyTree( Form("%s", sTmp.str().c_str()) );
    TTree* c_dststmc_cut  = c_dststmc ->CopyTree( Form("%s", sTmp.str().c_str()) );
    TTree* c_npmc_1st_cut = c_npmc_1st->CopyTree( Form("%s", sTmp.str().c_str()) );
    std::cout << "[ gmc_1st_cut] " << c_gmc_1st_cut ->GetEntries() << " events" << std::endl;
    std::cout << "[ dststmc_cut] " << c_dststmc_cut ->GetEntries() << " events" << std::endl;
    std::cout << "[npmc_1st_cut] " << c_npmc_1st_cut->GetEntries() << " events" << std::endl;
    
    for( Int_t ievt=0; ievt<c_gmc_1st_cut->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_gmc_1st_cut, ievt, 1.0 );
      eecl->setVal( c_gmc_1st_cut->GetLeaf(eecl_brname)->GetValue() );
      nb  ->setVal( c_gmc_1st_cut->GetLeaf(  nb_brname)->GetValue() );
      data->add( *varset, weight );
    }
    data->Print();

    gRandom->SetSeed( seed_dstst );
    for( Int_t ievt=0; ievt<c_dststmc_cut->GetEntries(); ievt++ ){
      if( gRandom->Rndm() > 1/nstream_dststmc ) continue; // D** MC samples is scaled to 1 stream using "gRandom->Rndm", which is uniform distribution between 0 and 1
      Double_t weight = cal_weight( c_dststmc_cut, ievt, 1.0 );
      eecl->setVal( c_dststmc_cut->GetLeaf(eecl_brname)->GetValue() );
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
  RooFitResult* fit_result = pdf_tot->fitTo( *data, Save(true), SumW2Error(roosumw2), Minos(true), Extended(true) );
  fit_result->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can_fit->cd(1);
  RooPlot* frame_fit_nb = nb->frame();
  frame_fit_nb->SetTitle( "NB" );
  data   ->plotOn( frame_fit_nb, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn( frame_fit_nb, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2) ); // total-pdf

  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_nb, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_nb, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
  }
  frame_fit_nb->Draw();
  
  //+++++++++++++++++++++++++++++

  can_fit->cd(2);
  can_fit->cd(2)->SetLogy();
  RooPlot* frame_fit_nb_sig_enh = nb->frame();
  frame_fit_nb_sig_enh->SetTitle( "NB with signal E_{ECL} region" );
  data   ->plotOn( frame_fit_nb_sig_enh, Binning(nb_xbin),     MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("signal_box_eecl") ); // data
  pdf_tot->plotOn( frame_fit_nb_sig_enh, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2), ProjectionRange("signal_box_eecl") ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_nb_sig_enh, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_eecl") ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_nb_sig_enh, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_eecl") ); // each-pdf
  }
  frame_fit_nb_sig_enh->Draw();

  //+++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++
  can_fit->cd(4);
  RooPlot* frame_fit_eecl = eecl->frame();
  frame_fit_eecl->SetTitle( "E_{ECL}" );
  data   ->plotOn ( frame_fit_eecl, Binning(eecl_xbin),   MarkerColor(1), LineColor(1), LineWidth(1) ); // data
  pdf_tot->plotOn ( frame_fit_eecl, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2) ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_eecl, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_eecl, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1) ); // each-pdf
  }
  pdf_tot->paramOn( frame_fit_eecl, Format("NELU", AutoPrecision(2)), Layout(0.40, 0.99, 0.99), ShowConstants(true) );
  frame_fit_eecl->Draw();

  //+++++++++++++++++++++++++++++
  can_fit->cd(5);
  RooPlot* frame_fit_eecl_sig_enh = eecl->frame();
  frame_fit_eecl_sig_enh->SetTitle( "E_{ECL} with signal NB region" );
  data   ->plotOn( frame_fit_eecl_sig_enh, Binning(eecl_xbin),   MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("signal_box_nb") ); // data
  pdf_tot->plotOn( frame_fit_eecl_sig_enh, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2), ProjectionRange("signal_box_nb") ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_eecl_sig_enh, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_nb") ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_eecl_sig_enh, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("signal_box_nb") ); // each-pdf
  }
  frame_fit_eecl_sig_enh->Draw();

  //+++++++++++++++++++++++++++++
  can_fit->cd(6);
  RooPlot* frame_fit_eecl_nor_enh = eecl->frame();
  frame_fit_eecl_nor_enh->SetTitle( "E_{ECL} with norm NB region" );
  data   ->plotOn( frame_fit_eecl_nor_enh, Binning(eecl_xbin),   MarkerColor(1), LineColor(1), LineWidth(1),        CutRange("norm_box_nb") ); // data
  pdf_tot->plotOn( frame_fit_eecl_nor_enh, Components(*pdflist), LineStyle(1),   LineColor(2), LineWidth(2), ProjectionRange("norm_box_nb") ); // total-pdf
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if     ( pdf_dim[ipdf]==1 ) pdf_tot->plotOn( frame_fit_eecl_nor_enh, Components(*pdf_roohist_prod[ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("norm_box_nb") ); // each-pdf
    else if( pdf_dim[ipdf]==2 ) pdf_tot->plotOn( frame_fit_eecl_nor_enh, Components(*pdf_roohist_2d  [ipdf]), LineStyle(lsty[ipdf]), LineColor(col[ipdf]), LineWidth(1), ProjectionRange("norm_box_nb") ); // each-pdf
  }
  frame_fit_eecl_nor_enh->Draw();
  if     ( fl_toymc   ) can_fit->Print( Form("pic/2dfit_%.1f_lep%d_fit.ps",             pdf_nexp[1],fl_lep          ) );
  else if( tag_cnt==0 ) can_fit->Print( Form("pic/2dfit_%.1f_lep%d_streamno_%d_fit.ps", pdf_nexp[1],fl_lep,fl_stream) );
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
