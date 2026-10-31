// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Switch the rumble channel to a new state (Sly 2 SetRumbleRums): starting a pattern sends its first motor bytes, stop/kill
// silence the actuators and arm a short wind-down timer.
typedef unsigned char byte;
enum RUMS { RUMS_Dead = 0, RUMS_Idle = 1, RUMS_Rumble = 2, RUMS_Stop = 3, RUMS_Kill = 4, RUMS_Muted = 5 };
struct RUMINS { byte fHighSpeedMotor; byte bLowSpeedMotor; float dt; };
struct RUMPAT { int crumins; RUMINS arumins[32]; };
struct RUMBLE {
    int nPort;
    int nSlot;
    RUMS rums;
    RUMPAT *prumpat;
    int irumins;
    float dtRumble;
    float dtRumins;
};
struct CLOCK { unsigned char opaque0[0x44]; float realDelta; };
extern CLOCK D_0036BB98;
extern "C" void func_00210D78(RUMBLE *, byte, byte);
extern "C" void func_00210D58(RUMBLE *prumble);
extern "C" void func_00210C90(RUMBLE *prumble, RUMS rums)
{
    if (rums == prumble->rums)
        return;
    if (prumble->rums == RUMS_Muted)
        func_00210D78(prumble, 0, 0);
    switch (rums) {
    case RUMS_Rumble:
        func_00210D78(prumble, prumble->prumpat->arumins[0].fHighSpeedMotor, prumble->prumpat->arumins[0].bLowSpeedMotor);
        prumble->rums = rums;
        break;
    case RUMS_Muted:
        func_00210D78(prumble, 0, 0);
        prumble->rums = rums;
        break;
    case RUMS_Stop:
    case RUMS_Kill:
        func_00210D58(prumble);
        prumble->dtRumins = D_0036BB98.realDelta * 4.0f;
    case RUMS_Dead:
    case RUMS_Idle:
    default:
        prumble->rums = rums;
        break;
    }
}
