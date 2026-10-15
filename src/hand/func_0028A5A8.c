// Return the selected original128-byte record when active and optionally refresh its sequence with the receiver counter. Complete28A470 consumes receiver only and returns actual incremented integer4C; both outer inputs are explicit.
// Reference compiler shape: src/hand/func_00147220.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0xC];int sequence;char remainder[0x80-0x10];};
struct S {char prefix[0x44];int active;char unknown[0x60-0x48];struct Record records[8];int selected;};
int func_0028A470(void *receiver);
struct Record *func_0028A5A8(struct S *p,int update){struct Record *record;if(!p->active)return 0;record=&p->records[p->selected];if(update==1)record->sequence=func_0028A470(p);return record;}
