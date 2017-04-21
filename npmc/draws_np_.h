#ifndef DRAWS_NP_H
#define DRAWS_NP_H

#include <iomanip>

//NeuroBayes
#include "NeuroBayesTeacher.hh"
#include "NeuroBayesExpert.hh"

/* type-II 2HDM
const Int_t nfile = 11;
const Char_t* model      = "2HDMII";
const Char_t* param_name = "tan#beta/m_{H^{+}}";
const Char_t* param_unit = "[GeV^{-1}]";
const Double_t param  [nfile] = {  0.0,   0.1,   0.2,   0.3,   0.4,   0.5,   0.6,   0.7,   0.8,   0.9,   1.0  };
const Char_t*  tagdir [nfile] = { "0p0", "0p1", "0p2", "0p3", "0p4", "0p5", "0p6", "0p7", "0p8", "0p9", "1p0" };
*/
/* R2 LQ
const Int_t nfile = 12;
const Char_t* model      = "R2LQ";
const Char_t* param_name = "C_{T}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {     0.000       -0.150,      -0.100,      -0.040,      -0.030,      0.090,      0.180,      0.250,      0.260,      0.340,      0.360,      0.400  };
const Char_t*  tagdir [nfile] = { "R2_0p000", "R2_m0p150", "R2_m0p100", "R2_m0p040", "R2_m0p030", "R2_0p090", "R2_0p180", "R2_0p250", "R2_0p260", "R2_0p340", "R2_0p360", "R2_0p400" };
*/
/* S1 LQ
const Int_t nfile = 12;
const Char_t* model      = "S1LQ";
const Char_t* param_name = "C_{T}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {     0.000       -0.150,      -0.100,      -0.040,      -0.030,      0.090,      0.180,      0.250,      0.260,      0.340,      0.360,      0.400  };
const Char_t*  tagdir [nfile] = { "S1_0p000", "S1_m0p150", "S1_m0p100", "S1_m0p040", "S1_m0p030", "S1_0p090", "S1_0p180", "S1_0p250", "S1_0p260", "S1_0p340", "S1_0p360", "S1_0p400" };
*/

/* OP(S1)
const Int_t nfile = 10;
const Char_t* model      = "OPS1";
const Char_t* param_name = "C_{S1}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {        0.00,         -5.00,         -4.00,         -3.00,         -2.00,         -1.00,         1.00,         1.05,         2.00,         3.00 };
const Char_t*  tagdir [nfile] = { "OP_S1_0p00", "OP_S1_m5p00", "OP_S1_m4p00", "OP_S1_m3p00", "OP_S1_m2p00", "OP_S1_m1p00", "OP_S1_1p00", "OP_S1_1p05", "OP_S1_2p00", "OP_S1_3p00"};
*/

/* OP(S2)
const Int_t nfile = 9;
const Char_t* model      = "OPS2";
const Char_t* param_name = "C_{S2}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {        0.00,         -3.00,         -2.00,         -1.00,         1.00,         2.00,         3.00,         4.00,         5.00 };
const Char_t*  tagdir [nfile] = { "OP_S2_0p00", "OP_S2_m3p00", "OP_S2_m2p00", "OP_S2_m1p00", "OP_S2_1p00", "OP_S2_2p00", "OP_S2_3p00", "OP_S2_4p00", "OP_S2_5p00"};
*/

/* OP(V1)
const Int_t nfile = 9;
const Char_t* model      = "OPV1";
const Char_t* param_name = "C_{V1}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {        0.00,         -2.50,         -2.10,         -2.00,         -1.50,         -1.00,         -0.50,         0.10,         0.50  };
const Char_t*  tagdir [nfile] = { "OP_V1_0p00", "OP_V1_m2p50", "OP_V1_m2p10", "OP_V1_m2p00", "OP_V1_m1p50", "OP_V1_m1p00", "OP_V1_m0p50", "OP_V1_0p10", "OP_V1_0p50" };
*/

///* OP(V2)
const Int_t nfile = 9;
const Char_t* model      = "OPV2";
const Char_t* param_name = "C_{V2}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {        0.00,         -0.50,         -0.10,         0.50,         1.00,         1.50,         1.88,         2.00,         2.50 };
const Char_t*  tagdir [nfile] = { "OP_V2_0p00", "OP_V2_m0p50", "OP_V2_m0p10", "OP_V2_0p50", "OP_V2_1p00", "OP_V2_1p50", "OP_V2_1p88", "OP_V2_2p00", "OP_V2_2p50"};
//*/

/* OP(T)
const Int_t nfile = 11;
const Char_t* model      = "OPT";
const Char_t* param_name = "C_{T}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {       0.00,        -0.15,        -0.07,        -0.04,        0.07,        0.15,        0.22,        0.30,        0.36,        0.37,        0.45 };
const Char_t*  tagdir [nfile] = { "OP_T_0p00", "OP_T_m0p15", "OP_T_m0p07", "OP_T_m0p04", "OP_T_0p07", "OP_T_0p15", "OP_T_0p22", "OP_T_0p30", "OP_T_0p36", "OP_T_0p37", "OP_T_0p45"};
*/


/* OP(V1)
const Int_t nfile = 2;
const Char_t* model      = "OPV1";
const Char_t* param_name = "C_{V1}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {  0.00,        -2.10  };
const Char_t*  tagdir [nfile] = { "0p0", "OP_V1_m2p10" };
*/

/* OP(V2)
const Int_t nfile = 2;
const Char_t* model      = "OPV2";
const Char_t* param_name = "C_{V2}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {  0.00,        1.88  };
const Char_t*  tagdir [nfile] = { "0p0", "OP_V2_1p88" };
*/

/* OP(S1)
const Int_t nfile = 2;
const Char_t* model      = "OPS1";
const Char_t* param_name = "C_{S1}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {  0.00,        1.05  };
const Char_t*  tagdir [nfile] = { "0p0", "OP_S1_1p05" };
*/

const Int_t    nvar = 4;        //q2,  cos_d,   cos_w,  cos_t
const Int_t    nbin    [nvar] = {   12,     12,      12,     12 };
//const Int_t    nbin    [nvar] = {    8,      8,       8,      8 };
const Double_t xmin    [nvar] = {  3.1,   -1.0,    -1.0,   -1.0 };
const Double_t xmax    [nvar] = { 11.8,    1.0,     1.0,    1.0 };
const Char_t*  brname  [nvar] = {"q2", "cos_d", "cos_w", "cos_t"};
const Char_t*  axisname[nvar] = {"q^{2} [GeV^{2}]", "cos#theta_{D}", "cos#theta_{W}", "cos#theta_{#tau}"};

void getIndex( Int_t index, Int_t sub_index[nvar] ){
  for( Int_t ivar=nvar-1; ivar>=0; ivar-- ){
    Int_t tmp = 1;
    for( Int_t i=0; i<ivar; i++ ) tmp *= nbin[i];
    sub_index[ivar] = index/tmp;
    index -= sub_index[ivar]*tmp;
  }
  return;
}

Int_t getGIndex( const Int_t sub_index[nvar], const Bool_t fl_message=false ){
  Int_t index = 0;
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    Int_t tmp = 1;
    for( Int_t i=0; i<ivar; i++ ){
      tmp *= nbin[i];
    }
    index += sub_index[ivar]*tmp;
  }

  if( fl_message ){
    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      std::cout << std::setw(3) << std::right << sub_index[ivar];
      if( ivar!=nvar-1 ) std::cout << ", ";
      else               std::cout << " -> ";
    }
    std::cout << "gindex = " << std::setw(7) << std::right << index << std::endl;
  }
  return index;
}

Int_t getGIndex( const Double_t val[nvar], const Bool_t fl_message=false ){
  Int_t sub_index[nvar];
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    Double_t width = (xmax[ivar]-xmin[ivar])/nbin[ivar];
    for( Int_t ibin=0; ibin<nbin[ivar]; ibin++ ){
      if( val[ivar] < xmin[ivar]+(ibin+1)*width ){
	sub_index[ivar] = ibin;
	break;
      }
      if( ibin==nbin[ivar]-1 ){
	std::cerr << "[WARNING] too large value ?" << std::endl;
	sub_index[ivar] = ibin;
      }
    }
  }
  if( fl_message ){
    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      std::cout << std::setw(12) << std::right << val[ivar];
      if( ivar!=nvar-1 ) std::cout << ", ";
      else               std::cout << " -> ";
    }
  }
  return getGIndex( sub_index, fl_message );
}

std::string makeCut_np( const Int_t index, const Bool_t fl_message=false ){
  std::stringstream sTmp;
  sTmp << "1";
  Int_t sub_index[nvar] = {0};
  getIndex( index, sub_index );
  if( fl_message ) std::cout << std::setw(5) << std::right << index << " : "
			     << std::setw(3) << std::right << sub_index[0] << ", "
			     << std::setw(3) << std::right << sub_index[1] << ", "
			     << std::setw(3) << std::right << sub_index[2] << ", "
			     << std::setw(3) << std::right << sub_index[3] << " : ";
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    //if( ivar==1 ) continue; // for the case of D tau nu
    sTmp << Form( " && (%f < %s && %f > %s)",
		  xmin[ivar] + (sub_index[ivar]  )*(xmax[ivar]-xmin[ivar])/nbin[ivar], brname[ivar],
		  xmin[ivar] + (sub_index[ivar]+1)*(xmax[ivar]-xmin[ivar])/nbin[ivar], brname[ivar]
		  );
  }
  if( fl_message ) std::cout << sTmp.str().c_str() << " : ";

  return sTmp.str();
}

#endif
