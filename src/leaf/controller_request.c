// SLY3_CFLAGS: -Os -G0
struct RequestRecord64 { unsigned char bytes[64]; };
struct ControllerRequest72 {
    int flags;
    struct RequestRecord64 record;
    int word;
};
struct RequestGame {
    unsigned char prefix[0x43DC];
    struct RequestRecord64 current_record;
};
extern unsigned char D_004C4090[];
extern void *func_00292034(void *,int,unsigned int);
extern void func_00288DE8(void *,const struct ControllerRequest72 *,int,int);
extern void func_0025AD70(struct RequestGame *,const struct ControllerRequest72 *);

typedef char RequestRecord64Size[(sizeof(struct RequestRecord64)==64)?1:-1];
typedef char ControllerRequest72Size[(sizeof(struct ControllerRequest72)==72)?1:-1];

void func_00289070(struct RequestGame *game,const struct RequestRecord64 *record,
                   int word,int flags,int selected_id)
{
    struct ControllerRequest72 request;
    func_00292034(&request,0,sizeof(request));
    request.record=*(record?record:&game->current_record);
    request.word=word;
    request.flags=flags;
    if(selected_id!=-1)
        func_00288DE8(D_004C4090,&request,selected_id,1);
    else
        func_0025AD70(game,&request);
}
