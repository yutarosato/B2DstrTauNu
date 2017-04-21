#include "draws_.h"
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

///* type-II 2HDM
const Int_t nfile = 5;
const Char_t* model      = "2HDMII";
const Char_t* param_name = "tan#beta/m_{H^{+}}";
const Char_t* param_unit = "[GeV^{-1}]";
const Double_t param  [nfile] = {  0.0,   0.3,   0.5,   0.7,  1.0  };
const Char_t*  tagdir [nfile] = { "0p0", "0p3", "0p5", "0p7","1p0" };
const Int_t    col    [nfile] = {    1,     3,     4,     2,    5  };
//*/
/* R2 LQ
const Int_t nfile = 5;
const Char_t* model      = "R2LQ";
const Char_t* param_name = "C_{T}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {  -0.150,      0.000,      0.180,      0.340,     0.400     };
const Char_t*  tagdir [nfile] = { "R2_m0p150", "R2_0p000", "R2_0p180", "R2_0p340","R2_0p400" };
const Int_t    col    [nfile] = {       3,          1,          4,          2,         5     };
*/
/* S1 LQ
const Int_t nfile = 5;
const Char_t* model      = "S1LQ";
const Char_t* param_name = "C_{T}";
const Char_t* param_unit = "";
const Double_t param  [nfile] = {  -0.150,      0.000,      0.180,      0.260,     0.400     };
const Char_t*  tagdir [nfile] = { "S1_m0p150", "S1_0p000", "S1_0p180", "S1_0p260","S1_0p400" };
const Int_t    col    [nfile] = {       3,          1,          4,          2,         5     };
*/
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
TChain** c = new TChain*[nfile];
const Char_t* indir = "/home/belle/syutaro/dstrtaunu/modules/np_dstrtaunu_gen/hbk/";
const Char_t* treename = "h37";
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
THStack* MakeHist( const Int_t xbin,   const Double_t xmin,  const Double_t xmax,
		   const Char_t* name, const Char_t* title,  const Char_t* axisname, const Char_t* brname,
		   const Char_t* selection ){
  THStack* mh = new THStack();
  mh->SetTitle( title );
  TH1D** hist = new TH1D*[nfile];
  for( Int_t ic=0; ic<nfile; ic++ ){
    hist[ic] = new TH1D( Form("%s_%.2f",name,param[ic]), title, xbin, xmin, xmax );
    c[ic]->Project( Form("%s_%.2f",name,param[ic]), brname, selection );
    hist[ic]->SetLineColor( col[ic] );
    hist[ic]->Scale(1.0/hist[ic]->Integral());
    hist[ic]->SetMinimum(0.0);
    mh->Add( hist[ic] );
  }
  Bool_t tmp = gROOT->IsBatch();

  gROOT->SetBatch(true);
  mh->Draw("nostack");
  mh->GetXaxis()->SetTitle(axisname);
  gROOT->SetBatch(tmp);
  return mh;
}
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetOptStat(0);

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  for( Int_t ic=0; ic<nfile; ic++ ){
    c[ic] = new TChain(treename);
    std::cout << param_name    << " = "
	      << std::setw( 7) << Form( "%.2f ",param[ic] )
	      << param_unit    << " : ";
    std::cout << std::setw( 5) << std::right << c[ic]->Add( Form("%s/%s/*set[A].root",indir, tagdir[ic]) ) << " files : ";
    std::cout << std::setw(10) << std::right << c[ic]->GetEntries()                             << " events" << std::endl;
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  std::cout << " calculation of q2, " << std::flush;
  // q2
  THStack* hist_q2_1 = MakeHist( 100, 2.0, 13.0, "q2_1", "q^{2} (B #rightarrow D #tau #nu)",   "q^{2} [GeV^{2}]", "q2", "(-1<dec_d && dec_d<2)" );
  THStack* hist_q2_2 = MakeHist( 100, 2.0, 13.0, "q2_2", "q^{2} (B #rightarrow D* #tau #nu)",  "q^{2} [GeV^{2}]", "q2", "( 1<dec_d && dec_d<7)" );

  std::cout << "angle, " << std::flush;
  // angle for tau
  THStack* hist_cos_w_1 = MakeHist( 100, -1.0, 1.0, "cos_w_1", "cos#theta_{W} (B #rightarrow D #tau #nu)",  "cos#theta_{W}", "cos_w", "-1 < dec_d && dec_d < 2" );
  THStack* hist_cos_w_2 = MakeHist( 100, -1.0, 1.0, "cos_w_2", "cos#theta_{W} (B #rightarrow D* #tau #nu)", "cos#theta_{W}", "cos_w", " 1 < dec_d && dec_d < 7" );

  // angle for D
  THStack* hist_cos_d_1 = MakeHist( 100, -1.0, 1.0, "cos_d_1", "cos#theta_{D*} (D* #rightarrow D #pi)",    "cos#theta_{D*}", "cos_d", "dec_d==2 || dec_d==4 || dec_d==5" );
  THStack* hist_cos_d_2 = MakeHist( 100, -1.0, 1.0, "cos_d_2", "cos#theta_{D*} (D* #rightarrow D #gamma)", "cos#theta_{D*}", "cos_d", "dec_d==3 || dec_d==6"             );
  
  // angle for tau daughters
  THStack* hist_cos_t_1_1 = MakeHist( 100, -1.0, 1.0, "cos_t_1_1", "cos#theta_{#tau} (#tau #rightarrow l #nu #nu in B #rightarrow D #tau #nu)",   "cos#theta_{#tau}", "cos_t", "(-1<dec_d && dec_d<2) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_cos_t_1_2 = MakeHist( 100, -1.0, 1.0, "cos_t_1_2", "cos#theta_{#tau} (#tau #rightarrow l #nu #nu in B #rightarrow D* #tau #nu)",  "cos#theta_{#tau}", "cos_t", "( 1<dec_d && dec_d<7) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_cos_t_2_1 = MakeHist( 100, -1.0, 1.0, "cos_t_2_1", "cos#theta_{#tau} (#tau #rightarrow #pi #nu in B #rightarrow D #tau #nu)",     "cos#theta_{#tau}", "cos_t", "(-1<dec_d && dec_d<2) && (dec_tau==3)" );
  THStack* hist_cos_t_2_2 = MakeHist( 100, -1.0, 1.0, "cos_t_2_2", "cos#theta_{#tau} (#tau #rightarrow #pi #nu in B #rightarrow D* #tau #nu)",    "cos#theta_{#tau}", "cos_t", "( 1<dec_d && dec_d<7) && (dec_tau==3)" );
  THStack* hist_cos_t_3_1 = MakeHist( 100, -1.0, 1.0, "cos_t_3_1", "cos#theta_{#tau} (#tau #rightarrow #rho #nu in B #rightarrow D #tau #nu)",    "cos#theta_{#tau}", "cos_t", "(-1<dec_d && dec_d<2) && (dec_tau==4)" );
  THStack* hist_cos_t_3_2 = MakeHist( 100, -1.0, 1.0, "cos_t_3_2", "cos#theta_{#tau} (#tau #rightarrow #rho #nu in B #rightarrow D* #tau #nu)",   "cos#theta_{#tau}", "cos_t", "( 1<dec_d && dec_d<7) && (dec_tau==4)" );
  THStack* hist_cos_t_4_1 = MakeHist( 100, -1.0, 1.0, "cos_t_4_1", "cos#theta_{#tau} (#tau #rightarrow a_{1} #nu in B #rightarrow D #tau #nu)",   "cos#theta_{#tau}", "cos_t", "(-1<dec_d && dec_d<2) && (dec_tau==5)" );
  THStack* hist_cos_t_4_2 = MakeHist( 100, -1.0, 1.0, "cos_t_4_2", "cos#theta_{#tau} (#tau #rightarrow a_{1} #nu in B #rightarrow D* #tau #nu)",  "cos#theta_{#tau}", "cos_t", "( 1<dec_d && dec_d<7) && (dec_tau==5)" );

  std::cout << "tau momentum, " << std::flush;
  // tau daughter momentum (tau -> l nu nu)
  THStack* hist_pdau_lab_1_1 = MakeHist( 100, 0.0, 3.0, "pdau_lab_1_1", "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D #tau #nu)",  "p_{l} [GeV] in lab frame",       "p_dau_la", "(-1<dec_d && dec_d<2) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_pdau_lab_1_2 = MakeHist( 100, 0.0, 3.0, "pdau_lab_1_2", "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D* #tau #nu)", "p_{l} [GeV] in lab frame",       "p_dau_la", "( 1<dec_d && dec_d<7) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_pdau_b_1_1   = MakeHist( 100, 0.0, 2.5, "pdau_b_1_1",   "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D #tau #nu)",  "p_{l} [GeV] in B-rest frame",    "p_dau_b",  "(-1<dec_d && dec_d<2) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_pdau_b_1_2   = MakeHist( 100, 0.0, 2.5, "pdau_b_1_2",   "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D* #tau #nu)", "p_{l} [GeV] in B-rest frame",    "p_dau_b",  "( 1<dec_d && dec_d<7) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_pdau_w_1_1   = MakeHist( 100, 0.0, 2.0, "pdau_w_1_1",   "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D #tau #nu)",  "p_{l} [GeV] in W-rest frame",    "p_dau_w",  "(-1<dec_d && dec_d<2) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_pdau_w_1_2   = MakeHist( 100, 0.0, 2.0, "pdau_w_1_2",   "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D* #tau #nu)", "p_{l} [GeV] in W-rest frame",    "p_dau_w",  "( 1<dec_d && dec_d<7) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_pdau_tau_1_1 = MakeHist( 100, 0.0, 1.0, "pdau_tau_1_1", "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D #tau #nu)",  "p_{l} [GeV] in #tau-rest frame", "p_dau_ta", "(-1<dec_d && dec_d<2) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_pdau_tau_1_2 = MakeHist( 100, 0.0, 1.0, "pdau_tau_1_2", "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D* #tau #nu)", "p_{l} [GeV] in #tau-rest frame", "p_dau_ta", "( 1<dec_d && dec_d<7) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_pdau_cm_1_1  = MakeHist( 100, 0.0, 2.5, "pdau_cm_1_1",  "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D #tau #nu)",  "p_{l} [GeV] in cm frame",        "p_dau_cm", "(-1<dec_d && dec_d<2) && (dec_tau==1 || dec_tau==2)" );
  THStack* hist_pdau_cm_1_2  = MakeHist( 100, 0.0, 2.5, "pdau_cm_1_2",  "p_{l} (#tau #rightarrow l #nu #nu in B #rightarrow D* #tau #nu)", "p_{l} [GeV] in cm frame",        "p_dau_cm", "( 1<dec_d && dec_d<7) && (dec_tau==1 || dec_tau==2)" );

  // tau daughter momentum (tau -> pi nu)
  THStack* hist_pdau_lab_2_1 = MakeHist( 100, 0.0, 3.0, "pdau_lab_2_1", "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D #tau #nu)",  "p_{#pi} [GeV] in lab frame",       "p_dau_la", "(-1<dec_d && dec_d<2) && (dec_tau==3)" );
  THStack* hist_pdau_lab_2_2 = MakeHist( 100, 0.0, 3.0, "pdau_lab_2_2", "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D* #tau #nu)", "p_{#pi} [GeV] in lab frame",       "p_dau_la", "( 1<dec_d && dec_d<7) && (dec_tau==3)" );
  THStack* hist_pdau_b_2_1   = MakeHist( 100, 0.0, 2.5, "pdau_b_2_1",   "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D #tau #nu)",  "p_{#pi} [GeV] in B-rest frame",    "p_dau_b",  "(-1<dec_d && dec_d<2) && (dec_tau==3)" );
  THStack* hist_pdau_b_2_2   = MakeHist( 100, 0.0, 2.5, "pdau_b_2_2",   "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D* #tau #nu)", "p_{#pi} [GeV] in B-rest frame",    "p_dau_b",  "( 1<dec_d && dec_d<7) && (dec_tau==3)" );
  THStack* hist_pdau_w_2_1   = MakeHist( 100, 0.0, 2.0, "pdau_w_2_1",   "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D #tau #nu)",  "p_{#pi} [GeV] in W-rest frame",    "p_dau_w",  "(-1<dec_d && dec_d<2) && (dec_tau==3)" );
  THStack* hist_pdau_w_2_2   = MakeHist( 100, 0.0, 2.0, "pdau_w_2_2",   "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D* #tau #nu)", "p_{#pi} [GeV] in W-rest frame",    "p_dau_w",  "( 1<dec_d && dec_d<7) && (dec_tau==3)" );
  THStack* hist_pdau_tau_2_1 = MakeHist( 100, 0.0, 1.0, "pdau_tau_2_1", "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D #tau #nu)",  "p_{#pi} [GeV] in #tau-rest frame", "p_dau_ta", "(-1<dec_d && dec_d<2) && (dec_tau==3)" );
  THStack* hist_pdau_tau_2_2 = MakeHist( 100, 0.0, 1.0, "pdau_tau_2_2", "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D* #tau #nu)", "p_{#pi} [GeV] in #tau-rest frame", "p_dau_ta", "( 1<dec_d && dec_d<7) && (dec_tau==3)" );
  THStack* hist_pdau_cm_2_1  = MakeHist( 100, 0.0, 2.5, "pdau_cm_2_1",  "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D #tau #nu)",  "p_{#pi} [GeV] in cm frame",        "p_dau_cm", "(-1<dec_d && dec_d<2) && (dec_tau==3)" );
  THStack* hist_pdau_cm_2_2  = MakeHist( 100, 0.0, 2.5, "pdau_cm_2_2",  "p_{#pi} (#tau #rightarrow #pi #nu in B #rightarrow D* #tau #nu)", "p_{#pi} [GeV] in cm frame",        "p_dau_cm", "( 1<dec_d && dec_d<7) && (dec_tau==3)" );

  std::cout << "D(*) momentum" << std::endl;
  // D* momentum
  THStack* hist_pd_lab    = MakeHist( 100, 0.0, 3.5, "pd_lab",    "p_{D} (B #rightarrow D #tau #nu)",   "p_{D} [GeV] in lab frame",  "dstp",   "(-1<dec_d && dec_d<2)" );
  THStack* hist_pdstr_lab = MakeHist( 100, 0.0, 3.5, "pdstr_lab", "p_{D*} (B #rightarrow D* #tau #nu)", "p_{D*} [GeV] in lab frame", "dstp",   "( 1<dec_d && dec_d<7)" );
  THStack* hist_pd_cm     = MakeHist( 100, 0.0, 2.5, "pd_cm",     "p_{D} (B #rightarrow D #tau #nu)",   "p_{D} [GeV] in cm frame",   "dstpcm", "(-1<dec_d && dec_d<2)" );
  THStack* hist_pdstr_cm  = MakeHist( 100, 0.0, 2.5, "pdstr_cm",  "p_{D*} (B #rightarrow D* #tau #nu)", "p_{D*} [GeV] in cm frame",  "dstpcm", "( 1<dec_d && dec_d<7)" );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <CANVAS>
  TCanvas* can1 = Canvas( "can1","can1", 3,2 );
  TCanvas* can2 = Canvas( "can2","can2", 4,2 );
  TCanvas* can3 = Canvas( "can3","can3", 4,2 );
  TCanvas* can4 = Canvas( "can4","can4", 4,2 );
  TCanvas* can5 = Canvas( "can5","can5", 4,2 );
  TCanvas* can6 = Canvas( "can6","can6", 4,2 );
  TCanvas* can7 = Canvas( "can7","can7", 4,2 );
  can1->Draw();
  can2->Draw();
  can3->Draw();
  can4->Draw();
  can5->Draw();
  can6->Draw();
  can7->Draw();

  TLegend* leg = new TLegend( 0.40,0.72,0.85,0.94 );
  for( Int_t ic=0; ic<nfile; ic++ ) leg->AddEntry( (hist_cos_w_1->GetHists())->At(ic), Form("%s = %.2f %s", param_name,param[ic],param_unit), "L" );

  // angle (tau, W)
  can1->cd(1); hist_cos_w_1->Draw("nostack");
  can1->cd(4); hist_cos_w_2->Draw("nostack");
  can1->cd(2); hist_cos_d_1->Draw("nostack");
  can1->cd(5); hist_cos_d_2->Draw("nostack");
  can1->cd(3); hist_q2_1   ->Draw("nostack");
  can1->cd(6); hist_q2_2   ->Draw("nostack");

  // angle (tau daughter)
  can2->cd(1); hist_cos_t_1_1->Draw("nostack");
  can2->cd(2); hist_cos_t_1_2->Draw("nostack");
  can2->cd(3); hist_cos_t_2_1->Draw("nostack");
  can2->cd(4); hist_cos_t_2_2->Draw("nostack");
  can2->cd(5); hist_cos_t_3_1->Draw("nostack");
  can2->cd(6); hist_cos_t_3_2->Draw("nostack");
  can2->cd(7); hist_cos_t_4_1->Draw("nostack");
  can2->cd(8); hist_cos_t_4_2->Draw("nostack");

  // momentum (tau daughter : lepton), D tau nu
  can3->cd(1); hist_pdau_lab_1_1->Draw("nostack");
  can3->cd(2); hist_pdau_b_1_1  ->Draw("nostack");
  can3->cd(3); hist_pdau_w_1_1  ->Draw("nostack");
  can3->cd(4); hist_pdau_tau_1_1->Draw("nostack");
  can3->cd(5); hist_pdau_cm_1_1 ->Draw("nostack");

  // momentum (tau daughter : lepton), D* tau nu
  can4->cd(1); hist_pdau_lab_1_2->Draw("nostack");
  can4->cd(2); hist_pdau_b_1_2  ->Draw("nostack");
  can4->cd(3); hist_pdau_w_1_2  ->Draw("nostack");
  can4->cd(4); hist_pdau_tau_1_2->Draw("nostack");
  can4->cd(5); hist_pdau_cm_1_2 ->Draw("nostack");

  // momentum (tau daughter : pion), D tau nu
  can5->cd(1); hist_pdau_lab_2_1->Draw("nostack");
  can5->cd(2); hist_pdau_b_2_1  ->Draw("nostack");
  can5->cd(3); hist_pdau_w_2_1  ->Draw("nostack");
  can5->cd(4); hist_pdau_tau_2_1->Draw("nostack");
  can5->cd(5); hist_pdau_cm_2_1 ->Draw("nostack");

  // momentum (tau daughter : pion), D* tau nu
  can6->cd(1); hist_pdau_lab_2_2->Draw("nostack");
  can6->cd(2); hist_pdau_b_2_2  ->Draw("nostack");
  can6->cd(3); hist_pdau_w_2_2  ->Draw("nostack");
  can6->cd(4); hist_pdau_tau_2_2->Draw("nostack");
  can6->cd(5); hist_pdau_cm_2_2 ->Draw("nostack");

  can7->cd(1); hist_pd_lab   ->Draw("nostack");
  can7->cd(2); hist_pdstr_lab->Draw("nostack");
  can7->cd(3); hist_pd_cm    ->Draw("nostack");
  can7->cd(4); hist_pdstr_cm ->Draw("nostack");

  can1->cd(1); leg->Draw();
  can2->cd(1); leg->Draw();
  can3->cd(1); leg->Draw();
  can4->cd(1); leg->Draw();
  can5->cd(1); leg->Draw();
  can6->cd(1); leg->Draw();
  can7->cd(1); leg->Draw();

  can1->Print( Form("pic/plot_dist_gen_%s_1.eps",model) );
  can2->Print( Form("pic/plot_dist_gen_%s_2.eps",model) );
  can3->Print( Form("pic/plot_dist_gen_%s_3.eps",model) );
  can4->Print( Form("pic/plot_dist_gen_%s_4.eps",model) );
  can5->Print( Form("pic/plot_dist_gen_%s_5.eps",model) );
  can6->Print( Form("pic/plot_dist_gen_%s_6.eps",model) );
  can7->Print( Form("pic/plot_dist_gen_%s_7.eps",model) );
  
  can1->Print( Form("pic/plot_dist_gen_%s_1.ps",model) );
  can2->Print( Form("pic/plot_dist_gen_%s_2.ps",model) );
  can3->Print( Form("pic/plot_dist_gen_%s_3.ps",model) );
  can4->Print( Form("pic/plot_dist_gen_%s_4.ps",model) );
  can5->Print( Form("pic/plot_dist_gen_%s_5.ps",model) );
  can6->Print( Form("pic/plot_dist_gen_%s_6.ps",model) );
  can7->Print( Form("pic/plot_dist_gen_%s_7.ps",model) );
  system( Form("psmerge -oplot_dist_gen_%s.ps pic/plot_dist_gen_%s_?.ps && ps2pdf plot_dist_gen_%s.ps pic/plot_dist_gen_%s.pdf && rm -f plot_dist_gen_%s.ps && rm -f pic/plot_dist_gen_%s_?.ps",model,model,model,model,model,model) );  

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
