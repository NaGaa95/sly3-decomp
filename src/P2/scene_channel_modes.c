// SLY3_CFLAGS: -Os -G0
struct ChannelModeFrame { unsigned char prefix[0x90]; int word90; int word94; short kind; };
struct ChannelModeConfiguration { float vector[4]; int kind; };
struct ChannelModeProperties {
    unsigned char prefix[0x90];
    struct ChannelModeConfiguration second;
    unsigned char gap[0xB0-0xA4];
    struct ChannelModeConfiguration first;
};
struct ChannelModeOwner {
    unsigned char prefix[0x48];
    struct ChannelModeFrame *first,*second;
    unsigned char gap[0xD8-0x50];
    struct ChannelModeProperties *properties;
};
struct SceneRebindState;
void func_0028F068(void *,void *,int);
void func_0023E9D0(void *,struct ChannelModeFrame *,int,struct ChannelModeConfiguration *);
void func_0023EA88(struct SceneRebindState *);
void func_00241F00(void *,int);
void func_0023EBF8(void *receiver,int mode)
{
    struct ChannelModeOwner *owner=(struct ChannelModeOwner *)receiver;
    if(owner->properties) {
        struct ChannelModeFrame *frame=owner->first;
        if(!frame->word90 && frame->kind!=2) func_0028F068(receiver,frame,1);
        func_0023E9D0(receiver,frame,mode,&owner->properties->first);
        func_0023EA88((struct SceneRebindState *)receiver);
        if(owner->properties->first.kind!=3) func_00241F00(receiver,0);
    }
}
void func_0023EC98(void *receiver,int mode)
{
    struct ChannelModeOwner *owner=(struct ChannelModeOwner *)receiver;
    if(owner->properties) {
        struct ChannelModeFrame *frame=owner->second;
        if(!frame->word90 && frame->kind!=2) func_0028F068(receiver,frame,1);
        func_0023E9D0(receiver,frame,mode,&owner->properties->second);
        func_0023EA88((struct SceneRebindState *)receiver);
        if(owner->properties->second.kind!=3) func_00241F00(receiver,0);
    }
}
