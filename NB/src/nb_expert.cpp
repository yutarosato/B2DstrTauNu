/*
 * nb_expert.cc
 *
 *  Created on: Oct 5, 2009
 *      Author: Michael Prim
 *     Contact: mprim@ekp.uni-karlsruhe.de
 *
 */
//ROOT
#include <TChain.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TLeaf.h>
#include <TString.h>
#include <TSystem.h>

//other stuff
#include <iostream>
#include <fstream>

//my Class
#include "../../Util/Style.h"
#include "../../Util/Canvas.h"
#include "../../Util/const.h"
#include "../../Util/FitFunc.h"

#include "nb_manip.h"

int main(int argc, char *argv[]) {
  gROOT->SetBatch(true);
  TApplication app( "app", &argc, argv );
  if( app.Argc()!=6 ) std::cerr << "wrong input" << std::endl
				<< " Usage   : ./nb_training (char*)infile (char*)outdir (int)fl_mode (char*)tag (char*)fl_type" << std::endl
				<< std::endl, abort();
  const Char_t* infile     = app.Argv(1);
  const Char_t* outdir     = app.Argv(2);
  const Int_t   fl_mode    = atoi(app.Argv(3));
  const Char_t* tag_var    = app.Argv(4);
  const Char_t* fl_type    = app.Argv(5);
  std::string   basename   = gSystem->BaseName( infile );
  const Char_t* outfile    = Form( "%s/%s", outdir, basename.c_str() );
  
  TChain* tree = new TChain("h15");
  //TChain* tree = new TChain("h37");
  Int_t nfile = tree->Add( infile );
  std::cout << "nfile = " << nfile              << ", "
	    << "nevt  = " << tree->GetEntries() << ", "
	    << "( "       << infile             << " )"
	    << std::endl;
  if( !nfile ) std::cerr << "[ABORT] Check infilename : " << infile << std::endl, abort();
  // -------- BEGIN OF NEUROBAYES SETUP -------------
  Expert* nb = new Expert( Form("/gpfs/home/belle/syutaro/dstrtaunu/ana/NB/info/nb_mode%d_%s_%s.nb",fl_mode,tag_var,fl_type) );
  // -------- END OF NEUROBAYES SETUP -------------
  Int_t nentries = (Int_t)tree->GetEntries();
  NB_manip::Expert_Event( tree, nb, outfile, fl_mode, tag_var, fl_type );
  delete nb;
  tree->Delete();
  return 0;
}
