#include "draws_.h"
#include "draws_fit_.h"
#include "draws_roofit_.h"

const Bool_t  fl_use_dststmc = true;
const Bool_t  fl_use_npmc    = true;
const Bool_t  fl_smoothing   = true;
//const Char_t* weight_table   = "../npmc/table/dstrtaunu_dpi_lep_12_all/est_weight.root"; // old
const Char_t* weight_table   = "../npmc/new_table/2hdmII/dstrtaunu_dpi_lep_12_all/est_weight.root";
//const Char_t* weight_table   = "../npmc/new_table/R2LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppppp
//const Char_t* weight_table   = "../npmc/new_table/S1LQ/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppppp
//const Char_t* weight_table   = "../npmc/new_table/OPV1/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppppp
//const Char_t* weight_table   = "../npmc/new_table/OPV2/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppppp
//const Char_t* weight_table   = "../npmc/new_table/OPS1/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppppp
//const Char_t* weight_table   = "../npmc/new_table/OPS2/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppppp
//const Char_t* weight_table   = "../npmc/new_table/OPV1/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppppp
//const Char_t* weight_table   = "../npmc/new_table/OPV2/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppppp
//const Char_t* weight_table   = "../npmc/new_table/OPT/dstrtaunu_dpi_lep_12_all/est_weight.root"; // tmpppppp
const Bool_t  fl_2sveto      = true; // veto D(2S) and D*(2S)

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Int_t nctgry          = 10;
const Char_t* ctgry    [nctgry] = { "other", "sig", "nor", "dstst", "doubled", "fake_other", "fake_sig", "fake_nor", "fake_dstst", "fake_doubled" };
const Char_t* selection[nctgry] = { "0", // [0] other
				    "(self==1||(self==0&&gm_semi>0&&dst1self==1&&dst2self==1))",                                            // [1] sig 
				    "(self==2||(self==0&&gm_semi<0&&dst1self==1&&dst2self==1))",                                            // [2] nor
				    "(self==-5&&dst1self==1&&dst2self==1)",                                                                 // [3] D**
				    "(self==-3&&dst1self==1&&dst2self==1)",                                                                 // [4] double D
				    "(self< 0 &&!(dst1self==1&&dst2self==1)&&self!=-5&&self!=-3&&!(self==-6&&(gm_ddst1==3||gm_ddst2==3)))", // [5] faked(other)
				    "(self==0 &&!(dst1self==1&&dst2self==1)&&gm_semi>0)",                                                   // [6] faked(sig)
				    "(self==0 &&!(dst1self==1&&dst2self==1)&&gm_semi<0)",                                                   // [7] faked(nor)
				    "((self==-5||(self==-6&&(gm_ddst1==3||gm_ddst2==3)))&&!(dst1self==1&&dst2self==1))",                    // [8] faked(D**)
				    "(self==-3&&!(dst1self==1&&dst2self==1))",                                                              // [9] faked(double D)
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t*  infile_gmc      = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/merge_cut_bcs_vtx/gMC_*s0[0-9]*.root";
const Double_t nstream_gmc     = 10;
const Char_t*  infile_dststmc  = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/DssMC_weight_nb_cut_bcs_vtx/DssMC_*.root";
const Double_t nstream_dststmc = 2.7118;
const Char_t*  infile_npmc     = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/0p0_weight_nb_cut_bcs_vtx/npMC_*.root";
const Double_t nstream_npmc    = 40;

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
	      << " (int)ctgry (char)param [(int)fl_lep]" << std::endl
	      << "ctgry  : 0(other), 1(sig), 2(nor), 3(D**), 4(Double D), 5(fake[sig]), 6(fake[nor]), 7(fake[D**]), 8(fake[Double D])" << std::endl
	      << " param : 0p0, 0p1, ... 1p0" << std::endl
	      << "fl_lep : 10(e), 1(mu), 0(l)"
	      << std::endl, abort();
  Int_t  fl_ctgry = atoi(app.Argv(1));
  Char_t fl_par[32];
  strcpy( fl_par, app.Argv(2) );
  Int_t fl_lep = 0;
  if( app.Argc()==4 ) fl_lep = atoi(app.Argv(3));

  Read_Data( "calib.dat", true );
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::stringstream sTmp;
  sTmp << Form("eecl<%f",eecl_xmax);
  sTmp << " && " << makeCut_dststmc( fl_use_dststmc ).c_str();
  sTmp << " && " << makeCut_npmc   ( fl_use_npmc    ).c_str();
  if( fl_lep ) sTmp << Form(" && ( (cosdll==cosdl1 && rm_l1==%d) || (cosdll==cosdl2 && rm_l2==%d) )",fl_lep,fl_lep);
  if( fl_ctgry==0 ) sTmp << " && " << makeCut_remain(selection,nctgry).c_str();
  else              sTmp << " && " << selection[fl_ctgry];

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
    hist1_nb  [ihist] = new TH1D( Form(  "nb_%s_%s_lep%d",ctgry[fl_ctgry],tagname[ihist],fl_lep), Form(  "nb_%s_%s_lep%d_%s",ctgry[fl_ctgry],tagname[ihist],fl_lep,fl_par),   nb_xbin,   nb_xmin,   nb_xmax );
    hist1_eecl[ihist] = new TH1D( Form("eecl_%s_%s_lep%d",ctgry[fl_ctgry],tagname[ihist],fl_lep), Form("eecl_%s_%s_lep%d_%s",ctgry[fl_ctgry],tagname[ihist],fl_lep,fl_par), eecl_xbin, eecl_xmin, eecl_xmax );
    hist1_nb  [ihist]->Sumw2();
    hist1_eecl[ihist]->Sumw2();
    hist1_nb  [ihist]->SetXTitle( "NB" );
    hist1_eecl[ihist]->SetXTitle( "E_{ECL} [GeV]" );
  }
  TH2D* hist2 = new TH2D( Form("nb_eecl_%s_lep%d",ctgry[fl_ctgry],fl_lep), Form("nb_eecl_%s_lep%d_%s",ctgry[fl_ctgry],fl_lep,fl_par),
			    nb_xbin,   nb_xmin,   nb_xmax,
			  eecl_xbin, eecl_xmin, eecl_xmax
			  );
  hist2->Sumw2();
  hist2->SetXTitle( "NB"            );
  hist2->SetYTitle( "E_{ECL} [GeV]" );
  
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  for( Int_t ievt=0; ievt<c_gmc_cut->GetEntries(); ievt++ ){
    Double_t weight = cal_weight( c_gmc_cut, ievt, (Double_t)nstream_gmc );
    if( fl_2sveto &&
	( c_gmc_cut->GetLeaf("ctgrsyst")->GetValue()==7 ||
	  c_gmc_cut->GetLeaf("ctgrsyst")->GetValue()==8 )
	) weight = 0;
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
    if( fl_2sveto &&
	( c_dststmc_cut->GetLeaf("ctgrsyst")->GetValue()==7 ||
	  c_dststmc_cut->GetLeaf("ctgrsyst")->GetValue()==8 )
	) weight = 0;
    if( weight==0.0 ) continue;
    ///* for fixing bug in dedicated D** MC @ 20160522
    

    //*/
    if( c_dststmc_cut->GetLeaf(nb_brname)->GetValue() > 0.0 ) hist1_eecl[2]->Fill( c_dststmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    else                                                      hist1_eecl[1]->Fill( c_dststmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    hist1_nb  [0]->Fill( c_dststmc_cut->GetLeaf(  nb_brname)->GetValue(), weight );
    hist1_eecl[0]->Fill( c_dststmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
    hist2        ->Fill( c_dststmc_cut->GetLeaf(  nb_brname)->GetValue(),
			 c_dststmc_cut->GetLeaf(eecl_brname)->GetValue(), weight );
  }


  // NP weight file
  TFile* npweight_file = new TFile( weight_table );
  if( npweight_file->IsZombie() ) std::cerr << "[ABORT] can not find weight-file for " << weight_table << std::endl, abort();
  TGraphErrors* npweight_table = (TGraphErrors*)npweight_file->Get( Form( "np_%s",fl_par) );
  if( npweight_table==NULL ) std::cerr << "[ABORT] can not find weight-table for " << fl_par << std::endl, abort();

  for( Int_t ievt=0; ievt<c_npmc_cut->GetEntries(); ievt++ ){
    Double_t weight = cal_weight( c_npmc_cut, ievt, (Double_t)nstream_npmc );
    if( fl_2sveto &&
	( c_npmc_cut->GetLeaf("ctgrsyst")->GetValue()==7 ||
	  c_npmc_cut->GetLeaf("ctgrsyst")->GetValue()==8 )
	) weight = 0;
    if( weight==0.0 ) continue;
    Double_t val[np::nvar];
    for( Int_t ivar=0; ivar<np::nvar; ivar++ ) val[ivar] = c_npmc_cut->GetLeaf(np::brname[ivar])->GetValue(); // reproduce NP distribution by re-weighted SM distribution
    Int_t gindex = getGIndex( val );
    Double_t npweight  = npweight_table->GetY()[gindex];
    Double_t npweightE = npweight_table->GetErrorY(gindex);
    weight *= npweight; // NP weight
    
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
  hist2->Print();

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
  //can->Print( Form("pdf/makepdf_%s_lep%d_%s.ps",ctgry[fl_ctgry],fl_lep, fl_par) );
  //can->Print( Form("pdf/makepdf_%s_lep%d_%s.eps",ctgry[fl_ctgry],fl_lep, fl_par) ); // for belle note
  can->Print( Form("pic/makepdf_%s_lep%d_%s.eps",ctgry[fl_ctgry],fl_lep, fl_par) ); // for belle note

  TFile outfile( Form("pdf/makepdf_%s_lep%d_%s.root", ctgry[fl_ctgry], fl_lep, fl_par), "RECREATE" );
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
