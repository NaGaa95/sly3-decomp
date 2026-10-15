// SLY3_CFLAGS: -Os -G0
struct ActorSelectionOwner {
    unsigned char prefix[0x298]; int fallback;
    unsigned char unused29C[0x320-0x29C]; char request[0x500-0x320];
    char message[0xE40-0x500]; char contextE40[0x1520-0xE40];
    int state; unsigned char unused1524[0x1820-0x1524];
    int substate; unsigned int word1824; int selection;
};
int func_001B5C78(void *context,int *mode);
void *func_001C4088(void *context,int *mode);
int func_001BD718(void *context,int *mode);
void func_0024DF48(void *receiver,int word,int mode);
void func_0013F1C8(struct ActorSelectionOwner *owner)
{
    int mode=0;
    int word;
    switch(owner->state) {
    case 3: word=func_001B5C78(owner->message,&mode); break;
    case 4: word=(int)func_001C4088(owner->contextE40,&mode); break;
    case 2: word=func_001BD718(owner->request,&mode); break;
    case 8:
        word=owner->substate==0 ? owner->selection : 0;
        break;
    default: word=0; break;
    }
    if(!word) word=owner->fallback;
    func_0024DF48(owner,word,mode);
}
