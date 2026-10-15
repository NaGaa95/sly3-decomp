// Use both explicit original mask bit selectors, look up kindD9 from the embedded object list and set its original state. Mask bit A1 propagates through2533C0/253190 into252AD0;16D840 consumes receiver/state only and generates its own float/message inputs.
// Reference compiler shape: src/hand/func_00181728.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
int func_002533C0(void *receiver,int bit);
void *func_002387A8(void *list,int kind);
void func_0016D840(void *receiver,int state);
void func_00255A40(void *receiver){if(func_002533C0(receiver,0x29)||func_002533C0(receiver,38))func_0016D840(func_002387A8((char *)receiver+0x29C,0xD9),3);}
