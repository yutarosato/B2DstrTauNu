#include "draws_.h"
#include "draws_single.h"

const Double_t ymin = 0.0;
const Double_t ymax = 3.0;
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(!true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetTitleOffset(1.0,"y");
  sty->SetOptStat(0);
  sty->SetMarkerSize(1.2);
  sty->SetEndErrorSize(7);
  sty->SetPadTickY(1);
  sty->SetTickLength( 0.005, "Y" );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Char_t* infile_e_t = "tmp_e_total.dat";
  const Char_t* infile_e_s = "tmp_e_success.dat";
  const Char_t* infile_e_f = "tmp_e_false.dat";
  const Char_t* infile_m_t = "tmp_m_total.dat";
  const Char_t* infile_m_s = "tmp_m_success.dat";
  const Char_t* infile_m_f = "tmp_m_false.dat";
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t npad = 5;
  TH1D** waku = new TH1D*[npad];
  waku[0] = new TH1D( "tageff", "tagging efficiency", nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  waku[1] = new TH1D( "nsig",   "N_{sig}"  ,          nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  waku[2] = new TH1D( "rsig",   "R_{sig}",            nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  waku[3] = new TH1D( "rbkg",   "R_{bkg}",            nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  waku[4] = new TH1D( "sn",     "S/N",                nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  for( Int_t ipad=0; ipad<npad; ipad++ ){
    for( Int_t idec=0; idec<nd_dec; idec++ ) ((TAxis*)waku[ipad]->GetXaxis())->SetBinLabel( idec+1, d_dec_name[idec] );
    if( ipad==0 ){
      waku[ipad]->SetMaximum(ymax);
      waku[ipad]->SetMinimum(ymin);
      waku[ipad]->SetYTitle("efficiency (data/mc)");
    }else if( ipad==1 ){
      waku[ipad]->SetMaximum(100000);
      waku[ipad]->SetYTitle("sig yield (data)");
    }else if( ipad==2 || ipad ==3 ){
      waku[ipad]->SetMaximum(0.30);
      waku[ipad]->SetMinimum(0.00);
      if     ( ipad==2 ) waku[ipad]->SetYTitle("sig yield ratio (data)");
      else if( ipad==3 ) waku[ipad]->SetYTitle("bkg yield ratio (data)");
    }else if( ipad==4 ){
      waku[ipad]->SetMaximum(1.0);
      waku[ipad]->SetYTitle("S/N (purity)");
    }
    //waku[ipad]->LabelsDeflate("X");
    waku[ipad]->LabelsOption ("v");
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TGraphErrors* g_e_t = new TGraphErrors( infile_e_t, "%lg %*lg %*lg %lg %lg" );
  TGraphErrors* g_e_s = new TGraphErrors( infile_e_s, "%lg %*lg %*lg %lg %lg" );
  TGraphErrors* g_e_f = new TGraphErrors( infile_e_f, "%lg %*lg %*lg %lg %lg" );
  TGraphErrors* g_m_t = new TGraphErrors( infile_m_t, "%lg %*lg %*lg %lg %lg" );
  TGraphErrors* g_m_s = new TGraphErrors( infile_m_s, "%lg %*lg %*lg %lg %lg" );
  TGraphErrors* g_m_f = new TGraphErrors( infile_m_f, "%lg %*lg %*lg %lg %lg" );
  TCanvas* can = Canvas( "can", "can", 3, 2, 600, 400 );

  can->Draw();
  for( Int_t ipad=0; ipad<npad; ipad++ ){
    can->cd(ipad+1)->SetGridx();
    can->cd(ipad+1)->SetGridy();
    if( ipad==1 || ipad==1 ) can->cd(ipad+1)->SetLogy();
  }

  g_e_t->SetLineWidth(2); g_e_t->SetMarkerColor(2); g_e_t->SetLineColor(2); g_e_t->SetMarkerStyle(20);
  g_e_s->SetLineWidth(2); g_e_s->SetMarkerColor(2); g_e_s->SetLineColor(2); g_e_s->SetMarkerStyle(20);
  g_e_f->SetLineWidth(2); g_e_f->SetMarkerColor(2); g_e_f->SetLineColor(2); g_e_f->SetMarkerStyle(24);
  g_m_t->SetLineWidth(3); g_m_t->SetMarkerColor(3); g_m_t->SetLineColor(3); g_m_t->SetMarkerStyle(20);
  g_m_s->SetLineWidth(3); g_m_s->SetMarkerColor(3); g_m_s->SetLineColor(3); g_m_s->SetMarkerStyle(20);
  g_m_f->SetLineWidth(3); g_m_f->SetMarkerColor(3); g_m_f->SetLineColor(3); g_m_f->SetMarkerStyle(24);

  can->cd(1);
  waku[0]->Draw();
  //if( g_m_t->GetN() ) g_m_t->Draw("PEsame");
  if( g_m_s->GetN() ) g_m_s->Draw("PEsame");
  if( g_m_f->GetN() ) g_m_f->Draw("PEsame");
  //if( g_e_t->GetN() ) g_e_t->Draw("PEsame");
  if( g_e_s->GetN() ) g_e_s->Draw("PEsame");
  if( g_e_f->GetN() ) g_e_f->Draw("PEsame");
  
  TLegend* leg  = new TLegend( 0.15,0.72,0.28,0.88 );
  leg->AddEntry( g_e_t, "D* e#nu",   "PL" );
  leg->AddEntry( g_m_t, "D* #mu#nu", "PL" );
  leg->Draw();

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TGraph* g_e_sig = new TGraph( infile_e_t, "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg"      );
  TGraph* g_e_bkg = new TGraph( infile_e_t, "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg" );
  TGraph* g_e_sn  = new TGraph( infile_e_t, "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg"           );
  TGraph* g_m_sig = new TGraph( infile_m_t, "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg"      );
  TGraph* g_m_bkg = new TGraph( infile_m_t, "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg" );
  TGraph* g_m_sn  = new TGraph( infile_m_t, "%lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %*lg %lg"           );

  g_e_sig->SetLineWidth(2); g_e_sig->SetMarkerColor(2); g_e_sig->SetLineColor(2); g_e_sig->SetMarkerStyle(20); g_e_sig->Sort();
  g_e_bkg->SetLineWidth(2); g_e_bkg->SetMarkerColor(2); g_e_bkg->SetLineColor(2); g_e_bkg->SetMarkerStyle(20); g_e_bkg->Sort();
  g_e_sn ->SetLineWidth(2); g_e_sn ->SetMarkerColor(2); g_e_sn ->SetLineColor(2); g_e_sn ->SetMarkerStyle(20); g_e_sn ->Sort();
  g_m_sig->SetLineWidth(2); g_m_sig->SetMarkerColor(3); g_m_sig->SetLineColor(3); g_m_sig->SetMarkerStyle(20); g_m_sig->Sort();
  g_m_bkg->SetLineWidth(2); g_m_bkg->SetMarkerColor(3); g_m_bkg->SetLineColor(3); g_m_bkg->SetMarkerStyle(20); g_m_bkg->Sort();
  g_m_sn ->SetLineWidth(2); g_m_sn ->SetMarkerColor(3); g_m_sn ->SetLineColor(3); g_m_sn ->SetMarkerStyle(20); g_m_sn ->Sort();

  can->cd(2);
  waku[1]->Draw();
  g_e_sig ->DrawClone("PLsame");
  g_m_sig ->DrawClone("PLsame");

  Double_t ntotal_e_sig = 0;
  for( Int_t i=0; i<g_e_sig->GetN(); i++ ) ntotal_e_sig += g_e_sig->GetY()[i];
  for( Int_t i=0; i<g_e_sig->GetN(); i++ ) g_e_sig->SetPoint(i, g_e_sig->GetX()[i], g_e_sig->GetY()[i]/ntotal_e_sig );

  Double_t ntotal_e_bkg = 0;
  for( Int_t i=0; i<g_e_bkg->GetN(); i++ ) ntotal_e_bkg += g_e_bkg->GetY()[i];
  for( Int_t i=0; i<g_e_bkg->GetN(); i++ ) g_e_bkg->SetPoint(i, g_e_bkg->GetX()[i], g_e_bkg->GetY()[i]/ntotal_e_bkg );

  Double_t ntotal_m_sig = 0;
  for( Int_t i=0; i<g_m_sig->GetN(); i++ ) ntotal_m_sig += g_m_sig->GetY()[i];
  for( Int_t i=0; i<g_m_sig->GetN(); i++ ) g_m_sig->SetPoint(i, g_m_sig->GetX()[i], g_m_sig->GetY()[i]/ntotal_m_sig );

  Double_t ntotal_m_bkg = 0;
  for( Int_t i=0; i<g_m_bkg->GetN(); i++ ) ntotal_m_bkg += g_m_bkg->GetY()[i];
  for( Int_t i=0; i<g_m_bkg->GetN(); i++ ) g_m_bkg->SetPoint(i, g_m_bkg->GetX()[i], g_m_bkg->GetY()[i]/ntotal_m_bkg );

  can->cd(3); waku[2]->Draw(); g_e_sig->Draw("PLsame"); g_m_sig->Draw("PLsame");
  can->cd(4); waku[3]->Draw(); g_e_bkg->Draw("PLsame"); g_m_bkg->Draw("PLsame");
  can->cd(5); waku[4]->Draw(); g_e_sn ->Draw("PLsame"); g_m_sn ->Draw("PLsame");

  TText* tex1 = new TText(); tex1->SetTextColor(2); tex1->SetTextSize(0.04);
  TText* tex2 = new TText(); tex2->SetTextColor(3); tex2->SetTextSize(0.04);
  can->cd(2);
  tex1->DrawTextNDC( 0.18,0.26, Form("N(sig,e ) = %.0f", ntotal_e_sig) );
  tex2->DrawTextNDC( 0.18,0.20, Form("N(sig,mu) = %.0f", ntotal_m_sig) );

  
  can->Print( "pic/tag_eff_single.eps" );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
