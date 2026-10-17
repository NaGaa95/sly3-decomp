// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct ReadMatrix { Quad row[4]; };
struct ReadVector { float v[4]; } __attribute__((aligned(16)));
struct ReadSelf { struct ReadMatrix local; struct ReadMatrix world; struct ReadVector position; };
extern unsigned char D_00317490[];
void func_001192D8(void *stream, void *vector);
void func_0011D660(struct ReadMatrix *matrix, Quad position, void *table, float *scale);
void func_0011D768(struct ReadMatrix *matrix, struct ReadMatrix *output);
void func_00195028(struct ReadSelf *self, void *stream)
{
    struct ReadVector direction;
    struct ReadVector extent;
    float scale[3];
    struct ReadVector position;
    struct ReadMatrix matrix;
    int i;
    float range;
    func_001192D8(stream, &self->position);
    func_001192D8(stream, &direction);
    func_001192D8(stream, &extent);
    range = 32439.330078125f;
    for(i = 0; i < 3; i++) {
        float value = extent.v[i];
        if(value < 0.01f) scale[i] = 1.0f;
        else scale[i] = value * 16.0f / range;
    }
    position = self->position;
    func_0011D660(&matrix, *(Quad *)&position, D_00317490, scale);
    self->world = matrix;
    func_0011D768(&matrix, &self->world);
    self->local = matrix;
}
