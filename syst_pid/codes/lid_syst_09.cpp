#include "lid_syst_09.h"
const bool fl_scale = !true; // default is false.

// [electron, svd1]
// [error scale down factor for normalization lepton]
const double scale_down_factor[70] = { 0, 0, 0, 0.360587, 0.757556, 1, 1, 1, 1, 1, 
				       0, 0, 0, 0.328136, 0.840251, 0.951104, 1, 1, 1, 1, 
				       0, 0, 0, 0.383, 0.88241, 0.961157, 1, 1, 1, 1, 
				       0, 0, 0, 0.557098, 0.939266, 0.982124, 1, 1, 1, 1, 
				       0, 0, 0.310296, 0.85275, 0.974292, 1, 1, 1, 1, 1, 
				       0, 0, 0.843163, 1, 1, 1, 1, 1, 1, 1, 
				       0, 0.0277054, 0.77042, 1, 1, 1, 1, 1, 1, 1 };


/*
// [electron, svd1]
// [error scale down factor for signal lepton]
const double scale_down_factor[70] = { 0.583567, 0.547248, 0.00861638, 0, 0, 1, 1, 1, 1, 1, 
				       0.866946, 0.814377, 0.445022, 0, 0, 0, 1, 1, 1, 1, 
				       0.85922, 0.729829, 0.339321, 0, 0, 0, 1, 1, 1, 1, 
				       0.854095, 0.759209, 0.344549, 0, 0, 0, 1, 1, 1, 1, 
				       0.825639, 0.602995, 0, 0, 0, 1, 1, 1, 1, 1, 
				       0.699243, 0.366262, 0, 1, 1, 1, 1, 1, 1, 1, 
				       0.645654, 0, 0, 1, 1, 1, 1, 1, 1, 1 };
// [error scale down factor for normalization lepton]
const double scale_down_factor[70] = { 0, 0, 0, 0.360587, 0.757556, 1, 1, 1, 1, 1, 
				       0, 0, 0, 0.328136, 0.840251, 0.951104, 1, 1, 1, 1, 
				       0, 0, 0, 0.383, 0.88241, 0.961157, 1, 1, 1, 1, 
				       0, 0, 0, 0.557098, 0.939266, 0.982124, 1, 1, 1, 1, 
				       0, 0, 0.310296, 0.85275, 0.974292, 1, 1, 1, 1, 1, 
				       0, 0, 0.843163, 1, 1, 1, 1, 1, 1, 1, 
				       0, 0.0277054, 0.77042, 1, 1, 1, 1, 1, 1, 1 };
// [electron, svd2]
// [error scale down factor for signal lepton]
const double scale_down_factor[70] = { 0.831853, 0.75783, 0.462195, 0, 0, 0, 1, 1, 1, 1, 
				       0.830674, 0.773528, 0.407822, 0, 0, 0, 1, 1, 1, 1, 
				       0.817066, 0.739966, 0.32326, 0, 0, 0, 1, 1, 1, 1, 
				       0.829804, 0.736303, 0.297896, 0, 0, 0, 1, 1, 1, 1, 
				       0.820643, 0.592883, 0, 0, 0, 1, 1, 1, 1, 1, 
				       0.850068, 0.34395, 0, 1, 1, 1, 1, 1, 1, 1, 
				       0.817912, 0.152676, 0, 1, 1, 1, 1, 1, 1, 1 };
// [error scale down factor for normalization lepton]
const double scale_down_factor[70] = { 0, 0, 0, 0.331015, 0.789374, 0.961499, 1, 1, 1, 1, 
				       0, 0, 0, 0.381521, 0.834229, 0.969335, 1, 1, 1, 1, 
				       0, 0, 0, 0.391095, 0.828695, 0.98595, 1, 1, 1, 1, 
				       0, 0, 0, 0.545907, 0.913093, 0.99491, 1, 1, 1, 1, 
				       0, 0, 0.35033, 0.854241, 0.977265, 1, 1, 1, 1, 1, 
				       0, 0, 0.827949, 1, 1, 1, 1, 1, 1, 1, 
				       0, 0, 0.869777, 1, 1, 1, 1, 1, 1, 1 };
// [muon, svd1]
// [error scale down factor for signal lepton]
const double scale_down_factor[70] = { 1, 1, 1, 0.0035573, 0, 0, 1, 1, 1, 1, 
				       1, 0.886218, 0.742612, 0.123702, 0, 0, 1, 1, 1, 1, 
				       1, 0.868308, 0.661646, 0, 0, 0, 1, 1, 1, 1, 
				       1, 0.740773, 0.198865, 0, 0, 0, 1, 1, 1, 1, 
				       1, 0.473365, 0, 1, 1, 1, 1, 1, 1, 1, 
				       1, 0.0233263, 0, 1, 1, 1, 1, 1, 1, 1, 
				       1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
// [error scale down factor for normalization lepton]
const double scale_down_factor[70] = { 1, 1, 1, 0, 0.586802, 0.896027, 1, 1, 1, 1, 
				       1, 0, 0, 0, 0.731287, 0.935883, 1, 1, 1, 1, 
				       1, 0, 0, 0.201915, 0.843017, 0.981939, 1, 1, 1, 1, 
				       1, 0, 0, 0.695509, 0.931548, 0.955781, 1, 1, 1, 1, 
				       1, 0, 0.615761, 1, 1, 1, 1, 1, 1, 1, 
				       1, 0, 0.756356, 1, 1, 1, 1, 1, 1, 1, 
				       1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
// [muon, svd2(e31-39&45a)]
// [error scale down factor for signal lepton]
const double scale_down_factor[70] = { 1, 1, 0, 0.115885, 0, 0, 1, 1, 1, 1, 
				       1, 0.890452, 0.704467, 0.0432285, 0, 0, 1, 1, 1, 1, 
				       1, 0.806355, 0.621908, 0.0392251, 0, 0, 1, 1, 1, 1, 
				       1, 0.739715, 0.221049, 0, 0, 1, 1, 1, 1, 1, 
				       1, 0.5624, 0, 1, 1, 1, 1, 1, 1, 1, 
				       1, 0.450569, 0, 1, 1, 1, 1, 1, 1, 1, 
				       1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
// [error scale down factor for normalization lepton]
const double scale_down_factor[70] = { 1, 1, 0.0141309, 0, 0.388608, 0.984351, 1, 1, 1, 1, 
				       1, 0, 0, 0, 0.685731, 0.96268, 1, 1, 1, 1, 
				       1, 0, 0, 0, 0.789815, 0.987441, 1, 1, 1, 1, 
				       1, 0, 0, 0.693353, 0.916443, 1, 1, 1, 1, 1, 
				       1, 0, 0.588967, 1, 1, 1, 1, 1, 1, 1, 
				       1, 0, 0.784263, 1, 1, 1, 1, 1, 1, 1, 
				       1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
// [muon, svd2(e41-49 except 45a)]
// [error scale down factor for signal lepton]
const double scale_down_factor[70] = { 1, 1, 0.749491, 0.340497, 0, 0, 1, 1, 1, 1, 
				       1, 0.898643, 0.682608, 0.0406486, 0, 0, 1, 1, 1, 1, 
				       1, 0.81775, 0.606644, 0, 0, 0, 1, 1, 1, 1, 
				       1, 0.74081, 0.219906, 0, 0, 0, 1, 1, 1, 1, 
				       1, 0.420142, 0, 0, 1, 1, 1, 1, 1, 1, 
				       1, 0.410735, 0, 0, 1, 1, 1, 1, 1, 1, 
				       1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
// [error scale down factor for normalization lepton]
const double scale_down_factor[70] = { 1, 1, 0, 0, 0.702986, 0.969759, 1, 1, 1, 1, 
				       1, 0, 0, 0, 0.687619, 0.934986, 1, 1, 1, 1, 
				       1, 0, 0, 0.174606, 0.815461, 0.96382, 1, 1, 1, 1, 
				       1, 0, 0, 0.67147, 0.935933, 0.985692, 1, 1, 1, 1, 
				       1, 0, 0.705409, 0.955646, 1, 1, 1, 1, 1, 1, 
				       1, 0, 0.751371, 0.897644, 1, 1, 1, 1, 1, 1, 
				       1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
// [muon, svd2(e51-65)]
// [error scale down factor for signal lepton]
const double scale_down_factor[70] = { 1, 1, 0.870451, 0.319866, 0, 0, 1, 1, 1, 1, 
				       1, 0.865468, 0.704628, 0.12971, 0, 0, 1, 1, 1, 1, 
				       1, 0.830722, 0.645148, 0, 0, 0, 1, 1, 1, 1, 
				       1, 0.745362, 0.262679, 0, 0, 1, 1, 1, 1, 1, 
				       1, 0.366058, 0, 0, 1, 1, 1, 1, 1, 1, 
				       1, 0.286483, 0, 1, 1, 1, 1, 1, 1, 1, 
				       1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
// [error scale down factor for normalization lepton]
const double scale_down_factor[70] = { 1, 1, 0, 0, 0.733825, 0.959373, 1, 1, 1, 1, 
				       1, 0, 0, 0, 0.653237, 0.970158, 1, 1, 1, 1, 
				       1, 0, 0, 0.104542, 0.821058, 0.975595, 1, 1, 1, 1, 
				       1, 0, 0, 0.693922, 0.943908, 1, 1, 1, 1, 1, 
				       1, 0, 0.661039, 0.97427, 1, 1, 1, 1, 1, 1, 
				       1, 0, 0.675439, 1, 1, 1, 1, 1, 1, 1, 
				       1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
*/


void LID_syst::init( double prob, int mode, const char *title,
		     const char *filename ) {

  for(int j=0;j<NBINS;j++) sum.entries[j]=0;
  sum.ngood = 0;
  sum.nbad = 0;
  //  mode = 1 : eid, 2 : muid
  m_deg2rad=0.017453293;
  m_mode=mode;
  if(m_mode<1 || m_mode>2 ) {
    fprintf( stderr, "[LID_syst] invarid arguments.\n" );
    fprintf( stderr, "mode = 1(e) or 2(mu)\n" );
    exit(1);
  }
  m_prob=(int)(100*(prob+0.0001)); // 0.0001 is to avoid floating error.
  m_probindex=0;
  if(m_mode==1) {
    strcpy( m_kind, "EIDCORR :" );
    switch (m_prob) {
    case 10: m_probindex=1; break;
    case 50: m_probindex=2; break;
    case 60: m_probindex=3; break;
    case 80: m_probindex=4; break;
    case 90: m_probindex=5; break;
    default:
      fprintf( stderr, "[LID_syst] invarid arguments.\n" );
      fprintf( stderr, "Proba cut = 0.1/0.5/0.6/0.8/0.9 \n" );
      exit(1);
    }
  } else if(m_mode==2) {
    strcpy( m_kind, "MUIDCORR:" );
    switch (m_prob) {
    case 10: m_probindex=1; break;
    case 80: m_probindex=2; break;
    case 90: m_probindex=3; break;
    case 95: m_probindex=4; break;
    case 97: m_probindex=5; break;
    default:
      fprintf( stderr, "[LID_syst] invarid arguments.\n" );
      fprintf( stderr, "Likelihood cut = 0.1/0.8/0.9/0.95/0.97 \n" );
      exit(1);
    }
  }
//   std::cout << "LID_syst::init ..... The data file: " << filename
// 	    << " is setted by default" << std::endl;
  /*
  std::cout << "Should be set in begin_run:" << std::endl;
  std::cout << "mylidcorr.set_param(ExpNb)" << std::endl;
  */

  strcpy( m_title, "lid_syst_" );
  strcat( m_title, title );
  //  strcpy( m_filename, filename );

  m_ngood = 0;
  m_nbad = 0;
  m_ratio_total = 0;
  m_ratio_error = 0;
  m_ratio_error_stat  = 0;
  m_ratio_error_syst1 = 0;
  m_ratio_error_syst2 = 0;
  for( int i=0; i<NBINS; i++ ) {
    m_thmin[i] = 0;
    m_thmax[i] = 0;
    m_pmin[i] = 0;
    m_pmax[i] = 0;
    m_ratio[i] = 0;
    m_ratio_st[i] = 0;
    m_ratio_expdep[i] = 0;
    m_ratio_jpsi[i] = 0;
  }
  read_param(filename);
}

/* ************************************ */
void LID_syst::read_param(const char * filename){
  //  strcpy( m_filename, filename );

  // read tables
  FILE *fp;
  if( (fp = fopen(filename,"r")) == NULL ) {
    fprintf( stderr, "cannot open %s.\n", filename );
    exit(1);
  }
  char cs[256];
  int kind, lid, mapid, f;
  float x0, x1, x2, x3, x4, x5, x6, x7,x8;
  int idx = -1;
  while( fgets(cs,sizeof(cs),fp)!=NULL ) {
    if( cs[0]=='#' ) continue;
    sscanf( cs, "%f %f %f %f %f %f %f %f %f",
	    &x0, &x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8);
    lid=(int)(100*(x0+0.0001));
    if( lid == m_prob ) {
      idx++;
      m_thmin[idx] = x1;
      m_thmax[idx] = x2;
      m_pmin[idx] = x3;
      m_pmax[idx] = x4;
      m_ratio[idx] = x5;
      m_ratio_st[idx] = x6;
      m_ratio_expdep[idx] = x7;
      m_ratio_jpsi[idx] = x8;
    }
  }
  fclose(fp);
}

/* ************************************
void LID_syst::set_param(int ExpNb){

  char filename[40];

  if(m_mode==1) {
    if (ExpNb < 30) {
      strcpy( filename, "eid_data-mc_corr_svd1.dat" );
    }
    else {
      strcpy( filename, "eid_data-mc_corr_svd2.dat" );
    }
  }
  if(m_mode==2) {
    if (ExpNb < 30) {
      strcpy( filename, "muid_data-mc_corr_svd1.dat" );
    }
    else {
      strcpy( filename, "muid_data-mc_corr_svd2.dat" );
    }
  }
  std::cout << "LID_syst::set_param ..... Experience Number: " << ExpNb << std::endl;
  std::cout << "LID_syst::set_param ..... CORR and ERROR FILE: " << filename << std::endl;
  read_param(filename);
}
*/

/* ************************************ */
int LID_syst::addtrack( double plab, double costheta ) {
  int size;
  int idx = getindex(plab,costheta);
  if( idx<0 ) {
    sum.nbad++;
    return 0;
  }
  sum.entries[idx]++;
  sum.ngood++;
  return 1;
}

/* ************************************ */
void LID_syst::calculate(double* ratio, double* ratioE) {
  int size;

  // set value
  m_ngood = sum.ngood;
  m_nbad = sum.nbad;
  // calculate dteff,
  m_ratio_total = 0;
  m_ratio_error = 0;
  double ratio_syst(0);
  double ratio_syst1(0);
  double ratio_syst2(0);
  for(int j=0;j<NBINS;j++) {
    m_ratio_total += sum.entries[j]*m_ratio[j];
    if( fl_scale ){
      ratio_syst1 += sum.entries[j]*m_ratio_expdep[j]*scale_down_factor[j];
      ratio_syst2 += sum.entries[j]*m_ratio_jpsi[j]*scale_down_factor[j];
    }else{
      ratio_syst1 += sum.entries[j]*m_ratio_expdep[j];
      ratio_syst2 += sum.entries[j]*m_ratio_jpsi[j];
    }
  }
  if (sum.ngood!=0) {
    m_ratio_total /= sum.ngood;
    ratio_syst /= sum.ngood;
  }
  else {
    m_ratio_total = 0.0;
    ratio_syst = 0.0;
  }
  // quadratic sum
  double re2(0), t;
  for(int j=0;j<NBINS;j++) {
   t = sum.entries[j]*sum.entries[j];
   if( fl_scale ) re2 += t*m_ratio_st[j]*m_ratio_st[j];
   else           re2 += t*m_ratio_st[j]*m_ratio_st[j]*scale_down_factor[j]*scale_down_factor[j];
  }
  if (sum.ngood!=0) {
    m_ratio_error = sqrt(re2 + ratio_syst1*ratio_syst1 + ratio_syst2*ratio_syst2)/sum.ngood;
    m_ratio_error_stat  =   sqrt(re2)/sum.ngood;
    m_ratio_error_syst1 = ratio_syst1/sum.ngood;
    m_ratio_error_syst2 = ratio_syst2/sum.ngood;
  }
  else {
    m_ratio_error = 0.0;
  }

  if( ratio  != NULL ) *ratio  = m_ratio_total;
  if( ratioE != NULL ) *ratioE = m_ratio_error;
}


/* ************************************ */
int LID_syst::getindex( double plab, double costheta ) {
  int idx_prob_min=0;
  int idx_prob_max=NTHETA*NMOMENTUM - 1;
  for (int i=idx_prob_min; i<idx_prob_max; i++) {
    if (costheta>cos(m_thmax[i]*m_deg2rad) && costheta<cos(m_thmin[i]*m_deg2rad)){
      if (plab>m_pmin[i] && plab<m_pmax[i]) {
	return i;
      }
    }
  }
  return -1;
}

/* ************************************ */
void LID_syst::dump() {
  printf( "%s %s Corr  %.4f +- %.4f (used tracks: %d   ignored tracks: %d) stat[%.4f],syst1[%.4f],syst2[%.4f]\n",m_kind,m_title, m_ratio_total, m_ratio_error, m_ngood, m_nbad, m_ratio_error_stat, m_ratio_error_syst1, m_ratio_error_syst2 );
  /*
  printf( "%s --- LID_syst dump ---\n",m_kind);
  printf("%s \n",m_kind);
  printf( "%s %s\n",m_kind,m_title );
  printf( "%s Corr  %.4f +- %.4f\n",m_kind, m_ratio_total, m_ratio_error );
  printf( "%s used tracks: %d   ignored tracks: %d\n",m_kind, m_ngood, m_nbad );
  printf( "%s S(job) = Sum niCi %.4f\n",m_kind,m_ratio_total*m_ngood);
  printf( "%s Corr = S(job)/used_tracks\n",m_kind);
  printf( "%s i ni*sig1i ni*sig2i ni*sig3i :\n",m_kind);
  for(int j=0;j<NBINS;j++) {
    printf( "%s %d %.4f %.4f %.4f\n",m_kind,j,sum.entries[j]*m_ratio_st[j],sum.entries[j]*m_ratio_expdep[j],sum.entries[j]*m_ratio_jpsi[j]);
  }
  printf( "%s Err(job) = sqrt(Sum_i ni^2*sig1i^2+(Sum_i ni*sig2i)^2+(Sum_i ni*sig3i)^2)/used_tracks\n",m_kind);
  printf( "%s \n",m_kind);
  printf( "%s --------------------------------------------------------------------------------\n",m_kind);
  */
}
