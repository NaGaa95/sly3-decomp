// Copy the complete original16-byte vector record from actual pointer A1 and advance receiver progress by1 only below one-half. All vector bits and ordered float semantics are preserved.
// Reference compiler shape: src/hand/func_001840B8.c.
// Original Sly 3 control flow, record layouts and input APIs recovered independently.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
union Vector {QWORD bits;float values[4];};
struct S {char prefix[0x19C];float progress;union Vector value;};
void func_0026D1E8(struct S *p,const union Vector *value){float progress=p->progress;union Vector copy=*value;p->value=copy;if(progress<0.5f)p->progress=progress+1.0f;}
