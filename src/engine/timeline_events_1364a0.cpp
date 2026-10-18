// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "../P2/heap.h"
#include "../P2/bis.h"
union TimelinePayload { int integer; float real; void *pointer; };
struct TimelineLoadedEvent {
    float time;
    int kind;
    TimelinePayload first,second,third;
};
struct TimelineStartPayload { int number,first,second,third; float x,y,z; };
struct TimelineSmallPayload { int first,second; float real; };
struct TimelinePair { unsigned int words[2]; };
extern "C" void func_001364A0(void *receiver,CBinaryInputStream *stream,HEAP *heap,int timed,int *outputCount,TimelineLoadedEvent **output)
{
    int index=0;
    int count=stream->U8Read();
    *outputCount=count;
    TimelineLoadedEvent *events=(TimelineLoadedEvent *)PvAllocClear(heap,count*sizeof(TimelineLoadedEvent),0xA);
    *output=events;
    for(;index<count;index++) {
        TimelineLoadedEvent *event=&events[index];
        event->kind=stream->S8Read();
        if(timed) event->time=stream->U16Read()*(1.0f/60.0f);
        switch(event->kind) {
        case 0: {
            TimelineStartPayload payload;
            payload.number=stream->S16Read();
            payload.first=stream->S32Read();
            payload.second=stream->S32Read();
            payload.third=stream->S32Read();
            payload.z=stream->F32Read();
            payload.x=stream->F32Read();
            payload.y=stream->F32Read();
            event->first.pointer=PvAllocCopy(heap,sizeof(payload),&payload,0xA);
            break;
        }
        case 1:
            event->first.integer=stream->S16Read();
            break;
        case 2:
            event->first.integer=stream->S16Read();
            event->second.integer=stream->S32Read();
            break;
        case 3:
            event->second.real=stream->U16Read()*(1.0f/60.0f);
            event->first.integer=stream->S16Read();
            event->third.integer=stream->S32Read();
            break;
        case 5:
            event->first.real=stream->U16Read()*(1.0f/60.0f);
            event->second.real=stream->F32Read();
            break;
        case 7: case 8:
            event->first.integer=stream->S32Read();
            event->second.real=stream->F32Read();
            break;
        case 13: case 14: case 15: case 16:
            event->first.integer=stream->S32Read();
            event->second.integer=stream->S32Read();
            break;
        case 17:
            event->first.pointer=PvAllocClear(heap,sizeof(TimelineSmallPayload),0xA);
            ((TimelineSmallPayload *)event->first.pointer)->first=stream->S32Read();
            ((TimelineSmallPayload *)event->first.pointer)->second=stream->S32Read();
            ((TimelineSmallPayload *)event->first.pointer)->real=stream->F32Read();
            break;
        case 20: {
            TimelineSmallPayload payload;
            payload.first=stream->S32Read();
            payload.second=stream->S32Read();
            payload.real=stream->F32Read();
            event->first.pointer=PvAllocCopy(heap,sizeof(payload),&payload,0xA);
            break;
        }
        case 21:
            event->first.integer=stream->S16Read();
            break;
        case 24: {
            TimelinePair *pairs=(TimelinePair *)heap->PvAlloc(3*sizeof(TimelinePair),0xA);
            stream->ReadCb8(&pairs[0]);
            stream->ReadCb8(&pairs[1]);
            stream->ReadCb8(&pairs[2]);
            event->first.pointer=pairs;
            break;
        }
        case 4: case 11: case 12: case 22: case 25: case 26:
            event->first.integer=stream->S32Read();
            break;
        }
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char EventSize[(sizeof(TimelineLoadedEvent)==20)?1:-1];
typedef char StartPayloadSize[(sizeof(TimelineStartPayload)==28)?1:-1];
typedef char SmallPayloadSize[(sizeof(TimelineSmallPayload)==12)?1:-1];
typedef char PairSize[(sizeof(TimelinePair)==8)?1:-1];
typedef char EventKindOffset[(MEMBER_OFFSET(TimelineLoadedEvent,kind)==4)?1:-1];
typedef char EventFirstOffset[(MEMBER_OFFSET(TimelineLoadedEvent,first)==8)?1:-1];
typedef char EventSecondOffset[(MEMBER_OFFSET(TimelineLoadedEvent,second)==12)?1:-1];
typedef char EventThirdOffset[(MEMBER_OFFSET(TimelineLoadedEvent,third)==16)?1:-1];
