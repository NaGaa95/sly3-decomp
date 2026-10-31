// SLY3_CFLAGS: -Os -G0 -ffast-math
struct MSG { int kind; };
struct OWNER;
struct S { struct MSG msg; int word4; int x8; int *xC; int pad[3]; unsigned flags; };
extern struct OWNER D_0046F550;
void func_001D3FC0(struct OWNER *g, struct MSG *s);
void func_001D4510(struct S *s)
{
    int i;
    int *a = s->xC;
    for (i = 0; i < s->x8; i++) {
        if (s->msg.kind == a[i]) {
            i++;
            s->msg.kind = a[i % s->x8];
            break;
        }
    }
    func_001D3FC0(&D_0046F550, &s->msg);
    s->flags |= 2;
}
