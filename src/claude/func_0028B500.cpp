// Port of Sly 2 func_0022CB90 (src/hand/func_0022CB90.cpp).
typedef int qword __attribute__((mode(TI)));
struct V {qword q;};
struct M4 { qword r[4];  };
extern "C" qword func_0028B440(qword,qword);
extern "C" M4 func_0028B640(void *,void *,V);
extern "C" M4 func_0028B500(void *a,void *b,qword c,qword d) return m {
    V v;v.q=func_0028B440(c,d);
    m=func_0028B640(a,b,v);
}
