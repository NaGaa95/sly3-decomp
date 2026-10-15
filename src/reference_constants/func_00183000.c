// Complete original Sly3 body; ordinary source/profile reconstruction.
// No incoming arguments. Original memset receives the complete60-byte global buffer, byte zero, and count60; following global words reset to zero.
// SLY3_CFLAGS: -Os -G0
extern char D_0036C698[]; extern int D_0036C694,D_0036C674; void *func_00292034(void *,int,unsigned int); void func_00183000(void) { func_00292034(D_0036C698,0,0x3C); D_0036C694=0; D_0036C674=0; }
