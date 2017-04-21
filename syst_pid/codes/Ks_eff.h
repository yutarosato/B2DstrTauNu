#ifndef KS_EFF_H
#define KS_EFF_H

#include <stdio.h>

class Ks_eff 
{

public:
  Ks_eff();
  virtual ~Ks_eff(){};

  void   add(double p, double cos);
  double total_effFactor(); //total eff correction after all events
  double total_errFactor(); //total uncertainty after all events
  int    get_totalNum   (); // return the total number of events up to this point
                            // (total number being used in weighing the eff. and errors)

private:
  static const double table_err[][4];
  static const double table_eff[][4];

  int bin_count[3][4];// counts events in momentum/cosTheta bins
  int global_count; // keeps track of total num of events (sum of all bin_count[][4])

};

#endif
