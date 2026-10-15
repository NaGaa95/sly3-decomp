// Look up the actual incoming integer resource ID, allocate from the original fixed pool with caller-derived unused size30, construct the receiver, and install owner/resource pointers before returning it.
// Reference algorithm: src/hand/func_00139318.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Result {char prefix[0x20];void *owner;void *resource;};
void *func_0023F3B8(void *receiver,int identifier);
void *func_001C9A50(unsigned int requested_bytes);
struct Result *func_002BF328(void *receiver);
struct Result *func_00241EA8(void *owner,int identifier){void *resource=func_0023F3B8(owner,identifier);if(resource){struct Result *result=func_002BF328(func_001C9A50(0x30));result->owner=owner;result->resource=resource;return result;}return 0;}
