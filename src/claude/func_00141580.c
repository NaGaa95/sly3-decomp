// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t; };
extern struct CLOCK g_clock;
struct T { unsigned char pad[0x2F]; unsigned long flags : 8; char pad2[0x4C - 0x30]; float f4C; float f50; float pad54; float f58; };
#define I(o) (*(int *)((char *)s + (o)))
#define F(o) (*(float *)((char *)s + (o)))
#define P(o) (*(struct T **)((char *)s + (o)))
void func_00142750(void *s);
int func_001469B0(void *s);
void func_00142E18(void *s);
void func_00143E50(void *s);
void func_00144580(void *s);
void func_00146B80(void *s);
void func_00142AE0(void *s, int st);
void func_00143D08(void *s);
int func_0023E130(void *s);
int func_001468A8(void *s);
void func_00141580(char *s)
{
    int st;
    func_00142750(s);
    do {
        st = I(0x2B0);
        switch (st) {
        case 0:
            break;
        case 1:
            switch (I(0x198)) {
            case 0:
                if (!func_001469B0(s))
                    func_00142E18(s);
                else
                    func_00142AE0(s, 2);
                break;
            case 1:
                func_00143E50(s);
                break;
            case 2:
                func_00144580(s);
                break;
            }
            break;
        case 2: {
            struct T *o = P(0x42C);
            int c = 1;
            if (o && (o->flags & 1) && g_clock.t - o->f58 < o->f4C)
                c = 0;
            if (c) {
                func_00146B80(s);
                func_00142AE0(s, 1);
            }
            break;
        }
        case 3:
            if (func_001469B0(s))
                func_00142AE0(s, 2);
            else
                func_00143D08(s);
            break;
        case 4: {
            int c = !I(0x198) && I(0x208);
            if (c) {
                struct T *o = P(0x204);
                int c2 = 1;
                if (o && (o->flags & 1) && g_clock.t - o->f58 < o->f4C + o->f50)
                    c2 = 0;
                if (c2) {
                    func_00146B80(s);
                    func_00142AE0(s, 1);
                }
            } else if (g_clock.t - F(0x2B4) > 5.0f) {
                func_00142AE0(s, -1);
                func_00142AE0(s, 4);
            } else if (!func_0023E130(s) && func_001468A8(s)) {
                func_00142AE0(s, 1);
            }
            break;
        }
        case 5:
            I(0x400) = 0;
            break;
        }
    } while (st != I(0x2B0));
}

/* Next .rodata items of the original unit (-FLT_MAX literals read by func_00141B78 and func_00141FD8). */
const float D_00320008 = -3.402823466e+38f;
const float D_0032000C = -3.402823466e+38f;
