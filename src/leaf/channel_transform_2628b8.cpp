// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct Transform { int words[8]; } __attribute__((aligned(16)));
struct Heap { virtual void *Allocate(int bytes,int kind); };
struct Frame { char prefix[0x10]; int identifier; };
struct Channel {
    unsigned short count;
    short unused;
    Frame *frames;
    char gap8[0x24];
    Transform *transform;
};
struct Owner {
    char prefix[0x70];
    unsigned short count;
    short unused;
    Channel *channels;
    char gap78[0x3C];
    Heap *heap;
};
extern "C" void func_002628B8(Owner *owner,int identifier,Transform *transform)
{
    for(int channelIndex=0;channelIndex<owner->count;channelIndex++) {
        Channel *channel=&owner->channels[channelIndex];
        for(int frameIndex=0;frameIndex<channel->count;frameIndex++) {
            Frame *frame=&channel->frames[frameIndex];
            if(frame->identifier==identifier) {
                if(!channel->transform)
                    channel->transform=(Transform *)owner->heap->Allocate(32,0x29);
                *channel->transform=*transform;
                return;
            }
        }
    }
}
