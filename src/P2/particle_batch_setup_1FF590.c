// SLY3_CFLAGS: -Os -G0 -mvu0-use-vf0-vf31
typedef int qword __attribute__((mode(TI)));
struct ParticleBatch {
    int count;
    qword *position, *velocity;
    float *birth, *death;
};
struct SetupAllocation { int bytes, alignment; };
struct SetupMethod { short delta, reserved; void (*function)(void *, struct ParticleBatch *); };
struct SetupTable { unsigned char prefix[0x10]; struct SetupMethod apply; };
struct SetupParticles { unsigned char prefix[0x40]; struct SetupTable *table; };
void *func_001D2770(void *receiver);
void func_001D2798(void *receiver, int flags);
void *func_001D25B0(struct SetupAllocation *request);
void func_001FF6B0(void *particles, struct ParticleBatch *batch);
void func_001FFC20(void *particles, struct ParticleBatch *batch);
void func_002001C0(void *particles, struct ParticleBatch *batch);
void func_00200328(void *particles, struct ParticleBatch *batch);

static inline struct SetupAllocation *setup_request(struct SetupAllocation *request, int bytes, int alignment)
{
    request->bytes = bytes;
    request->alignment = alignment;
    return request;
}

void func_001FF590(struct SetupParticles *particles, int count)
{
    struct ParticleBatch batch;
    unsigned char frame[16];
    struct SetupAllocation request;
    if (count) {
        func_001D2770(frame);
        batch.count = count;
        batch.position = func_001D25B0(setup_request(&request, count * 16, 16));
        batch.velocity = func_001D25B0(setup_request(&request, count * 16, 16));
        batch.birth = func_001D25B0(setup_request(&request, count * 4, 16));
        batch.death = func_001D25B0(setup_request(&request, count * 4, 16));
        func_001FF6B0(particles, &batch);
        func_001FFC20(particles, &batch);
        func_002001C0(particles, &batch);
        func_00200328(particles, &batch);
        particles->table->apply.function((char *)particles + particles->table->apply.delta, &batch);
        func_001D2798(frame, 2);
    }
}
