typedef int qword __attribute__((mode(TI)));
void func_0012DCC0(void *p, float *pt0, float *pt1, qword *pa, qword *pb, qword *pva, qword *pvb);
void func_00118558(float tMax, float t, float s, qword a, qword va, qword b, qword vb, qword *ppos, qword *pv, int n);
/* Hermite evaluation: func_0012DCC0 fetches the bracketing key times, positions and tangents; func_00118558 interpolates. */
typedef union { qword q; float f[4]; } U;
void func_0012DC28(void *p, float t, float s, qword *ppos, qword *pv)
{ U a, b, va, vb; float t0, t1;
    func_0012DCC0(p, &t0, &t1, &a.q, &b.q, &va.q, &vb.q);
    func_00118558(t1 - t0, t - t0, s, a.q, va.q, b.q, vb.q, ppos, pv, 0); }
