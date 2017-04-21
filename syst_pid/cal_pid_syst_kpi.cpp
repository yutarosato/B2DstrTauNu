#include "draws_.h"
#include "draws_syst.h"

Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(!true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetOptStat(0);

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c = new TChain("h17");
  std::cout << c->Add("~/dstrtaunu/modules/dstrtaunu/hbk_single/store/hbk15/through_cut/gMC_*.root" ) << " files, ";
  std::cout << c->GetEntries() << " entries -> ";
  //const TCut cut = "-10<cosdl1 && cosdl1<5 && l1pid>0.90";
  const TCut cut = "-10<cosdl1 && cosdl1<5 && self==2";
  TTree* tree = new TTree();
  tree = c->CopyTree( cut );
  std::cout << tree->GetEntries() << " entries" << std::endl;

  //++++++++++calculation of systematic error of pid ++++++++++++++++++++++++++++++
  KID_eff_06**** kid_syst  = new KID_eff_06***[nsvd]; // [svd1,svd2][e,m][modes]
  //KID_eff_06**** piid_syst = new KID_eff_06***[nsvd]; // [svd1,svd2][e,m][modes]
  for( Int_t isvd=0; isvd<nsvd; isvd++ ){
    kid_syst [isvd] = new KID_eff_06**[nlep];
    //piid_syst[isvd] = new KID_eff_06**[nlep];
    for( Int_t ilep=0; ilep<nlep; ilep++ ){
      kid_syst [isvd][ilep] = new KID_eff_06*[nd_dec];
      //piid_syst[isvd][ilep] = new KID_eff_06*[nd_dec];
      for( Int_t idec=0; idec<nd_dec; idec++ ){
	kid_syst [isvd][ilep][idec] = new KID_eff_06();
	//piid_syst[isvd][ilep][idec] = new KID_eff_06();
	if( isvd==0 ){ // svd1
	  kid_syst [isvd][ilep][idec]->init (0.10, 1, Form(  "syst_k_%d_%d_%d",isvd,ilep,idec), "codes/table/kideff-2006-svd1-all_caseA.dat"  );
	  //piid_syst[isvd][ilep][idec]->init (0.40, 3, Form( "syst_pi_%d_%d_%d",isvd,ilep,idec), "codes/table/kideff-2006-svd1-all_caseA.dat"  );
	}else if( isvd==1 ){ // svd2
	  kid_syst [isvd][ilep][idec]->init (0.10, 1, Form( "syst_k_%d_%d_%d",isvd,ilep,idec), "codes/table/kideff-2010_caseB.dat"           );
	  //piid_syst[isvd][ilep][idec]->init (0.40, 3, Form("syst_pi_%d_%d_%d",isvd,ilep,idec), "codes/table/kideff-2010_caseB.dat"           );
	}
      }
    }
  }

  // +++++++++++++++++++++++ addtrack  ++++++++++++++++++++++++++++++++
  Double_t cnt          [nlep][nd_dec] = {0}; //            [e,m,l][modes]
  Double_t cnt_svd[nsvd][nlep][nd_dec] = {0}; // [svd1,svd2][e,m,l][modes]
  Double_t cnt_tot      [nlep]         = {0}; //            [e,m,l]
  
  Int_t nentries = (Int_t)tree->GetEntries();

  for( Int_t m=0; m<nentries; m++ ){
    tree->GetEntry(m);
    
    Int_t rm_l   = (Int_t) tree->GetLeaf( "rm_l1"  )->GetValue();
    Int_t rm_d   = (Int_t) tree->GetLeaf( "rm_d1"  )->GetValue();
    Int_t exprun = (Int_t) tree->GetLeaf( "exprun" )->GetValue();

    Int_t fl_svd = -1;
    if( exprun < 30*10000 ) fl_svd = 0; // svd1
    else                    fl_svd = 1; // svd2
    
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
	if( fabs(tree->GetLeaf(Form("d1ch%drec",ich))->GetValue() ) != 321 ) continue;
	kid_syst[fl_svd][fl_lep][fl_dec]->addtrack( tree->GetLeaf( Form("d1ch%dp", ich))->GetValue(), tree->GetLeaf( Form("d1ch%dpc",ich))->GetValue() );
	kid_syst[fl_svd][     2][fl_dec]->addtrack( tree->GetLeaf( Form("d1ch%dp", ich))->GetValue(), tree->GetLeaf( Form("d1ch%dpc",ich))->GetValue() );
      }
      cnt            [fl_lep][fl_dec]++; 
      cnt            [     2][fl_dec]++;
      cnt_svd[fl_svd][fl_lep][fl_dec]++;
      cnt_svd[fl_svd][     2][fl_dec]++;
      cnt_tot        [fl_lep]++;
      cnt_tot        [     2]++;
  }

  // ++++++++++++++++ calculate systematic error +++++++++++++++++++++++++
  Double_t ratio [nsvd][nlep][nd_dec];
  Double_t ratioE[nsvd][nlep][nd_dec];

  for( Int_t isvd=0; isvd<nsvd; isvd++ ){
    for( Int_t ilep=0; ilep<nlep; ilep++ ){
      for( Int_t idec=0; idec<nd_dec; idec++ ){
	std::cout << Form( "[ (svd,lep)=(%d,%d) : ", isvd,ilep )
		  << std::setw(15) << std::right << d_dec_name[idec]          << " : "
		  << std::setw( 8) << std::right << cnt_svd[isvd][ilep][idec] << " events ] ";
	ratio  [isvd][ilep][idec] = 1.0;
	ratioE [isvd][ilep][idec] = 0.0;
	if( cnt_svd[isvd][ilep][idec] && kid_syst[isvd][ilep][idec]->n_goodtrack() ){
	  kid_syst[isvd][ilep][idec]->calculate(&ratio[isvd][ilep][idec],&ratioE[isvd][ilep][idec]);
	  kid_syst[isvd][ilep][idec]->dump();
	}else{
	  std::cout << std::endl;
	}
      }
    }
  }

  // ++++++++++++++++ make plots +++++++++++++++++++++++++
  TH1D*** hist  = makeHist( "kpi", 100, 0, 100, nsvd, nlep); // [svd][lep]
  for( Int_t isvd=0; isvd<nsvd; isvd++ ){
    for( Int_t ilep=0; ilep<nlep; ilep++ ){
      for( Int_t idec=0; idec<nd_dec; idec++ ){
	((TAxis*)hist[isvd][ilep]->GetXaxis())->SetBinLabel( idec+1, d_dec_name[idec] );
	hist[isvd][ilep]->SetBinContent( idec+1, ratio [isvd][ilep][idec] );
	hist[isvd][ilep]->SetBinError  ( idec+1, ratioE[isvd][ilep][idec] );
      }
      hist[isvd][ilep]->SetMarkerColor(ilep+2);
      hist[isvd][ilep]->SetLineColor  (ilep+2);
      if( ilep==2 ){
	hist[isvd][ilep]->SetMarkerStyle(1);
	hist[isvd][ilep]->SetMarkerColor(9);
	hist[isvd][ilep]->SetLineColor  (9);
	hist[isvd][ilep]->SetFillColor(9);
      }
      hist[isvd][ilep]->SetMaximum(1.05);
      hist[isvd][ilep]->SetMinimum(0.95);
      hist[isvd][ilep]->LabelsDeflate("X");
      hist[isvd][ilep]->LabelsOption ("v");
      hist[isvd][ilep]->SetYTitle("dt/mc [%]");
    }
  }

  // ++++++++++++++++ make draw +++++++++++++++++++++++++
  TLegend* leg  = new TLegend( 0.80,0.80,0.99,0.99 );
  leg->AddEntry( hist[0][0], "e",   "P" );
  leg->AddEntry( hist[0][1], "#mu", "P" );
  leg->AddEntry( hist[0][2], "l",   "F" );
  
  // ++++++++++++++++ make draw +++++++++++++++++++++++++
  TCanvas* can = Canvas("can", "can", 1, 2 );
  can->Draw();
  can->cd(1);
  can->cd(1)->SetGridy();
  hist[1][2]->DrawCopy("E2");
  hist[1][1]->DrawCopy("same");
  hist[1][0]->DrawCopy("same");
  leg->Draw();

  // ++++++++++++++++ multiple Kaon  +++++++++++++++++++++++++  
  for( Int_t isvd=0; isvd<nsvd; isvd++ ){
    for( Int_t ilep=0; ilep<nlep; ilep++ ){
      for( Int_t idec=0; idec<nd_dec; idec++ ){
	ratio [isvd][ilep][idec] = pow( ratio[isvd][ilep][idec], d_dec_K[idec] );
	ratioE[isvd][ilep][idec] = d_dec_K[idec]*ratioE[isvd][ilep][idec];
	hist[isvd][ilep]->SetBinContent( idec+1, ratio [isvd][ilep][idec] );
	hist[isvd][ilep]->SetBinError  ( idec+1, ratioE[isvd][ilep][idec] );
      }
    }
  }

  // ++++++++++++++++ make draw +++++++++++++++++++++++++
  can->cd(2);
  can->cd(2)->SetGridy();
  hist[1][2]->Draw("E2");
  hist[1][1]->Draw("same");
  hist[1][0]->Draw("same");

  // ++++++++ log output ++++++++++++++++++++++
  std::cout << "++++++++++++++++++++++++++++++++++++++ logoutput ++++++++++++++++++++++++++++++++++" << std::endl
	    << Form("Double_t eff_corr_kpi [%d][%d] = {0}; // [e,m,l][ddec]", nlep, nd_dec) << std::endl
	    << Form("Double_t eff_corr_kpiE[%d][%d] = {0}; // [e,m,l][ddec]", nlep, nd_dec) << std::endl;
  for( Int_t ilep=0; ilep<nlep; ilep++ ){
    for( Int_t idec=0; idec<nd_dec; idec++ ){
      std::cout << Form( "eff_corr_kpi [%d][%2d] = %f; ", ilep,idec, ratio [1][ilep][idec] )
		<< Form( "eff_corr_kpiE[%d][%2d] = %f;",  ilep,idec, ratioE[1][ilep][idec] )
		<< std::endl;
    }
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
  TFile outfile( "pic/syst_kpi.root", "RECREATE" );
  can->Write();
  for( Int_t isvd=0; isvd<nsvd; isvd++ ){
    for( Int_t ilep=0; ilep<nlep; ilep++ ){
      hist[isvd][ilep]->Write(); // saved histograms include multiple Kaon correction.
    }
  }
  outfile.Close();
  can->Print( "pic/syst_kpi.eps" ); 

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

