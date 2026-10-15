// Convert the full incoming packed point through the stored destination object, store it at80, set scale and update the receiver.28E910 consumes source A0,destination A1,packed point A2;2BA818 consumes output A0 and all128 bits A1;290078 only receiver.
// Reference algorithm: src/hand/func_0013C278.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
union Vector {QWORD bits;float words[4];};
struct Frame{char prefix[0x30];union Vector point;};
struct S{char prefix[0x40];void *destination;};
QWORD func_0028E910(void *source,void *destination,QWORD point);
QWORD *func_002BA818(QWORD *output,QWORD value);
void func_00290078(void *receiver);
void func_0028FF10(struct S *p,QWORD point){struct Frame *frame=(struct Frame *)((char *)p+0x50);QWORD value=func_0028E910(0,p->destination,point);func_002BA818(&frame->point.bits,value);frame->point.words[3]=1.0f;func_00290078(p);}
