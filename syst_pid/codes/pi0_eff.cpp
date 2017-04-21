// information from BN1244 is used
//

#include <string>
#include <iostream>
#include <cmath>

#include "pi0_eff.h"
#include <stdio.h>



// from http://belle.kek.jp/secured/wiki/doku.php?id=software:systematics:ks_systematic
const double pi0_eff::table_eff[12] = { 
  1.009,  0.9226, 0.9348, 0.9295,
  0.9463, 0.9455, 0.9713, 0.9699,
  0.9772, 0.9620, 0.9839, 0.9567,
};

const double pi0_eff::table_err[12] = {
  0.023, 0.021, 0.021, 0.021,
  0.022, 0.021, 0.022, 0.022,
  0.022, 0.022, 0.023, 0.023,
};
  
// Constructor
pi0_eff::pi0_eff(){
  for( int i=0; i<12; i++ ){
    bin_count[i] = 0;
  }
  global_count = 0;
  
}

void pi0_eff::add(double p)
{
  
  // Momentum indices
  int p_index;

  // check for momentum index
  if ( p <= 0.5                ) p_index = 0;
  if ( (0.5 < p) && (p <= 1.0) ) p_index = 1;
  if ( (1.0 < p) && (p <= 1.5) ) p_index = 2;
  if ( (1.5 < p) && (p <= 2.0) ) p_index = 3;
  if ( (2.0 < p) && (p <= 2.5) ) p_index = 4;
  if ( (2.5 < p) && (p <= 3.0) ) p_index = 5;
  if ( (3.0 < p) && (p <= 3.5) ) p_index = 6;
  if ( (3.5 < p) && (p <= 4.0) ) p_index = 7;
  if ( (4.0 < p) && (p <= 4.5) ) p_index = 8;
  if ( (4.5 < p) && (p <= 5.0) ) p_index = 9;
  if ( (5.0 < p) && (p <= 5.5) ) p_index =10;
  if ( 5.5 < p                 ) p_index =11;
  
  // Increment global counter and bin counter
  ++global_count;
  ++bin_count[p_index];
}

int pi0_eff::get_totalNum() {
  //returns the total number of events considered up to this point
  return global_count;
}

// call this at the very end
double pi0_eff::total_effFactor() {
  //Weighs each factor by the statistics recorded in bin_count[][]
  
  // Initialize
  double p_err[12] = {0};
  double p_wgt[12] = {0};
  // For efficiency factors
  double p_eff[12] = {0};

  //count how many in each row
  int row_total[12] = {0,0,0};
  for (int p=0; p<12; ++p) {
    row_total[p] +=  bin_count[p]; 
  }

  // loop over all indices, add weighted factor N_i / (sigma_i)^2
  for (int p=0; p<12; ++p) {
  // for each row
  double cos_w = 0.; //sum of frac/sig^2 for each row
  double c_wgt = 0; // sum of frac^2 for each row
  double eff_w = 0.; //sum of eff*frac/sig^2 for each row
  double eff_wgt = 0.; //normalized sum of 1/sig^2
  double frac_cos = 0.;
  // get number in this bin, divide by total to get frac
  if (row_total[p] > 0) frac_cos = double(bin_count[p])/double(row_total[p]);
  // (if == 0 then frac_cos stays zero
  double err_sq = table_err[p]*table_err[p];
  // sum 1/sig^2 with weight (frac)
  cos_w += frac_cos*frac_cos/err_sq;
  eff_w += table_eff[p]*frac_cos/err_sq;
  eff_wgt += frac_cos/err_sq;
  c_wgt += frac_cos*frac_cos;
  
  // now get p weighted err
  if (cos_w > 0) p_err[p] = sqrt(c_wgt)/sqrt(cos_w); // total err for this p
  if (eff_w > 0) p_eff[p] = eff_w/eff_wgt;
  p_wgt[p] = double(row_total[p])/double(global_count); // frac in this p region
  }
  
  // fraction of events in each momentum region
  double fr1  = p_wgt[ 0];
  double fr2  = p_wgt[ 1];
  double fr3  = p_wgt[ 2];
  double fr4  = p_wgt[ 3];
  double fr5  = p_wgt[ 4];
  double fr6  = p_wgt[ 5];
  double fr7  = p_wgt[ 6];
  double fr8  = p_wgt[ 7];
  double fr9  = p_wgt[ 8];
  double fr10 = p_wgt[ 9];
  double fr11 = p_wgt[10];
  double fr12 = p_wgt[11];
  // safety net
  double term1 = 0; if (p_err[0] > 0) term1 = fr1/(p_err[0]*p_err[0]);
  double eff_term1 = 0; if (p_err[0] > 0) eff_term1 = p_eff[0]*fr1/(p_err[0]*p_err[0]);
  double term2 = 0; if (p_err[1] > 0) term2 = fr2/(p_err[1]*p_err[1]);
  double eff_term2 = 0; if (p_err[1] > 0) eff_term2 = p_eff[1]*fr2/(p_err[1]*p_err[1]);
  double term3 = 0; if (p_err[2] > 0) term3 = fr3/(p_err[2]*p_err[2]);
  double eff_term3 = 0; if (p_err[2] > 0) eff_term3 = p_eff[2]*fr3/(p_err[2]*p_err[2]);
  double term4 = 0; if (p_err[3] > 0) term4 = fr4/(p_err[3]*p_err[3]);
  double eff_term4 = 0; if (p_err[3] > 0) eff_term4 = p_eff[3]*fr4/(p_err[3]*p_err[3]);
  double term5 = 0; if (p_err[4] > 0) term5 = fr5/(p_err[4]*p_err[4]);
  double eff_term5 = 0; if (p_err[4] > 0) eff_term5 = p_eff[4]*fr5/(p_err[4]*p_err[4]);
  double term6 = 0; if (p_err[5] > 0) term6 = fr6/(p_err[5]*p_err[5]);
  double eff_term6 = 0; if (p_err[5] > 0) eff_term6 = p_eff[5]*fr6/(p_err[5]*p_err[5]);
  double term7 = 0; if (p_err[6] > 0) term7 = fr7/(p_err[6]*p_err[6]);
  double eff_term7 = 0; if (p_err[6] > 0) eff_term7 = p_eff[6]*fr7/(p_err[6]*p_err[6]);
  double term8 = 0; if (p_err[7] > 0) term8 = fr8/(p_err[7]*p_err[7]);
  double eff_term8 = 0; if (p_err[7] > 0) eff_term8 = p_eff[7]*fr8/(p_err[7]*p_err[7]);
  double term9 = 0; if (p_err[8] > 0) term9 = fr9/(p_err[8]*p_err[8]);
  double eff_term9 = 0; if (p_err[8] > 0) eff_term9 = p_eff[8]*fr9/(p_err[8]*p_err[8]);
  double term10 = 0; if (p_err[9] > 0) term10 = fr10/(p_err[9]*p_err[9]);
  double eff_term10 = 0; if (p_err[9] > 0) eff_term10 = p_eff[9]*fr10/(p_err[9]*p_err[9]);
  double term11 = 0; if (p_err[10] > 0) term11 = fr11/(p_err[10]*p_err[10]);
  double eff_term11 = 0; if (p_err[10] > 0) eff_term11 = p_eff[10]*fr11/(p_err[10]*p_err[10]);
  double term12 = 0; if (p_err[11] > 0) term12 = fr12/(p_err[11]*p_err[11]);
  double eff_term12 = 0; if (p_err[11] > 0) eff_term12 = p_eff[11]*fr12/(p_err[11]*p_err[11]);
  
  // weigh errors frac/sig^2
  double total_w = term1 + term2 + term3 + term4 + term5 + term6 + term7 + term8 + term9 + term10 + term11 + term12 ;

  double total_eff = 0.;
  if (total_w > 0) total_eff = (eff_term1+eff_term2+eff_term3+eff_term4+eff_term5+eff_term6+eff_term7+eff_term8+eff_term9+eff_term10+eff_term11+eff_term12)/total_w;

  return total_eff;

}


double pi0_eff::total_errFactor() {

  //Weighs each error by corresponding statistics in bin_count[][]

  // Initialize
  double p_err[12] = {0};
  double p_wgt[12] = {0};

  //count how many in each row (sum cosTheta bins)
  int row_total[12] = {0};
  for (int p=0; p<12; ++p) { 
    row_total[p] +=  bin_count[p];
  }
 
  // loop over all indices, add weighted factor N_i / (sigma_i)^2
  for (int p=0; p<12; ++p) {
    // for each row
    double cos_w = 0.; //sum of frac/sig^2 for each row
    double c_wgt = 0; // sum of frac^2 for each row
    double frac_cos = 0.;
    // get number in this bin, divide by total to get frac
    if (row_total[p] > 0) frac_cos = double(bin_count[p])/double(row_total[p]);
    // (if == 0 then frac_cos stays zero
    double err_sq = table_err[p]*table_err[p];
    // sum 1/sig^2 with weight (frac)
    cos_w += frac_cos*frac_cos/err_sq;
    c_wgt += frac_cos*frac_cos;
    
    // now get p weighted err
    if (cos_w > 0) p_err[p] = (c_wgt)/sqrt(cos_w); // total err for this p
    p_wgt[p] = double(row_total[p])/double(global_count); // frac in this p region
  }
  
  // safety net
  double term1  = 0; if (p_err[ 0] > 0) term1  = p_wgt[ 0]*p_wgt[ 0]/(p_err[ 0]*p_err[ 0]);
  double term2  = 0; if (p_err[ 1] > 0) term2  = p_wgt[ 1]*p_wgt[ 1]/(p_err[ 1]*p_err[ 1]);
  double term3  = 0; if (p_err[ 2] > 0) term3  = p_wgt[ 2]*p_wgt[ 2]/(p_err[ 2]*p_err[ 2]);
  double term4  = 0; if (p_err[ 3] > 0) term4  = p_wgt[ 3]*p_wgt[ 3]/(p_err[ 3]*p_err[ 3]);
  double term5  = 0; if (p_err[ 4] > 0) term5  = p_wgt[ 4]*p_wgt[ 4]/(p_err[ 4]*p_err[ 4]);
  double term6  = 0; if (p_err[ 5] > 0) term6  = p_wgt[ 5]*p_wgt[ 5]/(p_err[ 5]*p_err[ 5]);
  double term7  = 0; if (p_err[ 6] > 0) term7  = p_wgt[ 6]*p_wgt[ 6]/(p_err[ 6]*p_err[ 6]);
  double term8  = 0; if (p_err[ 7] > 0) term8  = p_wgt[ 7]*p_wgt[ 7]/(p_err[ 7]*p_err[ 7]);
  double term9  = 0; if (p_err[ 8] > 0) term9  = p_wgt[ 8]*p_wgt[ 8]/(p_err[ 8]*p_err[ 8]);
  double term10 = 0; if (p_err[ 9] > 0) term10 = p_wgt[ 9]*p_wgt[ 9]/(p_err[ 9]*p_err[ 9]);
  double term11 = 0; if (p_err[10] > 0) term11 = p_wgt[10]*p_wgt[10]/(p_err[10]*p_err[10]);
  double term12 = 0; if (p_err[11] > 0) term12 = p_wgt[11]*p_wgt[11]/(p_err[11]*p_err[11]);


  // weigh errors frac/sig^2
  double total_w = term1 + term2 + term3 + term4 + term5 + term6 + term7 + term8 + term9 + term10 + term11 + term12;
  double total_err = 0.;
  if (total_w > 0) total_err = (p_wgt[0]*p_wgt[0] + p_wgt[1]*p_wgt[1] + p_wgt[2]*p_wgt[2] + p_wgt[3]*p_wgt[3] + p_wgt[4]*p_wgt[4] + p_wgt[5]*p_wgt[5] + p_wgt[6]*p_wgt[6] + p_wgt[7]*p_wgt[7] + p_wgt[8]*p_wgt[8] + p_wgt[9]*p_wgt[9] + p_wgt[10]*p_wgt[10] + p_wgt[11]*p_wgt[11])/sqrt(total_w);

  //return total_err;
  return 0.023;

}
