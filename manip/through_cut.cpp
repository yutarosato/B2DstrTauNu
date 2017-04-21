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
  const Char_t* treename   = "h15";
  // --------------------------------------------------------------------
  system( Form("mkdir -p %s", outdir) );
  TChain* chain = new TChain( treename );
  std::stringstream sTmp;
  Int_t nfile = chain->Add( infile );
  sTmp.str("");
  sTmp.clear();
  // --------------------------------------------------------------------  
  sTmp << "1";
  sTmp << " && (" << makeCut_dmass( 0.015, 0.015, 0.045, 0.030,
				    0.015, 0.015, 0.036, 0.024
				    ).c_str()  << ")"; // dmass
  sTmp << " && (" << makeCut_deltam(0.0025, 0.0025, 0.0020, 0.0020).c_str() << ")"; // delta m
  sTmp << " && ( ks1m<0 || (ks1m - 0.497614 < 0.010 && ks1m - 0.497614 > -0.010) )"; // Ks mass
  sTmp << " && ( ks2m<0 || (ks2m - 0.497614 < 0.010 && ks2m - 0.497614 > -0.010) )"; // Ks mass
  sTmp << " && (" << makeCut_rem().c_str()    << ")"; // remaining track/pi0/Ks
  sTmp << " && ( rm_d1!=1102 && rm_d2!=1102 )"        // D->2Kpipi0 veto
       << " && ( rm_d1!=1201 && rm_d2!=1201 )";       // D->K2pipi0 veto
  sTmp << " && ( !(rm_dst1==111 && rm_dst2==111) )";  // double slow pi0
  sTmp << " && ( (cosdl1>cosdl2 && dst1pcm<2.5 && dst2pcm<2.0) "
       <<   " || (cosdl1<cosdl2 && dst1pcm<2.0 && dst2pcm<2.5) )"; // D* momentum
  sTmp << " && ( -2<cosdlh && cosdlh<1.5 )"; // cos(theta)B-Dl
  sTmp << " && (dtchg1+dtchg2)==0 "; // charge
  sTmp << " && !(dfl1 && dfl2 && dfl1*dfl2==1)"; // flavor
  sTmp << " && (" << makeCut_pi0mass_d   (0.015, 0.010).c_str() << ")"; // pi0 mass for D decay
  sTmp << " && (" << makeCut_pi0mass_dstr(0.010, 0.010).c_str() << ")"; // pi0 mass for D* decay
  //sTmp << " && (kfd1chi2/kfd1ndf<100)&&(kfd2chi2/kfd2ndf<100)&&(kfs1chi2/kfs1ndf<100)&&(kfs2chi2/kfs2ndf<100)"; // vertex quality

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
