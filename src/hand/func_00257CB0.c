// Return the current original indexed item and advance the signed cursor cyclically, returning null for an empty collection. Nominal item pointer class is provisional; actual word bits and both count/cursor fields are explicit.
// Reference compiler shape: src/hand/func_0020FA10.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct S {char prefix[0x18];int count;void *items[32];int cursor;};
void *func_00257CB0(struct S *p){void *item;if(!p->count)return 0;item=p->items[p->cursor++];if(p->cursor>=p->count)p->cursor=0;return item;}
