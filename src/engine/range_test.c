// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
typedef int (*Filter)(void *query,void *hit);
struct RangeEntry { short delta,padding; char *(*fn)(void *); };
struct RangeHolder { unsigned char prefix[0xC]; struct RangeEntry *table; unsigned char gap10[0x218-0x10]; int blocked; };
struct RangeSelf { unsigned char prefix[0x10]; struct RangeHolder *holder; };
int func_00198D78(Qword *position,int flags,Filter filter,float upper,float lower);
int func_0015E628(struct RangeSelf *self)
{
    struct RangeHolder *holder=self->holder;
    Qword position;
    if(holder->blocked) return 0;
    position=*(Qword *)(holder->table[36].fn((char *)holder+holder->table[36].delta)+0x30);
    return func_00198D78(&position,0,0,100.0f,-350.0f)==0;
}
