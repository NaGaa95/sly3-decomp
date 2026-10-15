// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions -fno-rtti
// Original startup entry points invoke their independently indexed pool
// initializer with initialize=1 and priority=65535.
extern "C" void func_00118308(int initialize, int priority);
extern "C" void func_00118A90(int initialize, int priority);
extern "C" void func_00119FA0(int initialize, int priority);
extern "C" void func_0011A778(int initialize, int priority);
extern "C" void func_0011BBF0(int initialize, int priority);
extern "C" void func_0011C560(int initialize, int priority);
extern "C" void func_0011FC10(int initialize, int priority);
extern "C" void func_00137738(int initialize, int priority);
extern "C" void func_0013B398(int initialize, int priority);
extern "C" void func_00162900(int initialize, int priority);
extern "C" void func_00174B00(int initialize, int priority);
extern "C" void func_00180630(int initialize, int priority);
extern "C" void func_002380B8(int initialize, int priority);
extern "C" void func_00288A48(int initialize, int priority);

#define DEFINE_POOL_STARTUP(name, initializer) \
extern "C" void name(void) \
{ \
    initializer(1, 65535); \
}

DEFINE_POOL_STARTUP(func_00118440, func_00118308)
DEFINE_POOL_STARTUP(func_00118BC8, func_00118A90)
DEFINE_POOL_STARTUP(func_0011A0D8, func_00119FA0)
DEFINE_POOL_STARTUP(func_0011A8B0, func_0011A778)
DEFINE_POOL_STARTUP(func_0011BD28, func_0011BBF0)
DEFINE_POOL_STARTUP(func_0011C698, func_0011C560)
DEFINE_POOL_STARTUP(func_0011FD48, func_0011FC10)
DEFINE_POOL_STARTUP(func_00137870, func_00137738)
DEFINE_POOL_STARTUP(func_0013B4D0, func_0013B398)
DEFINE_POOL_STARTUP(func_00162A38, func_00162900)
DEFINE_POOL_STARTUP(func_00174C38, func_00174B00)
DEFINE_POOL_STARTUP(func_00180768, func_00180630)
DEFINE_POOL_STARTUP(func_002381F0, func_002380B8)
DEFINE_POOL_STARTUP(func_00288B80, func_00288A48)
