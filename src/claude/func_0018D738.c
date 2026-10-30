// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Adapted from the Sly 2 decomp (func_00167870); Sly 3 remaps the entry index through a table.
typedef unsigned int uint;
typedef unsigned long ulong;
struct META{float limit;long kind:4;ulong count:8;ulong channel:6;ulong feature:1;ulong index:13;};
struct RECORD{float position[3];float radius;struct META meta;void*link;int pad1C;};
struct GROUP{struct RECORD records[4];};
struct D{signed char channel;char pad1[0x13];};
struct E{char pad[0xC];uint flags;void*matrix;int word;char pad18[0xC];struct RECORD*sphere;};
struct P{char pad[0x3C];struct D*descriptors;struct E*entries;void*localSpheres;struct GROUP*groups;};
struct STREAM;
struct REQUEST{int bytes,alignment;};
typedef char MetaSize[sizeof(struct META)==8?1:-1];
typedef char RecordSize[sizeof(struct RECORD)==0x20?1:-1];
typedef char DescSize[sizeof(struct D)==0x14?1:-1];
typedef char EntrySize[sizeof(struct E)==0x28?1:-1];
short func_00117D50(struct STREAM*) __asm__("S16Read__18CBinaryInputStream");
char func_00117D00(struct STREAM*) __asm__("S8Read__18CBinaryInputStream");
struct VECTOR;
void func_00117EB0(struct STREAM*,struct VECTOR*) __asm__("ReadVector__18CBinaryInputStreamP6VECTOR");
float func_00117E38(struct STREAM*) __asm__("F32Read__18CBinaryInputStream");
unsigned char func_00117BD0(struct STREAM*) __asm__("U8Read__18CBinaryInputStream");
void*func_001D2538(struct REQUEST*);
static inline float Min(float a,float b){return b<a?b:a;}
void func_0018D738(struct P*p,struct STREAM*stream,int*remap){
    int count=func_00117D50(stream);
    if(count){
        struct REQUEST request;
        struct GROUP*groups;
        int i;
        request.bytes=count*sizeof(struct GROUP);request.alignment=0x10;
        groups=(struct GROUP*)func_001D2538(&request);
        for(i=0;i<count;i++){
            struct GROUP*group=&groups[i];
            uint j;
            for(j=0;j<4;j++){
                struct RECORD*record=&group->records[j];
                record->meta.kind=func_00117D00(stream);
                if(record->meta.kind==-1){
                    for(;j<4;j++)group->records[j].meta.kind=-1;
                    break;
                }
                func_00117EB0(stream,(struct VECTOR*)record->position);
                record->radius=func_00117E38(stream);
                record->meta.limit=func_00117E38(stream);
                record->meta.count=func_00117BD0(stream);
                record->meta.limit=Min(1.0e10f,record->meta.limit);
                switch(record->meta.kind){
                case 0:{
                    int index=remap[func_00117D50(stream)];
                    struct D*descriptor;
                    struct E*entry;
                    if(index<0){record->meta.kind=5;break;}
                    descriptor=&p->descriptors[index];
                    entry=&p->entries[index];
                    if(entry->flags&0x2000){record->meta.kind=3;record->link=entry->matrix;}
                    record->meta.channel=descriptor->channel;
                    record->meta.feature=(entry->flags>>12)&1;
                    record->meta.index=index;
                    entry->sphere=record;
                    break;
                }
                case 1:
                    record->link=&groups[func_00117D50(stream)];
                    break;
                }
            }
        }
        p->groups=groups;
    }
}
