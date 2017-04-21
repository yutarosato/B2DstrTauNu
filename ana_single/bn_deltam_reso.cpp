#include "draws_.h"
#include "draws_single.h"
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c_mc = new TChain(treename);
  std::cout << "[MC] "
	    << c_mc->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut_FitRange/gMC_mixed*.root") << " files -> ";
  std::cout << c_mc->GetEntries() << " entries" << std::endl;
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D* hist_dm_pip     = new TH1D("h_pip",    "h_pip",     100, 0.140, 0.150 );
  TH1D* hist_dm_pip_org = new TH1D("h_pip_org","h_pip_org", 100, 0.140, 0.150 );
  TH1D* hist_dm_pi0     = new TH1D("h_pi0",    "h_pi0",     100, 0.135, 0.145 );

  c_mc->Project( "h_pip",     "dm1",           "abs(rm_d1lun)==421&&dst1self==1&&d1self==1&&abs(d1_m - 1.86484) < 0.015 && rm_d1==101" );
  c_mc->Project( "h_pip_org", "dst1_mor-d1_m", "abs(rm_d1lun)==421&&dst1self==1&&d1self==1&&abs(d1_m - 1.86484) < 0.015 && rm_d1==101" );
  c_mc->Project( "h_pi0",     "dm1",           "abs(rm_d1lun)==411&&dst1self==1&&d1self==1&&abs(d1_m - 1.86961) < 0.015 && rm_d1==201" );
  hist_dm_pip    ->SetXTitle("#Delta m [GeV]");
  hist_dm_pip_org->SetXTitle("#Delta m [GeV]");
  hist_dm_pi0    ->SetXTitle("#Delta m [GeV]");
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  const Int_t sel_fun = 20;
  TF1* func_dm_pip     = new TF1( "f_dm_pip",     make_func(sel_fun),0.140,0.150,n_fitfunc_par(sel_fun) );
  TF1* func_dm_pip_org = new TF1( "f_dm_pip_org", make_func(sel_fun),0.140,0.150,n_fitfunc_par(sel_fun) );
  TF1* func_dm_pi0     = new TF1( "f_dm_pi0",     make_func(sel_fun),0.135,0.145,n_fitfunc_par(sel_fun) );
  func_dm_pip    ->SetParNames  ("area",  "are_ratio", "mean", "sigma",  "sigma_ratio");
  func_dm_pip    ->SetParameters(  25,          0.8,   0.145,   0.0003,           5.0 );
  func_dm_pip_org->SetParNames  ("area",  "are_ratio", "mean", "sigma",  "sigma_ratio");
  func_dm_pip_org->SetParameters(  25,          0.8,   0.145,   0.0003,           5.0 );
  func_dm_pi0    ->SetParNames  ("area",  "are_ratio", "mean", "sigma",  "sigma_ratio");
  func_dm_pi0    ->SetParameters(  12,          0.8,   0.141,   0.0005,           2.5 );
  */
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  hist_dm_pip    ->SetLineColor(2);
  hist_dm_pip_org->SetLineColor(1);
  hist_dm_pip    ->SetLineColor(1);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can", "can", 2, 1 );
  can->cd(1);
  hist_dm_pip    ->DrawNormalized("Shist");
  hist_dm_pip_org->DrawNormalized("sameShist");
  /*
  hist_dm_pip->Draw();
  hist_dm_pip->Fit(func_dm_pip);
  hist_dm_pip_org->Draw("same");
  hist_dm_pip_org->Fit(func_dm_pip_org);
  */
  can->cd(2);
  hist_dm_pi0->DrawNormalized();
  /*
  hist_dm_pi0->Draw();
  hist_dm_pi0->Fit(func_dm_pi0);
  */
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  TLine* l_pip_L = new TLine( PDGmass::dstrp - PDGmass::d0-0.0025, 0.00, 
			      PDGmass::dstrp - PDGmass::d0-0.0025, 0.10 );
  TLine* l_pip_H = new TLine( PDGmass::dstrp - PDGmass::d0+0.0025, 0.00, 
			      PDGmass::dstrp - PDGmass::d0+0.0025, 0.10 );
  
  TLine* l_pi0_L = new TLine( PDGmass::dstrp - PDGmass::dp-0.0020, 0.00, 
			      PDGmass::dstrp - PDGmass::dp-0.0020, 0.04 );
  TLine* l_pi0_H = new TLine( PDGmass::dstrp - PDGmass::dp+0.0020, 0.00, 
			      PDGmass::dstrp - PDGmass::dp+0.0020, 0.04 );
  */
  TLine* l_pip_L = new TLine( 0.145383-0.0025, 0.00, 
			      0.145383-0.0025, 0.02 );
  TLine* l_pip_H = new TLine( 0.145383+0.0025, 0.00, 
			      0.145383+0.0025, 0.02 );
  
  TLine* l_pi0_L = new TLine( 0.140747-0.0020, 0.00, 
			      0.140747-0.0020, 0.01 );
  TLine* l_pi0_H = new TLine( 0.140747+0.0020, 0.00, 
			      0.140747+0.0020, 0.01 );

  l_pip_L->SetLineColor(3);
  l_pip_H->SetLineColor(3);
  l_pi0_L->SetLineColor(3);
  l_pi0_H->SetLineColor(3);
  can->cd(1);
  l_pip_L->Draw("Lsame");
  l_pip_H->Draw("Lsame");
  can->cd(2);
  l_pi0_L->Draw("Lsame");
  l_pi0_H->Draw("Lsame");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  std::cout << sqrt( func_dm_pip    ->GetParameter(1) * pow( func_dm_pip    ->GetParameter(3),2 ) + ( 1 - func_dm_pip    ->GetParameter(1) )* pow( func_dm_pip    ->GetParameter(3) * func_dm_pip    ->GetParameter(4) , 2 ) ) << std::endl;
  std::cout << sqrt( func_dm_pip_org->GetParameter(1) * pow( func_dm_pip_org->GetParameter(3),2 ) + ( 1 - func_dm_pip_org->GetParameter(1) )* pow( func_dm_pip_org->GetParameter(3) * func_dm_pip_org->GetParameter(4) , 2 ) ) << std::endl;
  std::cout << sqrt( func_dm_pi0    ->GetParameter(1) * pow( func_dm_pi0    ->GetParameter(3),2 ) + ( 1 - func_dm_pi0    ->GetParameter(1) )* pow( func_dm_pi0    ->GetParameter(3) * func_dm_pi0    ->GetParameter(4) , 2 ) ) << std::endl;
  */
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //can->Print( Form("pic/%s_%d_%d_%d.ps", brname,fl_dec,sel_fun_sig,sel_fun_bkg) ); 
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
