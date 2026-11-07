// SLY3_CC: tools/third_party/ee-gcc2.9-991111-01
// SLY3_CFLAGS: -O2 -G0
// func_002A6558: __ieee754_expf (fdlibm/newlib ef_exp.c, old-style threshold tests)
typedef int __int32_t;
typedef unsigned int __uint32_t;
typedef union { float value; __uint32_t word; } ieee_float_shape_type;
#define GET_FLOAT_WORD(i,d) do { ieee_float_shape_type gf_u; gf_u.value = (d); (i) = gf_u.word; } while (0)
#define SET_FLOAT_WORD(d,i) do { ieee_float_shape_type sf_u; sf_u.word = (i); (d) = sf_u.value; } while (0)
static const float
one	= 1.0,
halF[2]	= {0.5,-0.5,},
huge	= 1.0e+30,
twom100 = 7.8886090522e-31,
o_threshold=  8.8721679688e+01,
u_threshold= -1.0397208405e+02,
ln2HI[2]   ={ 6.9313812256e-01,
	     -6.9313812256e-01,},
ln2LO[2]   ={ 9.0580006145e-06,
	     -9.0580006145e-06,},
invln2 =  1.4426950216e+00,
P1   =  1.6666667163e-01,
P2   = -2.7777778450e-03,
P3   =  6.6137559770e-05,
P4   = -1.6533901999e-06,
P5   =  4.1381369442e-08;

float func_002A6558(float x)
{
	float y,hi,lo,c,t;
	__int32_t k,xsb;
	__uint32_t hx;

	GET_FLOAT_WORD(hx,x);
	xsb = (hx>>31)&1;
	hx &= 0x7fffffff;

	if(hx >= 0x42b17218) {
	    if(hx>0x7f800000)
		return x+x;
	    if(hx==0x7f800000)
		return (xsb==0)? x:0.0;
	    if(x > o_threshold) return huge*huge;
	    if(x < u_threshold) return twom100*twom100;
	}

	if(hx > 0x3eb17218) {
	    if(hx < 0x3F851592) {
		hi = x-ln2HI[xsb]; lo=ln2LO[xsb]; k = 1-xsb-xsb;
	    } else {
		k  = invln2*x+halF[xsb];
		t  = k;
		hi = x - t*ln2HI[0];
		lo = t*ln2LO[0];
	    }
	    x  = hi - lo;
	}
	else if(hx < 0x31800000)  {
	    if(huge+x>one) return one+x;
	}
	else k = 0;

	t  = x*x;
	c  = x - t*(P1+t*(P2+t*(P3+t*(P4+t*P5))));
	if(k==0) 	return one-((x*c)/(c-(float)2.0)-x);
	else 		y = one-((lo-(x*c)/((float)2.0-c))-hi);
	if(k >= -125) {
	    __uint32_t hy;
	    GET_FLOAT_WORD(hy,y);
	    SET_FLOAT_WORD(y,hy+(k<<23));
	    return y;
	} else {
	    __uint32_t hy;
	    GET_FLOAT_WORD(hy,y);
	    SET_FLOAT_WORD(y,hy+((k+100)<<23));
	    return y*twom100;
	}
}
