// Complete retained-object count increment consumes receiver A0 only and updates signed reference word10; this count belongs to a different class from the scene owner-field10.
// Parent-reviewed independent original function boundary; orphan fragments remain excluded.
// SLY3_CFLAGS: -Os -G0
struct Object {char prefix[0x10];int references;};
void func_001C99E0(struct Object *object){++object->references;}
