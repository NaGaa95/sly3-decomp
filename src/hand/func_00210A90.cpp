// Advance actual rumble pattern timers, wrap the instruction index and dispatch the two unsigned motor bytes.
// Sly3 uses its local availability-checking motor wrapper, which initializes all six SDK actuator bytes.
// Receiver A0 is the only incoming input; clock+44 is loaded locally, not an incoming scalar.
// The two policy fields at1C/20 are verified by the real transitive availability helper.
// SLY3_CFLAGS: -Os -G0 -fno-exceptions
// Real clock field44 and local motor helper receiver/highbyte/lowbyte; no buffer bypass or SDK source ownership.
typedef unsigned char byte;
/* Sly 2 order differs from Sly 1: (rums == Stop) yields 1 */ enum RUMS {
    RUMS_Nil = -1, RUMS_Dead = 0, RUMS_Idle = 1, RUMS_Rumble = 2, RUMS_Stop = 3, RUMS_Kill = 4
};
struct RUMINS {
    byte fHighSpeedMotor;
    byte bLowSpeedMotor;
    float dt;
};
struct RUMPAT {
    int crumins;
    RUMINS arumins[32];
};
struct KEY;
struct RUMBLE {
    int nPort;
    int nSlot;
    RUMS rums;
    RUMPAT *prumpat;
    int irumins;
    float dtRumble;
    float dtRumins;
    int availabilityMode;
    KEY *availabilityKey;
};
struct CLOCK {
    unsigned char opaque0[0x44];
    float realDelta;
};
extern CLOCK D_0036BB98;
extern "C" void func_00210D78(RUMBLE *, byte, byte);
extern "C" void func_00210C90(RUMBLE *prumble, RUMS rums);
extern "C" void func_00210D58(RUMBLE *prumble);
extern "C" void func_00210A90(RUMBLE *prumble) {
    float dtReal = D_0036BB98.realDelta;
    switch (prumble->rums) {
        case RUMS_Rumble: if (prumble->dtRumble > 0.0f) {
            prumble->dtRumins -= dtReal;
            if (prumble->dtRumins <= 0.0f) {
                if (++prumble->irumins >= prumble->prumpat->crumins) prumble->irumins = 0;
                func_00210D78(prumble, prumble->prumpat->arumins[prumble->irumins].fHighSpeedMotor, prumble->prumpat->arumins[prumble->irumins].bLowSpeedMotor);
                prumble->dtRumins = prumble->prumpat->arumins[prumble->irumins].dt;
            }
            prumble->dtRumble -= dtReal;
        }
        else {
            func_00210C90(prumble, RUMS_Stop);
        }
        break;
        case RUMS_Stop: case RUMS_Kill: if (prumble->dtRumins > 0.0f) {
            func_00210D58(prumble);
            prumble->dtRumins -= dtReal;
        }
        else {
            func_00210C90(prumble, (prumble->rums == RUMS_Stop) ? RUMS_Idle : RUMS_Dead);
        }
        break;
        default: return;
    }
}
