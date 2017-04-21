#include "draws_.h"

const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/mixed/*s00*.root";
const char* tname  = "h15";

const Int_t n_ctgry = 4;
const Char_t* c_ctgry[n_ctgry] = {
  " ( abs(evt_type)==rm_bb&&gm_dd==rm_dd ) && ( d1self==1&&d2self==1&&dst1self!=0&&dst2self!=0 ) && l1self>0 && l2self>0 && l1self*l2self<3 )", // signal
  " ( abs(evt_type)==rm_bb&&gm_dd==rm_dd ) && ( d1self==1&&d2self==1&&dst1self!=0&&dst2self!=0 ) && l1self>0 && l2self>0 && l1self*l2self>3 )", // normalization
  " ( abs(evt_type)==rm_bb&&gm_dd==rm_dd ) && ( d1self==0||d2self==0||dst1self==0||dst2self==0||l1self<0||l2self<0)",                                          // fake
  "!( abs(evt_type)==rm_bb&&gm_dd==rm_dd )",                                                                                                                   // other events
};

const Char_t* ctgry_label[n_ctgry] = {
  "true sig",
  "true norm",
  "false",
  "other evt",
};

const Char_t* outname    = "cosBDL";
const Char_t* axis_name  = "cosdl%d";
const Char_t* axis_label = "cos#theta_{BDl}";
const Int_t    xbin =  45;
const Double_t xmin = -20;
const Double_t xmax =  10;
const Double_t cnt_xmin = -2.5;
const Double_t cnt_xmax =  1.2;


// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
THStack* hs  = new THStack("hs","hs");
TH1D***  hc  = makeHist ( "hc", xbin, xmin, xmax, 3,n_ctgry ); // [1st/2nd/1st+2nd][ctgry]
TLegend* leg = new TLegend( 0.75,0.75,0.99,0.99 );
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
      for( Int_t l=0; l<n_ctgry; l++ ){ // begin loop [category]
	if( !(i==0 && j==2) ) continue; // tmppppppppp
	sTmp.str("");
	sTmp.clear();
	sTmp << "1";
	sTmp << " && (" << makeCategory_recBBDD( i, j ).c_str() << ")";
	sTmp << " && (" << c_ctgry[l]                           << ")";
	sTmp << " && (" << makeCut_dmass().c_str()              << ")";
	sTmp << " && (" << makeCut_deltam().c_str()             << ")";
	sTmp << " && (" << makeCut_rem().c_str()                << ")";
	//sTmp << " && (" << makeCut_pi0cos().c_str()             << ")";
	//sTmp << " && rm_bdir<-10";
	
	if     ( j==0 && l==0 ) std::cout << "**********************************************************************************************************************" << std::endl;
	else if(         l==0 ) std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
	std::cout << ctgry_BB   [i]     << ", "
		  << ctgry_DD   [j]     << ", "
		  << ctgry_label[l]     << " : "
		  << chain->GetEntries( sTmp.str().c_str() )
		  << std::endl;

	chain->Project( Form("hc_0_%d",l), "cosdl1", sTmp.str().c_str() );
	chain->Project( Form("hc_1_%d",l), "cosdl1", sTmp.str().c_str() );
	hc[2][l]->Add( hc[0][l] );
	hc[2][l]->Add( hc[1][l] );
	hc[2][l]->SetLineColor(l+1);
	hc[2][l]->SetFillColor(l+1);
	hs->Add( hc[2][l] );
	leg->AddEntry( hc[2][l], ctgry_label[l], "F" );

      } // end loop [sig/nor]
    } // end loop [DD / D*D / D*D*]
  } // end loop [B0B0 / B+B-]

  TCanvas* c1 = new TCanvas( "c1","c1", 600, 600 );
  c1->Draw();
  hs->Draw();
  leg->Draw();
  c1->Print( Form("pic/%s_sum.eps", outname)  );
  c1->Print( Form("pic/%s_sum.root",outname)  );
    
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  
  return 0;
}
