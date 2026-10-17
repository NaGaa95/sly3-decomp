// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Method { short delta,unused; void (*method)(void *,int); };
struct Source { unsigned char prefix[0xC]; struct Method *methods; };
struct Target { unsigned char prefix[0x130]; int limit; int position; };
struct Player {
    unsigned char prefix[0x48];
    struct Source *source;
    unsigned char gap4C[0x220];
    struct Target *target;
    unsigned char gap270[4];
    int forwarded;
    unsigned char gap278[4];
    int count;
    unsigned char gap280[0x18];
    int active;
};
qword func_00250600(struct Source *source);
void func_00279960(struct Target *target,qword value);
void *func_002459F8(int identifier);
void func_00244F08(void *receiver,int mode);
void func_002791C8(struct Player *player)
{
    if(player->active) {
        if(player->count>0) {
            func_00279960(player->target,func_00250600(player->source));
            player->forwarded++;
        }
        player->count++;
        func_00244F08(func_002459F8(0x60),0);
        if(player->target->position>=player->target->limit) {
            struct Method *method=&player->source->methods[99];
            method->method((char *)player->source+method->delta,0);
        }
    }
}
