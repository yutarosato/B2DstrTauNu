#include "draws_.h"
#include "draws_leptoquark.h"

Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  /*
  if( !(app.Argc()==3) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (double)|CS2| (double)arg(CS2) "
	      << std::endl, abort();
  Double_t mag_CS2 = atof(app.Argv(1));
  Double_t arg_CS2 = atof(app.Argv(2));
  TComplex CS2(  mag_CS2*cos(arg_CS2), mag_CS2*sin(arg_CS2) );
  */
  ///*
  if( !(app.Argc()==3) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (double)Re(CS2) (double)Im(CS2) "
	      << std::endl, abort();
  Double_t Re_CS2 = atof(app.Argv(1));
  Double_t Im_CS2 = atof(app.Argv(2));
  TComplex CS2(  Re_CS2, Im_CS2 );
  //*/
  ///*
  std::cout << "Re   = " << CS2.Re()    << std::endl
	    << "Im   = " << CS2.Im()    << std::endl
	    << "mag  = " << CS2.Rho()   << std::endl
	    << "mag2 = " << CS2.Rho2()  << std::endl
	    << "arg  = " << CS2.Theta() << std::endl
    ;
  //*/

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // form factor parameters
  const Int_t npar_ff = 6;
  Double_t FF  [npar_ff] = { 1.207,    1.0, 1.403, 0.854,   6.2, 3.45 };
  Double_t FF_E[npar_ff] = { 0.026,    1.0, 0.033, 0.020,   0.4, 0.05 };
  
  Double_t rho_A1_2 = FF[0]; Double_t rho_A1_2_E = FF_E[0];
  Double_t a_3      = FF[1]; Double_t a_3_E      = FF_E[1];
  Double_t R11      = FF[2]; Double_t R11_E      = FF_E[2];
  Double_t R21      = FF[3]; Double_t R21_E      = FF_E[3];
  Double_t mbPmc    = FF[4]; Double_t mbPmc_E    = FF_E[4];
  Double_t mbMmc    = FF[5]; Double_t mbMmc_E    = FF_E[5];

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  Double_t f = cal_rdst_cs2( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc, Re_CS2, Im_CS2 );
  std::cout << " --> R(D*) = " << f << std::endl;
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}



		
