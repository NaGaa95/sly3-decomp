// Complete original function, inputs and emitted data independently reviewed.
// SLY3_CC: tools/third_party/ee-gcc2.95.3-136
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct EvalFrame {
    char prefix[8];
    EvalFrame *parent;
    void *bindings;
    int searching;
    int scopeFlag;
};
class CRef {
    public: short tag,word2;
    union {
        int integer;
        float real;
        void *pointer;
    }
    payload;
    CRef(int value) {
        tag=0x17;
        payload.integer=value;
    }
    CRef(const CRef &other);
    ~CRef();
};
typedef char CheckCRef8[(sizeof(CRef) == 8) ? 1 : -1];
extern "C" CRef *func_00129B58(EvalFrame *, int, int);
extern "C" CRef func_00127458(int unused_argument_count,CRef *arguments,EvalFrame *frame) {
    CRef *value;
    for (;;) {
        if (!frame || !frame->parent) goto missing;
        if (frame->scopeFlag) break;
        frame=frame->parent;
    }
    value=func_00129B58(frame->parent,arguments->payload.integer,1);
    if (value) return *value;
    missing: return CRef(0x8E);
}
