void plot_compare_output(){
  const Int_t nc     = 3;
  const Int_t testno = 13;
  TChain** c = new TChain*[nc];
  for( Int_t ic=0; ic<nc; ic++ ) c[ic] = new TChain("h15");
  //std::cout << c[0]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_HH_boost_true/*.root",testno) ) << std::endl;
  //nstd::cout << c[1]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_CC_boost_true/*.root",testno) ) << std::endl;
  //std::cout << c[2]->Add( Form("hbk/hbk_mode0_test%d_nor_setDD_FF_boost_true/*.root",testno) ) << std::endl;


  //std::cout << c[0]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_HH_sig100_nor100/*.root",testno) ) << std::endl;
  //std::cout << c[1]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_HH_sig100_nor97/*.root",testno) ) << std::endl;
  //std::cout << c[2]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_HH_sig97_nor100/*.root",testno) ) << std::endl;
  //std::cout << c[1]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_HH_sig99_nor99/*.root",testno) ) << std::endl;
  //std::cout << c[2]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_HH_sig97_nor97/*.root",testno) ) << std::endl;

  std::cout << c[0]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_HH_sig100_nor99/*.root",testno) ) << std::endl;
  std::cout << c[1]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_CC_sig100_nor99/*.root",testno) ) << std::endl;
  std::cout << c[2]->Add( Form("hbk/hbk_mode0_test%d_nor_setDD_FF_sig100_nor99/*.root",testno) ) << std::endl;

  //std::cout << c[0]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_CC_sig100_nor97/*.root",testno) ) << std::endl;
  //std::cout << c[1]->Add( Form("hbk/hbk_mode0_test%d_nor_setDD_FF_sig100_nor97/*.root",testno) ) << std::endl;


  //std::cout << c[0]->Add( Form("hbk/hbk_mode0_test%d_nor_setDD_FF/*.root",testno) ) << std::endl;
  //std::cout << c[1]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_HH/*set?[GH]*.root",testno) ) << std::endl;

  //std::cout << c[0]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_CC/*setGG*.root",testno) ) << std::endl;
  //std::cout << c[1]->Add( Form("hbk/hbk_mode0_test%d_nor_setAA_CC/*setHH*.root",testno) ) << std::endl;

  for( Int_t ic=0; ic<nc; ic++ ) std::cout <<  c[ic]->GetEntries() << std::endl;

  TCanvas* can = new TCanvas( "can", "can", 1200, 1000 );
  can->Divide(2,2);
  can->Draw();

  TH1D** h_sig = new TH1D*[nc];
  TH1D** h_nor = new TH1D*[nc];
  for( Int_t ic=0; ic<nc; ic++ ){
    h_sig[ic] = new TH1D( Form("h_sig%d",ic+1), Form("h_sig%d (test%d)",ic+1,testno), 100, -1, 1 );
    h_nor[ic] = new TH1D( Form("h_nor%d",ic+1), Form("h_nor%d (test%d)",ic+1,testno), 100, -1, 1 );
    c[ic]->Project( Form("h_sig%d",ic+1), Form("nb_mode0_test%d_nor",testno), "self==1" );
    c[ic]->Project( Form("h_nor%d",ic+1), Form("nb_mode0_test%d_nor",testno), "self==2" );
    h_sig[ic]->SetLineColor(1.6*ic+1);
    h_nor[ic]->SetLineColor(1.6*ic+1);
  }

  can->cd(1); for( Int_t ic=0; ic<nc; ic++ ) h_sig[ic]->Draw( ic ? "Esame" : "hist" );
  can->cd(2); for( Int_t ic=0; ic<nc; ic++ ) h_nor[ic]->Draw( ic ? "Esame" : "hist" );
  can->cd(3)->SetLogy(1);
  can->cd(3); for( Int_t ic=0; ic<nc; ic++ ) h_sig[ic]->Draw( ic ? "Esame" : "hist" );
  can->cd(4)->SetLogy(1);
  can->cd(4); for( Int_t ic=0; ic<nc; ic++ ) h_nor[ic]->Draw( ic ? "Esame" : "hist" );

  return;
}
