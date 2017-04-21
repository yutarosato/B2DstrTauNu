#include "draws_.h"

//const Char_t* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpi/*setA.root"; // [sig]
//const Char_t* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/nor_kpi/*setA.root"; // [nor]
//const Char_t* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpipi0/*setA.root"; // [sig]
//const Char_t* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/nor_kpipi0/*setA.root"; // [nor]
//const Char_t* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpi_dpi0/*setA.root"; // [sig]
//const Char_t* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/nor_kpi_dpi0/*setA.root"; // [nor]
const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/mixed/*s00*.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/mixed_only_kpi/*s00*.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/mixed_10modes/*s00*.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/mixed/*s00*.root";
const char* tname  = "h15";

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const Char_t* c_common  = "( abs(evt_type)==rm_bb&&gm_dd==rm_dd ) && ( d1self==1&&d2self==1&&dst1self!=0&&dst2self!=0 )";
//const Char_t* c_common  = "( abs(evt_type)==rm_bb&&gm_dd==rm_dd ) && ( d1self==1&&d2self==1&&dst1self!=0&&dst2self!=0 ) && (abs(rm_d1lun)==411&&abs(rm_d2lun)==411)";
//const Char_t* c_common  = "( abs(evt_type)==rm_bb&&gm_dd==rm_dd ) && ( d1self==1&&d2self==1&&dst1self!=0&&dst2self!=0 ) && (abs(rm_d1lun)==421&&abs(rm_d2lun)==411)";
//const Char_t* c_common  = "( abs(evt_type)==rm_bb&&gm_dd==rm_dd ) && ( d1self==1&&d2self==1&&dst1self!=0&&dst2self!=0 ) && (abs(rm_d1lun)==421&&abs(rm_d2lun)==421) && (rm_d1==1101&&rm_d2==1101)";
//const Char_t* c_common  = "( abs(evt_type)==rm_bb&&gm_dd==rm_dd ) && ( d1self==1&&d2self==1&&dst1self!=0&&dst2self!=0 ) && (rm_d1==110&&rm_d2==110)";
const Char_t* c_true[2] = { "( l1self==1 && l2self==2 ) || ( l1self==2 && l2self==1 )", // signal
			    "( l1self==2 && l2self==2 )",                               // normalization
};
const Char_t* c_name[2] = { "sig","nor" };
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  Style();
  
  TChain* chain = new TChain(tname);
  std::cout << "[REC] "
	    << chain->Add( infile ) << " files, ";
  std::cout << chain->GetEntries()  << " entries"
	    << std::endl;
  
  std::stringstream sTmp;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  for( Int_t i=0; i<2; i++ ){ // begin loop [B0B0 / B+B-]
    for( Int_t j=0; j<3; j++ ){ // begin loop [DD / D*D / D*D*]
      for( Int_t l=0; l<2; l++ ){ // begin loop [sig/nor]
	if( !(i==0 && j==2) ) continue; // tmppppppppp
	sTmp.str("");
	sTmp.clear();
	sTmp << c_common;
	//sTmp << "1";
	sTmp << " && (" << makeCategory_recBBDD( i, j ).c_str() << ")";
	sTmp << " && (" << c_true[l]                            << ")";
	sTmp << " && (" << makeCut_dmass().c_str()              << ")";
	sTmp << " && (" << makeCut_deltam().c_str()             << ")";
	sTmp << " && (" << makeCut_rem().c_str()                << ")";
	//sTmp << " && (" << makeCut_pi0cos().c_str()             << ")";
	sTmp << " && rm_bdir<-10";
	
	if     ( j==0 && l==0 ) std::cout << "**********************************************************************************************************************" << std::endl;
	else if(         l==0 ) std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << ctgry_BB [i]     << ", "
		  << ctgry_DD [j]     << ", "
		  << c_name[l]        << " : "
		  << chain->GetEntries( sTmp.str().c_str() )
		  << std::endl;

	//chain->SetScanField(0);
	//chain->Scan("exprun:event:rm_d1:rm_d2", sTmp.str().c_str() );
	
      } // end loop [sig/nor]
    } // end loop [DD / D*D / D*D*]
  } // end loop [B0B0 / B+B-]
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  
  return 0;
}
