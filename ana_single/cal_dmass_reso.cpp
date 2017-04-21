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
  const Char_t* infile1 = "tmp_d_1.dat";
  const Char_t* infile2 = "tmp_d_2.dat";
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t npad = 3;
  TH1D** waku = new TH1D*[npad];
  waku[0] = new TH1D( "dmassreso0", "D mass w/o tail",    nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  waku[1] = new TH1D( "dmassreso1", "D mass w/  tail(L)", nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  waku[2] = new TH1D( "dmassreso2", "D mass w/  tail(H)", nd_dec, -0.5, (Double_t)nd_dec-0.5 );
  for( Int_t ipad=0; ipad<npad; ipad++ ){
    for( Int_t idec=0; idec<nd_dec; idec++ ) ((TAxis*)waku[ipad]->GetXaxis())->SetBinLabel( idec+1, d_dec_name[idec] );
    waku[ipad]->SetMaximum(ymax);
    waku[ipad]->SetMinimum(ymin);
    //waku[ipad]->LabelsDeflate("X");
    waku[ipad]->LabelsOption ("v");
    waku[ipad]->SetYTitle("D mass resolution (data/mc)");
  }



  TGraphErrors* g_wo_tail = new TGraphErrors( infile1, "%lg %*lg %*lg %lg  %lg"          );
  TGraphErrors* g_tailL   = new TGraphErrors( infile2, "%lg %*lg %*lg %lg  %lg"          );
  TGraphErrors* g_tailH   = new TGraphErrors( infile2, "%lg %*lg %*lg %*lg %*lg %lg %lg" );
  TCanvas* can = Canvas( "can", "can", npad, 1, 500, 400 );
  can->Draw();
  for( Int_t ipad=0; ipad<npad; ipad++ ){
    can->cd(ipad+1)->SetGridx();
    can->cd(ipad+1)->SetGridy();
    waku[ipad]->Draw();
  }

  g_wo_tail->SetLineWidth(2); g_wo_tail->SetMarkerColor(1); g_wo_tail->SetLineColor(1); g_wo_tail->SetMarkerStyle(1);
  g_tailL  ->SetLineWidth(2); g_tailL  ->SetMarkerColor(1); g_tailL  ->SetLineColor(1); g_tailL  ->SetMarkerStyle(1);
  g_tailH  ->SetLineWidth(2); g_tailH  ->SetMarkerColor(1); g_tailH  ->SetLineColor(1); g_tailH  ->SetMarkerStyle(1);

  can->cd(1);
  if( g_wo_tail->GetN() ){
    g_wo_tail->Draw("PE");
    g_wo_tail->Fit("pol0");
  }
  
  can->cd(2);
  if( g_tailL->GetN() ){
    g_tailL->Draw("PE");
    g_tailL->Fit("pol0");
  }

  can->cd(3);
  if( g_tailH->GetN() ){
    g_tailH->Draw("PE");
    g_tailH->Fit("pol0");
  }

  can->Print( "pic/dmass_reso.eps" );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}

