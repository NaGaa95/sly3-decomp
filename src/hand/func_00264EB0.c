// Sum the actual per-character widths from the sixteen-bit text iterator.
// Nullable text reset and each character input are explicit.
// Actual nullable sixteen-bit text pointer and sixteen-bit cursor semantics.
// SLY3_CFLAGS: -Os -G0
void func_00264B18(void *receiver,const unsigned short *text);unsigned short func_00264BB0(void *receiver);float func_00264E78(void *receiver,unsigned short character);
float func_00264EB0(void *p){float sum=0.0f;unsigned short character;func_00264B18(p,0);while((character=func_00264BB0(p))!=0)sum+=func_00264E78(p,character);return sum;}
