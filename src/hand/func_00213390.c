// Forward original selection to the registration helper, then select active/inactive state from that same explicit sentinel; both actual helper arguments are expressed.
// Reference algorithm: src/hand/func_0021FB18.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_001F4548(void *receiver,int selection);
void func_00213418(void *receiver,int state);
void func_00213390(void *receiver,int selection){func_001F4548(receiver,selection);if(selection!=-1)func_00213418(receiver,1);else func_00213418(receiver,0);}
