#include "makeCut.h"

std::string makeCut_dmass( Double_t D_L, Double_t D_H, Double_t D_L_pi0, Double_t D_H_pi0 ){
  
  std::stringstream sTmp;
  sTmp << "( "
       << Form( "(abs(rm_d1lun)==421 && rm_d1<999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::d0, D_L,     PDGmass::d0, D_H     ) << " || " // d0
       << Form( "(abs(rm_d1lun)==421 && rm_d1>999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::d0, D_L_pi0, PDGmass::d0, D_H_pi0 ) << " || " // d0 with pi0
       << Form( "(abs(rm_d1lun)==411 && rm_d1<999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::dp, D_L,     PDGmass::dp, D_H     ) << " || " // d+
       << Form( "(abs(rm_d1lun)==411 && rm_d1>999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::dp, D_L_pi0, PDGmass::dp, D_H_pi0 )           // d+ with pi0
       << " ) && ( "
       << Form( "(abs(rm_d2lun)==421 && rm_d2<999 && %f-%f<d2_m&&d2_m<%f+%f)", PDGmass::d0, D_L,     PDGmass::d0, D_H     ) << " || " // d0
       << Form( "(abs(rm_d2lun)==421 && rm_d2>999 && %f-%f<d2_m&&d2_m<%f+%f)", PDGmass::d0, D_L_pi0, PDGmass::d0, D_H_pi0 ) << " || " // d0 with pi0
       << Form( "(abs(rm_d2lun)==411 && rm_d2<999 && %f-%f<d2_m&&d2_m<%f+%f)", PDGmass::dp, D_L,     PDGmass::dp, D_H     ) << " || " // d+
       << Form( "(abs(rm_d2lun)==411 && rm_d2>999 && %f-%f<d2_m&&d2_m<%f+%f)", PDGmass::dp, D_L_pi0, PDGmass::dp, D_H_pi0 )           // d+ with pi0
       << " )";
    return sTmp.str();
}

std::string makeCut_dmass ( Double_t D0_L,  Double_t D0_H,  Double_t D0_L_pi0,  Double_t D0_H_pi0,
			    Double_t Dp_L,  Double_t Dp_H,  Double_t Dp_L_pi0,  Double_t Dp_H_pi0 ){
  
  std::stringstream sTmp;
  sTmp << "( "
       << Form( "(abs(rm_d1lun)==421 && rm_d1<999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::d0, D0_L,     PDGmass::d0, D0_H     ) << " || " // d0
       << Form( "(abs(rm_d1lun)==421 && rm_d1>999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::d0, D0_L_pi0, PDGmass::d0, D0_H_pi0 ) << " || " // d0 with pi0
       << Form( "(abs(rm_d1lun)==411 && rm_d1<999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::dp, Dp_L,     PDGmass::dp, Dp_H     ) << " || " // d+
       << Form( "(abs(rm_d1lun)==411 && rm_d1>999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::dp, Dp_L_pi0, PDGmass::dp, Dp_H_pi0 )           // d+ with pi0
       << " ) && ( "
       << Form( "(abs(rm_d2lun)==421 && rm_d2<999 && %f-%f<d2_m&&d2_m<%f+%f)", PDGmass::d0, D0_L,     PDGmass::d0, D0_H     ) << " || " // d0
       << Form( "(abs(rm_d2lun)==421 && rm_d2>999 && %f-%f<d2_m&&d2_m<%f+%f)", PDGmass::d0, D0_L_pi0, PDGmass::d0, D0_H_pi0 ) << " || " // d0 with pi0
       << Form( "(abs(rm_d2lun)==411 && rm_d2<999 && %f-%f<d2_m&&d2_m<%f+%f)", PDGmass::dp, Dp_L,     PDGmass::dp, Dp_H     ) << " || " // d+
       << Form( "(abs(rm_d2lun)==411 && rm_d2>999 && %f-%f<d2_m&&d2_m<%f+%f)", PDGmass::dp, Dp_L_pi0, PDGmass::dp, Dp_H_pi0 )           // d+ with pi0
       << " )";
    return sTmp.str();
}

std::string makeCut_deltam( Double_t D_L, Double_t D_H, Double_t D_L_pi0, Double_t D_H_pi0 ){
  const Double_t pdg_dm_d0 = PDGmass::dstrp - PDGmass::d0; // ~145.421 MeV
  const Double_t pdg_dm_dp = PDGmass::dstrp - PDGmass::dp; // ~140.66  MeV
  std::stringstream sTmp;
  
  //sTmp << "dm1<0.155 && dm2<0.155";
  //sTmp << "dm1<0.148 && dm2<0.148";
  sTmp << "( "
       << Form( "(abs(rm_dst1l)==413 && abs(rm_dst1)==211 && %f-%f<dm1&&dm1<%f+%f)", pdg_dm_d0, D_L,     pdg_dm_d0, D_H     ) << " || " // D*+ -> D0 pi+
       << Form( "(abs(rm_dst1l)==413 && abs(rm_dst1)==111 && %f-%f<dm1&&dm1<%f+%f)", pdg_dm_dp, D_L_pi0, pdg_dm_dp, D_H_pi0 )           // D*+ -> D+ pi0
       << " ) && ( "
       << Form( "(abs(rm_dst2l)==413 && abs(rm_dst2)==211 && %f-%f<dm2&&dm2<%f+%f)", pdg_dm_d0, D_L,     pdg_dm_d0, D_H     ) << " || " // D*+ -> D0 pi+
       << Form( "(abs(rm_dst2l)==413 && abs(rm_dst2)==111 && %f-%f<dm2&&dm2<%f+%f)", pdg_dm_dp, D_L_pi0, pdg_dm_dp, D_H_pi0 )           // D*+ -> D+ pi0
       << " )";
  return sTmp.str();
}

std::string makeCut_dmass_single( Double_t D_L, Double_t D_H, Double_t D_L_pi0, Double_t D_H_pi0 ){
  
  std::stringstream sTmp;
  sTmp << "( "
       << Form( "(abs(rm_d1lun)==421 && rm_d1<999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::d0, D_L,     PDGmass::d0, D_H     ) << " || " // d0
       << Form( "(abs(rm_d1lun)==421 && rm_d1>999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::d0, D_L_pi0, PDGmass::d0, D_H_pi0 ) << " || " // d0 with pi0
       << Form( "(abs(rm_d1lun)==411 && rm_d1<999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::dp, D_L,     PDGmass::dp, D_H     ) << " || " // d+
       << Form( "(abs(rm_d1lun)==411 && rm_d1>999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::dp, D_L_pi0, PDGmass::dp, D_H_pi0 )           // d+ with pi0
       << " )";
  return sTmp.str();
}

std::string makeCut_dmass_single ( Double_t D0_L,  Double_t D0_H,  Double_t D0_L_pi0,  Double_t D0_H_pi0,
				   Double_t Dp_L,  Double_t Dp_H,  Double_t Dp_L_pi0,  Double_t Dp_H_pi0 ){
  std::stringstream sTmp;
  sTmp << "( "
       << Form( "(abs(rm_d1lun)==421 && rm_d1<999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::d0, D0_L,     PDGmass::d0, D0_H     ) << " || " // d0
       << Form( "(abs(rm_d1lun)==421 && rm_d1>999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::d0, D0_L_pi0, PDGmass::d0, D0_H_pi0 ) << " || " // d0 with pi0
       << Form( "(abs(rm_d1lun)==411 && rm_d1<999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::dp, Dp_L,     PDGmass::dp, Dp_H     ) << " || " // d+
       << Form( "(abs(rm_d1lun)==411 && rm_d1>999 && %f-%f<d1_m&&d1_m<%f+%f)", PDGmass::dp, Dp_L_pi0, PDGmass::dp, Dp_H_pi0 )           // d+ with pi0
       << " )";
  return sTmp.str();
}

std::string makeCut_deltam_single( Double_t D_L, Double_t D_H, Double_t D_L_pi0, Double_t D_H_pi0 ){
  const Double_t pdg_dm_d0 = PDGmass::dstrp - PDGmass::d0; // ~145.421 MeV
  const Double_t pdg_dm_dp = PDGmass::dstrp - PDGmass::dp; // ~140.66  MeV
  std::stringstream sTmp;
  
  sTmp << "( "
       << Form( "(abs(rm_dst1l)==413 && abs(rm_dst1)==211 && %f-%f<dm1&&dm1<%f+%f)", pdg_dm_d0, D_L,     pdg_dm_d0, D_H     ) << " || " // D*+ -> D0 pi+
       << Form( "(abs(rm_dst1l)==413 && abs(rm_dst1)==111 && %f-%f<dm1&&dm1<%f+%f)", pdg_dm_dp, D_L_pi0, pdg_dm_dp, D_H_pi0 )           // D*+ -> D+ pi0
       << " )";
  return sTmp.str();
}

std::string makeCut_rem( const Bool_t fl_trk, const Bool_t fl_pi0, const Bool_t fl_ks ){
  std::stringstream sTmp;
  sTmp << "1";
  if( fl_trk ) sTmp << "&& remtrk==0"; 
  //if( fl_pi0 ) sTmp << "&& rempi0==0"; 
  if( fl_pi0 ) sTmp << "&& rempi0_1==0"; // modified @20141127
  if( fl_ks  ) sTmp << "&& remks==0"; 
  return sTmp.str();
}

std::string makeCut_pi0cos(){
  std::stringstream sTmp;
  sTmp << "d1_pi0co>0.40 && d2_pi0co>0.40";
  return sTmp.str();
}

std::string makeCut_remain( const Char_t* ctgry[], const Int_t nctgry ){
  std::stringstream sTmp;
  sTmp << "( ";
  for( Int_t i=0; i<nctgry; i++ ){
    sTmp << "!(" << ctgry[i] << ")";
    if( i!=nctgry-1 ) sTmp << " && ";
  }
  sTmp << " )";
  return sTmp.str();
}

std::string makeCut_pi0mass( Double_t D_L,  Double_t D_H ){

  std::stringstream sTmp;
  sTmp << "( "
       << Form( "( (%f-%f<acc1m && acc1m<%f+%f) || acc1m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H ) << " && "
       << Form( "( (%f-%f<acc2m && acc2m<%f+%f) || acc2m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H ) << " && "
       << Form( "( (%f-%f<pi01m && pi01m<%f+%f) || pi01m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H ) << " && "
       << Form( "( (%f-%f<pi02m && pi02m<%f+%f) || pi02m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H )
       << " )";
    return sTmp.str();

}

std::string makeCut_pi0mass_d( Double_t D_L,  Double_t D_H ){

  std::stringstream sTmp;
  sTmp << "( "
       << Form( "( (%f-%f<pi01m && pi01m<%f+%f) || pi01m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H ) << " && "
       << Form( "( (%f-%f<pi02m && pi02m<%f+%f) || pi02m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H )
       << " )";
    return sTmp.str();

}

std::string makeCut_pi0mass_dstr( Double_t D_L,  Double_t D_H ){

  std::stringstream sTmp;
  sTmp << "( "
       << Form( "( (%f-%f<acc1m && acc1m<%f+%f) || acc1m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H ) << " && "
       << Form( "( (%f-%f<acc2m && acc2m<%f+%f) || acc2m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H )
       << " )";
    return sTmp.str();

}

std::string makeCut_pi0mass_single( Double_t D_L,  Double_t D_H ){

  std::stringstream sTmp;
  sTmp << "( "
       << Form( "( (%f-%f<acc1m && acc1m<%f+%f) || acc1m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H ) << " && "
       << Form( "( (%f-%f<pi01m && pi01m<%f+%f) || pi01m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H )
       << " )";
    return sTmp.str();
}

std::string makeCut_pi0mass_d_single( Double_t D_L,  Double_t D_H ){

  std::stringstream sTmp;
  sTmp << Form( "( (%f-%f<pi01m && pi01m<%f+%f) || pi01m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H );
    return sTmp.str();
}

std::string makeCut_pi0mass_dstr_single( Double_t D_L,  Double_t D_H ){

  std::stringstream sTmp;
  sTmp << Form( "( (%f-%f<acc1m && acc1m<%f+%f) || acc1m<0 )", PDGmass::pi0, D_L, PDGmass::pi0, D_H );
    return sTmp.str();
}


Double_t nominal_dmass( Int_t decay ){
  if( decay==101  || decay==2    || decay==200  || decay==1010 ||
      decay==1101 || decay==210  || decay==1200 || decay==12   ||
      decay==301  || decay==1210 ) return PDGmass::d0;
  else if( decay==110  || decay==201 || decay==1110 || decay==102 || decay==310 ) return PDGmass::dp;
  else if( decay==421 ) return PDGmass::d0; // !!!!!!!!!!
  else if( decay==411 ) return PDGmass::dp; // !!!!!!!!!!
  else std::cerr << "[ABORT] Wrong D decay : " << decay << std::endl, abort();
}

Double_t nominal_eff_dmass( Int_t decay ){
  if( decay==101  || decay==2    || decay==200  || decay==1010 ||
      decay==1101 || decay==210  || decay==1200 || decay==12   ||
      decay==301  || decay==1210 ) return 1.86224;
  else if( decay==110  || decay==201 || decay==1110 || decay==102 || decay==310 ) return 1.86740;
  else if( decay ==421 ) return 1.86224; // !!!!!!!!!!
  else if( decay ==411 ) return 1.86740; // !!!!!!!!!!
  else std::cerr << "[ABORT] Wrong D decay : " << decay << std::endl, abort();
}
