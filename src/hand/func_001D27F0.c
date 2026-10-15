// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
struct MSG { int cb; int nKind; };
void *func_001D2538(struct MSG *p);
void *func_001D27F0(int cb) { struct MSG m; m.cb = cb; m.nKind = 0x10; return func_001D2538(&m); }
