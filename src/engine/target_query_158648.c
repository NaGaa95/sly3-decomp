// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
struct QueryEntry { short delta; short pad; unsigned char *(*method)(void *); };
struct QueryTarget { unsigned char prefix[0xC]; struct QueryEntry *table; unsigned char gap10[0xD8-0x10]; unsigned char *first; };
struct QuerySelf { unsigned char prefix[0x30]; struct QueryTarget *target; };
int func_0013B500(void *object,int identifier);
void *func_001ED678(Qword position,int option);
void *func_00158648(struct QuerySelf *self)
{
    if(func_0013B500(self->target,0x2F)) {
        unsigned char *first=self->target->first;
        unsigned char *second=first ? *(unsigned char **)(first+0xDC) : 0;
        return second ? *(void **)(second+0x10) : 0;
    }
    return func_001ED678(*(Qword *)(self->target->table[36].method((unsigned char *)self->target+self->target->table[36].delta)+0x30),1);
}
