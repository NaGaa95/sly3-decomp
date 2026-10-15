// Attach the original primary global resource when it is present.
// Reference algorithm: src/hand/func_001492B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void *func_001F4AD0(void *global,int selection);
void func_0027FA70(void *p,void *resource);
void func_0027FA30(void *p){void *resource=func_001F4AD0(D_00475480,0);if(resource)func_0027FA70(p,resource);}
