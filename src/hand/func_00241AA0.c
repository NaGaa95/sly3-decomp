// Reconstructed from matching Sly 2 code with Sly 3 calls and data addresses.
struct T { int a[3]; int n; char pad[0x10]; struct T *pnext; };
extern struct T *D_00479B74;
struct T *func_00241AA0(int n) { struct T *pt; for (pt = D_00479B74; pt; pt = pt->pnext) if (pt->n == n) return pt; return 0; }
