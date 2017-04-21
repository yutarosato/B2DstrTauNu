#include "draws_.h"
#include "draws_fit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t* selection           = "nb_mode0_test13_nor>0.8 && eecl<0.5";
//const Char_t* selection           = "1";
const Int_t   npdf                = 6;
const Char_t* pdf_name     [npdf] = { "other", "sig", "nor","faked", "dstst", "doubled" };
Double_t      pdf_nexp     [npdf] = {     1.0,   1.0,   1.0,    1.0,     1.0,       1.0 };
const Char_t* pdf_selection[npdf] = { "0", // other
				      "(self==1||(self==0&&gm_semi>0&&dst1self==1&&dst2self==1))", // sig
				      "(self==2||(self==0&&gm_semi<0&&dst1self==1&&dst2self==1))", // nor
				      "(self<1&&!(dst1self==1&&dst2self==1))",                     // faked
				      "(self==-5&&dst1self==1&&dst2self==1)",                      // D**
				      "(self==-3&&dst1self==1&&dst2self==1)",                      // double D
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Bool_t  fl_use_dststmc   = true;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut_bcs_vtx/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetTitleOffset(1.0,"z");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Read_Data( calib_file, true );
  Int_t tmp_cnt = 1;
  std::stringstream sTmp;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TChain>
  sTmp.str("");
  sTmp.clear();
  sTmp << selection;
  sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
 std::cout << "[Cut] " << sTmp.str().c_str() << std::endl;
  
  TChain* c_gmc = new TChain(treename);
  std::cout << "[infile_gmc] " << infile_gmc << std::endl;
  std::cout << c_gmc->Add(infile_gmc)  << " files, ";
  std::cout << c_gmc->GetEntries()     << " entries, ";
  std::cout << nstream_gmc             << " streams" << std::endl;

  TTree** c_gmc_cut = new TTree*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( ipdf==0 ) c_gmc_cut[ipdf] = c_gmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(), makeCut_remain(pdf_selection,npdf).c_str()) );
    else          c_gmc_cut[ipdf] = c_gmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),                pdf_selection[ipdf]        ) );
    std::cout << "[Category] "
	      << std::setw(15) << std::right << pdf_name[ipdf]                << " : "
	      << std::setw(15) << std::right << c_gmc_cut[ipdf]->GetEntries() << " entries"
	      << std::endl;
  }
      
  TChain* c_dststmc = new TChain(treename);
  std::cout << "[infile_dststmc] " << infile_dststmc << std::endl;
  std::cout << c_dststmc->Add(infile_dststmc) << " files, ";
  std::cout << c_dststmc->GetEntries()        << " entries, ";
  std::cout << nstream_dststmc                << " streams" << std::endl;

  TTree** c_dststmc_cut = new TTree*[npdf];
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( ipdf==0 ) c_dststmc_cut[ipdf] = c_dststmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(), makeCut_remain(pdf_selection,npdf).c_str()) );
    else          c_dststmc_cut[ipdf] = c_dststmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),                pdf_selection[ipdf]        ) );
    std::cout << "[Category] "
	      << std::setw(15) << std::right << pdf_name[ipdf]                    << " : "
	      << std::setw(15) << std::right << c_dststmc_cut[ipdf]->GetEntries() << " entries"
	      << std::endl;
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t nhist = 4;
  const Char_t* histname [nhist] = { "nsig",    "nnor",    "bkg",     "signif"       };
  const Char_t* histtitle[nhist] = { "N_{sig}", "N_{nor}", "N_{bkg}", "significance" };
  TH1D** hist = new TH1D*[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist] = new TH1D( histname[ihist], histname[ihist], nd_dec, 0, (Double_t)nd_dec );
    for( Int_t id=0; id<nd_dec; id++ ) ((TAxis*)hist[ihist]->GetXaxis())->SetBinLabel( id+1, d_dec_name[id] );
    hist[ihist]->LabelsDeflate("X");
    hist[ihist]->LabelsOption ("v");
    hist[ihist]->SetMarkerSize(1.2);
    hist[ihist]->SetLabelSize(0.05,"XY");
    hist[ihist]->SetLineColor(3);
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  Double_t nsig[2] = {0};
  Double_t nnor[2] = {0};
  Double_t nbkg[2] = {0};
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    for( Int_t ievt=0; ievt<c_gmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_gmc_cut[ipdf], ievt, (Double_t)nstream_gmc );
      if( c_gmc_cut[ipdf]->GetLeaf("rm_dst1")->GetValue()==111 && c_gmc_cut[ipdf]->GetLeaf("rm_dst2")->GetValue()==111 ){
	if     ( ipdf==1 ) nsig[1] += weight;
	else if( ipdf==2 ) nnor[1] += weight;
	else               nbkg[1] += weight;
      }else{
	if     ( ipdf==1 ) nsig[0] += weight;
	else if( ipdf==2 ) nnor[0] += weight;
	else               nbkg[0] += weight;
      }
    }
    
    for( Int_t ievt=0; ievt<c_dststmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_dststmc_cut[ipdf], ievt, (Double_t)nstream_dststmc );
      if( c_dststmc_cut[ipdf]->GetLeaf("rm_dst1")->GetValue()==111 && c_dststmc_cut[ipdf]->GetLeaf("rm_dst2")->GetValue()==111 ){
	if     ( ipdf==1 ) nsig[1] += weight;
	else if( ipdf==2 ) nnor[1] += weight;
	else               nbkg[1] += weight;
      }else{
	if     ( ipdf==1 ) nsig[0] += weight;
	else if( ipdf==2 ) nnor[0] += weight;
	else               nbkg[0] += weight;
      }
    }
  }
  std::cout << nsig[0] = << std::enld;
  std::cout << nsig[1] = << std::enld;
  std::cout << nnor[0] = << std::enld;
  std::cout << nnor[1] = << std::enld;
  std::cout << nbkg[0] = << std::enld;
  std::cout << nbkg[1] = << std::enld;
  return 0;
  */
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    for( Int_t ievt=0; ievt<c_gmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_gmc_cut[ipdf], ievt, (Double_t)nstream_gmc );
      for( Int_t id=0; id<nd_dec; id++ ){
	if( c_gmc_cut[ipdf]->GetLeaf("rm_d1")->GetValue()==d_dec[id] || c_gmc_cut[ipdf]->GetLeaf("rm_d2")->GetValue()==d_dec[id] ){
	  if     ( ipdf==1 ) hist[0]->Fill( id, weight );
	  else if( ipdf==2 ) hist[1]->Fill( id, weight );
	  else  	     hist[2]->Fill( id, weight );
	}
      }
    }

    for( Int_t ievt=0; ievt<c_dststmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_dststmc_cut[ipdf], ievt, (Double_t)nstream_dststmc );
      for( Int_t id=0; id<nd_dec; id++ ){
	if( c_dststmc_cut[ipdf]->GetLeaf("rm_d1")->GetValue()==d_dec[id] || c_dststmc_cut[ipdf]->GetLeaf("rm_d2")->GetValue()==d_dec[id] ){
	  if     ( ipdf==1 ) hist[0]->Fill( id, weight );
	  else if( ipdf==2 ) hist[1]->Fill( id, weight );
	  else  	     hist[2]->Fill( id, weight );
	}
      }
    }
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t id=0; id<nd_dec; id++ ){
    Double_t nsig = hist[0]->GetBinContent( id+1 );
    Double_t nnor = hist[1]->GetBinContent( id+1 );
    Double_t nbkg = hist[2]->GetBinContent( id+1 );
    hist[3]->SetBinContent( id+1, (nsig+nnor+nbkg ? nsig/sqrt(nsig+nnor+nbkg) : 0.0) );
    hist[0]->SetBinContent( id+1, ((Int_t)(10*hist[0]->GetBinContent(id+1)))/10.0 );
    hist[1]->SetBinContent( id+1, ((Int_t)(10*hist[1]->GetBinContent(id+1)))/10.0 );
    hist[2]->SetBinContent( id+1, ((Int_t)(10*hist[2]->GetBinContent(id+1)))/10.0 );
    hist[3]->SetBinContent( id+1, ((Int_t)(10*hist[3]->GetBinContent(id+1)))/10.0 );
  }
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist[ihist]->SetMaximum( 1.15*hist[ihist]->GetMaximum() );

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", nhist );
  can->Draw();
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    can->cd(ihist+1);
    hist[ihist]->Draw("histTEXT");
  }
  can->Update();
  can->Print("pic/cnt_signal_double_tag.eps");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
