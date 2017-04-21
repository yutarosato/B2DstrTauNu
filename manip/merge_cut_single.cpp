#include "draws_.h"

Int_t main( Int_t argc, Char_t** argv ){
  if( argc!=3 ){
    std::cerr << "wrong input" << std::endl
	      << " Usage : "
	      << argv[0]
	      << " (char*)inifile (char*)outdir"
	      << std::endl;
    abort();
  }

  const Char_t* infile = argv[1];
  const Char_t* outdir = argv[2];
  
  std::string basename = gSystem->BaseName( infile );  
  if( basename.find(".root") == std::string::npos ){
    std::cerr << "[infile] " << std::setw(80) << infile
	      << " -> wrong file name" << std::endl;
    abort();
  }
  basename.erase( basename.rfind(".root") );
  // --------------------------------------------------------------------
  const Char_t* treename   = "h17";
  // --------------------------------------------------------------------
  system( Form("mkdir -p %s", outdir) );
  TChain* chain = new TChain( treename );
  std::stringstream sTmp;
  Int_t nfile = chain->Add( infile );
  sTmp.str("");
  sTmp.clear();
  // --------------------------------------------------------------------  
  sTmp << "1";
  //sTmp << " && (" << makeCut_dmass_single(0.030, 0.030, 0.080, 0.050).c_str()  << ")"; // dmass for test
  //sTmp << " && (" << makeCut_dmass_single().c_str()  << ")"; // dmass (old)
  sTmp << " && (" << makeCut_dmass_single( 0.015, 0.015, 0.045, 0.030,
					   0.015, 0.015, 0.036, 0.024
					   ).c_str()  << ")"; // dmass
  //sTmp << " && (" << makeCut_deltam_single().c_str() << ")"; // delta m (old)
  sTmp << " && (" << makeCut_deltam_single(0.0025, 0.0025, 0.0020, 0.0020).c_str() << ")"; // delta m
  //sTmp << " && (1.80<d1_m&&d1_m<1.90) &&( (dm1<0.150&&abs(rm_dst1)==211) || (dm1<0.145&&abs(rm_dst1)!=211) )"; // for FitRange


  sTmp << " && ( rm_d1!=1102 )"  // D->2Kpipi0 veto
       << " && ( rm_d1!=1201 )"; // D->K2pipi0 veto
  sTmp << " && ( dst1pcm<2.5 )"; // D* momentum
  //sTmp << " && (" << makeCut_pi0mass_single().c_str() << ")"; // pi0 mass (old)
  sTmp << " && (" << makeCut_pi0mass_d_single   (0.015, 0.010).c_str() << ")"; // pi0 mass for D decay
  sTmp << " && (" << makeCut_pi0mass_dstr_single(0.010, 0.010).c_str() << ")"; // pi0 mass for D* decay
  sTmp << " && ( cosdl1 > -10 && cosdl1 < 5 )";

  TCut cut = sTmp.str().c_str();
  sTmp.str("");
  sTmp.clear();
  //TCut cut = "1";
  // --------------------------------------------------------------------
  TTree* tree = new TTree();
  tree = chain->CopyTree( cut );
  TTree* newtree;
  if( chain->GetEntries(cut) ) newtree = tree ->CloneTree();
  else                         newtree = chain->CloneTree(0);
  // ------------------- display ----------------------------------------
  std::cout << std::setw(60) << std::right << infile	    << " : "
	    << std::setw( 3) << std::right << nfile << " files (" << treename
	    << ", "         << std::setw(9) << std::right << chain->GetEntries()
	    << " -> "
	    << std::setw(9) << std::right << newtree->GetEntries()
	    << " [" << std::setw(2) << std::right << int(100*((double)newtree->GetEntries()/chain->GetEntries())) << "%]"
	    << ")"
	    << std::endl;
  // --------------------------------------------------------------------
  const Char_t* outfile = Form( "%s/%s_cut.root",outdir,basename.c_str() );

  TFile* rootf = new TFile( outfile, "RECREATE" );
  newtree->Write();
  rootf->Close();
  
  delete chain;
  delete tree;
  delete newtree;
  delete rootf;

  return 0;
}
