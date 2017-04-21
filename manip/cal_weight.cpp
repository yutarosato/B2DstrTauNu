#include "draws_.h"


const Double_t lep_syst_sig[2][4] = { {0.964, 0.971}, // e
				      {0.975, 0.983, 0.980, 0.996} // mu
};
const Double_t lep_esyst_sig[2][4] = { {0.029, 0.022}, // e
				       {0.023, 0.016, 0.017, 0.16} // mu
};
const Double_t lep_syst_nor[2][4] = { {0.978, 0.980}, // e
				      {0.974, 0.968, 0.961, 0.982} // mu
};

const Double_t lep_esyst_nor[2][4] = { {0.022, 0.017}, // e
				       {0.023, 0.017, 0.017, 0.017} // mu
};


Double_t cal_lep_syst( Int_t f_exprun, Int_t f_event, Int_t f_rm_l, Int_t f_lself, Bool_t fl_E=false ){
  Int_t fl_lep = -1;
  Int_t fl_exp = 0;

  if     ( f_rm_l==10 ) fl_lep = 0; // e
  else if( f_rm_l== 1 ) fl_lep = 1; // mu
  else std::cerr << "[ABORT] Wrong lepton flavor : " << f_rm_l << std::endl, abort();
  
  if( f_rm_l==10 ){ // electron
    if  ( f_exprun < 30*10000 ) fl_exp = 0;
    else                        fl_exp = 1;
  }else if( f_rm_l==1 ){ // muon
    if     ( f_exprun < 30*10000                              ) fl_exp = 0;
    else if( f_exprun < 40*10000                              ) fl_exp = 1;
    else if( f_exprun > 45*10000 && f_exprun < 45*10000 + 221 ) fl_exp = 1;
    else if( f_exprun < 50*10000                              ) fl_exp = 2;
    else                                                        fl_exp = 3;
  }

  if     ( f_lself==1 ) return ( fl_E ? lep_esyst_sig[fl_lep][fl_exp] : lep_syst_sig[fl_lep][fl_exp] );
  else if( f_lself==2 ) return ( fl_E ? lep_esyst_nor[fl_lep][fl_exp] : lep_syst_nor[fl_lep][fl_exp] );
  else                  return ( fl_E ?                           0.0 :                          1.0 );
}

Double_t cal_lep_esyst( Int_t f_exprun, Int_t f_event, Int_t f_rm_l, Int_t f_lself ){
  return cal_lep_syst( f_exprun, f_event, f_rm_l, f_lself, true );
}

const Bool_t fl_message = !true;

Int_t main( Int_t argc, Char_t** argv ){
  if( argc!=4 ){
    std::cerr << "wrong input" << std::endl
	      << " Usage : "
	      << argv[0]
	      << " (char*)treename (char*)inifile (char*)outdir"
	      << std::endl;
    abort();
  }

  const Char_t* treename = argv[1];
  const Char_t* infile   = argv[2];
  const Char_t* outdir   = argv[3];
  
  std::string basename = gSystem->BaseName( infile );  
  if( basename.find(".root") == std::string::npos ){
    std::cerr << "[infile] " << std::setw(80) << infile
	      << " -> wrong file name" << std::endl;
    abort();
  }
  basename.erase( basename.rfind(".root") );
  // --------------------------------------------------------------------
  //const Char_t* treename   = "h15";
  //const Char_t* treename   = "h17";
  // --------------------------------------------------------------------
  system( Form("mkdir -p %s", outdir) );
  TChain* chain = new TChain( treename );
  //std::stringstream sTmp;
  Int_t nfile = chain->Add( infile );
  //sTmp.str("");
  //sTmp.clear();
  // --------------------------------------------------------------------
  TTree* tree = new TTree();
  if( chain->GetEntries() ) tree = chain->CloneTree();
  else                      tree = chain->CloneTree(0,"tree");
  std::cout << std::setw(50) << std::right << infile               << " : "
	    << std::setw( 5) << std::right << nfile                << " files, "
	    << std::setw( 5) << std::right << chain->GetEntries()  << " entries"
	    << std::endl;
  // --------------------------------------------------------------------  
  Float_t w1_mc, w1_mc_etot, w1_mc_estat, w1_mc_esyst, w1_bf;
  Float_t w2_mc, w2_mc_etot, w2_mc_estat, w2_mc_esyst, w2_bf;

  tree->Branch( "w1_mc",       &w1_mc,       "w1_mc/F"       );
  tree->Branch( "w1_mc_etot",  &w1_mc_etot,  "w1_mc_etot/F"  );
  tree->Branch( "w1_mc_estat", &w1_mc_estat, "w1_mc_estat/F" );
  tree->Branch( "w1_mc_esyst", &w1_mc_esyst, "w1_mc_esyst/F" );
  tree->Branch( "w1_bf",       &w1_bf,       "w1_bf/F"       );
  tree->Branch( "w2_mc",       &w2_mc,       "w2_mc/F"       );
  tree->Branch( "w2_mc_etot",  &w2_mc_etot,  "w2_mc_etot/F"  );
  tree->Branch( "w2_mc_estat", &w2_mc_estat, "w2_mc_estat/F" );
  tree->Branch( "w2_mc_esyst", &w2_mc_esyst, "w2_mc_esyst/F" );
  tree->Branch( "w2_bf",       &w2_bf,       "w2_bf/F"       );

  Float_t lidsys, lidesys;
  Double_t lid1sys, lid1esys;
  Double_t lid2sys, lid2esys;
  tree->Branch( "lidsys",     &lidsys,      "lidsys/F"     );
  tree->Branch( "lidesys",    &lidesys,     "lidesys/F"    );

  Float_t ctgrsyst;
  Float_t moresyst;
  tree->Branch( "ctgrsyst",    &ctgrsyst,    "ctgrsyst/F"    );
  tree->Branch( "moresyst",    &moresyst,    "moresyst/F"    );

  // --------------------------------------------------------------------  
  TTree* newtree = tree->CloneTree( 0, "newtree" );
  Float_t exprun;   tree->SetBranchAddress( "exprun",   &exprun );
  Float_t event;    tree->SetBranchAddress( "event",    &event );

  Float_t semi1;    tree->SetBranchAddress( "semi1",    &semi1    ); // flag for semileptonic decay
  Float_t gm_ddst1; tree->SetBranchAddress( "gm_ddst1", &gm_ddst1 ); // flag for D/D*/D**/other
  Float_t fldstst1; tree->SetBranchAddress( "fldstst1", &fldstst1 ); // flag for D**
  Float_t rootdf1;  tree->SetBranchAddress( "rootdf1",  &rootdf1  ); // LUND code for rootD
  Float_t semi2;    tree->SetBranchAddress( "semi2",    &semi2    ); // flag for semileptonic decay
  Float_t gm_ddst2; tree->SetBranchAddress( "gm_ddst2", &gm_ddst2 ); // flag for D/D*/D**/other
  Float_t fldstst2; tree->SetBranchAddress( "fldstst2", &fldstst2 ); // flag for D**
  Float_t rootdf2;  tree->SetBranchAddress( "rootdf2",  &rootdf2  ); // LUND code for rootD
  Float_t l1self; tree->SetBranchAddress( "l1self", &l1self );
  Float_t rm_l1;  tree->SetBranchAddress( "rm_l1",  &rm_l1  );

  Float_t k1_q2;  tree->SetBranchAddress( "k1_q2",  &k1_q2  );
  Float_t k1_pl;  tree->SetBranchAddress( "k1_pl",  &k1_pl  );
  Float_t k1_w;   tree->SetBranchAddress( "k1_w",   &k1_w   );
  Float_t k1_cos; tree->SetBranchAddress( "k1_cos", &k1_cos );
  Float_t k2_q2;  tree->SetBranchAddress( "k2_q2",  &k2_q2  );
  Float_t k2_pl;  tree->SetBranchAddress( "k2_pl",  &k2_pl  );
  Float_t k2_w;   tree->SetBranchAddress( "k2_w",   &k2_w   );
  Float_t k2_cos; tree->SetBranchAddress( "k2_cos", &k2_cos );
  Float_t l2self; tree->SetBranchAddress( "l2self", &l2self );
  Float_t rm_l2;  tree->SetBranchAddress( "rm_l2",  &rm_l2  );

  // --------------------------------------------------------------------
  SemiLepWeights2D       semilep_W1     (1, "BtoDstrlnu1" );
  SemiLepWeights2D       semilep_W2     (1, "BtoDstrlnu2" );
  SemiLepD2StarWeights2D semilepD2str_W1(1, "BtoD2strlnu1");
  SemiLepD2StarWeights2D semilepD2str_W2(1, "BtoD2strlnu2");

  Int_t nev = 0;
  while (tree->GetEntry(nev, 0)) {
    // initialize
    w1_mc       = 1.0;
    w1_mc_etot  = 0.0;
    w1_mc_estat = 0.0;
    w1_mc_esyst = 0.0;
    w1_bf       = 1.0;
    w2_mc       = 1.0;
    w2_mc_etot  = 0.0;
    w2_mc_estat = 0.0;
    w2_mc_esyst = 0.0;
    w2_bf       = 1.0;
    lidsys      = 1.0;
    lidesys     = 0.0;
    ctgrsyst = 0;
    moresyst = 0;

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // [lep-id correction] // 20150417
    lid1sys  = cal_lep_syst ( (Int_t)exprun, (Int_t)event, (Int_t)rm_l1, (Int_t)l1self );
    lid1esys = cal_lep_esyst( (Int_t)exprun, (Int_t)event, (Int_t)rm_l1, (Int_t)l1self );
    lid2sys  = cal_lep_syst ( (Int_t)exprun, (Int_t)event, (Int_t)rm_l1, (Int_t)l2self );
    lid2esys = cal_lep_esyst( (Int_t)exprun, (Int_t)event, (Int_t)rm_l1, (Int_t)l2self );
    lidsys  = lid1sys * lid2sys;
    lidesys = lidsys * sqrt( pow(lid1esys/lid1sys, 2) + pow(lid2esys/lid2sys, 2) );

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // [BF correction]
    // lclass : 1(D*), 2(D), 3-6(D**) [3(D1), 4(D2), 5(D1'), 6(D*0)]
    Int_t lclass1 = cal_lclass( (Int_t)semi1, (Int_t)gm_ddst1, (Int_t)rootdf1 );
    Int_t lclass2 = cal_lclass( (Int_t)semi2, (Int_t)gm_ddst2, (Int_t)rootdf2 );
    w1_bf = SemiLepBFs( lclass1, (Int_t)rootdf1 );
    w2_bf = SemiLepBFs( lclass2, (Int_t)rootdf2 );
    if( tree->GetLeaf("flmcddst")->GetValue()==1 ){
      if( lclass1>2 ) w1_bf = 1.0;
      if( lclass2>2 ) w2_bf = 1.0;
    }

    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    // categry for systematic study // 20150417
    Int_t ctgrsyst1 = cal_lclass_for_syst( (Int_t)semi1, (Int_t)gm_ddst1, (Int_t)rootdf1 );
    Int_t ctgrsyst2 = cal_lclass_for_syst( (Int_t)semi2, (Int_t)gm_ddst2, (Int_t)rootdf2 );

    if( ctgrsyst1 ){
      ctgrsyst = ctgrsyst1;
      ///*
      if     ( ctgrsyst1==3 && tree->GetLeaf("ddst1_nc")->GetValue()==2                                                                                                                         ) moresyst = 1;
      else if( ctgrsyst1==4 && tree->GetLeaf("ddst1_nc")->GetValue()==2 && ( abs((Int_t)tree->GetLeaf("ddst1_ac")->GetValue())==211 || abs((Int_t)tree->GetLeaf("ddst1_ac")->GetValue())==111 ) ) moresyst = 1;
      else if( ctgrsyst1==5 && tree->GetLeaf("ddst1_nc")->GetValue()==2 && ( abs((Int_t)tree->GetLeaf("ddst1_ac")->GetValue())==211 || abs((Int_t)tree->GetLeaf("ddst1_ac")->GetValue())==111 ) ) moresyst = 1;
      else if( ctgrsyst1==6 && tree->GetLeaf("ddst1_nc")->GetValue()==2 && ( abs((Int_t)tree->GetLeaf("ddst1_ac")->GetValue())==211 || abs((Int_t)tree->GetLeaf("ddst1_ac")->GetValue())==111 ) ) moresyst = 1;
      //*/
    }else if( ctgrsyst2 ){
      ctgrsyst = ctgrsyst2;
      ///*
      if     ( ctgrsyst2==3 && tree->GetLeaf("ddst2_nc")->GetValue()==2                                                                                                                         ) moresyst = 1;
      else if( ctgrsyst2==4 && tree->GetLeaf("ddst2_nc")->GetValue()==2 && ( abs((Int_t)tree->GetLeaf("ddst2_ac")->GetValue())==211 || abs((Int_t)tree->GetLeaf("ddst2_ac")->GetValue())==111 ) ) moresyst = 1;
      else if( ctgrsyst2==5 && tree->GetLeaf("ddst2_nc")->GetValue()==2 && ( abs((Int_t)tree->GetLeaf("ddst2_ac")->GetValue())==211 || abs((Int_t)tree->GetLeaf("ddst2_ac")->GetValue())==111 ) ) moresyst = 1;
      else if( ctgrsyst2==6 && tree->GetLeaf("ddst2_nc")->GetValue()==2 && ( abs((Int_t)tree->GetLeaf("ddst2_ac")->GetValue())==211 || abs((Int_t)tree->GetLeaf("ddst2_ac")->GetValue())==111 ) ) moresyst = 1;
      //*/
    }

    if( tree->GetLeaf("self")->GetValue()==-3 ){
      // Ds->tau nu in double D bkg
      if     ( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==431) && ( (tree->GetLeaf("gm_df1le")->GetValue()==1&&tree->GetLeaf("gm_df1nu")->GetValue()==12) || (tree->GetLeaf("gm_df1le")->GetValue()==10&&tree->GetLeaf("gm_df1nu")->GetValue()==102) ) ) ctgrsyst = 11;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==431) && ( (tree->GetLeaf("gm_ds1le")->GetValue()==1&&tree->GetLeaf("gm_ds1nu")->GetValue()==12) || (tree->GetLeaf("gm_ds1le")->GetValue()==10&&tree->GetLeaf("gm_ds1nu")->GetValue()==102) ) ) ctgrsyst = 11;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==431) && ( (tree->GetLeaf("gm_df2le")->GetValue()==1&&tree->GetLeaf("gm_df2nu")->GetValue()==12) || (tree->GetLeaf("gm_df2le")->GetValue()==10&&tree->GetLeaf("gm_df2nu")->GetValue()==102) ) ) ctgrsyst = 11;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==431) && ( (tree->GetLeaf("gm_ds2le")->GetValue()==1&&tree->GetLeaf("gm_ds2nu")->GetValue()==12) || (tree->GetLeaf("gm_ds2le")->GetValue()==10&&tree->GetLeaf("gm_ds2nu")->GetValue()==102) ) ) ctgrsyst = 11;
      if     ( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==433) && ( (tree->GetLeaf("gm_df1le")->GetValue()==1&&tree->GetLeaf("gm_df1nu")->GetValue()==12) || (tree->GetLeaf("gm_df1le")->GetValue()==10&&tree->GetLeaf("gm_df1nu")->GetValue()==102) ) ) ctgrsyst = 12;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==433) && ( (tree->GetLeaf("gm_ds1le")->GetValue()==1&&tree->GetLeaf("gm_ds1nu")->GetValue()==12) || (tree->GetLeaf("gm_ds1le")->GetValue()==10&&tree->GetLeaf("gm_ds1nu")->GetValue()==102) ) ) ctgrsyst = 12;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==433) && ( (tree->GetLeaf("gm_df2le")->GetValue()==1&&tree->GetLeaf("gm_df2nu")->GetValue()==12) || (tree->GetLeaf("gm_df2le")->GetValue()==10&&tree->GetLeaf("gm_df2nu")->GetValue()==102) ) ) ctgrsyst = 12;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==433) && ( (tree->GetLeaf("gm_ds2le")->GetValue()==1&&tree->GetLeaf("gm_ds2nu")->GetValue()==12) || (tree->GetLeaf("gm_ds2le")->GetValue()==10&&tree->GetLeaf("gm_ds2nu")->GetValue()==102) ) ) ctgrsyst = 12;

      // D(s) decay to K_L
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==  431) && tree->GetLeaf("gm_df1hn")->GetValue()==10000) ctgrsyst = 21; // Ds
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==  431) && tree->GetLeaf("gm_ds1hn")->GetValue()==10000) ctgrsyst = 21;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==  431) && tree->GetLeaf("gm_df2hn")->GetValue()==10000) ctgrsyst = 21;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==  431) && tree->GetLeaf("gm_ds2hn")->GetValue()==10000) ctgrsyst = 21;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==  433) && tree->GetLeaf("gm_df1hn")->GetValue()==10000) ctgrsyst = 22; // Ds*
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==  433) && tree->GetLeaf("gm_ds1hn")->GetValue()==10000) ctgrsyst = 22;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==  433) && tree->GetLeaf("gm_df2hn")->GetValue()==10000) ctgrsyst = 22;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==  433) && tree->GetLeaf("gm_ds2hn")->GetValue()==10000) ctgrsyst = 22;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==  411) && tree->GetLeaf("gm_df1hn")->GetValue()==10000) ctgrsyst = 23; // D
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==  411) && tree->GetLeaf("gm_ds1hn")->GetValue()==10000) ctgrsyst = 23;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==  411) && tree->GetLeaf("gm_df2hn")->GetValue()==10000) ctgrsyst = 23;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==  411) && tree->GetLeaf("gm_ds2hn")->GetValue()==10000) ctgrsyst = 23;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==  413) && tree->GetLeaf("gm_df1hn")->GetValue()==10000) ctgrsyst = 24; // D*
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==  413) && tree->GetLeaf("gm_ds1hn")->GetValue()==10000) ctgrsyst = 24;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==  413) && tree->GetLeaf("gm_df2hn")->GetValue()==10000) ctgrsyst = 24;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==  413) && tree->GetLeaf("gm_ds2hn")->GetValue()==10000) ctgrsyst = 24; // Ds1(2460)
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==20433) && tree->GetLeaf("gm_df1hn")->GetValue()==10000) ctgrsyst = 25;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==20433) && tree->GetLeaf("gm_ds1hn")->GetValue()==10000) ctgrsyst = 25;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==20433) && tree->GetLeaf("gm_df2hn")->GetValue()==10000) ctgrsyst = 25;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==20433) && tree->GetLeaf("gm_ds2hn")->GetValue()==10000) ctgrsyst = 25;

      // D(s) decay to pi0
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==  431) && Int_t(tree->GetLeaf("gm_df1hr")->GetValue()/1000) ) ctgrsyst = 31;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==  431) && Int_t(tree->GetLeaf("gm_ds1hr")->GetValue()/1000) ) ctgrsyst = 31;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==  431) && Int_t(tree->GetLeaf("gm_df2hr")->GetValue()/1000) ) ctgrsyst = 31;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==  431) && Int_t(tree->GetLeaf("gm_ds2hr")->GetValue()/1000) ) ctgrsyst = 31;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==  433) && Int_t(tree->GetLeaf("gm_df1hr")->GetValue()/1000) ) ctgrsyst = 32;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==  433) && Int_t(tree->GetLeaf("gm_ds1hr")->GetValue()/1000) ) ctgrsyst = 32;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==  433) && Int_t(tree->GetLeaf("gm_df2hr")->GetValue()/1000) ) ctgrsyst = 32;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==  433) && Int_t(tree->GetLeaf("gm_ds2hr")->GetValue()/1000) ) ctgrsyst = 32;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==  411) && Int_t(tree->GetLeaf("gm_df1hr")->GetValue()/1000) ) ctgrsyst = 33;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==  411) && Int_t(tree->GetLeaf("gm_ds1hr")->GetValue()/1000) ) ctgrsyst = 33;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==  411) && Int_t(tree->GetLeaf("gm_df2hr")->GetValue()/1000) ) ctgrsyst = 33;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==  411) && Int_t(tree->GetLeaf("gm_ds2hr")->GetValue()/1000) ) ctgrsyst = 33;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==  413) && Int_t(tree->GetLeaf("gm_df1hr")->GetValue()/1000) ) ctgrsyst = 34;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==  413) && Int_t(tree->GetLeaf("gm_ds1hr")->GetValue()/1000) ) ctgrsyst = 34;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==  413) && Int_t(tree->GetLeaf("gm_df2hr")->GetValue()/1000) ) ctgrsyst = 34;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==  413) && Int_t(tree->GetLeaf("gm_ds2hr")->GetValue()/1000) ) ctgrsyst = 34;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf1")->GetValue())==20433) && Int_t(tree->GetLeaf("gm_df1hr")->GetValue()/1000) ) ctgrsyst = 35;
      else if( tree->GetLeaf("nd1")->GetValue()==2 && (fabs(tree->GetLeaf("rootds1")->GetValue())==20433) && Int_t(tree->GetLeaf("gm_ds1hr")->GetValue()/1000) ) ctgrsyst = 35;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootdf2")->GetValue())==20433) && Int_t(tree->GetLeaf("gm_df2hr")->GetValue()/1000) ) ctgrsyst = 35;
      else if( tree->GetLeaf("nd2")->GetValue()==2 && (fabs(tree->GetLeaf("rootds2")->GetValue())==20433) && Int_t(tree->GetLeaf("gm_ds2hr")->GetValue()/1000) ) ctgrsyst = 35;
      
    }



    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    
    // [Model correction]
    if( lclass1==1 || lclass1==2 ){ // D(*)
      w1_mc       = semilep_W1.weight ( lclass1, k1_q2, k1_pl );
      w1_mc_estat = semilep_W1.errStat( lclass1, k1_q2, k1_pl );
      w1_mc_esyst = semilep_W1.errSyst( lclass1, k1_q2, k1_pl );
    }else if( lclass1==3 || lclass1==4 || lclass1==5 || lclass1==6 ){ // D**
      w1_mc       = semilepD2str_W1.weight ( lclass1, k1_q2, k1_pl );
      w1_mc_estat = semilepD2str_W1.errStat( lclass1, k1_q2, k1_pl );
      w1_mc_esyst = semilepD2str_W1.errSyst( lclass1, k1_q2, k1_pl );
    }

    if( lclass2==1 || lclass2==2 ){ // D(*)
      w2_mc       = semilep_W2.weight ( lclass2, k2_q2, k2_pl );
      w2_mc_estat = semilep_W2.errStat( lclass2, k2_q2, k2_pl );
      w2_mc_esyst = semilep_W2.errSyst( lclass2, k2_q2, k2_pl );
    }else if( lclass2==3 || lclass2==4 || lclass2==5 || lclass2==6 ){ // D**
      w2_mc       = semilepD2str_W2.weight ( lclass2, k2_q2, k2_pl );
      w2_mc_estat = semilepD2str_W2.errStat( lclass2, k2_q2, k2_pl );
      w2_mc_esyst = semilepD2str_W2.errSyst( lclass2, k2_q2, k2_pl );
    }
    
    w1_mc_etot = sqrt( pow(w1_mc_estat,2) + pow(w1_mc_esyst,2) );
    w2_mc_etot = sqrt( pow(w2_mc_estat,2) + pow(w2_mc_esyst,2) );
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    nev++;
    newtree->Fill();

    if( fl_message ) std::cout << "[evt = " << std::setw(5) << nev << "]" << std::endl
      //if( w1_mc_estat<0 || w1_mc_esyst<0 ||
      //w2_mc_estat<0 || w2_mc_esyst<0
      //) std::cout << "[evt = " << std::setw(5) << nev << "]" << std::endl
      			       << "semi1:"                                      << semi1       << ", "
			       << "gm_ddst1:"                                   << gm_ddst1    << ", "
			       << "fldstst1:"                                   << fldstst1    << ", "
			       << "rootdf1:"     << std::setw(10) << std::right << rootdf1     << " ==> "
			       << "lclass1="                                    << lclass1     << " ==> "
			       << "w1_bf="       << std::setw(10) << std::right << w1_bf       << ", "
			       << "w1_mc="       << std::setw(10) << std::right << w1_mc       << ", "
			       << "w1_mc_etot="  << std::setw(10) << std::right << w1_mc_etot  << ", "
			       << "w1_mc_estat=" << std::setw(10) << std::right << w1_mc_estat << ", "
			       << "w1_mc_esyst=" << std::setw(10) << std::right << w1_mc_esyst << ", "
			       << std::endl
      			       << "semi2:"                                      << semi2       << ", "
			       << "gm_ddst2:"                                   << gm_ddst2    << ", "
			       << "fldstst2:"                                   << fldstst2    << ", "
			       << "rootdf2:"     << std::setw(10) << std::right << rootdf2     << " ==> "
			       << "lclass2="                                    << lclass2     << " ==> "
			       << "w2_bf="       << std::setw(10) << std::right << w2_bf       << ", "
			       << "w2_mc="       << std::setw(10) << std::right << w2_mc       << ", "
			       << "w2_mc_etot="  << std::setw(10) << std::right << w2_mc_etot  << ", "
			       << "w2_mc_estat=" << std::setw(10) << std::right << w2_mc_estat << ", "
			       << "w2_mc_esyst=" << std::setw(10) << std::right << w2_mc_esyst << ", "
			       << std::endl
			       << std::endl;


  }

  // --------------------------------------------------------------------
  const Char_t* outfile = Form( "%s/%s_w.root",outdir,basename.c_str() );

  TFile* rootf = new TFile( outfile, "RECREATE" );
  newtree->Write();
  rootf->Close();
  
  delete chain;
  delete tree;
  delete newtree;
  delete rootf;

  return 0;
}
