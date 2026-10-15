// Clear both original globals and the complete64-byte block with all three explicit memset inputs; no incoming argument is consumed.
// Reference algorithm: src/hand/func_0014C6A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
extern int D_0046FF40,D_00474F50;
extern char D_00474F58[];
void *func_00292034(void *destination,int value,unsigned int length);
void func_00235E28(void){D_0046FF40=0;D_00474F50=0;func_00292034(D_00474F58,0,0x40);}
