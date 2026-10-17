// SLY3_CFLAGS: -Os -G0
typedef int Qword __attribute__((mode(TI)));
typedef union { Qword packed; float lane[4]; } LiftVector;
struct LiftEntry { short delta,padding; char *(*fn)(void *); };
struct LiftReceiver { unsigned char prefix[0xC]; struct LiftEntry *table; };
struct LiftSelf { struct LiftReceiver *base; unsigned char gap4[0x20-4]; struct LiftReceiver *override; };
int func_00166540(void *owner);
Qword func_0016A750(struct LiftSelf *self)
{
    struct LiftReceiver *receiver=self->override;
    LiftVector position;
    if(!receiver) {
        receiver=(struct LiftReceiver *)func_00166540(self->base);
        if(receiver) {
            position.packed=*(Qword *)(receiver->table[36].fn((char *)receiver+receiver->table[36].delta)+0x30);
            position.lane[2]+=150.0f;
            goto done;
        }
        receiver=self->base;
    }
    position.packed=*(Qword *)(receiver->table[36].fn((char *)receiver+receiver->table[36].delta)+0x30);
done:
    return position.packed;
}
