// SLY3_CFLAGS: -Os -G0
typedef int Quad __attribute__((mode(TI)));
struct LightPayload { unsigned char bytes[0x30]; };
struct LightObject { unsigned char prefix[0x70]; unsigned char light[0x9C]; void *payload; };
struct LightSelf {
    unsigned char prefix[0x310]; int count; struct LightObject *objects[4];
    int entries; unsigned char values[1];
};
extern unsigned char D_00475480[];
void *func_00292034(void *destination, int value, unsigned int bytes);
void func_001C8238(void *self);
int func_00168DD8(void *self);
void func_001C6B90(void *game, int count, void *values, struct LightPayload *payload);
int func_00165B48(void *game, void *item);
Quad func_001C8548(int index);
void func_0023CBE0(void *object);
void func_0018E800(void *light, Quad color, void *matrix, float scale, float intensity, void *payload);
void func_00168CC0(struct LightSelf *self)
{
    struct LightPayload buffer;
    func_001C8238(self);
    if(func_00168DD8(self)) {
        struct LightPayload *payload;
        int index;
        if(self->entries > 0) {
            func_00292034(&buffer, 0, sizeof(buffer));
            payload = &buffer;
            func_001C6B90(D_00475480, self->entries, self->values, &buffer);
        } else {
            payload = 0;
        }
        index = func_00165B48(D_00475480, self);
        if(index >= 0) {
            Quad color = func_001C8548(index);
            int i;
            for(i = 0; i < self->count; i++) {
                struct LightObject *object = self->objects[i];
                void *use = payload;
                if(!use) {
                    func_0023CBE0(object);
                    use = object->payload;
                }
                func_0018E800(object->light, color, 0, 1.0f, 1.0f, use);
            }
        }
    }
}
