#include "draws_.h"

const Bool_t fl_message  = true;
const Bool_t fl_save     = true; // outfile.eps and outfile.root
const Bool_t fl_scale    = true;
const Bool_t fl_scan     = !true;
const Int_t nfile = 2;

const Char_t* infile[nfile] = {"~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpi/*.root",
			       "~/dstrtaunu/modules/dstrtaunu/hbk/nor_kpi/*.root",
};
const char* tname  = "h15";

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace COSBDL{

  const Bool_t fl_cut_dmass  = true;
  const Bool_t fl_cut_deltam = true;
  const Int_t n_ctgry  = 4;
  const Int_t type_file[n_ctgry] = {0,1,0,1};
  
  const Char_t* c_ctgry[2][n_ctgry] = {
    {
      " dst1self!=0&&d1self==1&&l1self==1&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true sig-lepton
      " dst1self!=0&&d1self==1&&l1self==1&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true sig-lepton
      " dst1self!=0&&d1self==1&&l1self==2&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true tag-lepton
      " dst1self!=0&&d1self==1&&l1self==2&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true tag-lepton
    },
    {
      " dst2self!=0&&d2self==1&&l2self==1&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true sig-lepton
      " dst2self!=0&&d2self==1&&l2self==1&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true sig-lepton
      " dst2self!=0&&d2self==1&&l2self==2&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true tag-lepton
      " dst2self!=0&&d2self==1&&l2self==2&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true tag-lepton
    },
  };

  const Int_t n_plot = 2;
  const Char_t* ctgry_label[n_plot] = {
    "true sig-lepton",
    "true tag-lepton",
  };

  const Int_t add_matrix[n_plot][n_ctgry] = {
    {1,1,0,0},
    {0,0,1,1},
  };

  const Char_t* outname    = "lpcm";
  const Char_t* axis_name  = "l%dpcm";
  const Char_t* axis_label = "p_{l}^{CM} [GeV]";
  const Int_t    xbin =  30;
  const Double_t xmin =  0.0;
  const Double_t xmax =  3.0;
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  using namespace COSBDL;
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

  for( Int_t i=0; i<2; i++ ){ // B0B0 / B+B-
    for( Int_t j=0; j<3; j++ ){ // DD / D*D / D*D*
      for( Int_t k=0; k<2; k++ ){ // 1st / 2nd
	hs[i][j][k]->SetTitle( Form("(%s, %s, %s)", ctgry_BB[i], ctgry_DD[j], ctgry_12[k]) );
	for( Int_t l=0; l<n_ctgry; l++ ){ // category
	  sTmp.str("");
	  sTmp.clear();
	  sTmp << "1";
	  if( fl_cut_dmass  ) sTmp << " && (" << makeCut_dmass().c_str()  << ")";
	  if( fl_cut_deltam ) sTmp << " && (" << makeCut_deltam().c_str() << ")";
	  sTmp << " && "  << makeCategory_recBBDD( i, j ).c_str();
	  sTmp << " && (" << c_ctgry[k][l] << ")";
	  
	  chain[type_file[l]]->Project( Form("hc_%d_%d_%d_%d",i,j,k,l), Form(axis_name, k+1), Form("(%s)&&(%s)", makeCut_rem().c_str(), sTmp.str().c_str()) );
	  if( fl_scan ){
	    chain[type_file[l]]->SetScanField(0);
	    chain[type_file[l]]->Scan( "exprun:event:evt_type:rm_bb:gm_dd:rm_dd:gm_semi:gm_ddst1:dst1_acc:gm_ddst2:dst2_acc:nb1:nb2:d1self:dst1self:l1self:d2self:dst2self:l2self", Form("(%s)&&(%s)", makeCut_rem().c_str(), sTmp.str().c_str()) );
	  }

	  if( fl_scale ){
	    hc[i][j][k][l]->Sumw2();
	  }
	  
	  if( fl_message ){
	    if     ( k==0 && l==0 ) std::cout << "**********************************************************************************************************************" << std::endl;
	    else if(         l==0 ) std::cout << "----------------------------------------------------------------------------------------------------------------------" << std::endl;
	    std::cout << "category " << l << " : "
		      << ctgry_BB [i]     << ", "
		      << ctgry_DD [j]     << ", "
		      << ctgry_12 [k]     << " : "
		      << type_file[l]     << " : ";
	    Print( hc[i][j][k][l], xbin );
	    //<< std::endl << sTmp.str().c_str()
	    std::cout << std::endl;
	  }
	}
	
	for( Int_t m=0; m<n_plot; m++ ){ // plot
	  hp[i][j][k][m]->SetMarkerStyle(1);      
	  hp[i][j][k][m]->SetLineColor(m+2);
	  if( i==0 && j==0 && k==0 ) leg->AddEntry( hp[i][j][k][m], ctgry_label[m], "PL" );
	  std::cout << "plot " << m << " <- ";
	  for( Int_t l=0; l<n_ctgry; l++ ){
	    if( add_matrix[m][l] ){
	      std::cout << l << ", ";
	      hp[i][j][k][m]->Add( hc[i][j][k][l] );
	    }
	  }
	  std::cout << ") ";
	  Print( hp[i][j][k][m], xbin );
	  std::cout << std::endl;
	  hp[i][j][k][m]->Scale( (hp[i][j][k][m]->GetEntries() ? 1.0/hp[i][j][k][m]->GetEntries() : 1.0) );
	  hs[i][j][k]->Add( hp[i][j][k][m] );
	}

	c1[i]->cd(j+1+3*k);
	hs[i][j][k]->Draw("nostack PE hist");
	hs[i][j][k]->GetXaxis()->CenterTitle();
	hs[i][j][k]->GetXaxis()->SetTitle(axis_label);
	if( i==0 && j==0 && k==0 ) leg->Draw();
      }
    }
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
