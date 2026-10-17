// SLY3_CFLAGS: -Os -G0
struct PollEntry { int value; int button; };
struct PollSelf {
    unsigned char prefix[0x134]; void *input;
    unsigned char gap138[0x190-0x138]; int state;
    unsigned char gap194[4]; int selected; int count; struct PollEntry entries[1];
};
void func_0023C660(void *receiver);
int func_001A7A80(void *input,int button,float seconds);
void func_001633E0(void *owner,int value);
void func_00163408(struct PollSelf *self)
{
    int previous;
    int index;
    struct PollEntry *entry;
    func_0023C660(self);
    do {
        previous=self->state;
        if(previous==1) {
            if(self->count==0) {
                if(func_001A7A80(self->input,0xF0,0.15f)) func_001633E0(self,0);
            } else {
                index=0;
                for(entry=self->entries;index<self->count;index++,entry++) {
                    if(func_001A7A80(self->input,entry->button,0.15f)) {
                        self->selected=entry->value;
                        func_001633E0(self,0);
                        break;
                    }
                }
            }
        }
    } while(self->state!=previous);
}
