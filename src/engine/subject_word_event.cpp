// SLY3_CFLAGS: -Os -G0 -fno-exceptions
class SubjectEventObject {
    unsigned char prefix[12];
public:
    virtual void Retain();
    virtual void Release();
    virtual void Notify(int event,int schedule,int count,void **arguments,int flags);
};
struct SubjectWordEvent : SubjectEventObject {
    unsigned char before_owner[0x6C-0x10];
    SubjectEventObject *owner;
};
struct SubjectWordEventRecord { unsigned char unused[8]; int word; };
extern char D_0036C700[];
extern "C" {
int func_001880F0(SubjectWordEvent *subject);
int func_00185FD8(SubjectEventObject *owner);
void func_001854C8(void *record,int event,void *subject);
void func_00188868(SubjectWordEvent *subject,int word)
{
    void *arguments[1];
    arguments[0]=&word;
    if(func_001880F0(subject)) {
        ((SubjectWordEventRecord *)D_0036C700)->word=word;
        func_001854C8(D_0036C700,0x2B,subject);
        subject->Notify(0x15,0,1,arguments,0);
    }
    if(subject->owner && func_00185FD8(subject->owner))
        subject->owner->Notify(0x15,0,1,arguments,0);
}
}
