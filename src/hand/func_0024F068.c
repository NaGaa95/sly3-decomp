// Apply the explicit inherited identifier update and clear the matching stored record pointer.
// Reference algorithm: src/hand/func_001F82B8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0x48]; int id; };
struct S { char unknown_0[0x218]; struct R * record; };
void func_0023EDC8(void);
void func_0024F068(struct S *p,int id){func_0023EDC8();if(p->record && p->record->id==id)p->record=0;}
