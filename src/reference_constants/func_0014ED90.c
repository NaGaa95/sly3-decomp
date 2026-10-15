// Original USA entry 0x14ed90; ordinary C reconstruction.
// Receiver A0 and signed32-bit selection A1 are retained. Optional receiver1A4 calls14DC98(child,0), whose full body only retains its two GP inputs and defines its own floating values.1857E8(global36C700,receiver,selection) uses exactly those three words; its25E150 helper reads only global47989C. Selection!=-1 then calls14E9F0(receiver,0); no extra incoming value is needed.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C700[];
void func_0014DC98(void *,int);
void func_001857E8(void *,void *,int);
void func_0014E9F0(void *,int);
void func_0014ED90(char *p,int value)  {
    if(*(void **)(p+0x1A4))func_0014DC98(*(void **)(p+0x1A4),0);
    func_001857E8(D_0036C700,p,value);
    if(value!=-1)func_0014E9F0(p,0);
}
