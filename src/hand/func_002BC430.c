// EE hardware intrinsics preserve VU/FPU/COP0 operations; C expresses control flow.
typedef int qword __attribute__((mode(TI)));
float func_002BC430(qword *p) { float f; qword t; __asm__("prot3w %0, %1" : "=&r"(t) : "r"(*p)); __asm__("mtc1 %1, %0" : "=f"(f) : "r"(t)); return f; }
