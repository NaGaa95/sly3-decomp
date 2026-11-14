// Sly 2 counterpart: __ieee754_acosf (decomp src/lib/__ieee754_acosf.c)
// fdlibm/newlib ef_acos.c, written fresh. Sony libm compiler = ee-gcc2.9-991111-01, whose divsf3 pattern is the
// noreorder unit `nop; nop; div.s` (length 3: never put in a delay slot, but not a reorg search stop), so the DIVNOP emulation is not needed.
// SLY3_CC: tools/third_party/ee-gcc2.9-991111-01
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
/* fdlibm/newlib ef_acos.c
 * Copyright (C) 1993 by Sun Microsystems, Inc. All rights reserved.
 * Developed at SunPro, a Sun Microsystems, Inc. business.
 * Permission to use, copy, modify, and distribute this software is freely
 * granted, provided that this notice is preserved.
 */
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef union { float value; __uint32_t word; } ieee_float_shape_type;
#define GET_FLOAT_WORD(i,d) do { ieee_float_shape_type gf_u; gf_u.value = (d); (i) = gf_u.word; } while (0)
#define SET_FLOAT_WORD(d,i) do { ieee_float_shape_type sf_u; sf_u.word = (i); (d) = sf_u.value; } while (0)
float func_002A76D0(float x);

static const float
one =  1.0000000000e+00,
pi =  3.1415925026e+00,
pio2_hi =  1.5707962513e+00,
pio2_lo =  7.5497894159e-08,
pS0 =  1.6666667163e-01,
pS1 = -3.2556581497e-01,
pS2 =  2.0121252537e-01,
pS3 = -4.0055535734e-02,
pS4 =  7.9153501429e-04,
pS5 =  3.4793309169e-05,
qS1 = -2.4033949375e+00,
qS2 =  2.0209457874e+00,
qS3 = -6.8828397989e-01,
qS4 =  7.7038154006e-02;

float func_002A5AA0(float x)
{
	float z,p,q,r,w,s,c,df;
	__int32_t hx,ix;
	GET_FLOAT_WORD(hx,x);
	ix = hx&0x7fffffff;
	if(ix==0x3f800000) {		/* |x|==1 */
	    if(hx>0) return 0.0;	/* acos(1) = 0  */
	    else return pi+(float)2.0*pio2_lo;	/* acos(-1)= pi */
	} else if(ix>0x3f800000) {	/* |x| >= 1 */
	    return (x-x)/(x-x);		/* acos(|x|>1) is NaN */
	}
	if(ix<0x3f000000) {	/* |x| < 0.5 */
	    if(ix<=0x23000000) return pio2_hi+pio2_lo;/*if|x|<2**-57*/
	    z = x*x;
	    p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
	    q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
	    r = p/q;
	    return pio2_hi - (x - (pio2_lo-x*r));
	} else  if (hx<0) {		/* x < -0.5 */
	    z = (one+x)*(float)0.5;
	    p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
	    q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
	    s = func_002A76D0(z);
	    r = p/q;
	    w = r*s-pio2_lo;
	    return pi - (float)2.0*(s+w);
	} else {			/* x > 0.5 */
	    __int32_t idf;
	    z = (one-x)*(float)0.5;
	    s = func_002A76D0(z);
	    df = s;
	    GET_FLOAT_WORD(idf,df);
	    SET_FLOAT_WORD(df,idf&0xfffff000);
	    c  = (z-df*df)/(s+df);
	    p = z*(pS0+z*(pS1+z*(pS2+z*(pS3+z*(pS4+z*pS5)))));
	    q = one+z*(qS1+z*(qS2+z*(qS3+z*qS4)));
	    r = p/q;
	    w = r*s+c;
	    return (float)2.0*(df+w);
	}
}
