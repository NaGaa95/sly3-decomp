// SLY3_CFLAGS: -Os -G0
struct ActorCompletionOwner {
    char prefix[0x218]; void *component;
    char unused21C[0x1924-0x21C]; int completion_state;
};
void func_0013E510(void *receiver,int state);
void func_0013FDE8(struct ActorCompletionOwner *receiver)
{
    int state;
    do {
        state=receiver->completion_state;
        switch(state) {
        case 0: break;
        case 1:
            if(receiver->component)
                func_0013E510(receiver,0);
            break;
        }
    } while(receiver->completion_state!=state && receiver->completion_state!=-1);
}
