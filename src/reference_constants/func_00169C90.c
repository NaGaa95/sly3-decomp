// Reference algorithm: src/hand/func_0020C058.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
extern char D_00355D90[]; struct Object { void *owner; int mode; int unused8; char pad[0x1C-0xC]; void *vtable; }; struct Object *func_00169C90(struct Object *p,void *owner,int mode) { p->vtable = D_00355D90; p->owner = owner; p->mode = mode; p->unused8 = 0; return p; }
