// Set and register the original second record flag exactly once after the inherited first-flag registration. Both concrete helpers consume only their explicitly supplied pointers.
// Reference compiler shape: src/hand/func_00132238.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0x70];unsigned long flags;};
struct S { char unknown_0[0xDC]; struct Record * record; };
extern char D_00479950[];
void func_0023DCA0(void *receiver);
void func_0011AF60(void *list,void *record);
void func_0023DD40(struct S *p){func_0023DCA0(p);if(p->record&&!(p->record->flags&2)){p->record->flags|=2;func_0011AF60(D_00479950,p->record);}}
