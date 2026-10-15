// SLY3_CFLAGS: -Os -G0
struct SelectionEntry {
    int key;
    float activeTime;
    float idleTime;
    unsigned char tail[0x30-0xC];
};
struct SelectionOwner {
    unsigned char prefix[0x4C];
    int count;
    struct SelectionEntry *entries;
};
typedef char CheckSelectionEntry48[(sizeof(struct SelectionEntry)==0x30)?1:-1];
extern float D_0036BB98;

struct SelectionEntry *func_00199728(struct SelectionOwner *owner,int excludedKey)
{
    float activeCutoff=D_0036BB98-4.0f;
    float idleCutoff=D_0036BB98;
    struct SelectionEntry *best=0;
    int i;
    for(i=0;i<owner->count;i++) {
        struct SelectionEntry *entry=&owner->entries[i];
        if(entry->key!=0) {
            if(entry->key==excludedKey)
                continue;
            if(best && best->key==0)
                continue;
            if(activeCutoff<=entry->activeTime)
                continue;
            activeCutoff=entry->activeTime;
        } else {
            if(idleCutoff<=entry->idleTime)
                continue;
            idleCutoff=entry->idleTime;
        }
        best=entry;
    }
    return best;
}
