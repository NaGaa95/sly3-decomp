// SLY3_CFLAGS: -O2 -G0
// Qword lane helper (style of Sly 2 src/hand/func_00259D98.c): low lane of *p as float.
typedef int qword __attribute__((mode(TI)));
float func_002BC420(qword *p) { float f; __asm__("mtc1 %1, %0" : "=f"(f) : "r"(*p)); return f; }
