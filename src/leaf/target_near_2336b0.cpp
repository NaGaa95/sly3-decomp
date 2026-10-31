// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Report whether the target object is within the radius of this object: squared distance between the two actor positions
// (virtual slot 36 matrices, translation rows) against the radius squared.
#include "../P2/scene.h"
#include "../P2/state_position_ops.h"
struct ActorMatrix { qword row[4]; };
struct Seeker { SCENE_OBJECT scene; unsigned char gap[0x13C-sizeof(SCENE_OBJECT)]; SCENE_OBJECT *target; unsigned char gap140[0x2BC-0x140]; float radius; };
static inline qword Position(SCENE_OBJECT *object)
{
    SCENE_VIRTUAL_ENTRY *entry=&object->vtable[36];
    return ((ActorMatrix *(*)(void *))entry->Simple)((char *)object+entry->delta)->row[3];
}
static inline float SquaredLengthXYZ(qword difference)
{
    qword one;
    float result;
    asm("vmul.xyz %0,%0,%0
	vaddw.x %1,$vf0,$vf0w
	vadday.x $ACC,%0,%0y
	vmaddz.x %0,%1,%0z"
        : "+j"(difference), "=&j"(one));
    asm("mtc1 %1,%0" : "=f"(result) : "r"(difference));
    return result;
}
extern "C" int func_002336B0(Seeker *seeker)
{
    int result=0;
    if(seeker->target) {
        qword first;
        register qword second __asm__("vf2"); /* register pin: second position lives in vf2 */
        qword difference;
        float radius;
        first=Position(&seeker->scene);
        second=Position(seeker->target);
        radius=seeker->radius;
        asm("vsub.xyzw %0,%1,%2" : "=j"(difference) : "j"(first), "j"(second));
        if(SquaredLengthXYZ(difference)<radius*radius)
            result=1;
    }
    return result;
}
