// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
struct Frame;
struct Basic;
struct Node;
struct ObjectContext { char prefix[0x38]; void *scope; };
struct Game { char prefix[0x4634]; void *default_scope; };
class CRef {
public:
    short tag;
    unsigned short opaque_word2;
    union {
        int word;
        float real;
        void *pointer;
        ObjectContext *object;
        Node *node;
    } payload;
    CRef() { tag = -1; }
    CRef(const CRef &);
    void Decref();
    ~CRef() { Decref(); }
    CRef &operator=(const CRef &);
};
struct Node { CRef value; unsigned int tracking_word; Node *next; };
typedef char CRef8[(sizeof(CRef) == 8) ? 1 : -1];
typedef char Node16[(sizeof(Node) == 16) ? 1 : -1];
typedef char BasicPointer4[(sizeof(Basic *) == 4) ? 1 : -1];
extern Game D_00475480;
extern "C" {
    int func_0017E208(Game *, int flags, int key, ObjectContext *owner,
                     int capacity, Basic **objects);
    CRef func_00126060(int count, Basic **objects);
    CRef func_00126760(int count, CRef *arguments, Frame *frame);
}
CRef func_00126760(int count, CRef *arguments, Frame *frame)
{
    CRef result;
    Basic *objects[0x180];
    ObjectContext *owner = arguments[1].payload.object;
    int found = func_0017E208(&D_00475480, owner ? 0x401 : 0x405,
                            arguments[0].payload.word, owner, 0x180, objects);
    result = func_00126060(found, objects);
    return result;
}
