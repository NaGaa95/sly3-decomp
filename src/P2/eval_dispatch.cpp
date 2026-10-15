// Evaluate an expression node using its original Sly3 tag dispatch.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct CRef {
    short m_tagk;
    short word2;
    union { int n; float g; void *pv; } u;
    CRef() { m_tagk = -1; }
    CRef(const CRef &r);
    void Decref();
    void InitTag(int tagk);
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &r);
};
struct EvalFrame;
/* The node count at offset2 is live, although CRef value copies ignore it. */
struct NODE { CRef ref; int word8; NODE *pnext; };
typedef char CheckCRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char CheckNode16[(sizeof(NODE) == 16) ? 1 : -1];
extern "C" {
CRef func_001283D0(NODE *node, EvalFrame *frame);
CRef func_00128428(NODE *node, EvalFrame *frame);
CRef func_001284D8(NODE *node, EvalFrame *frame);
CRef func_00128588(NODE *node, EvalFrame *frame);
CRef func_00128610(NODE *node, EvalFrame *frame);
CRef func_001286A0(NODE *node, EvalFrame *frame);
CRef func_00128788(NODE *node, EvalFrame *frame);
CRef func_00128860(NODE *node, EvalFrame *frame);
CRef func_00128948(NODE *node, EvalFrame *frame);
CRef func_00128AD0(NODE *node, EvalFrame *frame);
CRef func_00128CE8(NODE *node, EvalFrame *frame);
CRef func_00128EA0(NODE *node, EvalFrame *frame);
CRef func_00128F90(NODE *node, EvalFrame *frame);
CRef func_00129148(NODE *node, EvalFrame *frame);
CRef func_00129208(NODE *node, EvalFrame *frame);
CRef func_001296F0(NODE *node, EvalFrame *frame);
}

CRef func_001296F0(NODE *node, EvalFrame *frame)
{
    switch (node->ref.m_tagk) {
    default:
        return node->ref;
    case 0x16:
        return func_001283D0(node, frame);
    case 0x1D: {
        NODE *operation = static_cast<NODE *>(node->ref.u.pv);
        switch (operation->ref.m_tagk) {
        case 1: return func_00128428(node, frame);
        case 2: return func_001284D8(node, frame);
        case 4: return func_00128588(node, frame);
        case 5: return func_00128610(node, frame);
        case 6: return func_001286A0(node, frame);
        case 7: return func_00128788(node, frame);
        case 8: return func_00128860(node, frame);
        case 9: return func_00128948(node, frame);
        case 11: return func_00128AD0(node, frame);
        case 12: return func_00128CE8(node, frame);
        case 13: return func_00128EA0(node, frame);
        case 15: return func_00129148(node, frame);
        case 14: return func_00128F90(node, frame);
        case 16: return operation->pnext->ref;
        }
        return func_00129208(node, frame);
    }
    }
}
