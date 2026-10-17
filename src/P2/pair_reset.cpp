// SLY3_CFLAGS: -Os -G0 -fno-exceptions
#include "scene.h"
struct PairHolder {
    char prefix[0x25C];
    int word25C;
    char pad260[0x26C-0x260];
    SCENE_OBJECT *first,*second;
    int word274,word278;
};
extern "C" void func_00279998(SCENE_OBJECT *object);
extern "C" void func_00278D68(PairHolder *holder)
{
    func_00279998(holder->first);
    func_00279998(holder->second);
    CallScene(holder->first,9);
    CallScene(holder->second,9);
    holder->word278=0;
    holder->word274=0;
    holder->word25C=0;
}
