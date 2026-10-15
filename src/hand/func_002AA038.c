// Complete nested getter explicitly consumes receiverA0 and returns the actual word0 from the stored40 record. Nominal scalar signedness remains provisional; original complete32-bit load/return is exact under the supported O2 profile.
// Parent-reviewed independent original function boundary; orphan fragments remain excluded.
// SLY3_CFLAGS: -O2 -G0
struct R {int value;};
struct O {char prefix[0x40];struct R *record;};
int func_002AA038(struct O *object){return object->record->value;}
