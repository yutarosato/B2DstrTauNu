void plot_compare_input(){
  const Int_t nc     = 2; // [setAA_CC, setDD_FF];
  const Int_t testno = 10;
    Int_t nvar = 0;
    if     ( testno==10 ) nvar = 2;
    else if( testno==11 ) nvar = 2;
    else if( testno==15 ) nvar = 3;
    else if( testno==19 ) nvar = 1;
    else if( testno==20 ) nvar = 1;
    else if( testno==21 ) nvar = 1;
    else if( testno==22 ) nvar = 1;
    else if( testno==23 ) nvar = 1;
    else if( testno==24 ) nvar = 1;
    else if( testno==25 ) nvar = 2;
    else if( testno==26 ) nvar = 2;
    else if( testno==27 ) nvar = 2;
    else if( testno==28 ) nvar = 2;
    else std::cerr << "[ABORT] Wrong testno" << std::endl, abort();



  TChain** c_sig = new TChain*[nc];
  TChain** c_nor = new TChain*[nc];
  for( Int_t ic=0; ic<nc; ic++ ){
    c_sig[ic] = new TChain("h15");
    c_nor[ic] = new TChain("h15");
  }

  std::cout << c_sig[0]->Add( Form("../pic/20140916/nb_setAA_CC/check/ck_mode0_test%d_nor_flsb1.root",testno) ) << std::endl;
  std::cout << c_sig[1]->Add( Form("../pic/20140916/nb_setDD_FF/check/ck_mode0_test%d_nor_flsb1.root",testno) ) << std::endl;
  std::cout << c_nor[0]->Add( Form("../pic/20140916/nb_setAA_CC/check/ck_mode0_test%d_nor_flsb0.root",testno) ) << std::endl;
  std::cout << c_nor[1]->Add( Form("../pic/20140916/nb_setDD_FF/check/ck_mode0_test%d_nor_flsb0.root",testno) ) << std::endl;

  for( Int_t ic=0; ic<nc; ic++ ){
    std::cout << c_sig[ic]->GetEntries() << std::endl;
    std::cout << c_nor[ic]->GetEntries() << std::endl;
  }

  Double_t* xmin = new Double_t[nvar];
  Double_t* xmax = new Double_t[nvar];
  for( Int_t j=0; j<nvar; j++ ){
    xmin[j] =  10000;
    xmax[j] = -10000;
  }
  for( Int_t ic=0; ic<nc; ic++ ){
    for( Int_t i=0; i<c_sig[ic]->GetEntries(); i++ ){
      c_sig[ic]->GetEntry(i);
      for( Int_t ivar=0; ivar<nvar; ivar++ ){
	if( c_sig[ic]->GetLeaf( Form("var%d",ivar) )->GetValue() == -999 ){ std::cout << "continue(sig, " << ivar << ")" << std::endl;  continue;}
	if( c_sig[ic]->GetLeaf( Form("var%d",ivar) )->GetValue() < xmin[ivar] ) xmin[ivar] = c_sig[ic]->GetLeaf( Form("var%d",ivar) )->GetValue();
	if( c_sig[ic]->GetLeaf( Form("var%d",ivar) )->GetValue() > xmax[ivar] ) xmax[ivar] = c_sig[ic]->GetLeaf( Form("var%d",ivar) )->GetValue();
      }
    }

    for( Int_t i=0; i<c_nor[ic]->GetEntries(); i++ ){
      c_nor[ic]->GetEntry(i);
      for( Int_t ivar=0; ivar<nvar; ivar++ ){
	if( c_nor[ic]->GetLeaf( Form("var%d",ivar) )->GetValue() == -999 ){ std::cout << "continue(nor, " << ivar << ")" << std::endl;  continue;}
	if( c_nor[ic]->GetLeaf( Form("var%d",ivar) )->GetValue() < xmin[ivar] ) xmin[ivar] = c_nor[ic]->GetLeaf( Form("var%d",ivar) )->GetValue();
	if( c_nor[ic]->GetLeaf( Form("var%d",ivar) )->GetValue() > xmax[ivar] ) xmax[ivar] = c_nor[ic]->GetLeaf( Form("var%d",ivar) )->GetValue();
      }
    }
  }

  TH1D** h_sig = new TH1D*[2*nvar];
  TH1D** h_nor = new TH1D*[2*nvar];

  for( Int_t ivar=0; ivar<2*nvar; ivar++ ){
    h_sig[ivar] = new TH1D( Form("h_sig%d",ivar+1), Form("h_sig%d (test%d, sig)",ivar+1,testno), 200, xmin[ivar%nvar], xmax[ivar%nvar] );
    h_nor[ivar] = new TH1D( Form("h_nor%d",ivar+1), Form("h_nor%d (test%d, nor)",ivar+1,testno), 200, xmin[ivar%nvar], xmax[ivar%nvar] );
  }

  for( Int_t ic=0; ic<nc; ic++ ){
    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      c_sig[ic]->Project( Form("h_sig%d",ic*nvar+ivar+1), Form("var%d",ivar) );
      c_nor[ic]->Project( Form("h_nor%d",ic*nvar+ivar+1), Form("var%d",ivar) );
      h_sig[ic*nvar+ivar]->SetLineColor(ic+1);
      h_nor[ic*nvar+ivar]->SetLineColor(ic+1);
    }
  }


  TCanvas* can = new TCanvas( "can", "can", 400*nvar, 800 );
  can->Divide(nvar,2);
  can->Draw();
  for( Int_t ic=0; ic<nc; ic++ ){
    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      can->cd(ivar+1);
      h_sig[ic*nvar+ivar]->Draw( ic ? "Esame" : "hist" );
      can->cd(ivar+nvar+1);
      h_nor[ic*nvar+ivar]->Draw( ic ? "Esame" : "hist" );
    }
  }

  return;

}
