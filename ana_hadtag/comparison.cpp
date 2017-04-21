#include "draws_.h"
#include "draws_had_.h"

Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(0);
  sty->SetOptStat(0);
  sty->SetMarkerSize(0.4);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Read Data>
  Int_t fl_dlund = 421; // 411(D+), 421(D0)
  const Int_t nd = 2;
  const Char_t* treename = "h18";
  const Char_t* tag[nd+1] = {"DATA", "MC", "MC(true)"};
  const Double_t nstream[nd] = { 1.0, 6.0};

  const Char_t* infile[nd] = {"~/dstrtaunu/modules/dstrtaunu/hbk_hadtag/merge_cut/RD_*.root",
			      "~/dstrtaunu/modules/dstrtaunu/hbk_hadtag/merge_cut/gMC_*.root",
  };
  const Int_t col[nd+1] = {2,9,16};
  TChain** c = new TChain*[nd];
  for( Int_t id=0; id<nd; id++ ){
    c[id] = new TChain(treename);
    std::cout << "["
	      << std::setw(4) << std::right << tag[id] << "] "
	      << c[id]->Add(infile[id]) << " files, ";
    std::cout << c[id]->GetEntries()    << " events"
	      << std::endl;
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D** h_mbc  = new TH1D*[nd+1];
  TH1D** h_dm   = new TH1D*[nd+1];
  TH1D** h_eecl = new TH1D*[nd+1];
  TH1D** h_pdst = new TH1D*[nd+1];
  TH1D** h_mm   = new TH1D*[nd+1];
  TH1D** h_evis = new TH1D*[nd+1];
  TH1D** h_cos  = new TH1D*[nd+1];
  TH1D** h_acos = new TH1D*[nd+1];
  for( Int_t id=0; id<nd+1; id++ ){
    h_mbc [id] = new TH1D( Form("mbc_%d", id), Form("mbc_%d", id),  80,  5.22, 5.30 ); h_mbc [id]->Sumw2();
    
    if( fl_dlund==421 ) h_dm[id] = new TH1D( Form("dm_%d",  id), Form("dm_%d",  id), 40,  PDGmass::pip, 0.150 );
    else                h_dm[id] = new TH1D( Form("dm_%d",  id), Form("dm_%d",  id), 40,  PDGmass::pi0, 0.145 );
    h_dm  [id]->Sumw2(); 
    h_eecl[id] = new TH1D( Form("eecl_%d",id), Form("eecl_%d",id),  24,   0.0,  1.2 ); h_eecl[id]->Sumw2();
    h_pdst[id] = new TH1D( Form("pdst_%d",id), Form("pdst_%d",id),  30,   0.0,  3.0 ); h_pdst[id]->Sumw2();
    h_mm  [id] = new TH1D( Form("mm_%d",  id), Form("mm_%d",  id),  40,  -1.0,  1.0 ); h_mm  [id]->Sumw2();
    h_evis[id] = new TH1D( Form("evis_%d",id), Form("evis_%d",id),  40,   6.0, 12.0 ); h_evis[id]->Sumw2();
    h_cos [id] = new TH1D( Form("cos_%d", id), Form("cos_%d", id),  40,  -5.0,  3.0 ); h_cos [id]->Sumw2();
    h_acos[id] = new TH1D( Form("acos_%d",id), Form("acos_%d",id),  50,  -2.0,  2.0 ); h_acos[id]->Sumw2();

    if( id==0 ){
      Deco( h_mbc [id], 0, col[id], col[id] );
      Deco( h_dm  [id], 0, col[id], col[id] );
      Deco( h_eecl[id], 0, col[id], col[id] );
      Deco( h_pdst[id], 0, col[id], col[id] );
      Deco( h_mm  [id], 0, col[id], col[id] );
      Deco( h_evis[id], 0, col[id], col[id] );
      Deco( h_cos [id], 0, col[id], col[id] );
      Deco( h_acos[id], 0, col[id], col[id] );
    }else{
      Deco( h_mbc [id], 3, col[id], col[id] );
      Deco( h_dm  [id], 3, col[id], col[id] );
      Deco( h_eecl[id], 3, col[id], col[id] );
      Deco( h_pdst[id], 3, col[id], col[id] );
      Deco( h_mm  [id], 3, col[id], col[id] );
      Deco( h_evis[id], 3, col[id], col[id] );
      Deco( h_cos [id], 3, col[id], col[id] );
      Deco( h_acos[id], 3, col[id], col[id] );
    }
      
    h_mbc [id]->SetXTitle( "M_{bc} [GeV]"            );
    h_dm  [id]->SetXTitle( "#Delta m [GeV]"          );
    h_eecl[id]->SetXTitle( "E_{ECL} [GeV]"           );
    h_pdst[id]->SetXTitle( "p*_{D*} [GeV]"           );
    h_mm  [id]->SetXTitle( "M_{miss}^{2} [GeV^{2}]"  );
    h_evis[id]->SetXTitle( "E_{vis} [GeV]"           );
    h_cos [id]->SetXTitle( "cos#theta_{B-D*l}"       );
    h_acos[id]->SetXTitle( "atan(cos#theta_{B-D*l})" );
  }

  // <Event Loop>
  for( Int_t id=0; id<nd; id++ ){
    for( Int_t ievt=0; ievt<c[id]->GetEntries(); ievt++ ){
      c[id]->GetEntry(ievt);
      
      Double_t weight = 1.0;
      if( id==1 ){ // calculate weiht factor for MC
	Int_t    hush   = (Int_t)c[id]->GetLeaf("tbdecay"  )->GetValue();
	Double_t nb     =        c[id]->GetLeaf("tnboutde" )->GetValue();
	weight = tagcorr( hush, nb );
	weight /= nstream[id];
      }

      Double_t q2     =        c[id]->GetLeaf("q2rec"    )->GetValue();
      Int_t    d_lund = (Int_t)c[id]->GetLeaf("rm_d1lun" )->GetValue(); // 411(D+), 421(D0)
      Double_t mbc    =        c[id]->GetLeaf("tmbc"     )->GetValue();
      Double_t eecl   =        c[id]->GetLeaf("eecl"     )->GetValue();
      Double_t pdst   =        c[id]->GetLeaf("dst1pcm"  )->GetValue();
      Double_t cos    =        c[id]->GetLeaf("cosdl1"   )->GetValue();
      Double_t acos   = atan(cos);
      Double_t mm     =        c[id]->GetLeaf("mmiss2"   )->GetValue();
      mm              = pow(mm,3)/fabs(mm);
      Double_t evis   =        c[id]->GetLeaf("evis"     )->GetValue();
      Double_t dm     =        c[id]->GetLeaf("dm1"      )->GetValue();
      Int_t    tself  = (Int_t)c[id]->GetLeaf("tself"    )->GetValue();
      Int_t    self   = (Int_t)c[id]->GetLeaf("self"     )->GetValue();
      Int_t    l1self = (Int_t)c[id]->GetLeaf("l1self"   )->GetValue();
      Int_t    d1self = (Int_t)c[id]->GetLeaf("d1self"   )->GetValue();
      Int_t  dst1self = (Int_t)c[id]->GetLeaf("dst1self" )->GetValue();


      //if( !( c[id]->GetLeaf("rm_l1")->GetValue()==10 && c[id]->GetLeaf("l1p")->GetValue()>0.4 ) ) continue; // e
      //if( !( c[id]->GetLeaf("rm_l1")->GetValue()== 1 && c[id]->GetLeaf("l1p")->GetValue()>0.8 ) ) continue; // mu
      //if( c[id]->GetLeaf("rm_l1")->GetValue()==10 ) continue; // mu(electron veto)
      //if( c[id]->GetLeaf("rm_l1")->GetValue()== 1 ) continue; // e (  muon   veto)

      if( q2 > 3.0 ) continue;
      if( fl_dlund!=abs(d_lund) ) continue;
      h_dm[id]->Fill( dm, weight );
      if( id!=0 && dst1self==1 ) h_dm[id+1]->Fill( dm, weight );
      if( fl_dlund==421 && 0.0025 > fabs(dm - (PDGmass::d0 + PDGmass::pip)) ) continue;
      if( fl_dlund==411 && 0.0020 > fabs(dm - (PDGmass::dp + PDGmass::pi0)) ) continue;
      h_mbc [id]->Fill(  mbc, weight ); if( id!=0 && self==2 ) h_mbc [id+1]->Fill( mbc, weight );
      if( mbc  < 5.27 ) continue;
      if( eecl > 1.2  ) continue;
      h_pdst[id]->Fill( pdst, weight ); if( id!=0 && self==2 ) h_pdst[id+1]->Fill( pdst, weight );
      h_mm  [id]->Fill(   mm, weight ); if( id!=0 && self==2 ) h_mm  [id+1]->Fill(   mm, weight );
      h_evis[id]->Fill( evis, weight ); if( id!=0 && self==2 ) h_evis[id+1]->Fill( evis, weight );
      h_eecl[id]->Fill( eecl, weight ); if( id!=0 && self==2 ) h_eecl[id+1]->Fill( eecl, weight );
      h_cos [id]->Fill(  cos, weight ); if( id!=0 && self==2 ) h_cos [id+1]->Fill(  cos, weight );
      h_acos[id]->Fill( acos, weight ); if( id!=0 && self==2 ) h_acos[id+1]->Fill( acos, weight );
    }
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <Canvas>
  TCanvas* can = Canvas( "can", "can", 4, 2 );
  can->Draw();

  Double_t scale_factor = h_mm[0]->Integral()/h_mm[1]->Integral();
  for( Int_t id=1; id<nd+1; id++ ){
    h_pdst[id]->Scale( scale_factor );
    h_mm  [id]->Scale( scale_factor );
    h_evis[id]->Scale( scale_factor );
    h_cos [id]->Scale( scale_factor );
    h_acos[id]->Scale( scale_factor );
  }

  for( Int_t id=0; id<nd+1; id++ ){
    if( h_mbc [0]->GetMaximum() < h_mbc [id]->GetMaximum() ) h_mbc [0]->SetMaximum( 1.15*h_mbc [id]->GetMaximum() );
    if( h_dm  [0]->GetMaximum() < h_dm  [id]->GetMaximum() ) h_dm  [0]->SetMaximum( 1.15*h_dm  [id]->GetMaximum() );
    if( h_eecl[0]->GetMaximum() < h_eecl[id]->GetMaximum() ) h_eecl[0]->SetMaximum( 1.15*h_eecl[id]->GetMaximum() );
    if( h_pdst[0]->GetMaximum() < h_pdst[id]->GetMaximum() ) h_pdst[0]->SetMaximum( 1.15*h_pdst[id]->GetMaximum() );
    if( h_mm  [0]->GetMaximum() < h_mm  [id]->GetMaximum() ) h_mm  [0]->SetMaximum( 1.15*h_mm  [id]->GetMaximum() );
    if( h_evis[0]->GetMaximum() < h_evis[id]->GetMaximum() ) h_evis[0]->SetMaximum( 1.15*h_evis[id]->GetMaximum() );
    if( h_cos [0]->GetMaximum() < h_cos [id]->GetMaximum() ) h_cos [0]->SetMaximum( 1.15*h_cos [id]->GetMaximum() );
    if( h_acos[0]->GetMaximum() < h_acos[id]->GetMaximum() ) h_acos[0]->SetMaximum( 1.15*h_acos[id]->GetMaximum() );

  }


  Deco( h_mbc [1], 0, 1, 1 );
  can->cd(1);
  h_mbc[0]->Draw();
  h_mbc[1]->Draw("same");

  for( Int_t id=0; id<nd+1; id++ ){
    //can->cd(1); h_mbc [id]->Draw( id==0 ? "" : "histsame");
    can->cd(2); h_dm  [id]->Draw( id==0 ? "" : "histsame");
    can->cd(3); h_eecl[id]->Draw( id==0 ? "" : "histsame");
    can->cd(4); h_pdst[id]->Draw( id==0 ? "" : "histsame");
    can->cd(5); h_mm  [id]->Draw( id==0 ? "" : "histsame");
    can->cd(6); h_evis[id]->Draw( id==0 ? "" : "histsame");
    can->cd(7); h_cos [id]->Draw( id==0 ? "" : "histsame");
    can->cd(8); h_acos[id]->Draw( id==0 ? "" : "histsame");
  }

  for( Int_t id=0; id<1; id++ ){
    //can->cd(1); h_mbc [id]->Draw( "same" );
    can->cd(2); h_dm  [id]->Draw( "same" );
    can->cd(3); h_eecl[id]->Draw( "same" );
    can->cd(4); h_pdst[id]->Draw( "same" );
    can->cd(5); h_mm  [id]->Draw( "same" );
    can->cd(6); h_evis[id]->Draw( "same" );
    can->cd(7); h_cos [id]->Draw( "same" );
    can->cd(8); h_acos[id]->Draw( "same" );
  }

  Double_t ndmdte(0);
  Double_t ndmmce(0);
  Double_t nmbcdte(0);
  Double_t nmbcmce(0);
  std::cout << "deltam(dt) = " << h_dm[0]->IntegralAndError(1,h_dm[0]->GetNbinsX(),ndmdte) << " +- ";
  std::cout << ndmdte << std::endl;
  std::cout << "deltam(mc) = " << h_dm[1]->IntegralAndError(1,h_dm[1]->GetNbinsX(),ndmmce) << " +- ";
  std::cout << ndmmce << std::endl;
  std::cout << "mbc(dt) = " << h_mbc[0]->IntegralAndError(1,h_mbc[0]->GetNbinsX(),nmbcdte) << " +- ";
  std::cout << nmbcdte << std::endl;
  std::cout << "mbc(mc) = " << h_mbc[1]->IntegralAndError(1,h_mbc[1]->GetNbinsX(),nmbcmce) << " +- ";
  std::cout << nmbcmce << std::endl;

  TLegend* leg  = new TLegend( 0.20,0.70,0.40,0.85 );
  for( Int_t id=0; id<nd+1; id++ ) leg->AddEntry( h_mbc[id], tag[id], "PL" );
  leg->SetHeader( Form("D-lund (%d)",fl_dlund) );
  leg->Draw();

  can->Print( Form("pic/comparison_hadtag_%d.eps", fl_dlund) );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <for syststudy>
  TH1D* hist_syst = new TH1D(*h_acos[0]);
  hist_syst->Reset();
  hist_syst->SetName("syst");
  hist_syst->SetTitle("Ratio(Data/MC) of atan(cos#theta_{B-D*l*})");
  hist_syst->SetYTitle("Ratio(Data/MC)");
  for( Int_t ibin=0; ibin<hist_syst->GetNbinsX(); ibin++ ){
    Double_t n_dt   = h_acos[0]->GetBinContent(ibin+1);
    Double_t n_mc   = h_acos[1]->GetBinContent(ibin+1);
    Double_t e_dt   = h_acos[0]->GetBinError  (ibin+1);
    Double_t e_mc   = h_acos[1]->GetBinError  (ibin+1);
    Double_t ratio  = ( n_mc ? n_dt/n_mc : 0.0 );
    Double_t ratioE = 0.0;
    ratioE += ( n_dt ? pow( e_dt/n_dt, 2 ) : 0.0 );
    ratioE += ( n_mc ? pow( e_mc/n_mc, 2 ) : 0.0 );
    ratioE  = ratio*sqrt(ratioE);
    hist_syst->SetBinContent( ibin+1, ratio  );
    hist_syst->SetBinError  ( ibin+1, ratioE );
  }
  hist_syst->SetMaximum(3.0);
  hist_syst->SetMinimum(0.0);

  TCanvas* can2 = Canvas( "can2", "can2" );
  can2->Draw();
  can2->SetGridx();
  can2->SetGridy();
  hist_syst->Draw();
  can2->Print( Form("pic/comparison_hadtag_%d_ratio.eps", fl_dlund) );

  std::cout << "const Double_t syst_cos_bin[" << hist_syst->GetNbinsX() << "] = { ";
    
  for( Int_t ibin=0; ibin<hist_syst->GetNbinsX(); ibin++ ){
    std::cout << hist_syst->GetBinLowEdge(ibin+1) + hist_syst->GetBinWidth(ibin+1);
    if( ibin!=hist_syst->GetNbinsX()-1               ) std::cout << ", ";
    if( ibin!=hist_syst->GetNbinsX()-1 && ibin%10==9 ) std::cout << std::endl
								 << "                                    ";
  }
  std::cout << std::endl << "};" << std::endl;

  std::cout << "const Double_t syst_cos_factor[" << hist_syst->GetNbinsX() << "] = { ";

  for( Int_t ibin=0; ibin<hist_syst->GetNbinsX(); ibin++ ){
    std::cout << hist_syst->GetBinContent(ibin+1);
    if( ibin!=hist_syst->GetNbinsX()-1               ) std::cout << ", ";
    if( ibin!=hist_syst->GetNbinsX()-1 && ibin%10==9 ) std::cout << std::endl
								 << "                                       ";
  }
  std::cout << std::endl << "};" << std::endl;

  std::cout << "const Double_t syst_cos_factorE[" << hist_syst->GetNbinsX() << "] = { ";
  
  for( Int_t ibin=0; ibin<hist_syst->GetNbinsX(); ibin++ ){
    std::cout << hist_syst->GetBinError(ibin+1);
    if( ibin!=hist_syst->GetNbinsX()-1               ) std::cout << ", ";
    if( ibin!=hist_syst->GetNbinsX()-1 && ibin%10==9 ) std::cout << std::endl
								 << "                                        ";
  }
  std::cout << std::endl << "};" << std::endl;
  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
