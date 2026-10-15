// Preserve the original selection result, upgrading -1 to1 only in state1.
// Original68-byte body and four-byte zero alignment independently reviewed.
// SLY3_CFLAGS: -Os -G0
struct S {char prefix[0x1470];int state;};
int func_001530F8(void *receiver);
int func_0022D028(struct S *p){int result=func_001530F8(p);if(result!=-1)return result;if(p->state==1)return 1;return result;}
