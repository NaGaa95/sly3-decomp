// Reset the inherited receiver and initialize its original unit vector and float scale.
// Reference algorithm: src/hand/func_001C2D70.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V { float x,y,z; };
struct S { char prefix[0x150];struct V value;char reserved[8];float scale; };
void func_0023AE08(struct S *p);
static inline void Init(struct V *v){v->x=1.0f;v->y=0.0f;v->z=0.0f;}
void func_0026E0D0(struct S *p){func_0023AE08(p);Init(&p->value);p->scale=100.0f;}
