#ifndef DRAWS_SINGLE_H
#define DRAWS_SINGLE_H

const Char_t*  treename = "h17";
const Double_t nscale   = 1.0; // 1/nscale

namespace CTGRY_DSTR{
  const Int_t    nhist    = 8;
  const Char_t*  ctgry_name[nhist] = { "data", "mc(total)",         "mc(true-nor)",         "mc(falsely rec.,true-D*)",            "mc(falsely rec.,fake-D*)",         "mc(true-sig)",                       "mc(B^{+}B^{-})",                        "mc(continuum)" };
  const Char_t*  ctgry_sel [nhist] = {    "1",         "1", "self==2&&acc1self==1", "self<1&&dst1self==1&&acc1self==1", "(dst1self!=1||acc1self!=1)&&self==0", "dst1self!=1&&self==1", "(dst1self!=1||acc1self!=1)&&self==-1", "(dst1self!=1||acc1self!=1)&&self==-2" };
  //const Char_t*  ctgry_sel [nhist] = {    "1",         "1",              "self==2",              "self<1&&dst1self==1",                "dst1self!=1&&self==0", "dst1self!=1&&self==1",                "dst1self!=1&&self==-1",                "dst1self!=1&&self==-2" };
  const Int_t    ctgry_lcol[nhist] = {      1,           9,                      2,                                 13,                                     5,                     11,                                     15,                                      4 };
  const Int_t    ctgry_fcol[nhist] = {      0,           9,                      2,                                 13,                                     5,                     11,                                     15,                                      4 };
}

namespace CTGRY_D{
  const Int_t    nhist    = 8;
  const Char_t*  ctgry_name[nhist] = { "data", "mc(total)", "mc(true-nor)", "mc(falsely rec.,true-D)", "mc(falsely rec.,fake-D)",       "mc(true-sig)",      "mc(B^{+}B^{-})",       "mc(continuum)" };
  const Char_t*  ctgry_sel [nhist] = {    "1",         "1",      "self==2",       "self<1&&d1self==1",      "d1self!=1&&self==0", "d1self!=1&&self==1", "d1self!=1&&self==-1", "d1self!=1&&self==-2" };
  const Int_t    ctgry_lcol[nhist] = {      1,           9,              2,                        13,                         5,                   11,                    15,                     4 };
  const Int_t    ctgry_fcol[nhist] = {      0,           9,              2,                        13,                         5,                   11,                    15,                     4 };
}

namespace AXIS_COS{
  const Char_t*  brname   = "cosdl1";
  const Char_t*  axisname = "cos#theta_{B-D*l}";
  const Int_t    xbin     =   120;
  const Double_t xmin     = -10.0;
  const Double_t xmax     =   5.0;
}

namespace AXIS_DSTR{
  const Char_t*  brname   = "dm1";
  const Char_t*  axisname = "#Deltam [GeV]";
        Int_t    xbin     = 330;
        Double_t xmin     = 0.139;
        Double_t xmax     = 0.150;
        //Int_t    xbin     = 270;
        //Double_t xmin     = 0.141;
        //Double_t xmax     = 0.150;
}

namespace AXIS_D{
  const Char_t*  brname   = "d1_m";
  const Char_t*  axisname = "m_{D} [GeV]";
  const Int_t    xbin     =  200;
  const Double_t xmin     = 1.80;
  const Double_t xmax     = 1.90;
}

void makeHist( Int_t decay, TChain* chain_dt, TChain* chain_mc, TH1D** hist, THStack* mh, TLegend* leg,
	       const Char_t* brname, const Char_t* axisname,    const Int_t xbin,         const Double_t xmin,     const Double_t xmax, const Char_t* selection,
	       const Int_t nhist,    const Char_t** ctgry_name, const Char_t** ctgry_sel, const Int_t* ctgry_lcol, const Int_t* ctgry_fcol ){
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist] = new TH1D( Form("h_%s_%d_%d",brname, decay,ihist), Form("h%d_%d [%s]",decay,ihist,ctgry_name[ihist]), xbin, xmin, xmax );
    if( decay==411 ){ // total D+ @20150311
      if( ihist==0 ) chain_dt->Project( Form("h_%s_%d_%d",brname,decay,ihist), brname, Form("(%s)&&(abs(rm_d1lun)==%d)&&(%s)", selection,decay,ctgry_sel[ihist]) );
      else           chain_mc->Project( Form("h_%s_%d_%d",brname,decay,ihist), brname, Form("(%s)&&(abs(rm_d1lun)==%d)&&(%s)", selection,decay,ctgry_sel[ihist]) );
    }else if( decay==421 ){ // total D0 @20150311
      if( ihist==0 ) chain_dt->Project( Form("h_%s_%d_%d",brname,decay,ihist), brname, Form("(%s)&&(abs(rm_d1lun)==%d)&&(%s)", selection,decay,ctgry_sel[ihist]) );
      else           chain_mc->Project( Form("h_%s_%d_%d",brname,decay,ihist), brname, Form("(%s)&&(abs(rm_d1lun)==%d)&&(%s)", selection,decay,ctgry_sel[ihist]) );
    }else{
      if( ihist==0 ) chain_dt->Project( Form("h_%s_%d_%d",brname,decay,ihist), brname, Form("(%s)&&(rm_d1==%d)&&(%s)", selection,decay,ctgry_sel[ihist]) );
      else           chain_mc->Project( Form("h_%s_%d_%d",brname,decay,ihist), brname, Form("(%s)&&(rm_d1==%d)&&(%s)", selection,decay,ctgry_sel[ihist]) );
    }
    if( ctgry_lcol[ihist] ) hist[ihist]->SetLineColor( ctgry_lcol[ihist] );
    if( ctgry_fcol[ihist] ) hist[ihist]->SetFillColor( ctgry_fcol[ihist] );
  }
  hist[1]->SetFillStyle(3002); hist[1]->SetMarkerStyle(1); // mc(total)
  leg->SetHeader(selection);

  for( Int_t ihist=0; ihist<nhist; ihist++ ) leg->AddEntry( hist[ihist], ctgry_name[ihist], (ihist==0 ? "P" : "F") );

  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    //hist[ihist]->SetXTitle(axisname);
    hist[ihist]->GetXaxis()->SetLabelSize(0);
    hist[ihist]->GetXaxis()->SetTitleSize(0);
    hist[ihist]->SetMinimum(0.0);
    hist[ihist]->Sumw2();
    if( ihist!=0 ) hist[ihist]->Scale(1.0/nscale);
  }

  for( Int_t ihist=nhist-1; ihist>1; ihist-- ) mh->Add( hist[ihist] );
  mh->SetMaximum( hist[0]->GetMaximum()> hist[1]->GetMaximum() ? 1.1*hist[0]->GetMaximum() : 1.1*hist[1]->GetMaximum() );

  return;
}

#endif
