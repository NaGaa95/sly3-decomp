// Update the enabled receiver with the actual incoming matrix A1 and float delta F12, default color and selector. Complete267608 consumes unchanged F12 on its reset path, so that sixth input is explicit; only the initialized four bytes of each aligned scalar local are read.
// Reference algorithm: src/hand/func_001F4440.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
union Color {QWORD storage;unsigned int word;};
union Mask {QWORD storage;unsigned int word;};
struct S { char unknown_0[0x28]; int enabled; };
void func_00267608(void *receiver,int index,void *matrix,unsigned int *color,unsigned int *selector,float delta);
void func_002675C0(struct S *p,void *matrix,float delta){if(p->enabled){union Color color;union Mask selector;color.word=0x7F7F7F7F;selector.word=0xFFFFFFFF;func_00267608(p,0,matrix,&color.word,&selector.word,delta);}}
