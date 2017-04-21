#include "draws_.h"

Int_t main( Int_t argc, Char_t** argv ){

  if( argc!=6 ){
    std::cerr << "wrong input" << std::endl
	      << " Usage : "
	      << argv[0]
	      << " (char*)indir (char*)outdir (char*)exp (int)stream (char*)type"
	      << std::endl;
    abort();
  }

  const Char_t* indir  = argv[1];
  const Char_t* outdir = argv[2];
  const Char_t* exp    = argv[3];
  const Int_t   stream = atoi( argv[4] );
  const Char_t* type   = argv[5];

  // --------------------------------------------------------------------
  const Char_t* treename   = "h15";
  // --------------------------------------------------------------------
  system( Form("mkdir -p %s", outdir) );
  Int_t fl_rd  = -1; // 1(rd)  0(gmc)
  
  TChain* chain = new TChain( treename );
  std::stringstream sTmp;
  if( strstr(type, "rd")!=NULL ){
    fl_rd = 1; // RD
    sTmp << indir << "/" << type << "/RD_e0" << exp << "*.root";
  }else{
    fl_rd = 0; // gMC
    sTmp << indir << "/" << type << "/gMC_" << type << "_e0" << exp << "*s0" << stream << "*.root";
  }
  Int_t nfile = chain->Add( sTmp.str().c_str() );    
  sTmp.str("");
  sTmp.clear();
  // --------------------------------------------------------------------  
  sTmp << "1";
  sTmp << " && (" << makeCut_dmass().c_str()  << ")"; // dmass
  sTmp << " && (" << makeCut_deltam().c_str() << ")"; // delta m
  sTmp << " && (" << makeCut_rem().c_str()    << ")"; // remaining track/pi0/Ks
  sTmp << " && ( rm_d1!=1102 && rm_d2!=1102 )"        // D->2Kpipi0
       << " && ( rm_d1!=1201 && rm_d2!=1201 )";       // D->K2pipi0
  sTmp << " && ( !(rm_dst1==111 && rm_dst2==111) )";  // double slow pi0
  //sTmp << " && ( (cosdl1>cosdl2 && dst1pcm<2.5 && dst2pcm<2.0) "
  //<<   " || (cosdl1<cosdl2 && dst1pcm<2.0 && dst2pcm<2.5) )"; // cos(theta)B-Dl
  //sTmp << " && ( -2<cosdlh && cosdlh<1.5 )";
  sTmp << " && ( (cosdl1_c>cosdl2_c && dst1pcm<2.5 && dst2pcm<2.0) "
       <<   " || (cosdl1_c<cosdl2_c && dst1pcm<2.0 && dst2pcm<2.5) )"; // cos(theta)B-Dl for D** ctrl samples
  sTmp << " && ( -2<cosdlh_c && cosdlh_c<1.5 )"; // for D** ctrl samples
  sTmp << " && ( rm_dst1==111 || rm_dst2==111 )"; // require at least one neutral slow pion
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
  std::cout << Form( "fl_rd(%d) : ", fl_rd)
	    << std::setw(7) << std::right << type
	    << ", s0"       << stream
	    << ", exp0"     << std::setw(3) << std::left  << exp
	    << ", "         << std::setw(3) << std::right << nfile << " files (" << treename
	    << ", "         << std::setw(9) << std::right << chain->GetEntries()
	    << " -> "
	    << std::setw(9) << std::right << newtree->GetEntries()
	    << " [" << std::setw(2) << std::right << int(100*((double)newtree->GetEntries()/chain->GetEntries())) << "%]"
	    << ")"
	    << std::endl;
  // --------------------------------------------------------------------
   if   ( fl_rd ) sTmp << Form( "%s/RD_e0%s_caseB_mergecut.root",          outdir,       exp         ); // [RD ]
   else           sTmp << Form( "%s/gMC_%s_e0%s_s0%d_caseB_mergecut.root", outdir, type, exp, stream ); // [gMC]

  Char_t outfile[1024];
  strcpy( outfile, (char*)sTmp.str().c_str() );
  sTmp.str("");
  sTmp.clear();

  TFile* rootf = new TFile( outfile, "RECREATE" );
  newtree->Write();
  rootf->Close();
  
  delete chain;
  delete tree;
  delete newtree;
  delete rootf;

  return 0;
}
