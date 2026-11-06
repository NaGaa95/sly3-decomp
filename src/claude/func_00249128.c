// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct G { char pad[0x238]; void *p238; };
extern struct G D_00474FF0;
int func_002489A0(struct G *);
void func_00246190(void *, int, float);
void func_00246230(void *, int, int);
void func_00249128(int a, int b, float g, int c)
{
    int k = func_002489A0(&D_00474FF0);
    void *o = D_00474FF0.p238;
    if (o) {
        func_00246190(o, k, g);
        func_00246230(o, k, c);
    }
}
