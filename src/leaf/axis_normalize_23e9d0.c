// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Look up the mode and the local axis for table entry `index`, rotate the axis by the matrix and store its normalized
// form (or the fallback vector D_00317560 when the length is below 0.0001). Port of Sly 2 func_001F5510.
typedef int qword __attribute__((mode(TI)));
typedef struct { qword row[3]; } M3;
struct OUT { qword axis; int mode; };
extern int D_00349830[];
extern qword D_003497B0[];
extern qword D_00317560;
static inline qword Transform(M3 *matrix,qword value) {
    qword x=matrix->row[0];
    qword y=matrix->row[1];
    register qword z __asm__("vf3")=matrix->row[2]; /* register pin: row 2 lives in vf3 */
    __asm__("vmulax.xyz $ACC,%1,%3x\n\tvmadday.xyz $ACC,%2,%3y\n\tvmaddz.xyz %0,%0,%3z" : "+j"(z) : "j"(x),"j"(y),"j"(value));
    return z;
}
static inline qword NormalizeOr(qword value,qword fallback) {
    register qword length __asm__("vf1");
    qword one;
    register qword result __asm__("vf1");
    float scalar;
    __asm__("vmul.xyz %0,%2,%2\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x $ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z" : "=j"(length),"=&j"(one) : "j"(value));
    __asm__("vsqrt $Q,%1x\n\tvwaitq\n\tvaddq.x %0,$vf0,$Q" : "=j"(length) : "j"(length));
    __asm__("mtc1 %1,%0" : "=f"(scalar) : "r"(length));
    if(scalar<0.0001f) result=fallback;
    else __asm__("vdiv $Q,$vf0w,%1x\n\tvwaitq\n\tvmulq.xyzw %0,%2,$Q" : "=j"(result) : "j"(length),"j"(value));
    return result;
}
void func_0023E9D0(void *unused,M3 *matrix,int index,struct OUT *out) {
    out->mode=D_00349830[index];
    out->axis=NormalizeOr(Transform(matrix,D_003497B0[index]),D_00317560);
}
