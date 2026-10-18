// SLY3_CFLAGS: -Os -G0
struct TransitionVTableEntry { short delta,pad; void (*function)(); };
struct TransitionObject { unsigned char prefix[0xC]; struct TransitionVTableEntry *table; };
struct TransitionSubject {
    unsigned char prefix[0x3C]; int flags;
    unsigned char gap40[0x58-0x40]; struct TransitionSubject *parent;
    unsigned char gap5C[0x74-0x5C]; int shared;
    unsigned char gap78[0x84-0x78]; int relatedCount; struct TransitionSubject **related;
    unsigned char gap8C[0x90-0x8C]; int childCount; struct TransitionSubject **children;
    unsigned char gap98[0xB0-0x98]; int value; struct TransitionSubject *chosen;
    int state; float started; int reservedC0; struct TransitionObject *item; int handle,otherHandle;
};
struct TransitionGame { unsigned char prefix[0x433C]; struct TransitionObject *first,*second; };
struct TransitionController { unsigned char prefix[0x50]; int mode; };
struct TransitionApplication { unsigned char prefix[0x14]; struct TransitionController *controller; };
struct TransitionPlayer {
    unsigned char prefix[0x2C]; struct TransitionVTableEntry *table;
    unsigned char tail[0x11C0-0x30];
};
struct TransitionClock { float time; };
extern struct TransitionGame D_00475480;
extern struct TransitionApplication D_004BC230;
extern struct TransitionObject *D_004797C0;
extern struct TransitionPlayer D_0036E740[];
extern struct TransitionClock D_0036BBD8;
extern int D_0036DBE0;
extern unsigned char D_0036C700[];
int func_00188A38(struct TransitionSubject *subject);
void func_001C9118(struct TransitionSubject *subject,int flag);
void func_001A93C8(void *game,int index,int group);
void func_001A9420(void *game,int index,int group);
void func_001A94A8(void *game,int index);
void func_001A94F0(void *game,int index);
void func_00226010(struct TransitionObject *object);
int func_00186930(struct TransitionSubject *subject);
int func_00186B68(struct TransitionSubject *subject);
void func_00262450(struct TransitionObject *object,int prompt);
void func_00284658(struct TransitionApplication *application);
void func_002846A8(struct TransitionApplication *application);
void func_00284778(struct TransitionApplication *application);
void func_00185638(void *context);
static __inline__ void ClearPrompt(struct TransitionObject *object)
{
    struct TransitionVTableEntry *entry=&object->table[54];
    ((void (*)(void *))entry->function)((char *)object+entry->delta);
}
static __inline__ void BeginPrompt(struct TransitionObject *object)
{
    struct TransitionVTableEntry *entry=&object->table[56];
    ((void (*)(void *))entry->function)((char *)object+entry->delta);
}
static __inline__ void PlayerCommand(struct TransitionPlayer *player,int command)
{
    struct TransitionVTableEntry *entry=&player->table[2];
    ((void (*)(void *,int))entry->function)((char *)player+entry->delta,command);
}
void func_001878E0(struct TransitionSubject *self,int state)
{
    int i;
    if(self->state==state) return;
    if(self->state==0) {
        int flags;
        self->chosen=0;
        for(i=0;i<self->parent->childCount;i++) {
            struct TransitionSubject *child=self->parent->children[i];
            if(child->handle) { self->chosen=child; break; }
        }
        if(self->chosen) {
            int j;
            for(j=0;j<self->chosen->relatedCount;j++) {
                struct TransitionSubject *related=self->chosen->related[j];
                if(related!=self->parent && !func_00188A38(related)) {
                    self->chosen=0;
                    break;
                }
            }
        }
        func_001C9118(self,1);
        flags=self->flags;
        if((flags^1)&1) *(int *)flags|=0x202;
        else self->flags=flags|0x202;
        if(self->shared) func_001A93C8(&D_00475480,-1,0);
        else func_001A93C8(&D_00475480,-1,2);
        func_001A94A8(&D_00475480,-1);
    }
    self->state=state;
    self->started=D_0036BBD8.time;
    switch(state) {
    case 0: {
        int flags;
        if(D_00475480.second) ClearPrompt(D_00475480.second);
        if(D_00475480.first) ClearPrompt(D_00475480.first);
        self->item=0;
        self->otherHandle=self->handle=-1;
        func_001C9118(self,2);
        flags=self->flags;
        if((flags^1)&1) *(int *)flags&=~0x202;
        else self->flags=flags&~0x202;
        if(self->shared) func_001A9420(&D_00475480,-1,0);
        else func_001A9420(&D_00475480,-1,2);
        func_001A94F0(&D_00475480,-1);
        break;
    }
    case 4:
        func_00226010(self->item);
        break;
    case 5: {
        int mode=D_004BC230.controller ? D_004BC230.controller->mode : -1;
        if(mode==0) {
            BeginPrompt(D_00475480.first);
            func_00262450(D_00475480.first,func_00186930(self));
            func_00284658(&D_004BC230);
        } else {
            BeginPrompt(D_004797C0);
        }
        break;
    }
    case 1:
        BeginPrompt(D_00475480.first);
        func_00262450(D_00475480.first,func_00186930(self));
        func_002846A8(&D_004BC230);
        func_00284778(&D_004BC230);
        break;
    case 2:
        func_00262450(D_00475480.first,func_00186B68(self));
        break;
    case 3: {
        int notmode=(D_0036DBE0!=2);
        if(!notmode) func_00185638(D_0036C700);
        PlayerCommand(&D_0036E740[0],0x90);
        PlayerCommand(&D_0036E740[1],0x90);
        break;
    }
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char VTableEntrySize[(sizeof(struct TransitionVTableEntry)==8)?1:-1];
typedef char FlagsOffset[(MEMBER_OFFSET(struct TransitionSubject,flags)==0x3C)?1:-1];
typedef char ParentOffset[(MEMBER_OFFSET(struct TransitionSubject,parent)==0x58)?1:-1];
typedef char SharedOffset[(MEMBER_OFFSET(struct TransitionSubject,shared)==0x74)?1:-1];
typedef char RelatedCountOffset[(MEMBER_OFFSET(struct TransitionSubject,relatedCount)==0x84)?1:-1];
typedef char ChildCountOffset[(MEMBER_OFFSET(struct TransitionSubject,childCount)==0x90)?1:-1];
typedef char ChosenOffset[(MEMBER_OFFSET(struct TransitionSubject,chosen)==0xB4)?1:-1];
typedef char StateOffset[(MEMBER_OFFSET(struct TransitionSubject,state)==0xB8)?1:-1];
typedef char TimeOffset[(MEMBER_OFFSET(struct TransitionSubject,started)==0xBC)?1:-1];
typedef char ItemOffset[(MEMBER_OFFSET(struct TransitionSubject,item)==0xC4)?1:-1];
typedef char HandleOffset[(MEMBER_OFFSET(struct TransitionSubject,handle)==0xC8)?1:-1];
typedef char OtherHandleOffset[(MEMBER_OFFSET(struct TransitionSubject,otherHandle)==0xCC)?1:-1];
typedef char GameFirstOffset[(MEMBER_OFFSET(struct TransitionGame,first)==0x433C)?1:-1];
typedef char ControllerOffset[(MEMBER_OFFSET(struct TransitionApplication,controller)==0x14)?1:-1];
typedef char PlayerVTableOffset[(MEMBER_OFFSET(struct TransitionPlayer,table)==0x2C)?1:-1];
typedef char PlayerStride[(sizeof(struct TransitionPlayer)==0x11C0)?1:-1];
