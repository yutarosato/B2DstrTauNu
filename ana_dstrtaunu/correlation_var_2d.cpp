#include "draws_.h"

const Char_t*  tname       = "h15";
const Bool_t   fl_message  = true;
const Bool_t   fl_save     = true; // outfile.eps and outfile.root

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
				     70, 30,
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
  Style(10);
  gROOT->SetBatch(true); // tmpppppp

  if( app.Argc()!=3 ) std::cerr << "wrong input" << std::endl
				<< " Usage : "   << app.Argv(0)
				<< " (int)fl_xaxis (int)fl_yaxis" << std::endl, abort();
  Int_t fl_xaxis  = atoi(app.Argv(1));
  Int_t fl_yaxis  = atoi(app.Argv(2));
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* chain = new TChain(tname);
  for( Int_t i=0; i<nfile; i++ ) std::cout << Form("infile%d : ", i)
					   << chain->Add( infile[i] )
					   << " files"
					   << std::endl;

  std::cout << chain->GetEntries()  << " entries, "
	    << std::endl;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas*  c1 = Canvas( "c1", "c1", 3, 2 );
  TH2D**    hc = new TH2D*[nctgry];
  for( Int_t i=0; i<nctgry; i++ ){
    hc[i] = new TH2D( Form("hc_%d",i), Form("%s",label[i]),
		      xbin[fl_xaxis], xmin[fl_xaxis], xmax[fl_xaxis],
		      xbin[fl_yaxis], xmin[fl_yaxis], xmax[fl_yaxis] );
    hc[i]->GetXaxis()->CenterTitle();
    hc[i]->GetXaxis()->SetTitle( axis_label[fl_xaxis] );
    hc[i]->GetYaxis()->CenterTitle();
    hc[i]->GetYaxis()->SetTitle( axis_label[fl_yaxis] );
  }
  std::stringstream sTmp;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  TText* tex = new TText();
  tex->SetTextColor(3);
  tex->SetTextSize(0.05);
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  for( Int_t i=0; i<nctgry; i++ ){
    sTmp.str("");
    sTmp.clear();
    sTmp << "1";
    if( fl_cut_dmass  ) sTmp << " && (" << makeCut_dmass().c_str()  << ")";
    if( fl_cut_deltam ) sTmp << " && (" << makeCut_deltam().c_str() << ")";
    chain->Project( Form("hc_%d",i), Form("%s:%s", axis_name[fl_yaxis], axis_name[fl_xaxis]), Form("(%s)&&(%s)&&(%s)&&(%s)", makeCut_rem().c_str(), sTmp.str().c_str(), c_type[i], c_common) );
    
    if( fl_message ){
      std::cout << std::setw(10) << std::right << axis_name[fl_xaxis]
		<< std::setw(10) << std::right << axis_name[fl_yaxis]
		<< std::setw(20) << std::right << label[i]
		<< " : "
		<< std::setw(20) << std::right << hc[i]->GetEntries()
		<< std::endl;
    }
    c1->cd(i+1);
    hc[i]->Draw("COLZ");
    tex->DrawTextNDC( 0.2,0.705, Form("correlation factor = %.3f",hc[i]->GetCorrelationFactor()) );
  }
  
  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  c1->Update();
  if( fl_save ){
    c1->Print( Form("pic/col_var_2d_x%d_y%d.eps",  fl_xaxis, fl_yaxis) );
    c1->Print( Form("pic/col_var_2d_x%d_y%d.root", fl_xaxis, fl_yaxis) );
  }
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  
  return 0;
}
