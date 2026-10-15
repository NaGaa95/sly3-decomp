// Recovered from the corresponding Sly 2 implementation; verified against Sly 3.
typedef struct { unsigned char c[4]; } RGBA;
typedef struct { int pad[4]; RGBA c; } P;
void func_002BC898(P *p, RGBA *c) { p->c = *c; }
