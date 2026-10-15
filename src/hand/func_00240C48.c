// Return the original owner query for the stored record value, or zero when the record is absent.
// Reference algorithm: src/hand/func_0012F8C0.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0x10]; int value; };
struct S { char unknown_0[0x14]; void * owner; struct R * record; };
int func_00241EA8(void *owner,int value);
int func_00240C48(struct S *object){if(object->record)return func_00241EA8(object->owner,object->record->value);return 0;}
