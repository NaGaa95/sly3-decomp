// SLY3_CFLAGS: -Os -G0

struct ApplyEntry { short delta, padding; void (*fn)(void *); };
struct ApplyTarget { unsigned char prefix[0xC]; struct ApplyEntry *table; };
struct ApplyRec { int kind; struct ApplyTarget *target; int value; };
struct ApplyOwner { unsigned char prefix[0xE4]; int count; struct ApplyRec *recs; };
void func_0023FE38(void *target, int value);
void func_0023FEC0(void *target, int value);

void func_00172D68(void *unused, struct ApplyOwner *owner, int flag)
{
    int i;
    if(!owner) return;
    for(i = 0; i < owner->count; i++) {
        struct ApplyRec *rec = &owner->recs[i];
        switch(rec->kind) {
        case 0:
        case 1:
            if(flag) rec->target->table[8].fn((char *)rec->target + rec->target->table[8].delta);
            else rec->target->table[9].fn((char *)rec->target + rec->target->table[9].delta);
            break;
        case 2:
        case 3:
            if(rec->kind == 2 ? flag != 1 : flag != 0) func_0023FE38(rec->target, rec->value);
            else func_0023FEC0(rec->target, rec->value);
            break;
        }
    }
}
