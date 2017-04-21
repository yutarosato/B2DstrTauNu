#ifndef DRAWS_NPCURVE_H
#define DRAWS_NPCURVE_H


const Int_t    ng          = 3;
const Int_t    fl_lep [ng] = {       0,     10,     1 };
const Char_t*  fl_name[ng] = {"e, #mu",    "e",  "#mu"};
const Double_t syst   [ng] = {   0.035,  0.041,  0.059};


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void AddSystematic( TGraphErrors* g, Double_t syst ){
  for( Int_t ip=0; ip<g->GetN(); ip++ ){
    Double_t val = g->GetY ()[ip];
    Double_t err = g->GetEY()[ip];
    err = sqrt( pow(err,2) + pow(syst*val,2) );
    g->SetPointError( ip, 0.0, err );
  }
  
  return;
}

TGraph* makeBand( TGraphErrors* g, Int_t col ){
  TGraph* band = new TGraph();
  band->SetFillColor(col);
  for( Int_t ip=0;           ip<g->GetN(); ip++ ) band->SetPoint( band->GetN(), g->GetX()[ip], g->GetY()[ip] + g->GetEY()[ip] );
  for( Int_t ip=g->GetN()-1; ip>=0;        ip-- ) band->SetPoint( band->GetN(), g->GetX()[ip], g->GetY()[ip] - g->GetEY()[ip] );

  band->GetXaxis()->SetTitle("Parameter");
  band->GetYaxis()->SetTitle("R(D*)");

  return band;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

double pi = 3.14159265359;
double G_F = 1.1663787 * pow(10, -5); // GeV^-2

double Bmass = 5.27925; // GeV
double taumass = 1.77682; // GeV
double Blife = 1.641 * pow(10, -12) / ( 6.58211928 * pow(10, -25) ); // GeV^-1

double f_B = 0.191; // GeV
double f_B_Err = 0.009; // GeV
double V_ub = 0.00415; // inclusive + exclusive from PDG 2012
double V_ub_Err = 0.00049; // inclusive + exclusive from PDG 2012


// parameters for Dtaunu

double bmass = 4.20; // m_b(MSbar) = 4.20 +/- 0.07 GeV
double dbmass = 0.07; // m_b(MSbar) = 4.20 +/- 0.07 GeV
double cmass = 0.901; // m_c(MSbar) = 0.901 +0.111/-0.113 GeV
double dcmass = 0.113; // m_c(MSbar) = 0.901 +0.111/-0.113 GeV (larger one taken)

double rho1_2 = 1.186; // rho_1^2 = 1.186 +/- 0.036 +/- 0.041 (HFAG)
double drho1_2 = 0.055; // rho_1^2 = 1.186 +/- 0.036 +/- 0.041 (HFAG)
double a = 1.; // a = 1 +/- 1 (Tanaka, Watanabe)
double da = 1.; // a = 1 +/- 1 (Tanaka, Watanabe)

double rhoA1_2 = 1.207; // rho_{A_1}^2 = 1.207 +/- 0.015 +/- 0.021 (HFAG)
double drhoA1_2 = 0.026; // rho_{A_1}^2 = 1.207 +/- 0.015 +/- 0.021 (HFAG)
double R1 = 1.403; // R_1(1) = 1.403 +/- 0.033 (HFAG)
double dR1 = 0.033; // R_1(1) = 1.403 +/- 0.033 (HFAG)
double R2 = 0.854; // R_2(1) = 0.854 +/- 0.020 (HFAG)
double dR2 = 0.020; // R_2(1) = 0.854 +/- 0.020 (HFAG)
double a3 = 1.; // a_3 = 1 +/- 1 (Tanaka, Watanabe)
double da3 = 1.; // a_3 = 1 +/- 1 (Tanaka, Watanabe)

double Get_R_Dsttaunu( double tanb, double hmass ){
  // Obtain central value of R(D*taunu)
  // Based on calculation of Y. Sakaki, R. Watanabe, and M. Tanaka in 2012

  double rhoA1_4 = rhoA1_2 * rhoA1_2;
  double R1_2 = R1 * R1;
  double R2_2 = R2 * R2;
  double a3_2 = a3 * a3;
    
  double bcmass = bmass + cmass;
  double cs1cs2 = - taumass * bmass / pow(hmass, 2) * pow(tanb, 2)
    + taumass * cmass / pow(hmass, 2);
    
  double L1 = + (5.538 - 0.005388 * R1 + 0.1344 * R1_2 - 2.027 * R2 + 0.3519 * R2_2
		 + 5.400 * 0.01 * a3 + 7.117 * 0.0001 * a3_2 - 2.444 * 0.01 * R2 * a3) * 0.01;
  double L2 = - (15.64 - 0.01815  * R1 + 0.4034 * R1_2 - 6.847 * R2 + 1.226  * R2_2
		 + 17.11 * 0.01 * a3 + 20.83 * 0.0001 * a3_2 - 7.749 * 0.01 * R2 * a3) * 0.001;
  double L3 = + (12.97 - 0.01635  * R1 + 0.3373 * R1_2 - 6.254 * R2 + 1.144  * R2_2
		 + 14.90 * 0.01 * a3 + 17.09 * 0.0001 * a3_2 - 6.756 * 0.01 * R2 * a3) * 0.0001;
  
  double L4 = + (1.136 - 1.028 * R2 + 0.2327 * R2_2
		 + 5.972 * 0.01 * a3 + 8.307 * 0.0001 * a3_2 - 2.701 * 0.01 * R2 * a3) * 0.01;
  double L5 = - (3.611 - 3.272 * R2 + 0.7412 * R2_2
		 + 17.55 * 0.01 * a3 + 22.48 * 0.0001 * a3_2 - 7.946 * 0.01 * R2 * a3) * 0.001;
  double L6 = + (3.154 - 2.859 * R2 + 0.6481 * R2_2
		 + 14.44 * 0.01 * a3 + 17.35 * 0.0001 * a3_2 - 6.541 * 0.01 * R2 * a3) * 0.0001;
  
  double L7 = + (0.3132 - 0.2834 * R2 + 0.06409 * R2_2
		 + 1.738 * 0.01 * a3 + 2.538 * 0.0001 * a3_2 - 0.7857 * 0.01 * R2 * a3) * 0.01;
  double L8 = - (0.9240 - 0.8368 * R2 + 0.1895  * R2_2
		 + 4.724 * 0.01 * a3 + 6.346 * 0.0001 * a3_2 - 2.138  * 0.01 * R2 * a3) * 0.001;
  double L9 = + (0.7623 - 0.6908 * R2 + 0.1565  * R2_2
		 + 3.658 * 0.01 * a3 + 4.600 * 0.0001 * a3_2 - 1.657  * 0.01 * R2 * a3) * 0.0001;
  
  double BR_Dsttaunu_Factor = L1 + L2 * rhoA1_2 + L3 * rhoA1_4
    + (L4 + L5 * rhoA1_2 + L6 * rhoA1_4) * (4.91+1.77)/bcmass * cs1cs2
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77)/bcmass, 2) * pow(cs1cs2, 2);
  
  double L1_Dstlnu = + (32.87
			- 0.04784  * R1 + 0.8060  * R1_2
			- 17.68 * R2 + 3.351  * R2_2) * 0.01;
  double L2_Dstlnu = - (15.34
			- 0.02262  * R1 + 0.3460  * R1_2
			- 9.521 * R2 + 1.875  * R2_2) * 0.01;
  double L3_Dstlnu = + (1.993
			- 0.002827 * R1 + 0.04062 * R1_2
			- 1.337 * R2 + 0.2699 * R2_2) * 0.01;
  
  double BR_Dstlnu_Factor = L1_Dstlnu + L2_Dstlnu * rhoA1_2 + L3_Dstlnu * rhoA1_4;
  
  double R_Dsttaunu = BR_Dsttaunu_Factor / BR_Dstlnu_Factor;
  
  return R_Dsttaunu;
}


double Get_R_Dsttaunu_Err( double tanb, double hmass ){
  // Obtain error of R(D*taunu)
  // Based on calculation of Y. Sakaki, R. Watanabe, and M. Tanaka in 2012

  // basic parts

  double rhoA1_4 = rhoA1_2 * rhoA1_2;
  double R1_2 = R1 * R1;
  double R2_2 = R2 * R2;
  double a3_2 = a3 * a3;
  
  double bcmass = bmass + cmass;
  double cs1cs2 = - taumass * bmass / pow(hmass, 2) * pow(tanb, 2)
    + taumass * cmass / pow(hmass, 2);
  
  double L1 = + (5.538 - 0.005388 * R1 + 0.1344 * R1_2 - 2.027 * R2 + 0.3519 * R2_2
		 + 5.400 * 0.01 * a3 + 7.117 * 0.0001 * a3_2 - 2.444 * 0.01 * R2 * a3) * 0.01;
  double L2 = - (15.64 - 0.01815  * R1 + 0.4034 * R1_2 - 6.847 * R2 + 1.226  * R2_2
		 + 17.11 * 0.01 * a3 + 20.83 * 0.0001 * a3_2 - 7.749 * 0.01 * R2 * a3) * 0.001;
  double L3 = + (12.97 - 0.01635  * R1 + 0.3373 * R1_2 - 6.254 * R2 + 1.144  * R2_2
		 + 14.90 * 0.01 * a3 + 17.09 * 0.0001 * a3_2 - 6.756 * 0.01 * R2 * a3) * 0.0001;
  
  double L4 = + (1.136 - 1.028 * R2 + 0.2327 * R2_2
		 + 5.972 * 0.01 * a3 + 8.307 * 0.0001 * a3_2 - 2.701 * 0.01 * R2 * a3) * 0.01;
  double L5 = - (3.611 - 3.272 * R2 + 0.7412 * R2_2
		 + 17.55 * 0.01 * a3 + 22.48 * 0.0001 * a3_2 - 7.946 * 0.01 * R2 * a3) * 0.001;
  double L6 = + (3.154 - 2.859 * R2 + 0.6481 * R2_2
		 + 14.44 * 0.01 * a3 + 17.35 * 0.0001 * a3_2 - 6.541 * 0.01 * R2 * a3) * 0.0001;
  
  double L7 = + (0.3132 - 0.2834 * R2 + 0.06409 * R2_2
		 + 1.738 * 0.01 * a3 + 2.538 * 0.0001 * a3_2 - 0.7857 * 0.01 * R2 * a3) * 0.01;
  double L8 = - (0.9240 - 0.8368 * R2 + 0.1895  * R2_2
		 + 4.724 * 0.01 * a3 + 6.346 * 0.0001 * a3_2 - 2.138  * 0.01 * R2 * a3) * 0.001;
  double L9 = + (0.7623 - 0.6908 * R2 + 0.1565  * R2_2
		 + 3.658 * 0.01 * a3 + 4.600 * 0.0001 * a3_2 - 1.657  * 0.01 * R2 * a3) * 0.0001;
  
  double BR_Dsttaunu_Factor = L1 + L2 * rhoA1_2 + L3 * rhoA1_4
    + (L4 + L5 * rhoA1_2 + L6 * rhoA1_4) * (4.91+1.77)/bcmass * cs1cs2
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77)/bcmass, 2) * pow(cs1cs2, 2);
  
  double L1_Dstlnu = + (32.87
			- 0.04784  * R1 + 0.8060  * R1_2
			- 17.68 * R2 + 3.351  * R2_2) * 0.01;
  double L2_Dstlnu = - (15.34
			- 0.02262  * R1 + 0.3460  * R1_2
			- 9.521 * R2 + 1.875  * R2_2) * 0.01;
  double L3_Dstlnu = + (1.993
			- 0.002827 * R1 + 0.04062 * R1_2
			- 1.337 * R2 + 0.2699 * R2_2) * 0.01;
  
  double BR_Dstlnu_Factor = L1_Dstlnu + L2_Dstlnu * rhoA1_2 + L3_Dstlnu * rhoA1_4;
  
  double R_Dsttaunu = BR_Dsttaunu_Factor / BR_Dstlnu_Factor;
  
  // error due to the uncertainty of R1
  // obtained by taking the difference between R obtained with the central value of R1
  // and R obtained with R1 varied to plus/minus side (plus/minus selected so that the
  // difference becomes larger).
  
  double R1_plus = R1 + dR1;
  double R1_2_plus = R1_plus * R1_plus;
  
  double L1_R1_plus = + (5.538 - 0.005388 * R1_plus + 0.1344 * R1_2_plus - 2.027 * R2 + 0.3519 * R2_2
			 + 5.400 * 0.01 * a3 + 7.117 * 0.0001 * a3_2 - 2.444 * 0.01 * R2 * a3) * 0.01;
  double L2_R1_plus = - (15.64 - 0.01815  * R1_plus + 0.4034 * R1_2_plus - 6.847 * R2 + 1.226  * R2_2
			 + 17.11 * 0.01 * a3 + 20.83 * 0.0001 * a3_2 - 7.749 * 0.01 * R2 * a3) * 0.001;
  double L3_R1_plus = + (12.97 - 0.01635  * R1_plus + 0.3373 * R1_2_plus - 6.254 * R2 + 1.144  * R2_2
			 + 14.90 * 0.01 * a3 + 17.09 * 0.0001 * a3_2 - 6.756 * 0.01 * R2 * a3) * 0.0001;
  double BR_Dsttaunu_Factor_R1_plus = L1_R1_plus + L2_R1_plus * rhoA1_2 + L3_R1_plus * rhoA1_4
    + (L4 + L5 * rhoA1_2 + L6 * rhoA1_4) * (4.91+1.77)/bcmass * cs1cs2
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77)/bcmass, 2) * pow(cs1cs2, 2);
  
  double L1_Dstlnu_R1_plus = + (32.87
				- 0.04784  * R1_plus + 0.8060  * R1_2_plus
				- 17.68 * R2 + 3.351  * R2_2) * 0.01;
  double L2_Dstlnu_R1_plus = - (15.34
				- 0.02262  * R1_plus + 0.3460  * R1_2_plus
				- 9.521 * R2 + 1.875  * R2_2) * 0.01;
  double L3_Dstlnu_R1_plus = + (1.993
				- 0.002827 * R1_plus + 0.04062 * R1_2_plus
				- 1.337 * R2 + 0.2699 * R2_2) * 0.01;
  double BR_Dstlnu_Factor_R1_plus = L1_Dstlnu_R1_plus + L2_Dstlnu_R1_plus * rhoA1_2 + L3_Dstlnu_R1_plus * rhoA1_4;
  
  double R_Dsttaunu_R1_plus = BR_Dsttaunu_Factor_R1_plus / BR_Dstlnu_Factor_R1_plus;
  
  double R1_minus = R1 + dR1;
  double R1_2_minus = R1_minus * R1_minus;
  
  double L1_R1_minus = + (5.538 - 0.005388 * R1_minus + 0.1344 * R1_2_minus - 2.027 * R2 + 0.3519 * R2_2
			  + 5.400 * 0.01 * a3 + 7.117 * 0.0001 * a3_2 - 2.444 * 0.01 * R2 * a3) * 0.01;
  double L2_R1_minus = - (15.64 - 0.01815  * R1_minus + 0.4034 * R1_2_minus - 6.847 * R2 + 1.226  * R2_2
			  + 17.11 * 0.01 * a3 + 20.83 * 0.0001 * a3_2 - 7.749 * 0.01 * R2 * a3) * 0.001;
  double L3_R1_minus = + (12.97 - 0.01635  * R1_minus + 0.3373 * R1_2_minus - 6.254 * R2 + 1.144  * R2_2
			  + 14.90 * 0.01 * a3 + 17.09 * 0.0001 * a3_2 - 6.756 * 0.01 * R2 * a3) * 0.0001;
  double BR_Dsttaunu_Factor_R1_minus = L1_R1_minus + L2_R1_minus * rhoA1_2 + L3_R1_minus * rhoA1_4
    + (L4 + L5 * rhoA1_2 + L6 * rhoA1_4) * (4.91+1.77)/bcmass * cs1cs2
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77)/bcmass, 2) * pow(cs1cs2, 2);
  
  double L1_Dstlnu_R1_minus = + (32.87
				 - 0.04784  * R1_minus + 0.8060  * R1_2_minus
				 - 17.68 * R2 + 3.351  * R2_2) * 0.01;
  double L2_Dstlnu_R1_minus = - (15.34
				 - 0.02262  * R1_minus + 0.3460  * R1_2_minus
				 - 9.521 * R2 + 1.875  * R2_2) * 0.01;
  double L3_Dstlnu_R1_minus = + (1.993
				 - 0.002827 * R1_minus + 0.04062 * R1_2_minus
				 - 1.337 * R2 + 0.2699 * R2_2) * 0.01;
  double BR_Dstlnu_Factor_R1_minus = L1_Dstlnu_R1_minus + L2_Dstlnu_R1_minus * rhoA1_2 + L3_Dstlnu_R1_minus * rhoA1_4;
  
  double R_Dsttaunu_R1_minus = BR_Dsttaunu_Factor_R1_minus / BR_Dstlnu_Factor_R1_minus;
  
  double R_Dsttaunu_Err_R1;
  if(fabs(R_Dsttaunu_R1_plus - R_Dsttaunu) > fabs(R_Dsttaunu_R1_minus - R_Dsttaunu)) R_Dsttaunu_Err_R1 = fabs(R_Dsttaunu_R1_plus - R_Dsttaunu);
  else R_Dsttaunu_Err_R1 = fabs(R_Dsttaunu_R1_minus - R_Dsttaunu);
  
  // error due to the uncertainty of R2
  // obtained by taking the difference between R obtained with the central value of R2
  // and R obtained with R2 varied to plus/minus side (plus/minus selected so that the
  // difference becomes larger).

  double R2_plus = R2 + dR2;
  double R2_2_plus = R2_plus * R2_plus;
  
  double L1_R2_plus = + (5.538 - 0.005388 * R1 + 0.1344 * R1_2 - 2.027 * R2_plus + 0.3519 * R2_2_plus
			 + 5.400 * 0.01 * a3 + 7.117 * 0.0001 * a3_2 - 2.444 * 0.01 * R2_plus * a3) * 0.01;
  double L2_R2_plus = - (15.64 - 0.01815  * R1 + 0.4034 * R1_2 - 6.847 * R2_plus + 1.226  * R2_2_plus
			 + 17.11 * 0.01 * a3 + 20.83 * 0.0001 * a3_2 - 7.749 * 0.01 * R2_plus * a3) * 0.001;
  double L3_R2_plus = + (12.97 - 0.01635  * R1 + 0.3373 * R1_2 - 6.254 * R2_plus + 1.144  * R2_2_plus
			 + 14.90 * 0.01 * a3 + 17.09 * 0.0001 * a3_2 - 6.756 * 0.01 * R2_plus * a3) * 0.0001;
  double L4_R2_plus = + (1.136 - 1.028 * R2_plus + 0.2327 * R2_2_plus
			 + 5.972 * 0.01 * a3 + 8.307 * 0.0001 * a3_2 - 2.701 * 0.01 * R2_plus * a3) * 0.01;
  double L5_R2_plus = - (3.611 - 3.272 * R2_plus + 0.7412 * R2_2_plus
			 + 17.55 * 0.01 * a3 + 22.48 * 0.0001 * a3_2 - 7.946 * 0.01 * R2_plus * a3) * 0.001;
  double L6_R2_plus = + (3.154 - 2.859 * R2_plus + 0.6481 * R2_2_plus
			 + 14.44 * 0.01 * a3 + 17.35 * 0.0001 * a3_2 - 6.541 * 0.01 * R2_plus * a3) * 0.0001;
  double L7_R2_plus = + (0.3132 - 0.2834 * R2_plus + 0.06409 * R2_2_plus
			 + 1.738 * 0.01 * a3 + 2.538 * 0.0001 * a3_2 - 0.7857 * 0.01 * R2_plus * a3) * 0.01;
  double L8_R2_plus = - (0.9240 - 0.8368 * R2_plus + 0.1895  * R2_2_plus
			 + 4.724 * 0.01 * a3 + 6.346 * 0.0001 * a3_2 - 2.138  * 0.01 * R2_plus * a3) * 0.001;
  double L9_R2_plus = + (0.7623 - 0.6908 * R2_plus + 0.1565  * R2_2_plus
			 + 3.658 * 0.01 * a3 + 4.600 * 0.0001 * a3_2 - 1.657  * 0.01 * R2_plus * a3) * 0.0001;
  double BR_Dsttaunu_Factor_R2_plus = L1_R2_plus + L2_R2_plus * rhoA1_2 + L3_R2_plus * rhoA1_4
    + (L4_R2_plus + L5_R2_plus * rhoA1_2 + L6_R2_plus * rhoA1_4) * (4.91+1.77)/bcmass * cs1cs2
    + (L7_R2_plus + L8_R2_plus * rhoA1_2 + L9_R2_plus * rhoA1_4) * pow((4.91+1.77)/bcmass, 2) * pow(cs1cs2, 2);
  
  double L1_Dstlnu_R2_plus = + (32.87
				- 0.04784  * R1 + 0.8060  * R1_2
				- 17.68 * R2_plus + 3.351  * R2_2_plus) * 0.01;
  double L2_Dstlnu_R2_plus = - (15.34
				- 0.02262  * R1 + 0.3460  * R1_2
				- 9.521 * R2_plus + 1.875  * R2_2_plus) * 0.01;
  double L3_Dstlnu_R2_plus = + (1.993
				- 0.002827 * R1 + 0.04062 * R1_2
				- 1.337 * R2_plus + 0.2699 * R2_2_plus) * 0.01;
  double BR_Dstlnu_Factor_R2_plus = L1_Dstlnu_R2_plus + L2_Dstlnu_R2_plus * rhoA1_2 + L3_Dstlnu_R2_plus * rhoA1_4;
  
  double R_Dsttaunu_R2_plus = BR_Dsttaunu_Factor_R2_plus / BR_Dstlnu_Factor_R2_plus;
  
  double R2_minus = R2 - dR2;
  double R2_2_minus = R2_minus * R2_minus;
  
  double L1_R2_minus = + (5.538 - 0.005388 * R1 + 0.1344 * R1_2 - 2.027 * R2_minus + 0.3519 * R2_2_minus
			  + 5.400 * 0.01 * a3 + 7.117 * 0.0001 * a3_2 - 2.444 * 0.01 * R2_minus * a3) * 0.01;
  double L2_R2_minus = - (15.64 - 0.01815  * R1 + 0.4034 * R1_2 - 6.847 * R2_minus + 1.226  * R2_2_minus
			  + 17.11 * 0.01 * a3 + 20.83 * 0.0001 * a3_2 - 7.749 * 0.01 * R2_minus * a3) * 0.001;
  double L3_R2_minus = + (12.97 - 0.01635  * R1 + 0.3373 * R1_2 - 6.254 * R2_minus + 1.144  * R2_2_minus
			  + 14.90 * 0.01 * a3 + 17.09 * 0.0001 * a3_2 - 6.756 * 0.01 * R2_minus * a3) * 0.0001;
  double L4_R2_minus = + (1.136 - 1.028 * R2_minus + 0.2327 * R2_2_minus
			  + 5.972 * 0.01 * a3 + 8.307 * 0.0001 * a3_2 - 2.701 * 0.01 * R2_minus * a3) * 0.01;
  double L5_R2_minus = - (3.611 - 3.272 * R2_minus + 0.7412 * R2_2_minus
			  + 17.55 * 0.01 * a3 + 22.48 * 0.0001 * a3_2 - 7.946 * 0.01 * R2_minus * a3) * 0.001;
  double L6_R2_minus = + (3.154 - 2.859 * R2_minus + 0.6481 * R2_2_minus
			  + 14.44 * 0.01 * a3 + 17.35 * 0.0001 * a3_2 - 6.541 * 0.01 * R2_minus * a3) * 0.0001;
  double L7_R2_minus = + (0.3132 - 0.2834 * R2_minus + 0.06409 * R2_2_minus
			  + 1.738 * 0.01 * a3 + 2.538 * 0.0001 * a3_2 - 0.7857 * 0.01 * R2_minus * a3) * 0.01;
  double L8_R2_minus = - (0.9240 - 0.8368 * R2_minus + 0.1895  * R2_2_minus
			  + 4.724 * 0.01 * a3 + 6.346 * 0.0001 * a3_2 - 2.138  * 0.01 * R2_minus * a3) * 0.001;
  double L9_R2_minus = + (0.7623 - 0.6908 * R2_minus + 0.1565  * R2_2_minus
			  + 3.658 * 0.01 * a3 + 4.600 * 0.0001 * a3_2 - 1.657  * 0.01 * R2_minus * a3) * 0.0001;
  double BR_Dsttaunu_Factor_R2_minus = L1_R2_minus + L2_R2_minus * rhoA1_2 + L3_R2_minus * rhoA1_4
    + (L4_R2_minus + L5_R2_minus * rhoA1_2 + L6_R2_minus * rhoA1_4) * (4.91+1.77)/bcmass * cs1cs2
    + (L7_R2_minus + L8_R2_minus * rhoA1_2 + L9_R2_minus * rhoA1_4) * pow((4.91+1.77)/bcmass, 2) * pow(cs1cs2, 2);
  
  double L1_Dstlnu_R2_minus = + (32.87
				 - 0.04784  * R1 + 0.8060  * R1_2
				 - 17.68 * R2_minus + 3.351  * R2_2_minus) * 0.01;
  double L2_Dstlnu_R2_minus = - (15.34
				 - 0.02262  * R1 + 0.3460  * R1_2
				 - 9.521 * R2_minus + 1.875  * R2_2_minus) * 0.01;
  double L3_Dstlnu_R2_minus = + (1.993
				 - 0.002827 * R1 + 0.04062 * R1_2
				 - 1.337 * R2_minus + 0.2699 * R2_2_minus) * 0.01;
  double BR_Dstlnu_Factor_R2_minus = L1_Dstlnu_R2_minus + L2_Dstlnu_R2_minus * rhoA1_2 + L3_Dstlnu_R2_minus * rhoA1_4;
  
  double R_Dsttaunu_R2_minus = BR_Dsttaunu_Factor_R2_minus / BR_Dstlnu_Factor_R2_minus;
  
  double R_Dsttaunu_Err_R2;
  if(fabs(R_Dsttaunu_R2_plus - R_Dsttaunu) > fabs(R_Dsttaunu_R2_minus - R_Dsttaunu)) R_Dsttaunu_Err_R2 = fabs(R_Dsttaunu_R2_plus - R_Dsttaunu);
  else R_Dsttaunu_Err_R2 = fabs(R_Dsttaunu_R2_minus - R_Dsttaunu);
  
  // error due to the uncertainty of a3
  
  double dL1_da3 = + (+ 5.400 * 0.01 + 2 * 7.117 * 0.0001 * a3 - 2.444 * 0.01 * R2) * 0.01;
  double dL2_da3 = - (+ 17.11 * 0.01 + 2 * 20.83 * 0.0001 * a3 - 7.749 * 0.01 * R2) * 0.001;
  double dL3_da3 = + (+ 14.90 * 0.01 + 2 * 17.09 * 0.0001 * a3 - 6.756 * 0.01 * R2) * 0.0001;
  
  double dL4_da3 = + (+ 5.972 * 0.01 + 2 * 8.307 * 0.0001 * a3 - 2.701 * 0.01 * R2) * 0.01;
  double dL5_da3 = - (+ 17.55 * 0.01 + 2 * 22.48 * 0.0001 * a3 - 7.946 * 0.01 * R2) * 0.001;
  double dL6_da3 = + (+ 14.44 * 0.01 + 2 * 17.35 * 0.0001 * a3 - 6.541 * 0.01 * R2) * 0.0001;
  
  double dL7_da3 = + (+ 1.738 * 0.01 + 2 * 2.538 * 0.0001 * a3 - 0.7857 * 0.01 * R2) * 0.01;
  double dL8_da3 = - (+ 4.724 * 0.01 + 2 * 6.346 * 0.0001 * a3 - 2.138  * 0.01 * R2) * 0.001;
  double dL9_da3 = + (+ 3.658 * 0.01 + 2 * 4.600 * 0.0001 * a3 - 1.657  * 0.01 * R2) * 0.0001;
  
  double dBR_Dsttaunu_Factor_da3 = dL1_da3 + dL2_da3 * rhoA1_2 + dL3_da3 * rhoA1_4
    + (dL4_da3 + dL5_da3 * rhoA1_2 + dL6_da3 * rhoA1_4) * (4.91+1.77)/bcmass * cs1cs2
    + (dL7_da3 + dL8_da3 * rhoA1_2 + dL9_da3 * rhoA1_4) * pow((4.91+1.77)/bcmass, 2) * pow(cs1cs2, 2);
  
  double R_Dsttaunu_Err_a3 = dBR_Dsttaunu_Factor_da3 * da3 / BR_Dstlnu_Factor;
  
  // error due to the uncertainty of rhoA1_2
  // obtained by taking the difference between R obtained with the central value of rhoA1_2
  // and R obtained with rhoA1_2 varied to plus/minus side (plus/minus selected so that the
  // difference becomes larger).
  
  double rhoA1_2_plus = rhoA1_2 + drhoA1_2;
  double rhoA1_4_plus = rhoA1_2_plus * rhoA1_2_plus;
  double BR_Dsttaunu_Factor_rhoA1_2_plus
    = L1 + L2 * rhoA1_2_plus + L3 * rhoA1_4_plus
    + (L4 + L5 * rhoA1_2_plus + L6 * rhoA1_4_plus) * (4.91+1.77)/bcmass * cs1cs2
    + (L7 + L8 * rhoA1_2_plus + L9 * rhoA1_4_plus) * pow((4.91+1.77)/bcmass, 2) * pow(cs1cs2, 2);
  double BR_Dstlnu_Factor_rhoA1_2_plus = L1_Dstlnu + L2_Dstlnu * rhoA1_2_plus + L3_Dstlnu * rhoA1_4_plus;
  double R_Dsttaunu_rhoA1_2_plus = BR_Dsttaunu_Factor_rhoA1_2_plus / BR_Dstlnu_Factor_rhoA1_2_plus;
  
  double rhoA1_2_minus = rhoA1_2 - drhoA1_2;
  double rhoA1_4_minus = rhoA1_2_minus * rhoA1_2_minus;
  double BR_Dsttaunu_Factor_rhoA1_2_minus
    = L1 + L2 * rhoA1_2_minus + L3 * rhoA1_4_minus
    + (L4 + L5 * rhoA1_2_minus + L6 * rhoA1_4_minus) * (4.91+1.77)/bcmass * cs1cs2
    + (L7 + L8 * rhoA1_2_minus + L9 * rhoA1_4_minus) * pow((4.91+1.77)/bcmass, 2) * pow(cs1cs2, 2);
  double BR_Dstlnu_Factor_rhoA1_2_minus = L1_Dstlnu + L2_Dstlnu * rhoA1_2_minus + L3_Dstlnu * rhoA1_4_minus;
  double R_Dsttaunu_rhoA1_2_minus = BR_Dsttaunu_Factor_rhoA1_2_minus / BR_Dstlnu_Factor_rhoA1_2_minus;
  
  double R_Dsttaunu_Err_rhoA1_2;
  if(fabs(R_Dsttaunu_rhoA1_2_plus - R_Dsttaunu) > fabs(R_Dsttaunu_rhoA1_2_minus - R_Dsttaunu)) R_Dsttaunu_Err_rhoA1_2 = fabs(R_Dsttaunu_rhoA1_2_plus - R_Dsttaunu);
  else R_Dsttaunu_Err_rhoA1_2 = fabs(R_Dsttaunu_rhoA1_2_minus - R_Dsttaunu);
  
  // error due to the uncertainty of bmass
  /*  
  double dBR_Dsttaunu_Factor_dbmass
    = (L4 + L5 * rhoA1_2 + L6 * rhoA1_4) * (4.91+1.77) * taumass / pow(hmass, 2) * pow(tanb, 2) * (-cmass) / pow(bcmass, 2)
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77), 2) * pow(taumass, 2) / pow(hmass, 4) * pow(tanb, 4) * 2 * bmass * cmass / pow(bcmass, 3)
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77), 2) * pow(taumass, 2) / pow(hmass, 4) * pow(tanb, 2) * 2 * cmass * (bmass - cmass) / pow(bcmass, 3);
  */
  double dBR_Dsttaunu_Factor_dbmass // modified @20150406
    = (L4 + L5 * rhoA1_2 + L6 * rhoA1_4) *     (4.91+1.77)     *     taumass     / pow(hmass, 2) * ( -pow(tanb,2)/bcmass + (bmass*pow(tanb,2)+cmass)/pow(bcmass,2) )
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77), 2) * pow(taumass, 2) / pow(hmass, 4) * ( 2*(bmass*pow(tanb,2)+cmass)*pow(tanb,2)/pow(bcmass,2) -2*pow(bmass*pow(tanb,2)+cmass,2)/pow(bcmass,3) );
  double R_Dsttaunu_Err_bmass = dBR_Dsttaunu_Factor_dbmass * dbmass / BR_Dstlnu_Factor;
  
  // error due to the uncertainty of cmass
  
  /*
  double dBR_Dsttaunu_Factor_dcmass
    = (L4 + L5 * rhoA1_2 + L6 * rhoA1_4) * (4.91+1.77) * taumass / pow(hmass, 2) * pow(tanb, 2) * bmass / pow(bcmass, 2)
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77), 2) * pow(taumass, 2) / pow(hmass, 4) * 2 * bmass * cmass / pow(bcmass, 3)
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77), 2) * pow(taumass, 2) / pow(hmass, 4) * pow(tanb, 2) * (-2) * cmass * (bmass - cmass) / pow(bcmass, 3);
  */
  double dBR_Dsttaunu_Factor_dcmass // modified @20150406
    = (L4 + L5 * rhoA1_2 + L6 * rhoA1_4) *     (4.91+1.77)     *     taumass     / pow(hmass, 2) * ( -1/bcmass - (bmass*pow(tanb,2)+cmass)/pow(bcmass,2) )
    + (L7 + L8 * rhoA1_2 + L9 * rhoA1_4) * pow((4.91+1.77), 2) * pow(taumass, 2) / pow(hmass, 4) * ( 2*(bmass*pow(tanb,2)+cmass)/pow(bcmass,2) +2*pow(bmass*pow(tanb,2)+cmass,2)/pow(bcmass,3) );
  double R_Dsttaunu_Err_cmass = dBR_Dsttaunu_Factor_dcmass * dcmass / BR_Dstlnu_Factor;
  
  // total error
  
  double R_Dsttaunu_Err = sqrt( pow(R_Dsttaunu_Err_R1, 2) + pow(R_Dsttaunu_Err_R2, 2) + pow(R_Dsttaunu_Err_a3, 2)
				+ pow(R_Dsttaunu_Err_rhoA1_2, 2) + pow(R_Dsttaunu_Err_bmass, 2) + pow(R_Dsttaunu_Err_cmass, 2) );
  
  return R_Dsttaunu_Err;
}

double makefunc_R_Dsttaunu( const double* x, const double*p ){ return Get_R_Dsttaunu( 30.0, 30.0/x[0] ); }

TGraph* makeband_R_Dsttaunu( const double xmin, const double xmax ){
  TGraph* g = new TGraph();
  g->SetName( "errband_r_dsttaunu");
  g->SetTitle( "Error band for R(D*)" );
  const Int_t np = 1000;
  for( Int_t ip=0; ip<np+1; ip++ ){
    double x = xmin + ip*(xmax-xmin)/(double)np;
    double y = Get_R_Dsttaunu( 30.0, 30.0/x ) - Get_R_Dsttaunu_Err( 30.0, 30.0/x );
    g->SetPoint( g->GetN(), x, y );
    //if( ip==0 ) std::cout << "R(D*) = " << Get_R_Dsttaunu( 30.0, 30.0/x ) << " +- " << Get_R_Dsttaunu_Err( 30.0, 30.0/x ) << std::endl;
  }
  for( Int_t ip=0; ip<np+1; ip++ ){
    double x = xmax - ip*(xmax-xmin)/(double)np;
    double y = Get_R_Dsttaunu( 30.0, 30.0/x ) + Get_R_Dsttaunu_Err( 30.0, 30.0/x );
    g->SetPoint( g->GetN(), x, y );
  }
  g->SetFillColor(7);

  return g;
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Double_t cal_rdst_cs2(
		      Double_t rho_A1_2, Double_t a_3, Double_t R11, Double_t R21, Double_t mbPmc, Double_t mbMmc,
		      Double_t Re_CS2, Double_t Im_CS2
 ){
  Double_t hA11 = 0.908;
  TComplex CS2(  Re_CS2, Im_CS2 );

  Double_t f = 
    (0. + 0.030254643456755624*pow(hA11,2) - 
     0.000029428775442260747*pow(hA11,2)*R11 + 
     0.0007343694139646086*pow(hA11,2)*pow(R11,2) - 
     0.011072908714145064*pow(hA11,2)*R21 + 
     0.0019220011820663837*pow(hA11,2)*pow(R21,2) + 
     0.00029493794054002645*pow(hA11,2)*a_3 - 
     0.00013349521629621802*pow(hA11,2)*R21*a_3 + 
     3.887335265869437e-6*pow(hA11,2)*pow(a_3,2) - 
     0.008542734639407037*pow(hA11,2)*rho_A1_2 + 
     9.911598201286346e-6*pow(hA11,2)*R11*rho_A1_2 - 
     0.00022032907826043975*pow(hA11,2)*pow(R11,2)*rho_A1_2 + 
     0.0037396547918801*pow(hA11,2)*R21*rho_A1_2 - 
     0.0006697488809060423*pow(hA11,2)*pow(R21,2)*rho_A1_2 - 
     0.0000934263320002305*pow(hA11,2)*a_3*rho_A1_2 + 
     0.00004232437499355708*pow(hA11,2)*R21*a_3*rho_A1_2 - 
     1.1376776993503411e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2 + 
     0.0007082924178598534*pow(hA11,2)*pow(rho_A1_2,2) - 
     8.926704671522045e-7*pow(hA11,2)*R11*pow(rho_A1_2,2) + 
     0.000018420800360323613*pow(hA11,2)*pow(R11,2)*pow(rho_A1_2,2) - 
     0.0003415435683189837*pow(hA11,2)*R21*pow(rho_A1_2,2) + 
     0.00006245643308607658*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2) + 
     8.13860365504776e-6*pow(hA11,2)*a_3*pow(rho_A1_2,2) - 
     3.689264332183857e-6*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2) + 
     9.332412489660764e-8*pow(hA11,2)*pow(a_3,2)*pow(rho_A1_2,2) + 
     (0.0003814229854998974*pow(hA11,2)*
      (200.15571614318196 - 59.04502572984423*rho_A1_2 + 
       4.870911743325851*pow(rho_A1_2,2) + 
       pow(a_3,2)*(0.16216131714996518 - 0.04054426767332307*rho_A1_2 + 
		   0.0029390310478812237*pow(rho_A1_2,2)) + 
       a_3*(11.106642782949837 - 3.0183476082225646*rho_A1_2 + 
	    0.233693411287558*pow(rho_A1_2,2)) + 
       pow(R21,2)*(40.955261663752275 - 12.1052559135445*rho_A1_2 + 
		   1.*pow(rho_A1_2,2)) + 
       R21*(-181.078585088732 + 53.469638106474065*rho_A1_2 - 
	    4.414016899669555*pow(rho_A1_2,2) + 
	    a_3*(-5.020757230126823 + 1.3658857015288806*rho_A1_2 - 
		 //0.10583312272059556*pow(rho_A1_2,2))))*pow(fabs(CS2),2))/
		 0.10583312272059556*pow(rho_A1_2,2))))*pow(CS2.Rho(),2))/
     pow(mbPmc,2) - (0.04144330132436068*pow(hA11,2)*(CS2.Re()))/mbPmc + 
     (0.03751744750983049*pow(hA11,2)*R21*(CS2.Re()))/mbPmc - 
     (0.008490937717314413*pow(hA11,2)*pow(R21,2)*(CS2.Re()))/mbPmc - 
     (0.0021789378469524966*pow(hA11,2)*a_3*(CS2.Re()))/mbPmc + 
     (0.0009855979226152775*pow(hA11,2)*R21*a_3*(CS2.Re()))/mbPmc - 
     (0.00003030671973485405*pow(hA11,2)*pow(a_3,2)*(CS2.Re()))/mbPmc + 
     (0.013174986773668847*pow(hA11,2)*rho_A1_2*(CS2.Re()))/mbPmc - 
     (0.01193746784975276*pow(hA11,2)*R21*rho_A1_2*(CS2.Re()))/mbPmc + 
     (0.002704063504749281*pow(hA11,2)*pow(R21,2)*rho_A1_2*(CS2.Re()))/
     mbPmc + (0.0006402381880497138*pow(hA11,2)*a_3*rho_A1_2*(CS2.Re()))/
     mbPmc - (0.0002898839301224981*pow(hA11,2)*R21*a_3*rho_A1_2*(CS2.Re()))/
     mbPmc + (8.201227824109433e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2*
	      (CS2.Re()))/mbPmc - (0.001150592951757508*pow(hA11,2)*pow(rho_A1_2,2)*
				   (CS2.Re()))/mbPmc + (0.001043158289727365*pow(hA11,2)*R21*
							pow(rho_A1_2,2)*(CS2.Re()))/mbPmc - 
     (0.00023643993251746013*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2)*
      (CS2.Re()))/mbPmc - (0.00005266795972187148*pow(hA11,2)*a_3*
			   pow(rho_A1_2,2)*(CS2.Re()))/mbPmc + 
     (0.000023863324110618327*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2)*(CS2.Re()))/
     mbPmc - (6.330191780842525e-7*pow(hA11,2)*pow(a_3,2)*
	      pow(rho_A1_2,2)*(CS2.Re()))/mbPmc)/
    (0. + pow(hA11,2)*(0.17957389170325488 - 1.0948037887075082e-18*a_3 + 
		       2.3379438621231702e-36*pow(a_3,2) - 0.08378631617748233*rho_A1_2 + 
		       5.874693941030267e-19*a_3*rho_A1_2 - 
		       1.301922254855869e-36*pow(a_3,2)*rho_A1_2 + 
		       0.01088597422339019*pow(rho_A1_2,2) - 
		       8.230978688193583e-20*a_3*pow(rho_A1_2,2) + 
		       1.8671634465810482e-37*pow(a_3,2)*pow(rho_A1_2,2) + 
		       R11*(-0.00026130896343670175 + 0.00012355740482715148*rho_A1_2 - 
			    0.000015436303110645208*pow(rho_A1_2,2)) + 
		       pow(R11,2)*(0.004402759842982002 - 0.0018896455785886214*rho_A1_2 + 
				   0.00022186379848383934*pow(rho_A1_2,2)) + 
		       pow(R21,2)*(0.018303717615447346 - 0.010242486422778429*rho_A1_2 + 
				   0.0014741148938045372*pow(rho_A1_2,2)) + 
		       R21*(-0.09657467358167796 + 0.05200218752839687*rho_A1_2 - 
			    0.007302966674209826*pow(rho_A1_2,2) + 
			    a_3*(4.136880533546651e-19 - 2.309365455120142e-19*rho_A1_2 + 
				 3.317886682533982e-20*pow(rho_A1_2,2)))));
  
  
  return f;
}


Double_t cal_rdst_full(
		      Double_t rho_A1_2, Double_t a_3, Double_t R11, Double_t R21, Double_t mbPmc, Double_t mbMmc,
		      Double_t Re_CS1, Double_t Im_CS1, Double_t Re_CS2, Double_t Im_CS2,
		      Double_t Re_CV1, Double_t Im_CV1, Double_t Re_CV2, Double_t Im_CV2,
		      Double_t Re_CT,  Double_t Im_CT
		      ){
  Double_t hA11 = 0.908;
  TComplex CS1(  Re_CS1, Im_CS1 );
  TComplex CS2(  Re_CS2, Im_CS2 );
  TComplex CV1(  Re_CV1, Im_CV1 );
  TComplex CV2(  Re_CV2, Im_CV2 );
  TComplex CT (  Re_CT,  Im_CT  );

    Double_t f = 
    (0. + (0.0003814229854998974*pow(hA11,2)*
        (200.15571614318196 - 59.04502572984423*rho_A1_2 + 
          4.870911743325851*pow(rho_A1_2,2) + 
          pow(a_3,2)*(0.16216131714996518 - 0.04054426767332307*rho_A1_2 + 
             0.0029390310478812237*pow(rho_A1_2,2)) + 
          a_3*(11.106642782949837 - 3.0183476082225646*rho_A1_2 + 
             0.233693411287558*pow(rho_A1_2,2)) + 
          pow(R21,2)*(40.955261663752275 - 12.1052559135445*rho_A1_2 + 
             1.*pow(rho_A1_2,2)) + 
          R21*(-181.078585088732 + 53.469638106474065*rho_A1_2 - 
             4.414016899669555*pow(rho_A1_2,2) + 
             a_3*(-5.020757230126823 + 1.3658857015288806*rho_A1_2 - 
                0.10583312272059556*pow(rho_A1_2,2))))*
	   pow(TComplex(CS1 - CS2).Rho(),2))/pow(mbPmc,2) + 
     pow(hA11,2)*(pow(mbPmc,2)*
         (7.951832783208808e-7 - 3.04555208567171e-7*rho_A1_2 + 
           3.025163809674795e-8*pow(rho_A1_2,2) + 
           R11*(-0.00006495101236954564 + 0.000023490263105137998*rho_A1_2 - 
              2.2398258866162303e-6*pow(rho_A1_2,2)) + 
           pow(R11,2)*(0.0014626776110531182 - 
              0.00048272573615856963*rho_A1_2 + 
              0.00004339011340339148*pow(rho_A1_2,2))) + 
        pow(mbMmc,2)*(0.025582520170939777 - 
           0.0068952506336765204*rho_A1_2 + 
           0.0005545882513819993*pow(rho_A1_2,2) + 
           a_3*(-0.00029104272223364885 + 0.00008983699796560681*rho_A1_2 - 
              7.675638397805538e-6*pow(rho_A1_2,2)) + 
           pow(R21,2)*(2.925539220531767e-37 - 
              1.0172136376844575e-37*rho_A1_2 + 
              9.394813747412587e-39*pow(rho_A1_2,2)) + 
           pow(a_3,2)*(4.189668310990552e-6 - 1.447598262665198e-6*rho_A1_2 + 
              1.3306537822597635e-7*pow(rho_A1_2,2)) + 
           R21*(-7.650336786695107e-20 + 2.372470109281603e-20*rho_A1_2 - 
              2.033670684581211e-21*pow(rho_A1_2,2) + 
              a_3*(2.2140564565540654e-21 - 7.674190752575326e-22*rho_A1_2 + 
                 7.071049276579794e-23*pow(rho_A1_2,2)))) + 
        mbMmc*mbPmc*(-1.3581280979331775e-18 - 2.5148651157300003e-22*a_3 - 
           6.035731014855145e-19*rho_A1_2 + 1.0438552759073408e-22*a_3*rho_A1_2 - 
           1.2217859042394043e-19*pow(rho_A1_2,2) - 
           1.0937471322717346e-23*a_3*pow(rho_A1_2,2) + 
           R21*(-6.711756728018738e-38 + 2.787633267724401e-38*rho_A1_2 - 
              2.9232723300967506e-39*pow(rho_A1_2,2)) + 
           R11*(-6.54616723150425e-18 - 2.1489301718287723e-17*rho_A1_2 + 
              1.2762461025711224e-18*pow(rho_A1_2,2) + 
              R21*(2.3420112653511584e-36 - 9.818794786987506e-37*rho_A1_2 + 
                 1.0184991149804732e-37*pow(rho_A1_2,2)) + 
              a_3*(8.77100670246e-21 - 3.679294937893606e-21*rho_A1_2 + 
                 3.814215477640381e-22*pow(rho_A1_2,2)))))*pow(CT.Rho(),2)\
      + 0.030254643456755624*pow(hA11,2)*pow(TComplex((TComplex)1 + CV1).Rho(),2) - 
     0.000029428775442260747*pow(hA11,2)*R11*pow(TComplex((TComplex)1 + CV1).Rho(),2) + 
     0.0007343694139646086*pow(hA11,2)*pow(R11,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 0.011072908714145064*pow(hA11,2)*R21*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) + 0.0019220011820663837*pow(hA11,2)*
      pow(R21,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.00029493794054002645*pow(hA11,2)*a_3*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     0.00013349521629621802*pow(hA11,2)*R21*a_3*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     3.887335265869437e-6*pow(hA11,2)*pow(a_3,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     0.008542734639407037*pow(hA11,2)*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     9.911598201286346e-6*pow(hA11,2)*R11*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     0.00022032907826043975*pow(hA11,2)*pow(R11,2)*rho_A1_2*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) + 0.0037396547918801*pow(hA11,2)*R21*rho_A1_2*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 0.0006697488809060423*pow(hA11,2)*
      pow(R21,2)*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     0.0000934263320002305*pow(hA11,2)*a_3*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.00004232437499355708*pow(hA11,2)*R21*a_3*rho_A1_2*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 1.1376776993503411e-6*pow(hA11,2)*
      pow(a_3,2)*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.0007082924178598534*pow(hA11,2)*pow(rho_A1_2,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 8.926704671522045e-7*pow(hA11,2)*R11*
      pow(rho_A1_2,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.000018420800360323613*pow(hA11,2)*pow(R11,2)*pow(rho_A1_2,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 0.0003415435683189837*pow(hA11,2)*R21*
      pow(rho_A1_2,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.00006245643308607658*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) + 8.13860365504776e-6*pow(hA11,2)*a_3*
      pow(rho_A1_2,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     3.689264332183857e-6*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) + 9.332412489660764e-8*pow(hA11,2)*
      pow(a_3,2)*pow(rho_A1_2,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) +
     0.030254643456755624*pow(hA11,2)*pow(CV2.Rho(),2) - 
     0.000029428775442260747*pow(hA11,2)*R11*pow(CV2.Rho(),2) + 
     0.0007343694139646086*pow(hA11,2)*pow(R11,2)*pow(CV2.Rho(),2) - 
     0.011072908714145064*pow(hA11,2)*R21*pow(CV2.Rho(),2) + 
     0.0019220011820663837*pow(hA11,2)*pow(R21,2)*pow(CV2.Rho(),2) + 
     0.00029493794054002645*pow(hA11,2)*a_3*pow(CV2.Rho(),2) - 
     0.00013349521629621802*pow(hA11,2)*R21*a_3*pow(CV2.Rho(),2) + 
     3.887335265869437e-6*pow(hA11,2)*pow(a_3,2)*pow(CV2.Rho(),2) - 
     0.008542734639407037*pow(hA11,2)*rho_A1_2*pow(CV2.Rho(),2) + 
     9.911598201286346e-6*pow(hA11,2)*R11*rho_A1_2*pow(CV2.Rho(),2) - 
     0.00022032907826043975*pow(hA11,2)*pow(R11,2)*rho_A1_2*
      pow(CV2.Rho(),2) + 0.0037396547918801*pow(hA11,2)*R21*rho_A1_2*
      pow(CV2.Rho(),2) - 0.0006697488809060423*pow(hA11,2)*pow(R21,2)*
      rho_A1_2*pow(CV2.Rho(),2) - 
     0.0000934263320002305*pow(hA11,2)*a_3*rho_A1_2*pow(CV2.Rho(),2) + 
     0.00004232437499355708*pow(hA11,2)*R21*a_3*rho_A1_2*pow(CV2.Rho(),2) - 
     1.1376776993503411e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2*
      pow(CV2.Rho(),2) + 0.0007082924178598534*pow(hA11,2)*
      pow(rho_A1_2,2)*pow(CV2.Rho(),2) - 
     8.926704671522045e-7*pow(hA11,2)*R11*pow(rho_A1_2,2)*
      pow(CV2.Rho(),2) + 0.000018420800360323613*pow(hA11,2)*
      pow(R11,2)*pow(rho_A1_2,2)*pow(CV2.Rho(),2) - 
     0.0003415435683189837*pow(hA11,2)*R21*pow(rho_A1_2,2)*
      pow(CV2.Rho(),2) + 0.00006245643308607658*pow(hA11,2)*pow(R21,2)*
      pow(rho_A1_2,2)*pow(CV2.Rho(),2) + 
     8.13860365504776e-6*pow(hA11,2)*a_3*pow(rho_A1_2,2)*
      pow(CV2.Rho(),2) - 3.689264332183857e-6*pow(hA11,2)*R21*a_3*
      pow(rho_A1_2,2)*pow(CV2.Rho(),2) + 
     9.332412489660764e-8*pow(hA11,2)*pow(a_3,2)*pow(rho_A1_2,2)*
      pow(CV2.Rho(),2) + (0.04144330132436068*pow(hA11,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.03751744750983049*pow(hA11,2)*R21*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.008490937717314413*pow(hA11,2)*pow(R21,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.0021789378469524966*pow(hA11,2)*a_3*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.0009855979226152775*pow(hA11,2)*R21*a_3*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.00003030671973485405*pow(hA11,2)*pow(a_3,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.013174986773668847*pow(hA11,2)*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.01193746784975276*pow(hA11,2)*R21*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.002704063504749281*pow(hA11,2)*pow(R21,2)*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.0006402381880497138*pow(hA11,2)*a_3*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.0002898839301224981*pow(hA11,2)*R21*a_3*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (8.201227824109433e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.001150592951757508*pow(hA11,2)*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.001043158289727365*pow(hA11,2)*R21*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.00023643993251746013*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.00005266795972187148*pow(hA11,2)*a_3*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.000023863324110618327*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (6.330191780842525e-7*pow(hA11,2)*pow(a_3,2)*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     0.043439468009419516*pow(hA11,2)*mbMmc*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     9.798284135027003e-7*pow(hA11,2)*mbPmc*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     1.8655855168452323e-19*pow(hA11,2)*mbMmc*R11*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.00008243139537072506*pow(hA11,2)*mbPmc*R11*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     0.0019292013079590545*pow(hA11,2)*mbPmc*pow(R11,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 0.0034193696288309103*pow(hA11,2)*mbMmc*R21*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 3.401673954395168e-21*pow(hA11,2)*mbPmc*R21*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 1.1860839048240666e-19*pow(hA11,2)*mbPmc*
      R11*R21*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     2.7286114008961167e-20*pow(hA11,2)*mbMmc*pow(R21,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 0.00042445809518316664*pow(hA11,2)*mbMmc*a_3*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 3.925810877538916e-38*pow(hA11,2)*mbPmc*a_3*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 1.3687507790235089e-36*pow(hA11,2)*mbPmc*
      R11*a_3*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     0.00010311438255775624*pow(hA11,2)*mbMmc*R21*a_3*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 1.2009435683456312e-21*pow(hA11,2)*mbMmc*
      pow(a_3,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.01161218633941612*pow(hA11,2)*mbMmc*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     3.671921590794541e-7*pow(hA11,2)*mbPmc*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     5.941230378828234e-20*pow(hA11,2)*mbMmc*R11*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 0.000029013422192823387*pow(hA11,2)*mbPmc*
      R11*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.0006143824185095328*pow(hA11,2)*mbPmc*pow(R11,2)*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 0.0010999351744124196*pow(hA11,2)*mbMmc*R21*
      rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     1.4233343671470915e-21*pow(hA11,2)*mbPmc*R21*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 4.972454414285408e-20*pow(hA11,2)*mbPmc*R11*
      R21*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     9.737246894582423e-21*pow(hA11,2)*mbMmc*pow(R21,2)*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 0.00013948436590074546*pow(hA11,2)*mbMmc*a_3*
      rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     1.6415007515343318e-38*pow(hA11,2)*mbPmc*a_3*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 5.739045781158288e-37*pow(hA11,2)*mbPmc*R11*
      a_3*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.000036689865865273666*pow(hA11,2)*mbMmc*R21*a_3*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 4.260582028894552e-22*pow(hA11,2)*mbMmc*
      pow(a_3,2)*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     0.000925606417129734*pow(hA11,2)*mbMmc*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 3.581177810278494e-8*pow(hA11,2)*mbPmc*
      pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     5.194937572194414e-21*pow(hA11,2)*mbMmc*R11*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 2.7059893094927234e-6*pow(hA11,2)*mbPmc*R11*
      pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     0.00005372083063766073*pow(hA11,2)*mbPmc*pow(R11,2)*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 0.00009686213016794422*pow(hA11,2)*mbMmc*
      R21*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     1.5052469308078281e-22*pow(hA11,2)*mbPmc*R21*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 5.195400166308854e-21*pow(hA11,2)*mbPmc*R11*
      R21*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     9.177660983172838e-22*pow(hA11,2)*mbMmc*pow(R21,2)*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 0.000012466760784620066*pow(hA11,2)*mbMmc*
      a_3*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     1.7345605810270768e-39*pow(hA11,2)*mbPmc*a_3*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 5.992292388488751e-38*pow(hA11,2)*mbPmc*R11*
      a_3*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     3.450552924495197e-6*pow(hA11,2)*mbMmc*R21*a_3*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 3.998057390849867e-23*pow(hA11,2)*mbMmc*
      pow(a_3,2)*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.043439468009419516*pow(hA11,2)*mbMmc*TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     9.79828413474989e-7*pow(hA11,2)*mbPmc*TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     1.8655855168452323e-19*pow(hA11,2)*mbMmc*R11*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.00008243139536951311*pow(hA11,2)*mbPmc*R11*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.0019292013079590545*pow(hA11,2)*mbPmc*pow(R11,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.0034193696288309103*pow(hA11,2)*mbMmc*R21*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     3.401673954395168e-21*pow(hA11,2)*mbPmc*R21*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.1860839048240664e-19*pow(hA11,2)*mbPmc*R11*R21*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     2.7286114008961167e-20*pow(hA11,2)*mbMmc*pow(R21,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.00042445809518316664*pow(hA11,2)*mbMmc*a_3*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     3.925810877538916e-38*pow(hA11,2)*mbPmc*a_3*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.3687507790235089e-36*pow(hA11,2)*mbPmc*R11*a_3*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.00010311438255775624*pow(hA11,2)*mbMmc*R21*a_3*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.2009435683456316e-21*pow(hA11,2)*mbMmc*pow(a_3,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.01161218633941612*pow(hA11,2)*mbMmc*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     3.671921590823067e-7*pow(hA11,2)*mbPmc*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     5.941230378828233e-20*pow(hA11,2)*mbMmc*R11*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.000029013422192870672*pow(hA11,2)*mbPmc*R11*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.0006143824185095327*pow(hA11,2)*mbPmc*pow(R11,2)*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.0010999351744124196*pow(hA11,2)*mbMmc*R21*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.4233343671470917e-21*pow(hA11,2)*mbPmc*R21*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     4.972454414285407e-20*pow(hA11,2)*mbPmc*R11*R21*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     9.73724689458242e-21*pow(hA11,2)*mbMmc*pow(R21,2)*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.00013948436590074546*pow(hA11,2)*mbMmc*a_3*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.6415007515343315e-38*pow(hA11,2)*mbPmc*a_3*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     5.739045781158287e-37*pow(hA11,2)*mbPmc*R11*a_3*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.000036689865865273666*pow(hA11,2)*mbMmc*R21*a_3*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     4.260582028894552e-22*pow(hA11,2)*mbMmc*pow(a_3,2)*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.0009256064171297339*pow(hA11,2)*mbMmc*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     3.58117781030956e-8*pow(hA11,2)*mbPmc*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     5.194937572194414e-21*pow(hA11,2)*mbMmc*R11*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     2.705989309492176e-6*pow(hA11,2)*mbPmc*R11*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.000053720830637660746*pow(hA11,2)*mbPmc*pow(R11,2)*
      pow(rho_A1_2,2)*TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.00009686213016794424*pow(hA11,2)*mbMmc*R21*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     1.5052469308078281e-22*pow(hA11,2)*mbPmc*R21*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     5.195400166308854e-21*pow(hA11,2)*mbPmc*R11*R21*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     9.177660983172838e-22*pow(hA11,2)*mbMmc*pow(R21,2)*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.000012466760784620066*pow(hA11,2)*mbMmc*a_3*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     1.7345605810270768e-39*pow(hA11,2)*mbPmc*a_3*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     5.992292388488751e-38*pow(hA11,2)*mbPmc*R11*a_3*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     3.450552924495197e-6*pow(hA11,2)*mbMmc*R21*a_3*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     3.998057390849867e-23*pow(hA11,2)*mbMmc*pow(a_3,2)*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.06050795291702513*pow(hA11,2)*TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.000058857550884521494*pow(hA11,2)*R11*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.0014687388279292172*pow(hA11,2)*pow(R11,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.022145817428290124*pow(hA11,2)*R21*TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0038440023641327674*pow(hA11,2)*pow(R21,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0005898758810800529*pow(hA11,2)*a_3*TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.00026699043259243604*pow(hA11,2)*R21*a_3*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     7.774670531738875e-6*pow(hA11,2)*pow(a_3,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.017084986257558863*pow(hA11,2)*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.000019823196402572692*pow(hA11,2)*R11*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0004406581565208795*pow(hA11,2)*pow(R11,2)*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0074793095837602*pow(hA11,2)*R21*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.0013394977618120844*pow(hA11,2)*pow(R21,2)*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.000186852664000461*pow(hA11,2)*a_3*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.00008464874998711415*pow(hA11,2)*R21*a_3*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     2.2753553987006822e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0014165390405698939*pow(hA11,2)*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     1.785340934304409e-6*pow(hA11,2)*R11*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.000036841600720647225*pow(hA11,2)*pow(R11,2)*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.0006830871366379674*pow(hA11,2)*R21*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.00012491286617215315*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.00001627720731009552*pow(hA11,2)*a_3*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     7.378528664367714e-6*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     1.8664824979321527e-7*pow(hA11,2)*pow(a_3,2)*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re())/
   (0. + pow(hA11,2)*(0.17957389170325488 - 1.0948037887075082e-18*a_3 + 
        2.3379438621231702e-36*pow(a_3,2) - 0.08378631617748233*rho_A1_2 + 
        5.874693941030267e-19*a_3*rho_A1_2 - 
        1.301922254855869e-36*pow(a_3,2)*rho_A1_2 + 
        0.01088597422339019*pow(rho_A1_2,2) - 
        8.230978688193583e-20*a_3*pow(rho_A1_2,2) + 
        1.8671634465810482e-37*pow(a_3,2)*pow(rho_A1_2,2) + 
        R11*(-0.00026130896343670175 + 0.00012355740482715148*rho_A1_2 - 
           0.000015436303110645208*pow(rho_A1_2,2)) + 
        pow(R11,2)*(0.004402759842982002 - 0.0018896455785886214*rho_A1_2 + 
           0.00022186379848383934*pow(rho_A1_2,2)) + 
        pow(R21,2)*(0.018303717615447346 - 0.010242486422778429*rho_A1_2 + 
           0.0014741148938045372*pow(rho_A1_2,2)) + 
        R21*(-0.09657467358167796 + 0.05200218752839687*rho_A1_2 - 
           0.007302966674209826*pow(rho_A1_2,2) + 
           a_3*(4.136880533546651e-19 - 2.309365455120142e-19*rho_A1_2 + 
	   3.317886682533982e-20*pow(rho_A1_2,2)))))
	     ;
  return f;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace LQ{
  //const Int_t    np   =    60; // # of scan point
  const Int_t    np   =   600; // # of scan point
  const Double_t xmin = -0.20;
  const Double_t xmax =  0.40;
  const Int_t    nt   =   500; // # of random number for error band
}

TGraphErrors* makeRdstr_LQ(
			   Double_t rho_A1_2, Double_t a_3, Double_t R11, Double_t R21, Double_t mbPmc, Double_t mbMmc,
			   Double_t factor_Re_CS1, Double_t factor_Im_CS1, Double_t factor_Re_CS2, Double_t factor_Im_CS2,
			   Double_t factor_Re_CV1, Double_t factor_Im_CV1, Double_t factor_Re_CV2, Double_t factor_Im_CV2,
			   Double_t factor_Re_CT,  Double_t factor_Im_CT
){
  TGraphErrors* g = new TGraphErrors();
  for( Int_t ip=0; ip<LQ::np+1; ip++ ){
    Double_t x = LQ::xmin + ip*(LQ::xmax-LQ::xmin)/(Double_t)LQ::np;
    Double_t f = cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc,
				x*factor_Re_CS1, x*factor_Im_CS1, x*factor_Re_CS2, x*factor_Im_CS2,
				x*factor_Re_CV1, x*factor_Im_CV1, x*factor_Re_CV2, x*factor_Im_CV2,
				x*factor_Re_CT,  x*factor_Im_CT
				);
    g->SetPoint( g->GetN(), x, f );
    //std::cout << x << " : " << f << std::endl;
  }
  g->SetTitle( Form("CS1(%.2f,%.2f) CS2(%.2f,%.2f) CV1(%.2f,%.2f) CV2(%.2f,%.2f) CT(%.2f,%.2f)",
		    factor_Re_CS1, factor_Im_CS1,
		    factor_Re_CS2, factor_Im_CS2,
		    factor_Re_CV1, factor_Im_CV1,
		    factor_Re_CV2, factor_Im_CV2,
		    factor_Re_CT,  factor_Im_CT
		    )
	       );
  g->GetXaxis()->SetTitle("Parameter");
  g->GetYaxis()->SetTitle("R(D*)");
  return g;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TGraphErrors* makeRdstr_LQ(
			   Double_t rho_A1_2,   Double_t a_3,   Double_t R11,   Double_t R21,   Double_t mbPmc,   Double_t mbMmc,
			   Double_t rho_A1_2_E, Double_t a_3_E, Double_t R11_E, Double_t R21_E, Double_t mbPmc_E, Double_t mbMmc_E,
			   Double_t factor_Re_CS1, Double_t factor_Im_CS1, Double_t factor_Re_CS2, Double_t factor_Im_CS2,
			   Double_t factor_Re_CV1, Double_t factor_Im_CV1, Double_t factor_Re_CV2, Double_t factor_Im_CV2,
			   Double_t factor_Re_CT,  Double_t factor_Im_CT
			   ){
  TGraphErrors* g = new TGraphErrors();
  TCanvas* tmpcan = Canvas( "tmpcan", "tmpcan" );
  tmpcan->Draw();
  for( Int_t ip=0; ip<LQ::np+1; ip++ ){
    Double_t x = LQ::xmin + ip*(LQ::xmax-LQ::xmin)/(Double_t)LQ::np;
    Double_t f = cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc,
				x*factor_Re_CS1, x*factor_Im_CS1, x*factor_Re_CS2, x*factor_Im_CS2,
				x*factor_Re_CV1, x*factor_Im_CV1, x*factor_Re_CV2, x*factor_Im_CV2,
				x*factor_Re_CT,  x*factor_Im_CT
				);
    TH1D* tmphist = new TH1D("tmphist","tmphist", 100, 0, 0 );
    for( Int_t it=0; it<LQ::nt; it++ ){
      Double_t tmp_rho_A1_2 = rho_A1_2 + gRandom->Gaus( 0.0, rho_A1_2_E );
      //Double_t tmp_a_3      = a_3      + gRandom->Gaus( 0.0, a_3_E      );
      Double_t tmp_a_3      = a_3      + gRandom->Uniform( -a_3_E, a_3_E );
      Double_t tmp_R11      = R11      + gRandom->Gaus( 0.0, R11_E      );
      Double_t tmp_R21      = R21      + gRandom->Gaus( 0.0, R21_E      );
      Double_t tmp_mbPmc    = mbPmc    + gRandom->Gaus( 0.0, mbPmc_E    );
      Double_t tmp_mbMmc    = mbMmc    + gRandom->Gaus( 0.0, mbMmc_E    );
      Double_t tmpf = cal_rdst_full( tmp_rho_A1_2, tmp_a_3, tmp_R11, tmp_R21, tmp_mbPmc, tmp_mbMmc,
				     x*factor_Re_CS1, x*factor_Im_CS1, x*factor_Re_CS2, x*factor_Im_CS2,
				     x*factor_Re_CV1, x*factor_Im_CV1, x*factor_Re_CV2, x*factor_Im_CV2,
				     x*factor_Re_CT,  x*factor_Im_CT
				     );
      tmphist->Fill( tmpf );
    }
    tmphist->Fit("gaus","Q");
    Double_t err = tmphist->GetFunction("gaus")->GetParameter(2);
    g->SetPoint     ( g->GetN(),     x, f   );
    g->SetPointError( g->GetN()-1, 0.0, err );

    //std::cout << std::setw(10) << std::right << x   << " : "
    //<< std::setw(10) << std::right << f   << " +- "
    //<< std::setw(10) << std::right << err << std::endl;

    /* for just checking
    if( ip==0 || ip==LQ::nt-1 ){
      tmphist->DrawCopy();
      tmpcan->Update();
      tmpcan->WaitPrimitive();
    }
    */
    
    delete tmphist;
  }
  g->SetTitle( Form("CS1(%.2f,%.2f) CS2(%.2f,%.2f) CV1(%.2f,%.2f) CV2(%.2f,%.2f) CT(%.2f,%.2f)",
		    factor_Re_CS1, factor_Im_CS1,
		    factor_Re_CS2, factor_Im_CS2,
		    factor_Re_CV1, factor_Im_CV1,
		    factor_Re_CV2, factor_Im_CV2,
		    factor_Re_CT,  factor_Im_CT
		    )
	       );
  g->GetXaxis()->SetTitle("Parameter");
  g->GetYaxis()->SetTitle("R(D*)");

  delete tmpcan;

  return g;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace OP{
  const Int_t    np   =    60; // # of scan point
  //const Double_t xmin = -0.20;
  //const Double_t xmax =  0.40;
  const Int_t    nt   =   500; // # of random number for error band
}

TGraphErrors* makeRdstr_OP(
			   Double_t rho_A1_2, Double_t a_3, Double_t R11, Double_t R21, Double_t mbPmc, Double_t mbMmc,
			   Double_t factor_Re_CS1, Double_t factor_Im_CS1, Double_t factor_Re_CS2, Double_t factor_Im_CS2,
			   Double_t factor_Re_CV1, Double_t factor_Im_CV1, Double_t factor_Re_CV2, Double_t factor_Im_CV2,
			   Double_t factor_Re_CT,  Double_t factor_Im_CT,
			   Double_t xmin, Double_t xmax
){
  TGraphErrors* g = new TGraphErrors();
  for( Int_t ip=0; ip<LQ::np+1; ip++ ){
    Double_t x = xmin + ip*(xmax-xmin)/(Double_t)LQ::np;
    Double_t f = cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc,
				x*factor_Re_CS1, x*factor_Im_CS1, x*factor_Re_CS2, x*factor_Im_CS2,
				x*factor_Re_CV1, x*factor_Im_CV1, x*factor_Re_CV2, x*factor_Im_CV2,
				x*factor_Re_CT,  x*factor_Im_CT
				);
    g->SetPoint( g->GetN(), x, f );
    //std::cout << x << " : " << f << std::endl;
  }
  g->SetTitle( Form("CS1(%.2f,%.2f) CS2(%.2f,%.2f) CV1(%.2f,%.2f) CV2(%.2f,%.2f) CT(%.2f,%.2f)",
		    factor_Re_CS1, factor_Im_CS1,
		    factor_Re_CS2, factor_Im_CS2,
		    factor_Re_CV1, factor_Im_CV1,
		    factor_Re_CV2, factor_Im_CV2,
		    factor_Re_CT,  factor_Im_CT
		    )
	       );
  g->GetXaxis()->SetTitle("Parameter");
  g->GetYaxis()->SetTitle("R(D*)");
  return g;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

TGraphErrors* makeRdstr_OP(
			   Double_t rho_A1_2,   Double_t a_3,   Double_t R11,   Double_t R21,   Double_t mbPmc,   Double_t mbMmc,
			   Double_t rho_A1_2_E, Double_t a_3_E, Double_t R11_E, Double_t R21_E, Double_t mbPmc_E, Double_t mbMmc_E,
			   Double_t factor_Re_CS1, Double_t factor_Im_CS1, Double_t factor_Re_CS2, Double_t factor_Im_CS2,
			   Double_t factor_Re_CV1, Double_t factor_Im_CV1, Double_t factor_Re_CV2, Double_t factor_Im_CV2,
			   Double_t factor_Re_CT,  Double_t factor_Im_CT,
			   Double_t xmin, Double_t xmax
			   ){
  TGraphErrors* g = new TGraphErrors();
  TCanvas* tmpcan = Canvas( "tmpcan", "tmpcan" );
  tmpcan->Draw();
  for( Int_t ip=0; ip<LQ::np+1; ip++ ){
    Double_t x = xmin + ip*(xmax-xmin)/(Double_t)LQ::np;
    Double_t f = cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc,
				x*factor_Re_CS1, x*factor_Im_CS1, x*factor_Re_CS2, x*factor_Im_CS2,
				x*factor_Re_CV1, x*factor_Im_CV1, x*factor_Re_CV2, x*factor_Im_CV2,
				x*factor_Re_CT,  x*factor_Im_CT
				);
    TH1D* tmphist = new TH1D("tmphist","tmphist", 100, 0, 0 );
    for( Int_t it=0; it<LQ::nt; it++ ){
      Double_t tmp_rho_A1_2 = rho_A1_2 + gRandom->Gaus( 0.0, rho_A1_2_E );
      //Double_t tmp_a_3      = a_3      + gRandom->Gaus( 0.0, a_3_E      );
      Double_t tmp_a_3      = a_3      + gRandom->Uniform( -a_3_E, a_3_E );
      Double_t tmp_R11      = R11      + gRandom->Gaus( 0.0, R11_E      );
      Double_t tmp_R21      = R21      + gRandom->Gaus( 0.0, R21_E      );
      Double_t tmp_mbPmc    = mbPmc    + gRandom->Gaus( 0.0, mbPmc_E    );
      Double_t tmp_mbMmc    = mbMmc    + gRandom->Gaus( 0.0, mbMmc_E    );
      Double_t tmpf = cal_rdst_full( tmp_rho_A1_2, tmp_a_3, tmp_R11, tmp_R21, tmp_mbPmc, tmp_mbMmc,
				     x*factor_Re_CS1, x*factor_Im_CS1, x*factor_Re_CS2, x*factor_Im_CS2,
				     x*factor_Re_CV1, x*factor_Im_CV1, x*factor_Re_CV2, x*factor_Im_CV2,
				     x*factor_Re_CT,  x*factor_Im_CT
				     );
      tmphist->Fill( tmpf );
    }
    tmphist->Fit("gaus","Q");
    Double_t err = tmphist->GetFunction("gaus")->GetParameter(2);
    g->SetPoint     ( g->GetN(),     x, f   );
    g->SetPointError( g->GetN()-1, 0.0, err );

    //std::cout << std::setw(10) << std::right << x   << " : "
    //<< std::setw(10) << std::right << f   << " +- "
    //<< std::setw(10) << std::right << err << std::endl;

    /* for just checking
    if( ip==0 || ip==LQ::nt-1 ){
      tmphist->DrawCopy();
      tmpcan->Update();
      tmpcan->WaitPrimitive();
    }
    */
    
    delete tmphist;
  }
  g->SetTitle( Form("CS1(%.2f,%.2f) CS2(%.2f,%.2f) CV1(%.2f,%.2f) CV2(%.2f,%.2f) CT(%.2f,%.2f)",
		    factor_Re_CS1, factor_Im_CS1,
		    factor_Re_CS2, factor_Im_CS2,
		    factor_Re_CV1, factor_Im_CV1,
		    factor_Re_CV2, factor_Im_CV2,
		    factor_Re_CT,  factor_Im_CT
		    )
	       );
  g->GetXaxis()->SetTitle("Parameter");
  g->GetYaxis()->SetTitle("R(D*)");

  delete tmpcan;

  return g;
}

#endif
