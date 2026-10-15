// Reference algorithm: src/hand/func_001AC4C8.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct B { char pad[0x6808]; char x5408[0x44]; int x544C; int x5450; };
void func_00292034(void *p, int c, int n);
void func_001CFB40(void *s, void *b, char *name);
int func_001D0058(void *s, char *name, void *p);
int func_001D0A68(void *s, char *name, void *b, int n);
int func_001D0588(void *s, struct B *b)
{
    char name[0x50];
    int r;
    func_00292034(b, 0, 0x6864);
    func_001CFB40(s, b, name);
    r = func_001D0058(s, name, b->x5408);
    if (r)
        return r;
    if ((b->x5450 & 0xD4) != 4)
        return 0x14;
    if (b->x544C != 0x6808)
        return 0x1C;
    return func_001D0A68(s, name, b, 0x6808);
}
