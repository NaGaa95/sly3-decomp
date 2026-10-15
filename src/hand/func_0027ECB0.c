// Initialize the original key/color/state record, then replace key and four-byte color except for sentinel kind37. Complete27EB50 consumes output/kind and writes exactly four individual color bytes; the alignment-one byte struct models its genuine unaligned word transfers.
// Reference compiler shape: src/hand/func_001406E8.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Color {unsigned char bytes[4];};
struct S {int key;struct Color color;int state;};
void func_0027ED18(void *receiver);
struct Color *func_0027EB50(struct Color *result,int kind);
void func_0027ECB0(struct S *p,int key,int kind){func_0027ED18(p);if(kind!=0x37){struct Color color;p->key=key;func_0027EB50(&color,kind);p->color=color;}}
