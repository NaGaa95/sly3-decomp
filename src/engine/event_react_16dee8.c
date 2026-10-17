// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct ReactEntry { short delta; short pad; union { void *(*get)(void *); void (*send)(void *, void *); } fn; };
struct ReactLink { unsigned char prefix[0xC]; struct ReactEntry *table; };
struct ReactObject { unsigned char prefix[4]; void *first; void *second; unsigned int flags; };
struct ReactSelf { unsigned char prefix[0x10]; struct ReactLink *link; unsigned char gap14[0x40 - 0x14]; struct ReactObject *object; unsigned char gap44[0x50 - 0x44]; int word50; unsigned char gap54[4]; int count; };
struct ReactTarget { unsigned char prefix[0xC]; struct ReactEntry *table; };
extern unsigned char D_00475480[];
extern int D_00321060[];
extern int D_00321078[];
int func_00254F80(void *object);
int func_00254EB8(void *object);
void func_00254E18(void *object);
void func_00254D38(void *object, void *link, float value, unsigned int flags);
float *func_00136880(void *first, int key);
void func_00137D08(void *second, float a, float b, int c, int d);
void func_0016E118(void *self, int value);
struct ReactTarget *func_0017E1B8(void *game, int kind, int id, void *context);
void *func_00292034(void *destination, int byte, unsigned int bytes);
int func_00131850(void *self, int kind, int *event);
int func_0016DEE8(struct ReactSelf *self, int kind, int *event)
{
    switch(kind) {
    case 0xA:
        if(self->object) {
            if(func_00254F80(self->object) == event[0]) {
                if(event[2] == 0x5A) {
                    self->count = 0;
                    return 1;
                }
            }
        }
        break;
    case 0x11: {
        int index;
        float value;
        struct ReactTarget *target;
        if(!self->word50) return 1;
        if(func_00254EB8(self->object)) {
            func_00254E18(self->object);
            func_00254D38(self->object, self->link, 0.0f, self->object->flags | 1);
        }
        self->count = self->count + 1;
        index = 4;
        if(self->count <= 3) index = self->count;
        value = 0.0f;
        while(index > 0) {
            float *found = func_00136880(self->object->first, D_00321060[index]);
            if(found) { value = *found; break; }
            index--;
        }
        func_00137D08(self->object->second, value, 1.0f, 0, 0);
        func_0016E118(self, 0);
        target = func_0017E1B8(D_00475480, 5, D_00321078[index], 0);
        if(!target) return 1;
        {
            int record[16];
            Quad *where;
            func_00292034(record, 0, 0x40);
            record[0] = 5;
            where = (Quad *)((char *)self->link->table[36].fn.get((char *)self->link + self->link->table[36].delta) + 0x30);
            *(Quad *)&record[8] = *where;
            target->table[55].fn.send((char *)target + target->table[55].delta, record);
        }
        return 1;
    }
    }
    return func_00131850(self, kind, event);
}
