// Complete nested getter consumes only explicit receiverA0 and returns its nested20 record pointer134.
// Parent-reviewed independent original function boundary; orphan fragments remain excluded.
// SLY3_CFLAGS: -Os -G0
struct R { char prefix[0x134]; void *record; };
struct O { char prefix[0x20];struct R *record; };
void *func_002B58D8(struct O *object){return object->record->record;}
