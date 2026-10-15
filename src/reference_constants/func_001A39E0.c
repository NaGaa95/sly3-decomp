// Reference algorithm: src/hand/func_00174B68.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
struct S { char pad[0x38]; int n30; char pad2[0xC]; void *p40; };
void func_002389A0(struct S *p);
int func_00238AD0(void *p);
void func_001A3860(struct S *p, int n);
void func_001A39E0(struct S *p) {
    int s;
    func_002389A0(p);
    do {
        s = p->n30;
        if (s == 0 && func_00238AD0(p)) func_001A3860(p, -1);
    } while (s != p->n30);
}
