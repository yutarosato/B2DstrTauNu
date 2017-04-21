#include "draws_.h"

Int_t main( Int_t argc, Char_t** argv ){
  TApplication app( "app", &argc, argv );
  Style(1);
  gROOT->SetBatch(!true);

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TCanvas* c1 = Canvas( "c1", "c1", 3, 2 );
  c1->Draw();

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  /*
  TChain* chain1_bug_nor = new TChain("h17");
  TChain* chain1_bug_sig = new TChain("h17");
  TChain* chain1_new_nor = new TChain("h17");
  TChain* chain1_new_sig = new TChain("h17");
  std::cout << "[BUG, nor] "
	    << chain1_bug_nor->Add("/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/20140313/bug/nor_kpi/*.root" ) << " files, ";
  std::cout << chain1_bug_nor->GetEntries()  << " entries" << std::endl;
  std::cout << "[BUG, sig] "
	    << chain1_bug_sig->Add("/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/20140313/bug/sig_kpi/*.root" ) << " files, ";
  std::cout << chain1_bug_sig->GetEntries()  << " entries" << std::endl;
  std::cout << "[NEW, nor] "
	    << chain1_new_nor->Add("/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/20140313/expand/nor_kpi/*.root" ) << " files, ";
  std::cout << chain1_new_nor->GetEntries()  << " entries" << std::endl;
  std::cout << "[NEW, sig] "
	    << chain1_new_sig->Add("/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/20140313/expand/sig_kpi/*.root" ) << " files, ";
  std::cout << chain1_new_sig->GetEntries()  << " entries" << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D* hist1_bug_sig_e = new TH1D( "bug_sig_e","bug_sig_e", 120, -10, 5 ); chain1_bug_sig->Project( "bug_sig_e", "cosdl1", "self==1&&rm_l1==10" ); hist1_bug_sig_e->SetLineColor(2); hist1_bug_sig_e->SetLineStyle(2);
  TH1D* hist1_bug_nor_e = new TH1D( "bug_nor_e","bug_nor_e", 120, -10, 5 ); chain1_bug_nor->Project( "bug_nor_e", "cosdl1", "self==2&&rm_l1==10" ); hist1_bug_nor_e->SetLineColor(2); hist1_bug_nor_e->SetLineStyle(2);
  TH1D* hist1_new_sig_e = new TH1D( "new_sig_e","new_sig_e", 120, -10, 5 ); chain1_new_sig->Project( "new_sig_e", "cosdl1", "self==1&&rm_l1==10" ); hist1_new_sig_e->SetLineColor(2); hist1_new_sig_e->SetLineStyle(1);
  TH1D* hist1_new_nor_e = new TH1D( "new_nor_e","new_nor_e", 120, -10, 5 ); chain1_new_nor->Project( "new_nor_e", "cosdl1", "self==2&&rm_l1==10" ); hist1_new_nor_e->SetLineColor(2); hist1_new_nor_e->SetLineStyle(1);

  TH1D* hist1_bug_sig_m = new TH1D( "bug_sig_m","bug_sig_m", 120, -10, 5 ); chain1_bug_sig->Project( "bug_sig_m", "cosdl1", "self==1&&rm_l1==1" ); hist1_bug_sig_m->SetLineColor(3); hist1_bug_sig_m->SetLineStyle(2);
  TH1D* hist1_bug_nor_m = new TH1D( "bug_nor_m","bug_nor_m", 120, -10, 5 ); chain1_bug_nor->Project( "bug_nor_m", "cosdl1", "self==2&&rm_l1==1" ); hist1_bug_nor_m->SetLineColor(3); hist1_bug_nor_m->SetLineStyle(2);
  TH1D* hist1_new_sig_m = new TH1D( "new_sig_m","new_sig_m", 120, -10, 5 ); chain1_new_sig->Project( "new_sig_m", "cosdl1", "self==1&&rm_l1==1" ); hist1_new_sig_m->SetLineColor(3); hist1_new_sig_m->SetLineStyle(1);
  TH1D* hist1_new_nor_m = new TH1D( "new_nor_m","new_nor_m", 120, -10, 5 ); chain1_new_nor->Project( "new_nor_m", "cosdl1", "self==2&&rm_l1==1" ); hist1_new_nor_m->SetLineColor(3); hist1_new_nor_m->SetLineStyle(1);


  TH1D* hist1_new_nor_e1 = new TH1D( "new_nor_e1","new_nor_e1", 120, -10, 5 ); chain1_new_nor->Project( "new_nor_e1", "cosdla1", "self==2&&rm_l1==10" ); hist1_new_nor_e1->SetLineColor(4); hist1_new_nor_e1->SetLineStyle(1);
  TH1D* hist1_new_nor_e2 = new TH1D( "new_nor_e2","new_nor_e2", 120, -10, 5 ); chain1_new_nor->Project( "new_nor_e2", "cosdlb1", "self==2&&rm_l1==10" ); hist1_new_nor_e2->SetLineColor(5); hist1_new_nor_e2->SetLineStyle(1);
  TH1D* hist1_new_nor_e3 = new TH1D( "new_nor_e3","new_nor_e3", 120, -10, 5 ); chain1_new_nor->Project( "new_nor_e3", "cosdlc1", "self==2&&rm_l1==10" ); hist1_new_nor_e3->SetLineColor(6); hist1_new_nor_e3->SetLineStyle(1);
  TH1D* hist1_new_nor_e4 = new TH1D( "new_nor_e4","new_nor_e4", 120, -10, 5 ); chain1_new_nor->Project( "new_nor_e4", "cosdld1", "self==2&&rm_l1==10" ); hist1_new_nor_e4->SetLineColor(7); hist1_new_nor_e4->SetLineStyle(1);
  TH1D* hist1_new_nor_e5 = new TH1D( "new_nor_e5","new_nor_e5", 120, -10, 5 ); chain1_new_nor->Project( "new_nor_e5", "cosdle1", "self==2&&rm_l1==10" ); hist1_new_nor_e5->SetLineColor(8); hist1_new_nor_e5->SetLineStyle(1);

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  c1->cd(1);
  hist1_new_sig_e->DrawNormalized();
  hist1_bug_sig_e->DrawNormalized("same");

  c1->cd(2);
  hist1_new_sig_m->DrawNormalized();
  hist1_bug_sig_m->DrawNormalized("same");

  c1->cd(3);
  hist1_new_nor_e->DrawNormalized();
  hist1_bug_nor_e->DrawNormalized("same");

  c1->cd(4);
  hist1_new_nor_m->DrawNormalized();
  hist1_bug_nor_m->DrawNormalized("same");

  c1->cd(5);
  hist1_new_nor_e->DrawNormalized();
  //hist1_new_nor_e1->DrawNormalized();
  hist1_new_nor_e2->DrawNormalized();
  //hist1_new_nor_e3->DrawNormalized();
  hist1_new_nor_e4->DrawNormalized();
  //hist1_new_nor_e5->DrawNormalized();
  */


  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

  TChain* chain2_bug_nor = new TChain("h15");
  TChain* chain2_bug_sig = new TChain("h15");
  TChain* chain2_new_nor = new TChain("h15");
  TChain* chain2_new_sig = new TChain("h15");
  std::cout << "[BUG, nor] "
	    << chain2_bug_nor->Add("/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/20140313/bug/nor_kpi/*.root" ) << " files, ";
  std::cout << chain2_bug_nor->GetEntries()  << " entries" << std::endl;
  std::cout << "[BUG, sig] "
	    << chain2_bug_sig->Add("/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/20140313/bug/sig_kpi/*.root" ) << " files, ";
  std::cout << chain2_bug_sig->GetEntries()  << " entries" << std::endl;
  std::cout << "[NEW, nor] "
	    << chain2_new_nor->Add("/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/20140313/expand/nor_kpi/*.root" ) << " files, ";
  std::cout << chain2_new_nor->GetEntries()  << " entries" << std::endl;
  std::cout << "[NEW, sig] "
	    << chain2_new_sig->Add("/home/belle/syutaro/dstrtaunu/modules/dstrtaunu/hbk/20140313/expand/sig_kpi/*.root" ) << " files, ";
  std::cout << chain2_new_sig->GetEntries()  << " entries" << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  TH1D* hist2_bug_sig = new TH1D( "bug_sig","bug_sig", 120, -10, 5 ); chain2_bug_sig->Project( "bug_sig", "rm_bdir", "self==1" ); hist2_bug_sig->SetLineColor(2); hist2_bug_sig->SetLineStyle(2);
  TH1D* hist2_bug_nor = new TH1D( "bug_nor","bug_nor", 120, -10, 5 ); chain2_bug_nor->Project( "bug_nor", "rm_bdir", "self==2" ); hist2_bug_nor->SetLineColor(3); hist2_bug_nor->SetLineStyle(2);
  TH1D* hist2_new_sig = new TH1D( "new_sig","new_sig", 120, -10, 5 ); chain2_new_sig->Project( "new_sig", "rm_bdir", "self==1" ); hist2_new_sig->SetLineColor(2); hist2_new_sig->SetLineStyle(1);
  TH1D* hist2_new_nor = new TH1D( "new_nor","new_nor", 120, -10, 5 ); chain2_new_nor->Project( "new_nor", "rm_bdir", "self==2" ); hist2_new_nor->SetLineColor(3); hist2_new_nor->SetLineStyle(1);


  TH1D* hist2_new_nor1 = new TH1D( "new_nor1","new_nor1", 120, -10, 5 ); chain2_new_nor->Project( "new_nor1", "rm_bdira", "self==2" ); hist2_new_nor1->SetLineColor(4); hist2_new_nor1->SetLineStyle(1);
  TH1D* hist2_new_nor2 = new TH1D( "new_nor2","new_nor2", 120, -10, 5 ); chain2_new_nor->Project( "new_nor2", "rm_bdirb", "self==2" ); hist2_new_nor2->SetLineColor(5); hist2_new_nor2->SetLineStyle(1);
  TH1D* hist2_new_nor3 = new TH1D( "new_nor3","new_nor3", 120, -10, 5 ); chain2_new_nor->Project( "new_nor3", "rm_bdirc", "self==2" ); hist2_new_nor3->SetLineColor(6); hist2_new_nor3->SetLineStyle(1);
  TH1D* hist2_new_nor4 = new TH1D( "new_nor4","new_nor4", 120, -10, 5 ); chain2_new_nor->Project( "new_nor4", "rm_bdird", "self==2" ); hist2_new_nor4->SetLineColor(7); hist2_new_nor4->SetLineStyle(1);
  TH1D* hist2_new_nor5 = new TH1D( "new_nor5","new_nor5", 120, -10, 5 ); chain2_new_nor->Project( "new_nor5", "rm_bdire", "self==2" ); hist2_new_nor5->SetLineColor(8); hist2_new_nor5->SetLineStyle(1);

  TH1D* hist2_new_sig1 = new TH1D( "new_sig1","new_sig1", 120, -10, 5 ); chain2_new_sig->Project( "new_sig1", "rm_bdira", "self==1" ); hist2_new_sig1->SetLineColor(4); hist2_new_sig1->SetLineStyle(1);
  TH1D* hist2_new_sig2 = new TH1D( "new_sig2","new_sig2", 120, -10, 5 ); chain2_new_sig->Project( "new_sig2", "rm_bdirb", "self==1" ); hist2_new_sig2->SetLineColor(5); hist2_new_sig2->SetLineStyle(1);
  TH1D* hist2_new_sig3 = new TH1D( "new_sig3","new_sig3", 120, -10, 5 ); chain2_new_sig->Project( "new_sig3", "rm_bdirc", "self==1" ); hist2_new_sig3->SetLineColor(6); hist2_new_sig3->SetLineStyle(1);
  TH1D* hist2_new_sig4 = new TH1D( "new_sig4","new_sig4", 120, -10, 5 ); chain2_new_sig->Project( "new_sig4", "rm_bdird", "self==1" ); hist2_new_sig4->SetLineColor(7); hist2_new_sig4->SetLineStyle(1);
  TH1D* hist2_new_sig5 = new TH1D( "new_sig5","new_sig5", 120, -10, 5 ); chain2_new_sig->Project( "new_sig5", "rm_bdire", "self==1" ); hist2_new_sig5->SetLineColor(8); hist2_new_sig5->SetLineStyle(1);
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  c1->cd(1);
  hist2_bug_nor->DrawNormalized();
  hist2_bug_sig->DrawNormalized("same");
  hist2_new_nor->DrawNormalized("same");
  hist2_new_sig->DrawNormalized("same");

  c1->cd(2);
  hist2_bug_nor->DrawNormalized();
  hist2_bug_sig->DrawNormalized("same");

  c1->cd(3);
  hist2_new_nor->DrawNormalized();
  hist2_new_sig->DrawNormalized("same");
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "[      bug    ] " << hist2_bug_nor ->Integral(0, hist2_bug_nor ->FindBin(-2-0.000001) )/hist2_bug_nor ->GetEntries() << std::endl;
  std::cout << "[  50mrad : e ] " << hist2_new_nor ->Integral(0, hist2_new_nor ->FindBin(-2-0.000001) )/hist2_new_nor ->GetEntries() << std::endl;
  std::cout << "[  50mrad : l ] " << hist2_new_nor1->Integral(0, hist2_new_nor1->FindBin(-2-0.000001) )/hist2_new_nor1->GetEntries() << std::endl;
  std::cout << "[ 100mrad : l ] " << hist2_new_nor2->Integral(0, hist2_new_nor2->FindBin(-2-0.000001) )/hist2_new_nor2->GetEntries() << std::endl;
  std::cout << "[ 100mrad : e ] " << hist2_new_nor3->Integral(0, hist2_new_nor3->FindBin(-2-0.000001) )/hist2_new_nor3->GetEntries() << std::endl;
  std::cout << "[ 200mrad : l ] " << hist2_new_nor4->Integral(0, hist2_new_nor4->FindBin(-2-0.000001) )/hist2_new_nor4->GetEntries() << std::endl;
  std::cout << "[ 200mrad : e ] " << hist2_new_nor5->Integral(0, hist2_new_nor5->FindBin(-2-0.000001) )/hist2_new_nor5->GetEntries() << std::endl;
  std::cout << std::endl;
  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "[      bug    ] " << hist2_bug_sig ->Integral(0, hist2_bug_sig ->FindBin(-2-0.000001) )/hist2_bug_sig ->GetEntries() << std::endl;
  std::cout << "[  50mrad : e ] " << hist2_new_sig ->Integral(0, hist2_new_sig ->FindBin(-2-0.000001) )/hist2_new_sig ->GetEntries() << std::endl;
  std::cout << "[  50mrad : l ] " << hist2_new_sig1->Integral(0, hist2_new_sig1->FindBin(-2-0.000001) )/hist2_new_sig1->GetEntries() << std::endl;
  std::cout << "[ 100mrad : l ] " << hist2_new_sig2->Integral(0, hist2_new_sig2->FindBin(-2-0.000001) )/hist2_new_sig2->GetEntries() << std::endl;
  std::cout << "[ 100mrad : e ] " << hist2_new_sig3->Integral(0, hist2_new_sig3->FindBin(-2-0.000001) )/hist2_new_sig3->GetEntries() << std::endl;
  std::cout << "[ 200mrad : l ] " << hist2_new_sig4->Integral(0, hist2_new_sig4->FindBin(-2-0.000001) )/hist2_new_sig4->GetEntries() << std::endl;
  std::cout << "[ 200mrad : e ] " << hist2_new_sig5->Integral(0, hist2_new_sig5->FindBin(-2-0.000001) )/hist2_new_sig5->GetEntries() << std::endl;

  // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  std::cout << "finish" << std::endl;
  if( !gROOT->IsBatch() ) app.Run();

  return 0;
}
