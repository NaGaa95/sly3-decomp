// Original USA entry 0x1f5b28; ordinary C reconstruction.
// Complete original entry, actual call inputs and return/data flow reviewed independently.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[];
void func_00238978(void *);
void func_001854C8(void *,int,void *);
void func_00170360(void *);
void func_001F5C58(void *);
void func_001F6148(void *,int,void *);
void func_001F5B28(char *p)  {
    func_00238978(p);
    func_001854C8(D_0036C700,0x1A,*(void **)(p+0x10));
    func_00170360(*(void **)(*(char **)(p+0x10)+0x10D0));
    func_001F5C58(p);
    func_001F6148(p,0,0);
}
