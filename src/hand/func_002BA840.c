// Release the original embedded reference, unlink and destroy the base receiver, and return it to its actual pool for deletion flag1. Every reference/base/pool argument is explicit.
// Reference compiler shape: src/hand/func_0017F8C8.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
extern char D_004D2AD8[];
void func_002BA8F8(void *reference,int flags);
void func_002B3B90(void *receiver);
void func_002BA8A8(void *receiver,int flags);
void func_0011E1F0(void *pool,void *allocation);
void func_002BA840(void *receiver,int flags){func_002BA8F8((char *)receiver+0xC,2);func_002B3B90(receiver);func_002BA8A8(receiver,0);if(flags&1)func_0011E1F0(D_004D2AD8,receiver);}
