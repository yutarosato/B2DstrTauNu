#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

Int_t    deltam_xbin[2]  = {55,55};
Double_t deltam_xmin[2]  = {PDGmass::pip,PDGmass::pip};
Double_t deltam_th  [2]  = {PDGmass::pip,PDGmass::pip};
Double_t deltam_xmax[2]  = {       0.150,       0.150};

//const Char_t*  selection       = "eecl_exp<0.5 && nb_mode0_test13_nor>0.8 && (rempi0_1==1 && remks==0 && remtrk==0)";
//const Char_t*  selection       = "eecl_exp<1.2 && (rempi0_1==1 && remks==0 && remtrk==0)";
//const Char_t*  selection       = "nb_mode0_test13_nor>0.8 && eecl_exp<0.2 && (rempi0_1==1 && remks==0 && remtrk==0)";
//const Char_t*  selection       = "nb_mode0_test13_nor>0.0 && nb_mode0_test13_nor<0.8 && eecl_exp<0.2 && (rempi0_1==1 && remks==0 && remtrk==0)";
const Char_t*  selection       = "eecl<1.2";
//const Char_t*  selection       = "eecl<1.2 && nb_mode0_test13_nor < 0.0";
///*
const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_nodmcut/RD_*.root";
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_nodmcut/gMC_*s0[0-9]*.root";
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_nodmcut/DssMC_*.root";
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/%s_weight_nb_nodmcut/npMC_*.root";
//*/
/*
const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut_nodmcut/RD_*.root";
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut_nodmcut/gMC_*s0[0-9]*.root";
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_noremcut_nodmcut/DssMC_*.root";
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/%s_weight_nb_noremcut_nodmcut/npMC_*.root";
*/

const Double_t nstream_gmc     = 10;
const Bool_t   fl_use_dststmc  = true;
const Double_t nstream_dststmc = 2.7118;
const Bool_t   fl_use_npmc     = true;
const Double_t nstream_npmc    = 10;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void inputEvent_dt( TTree* tree, RooDataSet* data, TH2D* hist, RooRealVar* deltam1, RooRealVar* deltam2,
		  Int_t fl_dec ){
  for( Int_t ievt=0; ievt<tree->GetEntries(); ievt++ ){
    tree->GetEntry(ievt);
    Int_t tmp_d1_lun = abs((Int_t)tree->GetLeaf("rm_d1lun")->GetValue());
    Int_t tmp_d2_lun = abs((Int_t)tree->GetLeaf("rm_d2lun")->GetValue());
    
    if( fl_dec==411 && !(tmp_d1_lun==411 || tmp_d2_lun==411) ) continue;
    if( fl_dec==421 && !(tmp_d1_lun==421 && tmp_d2_lun==421) ) continue;

    Double_t tmp_dm1;
    Double_t tmp_dm2;
    
    if( tmp_d2_lun==411 ){
      tmp_dm1 = tree->GetLeaf("dm2")->GetValue();
      tmp_dm2 = tree->GetLeaf("dm1")->GetValue();
    }else{
      tmp_dm1 = tree->GetLeaf("dm1")->GetValue();
      tmp_dm2 = tree->GetLeaf("dm2")->GetValue();
    }
    if( deltam_xmin[0] > tmp_dm1 || deltam_xmax[0] < tmp_dm1 ) continue;
    if( deltam_xmin[1] > tmp_dm2 || deltam_xmax[1] < tmp_dm2 ) continue;
    deltam1->setVal( tmp_dm1 );
    deltam2->setVal( tmp_dm2 );
    data->add( RooArgSet(*deltam1,*deltam2) );
    hist->Fill( deltam1->getVal(), deltam2->getVal() );
  }
  return;
}

void inputEvent_mc( TTree* tree, RooDataSet* data, TH2D* hist, RooRealVar* deltam1, RooRealVar* deltam2,
		    Int_t fl_dec, Double_t used_nstream ){
  for( Int_t ievt=0; ievt<tree->GetEntries(); ievt++ ){
    tree->GetEntry(ievt);
    Int_t tmp_d1_lun = abs((Int_t)tree->GetLeaf("rm_d1lun")->GetValue());
    Int_t tmp_d2_lun = abs((Int_t)tree->GetLeaf("rm_d2lun")->GetValue());
    
    if( fl_dec==411 && !(tmp_d1_lun==411 || tmp_d2_lun==411) ) continue;
    if( fl_dec==421 && !(tmp_d1_lun==421 && tmp_d2_lun==421) ) continue;

    Double_t tmp_dm1;
    Double_t tmp_dm2;
    
    if( tmp_d2_lun==411 ){
      tmp_dm1 = tree->GetLeaf("dm2")->GetValue();
      tmp_dm2 = tree->GetLeaf("dm1")->GetValue();
    }else{
      tmp_dm1 = tree->GetLeaf("dm1")->GetValue();
      tmp_dm2 = tree->GetLeaf("dm2")->GetValue();
    }
    if( deltam_xmin[0] > tmp_dm1 || deltam_xmax[0] < tmp_dm1 ) continue;
    if( deltam_xmin[1] > tmp_dm2 || deltam_xmax[1] < tmp_dm2 ) continue;
    Double_t weight = cal_weight( tree, ievt, used_nstream );
    deltam1->setVal( tmp_dm1 );
    deltam2->setVal( tmp_dm2 );
    data->add( RooArgSet(*deltam1,*deltam2), weight );
    hist->Fill( deltam1->getVal(), deltam2->getVal(), weight );
  }
  return;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Double_t func_deltam_threshold_slowpip( const Double_t x ){
  Double_t p[3];
  Double_t th = PDGmass::pip;
  Double_t f;
  if( x>th ){
    f = pow(x-th, 1/2.0); // threshold function in delta-M fitting
  }else{
    f = 0;
  }
  return f;
}

Double_t func_deltam_threshold_slowpi0( const Double_t x ){
  Double_t p[3];
  Double_t th = PDGmass::pi0;
  Double_t f;
  if( x>th ){
    f = pow(x-th, 1/2.0); // threshold function in delta-M fitting
  }else{
    f = 0;
  }
  return f;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetOptStat(0);

  if( !(app.Argc()==2) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (int)fl_dec" << std::endl
	      << "     * fl_dec : 421(D0) or 411(D+)"
	      << "[e.g]" << std::endl
	      << "./fit_deltam_2d 421" << std::endl
	      << "./fit_deltam_2d 411" << std::endl, abort();
  Int_t fl_dec = atoi(app.Argv(1));
  if( fl_dec!=421 && fl_dec!=411 ) std::cerr << "[ABORT] Wrong mode : " << fl_dec << std::endl, abort();
  Int_t fl_slowpi[2] = { (nominal_dmass(fl_dec)>1.866 ? 0 : 1), 1 }; // 0(D+pi0), 1(D0pi+)
  for( Int_t i=0; i<2; i++ ){
    if( !fl_slowpi[i] ){ // D+pi0
      deltam_xmin[i]  = PDGmass::pi0;
      deltam_th  [i]  = PDGmass::pi0;
      deltam_xmax[i] -= 0.005;
    }else{ // D0pi+
      deltam_xbin[i] *= 2;
    }
  }

  Double_t nominal_deltam[2] = {
    ( fl_slowpi[0] ? PDGmass::dstrp - PDGmass::d0 : PDGmass::dstrp - PDGmass::dp ),
    ( fl_slowpi[1] ? PDGmass::dstrp - PDGmass::d0 : PDGmass::dstrp - PDGmass::dp ),
  };

  Read_Data( calib_file, true );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  sTmp.str("");
  sTmp.clear();
  sTmp << selection;
  sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
  sTmp << " && " << makeCut_npmc   ( fl_use_npmc    ).c_str();
  std::cout << "[Cut] " << sTmp.str().c_str() << std::endl;

  TChain* c_dt = new TChain("h15");
  std::cout << "[infile Data] "      << infile_dt << " : ";
  std::cout << c_dt->Add(infile_dt)  << " files, ";
  std::cout << c_dt->GetEntries()    << " entries -> ";
  TTree* c_dt_cut;
  c_dt_cut = c_dt->CopyTree( selection );
  std::cout << c_dt_cut->GetEntries() << " entries" << std::endl;

  TChain* c_gmc = new TChain(treename);
  std::cout << "[infile_gmc] " << infile_gmc << std::endl;
  std::cout << c_gmc->Add(infile_gmc)  << " files, ";
  std::cout << nstream_gmc             << " streams, ";
  std::cout << c_gmc->GetEntries()     << " entries -> ";

  TTree* c_gmc_cut = c_gmc->CopyTree( sTmp.str().c_str() );
  std::cout << c_gmc_cut->GetEntries() << " entries"
	    << std::endl;
      
  TChain* c_dststmc = new TChain(treename);
  std::cout << "[infile_dststmc] " << infile_dststmc << std::endl;
  std::cout << c_dststmc->Add(infile_dststmc) << " files, ";
  std::cout << nstream_dststmc                << " streams, ";
  std::cout << c_dststmc->GetEntries()        << " entries -> ";
  
  TTree* c_dststmc_cut = c_dststmc->CopyTree( sTmp.str().c_str() );
  std::cout << c_dststmc_cut->GetEntries() << " entries"
	    << std::endl;
  
  TChain* c_npmc = new TChain(treename);
  std::cout << "[infile_npmc] " << Form(infile_npmc,"0p0") << std::endl;
  std::cout << c_npmc->Add(Form(infile_npmc,"0p0"))        << " files, ";
  std::cout << nstream_npmc                                << " streams, ";
  std::cout << c_npmc->GetEntries()                        << " entries -> ";

  TTree* c_npmc_cut = c_npmc->CopyTree( sTmp.str().c_str() );
  std::cout << c_npmc_cut->GetEntries() << " entries"
	    << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TFile file_deltam1( Form("../ana_double_sideband/pdf/deltam/dm1_%d.root",fl_dec) );
  TFile file_deltam2(      "../ana_double_sideband/pdf/deltam/dm1_421.root"         );
  if( file_deltam1.IsZombie() ) std::cerr << "[ABORT] can not find input-file for deltam1-PDF" << std::endl, abort();
  if( file_deltam2.IsZombie() ) std::cerr << "[ABORT] can not find input-file for deltam2-PDF" << std::endl, abort();
  TF1* hz_deltam1_func_pdf_dt = (TF1*)file_deltam1.Get( Form("func_sig_dt_%d",fl_dec) );
  TF1* hz_deltam2_func_pdf_dt = (TF1*)file_deltam2.Get(      "func_sig_dt_421"        );
  TF1* hz_deltam1_func_pdf_mc = (TF1*)file_deltam1.Get( Form("func_sig_mc_%d",fl_dec) );
  TF1* hz_deltam2_func_pdf_mc = (TF1*)file_deltam2.Get(      "func_sig_mc_421"        );

  const Int_t sel_fun = 40000;
  TF1* deltam1_func_pdf_dt = new TF1( "deltam1_func_sig_dt", make_func(sel_fun), deltam_xmin[0], deltam_xmax[0], n_fitfunc_par(sel_fun) );
  TF1* deltam2_func_pdf_dt = new TF1( "deltam2_func_sig_dt", make_func(sel_fun), deltam_xmin[1], deltam_xmax[1], n_fitfunc_par(sel_fun) );
  TF1* deltam1_func_pdf_mc = new TF1( "deltam1_func_sig_mc", make_func(sel_fun), deltam_xmin[0], deltam_xmax[0], n_fitfunc_par(sel_fun) );
  TF1* deltam2_func_pdf_mc = new TF1( "deltam2_func_sig_mc", make_func(sel_fun), deltam_xmin[1], deltam_xmax[1], n_fitfunc_par(sel_fun) );
  if( deltam1_func_pdf_dt->GetNpar() != hz_deltam1_func_pdf_dt->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for Deltam1(dt)" << std::endl, abort();
  if( deltam2_func_pdf_dt->GetNpar() != hz_deltam2_func_pdf_dt->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for Deltam1(dt)" << std::endl, abort();
  if( deltam1_func_pdf_mc->GetNpar() != hz_deltam1_func_pdf_mc->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for Deltam1(mc)" << std::endl, abort();
  if( deltam2_func_pdf_mc->GetNpar() != hz_deltam2_func_pdf_mc->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for Deltam1(mc)" << std::endl, abort();
  for( Int_t i=0; i<n_fitfunc_par(sel_fun); i++ ) deltam1_func_pdf_dt->SetParameter(i, hz_deltam1_func_pdf_dt->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun); i++ ) deltam2_func_pdf_dt->SetParameter(i, hz_deltam2_func_pdf_dt->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun); i++ ) deltam1_func_pdf_mc->SetParameter(i, hz_deltam1_func_pdf_mc->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun); i++ ) deltam2_func_pdf_mc->SetParameter(i, hz_deltam2_func_pdf_mc->GetParameter(i));
  //deltam1_func_pdf_mc->SetParameter( 2, 1.10*hz_deltam1_func_pdf_mc->GetParameter(2) ); // tmppppppp
  //deltam2_func_pdf_mc->SetParameter( 2, 1.10*hz_deltam2_func_pdf_mc->GetParameter(2) ); // tmppppppp
  deltam1_func_pdf_dt->SetParameter( 3, (hz_deltam1_func_pdf_mc->GetParameter(3)+hz_deltam1_func_pdf_dt->GetParameter(3))/2.0);
  deltam2_func_pdf_dt->SetParameter( 3, (hz_deltam2_func_pdf_mc->GetParameter(3)+hz_deltam2_func_pdf_dt->GetParameter(3))/2.0);

  
  deltam1_func_pdf_dt->Print();
  deltam2_func_pdf_dt->Print();
  deltam1_func_pdf_mc->Print();
  deltam2_func_pdf_mc->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooRealVar* deltam1 = new RooRealVar( "dm1",  "#Deltam_{1} [GeV]", deltam_xmin[0], deltam_xmax[0] );
  RooRealVar* deltam2 = new RooRealVar( "dm2",  "#Deltam_{2} [GeV]", deltam_xmin[1], deltam_xmax[1] );
  RooRealVar* w       = new RooRealVar( "w",    "w",                 0.0,      10.0 ); // weight
  RooArgSet*  varset = new RooArgSet ( *deltam1, *deltam2     );
  RooArgSet*  varsetw = new RooArgSet( *deltam1, *deltam2, *w );
  
  TF1* deltam1_func_sig_s1s2_dt = (TF1*)deltam1_func_pdf_dt->Clone(); deltam1_func_sig_s1s2_dt->SetName("deltam1_s1s2_dt"); RooAbsPdf* deltam1_pdf_sig_s1s2_dt = bindPdf( deltam1_func_sig_s1s2_dt, *deltam1 );
  TF1* deltam1_func_sig_s1b2_dt = (TF1*)deltam1_func_pdf_dt->Clone(); deltam1_func_sig_s1b2_dt->SetName("deltam1_s1b2_dt"); RooAbsPdf* deltam1_pdf_sig_s1b2_dt = bindPdf( deltam1_func_sig_s1b2_dt, *deltam1 );
  TF1* deltam2_func_sig_s1s2_dt = (TF1*)deltam2_func_pdf_dt->Clone(); deltam2_func_sig_s1s2_dt->SetName("deltam2_s1s2_dt"); RooAbsPdf* deltam2_pdf_sig_s1s2_dt = bindPdf( deltam2_func_sig_s1s2_dt, *deltam2 );
  TF1* deltam2_func_sig_b1s2_dt = (TF1*)deltam2_func_pdf_dt->Clone(); deltam2_func_sig_b1s2_dt->SetName("deltam2_b1s2_dt"); RooAbsPdf* deltam2_pdf_sig_b1s2_dt = bindPdf( deltam2_func_sig_b1s2_dt, *deltam2 );

  RooAbsPdf*  deltam1_pdf_bkg_b1s2_dt = ( fl_slowpi[0] ? bindPdf( "deltam1_bkg_b1s2_dt", func_deltam_threshold_slowpip, *deltam1 ) : bindPdf( "deltam1_bkg_b1s2_dt", func_deltam_threshold_slowpi0, *deltam1 ) );
  RooAbsPdf*  deltam2_pdf_bkg_s1b2_dt = ( fl_slowpi[1] ? bindPdf( "deltam2_bkg_s1b2_dt", func_deltam_threshold_slowpip, *deltam2 ) : bindPdf( "deltam2_bkg_s1b2_dt", func_deltam_threshold_slowpi0, *deltam2 ) );
  RooAbsPdf*  deltam1_pdf_bkg_b1b2_dt = ( fl_slowpi[0] ? bindPdf( "deltam1_bkg_b1b2_dt", func_deltam_threshold_slowpip, *deltam1 ) : bindPdf( "deltam1_bkg_b1b2_dt", func_deltam_threshold_slowpi0, *deltam1 ) );
  RooAbsPdf*  deltam2_pdf_bkg_b1b2_dt = ( fl_slowpi[1] ? bindPdf( "deltam2_bkg_b1b2_dt", func_deltam_threshold_slowpip, *deltam2 ) : bindPdf( "deltam2_bkg_b1b2_dt", func_deltam_threshold_slowpi0, *deltam2 ) );

  RooProdPdf* deltam_pdf_s1s2_dt = new RooProdPdf( "deltam_pdf_s1s2_dt", "deltam_pdf_s1s2_dt", RooArgSet( *deltam1_pdf_sig_s1s2_dt, *deltam2_pdf_sig_s1s2_dt) );
  RooProdPdf* deltam_pdf_s1b2_dt = new RooProdPdf( "deltam_pdf_s1b2_dt", "deltam_pdf_s1b2_dt", RooArgSet( *deltam1_pdf_sig_s1b2_dt, *deltam2_pdf_bkg_s1b2_dt) );
  RooProdPdf* deltam_pdf_b1s2_dt = new RooProdPdf( "deltam_pdf_b1s2_dt", "deltam_pdf_b1s2_dt", RooArgSet( *deltam1_pdf_bkg_b1s2_dt, *deltam2_pdf_sig_b1s2_dt) );
  RooProdPdf* deltam_pdf_b1b2_dt = new RooProdPdf( "deltam_pdf_b1b2_dt", "deltam_pdf_b1b2_dt", RooArgSet( *deltam1_pdf_bkg_b1b2_dt, *deltam2_pdf_bkg_b1b2_dt) );

  TF1* deltam1_func_sig_s1s2_mc = (TF1*)deltam1_func_pdf_mc->Clone(); deltam1_func_sig_s1s2_mc->SetName("deltam1_s1s2_mc"); RooAbsPdf* deltam1_pdf_sig_s1s2_mc = bindPdf( deltam1_func_sig_s1s2_mc, *deltam1 );
  TF1* deltam1_func_sig_s1b2_mc = (TF1*)deltam1_func_pdf_mc->Clone(); deltam1_func_sig_s1b2_mc->SetName("deltam1_s1b2_mc"); RooAbsPdf* deltam1_pdf_sig_s1b2_mc = bindPdf( deltam1_func_sig_s1b2_mc, *deltam1 );
  TF1* deltam2_func_sig_s1s2_mc = (TF1*)deltam2_func_pdf_mc->Clone(); deltam2_func_sig_s1s2_mc->SetName("deltam2_s1s2_mc"); RooAbsPdf* deltam2_pdf_sig_s1s2_mc = bindPdf( deltam2_func_sig_s1s2_mc, *deltam2 );
  TF1* deltam2_func_sig_b1s2_mc = (TF1*)deltam2_func_pdf_mc->Clone(); deltam2_func_sig_b1s2_mc->SetName("deltam2_b1s2_mc"); RooAbsPdf* deltam2_pdf_sig_b1s2_mc = bindPdf( deltam2_func_sig_b1s2_mc, *deltam2 );

  RooAbsPdf*  deltam1_pdf_bkg_b1s2_mc = ( fl_slowpi[0] ? bindPdf( "deltam1_bkg_b1s2_mc", func_deltam_threshold_slowpip, *deltam1 ) : bindPdf( "deltam1_bkg_b1s2_mc", func_deltam_threshold_slowpi0, *deltam1 ) );
  RooAbsPdf*  deltam2_pdf_bkg_s1b2_mc = ( fl_slowpi[1] ? bindPdf( "deltam2_bkg_s1b2_mc", func_deltam_threshold_slowpip, *deltam2 ) : bindPdf( "deltam2_bkg_s1b2_mc", func_deltam_threshold_slowpi0, *deltam2 ) );
  RooAbsPdf*  deltam1_pdf_bkg_b1b2_mc = ( fl_slowpi[0] ? bindPdf( "deltam1_bkg_b1b2_mc", func_deltam_threshold_slowpip, *deltam1 ) : bindPdf( "deltam1_bkg_b1b2_mc", func_deltam_threshold_slowpi0, *deltam1 ) );
  RooAbsPdf*  deltam2_pdf_bkg_b1b2_mc = ( fl_slowpi[1] ? bindPdf( "deltam2_bkg_b1b2_mc", func_deltam_threshold_slowpip, *deltam2 ) : bindPdf( "deltam2_bkg_b1b2_mc", func_deltam_threshold_slowpi0, *deltam2 ) );

  RooProdPdf* deltam_pdf_s1s2_mc = new RooProdPdf( "deltam_pdf_s1s2_mc", "deltam_pdf_s1s2_mc", RooArgSet( *deltam1_pdf_sig_s1s2_mc, *deltam2_pdf_sig_s1s2_mc) );
  RooProdPdf* deltam_pdf_s1b2_mc = new RooProdPdf( "deltam_pdf_s1b2_mc", "deltam_pdf_s1b2_mc", RooArgSet( *deltam1_pdf_sig_s1b2_mc, *deltam2_pdf_bkg_s1b2_mc) );
  RooProdPdf* deltam_pdf_b1s2_mc = new RooProdPdf( "deltam_pdf_b1s2_mc", "deltam_pdf_b1s2_mc", RooArgSet( *deltam1_pdf_bkg_b1s2_mc, *deltam2_pdf_sig_b1s2_mc) );
  RooProdPdf* deltam_pdf_b1b2_mc = new RooProdPdf( "deltam_pdf_b1b2_mc", "deltam_pdf_b1b2_mc", RooArgSet( *deltam1_pdf_bkg_b1b2_mc, *deltam2_pdf_bkg_b1b2_mc) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooDataSet* deltam_roohist_dt = new RooDataSet( "deltam_roohist_dt", "deltam_roohist_dt", *varset );
  RooDataSet* deltam_roohist_mc = new RooDataSet( "deltam_roohist_mc", "deltam_roohist_mc", *varsetw, WeightVar("w") );
  TH2D*       deltam_hist_dt    = new TH2D      ( "deltam_hist_dt",    "deltam_hist_dt",    deltam_xbin[0],deltam_xmin[0],deltam_xmax[0], deltam_xbin[1],deltam_xmin[1],deltam_xmax[1] );
  TH2D*       deltam_hist_mc    = new TH2D      ( "deltam_hist_mc",    "deltam_hist_mc",    deltam_xbin[0],deltam_xmin[0],deltam_xmax[0], deltam_xbin[1],deltam_xmin[1],deltam_xmax[1] );

  inputEvent_dt( c_dt_cut,      deltam_roohist_dt, deltam_hist_dt, deltam1, deltam2, fl_dec );
  inputEvent_mc( c_gmc_cut,     deltam_roohist_mc, deltam_hist_mc, deltam1, deltam2, fl_dec, nstream_gmc     );
  inputEvent_mc( c_dststmc_cut, deltam_roohist_mc, deltam_hist_mc, deltam1, deltam2, fl_dec, nstream_dststmc );
  inputEvent_mc( c_npmc_cut,    deltam_roohist_mc, deltam_hist_mc, deltam1, deltam2, fl_dec, nstream_npmc    );

  deltam_roohist_dt->Print();
  deltam_roohist_mc->Print();
  deltam_hist_dt   ->Print();
  deltam_hist_mc   ->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Setting for delta m>
  Double_t deltam_range[2] = { (fl_slowpi[0] ? 0.0025 : 0.0020),
			       (fl_slowpi[1] ? 0.0025 : 0.0020)
  };
  deltam1->setRange( "deltam1_cutrange", nominal_deltam[0]-deltam_range[0], nominal_deltam[0]+deltam_range[0] );
  deltam2->setRange( "deltam2_cutrange", nominal_deltam[1]-deltam_range[1], nominal_deltam[1]+deltam_range[1] );
  deltam1->setRange( "deltam_sigrange",  nominal_deltam[0]-deltam_range[0], nominal_deltam[0]+deltam_range[0] );
  deltam2->setRange( "deltam_sigrange",  nominal_deltam[1]-deltam_range[1], nominal_deltam[1]+deltam_range[1] );
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Double_t deltam_init_s1s2 = 0.7*deltam_hist_dt->Integral();
  Double_t deltam_init_s1b2 = 0.1*deltam_hist_dt->Integral();
  Double_t deltam_init_b1s2 = 0.1*deltam_hist_dt->Integral();
  Double_t deltam_init_b1b2 = 0.1*deltam_hist_dt->Integral();

  RooRealVar* deltam_s1s2_dt = new RooRealVar( "N_{s1s2,deltam,dt}", "N_{s1s2,deltam,dt}", deltam_init_s1s2, -50.0, 1.5*deltam_init_s1s2 );
  RooRealVar* deltam_s1b2_dt = new RooRealVar( "N_{s1b2,deltam,dt}", "N_{s1b2,deltam,dt}", deltam_init_s1b2, -50.0, 10.0*deltam_init_s1b2 );
  RooRealVar* deltam_b1s2_dt = new RooRealVar( "N_{b1s2,deltam,dt}", "N_{b1s2,deltam,dt}", deltam_init_b1s2, -50.0, 10.0*deltam_init_b1s2 );
  RooRealVar* deltam_b1b2_dt = new RooRealVar( "N_{b1b2,deltam,dt}", "N_{b1b2,deltam,dt}", deltam_init_b1b2, -50.0, 10.0*deltam_init_b1b2 );

  RooRealVar* deltam_s1s2_mc = new RooRealVar( "N_{s1s2,deltam,mc}", "N_{s1s2,deltam,mc}", deltam_init_s1s2, -50.0, 1.5*deltam_init_s1s2 );
  RooRealVar* deltam_s1b2_mc = new RooRealVar( "N_{s1b2,deltam,mc}", "N_{s1b2,deltam,mc}", deltam_init_s1b2, -50.0, 10.0*deltam_init_s1b2 );
  RooRealVar* deltam_b1s2_mc = new RooRealVar( "N_{b1s2,deltam,mc}", "N_{b1s2,deltam,mc}", deltam_init_b1s2, -50.0, 10.0*deltam_init_b1s2 );
  RooRealVar* deltam_b1b2_mc = new RooRealVar( "N_{b1b2,deltam,mc}", "N_{b1b2,deltam,mc}", deltam_init_b1b2, -50.0, 10.0*deltam_init_b1b2 );

  RooAddPdf*  deltam_pdf_dt  = new RooAddPdf ( "deltam_pdf_dt", "deltam_pdf_dt", RooArgList(*deltam_pdf_s1s2_dt, *deltam_pdf_s1b2_dt, *deltam_pdf_b1s2_dt, *deltam_pdf_b1b2_dt), RooArgList(*deltam_s1s2_dt, *deltam_s1b2_dt, *deltam_b1s2_dt, *deltam_b1b2_dt) );
  RooAddPdf*  deltam_pdf_mc  = new RooAddPdf ( "deltam_pdf_mc", "deltam_pdf_mc", RooArgList(*deltam_pdf_s1s2_mc, *deltam_pdf_s1b2_mc, *deltam_pdf_b1s2_mc, *deltam_pdf_b1b2_mc), RooArgList(*deltam_s1s2_mc, *deltam_s1b2_mc, *deltam_b1s2_mc, *deltam_b1b2_mc) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooFitResult* deltam_fit_result_dt = deltam_pdf_dt->fitTo( *deltam_roohist_dt, Extended(), Save(true), SumW2Error(true) );
  RooFitResult* deltam_fit_result_mc = deltam_pdf_mc->fitTo( *deltam_roohist_mc, Extended(), Save(true), SumW2Error(true) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 3, 2 );
  can->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* deltam1_frame_dt = deltam1->frame();
  deltam1_frame_dt->GetXaxis()->CenterTitle();
  deltam1_frame_dt->GetYaxis()->CenterTitle();
  deltam1_frame_dt->SetTitleOffset( 1.00,"x" );
  deltam1_frame_dt->SetTitleOffset( 1.25,"y" );
  deltam1_frame_dt->SetTitle( Form("dec(%d) : data",fl_dec) );

  Double_t ymax_deltam1_dt = deltam_roohist_dt->plotOn( deltam1_frame_dt, Binning(deltam_xbin[0]), CutRange("deltam2_cutrange"), MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  deltam_pdf_dt->plotOn( deltam1_frame_dt, ProjectionRange("deltam2_cutrange"),                                  LineStyle(1), LineColor(3), LineWidth(2) );
  deltam_pdf_dt->plotOn( deltam1_frame_dt, ProjectionRange("deltam2_cutrange"), Components(*deltam_pdf_s1s2_dt), LineStyle(1), LineColor(2), LineWidth(1) );
  deltam_pdf_dt->plotOn( deltam1_frame_dt, ProjectionRange("deltam2_cutrange"), Components(*deltam_pdf_s1b2_dt), LineStyle(1), LineColor(4), LineWidth(1) );
  deltam_pdf_dt->plotOn( deltam1_frame_dt, ProjectionRange("deltam2_cutrange"), Components(*deltam_pdf_b1s2_dt), LineStyle(2), LineColor(5), LineWidth(1) );
  deltam_pdf_dt->plotOn( deltam1_frame_dt, ProjectionRange("deltam2_cutrange"), Components(*deltam_pdf_b1b2_dt), LineStyle(2), LineColor(6), LineWidth(1) );

  deltam_pdf_dt->paramOn( deltam1_frame_dt, Format("NELU", AutoPrecision(2)), Layout(0.50, 0.95, 0.95), ShowConstants(kFALSE) );


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* deltam2_frame_dt = deltam2->frame();
  deltam2_frame_dt->GetXaxis()->CenterTitle();
  deltam2_frame_dt->GetYaxis()->CenterTitle();
  deltam2_frame_dt->SetTitleOffset( 1.00,"x" );
  deltam2_frame_dt->SetTitleOffset( 1.25,"y" );
  deltam2_frame_dt->SetTitle( Form("dec(%d) : data",fl_dec) );

  Double_t ymax_deltam2_dt = deltam_roohist_dt->plotOn( deltam2_frame_dt, Binning(deltam_xbin[1]), CutRange("deltam1_cutrange"), MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  deltam_pdf_dt->plotOn( deltam2_frame_dt, ProjectionRange("deltam1_cutrange"),                                  LineStyle(1), LineColor(3), LineWidth(2) );
  deltam_pdf_dt->plotOn( deltam2_frame_dt, ProjectionRange("deltam1_cutrange"), Components(*deltam_pdf_s1s2_dt), LineStyle(1), LineColor(2), LineWidth(1) );
  deltam_pdf_dt->plotOn( deltam2_frame_dt, ProjectionRange("deltam1_cutrange"), Components(*deltam_pdf_s1b2_dt), LineStyle(1), LineColor(4), LineWidth(1) );
  deltam_pdf_dt->plotOn( deltam2_frame_dt, ProjectionRange("deltam1_cutrange"), Components(*deltam_pdf_b1s2_dt), LineStyle(2), LineColor(5), LineWidth(1) );
  deltam_pdf_dt->plotOn( deltam2_frame_dt, ProjectionRange("deltam1_cutrange"), Components(*deltam_pdf_b1b2_dt), LineStyle(2), LineColor(6), LineWidth(1) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* deltam1_frame_mc = deltam1->frame();
  deltam1_frame_mc->GetXaxis()->CenterTitle();
  deltam1_frame_mc->GetYaxis()->CenterTitle();
  deltam1_frame_mc->SetTitleOffset( 1.00,"x" );
  deltam1_frame_mc->SetTitleOffset( 1.25,"y" );
  deltam1_frame_mc->SetTitle( Form("dec(%d) : mc",fl_dec) );

  Double_t ymax_deltam1_mc = deltam_roohist_mc->plotOn( deltam1_frame_mc, Binning(deltam_xbin[0]), CutRange("deltam2_cutrange"), MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  deltam_pdf_mc->plotOn( deltam1_frame_mc, ProjectionRange("deltam2_cutrange"),                                  LineStyle(1), LineColor(3), LineWidth(2) );
  deltam_pdf_mc->plotOn( deltam1_frame_mc, ProjectionRange("deltam2_cutrange"), Components(*deltam_pdf_s1s2_mc), LineStyle(1), LineColor(2), LineWidth(1) );
  deltam_pdf_mc->plotOn( deltam1_frame_mc, ProjectionRange("deltam2_cutrange"), Components(*deltam_pdf_s1b2_mc), LineStyle(1), LineColor(4), LineWidth(1) );
  deltam_pdf_mc->plotOn( deltam1_frame_mc, ProjectionRange("deltam2_cutrange"), Components(*deltam_pdf_b1s2_mc), LineStyle(2), LineColor(5), LineWidth(1) );
  deltam_pdf_mc->plotOn( deltam1_frame_mc, ProjectionRange("deltam2_cutrange"), Components(*deltam_pdf_b1b2_mc), LineStyle(2), LineColor(6), LineWidth(1) );

  deltam_pdf_mc->paramOn( deltam1_frame_mc, Format("NELU", AutoPrecision(2)), Layout(0.50, 0.95, 0.95), ShowConstants(kFALSE) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* deltam2_frame_mc = deltam2->frame();
  deltam2_frame_mc->GetXaxis()->CenterTitle();
  deltam2_frame_mc->GetYaxis()->CenterTitle();
  deltam2_frame_mc->SetTitleOffset( 1.00,"x" );
  deltam2_frame_mc->SetTitleOffset( 1.25,"y" );
  deltam2_frame_mc->SetTitle( Form("dec(%d) : mc",fl_dec) );

  Double_t ymax_deltam2_mc = deltam_roohist_mc->plotOn( deltam2_frame_mc, Binning(deltam_xbin[1]), CutRange("deltam1_cutrange"), MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  deltam_pdf_mc->plotOn( deltam2_frame_mc, ProjectionRange("deltam1_cutrange"),                                  LineStyle(1), LineColor(3), LineWidth(2) );
  deltam_pdf_mc->plotOn( deltam2_frame_mc, ProjectionRange("deltam1_cutrange"), Components(*deltam_pdf_s1s2_mc), LineStyle(1), LineColor(2), LineWidth(1) );
  deltam_pdf_mc->plotOn( deltam2_frame_mc, ProjectionRange("deltam1_cutrange"), Components(*deltam_pdf_s1b2_mc), LineStyle(1), LineColor(4), LineWidth(1) );
  deltam_pdf_mc->plotOn( deltam2_frame_mc, ProjectionRange("deltam1_cutrange"), Components(*deltam_pdf_b1s2_mc), LineStyle(2), LineColor(5), LineWidth(1) );
  deltam_pdf_mc->plotOn( deltam2_frame_mc, ProjectionRange("deltam1_cutrange"), Components(*deltam_pdf_b1b2_mc), LineStyle(2), LineColor(6), LineWidth(1) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  can->cd(1); deltam1_frame_dt->Draw();
  can->cd(2); deltam2_frame_dt->Draw();
  can->cd(3); deltam_hist_dt->Draw("COLZ");
  can->cd(4); deltam1_frame_mc->Draw();
  can->cd(5); deltam2_frame_mc->Draw();
  can->cd(6); deltam_hist_mc->Draw("COLZ");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  Double_t nevt_s1s2_dt  = deltam_pdf_s1s2_dt->createIntegral( RooArgSet(*deltam1,*deltam2), NormSet(RooArgSet(*deltam1,*deltam2)), Range("deltam_sigrange") )->getVal()*deltam_s1s2_dt->getVal();
  Double_t nevt_s1b2_dt  = deltam_pdf_s1b2_dt->createIntegral( RooArgSet(*deltam1,*deltam2), NormSet(RooArgSet(*deltam1,*deltam2)), Range("deltam_sigrange") )->getVal()*deltam_s1b2_dt->getVal();
  Double_t nevt_b1s2_dt  = deltam_pdf_b1s2_dt->createIntegral( RooArgSet(*deltam1,*deltam2), NormSet(RooArgSet(*deltam1,*deltam2)), Range("deltam_sigrange") )->getVal()*deltam_b1s2_dt->getVal();
  Double_t nevt_b1b2_dt  = deltam_pdf_b1b2_dt->createIntegral( RooArgSet(*deltam1,*deltam2), NormSet(RooArgSet(*deltam1,*deltam2)), Range("deltam_sigrange") )->getVal()*deltam_b1b2_dt->getVal();
  Double_t nevtE_s1s2_dt = nevt_s1s2_dt * ( deltam_s1s2_dt->getError() / deltam_s1s2_dt->getVal() );
  Double_t nevtE_s1b2_dt = nevt_s1b2_dt * ( deltam_s1b2_dt->getError() / deltam_s1b2_dt->getVal() );
  Double_t nevtE_b1s2_dt = nevt_b1s2_dt * ( deltam_b1s2_dt->getError() / deltam_b1s2_dt->getVal() );
  Double_t nevtE_b1b2_dt = nevt_b1b2_dt * ( deltam_b1b2_dt->getError() / deltam_b1b2_dt->getVal() );
  std::cout << "[DATA][# of Events in signal region]" << std::endl
	    << "    N(s1s2) = " << nevt_s1s2_dt << " +- " << nevtE_s1s2_dt << std::endl
	    << "    N(s1b2) = " << nevt_s1b2_dt << " +- " << nevtE_s1b2_dt << std::endl
	    << "    N(b1s2) = " << nevt_b1s2_dt << " +- " << nevtE_b1s2_dt << std::endl
	    << "    N(b1b2) = " << nevt_b1b2_dt << " +- " << nevtE_b1b2_dt << std::endl;

  Double_t nfake_dt  = nevt_s1b2_dt + nevt_b1s2_dt + nevt_b1b2_dt;
  Double_t corr_s1b2_b1b2_dt = deltam_fit_result_dt->correlation( *deltam_s1b2_dt, *deltam_b1b2_dt );
  Double_t corr_b1s2_b1b2_dt = deltam_fit_result_dt->correlation( *deltam_b1s2_dt, *deltam_b1b2_dt );
  Double_t corr_s1b2_b1s2_dt = deltam_fit_result_dt->correlation( *deltam_s1b2_dt, *deltam_b1s2_dt );
  Double_t nfakeE_dt = sqrt(
			 pow(nevtE_s1b2_dt,2) + pow(nevtE_b1s2_dt,2) + pow(nevtE_b1b2_dt,2)
			 + 2 * nevtE_s1b2_dt * nevtE_b1b2_dt * corr_s1b2_b1b2_dt
			 + 2 * nevtE_b1s2_dt * nevtE_b1b2_dt * corr_b1s2_b1b2_dt
			 + 2 * nevtE_s1b2_dt * nevtE_b1s2_dt * corr_s1b2_b1s2_dt
			 );
  std::cout << "    -> Correct D(*) : " << nevt_s1s2_dt << " +- " << nevtE_s1s2_dt << std::endl;
  std::cout << "    ->   Fake  D(*) : " << nfake_dt     << " +- " << nfakeE_dt     << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  Double_t nevt_s1s2_mc  = deltam_pdf_s1s2_mc->createIntegral( RooArgSet(*deltam1,*deltam2), NormSet(RooArgSet(*deltam1,*deltam2)), Range("deltam_sigrange") )->getVal()*deltam_s1s2_mc->getVal();
  Double_t nevt_s1b2_mc  = deltam_pdf_s1b2_mc->createIntegral( RooArgSet(*deltam1,*deltam2), NormSet(RooArgSet(*deltam1,*deltam2)), Range("deltam_sigrange") )->getVal()*deltam_s1b2_mc->getVal();
  Double_t nevt_b1s2_mc  = deltam_pdf_b1s2_mc->createIntegral( RooArgSet(*deltam1,*deltam2), NormSet(RooArgSet(*deltam1,*deltam2)), Range("deltam_sigrange") )->getVal()*deltam_b1s2_mc->getVal();
  Double_t nevt_b1b2_mc  = deltam_pdf_b1b2_mc->createIntegral( RooArgSet(*deltam1,*deltam2), NormSet(RooArgSet(*deltam1,*deltam2)), Range("deltam_sigrange") )->getVal()*deltam_b1b2_mc->getVal();
  Double_t nevtE_s1s2_mc = nevt_s1s2_mc * ( deltam_s1s2_mc->getError() / deltam_s1s2_mc->getVal() );
  Double_t nevtE_s1b2_mc = nevt_s1b2_mc * ( deltam_s1b2_mc->getError() / deltam_s1b2_mc->getVal() );
  Double_t nevtE_b1s2_mc = nevt_b1s2_mc * ( deltam_b1s2_mc->getError() / deltam_b1s2_mc->getVal() );
  Double_t nevtE_b1b2_mc = nevt_b1b2_mc * ( deltam_b1b2_mc->getError() / deltam_b1b2_mc->getVal() );
  std::cout << "[MC][# of Events in signal region]" << std::endl
	    << "    N(s1s2) = " << nevt_s1s2_mc << " +- " << nevtE_s1s2_mc << std::endl
	    << "    N(s1b2) = " << nevt_s1b2_mc << " +- " << nevtE_s1b2_mc << std::endl
	    << "    N(b1s2) = " << nevt_b1s2_mc << " +- " << nevtE_b1s2_mc << std::endl
	    << "    N(b1b2) = " << nevt_b1b2_mc << " +- " << nevtE_b1b2_mc << std::endl;

  Double_t nfake_mc  = nevt_s1b2_mc + nevt_b1s2_mc + nevt_b1b2_mc;
  Double_t corr_s1b2_b1b2_mc = deltam_fit_result_mc->correlation( *deltam_s1b2_mc, *deltam_b1b2_mc );
  Double_t corr_b1s2_b1b2_mc = deltam_fit_result_mc->correlation( *deltam_b1s2_mc, *deltam_b1b2_mc );
  Double_t corr_s1b2_b1s2_mc = deltam_fit_result_mc->correlation( *deltam_s1b2_mc, *deltam_b1s2_mc );
  Double_t nfakeE_mc = sqrt(
			 pow(nevtE_s1b2_mc,2) + pow(nevtE_b1s2_mc,2) + pow(nevtE_b1b2_mc,2)
			 + 2 * nevtE_s1b2_mc * nevtE_b1b2_mc * corr_s1b2_b1b2_mc
			 + 2 * nevtE_b1s2_mc * nevtE_b1b2_mc * corr_b1s2_b1b2_mc
			 + 2 * nevtE_s1b2_mc * nevtE_b1s2_mc * corr_s1b2_b1s2_mc
			 );
  std::cout << "    -> Correct D(*) : " << nevt_s1s2_mc << " +- " << nevtE_s1s2_mc << std::endl;
  std::cout << "    ->   Fake  D(*) : " << nfake_mc     << " +- " << nfakeE_mc     << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Print( Form("pic/fit_deltam_2d_%d.eps",fl_dec) );
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
