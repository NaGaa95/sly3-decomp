// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
#include "../P2/heap.h"
struct ArchiveLocalizedKeyGame {
    byte beforeAvailableKeys[0x4E5C];
    const unsigned short *availableKeys;
};
extern "C" int func_0014FEB0(ArchiveLocalizedKeyGame *game,int key) {
    unsigned short narrowedKey=(unsigned short)key;
    if(!game->availableKeys) return 1;
    int lower=0;
    int upper=CchzWide(game->availableKeys)-1;
    while(lower<=upper) {
        int middle=(upper+lower)/2;
        int difference=narrowedKey-game->availableKeys[middle];
        if(!difference) return 1;
        if(difference>0) lower=middle+1;
        else upper=middle-1;
    }
    return 0;
}
