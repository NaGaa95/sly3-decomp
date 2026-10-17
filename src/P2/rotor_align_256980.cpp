// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "mat.h"
#include "state_position_ops.h"
#include "matrix_algorithms.h"
struct SCENE_OBJECT;
struct Channel { char prefix[0x30]; qword value; char gap40[0x60]; MATRIX4 *transform; };
struct Owner { char prefix[0x80]; qword direction; Channel *channel; };
struct Rotor { char prefix[0x20]; qword rotation; };
struct Follower { char prefix[0x1084]; Owner *owner; Rotor *rotor; SCENE_OBJECT *source; qword point; };
extern "C" {
qword func_0028E910(SCENE_OBJECT *source, MATRIX4 *destination, qword point);
void func_0011CDC8(MATRIX3 *output, qword from, qword to);
void func_00256980(Follower *follower)
{
    MATRIX3 matrix;
    qword position = func_0028E910(follower->source, follower->owner->channel->transform, follower->point);
    func_0011CDC8(&matrix, follower->owner->direction, PackedDifference(position, follower->owner->channel->value));
    Rotor *rotor = follower->rotor;
    rotor->rotation = func_0011D3C0(&matrix);
}
}
