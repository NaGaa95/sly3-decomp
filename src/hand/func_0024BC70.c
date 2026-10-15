// Initialize the original position record, transform it into screen coordinates and store the explicit owner and absent selector.
// Reference algorithm: src/hand/func_00201D78.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct V { float x,y,z; };
struct S {int selection;char prefix[0x10-4];struct V position;char reserved[0xA8-0x1C];void *owner; };
static inline void Init(struct V *v){v->x=0.0f;v->y=0.0f;v->z=0.0f;}
static inline void Screen(struct V *v){float y=v->y;v->x=v->x*320.0f+320.0f;v->y=240.0f;v->z=y;}
void func_0024BC70(struct S *p,void *owner){p->owner=owner;Init(&p->position);Screen(&p->position);p->selection=-1;}
