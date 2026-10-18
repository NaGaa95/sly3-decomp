// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
struct Action {
    int objectId,ownerId;
    unsigned int flags;
    int selection;
    int reserved10;
};
class ActionObject {
public:
    int prefix[3];
    virtual void V1();
    virtual void V2();
    virtual void V3();
    virtual void V4();
    virtual void V5();
    virtual void V6();
    virtual void V7();
    virtual void Activate();
    virtual void Deactivate();
};
struct Game;
extern "C" {
extern Game D_00475480;
int func_00185980(int state);
int func_001859A8(int count,int *states);
int func_0025E150(void);
void *func_0017E1B8(void *game,int kind,int id,void *owner);
}
extern "C" void func_00185A70(void *transported_unused,int state,int count,Action *actions)
{
    int stateMask=func_00185980(state);
    int allMask;
    if(state==4 || state==5) {
        int states[2]={4,5};
        allMask=func_001859A8(2,states);
    } else {
        int states[4]={0,1,2,3};
        allMask=func_001859A8(4,states);
    }
    for(int i=0;i<count;i++) {
        Action *action=&actions[i];
        if(!(action->flags&allMask)) continue;
        if(action->selection!=-1 && action->selection!=func_0025E150()) continue;
        void *owner=func_0017E1B8(&D_00475480,5,action->ownerId,0);
        if(!owner && action->ownerId!=-1) continue;
        ActionObject *object=(ActionObject *)func_0017E1B8(&D_00475480,owner?4:5,action->objectId,owner);
        if(!object) continue;
        if(action->flags&stateMask) object->Activate();
        else object->Deactivate();
    }
}

#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char IntSize[(sizeof(int)==4)?1:-1];
typedef char ActionSize[(sizeof(Action)==20)?1:-1];
typedef char ActionId[(MEMBER_OFFSET(Action,objectId)==0)?1:-1];
typedef char ActionOwner[(MEMBER_OFFSET(Action,ownerId)==4)?1:-1];
typedef char ActionFlags[(MEMBER_OFFSET(Action,flags)==8)?1:-1];
typedef char ActionSelection[(MEMBER_OFFSET(Action,selection)==12)?1:-1];
typedef char ActionReserved[(MEMBER_OFFSET(Action,reserved10)==16)?1:-1];
typedef char ActionObjectPrefix[(sizeof(ActionObject)==16)?1:-1];
