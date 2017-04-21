#ifndef DRAWS_FIT_H
#define DRAWS_FIT_H

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//const Double_t convert_factor_nsig  = (0.0142/0.0533/0.92)/203.529;           // 1.4228e-3  @ 6stream
//const Double_t convert_factor_rdstr = (0.0142/0.0533/0.92)/(203.529/2758.28); // 3.924      @ 6stream
//const Double_t convert_factor_nsig  = (0.0142/0.0533/0.92)/202.661;           // @ 10streams
//const Double_t convert_factor_rdstr = (0.0142/0.0533/0.92)/(202.661/2750.01); // @ 10streams
//const Double_t convert_factor_nsig  = (0.0142/0.0533/0.92)/202.238;           // @ 10streams
//const Double_t convert_factor_rdstr = (0.0142/0.0533/0.92)/(202.238/2737.1);  // @ 10streams
/*
const Double_t convert_factor_nsig[3] = { (0.0142/0.0533/0.92)/202.238, // l
					  (0.0142/0.0533/0.92)/116.415, // e
					  (0.0142/0.0533/0.92)/85.227   // mu
};
const Double_t convert_factor_rdstr[3] = { (0.0142/0.0533/0.92)/(202.238/2737.1 ), // l
					   (0.0142/0.0533/0.92)/(116.415/1443.57), // e
					   (0.0142/0.0533/0.92)/( 85.227/1293.53)  // mu
};
*/

// 0.01247 :   NP  MC input BF(B -> D* tau nu)
// 0.0142  : Belle MC input BF(B -> D* tau nu)
// 0.0533  : Belle MC input BF(B -> D* l   nu)
// 0.92    : weight for B -> D* lnu
/*
// gMC
const Double_t input_BF = 0.0142;
const Double_t nsig_nominal_exp[3] = { 198.345,  114.311,  84.0347};
const Double_t nnor_nominal_exp[3] = {2686.83,  1417.27, 1269.56  };
*/

///*
// NPMC
const Double_t input_BF = 0.01247;

//const Double_t nnor_nominal_exp[3] = {2686.91, 1417.35, 1269.56 }; // (signal MC : 10 streams)
//const Double_t nsig_nominal_exp[3] = { 190.19,  117.972,  72.2178}; // 0.0 (signal MC : 10 streams)
//const Double_t nsig_nominal_exp[3] = { 191.578, 118.862,  72.7159}; // 0.1
//const Double_t nsig_nominal_exp[3] = { 191.03,  118.049,  72.9812}; // 0.2
//const Double_t nsig_nominal_exp[3] = { 190.815, 117.868,  72.9473}; // 0.3
//const Double_t nsig_nominal_exp[3] = { 190.53,  117.702,  72.8286}; // 0.4
//const Double_t nsig_nominal_exp[3] = { 189.296, 116.673,  72.6232}; // 0.5
//const Double_t nsig_nominal_exp[3] = { 186.536, 115.082,  71.4537}; // 0.6
//const Double_t nsig_nominal_exp[3] = { 183.72,  114.05,   69.6704}; // 0.7
//const Double_t nsig_nominal_exp[3] = { 180.403, 112.576,  67.8272}; // 0.8
//const Double_t nsig_nominal_exp[3] = { 178.872, 112.358,  66.5141}; // 0.9
//const Double_t nsig_nominal_exp[3] = { 176.94,  111.591,  65.349 }; // 1.0


const Double_t nnor_nominal_exp[3] = {2686.85, 1417.29, 1269.56 }; // (signal MC : 40 streams)
const Double_t nsig_nominal_exp[3] = { 186.799,  116.126,  70.6731}; // 0.0 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.679,  116.537,  71.1428}; // 0.1 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.127,  116.124,  71.0028}; // 0.2 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.859,  115.991,  70.8679}; // 0.3 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.252,  115.642,  70.6101}; // 0.4 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 184.823,  114.725,  70.0985}; // 0.5 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 182.94,   113.829,  69.1102}; // 0.6 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 180.915,  113.005,  67.9108}; // 0.7 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 178.61,   112.053,  66.5577}; // 0.8 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 177.536,  111.737,  65.7992}; // 0.9 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 176.75,   111.614,  65.1362}; // 1.0 (signal MC : 40 streams)

//const Double_t nsig_nominal_exp[3] = { 184.774,  116.304,  68.4701}; // R2_m0p150 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 184.667,  115.978,  68.689 }; // R2_m0p100 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 185.75,   115.868,  69.882 }; // R2_m0p040 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 185.56,   115.705,  69.8557}; // R2_m0p030 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.799,  116.126,  70.6731}; // R2_0p000  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 197.638,  121.977,  75.6613}; // R2_0p090  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 212.066,  131.454,  80.6114}; // R2_0p180  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 216.185,  135.512,  80.6731}; // R2_0p260  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 214.672,  135.446,  79.2256}; // R2_0p340  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 214.014,  135.235,  78.7794}; // R2_0p360  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 212.252,  134.385,  77.8678}; // R2_0p400  (signal MC : 40 streams)

//const Double_t nsig_nominal_exp[3] = { 183.869,  115.811,  68.0579}; // S1_m0p150 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 183.943,  115.353,  68.5901}; // S1_m0p100 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 185.41,   115.644,  69.7656}; // S1_m0p040 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 185.71,   115.798,  69.9115}; // S1_m0p030 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.799,  116.126,  70.6731}; // S1_0p000  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 196.627,  122.014,  74.6133}; // S1_0p090  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 204.515,  127.803,  76.7122}; // S1_0p180  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 207.247,  130.335,  76.9121}; // S1_0p260  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 206.698,  130.719,  75.9978}; // S1_0p340  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 206.544,  130.747,  75.7973}; // S1_0p360  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 205.831,  130.505,  75.326 }; // S1_0p400  (signal MC : 40 streams)

//const Double_t nsig_nominal_exp[3] = { 187.634,  116.556,  71.077  }; // OPV1_m2p10 (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 189.504,  119.789,  69.7154 }; // OPV2_1p88  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.586,  116.835,  70.751  }; // OPS1_1p05  (signal MC : 40 streams)

//const Double_t nsig_nominal_exp[3] = { 178.166,  111.938,  66.2287  }; // OPS1_m5p00  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 179.741,  112.494,  67.2475  }; // OPS1_m4p00  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 181.833,  113.478,  68.355   }; // OPS1_m3p00  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 183.892,  114.411,  69.4809  }; // OPS1_m2p00  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.124,  115.634,  70.4896  }; // OPS1_m1p00  (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.799,  116.126,  70.6731  }; // OPS1_0p00   (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.466,  116.898,  70.568   }; // OPS1_1p00   (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.279,  116.777,  70.5018  }; // OPS1_1p05   (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.79,   116.888,  69.9017  }; // OPS1_2p00   (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.082,  116.811,  69.2709  }; // OPS1_3p00   (signal MC : 40 streams)

//const Double_t nsig_nominal_exp[3] = { 186.231,  116.937,  69.2938  }; // OPS2_m3p00   (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.941,  117.041,  69.9004  }; // OPS2_m2p00   (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.300,  116.784,  70.5155  }; // OPS2_m1p00   (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.799,  116.126,  70.6731  }; // OPS2_0p00    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.086,  115.651,  70.4351  }; // OPS2_1p00    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 184.124,  114.513,  69.6102  }; // OPS2_2p00    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 181.795,  113.366,  68.428   }; // OPS2_3p00    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 179.567,  112.419,  67.1476  }; // OPS2_4p00    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 177.953,  111.808,  66.1457  }; // OPS2_5p00    (signal MC : 40 streams)

//const Double_t nsig_nominal_exp[3] = { 187.393,  116.632,  70.7606  }; // OPV1_m2p50    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.387,  116.548,  70.8392  }; // OPV1_m2p10    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.551,  116.684,  70.8677  }; // OPV1_m2p00    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.481,  116.544,  70.9375  }; // OPV1_m1p50    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 208.51,   131.364,  77.1457  }; // OPV1_m1p00    (signal MC : 40 streams) // invalid
//const Double_t nsig_nominal_exp[3] = { 187.305,  116.57,   70.7351  }; // OPV1_m0p50    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.799,  116.126,  70.6731  }; // OPV1_0p00     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.134,  116.41,   70.724   }; // OPV1_0p50     (signal MC : 40 streams)

//const Double_t nsig_nominal_exp[3] = { 183.192,  114.569,  68.6235  }; // OPV2_m0p50    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.799,  116.126,  70.6731  }; // OPV2_0p00     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 201.241,  124.07,   77.171   }; // OPV2_0p50     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 218.033,  135.782,  82.2511  }; // OPV2_1p00     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 196.305,  124.398,  71.9074  }; // OPV2_1p50     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 189.187,  119.903,  69.2835  }; // OPV2_1p88     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 187.851,  119.164,  68.6872  }; // OPV2_2p00     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 184.675,  117.081,  67.5945  }; // OPV2_2p50     (signal MC : 40 streams)

//const Double_t nsig_nominal_exp[3] = { 184.356,  115.75,   68.6057  }; // OPT_m0p15    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 184.691,  115.305,  69.3865  }; // OPT_m0p07    (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 186.799,  116.126,  70.6731  }; // OPT_0p00     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 194.313,  120.171,  74.1414  }; // OPT_0p07     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 207.023,  128.073,  78.9505  }; // OPT_0p15     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 215.363,  134.076,  81.2865  }; // OPT_0p22     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 218.463,  137.122,  81.3404  }; // OPT_0p30     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 217.696,  137.196,  80.5002   }; // OPT_0p36     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 217.573,  137.279,  80.294   }; // OPT_0p37     (signal MC : 40 streams)
//const Double_t nsig_nominal_exp[3] = { 215.156,  135.968,  79.1877  }; // OPT_0p45     (signal MC : 40 streams)

const Double_t convert_factor_nsig[3] = { (input_BF/0.0533/0.92)/nsig_nominal_exp[0], // l
					  (input_BF/0.0533/0.92)/nsig_nominal_exp[1], // e
					  (input_BF/0.0533/0.92)/nsig_nominal_exp[2], // mu
};
const Double_t convert_factor_rdstr[3] = { (input_BF/0.0533/0.92)/(nsig_nominal_exp[0]/nnor_nominal_exp[0]), // l
					   (input_BF/0.0533/0.92)/(nsig_nominal_exp[1]/nnor_nominal_exp[1]), // e
					   (input_BF/0.0533/0.92)/(nsig_nominal_exp[2]/nnor_nominal_exp[2]), // mu
};
const Int_t lep_index [11] = { 0, 2,-1,-1,-1,-1,-1,-1,-1,-1,1};

const Char_t*  calib_file           = "calib.dat";
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Char_t*  treename    = "h15";
const Char_t*  nb_brname   = "nb_mode0_test13_nor";
const Char_t*  eecl_brname = "eecl";
const Int_t    eecl_xbin   =   24; // default
const Double_t eecl_xmin   =  0.0;
const Double_t eecl_xmax   =  1.2;
const Int_t      nb_xbin   =   30; // default
const Double_t   nb_xmin   = -1.0;
const Double_t   nb_xmax   =  1.0;

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// correction factor
// D
Double_t R_ss_d[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_sb_d[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_bb_d[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0,
			   1.0, 1.0, 1.0, 1.0, 1.0};

Double_t R_ss_dE[nd_dec] = {0.0};
Double_t R_sb_dE[nd_dec] = {0.0};
Double_t R_bb_dE[nd_dec] = {0.0};
// D*
Double_t R_ss_dstr[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_sb_dstr[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0};
Double_t R_bb_dstr[nd_dec] = {1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0,
			      1.0, 1.0, 1.0, 1.0, 1.0};

Double_t R_ss_dstrE[nd_dec] = {0.0};
Double_t R_sb_dstrE[nd_dec] = {0.0};
Double_t R_bb_dstrE[nd_dec] = {0.0};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void Read_Data( const Char_t* infile, const Bool_t fl_message=!true ){
  Char_t buf[2048];
  const Int_t ndata = 21;
  Double_t data[ndata] = {0};
  ifstream fin( infile );
  if( !fin ){
    std::cout << "[WARNING] can not find a file" << std::endl;
    return;
  }
  while( !fin.eof() ){
    fin.getline( buf,1024 );
    if     ( buf[0] == '#' ) continue; // comment line
    else if( buf[0] == '*' ) break;    // finish
    else{
      std::istringstream sTmp(buf);
      sTmp >> data[ 0] >> data[ 1] >> data[ 2] >> data[ 3] >> data[ 4]
	   >> data[ 5] >> data[ 6] >> data[ 7] >> data[ 8] >> data[ 9]
	   >> data[10] >> data[11] >> data[12] >> data[13] >> data[14]
	   >> data[15] >> data[16] >> data[17] >> data[18] >> data[19]
	   >> data[20];

      if( (Int_t)data[1]==411 ){
	for( Int_t i=0; i<nd_dec; i++ ){
	  if( d_dec_chg[i]==1 ){
	    R_ss_dstr [i] = data[12];
	    R_ss_dstrE[i] = data[13];
	    R_sb_dstr [i] = data[15];
	    R_sb_dstrE[i] = data[16];
	    R_bb_dstr [i] = data[18];
	    R_bb_dstrE[i] = data[19];
	  }
	}
      }else if( (Int_t)data[1]==421 ){
	for( Int_t i=0; i<nd_dec; i++ ){
	  if( d_dec_chg[i]==0 ){
	    R_ss_dstr [i] = data[12];
	    R_ss_dstrE[i] = data[13];
	    R_sb_dstr [i] = data[15];
	    R_sb_dstrE[i] = data[16];
	    R_bb_dstr [i] = data[18];
	    R_bb_dstrE[i] = data[19];
	  }
	}
      }else{
	R_ss_d [(Int_t)data[0]] = data[ 3];
	R_ss_dE[(Int_t)data[0]] = data[ 4];
	R_sb_d [(Int_t)data[0]] = data[ 6];
	R_sb_dE[(Int_t)data[0]] = data[ 7];
	R_bb_d [(Int_t)data[0]] = data[ 9];
	R_bb_dE[(Int_t)data[0]] = data[10];
	
	R_ss_dstr [(Int_t)data[0]] = data[12];
	R_ss_dstrE[(Int_t)data[0]] = data[13];
	R_sb_dstr [(Int_t)data[0]] = data[15];
	R_sb_dstrE[(Int_t)data[0]] = data[16];
	R_bb_dstr [(Int_t)data[0]] = data[18];
	R_bb_dstrE[(Int_t)data[0]] = data[19];
      }
    }
  }
  if( fl_message ){
    std::cout << std::setw(28) << std::right << " DECAY MODE " << " : "
	      << std::setw(33) << std::left << " <TRUE D > "   << " : "
	      << std::setw(33) << std::left << " <FAKE D > "   << " : "
	      << std::setw(33) << std::left << " <TRUE D*> "   << " : "
	      << std::setw(33) << std::left << " <FAKE D*> "
	      << std::endl;
    for( Int_t idec=0; idec<nd_dec; idec++ ) std::cout << std::setw(20) << std::right << d_dec_name [idec] << "("
						       << std::setw( 6) << std::right << d_dec      [idec] << ") : "
						       << std::setw(15) << std::right << R_ss_d     [idec] << " + "
						       << std::setw(15) << std::right << R_ss_dE    [idec] << " : "
						       << std::setw(15) << std::right << R_bb_d     [idec] << " + "
						       << std::setw(15) << std::right << R_bb_dE    [idec] << " : "
						       << std::setw(15) << std::right << R_ss_dstr  [idec] << " + "
						       << std::setw(15) << std::right << R_ss_dstrE [idec] << " : "
						       << std::setw(15) << std::right << R_bb_dstr  [idec] << " + "
						       << std::setw(15) << std::right << R_bb_dstrE [idec] << " : "
						       << std::endl;
  }


  return;
}


void Fluct_calib( const Bool_t fl_message=!true ){
  for( Int_t idec=0; idec<nd_dec; idec++ ){
    R_ss_d   [idec] = gRandom->Gaus( R_ss_d   [idec], R_ss_dE   [idec] );
    R_bb_d   [idec] = gRandom->Gaus( R_bb_d   [idec], R_bb_dE   [idec] );
    R_ss_dstr[idec] = gRandom->Gaus( R_ss_dstr[idec], R_ss_dstrE[idec] );
    R_bb_dstr[idec] = gRandom->Gaus( R_bb_dstr[idec], R_bb_dstrE[idec] );
  }

  if( fl_message ){
    std::cout << std::setw(28) << std::right << " DECAY MODE " << " : "
	      << std::setw(33) << std::left << " <TRUE D > "   << " : "
	      << std::setw(33) << std::left << " <FAKE D > "   << " : "
	      << std::setw(33) << std::left << " <TRUE D*> "   << " : "
	      << std::setw(33) << std::left << " <FAKE D*> "
	      << std::endl;
    for( Int_t idec=0; idec<nd_dec; idec++ ) std::cout << std::setw(20) << std::right << d_dec_name [idec] << "("
						       << std::setw( 6) << std::right << d_dec      [idec] << ") : "
						       << std::setw(15) << std::right << R_ss_d     [idec] << " + "
						       << std::setw(15) << std::right << R_ss_dE    [idec] << " : "
						       << std::setw(15) << std::right << R_bb_d     [idec] << " + "
						       << std::setw(15) << std::right << R_bb_dE    [idec] << " : "
						       << std::setw(15) << std::right << R_ss_dstr  [idec] << " + "
						       << std::setw(15) << std::right << R_ss_dstrE [idec] << " : "
						       << std::setw(15) << std::right << R_bb_dstr  [idec] << " + "
						       << std::setw(15) << std::right << R_bb_dstrE [idec] << " : "
						       << std::endl;
  }
  return;
}

Double_t cal_weight( TTree* f_chain, Int_t f_ievt, Double_t f_nstream, Bool_t fl_syst=!true ){ // if "fl_syst = true", factor for semileptonic modeling will be fluctuated
  f_chain->GetEntry(f_ievt);
  Double_t weight = 1.0;
  //++++++++++++++++++++++++++++
  if( fl_syst ){
    weight *= gRandom->Gaus( f_chain->GetLeaf("w1_mc")->GetValue(), f_chain->GetLeaf("w1_mc_etot")->GetValue() ); // apply crrection for modeling of B1
    weight *= gRandom->Gaus( f_chain->GetLeaf("w2_mc")->GetValue(), f_chain->GetLeaf("w2_mc_etot")->GetValue() ); // apply crrection for modeling of B2
  }else{
    weight *= f_chain->GetLeaf("w1_mc")->GetValue(); // apply crrection for modeling of B1
    weight *= f_chain->GetLeaf("w2_mc")->GetValue(); // apply crrection for modeling of B2
  }
  if( f_chain->GetLeaf("flmcddst")->GetValue()==0 ){ // only for gMC
    weight *= f_chain->GetLeaf("w1_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B1
    weight *= f_chain->GetLeaf("w2_bf")->GetValue(); // apply crrection for semileptonic branching fraction of B2
  }
  if( f_chain->GetLeaf("d1self"  )->GetValue()==1 ) weight *= R_ss_d   [dec_index((Int_t)(f_chain->GetLeaf("rm_d1")->GetValue()))];
  else                                              weight *= R_bb_d   [dec_index((Int_t)(f_chain->GetLeaf("rm_d1")->GetValue()))];
  if( f_chain->GetLeaf("d2self"  )->GetValue()==1 ) weight *= R_ss_d   [dec_index((Int_t)(f_chain->GetLeaf("rm_d2")->GetValue()))];
  else                                              weight *= R_bb_d   [dec_index((Int_t)(f_chain->GetLeaf("rm_d2")->GetValue()))];
  if( f_chain->GetLeaf("dst1self")->GetValue()==1 ) weight *= R_ss_dstr[dec_index((Int_t)(f_chain->GetLeaf("rm_d1")->GetValue()))];
  else                                              weight *= R_bb_dstr[dec_index((Int_t)(f_chain->GetLeaf("rm_d1")->GetValue()))];
  if( f_chain->GetLeaf("dst2self")->GetValue()==1 ) weight *= R_ss_dstr[dec_index((Int_t)(f_chain->GetLeaf("rm_d2")->GetValue()))];
  else                                              weight *= R_bb_dstr[dec_index((Int_t)(f_chain->GetLeaf("rm_d2")->GetValue()))];
  weight /= (Double_t)f_nstream;

  return weight;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Double_t cal_weight_syst1( TTree* f_chain, Int_t f_ievt, Int_t fl_syst ){
  f_chain->GetEntry(f_ievt);
  Double_t weight = 1.0;
  Int_t ctgry = (Int_t)(f_chain->GetLeaf("ctgrsyst")->GetValue());
  // 3-8 : (D**) [3(D1), 4(D2), 5(D1'), 6(D*0), 7(D(2S)), 8(D*(2S))]
  //  11 :        Ds -> tau nu in double D bkg
  //  12 : Ds* -> Ds -> tau nu in double D bkg
  //  21 :        Ds -> KL + X
  //  22 : Ds* -> Ds -> KL + X
  //  23 :        D+ -> KL + X
  if( abs(fl_syst)==ctgry ){
    ///*
    if     ( fl_syst==  3 ) weight *= (1.0 + 0.06); // D1
    else if( fl_syst== -3 ) weight *= (1.0 - 0.06);
    else if( fl_syst==  4 ) weight *= (1.0 + 0.10); // D2
    else if( fl_syst== -4 ) weight *= (1.0 - 0.10);
    else if( fl_syst==  5 ) weight *= (1.0 + 0.83); // D1'
    else if( fl_syst== -5 ) weight *= (1.0 - 0.83);
    else if( fl_syst==  6 ) weight *= (1.0 + 1.0); // D*0
    else if( fl_syst== -6 ) weight *= (1.0 - 1.0);
    else if( fl_syst==  7 ) weight *= (1.0 + 1.0); // D(2S)
    else if( fl_syst== -7 ) weight *= (1.0      );
    else if( fl_syst==  8 ) weight *= (1.0 + 1.0); // D*(2S)
    else if( fl_syst== -8 ) weight *= (1.0      );
    else if( fl_syst== 11 ) weight *= (1.0 + 0.145); // B -> Ds D* & Ds -> tau nu
    else if( fl_syst==-11 ) weight *= (1.0 - 0.145); // B -> Ds D* & Ds -> tau nu
    else if( fl_syst== 12 ) weight *= (1.0 + 0.090); // B -> Ds*D* & Ds -> tau nu
    else if( fl_syst==-12 ) weight *= (1.0 - 0.090); // B -> Ds*D* & Ds -> tau nu
    //*/
    /* old method
    if     ( fl_syst==  3 ) weight *= (1.0 + 0.149); // D1
    else if( fl_syst== -3 ) weight *= (1.0 - 0.149);
    else if( fl_syst==  4 ) weight *= (1.0 + 0.423); // D2
    else if( fl_syst== -4 ) weight *= (1.0 - 0.423);
    else if( fl_syst==  5 ) weight *= (1.0 + 0.362); // D1'
    else if( fl_syst== -5 ) weight *= (1.0 - 0.362);
    else if( fl_syst==  6 ) weight *= (1.0 + 0.346); // D*0
    else if( fl_syst== -6 ) weight *= (1.0 - 0.346);
    else if( fl_syst==  7 ) weight *= (1.0 + 1.0); // D(2S)
    else if( fl_syst== -7 ) weight *= (1.0 - 1.0);
    else if( fl_syst==  8 ) weight *= (1.0 + 1.0); // D*(2S)
    else if( fl_syst== -8 ) weight *= (1.0 - 1.0);
    else if( fl_syst== 11 ) weight *= (1.0 + 0.145);
    else if( fl_syst==-11 ) weight *= (1.0 - 0.145);
    else if( fl_syst== 12 ) weight *= (1.0 + 0.090);
    else if( fl_syst==-12 ) weight *= (1.0 - 0.090);
    */
  }
  return weight;
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const Double_t syst_cos_bin[50] = { -1.92, -1.84, -1.76, -1.68, -1.6, -1.52, -1.44, -1.36, -1.28, -1.2, 
                                    -1.12, -1.04, -0.96, -0.88, -0.8, -0.72, -0.64, -0.56, -0.48, -0.4, 
                                    -0.32, -0.24, -0.16, -0.08, -6.93889e-17, 0.08, 0.16, 0.24, 0.32, 0.4, 
                                    0.48, 0.56, 0.64, 0.72, 0.8, 0.88, 0.96, 1.04, 1.12, 1.2, 
                                    1.28, 1.36, 1.44, 1.52, 1.6, 1.68, 1.76, 1.84, 1.92, 2
};
const Double_t syst_cos_factor[50] = { 0, 0, 0, 0, 0, 0, 0, 3.49756, 1.57592, 1.48895, 
                                       1.40563, 1.08893, 1.02039, 0.785561, 0.800519, 0.980318, 0.753819, 0.94185, 0.606984, 0.760007, 
                                       1.03922, 0.636593, 0.988974, 1.27569, 0.976919, 0.922168, 0.984104, 1.21345, 1.14148, 0.954107, 
                                       1.14773, 1.21118, 1.10567, 0.949683, 0.952904, 1.0665, 0.905211, 2.20754, 0, 0, 
                                       0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
const Double_t syst_cos_factorE[50] = { 0, 0, 0, 0, 0, 0, 0, 4.11355, 1.23122, 0.807762, 
                                        0.579552, 0.439491, 0.382769, 0.274158, 0.192677, 0.178562, 0.129827, 0.150474, 0.12133, 0.140862, 
                                        0.163161, 0.125284, 0.159985, 0.190621, 0.149579, 0.14552, 0.146323, 0.155045, 0.152933, 0.120021, 
                                        0.128253, 0.122044, 0.106092, 0.0907374, 0.0975623, 0.189389, 0.477865, 1.25433, 0, 0, 
                                        0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

Double_t cal_weight_syst2( TTree* f_chain, Int_t f_ievt ){
  f_chain->GetEntry(f_ievt);
  Double_t weight = 1.0;
  Int_t self = (Int_t)(f_chain->GetLeaf("self")->GetValue());
  Double_t cosdll = atan( f_chain->GetLeaf("cosdll")->GetValue() );
  Double_t cosdlh = atan( f_chain->GetLeaf("cosdlh")->GetValue() );
  for( Int_t i=0; i<50; i++ ){
    if( syst_cos_bin[i] > cosdll ){
      ///*
      if( i%2==0 ){
	if( syst_cos_factor[i]==0 || syst_cos_factor[i+1]==0 ){
	  weight *= ( syst_cos_factor[i  ]/pow(syst_cos_factorE[i  ],2) +
		      syst_cos_factor[i+1]/pow(syst_cos_factorE[i+1],2)
		      )/( 1.0/pow(syst_cos_factorE[i  ],2) +
			  1.0/pow(syst_cos_factorE[i+1],2)
			  );
	}else{
	  weight = syst_cos_factor[i];
	}
      }else{
	if( syst_cos_factor[i]==0 || syst_cos_factor[i-1]==0 ){
	  weight *= ( syst_cos_factor[i  ]/pow(syst_cos_factorE[i  ],2) +
		      syst_cos_factor[i-1]/pow(syst_cos_factorE[i-1],2)
		      )/( 1.0/pow(syst_cos_factorE[i  ],2) +
			  1.0/pow(syst_cos_factorE[i-1],2)
			  );
	}else{
	  weight = syst_cos_factor[i];
	}
      }
      //*/
      //weight *= syst_cos_factor[i];
      break;
    }
  }

  for( Int_t i=0; i<50; i++ ){
    if( syst_cos_bin[i] > cosdlh ){
      ///*
      if( i%2==0 ){
	if( syst_cos_factor[i]==0 || syst_cos_factor[i+1]==0 ){
	  weight *= ( syst_cos_factor[i  ]/pow(syst_cos_factorE[i  ],2) +
		      syst_cos_factor[i+1]/pow(syst_cos_factorE[i+1],2)
		      )/( 1.0/pow(syst_cos_factorE[i  ],2) +
			  1.0/pow(syst_cos_factorE[i+1],2)
			  );
	}else{
	  weight = syst_cos_factor[i];
	}
      }else{
	if( syst_cos_factor[i]==0 || syst_cos_factor[i-1]==0 ){
	  weight *= ( syst_cos_factor[i  ]/pow(syst_cos_factorE[i  ],2) +
		      syst_cos_factor[i-1]/pow(syst_cos_factorE[i-1],2)
		      )/( 1.0/pow(syst_cos_factorE[i  ],2) +
			  1.0/pow(syst_cos_factorE[i-1],2)
			  );
	}else{
	  weight = syst_cos_factor[i];
	}
      }
      //*/
      //weight *= syst_cos_factor[i];
      break;
    }
  }

  return weight;
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


void smooth( TH2D* hist, Int_t n=1 ){
//void smooth( TH2D* hist, Int_t n=20 ){
  Int_t xbin = hist->GetNbinsX(); // nb
  Int_t ybin = hist->GetNbinsY(); // eecl

  for( Int_t iybin=0; iybin<ybin; iybin++ ){
    TH1D* hist_proj = hist->ProjectionX( "_proj", iybin+1, iybin+1 );

    //+++++++++++++++++++++++++++++++++++
    Double_t low  = 0;
    Double_t high = 0;
    for( Int_t ixbin=0; ixbin<xbin; ixbin++ ){
      if( ixbin==0 ) continue;
      if( hist_proj->GetBinContent(ixbin+1)==0 || ixbin>nb_xbin/5 ){
	low = hist_proj->GetBinLowEdge(ixbin+1);
	break;
      }
    }

    for( Int_t ixbin=xbin-1; ixbin>=0; ixbin-- ){
      if( hist_proj->GetBinContent(ixbin+1)==0 || xbin-ixbin > nb_xbin/5+1 ){
	high = hist_proj->GetBinLowEdge(ixbin+1) + hist_proj->GetBinWidth(ixbin+1);
	break;
      }
    }

    //std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
    //std::cout << "low = "  << low  << std::endl;
    //std::cout << "high = " << high << std::endl;
    hist_proj->SetAxisRange(low,high);
    //hist_proj->Print("all");
    hist_proj->Smooth(n,"R");
    //hist_proj->Print("all");
    //+++++++++++++++++++++++++++++++++++
    //hist_proj->Smooth(n);

    Double_t n_before = 0.0;
    Double_t n_after  = 0.0;
    for( Int_t ixbin=0; ixbin<xbin; ixbin++ ){
      if( ixbin==0 || ( hist->GetBinContent(ixbin+1,iybin+1)!=0.0 && ( ixbin<nb_xbin/5 || xbin - ixbin <nb_xbin/5+1 ) ) ) continue;
      n_before += hist     ->GetBinContent( ixbin+1, iybin+1 );
      n_after  += hist_proj->GetBinContent( ixbin+1          );
    }

    Double_t scale = ( n_after==0 ? 1.0 : n_before/n_after );
    if( scale==0.0 ){
      scale = hist->Integral(1,xbin,iybin+1,iybin+1) / ( hist->Integral(1,xbin,iybin+1,iybin+1) + n_after );
      for( Int_t ixbin=0; ixbin<xbin; ixbin++ ){
	if( ixbin==0 || ( hist->GetBinContent(ixbin+1,iybin+1)!=0.0 && ( ixbin<nb_xbin/5 || xbin - ixbin <nb_xbin/5+1 ) ) ) hist->SetBinContent( ixbin+1, iybin+1, scale*hist     ->GetBinContent(ixbin+1,iybin+1) );
	else  	                                                                                                            hist->SetBinContent( ixbin+1, iybin+1, scale*hist_proj->GetBinContent(ixbin+1        ) );
      }
    }else{
      for( Int_t ixbin=0; ixbin<xbin; ixbin++ ){
	if( ixbin==0 || ( hist->GetBinContent(ixbin+1,iybin+1)!=0.0 && ( ixbin<nb_xbin/5 || xbin - ixbin <nb_xbin/5+1 ) ) ) continue;
	hist->SetBinContent( ixbin+1, iybin+1, scale*hist_proj->GetBinContent(ixbin+1) );
      }
    }
  }
  
  return;
}


std::string makeCut_dststmc( const Bool_t fl ){
  std::stringstream sTmp;
  if( fl ) sTmp << "( flmcddst==1 || (flmcddst!=1 && !(2<ctgrsyst&&ctgrsyst<9)) )";
  else     sTmp << "( flmcddst!=1 )";
  
  return sTmp.str();
}

std::string makeCut_npmc( const Bool_t fl ){
  std::stringstream sTmp;
  if( fl ) sTmp << "( flmcddst==2 || (flmcddst!=2 && !((semi1==3&&gm_ddst1==2)||(semi2==3&&gm_ddst2==2))) )";
  else     sTmp << "( flmcddst!=2 )";
  
  return sTmp.str();
}



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

namespace np{
  const Int_t    nvar = 4;        //q2,  cos_d,   cos_w,  cos_t
  const Int_t    nbin    [nvar] = {   12,     12,      12,     12 };
  //const Int_t    nbin    [nvar] = {   10,     10,      20,     10 };
  const Double_t xmin    [nvar] = {  3.1,   -1.0,    -1.0,   -1.0 };
  const Double_t xmax    [nvar] = { 11.8,    1.0,     1.0,    1.0 };
  const Char_t*  brname  [nvar] = {"q2", "cos_d", "cos_w", "cos_t"};
  const Char_t*  axisname[nvar] = {"q^{2} [GeV^{2}]", "cos#theta_{D}", "cos#theta_{W}", "cos#theta_{#tau}"};
}
void getIndex( Int_t index, Int_t sub_index[np::nvar] ){
  for( Int_t ivar=np::nvar-1; ivar>=0; ivar-- ){
    Int_t tmp = 1;
    for( Int_t i=0; i<ivar; i++ ) tmp *= np::nbin[i];
    sub_index[ivar] = index/tmp;
    index -= sub_index[ivar]*tmp;
  }
  return;
}

Int_t getGIndex( const Int_t sub_index[np::nvar], const Bool_t fl_message=false ){
  Int_t index = 0;
  for( Int_t ivar=0; ivar<np::nvar; ivar++ ){
    Int_t tmp = 1;
    for( Int_t i=0; i<ivar; i++ ){
      tmp *= np::nbin[i];
    }
    index += sub_index[ivar]*tmp;
  }

  if( fl_message ){
    for( Int_t ivar=0; ivar<np::nvar; ivar++ ){
      std::cout << std::setw(3) << std::right << sub_index[ivar];
      if( ivar!=np::nvar-1 ) std::cout << ", ";
      else                   std::cout << " -> ";
    }
    std::cout << "gindex = " << std::setw(7) << std::right << index << std::endl;
  }
  return index;
}

Int_t getGIndex( const Double_t val[np::nvar], const Bool_t fl_message=false ){
  Int_t sub_index[np::nvar];
  for( Int_t ivar=0; ivar<np::nvar; ivar++ ){
    Double_t width = (np::xmax[ivar]-np::xmin[ivar])/np::nbin[ivar];
    for( Int_t ibin=0; ibin<np::nbin[ivar]; ibin++ ){
      if( val[ivar] < np::xmin[ivar]+(ibin+1)*width ){
	sub_index[ivar] = ibin;
	break;
      }
      if( ibin==np::nbin[ivar]-1 ){
	std::cerr << "[WARNING] too large value ?" << std::endl;
	sub_index[ivar] = ibin;
      }
    }
  }
  if( fl_message ){
    for( Int_t ivar=0; ivar<np::nvar; ivar++ ){
      std::cout << std::setw(12) << std::right << val[ivar];
      if( ivar!=np::nvar-1 ) std::cout << ", ";
      else               std::cout << " -> ";
    }
  }
  return getGIndex( sub_index, fl_message );
}

std::string makeCut_np( const Int_t index, const Bool_t fl_message=false ){
  std::stringstream sTmp;
  sTmp << "1";
  Int_t sub_index[np::nvar] = {0};
  getIndex( index, sub_index );
  if( fl_message ) std::cout << std::setw(5) << std::right << index << " : "
			     << std::setw(3) << std::right << sub_index[0] << ", "
			     << std::setw(3) << std::right << sub_index[1] << ", "
			     << std::setw(3) << std::right << sub_index[2] << ", "
			     << std::setw(3) << std::right << sub_index[3] << " : ";
  for( Int_t ivar=0; ivar<np::nvar; ivar++ ){
    //if( ivar==1 ) continue; // for the case of D tau nu
    sTmp << Form( " && (%f < %s && %f > %s)",
		  np::xmin[ivar] + (sub_index[ivar]  )*(np::xmax[ivar]-np::xmin[ivar])/np::nbin[ivar], np::brname[ivar],
		  np::xmin[ivar] + (sub_index[ivar]+1)*(np::xmax[ivar]-np::xmin[ivar])/np::nbin[ivar], np::brname[ivar]
		  );
  }
  if( fl_message ) std::cout << sTmp.str().c_str() << " : ";

  return sTmp.str();
}

#endif
