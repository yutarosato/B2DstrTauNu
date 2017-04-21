/*
 * nb_manip.cc
 *
 *  Created on: Oct 5, 2009
 *      Author: Michael Prim
 *     Contact: mprim@ekp.uni-karlsruhe.de
 *
 */

#include "nb_manip.h"


Int_t NB_manip::nnVars( const Char_t* tag_var, const Char_t* fl_type )
{
  if     ( strstr(tag_var, "test00"   )!=NULL ) return 5; // eecl[14], mmiss ^2[14], evis [14],      rm_bdir [18], cosdll[14]
  else if( strstr(tag_var, "test01"   )!=NULL ) return 5; // eecl[14], mmiss ^2[14], evis [14],      rm_bdir [14], cosdll[14] <- rm_bdir is discrete varialbe.
  else if( strstr(tag_var, "test02"   )!=NULL ) return 5; // eecl[14], mmiss ^2[14], evis [14], atan(rm_bdir)[14], cosdll[14] <- rm_bdir is converted by atan.
  else if( strstr(tag_var, "test03"   )!=NULL ) return 5; // eecl[14], mmiss2^2[14], evis2[14],      rm_bdir [18], cosdll[14] <- different calculation method for evis and mmiss
  else if( strstr(tag_var, "test04"   )!=NULL ) return 3; // mmiss^2[14],      cosdll [14], evis[14]
  else if( strstr(tag_var, "test05"   )!=NULL ) return 3; // mmiss^2[14],      cosdll [12], evis[14] <- different preprocessing flag(12 : no spline fit)
  else if( strstr(tag_var, "test06"   )!=NULL ) return 3; // mmiss^2[12],      cosdll [12], evis[12] <- different preprocessing flag(12 : no spline fit)
  else if( strstr(tag_var, "test07"   )!=NULL ) return 3; // mmiss^2[14], atan(cosdll)[14], evis[14] <- cosdll is converted by atan
  else if( strstr(tag_var, "test08"   )!=NULL ) return 3; // mmiss^2[14], atan(cosdll)[12], evis[14] <- different preprocessing flag(12 : no spline fit)
  else if( strstr(tag_var, "test09"   )!=NULL ) return 3; // mmiss^2[12], atan(cosdll)[12], evis[12] <- different preprocessing flag(12 : no spline fit)
  else if( strstr(tag_var, "test10"   )!=NULL ) return 2; // mmiss^2[14], evis[14] <- test with only two variables
  else if( strstr(tag_var, "test11"   )!=NULL ) return 2; // mmiss^2[12], evis[12]
  else if( strstr(tag_var, "test12"   )!=NULL ) return 4; // mmiss^2[14]  atan(cosdll)[14], evis[14], eecl[18]
  else if( strstr(tag_var, "test13"   )!=NULL ) return 3; // mmiss2^2[14],  cosdll [14], evis2[14] <- different calculation method for evis and mmiss
  else if( strstr(tag_var, "test14"   )!=NULL ) return 3; // mmiss2^2[14],  cosdll [12], evis2[14] <- different preprocessing flag(12 : no spline fit)
  else if( strstr(tag_var, "test15"   )!=NULL ) return 3; // mmiss2^2[12],  cosdll [12], evis2[12] <- different preprocessing flag(12 : no spline fit)
  else if( strstr(tag_var, "test16"   )!=NULL ) return 3; // mmiss2^2[14],  rm_bdir[14], evis2[14] <- different calculation method for evis and mmiss
  else if( strstr(tag_var, "test17"   )!=NULL ) return 3; // mmiss2^2[14],  rm_bdir[12], evis2[14] <- different preprocessing flag(12 : no spline fit)
  else if( strstr(tag_var, "test18"   )!=NULL ) return 3; // mmiss2^2[12],  rm_bdir[12], evis2[12] <- different preprocessing flag(12 : no spline fit)
  else if( strstr(tag_var, "test19"   )!=NULL ) return 1; // mmiss2^2[14] <- test with only one variables
  else if( strstr(tag_var, "test20"   )!=NULL ) return 1; // mmiss2^2[12]
  else if( strstr(tag_var, "test21"   )!=NULL ) return 1; // evis2   [14]
  else if( strstr(tag_var, "test22"   )!=NULL ) return 1; // evis2   [12]
  else if( strstr(tag_var, "test23"   )!=NULL ) return 1; // cosdll  [14]
  else if( strstr(tag_var, "test24"   )!=NULL ) return 1; // cosdll  [12]
  else if( strstr(tag_var, "test25"   )!=NULL ) return 2; // mmiss2^2[14], cosdll[14] <- test with only two variables
  else if( strstr(tag_var, "test26"   )!=NULL ) return 2; // mmiss2^2[12], cosdll[12]
  else if( strstr(tag_var, "test27"   )!=NULL ) return 2; // evis2   [14], cosdll[14]
  else if( strstr(tag_var, "test28"   )!=NULL ) return 2; // evis2   [12], cosdll[12]
  else std::cerr << "[ABORT] Invalid tag_var (in nnVars) : " << tag_var << std::endl, abort();
}


void NB_manip::Set_Par_Names( NeuroBayesTeacher *nb, std::fstream& var_names, const Char_t* tag_var, const Char_t* fl_type ){
  // 14(continuum var), 18(discrete var), 94(continuum var with delta func)
  Int_t cnt =0;

  if( strstr(tag_var,"test00")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "eecl"    );
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss"   );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis"    );
    add_variable_to_network( nb, var_names, cnt++, 18, "rm_bdir" ); //
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
  }else if( strstr(tag_var,"test01")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "eecl"    );
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss"   );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis"    );
    add_variable_to_network( nb, var_names, cnt++, 14, "rm_bdir" );
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
  }else if( strstr(tag_var,"test02")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "eecl"    );
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss"   );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis"    );
    add_variable_to_network( nb, var_names, cnt++, 14, "rm_bdir" );
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
  }else if( strstr(tag_var,"test03")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "eecl"    );
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss2"  ); //
    add_variable_to_network( nb, var_names, cnt++, 14, "evis2"   ); //
    add_variable_to_network( nb, var_names, cnt++, 18, "rm_bdir" ); //
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
  }else if( strstr(tag_var,"test04")!=NULL ||
	    strstr(tag_var,"test07")!=NULL
	    ){
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss"   );
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis"    );
  }else if( strstr(tag_var,"test05")!=NULL ||
	    strstr(tag_var,"test08")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss"   );
    add_variable_to_network( nb, var_names, cnt++, 12, "cosdll"  );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis"    );
  }else if( strstr(tag_var,"test06")!=NULL ||
	    strstr(tag_var,"test09")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 12, "mmiss"   );
    add_variable_to_network( nb, var_names, cnt++, 12, "cosdll"  );
    add_variable_to_network( nb, var_names, cnt++, 12, "evis"    );
  }else if( strstr(tag_var,"test10")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss"   );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis"    );
  }else if( strstr(tag_var,"test11")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 12, "mmiss"   );
    add_variable_to_network( nb, var_names, cnt++, 12, "evis"    );
  }else if( strstr(tag_var,"test12")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 18, "eecl"    );
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss"   );
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis"    );
  }else if( strstr(tag_var,"test13")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss2"  );
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis2"   );
  }else if( strstr(tag_var,"test14")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss2"  );
    add_variable_to_network( nb, var_names, cnt++, 12, "cosdll"  );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis2"   );
  }else if( strstr(tag_var,"test15")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 12, "mmiss2"  );
    add_variable_to_network( nb, var_names, cnt++, 12, "cosdll"  );
    add_variable_to_network( nb, var_names, cnt++, 12, "evis2"   );
  }else if( strstr(tag_var,"test16")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss2"  );
    add_variable_to_network( nb, var_names, cnt++, 14, "rm_bdir" );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis2"   );
  }else if( strstr(tag_var,"test17")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss2"  );
    add_variable_to_network( nb, var_names, cnt++, 12, "rm_bdir" );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis2"   );
  }else if( strstr(tag_var,"test18")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 12, "mmiss2"  );
    add_variable_to_network( nb, var_names, cnt++, 12, "rm_bdir" );
    add_variable_to_network( nb, var_names, cnt++, 12, "evis2"   );
  }else if( strstr(tag_var,"test19")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss2"  );
  }else if( strstr(tag_var,"test20")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 12, "mmiss2"  );
  }else if( strstr(tag_var,"test21")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "evis2"   );
  }else if( strstr(tag_var,"test22")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 12, "evis2"   );
  }else if( strstr(tag_var,"test23")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
  }else if( strstr(tag_var,"test24")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 12, "cosdll"  );
  }else if( strstr(tag_var,"test25")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "mmiss2"  );
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
  }else if( strstr(tag_var,"test26")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 12, "mmiss2"  );
    add_variable_to_network( nb, var_names, cnt++, 12, "cosdll"  );
  }else if( strstr(tag_var,"test27")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 14, "cosdll"  );
    add_variable_to_network( nb, var_names, cnt++, 14, "evis2"   );
  }else if( strstr(tag_var,"test28")!=NULL ){
    add_variable_to_network( nb, var_names, cnt++, 12, "cosdll"  );
    add_variable_to_network( nb, var_names, cnt++, 12, "evis2"   );
  }

  if( cnt != nnVars(tag_var,fl_type) ) std::cerr << "[ABORT] Wrong Set_Par_names() : " << cnt << std::endl, abort();
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void NB_manip::Input_Event( TTree* tree, Float_t* nnInput, Int_t i, const Char_t* tag_var, const Char_t* fl_type )
{
  tree->GetEntry(i);
  Int_t cnt=0;

  if( strstr(tag_var,"test00")!=NULL ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t eecl  = tree->GetLeaf("eecl")->GetValue();
    nnInput[cnt++] = ((Int_t)(eecl/0.050))*50; // [MeV], bin width = 50 MeV

    Double_t mmiss = tree->GetLeaf("mmiss")->GetValue();
    Double_t evis  = tree->GetLeaf("evis" )->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    //nnInput[cnt++] = fabs(mmiss);
    nnInput[cnt++] = evis;

    Double_t rm_bdir = tree->GetLeaf("rm_bdir")->GetValue();
    if( rm_bdir < 0 ) nnInput[cnt++] = 0;
    else              nnInput[cnt++] = 1;

    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
  }else if( strstr(tag_var,"test01")!=NULL ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t eecl  = tree->GetLeaf("eecl")->GetValue();
    nnInput[cnt++] = ((Int_t)(eecl/0.050))*50; // [MeV], bin width = 50 MeV

    Double_t mmiss = tree->GetLeaf("mmiss")->GetValue();
    Double_t evis  = tree->GetLeaf("evis" )->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    nnInput[cnt++] = evis;

    Double_t rm_bdir = tree->GetLeaf("rm_bdir")->GetValue();
    nnInput[cnt++] = rm_bdir; // 
    
    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
  }else if( strstr(tag_var,"test02")!=NULL ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t eecl  = tree->GetLeaf("eecl")->GetValue();
    nnInput[cnt++] = ((Int_t)(eecl/0.050))*50; // [MeV], bin width = 50 MeV

    Double_t mmiss = tree->GetLeaf("mmiss")->GetValue();
    Double_t evis  = tree->GetLeaf("evis" )->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    nnInput[cnt++] = evis;

    Double_t rm_bdir = tree->GetLeaf("rm_bdir")->GetValue();
    nnInput[cnt++] = atan(rm_bdir); //
    
    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
  }else if( strstr(tag_var,"test03")!=NULL ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t eecl  = tree->GetLeaf("eecl")->GetValue();
    nnInput[cnt++] = ((Int_t)(eecl/0.050))*50; // [MeV], bin width = 50 MeV

    Double_t mmiss = tree->GetLeaf("mmiss2")->GetValue(); //
    Double_t evis  = tree->GetLeaf("evis2" )->GetValue(); //
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    nnInput[cnt++] = evis;

    Double_t rm_bdir = tree->GetLeaf("rm_bdir")->GetValue();
    if( rm_bdir < 0 ) nnInput[cnt++] = 0;
    else              nnInput[cnt++] = 1;

    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
  }else if( strstr(tag_var,"test04")!=NULL ||
	    strstr(tag_var,"test05")!=NULL ||
	    strstr(tag_var,"test06")!=NULL
	    ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t mmiss = tree->GetLeaf("mmiss")->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
    Double_t evis  = tree->GetLeaf("evis" )->GetValue();
    nnInput[cnt++] = evis;
  }else if( strstr(tag_var,"test07")!=NULL ||
	    strstr(tag_var,"test08")!=NULL ||
	    strstr(tag_var,"test09")!=NULL
	    ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t mmiss = tree->GetLeaf("mmiss")->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    nnInput[cnt++] = atan(tree->GetLeaf("cosdll")->GetValue());
    Double_t evis  = tree->GetLeaf("evis" )->GetValue();
    nnInput[cnt++] = evis;
  }else if( strstr(tag_var,"test10")!=NULL ||
	    strstr(tag_var,"test11")!=NULL
	    ){
    Double_t mmiss = tree->GetLeaf("mmiss")->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    Double_t evis  = tree->GetLeaf("evis" )->GetValue();
    nnInput[cnt++] = evis;
  }else if( strstr(tag_var,"test12")!=NULL ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t eecl  = tree->GetLeaf("eecl")->GetValue();
    nnInput[cnt++] = ((Int_t)(eecl/0.050))*50; // [MeV], bin width = 50 MeV
    Double_t mmiss = tree->GetLeaf("mmiss")->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
    Double_t evis  = tree->GetLeaf("evis" )->GetValue();
    nnInput[cnt++] = evis;
  }else if( strstr(tag_var,"test13")!=NULL ||
	    strstr(tag_var,"test14")!=NULL ||
	    strstr(tag_var,"test15")!=NULL
	    ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t mmiss = tree->GetLeaf("mmiss2")->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
    Double_t evis  = tree->GetLeaf("evis2" )->GetValue();
    nnInput[cnt++] = evis;
  }else if( strstr(tag_var,"test16")!=NULL ||
	    strstr(tag_var,"test17")!=NULL ||
	    strstr(tag_var,"test18")!=NULL
	    ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t mmiss = tree->GetLeaf("mmiss2")->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    Double_t rm_bdir = tree->GetLeaf("rm_bdir")->GetValue();
    nnInput[cnt++] = rm_bdir; // 
    Double_t evis  = tree->GetLeaf("evis2" )->GetValue();
    nnInput[cnt++] = evis;
  }else if( strstr(tag_var,"test19")!=NULL ||
	    strstr(tag_var,"test20")!=NULL
	    ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t mmiss = tree->GetLeaf("mmiss2")->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
  }else if( strstr(tag_var,"test21")!=NULL ||
	    strstr(tag_var,"test22")!=NULL
	    ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t evis  = tree->GetLeaf("evis2" )->GetValue();
    nnInput[cnt++] = evis;
  }else if( strstr(tag_var,"test23")!=NULL ||
	    strstr(tag_var,"test24")!=NULL
	    ){ // +++++++++++++++++++++++++++++++++++++++
    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
  }else if( strstr(tag_var,"test25")!=NULL ||
	    strstr(tag_var,"test26")!=NULL
	    ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t mmiss = tree->GetLeaf("mmiss2")->GetValue();
    nnInput[cnt++] = mmiss*mmiss*fabs(mmiss)/mmiss;
    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
  }else if( strstr(tag_var,"test27")!=NULL ||
	    strstr(tag_var,"test28")!=NULL
	    ){ // +++++++++++++++++++++++++++++++++++++++
    Double_t evis  = tree->GetLeaf("evis2" )->GetValue();
    nnInput[cnt++] = evis;
    nnInput[cnt++] = tree->GetLeaf("cosdll")->GetValue();
  }
  
  // check for NaN
  for(int k = 0; k < NB_manip::nnVars(tag_var,fl_type); ++k){
    if( isnan(nnInput[k]) ) nnInput[k]=-999;
    if( isinf(nnInput[k]) ) nnInput[k]=-999; // added @20150305
  }
  
  if( cnt != nnVars(tag_var,fl_type) ) std::cerr << "[ABORT] Wrong Input_Event() : " << cnt << std::endl, abort();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


Int_t NB_manip::Train_Event( TTree* tree, NeuroBayesTeacher* nb, const Int_t fl_sb, const Int_t fl_mode,
			     const Char_t* tag_var, const Char_t* fl_type, std::fstream& var_names, const Int_t max_nevt )
{
  // counter for signal and backgronud samples
  Int_t   nevt = 0;
  Float_t nnInput[nnVars(tag_var,fl_type)]; // array for input vars (has to be float)
  
  //setup network topology
  nb->NB_DEF_NODE1(nnVars(tag_var,fl_type)+1); // nodes in input  layer
  nb->NB_DEF_NODE2(nnVars(tag_var,fl_type)+2); // nodes in hidden layer
  nb->NB_DEF_NODE3(1);                         // nodes in output layer
  
  Int_t nentries = (Int_t)tree->GetEntries();

  TFile file_ck( Form("check/ck_mode%d_%s_%s_flsb%d.root", fl_mode, tag_var, fl_type,fl_sb),"RECREATE" );
  TTree* tree_ck = new TTree( "h15","h15" );
  for( Int_t i=0; i<nnVars(tag_var,fl_type); i++ ) tree_ck->Branch( Form("var%d",i), &nnInput[i], Form("var%d/F",i) );

  for ( Int_t i=0; i < nentries; ++i ){
    if( i >= max_nevt ){
      std::cout << "Remaining events are removed to adjust # of events : " << i << std::endl;
      break;
    }
      
    Input_Event( tree, nnInput, i, tag_var, fl_type );
    tree_ck->Fill();
    
    if( i==0 ){
      var_names << "=============================================================================" << std::endl
		<< "evt = " << std::setw(5) << std::right << i << std::endl
		<< "=============================================================================" << std::endl;
      for( Int_t k=0; k<nnVars(tag_var,fl_type); k++ ){
	var_names << "var"
		  << std::setw( 3) << std::right << k << " : "
		  << std::setw(10) << std::right << nnInput[k]
		  << std::endl;
      }
      var_names << "=============================================================================" << std::endl;
      tree->Show(0);
    }
    nevt++;
    nb->SetTarget(fl_sb);
    nb->SetNextInput(nnVars(tag_var,fl_type), nnInput);
   
    if( i%25000 == 0        ) std::cout << i        << "/" << nentries << " events processed" << std::endl;
    if( i+1     == nentries ) std::cout << nentries << "/" << nentries << " events processed" << std::endl;
  }
  std::cout << "fl_sb(" << fl_sb << ") : " << nevt << std::endl;

  tree_ck->Write();
  file_ck.Close();
  return nentries;
}

Int_t NB_manip::Expert_Event( TTree* tree, Expert*  nb, const Char_t* outfile,
			      const Int_t fl_mode, const Char_t* tag_var, const Char_t* fl_type )
{
  Float_t nnOutput;                         // output of neural network
  Float_t nnInput[nnVars(tag_var,fl_type)]; // array for input vars (has to be float)
  Int_t   nentries = (Int_t)tree->GetEntries();

  TFile* rootf   = new TFile( outfile, "RECREATE" );
  TTree* newtree = tree->CloneTree( 0, "newtree" );

  newtree->Branch( Form("nb_mode%d_%s_%s", fl_mode,tag_var,fl_type),&nnOutput, Form("nb_mode%d_%s_%s/F",fl_mode,tag_var,fl_type) );
  
  for ( Int_t i=0; i < nentries; ++i ){
    //if( nentries>35000 && i%2==1 ) continue;
    //if( i%2!=1 ) continue;
    Input_Event( tree, nnInput, i, tag_var, fl_type );

    // status report
    //if( i%25000 == 0        )  std::cout << i        << "/" << nentries << " events processed" << std::endl;
    //if( i+1     == nentries )  std::cout << nentries << "/" << nentries << " events processed" << std::endl;
    nnOutput = nb->nb_expert(nnInput);
    
    newtree->Fill();
  }

  newtree->Write();
  return 0;
  
}

//========================================================================================================================================

void NB_manip::add_variable_to_network( NeuroBayesTeacher *nb, std::fstream& var_names, int index, int preproflag, const char* name )
{
  nb->SetIndividualPreproFlag(index,preproflag,name);
  var_names << std::setw(15) << std::right << name
	    << " "
	    << std::setw( 3) << std::right << preproflag
	    << std::endl;	
}
