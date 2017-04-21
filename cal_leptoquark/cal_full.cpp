#include "draws_.h"
#include "draws_leptoquark.h"

Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  /*
  if( !(app.Argc()==11) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (double)|CS1| (double)arg(CS1) "
	      << " (double)|CS2| (double)arg(CS2) "
	      << " (double)|CV1| (double)arg(CV1) "
	      << " (double)|CV2| (double)arg(CV2) "
	      << " (double)|CT | (double)arg(CT ) "
	      << std::endl, abort();
  Double_t mag_CS1 = atof(app.Argv( 1));
  Double_t arg_CS1 = atof(app.Argv( 2));
  Double_t mag_CS2 = atof(app.Argv( 3));
  Double_t arg_CS2 = atof(app.Argv( 4));
  Double_t mag_CV1 = atof(app.Argv( 5));
  Double_t arg_CV1 = atof(app.Argv( 6));
  Double_t mag_CV2 = atof(app.Argv( 7));
  Double_t arg_CV2 = atof(app.Argv( 8));
  Double_t mag_CT  = atof(app.Argv( 9));
  Double_t arg_CT  = atof(app.Argv(10));
  TComplex CS1(  mag_CS1*cos(arg_CS1), mag_CS1*sin(arg_CS1) );
  TComplex CS2(  mag_CS2*cos(arg_CS2), mag_CS2*sin(arg_CS2) );
  TComplex CV1(  mag_CV1*cos(arg_CV1), mag_CV1*sin(arg_CV1) );
  TComplex CV2(  mag_CV2*cos(arg_CV2), mag_CV2*sin(arg_CV2) );
  TComplex CT (  mag_CT *cos(arg_CT ), mag_CT *sin(arg_CT ) );
  */
  if( !(app.Argc()==5 || app.Argc()==11) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (double)Re(CS1) (double)Im(CS1) "
	      << " (double)Re(CS2) (double)Im(CS2) "
	      << " (double)Re(CV1) (double)Im(CV1) "
	      << " (double)Re(CV2) (double)Im(CV2) "
	      << " (double)Re(CT ) (double)Im(CT ) "
	      << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (double)Re(CS2) (double)Im(CS2) "
	      << " (double)Re(CT ) (double)Im(CT ) "
	      << std::endl
	      << "          (R2 LQ : C_S2 = +7.8 * C_T)" << std::endl
	      << "          (S1 LQ : C_S2 = -7.8 * C_T)" << std::endl, abort();

  Double_t Re_CS1 = 0.0;
  Double_t Im_CS1 = 0.0;
  Double_t Re_CS2 = 0.0;
  Double_t Im_CS2 = 0.0;
  Double_t Re_CV1 = 0.0;
  Double_t Im_CV1 = 0.0;
  Double_t Re_CV2 = 0.0;
  Double_t Im_CV2 = 0.0;
  Double_t Re_CT  = 0.0;
  Double_t Im_CT  = 0.0;
  if( app.Argc()==5 ){
    Re_CS2 = atof(app.Argv(1));
    Im_CS2 = atof(app.Argv(2));
    Re_CT  = atof(app.Argv(3));
    Im_CT  = atof(app.Argv(4));
  }else if( app.Argc()==11 ){
    Re_CS1 = atof(app.Argv( 1));
    Im_CS1 = atof(app.Argv( 2));
    Re_CS2 = atof(app.Argv( 3));
    Im_CS2 = atof(app.Argv( 4));
    Re_CV1 = atof(app.Argv( 5));
    Im_CV1 = atof(app.Argv( 6));
    Re_CV2 = atof(app.Argv( 7));
    Im_CV2 = atof(app.Argv( 8));
    Re_CT  = atof(app.Argv( 9));
    Im_CT  = atof(app.Argv(10));
  }
  
  TComplex CS1(  Re_CS1, Im_CS1 );
  TComplex CS2(  Re_CS2, Im_CS2 );
  TComplex CV1(  Re_CV1, Im_CV1 );
  TComplex CV2(  Re_CV2, Im_CV2 );
  TComplex CT (  Re_CT,  Im_CT  );

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

  Double_t f = cal_rdst_full( rho_A1_2, a_3, R11, R21, mbPmc, mbMmc,
			      Re_CS1, Im_CS1, Re_CS2, Im_CS2,
			      Re_CV1, Im_CV1, Re_CV2, Im_CV2,
			      Re_CT,  Im_CT
			      );
  std::cout << " --> R(D*) = " << f << std::endl;
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

 return 0;
}
