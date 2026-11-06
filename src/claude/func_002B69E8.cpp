// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
typedef int qword __attribute__((mode(TI)));
inline void *operator new(unsigned int, void *p) { return p; }
struct V { qword q; V() {} };
struct ARR { V a[32]; ARR() {} };
struct S { char base[0xC]; void *vt; ARR arr; };
extern "C" {
extern char D_00353318[];
S *func_002B5328(S *);
}
extern "C" S *func_002B69E8(S *s)
{
    func_002B5328(s);
    s->vt = D_00353318;
    new (&s->arr) ARR;
    return s;
}
