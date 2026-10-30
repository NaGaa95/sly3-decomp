// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct S { char pad[0x3EB8]; int c; void *ap[5]; float af[4]; float ag[4]; };
int func_00168DD8(void *p);
int func_0013B500(void *p, int k);
void func_00165B88(struct S *p)
{
    int i;
    float *pf = p->af;
    float *pg = p->ag;
    pf[3] = 0; pf[2] = 0; pf[1] = 0; pf[0] = 0;
    pg[3] = 0; pg[2] = 0; pg[1] = 0; pg[0] = 0;
    for (i = 0; i < p->c; i++) {
        void *o = p->ap[i];
        if (!func_00168DD8(o))
            pf[i] = 1.0f;
        if (!func_0013B500(o, 6))
            pg[i] = 1.0f;
    }
}

