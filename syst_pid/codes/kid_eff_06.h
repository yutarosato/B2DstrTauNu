/********************\
  kid_eff_06.h

  update: 07/12/23

\********************/
#ifndef KID_EFF_06_H
#define KID_EFF_06_H

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>

class KID_eff_06;

struct KID_eff_buffer {
  enum { NBINS = 384 };
  int dummy;  // To avoid the problem of bellum. See whiteboard 328.
  int entries[NBINS];
  int ngood;
  int nbad;
};

class KID_eff_06 {
public:
  enum { NBINS = 384 };
private:
  int m_prob;   // 1,2,...,9
  int m_mode;   // 0,1,2,3
  char m_title[256];
  char m_filename[1024];
  float m_effdt[NBINS];
  float m_effdt_st[NBINS];
  float m_effdt_sy[NBINS];
  float m_effmc[NBINS];
  float m_effmc_st[NBINS];
  float m_ratio[NBINS];
  float m_ratio_st[NBINS];
  float m_ratio_sy[NBINS];
  int m_flag[NBINS];
  double m_effdt_total;
  double m_effdt_error;
  double m_effmc_total;
  double m_effmc_error;
  double m_ratio_total;
  double m_ratio_error;
  double m_ratio_ref;
  int m_ngood;
  int m_nbad;
  KID_eff_buffer sum;
public:
  KID_eff_06() {}
  ~KID_eff_06() {}
  void init( double prob, int mode, const char *title, const char *filename );
  int addtrack( double plab, double costheta );
  void calculate(double* ratio=NULL, double* ratioE=NULL);
  void dump();
  double effdt() { return m_effdt_total; }
  double effdt_error() { return m_effdt_error; }
  double effmc() { return m_effmc_total; }
  double effmc_error() { return m_effmc_error; }
  double ratio() { return m_ratio_total; }
  double ratio_error() { return m_ratio_error; }
  double ratio_ref() { return m_ratio_ref; }
  int n_track() { return m_ngood + m_nbad; }
  int n_goodtrack() { return sum.ngood; }
  int n_badtrack(){ return sum.nbad; }
  //int n_goodtrack() { return m_ngood; }
  //int n_badtrack(){ return m_nbad; }
private:
  int getindex( double plab, double costheta );
};

#endif
