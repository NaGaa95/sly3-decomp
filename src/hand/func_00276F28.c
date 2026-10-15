// Forward the real nullable owner pointer and copy four packed basis rows from the valid first record.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Record {QWORD basis[4];char gap[0x54];int flags;};struct S {char prefix[0x40];int count;struct Record *record;char gap[0x148];QWORD basis[4];};
void func_001FC968(void *receiver,void *owner);
void func_00276F28(struct S *p,void *owner){func_001FC968(p,owner);if(p->count>0){struct Record *record=p->record;if(record->flags==0){p->basis[0]=record->basis[0];p->basis[1]=record->basis[1];p->basis[2]=record->basis[2];p->basis[3]=record->basis[3];}}}
