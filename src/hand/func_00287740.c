// Publish the original object notification and select the absent state.1854C8 uses integer code A1 and object A2, while its supplied context A0 is caller-derived unused by its first1855F0 call; preserve that historical formal explicitly.
// Reference algorithm: src/hand/func_001492B0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[];
void func_001854C8(void *context,int code,void *object);
void func_00286360(void *object,int state);
void func_00287740(void *object){func_001854C8(D_0036C700,0x60,object);func_00286360(object,-1);}
