#include "draws_.h"

const Int_t   nfile  = 1;
const Char_t* infilename[nfile] = {
  //"../../modules/dstrtaunu/hbk/nor_kpi_kf0/*31*.root",
  //"../../modules/dstrtaunu/hbk/nor_kpi_kf1/*31*.root",
  //"../../modules/dstrtaunu/hbk/nor_kpi_kf2/*31*.root",
  //"../../modules/dstrtaunu/hbk/nor_kpi_kf3/*31*.root",
  //"../../modules/dstrtaunu/hbk/hbk5/mixed_single_d0/*.root",
  "../../modules/dstrtaunu/hbk/hbk5/mixed_single_dp/*.root",
};
  
const Char_t* tname  = "h17";

namespace DMASS{
  const Int_t    nctgry = 1;//2;
  const Char_t*  ctgry[nctgry] = {
    //"d1self==0",
    "d1self==1",
  };
  const Char_t*  axis_file     = "dmass";
  const Char_t*  axis_name     = "d1_m";
  const Char_t*  axis_label    = "D mass [GeV]";
  const Int_t    xbin          =  100;
  const Double_t xmin          = 1.81;
  const Double_t xmax          = 1.91;
  const Char_t*  c_common      = "1";
  const Int_t sel_fun = 20;
  const Double_t xmin_fit = xmin;
  const Double_t xmax_fit = xmax;
}

namespace DELTAM{
  const Int_t   nctgry  = 3;
  const Char_t* ctgry[nctgry] = { 
    "dst1self==0&&d1self==0",
    "dst1self==0&&d1self==1",
    "dst1self==1",
  };
  const Char_t*  axis_file  = "deltam";
  const Char_t*  axis_name  = "dm1";
  const Char_t*  axis_label = "#Delta m [GeV]";
  const Int_t    xbin       =   100;
  //const Double_t xmin       = 0.140; // for D0
  //const Double_t xmax       = 0.150; // for D0
  const Double_t xmin       = 0.135; // for D+
  const Double_t xmax       = 0.145; // for D+
  const Int_t sel_fun = 20;
  const Double_t xmin_fit = xmin;
  const Double_t xmax_fit = xmax;
  const Char_t*  c_common = "( (abs(rm_d1lun)==421 && rm_d1<999 && 1.864840-0.015000<d1_m&&d1_m<1.864840+0.015000) || (abs(rm_d1lun)==421 && rm_d1>999 && 1.864840-0.036000<d1_m&&d1_m<1.864840+0.036000) || (abs(rm_d1lun)==411 && rm_d1<999 && 1.869620-0.015000<d1_m&&d1_m<1.869620+0.015000) || (abs(rm_d1lun)==411 && rm_d1>999 && 1.869620-0.036000<d1_m&&d1_m<1.869620+0.036000) )";
};
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//using namespace DMASS;
using namespace DELTAM;
Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* style = Style(1);
  gROOT->SetBatch(true); // tmpppppp
  style->SetLabelSize(0.04,"xyz");
  
  if( app.Argc()!=2 ) std:: cerr << "Wrong input"  << std::endl
				 << " Usage : "    << app.Argv(0)
				 << "(int)fl_mode" << std::endl, abort();
  Int_t fl_mode = atoi(app.Argv(1));
  //Int_t fl_mode = 101;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain** chain = new TChain*[nfile];
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    chain[ifile] = new TChain(tname);
    std::cout << "[INFILE : " << ifile << "] "
	      << chain[ifile]->Add( infilename[ifile] ) << " files, ";
    std::cout << chain[ifile]->GetEntries()  << " entries, "
	      << infilename[ifile]
	      << std::endl;
  }
    
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D***   hc = makeHist ( "hc", xbin, xmin, xmax, nfile, nctgry ); // [nfile][nctgry]
  THStack** hs = makeStack( "hs", nfile         );                   // [nfile]
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    for( Int_t ictgry=0; ictgry<nctgry; ictgry++ ){
      chain[ifile]->Project( Form("hc_%d_%d",ifile,ictgry), axis_name, Form("(%s)&&(%s)&&(rm_d1==%d)",c_common,ctgry[ictgry],fl_mode) );
      if( ictgry!=nctgry-1 ) hc[ifile][ictgry]->SetFillColor(col_fil[ictgry]);
      else                   hc[ifile][ictgry]->SetLineColor(2);
      hc[ifile][ictgry]->SetXTitle(axis_label);
      hs[ifile]->Add( hc[ifile][ictgry] );
    }
  }

  TText* tex = new TText();
  tex->SetTextColor(2);
  tex->SetTextSize(0.035);
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* c1 = Canvas( "c1", Form("mass resolution : %d", fl_mode), nfile );
  c1->Draw();

  TF1** func    = new TF1*[nfile];
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    func[ifile] = new TF1( Form("func%d",ifile), make_func(sel_fun), xmin_fit, xmax_fit, n_fitfunc_par(sel_fun) );
    func_set_parameters(sel_fun, func[ifile], hc[ifile][nctgry-1], xbin, xmin_fit, xmax_fit);

    c1->cd(ifile+1);
    hc[ifile][nctgry-1]->Fit( Form("func%d",ifile),"R0");
    hc[ifile][nctgry-1]->Draw("PE0");
    func[ifile]->SetLineColor(4);
    func[ifile]->Draw("Lsame");
    Double_t eff_sigma = func[ifile]->GetParameter(1) * func[ifile]->GetParameter(3)
      + (1-func[ifile]->GetParameter(1)) * func[ifile]->GetParameter(3) * func[ifile]->GetParameter(4);
    tex->DrawTextNDC( 0.13,0.91, Form("effective sigma : %.1f MeV", 1000*eff_sigma) );
  }
  c1->Update();
  c1->Print( Form("pic/mass_reso_%s_%d_c1.eps", axis_file, fl_mode) );
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* c2 = Canvas( "c2", Form("mass resolution : %d", fl_mode), nfile );
  c2->Draw();
  for( Int_t ifile=0; ifile<nfile; ifile++ ){
    c2->cd(ifile+1);
    hs[ifile]->SetTitle( Form("mode(%d)", fl_mode) );
    hs[ifile]->Draw();
    hs[ifile]->GetXaxis()->CenterTitle();
    hs[ifile]->GetXaxis()->SetTitle(axis_label);
  }
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  c2->Update();
  c2->Print( Form("pic/mass_reso_%s_%d_c2.eps", axis_file, fl_mode) );
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
