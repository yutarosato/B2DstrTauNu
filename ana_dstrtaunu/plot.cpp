#include "draws_.h"

const Bool_t fl_message  = true;
const Bool_t fl_save     = true; // outfile.eps and outfile.root
const Bool_t fl_scan     = !true;
//const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/nor_kpi/*setA.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpi/*setA.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/mixed/*s00*.root";
const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/mixed/*s00*.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/mixed_10modes/*s00*.root";
//const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/mixed_only_kpi/*s00*.root";
//const char* infile = "tmp/*.root";
const char* tname  = "h15";

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace DMASS{
  const Bool_t fl_cut_pi0cos = true;
  const Bool_t fl_cut_dmass  = false;
  const Bool_t fl_cut_deltam = false;
  const Int_t n_ctgry  = 2;
  const Char_t* c_ctgry[2][n_ctgry] = { 
    {"d1self==0", "d1self==1"},
    {"d2self==0", "d2self==1"},
  };
  
  const Char_t* ctgry_label[n_ctgry] = {
    "fake D",
    "true D",
  };

  const Char_t* c_common = "1";
  //const Char_t* c_common = "abs(rm_d1lun)==421&&abs(rm_d2lun)==421";
  //const Char_t* c_common = "abs(rm_d1lun)==421&&abs(rm_d2lun)==421&&rm_d1==101";
  //const Char_t* c_common = "abs(rm_d1lun)==411&&rm_d1<1000";
  //const Char_t* c_common = "abs(rm_d1lun)==411&&abs(rm_d2lun)==421";

  //"rm_d1==101&&rm_d2==101"
  //"abs(rm_d1lun)==411&&abs(rm_d2lun)==411" // D+ (411), D0 (421)
  //"abs(rm_dst1l)==413&&abs(rm_dst2l)==413" // D*+(413), D*0(423)
  //"abs(rm_dst1)==211&&abs(rm_dst2)==211"   // pi+(211), pi0(111)
  
  const Char_t* outname    = "dmass";
  const Char_t* axis_name  = "d%d_m";
  const Char_t* axis_label = "D mass [GeV]";
  const Int_t    xbin =  100;
  const Double_t xmin = 1.81;
  const Double_t xmax = 1.91;
  const Double_t cnt_xmin = 1.835;
  const Double_t cnt_xmax = 1.895;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace DELTAM{
  const Bool_t fl_cut_pi0cos = true;
  const Bool_t fl_cut_dmass  = true;
  const Bool_t fl_cut_deltam = false;
  const Int_t n_ctgry  = 3;
  const Char_t* c_ctgry[2][n_ctgry] = { 
    {
     "dst1self==0&&d1self==0",
     "dst1self==0&&d1self==1",
     "dst1self==1",
    },
    {
     "dst2self==0&&d2self==0",
     "dst2self==0&&d2self==1",
     "dst2self==1",
    },
  };
  
  const Char_t* ctgry_label[n_ctgry] = {
    "fake D* (fake D)",
    "fake D* (true D)",
    "true D*",
  };

  const Char_t* c_common = "abs(rm_dst1)==211";
  
  const Char_t* outname    = "deltam";
  const Char_t* axis_name  = "dm%d";
  const Char_t* axis_label = "#Delta m [GeV]";
  const Int_t    xbin =   48;
  const Double_t xmin = 0.13;
  const Double_t xmax = 0.17;
  const Double_t cnt_xmin = 0.0;
  const Double_t cnt_xmax = 0.155;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace COSBDL{
  const Bool_t fl_cut_pi0cos = true;
  const Bool_t fl_cut_dmass  = true;
  const Bool_t fl_cut_deltam = true;
  const Int_t n_ctgry  = 5;

  const Char_t* c_ctgry[2][n_ctgry] = {
    {
      "(dst1self==0||d1self==0)",                                                  // fake D(*)
      " dst1self!=0&&d1self==1&&l1self<0",                                         // true D(*) and fake lepton
      " dst1self!=0&&d1self==1&&l1self>0 &&!(abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true lepton but other event_type
      " dst1self!=0&&d1self==1&&l1self==1&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true sig-lepton
      " dst1self!=0&&d1self==1&&l1self==2&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true tag-lepton
    },
    {
      "(dst2self==0||d2self==0)",                                                  // fake D(*)
      " dst2self!=0&&d2self==1&&l2self<0",                                         // true D(*) and fake lepton
      " dst2self!=0&&d2self==1&&l2self>0 &&!(abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true lepton but other event_type
      " dst2self!=0&&d2self==1&&l2self==1&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true sig-lepton
      " dst2self!=0&&d2self==1&&l2self==2&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true tag-lepton
    },
  };
  
  const Char_t* ctgry_label[n_ctgry] = {
    "fake D(*)",
    "true D(*), fake lepton",
    "true D(*), true lepton from other event",
    "true D(*), true sig-lepton",
    "true D(*), true tag-lepton",
  };

  const Char_t* c_common = "1";

  const Char_t* outname    = "cosBDL";
  const Char_t* axis_name  = "cosdl%d";
  const Char_t* axis_label = "cos#theta_{BDl}";
  const Int_t    xbin =  45;
  const Double_t xmin = -20;
  const Double_t xmax =  10;
  const Double_t cnt_xmin = -2.5;
  const Double_t cnt_xmax =  1.2;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  //using namespace DMASS;
  //using namespace DELTAM;
  using namespace COSBDL;
  TApplication app( "app", &argc, argv );
  Style();

  TChain* chain = new TChain(tname);
  std::cout << "[REC] "
	    << chain->Add( infile ) << " files, ";
  std::cout << chain->GetEntries()  << " entries, "
	    << outname << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas** c1 = new TCanvas*[2];
  for( int v=0; v<2; v++ ){
    c1[v] = Canvas( Form("c1_%d",v), Form("c1_%d", v), 3, 2 );
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  THStack**** hs  = makeStack( "hs",                   2,3,2         ); // [BB][DD][1st/2nd]
  TH1D*****   hc  = makeHist ( "hc", xbin, xmin, xmax, 2,3,2,n_ctgry ); // [BB][DD][1st/2nd][ctgry]
  std::stringstream sTmp;
  TLegend* leg = new TLegend( 0.75,0.75,0.99,0.99 );
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  for( Int_t i=0; i<2; i++ ){ // begin loop [B0B0 / B+B-]
    for( Int_t j=0; j<3; j++ ){ // begin loop [DD / D*D / D*D*]
      for( Int_t k=0; k<2; k++ ){ // begin loop [1st / 2nd]
	hs[i][j][k]->SetTitle( Form("(%s, %s, %s)", ctgry_BB[i], ctgry_DD[j], ctgry_12[k]) );
	for( Int_t l=0; l<n_ctgry; l++ ){ // begin loop [category]
	  sTmp.str("");
	  sTmp.clear();
	  sTmp << "(" << c_common << ")";
	  //if( fl_cut_pi0cos ) sTmp << " && (" << makeCut_pi0cos().c_str() << ")";
	  if( fl_cut_dmass  ) sTmp << " && (" << makeCut_dmass().c_str()  << ")";
	  if( fl_cut_deltam ) sTmp << " && (" << makeCut_deltam().c_str() << ")";
	  sTmp << " && " << makeCategory_recBBDD( i, j ).c_str();
	  sTmp << " && " << makeCut_rem().c_str(); 
	  sTmp << " && (" << c_ctgry[k][l] << ")";
	  sTmp << " && ( rm_bdir<-10 )"; // b direction
	  
	  chain->Project( Form("hc_%d_%d_%d_%d",i,j,k,l), Form(axis_name, k+1), sTmp.str().c_str() );
	  if( fl_scan ){
	    chain->SetScanField(0);
	    chain->Scan( "exprun:event:evt_type:rm_bb:gm_dd:rm_dd:gm_semi:gm_ddst1:dst1_acc:gm_ddst2:dst2_acc:nb1:nb2:d1self:dst1self:l1self:d2self:dst2self:l2self:rm_dst1:rm_d1:rm_l1:rm_dst2:rm_d2:rm_l2:gm_df1hr:gm_df1hn:gm_df1le:gm_df1nu:gm_df1ga:gm_df2hr:gm_df2hn:gm_df2le:gm_df2nu:gm_df2ga", Form("(%s)&&(dm%d>0.143&&dm%d<0.147)", sTmp.str().c_str(), k+1,k+1) );
	  }
	  
	  hc[i][j][k][l]->SetFillColor(col_fil[l]);
	  hs[i][j][k]->Add( hc[i][j][k][l] );
	  if( i==0 && j==0 && k==0 ) leg->AddEntry( hc[i][j][k][l], ctgry_label[l], "F" );

	  if( fl_message ){
	    if     ( k==0 && l==0 ) std::cout << "**********************************************************************************************************************" << std::endl;
	    else if(         l==0 ) std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
	    std::cout << ctgry_BB[i] << ", "
		      << ctgry_DD[j] << ", "
		      << ctgry_12[k] << " : ";
	    Print( hc[i][j][k][l], xbin, cnt_xmin, cnt_xmax );
	    std::cout << ctgry_label[l]
	      //<< std::endl << sTmp.str().c_str()
		      << std::endl;
	  }
	} // end loop [category]
	c1[i]->cd(j+1+3*k);
	hs[i][j][k]->Draw();
	hs[i][j][k]->GetXaxis()->CenterTitle();
	hs[i][j][k]->GetXaxis()->SetTitle(axis_label);
	if( i==0 && j==0 && k==0 ) leg->Draw();
      } // end loop [1st / 2nd]
    } // end loop [DD / D*D / D*D*]

    c1[i]->Update();
    if( fl_save ){
      c1[i]->Print( Form("pic/%s_%d.eps", outname,i)  );
      c1[i]->Print( Form("pic/%s_%d.root",outname,i)  );
    }
  } // end loop [B0B0 / B+B-]

  /*
  TCanvas* c2 = Canvas( "c2", "c2" );

  TH1D** h_fit = makeHist("h_fit", xbin, xmin, xmax, n_ctgry );
  h_fit[0]->SetFillColor( col_fil[0] );
  h_fit[1]->SetFillColor( col_fil[1] );
  h_fit[0]->Add( hc[0][2][0][0] );
  h_fit[1]->Add( hc[0][2][0][0] );
  h_fit[1]->Add( hc[0][2][0][1] );
  */

  const Int_t sel_fun = 20;
  const Double_t xmin_fit = 1.82;
  const Double_t xmax_fit = xmax;
  

  //TF1* func = new TF1( "func", make_func(sel_fun), xmin_fit, xmax_fit, n_fitfunc_par(sel_fun) );
  //func_set_parameters(sel_fun, func, h_fit[1], xbin, xmin_fit, xmax_fit);
  //h_fit[1]->Fit("func","R");
  //h_fit[0]->Draw("same");
  //TF1* func_bg = new TF1( "func_bg", "[0]*x+[1]", xmin_fit, xmax_fit );
  //func_bg->SetParameters( func->GetParameter(3), func->GetParameter(4) );
  //func_bg->Draw("Lsame");
  /*
  TF1* func = new TF1( "func", make_func(sel_fun), xmin_fit, xmax_fit, n_fitfunc_par(sel_fun) );
  func_set_parameters(sel_fun, func, hc[0][2][0][1], xbin, xmin_fit, xmax_fit);
  hc[0][2][0][1]->Fit("func","R");
  */
  //c2->Update();  



  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
