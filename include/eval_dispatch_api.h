/* Measured original evaluation ABI: all refs occupy8 bytes. */
#ifndef SLY3_EVAL_DISPATCH_API_H
#define SLY3_EVAL_DISPATCH_API_H
typedef struct EvalFrame EvalFrame;
typedef struct ScriptNode ScriptNode;
typedef struct CRef {
    short tag;
    short word2;
    union { int integer; float real; void *pointer; } payload;
} CRef;
/* Node offset2 is a live reference count; value-copy helpers ignore this word. */
struct ScriptNode { CRef ref; int word8; ScriptNode *next; };
typedef char CheckCRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char CheckScriptNode16[(sizeof(ScriptNode) == 16) ? 1 : -1];
CRef *func_001296F0(CRef *destination, ScriptNode *node, EvalFrame *frame);
CRef *func_00129B58(EvalFrame *frame, int key, int searchParents);
int func_00129B18(EvalFrame *frame, int key, int searchParents, CRef *output);
CRef *func_0012B3B0(CRef *destination, const CRef *source);
CRef *func_0012AF00(CRef *destination, const CRef *source);
void func_0012BC20(CRef *reference);
void func_0012BDD8(CRef *reference, int tag);
#endif
