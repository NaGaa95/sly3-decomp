// Resolve the six original scene fields and explicitly set the packed value and both enabled states.
// Complete original input, boundary, relocation and whole initialized-section evidence are independently reviewed.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
extern const char D_003496B8[];
extern const QWORD D_00317560;
void func_0023C580(void *receiver);
void func_001C8970(void *receiver, int count, const void *fields, void *context);
void func_0023ED58(void *receiver, QWORD value);
void func_0023EBF8(void *receiver, int enabled);
void func_0023EC98(void *receiver, int enabled);
void func_00232360(void *p) {
    func_0023C580(p);
    func_001C8970(p, 6, D_003496B8, 0);
    func_0023ED58(p, D_00317560);
    func_0023EBF8(p, 1);
    func_0023EC98(p, 1);
}
