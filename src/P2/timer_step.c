// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Method { short delta,unused; void *(*method)(void *); };
struct Target { unsigned char prefix[0xC]; struct Method *methods; };
struct Countdown {
    unsigned char prefix[0x13C];
    struct Target *target;
    unsigned char gap140[0x2C];
    int state;
    unsigned char gap170[4];
    int timer;
    unsigned char gap178[0xF8];
    qword captured;
};
struct Step { unsigned char prefix[0x24]; int delta; unsigned char gap28[0x28]; unsigned flags; };
void func_00232A38(struct Countdown *countdown,int state);
void func_00232E88(struct Countdown *countdown);
int func_00232670(struct Countdown *countdown,struct Step *step)
{
    int state;
    if(!(step->flags&2))
        return 0;
    state=countdown->state;
    if(state==4)
        return 0;
    countdown->timer-=step->delta;
    if(countdown->timer<=0) {
        func_00232A38(countdown,4);
        return 1;
    }
    if(state==0) {
        struct Method *entry=&countdown->target->methods[36];
        void *current=entry->method((char *)countdown->target+entry->delta);
        countdown->captured=*(qword *)((char *)current+0x30);
        func_00232E88(countdown);
    }
    return 1;
}
