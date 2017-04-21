#include "draws_.h"

const Char_t* tname  = "h15";
//const Char_t* infile = "~/dstrtaunu/ana/NB/hbk/hbk_mode0_test04_nor_setAA_HH/sigMC*setA_cut.root";
const Char_t* infile = "~/dstrtaunu/ana/NB/hbk/hbk_mode0_test04_nor_setAA_HH/sigMC_*.root";

const Int_t   nhist     = 4;
const Char_t* selection[nhist] = {
  "self==2",
  "self==2 && eecl>1.5 && 0.5<nb_mode0_test04_nor && nb_mode0_test04_nor<0.7",
  "self==1",
  "self==1 && eecl>1.5 && 0.5<nb_mode0_test04_nor && nb_mode0_test04_nor<0.7",
};
const Int_t line_col[nhist] = {3,3,2,2};
const Int_t line_wid[nhist] = {2,1,2,1};
const Int_t line_sty[nhist] = {1,2,1,2};

const Int_t      naxis             = 5;
const Char_t*    axis_sel  [naxis] = {           "eecl>1.5",             "1",                            "1",             "1",                        "1"  };
const Char_t*    axis_name [naxis] = {"nb_mode0_test04_nor",          "eecl", "mmiss*mmiss*abs(mmiss)/mmiss",          "evis",             "atan(cosdll)"  };
const Char_t*    axis_label[naxis] = {                 "NB", "E_{ECL} [GeV]",           "M_{miss}^{2} [GeV]", "E_{vis} [GeV]",   "atan(cos#theta_{B-Dl})"  };
const Int_t      xbin      [naxis] = {                  100,              48,                             45,              45,                        100  };
const Double_t   xmin      [naxis] = {                 -1.0,             0.0,                             -9,               4,           -TMath::PiOver2() };
const Double_t   xmax      [naxis] = {                  1.0,             2.4,                             36,              12,            TMath::PiOver2() };


Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  Style();
  gROOT->SetBatch(!true); // tmpppppp

  TChain* c = new TChain(tname);
  std::cout << c->Add(infile)  << " files" << std::endl;
  std::cout << c->GetEntries() << " entries" << std::endl;

  TLegend* leg = new TLegend( 0.75,0.75,0.99,0.99 );
  TH1D*** hist = new TH1D**[naxis];
  for( Int_t iaxis=0; iaxis<naxis; iaxis++ ){
    hist[iaxis] = new TH1D*[nhist];
    for( Int_t ihist=0; ihist<nhist; ihist++ ){
      hist[iaxis][ihist] = new TH1D( Form("h_%d_%d",iaxis,ihist), Form("h_%d_%d",iaxis,ihist), xbin[iaxis], xmin[iaxis], xmax[iaxis] );
      c->Project( Form("h_%d_%d",iaxis,ihist), axis_name[iaxis], Form("(%s)&&(%s)",axis_sel[iaxis],selection[ihist]) );
      hist[iaxis][ihist]->SetLineColor(line_col[ihist]);
      hist[iaxis][ihist]->SetLineWidth(line_wid[ihist]);
      hist[iaxis][ihist]->SetLineStyle(line_sty[ihist]);
      hist[iaxis][ihist]->SetXTitle(axis_label[iaxis]);

      if( iaxis==0 ) leg->AddEntry( hist[iaxis][ihist], selection[ihist], "L" );
    }
  }
  
  TCanvas*  c1 = Canvas( "c1", "c1", 3, 2 );
  for( Int_t iaxis=0; iaxis<naxis; iaxis++ ){
    for( Int_t ihist=0; ihist<nhist; ihist++ ){
      c1->cd(iaxis+1);
      hist[iaxis][ihist]->DrawNormalized(ihist==0 ? "" : "same");
    }
  }
  leg->Draw();

  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  
  return 0;
}
