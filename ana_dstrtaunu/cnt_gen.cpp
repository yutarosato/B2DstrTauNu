#include "draws_.h"

//const char* infile = "~/dstrtaunu/modules/dstrtaunu_gen/hbk/nor_kpi/*setB.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu_gen/hbk/sig_kpi/*setA.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu_gen/hbk/nor_kpipi0/*setA.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu_gen/hbk/sig_kpipi0/*setA.root";
const char* infile = "~/dstrtaunu/modules/dstrtaunu_gen/hbk/mixed/*s00*.root";
const char* tname  = "h16";

const Int_t   ctgry_evt_type[6] = {1,2,3,-3,4,5};
const Int_t   ctgry_gm_dd   [4] = {0,1,2,3};
const Int_t   ctgry_gm_semi [7] = {-3,-2,-1,0,1,2,3};
const Char_t* ctgry_gm_semi2[3] = {"gm_semi<0","gm_semi==1","gm_semi>1"};

const Char_t* name_evt_type[6] = {"uds","charm","unmixed","mixed","charged","Y(nS)"};
const Char_t* name_gm_dd   [4] = {"other","D D ","D*D ","D*D*"};
const Char_t* name_gm_semi [7] = {"e-mu","mu-mu","e-e","other","tau-tau","e-tau","mu-tau"};
const Char_t* name_gm_semi2[3] = {"l-l","tau-tau","l-tau"};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  TChain* chain = new TChain(tname);
  std::cout << "[Gen] "
	    << chain->Add( infile ) << " files, ";
  Int_t ntot = chain->GetEntries();
  std::cout << ntot << " entries "
	    << std::endl;
  std::cout << infile << std::endl;

  std::cout << "--------------------------------------------------------------" << std::endl;
  for( Int_t i=0; i<6; i++ ){
    Int_t tmp_n = chain->GetEntries( Form("evt_type==%d",ctgry_evt_type[i]) );
    std::cout << std::setw(10) << std::right << name_evt_type[i] << " : "
	      << Form( "%10d ( %6.2f % )", tmp_n, 100.*tmp_n/ntot ) 
	      << std::endl;
  }
  std::cout << "--------------------------------------------------------------" << std::endl;
  for( Int_t j=0; j<4; j++ ){
    Int_t tmp_n = chain->GetEntries( Form("gm_dd==%d",ctgry_gm_dd[j]) );
    std::cout << std::setw(10) << std::right << name_gm_dd[j] << " : "
	      << Form( "%10d ( %6.2f % )", tmp_n, 100.*tmp_n/ntot ) 
	      << std::endl;
  }
  std::cout << "--------------------------------------------------------------" << std::endl;
  for( Int_t k=0; k<7; k++ ){
    Int_t tmp_n = chain->GetEntries( Form("gm_semi==%d",ctgry_gm_semi[k]) );
    std::cout << std::setw(10) << std::right << name_gm_semi[k] << " : "
	      << Form( "%10d ( %6.2f % )", tmp_n, 100.*tmp_n/ntot );
    if( k==5 || k==6 ){
      tmp_n = chain->GetEntries( Form("gm_semi==%d && (gm_t1lep==1||gm_t1lep==10)",ctgry_gm_semi[k]) );
      std::cout << ", tau ->  lnunu : "
		<< Form( "%10d ( %6.2f % )", tmp_n, 100.*tmp_n/ntot );
    }
    std::cout << std::endl;
  }
  std::cout << "**************************************************************" << std::endl;

  for( Int_t i=2; i<5; i++ ){ // unmied, mixed, charged
    for( Int_t j=1; j<4; j++ ){ // DD, D*D, D*D*
      for( Int_t k=0; k<3; k++ ){ // l-l, tau-tau, l-tau
	Int_t tmp_n = chain->GetEntries( Form("evt_type==%d&&gm_dd==%d&&%s",ctgry_evt_type[i],ctgry_gm_dd[j],ctgry_gm_semi2[k]) );
	std::cout << std::setw(10) << std::right << name_evt_type[i] << ", "
		  << std::setw(10) << std::right << name_gm_dd   [j] << ", "
		  << std::setw(10) << std::right << name_gm_semi2[k] << " : "
		  << Form( "%10d ( %6.2f % )", tmp_n, 100.*tmp_n/ntot );
	if( k==2 ){
	  tmp_n = chain->GetEntries( Form("evt_type==%d&&gm_dd==%d&&%s&&(gm_t1lep==1||gm_t1lep==10)",ctgry_evt_type[i],ctgry_gm_dd[j],ctgry_gm_semi2[k]) );
	  std::cout << ", tau -> lnunu : "
		    << Form( "%10d ( %6.2f % )", tmp_n, 100.*tmp_n/ntot );
	}
	std::cout << std::endl;
      }
      if( j!=3 )std::cout << "--------------------------------------------------------------" << std::endl;
    }
    std::cout << "==============================================================" << std::endl;
  }

  std::cout << "finish" << std::endl;

  return 0;
}
