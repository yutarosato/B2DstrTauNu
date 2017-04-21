/*
 * InputNB.h
 *
 *  Created on: Oct 5, 2009
 *      Author: Michael Prim
 *     Contact: mprim@ekp.uni-karlsruhe.de
 *
 */

#ifndef READINPUT_H_
#define READINPUT_H_

//ROOT
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TLeaf.h"
#include "TMath.h"
#include "TF1.h"

//NeuroBayes
#include "NeuroBayesTeacher.hh"
#include "NeuroBayesExpert.hh"

//other stuff
#include <iostream>
#include <fstream>
#include <iomanip>
#include "math.h"
#include "string.h"

class NB_manip
{
 public:
  NB_manip();
  ~NB_manip();
  
 private:
  static void add_variable_to_network( NeuroBayesTeacher *nb, std::fstream& var_names, int index, int preproflag, const char* name );
  
 public:
  static Int_t nnVars( const Char_t* tag_var, const Char_t* fl_type );
  static void  Set_Par_Names( NeuroBayesTeacher *nb, std::fstream& var_names, const Char_t* tag_var, const Char_t* fl_type );
  static void  Input_Event ( TTree* tree, Float_t* nnInput, Int_t i, const Char_t* tag_var, const Char_t* fl_type );
  static Int_t Train_Event ( TTree* tree, NeuroBayesTeacher* nb, const Int_t fl_sb, const Int_t fl_mode, const Char_t* tag_var, const Char_t* fl_type, std::fstream& var_names, const Int_t max_nevt );
  static Int_t Expert_Event( TTree* tree, Expert*  nb, const Char_t* outfile, const Int_t fl_mode, const Char_t* tag_var, const Char_t* fl_type );

  
};

#endif /* READINPUT_H_ */
