// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
/* Splice "sort": copy list nodes into a slot array, qsort them with a script comparator, rebuild a list. */
inline void *operator new(unsigned int, void *p) { return p; }
struct EvalFrame;
struct Node;
struct CRef {
    short tag;
    short word2;
    union { int integer; float real; void *pointer; } payload;
    CRef() { InitTag(0); }
    CRef(const CRef &) __asm__("func_0012AF00");
    CRef(Node *);
    CRef &operator=(const CRef &);
    void InitTag(int);
};
struct ScriptNode { CRef ref; int word8; ScriptNode *next; };
struct CTX { int a[4]; CTX(); ~CTX(); };
struct ALLOCREQ { int cb; int cbAlign; };
void *PvAllocSlot(ALLOCREQ *);
struct CompareContext { ScriptNode *expression; EvalFrame *frame; CRef *left; CRef *right; };
extern "C" {
extern CompareContext D_0036B128;
int func_00123868(ScriptNode *const *, ScriptNode *const *);
void func_00292540(void *, int, int, int (*)(ScriptNode *const *, ScriptNode *const *));
ScriptNode *func_002BA6B8();
void func_002BA780(ScriptNode **, ScriptNode *);
void func_002BA840(ScriptNode *, int);
}
struct TreeResult {
    ScriptNode *p;
    TreeResult(const TreeResult &);
    ~TreeResult() {
        ScriptNode *node = p;
        if (node && --node->ref.word2 == 0) func_002BA840(node, 3);
    }
};
extern "C" TreeResult func_001236B0(CRef **, CRef **, CRef **);

inline ALLOCREQ *SortRequest(ALLOCREQ *request, int bytes, int alignment)
{
    request->cb = bytes;
    request->cbAlign = alignment;
    return request;
}

extern "C" CRef func_001238F0(int carg, CRef *aref, EvalFrame *pframe)
{
    if (aref[1].tag == 0) {
        return aref[1];
    }
    ScriptNode *pn = (ScriptNode *)aref[1].payload.pointer;
    int c = 0;
    if (!pn) {
        return CRef();
    }
    for (ScriptNode *p = pn; p; p = p->next)
        c++;
    CTX ctx;
    ScriptNode **apn;
    {
        ALLOCREQ req;
        apn = (ScriptNode **)PvAllocSlot(SortRequest(&req, c * 4, 0x10));
    }
    ScriptNode **pp = apn;
    for (ScriptNode *p = pn; p; p = p->next)
        *pp++ = p;
    CRef *prefFirst;
    TreeResult tr = func_001236B0(&prefFirst, &D_0036B128.left, &D_0036B128.right);
    *prefFirst = *aref;
    D_0036B128.frame = pframe;
    D_0036B128.expression = tr.p;
    func_00292540(apn, c, 4, func_00123868);
    ScriptNode *pnHead = func_002BA6B8();
    pnHead->ref = apn[0]->ref;
    ScriptNode *pnTail = pnHead;
    for (int i = 1; i < c; i++) {
        ScriptNode *p = func_002BA6B8();
        func_002BA780(&pnTail->next, p);
        p->ref = apn[i]->ref;
        pnTail = p;
    }
    return CRef((Node *)pnHead);
}
