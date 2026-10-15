// Apply the inherited explicit stream update, resolve the original43 descriptor fields and initialize the missing stored destination.
// Reference algorithm: src/hand/func_001C2D20.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00349460[];
struct S { char unknown_0[0x1134]; void * source; char unknown_1138[0x4B4]; void * destination; };
void func_00152448(struct S *p,void *stream);
void func_001C8970(struct S *p,int fieldCount,void *fields,void *context);
void func_0022C260(struct S *p,void *stream){func_00152448(p,stream);func_001C8970(p,43,D_00349460,0);if(!p->destination)p->destination=p->source;}
