// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Port of Sly 2 src/hand/func_002048C8.c (breadth-first polygon adjacency search).
typedef int qword __attribute__((mode(TI)));
typedef unsigned short ushort;
union V {qword q;float f[4];};
struct E {ushort vertices[2],faces[2];struct E *next0,*next1;};
struct POLY {float normal[3];int unknown;struct E *head0,*head1;int flags,pad;};
struct MESH {int x0;qword *positions;int unknown;struct POLY *polygons;};
struct GH {char pad[0xA4];int stamp;};
struct GEOM {struct GH *head;char pad4[0xA0-4];struct MESH m;char padB0[0xC0-0xB0];int stamp;};
struct P {char pad[0x220];float height;char pad224[0x268-0x224];float previous;};
void func_00120A00(qword,qword,qword,qword *,float *,float *);
void func_0018B1E0(struct GEOM *);
static __inline__ float Z(qword q){float f;__asm__("pextuw %0,$zero,%1":"=r"(f):"r"(q));return f;}
int func_0024EC28(struct P *p,qword position,struct GEOM *g,struct POLY *first)
{
    struct POLY *queue[32];
    union V closest;
    float distance;
    int count=1,current;
    float delta,limit;
    struct MESH *m;
    queue[0]=first;
    if(g->stamp!=g->head->stamp)func_0018B1E0(g);
    m=&g->m;
    current=0;
    delta=p->height-p->previous;
    limit=delta*1.45f;
    do {
        struct POLY *poly=queue[current];
        int side;
        for(side=0;side<2;side++){
            struct E *edge;
            if(!side)edge=poly->head0;else edge=poly->head1;
            while(edge){
                func_00120A00(position,m->positions[edge->vertices[0]],m->positions[edge->vertices[1]],&closest.q,0,&distance);
                if(limit<distance)goto next;
                if(Z(position)+delta<closest.f[2])goto next;
                {
                    struct POLY *neighbor=&m->polygons[edge->faces[1-side]];
                    int j;struct POLY **pp;
                    if(0.7f<neighbor->normal[2])return 1;
                    for(j=0,pp=queue;;pp++,j++){
                        if(j>=count){
                            if((unsigned)count<32)queue[count++]=neighbor;
                            break;
                        }
                        if(neighbor==*pp)break;
                    }
                }
            next:
                if(!side)edge=edge->next0;else edge=edge->next1;
            }
        }
    }while(++current<count);
    return 0;
}
