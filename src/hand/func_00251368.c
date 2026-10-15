// Check the original one-entry property table against the explicit receiver and return its Boolean result;13B500 consumes both actual inputs.
// Reference algorithm: src/hand/func_00206D48.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern int D_003498F8[];
int func_0013B500(void *object,int property);
int func_00251368(void *object){unsigned int i;for(i=0;i<1;i++)if(func_0013B500(object,D_003498F8[i]))return 1;return 0;}
