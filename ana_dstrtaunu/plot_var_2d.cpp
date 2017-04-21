#include "draws_.h"

const Bool_t fl_message  = true;
const Bool_t fl_save     = true; // outfile.eps and outfile.root
//const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/nor_kpi/*setA.root";
const char* infile = "~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpi/*setA.root";
const char* tname  = "h15";

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
namespace Two_Dim_cosBDL{

  const Bool_t fl_cut_dmass  = true;
  const Bool_t fl_cut_deltam = true;
  const Char_t* c_ctgry = "dst1self!=0&&dst2self!=0&&d1self==1&&d2self==1&&l1self>0&&l2self>0&&(abs(evt_type)==rm_bb&&gm_dd==rm_dd) && l1self==1 && l2self==2"; // 1st(sig), 2nd(tag)
  
  const Int_t    nvar             = 5;
  const Char_t*  outname   [nvar] = {"cosBDL1","cosBDL2","eecl","mmiss","evis"};
  const Char_t*  axis_name [nvar] = {"cosdl1", "cosdl2", "eecl","mmiss","evis"};
  const Int_t    xbin      [nvar] = {      45,       30,     12,     30,    40};
  const Double_t xmin      [nvar] = {     -20,       -5,    0.0,    0.0,   4.0};
  const Double_t xmax      [nvar] = {      10,        5,    0.6,    6.0,  12.0};
  const Char_t*  axis_label[nvar] = {"cos#theta_{BDl1}","cos#theta_{BDl2}","E_{ECL} [GeV]","M_{miss} [GeV]","E_{vis} [GeV]"};
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  using namespace Two_Dim_cosBDL;
  TApplication app( "app", &argc, argv );
  Style(10);

  TChain* chain = new TChain(tname);
  std::cout << "[REC] "
	    << chain->Add( infile ) << " files, ";
  std::cout << chain->GetEntries()  << " entries"
	    << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas** c1 = new TCanvas*[6];
  for( int v=0; v<6; v++ ) c1[v] = Canvas( Form("c1_%d",v), Form("c1_%d", v), 4, 3 );

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH2D***** hc = makeHist ( "hc", xbin, xmin, xmax, xbin, xmin, xmax, 2,3,nvar,nvar ); // [BB][DD][nvar][nvar]
  std::stringstream sTmp;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  for( Int_t i=0; i<2; i++ ){ // begin loop [B0B0 / B+B-]
    for( Int_t j=0; j<3; j++ ){ // begin loop [DD / D*D / D*D*]
      Int_t cnt_canvas = 1;
      for( Int_t k1=0; k1<nvar; k1++ ){ // begin loop [nvar]
	for( Int_t k2=0; k2<nvar; k2++ ){ // begin loop [nvar]
	  if( k1>=k2 ) continue;
	  sTmp.str("");
	  sTmp.clear();
	  sTmp << "1";
	  if( fl_cut_dmass  ) sTmp << " && (" << makeCut_dmass().c_str()  << ")";
	  if( fl_cut_deltam ) sTmp << " && (" << makeCut_deltam().c_str() << ")";
	  sTmp << " && "  << makeCategory_recBBDD( i, j ).c_str();
	  sTmp << " && (" << c_ctgry << ")";
	  chain->Project( Form("hc_%d_%d_%d_%d",i,j,k1,k2), Form("%s:%s", axis_name[k2], axis_name[k1]), Form("(%s)&&(%s)", makeCut_rem().c_str(), sTmp.str().c_str()) );
	  c1[3*i+j]->cd( cnt_canvas++ );
	  hc[i][j][k1][k2]->SetTitle( Form("%s:%s (%s, %s)", axis_name[k1],axis_name[k2], ctgry_BB[i], ctgry_DD[j]) );
	  hc[i][j][k1][k2]->GetXaxis()->CenterTitle();
	  hc[i][j][k1][k2]->GetYaxis()->CenterTitle();
	  hc[i][j][k1][k2]->GetXaxis()->SetTitle(axis_label[k1]);	    
	  hc[i][j][k1][k2]->GetYaxis()->SetTitle(axis_label[k2]);
	  hc[i][j][k1][k2]->Draw("COLZ");
	} // end loop [nvar]
      } // end loop [nvar]
      c1[3*i+j]->Update();
      if( fl_save ){
	c1[3*i+j]->Print( Form("pic/plot_2d_%d.eps", 3*i+j)  );
	c1[3*i+j]->Print( Form("pic/plot_2d_%d.root",3*i+j)  );
      }
    } // end loop [DD / D*D / D*D*]
  } // end loop [B0B0 / B+B-]

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
