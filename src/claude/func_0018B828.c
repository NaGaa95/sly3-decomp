// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct SEQ { int n0; int a4[8]; };
struct Self {
    unsigned char pad[0x34]; int state; float t38; unsigned char pad3C[0x44 - 0x3C]; struct SEQ *pseq;
    unsigned char pad48[0x50 - 0x48]; int n50; float t54; int n58; int a5C[4]; float t6C; int n70;
};
struct GAME { unsigned char pad[0x1F40]; void *p1F40; };
extern struct CLOCK { float t; } g_clock;
extern struct GAME *D_00370AC0;
void func_0018BB20(struct Self *s, int state);
int func_0018C170(struct Self *s);
int func_00260738(void *p);
void func_0018B828(struct Self *s)
{
    int st;
    do {
        st = s->state;
        switch (st) {
        case 0:
            if (g_clock.t - s->t38 > 0.1f) func_0018BB20(s, 1);
            break;
        case 1:
            if (func_0018C170(s)) func_0018BB20(s, 2);
            break;
        case 2:
            if (func_0018C170(s)) func_0018BB20(s, 3);
            break;
        case 3:
            if (g_clock.t - s->t54 > 0.33f) {
                float t;
                s->n50++;
                t = g_clock.t;
                s->t54 = t;
                if (s->n50 == 4) s->t54 = t + 0.25f;
                else if (s->n50 >= 5) func_0018BB20(s, 4);
            }
            break;
        case 4: {
            void *p = D_00370AC0->p1F40;
            if (!p || func_00260738(p)) func_0018BB20(s, 5);
            break;
        }
        case 5: {
            int i;
            for (i = 0; i < s->n58; i++) {
                if (s->a5C[i] != s->pseq->a4[i]) break;
            }
            if (i < s->n58) {
                func_0018BB20(s, 6);
            } else if (s->n58 >= 4) {
                s->n70 = 1;
                func_0018BB20(s, 6);
            } else if (g_clock.t - s->t6C > 0.75f) {
                func_0018BB20(s, 0xC);
            }
            break;
        }
        case 6:
            if (g_clock.t - s->t38 > 0.5f) func_0018BB20(s, s->n70 ? 7 : 9);
            break;
        case 7:
            if (func_0018C170(s)) func_0018BB20(s, 8);
            break;
        case 9:
            if (func_0018C170(s)) func_0018BB20(s, 0xA);
            break;
        case 8:
        case 10:
        case 12:
            if (func_0018C170(s)) func_0018BB20(s, -1);
            break;
        case 11:
            func_0018BB20(s, -1);
            break;
        }
    } while (st != s->state);
}
