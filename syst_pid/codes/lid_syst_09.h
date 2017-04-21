/********************\
  lid_syst_09.h

   ( based on lid_syst.h by L.Hinz san )

  update: 2009/09/09

\********************/
#ifndef LID_SYST_H
#define LID_SYST_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>

class LID_syst;

struct LID_syst_buffer {
  enum { NPROB=5,
	 NTHETA=7,
	 NMOMENTUM=10,
	 NBINS = 70 };
  // NBINS = NPROB*NTHETA*NMOMENTUM
  int dummy;  // for old bug in basfshm
  int entries[NBINS];
  int ngood;
  int nbad;
};

class LID_syst {
public:
  enum { NPROB=5,
	 NTHETA=7,
	 NMOMENTUM=10,
	 NBINS = 70 };
private:
  //  char m_filename[1024];
  float m_thmin[NBINS];
  float m_thmax[NBINS];
  float m_pmin[NBINS];
  float m_pmax[NBINS];
  float m_ratio[NBINS];
  float m_ratio_st[NBINS];
  float m_ratio_expdep[NBINS];
  float m_ratio_jpsi[NBINS];
  int m_flag[NBINS];
  char m_title[256];
  char m_kind[9];
  int m_prob; // 10,50,...,97
  int m_probindex; // 1,2,3,...,NPROB
  int m_mode; // 0,1,2,3
  double m_ratio_total;
  double m_ratio_error;
  double m_ratio_error_stat;  // added @ 20150704
  double m_ratio_error_syst1; // added @ 20150704
  double m_ratio_error_syst2; // added @ 20150704
  LID_syst_buffer sum;
  int m_ngood;
  int m_nbad;
  double m_deg2rad;
public:
  LID_syst() {}
  ~LID_syst() {}
  void init( double prob, int mode, const char *title, const char *filename );
//   void set_param(int);
  int addtrack( double plab, double costheta );
  void calculate(double* ratio=NULL, double* ratioE=NULL);
  void dump();
  double ratio() { return m_ratio_total; }
  double ratio_error() { return m_ratio_error; }
  int n_track() { return m_ngood + m_nbad; }
  //int n_goodtrack() { return m_ngood; }
  //int n_badtrack(){ return m_nbad; }
  int n_goodtrack() { return sum.ngood; }
  int n_badtrack(){ return sum.nbad; }
  int getindex(double plab, double costheta); // move to public fuction @ 20150704
private:
  void read_param(const char *filename);
};


#endif
