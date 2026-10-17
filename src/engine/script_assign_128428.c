// SLY3_CFLAGS: -Os -G0
typedef struct EvalFrame EvalFrame;
typedef struct ScriptNode ScriptNode;
typedef struct CRef {
    short tag;
    short word2;
    union { int integer; float real; void *pointer; } payload;
} CRef;
struct ScriptNode { CRef ref; int word8; ScriptNode *next; };
CRef *func_001296F0(CRef *destination,ScriptNode *node,EvalFrame *frame);
CRef *func_00129A90(CRef *result,EvalFrame *frame,int key,CRef *value);
CRef *func_0012B3B0(CRef *destination,const CRef *source);
CRef *func_0012AF00(CRef *destination,const CRef *source);
void func_0012BC20(CRef *reference);
CRef *func_00128428(CRef *result,CRef *arguments,EvalFrame *frame)
{
    CRef reference;
    CRef scratch;
    ScriptNode *node;
    reference.tag=-1;
    node=((ScriptNode *)arguments[0].payload.pointer)->next;
    func_001296F0(&scratch,node->next,frame);
    func_0012B3B0(&reference,&scratch);
    func_0012BC20(&scratch);
    func_00129A90(&scratch,frame,node->ref.payload.integer,&reference);
    func_0012B3B0(&reference,&scratch);
    func_0012BC20(&scratch);
    func_0012AF00(result,&reference);
    func_0012BC20(&reference);
    return result;
}
