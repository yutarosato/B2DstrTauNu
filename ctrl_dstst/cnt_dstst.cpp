#include "draws_.h"
#include "draws_fit_.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//const Char_t* selection           = "nb_mode0_test13_nor>0.0 && eecl<0.5";
//const Char_t* selection           = "nb_mode0_test13_nor>0.8 && eecl<0.5";
const Char_t* selection           = "nb_mode0_test13_nor>0.0 && nb_mode0_test13_nor<0.8 && eecl<0.5";
//const Char_t* selection           = "nb_mode0_test13_nor<0.0 && eecl<0.5";
//const Char_t* selection           = "1";

//const Char_t* selection           = "( rempi0_1==1 && remks==0 && remtrk==0 ) &&( nb_mode0_test13_nor>0.0 && eecl_exp < 1.2)";
//const Char_t* selection           = "( rempi0_1==1 && remks==0 && remtrk==0 ) &&( nb_mode0_test13_nor<0.0 && eecl_exp < 1.2)";


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

//const Int_t   ndstst_dec = 6;
//const Char_t* dstst_dec_name[ndstst_dec] ={"D_{1}","D_{2}","D_{1}'", "D_{0}*", "D(2S)", "D*(2S)"};
/*
const Int_t   ndstst_dec = 12;
const Char_t* dstst_dec_name[ndstst_dec] ={"D_{1}(non-meas)",
					   "D_{1}(meas)",
					   "D_{2}(non-meas)",
					   "D_{2}(meas)",
					   "D_{1}'(non-meas)",
					   "D_{1}'(meas)",
					   "D_{0}*(non-meas)",
					   "D_{0}*(meas)",
					   "D(2S)(non-meas)",
					   "D(2S)(meas)",
					   "D*(2S)(non-meas)",
					   "D*(2S)(meas)"
};
*/
///*
const Int_t   ndstst_dec = 18;
const Char_t* dstst_dec_name[ndstst_dec] ={"D_{1}(non-meas)",
					   "D_{1}(meas)",
					   "D_{2}(non-meas)",
					   "D_{2}(meas)",
					   "D_{1}'(non-meas)",
					   "D_{1}'(meas)",
					   "D_{0}*(non-meas)",
					   "D_{0}*(meas)",
					   "D(2S)(Dpipi)",
					   "D(2S)(D0*pi)",
					   "D(2S)(D*pi)",
					   "D(2S)(D2*pi)",
					   "D(2S)(meas)",
					   "D*(2S)(D*pipi)",
					   "D*(2S)(D1'pi)",
					   "D*(2S)(D(2S)gam)",
					   "D*(2S)(D(2S)pi)",
					   "D*(2S)(meas)"
};
//*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
///*
const Bool_t  fl_use_dststmc   = true;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut_bcs_vtx/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
//*/
/*
const Bool_t  fl_use_dststmc   = true;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_noremcut/gMC_*s0[0-9]*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_noremcut/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
*/

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetPadBottomMargin(0.25);
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
    if( !(ipdf==3 || ipdf==4) ) continue;
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
    if( !(ipdf==3 || ipdf==4) ) continue;
    if( ipdf==0 ) c_dststmc_cut[ipdf] = c_dststmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(), makeCut_remain(pdf_selection,npdf).c_str()) );
    else          c_dststmc_cut[ipdf] = c_dststmc->CopyTree( Form("(%s)&&(%s)", sTmp.str().c_str(),                pdf_selection[ipdf]        ) );
    std::cout << "[Category] "
	      << std::setw(15) << std::right << pdf_name[ipdf]                    << " : "
	      << std::setw(15) << std::right << c_dststmc_cut[ipdf]->GetEntries() << " entries"
	      << std::endl;
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t nhist = 2;
  const Char_t* histname [nhist] = { "nddst_correct",     "nddst_fake"     };
  const Char_t* histtitle[nhist] = { "N_{D**}^{correct}", "N_{D**}^{fake}" };
  TH1D** hist = new TH1D*[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist[ihist] = new TH1D( histname[ihist], histname[ihist], ndstst_dec,0, (Double_t)ndstst_dec );
    for( Int_t id=0; id<ndstst_dec; id++ ) ((TAxis*)hist[ihist]->GetXaxis())->SetBinLabel( id+1, dstst_dec_name[id] );
    hist[ihist]->LabelsDeflate("X");
    hist[ihist]->LabelsOption ("v");
    hist[ihist]->SetMarkerSize(1.2);
    hist[ihist]->SetLabelSize(0.04,"X");
    hist[ihist]->SetLineColor(3);
    hist[ihist]->SetMarkerColor(3);
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ipdf=0; ipdf<npdf; ipdf++ ){
    if( !(ipdf==3 || ipdf==4) ) continue;
    for( Int_t ievt=0; ievt<c_gmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_gmc_cut[ipdf], ievt, (Double_t)nstream_gmc );
      /*
      if     ( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)0, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)1, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)2, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)3, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)4, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)5, weight );
      */
      /*
      if     ( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 0, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 1, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 2, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 3, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 4, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 5, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 6, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 7, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 8, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 9, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)10, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)11, weight );
      */
      ///*
      if     ( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 0, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 1, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 2, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 3, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 4, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 5, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 6, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 7, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0

	       && ( fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==411 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==421 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==411 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==421 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 8, weight ); // D(2S) -> D pipi
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==10411 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==10421 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==10411 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==10421 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 9, weight ); // D(2S) -> D_0* pi
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==413 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==423 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==413 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==423 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 10, weight ); // D(2S) -> D* pi
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==415 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==425 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==415 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==425 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 11, weight ); // D(2S) -> D_2* pi
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)12, weight );
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==413 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==423 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==413 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==423 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)13, weight ); // D*(2S) -> D* pipi
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==20413 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==20423 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==20413 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==20423 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)14, weight ); // D*(2S) -> D*'1 pi
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==100411 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==100421 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==100411 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==100421 ) &&
	       ( c_gmc_cut[ipdf]->GetLeaf("nddst1pp")->GetValue() + c_gmc_cut[ipdf]->GetLeaf("nddst1p0")->GetValue() + c_gmc_cut[ipdf]->GetLeaf("nddst2pp")->GetValue() + c_gmc_cut[ipdf]->GetLeaf("nddst2p0")->GetValue()==0 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)15, weight ); // D*(2S) -> D(2S) gamma
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==100411 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==100421 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==100411 || fabs(c_gmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==100421 ) &&
	       ( c_gmc_cut[ipdf]->GetLeaf("nddst1pp")->GetValue() + c_gmc_cut[ipdf]->GetLeaf("nddst1p0")->GetValue() + c_gmc_cut[ipdf]->GetLeaf("nddst2pp")->GetValue() + c_gmc_cut[ipdf]->GetLeaf("nddst2p0")->GetValue()==1 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)16, weight ); // D*(2S) -> D(2S) pi
      else if( c_gmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_gmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)17, weight );
      //*/
    }
    
    for( Int_t ievt=0; ievt<c_dststmc_cut[ipdf]->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( c_dststmc_cut[ipdf], ievt, (Double_t)nstream_dststmc );
      /*
      if     ( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)0, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)1, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)2, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)3, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)4, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)5, weight );
      */
      /*
      if     ( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 0, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 1, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 2, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 3, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 4, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 5, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 6, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 7, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 8, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 9, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)10, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)11, weight );
      */
      ///*
      if     ( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 0, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==3 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 1, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 2, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==4 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 3, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 4, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==5 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 5, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 6, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==6 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 7, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0

	       && ( fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==411 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==421 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==411 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==421 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 8, weight ); // D(2S) -> D pipi
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==10411 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==10421 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==10411 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==10421 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 9, weight ); // D(2S) -> D_0* pi
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==413 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==423 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==413 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==423 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 10, weight ); // D(2S) -> D* pi
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==415 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==425 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==415 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==425 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t) 11, weight ); // D(2S) -> D_2* pi
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==7 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)12, weight );
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==413 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==423 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==413 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==423 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)13, weight ); // D*(2S) -> D* pipi
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==20413 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==20423 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==20413 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==20423 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)14, weight ); // D*(2S) -> D*'1 pi
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==100411 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==100421 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==100411 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==100421 ) &&
	       ( c_dststmc_cut[ipdf]->GetLeaf("nddst1pp")->GetValue() + c_dststmc_cut[ipdf]->GetLeaf("nddst1p0")->GetValue() + c_dststmc_cut[ipdf]->GetLeaf("nddst2pp")->GetValue() + c_dststmc_cut[ipdf]->GetLeaf("nddst2p0")->GetValue()==0 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)15, weight ); // D*(2S) -> D(2S) gamma
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==0
	       && ( fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==100411 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst1_d")->GetValue())==100421 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==100411 || fabs(c_dststmc_cut[ipdf]->GetLeaf("ddst2_d")->GetValue())==100421 ) &&
	       ( c_dststmc_cut[ipdf]->GetLeaf("nddst1pp")->GetValue() + c_dststmc_cut[ipdf]->GetLeaf("nddst1p0")->GetValue() + c_dststmc_cut[ipdf]->GetLeaf("nddst2pp")->GetValue() + c_dststmc_cut[ipdf]->GetLeaf("nddst2p0")->GetValue()==1 )
	       ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)16, weight ); // D*(2S) -> D(2S) pi
      else if( c_dststmc_cut[ipdf]->GetLeaf("ctgrsyst")->GetValue()==8 && c_dststmc_cut[ipdf]->GetLeaf("moresyst")->GetValue()==1 ) hist[(ipdf==3 ? 1 : 0)]->Fill( (Double_t)17, weight );
      //*/

    }
  }


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D** hist_norm = new TH1D*[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist_norm[ihist] = new TH1D( *hist[ihist] );
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 2*nhist );
  can->Draw();
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    std::cout << hist[ihist]->Integral() << std::endl;
    can->cd(ihist+1);
    hist[ihist]->DrawClone("histTEXT");
    can->cd(ihist+1+nhist);
    hist[ihist]->DrawNormalized("histTEXT");
  }
  can->Update();
  can->Print("pic/cnt_dstst.eps");

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;

}
