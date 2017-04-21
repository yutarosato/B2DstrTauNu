#include "draws_.h"
#include "draws_roofit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
using namespace RooFit;
const Char_t* treename  = "h15";
const Bool_t  fl_line   = true;
const Char_t* wbr       = "w1_mc*w1_bf*w2_mc*w2_bf"; // (A+a) * (B+b) = AB + aB + Ab + ab
const Char_t* wbrEstat2 = "pow(w1_mc_estat*w2_mc,2) + pow(w1_mc*w2_mc_estat,2)";
const Char_t* wbrEsyst  = "w1_mc_esyst*w2_mc + w1_mc*w2_mc_esyst";
const Int_t   tmp_dec   = 421; // 411(D+), 421(D0)
const Double_t thnevt   = 3.0; // 3.0, 20.0

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t* infile_dt = "~/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/merge_loose_masscut/RD_*.root";
const Char_t* infile_mc = "~/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/merge_loose_masscut/gMC_*.root";
const Int_t   nstream   = 6;

const Bool_t   fl_use_dststmc  = true;
const Char_t*  infile_dststmc  = "~/dstrtaunu/modules/skim_dstrtaunu/hbk/hbk20/DssMC_weight_loose_masscut_nb/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;

const Char_t* selection = "eecl<1.2";
//const Char_t* selection = "eecl<1.2 && nb_mode0_test13_nor>0.8";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// correction factor
// D
Double_t R_ss_d[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_sb_d[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_bb_d[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0};

Double_t R_ss_dE[nd_dec] = {0.0};
Double_t R_sb_dE[nd_dec] = {0.0};
Double_t R_bb_dE[nd_dec] = {0.0};
// D*
Double_t R_ss_dstr[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_sb_dstr[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_bb_dstr[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0};

Double_t R_ss_dstrE[nd_dec] = {0.0};
Double_t R_sb_dstrE[nd_dec] = {0.0};
Double_t R_bb_dstrE[nd_dec] = {0.0};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// d mass
const Char_t*  d_brname     = "d1_m";
const Char_t*  d_axisname = "m_{D} [GeV]";
      Double_t d_xmin[2]     = {1.81,1.81}; // if final state in 1st axis includes pi0, it will be expand later.
      Double_t d_xmax[2]     = {1.91,1.91};
const Int_t    d_xbin[2]     = {  40,  40};

// delta m
const Char_t*  dstr_brname   = "dm1";
const Char_t*  dstr_axisname = "#Deltam [GeV]";
const Int_t    dstr_xbin[2]  = {55,55};
      Double_t dstr_xmin[2]  = {PDGmass::pip,PDGmass::pip};
      Double_t dstr_th  [2]  = {PDGmass::pip,PDGmass::pip};
      Double_t dstr_xmax[2]  = {       0.150,       0.150};
// cos
const Char_t*  cos_brname   = "cosdl1";
const Char_t*  cos_axisname = "cos#theta_{B-D*l}";
const Int_t    cos_xbin[2]  = {  120,  120};
const Double_t cos_xmin[2]  = {-10.0,-10.0};
const Double_t cos_xmax[2]  = {  5.0,  5.0};
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Read_Data( const Char_t* infile ){
  Char_t buf[2048];
  const Int_t ndata = 21;
  Double_t data[ndata] = {0};
  ifstream fin( infile );
  if( !fin ){
    std::cout << "[WARNING] can not find a file" << std::endl;
    return;
  }
  while( !fin.eof() ){
    fin.getline( buf,1024 );
    if     ( buf[0] == '#' ) continue; // comment line
    else if( buf[0] == '*' ) break;    // finish
    else{
      std::istringstream sTmp(buf);
      sTmp >> data[ 0] >> data[ 1] >> data[ 2] >> data[ 3] >> data[ 4]
	   >> data[ 5] >> data[ 6] >> data[ 7] >> data[ 8] >> data[ 9]
	   >> data[10] >> data[11] >> data[12] >> data[13] >> data[14]
	   >> data[15] >> data[16] >> data[17] >> data[18] >> data[19]
	   >> data[20];

      if( (Int_t)data[1]==411 ){ // total D+ (calibration factor for D* is common for all D decay)
	for( Int_t i=0; i<nd_dec; i++ ){
	  if( d_dec_chg[i]==1 ){
	    R_ss_dstr [i] = data[12];
	    R_ss_dstrE[i] = data[13];
	    R_sb_dstr [i] = data[15];
	    R_sb_dstrE[i] = data[16];
	    R_bb_dstr [i] = data[18];
	    R_bb_dstrE[i] = data[19];
	  }
	}
      }else if( (Int_t)data[1]==421 ){ // total D0 (calibration factor for D* is common for all D decay)
	for( Int_t i=0; i<nd_dec; i++ ){
	  if( d_dec_chg[i]==0 ){
	    R_ss_dstr [i] = data[12];
	    R_ss_dstrE[i] = data[13];
	    R_sb_dstr [i] = data[15];
	    R_sb_dstrE[i] = data[16];
	    R_bb_dstr [i] = data[18];
	    R_bb_dstrE[i] = data[19];
	  }
	}
      }else{ // for each D decay
	R_ss_d [(Int_t)data[0]] = data[ 3];
	R_ss_dE[(Int_t)data[0]] = data[ 4];
	R_sb_d [(Int_t)data[0]] = data[ 6];
	R_sb_dE[(Int_t)data[0]] = data[ 7];
	R_bb_d [(Int_t)data[0]] = data[ 9];
	R_bb_dE[(Int_t)data[0]] = data[10];
	
	R_ss_dstr [(Int_t)data[0]] = data[12];
	R_ss_dstrE[(Int_t)data[0]] = data[13];
	R_sb_dstr [(Int_t)data[0]] = data[15];
	R_sb_dstrE[(Int_t)data[0]] = data[16];
	R_bb_dstr [(Int_t)data[0]] = data[18];
	R_bb_dstrE[(Int_t)data[0]] = data[19];
      }
    }
  }

  return;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Double_t func_deltam_threshold_slowpip( const Double_t x ){
  Double_t p[3];
  Double_t th = PDGmass::pip;
  Double_t f;
  if( x>th ){
    f = pow(x-th, 1/2.0); // threshold function in delta-M fitting
  }else{
    f = 0;
  }
  return f;
}

Double_t func_deltam_threshold_slowpi0( const Double_t x ){
  Double_t p[3];
  Double_t th = PDGmass::pi0;
  Double_t f;
  if( x>th ){
    f = pow(x-th, 1/2.0); // threshold function in delta-M fitting
  }else{
    f = 0;
  }
  return f;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetTitleOffset(1.0,"y");
  sty->SetOptStat(0);
  sty->SetLabelSize(0.030,"xyz");
  sty->SetTitleSize(0.045,"xyz");
  sty->SetOptFit(11);
  sty->SetStatW(0.16);
  sty->SetMarkerSize(0.4);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( !(app.Argc()==3 || app.Argc()==4 || app.Argc()==5|| app.Argc()==6 || app.Argc()==7 || app.Argc()==8 || app.Argc()==9 || app.Argc()==10 || app.Argc()==11)  )
    std::cerr << "Wrong input"      << std::endl
	      << " Usage : "        << app.Argv(0)
	      << " (int)fl_dec (int)fl_lep (char*)infile (int) fl_calib_d_ss (int)fl_calib_d_sb (int)fl_calib_d_bb (int)fl_calib_dstr_ss (int)fl_calib_dstr_sb (int)fl_calib_dstr_bb" << std::endl
	      << "fl_lep : -999(all), 10(e), 1(mu)"       << std::endl
	      << "* first D is selected from argument. Other D is all D0 mode removeing specified mode(first D mode)." << std::endl
	      << "* if fl_calib=true, correction factor will be calculated"
	      << std::endl, abort();
  Int_t fl_dec = atoi(app.Argv(1));
  Int_t fl_lep = atoi(app.Argv(2));
  Int_t fl_slowpi[2] = { (nominal_dmass( fl_dec)>1.866 ? 0 : 1),
			 (nominal_dmass(tmp_dec)>1.866 ? 0 : 1)}; // 0(D+pi0), 1(D0pi+)
  ///* testtttttttttt1
  if( fl_dec>999 ){
    if( fl_dec != 1200 ) d_xmin[0] = 1.72;
    d_xmax[0] = 1.98;
  }
  //*/
  /* testtttttttttt2
  if( fl_dec!=421 && fl_dec!=411 && fl_dec!=1200 && fl_dec!=200 && fl_dec!=101 && fl_dec!=12 && fl_dec!=201) d_xmin[0] = 1.72;
  if( fl_dec!=421 && fl_dec!=411 && fl_dec!=   2 && fl_dec!=102                && fl_dec!=12 && fl_dec!=201) d_xmax[0] = 1.98;
  */
  for( Int_t i=0; i<2; i++ ){
    if( !fl_slowpi[i] ){
      dstr_xmin[i]  = PDGmass::pi0;
      dstr_th  [i]  = PDGmass::pi0;
      dstr_xmax[i] -= 0.005;
    }
  }
  Double_t nominal_deltam[2] = {
    ( fl_slowpi[0] ? PDGmass::dstrp - PDGmass::d0 : PDGmass::dstrp - PDGmass::dp ),
    ( fl_slowpi[1] ? PDGmass::dstrp - PDGmass::d0 : PDGmass::dstrp - PDGmass::dp ),
  };
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( app.Argc()>3 ){
    std::cout << "[SCALING] " << app.Argv(3) << std::endl;
    Read_Data( app.Argv(3) ); // update correction factor from input files
  }
  std::cout << std::setw(28) << std::right << " DECAY MODE "      << " : "
	    << std::setw(33) << std::left << " <TRUE,TRUE D> "    << " : "
	    << std::setw(33) << std::left << " <TRUE,FAKE D> "    << " : "
	    << std::setw(33) << std::left << " <FAKE,FAKE D> "    << " : "
	    << std::setw(33) << std::left << " <TRUE,TREU D*> "   << " : "
	    << std::setw(33) << std::left << " <TRUE,FAKE D*> "   << " : "
	    << std::setw(33) << std::left << " <FAKE,FAKE D*> "
	    << std::endl;
  for( Int_t idec=0; idec<nd_dec; idec++ ) std::cout << std::setw(20) << std::right << d_dec_name   [idec] << "("
						     << std::setw( 6) << std::right << d_dec        [idec] << ") : "
						     << std::setw(15) << std::right << R_ss_d       [idec] << " + "
						     << std::setw(15) << std::right << R_ss_dE      [idec] << " : "
						     << std::setw(15) << std::right << R_sb_d       [idec] << " + "
						     << std::setw(15) << std::right << R_sb_dE      [idec] << " : "
						     << std::setw(15) << std::right << R_bb_d       [idec] << " + "
						     << std::setw(15) << std::right << R_bb_dE      [idec] << " : "
						     << std::setw(15) << std::right << R_ss_dstr    [idec] << " + "
						     << std::setw(15) << std::right << R_ss_dstrE   [idec] << " : "
						     << std::setw(15) << std::right << R_sb_dstr    [idec] << " + "
						     << std::setw(15) << std::right << R_sb_dstrE   [idec] << " : "
						     << std::setw(15) << std::right << R_bb_dstr    [idec] << " + "
						     << std::setw(15) << std::right << R_bb_dstrE   [idec] << " : "
						     << std::endl;
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Int_t fl_calib_d_ss    = 0;
  Int_t fl_calib_d_sb    = 0;
  Int_t fl_calib_d_bb    = 0;
  Int_t fl_calib_dstr_ss = 0;
  Int_t fl_calib_dstr_sb = 0;
  Int_t fl_calib_dstr_bb = 0;

  if( app.Argc()>4 ) fl_calib_d_ss    = atoi(app.Argv(4));
  if( app.Argc()>5 ) fl_calib_d_sb    = atoi(app.Argv(5));
  if( app.Argc()>6 ) fl_calib_d_bb    = atoi(app.Argv(6));
  if( app.Argc()>7 ) fl_calib_dstr_ss = atoi(app.Argv(7));
  if( app.Argc()>8 ) fl_calib_dstr_sb = atoi(app.Argv(8));
  if( app.Argc()>9 ) fl_calib_dstr_bb = atoi(app.Argv(9));

  std::cout << "[fl_calib_d_ss   ] " << fl_calib_d_ss    << std::endl;
  std::cout << "[fl_calib_d_sb   ] " << fl_calib_d_sb    << std::endl;
  std::cout << "[fl_calib_d_bb   ] " << fl_calib_d_bb    << std::endl;
  std::cout << "[fl_calib_dstr_ss] " << fl_calib_dstr_ss << std::endl;
  std::cout << "[fl_calib_dstr_sb] " << fl_calib_dstr_sb << std::endl;
  std::cout << "[fl_calib_dstr_bb] " << fl_calib_dstr_bb << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Read Data file>
  TChain* c_dt = new TChain(treename);
  std::cout << "[DT] "
	    << c_dt->Add( infile_dt ) << " files -> ";
  std::cout << c_dt->GetEntries() << " entries" << std::endl;

  TChain* c_mc = new TChain(treename);
  std::cout << "[MC] "
	    << c_mc->Add( infile_mc ) << " files -> ";
  std::cout << c_mc->GetEntries() << " entries" << std::endl;

  TChain* c_dststmc = new TChain(treename);
  std::cout << "[MC(D**)] "
	    << c_dststmc->Add( infile_dststmc ) << " files -> ";
  std::cout << c_dststmc->GetEntries()          << " entries" << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <OBSERVABLES>
  RooRealVar* dmass1  = new RooRealVar( "d1_m", "m_{D_{1}} [GeV]",   d_xmin[0],    d_xmax[0]    );
  RooRealVar* dmass2  = new RooRealVar( "d2_m", "m_{D_{2}} [GeV]",   d_xmin[1],    d_xmax[1]    );
  RooRealVar* deltam1 = new RooRealVar( "dm1",  "#Deltam_{1} [GeV]", dstr_xmin[0], dstr_xmax[0] );
  RooRealVar* deltam2 = new RooRealVar( "dm2",  "#Deltam_{2} [GeV]", dstr_xmin[1], dstr_xmax[1] );
  RooRealVar* dmass_w = new RooRealVar( "d_w",  "w_{D}",                      0.0,         10.0 );
  RooRealVar* delta_w = new RooRealVar( "dm_w", "w_{#Deltam}",                0.0,         10.0 );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  sTmp << " 1 && (";
  if( fl_dec==411 || fl_dec==421 ){ // for total
    if( fl_lep>0 ) sTmp << Form( " (abs(rm_d1lun)==%d&&rm_l1==%d&&abs(rm_d2lun)==%d&&(%f<d1_m&&d1_m<%f)&&(%f<d2_m&&d2_m<%f)&&(%f<dm1&&dm1<%f)&&(%f<dm2&&dm2<%f)) || ", fl_dec,fl_lep,tmp_dec, d_xmin[0],d_xmax[0],d_xmin[1],d_xmax[1],dstr_xmin[0],dstr_xmax[0],dstr_xmin[1],dstr_xmax[1] )
			<< Form( " (abs(rm_d2lun)==%d&&rm_l2==%d&&abs(rm_d1lun)==%d&&(%f<d1_m&&d1_m<%f)&&(%f<d2_m&&d2_m<%f)&&(%f<dm1&&dm1<%f)&&(%f<dm2&&dm2<%f))",     fl_dec,fl_lep,tmp_dec, d_xmin[1],d_xmax[1],d_xmin[0],d_xmax[0],dstr_xmin[1],dstr_xmax[1],dstr_xmin[0],dstr_xmax[0] );
    else           sTmp << Form( " (abs(rm_d1lun)==%d           &&abs(rm_d2lun)==%d&&(%f<d1_m&&d1_m<%f)&&(%f<d2_m&&d2_m<%f)&&(%f<dm1&&dm1<%f)&&(%f<dm2&&dm2<%f)) || ", fl_dec,       tmp_dec, d_xmin[0],d_xmax[0],d_xmin[1],d_xmax[1],dstr_xmin[0],dstr_xmax[0],dstr_xmin[1],dstr_xmax[1] )
			<< Form( " (abs(rm_d2lun)==%d           &&abs(rm_d1lun)==%d&&(%f<d1_m&&d1_m<%f)&&(%f<d2_m&&d2_m<%f)&&(%f<dm1&&dm1<%f)&&(%f<dm2&&dm2<%f))",     fl_dec,       tmp_dec, d_xmin[1],d_xmax[1],d_xmin[0],d_xmax[0],dstr_xmin[1],dstr_xmax[1],dstr_xmin[0],dstr_xmax[0] );
  }else{ // for each D decay
    if( fl_lep>0 ) sTmp << Form( " (rm_d1==%d&&rm_l1==%d&&rm_d2!=%d&&abs(rm_d2lun)==%d&&(%f<d1_m&&d1_m<%f)&&(%f<d2_m&&d2_m<%f)&&(%f<dm1&&dm1<%f)&&(%f<dm2&&dm2<%f)) || ", fl_dec,fl_lep,fl_dec,tmp_dec, d_xmin[0],d_xmax[0],d_xmin[1],d_xmax[1],dstr_xmin[0],dstr_xmax[0],dstr_xmin[1],dstr_xmax[1] )
			<< Form( " (rm_d2==%d&&rm_l2==%d&&rm_d1!=%d&&abs(rm_d1lun)==%d&&(%f<d1_m&&d1_m<%f)&&(%f<d2_m&&d2_m<%f)&&(%f<dm1&&dm1<%f)&&(%f<dm2&&dm2<%f))",     fl_dec,fl_lep,fl_dec,tmp_dec, d_xmin[1],d_xmax[1],d_xmin[0],d_xmax[0],dstr_xmin[1],dstr_xmax[1],dstr_xmin[0],dstr_xmax[0] );
    else           sTmp << Form( " (rm_d1==%d           &&rm_d2!=%d&&abs(rm_d2lun)==%d&&(%f<d1_m&&d1_m<%f)&&(%f<d2_m&&d2_m<%f)&&(%f<dm1&&dm1<%f)&&(%f<dm2&&dm2<%f)) || ", fl_dec,       fl_dec,tmp_dec, d_xmin[0],d_xmax[0],d_xmin[1],d_xmax[1],dstr_xmin[0],dstr_xmax[0],dstr_xmin[1],dstr_xmax[1] )
			<< Form( " (rm_d2==%d           &&rm_d1!=%d&&abs(rm_d1lun)==%d&&(%f<d1_m&&d1_m<%f)&&(%f<d2_m&&d2_m<%f)&&(%f<dm1&&dm1<%f)&&(%f<dm2&&dm2<%f))",     fl_dec,       fl_dec,tmp_dec, d_xmin[1],d_xmax[1],d_xmin[0],d_xmax[0],dstr_xmin[1],dstr_xmax[1],dstr_xmin[0],dstr_xmax[0] );
  }
  sTmp << ")";
  sTmp << Form( " && (%s)", selection );
  std::cout << sTmp.str().c_str() << std::endl;

  // <Tree>
  TTree* d_tree_dt         = c_dt     ->CopyTree( Form("(%s)",       sTmp.str().c_str()) );
  TTree* d_tree_mc         = c_mc     ->CopyTree( Form("(%s)",       sTmp.str().c_str()) );
  TTree* d_tree_dststmc    = c_dststmc->CopyTree( Form("(%s)",       sTmp.str().c_str()) );
  TTree* dstr_tree_dt      = c_dt     ->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),makeCut_dmass(0.015, 0.015, 0.045, 0.030,0.015, 0.015, 0.036, 0.024).c_str()) );
  TTree* dstr_tree_mc      = c_mc     ->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),makeCut_dmass(0.015, 0.015, 0.045, 0.030,0.015, 0.015, 0.036, 0.024).c_str()) );
  TTree* dstr_tree_dststmc = c_dststmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),makeCut_dmass(0.015, 0.015, 0.045, 0.030,0.015, 0.015, 0.036, 0.024).c_str()) );
  sTmp.str("");
  sTmp.clear();
  std::cout << "[D, dt     ] " << d_tree_dt        ->GetEntries() << " entries" << std::endl;
  std::cout << "[D, mc     ] " << d_tree_mc        ->GetEntries() << " entries" << std::endl;
  std::cout << "[D, dststmc] " << d_tree_dststmc   ->GetEntries() << " entries" << std::endl;
  std::cout << "[D*,dt     ] " << dstr_tree_dt     ->GetEntries() << " entries" << std::endl;
  std::cout << "[D*,mc     ] " << dstr_tree_mc     ->GetEntries() << " entries" << std::endl;
  std::cout << "[D*,dststmc] " << dstr_tree_dststmc->GetEntries() << " entries" << std::endl;
  TH2D* d_hist_mc    = new TH2D(    "d_hist_mc",   "d_hist_mc",    d_xbin[0],   d_xmin[0],   d_xmax[0],    d_xbin[1],   d_xmin[1],   d_xmax[1] );
  TH2D* d_hist_dt    = new TH2D(    "d_hist_dt",   "d_hist_dt",    d_xbin[0],   d_xmin[0],   d_xmax[0],    d_xbin[1],   d_xmin[1],   d_xmax[1] );
  TH2D* dstr_hist_mc = new TH2D( "dstr_hist_mc","dstr_hist_mc", dstr_xbin[0],dstr_xmin[0],dstr_xmax[0], dstr_xbin[1],dstr_xmin[1],dstr_xmax[1] );
  TH2D* dstr_hist_dt = new TH2D( "dstr_hist_dt","dstr_hist_dt", dstr_xbin[0],dstr_xmin[0],dstr_xmax[0], dstr_xbin[1],dstr_xmin[1],dstr_xmax[1] );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Read Data for D mass>
  RooDataSet* d_roohist_dt = new RooDataSet( "d_roohist_dt", "d_roohist_dt", RooArgSet(*dmass1, *dmass2) );
  for( Int_t ievt=0; ievt<d_tree_dt->GetEntries(); ievt++ ){
    d_tree_dt->GetEntry(ievt);
    if( fl_dec==421 ){ // total D0
      dmass1->setVal( d_tree_dt->GetLeaf("d1_m")->GetValue() );
      dmass2->setVal( d_tree_dt->GetLeaf("d2_m")->GetValue() );
    }else if( fl_dec==411 && fabs(d_tree_dt->GetLeaf("rm_d1lun")->GetValue())==fl_dec ){ // total D+ (not swap)
      dmass1->setVal( d_tree_dt->GetLeaf("d1_m")->GetValue() );
      dmass2->setVal( d_tree_dt->GetLeaf("d2_m")->GetValue() );
    }else if( fl_dec==411 && fabs(d_tree_dt->GetLeaf("rm_d2lun")->GetValue())==fl_dec ){ // total D+ (swap)
      dmass2->setVal( d_tree_dt->GetLeaf("d1_m")->GetValue() );
      dmass1->setVal( d_tree_dt->GetLeaf("d2_m")->GetValue() );
    }else if( d_tree_dt->GetLeaf("rm_d1")->GetValue()==fl_dec ){ // each D decay (not swap)
      dmass1->setVal( d_tree_dt->GetLeaf("d1_m")->GetValue() );
      dmass2->setVal( d_tree_dt->GetLeaf("d2_m")->GetValue() );
    }else if( d_tree_dt->GetLeaf("rm_d2")->GetValue()==fl_dec ){ // each D decay (swap)
      dmass2->setVal( d_tree_dt->GetLeaf("d1_m")->GetValue() );
      dmass1->setVal( d_tree_dt->GetLeaf("d2_m")->GetValue() );
    }else{
      std::cerr << "[ABORT] Wrong D decay mode events in data" << std::endl;
      abort();
    }
    d_roohist_dt->add( RooArgSet(*dmass1,*dmass2) );
    d_hist_dt->Fill( dmass1->getVal(), dmass2->getVal() );
  }
  d_roohist_dt->Print();

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Read Data for delta m>
  RooDataSet* dstr_roohist_dt = new RooDataSet( "dstr_roohist_dt", "dstr_roohist_dt", RooArgSet(*deltam1, *deltam2) );
  for( Int_t ievt=0; ievt<dstr_tree_dt->GetEntries(); ievt++ ){
    dstr_tree_dt->GetEntry(ievt);
    if( fl_dec==421 ){ // total D0
      deltam1->setVal( dstr_tree_dt->GetLeaf("dm1")->GetValue() );
      deltam2->setVal( dstr_tree_dt->GetLeaf("dm2")->GetValue() );
    }else if( fl_dec==411 && fabs(dstr_tree_dt->GetLeaf("rm_d1lun")->GetValue())==fl_dec ){ // total D+ (not swap)
      deltam1->setVal( dstr_tree_dt->GetLeaf("dm1")->GetValue() );
      deltam2->setVal( dstr_tree_dt->GetLeaf("dm2")->GetValue() );
    }else if( fl_dec==411 && fabs(dstr_tree_dt->GetLeaf("rm_d2lun")->GetValue())==fl_dec ){ // total D+ (swap)
      deltam2->setVal( dstr_tree_dt->GetLeaf("dm1")->GetValue() );
      deltam1->setVal( dstr_tree_dt->GetLeaf("dm2")->GetValue() );
    }else if( dstr_tree_dt->GetLeaf("rm_d1")->GetValue()==fl_dec ){ // each D decay (not swap)
      deltam1->setVal( dstr_tree_dt->GetLeaf("dm1")->GetValue() );
      deltam2->setVal( dstr_tree_dt->GetLeaf("dm2")->GetValue() );
    }else if( dstr_tree_dt->GetLeaf("rm_d2")->GetValue()==fl_dec ){ // each D decay (swap)
      deltam2->setVal( dstr_tree_dt->GetLeaf("dm1")->GetValue() );
      deltam1->setVal( dstr_tree_dt->GetLeaf("dm2")->GetValue() );
    }else{
      std::cerr << "[ABORT] Wrong D(*) decay mode events in data" << std::endl;
      abort();
    }
    dstr_roohist_dt->add( RooArgSet(*deltam1,*deltam2) );
    dstr_hist_dt->Fill( deltam1->getVal(), deltam2->getVal() );
  }
  dstr_roohist_dt->Print();

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Read MC for D mass>
  RooDataSet* d_roohist_mc        = new RooDataSet( "d_roohist_mc",        "d_roohist_mc",        RooArgSet(*dmass1, *dmass2, *dmass_w), WeightVar(*dmass_w) );
  RooDataSet* d_roohist_mc_smear1 = new RooDataSet( "d_roohist_mc_smear1", "d_roohist_mc_smear1", RooArgSet(*dmass1,          *dmass_w), WeightVar(*dmass_w) );
  RooDataSet* d_roohist_mc_smear2 = new RooDataSet( "d_roohist_mc_smear2", "d_roohist_mc_smear2", RooArgSet(         *dmass2, *dmass_w), WeightVar(*dmass_w) );
  Double_t d_init[4] = {0.0}; // {BB, SB, BS, SS}

  // MC
  for( Int_t ievt=0; ievt<d_tree_mc->GetEntries(); ievt++ ){
    d_tree_mc->GetEntry(ievt);
    if( fl_use_dststmc &&
	cal_lclass_for_syst( (Int_t)d_tree_mc->GetLeaf("semi1")->GetValue(), (Int_t)d_tree_mc->GetLeaf("gm_ddst1")->GetValue(), (Int_t)d_tree_mc->GetLeaf("rootdf1" )->GetValue() ) && 
	cal_lclass_for_syst( (Int_t)d_tree_mc->GetLeaf("semi2")->GetValue(), (Int_t)d_tree_mc->GetLeaf("gm_ddst2")->GetValue(), (Int_t)d_tree_mc->GetLeaf("rootdf2" )->GetValue() )
	) continue;
    Double_t weight = 1.0;
    weight *= d_tree_mc->GetLeaf("w1_mc")->GetValue(); // apply crrection for modeling of B1
    weight *= d_tree_mc->GetLeaf("w2_mc")->GetValue(); // apply crrection for modeling of B2
    weight *= d_tree_mc->GetLeaf("w1_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B1
    weight *= d_tree_mc->GetLeaf("w2_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B2

    if     ( d_tree_mc->GetLeaf("d1self")->GetValue()==1 && d_tree_mc->GetLeaf("d2self")->GetValue()==1 ) weight *= R_ss_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_ss_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))];
    else if( d_tree_mc->GetLeaf("d1self")->GetValue()==1 && d_tree_mc->GetLeaf("d2self")->GetValue()!=1 ) weight *= R_ss_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_bb_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))] * R_sb_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))];
    else if( d_tree_mc->GetLeaf("d1self")->GetValue()!=1 && d_tree_mc->GetLeaf("d2self")->GetValue()==1 ) weight *= R_bb_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_ss_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))] * R_sb_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))];
    else                                                                                                  weight *= R_bb_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_bb_d[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))];

    weight /= (Double_t)nstream;
    Double_t smear_dmass1;
    Double_t smear_dmass2;

    if( fl_dec==421 ){ // total D0
      dmass1->setVal( d_tree_mc->GetLeaf("d1_m")->GetValue() );
      dmass2->setVal( d_tree_mc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_mc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_mc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_mc->GetLeaf("d1_m")->GetValue()>d_xmin[0] && d_tree_mc->GetLeaf("d1_m")->GetValue()<d_xmax[0] &&
	  d_tree_mc->GetLeaf("d2_m")->GetValue()>d_xmin[1] && d_tree_mc->GetLeaf("d2_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_mc->GetLeaf("d1self")->GetValue()) + 2*(Int_t)(d_tree_mc->GetLeaf("d2self")->GetValue())] += weight; // count #events for initial values
    }else if( fl_dec==411 && fabs(d_tree_mc->GetLeaf("rm_d1lun")->GetValue())==fl_dec ){ // total D+ (not swap)
      dmass1->setVal( d_tree_mc->GetLeaf("d1_m")->GetValue() );
      dmass2->setVal( d_tree_mc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_mc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_mc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_mc->GetLeaf("d1_m")->GetValue()>d_xmin[0] && d_tree_mc->GetLeaf("d1_m")->GetValue()<d_xmax[0] &&
	  d_tree_mc->GetLeaf("d2_m")->GetValue()>d_xmin[1] && d_tree_mc->GetLeaf("d2_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_mc->GetLeaf("d1self")->GetValue()) + 2*(Int_t)(d_tree_mc->GetLeaf("d2self")->GetValue())] += weight; // count #events for initial values
    }else if( fl_dec==411 && fabs(d_tree_mc->GetLeaf("rm_d2lun")->GetValue())==fl_dec ){ // total D+ (swap)
      dmass2->setVal( d_tree_mc->GetLeaf("d1_m")->GetValue() );
      dmass1->setVal( d_tree_mc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_mc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_mc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_mc->GetLeaf("d2_m")->GetValue()>d_xmin[0] && d_tree_mc->GetLeaf("d2_m")->GetValue()<d_xmax[0] &&
	  d_tree_mc->GetLeaf("d1_m")->GetValue()>d_xmin[1] && d_tree_mc->GetLeaf("d1_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_mc->GetLeaf("d2self")->GetValue()) + 2*(Int_t)(d_tree_mc->GetLeaf("d1self")->GetValue())] += weight; // count #events for initial values
    }else if( d_tree_mc->GetLeaf("rm_d1")->GetValue()==fl_dec ){ // each D decay (not swap)
      dmass1->setVal( d_tree_mc->GetLeaf("d1_m")->GetValue() );
      dmass2->setVal( d_tree_mc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_mc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_mc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_mc->GetLeaf("d1_m")->GetValue()>d_xmin[0] && d_tree_mc->GetLeaf("d1_m")->GetValue()<d_xmax[0] &&
	  d_tree_mc->GetLeaf("d2_m")->GetValue()>d_xmin[1] && d_tree_mc->GetLeaf("d2_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_mc->GetLeaf("d1self")->GetValue()) + 2*(Int_t)(d_tree_mc->GetLeaf("d2self")->GetValue())] += weight; // count #events for initial values
    }else if( d_tree_mc->GetLeaf("rm_d2")->GetValue()==fl_dec ){ // each D decay (swap)
      dmass2->setVal( d_tree_mc->GetLeaf("d1_m")->GetValue() );
      dmass1->setVal( d_tree_mc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_mc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_mc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_mc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_mc->GetLeaf("d2_m")->GetValue()>d_xmin[0] && d_tree_mc->GetLeaf("d2_m")->GetValue()<d_xmax[0] &&
	  d_tree_mc->GetLeaf("d1_m")->GetValue()>d_xmin[1] && d_tree_mc->GetLeaf("d1_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_mc->GetLeaf("d2self")->GetValue()) + 2*(Int_t)(d_tree_mc->GetLeaf("d1self")->GetValue())] += weight; // count #events for initial values
    }else{
      std::cerr << "[ABORT] Wrong D decay mode events in mc" << std::endl;
      abort();
    }

    dmass1->setVal(smear_dmass1); // smearing MC
    dmass2->setVal(smear_dmass2); // smearing MC
    if( smear_dmass1 < d_xmin[0] || smear_dmass1 > d_xmax[0] || smear_dmass2 < d_xmin[1] || smear_dmass2 > d_xmax[1] ) continue; // smearing MC
    d_roohist_mc->add( RooArgSet(*dmass1,*dmass2), weight );
    d_hist_mc->Fill( dmass1->getVal(), dmass2->getVal(), weight );


    dmass1->setVal(smear_dmass1);
    dmass2->setVal(smear_dmass2);
    if( smear_dmass1 > d_xmin[0] && smear_dmass1 < d_xmax[0] ) d_roohist_mc_smear1->add( RooArgSet(*dmass1), weight );
    if( smear_dmass2 > d_xmin[1] && smear_dmass2 < d_xmax[1] ) d_roohist_mc_smear2->add( RooArgSet(*dmass2), weight );
    
    
  }

  // D** MC
  for( Int_t ievt=0; ievt<d_tree_dststmc->GetEntries(); ievt++ ){
    d_tree_dststmc->GetEntry(ievt);
    if( !fl_use_dststmc ) continue;
    Double_t weight = 1.0;
    weight *= d_tree_dststmc->GetLeaf("w1_mc")->GetValue(); // apply crrection for modeling of B1
    weight *= d_tree_dststmc->GetLeaf("w2_mc")->GetValue(); // apply crrection for modeling of B2
    weight *= d_tree_dststmc->GetLeaf("w1_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B1
    weight *= d_tree_dststmc->GetLeaf("w2_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B2

    if     ( d_tree_dststmc->GetLeaf("d1self")->GetValue()==1 && d_tree_dststmc->GetLeaf("d2self")->GetValue()==1 ) weight *= R_ss_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_ss_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))];
    else if( d_tree_dststmc->GetLeaf("d1self")->GetValue()==1 && d_tree_dststmc->GetLeaf("d2self")->GetValue()!=1 ) weight *= R_ss_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_bb_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))] * R_sb_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))];
    else if( d_tree_dststmc->GetLeaf("d1self")->GetValue()!=1 && d_tree_dststmc->GetLeaf("d2self")->GetValue()==1 ) weight *= R_bb_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_ss_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))] * R_sb_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))];
    else                                                                                                  weight *= R_bb_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_bb_d[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))];

    weight /= (Double_t)nstream_dststmc;
    Double_t smear_dmass1;
    Double_t smear_dmass2;

    if( fl_dec==421 ){ // total D0
      dmass1->setVal( d_tree_dststmc->GetLeaf("d1_m")->GetValue() );
      dmass2->setVal( d_tree_dststmc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_dststmc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_dststmc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_dststmc->GetLeaf("d1_m")->GetValue()>d_xmin[0] && d_tree_dststmc->GetLeaf("d1_m")->GetValue()<d_xmax[0] &&
	  d_tree_dststmc->GetLeaf("d2_m")->GetValue()>d_xmin[1] && d_tree_dststmc->GetLeaf("d2_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_dststmc->GetLeaf("d1self")->GetValue()) + 2*(Int_t)(d_tree_dststmc->GetLeaf("d2self")->GetValue())] += weight; // count #events for initial values
    }else if( fl_dec==411 && fabs(d_tree_dststmc->GetLeaf("rm_d1lun")->GetValue())==fl_dec ){ // total D+ (not swap)
      dmass1->setVal( d_tree_dststmc->GetLeaf("d1_m")->GetValue() );
      dmass2->setVal( d_tree_dststmc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_dststmc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_dststmc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_dststmc->GetLeaf("d1_m")->GetValue()>d_xmin[0] && d_tree_dststmc->GetLeaf("d1_m")->GetValue()<d_xmax[0] &&
	  d_tree_dststmc->GetLeaf("d2_m")->GetValue()>d_xmin[1] && d_tree_dststmc->GetLeaf("d2_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_dststmc->GetLeaf("d1self")->GetValue()) + 2*(Int_t)(d_tree_dststmc->GetLeaf("d2self")->GetValue())] += weight; // count #events for initial values
    }else if( fl_dec==411 && fabs(d_tree_dststmc->GetLeaf("rm_d2lun")->GetValue())==fl_dec ){ // total D+ (swap)
      dmass2->setVal( d_tree_dststmc->GetLeaf("d1_m")->GetValue() );
      dmass1->setVal( d_tree_dststmc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_dststmc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_dststmc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_dststmc->GetLeaf("d2_m")->GetValue()>d_xmin[0] && d_tree_dststmc->GetLeaf("d2_m")->GetValue()<d_xmax[0] &&
	  d_tree_dststmc->GetLeaf("d1_m")->GetValue()>d_xmin[1] && d_tree_dststmc->GetLeaf("d1_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_dststmc->GetLeaf("d2self")->GetValue()) + 2*(Int_t)(d_tree_dststmc->GetLeaf("d1self")->GetValue())] += weight; // count #events for initial values
    }else if( d_tree_dststmc->GetLeaf("rm_d1")->GetValue()==fl_dec ){ // each D decay (not swap)
      dmass1->setVal( d_tree_dststmc->GetLeaf("d1_m")->GetValue() );
      dmass2->setVal( d_tree_dststmc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_dststmc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_dststmc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_dststmc->GetLeaf("d1_m")->GetValue()>d_xmin[0] && d_tree_dststmc->GetLeaf("d1_m")->GetValue()<d_xmax[0] &&
	  d_tree_dststmc->GetLeaf("d2_m")->GetValue()>d_xmin[1] && d_tree_dststmc->GetLeaf("d2_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_dststmc->GetLeaf("d1self")->GetValue()) + 2*(Int_t)(d_tree_dststmc->GetLeaf("d2self")->GetValue())] += weight; // count #events for initial values
    }else if( d_tree_dststmc->GetLeaf("rm_d2")->GetValue()==fl_dec ){ // each D decay (swap)
      dmass2->setVal( d_tree_dststmc->GetLeaf("d1_m")->GetValue() );
      dmass1->setVal( d_tree_dststmc->GetLeaf("d2_m")->GetValue() );

      if( d_tree_dststmc->GetLeaf("d1self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_dmass2 = PDGmass::d0 + 1.17452 *( dmass2->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==1 ) smear_dmass2 = PDGmass::d0 + 1.1763  *( dmass2->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass2 = PDGmass::dp + 1.1763  *( dmass2->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass1 = dmass1->getVal();
      }
      if( d_tree_dststmc->GetLeaf("d2self")->GetValue()==1 ){
	if     ( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_dmass1 = PDGmass::d0 + 1.17452 *( dmass1->getVal()-PDGmass::d0 ); // D0 w/o pi0
	else if( d_dec_chg[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 && d_dec_pi0[dec_index((Int_t)(d_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==1 ) smear_dmass1 = PDGmass::d0 + 1.1763  *( dmass1->getVal()-PDGmass::d0 ); // D0 w/  pi0
	else                                                                                                                                                              smear_dmass1 = PDGmass::dp + 1.1763  *( dmass1->getVal()-PDGmass::dp ); // D+
      }else{
	smear_dmass2 = dmass2->getVal();
      }

      if( d_tree_dststmc->GetLeaf("d2_m")->GetValue()>d_xmin[0] && d_tree_dststmc->GetLeaf("d2_m")->GetValue()<d_xmax[0] &&
	  d_tree_dststmc->GetLeaf("d1_m")->GetValue()>d_xmin[1] && d_tree_dststmc->GetLeaf("d1_m")->GetValue()<d_xmax[1]
	  ) d_init[(Int_t)(d_tree_dststmc->GetLeaf("d2self")->GetValue()) + 2*(Int_t)(d_tree_dststmc->GetLeaf("d1self")->GetValue())] += weight; // count #events for initial values
    }else{
      std::cerr << "[ABORT] Wrong D decay mode events in mc" << std::endl;
      abort();
    }

    dmass1->setVal(smear_dmass1); // smearing MC
    dmass2->setVal(smear_dmass2); // smearing MC
    if( smear_dmass1 < d_xmin[0] || smear_dmass1 > d_xmax[0] || smear_dmass2 < d_xmin[1] || smear_dmass2 > d_xmax[1] ) continue; // smearing MC
    d_roohist_mc->add( RooArgSet(*dmass1,*dmass2), weight );
    d_hist_mc->Fill( dmass1->getVal(), dmass2->getVal(), weight );


    dmass1->setVal(smear_dmass1);
    dmass2->setVal(smear_dmass2);
    if( smear_dmass1 > d_xmin[0] && smear_dmass1 < d_xmax[0] ) d_roohist_mc_smear1->add( RooArgSet(*dmass1), weight );
    if( smear_dmass2 > d_xmin[1] && smear_dmass2 < d_xmax[1] ) d_roohist_mc_smear2->add( RooArgSet(*dmass2), weight );
    
    
  }
  d_roohist_mc->Print();

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Read MC for delta m>
  RooDataSet* dstr_roohist_mc        = new RooDataSet( "dstr_roohist_mc",        "dstr_roohist_mc",        RooArgSet(*deltam1, *deltam2, *delta_w), WeightVar(*delta_w) );
  RooDataSet* dstr_roohist_mc_smear1 = new RooDataSet( "dstr_roohist_mc_smear1", "dstr_roohist_mc_smear1", RooArgSet(*deltam1,           *delta_w), WeightVar(*delta_w) );
  RooDataSet* dstr_roohist_mc_smear2 = new RooDataSet( "dstr_roohist_mc_smear2", "dstr_roohist_mc_smear2", RooArgSet(          *deltam2, *delta_w), WeightVar(*delta_w) );
  Double_t dstr_init[4] = {0.0}; // {BB, SB, BS, SS}

  // MC
  for( Int_t ievt=0; ievt<dstr_tree_mc->GetEntries(); ievt++ ){
    dstr_tree_mc->GetEntry(ievt);
    if( fl_use_dststmc &&
	cal_lclass_for_syst( (Int_t)dstr_tree_mc->GetLeaf("semi1")->GetValue(), (Int_t)dstr_tree_mc->GetLeaf("gm_ddst1")->GetValue(), (Int_t)dstr_tree_mc->GetLeaf("rootdf1" )->GetValue() ) && 
	cal_lclass_for_syst( (Int_t)dstr_tree_mc->GetLeaf("semi2")->GetValue(), (Int_t)dstr_tree_mc->GetLeaf("gm_ddst2")->GetValue(), (Int_t)dstr_tree_mc->GetLeaf("rootdf2" )->GetValue() )
	) continue;
    Double_t weight = 1.0;
    weight *= dstr_tree_mc->GetLeaf("w1_mc")->GetValue(); // apply crrection for modeling of B1
    weight *= dstr_tree_mc->GetLeaf("w2_mc")->GetValue(); // apply crrection for modeling of B2
    weight *= dstr_tree_mc->GetLeaf("w1_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B1
    weight *= dstr_tree_mc->GetLeaf("w2_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B2

    if     ( dstr_tree_mc->GetLeaf("d1self")->GetValue()==1 && dstr_tree_mc->GetLeaf("d2self")->GetValue()==1 )     weight *= R_ss_d   [dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_ss_d   [dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))];
    else if( dstr_tree_mc->GetLeaf("d1self")->GetValue()==1 && dstr_tree_mc->GetLeaf("d2self")->GetValue()!=1 )     weight *= R_ss_d   [dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_bb_d   [dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))] * R_sb_d[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))];
    else if( dstr_tree_mc->GetLeaf("d1self")->GetValue()!=1 && dstr_tree_mc->GetLeaf("d2self")->GetValue()==1 )     weight *= R_bb_d   [dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_ss_d   [dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))] * R_sb_d[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))];
    else                                                                                                            weight *= R_bb_d   [dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_bb_d   [dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))];
    if     ( dstr_tree_mc->GetLeaf("dst1self")->GetValue()==1 && dstr_tree_mc->GetLeaf("dst2self")->GetValue()==1 ) weight *= R_ss_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_ss_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))];
    else if( dstr_tree_mc->GetLeaf("dst1self")->GetValue()==1 && dstr_tree_mc->GetLeaf("dst2self")->GetValue()!=1 ) weight *= R_ss_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_bb_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))] * R_sb_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))];
    else if( dstr_tree_mc->GetLeaf("dst1self")->GetValue()!=1 && dstr_tree_mc->GetLeaf("dst2self")->GetValue()==1 ) weight *= R_bb_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_ss_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))] * R_sb_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))];
    else                                                                                                            weight *= R_bb_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))] * R_bb_dstr[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))];

    weight /= (Double_t)nstream;

    Double_t smear_deltam1;
    Double_t smear_deltam2;
    if( fl_dec==421 ){
      deltam1->setVal( dstr_tree_mc->GetLeaf("dm1")->GetValue() );
      deltam2->setVal( dstr_tree_mc->GetLeaf("dm2")->GetValue() );

   
      if( dstr_tree_mc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }
      if( dstr_tree_mc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }
      
      dstr_init[(Int_t)(dstr_tree_mc->GetLeaf("dst1self")->GetValue()) + 2*(Int_t)(dstr_tree_mc->GetLeaf("dst2self")->GetValue())] += weight; // count #events for initial values
      
    }else if( fl_dec==411 && fabs(dstr_tree_mc->GetLeaf("rm_d1lun")->GetValue())==fl_dec ){ // not swap
      deltam1->setVal( dstr_tree_mc->GetLeaf("dm1")->GetValue() );
      deltam2->setVal( dstr_tree_mc->GetLeaf("dm2")->GetValue() );
      if( dstr_tree_mc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }
      if( dstr_tree_mc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }

      dstr_init[(Int_t)(dstr_tree_mc->GetLeaf("dst1self")->GetValue()) + 2*(Int_t)(dstr_tree_mc->GetLeaf("dst2self")->GetValue())] += weight; // count #events for initial values
    }else if( fl_dec==411 && fabs(dstr_tree_mc->GetLeaf("rm_d2lun")->GetValue())==fl_dec ){ // swap
      deltam2->setVal( dstr_tree_mc->GetLeaf("dm1")->GetValue() );
      deltam1->setVal( dstr_tree_mc->GetLeaf("dm2")->GetValue() );

      if( dstr_tree_mc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }
      if( dstr_tree_mc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }
      
      dstr_init[(Int_t)(dstr_tree_mc->GetLeaf("dst2self")->GetValue()) + 2*(Int_t)(dstr_tree_mc->GetLeaf("dst1self")->GetValue())] += weight; // count #events for initial values
    }else if( dstr_tree_mc->GetLeaf("rm_d1")->GetValue()==fl_dec ){ // not swap
      deltam1->setVal( dstr_tree_mc->GetLeaf("dm1")->GetValue() );
      deltam2->setVal( dstr_tree_mc->GetLeaf("dm2")->GetValue() );

      if( dstr_tree_mc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }
      if( dstr_tree_mc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }
      dstr_init[(Int_t)(dstr_tree_mc->GetLeaf("dst1self")->GetValue()) + 2*(Int_t)(dstr_tree_mc->GetLeaf("dst2self")->GetValue())] += weight; // count #events for initial values
    }else if( dstr_tree_mc->GetLeaf("rm_d2")->GetValue()==fl_dec ){ // swap
      deltam2->setVal( dstr_tree_mc->GetLeaf("dm1")->GetValue() );
      deltam1->setVal( dstr_tree_mc->GetLeaf("dm2")->GetValue() );

      if( dstr_tree_mc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }
      if( dstr_tree_mc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_mc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }

      dstr_init[(Int_t)(dstr_tree_mc->GetLeaf("dst2self")->GetValue()) + 2*(Int_t)(dstr_tree_mc->GetLeaf("dst1self")->GetValue())] += weight; // count #events for initial values
    }else{
      std::cerr << "[ABORT] Wrong D(*) decay mode events in mc" << std::endl;
      abort();
    }


    deltam1->setVal(smear_deltam1); // smearing MC
    deltam2->setVal(smear_deltam2); // smearing MC
    if( smear_deltam1 < dstr_xmin[0] || smear_deltam1 > dstr_xmax[0] || smear_deltam2 < dstr_xmin[1] || smear_deltam2 > dstr_xmax[1] ) continue; // smearing MC
    dstr_roohist_mc->add( RooArgSet(*deltam1,*deltam2), weight );
    dstr_hist_mc->Fill( deltam1->getVal(), deltam2->getVal(), weight );

    deltam1->setVal(smear_deltam1);
    deltam2->setVal(smear_deltam2);

    if( smear_deltam1 > dstr_xmin[0] && smear_deltam1 < dstr_xmax[0] ) dstr_roohist_mc_smear1->add( RooArgSet(*deltam1), weight );
    if( smear_deltam2 > dstr_xmin[1] && smear_deltam2 < dstr_xmax[1] ) dstr_roohist_mc_smear2->add( RooArgSet(*deltam2), weight );
    
  }

    // D** MC
  for( Int_t ievt=0; ievt<dstr_tree_dststmc->GetEntries(); ievt++ ){
    dstr_tree_dststmc->GetEntry(ievt);
    if( !fl_use_dststmc ) continue;
    Double_t weight = 1.0;
    weight *= dstr_tree_dststmc->GetLeaf("w1_mc")->GetValue(); // apply crrection for modeling of B1
    weight *= dstr_tree_dststmc->GetLeaf("w2_mc")->GetValue(); // apply crrection for modeling of B2
    weight *= dstr_tree_dststmc->GetLeaf("w1_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B1
    weight *= dstr_tree_dststmc->GetLeaf("w2_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B2

    if     ( dstr_tree_dststmc->GetLeaf("d1self")->GetValue()==1 && dstr_tree_dststmc->GetLeaf("d2self")->GetValue()==1 )     weight *= R_ss_d   [dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_ss_d   [dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))];
    else if( dstr_tree_dststmc->GetLeaf("d1self")->GetValue()==1 && dstr_tree_dststmc->GetLeaf("d2self")->GetValue()!=1 )     weight *= R_ss_d   [dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_bb_d   [dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))] * R_sb_d[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))];
    else if( dstr_tree_dststmc->GetLeaf("d1self")->GetValue()!=1 && dstr_tree_dststmc->GetLeaf("d2self")->GetValue()==1 )     weight *= R_bb_d   [dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_ss_d   [dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))] * R_sb_d[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))];
    else                                                                                                            weight *= R_bb_d   [dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_bb_d   [dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))];
    if     ( dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()==1 && dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()==1 ) weight *= R_ss_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_ss_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))];
    else if( dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()==1 && dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()!=1 ) weight *= R_ss_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_bb_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))] * R_sb_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))];
    else if( dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()!=1 && dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()==1 ) weight *= R_bb_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_ss_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))] * R_sb_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))];
    else                                                                                                            weight *= R_bb_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))] * R_bb_dstr[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))];

    weight /= (Double_t)nstream_dststmc;

    Double_t smear_deltam1;
    Double_t smear_deltam2;
    if( fl_dec==421 ){
      deltam1->setVal( dstr_tree_dststmc->GetLeaf("dm1")->GetValue() );
      deltam2->setVal( dstr_tree_dststmc->GetLeaf("dm2")->GetValue() );

   
      if( dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }
      if( dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }
      
      dstr_init[(Int_t)(dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()) + 2*(Int_t)(dstr_tree_dststmc->GetLeaf("dst2self")->GetValue())] += weight; // count #events for initial values
      
    }else if( fl_dec==411 && fabs(dstr_tree_dststmc->GetLeaf("rm_d1lun")->GetValue())==fl_dec ){ // not swap
      deltam1->setVal( dstr_tree_dststmc->GetLeaf("dm1")->GetValue() );
      deltam2->setVal( dstr_tree_dststmc->GetLeaf("dm2")->GetValue() );
      if( dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }
      if( dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }

      dstr_init[(Int_t)(dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()) + 2*(Int_t)(dstr_tree_dststmc->GetLeaf("dst2self")->GetValue())] += weight; // count #events for initial values
    }else if( fl_dec==411 && fabs(dstr_tree_dststmc->GetLeaf("rm_d2lun")->GetValue())==fl_dec ){ // swap
      deltam2->setVal( dstr_tree_dststmc->GetLeaf("dm1")->GetValue() );
      deltam1->setVal( dstr_tree_dststmc->GetLeaf("dm2")->GetValue() );

      if( dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }
      if( dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }
      
      dstr_init[(Int_t)(dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()) + 2*(Int_t)(dstr_tree_dststmc->GetLeaf("dst1self")->GetValue())] += weight; // count #events for initial values
    }else if( dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()==fl_dec ){ // not swap
      deltam1->setVal( dstr_tree_dststmc->GetLeaf("dm1")->GetValue() );
      deltam2->setVal( dstr_tree_dststmc->GetLeaf("dm2")->GetValue() );

      if( dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }
      if( dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }
      dstr_init[(Int_t)(dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()) + 2*(Int_t)(dstr_tree_dststmc->GetLeaf("dst2self")->GetValue())] += weight; // count #events for initial values
    }else if( dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()==fl_dec ){ // swap
      deltam2->setVal( dstr_tree_dststmc->GetLeaf("dm1")->GetValue() );
      deltam1->setVal( dstr_tree_dststmc->GetLeaf("dm2")->GetValue() );

      if( dstr_tree_dststmc->GetLeaf("dst1self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.26479 *(deltam2->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d1")->GetValue()))]==0 ) smear_deltam2 = 0.145344 + 1.20000 *(deltam2->getVal()-0.145344); // D0
	else                                                                               smear_deltam2 = 0.140648 + 0.994473*(deltam2->getVal()-0.140648); // D+
      }else{
	smear_deltam2 = deltam2->getVal();
      }
      if( dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()==1 ){
	//if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.26479 *(deltam1->getVal()-0.145344); // D0
	if( d_dec_chg[dec_index((Int_t)(dstr_tree_dststmc->GetLeaf("rm_d2")->GetValue()))]==0 ) smear_deltam1 = 0.145344 + 1.20000 *(deltam1->getVal()-0.145344); // D0
	else                                                                               smear_deltam1 = 0.140648 + 0.994473*(deltam1->getVal()-0.140648); // D+
      }else{
	smear_deltam1 = deltam1->getVal();
      }

      dstr_init[(Int_t)(dstr_tree_dststmc->GetLeaf("dst2self")->GetValue()) + 2*(Int_t)(dstr_tree_dststmc->GetLeaf("dst1self")->GetValue())] += weight; // count #events for initial values
    }else{
      std::cerr << "[ABORT] Wrong D(*) decay mode events in mc" << std::endl;
      abort();
    }


    deltam1->setVal(smear_deltam1); // smearing MC
    deltam2->setVal(smear_deltam2); // smearing MC
    if( smear_deltam1 < dstr_xmin[0] || smear_deltam1 > dstr_xmax[0] || smear_deltam2 < dstr_xmin[1] || smear_deltam2 > dstr_xmax[1] ) continue; // smearing MC
    dstr_roohist_mc->add( RooArgSet(*deltam1,*deltam2), weight );
    dstr_hist_mc->Fill( deltam1->getVal(), deltam2->getVal(), weight );

    deltam1->setVal(smear_deltam1);
    deltam2->setVal(smear_deltam2);

    if( smear_deltam1 > dstr_xmin[0] && smear_deltam1 < dstr_xmax[0] ) dstr_roohist_mc_smear1->add( RooArgSet(*deltam1), weight );
    if( smear_deltam2 > dstr_xmin[1] && smear_deltam2 < dstr_xmax[1] ) dstr_roohist_mc_smear2->add( RooArgSet(*deltam2), weight );
    
  }
  dstr_roohist_mc->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 4, 3 );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TFile file_dmass1 ( Form("pdf/dmass/d1_m_%d.root", fl_dec ) );
  TFile file_dmass2 ( Form("pdf/dmass/d1_m_%d.root", tmp_dec) );
  // need to special treatment
  // for 102 and 310 ( resolution can't be estimated due to too bas S/N )
  // for 1110        ( shape      can't be estimated by false converge  )
  // for total D0, function of 1101 is used temporarily and it will be adjusted later.
  TFile file_deltam1( Form("pdf/deltam/dm1_%d.root", (fl_dec==102 || fl_dec==310 ?  411 : (fl_dec==421 ? 1101 : (fl_dec==1110 ? 110 : fl_dec)))) );
  TFile file_deltam2( Form("pdf/deltam/dm1_%d.root", (tmp_dec==421               ? 1101 : tmp_dec                                             )) );
  
  if( file_dmass1.IsZombie () ) std::cerr << "[ABORT] can not find input-file for dmass1-PDF"  << std::endl, abort();
  if( file_dmass2.IsZombie () ) std::cerr << "[ABORT] can not find input-file for dmass2-PDF"  << std::endl, abort();
  if( file_deltam1.IsZombie() ) std::cerr << "[ABORT] can not find input-file for deltam1-PDF" << std::endl, abort();
  if( file_deltam2.IsZombie() ) std::cerr << "[ABORT] can not find input-file for deltam2-PDF" << std::endl, abort();
  // function of Dat is also used for MC, because MC is already smeared.
  TF1* hz_d1_func_pdf_mc    = (TF1*)file_dmass1.Get ( Form("func_sig_dt_%d",fl_dec ) );
  TF1* hz_d2_func_pdf_mc    = (TF1*)file_dmass2.Get ( Form("func_sig_dt_%d",tmp_dec) );
  TF1* hz_dstr1_func_pdf_mc = (TF1*)file_deltam1.Get( Form("func_sig_dt_%d",(fl_dec==102 || fl_dec==310 ?  411 : (fl_dec==421 ? 1101 : (fl_dec==1110 ? 110 : fl_dec))) ) );
  TF1* hz_dstr2_func_pdf_mc = (TF1*)file_deltam2.Get( Form("func_sig_dt_%d",(tmp_dec==421               ? 1101 : tmp_dec                                             ) ) );
  TF1* hz_d1_func_pdf_dt    = (TF1*)file_dmass1.Get ( Form("func_sig_dt_%d",fl_dec ) );
  TF1* hz_d2_func_pdf_dt    = (TF1*)file_dmass2.Get ( Form("func_sig_dt_%d",tmp_dec) );
  TF1* hz_dstr1_func_pdf_dt = (TF1*)file_deltam1.Get( Form("func_sig_dt_%d",(fl_dec==102 || fl_dec==310 ?  411 : (fl_dec==421 ? 1101 : (fl_dec==1110 ? 110 : fl_dec))) ) );
  TF1* hz_dstr2_func_pdf_dt = (TF1*)file_deltam2.Get( Form("func_sig_dt_%d",(tmp_dec==421               ? 1101 : tmp_dec                                             ) ) );

  Int_t sel_fun_d[2]    = {
    ( ( fl_dec>999 || nominal_dmass( fl_dec)==PDGmass::dp || fl_dec ==411 || fl_dec ==421 ) ? 30000 : 30 ),
    ( (tmp_dec>999 || nominal_dmass(tmp_dec)==PDGmass::dp || tmp_dec==411 || tmp_dec==421 ) ? 30000 : 30 ),
  };
  Int_t sel_fun_dstr[2] = {40000,40000};
  TF1*    d1_func_pdf_mc = new TF1(    "d1_func_sig_mc", make_func(sel_fun_d[0]   ),    d_xmin[0],   d_xmax[0], n_fitfunc_par(sel_fun_d[0]   ) );
  TF1*    d2_func_pdf_mc = new TF1(    "d2_func_sig_mc", make_func(sel_fun_d[1]   ),    d_xmin[1],   d_xmax[1], n_fitfunc_par(sel_fun_d[1]   ) );
  TF1*    d1_func_pdf_dt = new TF1(    "d1_func_sig_dt", make_func(sel_fun_d[0]   ),    d_xmin[0],   d_xmax[0], n_fitfunc_par(sel_fun_d[0]   ) );
  TF1*    d2_func_pdf_dt = new TF1(    "d2_func_sig_dt", make_func(sel_fun_d[1]   ),    d_xmin[1],   d_xmax[1], n_fitfunc_par(sel_fun_d[1]   ) );
  TF1* dstr1_func_pdf_mc = new TF1( "dstr1_func_sig_mc", make_func(sel_fun_dstr[0]), dstr_xmin[0],dstr_xmax[0], n_fitfunc_par(sel_fun_dstr[0]) );
  TF1* dstr2_func_pdf_mc = new TF1( "dstr2_func_sig_mc", make_func(sel_fun_dstr[1]), dstr_xmin[1],dstr_xmax[1], n_fitfunc_par(sel_fun_dstr[1]) );
  TF1* dstr1_func_pdf_dt = new TF1( "dstr1_func_sig_dt", make_func(sel_fun_dstr[0]), dstr_xmin[0],dstr_xmax[0], n_fitfunc_par(sel_fun_dstr[0]) );
  TF1* dstr2_func_pdf_dt = new TF1( "dstr2_func_sig_dt", make_func(sel_fun_dstr[1]), dstr_xmin[1],dstr_xmax[1], n_fitfunc_par(sel_fun_dstr[1]) );
  if(    d1_func_pdf_mc->GetNpar() !=    hz_d1_func_pdf_mc->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for D1 mass(mc) " << std::endl, abort();
  if(    d2_func_pdf_mc->GetNpar() !=    hz_d2_func_pdf_mc->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for D2 mass(mc) " << std::endl, abort();
  if(    d1_func_pdf_dt->GetNpar() !=    hz_d1_func_pdf_dt->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for D1 mass(dt) " << std::endl, abort();
  if(    d2_func_pdf_dt->GetNpar() !=    hz_d2_func_pdf_dt->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for D2 mass(dt) " << std::endl, abort();
  if( dstr1_func_pdf_mc->GetNpar() != hz_dstr1_func_pdf_mc->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for Deltam1(mc) " << std::endl, abort();
  if( dstr2_func_pdf_mc->GetNpar() != hz_dstr2_func_pdf_mc->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for Deltam2(mc) " << std::endl, abort();
  if( dstr1_func_pdf_dt->GetNpar() != hz_dstr1_func_pdf_dt->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for Deltam1(dt) " << std::endl, abort();
  if( dstr2_func_pdf_dt->GetNpar() != hz_dstr2_func_pdf_dt->GetNpar() ) std::cerr << "[ABORT] Wrong # of parameters for Deltam2(dt) " << std::endl, abort();
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_d[0]   ); i++ )    d1_func_pdf_mc->SetParameter(i,    hz_d1_func_pdf_mc->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_d[1]   ); i++ )    d2_func_pdf_mc->SetParameter(i,    hz_d2_func_pdf_mc->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_d[0]   ); i++ )    d1_func_pdf_dt->SetParameter(i,    hz_d1_func_pdf_dt->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_d[1]   ); i++ )    d2_func_pdf_dt->SetParameter(i,    hz_d2_func_pdf_dt->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_dstr[0]); i++ ) dstr1_func_pdf_mc->SetParameter(i, hz_dstr1_func_pdf_mc->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_dstr[1]); i++ ) dstr2_func_pdf_mc->SetParameter(i, hz_dstr2_func_pdf_mc->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_dstr[0]); i++ ) dstr1_func_pdf_dt->SetParameter(i, hz_dstr1_func_pdf_dt->GetParameter(i));
  for( Int_t i=0; i<n_fitfunc_par(sel_fun_dstr[1]); i++ ) dstr2_func_pdf_dt->SetParameter(i, hz_dstr2_func_pdf_dt->GetParameter(i));

  // small effect by total shape except specified mode
  if( tmp_dec==421 ){
    if( fl_dec==101 || fl_dec==301 ){
      d2_func_pdf_mc->SetParameter(4, 1.10*d2_func_pdf_mc->GetParameter(4));
      d2_func_pdf_dt->SetParameter(4, 1.10*d2_func_pdf_dt->GetParameter(4));
      d2_func_pdf_mc->SetParameter(7, 1.10*d2_func_pdf_mc->GetParameter(7));
      d2_func_pdf_dt->SetParameter(7, 1.10*d2_func_pdf_dt->GetParameter(7));
    }else if( fl_dec==1101 ){
      d2_func_pdf_mc->SetParameter(4, 0.87*d2_func_pdf_mc->GetParameter(4));
      d2_func_pdf_dt->SetParameter(4, 0.87*d2_func_pdf_dt->GetParameter(4));
      d2_func_pdf_mc->SetParameter(7, 0.87*d2_func_pdf_mc->GetParameter(7));
      d2_func_pdf_dt->SetParameter(7, 0.87*d2_func_pdf_dt->GetParameter(7));
    }else if( fl_dec==411 || fl_dec==102 || fl_dec==201 ){
      d2_func_pdf_mc->SetParameter(4, 0.92*d2_func_pdf_mc->GetParameter(4));
      d2_func_pdf_dt->SetParameter(4, 0.92*d2_func_pdf_dt->GetParameter(4));
      d2_func_pdf_mc->SetParameter(7, 0.92*d2_func_pdf_mc->GetParameter(7));
      d2_func_pdf_dt->SetParameter(7, 0.92*d2_func_pdf_dt->GetParameter(7));
    }
  }

  
  // Since function of 1101 is used for total D0 temporarily, it should be adjusted.
  if( fl_dec==421 ){
    dstr1_func_pdf_mc->SetParameter(2, 0.85*dstr1_func_pdf_mc->GetParameter(2));
    dstr1_func_pdf_dt->SetParameter(2, 0.85*dstr1_func_pdf_dt->GetParameter(2));
  }
  if( tmp_dec==421 ){
    dstr2_func_pdf_mc->SetParameter(2, 0.85*dstr2_func_pdf_mc->GetParameter(2));
    dstr2_func_pdf_dt->SetParameter(2, 0.85*dstr2_func_pdf_dt->GetParameter(2));
  }

  d1_func_pdf_mc   ->Print();
  d2_func_pdf_mc   ->Print();
  d1_func_pdf_dt   ->Print();
  d2_func_pdf_dt   ->Print();
  dstr1_func_pdf_mc->Print();
  dstr2_func_pdf_mc->Print();
  dstr1_func_pdf_dt->Print();
  dstr2_func_pdf_dt->Print();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <PDF COMPONENT FOR DMASS>
  TF1* d1_func_sig_s1s2_mc = (TF1*)d1_func_pdf_mc->Clone(); d1_func_sig_s1s2_mc->SetName("d1_s1s2_mc"); RooAbsPdf* d1_pdf_sig_s1s2_mc = bindPdf( d1_func_sig_s1s2_mc, *dmass1 );
  TF1* d1_func_sig_s1b2_mc = (TF1*)d1_func_pdf_mc->Clone(); d1_func_sig_s1b2_mc->SetName("d1_s1b2_mc"); RooAbsPdf* d1_pdf_sig_s1b2_mc = bindPdf( d1_func_sig_s1b2_mc, *dmass1 );
  TF1* d2_func_sig_s1s2_mc = (TF1*)d2_func_pdf_mc->Clone(); d2_func_sig_s1s2_mc->SetName("d2_s1s2_mc"); RooAbsPdf* d2_pdf_sig_s1s2_mc = bindPdf( d2_func_sig_s1s2_mc, *dmass2 );
  TF1* d2_func_sig_b1s2_mc = (TF1*)d2_func_pdf_mc->Clone(); d2_func_sig_b1s2_mc->SetName("d2_b1s2_mc"); RooAbsPdf* d2_pdf_sig_b1s2_mc = bindPdf( d2_func_sig_b1s2_mc, *dmass2 );

  TF1* d1_func_sig_s1s2_dt = (TF1*)d1_func_pdf_dt->Clone(); d1_func_sig_s1s2_dt->SetName("d1_s1s2_dt"); RooAbsPdf* d1_pdf_sig_s1s2_dt = bindPdf( d1_func_sig_s1s2_dt, *dmass1 );
  TF1* d1_func_sig_s1b2_dt = (TF1*)d1_func_pdf_dt->Clone(); d1_func_sig_s1b2_dt->SetName("d1_s1b2_dt"); RooAbsPdf* d1_pdf_sig_s1b2_dt = bindPdf( d1_func_sig_s1b2_dt, *dmass1 );
  TF1* d2_func_sig_s1s2_dt = (TF1*)d2_func_pdf_dt->Clone(); d2_func_sig_s1s2_dt->SetName("d2_s1s2_dt"); RooAbsPdf* d2_pdf_sig_s1s2_dt = bindPdf( d2_func_sig_s1s2_dt, *dmass2 );
  TF1* d2_func_sig_b1s2_dt = (TF1*)d2_func_pdf_dt->Clone(); d2_func_sig_b1s2_dt->SetName("d2_b1s2_dt"); RooAbsPdf* d2_pdf_sig_b1s2_dt = bindPdf( d2_func_sig_b1s2_dt, *dmass2 );


  RooRealVar* d1_pol_bkg_b1s2_c1_mc = new RooRealVar ( "c_{1,d1,b1s2,mc}", "c_{1,d1,b1s2,mc}", -0.5, -50, 50); RooPolynomial* d1_pdf_bkg_b1s2_mc = new RooPolynomial("d1_bkg_b1s2_mc","d1_bkg_b1s2_mc", *dmass1, *d1_pol_bkg_b1s2_c1_mc );
  RooRealVar* d2_pol_bkg_s1b2_c1_mc = new RooRealVar ( "c_{1,d2,s1b2,mc}", "c_{1,d2,s1b2,mc}", -0.5, -50, 50); RooPolynomial* d2_pdf_bkg_s1b2_mc = new RooPolynomial("d2_bkg_s1b2_mc","d2_bkg_s1b2_mc", *dmass2, *d2_pol_bkg_s1b2_c1_mc );
  
  RooRealVar* d1_pol_bkg_b1s2_c1_dt = new RooRealVar ( "c_{1,d1,b1s2,dt}", "c_{1,d1,b1s2,dt}", -0.5, -50, 50); RooPolynomial* d1_pdf_bkg_b1s2_dt = new RooPolynomial("d1_bkg_b1s2_dt","d1_bkg_b1s2_dt", *dmass1, *d1_pol_bkg_b1s2_c1_dt );
  RooRealVar* d2_pol_bkg_s1b2_c1_dt = new RooRealVar ( "c_{1,d2,s1b2,dt}", "c_{1,d2,s1b2,dt}", -0.5, -50, 50); RooPolynomial* d2_pdf_bkg_s1b2_dt = new RooPolynomial("d2_bkg_s1b2_dt","d2_bkg_s1b2_dt", *dmass2, *d2_pol_bkg_s1b2_c1_dt );
  
  RooProdPdf* d_pdf_s1s2_mc = new RooProdPdf( "d_pdf_s1s2_mc", "d_pdf_s1s2_mc", RooArgSet( *d1_pdf_sig_s1s2_mc, *d2_pdf_sig_s1s2_mc) );
  RooProdPdf* d_pdf_s1b2_mc = new RooProdPdf( "d_pdf_s1b2_mc", "d_pdf_s1b2_mc", RooArgSet( *d1_pdf_sig_s1b2_mc, *d2_pdf_bkg_s1b2_mc) );
  RooProdPdf* d_pdf_b1s2_mc = new RooProdPdf( "d_pdf_b1s2_mc", "d_pdf_b1s2_mc", RooArgSet( *d1_pdf_bkg_b1s2_mc, *d2_pdf_sig_b1s2_mc) );
  RooProdPdf* d_pdf_b1b2_mc = new RooProdPdf( "d_pdf_b1b2_mc", "d_pdf_b1b2_mc", RooArgSet( *d1_pdf_bkg_b1s2_mc, *d2_pdf_bkg_s1b2_mc) );

  RooProdPdf* d_pdf_s1s2_dt = new RooProdPdf( "d_pdf_s1s2_dt", "d_pdf_s1s2_dt", RooArgSet( *d1_pdf_sig_s1s2_dt, *d2_pdf_sig_s1s2_dt) );
  RooProdPdf* d_pdf_s1b2_dt = new RooProdPdf( "d_pdf_s1b2_dt", "d_pdf_s1b2_dt", RooArgSet( *d1_pdf_sig_s1b2_dt, *d2_pdf_bkg_s1b2_dt) );
  RooProdPdf* d_pdf_b1s2_dt = new RooProdPdf( "d_pdf_b1s2_dt", "d_pdf_b1s2_dt", RooArgSet( *d1_pdf_bkg_b1s2_dt, *d2_pdf_sig_b1s2_dt) );
  RooProdPdf* d_pdf_b1b2_dt = new RooProdPdf( "d_pdf_b1b2_dt", "d_pdf_b1b2_dt", RooArgSet( *d1_pdf_bkg_b1s2_dt, *d2_pdf_bkg_s1b2_dt) );

  Double_t d_init_s1s2 = d_init[3];
  Double_t d_init_s1b2 = d_init[1];
  Double_t d_init_b1s2 = d_init[2];
  Double_t d_init_b1b2 = d_init[0];
  std::cout << "d_init_s1s2 = " << d_init_s1s2 << std::endl;
  std::cout << "d_init_s1b2 = " << d_init_s1b2 << std::endl;
  std::cout << "d_init_b1s2 = " << d_init_b1s2 << std::endl;
  std::cout << "d_init_b1b2 = " << d_init_b1b2 << std::endl;
  std::cout << "r_init_s1b2 = " << d_init_s1b2/d_init_s1s2 << std::endl;
  std::cout << "r_init_b1s2 = " << d_init_b1s2/d_init_s1s2 << std::endl;

  RooRealVar* d_s1s2_mc = new RooRealVar( "N_{s1s2,d,mc}", "N_{s1s2,d,mc}", d_init_s1s2, -30.0, ( d_init_s1s2>10 ? 5.0*d_init_s1s2 : 30 ) );
  RooRealVar* d_s1b2_mc = new RooRealVar( "N_{s1b2,d,mc}", "N_{s1b2,d,mc}", d_init_s1b2, -30.0, ( d_init_s1b2> 5 ? 5.0*d_init_s1b2 : 30 ) );
  RooRealVar* d_b1s2_mc = new RooRealVar( "N_{b1s2,d,mc}", "N_{b1s2,d,mc}", d_init_b1s2, -30.0, ( d_init_b1s2> 5 ? 5.0*d_init_b1s2 : 30 ) );
  RooRealVar* d_b1b2_mc = new RooRealVar( "N_{b1b2,d,mc}", "N_{b1b2,d,mc}", d_init_b1b2, -30.0, ( d_init_b1b2>10 ? 5.0*d_init_b1b2 : 30 ) );

  RooRealVar* d_s1s2_dt = new RooRealVar( "N_{s1s2,d,dt}", "N_{s1s2,d,dt}", d_init_s1s2, -30.0, ( d_init_s1s2>10 ? 5.0*d_init_s1s2 : 30 ) );
  RooRealVar* d_s1b2_dt = new RooRealVar( "N_{s1b2,d,dt}", "N_{s1b2,d,dt}", d_init_s1b2, -30.0, ( d_init_s1b2> 5 ? 5.0*d_init_s1b2 : 30 ) );
  RooRealVar* d_b1s2_dt = new RooRealVar( "N_{b1s2,d,dt}", "N_{b1s2,d,dt}", d_init_b1s2, -30.0, ( d_init_b1s2> 5 ? 5.0*d_init_b1s2 : 30 ) );
  RooRealVar* d_b1b2_dt = new RooRealVar( "N_{b1b2,d,dt}", "N_{b1b2,d,dt}", d_init_b1b2, -30.0, ( d_init_b1b2>10 ? 5.0*d_init_b1b2 : 30 ) );

  RooAddPdf*  d_pdf_mc  = new RooAddPdf ( "d_pdf_mc", "d_pdf_mc",
					  RooArgList(*d_pdf_s1s2_mc, *d_pdf_s1b2_mc, *d_pdf_b1s2_mc, *d_pdf_b1b2_mc),
					  RooArgList(    *d_s1s2_mc,     *d_s1b2_mc,     *d_b1s2_mc,     *d_b1b2_mc)
					  );
  
  RooAddPdf*  d_pdf_dt  = new RooAddPdf ( "d_pdf_dt", "d_pdf_dt",
					  RooArgList(*d_pdf_s1s2_dt, *d_pdf_s1b2_dt, *d_pdf_b1s2_dt, *d_pdf_b1b2_dt),
					  RooArgList(    *d_s1s2_dt,     *d_s1b2_dt,     *d_b1s2_dt,     *d_b1b2_dt)
					  );
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Setting for D mass>
  Double_t d_range_L = 0.015;
  Double_t d_range_H = 0.015;
  if( fl_dec > 999 ){
    if( fl_slowpi[0]==1 ){ // D0 decays with pi0
      d_range_L = 0.045;
      d_range_H = 0.030;
    }else{ // D+ decays with pi0
      d_range_L = 0.036;
      d_range_H = 0.024;
    }
  }
  //dmass1->setRange( "d1_cutrange", nominal_eff_dmass( fl_dec)-d_range_L, nominal_eff_dmass( fl_dec)+d_range_H );
  //dmass2->setRange( "d2_cutrange", nominal_eff_dmass(tmp_dec)-d_range_L, nominal_eff_dmass(tmp_dec)+d_range_H );
  dmass1->setRange( "d1_cutrange", d_xmin[0], d_xmax[0] );
  dmass2->setRange( "d2_cutrange", d_xmin[1], d_xmax[1] );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Fitting D mass>
  if( fl_dec==1010 || fl_dec==110 || fl_dec==200 || fl_dec==102 || fl_dec==201 || fl_dec==301 || fl_dec==411 ){
    d1_pol_bkg_b1s2_c1_mc->setVal(0.0);
    d2_pol_bkg_s1b2_c1_mc->setVal(0.0);
    d1_pol_bkg_b1s2_c1_mc->setConstant(kTRUE);
    d2_pol_bkg_s1b2_c1_mc->setConstant(kTRUE);
  }

  RooFitResult* d_fit_result_mc = d_pdf_mc->fitTo( *d_roohist_mc, Extended(), Save(true), SumW2Error(true) ); // Minos(true) ?
  d1_pol_bkg_b1s2_c1_dt->setVal(d1_pol_bkg_b1s2_c1_mc->getVal()); d1_pol_bkg_b1s2_c1_dt->setConstant(kTRUE);
  d2_pol_bkg_s1b2_c1_dt->setVal(d2_pol_bkg_s1b2_c1_mc->getVal()); d2_pol_bkg_s1b2_c1_dt->setConstant(kTRUE);
  RooFitResult* d_fit_result_dt = d_pdf_dt->fitTo( *d_roohist_dt, Extended(), Save(true), SumW2Error(true) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Draw D mass>
  RooPlot* d1_frame_mc = dmass1->frame();
  d1_frame_mc->GetXaxis()->CenterTitle();
  d1_frame_mc->GetYaxis()->CenterTitle();
  d1_frame_mc->SetTitleOffset( 1.00,"x" );
  d1_frame_mc->SetTitleOffset( 1.25,"y" );
  d1_frame_mc->SetTitle( Form("dec(%d), lep(%d), mc",fl_dec,fl_lep) );

  Double_t ymax_d1_mc = d_roohist_mc->plotOn( d1_frame_mc, Binning(d_xbin[0]), CutRange("d2_cutrange"),          MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  d_pdf_mc->plotOn( d1_frame_mc, ProjectionRange("d2_cutrange"),                             LineStyle(1), LineColor(3), LineWidth(2) );
  d_pdf_mc->plotOn( d1_frame_mc, ProjectionRange("d2_cutrange"), Components(*d_pdf_s1s2_mc), LineStyle(1), LineColor(2), LineWidth(1) );
  d_pdf_mc->plotOn( d1_frame_mc, ProjectionRange("d2_cutrange"), Components(*d_pdf_s1b2_mc), LineStyle(1), LineColor(4), LineWidth(1) );
  d_pdf_mc->plotOn( d1_frame_mc, ProjectionRange("d2_cutrange"), Components(*d_pdf_b1s2_mc), LineStyle(2), LineColor(5), LineWidth(1) );
  d_pdf_mc->plotOn( d1_frame_mc, ProjectionRange("d2_cutrange"), Components(*d_pdf_b1b2_mc), LineStyle(2), LineColor(6), LineWidth(1) );

  d_pdf_mc->paramOn( d1_frame_mc, Format("NELU", AutoPrecision(2)), Layout(0.02,0.50,0.90), ShowConstants(kFALSE) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* d2_frame_mc = dmass2->frame();
  d2_frame_mc->GetXaxis()->CenterTitle();
  d2_frame_mc->GetYaxis()->CenterTitle();
  d2_frame_mc->SetTitleOffset( 1.00,"x" );
  d2_frame_mc->SetTitleOffset( 1.25,"y" );
  if     ( tmp_dec==421 ) d2_frame_mc->SetTitle( Form("total D0 without dec(%d), mc",fl_dec) );
  else if( tmp_dec==411 ) d2_frame_mc->SetTitle( Form("total D+ without dec(%d), mc",fl_dec) );

  Double_t ymax_d2_mc = d_roohist_mc->plotOn( d2_frame_mc, Binning(d_xbin[1]), CutRange("d1_cutrange"),          MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  d_pdf_mc->plotOn( d2_frame_mc, ProjectionRange("d1_cutrange"),                             LineStyle(1), LineColor(3), LineWidth(2) );
  d_pdf_mc->plotOn( d2_frame_mc, ProjectionRange("d1_cutrange"), Components(*d_pdf_s1s2_mc), LineStyle(1), LineColor(2), LineWidth(1) );
  d_pdf_mc->plotOn( d2_frame_mc, ProjectionRange("d1_cutrange"), Components(*d_pdf_s1b2_mc), LineStyle(2), LineColor(4), LineWidth(1) );
  d_pdf_mc->plotOn( d2_frame_mc, ProjectionRange("d1_cutrange"), Components(*d_pdf_b1s2_mc), LineStyle(1), LineColor(5), LineWidth(1) );
  d_pdf_mc->plotOn( d2_frame_mc, ProjectionRange("d1_cutrange"), Components(*d_pdf_b1b2_mc), LineStyle(2), LineColor(6), LineWidth(1) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* d1_frame_dt = dmass1->frame();
  d1_frame_dt->GetXaxis()->CenterTitle();
  d1_frame_dt->GetYaxis()->CenterTitle();
  d1_frame_dt->SetTitleOffset( 1.00,"x" );
  d1_frame_dt->SetTitleOffset( 1.25,"y" );
  d1_frame_dt->SetTitle( Form("dec(%d), lep(%d), dt",fl_dec,fl_lep) );

  Double_t ymax_d1_dt = d_roohist_dt->plotOn( d1_frame_dt, Binning(d_xbin[0]), CutRange("d2_cutrange"),          MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  d_pdf_dt->plotOn( d1_frame_dt, ProjectionRange("d2_cutrange"),                             LineStyle(1), LineColor(3), LineWidth(2) );
  d_pdf_dt->plotOn( d1_frame_dt, ProjectionRange("d2_cutrange"), Components(*d_pdf_s1s2_dt), LineStyle(1), LineColor(2), LineWidth(1) );
  d_pdf_dt->plotOn( d1_frame_dt, ProjectionRange("d2_cutrange"), Components(*d_pdf_s1b2_dt), LineStyle(1), LineColor(4), LineWidth(1) );
  d_pdf_dt->plotOn( d1_frame_dt, ProjectionRange("d2_cutrange"), Components(*d_pdf_b1s2_dt), LineStyle(2), LineColor(5), LineWidth(1) );
  d_pdf_dt->plotOn( d1_frame_dt, ProjectionRange("d2_cutrange"), Components(*d_pdf_b1b2_dt), LineStyle(2), LineColor(6), LineWidth(1) );

  d_pdf_dt->paramOn( d1_frame_dt, Format("NELU", AutoPrecision(2)), Layout(0.02,0.50,0.90), ShowConstants(kFALSE) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* d2_frame_dt = dmass2->frame();
  d2_frame_dt->GetXaxis()->CenterTitle();
  d2_frame_dt->GetYaxis()->CenterTitle();
  d2_frame_dt->SetTitleOffset( 1.00,"x" );
  d2_frame_dt->SetTitleOffset( 1.25,"y" );
  if     ( tmp_dec==421 ) d2_frame_dt->SetTitle( Form("total D0 without dec(%d), dt",fl_dec) );
  else if( tmp_dec==411 ) d2_frame_dt->SetTitle( Form("total D+ without dec(%d), dt",fl_dec) );

  Double_t ymax_d2_dt = d_roohist_dt->plotOn( d2_frame_dt, Binning(d_xbin[1]), CutRange("d1_cutrange"),          MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  d_pdf_dt->plotOn( d2_frame_dt, ProjectionRange("d1_cutrange"),                             LineStyle(1), LineColor(3), LineWidth(2) );
  d_pdf_dt->plotOn( d2_frame_dt, ProjectionRange("d1_cutrange"), Components(*d_pdf_s1s2_dt), LineStyle(1), LineColor(2), LineWidth(1) );
  d_pdf_dt->plotOn( d2_frame_dt, ProjectionRange("d1_cutrange"), Components(*d_pdf_s1b2_dt), LineStyle(2), LineColor(4), LineWidth(1) );
  d_pdf_dt->plotOn( d2_frame_dt, ProjectionRange("d1_cutrange"), Components(*d_pdf_b1s2_dt), LineStyle(1), LineColor(5), LineWidth(1) );
  d_pdf_dt->plotOn( d2_frame_dt, ProjectionRange("d1_cutrange"), Components(*d_pdf_b1b2_dt), LineStyle(2), LineColor(6), LineWidth(1) );


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <PDF COMPONENT FOR delta m>
  TF1* dstr1_func_sig_s1s2_mc = (TF1*)dstr1_func_pdf_mc->Clone(); dstr1_func_sig_s1s2_mc->SetName("dstr1_s1s2_mc"); RooAbsPdf* dstr1_pdf_sig_s1s2_mc = bindPdf( dstr1_func_sig_s1s2_mc, *deltam1 );
  TF1* dstr1_func_sig_s1b2_mc = (TF1*)dstr1_func_pdf_mc->Clone(); dstr1_func_sig_s1b2_mc->SetName("dstr1_s1b2_mc"); RooAbsPdf* dstr1_pdf_sig_s1b2_mc = bindPdf( dstr1_func_sig_s1b2_mc, *deltam1 );
  TF1* dstr2_func_sig_s1s2_mc = (TF1*)dstr2_func_pdf_mc->Clone(); dstr2_func_sig_s1s2_mc->SetName("dstr2_s1s2_mc"); RooAbsPdf* dstr2_pdf_sig_s1s2_mc = bindPdf( dstr2_func_sig_s1s2_mc, *deltam2 );
  TF1* dstr2_func_sig_b1s2_mc = (TF1*)dstr2_func_pdf_mc->Clone(); dstr2_func_sig_b1s2_mc->SetName("dstr2_b1s2_mc"); RooAbsPdf* dstr2_pdf_sig_b1s2_mc = bindPdf( dstr2_func_sig_b1s2_mc, *deltam2 );

  TF1* dstr1_func_sig_s1s2_dt = (TF1*)dstr1_func_pdf_dt->Clone(); dstr1_func_sig_s1s2_dt->SetName("dstr1_s1s2_dt"); RooAbsPdf* dstr1_pdf_sig_s1s2_dt = bindPdf( dstr1_func_sig_s1s2_dt, *deltam1 );
  TF1* dstr1_func_sig_s1b2_dt = (TF1*)dstr1_func_pdf_dt->Clone(); dstr1_func_sig_s1b2_dt->SetName("dstr1_s1b2_dt"); RooAbsPdf* dstr1_pdf_sig_s1b2_dt = bindPdf( dstr1_func_sig_s1b2_dt, *deltam1 );
  TF1* dstr2_func_sig_s1s2_dt = (TF1*)dstr2_func_pdf_dt->Clone(); dstr2_func_sig_s1s2_dt->SetName("dstr2_s1s2_dt"); RooAbsPdf* dstr2_pdf_sig_s1s2_dt = bindPdf( dstr2_func_sig_s1s2_dt, *deltam2 );
  TF1* dstr2_func_sig_b1s2_dt = (TF1*)dstr2_func_pdf_dt->Clone(); dstr2_func_sig_b1s2_dt->SetName("dstr2_b1s2_dt"); RooAbsPdf* dstr2_pdf_sig_b1s2_dt = bindPdf( dstr2_func_sig_b1s2_dt, *deltam2 );
  
  RooAbsPdf*  dstr1_pdf_bkg_b1s2_mc = ( fl_slowpi[0] ? bindPdf( "dstr1_bkg_b1s2_mc", func_deltam_threshold_slowpip, *deltam1 ) : bindPdf( "dstr1_bkg_b1s2_mc", func_deltam_threshold_slowpi0, *deltam1 ) );
  RooAbsPdf*  dstr2_pdf_bkg_s1b2_mc = ( fl_slowpi[1] ? bindPdf( "dstr2_bkg_s1b2_mc", func_deltam_threshold_slowpip, *deltam2 ) : bindPdf( "dstr2_bkg_s1b2_mc", func_deltam_threshold_slowpi0, *deltam2 ) );
  RooAbsPdf*  dstr1_pdf_bkg_b1b2_mc = ( fl_slowpi[0] ? bindPdf( "dstr1_bkg_b1b2_mc", func_deltam_threshold_slowpip, *deltam1 ) : bindPdf( "dstr1_bkg_b1b2_mc", func_deltam_threshold_slowpi0, *deltam1 ) );
  RooAbsPdf*  dstr2_pdf_bkg_b1b2_mc = ( fl_slowpi[1] ? bindPdf( "dstr2_bkg_b1b2_mc", func_deltam_threshold_slowpip, *deltam2 ) : bindPdf( "dstr2_bkg_b1b2_mc", func_deltam_threshold_slowpi0, *deltam2 ) );

  RooAbsPdf*  dstr1_pdf_bkg_b1s2_dt = ( fl_slowpi[0] ? bindPdf( "dstr1_bkg_b1s2_dt", func_deltam_threshold_slowpip, *deltam1 ) : bindPdf( "dstr1_bkg_b1s2_dt", func_deltam_threshold_slowpi0, *deltam1 ) );
  RooAbsPdf*  dstr2_pdf_bkg_s1b2_dt = ( fl_slowpi[1] ? bindPdf( "dstr2_bkg_s1b2_dt", func_deltam_threshold_slowpip, *deltam2 ) : bindPdf( "dstr2_bkg_s1b2_dt", func_deltam_threshold_slowpi0, *deltam2 ) );
  RooAbsPdf*  dstr1_pdf_bkg_b1b2_dt = ( fl_slowpi[0] ? bindPdf( "dstr1_bkg_b1b2_dt", func_deltam_threshold_slowpip, *deltam1 ) : bindPdf( "dstr1_bkg_b1b2_dt", func_deltam_threshold_slowpi0, *deltam1 ) );
  RooAbsPdf*  dstr2_pdf_bkg_b1b2_dt = ( fl_slowpi[1] ? bindPdf( "dstr2_bkg_b1b2_dt", func_deltam_threshold_slowpip, *deltam2 ) : bindPdf( "dstr2_bkg_b1b2_dt", func_deltam_threshold_slowpi0, *deltam2 ) );

  RooProdPdf* dstr_pdf_s1s2_mc = new RooProdPdf( "dstr_pdf_s1s2_mc", "dstr_pdf_s1s2_mc", RooArgSet( *dstr1_pdf_sig_s1s2_mc, *dstr2_pdf_sig_s1s2_mc) );
  RooProdPdf* dstr_pdf_s1b2_mc = new RooProdPdf( "dstr_pdf_s1b2_mc", "dstr_pdf_s1b2_mc", RooArgSet( *dstr1_pdf_sig_s1b2_mc, *dstr2_pdf_bkg_s1b2_mc) );
  RooProdPdf* dstr_pdf_b1s2_mc = new RooProdPdf( "dstr_pdf_b1s2_mc", "dstr_pdf_b1s2_mc", RooArgSet( *dstr1_pdf_bkg_b1s2_mc, *dstr2_pdf_sig_b1s2_mc) );
  RooProdPdf* dstr_pdf_b1b2_mc = new RooProdPdf( "dstr_pdf_b1b2_mc", "dstr_pdf_b1b2_mc", RooArgSet( *dstr1_pdf_bkg_b1b2_mc, *dstr2_pdf_bkg_b1b2_mc) );

  RooProdPdf* dstr_pdf_s1s2_dt = new RooProdPdf( "dstr_pdf_s1s2_dt", "dstr_pdf_s1s2_dt", RooArgSet( *dstr1_pdf_sig_s1s2_dt, *dstr2_pdf_sig_s1s2_dt) );
  RooProdPdf* dstr_pdf_s1b2_dt = new RooProdPdf( "dstr_pdf_s1b2_dt", "dstr_pdf_s1b2_dt", RooArgSet( *dstr1_pdf_sig_s1b2_dt, *dstr2_pdf_bkg_s1b2_dt) );
  RooProdPdf* dstr_pdf_b1s2_dt = new RooProdPdf( "dstr_pdf_b1s2_dt", "dstr_pdf_b1s2_dt", RooArgSet( *dstr1_pdf_bkg_b1s2_dt, *dstr2_pdf_sig_b1s2_dt) );
  RooProdPdf* dstr_pdf_b1b2_dt = new RooProdPdf( "dstr_pdf_b1b2_dt", "dstr_pdf_b1b2_dt", RooArgSet( *dstr1_pdf_bkg_b1b2_dt, *dstr2_pdf_bkg_b1b2_dt) );

  Double_t dstr_init_s1s2 = dstr_init[3];
  Double_t dstr_init_s1b2 = dstr_init[1];
  Double_t dstr_init_b1s2 = dstr_init[2];
  Double_t dstr_init_b1b2 = dstr_init[0];
  std::cout << "dstr_init_s1s2 = " << dstr_init_s1s2 << std::endl;
  std::cout << "dstr_init_s1b2 = " << dstr_init_s1b2 << std::endl;
  std::cout << "dstr_init_b1s2 = " << dstr_init_b1s2 << std::endl;
  std::cout << "dstr_init_b1b2 = " << dstr_init_b1b2 << std::endl;
  std::cout << "   r_init_s1b2 = " << dstr_init_s1b2/dstr_init_s1s2 << std::endl;
  std::cout << "   r_init_b1s2 = " << dstr_init_b1s2/dstr_init_s1s2 << std::endl;

  RooRealVar* dstr_s1s2_mc = new RooRealVar( "N_{s1s2,dstr,mc}", "N_{s1s2,dstr,mc}", dstr_init_s1s2, -10.0, ( dstr_init_s1s2>10 ? 5.0*dstr_init_s1s2 : 50 ) );
  RooRealVar* dstr_s1b2_mc = new RooRealVar( "N_{s1b2,dstr,mc}", "N_{s1b2,dstr,mc}", dstr_init_s1b2, -10.0, ( dstr_init_s1b2>10 ? 5.0*dstr_init_s1b2 : 50 ) );
  RooRealVar* dstr_b1s2_mc = new RooRealVar( "N_{b1s2,dstr,mc}", "N_{b1s2,dstr,mc}", dstr_init_b1s2, -10.0, ( dstr_init_b1s2>10 ? 5.0*dstr_init_b1s2 : 50 ) );
  RooRealVar* dstr_b1b2_mc = new RooRealVar( "N_{b1b2,dstr,mc}", "N_{b1b2,dstr,mc}", dstr_init_b1b2, -10.0, ( dstr_init_b1b2>10 ? 5.0*dstr_init_b1b2 : 50 ) );

  RooRealVar* dstr_s1s2_dt = new RooRealVar( "N_{s1s2,dstr,dt}", "N_{s1s2,dstr,dt}", dstr_init_s1s2, -10.0, ( dstr_init_s1s2>10 ? 5.0*dstr_init_s1s2 : 50 ) );
  RooRealVar* dstr_s1b2_dt = new RooRealVar( "N_{s1b2,dstr,dt}", "N_{s1b2,dstr,dt}", dstr_init_s1b2, -10.0, ( dstr_init_s1b2>10 ? 5.0*dstr_init_s1b2 : 50 ) );
  RooRealVar* dstr_b1s2_dt = new RooRealVar( "N_{b1s2,dstr,dt}", "N_{b1s2,dstr,dt}", dstr_init_b1s2, -10.0, ( dstr_init_b1s2>10 ? 5.0*dstr_init_b1s2 : 50 ) );
  RooRealVar* dstr_b1b2_dt = new RooRealVar( "N_{b1b2,dstr,dt}", "N_{b1b2,dstr,dt}", dstr_init_b1b2, -10.0, ( dstr_init_b1b2>10 ? 5.0*dstr_init_b1b2 : 50 ) );

  RooAddPdf*  dstr_pdf_mc  = new RooAddPdf ( "dstr_pdf_mc", "dstr_pdf_mc", RooArgList(*dstr_pdf_s1s2_mc, *dstr_pdf_s1b2_mc, *dstr_pdf_b1s2_mc, *dstr_pdf_b1b2_mc), RooArgList(*dstr_s1s2_mc, *dstr_s1b2_mc, *dstr_b1s2_mc, *dstr_b1b2_mc) );
  RooAddPdf*  dstr_pdf_dt  = new RooAddPdf ( "dstr_pdf_dt", "dstr_pdf_dt", RooArgList(*dstr_pdf_s1s2_dt, *dstr_pdf_s1b2_dt, *dstr_pdf_b1s2_dt, *dstr_pdf_b1b2_dt), RooArgList(*dstr_s1s2_dt, *dstr_s1b2_dt, *dstr_b1s2_dt, *dstr_b1b2_dt) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Setting for delta m>
  Double_t dstr_range[2] = { (fl_slowpi[0] ? 0.0025 : 0.0020),
			     (fl_slowpi[1] ? 0.0025 : 0.0020)
  };
  //deltam1->setRange( "dstr1_cutrange", nominal_deltam[0]-dstr_range[0], nominal_deltam[0]+dstr_range[0] );
  //deltam2->setRange( "dstr2_cutrange", nominal_deltam[1]-dstr_range[1], nominal_deltam[1]+dstr_range[1] );
  deltam1->setRange( "dstr1_cutrange", dstr_xmin[0], dstr_xmax[0] );
  deltam2->setRange( "dstr2_cutrange", dstr_xmin[1], dstr_xmax[1] );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Fitting delta m>
  RooFitResult* dstr_fit_result_mc = dstr_pdf_mc->fitTo( *dstr_roohist_mc, Extended(), Save(true), SumW2Error(true) );
  RooFitResult* dstr_fit_result_dt = dstr_pdf_dt->fitTo( *dstr_roohist_dt, Extended(), Save(true), SumW2Error(true) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Draw delta m>
  RooPlot* dstr1_frame_mc = deltam1->frame();
  dstr1_frame_mc->GetXaxis()->CenterTitle();
  dstr1_frame_mc->GetYaxis()->CenterTitle();
  dstr1_frame_mc->SetTitleOffset( 1.00,"x" );
  dstr1_frame_mc->SetTitleOffset( 1.25,"y" );
  dstr1_frame_mc->SetTitle( Form("dec(%d), lep(%d), mc",fl_dec,fl_lep) );

  Double_t ymax_dstr1_mc = dstr_roohist_mc->plotOn( dstr1_frame_mc, Binning(dstr_xbin[0]), CutRange("dstr2_cutrange"),    MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  dstr_pdf_mc->plotOn( dstr1_frame_mc, ProjectionRange("dstr2_cutrange"),                                LineStyle(1), LineColor(3), LineWidth(2) );
  dstr_pdf_mc->plotOn( dstr1_frame_mc, ProjectionRange("dstr2_cutrange"), Components(*dstr_pdf_s1s2_mc), LineStyle(1), LineColor(2), LineWidth(1) );
  dstr_pdf_mc->plotOn( dstr1_frame_mc, ProjectionRange("dstr2_cutrange"), Components(*dstr_pdf_s1b2_mc), LineStyle(1), LineColor(4), LineWidth(1) );
  dstr_pdf_mc->plotOn( dstr1_frame_mc, ProjectionRange("dstr2_cutrange"), Components(*dstr_pdf_b1s2_mc), LineStyle(2), LineColor(5), LineWidth(1) );
  dstr_pdf_mc->plotOn( dstr1_frame_mc, ProjectionRange("dstr2_cutrange"), Components(*dstr_pdf_b1b2_mc), LineStyle(2), LineColor(6), LineWidth(1) );

  dstr_pdf_mc->paramOn( dstr1_frame_mc, Format("NELU", AutoPrecision(2)), Layout(0.50, 0.95, 0.95), ShowConstants(kFALSE) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* dstr2_frame_mc = deltam2->frame();
  dstr2_frame_mc->GetXaxis()->CenterTitle();
  dstr2_frame_mc->GetYaxis()->CenterTitle();
  dstr2_frame_mc->SetTitleOffset( 1.00,"x" );
  dstr2_frame_mc->SetTitleOffset( 1.25,"y" );
  if     ( tmp_dec==421 ) dstr2_frame_mc->SetTitle( Form("total D0 without dec(%d), mc",fl_dec) );
  else if( tmp_dec==411 ) dstr2_frame_mc->SetTitle( Form("total D+ without dec(%d), mc",fl_dec) );

  Double_t ymax_dstr2_mc = dstr_roohist_mc->plotOn( dstr2_frame_mc, Binning(dstr_xbin[1]), CutRange("dstr1_cutrange"),          MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  dstr_pdf_mc->plotOn( dstr2_frame_mc, ProjectionRange("dstr1_cutrange"),                                LineStyle(1), LineColor(3), LineWidth(2) );
  dstr_pdf_mc->plotOn( dstr2_frame_mc, ProjectionRange("dstr1_cutrange"), Components(*dstr_pdf_s1s2_mc), LineStyle(1), LineColor(2), LineWidth(1) );
  dstr_pdf_mc->plotOn( dstr2_frame_mc, ProjectionRange("dstr1_cutrange"), Components(*dstr_pdf_s1b2_mc), LineStyle(2), LineColor(4), LineWidth(1) );
  dstr_pdf_mc->plotOn( dstr2_frame_mc, ProjectionRange("dstr1_cutrange"), Components(*dstr_pdf_b1s2_mc), LineStyle(1), LineColor(5), LineWidth(1) );
  dstr_pdf_mc->plotOn( dstr2_frame_mc, ProjectionRange("dstr1_cutrange"), Components(*dstr_pdf_b1b2_mc), LineStyle(2), LineColor(6), LineWidth(1) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* dstr1_frame_dt = deltam1->frame();
  dstr1_frame_dt->GetXaxis()->CenterTitle();
  dstr1_frame_dt->GetYaxis()->CenterTitle();
  dstr1_frame_dt->SetTitleOffset( 1.00,"x" );
  dstr1_frame_dt->SetTitleOffset( 1.25,"y" );
  dstr1_frame_dt->SetTitle( Form("dec(%d), lep(%d), dt",fl_dec,fl_lep) );

  Double_t ymax_dstr1_dt = dstr_roohist_dt->plotOn( dstr1_frame_dt, Binning(dstr_xbin[0]), CutRange("dstr2_cutrange"),    MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  dstr_pdf_dt->plotOn( dstr1_frame_dt, ProjectionRange("dstr2_cutrange"),                                LineStyle(1), LineColor(3), LineWidth(2) );
  dstr_pdf_dt->plotOn( dstr1_frame_dt, ProjectionRange("dstr2_cutrange"), Components(*dstr_pdf_s1s2_dt), LineStyle(1), LineColor(2), LineWidth(1) );
  dstr_pdf_dt->plotOn( dstr1_frame_dt, ProjectionRange("dstr2_cutrange"), Components(*dstr_pdf_s1b2_dt), LineStyle(1), LineColor(4), LineWidth(1) );
  dstr_pdf_dt->plotOn( dstr1_frame_dt, ProjectionRange("dstr2_cutrange"), Components(*dstr_pdf_b1s2_dt), LineStyle(2), LineColor(5), LineWidth(1) );
  dstr_pdf_dt->plotOn( dstr1_frame_dt, ProjectionRange("dstr2_cutrange"), Components(*dstr_pdf_b1b2_dt), LineStyle(2), LineColor(6), LineWidth(1) );

  dstr_pdf_dt->paramOn( dstr1_frame_dt, Format("NELU", AutoPrecision(2)), Layout(0.50, 0.95, 0.95), ShowConstants(kFALSE) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  RooPlot* dstr2_frame_dt = deltam2->frame();
  dstr2_frame_dt->GetXaxis()->CenterTitle();
  dstr2_frame_dt->GetYaxis()->CenterTitle();
  dstr2_frame_dt->SetTitleOffset( 1.00,"x" );
  dstr2_frame_dt->SetTitleOffset( 1.25,"y" );
  if     ( tmp_dec==421 ) dstr2_frame_dt->SetTitle( Form("total D0 without dec(%d), dt",fl_dec) );
  else if( tmp_dec==411 ) dstr2_frame_dt->SetTitle( Form("total D+ without dec(%d), dt",fl_dec) );

  Double_t ymax_dstr2_dt = dstr_roohist_dt->plotOn( dstr2_frame_dt, Binning(dstr_xbin[1]), CutRange("dstr1_cutrange"),          MarkerColor(1), LineColor(1), LineWidth(1) )->GetMaximum();
  dstr_pdf_dt->plotOn( dstr2_frame_dt, ProjectionRange("dstr1_cutrange"),                                LineStyle(1), LineColor(3), LineWidth(2) );
  dstr_pdf_dt->plotOn( dstr2_frame_dt, ProjectionRange("dstr1_cutrange"), Components(*dstr_pdf_s1s2_dt), LineStyle(1), LineColor(2), LineWidth(1) );
  dstr_pdf_dt->plotOn( dstr2_frame_dt, ProjectionRange("dstr1_cutrange"), Components(*dstr_pdf_s1b2_dt), LineStyle(2), LineColor(4), LineWidth(1) );
  dstr_pdf_dt->plotOn( dstr2_frame_dt, ProjectionRange("dstr1_cutrange"), Components(*dstr_pdf_b1s2_dt), LineStyle(1), LineColor(5), LineWidth(1) );
  dstr_pdf_dt->plotOn( dstr2_frame_dt, ProjectionRange("dstr1_cutrange"), Components(*dstr_pdf_b1b2_dt), LineStyle(2), LineColor(6), LineWidth(1) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  d1_frame_mc->SetMaximum( ymax_d1_mc > ymax_d1_dt ? 1.2*ymax_d1_mc : 1.2*ymax_d1_dt );
  d1_frame_dt->SetMaximum( ymax_d1_mc > ymax_d1_dt ? 1.2*ymax_d1_mc : 1.2*ymax_d1_dt );
  d2_frame_mc->SetMaximum( ymax_d2_mc > ymax_d2_dt ? 1.2*ymax_d2_mc : 1.2*ymax_d2_dt );
  d2_frame_dt->SetMaximum( ymax_d2_mc > ymax_d2_dt ? 1.2*ymax_d2_mc : 1.2*ymax_d2_dt );
  can->cd(1); d1_frame_mc->Draw();
  can->cd(2); d2_frame_mc->Draw();
  can->cd(5); d1_frame_dt->Draw();
  can->cd(6); d2_frame_dt->Draw();

  TLine* d1_l_L = new TLine( nominal_eff_dmass(fl_dec)-d_range_L, 0.0, nominal_eff_dmass(fl_dec)-d_range_L, 0.60*ymax_d1_mc );
  TLine* d1_l_H = new TLine( nominal_eff_dmass(fl_dec)+d_range_H, 0.0, nominal_eff_dmass(fl_dec)+d_range_H, 0.60*ymax_d1_mc );
  d1_l_L->SetLineColor(2);
  d1_l_H->SetLineColor(2);
  if( fl_line ){
    can->cd(1);
    d1_l_L->Draw("Lsame");
    d1_l_H->Draw("Lsame");
    can->cd(5);
    d1_l_L->Draw("Lsame");
    d1_l_H->Draw("Lsame");
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  dstr1_frame_mc->SetMaximum( ymax_dstr1_mc > ymax_dstr1_dt ? 1.15*ymax_dstr1_mc : 1.15*ymax_dstr1_dt );
  dstr1_frame_dt->SetMaximum( ymax_dstr1_mc > ymax_dstr1_dt ? 1.15*ymax_dstr1_mc : 1.15*ymax_dstr1_dt );
  dstr2_frame_mc->SetMaximum( ymax_dstr2_mc > ymax_dstr2_dt ? 1.15*ymax_dstr2_mc : 1.15*ymax_dstr2_dt );
  dstr2_frame_dt->SetMaximum( ymax_dstr2_mc > ymax_dstr2_dt ? 1.15*ymax_dstr2_mc : 1.15*ymax_dstr2_dt );
  can->cd(3); dstr1_frame_mc->Draw();
  can->cd(4); dstr2_frame_mc->Draw();
  can->cd(7); dstr1_frame_dt->Draw();
  can->cd(8); dstr2_frame_dt->Draw();
  
  TLine* dstr1_l_L = new TLine( nominal_deltam[0]-dstr_range[0], 0.0, nominal_deltam[0]-dstr_range[0], 0.60*ymax_dstr1_mc );
  TLine* dstr1_l_H = new TLine( nominal_deltam[0]+dstr_range[0], 0.0, nominal_deltam[0]+dstr_range[0], 0.60*ymax_dstr1_mc );
  dstr1_l_L->SetLineColor(2);
  dstr1_l_H->SetLineColor(2);
  if( fl_line ){
    can->cd(3);
    dstr1_l_L->Draw("Lsame");
    dstr1_l_H->Draw("Lsame");
    can->cd(7);
    dstr1_l_L->Draw("Lsame");
    dstr1_l_H->Draw("Lsame");
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  RooPlot* d1_frame = dmass1->frame();
  d1_frame->GetXaxis()->CenterTitle();
  d1_frame->GetYaxis()->CenterTitle();
  d1_frame->SetTitleOffset( 1.00,"x" );
  d1_frame->SetTitleOffset( 1.25,"y" );
  d1_frame->SetTitle( Form("dec(%d), lep(%d)",fl_dec,fl_lep) );
  d_roohist_dt       ->plotOn( d1_frame, Binning(d_xbin[0]), CutRange("d2_cutrange"), MarkerColor(2), LineColor(2), LineWidth(1) );
  d_roohist_mc_smear1->plotOn( d1_frame, Binning(d_xbin[0]),                          MarkerColor(1), LineColor(1), LineWidth(1) );

  RooPlot* d2_frame = dmass2->frame();
  d2_frame->GetXaxis()->CenterTitle();
  d2_frame->GetYaxis()->CenterTitle();
  d2_frame->SetTitleOffset( 1.00,"x" );
  d2_frame->SetTitleOffset( 1.25,"y" );
  if     ( tmp_dec==421 ) d2_frame->SetTitle( Form("total D0 without dec(%d), mc",fl_dec) );
  else if( tmp_dec==411 ) d2_frame->SetTitle( Form("total D+ without dec(%d), mc",fl_dec) );
  d_roohist_dt       ->plotOn( d2_frame, Binning(d_xbin[0]), CutRange("d1_cutrange"), MarkerColor(2), LineColor(2), LineWidth(1) );
  d_roohist_mc_smear2->plotOn( d2_frame, Binning(d_xbin[0]),                          MarkerColor(1), LineColor(1), LineWidth(1) );

  RooPlot* dstr1_frame = deltam1->frame();
  dstr1_frame->GetXaxis()->CenterTitle();
  dstr1_frame->GetYaxis()->CenterTitle();
  dstr1_frame->SetTitleOffset( 1.00,"x" );
  dstr1_frame->SetTitleOffset( 1.25,"y" );
  dstr1_frame->SetTitle( Form("dec(%d), lep(%d)",fl_dec,fl_lep) );
  dstr_roohist_dt       ->plotOn( dstr1_frame, Binning(dstr_xbin[0]), CutRange("dstr2_cutrange"), MarkerColor(2), LineColor(2), LineWidth(1) );
  dstr_roohist_mc_smear1->plotOn( dstr1_frame, Binning(dstr_xbin[0]),                             MarkerColor(1), LineColor(1), LineWidth(1) );

  RooPlot* dstr2_frame = deltam2->frame();
  dstr2_frame->GetXaxis()->CenterTitle();
  dstr2_frame->GetYaxis()->CenterTitle();
  dstr2_frame->SetTitleOffset( 1.00,"x" );
  dstr2_frame->SetTitleOffset( 1.25,"y" );
  if     ( tmp_dec==421 ) dstr2_frame->SetTitle( Form("total D0 without dec(%d)",fl_dec) );
  else if( tmp_dec==411 ) dstr2_frame->SetTitle( Form("total D+ without dec(%d)",fl_dec) );
  dstr_roohist_dt       ->plotOn( dstr2_frame, Binning(dstr_xbin[0]), CutRange("dstr1_cutrange"), MarkerColor(2), LineColor(2), LineWidth(1) );
  dstr_roohist_mc_smear2->plotOn( dstr2_frame, Binning(dstr_xbin[0]),                             MarkerColor(1), LineColor(1), LineWidth(1) );

  can->cd( 9);    d1_frame->Draw();
  can->cd(10);    d2_frame->Draw();
  can->cd(11); dstr1_frame->Draw();
  can->cd(12); dstr2_frame->Draw();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TText* tex = new TText();
  tex->SetTextColor(3);
  tex->SetTextSize(0.03);
  can->cd(9);
  tex->DrawTextNDC( 0.18,0.66, Form("dt = %.0f, mc = %.0f", d_s1s2_dt->getVal(), d_s1s2_mc->getVal()) );
  tex->DrawTextNDC( 0.18,0.62, Form("R(data/mc) = %.1f",    d_s1s2_dt->getVal() /d_s1s2_mc->getVal()) );
  can->cd(11);
  tex->DrawTextNDC( 0.18,0.66, Form("dt = %.0f, mc = %.0f", dstr_s1s2_dt->getVal(), dstr_s1s2_mc->getVal()) );
  tex->DrawTextNDC( 0.18,0.62, Form("R(data/mc) = %.1f",    dstr_s1s2_dt->getVal() /dstr_s1s2_mc->getVal()) );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Calculation Variation for D mass>
  Double_t diff_ss_d = d_s1s2_dt->getVal()/d_s1s2_mc->getVal(); Double_t diff_ss_dE = diff_ss_d * sqrt( pow(d_s1s2_dt->getError()/d_s1s2_dt->getVal(),2) + pow(d_s1s2_mc->getError()/d_s1s2_mc->getVal(),2) );
  Double_t diff_sb_d = d_s1b2_dt->getVal()/d_s1b2_mc->getVal(); Double_t diff_sb_dE = diff_sb_d * sqrt( pow(d_s1b2_dt->getError()/d_s1b2_dt->getVal(),2) + pow(d_s1b2_mc->getError()/d_s1b2_mc->getVal(),2) );
  Double_t diff_bs_d = d_b1s2_dt->getVal()/d_b1s2_mc->getVal(); Double_t diff_bs_dE = diff_bs_d * sqrt( pow(d_b1s2_dt->getError()/d_b1s2_dt->getVal(),2) + pow(d_b1s2_mc->getError()/d_b1s2_mc->getVal(),2) );
  Double_t diff_bb_d = d_b1b2_dt->getVal()/d_b1b2_mc->getVal(); Double_t diff_bb_dE = diff_bb_d * sqrt( pow(d_b1b2_dt->getError()/d_b1b2_dt->getVal(),2) + pow(d_b1b2_mc->getError()/d_b1b2_mc->getVal(),2) );
  
  if( fl_calib_d_ss && fl_dec!=421 && fl_dec!=411 ){
    if( fl_calib_d_sb ){
      //if( d_s1b2_dt->getVal() < thnevt || d_s1b2_mc->getVal() < thnevt ) diff_ss_d = ( d_s1s2_dt->getVal() + d_s1b2_dt->getVal() )/( d_s1s2_mc->getVal() + d_s1b2_mc->getVal() );
      //else                                                               diff_ss_d = ( diff_ss_d/pow(diff_ss_dE,2) + diff_sb_d/pow(diff_sb_dE,2) ) / ( 1/pow(diff_ss_dE,2) + 1/pow(diff_sb_dE,2) );
      diff_ss_d = ( d_s1s2_dt->getVal() + d_s1b2_dt->getVal() )/( d_s1s2_mc->getVal() + d_s1b2_mc->getVal() );
    }
    

    R_ss_d [dec_index(fl_dec)] *= (diff_ss_d - 1.0)/2.0 + 1.0; // moderate change in order to converge !!!!!!!!!!!!!!!!!
    R_ss_dE[dec_index(fl_dec)]  = R_ss_d[dec_index(fl_dec)]*sqrt( pow(d_s1s2_dt->getError()/d_s1s2_dt->getVal(),2) +
								  pow(d_s1s2_mc->getError()/d_s1s2_mc->getVal(),2)
								  );
    if( d_s1s2_dt->getVal() < thnevt || d_s1s2_mc->getVal() < thnevt ){
      R_ss_d [dec_index(fl_dec)] = 1.0;
      R_ss_dE[dec_index(fl_dec)] = 0.0;
    }
  }

  if( fl_calib_d_bb && fl_dec!=421 && fl_dec!=411 ){  
    if( fl_calib_d_sb ){
      //if( d_b1s2_dt->getVal() < thnevt || d_b1s2_mc->getVal() < thnevt ) diff_bb_d = ( d_b1s2_dt->getVal() + d_b1b2_dt->getVal() )/( d_b1s2_mc->getVal() + d_b1b2_mc->getVal() );
      //else                                                               diff_bb_d = ( diff_bb_d/pow(diff_bb_dE,2) + diff_bs_d/pow(diff_bs_dE,2) ) / ( 1/pow(diff_bb_dE,2) + 1/pow(diff_bs_dE,2) );
      diff_bb_d = ( d_b1s2_dt->getVal() + d_b1b2_dt->getVal() )/( d_b1s2_mc->getVal() + d_b1b2_mc->getVal() );
    }

    R_bb_d [dec_index(fl_dec)] *= (diff_bb_d - 1.0)/2.0 + 1.0; // moderate change in order to converge !!!!!!!!!!!!!!!!!
    R_bb_dE[dec_index(fl_dec)]  = R_bb_d[dec_index(fl_dec)]*sqrt( pow(d_b1b2_dt->getError()/d_b1b2_dt->getVal(),2) +
								  pow(d_b1b2_mc->getError()/d_b1b2_mc->getVal(),2)
								  );
    if( d_b1b2_dt->getVal() < thnevt || d_b1b2_mc->getVal() < thnevt ){
      R_bb_d [dec_index(fl_dec)] = 1.0;
      R_bb_dE[dec_index(fl_dec)] = 0.0;
    }
  }


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Calculation Variation for delta m>
  Double_t diff_ss_dstr = dstr_s1s2_dt->getVal()/dstr_s1s2_mc->getVal(); Double_t diff_ss_dstrE = diff_ss_dstr * sqrt( pow(dstr_s1s2_dt->getError()/dstr_s1s2_dt->getVal(),2) + pow(dstr_s1s2_mc->getError()/dstr_s1s2_mc->getVal(),2) ); // for s1
  Double_t diff_sb_dstr = dstr_s1b2_dt->getVal()/dstr_s1b2_mc->getVal(); Double_t diff_sb_dstrE = diff_sb_dstr * sqrt( pow(dstr_s1b2_dt->getError()/dstr_s1b2_dt->getVal(),2) + pow(dstr_s1b2_mc->getError()/dstr_s1b2_mc->getVal(),2) ); // for b2
  Double_t diff_bs_dstr = dstr_b1s2_dt->getVal()/dstr_b1s2_mc->getVal(); Double_t diff_bs_dstrE = diff_bs_dstr * sqrt( pow(dstr_b1s2_dt->getError()/dstr_b1s2_dt->getVal(),2) + pow(dstr_b1s2_mc->getError()/dstr_b1s2_mc->getVal(),2) ); // for s1
  Double_t diff_bb_dstr = dstr_b1b2_dt->getVal()/dstr_b1b2_mc->getVal(); Double_t diff_bb_dstrE = diff_bb_dstr * sqrt( pow(dstr_b1b2_dt->getError()/dstr_b1b2_dt->getVal(),2) + pow(dstr_b1b2_mc->getError()/dstr_b1b2_mc->getVal(),2) ); // for b1

  Double_t scale_s1_dstr = 1.0; Double_t scale_s1_dstrE = 0.0;
  Double_t scale_b1_dstr = 1.0; Double_t scale_b1_dstrE = 0.0;
  Double_t scale_s2_dstr = 1.0; Double_t scale_s2_dstrE = 0.0;
  Double_t scale_b2_dstr = 1.0; Double_t scale_b2_dstrE = 0.0;
  std::cout << "diff_ss_dstr = " << diff_ss_dstr << " +- " << diff_ss_dstrE << std::endl;
  std::cout << "diff_sb_dstr = " << diff_sb_dstr << " +- " << diff_sb_dstrE << std::endl;
  std::cout << "diff_bs_dstr = " << diff_bs_dstr << " +- " << diff_bs_dstrE << std::endl;
  std::cout << "diff_bb_dstr = " << diff_bb_dstr << " +- " << diff_bb_dstrE << std::endl;
  if( fl_calib_dstr_ss ){
    if( !(dstr_s1b2_dt->getVal() < thnevt || dstr_s1b2_mc->getVal() < thnevt) ){
      scale_s1_dstr  = ( diff_ss_dstr/pow(diff_ss_dstrE,2) + diff_sb_dstr/pow(diff_sb_dstrE,2) ) / ( 1/pow(diff_ss_dstrE,2) + 1/pow(diff_sb_dstrE,2) );
      scale_s1_dstrE =                                                                       1.0 / ( 1/pow(diff_ss_dstrE,2) + 1/pow(diff_sb_dstrE,2) );
    }else{
      scale_s1_dstr = diff_ss_dstr;
      scale_s1_dstr = diff_ss_dstrE;
    }
    if( !(dstr_b1s2_dt->getVal() < thnevt || dstr_b1s2_mc->getVal() < thnevt) ){
      scale_s2_dstr  = ( diff_ss_dstr/pow(diff_ss_dstrE,2) + diff_bs_dstr/pow(diff_bs_dstrE,2) ) / ( 1/pow(diff_ss_dstrE,2) + 1/pow(diff_bs_dstrE,2) );
      scale_s2_dstrE =                                                                       1.0 / ( 1/pow(diff_ss_dstrE,2) + 1/pow(diff_bs_dstrE,2) );
    }else{
      scale_s2_dstr  = diff_ss_dstr;
      scale_s2_dstrE = diff_ss_dstrE;
    }
    if( !(dstr_s1b2_dt->getVal() < thnevt || dstr_s1b2_mc->getVal() < thnevt) ){
      scale_b2_dstr  = ( diff_bb_dstr/pow(diff_bb_dstrE,2) + diff_sb_dstr/pow(diff_sb_dstrE,2) ) / ( 1/pow(diff_bb_dstrE,2) + 1/pow(diff_sb_dstrE,2) );
      scale_b2_dstrE =                                                                       1.0 / ( 1/pow(diff_bb_dstrE,2) + 1/pow(diff_sb_dstrE,2) );
    }else{
      scale_b2_dstr  = diff_bb_dstr;
      scale_b2_dstrE = diff_bb_dstrE;
    }
    if( !(dstr_b1s2_dt->getVal() < thnevt || dstr_b1s2_mc->getVal() < thnevt) ){
      scale_b1_dstr  = ( diff_bb_dstr/pow(diff_bb_dstrE,2) + diff_bs_dstr/pow(diff_bs_dstrE,2) ) / ( 1/pow(diff_bb_dstrE,2) + 1/pow(diff_bs_dstrE,2) );
      scale_b1_dstrE =                                                                       1.0 / ( 1/pow(diff_bb_dstrE,2) + 1/pow(diff_bs_dstrE,2) );
    }else{
      scale_b1_dstr  = diff_bb_dstr;
      scale_b1_dstrE = diff_bb_dstrE;
    }
    std::cout << "scale_s1 = " << scale_s1_dstr << " +- " << scale_s1_dstrE << std::endl;
    std::cout << "scale_b1 = " << scale_b1_dstr << " +- " << scale_b1_dstrE << std::endl;
    std::cout << "scale_s2 = " << scale_s2_dstr << " +- " << scale_s2_dstrE << std::endl;
    std::cout << "scale_b2 = " << scale_b2_dstr << " +- " << scale_b2_dstrE << std::endl;

    if( fl_dec==411 ){
      R_ss_dstr [dec_index(fl_dec)] *= (scale_s1_dstr - 1.0)/2.0 + 1.0; // moderate change in order to converge !!!!!!!!!!!!!!!!!
      R_ss_dstrE[dec_index(fl_dec)]  = R_ss_dstr[dec_index(fl_dec)]*scale_s1_dstrE;
      R_bb_dstr [dec_index(fl_dec)] *= (scale_b1_dstr - 1.0)/2.0 + 1.0; // moderate change in order to converge !!!!!!!!!!!!!!!!!
      R_bb_dstrE[dec_index(fl_dec)]  = R_bb_dstr[dec_index(fl_dec)]*scale_b1_dstrE;
      
      R_ss_dstr [0] *= (scale_s2_dstr - 1.0)/2.0 + 1.0; // moderate change in order to converge !!!!!!!!!!!!!!!!!
      R_ss_dstrE[0]  = R_ss_dstr[0]*scale_s2_dstrE;
      R_bb_dstr [0] *= (scale_b2_dstr - 1.0)/2.0 + 1.0; // moderate change in order to converge !!!!!!!!!!!!!!!!!
      R_bb_dstrE[0]  = R_bb_dstr[0]*scale_b2_dstrE;
    }
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Output log>
  if( fl_dec!=411 && fl_dec!=421 ){ // each D decay
    std::cout << std::setw(12) << std::right << dec_index(fl_dec) // 0
	      << std::setw(12) << std::right << fl_dec // 1
	      << std::setw(12) << std::right << fl_lep // 2
	      << std::setw(12) << std::right << R_ss_d [dec_index(fl_dec)] // 3
	      << std::setw(12) << std::right << R_ss_dE[dec_index(fl_dec)] // 4
	      << std::setw(12) << std::right << diff_ss_d // 5
	      << std::setw(12) << std::right << R_sb_d [dec_index(fl_dec)] // 6
	      << std::setw(12) << std::right << R_sb_dE[dec_index(fl_dec)] // 7
	      << std::setw(12) << std::right << diff_sb_d // 8
	      << std::setw(12) << std::right << R_bb_d [dec_index(fl_dec)] // 9
	      << std::setw(12) << std::right << R_bb_dE[dec_index(fl_dec)] // 10
	      << std::setw(12) << std::right << diff_bb_d; // 11
    if( d_dec_chg[dec_index(fl_dec)]==0 ){ // each D0 decay
      std::cout << std::setw(12) << std::right << 1.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 1.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 1.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 0.0;
    }else{ // each D0 decay
      std::cout << std::setw(12) << std::right << 1.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 1.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 1.0
		<< std::setw(12) << std::right << 0.0
		<< std::setw(12) << std::right << 0.0;
    }
    std::cout << " HOGEEEE"
	      << std::endl;
  }else if( fl_dec==411 ){ // total D+
    std::cout << std::setw(12) << std::right << dec_index(fl_dec) // 0
	      << std::setw(12) << std::right << fl_dec // 1
	      << std::setw(12) << std::right << fl_lep // 2
	      << std::setw(12) << std::right << 1.0 // 3
	      << std::setw(12) << std::right << 0.0 // 4
	      << std::setw(12) << std::right << 1.0 // 5
	      << std::setw(12) << std::right << 1.0 // 6
	      << std::setw(12) << std::right << 0.0 // 7
	      << std::setw(12) << std::right << 1.0 // 8
	      << std::setw(12) << std::right << 1.0 // 9
	      << std::setw(12) << std::right << 0.0 // 10
	      << std::setw(12) << std::right << 1.0 // 11
	      << std::setw(12) << std::right << R_ss_dstr [dec_index(fl_dec)] // 12
	      << std::setw(12) << std::right << R_ss_dstrE[dec_index(fl_dec)] // 13
	      << std::setw(12) << std::right << scale_s1_dstr // 14
	      << std::setw(12) << std::right << 1.0 // 15
	      << std::setw(12) << std::right << 0.0 // 16
	      << std::setw(12) << std::right << 1.0 // 17
	      << std::setw(12) << std::right << R_bb_dstr [dec_index(fl_dec)] // 18
	      << std::setw(12) << std::right << R_bb_dstrE[dec_index(fl_dec)] // 19
	      << std::setw(12) << std::right << scale_b1_dstr // 20
	      << " HUGEEEE"
	      << std::endl;

    std::cout << std::setw(12) << std::right << dec_index(fl_dec) // 0
	      << std::setw(12) << std::right << 421 // 1
	      << std::setw(12) << std::right << fl_lep // 2
	      << std::setw(12) << std::right << 1.0 // 3
	      << std::setw(12) << std::right << 0.0 // 4
	      << std::setw(12) << std::right << 1.0 // 5
	      << std::setw(12) << std::right << 1.0 // 6
	      << std::setw(12) << std::right << 0.0 // 7
	      << std::setw(12) << std::right << 1.0 // 8
	      << std::setw(12) << std::right << 1.0 // 9
	      << std::setw(12) << std::right << 0.0 // 10
	      << std::setw(12) << std::right << 1.0 // 11
	      << std::setw(12) << std::right << R_ss_dstr [0] // 12
	      << std::setw(12) << std::right << R_ss_dstrE[0] // 13
	      << std::setw(12) << std::right << scale_s2_dstr // 14
	      << std::setw(12) << std::right << 1.0 // 15
	      << std::setw(12) << std::right << 0.0 // 16
	      << std::setw(12) << std::right << 1.0 // 17
	      << std::setw(12) << std::right << R_bb_dstr [0] // 18
	      << std::setw(12) << std::right << R_bb_dstrE[0] // 19
	      << std::setw(12) << std::right << scale_b2_dstr // 20
	      << " HUGEEEE"
	      << std::endl;
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  d_fit_result_mc   ->Print("v");
  d_fit_result_dt   ->Print("v");
  dstr_fit_result_mc->Print("v");
  dstr_fit_result_dt->Print("v");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  can->Update();
  can->Print( Form("pic/dmass_deltam_morecalib_%d_%d.ps", fl_dec,fl_lep) ); 
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
