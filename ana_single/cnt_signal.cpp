#include "draws_.h"
#include "draws_single.h"

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t* selection  = "-1.0 < cosdl1 && cosdl1 < 1.0";
const Char_t* infile_gmc = "/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk_single/through_cut/gMC_*.root";

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Int_t main( Int_t argc, Char_t** argv ){
  //gROOT->SetBatch(true); // tmpppppp
  TApplication app( "app", &argc, argv );
  TStyle* sty = Style(11);
  sty->SetTitleOffset(1.0,"z");
  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  Int_t tmp_cnt = 1;
  std::stringstream sTmp;

  //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // <TChain>
  /*
  sTmp.str("");
  sTmp.clear();
  sTmp << selection;
  std::cout << "[Cut] " << sTmp.str().c_str() << std::endl;

 TChain* c_gmc = new TChain(treename);
 std::cout << "[infile_gmc] " << infile_gmc << std::endl;
 std::cout << c_gmc->Add(infile_gmc)  << " files, ";
 std::cout << c_gmc->GetEntries()     << " entries -> ";
 
 TTree* c_gmc_cut = c_gmc->CopyTree( Form("(%s)", sTmp.str().c_str()) );
 std::cout << c_gmc_cut->GetEntries() << " entries"
	   << std::endl;
  */
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 const Int_t nhist = 5;
 const Char_t* histname [nhist] = { "nsig",    "bkg",     "sb",  "r_s",     "r_b"     };
 const Char_t* histtitle[nhist] = { "N_{sig}", "N_{bkg}", "S/B", "R_{sig}", "R_{bkg}" };
 TH1D** hist = new TH1D*[nhist];
 for( Int_t ihist=0; ihist<nhist; ihist++ ){
   hist[ihist] = new TH1D( histname[ihist], histtitle[ihist], nd_dec, 0, (Double_t)nd_dec );
   hist[ihist]->SetMarkerSize(0.7);
   hist[ihist]->SetMarkerColor(3);
   hist[ihist]->SetLineColor  (3);
   for( Int_t id=0; id<nd_dec; id++ ) ((TAxis*)hist[ihist]->GetXaxis())->SetBinLabel( id+1, d_dec_name[id] );
   hist[ihist]->LabelsDeflate("X");
   hist[ihist]->LabelsOption ("v");
   hist[ihist]->SetMarkerSize(1.2);
   hist[ihist]->SetLabelSize(0.05,"XY");
   hist[ihist]->SetLineColor(3);
 }
 
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 //Double_t nsig[nd_dec] = {0.0};
 //Double_t nbkg[nd_dec] = {0.0};
 Double_t nsig[nd_dec] = {52710, 4920,  2021, 4212,  77071, 14471,  10660, 2086,  57148, 11016,   2720,  25792,   4408,   2071,   3012};
 Double_t nbkg[nd_dec] = {59901, 8615, 11585, 6574, 291557, 33488, 397779, 3423, 246767, 248152, 13303, 253730, 195032, 183789, 226705};
 Double_t nsig_tot = 0;
 Double_t nbkg_tot = 0;
 for( Int_t id=0; id<nd_dec; id++ ){
   //nsig[id] = c_gmc_cut->GetEntries( Form("rm_d1==%d && self==2",d_dec[id] ) );
   //nbkg[id] = c_gmc_cut->GetEntries( Form("rm_d1==%d && self!=2",d_dec[id] ) );
   std::cout << std::setw( 5) << std::right << d_dec[id] << " : sig = "
	     << std::setw(10) << std::right << nsig [id] << " : bkg = "
	     << std::setw(10) << std::right << nbkg [id] << std::endl;
   nsig_tot += nsig[id];
   nbkg_tot += nbkg[id];
   hist[0]->SetBinContent( id+1, nsig[id]          );
   hist[1]->SetBinContent( id+1, nbkg[id]          );
   hist[2]->SetBinContent( id+1, nsig[id]/nbkg[id] );
 }
 std::cout << "nsig_tot = " << nsig_tot << std::endl;
 std::cout << "nbkg_tot = " << nbkg_tot << std::endl;
 for( Int_t id=0; id<nd_dec; id++ ){
   hist[3]->SetBinContent( id+1, nsig[id]/nsig_tot );
   hist[4]->SetBinContent( id+1, nbkg[id]/nbkg_tot );
 }
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 for( Int_t ihist=0; ihist<nhist; ihist++ ){
   for( Int_t id=0; id<nd_dec; id++ ){
     //hist[ihist]->SetBinContent( id+1, ((Int_t)(100*hist[ihist]->GetBinContent(id+1)))/100.0 );
   }
 }
 
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 TCanvas* can = Canvas( "can","can", nhist );
 can->Draw();
 for( Int_t ihist=0; ihist<nhist; ihist++ ){
   can->cd(ihist+1);
   if( ihist==0 || ihist==1 ) can->cd(ihist+1)->SetLogy();
   hist[ihist]->Draw("PL");
 }
 can->Update();
 can->Print("pic/cnt_signal_single_tag.eps");
 //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 std::cout << "finish" << std::endl;
 if( !gROOT->IsBatch() ) app.Run();
 
 return 0;
  
}
