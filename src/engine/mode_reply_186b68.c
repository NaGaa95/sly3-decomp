// SLY3_CFLAGS: -Os -G0
struct PromptController { unsigned char prefix[0x50]; int mode; };
struct PromptSubject { unsigned char prefix[0xB0]; int value; };
extern struct PromptController *D_004BC244;
int func_00186900(struct PromptSubject *subject);
int func_00186B68(struct PromptSubject *subject)
{
    struct PromptController *controller=D_004BC244;
    int mode=controller ? controller->mode : -1;
    switch(mode) {
    case 0:
        switch(func_00186900(subject)) {
        case 1: return 0x43F;
        case 2: return 0x441;
        case 4: return 0x443;
        case 8: return 0x445;
        case 16: return 0x447;
        case 32: return 0x449;
        case 64: return 0x44B;
        case 128: return 0x44D;
        default: return 0x44F;
        }
    case 2:
        switch(func_00186900(subject)) {
        case 1: return 0x451;
        case 2: return 0x453;
        case 64: return 0x455;
        default: return 0x451;
        }
    default:
        switch(func_00186900(subject)) {
        case 1: return 0x42D;
        case 2: return 0x42F;
        case 4: return 0x431;
        case 8: return 0x433;
        case 16: return 0x435;
        case 32: return 0x437;
        case 64: return 0x439;
        case 128: return 0x43B;
        default: return 0x43D;
        }
    }
}
#define MEMBER_OFFSET(type,member) ((unsigned int)&(((type *)0)->member))
typedef char PointerSize[(sizeof(void *)==4)?1:-1];
typedef char ControllerModeOffset[(MEMBER_OFFSET(struct PromptController,mode)==0x50)?1:-1];
typedef char SubjectValueOffset[(MEMBER_OFFSET(struct PromptSubject,value)==0xB0)?1:-1];
