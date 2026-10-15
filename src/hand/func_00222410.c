// Map the nine supported selection indices to their Sly 3 event identifiers, returning -1 for unsupported indices.
// SLY3_CFLAGS: -Os -G0
int func_00222410(int index) {
 int result=-1;
 static void *const targets[9] __attribute__((aligned(8))) = {&&case0, &&case1, &&case2, &&case3, &&case4, &&case5, &&case6, &&case7, &&case8};
 if ((unsigned)index >= 9) goto done;
 goto *targets[index];
case0: result=0xAA; goto done;
case1: result=0xA3; goto done;
case2: result=0xAB; goto done;
case3: result=0xA4; goto done;
case4: result=0xA5; goto done;
case5: result=0xA6; goto done;
case6: result=0xA7; goto done;
case7: result=0xA8; goto done;
case8: result=0xA9; 
done: return result;
}
