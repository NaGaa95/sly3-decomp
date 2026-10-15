// Reset the explicit receiver, obtain the original two-entry record and initialize its state and full128-bit default position.
// Reference algorithm: src/hand/func_001D4EC8.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Record {char prefix[0x10];int state;char unknown[12];QWORD position;};
extern QWORD D_00317530;
void func_00289678(void *receiver);
struct Record *func_0028A480(void *receiver,int selection,int count);
void func_0028A788(void *receiver){struct Record *record;func_00289678(receiver);record=func_0028A480(receiver,0,2);record->position=D_00317530;record->state=0;}
