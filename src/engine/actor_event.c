// SLY3_CFLAGS: -Os -G0
#include "actor_resource_lookup_api.h"
struct ActorEventMethod { short adjustment,unused; void (*method)(void *,int); };
struct ActorEventChild {
    char prefix[12]; struct ActorEventMethod *methods;
    char before_kind[0x13C-0x10]; int kind;
};
struct ActorEventSubject {
    char prefix[0x4A4]; int transferred;
    char before_spatial[0x4AC-0x4A8]; void *spatial;
};
struct ActorEventEntry { int kind; void *resource; void *message; };
struct ActorEventPayload { void *source; char unused4[4]; int event; };
struct ActorEventOwner {
    char prefix[0x113C]; void *animation;
    char before_subject[0x11B4-0x1140]; struct ActorEventSubject *subject;
    char before_state[0x1520-0x11B8]; int state;
    char before_flag[0x1640-0x1524]; int flag;
    char before_substate[0x1820-0x1644]; int substate;
    struct ActorEventEntry *entry;
    char before_context[0x1830-0x1828]; char context[0x1950-0x1830];
    struct ActorEventEntry entries[7]; struct ActorEventChild *child;
};
void func_00153738(void *receiver,int kind,void *payload);
void func_0017F788(void *context,int kind,void *payload);
void func_001FC060(void *resource,void *object);
int func_0013F840(void *receiver);
void func_0013F8D0(void *receiver);
void func_001F2950(void *receiver);
int func_001F29A0(void *receiver,void *object,int index,int key);
void func_0013F870(void *receiver,int mode);
void func_001AF2A8(void *receiver,void *entry,void *object);
void func_0013EE68(struct ActorEventOwner *receiver,int kind,void *payload)
{
    func_00153738(receiver,kind,payload);
    if(receiver->state==16) func_0017F788(receiver->context,kind,payload);
    switch(kind) {
    case 10: {
        struct ActorEventPayload *event=payload;
        if(event->source==receiver->animation) {
            switch(event->event) {
            case 0x1EF: receiver->flag=1; break;
            case 0x264:
                if(receiver->substate==0) {
                    struct ActorEventChild *child;
                    receiver->child=func_001FBE30(receiver->entry->resource,0);
                    func_001FC060(receiver->entry->resource,receiver->child);
                    receiver->child->kind=receiver->entry->kind;
                    child=receiver->child;
                    child->methods[80].method((char *)child+child->methods[80].adjustment,0);
                }
                break;
            case 0x2E8:
                if(receiver->substate==4) {
                    if(func_0013F840(receiver)) {
                        struct ActorEventChild *child=receiver->child;
                        struct ActorEventSubject *subject;
                        void *spatial;
                        func_0013F8D0(receiver);
                        subject=receiver->subject;
                        spatial=subject->spatial;
                        func_001F2950(spatial);
                        func_001F29A0(spatial,child,-1,0x255);
                        subject->transferred=1;
                    } else func_0013F870(receiver,4);
                }
                break;
            case 0x1F0: receiver->flag=0; break;
            }
        }
        break;
    }
    case 1: {
        int i;
        for(i=0;i<7;++i) {
            struct ActorEventEntry *entry=&receiver->entries[i];
            if(entry->message==payload) func_001AF2A8(receiver,entry,0);
        }
        break;
    }
    }
}
