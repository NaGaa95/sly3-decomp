// Choose the original state from the explicit selection sentinel, then forward that same receiver/selection pair to its registration helper.
// Reference algorithm: src/hand/func_0013C278.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
void func_0020F868(void *receiver,int state);
void func_001F4548(void *receiver,int selection);
void func_0020F738(void *receiver,int selection){if(selection==-1)func_0020F868(receiver,1);else func_0020F868(receiver,2);func_001F4548(receiver,selection);}
