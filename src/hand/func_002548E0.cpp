// Original valid-reference protocol: the property metadata expects volume CID[19,26).
// The deferred flags4 lookup performs no runtime class check; this source preserves
// the original opaque reference behavior and does not assert a universal asset or
// alias-domain restriction. Expected-volume slot36 is2900D0; actor/state slot36
// is23CFB8. Supporting tables and external bytes are preserved, not emitted here.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Three real GP pointer inputs; all float/128-bit temporaries are produced locally.
// The symbol alias on the constructor binds an external function only; it emits
// no assembly instructions. The16-byte mask is copied/intersected bytewise.
#define FIELD_OFFSET(TYPE, FIELD) ((unsigned int)&((TYPE *)0)->FIELD)
typedef int qword __attribute__((mode(TI)));
struct ActionClassifierMask {
    union { unsigned int words[4]; unsigned char bytes[16]; };
    ActionClassifierMask() {}
    ActionClassifierMask(int index) asm("func_00252AD0");
    ActionClassifierMask operator&(const ActionClassifierMask &other) const {
        ActionClassifierMask result;
        for(int i=0;i<16;i++)result.bytes[i]=other.bytes[i]&bytes[i];
        return result;
    }
};
static inline int unequal_mask(const ActionClassifierMask & left,const ActionClassifierMask &right) {
    for(int i=0;i<16;i++)if(left.bytes[i]!=right.bytes[i])return 1;
    return 0;
}
struct ActionClassifierLimit { char prefix[0x28]; unsigned long flags; };
struct ActionClassifierRecord { char prefix[0x30]; void *object30; char pad34[0x5C-0x34]; void *object5C; };
struct ActionClassifierState {
    char prefix[0x2F4]; ActionClassifierMask mask;
    char pad304[0x384-0x304]; int near_enabled;
    float angle_a[2],angle_b[2]; float near_distance; int far_enabled;
    float far_angle[2]; float far_distance;
    char pad3AC[0x404-0x3AC]; struct ActionClassifierLimit *default_limit,*attached_limit;
};
struct ActionClassifierMatrix4 { qword row[4]; };
struct ActionClassifierVEntry { short delta,padding; const struct ActionClassifierMatrix4 *(*matrix)(void *); };
struct ActionClassifierActorPrefix {
    char prefix[0xC]; struct ActionClassifierVEntry *table;
    char pad10[0x11B4-0x10]; void *attached;
    int unused11B8,state; char pad11C0[8]; int enabled;
};
extern "C" {
extern ActionClassifierMask D_00475440;
ActionClassifierMask *func_00252AD0(ActionClassifierMask *output,int index);
void func_00155380(struct ActionClassifierActorPrefix *,struct ActionClassifierState *,void **attached,float *distance,float *angle);
int func_002533C0(struct ActionClassifierState *,int bit);
struct ActionClassifierRecord *func_002387A8(void *catalog,int key);
int func_0013B500(void *object,int kind);
int func_0027F258(struct ActionClassifierLimit *,qword position);
int func_0011EE30(const float *interval,float angle);
}
static inline qword actor_position(struct ActionClassifierActorPrefix *actor) {
    struct ActionClassifierVEntry *entry=&actor->table[36];
    return entry->matrix((char *)actor+entry->delta)->row[3];
}
typedef char ClassifierMaskIs16Bytes[sizeof(ActionClassifierMask)==16?1:-1];
typedef char ClassifierMatrixIs64Bytes[sizeof(ActionClassifierMatrix4)==64?1:-1];
typedef char ClassifierPackedPositionIs16Bytes[sizeof(qword)==16?1:-1];
typedef char ClassifierMaskOffset2F4[FIELD_OFFSET(ActionClassifierState,mask)==0x2F4?1:-1];
typedef char ClassifierEnabledOffset384[FIELD_OFFSET(ActionClassifierState,near_enabled)==0x384?1:-1];
typedef char ClassifierLimitOffset404[FIELD_OFFSET(ActionClassifierState,default_limit)==0x404?1:-1];
typedef char ClassifierAttachedOffset11B4[FIELD_OFFSET(ActionClassifierActorPrefix,attached)==0x11B4?1:-1];
typedef char ClassifierStateOffset11BC[FIELD_OFFSET(ActionClassifierActorPrefix,state)==0x11BC?1:-1];
typedef char ClassifierEnabledOffset11C8[FIELD_OFFSET(ActionClassifierActorPrefix,enabled)==0x11C8?1:-1];
extern "C" int func_002548E0(struct ActionClassifierState *p,struct ActionClassifierActorPrefix *actor,float *output)
{
    float distance,angle;
    void *object;
    struct ActionClassifierLimit *limit;
    const float *interval;
        func_00155380(actor,p,&actor->attached,&distance,&angle);
    if(output)*output=distance;
    if(!unequal_mask(ActionClassifierMask(1)&p->mask,D_00475440)) {
        if(p->near_enabled&&actor->enabled) {
            if(func_002533C0(p,0x31))
                object=func_002387A8((char *)p+0x29C,0xD2)->object30;
            else if(func_002533C0(p,0x44))
                object=func_002387A8((char *)p+0x29C,0xF1)->object30;
            else if(func_002533C0(p,0x2A))
                object=func_002387A8((char *)p+0x29C,0xDA)->object5C;
            else object=0;
            if(object) {
                if(object==actor)return 4;
                if(func_0013B500(object,0x33))return 4;
            }
        }
        if(p==actor->attached&&actor->state==3)limit=p->attached_limit;
        else limit=p->default_limit;
        if(limit&&((int)(limit->flags>>56)&1)&&func_0027F258(limit,actor_position(actor)))return 3;
    }
    interval=func_002533C0(p,0x2A)?p->angle_a:p->angle_b;
    if(distance<=p->near_distance*0.7f&&func_0011EE30(interval,angle)&&p->near_enabled)return 2;
    if(distance<=p->far_distance&&func_0011EE30(p->far_angle,angle)&&p->far_enabled)return 1;
    return 0;
}
