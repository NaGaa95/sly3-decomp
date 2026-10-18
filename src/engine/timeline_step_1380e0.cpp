// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct TimelineEvent { float time; int kind; unsigned int payload[3]; };
struct TimelineSequence { unsigned char prefix[0x90]; int eventCount; TimelineEvent *events; };
class TimelineBase {
public:
    int first,second,third;
    virtual void Begin();
    virtual void End();
};
struct TimelineRuntime : TimelineBase {
    int context;
    TimelineSequence *sequence;
    int flags;
    float time,target;
    unsigned char gap24[0x40-0x24]; float rate;
    unsigned char gap44[0x50-0x44]; int cursor;
};
class TimelineGuard {
public:
    TimelineRuntime *object;
    TimelineGuard(TimelineRuntime *runtime):object(runtime) { object->Begin(); }
    ~TimelineGuard() { object->End(); }
};
extern "C" {
void func_00138270(TimelineRuntime *self,TimelineEvent *event);
int func_00138AC8(TimelineRuntime *self);
}
extern "C" void func_001380E0(TimelineRuntime *self)
{
    if(self->sequence->eventCount) {
        TimelineGuard guard(self);
        self->target=self->time;
        while(!func_00138AC8(self)) {
            TimelineSequence *sequence=self->sequence;
            int index=self->cursor;
            TimelineEvent *event;
            if(index<sequence->eventCount && sequence->events[index].time<=self->target &&
               (event=&sequence->events[index],1) && 0.0f<=self->rate) {
                self->cursor=index+1;
            } else if(self->cursor>0 && self->target<=self->sequence->events[self->cursor-1].time && self->rate<0.0f) {
                self->cursor=self->cursor-1;
                event=&self->sequence->events[self->cursor];
            } else {
                self->time=self->target;
                break;
            }
            switch(event->kind) {
            case 7: case 8: case 11: case 13: case 14: case 15: case 16:
            case 21: case 22: case 23: case 24: case 25: case 26:
                func_00138270(self,event);
                break;
            }
        }
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char EventSize[(sizeof(TimelineEvent)==20)?1:-1];
typedef char RealGuardSize[(sizeof(TimelineGuard)==4)?1:-1];
typedef char SequenceCountOffset[(MEMBER_OFFSET(TimelineSequence,eventCount)==0x90)?1:-1];
typedef char SequenceEventsOffset[(MEMBER_OFFSET(TimelineSequence,events)==0x94)?1:-1];
typedef char RuntimeSequenceOffset[(MEMBER_OFFSET(TimelineRuntime,sequence)==0x14)?1:-1];
typedef char RuntimeTimeOffset[(MEMBER_OFFSET(TimelineRuntime,time)==0x1C)?1:-1];
typedef char RuntimeTargetOffset[(MEMBER_OFFSET(TimelineRuntime,target)==0x20)?1:-1];
typedef char RuntimeRateOffset[(MEMBER_OFFSET(TimelineRuntime,rate)==0x40)?1:-1];
typedef char RuntimeCursorOffset[(MEMBER_OFFSET(TimelineRuntime,cursor)==0x50)?1:-1];
