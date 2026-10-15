// SLY3_CFLAGS: -Os -G0
#include "actor_resource_lookup_api.h"
#include "actor_state_resource_api.h"
struct ActorRequestEntry { int kind; void *resource; void *message; };
struct ActorRequestOwner;
struct ActorRequestObject {
    char prefix[0x13C];
    int kind;
    char before_owner[0x14C-0x140];
    struct ActorRequestOwner *owner;
};
struct ActorRequestGate {
    char prefix[0x190];
    int first;
    int word194;
    int second;
    int word19C;
    int third;
};
struct ActorRequestOwner {
    char prefix[0x500];
    char message_context[0x9FC-0x500];
    int request_kind;
    char before_state[0x1290-0xA00];
    int state_word;
    int state;
    char before_object[0x12A0-0x1298];
    struct ActorRequestObject *object;
    char before_saved[0x13F4-0x12A4];
    int saved;
    char before_event[0x1400-0x13F8];
    int event_request;
    char before_entry[0x1824-0x1404];
    struct ActorRequestEntry *entry;
    char before_first[0x19AC-0x1828];
    int first_saved;
    int second_saved;
    int word19B4;
    struct ActorRequestGate *gate;
};
extern char D_0036C700[];
void func_001854C8(void *,int,struct ActorRequestOwner *);
struct ActorRequestEntry *func_001400C0(struct ActorRequestOwner *,int);
void func_002734E8(void *,int);
int func_00277610(struct ActorRequestObject *);
void func_001AF2A8(struct ActorRequestOwner *,struct ActorRequestEntry *,struct ActorRequestObject *);
unsigned int func_00154798(struct ActorRequestOwner *,int);
void func_00154460(struct ActorRequestOwner *,int);
void func_0013E510(struct ActorRequestOwner *,int);
void func_001545A8(struct ActorRequestOwner *,int);
void func_00286D70(struct ActorRequestGate *);

void func_00140128(struct ActorRequestOwner *owner,int kind)
{
    owner->event_request = kind;
    func_001854C8(D_0036C700,0x4D,owner);
    owner->event_request = -1;
    switch(kind) {
    case 4: case 6: case 8: case 10: case 15: case 16: {
        struct ActorRequestEntry *entry = func_001400C0(owner,kind);
        if(((unsigned int)owner->state-4u)<3u) {
            func_002734E8(&owner->state_word,7);
            return;
        }
        if(entry->message) {
            func_001B40F0(owner->message_context,0xB,entry->message,0);
            return;
        }
        owner->entry = entry;
        switch(kind) {
        case 6: case 8: case 10: case 15: {
            struct ActorRequestObject *object = func_001FBE30(entry->resource,0);
            if(!object) return;
            object->kind = entry->kind;
            if(func_00277610(object)) {
                object->owner = owner;
                func_001AF2A8(owner,entry,object);
            }
            owner->object = object;
            func_00154798(owner,kind);
            func_0013E510(owner,0xE);
            func_002734E8(&owner->state_word,4);
            return;
        }
        default: break;
        }
        func_00154460(owner,kind);
        func_0013E510(owner,8);
        return;
    }
    case 13: {
        struct ActorRequestEntry *entry = func_001400C0(owner,kind);
        if(!entry->message && !owner->gate) {
            struct ActorRequestObject *object;
            owner->entry = entry;
            object = func_001FBE30(entry->resource,0);
            if(!object) return;
            object->kind = entry->kind;
            if(func_00277610(object)) {
                object->owner = owner;
                func_001AF2A8(owner,entry,object);
            }
            owner->object = object;
            func_001AF2A8(owner,entry,object);
            func_0013E510(owner,0xE);
            func_002734E8(&owner->state_word,4);
            return;
        }
        if(((unsigned int)owner->state-4u)<3u) {
            func_002734E8(&owner->state_word,7);
            return;
        }
        if(owner->gate->first || owner->gate->third || owner->gate->second) return;
        func_00286D70(owner->gate);
        return;
    }
    case 9:
        func_00154460(owner,kind);
        func_0013E510(owner,0xF);
        return;
    case 14:
        owner->request_kind = kind;
        owner->saved = owner->second_saved;
        func_001B40F0(owner->message_context,0xB,0,0);
        return;
    case 12:
        owner->request_kind = kind;
        owner->saved = owner->first_saved;
        func_001B40F0(owner->message_context,0xB,0,0);
        return;
    case 7:
        func_0013E510(owner,0x10);
        return;
    default:
        func_001545A8(owner,kind);
        return;
    }
}
