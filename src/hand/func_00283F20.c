// Initialize the original receiver from its nested scalar record and enter state1. Complete284DC8 consumes receiver A0/state A1 only; the caller -1 word also occupies A2 physically but is a stored field value, not an extra consumed callee formal.
// Reference compiler shape: src/hand/func_001FB658.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
struct Record {char prefix[0x78];float first,second,third;int unknown;int value;};
struct S { char unknown_0[0x14]; struct Record * record; char unknown_18[0x4]; float first; int state; float second; float third; int value; int selection; };
void func_00284DC8(void *receiver,int state);
void func_00283F20(struct S *p){struct Record *record=p->record;p->first=record->first;p->state=0;p->second=record->second;p->third=record->third;p->value=record->value;p->selection=-1;func_00284DC8(p,1);}
