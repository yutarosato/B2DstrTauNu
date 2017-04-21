#include "draws_.h"
#include "draws_syst.h"

Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetOptStat(0);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c = new TChain("h17");
  std::cout << c->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/store/hbk15/through_cut/gMC_*.root" ) << " files, ";
  std::cout << c->GetEntries() << " entries -> ";
  const TCut cut = "-10<cosdl1 && cosdl1<5 && l1pid>0.90";
  TTree* tree = new TTree();
  tree = c->CopyTree( cut );
  std::cout << tree->GetEntries() << " entries" << std::endl;

  //++++++++++calculation of systematic error of pid ++++++++++++++++++++++++++++++
  Ks_eff*** ks_syst = new Ks_eff**[nlep]; // [e,m,l][modes]
    for( Int_t ilep=0; ilep<nlep; ilep++ ){
      ks_syst[ilep] = new Ks_eff*[nd_dec];
      for( Int_t idec=0; idec<nd_dec; idec++ ){
	ks_syst [ilep][idec] = new Ks_eff();
      }
    }

  // +++++++++++++++++++++++ add Ks ++++++++++++++++++++++++++++++++
  Double_t cnt    [nlep][nd_dec] = {0}; // [e,m,l][modes]
  Double_t cnt_tot[nlep]         = {0}; // [e,m,l]

  Int_t nentries = (Int_t)tree->GetEntries();
  for( Int_t m=0; m<nentries; m++ ){
    tree->GetEntry(m);

    Int_t rm_l   = (Int_t) tree->GetLeaf( "rm_l1"  )->GetValue();
    Int_t rm_d   = (Int_t) tree->GetLeaf( "rm_d1"  )->GetValue();
    Int_t exprun = (Int_t) tree->GetLeaf( "exprun" )->GetValue();

    Int_t fl_lep = -1;
    if     ( rm_l==10 ) fl_lep = 0; // e
    else if( rm_l== 1 ) fl_lep = 1; // mu
    else std::cerr << "[ABORT] Wrong lepton flavor : " << rm_l << std::endl, abort();
    
    
    Int_t fl_dec = -1;
    for( Int_t idec=0; idec<nd_dec; idec++ ){
      if( rm_d == d_dec[idec] ) fl_dec = idec;
    }
      if( fl_dec ==-1 ) std::cerr << "[ABORT] Wrong D decay : " << rm_d << std::endl, abort();

      for( int ich=0; ich<4; ich++ ){
	if( tree->GetLeaf(Form("d1ch%drec",ich))->GetValue() != 310 ) continue;
	ks_syst [fl_lep][fl_dec]->add( tree->GetLeaf( Form("d1ch%dp", ich))->GetValue(), tree->GetLeaf( Form("d1ch%dpc",ich))->GetValue() );
	ks_syst [     2][fl_dec]->add( tree->GetLeaf( Form("d1ch%dp", ich))->GetValue(), tree->GetLeaf( Form("d1ch%dpc",ich))->GetValue() );
      }
      cnt    [fl_lep][fl_dec]++;
      cnt    [     2][fl_dec]++;
      cnt_tot[fl_lep]++;
      cnt_tot[     2]++;
  }

  // ++++++++++++++++ calculate systematic error +++++++++++++++++++++++++
  Double_t ratio [nlep][nd_dec];
  Double_t ratioE[nlep][nd_dec];
  
  for( Int_t ilep=0; ilep<nlep; ilep++ ){
    for( Int_t idec=0; idec<nd_dec; idec++ ){
      ratio  [ilep][idec] = 1.0;
      ratioE [ilep][idec] = 0.0;
      if( cnt[ilep][idec] && ks_syst[ilep][idec]->get_totalNum() ){
	ratio [ilep][idec] = ks_syst[ilep][idec]->total_effFactor();
	ratioE[ilep][idec] = ks_syst[ilep][idec]->total_errFactor();
      }
      std::cout << Form( "[ (lep)=(%d) : ", ilep )
		<< std::setw(15) << std::right << d_dec_name  [idec] << " : "
		<< std::setw( 8) << std::right << cnt   [ilep][idec] << " events ] "
		<< std::setw(10) << std::right << ratio [ilep][idec] << " +- "
		<< std::setw(10) << std::right << ratioE[ilep][idec]
		<< std::endl;
    }
  }

  // ++++++++++++++++ make plots +++++++++++++++++++++++++
  TH1D** hist = makeHist( "ks", 100, 0, 100, nlep); // [lep]
  for( Int_t ilep=0; ilep<nlep; ilep++ ){
    for( Int_t idec=0; idec<nd_dec; idec++ ){
      ((TAxis*)hist[ilep]->GetXaxis())->SetBinLabel( idec+1, d_dec_name[idec] );
      hist[ilep]->SetBinContent( idec+1, ratio [ilep][idec] );
      hist[ilep]->SetBinError  ( idec+1, ratioE[ilep][idec] );
    }
    hist[ilep]->SetMarkerColor(ilep+2);
    hist[ilep]->SetLineColor  (ilep+2);
    if( ilep==2 ){
      hist[ilep]->SetMarkerStyle(1);
      hist[ilep]->SetMarkerColor(9);
      hist[ilep]->SetFillColor(9);
    }
    hist[ilep]->SetMaximum(1.05);
    hist[ilep]->SetMinimum(0.90);
    hist[ilep]->LabelsDeflate("X");
    hist[ilep]->LabelsOption ("v");
    hist[ilep]->SetYTitle("dt/mc [%]");
  }
  
  // ++++++++++++++++ make draw +++++++++++++++++++++++++
  TCanvas* can = Canvas("can", "can", 1, 1 );
  can->Draw();
  can->cd(1)->SetGridy();
  hist[2]->Draw("E2");
  hist[1]->Draw("same");
  hist[0]->Draw("same");

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
  TFile outfile( "pic/syst_ks.root", "RECREATE" );
  can->Write();
  for( Int_t ilep=0; ilep<nlep; ilep++ ) hist[ilep]->Write();

  outfile.Close();
  can->Print( "pic/syst_ks.eps" ); 

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
