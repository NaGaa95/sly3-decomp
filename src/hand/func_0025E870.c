// Find the first original key entry with a nonnull value, otherwise return the concrete original default object address. Both receiver/key inputs and eight-byte entry layout are explicit; nominal value class remains provisional.
// Reference compiler shape: src/hand/func_0013C490.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Entry {int key;void *value;};
struct S {int count;struct Entry *entries;};
extern char D_004BB210[];
void *func_0025E870(struct S *p,int key){int i;for(i=0;i<p->count;i++){struct Entry *entry=p->entries+i;if(key==entry->key&&entry->value)return entry->value;}return D_004BB210;}
