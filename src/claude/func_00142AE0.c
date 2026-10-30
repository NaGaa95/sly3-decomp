// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct Method { short delta, reserved; void (*call)(void *, ...); };
#define I(o) (*(int *)((char *)s + (o)))
#define F(o) (*(float *)((char *)s + (o)))
#define P(o) (*(void **)((char *)s + (o)))
#define VCALL(n) (s->methods[n].call)((unsigned char *)s + s->methods[n].delta
struct S { unsigned char pad00[0xC]; struct Method *methods; };
extern char D_0036C700[];
extern qword D_00317560;
void func_00262280(void *p, int n);
void func_00143230(void *s, int n);
void func_00143B30(void *s, int n);
void func_00240DB0(void *s);
void func_00137628(void *p);
void func_001854C8(void *g, int n, void *s);
void func_0017D840(void *p, void *s);
void func_0017D7D0(void *p);
void func_00146558(void *s);
void func_001FE728(void *p, int n);
void func_00142AE0(struct S *s, int st)
{
    int old = I(0x2B0);
    if (st == old)
        return;
    switch (old) {
    case 1:
        I(0x418) = 0;
        I(0x410) = 0;
        if (!I(0x198) && P(0x168))
            func_00262280(P(0x168), 0x78A);
        func_00143230(s, 0);
        break;
    case 3:
        func_00143B30(s, -1);
        break;
    case 4:
    case 5:
        func_00240DB0(s);
        break;
    }
    I(0x2B0) = st;
    F(0x2B4) = g_clock.t;
    switch (st) {
    case 2:
        func_00137628((char *)s + 0x234);
        func_001854C8(D_0036C700, 0x54, s);
        if (P(0x42C))
            func_0017D840(P(0x42C), s);
        VCALL(40), D_00317560);
        VCALL(41), D_00317560);
        break;
    case 3:
        func_00143B30(s, 0);
        break;
    case 1:
        F(0x400) = F(0x19C);
        break;
    case 4: {
        int c = !I(0x198) && I(0x208);
        if (c) {
            if (P(0x204))
                func_0017D7D0(P(0x204));
            VCALL(40), D_00317560);
            VCALL(41), D_00317560);
        } else {
            func_00146558(s);
        }
        break;
    }
    case 5:
        if (P(0x384))
            func_001FE728(P(0x384), 1);
        VCALL(9));
        if (!I(0x198))
            func_001854C8(D_0036C700, 0xC, s);
        else if (I(0x190) == 1)
            func_001854C8(D_0036C700, 0x53, s);
        break;
    }
}

/* Next .rodata item of the original unit (the FLT_MAX literal of the following function). */
const float D_00320094 = 3.402823466e+38f;
