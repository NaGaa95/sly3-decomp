// Original USA entry 0x13f8d0; ordinary C reconstruction.
// Only receiver A0 is consumed.277610(receiver19A4) reads only its state13C. On true, that object.owner14C becomes receiver, then1AF2A8 receives explicit receiver/node1824/object19A4 and retains all three.1FC090 receives node1824.owner4/object19A4 and forwards both into1FBFF0. Final receiver1824 and19A4 stores are zero; no inherited FPR is read.
// SLY3_CFLAGS: -Os -G0 -fno-schedule-insns
int func_00277610(void *);
void func_001AF2A8(void *,void *,void *);
void func_001FC090(void *,void *);
void func_0013F8D0(char *p)  {
    if(func_00277610(*(void **)(p+0x19A4))) {
        *(void **)(*(char **)(p+0x19A4)+0x14C)=p;
        func_001AF2A8(p,*(void **)(p+0x1824),*(void **)(p+0x19A4));
    }
    func_001FC090(*(void **)(*(char **)(p+0x1824)+4),*(void **)(p+0x19A4));
    *(void **)(p+0x1824)=0;
    *(void **)(p+0x19A4)=0;
}
