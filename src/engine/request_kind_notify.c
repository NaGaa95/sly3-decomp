// SLY3_CFLAGS: -Os -G0
void func_001B40F0(void *context,int kind,int message,int flag);
struct RequestKindOwner {
    char prefix[0x500];
    char message_context[0x9FC-0x500];
    int request_kind;
};
void func_001545A8(struct RequestKindOwner *owner,int kind)
{
    switch(kind) {
    case 0x16:
        owner->request_kind=kind;
        func_001B40F0(owner->message_context,0xB,0,0);
        break;
    case 0x14:
        owner->request_kind=kind;
        func_001B40F0(owner->message_context,0xB,0,0);
        break;
    }
}
