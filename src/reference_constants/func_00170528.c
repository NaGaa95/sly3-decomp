// Complete USA inline-record lookup; actual table and nullable key.
// No incoming third argument; the loop computes each returned record.
// GCC zero-length tail leaves original array capacity unknown.
// SLY3_CFLAGS: -Os -G0
struct Record {
    void *key;
    int words[4];
};
struct Holder {
    char prefix[0xD8];
    int count;
    struct Record entries[0];
};
struct Record *func_00170528(struct Holder *p,void *key) {
    int i,count;
    if(!key)return 0;
    count=p->count;
    for(i=0;i<count;) {
        struct Record *r=&p->entries[i++];
        if(r->key==key)return r;
    }
    return 0;
}
