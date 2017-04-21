#include "draws_.h"
#include "draws_single.h"

const Double_t ymin = 0.5;
const Double_t ymax = 2.0;
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
  const Char_t* infile1 = "tmp_dstr_1.dat";
  const Char_t* infile2 = "tmp_dstr_2.dat";
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t npad = 4;
  TH1D** waku = new TH1D*[npad];
  waku[0] = new TH1D( "deltamreso0", "D^{0}#pi^{+}(width)", nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  waku[1] = new TH1D( "deltamreso1", "D^{+}#pi^{0}(width)", nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  waku[2] = new TH1D( "deltamreso2", "D^{0}#pi^{+}(mean)",  nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  waku[3] = new TH1D( "deltamreso3", "D^{+}#pi^{0}(mean)",  nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  for( Int_t ipad=0; ipad<npad; ipad++ ){
    for( Int_t idec=0; idec<nd_dec; idec++ ) ((TAxis*)waku[ipad]->GetXaxis())->SetBinLabel( idec+1, d_dec_name[idec] );
    if( ipad<2 ){
      waku[ipad]->SetMaximum(ymax);
      waku[ipad]->SetMinimum(ymin);
      waku[ipad]->SetYTitle("#Delta m resolution (data/mc)");
    }else if( ipad==2 ){
      waku[ipad]->SetMaximum(0.1458);
      waku[ipad]->SetMinimum(0.1450);
      waku[ipad]->SetYTitle("#Delta m mean");
    }else if( ipad==3 ){
      waku[ipad]->SetMaximum(0.142);
      waku[ipad]->SetMinimum(0.140);
      waku[ipad]->SetYTitle("#Delta m mean");
    }
    //waku[ipad]->LabelsDeflate("X");
    waku[ipad]->LabelsOption ("v");

  }
  TGraphErrors* g1 = new TGraphErrors( infile1, "%lg %*lg %*lg %lg   %lg" );
  TGraphErrors* g2 = new TGraphErrors( infile2, "%lg %*lg %*lg %lg   %lg" );
  TGraphErrors* g3 = new TGraphErrors( infile1, "%lg %*lg %*lg %*lg  %*lg %*lg  %*lg %lg  %lg" );
  TGraphErrors* g4 = new TGraphErrors( infile2, "%lg %*lg %*lg %*lg  %*lg %*lg  %*lg %lg  %lg" );
  TCanvas* can = Canvas( "can", "can", 2, 2, 500, 400 );
  can->Draw();
  for( Int_t ipad=0; ipad<npad; ipad++ ){
    can->cd(ipad+1)->SetGridx();
    can->cd(ipad+1)->SetGridy();
    waku[ipad]->Draw();
  }

  g1->SetLineWidth(2); g1->SetMarkerColor(1); g1->SetLineColor(1); g1->SetMarkerStyle(1);
  g2->SetLineWidth(2); g2->SetMarkerColor(1); g2->SetLineColor(1); g2->SetMarkerStyle(1);
  g3->SetLineWidth(2); g3->SetMarkerColor(1); g3->SetLineColor(1); g3->SetMarkerStyle(1);
  g4->SetLineWidth(2); g4->SetMarkerColor(1); g4->SetLineColor(1); g4->SetMarkerStyle(1);

  can->cd(1);
  if( g1->GetN() ){
    g1->Draw("PE");
    g1->Fit("pol0");
  }

  can->cd(2);
  if( g2->GetN() ){
    g2->Draw("PE");
    g2->Fit("pol0");
  }

  can->cd(3);
  if( g3->GetN() ){
    g3->Draw("PE");
    g3->Fit("pol0");
  }

  can->cd(4);
  if( g4->GetN() ){
    g4->Draw("PE");
    g4->Fit("pol0");
  }
  

  can->Update();
  can->Print( "pic/deltam_reso.eps" );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

