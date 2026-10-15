// Reference algorithm: src/hand/func_001FB018.c; Sly 3 identity is canonical.
// Sly 3 literal/layout changes are verified against every compiled instruction.
// SLY3_CFLAGS: -Os -G0
int func_001F57E0(void *,int); int func_001F5838(char *p,int event) { switch(event) { case 0:return 0x264; case 8:if(*(int *)(p+0x284))return 0x265; } return func_001F57E0(p,event); }
