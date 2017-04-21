#include "draws_.h"

const Char_t*  infile = "~/dstrtaunu/modules/dstrtaunu/hbk/hbk5_merge_cut/*s0[0-1]*.root";
const Double_t nstream = 2.0;
const Char_t*  tname  = "h15";

const Char_t* c_common = "1";
//const Char_t* c_common = "dst1_pi0>0.0&&dst2_pi0>0.0";
//const Char_t* c_common = "(abs(rm_dst1)==211||abs(rm_dst2)==211) && rm_d1!=1201 && rm_d2!=1201 && rm_d1!=1102 && rm_d2!=1102";
//const Char_t* c_common = "(abs(rm_dst1)==211||abs(rm_dst2)==211) && rm_d1!=1201 && rm_d2!=1201 && rm_d1!=1102 && rm_d2!=1102 && ( (cosdl1<cosdl2 && dst1pcm<2.0 && dst2pcm<2.5) || (cosdl1>cosdl2 && dst1pcm<2.5 && dst2pcm<2.0) ) && cosdlh>-2.0 && cosdlh<1.5";

const Int_t nctgry = 6;
const Char_t* c_type [nctgry] = {
  "self==1", // sig
  "self==2", // tag
  "self==0", // fake
  "self==-1", // other DD
  "self==-2&&evt_type==4", // other BB(charged)
  "self==-2&&evt_type<3",  // other BB(continuum)
};

const Char_t* c_name[nctgry+3] = { "sig", "norm", "fake", "otherDD", "B+B-", "qq",
				   "sig(sig+norm)", "bkg", "S/B" };

const Int_t nmode = 17;
const Int_t mode[nmode] = { 201, 1110, 1201, 310, 1102,  110,  102, // 7 modes(D+)
			    1101, 301, 1210, 101,  210, 1200, 1010, 12, 2, 200, // 10 modes(D0)
};
const Char_t* mode_name[nmode] = { "K2#pi", "K_{s}#pi#pi^{0}", "K2#pi#pi^{0}", "Ks3#pi", "2K#pi#pi^{0}", "Ks#pi", "2K#pi",
				   "K#pi#pi^{0}", "K3#pi", "Ks2#pi#pi^{0}", "K#pi", "Ks2#pi", "2#pi#pi^{0}", "Ks#pi^{0}", "Ks2K", "2K", "2#pi",
};

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  TStyle* style = Style(1);
  style->SetOptStat(0);
  gROOT->SetBatch(true); // tmpppppp
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* chain = new TChain(tname);
  std::cout << "[INFILE] "
	    << chain->Add( infile ) << " files, ";
  Int_t ntot = chain->GetEntries();
  std::cout << ntot   << " entries : "
	    << infile << std::endl;
  std::cout << "[CUT] " << c_common << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D** hist1 = new TH1D*[nctgry+3];
  for( Int_t ic=0; ic<nctgry+3; ic++ ){ // [nctgry] + [sig, bkg, ratio]
    hist1[ic] = new TH1D( Form("h1_%d",ic), c_name[ic],
			  nmode, 0.0, (Double_t)nmode );
    for( Int_t im=0; im<nmode; im++ ){
      ((TAxis*)hist1[ic]->GetXaxis())->SetBinLabel( im+1, mode_name[im] );
    }
    hist1[ic]->LabelsDeflate("X");
    hist1[ic]->LabelsOption ("v");
    hist1[ic]->SetMarkerSize(1.2);
    hist1[ic]->SetLabelSize(0.05,"XY");
    hist1[ic]->SetLineColor(3);
  }


  TH2D** hist2 = new TH2D*[nctgry+3];
  for( Int_t ic=0; ic<nctgry+3; ic++ ){ // [nctgry] + [sig, bkg, ratio]
    hist2[ic] = new TH2D( Form("h2_%d",ic), c_name[ic],
			  nmode, 0.0, (Double_t)nmode,
			  nmode, 0.0, (Double_t)nmode );
    for( Int_t im=0; im<nmode; im++ ){
      ((TAxis*)hist2[ic]->GetXaxis())->SetBinLabel( im+1, mode_name[im] );
      ((TAxis*)hist2[ic]->GetYaxis())->SetBinLabel( im+1, mode_name[im] );
    }
    hist2[ic]->LabelsDeflate("XY");
    hist2[ic]->LabelsOption ("v");
    hist2[ic]->SetMarkerSize(0.9);
    hist2[ic]->SetLabelSize(0.05,"XY");
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TText* tex = new TText();
  tex->SetTextColor(2);
  tex->SetTextSize(0.025);
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  TTree** tree = new TTree*[nctgry];
  for( Int_t ic=0; ic<nctgry; ic++ ){
    tree[ic] = new TTree();
    tree[ic] = chain->CopyTree( Form("(%s)&&(%s)",c_common,c_type[ic]) );
    Double_t cnt = tree[ic]->GetEntries()/nstream;
    std::cout << std::setw(10) << std::right << c_name[ic] << " : "
	      << cnt           << std::endl;
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
  for( Int_t ic=0; ic<nctgry; ic++ ){
    for( Int_t imy=0; imy<nmode; imy++ ){
      Double_t cnt1 = tree[ic]->GetEntries( Form("rm_d1==%d||rm_d2==%d", mode[imy],mode[imy]) )/nstream;
      cnt1 += 0.05;
      cnt1 *= 10;
      cnt1  = (Int_t)cnt1;
      cnt1 /= 10;
      hist1[ic]->Fill( mode_name[imy], cnt1 );
      for( Int_t imx=imy; imx<nmode; imx++ ){
	Double_t cnt2 = tree[ic]->GetEntries( Form("(rm_d1==%d&&rm_d2==%d) || (rm_d1==%d&&rm_d2==%d)", mode[imx],mode[imy],mode[imy],mode[imx]) )/nstream;
	cnt2 += 0.05;
	cnt2 *= 10;
	cnt2  = (Int_t)cnt2;
	cnt2 /= 10;
	hist2[ic]->Fill( mode_name[imx], mode_name[imy], cnt2 );
      }
    }

    hist1[ic]->SetTitle( Form("%s",               c_name[ic]                       ) );
    hist2[ic]->SetTitle( Form("%s (%.0f events)", c_name[ic], hist2[ic]->Integral()) );
    std::cout << std::setw(10) << std::right << c_name[ic] << " : "
	      << hist2[ic]->Integral()
	      << std::endl;
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  hist1[nctgry+0]->Add( hist1[0] ); // sig
  hist1[nctgry+0]->Add( hist1[1] ); // sig
  hist1[nctgry+1]->Add( hist1[2] ); // bkg
  hist1[nctgry+1]->Add( hist1[3] ); // bkg
  hist1[nctgry+1]->Add( hist1[4] ); // bkg
  hist1[nctgry+1]->Add( hist1[5] ); // bkg
  hist1[nctgry+2]->Add( hist1[0] ); // S/B
  hist1[nctgry+2]->Add( hist1[1] ); // S/B
  hist1[nctgry+2]->Divide( hist1[nctgry+1] ); // S/B
  for( Int_t ix=0; ix<hist1[nctgry+2]->GetNbinsX(); ix++ ){
    Double_t tmp_cnt = hist1[nctgry+2]->GetBinContent( ix+1 );
    tmp_cnt += 0.005;
    tmp_cnt *= 100;
    tmp_cnt  = (Int_t)tmp_cnt;
    tmp_cnt /= 100;
    hist1[nctgry+2]->SetBinContent( ix+1, tmp_cnt );
  }

  hist2[nctgry+0]->Add( hist2[0] ); // sig
  hist2[nctgry+0]->Add( hist2[1] ); // sig
  hist2[nctgry+1]->Add( hist2[2] ); // bkg
  hist2[nctgry+1]->Add( hist2[3] ); // bkg
  hist2[nctgry+1]->Add( hist2[4] ); // bkg
  hist2[nctgry+1]->Add( hist2[5] ); // bkg
  hist2[nctgry+2]->Add( hist2[0] ); // S/B
  hist2[nctgry+2]->Add( hist2[1] ); // S/B
  hist2[nctgry+2]->Divide( hist2[nctgry+1] ); // S/B

  for( Int_t ix=0; ix<hist2[nctgry+2]->GetNbinsX(); ix++ ){
    for( Int_t iy=0; iy<hist2[nctgry+2]->GetNbinsY(); iy++ ){
      Double_t tmp_cnt = hist2[nctgry+2]->GetBinContent( ix+1, iy+1 );
      tmp_cnt += 0.005;
      tmp_cnt *= 100;
      tmp_cnt  = (Int_t)tmp_cnt;
      tmp_cnt /= 100;
      hist2[nctgry+2]->SetBinContent( ix+1, iy+1, tmp_cnt );
    }
  }

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas*  c1 = new TCanvas( "c1", "c1", 1200, 600 );
  c1->Draw();
  c1->Print( "pic/cnt_signal.ps["  );
  for( Int_t ic=0; ic<nctgry+3; ic++ ){
    c1->Clear();
    c1->Divide(2,1);
    c1->cd(1); hist1[ic]->Draw("TEXT hist");
    c1->cd(2); hist2[ic]->Draw("TEXTCOLZ");
    tex->DrawTextNDC( 0.13,0.91, Form("cut : %s",c_common) );
    c1->Update();
    c1->Print( "pic/cnt_signal.ps"  );
    if( !gROOT->IsBatch() ) c1->WaitPrimitive();
  }
  c1->Print( "pic/cnt_signal.ps]"  );
  system("ps2pdf pic/cnt_signal.ps pic/cnt_signal.pdf");
  system("rm -f ps2pdf pic/cnt_signal.ps");
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  return 0;
}
