// SLY3_CFLAGS: -Os -G0
struct EngineWorldView { unsigned char prefix[0x134]; void *current; };
struct EngineWorldOwner { unsigned char prefix[0x10]; struct EngineWorldView *world; };
void *func_0015F908(struct EngineWorldOwner *owner){return owner->world->current;}
