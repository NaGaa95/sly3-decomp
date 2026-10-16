// SLY3_CFLAGS: -Os -G0
struct CLOCK { float t,dt; };
extern struct CLOCK D_0036BB98;
struct EngineSlotEntry { unsigned char prefix[0x148]; void *word148; };
struct EngineSlotSubject { unsigned char prefix[0x198]; int state; float since; void *list; unsigned char gap[0x1A8-0x1A4]; struct EngineSlotEntry *slots[7]; int index; };
void func_00154B48(void *list,void *word);
void func_00171670(struct EngineSlotSubject *subject,int state)
{
    if(subject->state==state) return;
    if(subject->state==2) func_00154B48(subject->list,subject->slots[subject->index]->word148);
    subject->state=state;
    subject->since=D_0036BB98.t;
    if(state==-1) {
        subject->index=state;
        func_00154B48(subject->list,0);
    }
}
