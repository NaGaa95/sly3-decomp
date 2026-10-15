// SLY3_CFLAGS: -Os -G0
/* Grow two endpoint arrays and the corresponding object-pointer array. */
struct ENDPOINT {
    float coordinate;
    unsigned short entering;
    unsigned short objectIndex;
};
struct REGION_VIEW {
    char opaque0[0xE8];
    int objectCount;
    int capacity;
    int endpointCount;
    struct ENDPOINT *endpoints1;
    struct ENDPOINT *endpoints2;
    void **objects;
};
struct ALLOCATION_REQUEST {
    int bytes;
    int alignment;
};
typedef char CheckEndpoint8[(sizeof(struct ENDPOINT) == 8) ? 1 : -1];
typedef char CheckAllocationRequest8[(sizeof(struct ALLOCATION_REQUEST) == 8) ? 1 : -1];
typedef char CheckRegionPrefix100[(sizeof(struct REGION_VIEW) == 0x100) ? 1 : -1];

extern const float D_00324E4C;
extern const float D_00324E50;
void *func_001D2470(struct ALLOCATION_REQUEST *request);
void func_001D2898(void *destination, void *source, unsigned int bytes);
void *func_00292034(void *destination, int value, unsigned int bytes);

void func_001EE5C8(struct REGION_VIEW *p) {
    struct ALLOCATION_REQUEST request;
    int capacity;
    int bytes;
    struct ENDPOINT *endpoints1, *endpoints2;
    void **objects;

    /* The original handles the capacity states 0,16,128. It supplies no
       initialized replacement capacity for other states. */
    switch (p->capacity) {
    case 0:
        capacity = 0x10;
        break;
    case 0x10:
        capacity = 0x80;
        break;
    case 0x80:
        return;
    }

    bytes = capacity * 16 + 16;
    request.bytes = bytes;
    request.alignment = 0x10;
    endpoints1 = func_001D2470(&request);
    request.bytes = bytes;
    request.alignment = 0x10;
    endpoints2 = func_001D2470(&request);
    request.bytes = capacity * 4;
    request.alignment = 0x10;
    objects = func_001D2470(&request);
    func_001D2898(endpoints1, p->endpoints1, p->endpointCount * 8);
    func_001D2898(endpoints2, p->endpoints2, p->endpointCount * 8);
    func_001D2898(objects, p->objects, p->capacity * 4);
    {
        int bytesToClear = (capacity - p->capacity) * 4;
        /* The original EE code forms this 32-bit byte address explicitly. */
        unsigned int address = p->capacity * 4 + (unsigned int)objects;
        func_00292034((void *)address, 0, bytesToClear);
    }
    p->endpoints2 = endpoints2;
    p->objects = objects;
    p->capacity = capacity;
    p->endpoints1 = endpoints1;
    if (p->endpointCount == 0) {
        p->endpoints1[0].coordinate = D_00324E4C;
        p->endpoints1[0].entering = 1;
        p->endpoints1[0].objectIndex = 0xFF;
        p->endpoints1[1].coordinate = D_00324E50;
        p->endpoints1[1].entering = 0;
        p->endpoints1[1].objectIndex = 0xFF;
        p->endpoints2[0].coordinate = D_00324E4C;
        p->endpoints2[0].entering = 1;
        p->endpoints2[0].objectIndex = 0xFF;
        p->endpoints2[1].coordinate = D_00324E50;
        p->endpoints2[1].entering = 0;
        p->endpoints2[1].objectIndex = 0xFF;
        p->endpointCount = 2;
    }
}
