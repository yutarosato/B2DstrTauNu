#include "draws_.h"

const Bool_t fl_message  = true;
const Bool_t fl_save     = true; // outfile.eps and outfile.root
const Bool_t fl_scale    = !true;
const char* tname  = "h15";

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace VAR{

  const Bool_t fl_cut_dmass  = true;
  const Bool_t fl_cut_deltam = true;

  const Int_t nfile = 2;
  const Char_t* infile[nfile] = {"~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpi/*.root",
				 "~/dstrtaunu/modules/dstrtaunu/hbk/nor_kpi/*.root",
  };


  const Int_t ntype = 2;
  const Int_t type_file[ntype] = {0,1};
  const Char_t* c_type [ntype] = { 
    "dst1self!=0&&d1self==1&&l1self>0 && dst2self!=0&&d2self==1&&l2self>0&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true lepton
    "dst1self!=0&&d1self==1&&l1self>0 && dst2self!=0&&d2self==1&&l2self>0&& (abs(evt_type)==rm_bb&&gm_dd==rm_dd)", // true D(*) and true lepton
  };

  const Char_t* type_label[ntype] = {
    "signal",
    "normalization",
  };
  
  const Int_t    nvar             = 4;
  const Char_t*  outname   [nvar] = {"eecl","mmiss","evis","rm_bdir"};
  const Char_t*  axis_name [nvar] = {"eecl","mmiss","evis","rm_bdir"};
  const Char_t*  axis_label[nvar] = {"E_{ECL} [GeV]","M_{miss} [GeV]","E_{vis} [GeV]", "flag of B direction"};
  const Int_t    xbin      [nvar] = {24,    30,   40,    6};
  const Double_t xmin      [nvar] = {0.0,  0.0,  4.0, -1.0};
  const Double_t xmax      [nvar] = {1.2,  6.0, 12.0,  2.0};
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  using namespace VAR;
  TApplication app( "app", &argc, argv );
  Style();
 
  TChain** chain = new TChain*[nfile];
  for( Int_t i=0; i<nfile; i++ ){
    chain[i] = new TChain(tname);
    std::cout << "infile " << i << " : "
	      << chain[i]->Add( infile[i] ) << " files, ";
    std::cout << chain[i]->GetEntries()     << " entries, "
	      << std::endl;
  }
  
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas*  c1 = Canvas( "c1", "c1", 3, 2 );
  THStack** hs = makeStack( "hs", nvar ); // [nvar]
  TH1D***   hc = new TH1D**[nvar];        // [nvar][ntype]
  for( Int_t i=0; i<nvar; i++ ) hc[i] = makeHist( Form("hc_%d",i), xbin[i], xmin[i], xmax[i], ntype );
  std::stringstream sTmp;
  TLegend* leg = new TLegend( 0.75,0.75,0.99,0.99 );
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  

  for( Int_t i=0; i<nvar; i++ ){
    hs[i]->SetTitle( axis_label[i] );
    for( Int_t j=0; j<ntype; j++ ){
      sTmp.str("");
      sTmp.clear();
      sTmp << "1";
      if( fl_cut_dmass  ) sTmp << " && (" << makeCut_dmass().c_str()  << ")";
      if( fl_cut_deltam ) sTmp << " && (" << makeCut_deltam().c_str() << ")";
      //sTmp << " && ( " << "rm_bdir<-5"<< ")";
      chain[type_file[j]]->Project( Form("hc_%d_%d",i,j), axis_name[i], Form("(%s)&&(%s)&&(%s)", makeCut_rem().c_str(), sTmp.str().c_str(), c_type[j]) );
      hc[i][j]->SetMarkerStyle(1);
      hc[i][j]->SetLineColor  (j+1);
      //hc[i][j]->SetFillColor  (j+1);

      if( fl_message ){
	std::cout << std::setw(10) << std::right << axis_name [i]
		  << std::setw(20) << std::right << type_label[j]
		  << " : ";
	Print( hc[i][j], xbin[i] );
	std::cout << std::endl;
	//hc[i][j]->Print("base");
      }

      if( fl_scale ){
	hc[i][j]->Sumw2();
	hc[i][j]->Scale( 1.0/hc[i][j]->GetEntries() );
      }

      hs[i]->Add( hc[i][j] );
      if( i==0 ) leg->AddEntry( hc[i][j], type_label[j], "L" );
    }
    c1->cd(i+1);
    hs[i]->Draw("nostack PE hist");
    //hs[i]->Draw();
    hs[i]->GetXaxis()->CenterTitle();
    hs[i]->GetXaxis()->SetTitle( axis_label[i] );
    if( i==0 ) leg->Draw();
  }


  c1->Update();
  if( fl_save ){
    c1->Print( "pic/var.eps"  );
    c1->Print( "pic/var.root" );
  }
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  
  return 0;
}
