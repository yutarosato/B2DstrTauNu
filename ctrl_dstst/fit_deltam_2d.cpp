#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

Double_t cnt_mc_s1s2 = 0.0;
Double_t cnt_mc_s1b2 = 0.0;
Double_t cnt_mc_b1s2 = 0.0;
Double_t cnt_mc_b1b2 = 0.0;
Double_t cnt_mc_s1s2_sig = 0.0;
Double_t cnt_mc_s1b2_sig = 0.0;
Double_t cnt_mc_b1s2_sig = 0.0;
Double_t cnt_mc_b1b2_sig = 0.0;

Int_t    deltam_xbin[2]  = {55,55};
//Int_t    deltam_xbin[2]  = {55,110}; // tmpppp
Double_t deltam_xmin[2]  = {PDGmass::pip,PDGmass::pip};
Double_t deltam_th  [2]  = {PDGmass::pip,PDGmass::pip};
Double_t deltam_xmax[2]  = {       0.150,       0.150};

Double_t nominal_deltam[2];
Double_t deltam_range  [2];

///*
const Int_t    fl_ratio_fixed  = 1; // 1(fix only ratio), 2(fix both ratio and value)
//const Int_t    fl_ratio_fixed  = 1;
//const Int_t    fl_ratio_fixed  = 2;
const Char_t*  selection       = "eecl<1.2";
//const Char_t*  selection       = "eecl<1.2 && nb_mode0_test13_nor > 0.0";
//const Char_t*  selection       = "eecl > 0.6 && eecl<1.2 && nb_mode0_test13_nor > 0.0";
const Char_t*  infile_dt       = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_nodmcut/RD_*.root";
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_nodmcut/gMC_*s0[0-9]*.root";
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_nodmcut/DssMC_*.root";
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/%s_weight_nb_nodmcut/npMC_*s0*.root";
//*/
/*
const Int_t    fl_ratio_fixed  = 1; // 1(fix only ratio), 2(fix both ratio and value)
//const Int_t    fl_ratio_fixed  = 2;
//const Char_t*  selection       = "eecl_exp<1.2 && nb_mode0_test13_nor<0.0 && (rempi0_1==1 && remks==0 && remtrk==0)";
const Char_t*  selection       = "eecl_exp<1.2 && (rempi0_1==1 && remks==0 && remtrk==0)";
//const Char_t*  selection       = "nb_mode0_test13_nor>0.8 && eecl_exp<0.2 && (rempi0_1==1 && remks==0 && remtrk==0)";
//const Char_t*  selection       = "nb_mode0_test13_nor>0.0 && nb_mode0_test13_nor<0.8 && eecl_exp<0.2 && (rempi0_1==1 && remks==0 && remtrk==0)";
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
void inputEvent_dt( TTree* tree, RooDataSet* data, TH2D* hist, TH1D* hist1, TH1D* hist2, RooRealVar* deltam1, RooRealVar* deltam2,
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
    hist ->Fill( deltam1->getVal(), deltam2->getVal() );
    hist1->Fill( deltam1->getVal()                    );
    hist2->Fill( deltam2->getVal()                    );
  }
  return;
}

void inputEvent_mc( TTree* tree, RooDataSet* data, TH2D* hist, TH1D* hist1, TH1D* hist2, RooRealVar* deltam1, RooRealVar* deltam2,
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

    Bool_t fl_sigregion = !true;
    if( nominal_deltam[0]-deltam_range[0] < deltam1->getVal() && deltam1->getVal() < nominal_deltam[0]+deltam_range[0] &&
	nominal_deltam[1]-deltam_range[1] < deltam2->getVal() && deltam2->getVal() < nominal_deltam[1]+deltam_range[1] ) fl_sigregion = true;

    data->add( RooArgSet(*deltam1,*deltam2), weight );
    hist ->Fill( deltam1->getVal(), deltam2->getVal(), weight );
    if( tree->GetLeaf("dst1self")->GetValue()==1 && tree->GetLeaf("dst2self")->GetValue()==1 ){
      hist1->Fill( deltam1->getVal(),                    weight );
      hist2->Fill( deltam2->getVal(),                    weight );
      cnt_mc_s1s2 += weight;
      if( fl_sigregion ) cnt_mc_s1s2_sig += weight;
    }else if( tree->GetLeaf("dst1self")->GetValue()!=1 && tree->GetLeaf("dst2self")->GetValue()==1 ){
      if( tmp_d2_lun==411 ){
	cnt_mc_s1b2 += weight;
	if( fl_sigregion ) cnt_mc_s1b2_sig += weight;
      }else{
	cnt_mc_b1s2 += weight;
	if( fl_sigregion ) cnt_mc_b1s2_sig += weight;
      }
    }else if( tree->GetLeaf("dst1self")->GetValue()==1 && tree->GetLeaf("dst2self")->GetValue()!=1 ){
      if( tmp_d2_lun==411 ){
	cnt_mc_b1s2 += weight;
	if( fl_sigregion ) cnt_mc_b1s2_sig += weight;
      }else{
	cnt_mc_s1b2 += weight;
	if( fl_sigregion ) cnt_mc_s1b2_sig += weight;
      }
    }else if( tree->GetLeaf("dst1self")->GetValue()!=1 && tree->GetLeaf("dst2self")->GetValue()!=1 ){
      cnt_mc_b1b2 += weight;
      if( fl_sigregion ) cnt_mc_b1b2_sig += weight;
    }
  }
  return;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void SetFunc( TH1* hist, TF1* func, Double_t threshold, Double_t mean, Double_t sigma ){
  Double_t nsig = 0.1;//hist->GetMaximum()*sqrt( TMath::TwoPi() )*sigma;
  Double_t nbkg = 35;//hist->GetBinContent( hist->GetNbinsX() );

  func->SetParNames  ( "Sig",  "are_ratio1", "area_ratio2", "mean", "sigma",  "sigma_ratio1", "sigma_ratio2", "Bkg", "threshold" );
  func->SetParameters(  nsig,          0.4,            0.1,  mean,   sigma,              0.3,           0.15,  nbkg,  threshold  );
  func->FixParameter( 8, threshold );

  return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// threshold function
// p[0]=norm, p[1]=threshold
Double_t lfunc_threshold( const Double_t* x, const Double_t* p ){
  Double_t f;
  if( x[0]>p[1] ) f = p[0]*pow(x[0]-p[1], 0.5);
  else            f = 0;
  return f;
}

Double_t makeFunc(const Double_t* x, const Double_t*p){
  Double_t f = func_3gauss(x,&p[0]) + lfunc_threshold(x,&p[7]);
  return f;
}

void manip_func( TF1* func ){
  func->FixParameter( 7, func->GetParameter(7) );
  func->FixParameter( 8, func->GetParameter(8) );
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Double_t func_deltam_threshold_slowpip( const Double_t x ){
  Double_t p[3];
  Double_t th = PDGmass::pip;
  Double_t f;
  if( x>th ) f = pow(x-th, 1/2.0); // threshold function in delta-M fitting
  else       f = 0;
  return f;
}

Double_t func_deltam_threshold_slowpi0( const Double_t x ){
  Double_t p[3];
  Double_t th = PDGmass::pi0;
  Double_t f;
  if( x>th ) f = pow(x-th, 1/2.0); // threshold function in delta-M fitting
  else       f = 0;
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
      deltam_xbin[i] *= 1.5; // tmppppp
    }
  }

  nominal_deltam[0] = ( fl_slowpi[0] ? PDGmass::dstrp - PDGmass::d0 : PDGmass::dstrp - PDGmass::dp );
  nominal_deltam[1] = ( fl_slowpi[1] ? PDGmass::dstrp - PDGmass::d0 : PDGmass::dstrp - PDGmass::dp );

  deltam_range[0] = (fl_slowpi[0] ? 0.0025 : 0.0020);
  deltam_range[1] = (fl_slowpi[1] ? 0.0025 : 0.0020);

  Read_Data( calib_file, true );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // Read TTree
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
  TTree* c_dt_cut = c_dt->CopyTree( selection );
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
  // Read Data
  RooRealVar* deltam1 = new RooRealVar( "dm1",  "#Deltam_{1} [GeV]", deltam_xmin[0], deltam_xmax[0] );
  RooRealVar* deltam2 = new RooRealVar( "dm2",  "#Deltam_{2} [GeV]", deltam_xmin[1], deltam_xmax[1] );
  RooRealVar* w       = new RooRealVar( "w",    "w",                 0.0,      10.0 ); // weight
  RooArgSet*  varset = new RooArgSet ( *deltam1, *deltam2     );
  RooArgSet*  varsetw = new RooArgSet( *deltam1, *deltam2, *w );
  
  RooDataSet* deltam_roohist_dt = new RooDataSet( "deltam_roohist_dt", "deltam_roohist_dt", *varset );
  RooDataSet* deltam_roohist_mc = new RooDataSet( "deltam_roohist_mc", "deltam_roohist_mc", *varsetw, WeightVar("w") );
  TH2D*       deltam_hist_dt    = new TH2D      ( "deltam_hist_dt",    "deltam_hist_dt",    deltam_xbin[0],deltam_xmin[0],deltam_xmax[0], deltam_xbin[1],deltam_xmin[1],deltam_xmax[1] );
  TH2D*       deltam_hist_mc    = new TH2D      ( "deltam_hist_mc",    "deltam_hist_mc",    deltam_xbin[0],deltam_xmin[0],deltam_xmax[0], deltam_xbin[1],deltam_xmin[1],deltam_xmax[1] );
  TH1D*       deltam1_hist_dt   = new TH1D      ( "deltam1_hist_dt",   "deltam1_hist_dt",   deltam_xbin[0],deltam_xmin[0],deltam_xmax[0] );
  TH1D*       deltam2_hist_dt   = new TH1D      ( "deltam2_hist_dt",   "deltam2_hist_dt",   deltam_xbin[1],deltam_xmin[1],deltam_xmax[1] );
  TH1D*       deltam1_hist_mc   = new TH1D      ( "deltam1_hist_mc",   "deltam1_hist_mc",   deltam_xbin[0],deltam_xmin[0],deltam_xmax[0] );
  TH1D*       deltam2_hist_mc   = new TH1D      ( "deltam2_hist_mc",   "deltam2_hist_mc",   deltam_xbin[1],deltam_xmin[1],deltam_xmax[1] );

  inputEvent_dt( c_dt_cut,      deltam_roohist_dt, deltam_hist_dt, deltam1_hist_dt, deltam2_hist_dt, deltam1, deltam2, fl_dec );
  inputEvent_mc( c_gmc_cut,     deltam_roohist_mc, deltam_hist_mc, deltam1_hist_mc, deltam2_hist_mc, deltam1, deltam2, fl_dec, nstream_gmc     );
  inputEvent_mc( c_dststmc_cut, deltam_roohist_mc, deltam_hist_mc, deltam1_hist_mc, deltam2_hist_mc, deltam1, deltam2, fl_dec, nstream_dststmc );
  inputEvent_mc( c_npmc_cut,    deltam_roohist_mc, deltam_hist_mc, deltam1_hist_mc, deltam2_hist_mc, deltam1, deltam2, fl_dec, nstream_npmc    );

  deltam_roohist_dt->Print();
  deltam_roohist_mc->Print();
  deltam_hist_dt   ->Print();
  deltam_hist_mc   ->Print();
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can2 = Canvas( "can2","can2", 2, 2 );
  can2->Draw();
  TF1* func1_tot_dt = new TF1( "func1_tot_dt", makeFunc, deltam_xmin[0], deltam_xmax[0], 9 );
  TF1* func2_tot_dt = new TF1( "func2_tot_dt", makeFunc, deltam_xmin[1], deltam_xmax[1], 9 );
  TF1* func1_tot_mc = new TF1( "func1_tot_mc", makeFunc, deltam_xmin[0], deltam_xmax[0], 9 );
  TF1* func2_tot_mc = new TF1( "func2_tot_mc", makeFunc, deltam_xmin[1], deltam_xmax[1], 9 );
  SetFunc( deltam1_hist_dt, func1_tot_dt, deltam_th[0], nominal_deltam[0], 0.001 );
  SetFunc( deltam2_hist_dt, func2_tot_dt, deltam_th[1], nominal_deltam[1], 0.001 );
  SetFunc( deltam1_hist_mc, func1_tot_mc, deltam_th[0], nominal_deltam[0], 0.001 );
  SetFunc( deltam2_hist_mc, func2_tot_mc, deltam_th[1], nominal_deltam[1], 0.001 );
  func1_tot_mc->FixParameter( 7, 0.0 );
  func2_tot_mc->FixParameter( 7, 0.0 );

  /* // tmpppppp
  func1_tot_mc->FixParameter( 2, 0.3 );
  func1_tot_mc->FixParameter( 3, func1_tot_mc->GetParameter(3) );
  func1_tot_mc->SetParLimits( 4, 0.0,   0.003 );
  func1_tot_mc->FixParameter( 6, 1.0 );
  func2_tot_mc->FixParameter( 2, 0.3 );
  func2_tot_mc->FixParameter( 3, func2_tot_mc->GetParameter(3) );
  func2_tot_mc->SetParLimits( 4, 0.0,   0.0010 );
  func2_tot_mc->FixParameter( 6, 1.0 );
  */  
  can2->cd(3); deltam1_hist_mc->Fit(func1_tot_mc);
  can2->cd(4); deltam2_hist_mc->Fit(func2_tot_mc);
  Double_t init_var1[9];
  Double_t init_var2[9];
  for( Int_t ip=0; ip<9; ip++ ){
    init_var1[ip] = func1_tot_mc->GetParameter(ip);
    init_var2[ip] = func2_tot_mc->GetParameter(ip);
  }
  /*
  can2->cd(3);
  iterative_fit( deltam1_hist_mc, func1_tot_mc, 9, init_var1, "PRE0", manip_func );

  can2->cd(4);  
  iterative_fit( deltam2_hist_mc, func2_tot_mc, 9, init_var2, "PRE0", manip_func );
  */

  //////////
  func1_tot_mc->Print();
  func2_tot_mc->Print();
  //////////
  if( fl_ratio_fixed ){
    for( Int_t ip=0; ip<7; ip++ ){
      if( ip==1 || ip==2 || ip==5 || ip==6 ){
	func1_tot_dt->FixParameter( ip, func1_tot_mc->GetParameter(ip) );
	func2_tot_dt->FixParameter( ip, func2_tot_mc->GetParameter(ip) );
      }else if( fl_ratio_fixed>1 && (ip==3 || ip==4) ){
	func1_tot_dt->FixParameter( ip, func1_tot_mc->GetParameter(ip) );
	func2_tot_dt->FixParameter( ip, func2_tot_mc->GetParameter(ip) );
      }
    }
  }

  can2->cd(1); deltam1_hist_dt->Fit(func1_tot_dt);
  can2->cd(2); deltam2_hist_dt->Fit(func2_tot_dt);
  
  //////////
  func1_tot_dt->Print();
  func2_tot_dt->Print();
  //////////

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TF1* deltam1_func_pdf_dt = new TF1( "deltam1_func_sig_dt", func_3gauss, deltam_xmin[0], deltam_xmax[0], 7 );
  TF1* deltam2_func_pdf_dt = new TF1( "deltam2_func_sig_dt", func_3gauss, deltam_xmin[1], deltam_xmax[1], 7 );
  TF1* deltam1_func_pdf_mc = new TF1( "deltam1_func_sig_mc", func_3gauss, deltam_xmin[0], deltam_xmax[0], 7 );
  TF1* deltam2_func_pdf_mc = new TF1( "deltam2_func_sig_mc", func_3gauss, deltam_xmin[1], deltam_xmax[1], 7 );
  for( Int_t ip=0; ip<7; ip++ ){
    deltam1_func_pdf_dt->SetParameter( ip, func1_tot_dt->GetParameter(ip) );
    deltam2_func_pdf_dt->SetParameter( ip, func2_tot_dt->GetParameter(ip) );
    deltam1_func_pdf_mc->SetParameter( ip, func1_tot_mc->GetParameter(ip) );
    deltam2_func_pdf_mc->SetParameter( ip, func2_tot_mc->GetParameter(ip) );
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 
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

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Setting for delta m>
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
  std::cout << "[MC counting in whole region]" << std::endl
	    << "N(s1s2) = " << cnt_mc_s1s2 << std::endl
	    << "N(s1b2) = " << cnt_mc_s1b2 << std::endl
	    << "N(b1s2) = " << cnt_mc_b1s2 << std::endl
	    << "N(b1b2) = " << cnt_mc_b1b2 << std::endl;
  std::cout << "[MC counting in signal region]" << std::endl
	    << "N(s1s2) = " << cnt_mc_s1s2_sig << std::endl
	    << "N(s1b2) = " << cnt_mc_s1b2_sig << std::endl
	    << "N(b1s2) = " << cnt_mc_b1s2_sig << std::endl
	    << "N(b1b2) = " << cnt_mc_b1b2_sig << std::endl
	    << "  -> N(corr) = " << cnt_mc_s1s2_sig << std::endl
	    << "  -> N(fake) = " << cnt_mc_s1b2_sig + cnt_mc_b1s2_sig + cnt_mc_b1b2_sig << std::endl;
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Print( Form("pic/fit_deltam_2d_%d.eps",fl_dec) );
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
