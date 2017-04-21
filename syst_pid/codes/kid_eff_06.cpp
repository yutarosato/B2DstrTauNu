#include "kid_eff_06.h"

void KID_eff_06::init( double prob, int mode, const char *title,
		       const char * filename ) {
  for(int j=0;j<NBINS;j++) sum.entries[j]=0;
  sum.ngood = 0;
  sum.nbad = 0;

  //  m_prob = (int)(10*prob);
  m_prob = (int)(10*(prob+0.001)); // 0.001 is to avoid floating error.
  m_mode = mode-1;
  if( m_prob<0 || m_prob>9 || m_mode<0 || m_mode>4 ) {
    fprintf( stderr, "[KID_eff_06] invarid arguments.\n" );
    exit(1);
  }
  strcpy( m_title, "kid_eff_" );
  strcat( m_title, title );
  strcpy( m_filename, filename );
  m_ngood = 0;
  m_nbad = 0;
  m_effdt_total = 0;
  m_effdt_error = 0;
  m_effmc_total = 0;
  m_effmc_error = 0;
  m_ratio_total = 0;
  m_ratio_error = 0;
  m_ratio_ref = 0;
  for( int i=0; i<NBINS; i++ ) {
    m_effdt[i] = 0;
    m_effdt_st[i] = 0;
    m_effdt_sy[i] = 0;
    m_effmc[i] = 0;
    m_effmc_st[i] = 0;
    m_ratio[i] = 0;
    m_ratio_st[i] = 0;
    m_ratio_sy[i] = 0;
    m_flag[i] = 0;
  }
  // read tables
  FILE *fp;
  if( (fp = fopen(m_filename,"r")) == NULL ) {
    fprintf( stderr, "cannot open %s.\n", m_filename );
    exit(1);
  }
  char cs[256];
  int kind, pid, mapid, f;
  float x1, x2, x3, x4, x5, x6, x7, x8;
  
  while( fgets(cs,sizeof(cs),fp)!=NULL ) {
    if( cs[0]=='#' ) continue;
    sscanf( cs, "%d %d %d %f %f %f %f %f %f %f %f %d",
	    &kind, &pid, &mapid, &x1, &x2, &x3, &x4, &x5, &x6, &x7, &x8, &f );
    if( kind == m_mode && pid == m_prob ) {
      int idx = 12*(32-(mapid/100))+(mapid%100-1); // convert jasna->n6
      m_effdt[idx] = x1;
      m_effdt_st[idx] = x2;
      m_effdt_sy[idx] = x3;
      m_effmc[idx] = x4;
      m_effmc_st[idx] = x5;
      m_ratio[idx] = x6;
      m_ratio_st[idx] = x7;
      m_ratio_sy[idx] = x8;
      m_flag[idx] = f;
    }
  }
  fclose(fp);
}

int KID_eff_06::addtrack( double plab, double costheta ) {
  int size;
  int idx = getindex(plab,costheta);
  sum.entries[idx]++;
  if( m_flag[idx]>0 ) {
    sum.nbad++;
    return 0;
  }
  sum.ngood++;
  return 1;
}

void KID_eff_06::calculate(double* ratio, double* ratioE) {
  int size;

  // set value
  m_ngood = sum.ngood;
  m_nbad = sum.nbad;
  // calculate dteff,
  m_effdt_total = 0;
  m_effdt_error = 0;
  m_effmc_total = 0;
  m_effmc_error = 0;
  m_ratio_total = 0;
  m_ratio_error = 0;
  // linear sum
  double effdt_syst(0), ratio_syst(0);
  for(int j=0;j<NBINS;j++) {
    if( m_flag[j]==0 ) {
      m_effdt_total += sum.entries[j]*m_effdt[j];
      m_effmc_total += sum.entries[j]*m_effmc[j];
      m_ratio_total += sum.entries[j]*m_ratio[j];
      m_ratio_ref   += sum.entries[j]*m_ratio[j];
      effdt_syst += sum.entries[j]*m_effdt_sy[j];
      ratio_syst += sum.entries[j]*m_ratio_sy[j];
    } else { // bad tracks
      m_ratio_ref += sum.entries[j];
    }
  }

  m_effdt_total /= sum.ngood;
  m_effmc_total /= sum.ngood;
  m_ratio_total /= sum.ngood;
  m_ratio_ref /= (sum.ngood+sum.nbad);
  effdt_syst /= sum.ngood;
  ratio_syst /= sum.ngood;
  // quadratic sum
  double t, de2(0.0), me2(0.0), re2(0.0);
  for(int j=0;j<NBINS;j++) {
    if( m_flag[j]==0 ) {
      t = sum.entries[j]*sum.entries[j];
      de2 += t*m_effdt_st[j]*m_effdt_st[j];
      me2 += t*m_effmc_st[j]*m_effmc_st[j];
      re2 += t*m_ratio_st[j]*m_ratio_st[j];
    }
  }

  double re_const(.0030); // 0.3%(run-dependence)
  if(m_mode==1) re_const = .01; // 1%(run-dep) for KID fake
  else if(m_mode==3) re_const = .02; // 2%(run-dep) for piID fake
  m_effdt_error = effdt_syst + sqrt(de2)/sum.ngood;
  m_effmc_error = sqrt(me2)/sum.ngood;
  m_ratio_error = ratio_syst + sqrt(re2)/sum.ngood + re_const;

  if( ratio  != NULL ) *ratio  = m_ratio_total;
  if( ratioE != NULL ) *ratioE = m_ratio_error;
  return;
}

int KID_eff_06::getindex( double plab, double costheta ) {
  int np(31);
  if(plab>4.5) np=0;
  else if(plab>4.0) np=1;
  else if(plab>3.6) np=2;
  else if(plab>3.0) np = 20 - (int)(plab*5);
  else if(plab>0.5) np = 35 - (int)(plab*10);
  int nt(0);
  if(costheta>0.842) nt=11; // forward
  else if(costheta>0.692) nt=10; // A2
  else if(costheta>.542) nt=9; // A1
  else if(costheta>.435) nt=8; // B
  else if(costheta>.355) nt=7; // C
  else if(costheta>.209) nt=6; // D
  else if(costheta>.017) nt=5; // E
  else if(costheta>-.152) nt=4; // F
  else if(costheta>-.300) nt=3; // G
  else if(costheta>-.511) nt=2; // H
  else if(costheta>-.612) nt=1; // I
  return np*12+nt;
}

void KID_eff_06::dump() {
  //printf( "%s Corr  %.4f +- %.4f (used tracks: %d   ignored tracks: %d)\n", m_title, m_ratio_total, m_ratio_error, m_ngood, m_nbad );
  double diff = fabs(m_ratio_ref-m_ratio_total);
  printf( "%s Corr  %.4f +- %.4f (used tracks: %d   ignored tracks: %d)\n", m_title, m_ratio_total, sqrt(m_ratio_error*m_ratio_error+diff*diff), m_ngood, m_nbad ); // conservative
  /*
  printf( "%s\n", m_title );
  printf( "ratio  %.4f +- %.4f", m_ratio_total, m_ratio_error );
  printf( " (ref. ratio %.4f)\n", m_ratio_ref );
  printf( "data   %.4f +- %.4f\n", m_effdt_total, m_effdt_error );
  printf( "MC     %.4f +- %.4f\n", m_effmc_total, m_effmc_error );
  printf( "used track: %d   ignored track: %d\n", m_ngood, m_nbad );
  double diff = fabs(m_ratio_ref-m_ratio_total);
  printf( "ref. ratio is the data/MC ratio assuming that MC is correct "
	  "for invalid bins.\n"
	  "You may take the difference to the ratio (%.4f) as an "
	  "additional\nsystematic error (i.e. %.4f syst. error)\n",
	  diff, sqrt(m_ratio_error*m_ratio_error+diff*diff) );
  */
}

