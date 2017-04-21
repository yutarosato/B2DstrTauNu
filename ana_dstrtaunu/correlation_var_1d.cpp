#include "draws_.h"

const Char_t*  tname       = "h15";
const Bool_t   fl_message  = true;
const Bool_t   fl_save     = true; // outfile.eps and outfile.root

const Bool_t   fl_scale    = true; // true(no-stack), false(stack)

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace VAR{

  const Bool_t fl_cut_dmass  = true;
  const Bool_t fl_cut_deltam = true;

  const Int_t nfile = 4;
  const Char_t* infile[nfile] = {
    "~/dstrtaunu/modules/dstrtaunu/hbk/hbk4_merge_cut/*mixed*s0[0-5]*.root",
    "~/dstrtaunu/modules/dstrtaunu/hbk/hbk4_merge_cut/*charged*s0[0-5]*.root",
    "~/dstrtaunu/modules/dstrtaunu/hbk/hbk4_merge_cut/*uds*s0[0-5]*.root",
    "~/dstrtaunu/modules/dstrtaunu/hbk/hbk4_merge_cut/*charm*s0[0-5]*.root",
  };
    
  const Char_t* c_common = "dst1_pi0>0.0&&dst2_pi0>0.0";
  const Int_t nctgry = 6;
  const Char_t* c_type [nctgry] = {
    "self==1", // sig
    "self==2", // tag
    "self==0", // fake
    "self==-1", // other DD
    "self==-2&&evt_type==4", // other BB(charged)
    "self==-2&&evt_type<3",  // other BB(continuum)
    
  };

  const Char_t* label[nctgry] = {
    "true-sig",
    "true-tag",
    "fake",
    "other DD",
    "other BB(B+B-)",
    "other BB(continuum)",
  };

  const Int_t ncut = 3;
  const Char_t* cut[ncut] = {
    //"-2<rm_bdir",
    //"-10<rm_bdir && rm_bdir<=-2",
    //"rm_bdir<=-10",
    "-2.0<cosdll",
    "-4.0<cosdll && cosdll<=-2.0",
    "cosdll<=-4.0",
  };
  
  const Int_t    nvar             = 13;
  const Char_t*  axis_name [nvar] = {"abs(mmiss)",  "abs(mmiss2)",
				     "mmiss",       "mmiss2",
				     "abs(mmiss *mmiss *mmiss )/mmiss",
				     "abs(mmiss2*mmiss2*mmiss2)/mmiss2",
				     "evis",        "evis2",
				     "cosdlh",      "cosdll",
				     "rm_bdir",     "atan(rm_bdir)",
				     "eecl", 
  };
  const Char_t*  axis_label[nvar] = {"|M_{miss}| [GeV]",        "|M'_{miss}| [GeV]",
				     "M_{miss} [GeV]",          "M'_{miss} [GeV]",
				     "M_{miss}^{2} [GeV^{2}]",  "M'_{miss}^{2} [GeV^{2}]",  
				     "E_{vis} [GeV]",           "E'_{vis} [GeV]",
				     "cos#theta_{B-DL}^{high}", "cos#theta_{B-DL}^{low}",
				     "flag of B direction",     "atan(bdir)",
				     "E_{ECL} [GeV]",

  };
  const Int_t    xbin      [nvar] = {30, 30, 45,  45, 45, 45,
				     40, 40, 40,  70,
				     100, 30,
				     24,

  };
  const Double_t xmin      [nvar] = {0,   0,  -3,   -3, -3, -3,
				     4,   4, -10, -25,
				     -97, -TMath::PiOver2(),
				     0,

  };
  const Double_t xmax      [nvar] = {  6,  6,  6,  6, 30, 30,
				      12, 12, 10, 10,
				       3, TMath::PiOver2(),
				     1.2,

  };
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  using namespace VAR;
  TApplication app( "app", &argc, argv );
  Style();
  gROOT->SetBatch(true); // tmpppppp

  if( app.Argc()!=2 ) std::cerr << "wrong input" << std::endl
				<< " Usage : "   << app.Argv(0)
				<< " (int)fl_xaxis" << std::endl, abort();
  Int_t fl_xaxis  = atoi(app.Argv(1));

  TChain* chain = new TChain(tname);
  for( Int_t i=0; i<nfile; i++ ) std::cout << Form("infile%d : ", i)
					   << chain->Add( infile[i] )
					   << " files"
					   << std::endl;

  std::cout << chain->GetEntries()  << " entries, "
	    << std::endl;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas*  c1 = Canvas( "c1", "c1", 3, 2 );
  THStack** hs = makeStack( "hs", nvar ); // [nctgry]
  TH1D***   hc = makeHist ( "hc", xbin[fl_xaxis], xmin[fl_xaxis], xmax[fl_xaxis], nctgry, ncut ); // [nctgry][ncut]
  std::stringstream sTmp;
  TLegend* leg = new TLegend( 0.75,0.75,0.99,0.99 );
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  

  for( Int_t i=0; i<nctgry; i++ ){
    hs[i]->SetTitle( label[i] );
    for( Int_t j=0; j<ncut; j++ ){
      sTmp.str("");
      sTmp.clear();
      sTmp << "1";
      if( fl_cut_dmass  ) sTmp << " && (" << makeCut_dmass().c_str()  << ")";
      if( fl_cut_deltam ) sTmp << " && (" << makeCut_deltam().c_str() << ")";
      chain->Project( Form("hc_%d_%d",i,j), axis_name[fl_xaxis], Form("(%s)&&(%s)&&(%s)&&(%s)&&(%s)", makeCut_rem().c_str(), sTmp.str().c_str(), c_type[i],cut[j],c_common) );
      hc[i][j]->SetMarkerStyle(1);
      hc[i][j]->SetLineColor  (j+1);
      if( !fl_scale ) hc[i][j]->SetFillColor(j+1);
      
      if( fl_message ){
	std::cout << std::setw(10) << std::right << axis_name [fl_xaxis]
		  << std::setw(20) << std::right << label[i]
		  << std::setw(25) << std::right << cut[j]
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
      if( i==0 ) leg->AddEntry( hc[i][j], cut[j], "FL" );
    }
    c1->cd(i+1);

    if( fl_scale ) hs[i]->Draw("nostack hist");
    else           hs[i]->Draw();
    
    hs[i]->GetXaxis()->CenterTitle();
    hs[i]->GetXaxis()->SetTitle( axis_label[fl_xaxis] );
    if( i==0 ) leg->Draw();
  }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  c1->Update();
  if( fl_save ){
    c1->Print( Form("pic/col_var_1d_x%d_norm%d.eps",  fl_xaxis, fl_scale) );
    c1->Print( Form("pic/col_var_1d_x%d_norm%d.root", fl_xaxis, fl_scale) );
  }
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  
  return 0;
}
