#ifndef DRAWS_LQ_H
#define DRAWS_LQ_H


Double_t cal_rdst_cs2(
		      Double_t rho_A1_2, Double_t a_3, Double_t R11, Double_t R21, Double_t mbPmc, Double_t mbMmc,
		      Double_t Re_CS2, Double_t Im_CS2
 ){
  Double_t hA11 = 0.908;
  TComplex CS2(  Re_CS2, Im_CS2 );

  Double_t f = 
    (0. + 0.030254643456755624*pow(hA11,2) - 
     0.000029428775442260747*pow(hA11,2)*R11 + 
     0.0007343694139646086*pow(hA11,2)*pow(R11,2) - 
     0.011072908714145064*pow(hA11,2)*R21 + 
     0.0019220011820663837*pow(hA11,2)*pow(R21,2) + 
     0.00029493794054002645*pow(hA11,2)*a_3 - 
     0.00013349521629621802*pow(hA11,2)*R21*a_3 + 
     3.887335265869437e-6*pow(hA11,2)*pow(a_3,2) - 
     0.008542734639407037*pow(hA11,2)*rho_A1_2 + 
     9.911598201286346e-6*pow(hA11,2)*R11*rho_A1_2 - 
     0.00022032907826043975*pow(hA11,2)*pow(R11,2)*rho_A1_2 + 
     0.0037396547918801*pow(hA11,2)*R21*rho_A1_2 - 
     0.0006697488809060423*pow(hA11,2)*pow(R21,2)*rho_A1_2 - 
     0.0000934263320002305*pow(hA11,2)*a_3*rho_A1_2 + 
     0.00004232437499355708*pow(hA11,2)*R21*a_3*rho_A1_2 - 
     1.1376776993503411e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2 + 
     0.0007082924178598534*pow(hA11,2)*pow(rho_A1_2,2) - 
     8.926704671522045e-7*pow(hA11,2)*R11*pow(rho_A1_2,2) + 
     0.000018420800360323613*pow(hA11,2)*pow(R11,2)*pow(rho_A1_2,2) - 
     0.0003415435683189837*pow(hA11,2)*R21*pow(rho_A1_2,2) + 
     0.00006245643308607658*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2) + 
     8.13860365504776e-6*pow(hA11,2)*a_3*pow(rho_A1_2,2) - 
     3.689264332183857e-6*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2) + 
     9.332412489660764e-8*pow(hA11,2)*pow(a_3,2)*pow(rho_A1_2,2) + 
     (0.0003814229854998974*pow(hA11,2)*
      (200.15571614318196 - 59.04502572984423*rho_A1_2 + 
       4.870911743325851*pow(rho_A1_2,2) + 
       pow(a_3,2)*(0.16216131714996518 - 0.04054426767332307*rho_A1_2 + 
		   0.0029390310478812237*pow(rho_A1_2,2)) + 
       a_3*(11.106642782949837 - 3.0183476082225646*rho_A1_2 + 
	    0.233693411287558*pow(rho_A1_2,2)) + 
       pow(R21,2)*(40.955261663752275 - 12.1052559135445*rho_A1_2 + 
		   1.*pow(rho_A1_2,2)) + 
       R21*(-181.078585088732 + 53.469638106474065*rho_A1_2 - 
	    4.414016899669555*pow(rho_A1_2,2) + 
	    a_3*(-5.020757230126823 + 1.3658857015288806*rho_A1_2 - 
		 //0.10583312272059556*pow(rho_A1_2,2))))*pow(fabs(CS2),2))/
		 0.10583312272059556*pow(rho_A1_2,2))))*pow(CS2.Rho(),2))/
     pow(mbPmc,2) - (0.04144330132436068*pow(hA11,2)*(CS2.Re()))/mbPmc + 
     (0.03751744750983049*pow(hA11,2)*R21*(CS2.Re()))/mbPmc - 
     (0.008490937717314413*pow(hA11,2)*pow(R21,2)*(CS2.Re()))/mbPmc - 
     (0.0021789378469524966*pow(hA11,2)*a_3*(CS2.Re()))/mbPmc + 
     (0.0009855979226152775*pow(hA11,2)*R21*a_3*(CS2.Re()))/mbPmc - 
     (0.00003030671973485405*pow(hA11,2)*pow(a_3,2)*(CS2.Re()))/mbPmc + 
     (0.013174986773668847*pow(hA11,2)*rho_A1_2*(CS2.Re()))/mbPmc - 
     (0.01193746784975276*pow(hA11,2)*R21*rho_A1_2*(CS2.Re()))/mbPmc + 
     (0.002704063504749281*pow(hA11,2)*pow(R21,2)*rho_A1_2*(CS2.Re()))/
     mbPmc + (0.0006402381880497138*pow(hA11,2)*a_3*rho_A1_2*(CS2.Re()))/
     mbPmc - (0.0002898839301224981*pow(hA11,2)*R21*a_3*rho_A1_2*(CS2.Re()))/
     mbPmc + (8.201227824109433e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2*
	      (CS2.Re()))/mbPmc - (0.001150592951757508*pow(hA11,2)*pow(rho_A1_2,2)*
				   (CS2.Re()))/mbPmc + (0.001043158289727365*pow(hA11,2)*R21*
							pow(rho_A1_2,2)*(CS2.Re()))/mbPmc - 
     (0.00023643993251746013*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2)*
      (CS2.Re()))/mbPmc - (0.00005266795972187148*pow(hA11,2)*a_3*
			   pow(rho_A1_2,2)*(CS2.Re()))/mbPmc + 
     (0.000023863324110618327*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2)*(CS2.Re()))/
     mbPmc - (6.330191780842525e-7*pow(hA11,2)*pow(a_3,2)*
	      pow(rho_A1_2,2)*(CS2.Re()))/mbPmc)/
    (0. + pow(hA11,2)*(0.17957389170325488 - 1.0948037887075082e-18*a_3 + 
		       2.3379438621231702e-36*pow(a_3,2) - 0.08378631617748233*rho_A1_2 + 
		       5.874693941030267e-19*a_3*rho_A1_2 - 
		       1.301922254855869e-36*pow(a_3,2)*rho_A1_2 + 
		       0.01088597422339019*pow(rho_A1_2,2) - 
		       8.230978688193583e-20*a_3*pow(rho_A1_2,2) + 
		       1.8671634465810482e-37*pow(a_3,2)*pow(rho_A1_2,2) + 
		       R11*(-0.00026130896343670175 + 0.00012355740482715148*rho_A1_2 - 
			    0.000015436303110645208*pow(rho_A1_2,2)) + 
		       pow(R11,2)*(0.004402759842982002 - 0.0018896455785886214*rho_A1_2 + 
				   0.00022186379848383934*pow(rho_A1_2,2)) + 
		       pow(R21,2)*(0.018303717615447346 - 0.010242486422778429*rho_A1_2 + 
				   0.0014741148938045372*pow(rho_A1_2,2)) + 
		       R21*(-0.09657467358167796 + 0.05200218752839687*rho_A1_2 - 
			    0.007302966674209826*pow(rho_A1_2,2) + 
			    a_3*(4.136880533546651e-19 - 2.309365455120142e-19*rho_A1_2 + 
				 3.317886682533982e-20*pow(rho_A1_2,2)))));
  
  
  return f;
}


Double_t cal_rdst_full(
		      Double_t rho_A1_2, Double_t a_3, Double_t R11, Double_t R21, Double_t mbPmc, Double_t mbMmc,
		      Double_t Re_CS1, Double_t Im_CS1, Double_t Re_CS2, Double_t Im_CS2,
		      Double_t Re_CV1, Double_t Im_CV1, Double_t Re_CV2, Double_t Im_CV2,
		      Double_t Re_CT,  Double_t Im_CT
		      ){
  Double_t hA11 = 0.908;
  TComplex CS1(  Re_CS1, Im_CS1 );
  TComplex CS2(  Re_CS2, Im_CS2 );
  TComplex CV1(  Re_CV1, Im_CV1 );
  TComplex CV2(  Re_CV2, Im_CV2 );
  TComplex CT (  Re_CT,  Im_CT  );

    Double_t f = 
    (0. + (0.0003814229854998974*pow(hA11,2)*
        (200.15571614318196 - 59.04502572984423*rho_A1_2 + 
          4.870911743325851*pow(rho_A1_2,2) + 
          pow(a_3,2)*(0.16216131714996518 - 0.04054426767332307*rho_A1_2 + 
             0.0029390310478812237*pow(rho_A1_2,2)) + 
          a_3*(11.106642782949837 - 3.0183476082225646*rho_A1_2 + 
             0.233693411287558*pow(rho_A1_2,2)) + 
          pow(R21,2)*(40.955261663752275 - 12.1052559135445*rho_A1_2 + 
             1.*pow(rho_A1_2,2)) + 
          R21*(-181.078585088732 + 53.469638106474065*rho_A1_2 - 
             4.414016899669555*pow(rho_A1_2,2) + 
             a_3*(-5.020757230126823 + 1.3658857015288806*rho_A1_2 - 
                0.10583312272059556*pow(rho_A1_2,2))))*
	   pow(TComplex(CS1 - CS2).Rho(),2))/pow(mbPmc,2) + 
     pow(hA11,2)*(pow(mbPmc,2)*
         (7.951832783208808e-7 - 3.04555208567171e-7*rho_A1_2 + 
           3.025163809674795e-8*pow(rho_A1_2,2) + 
           R11*(-0.00006495101236954564 + 0.000023490263105137998*rho_A1_2 - 
              2.2398258866162303e-6*pow(rho_A1_2,2)) + 
           pow(R11,2)*(0.0014626776110531182 - 
              0.00048272573615856963*rho_A1_2 + 
              0.00004339011340339148*pow(rho_A1_2,2))) + 
        pow(mbMmc,2)*(0.025582520170939777 - 
           0.0068952506336765204*rho_A1_2 + 
           0.0005545882513819993*pow(rho_A1_2,2) + 
           a_3*(-0.00029104272223364885 + 0.00008983699796560681*rho_A1_2 - 
              7.675638397805538e-6*pow(rho_A1_2,2)) + 
           pow(R21,2)*(2.925539220531767e-37 - 
              1.0172136376844575e-37*rho_A1_2 + 
              9.394813747412587e-39*pow(rho_A1_2,2)) + 
           pow(a_3,2)*(4.189668310990552e-6 - 1.447598262665198e-6*rho_A1_2 + 
              1.3306537822597635e-7*pow(rho_A1_2,2)) + 
           R21*(-7.650336786695107e-20 + 2.372470109281603e-20*rho_A1_2 - 
              2.033670684581211e-21*pow(rho_A1_2,2) + 
              a_3*(2.2140564565540654e-21 - 7.674190752575326e-22*rho_A1_2 + 
                 7.071049276579794e-23*pow(rho_A1_2,2)))) + 
        mbMmc*mbPmc*(-1.3581280979331775e-18 - 2.5148651157300003e-22*a_3 - 
           6.035731014855145e-19*rho_A1_2 + 1.0438552759073408e-22*a_3*rho_A1_2 - 
           1.2217859042394043e-19*pow(rho_A1_2,2) - 
           1.0937471322717346e-23*a_3*pow(rho_A1_2,2) + 
           R21*(-6.711756728018738e-38 + 2.787633267724401e-38*rho_A1_2 - 
              2.9232723300967506e-39*pow(rho_A1_2,2)) + 
           R11*(-6.54616723150425e-18 - 2.1489301718287723e-17*rho_A1_2 + 
              1.2762461025711224e-18*pow(rho_A1_2,2) + 
              R21*(2.3420112653511584e-36 - 9.818794786987506e-37*rho_A1_2 + 
                 1.0184991149804732e-37*pow(rho_A1_2,2)) + 
              a_3*(8.77100670246e-21 - 3.679294937893606e-21*rho_A1_2 + 
                 3.814215477640381e-22*pow(rho_A1_2,2)))))*pow(CT.Rho(),2)\
      + 0.030254643456755624*pow(hA11,2)*pow(TComplex((TComplex)1 + CV1).Rho(),2) - 
     0.000029428775442260747*pow(hA11,2)*R11*pow(TComplex((TComplex)1 + CV1).Rho(),2) + 
     0.0007343694139646086*pow(hA11,2)*pow(R11,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 0.011072908714145064*pow(hA11,2)*R21*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) + 0.0019220011820663837*pow(hA11,2)*
      pow(R21,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.00029493794054002645*pow(hA11,2)*a_3*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     0.00013349521629621802*pow(hA11,2)*R21*a_3*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     3.887335265869437e-6*pow(hA11,2)*pow(a_3,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     0.008542734639407037*pow(hA11,2)*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     9.911598201286346e-6*pow(hA11,2)*R11*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     0.00022032907826043975*pow(hA11,2)*pow(R11,2)*rho_A1_2*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) + 0.0037396547918801*pow(hA11,2)*R21*rho_A1_2*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 0.0006697488809060423*pow(hA11,2)*
      pow(R21,2)*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     0.0000934263320002305*pow(hA11,2)*a_3*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.00004232437499355708*pow(hA11,2)*R21*a_3*rho_A1_2*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 1.1376776993503411e-6*pow(hA11,2)*
      pow(a_3,2)*rho_A1_2*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.0007082924178598534*pow(hA11,2)*pow(rho_A1_2,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 8.926704671522045e-7*pow(hA11,2)*R11*
      pow(rho_A1_2,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.000018420800360323613*pow(hA11,2)*pow(R11,2)*pow(rho_A1_2,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) - 0.0003415435683189837*pow(hA11,2)*R21*
      pow(rho_A1_2,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) + 
     0.00006245643308607658*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) + 8.13860365504776e-6*pow(hA11,2)*a_3*
      pow(rho_A1_2,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) - 
     3.689264332183857e-6*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2)*
      pow(TComplex(TComplex(1) + CV1).Rho(),2) + 9.332412489660764e-8*pow(hA11,2)*
      pow(a_3,2)*pow(rho_A1_2,2)*pow(TComplex(TComplex(1) + CV1).Rho(),2) +
     0.030254643456755624*pow(hA11,2)*pow(CV2.Rho(),2) - 
     0.000029428775442260747*pow(hA11,2)*R11*pow(CV2.Rho(),2) + 
     0.0007343694139646086*pow(hA11,2)*pow(R11,2)*pow(CV2.Rho(),2) - 
     0.011072908714145064*pow(hA11,2)*R21*pow(CV2.Rho(),2) + 
     0.0019220011820663837*pow(hA11,2)*pow(R21,2)*pow(CV2.Rho(),2) + 
     0.00029493794054002645*pow(hA11,2)*a_3*pow(CV2.Rho(),2) - 
     0.00013349521629621802*pow(hA11,2)*R21*a_3*pow(CV2.Rho(),2) + 
     3.887335265869437e-6*pow(hA11,2)*pow(a_3,2)*pow(CV2.Rho(),2) - 
     0.008542734639407037*pow(hA11,2)*rho_A1_2*pow(CV2.Rho(),2) + 
     9.911598201286346e-6*pow(hA11,2)*R11*rho_A1_2*pow(CV2.Rho(),2) - 
     0.00022032907826043975*pow(hA11,2)*pow(R11,2)*rho_A1_2*
      pow(CV2.Rho(),2) + 0.0037396547918801*pow(hA11,2)*R21*rho_A1_2*
      pow(CV2.Rho(),2) - 0.0006697488809060423*pow(hA11,2)*pow(R21,2)*
      rho_A1_2*pow(CV2.Rho(),2) - 
     0.0000934263320002305*pow(hA11,2)*a_3*rho_A1_2*pow(CV2.Rho(),2) + 
     0.00004232437499355708*pow(hA11,2)*R21*a_3*rho_A1_2*pow(CV2.Rho(),2) - 
     1.1376776993503411e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2*
      pow(CV2.Rho(),2) + 0.0007082924178598534*pow(hA11,2)*
      pow(rho_A1_2,2)*pow(CV2.Rho(),2) - 
     8.926704671522045e-7*pow(hA11,2)*R11*pow(rho_A1_2,2)*
      pow(CV2.Rho(),2) + 0.000018420800360323613*pow(hA11,2)*
      pow(R11,2)*pow(rho_A1_2,2)*pow(CV2.Rho(),2) - 
     0.0003415435683189837*pow(hA11,2)*R21*pow(rho_A1_2,2)*
      pow(CV2.Rho(),2) + 0.00006245643308607658*pow(hA11,2)*pow(R21,2)*
      pow(rho_A1_2,2)*pow(CV2.Rho(),2) + 
     8.13860365504776e-6*pow(hA11,2)*a_3*pow(rho_A1_2,2)*
      pow(CV2.Rho(),2) - 3.689264332183857e-6*pow(hA11,2)*R21*a_3*
      pow(rho_A1_2,2)*pow(CV2.Rho(),2) + 
     9.332412489660764e-8*pow(hA11,2)*pow(a_3,2)*pow(rho_A1_2,2)*
      pow(CV2.Rho(),2) + (0.04144330132436068*pow(hA11,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.03751744750983049*pow(hA11,2)*R21*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.008490937717314413*pow(hA11,2)*pow(R21,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.0021789378469524966*pow(hA11,2)*a_3*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.0009855979226152775*pow(hA11,2)*R21*a_3*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.00003030671973485405*pow(hA11,2)*pow(a_3,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.013174986773668847*pow(hA11,2)*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.01193746784975276*pow(hA11,2)*R21*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.002704063504749281*pow(hA11,2)*pow(R21,2)*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.0006402381880497138*pow(hA11,2)*a_3*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.0002898839301224981*pow(hA11,2)*R21*a_3*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (8.201227824109433e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.001150592951757508*pow(hA11,2)*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.001043158289727365*pow(hA11,2)*R21*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.00023643993251746013*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (0.00005266795972187148*pow(hA11,2)*a_3*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc - 
     (0.000023863324110618327*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     (6.330191780842525e-7*pow(hA11,2)*pow(a_3,2)*pow(rho_A1_2,2)*
        TComplex(((TComplex)1 + CV1 - CV2)*(TComplex::Conjugate(CS1) - TComplex::Conjugate(CS2))).Re())/mbPmc + 
     0.043439468009419516*pow(hA11,2)*mbMmc*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     9.798284135027003e-7*pow(hA11,2)*mbPmc*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     1.8655855168452323e-19*pow(hA11,2)*mbMmc*R11*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.00008243139537072506*pow(hA11,2)*mbPmc*R11*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     0.0019292013079590545*pow(hA11,2)*mbPmc*pow(R11,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 0.0034193696288309103*pow(hA11,2)*mbMmc*R21*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 3.401673954395168e-21*pow(hA11,2)*mbPmc*R21*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 1.1860839048240666e-19*pow(hA11,2)*mbPmc*
      R11*R21*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     2.7286114008961167e-20*pow(hA11,2)*mbMmc*pow(R21,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 0.00042445809518316664*pow(hA11,2)*mbMmc*a_3*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 3.925810877538916e-38*pow(hA11,2)*mbPmc*a_3*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 1.3687507790235089e-36*pow(hA11,2)*mbPmc*
      R11*a_3*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     0.00010311438255775624*pow(hA11,2)*mbMmc*R21*a_3*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 1.2009435683456312e-21*pow(hA11,2)*mbMmc*
      pow(a_3,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.01161218633941612*pow(hA11,2)*mbMmc*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     3.671921590794541e-7*pow(hA11,2)*mbPmc*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     5.941230378828234e-20*pow(hA11,2)*mbMmc*R11*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 0.000029013422192823387*pow(hA11,2)*mbPmc*
      R11*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.0006143824185095328*pow(hA11,2)*mbPmc*pow(R11,2)*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 0.0010999351744124196*pow(hA11,2)*mbMmc*R21*
      rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     1.4233343671470915e-21*pow(hA11,2)*mbPmc*R21*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 4.972454414285408e-20*pow(hA11,2)*mbPmc*R11*
      R21*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     9.737246894582423e-21*pow(hA11,2)*mbMmc*pow(R21,2)*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 0.00013948436590074546*pow(hA11,2)*mbMmc*a_3*
      rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     1.6415007515343318e-38*pow(hA11,2)*mbPmc*a_3*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 5.739045781158288e-37*pow(hA11,2)*mbPmc*R11*
      a_3*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.000036689865865273666*pow(hA11,2)*mbMmc*R21*a_3*rho_A1_2*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 4.260582028894552e-22*pow(hA11,2)*mbMmc*
      pow(a_3,2)*rho_A1_2*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     0.000925606417129734*pow(hA11,2)*mbMmc*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 3.581177810278494e-8*pow(hA11,2)*mbPmc*
      pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     5.194937572194414e-21*pow(hA11,2)*mbMmc*R11*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 2.7059893094927234e-6*pow(hA11,2)*mbPmc*R11*
      pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     0.00005372083063766073*pow(hA11,2)*mbPmc*pow(R11,2)*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 0.00009686213016794422*pow(hA11,2)*mbMmc*
      R21*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     1.5052469308078281e-22*pow(hA11,2)*mbPmc*R21*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 5.195400166308854e-21*pow(hA11,2)*mbPmc*R11*
      R21*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     9.177660983172838e-22*pow(hA11,2)*mbMmc*pow(R21,2)*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() - 0.000012466760784620066*pow(hA11,2)*mbMmc*
      a_3*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     1.7345605810270768e-39*pow(hA11,2)*mbPmc*a_3*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 5.992292388488751e-38*pow(hA11,2)*mbPmc*R11*
      a_3*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() + 
     3.450552924495197e-6*pow(hA11,2)*mbMmc*R21*a_3*pow(rho_A1_2,2)*
      TComplex(CV2*TComplex::Conjugate(CT)).Re() + 3.998057390849867e-23*pow(hA11,2)*mbMmc*
      pow(a_3,2)*pow(rho_A1_2,2)*TComplex(CV2*TComplex::Conjugate(CT)).Re() - 
     0.043439468009419516*pow(hA11,2)*mbMmc*TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     9.79828413474989e-7*pow(hA11,2)*mbPmc*TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     1.8655855168452323e-19*pow(hA11,2)*mbMmc*R11*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.00008243139536951311*pow(hA11,2)*mbPmc*R11*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.0019292013079590545*pow(hA11,2)*mbPmc*pow(R11,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.0034193696288309103*pow(hA11,2)*mbMmc*R21*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     3.401673954395168e-21*pow(hA11,2)*mbPmc*R21*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.1860839048240664e-19*pow(hA11,2)*mbPmc*R11*R21*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     2.7286114008961167e-20*pow(hA11,2)*mbMmc*pow(R21,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.00042445809518316664*pow(hA11,2)*mbMmc*a_3*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     3.925810877538916e-38*pow(hA11,2)*mbPmc*a_3*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.3687507790235089e-36*pow(hA11,2)*mbPmc*R11*a_3*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.00010311438255775624*pow(hA11,2)*mbMmc*R21*a_3*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.2009435683456316e-21*pow(hA11,2)*mbMmc*pow(a_3,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.01161218633941612*pow(hA11,2)*mbMmc*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     3.671921590823067e-7*pow(hA11,2)*mbPmc*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     5.941230378828233e-20*pow(hA11,2)*mbMmc*R11*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.000029013422192870672*pow(hA11,2)*mbPmc*R11*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.0006143824185095327*pow(hA11,2)*mbPmc*pow(R11,2)*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.0010999351744124196*pow(hA11,2)*mbMmc*R21*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.4233343671470917e-21*pow(hA11,2)*mbPmc*R21*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     4.972454414285407e-20*pow(hA11,2)*mbPmc*R11*R21*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     9.73724689458242e-21*pow(hA11,2)*mbMmc*pow(R21,2)*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.00013948436590074546*pow(hA11,2)*mbMmc*a_3*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     1.6415007515343315e-38*pow(hA11,2)*mbPmc*a_3*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     5.739045781158287e-37*pow(hA11,2)*mbPmc*R11*a_3*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.000036689865865273666*pow(hA11,2)*mbMmc*R21*a_3*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     4.260582028894552e-22*pow(hA11,2)*mbMmc*pow(a_3,2)*rho_A1_2*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.0009256064171297339*pow(hA11,2)*mbMmc*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     3.58117781030956e-8*pow(hA11,2)*mbPmc*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     5.194937572194414e-21*pow(hA11,2)*mbMmc*R11*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     2.705989309492176e-6*pow(hA11,2)*mbPmc*R11*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.000053720830637660746*pow(hA11,2)*mbPmc*pow(R11,2)*
      pow(rho_A1_2,2)*TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.00009686213016794424*pow(hA11,2)*mbMmc*R21*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     1.5052469308078281e-22*pow(hA11,2)*mbPmc*R21*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     5.195400166308854e-21*pow(hA11,2)*mbPmc*R11*R21*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     9.177660983172838e-22*pow(hA11,2)*mbMmc*pow(R21,2)*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     0.000012466760784620066*pow(hA11,2)*mbMmc*a_3*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() + 
     1.7345605810270768e-39*pow(hA11,2)*mbPmc*a_3*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     5.992292388488751e-38*pow(hA11,2)*mbPmc*R11*a_3*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     3.450552924495197e-6*pow(hA11,2)*mbMmc*R21*a_3*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     3.998057390849867e-23*pow(hA11,2)*mbMmc*pow(a_3,2)*pow(rho_A1_2,2)*
      TComplex(CT + CV1*TComplex::Conjugate(CT)).Re() - 
     0.06050795291702513*pow(hA11,2)*TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.000058857550884521494*pow(hA11,2)*R11*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.0014687388279292172*pow(hA11,2)*pow(R11,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.022145817428290124*pow(hA11,2)*R21*TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0038440023641327674*pow(hA11,2)*pow(R21,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0005898758810800529*pow(hA11,2)*a_3*TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.00026699043259243604*pow(hA11,2)*R21*a_3*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     7.774670531738875e-6*pow(hA11,2)*pow(a_3,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.017084986257558863*pow(hA11,2)*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.000019823196402572692*pow(hA11,2)*R11*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0004406581565208795*pow(hA11,2)*pow(R11,2)*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0074793095837602*pow(hA11,2)*R21*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.0013394977618120844*pow(hA11,2)*pow(R21,2)*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.000186852664000461*pow(hA11,2)*a_3*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.00008464874998711415*pow(hA11,2)*R21*a_3*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     2.2753553987006822e-6*pow(hA11,2)*pow(a_3,2)*rho_A1_2*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.0014165390405698939*pow(hA11,2)*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     1.785340934304409e-6*pow(hA11,2)*R11*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.000036841600720647225*pow(hA11,2)*pow(R11,2)*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     0.0006830871366379674*pow(hA11,2)*R21*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.00012491286617215315*pow(hA11,2)*pow(R21,2)*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     0.00001627720731009552*pow(hA11,2)*a_3*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() + 
     7.378528664367714e-6*pow(hA11,2)*R21*a_3*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re() - 
     1.8664824979321527e-7*pow(hA11,2)*pow(a_3,2)*pow(rho_A1_2,2)*
      TComplex(CV2 + CV1*TComplex::Conjugate(CV2)).Re())/
   (0. + pow(hA11,2)*(0.17957389170325488 - 1.0948037887075082e-18*a_3 + 
        2.3379438621231702e-36*pow(a_3,2) - 0.08378631617748233*rho_A1_2 + 
        5.874693941030267e-19*a_3*rho_A1_2 - 
        1.301922254855869e-36*pow(a_3,2)*rho_A1_2 + 
        0.01088597422339019*pow(rho_A1_2,2) - 
        8.230978688193583e-20*a_3*pow(rho_A1_2,2) + 
        1.8671634465810482e-37*pow(a_3,2)*pow(rho_A1_2,2) + 
        R11*(-0.00026130896343670175 + 0.00012355740482715148*rho_A1_2 - 
           0.000015436303110645208*pow(rho_A1_2,2)) + 
        pow(R11,2)*(0.004402759842982002 - 0.0018896455785886214*rho_A1_2 + 
           0.00022186379848383934*pow(rho_A1_2,2)) + 
        pow(R21,2)*(0.018303717615447346 - 0.010242486422778429*rho_A1_2 + 
           0.0014741148938045372*pow(rho_A1_2,2)) + 
        R21*(-0.09657467358167796 + 0.05200218752839687*rho_A1_2 - 
           0.007302966674209826*pow(rho_A1_2,2) + 
           a_3*(4.136880533546651e-19 - 2.309365455120142e-19*rho_A1_2 + 
	   3.317886682533982e-20*pow(rho_A1_2,2)))))
	     ;
  return f;
}

#endif
