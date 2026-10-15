// Return the identifier resource or the original primary global resource for special identifier32.226770 consumes both receiver/id;1F4AD0 consumes selection A1 while supplied context A0 is caller-derived unused.
// Reference algorithm: src/hand/func_0017DCF8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern char D_00475480[];
void *func_00226770(void *receiver,int id);
void *func_001F4AD0(void *context,int selection);
void *func_002267E8(void *receiver,int id){if(id==0x20)return func_001F4AD0(D_00475480,0);return func_00226770(receiver,id);}
