// SLY3_CFLAGS: -Os -G0
struct EngineComponent04 { unsigned char prefix[4]; void *value; };
struct EngineComponentOwner04 { unsigned char prefix[0x50]; struct EngineComponent04 *component; };
void *func_001733F8(struct EngineComponentOwner04 *owner){return owner->component->value;}
