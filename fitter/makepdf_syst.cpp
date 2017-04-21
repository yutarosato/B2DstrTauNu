#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

const Bool_t fl_use_dststmc = true;
const Bool_t fl_smoothing   = true;
const Bool_t  fl_use_npmc   = true;
const Char_t* weight_table  = "../npmc/table/dstrtaunu_lep_20_all/est_weight.root";
const Char_t* fl_par        = "0p0";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Int_t nctgry              = 6;
const Char_t* ctgry    [nctgry] = {"faked", "sig", "nor", "doubled", "other", "dstst"};
/*
const Char_t* selection[nctgry] = {
  "eecl<1.2 && (dst1self!=1 || dst2self!=1)", // fake D
  "eecl<1.2 && self==1", // sig
  "eecl<1.2 && self==2", // norm
  "eecl<1.2 && self==-3", // double D
  "eecl<1.2 && self<0 && self!=-3 && self!=-5", // other
  "eecl<1.2 && self==-5", // D**
};
*/
const Char_t* selection[nctgry] = {
  "eecl<1.2 && (self<1&&!(dst1self==1&&dst2self==1))",                       // faked
  "eecl<1.2 && (self==1||(self==0&&gm_semi>0&&dst1self==1&&dst2self==1))",   // sig
  "eecl<1.2 && (self==2||(self==0&&gm_semi<0&&dst1self==1&&dst2self==1))",   // nor
  "eecl<1.2 && (self==-3&&dst1self==1&&dst2self==1)",                        // double D
  "eecl<1.2 && (dst1self==1&&dst2self==1) && self<0 &&self!=-3 && self!=-5", // other
  "eecl<1.2 && (self==-5&&dst1self==1&&dst2self==1)",                        // D**
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-5]*.root";
//const Double_t nstream_gmc     = 6;
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut_bcs_vtx/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/0p0_weight_nb_cut_bcs_vtx/npMC_*.root";
const Double_t nstream_npmc    = 10;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(10);
  sty->SetOptStat(0);
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( !(app.Argc()==3 || app.Argc()==4) )
    std::cerr << "Wrong input" << std::endl
	      << "Usage : " << app.Argv(0)
	      << " (int)ctgyr (int)tag_cnt [(int)fl_lep]" << std::endl
      //<< "1(sig), 2(nor), 0(fake-D(*)), 5(D**), 3(Double DD), 4(other)" << std::endl
	      << "2(nor), 0(fake-D(*)), 5(D**), 3(Double DD)" << std::endl
	      << "fl_lep : 10(e), 1(mu), 0(l)"
	      << std::endl, abort();
  Int_t fl_ctgry = atoi(app.Argv(1));
  Int_t tag_cnt  = atoi(app.Argv(2));
  Int_t fl_lep = 0;
  if( app.Argc()==4 ) fl_lep = atoi(app.Argv(3));
  unsigned int seed = time(NULL);
  seed += 1000*tag_cnt;
  gRandom->SetSeed( seed );
  if( fl_ctgry==0 ){
    Read_Data( "calib.dat" );
    Fluct_calib(true);
  }else Read_Data( "calib.dat", true );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  sTmp << Form("eecl<%f",eecl_xmax);
  sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
  sTmp << " && " << makeCut_npmc   ( fl_use_npmc    ).c_str();
  if( fl_lep ) sTmp << Form(" && ( (cosdll==cosdl1 && rm_l1==%d) || (cosdll==cosdl2 && rm_l2==%d) )",fl_lep,fl_lep);
  sTmp << " && " << selection[fl_ctgry];

  TChain* c_gmc = new TChain(treename);
  std::cout << "[infile_gmc] " << infile_gmc << std::endl;
  std::cout << c_gmc->Add(infile_gmc)  << " files, ";
  std::cout << c_gmc->GetEntries()     << " entries, ";
  std::cout << nstream_gmc             << " streams" << std::endl;
  TTree* c_gmc_cut = c_gmc->CopyTree( Form("(%s)", sTmp.str().c_str()) );
  std::cout << "[Category] " << ctgry[fl_ctgry]                       << std::endl;
  std::cout << "[Cut] "      << sTmp.str().c_str()                    << std::endl;
  std::cout << " -> "        << c_gmc_cut->GetEntries() << " entries" << std::endl;

  TChain* c_dststmc = new TChain("h15");
  std::cout << "[infile_dststmc] " << infile_dststmc << std::endl;
  std::cout << c_dststmc->Add(infile_dststmc) << " files, ";
  std::cout << c_dststmc->GetEntries()        << " entries, ";
  std::cout << nstream_dststmc                << " streams" << std::endl;
  TTree* c_dststmc_cut = c_dststmc->CopyTree( Form("(%s)", sTmp.str().c_str()) );
  std::cout << "[Category] " << ctgry[fl_ctgry]                           << std::endl;
  std::cout << "[Cut] "      << sTmp.str().c_str()                        << std::endl;
  std::cout << " -> "        << c_dststmc_cut->GetEntries() << " entries" << std::endl;

  TChain* c_npmc = new TChain("h15");
  std::cout << "[infile_npmc] " << infile_npmc << std::endl;
  std::cout << c_npmc->Add(infile_npmc) << " files, ";
  std::cout << c_npmc->GetEntries()     << " entries, ";
  std::cout << nstream_npmc             << " streams" << std::endl;
  TTree* c_npmc_cut = c_npmc->CopyTree( Form("(%s)", sTmp.str().c_str()) );
  std::cout << "[Category] " << ctgry[fl_ctgry]                        << std::endl;
  std::cout << "[Cut] "      << sTmp.str().c_str()                     << std::endl;
  std::cout << " -> "        << c_npmc_cut->GetEntries() << " entries" << std::endl;


  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* can = Canvas( "can","can", 3, 2 );
  can->Draw();
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  const Int_t nhist = 3;
  const Char_t* tagname[nhist] = {"all_nb", "neg_nb", "pos_nb"};
  TH1D** hist1_nb   = new TH1D*[nhist];
  TH1D** hist1_eecl = new TH1D*[nhist];
  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist1_nb  [ihist] = new TH1D( Form(  "nb_%s_%s_lep%d",ctgry[fl_ctgry],tagname[ihist],fl_lep), Form(  "nb_%s_%s_lep%d",ctgry[fl_ctgry],tagname[ihist],fl_lep),   nb_xbin,   nb_xmin,   nb_xmax );
    hist1_eecl[ihist] = new TH1D( Form("eecl_%s_%s_lep%d",ctgry[fl_ctgry],tagname[ihist],fl_lep), Form("eecl_%s_%s_lep%d",ctgry[fl_ctgry],tagname[ihist],fl_lep), eecl_xbin, eecl_xmin, eecl_xmax );
    hist1_nb  [ihist]->Sumw2();
    hist1_eecl[ihist]->Sumw2();
    hist1_nb  [ihist]->SetXTitle( "NB" );
    hist1_eecl[ihist]->SetXTitle( "E_{ECL} [GeV]" );
  }
  TH2D* hist2 = new TH2D( Form("nb_eecl_%s_lep%d",ctgry[fl_ctgry],fl_lep), Form("nb_eecl_%s_lep%d",ctgry[fl_ctgry],fl_lep),
			  nb_xbin,   nb_xmin,   nb_xmax,
			  eecl_xbin, eecl_xmin, eecl_xmax
			  );
  hist2->Sumw2();
  hist2->SetXTitle( "NB"            );
  hist2->SetYTitle( "E_{ECL} [GeV]" );
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ievt=0; ievt<c_gmc_cut->GetEntries(); ievt++ ){
    Double_t weight = cal_weight( c_gmc_cut, ievt, (Double_t)nstream_gmc );
    //Double_t weight = cal_weight( c_gmc_cut, ievt, (Double_t)nstream_gmc, true ); // syst from modelling
    if     ( fl_ctgry==5 || fl_ctgry==3 ) weight *= cal_weight_syst1( c_gmc_cut, ievt, tag_cnt ); // syst from D** composition or Double D
    else if( fl_ctgry==2                ) weight *= cal_weight_syst2( c_gmc_cut, ievt          ); // syst from cos resolution (norm)
    if( weight==0.0 ) continue;
    if( c_gmc_cut->GetLeaf(nb_brname)->GetValue() > 0.0 ) hist1_eecl[2]->Fill( c_gmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    else                                                  hist1_eecl[1]->Fill( c_gmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    hist1_nb  [0]->Fill( c_gmc_cut->GetLeaf(  nb_brname)->GetValue(), weight );
    hist1_eecl[0]->Fill( c_gmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    hist2        ->Fill( c_gmc_cut->GetLeaf(  nb_brname)->GetValue(),
			 c_gmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
  }

  for( Int_t ievt=0; ievt<c_dststmc_cut->GetEntries(); ievt++ ){
    Double_t weight = cal_weight( c_dststmc_cut, ievt, (Double_t)nstream_dststmc );
    //Double_t weight = cal_weight( c_dststmc_cut, ievt, (Double_t)nstream_dststmc, true ); // syst for modeling
    if( weight==0.0 ) continue;
    if     ( fl_ctgry==5 || fl_ctgry==3 ) weight *= cal_weight_syst1( c_dststmc_cut, ievt, tag_cnt ); // syst from D** composition or Double D
    else if( fl_ctgry==2                ) weight *= cal_weight_syst2( c_dststmc_cut, ievt          ); // syst from cos resolution (norm)
    if( c_dststmc_cut->GetLeaf(nb_brname)->GetValue() > 0.0 ) hist1_eecl[2]->Fill( c_dststmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    else                                                      hist1_eecl[1]->Fill( c_dststmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    hist1_nb  [0]->Fill( c_dststmc_cut->GetLeaf(  nb_brname)->GetValue(), weight );
    hist1_eecl[0]->Fill( c_dststmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    hist2        ->Fill( c_dststmc_cut->GetLeaf(  nb_brname)->GetValue(),
			 c_dststmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
  }

  for( Int_t ievt=0; ievt<c_npmc_cut->GetEntries(); ievt++ ){
    Double_t weight = cal_weight( c_npmc_cut, ievt, (Double_t)nstream_npmc );
    //Double_t weight = cal_weight( c_npmc_cut, ievt, (Double_t)nstream_npmc, true ); // syst for modeling
    if( weight==0.0 ) continue;
    if     ( fl_ctgry==5 || fl_ctgry==3 ) weight *= cal_weight_syst1( c_npmc_cut, ievt, tag_cnt ); // syst from D** composition or Double D
    else if( fl_ctgry==2                ) weight *= cal_weight_syst2( c_npmc_cut, ievt          ); // syst from cos resolution (norm)
    if( c_npmc_cut->GetLeaf(nb_brname)->GetValue() > 0.0 ) hist1_eecl[2]->Fill( c_npmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    else                                                   hist1_eecl[1]->Fill( c_npmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    hist1_nb  [0]->Fill( c_npmc_cut->GetLeaf(  nb_brname)->GetValue(), weight );
    hist1_eecl[0]->Fill( c_npmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    hist2        ->Fill( c_npmc_cut->GetLeaf(  nb_brname)->GetValue(),
			 c_npmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
  }

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_nb  [ihist]->Print();
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_eecl[ihist]->Print();
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist2            ->Print();

  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_nb  [ihist]->SetMinimum(0.0);
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_eecl[ihist]->SetMinimum(0.0);

  for( Int_t ihist=0; ihist<nhist; ihist++ ){
    hist1_nb  [ihist]->SetLineColor  (ihist+1);
    hist1_nb  [ihist]->SetMarkerColor(ihist+1);
    hist1_eecl[ihist]->SetLineColor(ihist+1);
    hist1_eecl[ihist]->SetMarkerColor(ihist+1);
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH2D* hist2_nosmooth = (TH2D*)hist2->Clone( Form("nb_eecl_%s_lep%d_nosmooth",ctgry[fl_ctgry],fl_lep) );
  //can->cd(1); hist2        ->DrawClone("COLZTEXT");
  can->cd(1); hist2        ->DrawClone("COLZ");
  can->cd(2); hist1_nb  [0]->Draw();
  //can->cd(2); hist1_nb  [0]->DrawNormalized(); //tmppppp
  can->cd(3); hist1_eecl[0]->DrawClone();
  hist1_eecl[1]->DrawClone("same");
  hist1_eecl[2]->DrawClone("same");

  can->cd(6);
  //for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_eecl[ihist]->DrawNormalized( ihist ? "PEsame" : "PE" );
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_eecl[ihist]->Scale( 1.0/hist1_eecl[ihist]->Integral() );
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_eecl[ihist]->SetMaximum( 2.0*hist1_eecl[ihist]->GetMaximum() );
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_eecl[ihist]->SetMinimum( 0.0 );
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_eecl[ihist]->Draw( ihist ? "PEsame" : "PE" );
  

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  if( fl_smoothing ){
    can->cd(5);
    //TH1D* hist_proj_before = hist2->ProjectionX( "_proj_before", eecl_xbin-3, eecl_xbin-3 );
    TH1D* hist_proj_before = hist2->ProjectionX( "_proj_before", 1,eecl_xbin );
    hist_proj_before->SetMarkerColor(1);
    hist_proj_before->SetLineColor(1);
    hist_proj_before->SetLineWidth(2);
    hist_proj_before->Draw();
    smooth( hist2 );
    //TH1D* hist_proj_after = hist2->ProjectionX( "_proj_after", eecl_xbin-3, eecl_xbin-3 );
    TH1D* hist_proj_after = hist2->ProjectionX( "_proj_after", 1, eecl_xbin );
    hist_proj_after->SetMarkerColor(2);
    hist_proj_after->SetLineColor(2);
    hist_proj_after->Draw("same");
    can->cd(4);
    //hist2->Draw("COLZTEXT");
    hist2->Draw("COLZ");
  }
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  can->cd(3);
  TLegend* leg = new TLegend( 0.65,0.80,0.85,0.95 );  
  for( Int_t ihist=0; ihist<nhist; ihist++ ) leg->AddEntry( hist1_eecl[ihist], tagname[ihist], "PL" );
  leg->Draw();

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //can->Print( Form("pic/makepdf_%s_%d_lep%d_%s.ps",ctgry[fl_ctgry],tag_cnt,fl_lep,fl_par) );

  TFile outfile( Form("pic/makepdf_%s_%d_lep%d_%s.root", ctgry[fl_ctgry],tag_cnt,fl_lep,fl_par), "RECREATE" );
  can->Write();
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_nb  [ihist]->Write();
  for( Int_t ihist=0; ihist<nhist; ihist++ ) hist1_eecl[ihist]->Write();
  hist2->Write();
  hist2_nosmooth->Write();
  outfile.Close();
  
  
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();
  return 0;
}
