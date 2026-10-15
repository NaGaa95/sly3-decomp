// Related actor conversion preserves its measured32-bit attachment word; no ID claim.
// SLY3_CFLAGS: -Os -G0
#include "position_attachment_api.h"
#include "sequence_activity_api.h"
typedef SequencePackedPosition qword;
struct Matrix4 { qword rows[4]; };
struct VirtualEntry {
    short delta,word2;
    union {
        void (*event)(void *,int,void *,int,void *,void *);
        void (*notify)(void *,int,void *);
        struct Matrix4 *(*matrix)(void *);
    };
};
struct IdentityOwner { void *actor; };
struct RelatedLink { char pad0[0x14];struct IdentityOwner *owner; };
struct RelatedActor { char pad0[0x1E8];struct RelatedLink *link; };
struct Counters { int word0,word4; };
struct SequenceEntry { int identifier,count,operationCount;void *values; };
typedef char SequencePointer32[(sizeof(void *)==4)?1:-1];
struct SequenceActor {
    char pad0[0xC];struct VirtualEntry *table;
    char pad10[0x130-0x10];int counterCount;struct Counters *counters;
    int elementIndex,sequenceIndex,sequenceCount;struct SequenceEntry *entries;
    int flags;struct RelatedActor *related;int relationKind;
};
extern char D_00475480[],D_0036C700[];
void *func_001F4AD0(void *context,int index);
int func_0013B500(void *object,int type);
void func_001E57A0(struct SequenceActor *actor,struct SequenceEntry *entry);
// Shared query returns an attachment pointer; this callback ignores it.
void func_001854C8(void *context,int kind,struct SequenceActor *actor);
// The original15DE78 queue supplies its actual nullable owner in A1.
// This particular direct callback consumes only the receiver and ignores it.
void func_001E5508(struct SequenceActor *p,void *unusedCallbackOwner) {
    struct SequenceEntry *entry;
    int kind;
    if(func_001E5FF8(p))return;
    if(p->related==func_001F4AD0(D_00475480,0)) {
        p->flags=0xE;
    } else {
        kind=p->relationKind;
        if(kind==0x100||kind==0x10000||kind==0x20000||(p->related&&func_0013B500(p->related,0x3B))) {
            p->flags=8;
        } else if(p->related&&func_0013B500(p->related,0x59)) {
            if(p->related->link&&p->related->link->owner->actor==func_001F4AD0(D_00475480,0))p->flags=8;
        } else {
            p->flags=0;
        }
    }
    p->table[3].event((char *)p+p->table[3].delta,0x13,0,0,0,0);
    if(p->flags&1)return;
    entry=&p->entries[p->sequenceIndex];
    func_001E57A0(p,p->entries-1);
    func_001E57A0(p,entry);
    if(!p->related||!func_0013B500(p->related,0x3A)) {
        func_00173E00(D_00475480,0,
            p->table[36].matrix((char *)p+p->table[36].delta)->rows[3],(int)p->related);
    }
    if(entry->count>0) {
        if(++p->elementIndex>=entry->count) {
            p->elementIndex=0;
            if(++p->sequenceIndex>=p->sequenceCount) {
                p->table[4].notify((char *)p+p->table[4].delta,0x17,p);
                p->table[3].event((char *)p+p->table[3].delta,5,0,0,0,0);
                func_001854C8(D_0036C700,0xD,p);
            }
        }
    }
    if(func_001E5FC8(p)) {
        entry=&p->entries[p->sequenceIndex];
        if(entry->count<=0) {
            int i;
            for(i=0;i<p->counterCount;i++)p->counters[i].word4=0;
        }
    }
}
