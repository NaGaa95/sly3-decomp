// SLY3_CFLAGS: -Os -G0
// Accessors for the packed byte/mode fields of the 64-bit word at +0x120 (layout as in src/leaf/link_release_240f30.cpp).
union ModeState {
    unsigned long value;
    struct {
        unsigned long low:32;
        unsigned char byte124:8;
        unsigned char byte125:8;
        unsigned long unknown126:8;
        unsigned int mode:2;
        unsigned long rest:6;
    } __attribute__((packed)) fields;
} __attribute__((packed,aligned(8)));
struct ModeObject { char prefix[0x120]; union ModeState state; };
int func_00241230(struct ModeObject *p) { return p->state.fields.mode; }
void func_00241248(struct ModeObject *p, int v) { p->state.fields.byte124 = v; }
int func_00241250(struct ModeObject *p) { return p->state.fields.byte124; }
void func_00241258(struct ModeObject *p, int v) { p->state.fields.byte125 = v; }
int func_00241260(struct ModeObject *p) { return p->state.fields.byte125; }
