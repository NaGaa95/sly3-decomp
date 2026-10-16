// SLY3_CFLAGS: -Os -G0
union ChainCopyQuadword { unsigned int words[4]; unsigned short halves[8]; };
struct ChainCopyRequest {
    int bytes, alignment;
};
struct ChainCopyCount {
    char prefix[0x10];
    unsigned int qword_count;
};
struct ChainCopyView {
    char prefix[0x10];
    union ChainCopyQuadword *words;
    void *cursor;
};
void *func_001D24D0(struct ChainCopyRequest *request, void *source);
void func_0018FBB0(struct ChainCopyCount *count, struct ChainCopyView *view,
    unsigned int qword_count, union ChainCopyQuadword *source, unsigned int relocation_qwords,
    unsigned int new_base_address, unsigned int old_base_address)
{
    struct ChainCopyRequest request;
    union ChainCopyQuadword *copy;
    request.bytes=(int)(qword_count<<4);
    request.alignment=0x10;
    count->qword_count=qword_count;
    copy=func_001D24D0(&request, source);
    view->words=copy;
    { unsigned int copy_displacement=(unsigned int)copy-(unsigned int)source;
      view->cursor=(void *)((unsigned int)view->cursor+copy_displacement); }
    if (relocation_qwords && new_base_address!=old_base_address) {
        unsigned int difference=new_base_address-old_base_address;
        union ChainCopyQuadword *packet=copy;
        while((unsigned int)packet<(unsigned int)view->words+(count->qword_count<<4)) {
            switch ((int)(packet->words[0]>>28)) {
            case 4:
                if (packet->words[1]>=old_base_address &&
                   packet->words[1]<old_base_address+(relocation_qwords<<4))
                    packet->words[1]+=difference;
                packet++;
                break;
            case 1:
                packet+=packet->halves[0]+1;
                break;
            case 6:
                packet=(union ChainCopyQuadword *)((unsigned int)view->words+(count->qword_count<<4));
                break;
            }
        }
    }
}
