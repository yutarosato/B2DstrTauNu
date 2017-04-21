#include "draws_.h"
#include "draws_fit_.h"

const Double_t xmin =  -1.0;
const Double_t xmax =  10.0;

const Int_t   npdf           = 3;
const Char_t* pdf_name[npdf] = { "sig", "nor", "dstst" };

const Double_t nsig_belle[3] = { 18.3569,
				 11.0363,
				 7.32066,
}; // [l, e, m]
const Double_t nnor_belle[3] = { 212.096,
				 115.191,
				 96.9051,
				 
};
const Double_t ndstst_belle[3] = { 324.807,
				   167.495,
				   157.312,
};

const Double_t ymin_sig  [3] = {  -40,  -50,  -50 };
const Double_t ymax_sig  [3] = {   70,   50,   50 };
const Double_t ymin_nor  [3] = {  160,   60,   30 };
const Double_t ymax_nor  [3] = {  280,  200,  180 };
const Double_t ymin_dstst[3] = {  250,  100,  100 };
const Double_t ymax_dstst[3] = {  400,  280,  240 };

TGraph* calAve( TGraphErrors* g ){
  Double_t ave  = 0.0;
  Double_t aveE = 0.0;
  for( Int_t ip=0; ip<g->GetN(); ip++ ){
    ave  += g->GetY()[ip] / pow( g->GetEY()[ip],2 );
    aveE +=           1.0 / pow( g->GetEY()[ip],2 );
  }

  ave  = ave/aveE;
  aveE = 1.0/sqrt(aveE);

  TGraph* f = new TGraph();
  f->SetPoint( 0, xmin, ave-aveE );
  f->SetPoint( 1, xmin, ave+aveE );
  f->SetPoint( 2, xmax, ave+aveE );
  f->SetPoint( 3, xmax, ave-aveE );
  std::cout << ave << " +- " << aveE << " : " << ave - aveE << " : " << ave + aveE << std::endl;
  f->SetFillColor(9);
  return f;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(!true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(11);
  sty->SetOptStat(0);
  sty->SetTitleSize(0.04,"xyz");
  sty->SetTitleOffset(1.6,"x");
  sty->SetTitleOffset(2.0,"y");
  sty->SetMarkerSize(1.5);

  if( !(app.Argc()==2) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0) << " (int)fl_lep" << std::endl
	      << "      * fl_lep : 10(e), 1(mu), 0(l)"
	      << std::endl, abort();
  Int_t fl_lep = atoi(app.Argv(1));
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TGraphErrors* nsig   = new TGraphErrors( Form("log/ensemble_lep%d.dat",fl_lep), "%lg %*lg %*lg %*lg %lg  %lg"                    );
  TGraphErrors* nnor   = new TGraphErrors( Form("log/ensemble_lep%d.dat",fl_lep), "%lg %*lg %*lg %*lg %*lg %*lg %lg %lg"           );
  TGraphErrors* ndstst = new TGraphErrors( Form("log/ensemble_lep%d.dat",fl_lep), "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg %lg" );
  nsig  ->Sort();
  nnor  ->Sort();
  ndstst->Sort();

  std::cout << "[Nsig  ]" << std::endl; nsig  ->Print();
  std::cout << "[Nnor  ]" << std::endl; nnor  ->Print();
  std::cout << "[Ndstst]" << std::endl; ndstst->Print();

  TGraph*  nsig_ave   = calAve( nsig   );
  TGraph*  nnor_ave   = calAve( nnor   );
  TGraph*  ndstst_ave = calAve( ndstst );
  std::cout << "[Ave-Nsig  ]" << std::endl; nsig_ave  ->Print();
  std::cout << "[Ave-Nnor  ]" << std::endl; nnor_ave  ->Print();
  std::cout << "[Ave-Ndstst]" << std::endl; ndstst_ave->Print();
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH2D* wakunsig   = new TH2D( "nsig",   "N_{sig}",   2, xmin, xmax, 2,  ymin_sig  [lep_index[fl_lep]], ymax_sig  [lep_index[fl_lep]] );
  TH2D* wakunnor   = new TH2D( "nnor",   "N_{nor}",   2, xmin, xmax, 2,  ymin_nor  [lep_index[fl_lep]], ymax_nor  [lep_index[fl_lep]] );
  TH2D* wakundstst = new TH2D( "ndstst", "N_{dstst}", 2, xmin, xmax, 2,  ymin_dstst[lep_index[fl_lep]], ymax_dstst[lep_index[fl_lep]] );
  wakunsig  ->SetXTitle("stream No");
  wakunnor  ->SetXTitle("stream No");
  wakundstst->SetXTitle("stream No");
  wakunsig  ->SetYTitle("N_{sig}"  );
  wakunnor  ->SetYTitle("N_{nor}"  );
  wakundstst->SetYTitle("N_{dstst}");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLine* mc_nsig   = new TLine( xmin,   nsig_belle[lep_index[fl_lep]], xmax,   nsig_belle[lep_index[fl_lep]] ); mc_nsig  ->SetLineColor(2); mc_nsig  ->SetLineWidth(3);
  TLine* mc_nnor   = new TLine( xmin,   nnor_belle[lep_index[fl_lep]], xmax,   nnor_belle[lep_index[fl_lep]] ); mc_nnor  ->SetLineColor(2); mc_nnor  ->SetLineWidth(3);
  TLine* mc_ndstst = new TLine( xmin, ndstst_belle[lep_index[fl_lep]], xmax, ndstst_belle[lep_index[fl_lep]] ); mc_ndstst->SetLineColor(2); mc_ndstst->SetLineWidth(3);

  TLegend* leg  = new TLegend( 0.50,0.72,0.80,0.92 );
  leg->AddEntry(  mc_nsig, "MC expectation", "L" );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 3, 1 );
  can->Draw();



  can->cd(1);
  wakunsig->Draw();
  nsig_ave->Draw("Fsame");
  mc_nsig ->Draw("Lsame");
  nsig    ->Draw("PEsame");
  leg->Draw();
  
  can->cd(2);
  wakunnor->Draw();
  nnor_ave->Draw("Fsame");
  mc_nnor ->Draw("Lsame");
  nnor    ->Draw("PEsame");

  can->cd(3);
  wakundstst->Draw();
  ndstst_ave->Draw("Fsame");
  mc_ndstst ->Draw("Lsame");
  ndstst    ->Draw("PEsame");

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Print( Form("pic/ensemble_lep%d.eps",fl_lep) );
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
