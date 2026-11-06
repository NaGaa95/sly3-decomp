// SLY3_CFLAGS: -Os -G0 -fno-exceptions -fno-rtti
// Write the card icon buffer (memcard_icon.ico) into the save directory `name` in chunks of up to 0x1000 bytes.
#include "heap_frame_api.h"
class CardFrame {
public:
    CardFrame() __asm__("func_001D2770");
    ~CardFrame() { func_001D2798(this, 2); }
};
static inline int Minimum(int first, int second)
{
    return first < second ? first : second;
}
static const char kIconName[] = "memcard_icon.ico";
static const char kPathFormat[] = "%s/%s";
extern "C" {
extern char D_00317FE0[];
int func_001CF7A0(void);
int func_001D0860(void *save, const char *path, int mode, int *descriptor);
int func_001D0970(void *save, int descriptor, void *buffer, int bytes, int *written);
int func_001D08C8(void *save, int descriptor);
int func_00271448(char *path, const char *format, ...);
int func_001D02D0(void *save, char *name)
{
    CardFrame frame;
    char path[0x50];
    int handle;
    int written;
    int result;
    func_00271448(path, kPathFormat, name, kIconName);
    handle = -1;
    result = func_001D0860(save, path, 0x202, &handle);
    if (result)
        return result;
    {
        int remaining = func_001CF7A0();
        int offset = 0;
        int chunk;
        while ((chunk = Minimum(0x1000, remaining)) != 0) {
            result = func_001D0970(save, handle, D_00317FE0 + offset, chunk, &written);
            if (result)
                goto done;
            if (written != chunk) {
                result = 7;
                goto done;
            }
            offset += chunk;
            remaining -= chunk;
        }
        result = 0;
    done:
        {
            int closed = func_001D08C8(save, handle);
            if (!result)
                result = closed;
        }
    }
    return result;
}
}
