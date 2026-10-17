// SLY3_CFLAGS: -Os -G0
struct Record { int kind; unsigned int mask; unsigned char gap8[0x98]; };
struct Table { unsigned char prefix[0x11E8]; int count; struct Record records[1]; };
struct Query { unsigned char prefix[0x250]; int kind; unsigned int mask; };
int func_002BF698(const unsigned char *bytes);
struct Record *func_002579A0(struct Table *table,struct Query *query)
{
    struct Record *best=0;
    int bestScore=0x7FFFFFFF;
    int i;
    for(i=0;i<table->count;i++) {
        struct Record *record=&table->records[i];
        if(record->kind==query->kind&&(record->mask&query->mask)) {
            int score=func_002BF698((const unsigned char *)&record->mask);
            if(score<bestScore) {
                best=record;
                bestScore=score;
            }
        }
    }
    return best;
}
