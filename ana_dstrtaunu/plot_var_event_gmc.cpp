#include "draws_.h"

const Char_t*  tname       = "h15";
const Bool_t   fl_message  = true;
const Bool_t   fl_save     = true; // outfile.eps and outfile.root

const Bool_t   fl_scale    = true; // true(no-stack), false(stack)
const Double_t bdir_cut    = 100;

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace VAR{

  const Bool_t fl_cut_dmass  = true;
  const Bool_t fl_cut_deltam = true;

  const Int_t nfile = 4;
  const Char_t* infile[nfile] = {
    "~/dstrtaunu/modules/dstrtaunu/hbk/hbk8_merge_cut/*mixed*s0[0-5]*.root",
    "~/dstrtaunu/modules/dstrtaunu/hbk/hbk8_merge_cut/*charged*s0[0-5]*.root",
    "~/dstrtaunu/modules/dstrtaunu/hbk/hbk8_merge_cut/*uds*s0[0-5]*.root",
    "~/dstrtaunu/modules/dstrtaunu/hbk/hbk8_merge_cut/*charm*s0[0-5]*.root",
  };
    
  const Char_t* c_common = "1";
  const Int_t nctgry = 6;
  const Char_t* c_type [nctgry] = {
    "self==1", // sig
    "self==2", // tag
    "self==0", // fake
    "self==-1", // other DD
    "self==-2&&evt_type==4", // other BB(charged)
    "self==-2&&abs(evt_type)<3",  // other BB(continuum)
  };

  const Char_t* label[nctgry] = {
    "true-sig",
    "true-tag",
    "fake",
    "other DD",
    "other BB(B+B-)",
    "other BB(continuum)",
  };
  
  const Int_t    nvar             = 10;
  const Char_t*  axis_name [nvar] = {
    "mmiss*mmiss*abs(mmiss)/mmiss", "mmiss2*mmiss2*abs(mmiss2)/mmiss2",
    "evis",        "evis2",
    "cosdlh",      "cosdll",
    "rm_bdir",     "atan(rm_bdir)",
    "eecl",  "atan(cosdll)",
  };
  const Char_t*  axis_label[nvar] = {
    "M_{miss}^{2} [GeV^{2}]",  "M'_{miss}^{2} [GeV^{2}]",
    "E_{vis} [GeV]",           "E'_{vis} [GeV]",
    "cos#theta_{B-DL}^{high}", "cos#theta_{B-DL}^{low}",
    "flag of B direction",     "atan(bdir)",
    "E_{ECL} [GeV]", "atan(cos#theta_{B-DL}^{low})",
  };
  const Int_t    xbin      [nvar] = {45,  45,
				     40, 40, 40,  50,
				     70, 30,
				     24, 30,

  };
  const Double_t xmin      [nvar] = {-9, -9,
				     4,   4, -10, -40,
				     -30, -TMath::PiOver2(),
				     0,   -TMath::PiOver2(),

  };
  const Double_t xmax      [nvar] = { 36, 36,
				      12, 12, 10, 10,
				       5, TMath::PiOver2(),
				     1.2, TMath::PiOver2(),

  };
  /*
  const Char_t*  axis_name [nvar] = {"eecl","abs(mmiss)","evis","rm_bdir","cosdlh", "cosdll", "abs(mmiss2)", "evis2","mmiss","mmiss2"};
  const Char_t*  axis_label[nvar] = {"E_{ECL} [GeV]","|M_{miss}| [GeV]","E_{vis} [GeV]", "flag of B direction",
				     "cos#theta_{B-DL}^{high}","cos#theta_{B-DL}^{low}",
				     "|M'_{miss}| [GeV]", "E'_{vis} [GeV]", "M_{miss} [GeV]", "M'_{miss} [GeV]"};
  const Int_t    xbin      [nvar] = {24,    30,   40,    70, 100,  100,  30,   40,  45,    45};
  const Double_t xmin      [nvar] = {0.0,  0.0,  4.0, -30.0, -30, -100, 0.0,  4.0, -3.0, -3.0};
  const Double_t xmax      [nvar] = {1.2,  6.0, 12.0,   5.0,  10,   10, 6.0, 12.0,  6.0,  6.0};
  */
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(!true); // tmpppppp
  using namespace VAR;
  TApplication app( "app", &argc, argv );
  Style();

  TChain* chain = new TChain(tname);
  for( Int_t i=0; i<nfile; i++ ) std::cout << Form("infile%d : ", i)
					   << chain->Add( infile[i] )
					   << " files"
					   << std::endl;

  std::cout << chain->GetEntries()  << " entries, "
	    << std::endl;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas*  c1 = Canvas( "c1", "c1", 4, 3 );
  THStack** hs = makeStack( "hs", nvar ); // [nvar]
  TH1D***   hc = new TH1D**[nvar];        // [nvar][nctgry]
  for( Int_t i=0; i<nvar; i++ ) hc[i] = makeHist( Form("hc_%d",i), xbin[i], xmin[i], xmax[i], nctgry );
  std::stringstream sTmp;
  TLegend* leg = new TLegend( 0.75,0.75,0.99,0.99 );
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  

  for( Int_t i=0; i<nvar; i++ ){
    hs[i]->SetTitle( axis_label[i] );
    for( Int_t j=0; j<nctgry; j++ ){
      sTmp.str("");
      sTmp.clear();
      sTmp << "1";
      if( fl_cut_dmass  ) sTmp << " && (" << makeCut_dmass().c_str()  << ")";
      if( fl_cut_deltam ) sTmp << " && (" << makeCut_deltam().c_str() << ")";
      sTmp << " && ( rm_bdir< " << bdir_cut << ")";
      chain->Project( Form("hc_%d_%d",i,j), axis_name[i], Form("(%s)&&(%s)&&(%s)&&(%s)", c_common, makeCut_rem().c_str(), sTmp.str().c_str(), c_type[j]) );
      hc[i][j]->SetMarkerStyle(1);
      hc[i][j]->SetLineColor  (j+1);
      if( !fl_scale ) hc[i][j]->SetFillColor(j+1);

      if( fl_message ){
	std::cout << std::setw(10) << std::right << axis_name [i]
		  << std::setw(20) << std::right << label[j]
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
      if( i==0 ) leg->AddEntry( hc[i][j], label[j], "F" );
    }
    c1->cd(i+1);
    if( fl_scale ){
      for( Int_t i=0; i<nvar; i++ ){
	hc[i][0]->SetLineWidth(2); // sig.
	hc[i][1]->SetLineWidth(2); // norm.
      }
    }
    if( fl_scale ) hs[i]->Draw("nostack hist");
    else           hs[i]->Draw();
    
    hs[i]->GetXaxis()->CenterTitle();
    hs[i]->GetXaxis()->SetTitle( axis_label[i] );
    if( i==0 ) leg->Draw();
  }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  c1->Update();
  if( fl_save ){
    c1->Print( Form("pic/var_norm%d_bdir%.0f.eps",  fl_scale, bdir_cut) );
    c1->Print( Form("pic/var_norm%d_bdir%.0f.root", fl_scale, bdir_cut) );
  }
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  
  return 0;
}
