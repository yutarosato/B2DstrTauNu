#ifndef MAKECUT_H
#define MAKECUT_H

#include "const.h"

std::string makeCut_dmass ( Double_t D_L=0.015,  Double_t D_H=0.015,  Double_t D_L_pi0=0.036,  Double_t D_H_pi0=0.036  );
std::string makeCut_dmass ( Double_t D0_L,  Double_t D0_H,  Double_t D0_L_pi0,  Double_t D0_H_pi0,
			    Double_t Dp_L,  Double_t Dp_H,  Double_t Dp_L_pi0,  Double_t Dp_H_pi0  );
std::string makeCut_deltam( Double_t D_L=0.0025, Double_t D_H=0.0025, Double_t D_L_pi0=0.0025, Double_t D_H_pi0=0.0025 );

std::string makeCut_dmass_single ( Double_t D_L=0.015,  Double_t D_H=0.015,  Double_t D_L_pi0=0.036,  Double_t D_H_pi0=0.036  );
std::string makeCut_dmass_single ( Double_t D0_L,  Double_t D0_H,  Double_t D0_L_pi0,  Double_t D0_H_pi0,
				   Double_t Dp_L,  Double_t Dp_H,  Double_t Dp_L_pi0,  Double_t Dp_H_pi0 );
std::string makeCut_deltam_single( Double_t D_L=0.0025, Double_t D_H=0.0025, Double_t D_L_pi0=0.0025, Double_t D_H_pi0=0.0025 );

std::string makeCut_rem( const Bool_t fl_trk=1, const Bool_t fl_pi0=1, const Bool_t fl_ks=1 );
std::string makeCut_pi0cos();
std::string makeCut_remain( const Char_t* ctgry[], const Int_t nctgry );

std::string makeCut_pi0mass            ( Double_t D_L=0.010,  Double_t D_H=0.010  );
std::string makeCut_pi0mass_d          ( Double_t D_L=0.010,  Double_t D_H=0.010  ); // for pi0 from D  decay
std::string makeCut_pi0mass_dstr       ( Double_t D_L=0.010,  Double_t D_H=0.010  ); // for pi0 from D* decay (slow pi0)

std::string makeCut_pi0mass_single     ( Double_t D_L=0.010,  Double_t D_H=0.010  );
std::string makeCut_pi0mass_d_single   ( Double_t D_L=0.010,  Double_t D_H=0.010  ); // for pi0 from D  decay
std::string makeCut_pi0mass_dstr_single( Double_t D_L=0.010,  Double_t D_H=0.010  ); // for pi0 from D* decay (slow pi0)

Double_t nominal_dmass    ( Int_t decay );
Double_t nominal_eff_dmass( Int_t decay );

#endif
