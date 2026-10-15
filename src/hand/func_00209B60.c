// Clear the complete original sixteen-byte global allocation, advance its cursor and return the original pointer; no incoming register is consumed.
// Reference algorithm: src/hand/func_00210B28.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Slot {char bytes[16];};
extern struct Slot *D_00468D00;
void *func_00292034(void *destination,int value,unsigned int bytes);
void *func_00209B60(void){void *result;func_00292034(D_00468D00,0,16);result=D_00468D00++;return result;}
