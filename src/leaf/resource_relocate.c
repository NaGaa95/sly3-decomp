// SLY3_CFLAGS: -Os -G0
struct ClutPixel { unsigned char red,green,blue,alpha; };
struct RelocatedCountBits {
    unsigned long reserved0:7;
    unsigned short color_count:9;
    unsigned long reserved16:48;
};
union RelocatedClutMetadata {
    struct RelocatedCountBits bits;
    struct { unsigned short flags,reservedA; struct ClutPixel *data; } pointer;
};
struct RelocatedClut32 {
    int id;
    unsigned char mode,opaque5;
    signed char id_count,key_count;
    union RelocatedClutMetadata metadata;
    unsigned int quadword_count;
    unsigned char opaque14[12];
};
struct RelocatedResource40 {
    int id;
    unsigned char mode;
    unsigned char opaque5[15];
    void *data;
    unsigned char opaque18[16];
};
extern int D_00474FA0,D_00474F98;
extern struct RelocatedClut32 *D_00474FA4;
extern struct RelocatedResource40 *D_00474F9C;
void func_002338B8(struct ClutPixel *color);
void func_00236908(struct ClutPixel *color);
typedef char RelocatedCountSize8[(sizeof(struct RelocatedCountBits)==8)?1:-1];
typedef char RelocatedClutSize32[(sizeof(struct RelocatedClut32)==32)?1:-1];
typedef char RelocatedResourceSize40[(sizeof(struct RelocatedResource40)==40)?1:-1];
typedef char RelocatedPointerSize4[(sizeof(void*)==4)?1:-1];
void func_00233AE0(void *payload)
{
    int i=0,j;
    for(;i<D_00474FA0;i++) {
        struct RelocatedClut32 *clut=&D_00474FA4[i];
        if(clut->mode!=1)continue;
        clut->metadata.pointer.data=(struct ClutPixel *)
            ((unsigned int)payload+(unsigned int)clut->metadata.pointer.data);
        if(clut->metadata.pointer.flags&1) {
            struct ClutPixel *color;
            for(color=clut->metadata.pointer.data;
                (unsigned int)color < (unsigned int)clut->metadata.pointer.data+
                    clut->metadata.bits.color_count*sizeof(struct ClutPixel);++color)
                func_002338B8(color);
        }
        {
            struct ClutPixel *color;
            for(color=clut->metadata.pointer.data;
                (unsigned int)color < (unsigned int)clut->metadata.pointer.data+
                    clut->metadata.bits.color_count*sizeof(struct ClutPixel);++color)
                func_00236908(color);
        }
    }
    for(j=0;j<D_00474F98;j++) {
        struct RelocatedResource40 *resource=&D_00474F9C[j];
        if(resource->mode==1)
            resource->data=(void *)((unsigned int)payload+(unsigned int)resource->data);
    }
}
