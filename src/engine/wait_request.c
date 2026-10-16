// SLY3_CFLAGS: -Os -G0
typedef struct WaitRequestMessage {
    int kind;
    void *value;
    unsigned int word8,wordC;
} WaitRequestMessage;
void *func_002387A8(void *list,int kind);
void *func_00292034(void *destination,int value,unsigned int bytes);
void func_0019A2D0(void *state,WaitRequestMessage *message);
void func_00198540(void *owner,void *value)
{
    WaitRequestMessage message;
    void *state=func_002387A8((char *)owner+0x29C,0xC8);
    if(state) {
        func_00292034(&message,0,sizeof(message));
        message.value=value;
        message.kind=5;
        func_0019A2D0(state,&message);
    }
}
