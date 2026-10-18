// SLY3_CFLAGS: -Os -G0
struct PromptController { unsigned char prefix[0x50]; int mode; };
struct PromptSubject { unsigned char prefix[0xB0]; int value; };
extern struct PromptController *D_004BC244;
int func_00186900(struct PromptSubject *subject);
int func_00186930(struct PromptSubject *subject)
{
    struct PromptController *controller=D_004BC244;
    int mode=controller ? controller->mode : -1;
    switch(mode) {
    case 0:
        switch(func_00186900(subject)) {
        case 1: return 0x43E;
        case 2: return 0x440;
        case 4: return 0x442;
        case 8: return 0x444;
        case 16: return 0x446;
        case 32: return 0x448;
        case 64: return 0x44A;
        case 128: return 0x44C;
        default: return 0x44E;
        }
    case 2:
        switch(func_00186900(subject)) {
        case 1: return 0x450;
        case 2: return 0x452;
        case 64: return 0x454;
        default: return 0x450;
        }
    default:
        switch(func_00186900(subject)) {
        case 1: return 0x42C;
        case 2: return 0x42E;
        case 4: return 0x430;
        case 8: return 0x432;
        case 16: return 0x434;
        case 32: return 0x436;
        case 64: return 0x438;
        case 128: return 0x43A;
        default: return 0x43C;
        }
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char ControllerModeOffset[(MEMBER_OFFSET(struct PromptController,mode)==0x50)?1:-1];
typedef char SubjectValueOffset[(MEMBER_OFFSET(struct PromptSubject,value)==0xB0)?1:-1];
