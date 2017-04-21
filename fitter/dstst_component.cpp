#include "draws_.h"
#include "draws_fit_.h"

const Int_t    nvar            = 8;
const Char_t*  brname [nvar]   = {"eecl",          "nb_mode0_test13_nor", "mmiss2",                 "evis2",         "dst1pcm",            "dst2pcm",            "l1pcm",              "l2pcm"             };
const Char_t* axisname[nvar]   = {"E_{ECL} [GeV]", "NB",                  "M_{miss}^{2} [GeV^{2}]", "E_{vis} [GeV]", "p_{D*}^{sig} [GeV]", "p_{D*}^{tag} [GeV]", "p_{l}^{sig} [GeV]",  "p_{l}^{tag} [GeV]" };
const Int_t    xbin[nvar]      = { 24,     30,   30,   25,   30,   30,   30,   30 };
const Double_t xmin[nvar]      = { 0.0,  -1.0, -1.0,  5.0,  0.0,  0.0,  0.0,  0.0 };
const Double_t xmax[nvar]      = { 1.2,   1.0, 19.0, 10.0,  3.0,  3.0,  2.0,  2.5 };
const Bool_t   fl_draw[nvar]   = {!true,!true, true, true, true,!true, true,!true };
//                                 EECL  NB    Mmiss Evis  pD*   pD*   pl    pl
//const Char_t* selection = "dst1self==1&&dst2self==1&&self==-5";
const Char_t* selection = "dst1self==1&&dst2self==1&&self==-5&&nb_mode0_test13_nor>0.8&&eecl<0.5";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Int_t nhist = 6;
const Char_t* ctgry     [nhist] = { "ctgrsyst==3", "ctgrsyst==4", "ctgrsyst==5", "ctgrsyst==6", "ctgrsyst==7", "ctgrsyst==8" };
const Char_t* ctgry_name[nhist] = {          "D1",          "D2",         "D1'",         "D*0",       "D(2S)",      "D*(2S)" };
const Int_t   col       [nhist] = {             1,             2,             3,             4,             5,             6 };
//const Bool_t  fl_add    [nhist] = {          true,          true,          true,          true,          true,          true };
const Bool_t  fl_add    [nhist] = {         !true,         !true,         !true,          true,          true,          true };


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Int_t    nstream      = 10;
//const Char_t*  infile_gmc   = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0]*.root";
//const Int_t    nstream      = 1;
const Char_t*  infile_dstst = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut_bcs_vtx/DssMC_*.root";
const Double_t ndstst       = 2.7118;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){

  TApplication app( "app", &argc, argv );
  TStyle* sty = Style();
  sty->SetOptStat(0);
  sty->SetPadBottomMargin(0.16);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Read_Data( calib_file, true );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TChain* c_gmc = new TChain("h15");
  std::cout << "[infile gMC] " << infile_gmc << " : ";
  std::cout << c_gmc->Add(infile_gmc)        << " files, ";
  std::cout << c_gmc->GetEntries()           << " entries, ";
  std::cout << nstream                       << " streams" << std::endl;

  TChain* c_dstst = new TChain("h15");
  std::cout << "[infile D**lnu MC] "       << infile_dstst << " : ";
  std::cout << c_dstst->Add(infile_dstst)  << " files, ";
  std::cout << c_dstst->GetEntries()       << " entries, ";
  std::cout << ndstst                      << " times, "
	    << std::endl;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TLegend* leg       = new TLegend( 0.70,0.65,0.99,0.94 );
  THStack** mh_gmc   = new THStack*[nvar];
  THStack** mh_dstst = new THStack*[nvar];
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    mh_gmc  [ivar] = new THStack( Form("mh_gmc_%d",   ivar),Form("gmc : %s;%s",selection,axisname[ivar]) );
    mh_dstst[ivar] = new THStack( Form("mh_dstst_%d", ivar),Form("D** : %s;%s",selection,axisname[ivar]) );
  }

  TH1D*** hist_gmc   = new TH1D**[nvar]; // [var][hist]
  TH1D*** hist_dstst = new TH1D**[nvar]; // [var][hist]
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    hist_gmc  [ivar] = new TH1D*[nhist];
    hist_dstst[ivar] = new TH1D*[nhist];
    for( Int_t ihist=0; ihist<nhist; ihist++ ){
      hist_gmc  [ivar][ihist] = new TH1D( Form("hg%d_%d",ivar,ihist), Form("hg%d_%d",ivar,ihist), xbin[ivar], xmin[ivar], xmax[ivar] );
      hist_dstst[ivar][ihist] = new TH1D( Form("hd%d_%d",ivar,ihist), Form("hd%d_%d",ivar,ihist), xbin[ivar], xmin[ivar], xmax[ivar] );
    }
  }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    TTree* tmp_tree_gmc   = c_gmc  ->CopyTree( Form("(%s)&&(%s)",ctgry[ihist],selection) );
    TTree* tmp_tree_dstst = c_dstst->CopyTree( Form("(%s)&&(%s)",ctgry[ihist],selection) );
    
    for( Int_t ievt=0; ievt<tmp_tree_gmc->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( tmp_tree_gmc, ievt, 1.0 );
      Double_t val[nvar];
      for( Int_t ivar=0; ivar<nvar; ivar++ ){
	val[ivar] = tmp_tree_gmc->GetLeaf(brname[ivar])->GetValue();
	if     ( ivar==2 ) val[ivar] = val[ivar]*val[ivar]*fabs(val[ivar])/val[ivar];
	else if( ivar==4 ){
	  if( tmp_tree_gmc->GetLeaf("cosdl1")->GetValue() < tmp_tree_gmc->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_gmc->GetLeaf("dst1pcm")->GetValue();
	  else                                                                                            val[ivar] = tmp_tree_gmc->GetLeaf("dst2pcm")->GetValue();
	}else if( ivar==5 ){
	  if( tmp_tree_gmc->GetLeaf("cosdl1")->GetValue() > tmp_tree_gmc->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_gmc->GetLeaf("dst1pcm")->GetValue();
	  else                                                                                            val[ivar] = tmp_tree_gmc->GetLeaf("dst2pcm")->GetValue();
	}else if( ivar==6 ){
	  if( tmp_tree_gmc->GetLeaf("cosdl1")->GetValue() < tmp_tree_gmc->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_gmc->GetLeaf("l1pcm")->GetValue();
	  else                                                                                            val[ivar] = tmp_tree_gmc->GetLeaf("l2pcm")->GetValue();
	}else if( ivar==7 ){
	  if( tmp_tree_gmc->GetLeaf("cosdl1")->GetValue() > tmp_tree_gmc->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_gmc->GetLeaf("l1pcm")->GetValue();
	  else                                                                                            val[ivar] = tmp_tree_gmc->GetLeaf("l2pcm")->GetValue();
	}
	hist_gmc[ivar][ihist]->Fill( val[ivar], weight );
      }
    }
    
    for( Int_t ievt=0; ievt<tmp_tree_dstst->GetEntries(); ievt++ ){
      Double_t weight = cal_weight( tmp_tree_dstst, ievt, 1.0 );
      Double_t val[nvar];
      for( Int_t ivar=0; ivar<nvar; ivar++ ){
	val[ivar] = tmp_tree_dstst->GetLeaf(brname[ivar])->GetValue();
	if     ( ivar==2 ) val[ivar] = val[ivar]*val[ivar]*fabs(val[ivar])/val[ivar];
	else if( ivar==4 ){
	  if( tmp_tree_dstst->GetLeaf("cosdl1")->GetValue() < tmp_tree_dstst->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_dstst->GetLeaf("dst1pcm")->GetValue();
	  else                                                                                                val[ivar] = tmp_tree_dstst->GetLeaf("dst2pcm")->GetValue();
	}else if( ivar==5 ){
	  if( tmp_tree_dstst->GetLeaf("cosdl1")->GetValue() > tmp_tree_dstst->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_dstst->GetLeaf("dst1pcm")->GetValue();
	  else                                                                                                val[ivar] = tmp_tree_dstst->GetLeaf("dst2pcm")->GetValue();
	}else if( ivar==6 ){
	  if( tmp_tree_dstst->GetLeaf("cosdl1")->GetValue() < tmp_tree_dstst->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_dstst->GetLeaf("l1pcm")->GetValue();
	  else                                                                                                val[ivar] = tmp_tree_dstst->GetLeaf("l2pcm")->GetValue();
	}else if( ivar==7 ){
	  if( tmp_tree_dstst->GetLeaf("cosdl1")->GetValue() > tmp_tree_dstst->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_dstst->GetLeaf("l1pcm")->GetValue();
	  else                                                                                                val[ivar] = tmp_tree_dstst->GetLeaf("l2pcm")->GetValue();
	}
	hist_dstst[ivar][ihist]->Fill( val[ivar], weight );
      }
    }
  }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D** hist_sig = new TH1D*[nvar];
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    hist_sig[ivar] = new TH1D( Form("hs%d",ivar), Form("hs%d",ivar), xbin[ivar], xmin[ivar], xmax[ivar] );
  }
  TTree* tmp_tree_sig = c_gmc->CopyTree( "(self==1||(self==0&&gm_semi>0&&dst1self==1&&dst2self==1))" );
  //TTree* tmp_tree_sig = c_gmc->CopyTree( "((self==1||(self==0&&gm_semi>0&&dst1self==1&&dst2self==1)))&&nb_mode0_test13_nor>0.8&&eecl<0.5" );
  for( Int_t ievt=0; ievt<tmp_tree_sig->GetEntries(); ievt++ ){
    Double_t weight = cal_weight( tmp_tree_sig, ievt, 1.0 );
    Double_t val[nvar];
    for( Int_t ivar=0; ivar<nvar; ivar++ ){
      val[ivar] = tmp_tree_sig->GetLeaf(brname[ivar])->GetValue();
      if     ( ivar==2 ) val[ivar] = val[ivar]*val[ivar]*fabs(val[ivar])/val[ivar];
      else if( ivar==4 ){
	if( tmp_tree_sig->GetLeaf("cosdl1")->GetValue() < tmp_tree_sig->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_sig->GetLeaf("dst1pcm")->GetValue();
	else                                                                                            val[ivar] = tmp_tree_sig->GetLeaf("dst2pcm")->GetValue();
      }else if( ivar==5 ){
	if( tmp_tree_sig->GetLeaf("cosdl1")->GetValue() > tmp_tree_sig->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_sig->GetLeaf("dst1pcm")->GetValue();
	else                                                                                            val[ivar] = tmp_tree_sig->GetLeaf("dst2pcm")->GetValue();
      }else if( ivar==6 ){
	if( tmp_tree_sig->GetLeaf("cosdl1")->GetValue() < tmp_tree_sig->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_sig->GetLeaf("l1pcm")->GetValue();
	else                                                                                            val[ivar] = tmp_tree_sig->GetLeaf("l2pcm")->GetValue();
      }else if( ivar==7 ){
	if( tmp_tree_sig->GetLeaf("cosdl1")->GetValue() > tmp_tree_sig->GetLeaf("cosdl2")->GetValue() ) val[ivar] = tmp_tree_sig->GetLeaf("l1pcm")->GetValue();
	else                                                                                            val[ivar] = tmp_tree_sig->GetLeaf("l2pcm")->GetValue();
      }
      hist_sig[ivar]->Fill( val[ivar], weight );
    }
  }

  //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  std::cout << "======================================================================" << std::endl;
  std::cout << std::setw( 3) << std::right << "no"     << " : "
	    << std::setw(15) << std::right << "ctgry"  << " : "
	    << std::setw( 8) << std::right << "gmc"    << " : "
	    << std::setw( 8) << std::right << "D** mc" << std::endl;
  std::cout << "----------------------------------------------------------------------" << std::endl;

  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    for( Int_t ihist=0; ihist<nhist; ihist++ ){
      hist_gmc  [ivar][ihist]->Sumw2();
      hist_dstst[ivar][ihist]->Sumw2();
      hist_gmc  [ivar][ihist]->Scale(1.0/nstream);
      hist_dstst[ivar][ihist]->Scale(1.0/ndstst );
      
      if( fl_add[ihist] ) mh_gmc  [ivar]->Add( hist_gmc  [ivar][ihist] );
      if( fl_add[ihist] ) mh_dstst[ivar]->Add( hist_dstst[ivar][ihist] );
      if( ivar==0 ) std::cout << std::setw( 3) << std::right << ihist                                << " : "
			      << std::setw(15) << std::right << ctgry_name[ihist]                    << " : "
			      << std::setw( 8) << std::right << hist_gmc  [ivar][ihist]->Integral()  << " : "
			      << std::setw( 8) << std::right << hist_dstst[ivar][ihist]->Integral()  << std::endl;
    }
  }

  Double_t tot_gmc   = 0;
  Double_t tot_dstst = 0;
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    tot_gmc   += hist_gmc  [0][ihist]->Integral();
    tot_dstst += hist_dstst[0][ihist]->Integral();
  }
  std::cout << "----------------------------------------------------------------------" << std::endl;
  std::cout << std::setw( 3) << std::right << ""                             << " : "
	    << std::setw(15) << std::right << "total"                        << " : "
	    << std::setw( 8) << std::right << tot_gmc                        << " : "
	    << std::setw( 8) << std::right << tot_dstst                      << std::endl;
  std::cout << "----------------------------------------------------------------------" << std::endl;
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    for( Int_t ihist=0; ihist<nhist; ihist++ ){
      //hist_gmc  [ivar][ihist]->SetFillColor  (col[ihist]);
      hist_gmc    [ivar][ihist]->SetLineColor  (col[ihist]);
      hist_gmc    [ivar][ihist]->SetMarkerColor(col[ihist]);    
      //hist_dstst[ivar][ihist]->SetFillColor  (col[ihist]);
      hist_dstst  [ivar][ihist]->SetLineColor  (col[ihist]);
      hist_dstst  [ivar][ihist]->SetMarkerColor(col[ihist]);
    }
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    //Double_t max1 = mh_gmc[ivar]->GetMaximum("nostack");
    //if( mh_dstst[ivar]->GetMaximum("nostack") < max1 ) max1 = mh_dstst[ivar]->GetMaximum();
    //Double_t max2 = hist_sig[ivar]->GetMaximum();
    //hist_sig[ivar]->Scale(max1/max2);
    hist_sig[ivar]->SetFillColor(9);
    hist_sig[ivar]->SetLineColor(10);
  }
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Int_t cnt_can = 0;
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    if( fl_draw[ivar] ) cnt_can++;
  }
  Int_t n_can = cnt_can;

  TCanvas* can = Canvas( "can","can", n_can, 2 );
  can->Draw();
  cnt_can=0;
  for( Int_t ivar=0; ivar<nvar; ivar++ ){
    if( !fl_draw[ivar] ) continue;
    can->cd(cnt_can+1);
    mh_gmc[ivar]->DrawClone("histnostack");
    hist_sig[ivar]->Scale( mh_gmc[ivar]->GetMaximum("nostack")/hist_sig[ivar]->GetMaximum() );
    hist_sig[ivar]->DrawClone("same");
    mh_gmc[ivar]->DrawClone("histnostacksame");
    can->cd(n_can+cnt_can+1);
    mh_dstst[ivar]->DrawClone("histnostack");
    hist_sig[ivar]->Scale( mh_dstst[ivar]->GetMaximum("nostack")/hist_sig[ivar]->GetMaximum() );
    hist_sig[ivar]->Draw("same");    
    mh_dstst[ivar]->DrawClone("histnostacksame");
    cnt_can++;
  }

  for( Int_t ihist=0; ihist<nhist; ihist++ ) leg->AddEntry( hist_gmc[0][ihist], ctgry_name[ihist], "PL" );
  can->cd(1);
  leg->DrawClone();
  
  //++++++++++++++

  can->Print("pic/dstst_component.eps");
  std::cout << "finish" << std::endl;
  app.Run();
  return 0;
}
