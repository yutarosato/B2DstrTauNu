#include "draws_.h"
#include "draws_syst.h"

const Int_t    fl_mode = 2; // 1(signal lepton), 2(normalization lepton)
const Double_t lepid   = 0.10;

Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetOptStat(0);

  if     ( fl_mode==1 ) std::cout << "[   signal     lepton correction]"   << std::endl;
  else if( fl_mode==2 ) std::cout << "[normalization lepton correction]"   << std::endl;
  else                  std::cerr << "[ABORT] Wrong fl_mode : " << fl_mode << std::endl, abort();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c = new TChain("h15");
  std::cout << c->Add("~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpi/sigMC_*.root" ) << " files, ";
  std::cout << c->GetEntries() << " entries -> ";
  TTree* tree = new TTree();
  tree = c->CopyTree( "self==1" );
  std::cout << tree->GetEntries() << " entries" << std::endl;

  //++++++++++calculation of systematic error of pid ++++++++++++++++++++++++++++++
  const Int_t nexp = 4;
  LID_syst*** lid_syst = new LID_syst**[nexp]; // [exp][e,m]
  for( Int_t iexp=0; iexp<nexp; iexp++ ){
    lid_syst[iexp] = new LID_syst*[nlep-1];
    for( Int_t ilep=0; ilep<nlep-1; ilep++ ){
      lid_syst[iexp][ilep] = new LID_syst();
      if     ( ilep==0 && iexp==0 ) lid_syst[iexp][ilep]->init( lepid, 1, Form("syst_lep_%d_%d",iexp,ilep), "codes/table/eid_data-mc_corr_svd1.dat"                );
      else if( ilep==0 && iexp==1 ) lid_syst[iexp][ilep]->init( lepid, 1, Form("syst_lep_%d_%d",iexp,ilep), "codes/table/eid_data-mc_corr_exp31-65-caseB.dat"      );
      else if( ilep==1 && iexp==0 ) lid_syst[iexp][ilep]->init( lepid, 2, Form("syst_lep_%d_%d",iexp,ilep), "codes/table/muid_data-mc_corr_svd1.dat"               );
      else if( ilep==1 && iexp==1 ) lid_syst[iexp][ilep]->init( lepid, 2, Form("syst_lep_%d_%d",iexp,ilep), "codes/table/muid_data-mc_corr_exp31-39-45a-caseB.dat" );
      else if( ilep==1 && iexp==2 ) lid_syst[iexp][ilep]->init( lepid, 2, Form("syst_lep_%d_%d",iexp,ilep), "codes/table/muid_data-mc_corr_exp41-49-caseB.dat"     );
      else if( ilep==1 && iexp==3 ) lid_syst[iexp][ilep]->init( lepid, 2, Form("syst_lep_%d_%d",iexp,ilep), "codes/table/muid_data-mc_corr_exp51-65-caseB.dat"     );
    }
  }

  // +++++++++++++++++++++++ add track ++++++++++++++++++++++++++++++++
  Double_t cnt    [nexp][nlep-1]={0}; // [exp][e,m]
  Double_t cnt_tot      [nlep-1]={0}; //      [e,m]
  Int_t nentries = (Int_t)tree->GetEntries();
  for( Int_t m=0; m<nentries; m++ ){
    tree->GetEntry(m);
    Int_t rm_l;
    Double_t lep_p, lep_c;
    if( ((Int_t) tree->GetLeaf( "l1self" )->GetValue()) == fl_mode ){
      rm_l  = (Int_t   ) tree->GetLeaf( "rm_l1" )->GetValue();
      lep_p = (Double_t) tree->GetLeaf( "l1p"   )->GetValue();
      lep_c = (Double_t) tree->GetLeaf( "l1pc"  )->GetValue();
    }else if( ((Int_t) tree->GetLeaf( "l2self" )->GetValue()) == fl_mode ){
      rm_l  = (Int_t   ) tree->GetLeaf( "rm_l2" )->GetValue();
      lep_p = (Double_t) tree->GetLeaf( "l2p"   )->GetValue();
      lep_c = (Double_t) tree->GetLeaf( "l2pc"  )->GetValue();
    }else{
      continue;
    }

    Int_t exprun = (Int_t) tree->GetLeaf( "exprun" )->GetValue();

    Int_t fl_lep = -1;
    if     ( rm_l==10 ) fl_lep = 0; // e
    else if( rm_l== 1 ) fl_lep = 1; // mu
    else std::cerr << "[ABORT] Wrong lepton flavor : " << rm_l << std::endl, abort();

    Int_t fl_exp = -1;
    if( rm_l==10 ){ // electron
      if  ( exprun < 30*10000 ) fl_exp = 0;
      else                      fl_exp = 1;
    }else if( rm_l==1 ){ // muon
      if     ( exprun < 30*10000                            ) fl_exp = 0;
      else if( exprun < 40*10000                            ) fl_exp = 1;
      else if( exprun > 45*10000 && exprun < 45*10000 + 221 ) fl_exp = 1;
      else if( exprun < 50*10000                            ) fl_exp = 2;
      else                                                    fl_exp = 3;
    }
    lid_syst[fl_exp][fl_lep]->addtrack( lep_p, lep_c );
    cnt     [fl_exp][fl_lep]++;
    cnt_tot         [fl_lep]++;
  }

  // ++++++++++++++++ calculate systematic error +++++++++++++++++++++++++
  Double_t ratio [nexp][nlep-1];
  Double_t ratioE[nexp][nlep-1];

  for( Int_t iexp=0; iexp<nexp; iexp++ ){  
    for( Int_t ilep=0; ilep<nlep-1; ilep++ ){
      std::cout << Form( "[ (exp,lep)=(%d,%d) : ", iexp,ilep )
		<< std::setw( 8) << std::right << cnt[iexp][ilep] << " events ] ";
      ratio  [iexp][ilep] = 1.0;
      ratioE [iexp][ilep] = 0.0;
      if( cnt[iexp][ilep] && lid_syst[iexp][ilep]->n_goodtrack() ){
	lid_syst[iexp][ilep]->calculate(&ratio[iexp][ilep],&ratioE[iexp][ilep]);
	lid_syst[iexp][ilep]->dump();
      }else{
	std::cout << std::endl;
      }
    }
  }
  
  // ++++++++++++++++ make plots +++++++++++++++++++++++++
  TH1D* hist = new TH1D( "lep", "lep", 100, 0, 100 );
  ((TAxis*)hist->GetXaxis())->SetBinLabel( 1, "e (svd1)"     ); 
  ((TAxis*)hist->GetXaxis())->SetBinLabel( 2, "e (svd2)"     );
  ((TAxis*)hist->GetXaxis())->SetBinLabel( 3, "#mu (svd1)"   );
  ((TAxis*)hist->GetXaxis())->SetBinLabel( 4, "#mu (e31-39)" );
  ((TAxis*)hist->GetXaxis())->SetBinLabel( 5, "#mu (e41-49)" );
  ((TAxis*)hist->GetXaxis())->SetBinLabel( 6, "#mu (e51-65)" );

  hist->SetBinContent( 1, ratio [0][0] ); hist->SetBinError( 1, ratioE[0][0] );
  hist->SetBinContent( 2, ratio [1][0] ); hist->SetBinError( 2, ratioE[1][0] );
  hist->SetBinContent( 3, ratio [0][1] ); hist->SetBinError( 3, ratioE[0][1] );
  hist->SetBinContent( 4, ratio [1][1] ); hist->SetBinError( 4, ratioE[1][1] );
  hist->SetBinContent( 5, ratio [2][1] ); hist->SetBinError( 5, ratioE[2][1] );
  hist->SetBinContent( 6, ratio [3][1] ); hist->SetBinError( 6, ratioE[3][1] );
  hist->SetMaximum(1.05);
  hist->SetMinimum(0.95);
  hist->LabelsDeflate("X");
  hist->LabelsOption ("v");
  hist->SetYTitle("dt/mc [%]");

  // ++++++++++++++++ make draw +++++++++++++++++++++++++
  TCanvas* can = Canvas("can", "can", 1, 1 );
  can->Draw();
  can->cd(1)->SetGridy();
  hist->Draw();

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
  TFile outfile( "pic/syst_lep_double.root", "RECREATE" );
  can->Write();
  hist->Write();
  outfile.Close();
  can->Print( "pic/syst_lep_double.eps" ); 

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

