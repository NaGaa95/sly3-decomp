// Sly 2 counterpart: pow (decomp src/lib/pow.c)
// newlib w_pow.c.
// SLY3_CC: tools/third_party/ee-gcc2.9-991111
// SLY3_CFLAGS: -O2 -G0
// SLY3_ASM: gnu-reorder-db
struct exception {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
    int err;
};
extern const int D_0032C2F0;
extern const double D_0032C2E8;
double func_002A4A70(double x, double y);
int func_002A86A8(double x);
int func_002A8688(double x);
double func_002A8708(double x);
int matherr(struct exception *x);
int *func_0029EE48(void);
#define _LIB_VERSION D_0032C2F0
#define _IEEE_ -1
#define _SVID_ 0
#define _POSIX_ 2
#define DOMAIN 1
#define OVERFLOW 3
#define UNDERFLOW 4
#define errno (*func_0029EE48())
#define EDOM 33
#define ERANGE 34
#define HUGE 3.40282346638528859812e+38
#define HUGE_VAL D_0032C2E8
#define isnan func_002A86A8
#define finite func_002A8688
#define rint func_002A8708
double func_002A38B8(double x, double y)
{
	double z;
	struct exception exc;
	z=func_002A4A70(x,y);
	if(_LIB_VERSION == _IEEE_|| isnan(y)) return z;
	if(isnan(x)) {
	    if(y==0.0) { 
		exc.type = DOMAIN;
		exc.name = "pow";
		exc.err = 0;
		exc.arg1 = x;
		exc.arg2 = y;
		exc.retval = x;
		if (_LIB_VERSION == _IEEE_ ||
		    _LIB_VERSION == _POSIX_) exc.retval = 1.0;
		else if (!matherr(&exc)) {
			errno = EDOM;
		}
	        if (exc.err != 0)
	           errno = exc.err;
                return exc.retval; 
	    } else 
		return z;
	}
	if(x==0.0){ 
	    if(y==0.0) {
		exc.type = DOMAIN;
		exc.name = "pow";
		exc.err = 0;
		exc.arg1 = x;
		exc.arg2 = y;
		exc.retval = 0.0;
		if (_LIB_VERSION != _SVID_) exc.retval = 1.0;
		else if (!matherr(&exc)) {
			errno = EDOM;
		}
	        if (exc.err != 0)
	           errno = exc.err;
                return exc.retval; 
	    }
	    if(finite(y)&&y<0.0) {
		exc.type = DOMAIN;
		exc.name = "pow";
		exc.err = 0;
		exc.arg1 = x;
		exc.arg2 = y;
		if (_LIB_VERSION == _SVID_)
		  exc.retval = 0.0;
		else
		  exc.retval = -HUGE_VAL;
		if (_LIB_VERSION == _POSIX_)
		  errno = EDOM;
		else if (!matherr(&exc)) {
		  errno = EDOM;
		}
	        if (exc.err != 0)
	           errno = exc.err;
                return exc.retval; 
	    }
	    return z;
	}
	if(!finite(z)) {
	    if(finite(x)&&finite(y)) {
	        if(isnan(z)) {
		    exc.type = DOMAIN;
		    exc.name = "pow";
		    exc.err = 0;
		    exc.arg1 = x;
		    exc.arg2 = y;
		    if (_LIB_VERSION == _SVID_) 
		        exc.retval = 0.0;
		    else 
		        exc.retval = 0.0/0.0;
		    if (_LIB_VERSION == _POSIX_) 
		        errno = EDOM;
		    else if (!matherr(&exc)) {
		        errno = EDOM;
		    }
	            if (exc.err != 0)
	                errno = exc.err;
                    return exc.retval; 
	        } else {
		    exc.type = OVERFLOW;
		    exc.name = "pow";
		    exc.err = 0;
		    exc.arg1 = x;
		    exc.arg2 = y;
		    if (_LIB_VERSION == _SVID_) {
		       exc.retval = HUGE;
		       y *= 0.5;
		       if(x<0.0&&rint(y)!=y) exc.retval = -HUGE;
		    } else {
		       exc.retval = HUGE_VAL;
		       y *= 0.5;
		       if(x<0.0&&rint(y)!=y) exc.retval = -HUGE_VAL;
		    }
		    if (_LIB_VERSION == _POSIX_)
		        errno = ERANGE;
		    else if (!matherr(&exc)) {
			errno = ERANGE;
		    }
	            if (exc.err != 0)
	                errno = exc.err;
                    return exc.retval; 
	        }
	    }
	} 
	if(z==0.0&&finite(x)&&finite(y)) {
	    exc.type = UNDERFLOW;
	    exc.name = "pow";
	    exc.err = 0;
	    exc.arg1 = x;
	    exc.arg2 = y;
	    exc.retval =  0.0;
	    if (_LIB_VERSION == _POSIX_)
	        errno = ERANGE;
	    else if (!matherr(&exc)) {
	        errno = ERANGE;
	    }
	    if (exc.err != 0)
	        errno = exc.err;
            return exc.retval; 
        }
	return z;
}
