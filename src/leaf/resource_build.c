// SLY3_CFLAGS: -Os -G0
struct ResourceColor4 { unsigned char r,g,b,a; };
struct ResourcePacketPart { int count; void *data; };
struct ResourceBuild44;
struct ResourceBuildLink20 {
    unsigned char opaque0[6];
    unsigned char resource40_count;
    unsigned char resource32_count;
    struct ResourceBuild44 *owner;
    void *resources40;
    void *resources32;
};
struct ResourceBuild44 {
    unsigned char opaque0[4];
    unsigned char kind;
    unsigned char flags;
    unsigned char opaque6[2];
    struct ResourceColor4 color8,colorC,color10;
    unsigned char opaque14[3];
    unsigned char link_count;
    struct ResourceBuildLink20 *links;
    int part_count;
    struct ResourcePacketPart *parts;
    int resource_count;
    void *auxiliary;
};
typedef char ResourceBuildSize44[(sizeof(struct ResourceBuild44)==44)?1:-1];
typedef char ResourceBuildLinkSize20[(sizeof(struct ResourceBuildLink20)==20)?1:-1];
typedef char ResourcePacketPartSize8[(sizeof(struct ResourcePacketPart)==8)?1:-1];
extern void **D_00474FAC;
void func_00118DA0(void *stream,int bytes,void *output);
void func_00236908(struct ResourceColor4 *);
int func_00119128(void *stream);
void *func_00117B40(void *heap,unsigned int bytes,int category);
void func_00234900(void *stream,void *heap,struct ResourceBuildLink20 *link);
static __inline__ void InitResourcePart(struct ResourcePacketPart *part,int count,void *heap)
{
    part->count=count;
    part->data=func_00117B40(heap,count*16,0x2B);
}
void func_00234A58(void *stream,void *heap,struct ResourceBuild44 *object)
{
    int i,index;
    struct ResourcePacketPart *parts,*part;
    func_00118DA0(stream,24,object);
    func_00236908(&object->color8);
    func_00236908(&object->colorC);
    func_00236908(&object->color10);
    index=func_00119128(stream);
    if(index>=0)object->auxiliary=D_00474FAC[index];
    object->links=func_00117B40(heap,object->link_count*20,0x2F);
    for(i=0;i<object->link_count;i++) {
        struct ResourceBuildLink20 *link=&object->links[i];
        func_00234900(stream,heap,link);
        link->owner=object;
    }
    object->resource_count=object->links->resource40_count;
    switch(object->kind) {
    case 0:case 4:case 5:case 6:object->part_count=1;break;
    case 1:case 2:object->part_count=2;break;
    case 7:object->part_count=(object->flags&0x10)?2:3;break;
    case 3:object->part_count=4;break;
    }
    parts=func_00117B40(heap,object->part_count*8,0x2B);
    object->parts=parts;
    switch(object->kind) {
    case 0:case 4:case 5:case 6:
        InitResourcePart(parts,object->links->owner->resource_count+8,heap);
        break;
    case 3:{
        int count=(object->flags&2)?object->links->owner->resource_count+2:0;
        InitResourcePart(parts,count+6,heap);
        part=&parts[1];InitResourcePart(part,6,heap);
        part=&parts[2];InitResourcePart(part,8,heap);
        part=&parts[3];InitResourcePart(part,4,heap);
        break;
    }
    case 2:
        InitResourcePart(parts,5,heap);
        part=&parts[1];InitResourcePart(part,5,heap);
        break;
    case 1:{
        int count=object->links->owner->resource_count+8;
        InitResourcePart(parts,count,heap);
        part=&parts[1];InitResourcePart(part,count,heap);
        break;
    }
    case 7:{
        int count=object->links->owner->resource_count+8;
        InitResourcePart(parts,count,heap);
        part=&parts[1];InitResourcePart(part,count,heap);
        part=&parts[2];
        if(!(object->flags&0x10))InitResourcePart(part,count,heap);
        break;
    }
    }
}
