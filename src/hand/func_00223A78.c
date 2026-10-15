// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct S { char pad[0x70]; unsigned long fl; };
struct S *func_0023EBD0(void *p);
struct S *func_00223A78(void *p) {
    struct S *ps = func_0023EBD0(p);
    ps->fl |= 0x20;
    return ps;
}
