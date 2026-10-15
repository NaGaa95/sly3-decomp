// Original USA entry 0x1716f8; ordinary C reconstruction.
// Receiver A0 and its word-sized value A1 are explicit; field1A0 is assigned and 171538(receiver,state2) consumes the explicit receiver/state pair. The adjacent original bounded setter is preserved separately.
// SLY3_CFLAGS: -Os -G0
void func_00171538(void *,int);
void func_001716F8(char *p,void *value)  {
    *(void **)(p+0x1A0)=value;
    func_00171538(p,2);
}
