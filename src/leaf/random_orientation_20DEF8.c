// SLY3_CFLAGS: -Os -G0
// Give the object a random orientation: a direction with x,y in [-1,1] and z in [0.1,1.0], turned into a 3-row basis.
typedef int qword __attribute__((mode(TI)));
struct Matrix { qword rows[3]; };
union Direction { qword packed; struct { float x, y, z; } v; };
struct OrientedObject {
    unsigned char prefix[0x40];
    qword rows[3];
};
void func_0020BDA8(struct OrientedObject *self);
float func_0011E940(float low, float high);
struct Matrix *func_0011CBA0(struct Matrix *destination, qword direction);
void func_0020DEF8(struct OrientedObject *self)
{
    union Direction direction;
    struct Matrix matrix;
    float x, y, z;
    func_0020BDA8(self);
    x = func_0011E940(-1.0f, 1.0f);
    y = func_0011E940(-1.0f, 1.0f);
    z = func_0011E940(0.1f, 0.9f) + 0.1f;
    direction.v.x = x;
    direction.v.y = y;
    direction.v.z = z;
    func_0011CBA0(&matrix, direction.packed);
    self->rows[0] = matrix.rows[0];
    self->rows[1] = matrix.rows[1];
    self->rows[2] = matrix.rows[2];
}
