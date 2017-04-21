/*
 * nb_training.cc
 *
 *  Created on: Oct 5, 2009
 *      Author: Michael Prim
 *     Contact: mprim@ekp.uni-karlsruhe.de
 *
 */

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
  if( argc!=10 ) std::cerr << "wrong input" << std::endl
			   << " Usage     : ./nb_training (char*)indir_sig (char*)indir_nor (char*)indir_bkg "
			   <<                            "(char*)setname_sig (char*)setname_nor (char*)stream "
			   <<                            "(int)fl_mode (char*)tag_var (char*)fl_type"
			   << std::endl
			   << "[fl_type] : tot nor qq bb " << std::endl
			   << std::endl, abort();
  const Char_t* indir_sig   = argv[1];
  const Char_t* indir_nor   = argv[2];
  const Char_t* indir_bkg   = argv[3];
  const Char_t* setname_sig = argv[4];
  const Char_t* setname_nor = argv[5];
  const Char_t* stream      = argv[6];
  const Int_t   fl_mode    = atoi(argv[7]); // select mode
  const Char_t* tag_var    = argv[8];       // select variables
  const Char_t* fl_type    = argv[9];       // select bkg type(tot,nor)
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Char_t* treename = "h15";
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  Char_t* infile_sig = new Char_t[1024];
  //sTmp << indir_sig << "/sigMC_*_set[" << setname_sig << "]*.root";
  sTmp << indir_sig << "/sigMC_*_set?[" << setname_sig << "]*.root";
  //sTmp << indir_sig << "/sigMC_31_*_set[A]*.root"; // for test using small data
  strcpy( infile_sig, (char*)sTmp.str().c_str() );
  sTmp.str("");
  sTmp.clear();

  Char_t* infile_nor = new Char_t[1024];
  //sTmp << indir_nor << "/sigMC_*_set[" << setname_nor << "]*.root";
  sTmp << indir_nor << "/sigMC_*_set?[" << setname_nor << "]*.root";
  //sTmp << indir_nor << "/sigMC_31_*_set[A]*.root"; // for test using small data
  strcpy( infile_nor, (char*)sTmp.str().c_str() );
  sTmp.str("");
  sTmp.clear();

  Char_t* infile_bkg = new Char_t[1024];
  sTmp << indir_bkg << "/gMC_*s0[" << stream << "]*.root";
  //sTmp << indir_bkg << "/gMC_*_e021*s0[0]*.root"; // for test using small data
  strcpy( infile_bkg, (char*)sTmp.str().c_str() );
  sTmp.str("");
  sTmp.clear();
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  TChain *chain_sig = new TChain( treename );
  TChain *chain_nor = new TChain( treename );
  TChain *chain_bkg = new TChain( treename );
  Int_t nfile_sig = chain_sig->Add( infile_sig );
  Int_t nfile_nor = chain_nor->Add( infile_nor );
  Int_t nfile_bkg = chain_bkg->Add( infile_bkg );

  /*
  Int_t nfile_bkg = 0;
  nfile_bkg += chain_bkg->Add( Form(infile_bkg, "uds",     "uds"     ) );
  nfile_bkg += chain_bkg->Add( Form(infile_bkg, "charm",   "charm"   ) );
  nfile_bkg += chain_bkg->Add( Form(infile_bkg, "mixed",   "mixed"   ) );
  nfile_bkg += chain_bkg->Add( Form(infile_bkg, "charged", "charged" ) );
  */
  if( !nfile_sig ) std::cerr << "[ABORT] Check infile name : " << infile_sig << std::endl, abort();
  if( !nfile_nor ) std::cerr << "[ABORT] Check infile name : " << infile_nor << std::endl, abort();
  if( !nfile_bkg ) std::cerr << "[ABORT] Check infile name : " << infile_bkg << std::endl, abort();
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TTree* tree_sig = new TTree();
  TTree* tree_bkg = new TTree();

  //TCut cut_region   = "eecl<0.5";
  //TCut cut_region   = "eecl<1.5&&mmiss*mmiss*abs(mmiss)/mmiss>-0.5&&evis<10.0";
  //TCut cut_region   = "atan(cosdll)<-1";
  TCut cut_region   = "1";
  TCut cut_true_sig = "self==1"; // select true-sig.
  TCut cut_true_nor = "self==2"; // select true-norm.
  TCut cut_tot      = "self!=1"; // all events except true-sig.
  TCut cut_qq       = "self==-7"; // select qq events
  TCut cut_bb       = "!(self==1||self==2||sel==-7)"; // BB events except true-sig. and norm.

  tree_sig = chain_sig->CopyTree( cut_region && cut_true_sig );
  //if     ( strstr(fl_type,"nor")!=NULL ) tree_bkg = chain_bkg->CopyTree( cut_region && cut_true_nor ); //   gMC is used for bkg samples.
  if     ( strstr(fl_type,"nor")!=NULL ) tree_bkg = chain_nor->CopyTree( cut_region && cut_true_nor ); // sigMC is used for bkg samples.
  else if( strstr(fl_type,"tot")!=NULL ) tree_bkg = chain_bkg->CopyTree( cut_region && cut_tot      );
  else if( strstr(fl_type,"qq" )!=NULL ) tree_bkg = chain_bkg->CopyTree( cut_region && cut_qq       );
  else if( strstr(fl_type,"bb" )!=NULL ) tree_bkg = chain_bkg->CopyTree( cut_region && cut_bb       );
  else                                   std::cerr << "[ABORT] Invalid fl_type : " << fl_type << std::endl, abort();
  std::cout << "[cut region] " << std::endl;
  cut_region.Print();
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  std::cout << "[indir_sig] "  << std::setw(60) << std::right << indir_sig << " : " << setname_sig << std::endl
	    << "[indir_nor] "  << std::setw(60) << std::right << indir_nor << " : " << setname_nor << std::endl
	    << "[indir_bkg] "  << std::setw(60) << std::right << indir_bkg << " : " << stream      << std::endl;
  std::cout << "nfile(sig) = " << std::setw(4)  << std::right << nfile_sig << " : "
	    << "nevt (sig) = " << std::setw(10) << std::right << chain_sig->GetEntries()
	    << " -> "          << std::setw(10) << std::right << tree_sig->GetEntries()
	    << std::endl;
  std::cout << "nfile(nor) = " << std::setw(4)  << std::right << nfile_nor << " : "
	    << "nevt (nor) = " << std::setw(10) << std::right << chain_nor->GetEntries()
	    << std::endl;
  std::cout << "nfile(bkg) = " << std::setw(4)  << std::right << nfile_bkg << " : "
	    << "nevt (bkg) = " << std::setw(10) << std::right << chain_bkg->GetEntries()
	    << std::endl;
  std::cout << " -> "          << std::setw(10) << std::right << tree_bkg->GetEntries()
	    << std::endl;

  
  // -------- BEGIN OF NEUROBAYES SETUP -------------
  NeuroBayesTeacher* nb = NeuroBayesTeacher::Instance();
  nb->SetOutputFile( Form("info/nb_mode%d_%s_%s.nb",  fl_mode, tag_var, fl_type) );
  nb->SetCArrayFile( Form("info/nb_mode%d_%s_%s.icc", fl_mode, tag_var, fl_type) );

  // kind of config flags (see below)
  bool boost     = false;  // turn on/off internal boost (start with false to get first feeling of data, later turn on)
  bool bfgs      = true;  // turn on/off bfgs algorithm (keep turned on, avoids overtraining, you need good reason to turn it off, ask experts)
  bool learndiag = false; // add additional term to loss function, usually you can turn this off
  bool zero      = false; // do a zero iteration training (fast - only preprocessing)
  
  // zero=true --> Just 0 iteration training
  // zero=false boost=true --> First preprocessing and 0 iteration training, then internal boost
  // zero=false boost=false --> First preprocessing then normal network training
  
  nb->NB_DEF_TASK("CLA");     // binominal classification
  
  if( zero ){
    nb->NB_DEF_PRE(622);      // 6*0.5sigma cut, decorrelate+normalize, transform to Gaussian  (change to 422 if you want 4*0.5 sigma cut on input variables, don't change 2nd and 3rd digit)
    nb->NB_DEF_SHAPE("DIAG"); // 'OFF', 'INCL', 'TOTL' (keep "DIAG" as this is the most advanced method)
    nb->NB_DEF_ITER(0); // 0 iterations training (no real network, just preprocessing, good for first look on data)
  }else{
    if( boost ){
      nb->NB_DEF_PRE(622);      // 6*0.5sigma cut, decorrelate+normalize, transform to Gaussian (change to 422 if you want 4*0.5 sigma cut on input variables, don't change 2nd and 3rd digit)
      nb->NB_DEF_SHAPE("DIAG"); // 'OFF', 'INCL', 'TOTL' (keep "DIAG" as this is the most advanced method)
    }else{
      nb->NB_DEF_PRE(612);      // 6*0.5sigma cut, decorrelate+normalize, transform to Gaussian (if real network training, second digit has to be 1, as above change first digits to change X*0.5sigma cut, don't change 3rd digit)
      nb->NB_DEF_SHAPE("OFF");  // 'OFF', 'INCL', 'TOTL' (for network training it has to be 'OFF')
    }
    nb->NB_DEF_ITER(150); // real network training (number of interations, if BFGS algorithm is turned on and doesn't stop training before last iteration is reached, you might increase this number)
  }
  
  nb->NB_DEF_REG("REG");        // 'OFF','REG' (def) ,'ARD','ASR','ALL' (keep 'REG' to use advanced regularization)
  nb->NB_DEF_LOSS("ENTROPY");   // 'ENTROPY'(def),'QUADRATIC' (usually 'ENTROPY' gives better results when used as loss function)
  nb->NB_DEF_RTRAIN(0.95);       // use 100% of events for training (if you have high statistic, try 0.8 or 0.9 to use 20% or 10% for internal checks during training (upper right plot on first page of analysis.ps))
  nb->NB_DEF_EPOCH(100);        // weight update after 100 events (100 is a good value, no realy need to change it)
  
  if( bfgs      ) nb->NB_DEF_METHOD("BFGS");  // switch on BFGS minimization algorithm (this will stop minimazation to avoid overtraining at certain point, don't turn off if you don't have good reason)
  if( learndiag ) nb->NB_DEF_LEARNDIAG(1);    // switch on diagonal in loss function
  
  nb->NB_DEF_SPEED(1.0); // increase learning speed by factor, if changed to e.g. 2.0 network might learn faster but not that well, so keep 1.0)
  nb->NB_DEF_MAXLEARN(1.0); // upper limit to the learning rate 1.0 is default, don't change without good reason
  
  // random number seed initialisation, i has to be an odd number, the third argument is a debugging flag (sometimes different random seed can help, but usually this is not needed)
  //	int i = 4701;
  //	int j = 21;
  //	nb->NB_RANVIN(i,j,2);
  
  // individual preprocessing flags
  //    1: do nothing (forbidden)
  //    2: transform to Gaussian (forbidden, only 12 and 92)
  //    3: transform to flat variable (forbidden, only 23 and 93)
  //    4: regularised spline fit
  //    5: regularised monotonous spline fit
  //    6: azimuth angle, rotate parallel to target (not implemented)
  //    7: azimuth angle, rotate perpendicular to target (not implemented)
  //    8: use map for unordered classes
  //    9: use map for ordered classes
  //   1: equalise variable, no delta-function
  //   2: do not equalise variable, no delta-function
  //   3: equalise variable, delta-function at -999
  //   4: do not equalise variable, delta-function at -999
  //   5: correlate to width of target, equalise, no delta
  //   6: correlate to width of target, do not equalise, no delta
  //   7: correlate to width of target, equalise, delta
  //   8: correlate to width of target, do not equalise, delta
  //   9: equalise variable, set delta-function at -999 to zero
  
  // TODO: Adding all variables to the network
  // nb->SetIndividualPreproFlag(index,preproflag,varname);
  // -------- END OF NEUROBAYES SETUP -------------
  
  std::fstream var_names( Form("info/variables_mode%d_%s_%s.names",fl_mode,tag_var,fl_type),std::fstream::out );

  // 14(continuum var), 18(discrete var), 94(continuum var with delta func)
  var_names << "================================== INPUT VARIABLE SETTING ======================================" << std::endl;
  NB_manip::Set_Par_Names( nb, var_names, tag_var, fl_type );
  var_names << "==================================   # of INPUT EVENT     ======================================" << std::endl
	    << "nfile(sig) = " << std::setw(4)  << std::right << nfile_sig << " : "
	    << "nevt (sig) = " << std::setw(10) << std::right << chain_sig->GetEntries()
	    << " -> "          << std::setw(10) << std::right << tree_sig->GetEntries()
	    << std::endl
	    << "nfile(nor) = " << std::setw(4)  << std::right << nfile_nor << " : "
	    << "nevt (nor) = " << std::setw(10) << std::right << chain_nor->GetEntries()
	    << std::endl
	    << "nfile(bkg) = " << std::setw(4)  << std::right << nfile_bkg << " : "
	    << "nevt (bkg) = " << std::setw(10) << std::right << chain_bkg->GetEntries()
	    << " -> "          << std::setw(10) << std::right << tree_bkg->GetEntries()
	    << std::endl
	    << "================================================================================================" << std::endl;

  Int_t nused_sig = tree_sig->GetEntries();
  Int_t nused_bkg = tree_bkg->GetEntries();
  Int_t nused     = ( nused_sig < nused_bkg ? nused_sig : nused_bkg );

  std::cout << "[SIG]" << std::endl; NB_manip::Train_Event( tree_sig, nb, 1, fl_mode, tag_var, fl_type, var_names, nused );
  std::cout << "[BKG]" << std::endl; NB_manip::Train_Event( tree_bkg, nb, 0, fl_mode, tag_var, fl_type, var_names, nused );
  //std::cout << "[SIG]" << std::endl; NB_manip::Train_Event( tree_sig, nb, 1, fl_mode, tag_var, fl_type, var_names, (Int_t)(1.00*nused) );
  //std::cout << "[BKG]" << std::endl; NB_manip::Train_Event( tree_bkg, nb, 0, fl_mode, tag_var, fl_type, var_names, (Int_t)(0.97*nused) );
  var_names.close();
  
  nb->TrainNet();
  nb->nb_correl_signi( Form("info/correl_signi_mode%d_%s_%s.txt",fl_mode,tag_var,fl_type), Form("info/correl_signi_mode%d_%s_%s.html",fl_mode,tag_var,fl_type) );
  
  delete chain_sig;
  delete chain_bkg;
  delete tree_sig;
  delete tree_bkg;
  
  return 0;
}
