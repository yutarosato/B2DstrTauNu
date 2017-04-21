#include "bcs_sigmc_rnd.h"

const Bool_t fl_message = !true;

Int_t main( Int_t argc, Char_t** argv ){

  if( argc != 3 ){
    std::cerr << "wrong input" << std::endl
	      << "Usage : ./bcs_gmc (char*)infile (char*)outdir" << std::endl
	      << std::endl;
    abort();
  }

  // --------------------------------------------------------------------  
  const Char_t* tname   = "h15";
  const Char_t* infile  = argv[1];
  const Char_t* outdir  = argv[2];
  // --------------------------------------------------------------------    
  std::string basename = gSystem->BaseName( infile );  
  if( basename.find(".root") == std::string::npos ){
    std::cerr << "[infile] " << std::setw(80) << infile
	      << " -> wrong file name" << std::endl;
    abort();
  }
  basename.erase( basename.rfind(".root") );
  // --------------------------------------------------------------------    
  system( Form("mkdir -p %s", outdir) );
  TChain* chain = new TChain( tname );
  Int_t nfile = chain->Add( infile );
  gRandom->SetSeed( time(NULL) );
  // --------------------------------------------------------------------
  TTree* tree = new TTree();
  //Char_t* cut = "remtrk==0&&rempi0==0&&remks==0&&1.835<d1_m&&d1_m<1.895&&1.835<d2_m&&d2_m<1.895&&dm1<0.155&&dm2<0.155";
  Char_t* cut = "1";
  if( chain->GetEntries(cut) ) tree = chain->CopyTree ( cut ); // "tree" is copied from "chain" with "cut"
  else                         tree = chain->CloneTree(0, "newtree" );
  Int_t dupli=0, sum_dupli=0;
  Int_t tr_exist=0;
  tree->Branch("dupli",    &dupli,    "dupli/I");
  tree->Branch("tr_exist", &tr_exist, "tr_exist/I" );

  // --------------------------------------------------------------------
  TTree* newtree;
  if( chain->GetEntries(cut) ) newtree = tree ->CloneTree(0,"newtree");
  else                         newtree = chain->CloneTree(0,"newtree");

  //TTree* newtree = tree->CloneTree( 0, "newtree" );
  Float_t exprun, event, bcs;
  Float_t d1_m,d2_m;
  Float_t dm1,dm2;
  Float_t d1_lund, d2_lund;
  Float_t dstr1_lund, dstr2_lund;
  Float_t self;

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
    const Char_t* outfile = Form( "%s/%s_bcs.root",outdir,basename.c_str() );
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
      bcs = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
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
      bcs        = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
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
      bcs = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
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
      bcs = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
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
      bcs        = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );
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
      bcs = calc_bcs( d1_m, d2_m, dm1, dm2, d1_lund, d2_lund, dstr1_lund, dstr2_lund );

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
  const Char_t* outfile = Form( "%s/%s_bcs.root",outdir,basename.c_str() );
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
  //return event.begin()->second; // select event with min value

  // random selection
  double rnd_d = gRandom->Rndm();
  rnd_d *= (double)event.size();
  int rnd_i = (int)rnd_d;
  rnd_i = rnd_i%((int)event.size());
  for( int i=0; i<rnd_i; i++ ) it_last--;
  return it_last->second; // random selection
}

Double_t calc_bcs( Float_t d1_m,    Float_t d2_m,    Float_t dm1,        Float_t dm2,
		   Float_t d1_lund, Float_t d2_lund, Float_t dstr1_lund, Float_t dstr2_lund ){

  Double_t d1_m_PDG;
  if     ( abs((Int_t)d1_lund)==421 ) d1_m_PDG = PDGmass::d0;
  else if( abs((Int_t)d1_lund)==411 ) d1_m_PDG = PDGmass::dp;
  else                                std::cerr << "Wrong D lund cod : " << d1_lund << std::endl, abort();
  Double_t d2_m_PDG;
  if     ( abs((Int_t)d2_lund)==421 ) d2_m_PDG = PDGmass::d0;
  else if( abs((Int_t)d2_lund)==411 ) d2_m_PDG = PDGmass::dp;
  else                                std::cerr << "Wrong D lund cod : " << d2_lund << std::endl, abort();

  Double_t dstr1_m_PDG;
  if     ( abs((Int_t)dstr1_lund)==423 ) dstr1_m_PDG = PDGmass::dstr0;
  else if( abs((Int_t)dstr1_lund)==413 ) dstr1_m_PDG = PDGmass::dstrp;
  else                                   std::cerr << "Wrong D* lund cod : " << dstr1_lund << std::endl, abort();
  Double_t dstr2_m_PDG;
  if     ( abs((Int_t)dstr2_lund)==423 ) dstr2_m_PDG = PDGmass::dstr0;
  else if( abs((Int_t)dstr2_lund)==413 ) dstr2_m_PDG = PDGmass::dstrp;
  else                                   std::cerr << "Wrong D* lund cod : " << dstr2_lund << std::endl, abort();

  Double_t dm1_PDG = dstr1_m_PDG - d1_m_PDG;
  Double_t dm2_PDG = dstr2_m_PDG - d2_m_PDG;

  Double_t sigma_d  = 0.005;  // ~5   MeV
  Double_t sigma_dm = 0.0008; // ~0.8 MeV
  Double_t bcs = (d1_m - d1_m_PDG)*(d1_m - d1_m_PDG)/sigma_d /sigma_d  + 
                 (d2_m - d2_m_PDG)*(d2_m - d2_m_PDG)/sigma_d /sigma_d  + 
                 (dm1  - dm1_PDG )*(dm1  - dm1_PDG )/sigma_dm/sigma_dm + 
                 (dm2  - dm2_PDG )*(dm2  - dm2_PDG )/sigma_dm/sigma_dm;
  return bcs;
}
