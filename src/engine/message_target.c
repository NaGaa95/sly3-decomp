// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
extern Qword D_00317550;
struct MsgEntry { short delta,padding; char *(*fn)(void *); };
struct MsgSelf { unsigned char prefix[0xC]; struct MsgEntry *table; unsigned char gap10[0x130-0x10]; int busy; };
struct Msg { int word0; struct MsgSelf *target; };
void func_0013BEC0(struct MsgSelf *self,int id,struct Msg *msg);
void func_0014C9B8(void *self,Qword a,Qword b,int word);
void func_0014CB98(void *self,float value);
void func_0014C0B8(struct MsgSelf *self,int id,struct Msg *msg)
{
    func_0013BEC0(self,id,msg);
    if(id==6) {
        struct MsgSelf *target=msg->target;
        if(target==self) {
            if(!target->busy) {
                char *record=target->table[36].fn((char *)target+target->table[36].delta);
                func_0014C9B8(target,*(Qword *)(record+0x30),D_00317550,msg->word0);
                func_0014CB98(target,0.0f);
            }
        }
    }
}
