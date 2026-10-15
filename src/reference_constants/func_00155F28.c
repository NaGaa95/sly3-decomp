// Original USA entry 0x155f28; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[];
void func_00155F80(void *,int,void *);
void func_001854C8(void *,int,void *);
void func_0014DC98(void *,void *);
void func_00155F28(char *p)  {
    if(*(void **)(p+0x127C))  {
        func_00155F80(p,1,0);
        func_001854C8(D_0036C700,0x46,*(void **)(p+0x127C));
        func_0014DC98(*(void **)(p+0x127C),0);
    }
}
