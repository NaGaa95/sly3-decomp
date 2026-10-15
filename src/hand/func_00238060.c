// Propagate each original12-byte entry reference into its object then reset the range end to its beginning. Complete2371C8 consumes object A0/reference A1 and internally supplies its byte-copy/cleanup inputs.
// Reference compiler shape: src/hand/func_00148740.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Ref {int kind,value;};
struct Entry {void *object;struct Ref reference;};
struct S { char unknown_0[0x50]; struct Entry * begin; struct Entry * end; };
void func_002371C8(void *object,const struct Ref *reference);
void func_00238060(struct S *p){struct Entry *entry;for(entry=p->begin;entry<p->end;entry++)func_002371C8(entry->object,&entry->reference);p->end=p->begin;}
