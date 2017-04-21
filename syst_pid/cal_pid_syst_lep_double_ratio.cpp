#include "draws_.h"
#include "draws_syst.h"

const Double_t lepid = 0.10;

const Int_t nctgry = 3; // sig, nor, ratio
const Int_t nexp   = 4;
const Int_t nbin   = 70;

void makePrint( TH1D* hist ){
  std::cout << "// [error scale down factor for signal lepton]" << std::endl;
  std::cout << "Double_t scale_down_factor[" << nbin << "] = { ";
  for( Int_t ibin=0; ibin<nbin; ibin++ ){
    if( hist->GetBinContent(ibin+1) > 0 ) std::cout << hist->GetBinContent(ibin+1);
    else                                  std::cout << 0.0;
    if( ibin!=nbin-1 ) std::cout << ", ";
    if( ibin%10==9 &&ibin!=nbin-1 ) std::cout << std::endl
					      << "                                   ";
      
  }
  std::cout << " };" << std::endl;

  std::cout << "// [error scale down factor for normalization lepton]" << std::endl;
  std::cout << "const double scale_down_factor[" << nbin << "] = { ";
  for( Int_t ibin=0; ibin<nbin; ibin++ ){
    if     ( hist->GetBinContent(ibin+1) < 0 ) std::cout << fabs(hist->GetBinContent(ibin+1));
    else if( hist->GetBinContent(ibin+1) ==1 ) std::cout << 1.0;
    else                                       std::cout << 0.0;
    if( ibin!=nbin-1 ) std::cout << ", ";
    if( ibin%10==9 &&ibin!=nbin-1 ) std::cout << std::endl
					      << "                                       ";
      
  }
  std::cout << " };" << std::endl;

  return;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetOptStat(0);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c = new TChain("h15");
  std::cout << c->Add("~/dstrtaunu/modules/dstrtaunu/hbk/sig_kpi/sigMC_*.root" ) << " files, ";
  std::cout << c->GetEntries() << " entries -> ";
  TTree* tree = new TTree();
  tree = c->CopyTree( "self==1" );
  std::cout << tree->GetEntries() << " entries" << std::endl;
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TH1D**** hist = new TH1D***[nctgry]; // [sig,nor,ratio][exp][e,m]
  for( Int_t ictgry=0; ictgry<nctgry; ictgry++ ){
    hist[ictgry] = new TH1D**[nexp];
    for( Int_t iexp=0; iexp<nexp; iexp++ ){
      hist[ictgry][iexp] = new TH1D*[nlep-1];
      for( Int_t ilep=0; ilep<nlep-1; ilep++ ){
	hist[ictgry][iexp][ilep] = new TH1D( Form("hist_%d_%d_%d",ictgry,iexp,ilep), Form("hist_%d_%d_%d",ictgry,iexp,ilep), nbin, 0, nbin );
      }
    }
  }

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
  for( Int_t m=0; m<(Int_t)tree->GetEntries(); m++ ){
    tree->GetEntry(m);
    Int_t    rm_l [2]; // sig, nor
    Double_t lep_p[2]; // sig, nor
    Double_t lep_c[2]; // sig, nor
    if( ((Int_t) tree->GetLeaf( "l1self" )->GetValue()) == 1 && ((Int_t) tree->GetLeaf( "l2self" )->GetValue()) == 2 ){
      rm_l [0] = (Int_t   ) tree->GetLeaf( "rm_l1" )->GetValue();
      lep_p[0] = (Double_t) tree->GetLeaf( "l1p"   )->GetValue();
      lep_c[0] = (Double_t) tree->GetLeaf( "l1pc"  )->GetValue();
      rm_l [1] = (Int_t   ) tree->GetLeaf( "rm_l2" )->GetValue();
      lep_p[1] = (Double_t) tree->GetLeaf( "l2p"   )->GetValue();
      lep_c[1] = (Double_t) tree->GetLeaf( "l2pc"  )->GetValue();
    }else if( ((Int_t) tree->GetLeaf( "l1self" )->GetValue()) == 2 && ((Int_t) tree->GetLeaf( "l2self" )->GetValue()) == 1 ){
      rm_l [1] = (Int_t   ) tree->GetLeaf( "rm_l1" )->GetValue();
      lep_p[1] = (Double_t) tree->GetLeaf( "l1p"   )->GetValue();
      lep_c[1] = (Double_t) tree->GetLeaf( "l1pc"  )->GetValue();
      rm_l [0] = (Int_t   ) tree->GetLeaf( "rm_l2" )->GetValue();
      lep_p[0] = (Double_t) tree->GetLeaf( "l2p"   )->GetValue();
      lep_c[0] = (Double_t) tree->GetLeaf( "l2pc"  )->GetValue();
    }else{
      continue;
    }
    
    Int_t exprun = (Int_t) tree->GetLeaf( "exprun" )->GetValue();
    
    Int_t fl_lep[nctgry-1];
    for( Int_t ictgry=0; ictgry<nctgry-1; ictgry++ ){
      if     ( rm_l[ictgry]==10 ) fl_lep[ictgry] = 0; // e
      else if( rm_l[ictgry]== 1 ) fl_lep[ictgry] = 1; // mu
      else std::cerr << "[ABORT] Wrong lepton flavor : " << rm_l[ictgry] << std::endl, abort();
      
      Int_t fl_exp[nctgry-1];
      if( rm_l[ictgry]==10 ){ // electron
	if  ( exprun < 30*10000 ) fl_exp[ictgry] = 0;
	else                      fl_exp[ictgry] = 1;
      }else if( rm_l[ictgry]==1 ){ // muon
	if     ( exprun < 30*10000                            ) fl_exp[ictgry] = 0;
	else if( exprun < 40*10000                            ) fl_exp[ictgry] = 1;
	else if( exprun > 45*10000 && exprun < 45*10000 + 221 ) fl_exp[ictgry] = 1;
	else if( exprun < 50*10000                            ) fl_exp[ictgry] = 2;
	else                                                    fl_exp[ictgry] = 3;
      }
      hist[ictgry][fl_exp[ictgry]][fl_lep[ictgry]]->Fill( lid_syst[fl_exp[ictgry]][fl_lep[ictgry]]->getindex( lep_p[ictgry], lep_c[ictgry] ) );
    }
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t iexp=0; iexp<nexp; iexp++ ){
    for( Int_t ilep=0; ilep<nlep-1; ilep++ ){
      if( hist[0][iexp][ilep]->GetEntries()==0 ) continue;
      hist[0][iexp][ilep]->Sumw2();
      hist[1][iexp][ilep]->Sumw2();
      hist[0][iexp][ilep]->Scale( 10000.0/hist[0][iexp][ilep]->Integral() );
      hist[1][iexp][ilep]->Scale( 10000.0/hist[1][iexp][ilep]->Integral() );
      for( Int_t ibin=0; ibin<nbin; ibin++ ){
	if( hist[0][iexp][ilep]->GetBinContent(ibin+1)==0 ) hist[2][iexp][ilep]->SetBinContent( ibin+1, 1.0 );
	else{
	  Double_t nsig = hist[0][iexp][ilep]->GetBinContent(ibin+1);
	  Double_t nnor = hist[1][iexp][ilep]->GetBinContent(ibin+1);
	  //Double_t r    =  fabs(nsig-nnor); // for estimation of duplicated ratio
	  Double_t r = ( nsig > nnor ? (nsig-nnor)/nsig : (nsig-nnor)/nnor ); // positive(sig:0,nor:r), negative(sig:r,nor:0) : *(exception for r==1)
	  hist[2][iexp][ilep]->SetBinContent( ibin+1, r );
	}
      }
    }
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  
  TCanvas* can = Canvas("can", "can", 3, 2 );
  can->Draw();
  Int_t cnt_can = 1;
  for( Int_t iexp=0; iexp<nexp; iexp++ ){
    for( Int_t ilep=0; ilep<nlep-1; ilep++ ){
      if( hist[0][iexp][ilep]->GetEntries()==0 ) continue;
      can->cd(cnt_can++)->SetGridy();
      //for( Int_t ictgry=0; ictgry<nctgry;   ictgry++ ) std::cout << hist[ictgry][iexp][ilep]->Integral() << std::endl;
      /*
      for( Int_t ictgry=0; ictgry<nctgry-1; ictgry++ ){
	hist[ictgry][iexp][ilep]->SetLineColor  ( ictgry+2 );
	hist[ictgry][iexp][ilep]->SetMarkerColor( ictgry+2 );
	hist[ictgry][iexp][ilep]->Draw( ictgry ? "same" : "");	
      }
      */
      hist[2][iexp][ilep]->Draw();
    }
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // electron
  std::cout << "// [electron, svd1]" << std::endl;
  makePrint( hist[2][0][0] );
  std::cout << "// [electron, svd2]" << std::endl;
  makePrint( hist[2][1][0] );
  // muon
  std::cout << "// [muon, svd1]" << std::endl;
  makePrint( hist[2][0][1] );
  std::cout << "// [muon, svd2(e31-39&45a)]" << std::endl;
  makePrint( hist[2][1][1] ); 
  std::cout << "// [muon, svd2(e41-49 except 45a)]" << std::endl;
  makePrint( hist[2][2][1] );
  std::cout << "// [muon, svd2(e51-65)]" << std::endl;
  makePrint( hist[2][3][1] );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++    
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

