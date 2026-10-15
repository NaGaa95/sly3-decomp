// Recovered parent registration and tag-dependent row availability initialization.
// Tag layout and encoded comparisons are derived from original accessed fields.
// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
#include "session.h"
struct SESSION_REGISTRATION_TAG {
    int unknown0,encodedType,encodedId;
    char padC[0x38-0xC];
    int idMask,typeMask;
};
static inline bool HasTagType(SESSION_REGISTRATION_TAG *tag) {
    if(!tag)return false;
    return (tag->encodedType^tag->typeMask)!=0;
}
static inline int MatchesTag(SESSION_REGISTRATION_TAG *left,SESSION_REGISTRATION_TAG *right) {
    if(left==right)return 1;
    if(!left||!right)return 0;
    return (left->encodedId^left->idMask)==(right->encodedId^right->idMask);
}
extern "C" SESSION_CONTROL_GAME D_00475480;
extern "C" int D_003448E0;
extern "C" SESSION_REGISTRATION_TAG D_003179F8,D_00317A38,D_00317A78,D_00317AB8,D_00317AF8;
extern "C" unsigned char D_00468D30[];
extern "C" void func_001C7DC8(SESSION_CONTROL_PARENT *);
extern "C" SESSION_CONTROL_NODE *func_0017E1B8(SESSION_CONTROL_GAME *,int,SESSION_CONTROL_NODE *,void *);
extern "C" int func_002833C8(SESSION_CONTROL_NODE *);
extern "C" int func_0025E4A0(int,void *);
extern "C" int func_0025E510(void *);
extern "C" int func_0025E6D0(void *);
extern "C" void func_0017AF50(SESSION_CONTROL_PARENT *);
extern "C" void func_0017AB08(SESSION_CONTROL_PARENT *parent) {
    func_001C7DC8(parent);
    SESSION_CONTROL_DATA *session=D_00475480.session;
    if(session) {
        if((unsigned int)parent->mode<3&&parent->index>=0&&parent->index<9) session->groups[parent->index].slots[parent->mode]=parent;
        for(int i=0;i<parent->count;i++) {
            SESSION_CONTROL_ROW *row=&parent->rows[i];
            switch(parent->mode) {
                case 0: row->node=func_0017E1B8(&D_00475480,261,row->node,0);
                if(row->node)row->available=func_002833C8(row->node);
                break;
                case 1: row->available=func_0025E4A0(parent->index,D_00468D30);
                break;
                case 2: {
                    SESSION_REGISTRATION_TAG *tag=(SESSION_REGISTRATION_TAG *)row->node;
                    if(HasTagType(tag)) {
                        if(MatchesTag(tag,&D_003179F8))row->available=1;
                        else if(MatchesTag(tag,&D_00317A38))row->available=func_0025E510(D_00468D30)>=35;
                        else if(MatchesTag(tag,&D_00317A78))row->available=func_0025E510(D_00468D30)>=70;
                        else if(MatchesTag(tag,&D_00317AB8))row->available=func_0025E6D0(D_00468D30)>=100;
                        else if(MatchesTag(tag,&D_00317AF8))row->available=func_0025E4A0(8,D_00468D30);
                    }
                    break;
                }
                default:break;
            }
            if(D_003448E0)row->available=1;
            if(row->available)parent->enabled=1;
        }
        parent->selected=-1;
        func_0017AF50(parent);
    }
}
