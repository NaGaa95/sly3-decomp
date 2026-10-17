// SLY3_CFLAGS: -Os -G0
struct CommandRecord { int kind; int id; int word; unsigned char gapC[4]; unsigned char data[0x40]; int flag; };
struct CommandOwner { unsigned char prefix[0x44]; struct CommandRecord *records; };
struct CommandMessage { unsigned char prefix[8]; int index; };
struct MovieState { unsigned char prefix[0x108]; int active; };
extern unsigned char D_0036C700[];
extern struct MovieState D_00389AC0;
extern unsigned char D_00475480[];
void func_001D52D0(void *message);
void *func_0025E070(int id);
void func_00189E70(void *receiver,void *request,int identifier,int mode);
void func_001DBD08(void *state,void *record);
void func_00289070(void *game,void *request,int word,int flags,int extra);
void func_0016FA08(struct CommandOwner *owner,struct CommandMessage *message)
{
    struct CommandRecord *record=owner->records+message->index;
    if(record->kind==0x56) {
        func_001D52D0(message);
        return;
    }
    if(record->word!=-1) {
        func_00189E70(D_0036C700,func_0025E070(record->id),record->word,2);
    } else {
        func_001DBD08(&D_00389AC0,record->data);
        if(record->flag) D_00389AC0.active=1;
        func_00289070(D_00475480,func_0025E070(0),0x1A8,3,-1);
    }
}
