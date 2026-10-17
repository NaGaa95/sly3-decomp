// SLY3_CFLAGS: -Os -G0
struct AllocRequest { int bytes, alignment; };
struct Buffer { int unknown_0; int unknown_4; int unknown_8; int owner; int unknown_10; int capacity; int unknown_18; void *data; unsigned char inline_storage[0x400]; };
void *func_001D25B0(struct AllocRequest *request);
struct Buffer *func_0025A1A0(struct Buffer *buffer,int owner,int capacity)
{
    buffer->owner=owner;
    buffer->unknown_0=0;
    buffer->unknown_4=0;
    buffer->unknown_8=0;
    buffer->unknown_10=0;
    buffer->unknown_18=0;
    if(capacity) {
        struct AllocRequest request;
        request.bytes=buffer->capacity=capacity;
        request.alignment=0x10;
        buffer->data=func_001D25B0(&request);
    } else {
        buffer->capacity=0x400;
        buffer->data=buffer->inline_storage;
    }
    return buffer;
}
