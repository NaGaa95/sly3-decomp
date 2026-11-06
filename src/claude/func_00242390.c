// SLY3_CFLAGS: -Os -G0
// Millisecond fields of the runtime at +0x24 exposed as seconds; setters re-bind via func_0028F260.
struct Runtime { char prefix[0xAC]; unsigned short msA; unsigned short msB; };
struct Binding { char prefix[0x20]; void *owner; struct Runtime *runtime; };
void func_0028F260(void *, struct Runtime *);
float func_00242390(struct Binding *b) { return b->runtime->msA * 0.001f; }
void func_002423B8(struct Binding *b, float t) { b->runtime->msA = t * 1000.0f; func_0028F260(b->owner, b->runtime); }
float func_002423F8(struct Binding *b) { return b->runtime->msB * 0.001f; }
void func_00242420(struct Binding *b, float t) { b->runtime->msB = t * 1000.0f; func_0028F260(b->owner, b->runtime); }
float func_00242460(struct Binding *b) { return b->runtime->msA * 0.001f; }
void func_00242488(struct Binding *b, float t) { b->runtime->msA = t * 1000.0f; func_0028F260(b->owner, b->runtime); }
