// SLY3_CFLAGS: -Os -G0
struct Receiver { unsigned char prefix[0x74]; void *record; };
int func_00263028(struct Receiver *receiver,void *record,int code);
void func_00260F18(struct Receiver *receiver,int first,int second,int third);
void func_00260E30(struct Receiver *receiver)
{
    int first=-1;
    int second=0x37B;
    int third=-1;
    if(func_00263028(receiver,receiver->record,0x376))
        first=0x376;
    if(func_00263028(receiver,receiver->record,0x377))
        second=0x377;
    if(func_00263028(receiver,receiver->record,0x378))
        third=0x378;
    func_00260F18(receiver,first,second,third);
}
