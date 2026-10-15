// Reference algorithm: src/hand/func_001B0808.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
void func_001D2ED0(void *,int); void func_001D3AE8(char *p) { if(*(int *)(p+0x1FC)==7) { if(*(int *)(p+0x38)>=2)*(int *)(p+0x38)=1; func_001D2ED0(p,8); } }
