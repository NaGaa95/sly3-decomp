// SLY3_CFLAGS: -Os -G0
struct SelectionMessage { int kind; unsigned char unused[12]; };
void *func_00292034(void *destination,int value,unsigned int bytes);
void *func_002387A8(void *list,int key);
void func_0019A2D0(void *receiver,struct SelectionMessage *message);
void func_001F4548(void *receiver,int selection);
void func_00162810(char *self,int selection)
{
    void *receiver;
    struct SelectionMessage message;
    if(selection!=*(int *)(self+0x130)) {
        receiver=func_002387A8(self+0x29C,0xC8);
        if(selection==-1) {
            func_00292034(&message,0,sizeof(message));
            message.kind=0;
            if(receiver) func_0019A2D0(receiver,&message);
        }
        func_001F4548(self,selection);
        if(selection!=-1) {
            func_00292034(&message,0,sizeof(message));
            message.kind=0x14;
            if(receiver) func_0019A2D0(receiver,&message);
        }
    }
}
