#include "draws_.h"

const Bool_t fl_message  = true;
const Bool_t fl_save     = true; // outfile.eps and outfile.root
const Bool_t fl_scale    = true;
const Bool_t fl_scan     = !true;
const Int_t nfile = 2;

const Char_t* infile[nfile] = {"~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpi/*setA.root", // [sig]
			       "~/dstrtaunu/modules/dstrtaunu/hbk/nor_kpi/*setA.root", // [nor]
};
const Double_t scale_factor[nfile] = {0.25, 1.0};
const char* tname  = "h15";

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const Int_t n_ctgry = 3;

const Int_t type_file[n_ctgry] = {0,0,1};

const Char_t* c_common = "( abs(evt_type)==rm_bb&&gm_dd==rm_dd ) && ( d1self==1&&d2self==1&&dst1self!=0&&dst2self!=0 )";

const Char_t* c_ctgry[2][n_ctgry] = {
  { "( l1self==1 && l2self==2 )", "( l1self==2 && l2self==1 )", "( l1self==2 && l2self==2 )" },
  { "( l1self==2 && l2self==1 )", "( l1self==1 && l2self==2 )", "( l1self==2 && l2self==2 )" },
};

const Int_t n_plot = 3;
const Char_t* plot_label[n_plot] = {
  "sig(sig)",
  "tag(sig)",
  "tag(nor)",
};

const Int_t add_matrix[n_plot][n_ctgry] = {
  {1},
  {0,1},
  {0,0,1},
};


namespace COSBDL{
  const Char_t* outname    = "cosBDL";
  const Char_t* axis_name  = "cosdl%d";
  const Char_t* axis_label = "cos#theta_{BDl}";
  const Int_t    xbin =  30;
  const Double_t xmin = -10;
  const Double_t xmax =  10;
  const Double_t cnt_xmin = -2.5;
  const Double_t cnt_xmax =  1.2;
  const Bool_t fl_cut_dmass  = true;
  const Bool_t fl_cut_deltam = true;
  const Bool_t fl_cut_bdir   = !true;
}

namespace BDIR{
  const Char_t* outname    = "rm_bdir";
  const Char_t* axis_name  = "rm_bdir";
  const Char_t* axis_label = "B direction";
  const Int_t    xbin =  55;
  const Double_t xmin = -100;
  const Double_t xmax =  10;
  const Double_t cnt_xmin = -2.5;
  const Double_t cnt_xmax =  1.2;
  const Bool_t fl_cut_dmass  = true;
  const Bool_t fl_cut_deltam = true;
  const Bool_t fl_cut_bdir   = !true;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  //using namespace COSBDL;
  using namespace BDIR;
  TApplication app( "app", &argc, argv );
  Style();

  TChain** chain = makeChain( tname, nfile );
  for( Int_t i=0; i< nfile; i++ ){
    std::cout << Form( "[infile %d] ", i )
	      << chain[i]->Add( infile[i] ) << " files, ";
    std::cout << chain[i]->GetEntries()     << " entries, "
	      << outname << std::endl;
  }
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas** c1 = new TCanvas*[2];
  for( int v=0; v<2; v++ ) c1[v]= Canvas( Form("c1_%d",v), Form("c1_%d",v), 3, 2 );
  
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  THStack**** hs  = makeStack( "hs",                   2,3,2         ); // [BB][DD][1st/2nd]
  TH1D*****   hc  = makeHist ( "hc", xbin, xmin, xmax, 2,3,2,n_ctgry ); // [BB][DD][1st/2nd][ctgry]  
  TH1D*****   hp  = makeHist ( "hp", xbin, xmin, xmax, 2,3,2,n_plot  ); // [BB][DD][1st/2nd][plot]  
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
	  sTmp << c_common;
	  if( fl_cut_dmass  ) sTmp << " && (" << makeCut_dmass().c_str()  << ")";
	  if( fl_cut_deltam ) sTmp << " && (" << makeCut_deltam().c_str() << ")";
	  if( fl_cut_bdir   ) sTmp << " && rm_bdir==0";
	  sTmp << " && "  << makeCategory_recBBDD( i, j ).c_str();
	  sTmp << " && (" << c_ctgry[k][l] << ")";
	  
	  chain[type_file[l]]->Project( Form("hc_%d_%d_%d_%d",i,j,k,l), Form(axis_name, k+1), Form("(%s)&&(%s)", makeCut_rem().c_str(), sTmp.str().c_str()) );
	  if( fl_scan ){
	    chain[type_file[l]]->SetScanField(0);
	    chain[type_file[l]]->Scan( "exprun:event:evt_type:rm_bb:gm_dd:rm_dd:gm_semi:gm_ddst1:dst1_acc:gm_ddst2:dst2_acc:nb1:nb2:d1self:dst1self:l1self:d2self:dst2self:l2self", Form("(%s)&&(%s)", makeCut_rem().c_str(), sTmp.str().c_str()) );
	  }
	  
	  if( fl_scale ){
	    hc[i][j][k][l]->Sumw2();
	    //hc[i][j][k][l]->Scale( scale_factor[type_file[l]] ); 
	    if( hc[i][j][k][l]->GetEntries() ) hc[i][j][k][l]->Scale( 1/hc[i][j][k][l]->GetEntries() ); 
	  }
	  
	  if( fl_message ){
	    if     ( k==0 && l==0 ) std::cout << "**********************************************************************************************************************" << std::endl;
	    else if(         l==0 ) std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
	    std::cout << "category " << l << " : "
		      << ctgry_BB [i]     << ", "
		      << ctgry_DD [j]     << ", "
		      << ctgry_12 [k]     << " : "
		      << type_file[l]     << " : ";
	    Print( hc[i][j][k][l], xbin, cnt_xmin, cnt_xmax );
	    //<< std::endl << sTmp.str().c_str()
	    std::cout << std::endl;
	  }
	} // end loop [category]
	
	for( Int_t m=0; m<n_plot; m++ ){ // begin loop [plot]
	  hp[i][j][k][m]->SetMarkerStyle(1);      
	  hp[i][j][k][m]->SetLineColor(m+1);
	  //hp[i][j][k][m]->SetFillColor(col_fil[m]);
	  if( i==0 && j==0 && k==0 ) leg->AddEntry( hp[i][j][k][m], plot_label[m], "F" );
	  std::cout << "plot " << m << " : ";
	  sTmp.str("");
	  sTmp.clear();
	  for( Int_t l=0; l<n_ctgry; l++ ){ // begin loop [category]
	    if( add_matrix[m][l] ){
	      sTmp << l << ", ";
	      hp[i][j][k][m]->Add( hc[i][j][k][l] );
	    }
	  } // end loop [category]

	  Print( hp[i][j][k][m], xbin );
	  std::cout << std::setw(60) << std::left << plot_label[m]
		    << " <- (" << sTmp.str().c_str() << ")"
		    << std::endl;
	  hs[i][j][k]->Add( hp[i][j][k][m] );
	} // end loop [plot]
	c1[i]->cd(j+1+3*k);
	//hs[i][j][k]->Draw("E hist");
	hs[i][j][k]->Draw("E hist nostack");
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
  }
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  
  return 0;
}
