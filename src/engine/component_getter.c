// SLY3_CFLAGS: -Os -G0
struct EngineComponent18 { unsigned char prefix[0x18]; void *value; };
struct EngineComponentOwner18 { unsigned char prefix[0x50]; struct EngineComponent18 *component; };
void *func_001733B8(struct EngineComponentOwner18 *owner){return owner->component->value;}
