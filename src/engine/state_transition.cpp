// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "resource_attachment_api.h"
#include "activation_selector_api.h"
#include "owner_parent_link.h"
#include "../P2/matrix_algorithms.h"
struct StateTransitionMatrix { EE_ATTACHMENT_QWORD rows[4]; };
struct StateTransitionEntry { short delta,padding; void *function; };
struct StateTransitionObject {
    unsigned char prefix[0xC];
    StateTransitionEntry *table;
    void *pointer10;
};
struct StateTransitionBone { unsigned char prefix[0xA0]; const void *pose; };
struct StateTransitionRecord { void *object; unsigned char rest[20]; };
struct StateTransitionOwner {
    unsigned char prefix[0xC]; StateTransitionEntry *table;
    unsigned char pad10[0x44-0x10];
    StateTransitionBone *bone44,*bone48,*bone4C;
    unsigned char pad50[0x130-0x50]; int controller;
    unsigned char pad134[0x1F0-0x134]; int state; float changed_at;
    unsigned char input_records[0x28C-0x1F8];
    int record_count;
    unsigned char pad290[0x2A4-0x290]; unsigned char record_storage[0x48];
    unsigned char pad2EC[4]; StateTransitionObject *object2F0;
    void *task2F4,*task2F8; int saved_controller;
    void *sound; int sound_identifier;
};
extern "C" {
struct StateTransitionClock { float now,delta; };
extern StateTransitionClock D_0036BB98;
extern unsigned char D_00475480[];
extern EE_ATTACHMENT_QWORD D_00317560;
void *func_002459F8(int identifier);
void func_00244F08(void *sound,void *owner);
void func_002BBCD8(void **destination,void *source);
void func_00244C28(void *sound);
void func_00244CA8(void *sound,float value);
void func_00240DB0(void *owner);
void func_0028F068(void *owner,void *bone,int flags);
void func_0023EBF8(void *owner,int mode);
void func_0023EC98(void *owner,int mode);
void func_0023FCD8(void *owner,int mode);
void func_001A94F0(void *game,int controller);
void func_001A94A8(void *game,int controller);
StateTransitionMatrix func_0028EC08(const void *first,const void *second,StateTransitionMatrix *matrix);
void func_0019BA10(StateTransitionOwner *owner,void *input_record);
void func_0019C570(StateTransitionOwner *owner,int state)
{
    int old=owner->state;
    if(state==old)return;
    switch(old) {
    case -1:
        if(owner->sound_identifier!=-1) {
            void *sound=func_002459F8(owner->sound_identifier);
            func_00244F08(sound,0);
            func_002BBCD8(&owner->sound,sound);
            func_00244C28(owner->sound);
        }
        break;
    case 2:
    case 6:
        func_00240DB0(owner);
        break;
    case 3:
        func_001309D8(&owner->task2F4);
        func_001309D8(&owner->task2F8);
        func_0028F068(owner,owner->bone48,2);
        func_0028F068(owner,owner->bone4C,2);
        func_001C7A00(owner,0,15);
        func_0023EBF8(owner,5);
        func_0023EC98(owner,4);
        func_0023FCD8(owner,0);
        func_001A94F0(D_00475480,owner->saved_controller);
        owner->object2F0=0;
        break;
    case 4:
        func_0023EBF8(owner,5);
        func_0023EC98(owner,4);
        break;
    case 5:
        func_0023EBF8(owner,5);
        break;
    case 1:
        for(int i=0;i<owner->record_count;++i) {
            StateTransitionRecord *record=(StateTransitionRecord *)(owner->record_storage+i*24);
            if(record->object)
                func_00239CE8(record->object,0x84);
        }
        break;
    }
    owner->state=state;
    owner->changed_at=D_0036BB98.now;
    switch(state) {
    case -1:
        {
            void **sound=&owner->sound;
            if(*sound) {
                func_00244CA8(*sound,0.0f);
                func_002BBCD8(sound,0);
            }
        }
        break;
    case 3:
        {
            StateTransitionMatrix matrix;
            StateTransitionObject *object=owner->object2F0;
            StateTransitionEntry *entry=&object->table[37];
            void *result=((void *(*)(void *,StateTransitionMatrix *))entry->function)((char *)object+entry->delta,&matrix);
            matrix=func_0028EC08(owner->bone44->pose,owner->bone48->pose,&matrix);
            entry=&owner->table[10];
            ((void (*)(void *,void *,void *,int))entry->function)((char *)owner+entry->delta,owner->object2F0->pointer10,result,3);
            entry=&owner->table[40];
            ((void (*)(void *,EE_ATTACHMENT_QWORD))entry->function)((char *)owner+entry->delta,D_00317560);
            entry=&owner->table[41];
            ((void (*)(void *,EE_ATTACHMENT_QWORD))entry->function)((char *)owner+entry->delta,D_00317560);
            owner->task2F4=func_00130078(owner,owner->bone48,1,8,2,matrix.rows[3]);
            owner->task2F8=func_00130078(owner,owner->bone4C,1,8,2,func_0011D3C0((const MATRIX3 *)&matrix));
            func_0023EBF8(owner,1);
            func_0023EC98(owner,1);
            func_0023FCD8(owner,1);
            owner->saved_controller=owner->controller;
            func_001A94A8(D_00475480,owner->saved_controller);
        }
        break;
    case 4:
        {
            StateTransitionEntry *entry=&owner->table[40];
            ((void (*)(void *,EE_ATTACHMENT_QWORD))entry->function)((char *)owner+entry->delta,D_00317560);
            entry=&owner->table[41];
            ((void (*)(void *,EE_ATTACHMENT_QWORD))entry->function)((char *)owner+entry->delta,D_00317560);
            func_0023EBF8(owner,1);
            func_0023EC98(owner,1);
        }
        break;
    case 5:
        {
            StateTransitionEntry *entry=&owner->table[40];
            ((void (*)(void *,EE_ATTACHMENT_QWORD))entry->function)((char *)owner+entry->delta,D_00317560);
            entry=&owner->table[41];
            ((void (*)(void *,EE_ATTACHMENT_QWORD))entry->function)((char *)owner+entry->delta,D_00317560);
            func_0023EBF8(owner,4);
        }
        break;
    }
    func_0019BA10(owner,state==-1?0:(char *)owner+(0x1F8u+(unsigned int)state*16u));
}
}
