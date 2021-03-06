#include "draws_.h"
#include "draws_fit_.h"


const Bool_t fl_sm = true;

const Double_t xmin =  -1.0;
const Double_t xmax =  10.0;

//const Int_t   npdf           = 1;
//const Char_t* pdf_name[npdf] = { "sig" };
const Int_t   npdf           = 3;
const Char_t* pdf_name[npdf] = { "sig", "nor", "dstst" };

//const Double_t nsig_belle[3] = {  202.238,  116.415,   85.227 }; // [l, e, m]
//const Double_t nnor_belle[3] = { 2737.1,   1443.57,  1293.53  };
//const Double_t nsig_belle[3] = {  198.345,  114.311,   84.0347 }; // [l, e, m]
//const Double_t nnor_belle[3] = { 2686.83,  1417.27,  1269.56   };
const Double_t nsig_belle[3] = { nsig_nominal_exp[0],
				 nsig_nominal_exp[1],
				 nsig_nominal_exp[2]
}; // [l, e, m]
const Double_t nnor_belle[3] = { nnor_nominal_exp[0],
				 nnor_nominal_exp[1],
				 nnor_nominal_exp[2]
};

const Double_t ymin_sig[3] = {  100,   50,   20 };
const Double_t ymax_sig[3] = {  350,  180,  150 };
const Double_t ymin_nor[3] = { 2300, 1200, 1100 };
const Double_t ymax_nor[3] = { 3200, 1700, 1500 };

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
  TGraphErrors* rdstr = new TGraphErrors( Form("log/ensemble_lep%d.dat",fl_lep), "%lg %*lg %lg  %lg"                   );
  TGraphErrors* nsig  = new TGraphErrors( Form("log/ensemble_lep%d.dat",fl_lep), "%lg %*lg %*lg %*lg %lg  %lg"         );
  TGraphErrors* nnor  = new TGraphErrors( Form("log/ensemble_lep%d.dat",fl_lep), "%lg %*lg %*lg %*lg %*lg %*lg%lg %lg" );
  rdstr->Sort();
  nsig ->Sort();
  nnor ->Sort();

  std::cout << "[R(D*)]" << std::endl; rdstr->Print();
  std::cout << "[Nsig ]" << std::endl; nsig ->Print();
  std::cout << "[Nnor ]" << std::endl; nnor ->Print();

  TGraph* rdstr_ave = calAve( rdstr );
  TGraph*  nsig_ave = calAve( nsig  );
  TGraph*  nnor_ave = calAve( nnor  );
  std::cout << "[Ave-R(D*)]" << std::endl; rdstr_ave->Print();
  std::cout << "[Ave-Nsig ]" << std::endl; nsig_ave ->Print();
  std::cout << "[Ave-Nnor ]" << std::endl; nnor_ave ->Print();
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH2D* wakurdstr = new TH2D( "rdstr", "R(D*)",   2, xmin, xmax, 2,  0.0,  0.4 );
  TH2D* wakunsig  = new TH2D( "nsig",  "N_{sig}", 2, xmin, xmax, 2,  ymin_sig[lep_index[fl_lep]], ymax_sig[lep_index[fl_lep]] );
  TH2D* wakunnor  = new TH2D( "nnor",  "N_{nor}", 2, xmin, xmax, 2,  ymin_nor[lep_index[fl_lep]], ymax_nor[lep_index[fl_lep]] );
  wakurdstr->SetXTitle("stream No");
  wakunsig ->SetXTitle("stream No");
  wakunnor ->SetXTitle("stream No");
  wakurdstr->SetYTitle("R(D*)"  );
  wakunsig ->SetYTitle("N_{sig}");
  wakunnor ->SetYTitle("N_{nor}");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLine* sm_rdstr = new TLine( xmin, 0.2520,                        xmax, 0.2520                        ); sm_rdstr->SetLineColor(2); sm_rdstr->SetLineWidth(3);
  TLine* mc_rdstr = new TLine( xmin, 0.2896,                        xmax, 0.2896                        ); mc_rdstr->SetLineColor(3); mc_rdstr->SetLineWidth(3);
  TLine* sm_nsig  = new TLine( xmin, (0.2520/0.2896)*nsig_belle[lep_index[fl_lep]], xmax, (0.2520/0.2896)*nsig_belle[lep_index[fl_lep]] ); sm_nsig ->SetLineColor(2); sm_nsig ->SetLineWidth(3);
  TLine* mc_nsig  = new TLine( xmin, nsig_belle[lep_index[fl_lep]], xmax, nsig_belle[lep_index[fl_lep]] ); mc_nsig ->SetLineColor(3); mc_nsig ->SetLineWidth(3);
  TLine* mc_nnor  = new TLine( xmin, nnor_belle[lep_index[fl_lep]], xmax, nnor_belle[lep_index[fl_lep]] ); mc_nnor ->SetLineColor(3); mc_nnor ->SetLineWidth(3);

  TLegend* leg  = new TLegend( 0.50,0.72,0.80,0.92 );
  if( fl_sm ) leg->AddEntry(  sm_rdstr, "SM",       "L" );
  leg->AddEntry(  mc_rdstr, "Belle MC", "L" );
  leg->AddEntry( rdstr_ave, "Average",  "F" );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 3, 1 );
  can->Draw();

  can->cd(1);
  wakurdstr->Draw();
  rdstr_ave->Draw("Fsame");
  if( fl_sm ) sm_rdstr ->Draw("Lsame"); // SM value
  mc_rdstr ->Draw("Lsame"); // Belle MC value
  rdstr    ->Draw("PEsame");
  leg->Draw();

  /* MC expectation of R(D*) for each stream
  TGraph* mcexp = new TGraph();
  mcexp->SetPoint( mcexp->GetN(), 0, 0.306724 );
  mcexp->SetPoint( mcexp->GetN(), 1, 0.283519 );
  mcexp->SetPoint( mcexp->GetN(), 2, 0.268167 );
  mcexp->SetPoint( mcexp->GetN(), 3, 0.304950 );
  mcexp->SetPoint( mcexp->GetN(), 4, 0.282532 );
  mcexp->SetPoint( mcexp->GetN(), 5, 0.291839 );
  mcexp->SetMarkerStyle(24);
  mcexp->SetMarkerColor(5);
  mcexp->Draw("P");
  */
  
  can->cd(2);
  wakunsig->Draw();
  nsig_ave->Draw("Fsame");
  if( fl_sm ) sm_nsig ->Draw("Lsame"); // SM value
  mc_nsig ->Draw("Lsame");
  nsig    ->Draw("PEsame");
  
  can->cd(3);
  wakunnor->Draw();
  nnor_ave->Draw("Fsame");
  mc_nnor ->Draw("Lsame");
  nnor    ->Draw("PEsame");

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->Print( Form("pic/ensemble_lep%d.eps",fl_lep) );
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
