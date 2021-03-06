#include "bcs_gmc_vtx.h"

const Bool_t fl_message = true;

Int_t main( Int_t argc, Char_t** argv ){

  if( argc != 6 ){
    std::cerr << "wrong input" << std::endl
	      << "Usage : ./bcs_gmc (char*)expno (int)stream (char*)type (char*)indir (char*)outdir" << std::endl
	      << std::endl;
    abort();
  }

  const Char_t* expno  = argv[1];
  const Int_t   stream = atoi( argv[2] );
  const Char_t* type   = argv[3];
  // --------------------------------------------------------------------  
  const Char_t* tname   = "h15";
  const Char_t* indir   = argv[4];
  const Char_t* outdir  = argv[5];
  // --------------------------------------------------------------------    

  std::stringstream sTmp;
  //sTmp << indir << "/gMC_" << type << "_e0" << expno << "c*s0" << stream << "*.root";
  sTmp << indir << "/gMC_" << type << "_e0" << expno << "_*s0" << stream << "*.root";
  Char_t tmp_infile[255];
  strcpy( tmp_infile, (Char_t*)sTmp.str().c_str() );
  sTmp.str("");
  sTmp.clear();
  const Char_t* infile = (const Char_t*)tmp_infile;

  // --------------------------------------------------------------------
  system( Form("mkdir -p %s", outdir) );
  TChain* chain = new TChain( tname );
  Int_t nfile = chain->Add( infile );

  // --------------------------------------------------------------------
  TTree* tree = new TTree();
  //Char_t* cut = "remtrk==0&&rempi0==0&&remks==0&&1.835<d1_m&&d1_m<1.895&&1.835<d2_m&&d2_m<1.895&&dm1<0.155&&dm2<0.155";
  Char_t* cut = "1";
  //sTmp <<    " (" << makeCut_pi0mass_d   (0.015, 0.015).c_str() << ")"; // pi0 mass for D decay
  //sTmp << " && (" << makeCut_pi0mass_dstr(0.010, 0.010).c_str() << ")"; // pi0 mass for D* decay
  //sTmp << "(" << makeCut_dmass( 0.015, 0.015, 0.045, 0.030,
  //0.015, 0.015, 0.036, 0.024
  //).c_str()  << ")"; // dmass
  //sTmp << "(" << makeCut_deltam( 0.0025, 0.0025, 0.0020, 0.0020 ).c_str()  << ")"; // deltam
  //TCut cut = sTmp.str().c_str();
  //sTmp.str("");
  //sTmp.clear();
  if( chain->GetEntries(cut) ) tree = chain->CopyTree ( cut ); // "tree" is copied from "chain" with "cut"
  else                         tree = chain->CloneTree(0, "newtree" );
  Int_t dupli=0, sum_dupli=0;
  Int_t tr_exist=0;//, tr_rmxs=0;
  tree->Branch("dupli",    &dupli,    "dupli/I");
  tree->Branch("tr_exist", &tr_exist, "tr_exist/I" );
  //tree->Branch("tr_rmxs",  &tr_rmxs,  "tr_rmxs/I"  );

  // --------------------------------------------------------------------
  TTree* newtree;
  if( chain->GetEntries(cut) ) newtree = tree ->CloneTree(0,"newtree");
  else                         newtree = chain->CloneTree(0,"newtree");

  //TTree* newtree = tree->CloneTree( 0, "newtree" );
  Float_t  exprun, event, bcs;
  Float_t d1_m,d2_m;
  Float_t dm1,dm2;
  Float_t d1_lund, d2_lund;
  Float_t dstr1_lund, dstr2_lund;
  Float_t self;
  Float_t chisq1, ndf1, chisq2, ndf2;

  tree->SetBranchAddress( "exprun",    &exprun     );
  tree->SetBranchAddress( "event",     &event      );
  tree->SetBranchAddress( "self",      &self       );
  tree->SetBranchAddress( "d1_m",      &d1_m       );
  tree->SetBranchAddress( "d2_m",      &d2_m       );
  tree->SetBranchAddress( "dm1",       &dm1        );
  tree->SetBranchAddress( "dm2",       &dm2        );
  tree->SetBranchAddress( "rm_d1lun",  &d1_lund    );
  tree->SetBranchAddress( "rm_d2lun",  &d2_lund    );
  tree->SetBranchAddress( "rm_dst1l",  &dstr1_lund );
  tree->SetBranchAddress( "rm_dst2l",  &dstr2_lund );
  tree->SetBranchAddress( "kfd1chi2",  &chisq1     );
  tree->SetBranchAddress( "kfd2chi2",  &chisq2     );
  tree->SetBranchAddress( "kfd1ndf",   &ndf1       );
  tree->SetBranchAddress( "kfd2ndf",   &ndf2       );


  // --------------------------------------------------------------------
  long long int n = 0;
  std::multimap<long long int, long long int> m; // <key, value>, sorted by key, All data is sorted by expruneventNo.
  while( tree->GetEntry(n, 0) ) {
    m.insert( std::pair<long long int, long long int>((long long int)exprun*10000000000+(long long int)event, (long long int)n) );
    n++;
  }
  if( fl_message ) std::cout <<  n << " events (total) -> " << m.size() << " events" << std::endl;
  if( fl_message ) std::cout << " ************************************************************************************************************************" << std::endl;


  // --------------------------------------------------------------------
  if( m.size()==0 ){ // for empty file
    std::cout << std::setw(7)  << std::right << chain->GetEntries()   << " " // total
	      << std::setw(7)  << std::right << tree ->GetEntries()   << " " // bcs-region cut
	      << std::setw(5)  << std::right << 0                     << " " // select mode(xs and lepton)
	      << std::setw(5)  << std::right << 0                     << " " // after BCS
	      << std::setw(5)  << std::right << nfile                 << "  "
	      << std::setw(80) << std::right << infile                << "   ";
    if( chain->GetEntries() ) std::cout << int( 100*((double)tree->GetEntries()/chain->GetEntries()) ) << " %(bcs-region cut) ";
    else                      std::cout <<                                                           0 << " %(bcs-region cut) ";
    std::cout << 0 << " %(BCS)"
	      << std::endl;
    const Char_t* outfile = Form( "%s/gMC_%s_e0%s_s0%d_bcs.root",outdir, type, expno, stream );
    TFile* rootf = new TFile( outfile, "RECREATE" );
    newtree->Write();
    rootf->Close();
    delete chain;
    delete tree;
    delete newtree;
    delete rootf;
    return 0;
  }
  // --------------------------------------------------------------------

  std::multimap<double, int> m_event;
  // <key, value>, "value" in "m_events" is same with "value" in "m", data in a events are accumulated and BCS are performed based on "key" (e.g. likelihood, chi2, ... )
  double prev_event = 0;
  int cnt = 0;
  std::multimap<long long int, long long int>::iterator it_last = m.end();
  it_last--;

  for( std::multimap<long long int, long long int>::iterator i = m.begin(); i != m.end(); i++ ){ // START EVENT LOOP
    if( i==m.begin() ){ // for first event
      tree->GetEntry( i->second, 0 );
      //bcs = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
      bcs = calc_bcs( chisq1, ndf1, chisq2, ndf2 );
      if( self==1 || self==2 ) tr_exist++;
      m_event.insert( std::pair<double, int>(bcs, i->second) );
      prev_event = i->first;
      if( fl_message ) std::cout << "[" << std::setw(5) << std::right << i->second << "] "
				 << "exprun = "  << std::setw(8)  << std::right << exprun
				 << ", event = " << std::setw(6)  << std::right << event
				 << ", bcs = "   << std::setw(15) << std::right << bcs
				 << std::endl;
    }else if( i->first!=prev_event ){ // if "next" event is detected, BCS is performed.
      tree->GetEntry( select(m_event), 0 );
      //bcs        = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
      bcs        = calc_bcs( chisq1, ndf1, chisq2, ndf2 );
      dupli      = m_event.size();
      sum_dupli += dupli;
      if( fl_message ) std::cout << " -------> [FILL!!!!!!] "
				 << "exprun = "     << exprun   << ", event = "    << event << ", bcs = " << bcs
				 << ", dupli = "    << dupli    << ", tr_exist = " << tr_exist
				 << std::endl;

      newtree->Fill();
      tr_exist=0;
      cnt++;
      m_event.clear();
      if( fl_message ) std::cout << " +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
				 << std::endl << std::endl;
      tree->GetEntry( i->second, 0 );
      //bcs = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
      bcs = calc_bcs( chisq1, ndf1, chisq2, ndf2 );
      if( self==1||self==2 ) tr_exist++;
      
      m_event.insert( std::pair<double, int>(bcs, i->second) );
      prev_event = i->first;
      if( fl_message ) std::cout << "[" << std::setw(5) << std::right << i->second << "] "
				 << "exprun = "  << std::setw(8)  << std::right << exprun
				 << ", event = " << std::setw(6)  << std::right << event
				 << ", bcs = "   << std::setw(15) << std::right << bcs
				 << std::endl;
    }else{ // data in same events are accumulated to "m_event".
      tree->GetEntry(i->second, 0);
      //bcs = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
      bcs = calc_bcs( chisq1, ndf1, chisq2, ndf2 );
      if( self==1 || self==2 ) tr_exist++;

      m_event.insert( std::pair<double, int>(bcs, i->second) );
      prev_event = i->first;
      if( fl_message ) std::cout << "[" << std::setw(5) << std::right << i->second << "] "
				 << "exprun = "  << std::setw(8)  << std::right << exprun
				 << ", event = " << std::setw(6)  << std::right << event
				 << ", bcs = "   << std::setw(15) << std::right << bcs
				 << std::endl;
    }

    if( i==it_last) { // for last event
      tree->GetEntry( select(m_event), 0 );
      //bcs = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
      bcs = calc_bcs( chisq1, ndf1, chisq2, ndf2 );
      dupli      = m_event.size();
      sum_dupli += dupli;
      if( fl_message ) std::cout << " -------> [FILL!!!!!!] "
				 << "exprun = "     << exprun   << ", event = "   << event << ", bcs = " << bcs
				 << ", dupli = "    << dupli    << ", tr_exist = " << tr_exist
				 << std::endl;
      newtree->Fill();
      tr_exist=0;
      cnt++;
      if( fl_message ) std::cout << " ************************************************************************************************************************" << std::endl;
    }
  } // END EVENT LOOP


  // -------------< DEBUG MESSAGE > ---------------------------------------------------------------------------

  if( fl_message ){
    std::cout <<  n << " events (total) -> " << m.size() << " events" << std::endl;
    for( std::multimap<long long int, long long int>::iterator i = m.begin(); i != m.end(); i++ ){
      tree->GetEntry( i->second, 0 );
      //bcs = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
      bcs = calc_bcs( chisq1, ndf1, chisq2, ndf2 );

      std::cout << "[" << std::setw(5) << std::right << i->second << "] "
		<< "exprun = "  << std::setw(8)  << std::right << exprun
		<< ", event = " << std::setw(6)  << std::right << event
		<< ", bcs = "   << std::setw(15) << std::right << bcs
		<< std::endl;
      
    }
  }

  // -------------< CHECK > ---------------------------------------------------------------------------
  if( m.size() != sum_dupli        ) std::cerr << infile << " -> [ABORT] Event is missing : "    << m.size()              << " ?=? " << sum_dupli << std::endl, abort();
  if( newtree->GetEntries() != cnt ) std::cerr << infile << " -> [ABORT] Event is not filled : " << newtree->GetEntries() << " ?=? " << cnt       << std::endl, abort();
  
  // -------------< DISPLAY > ---------------------------------------------------------------------------  
  std::cout << std::setw(7)  << std::right << chain->GetEntries() << " " // total
	    << std::setw(7)  << std::right << tree->GetEntries()  << " " // bcs-region cut
	    << std::setw(5)  << std::right << sum_dupli           << " " // select mode(xs and lepton)
	    << std::setw(5)  << std::right << cnt                 << " " // after BCS
	    << std::setw(5)  << std::right << nfile               << "  "
    	    << std::setw(80) << std::right << infile              << "   ";
  if( chain->GetEntries() ) std::cout << int( 100*((double)tree->GetEntries()/chain->GetEntries()) ) << " %(bcs-region cut) ";
  else                      std::cout <<                                                           0 << " %(bcs-region cut) ";
  std::cout << int( 100*((double)                 cnt/            sum_dupli) ) << " %(BCS)"
	    << std::endl;

  // --------------------------------------------------------------------------------------------
  const Char_t* outfile = Form( "%s/gMC_%s_e0%s_s0%d_bcs.root",outdir, type, expno, stream );
  TFile* rootf = new TFile( outfile, "RECREATE" );
  newtree->Write();
  rootf->Close();
  delete chain;
  delete tree;
  delete newtree;
  delete rootf;
  return 0;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t select( std::multimap<double, int>& event ){
  if( fl_message ){
    std::cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
    std::cout << "event.size() = " << event.size() << std::endl;
    for( std::multimap<double, int>::iterator i = event.begin(); i != event.end(); i++ ){
      std::cout << "[" << i->second << "] bcs = " << i->first << std::endl;
    }
  }
  
  std::multimap<double, int>::iterator it_last = event.end();
  it_last--;
  double  min = event.begin()->first;
  double  max = it_last->first;
  double& var = max;
  //return it_last->second; // select event with max value
  return event.begin()->second; // select event with min value
}

Double_t calc_bcs( Float_t chisq1,    Float_t ndf1,    Float_t chisq2, Float_t ndf2 ){
  Double_t bcs = ( chisq1 + chisq2 )/ ( ndf1+ndf2 );
  return bcs;
}
