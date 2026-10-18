// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
struct Point { float x,y,z; char tail[0xC]; };
struct Record { char data[0x14]; };
struct Link { struct Record *record; char gap4[8]; struct Link *next; };
struct Mesh {
    char prefix[0xAC]; struct Record *records;
    char gapB0[4]; struct Point *points;
    char gapB8[0x14]; struct Link *links;
};
float func_002BC420(qword *);
float func_002BC430(qword *);
float func_002BC448(qword *);
void func_0026EC80(struct Mesh *self,qword position)
{
    struct Link *link;
    for(link=self->links;link;link=link->next) {
        struct Point *point=(struct Point *)((link->record-self->records)*sizeof(struct Point)+(int)self->points);
        qword temporary=position;
        float x=func_002BC420(&temporary);
        float y=func_002BC430(&temporary);
        float z=func_002BC448(&temporary);
        point->x=x;
        point->y=y;
        point->z=z;
    }
}
typedef char RecordSize[(sizeof(struct Record)==0x14)?1:-1];
typedef char PointSize[(sizeof(struct Point)==0x18)?1:-1];
