// Apply the original owner notification when the referenced record value changes.
// Reference algorithm: src/hand/func_0014C6A0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0xA4]; int value; };
struct S { struct R * record; void * owner; char unknown_8[0xB4]; int value; };
void func_0023DD40(void *owner);
void func_0023C840(struct S *p){int value=p->record->value;if(p->value!=value){p->value=value;func_0023DD40(p->owner);}}
