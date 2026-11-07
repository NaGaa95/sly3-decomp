// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// func_002405F8: copy geometry with inserted zeroed vertices, retransform and rebase its tree (Sly 3: radius copied, no recompute).
typedef int qword __attribute__((mode(TI)));
union U {qword q;float f[4];};
struct M4 {U rows[4];M4(){}M4(const M4&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];rows[3]=m.rows[3];}M4&operator=(const M4&m){rows[0]=m.rows[0];rows[1]=m.rows[1];rows[2]=m.rows[2];rows[3]=m.rows[3];return *this;}};
struct LO {char pad40[0x40];M4 matrix;};
struct GEO {int count;qword *points;int planeCount;void *planes;int x10,x14;};
struct TREE {int count,flag,unused;void *nodes;};
struct P {LO *owner;int flags;float radius;char pad0C[4];int material;char pad14[0xC];int pinnedCount;char pad24[0x54];TREE tree;GEO local,world;};
struct FRAME {int pad[4];};
extern "C" FRAME *__5FRAME(FRAME *);
extern "C" void _$_5FRAME(FRAME *,int);
struct MSG {int bytes,alignment;};
extern "C" void *func_001D2670(MSG *);
extern "C" void CopyAb(void *,const void *,unsigned int) asm("func_001D2898");
extern "C" M4 *func_0011D768(M4 *,const M4 *);
extern "C" M4 *func_0011D558(M4 *,const M4 *,const M4 *);
extern "C" void func_0018AFB0(GEO *,const M4 *,GEO *);
extern "C" void func_00119D00(TREE *,GEO *,TREE *,GEO *);

static inline float SquaredLength(qword a){qword one;float f;__asm__("vmul.xyz %0,%0,%0\n\tvaddw.x %1,$vf0,$vf0w\n\tvadday.x ACC,%0,%0y\n\tvmaddz.x %0,%1,%0z":"+j"(a),"=&j"(one));__asm__("mtc1 %1,%0":"=f"(f):"r"(a));return f;}
/* volatile: the game's sqrt.s is a barrier for the scheduler (the radius store must precede the next constant). */
static inline float Sqrt(float f){float r;__asm__ volatile("sqrt.s %0,%1":"=f"(r):"f"(f));return r;}
extern "C" void func_002405F8(P *source,LO *space,int inserted,P *dest)
{
    M4 transform;
    GEO temporary;
    FRAME frame;
    __5FRAME(&frame);
    MSG request;MSG *allocation=&request;
    dest->owner=space;dest->flags=source->flags;dest->material=source->material;dest->pinnedCount=source->pinnedCount;
    dest->radius=source->radius;
    temporary=source->local;
    request.bytes=(temporary.count+inserted)*16;allocation->alignment=16;
    qword *points=(qword *)func_001D2670(allocation);
    int pinned=source->pinnedCount;
    CopyAb(points,temporary.points,pinned*16);
    CopyAb(points+(pinned+inserted),temporary.points+pinned,(temporary.count-pinned)*16);
    temporary.count+=inserted;temporary.points=points;
    {M4 product,inverse;func_0011D558(&product,(func_0011D768(&inverse,&space->matrix),&inverse),&source->owner->matrix);transform=product;}
    func_0018AFB0(&temporary,&transform,&dest->local);
    func_0018AFB0(&dest->local,&space->matrix,&dest->world);
    func_00119D00(&source->tree,&source->world,&dest->tree,&dest->world);
    _$_5FRAME(&frame,2);
}
