// SLY3_CFLAGS: -Os -G0
typedef int qword __attribute__((mode(TI)));
typedef struct { qword r[3]; } M3;
typedef union { struct { qword r[4]; } q; M3 m3; float af[4][4]; } M4;
struct Clock { float now; float step; };
struct Sound { unsigned char prefix[0x5A]; short state; };
struct Limits { float min; float max; };
struct CameraFollow {
    void *owner;
    unsigned char gap04[0x28 - 0x04];
    float blendTarget;
    unsigned char gap2C[0x30 - 0x2C];
    qword vec30;
    qword vec40;
    void *mode50;
    unsigned char gap54[0x60 - 0x54];
    qword euler60;
    qword euler70;
    float g80;
    unsigned char gap84[0x90 - 0x84];
    qword euler90;
    qword eulerA0;
    float gB0;
    float gB4;
    float gB8;
    float blend;
    float blendRate;
    unsigned char gapC4[0xC8 - 0xC4];
    float blendFrom;
    float blendTo;
    struct Sound *sound;
};
extern struct Clock D_0036BB98;
extern unsigned char D_00320EB8[], D_00320EC8[], D_00320ED8[], D_00320EE8[], D_00320EF8[];
extern struct Limits D_00341FF0, D_00341FF8;
void func_00169E78(struct CameraFollow *self);
float func_0011E598(float current, float desired, const void *curve, int mode, float step);
float func_0011EE68(struct Limits *limits, float value);
void func_00244ED0(struct Sound *sound, float value);
void func_00244E08(struct Sound *sound, float value);
void func_00244C70(struct Sound *sound);
void func_00244C28(struct Sound *sound);
qword func_00120C80(qword current, qword target, const void *table, int mode, float step);
void func_0011C9E8(M3 *matrix, qword angles);
void func_0011DDA8(M3 *first, M3 *second, const void *table, M3 *out, int mode, float step);
qword func_0011D3C0(M3 *matrix);
float func_0011E840(float current, float target, float step, const void *table, int mode);
qword *func_002BA818(qword *out, qword value);
void func_00166DE8(void *owner, M4 *matrix);
void func_00167960(void *owner, float value);
void func_0011D048(M4 *matrix, float *pan, float *tilt);
qword func_0016A7E8(struct CameraFollow *self);
qword func_0016A750(struct CameraFollow *self);
void func_00166E48(void *owner, qword first, qword second, float a, float b);
void func_00168670(void *owner, int mode);

static __inline__ float Clamp(float value, float low, float high)
{
    if(value < low) return low;
    if(high < value) return high;
    return value;
}

static __inline__ float Fraction(float value, float from, float to)
{
    if(from == to) return 0.0f;
    return (value - from) / (to - from);
}

void func_0016AA20(struct CameraFollow *self)
{
    func_00169E78(self);
    if(D_0036BB98.step == 0.0f) return;
    if(0.0f <= self->blendTarget) {
        float blend = Clamp(func_0011E598(self->blend, self->blendTarget, D_00320EB8, 0, D_0036BB98.step), 0.0f, 1.0f);
        self->blendRate = (blend - self->blend) / D_0036BB98.step;
        self->blend = blend;
    }
    if(self->blendRate != 0.0f) {
        struct Sound *sound = self->sound;
        func_00244ED0(sound, func_0011EE68(&D_00341FF8, __builtin_fabsf(self->blendRate)));
        sound = self->sound;
        func_00244E08(sound, func_0011EE68(&D_00341FF0, __builtin_fabsf(self->blendRate) * 0.5f + 0.5f));
        if(self->sound->state > 0) func_00244C70(self->sound);
    } else {
        if(self->sound->state <= 0) func_00244C28(self->sound);
    }
    if(self->mode50) {
        M3 m0, m30, m60, m90;
        M4 m4;
        self->euler60 = func_00120C80(self->euler60, self->euler90, D_00320EC8, 0, D_0036BB98.step);
        func_0011C9E8(&m90, self->euler70);
        m0 = m90;
        func_0011C9E8(&m90, self->eulerA0);
        m30 = m90;
        func_0011DDA8(&m0, &m30, D_00320ED8, &m60, 0, D_0036BB98.step);
        self->euler70 = func_0011D3C0(&m60);
        self->g80 = func_0011E840(self->g80, self->gB0, D_0036BB98.step, D_00320EE8, 0);
        {
            M4 *pm4 = &m4;
            func_002BA818(&pm4->q.r[3], self->euler60);
            pm4->q.r[0] = m60.r[0];
            pm4->q.r[1] = m60.r[1];
            pm4->q.r[2] = m60.r[2];
            m4.af[2][3] = 0.0f;
            m4.af[1][3] = 0.0f;
            m4.af[0][3] = 0.0f;
            pm4->af[3][3] = 1.0f;
            func_00166DE8(self->owner, pm4);
            func_00167960(self->owner, self->g80);
            func_0011D048(pm4, &self->gB4, &self->gB8);
        }
        self->blend = func_0011EE68(&D_00341FF0, Fraction(self->g80, self->blendFrom, self->blendTo));
    } else {
        float u = 1.0f - self->blend;
        func_00167960(self->owner, (1.0f - u) * self->blendFrom + u * self->blendTo);
        {
            qword old = self->vec40;
            self->vec40 = func_00120C80(old, func_0016A7E8(self), D_00320EF8, 0, D_0036BB98.step);
        }
        {
            qword old = self->vec30;
            self->vec30 = func_00120C80(old, func_0016A750(self), D_00320EF8, 0, D_0036BB98.step);
        }
        func_00166E48(self->owner, self->vec40, self->vec30, 0.0f, 0.0f);
    }
    func_00168670(self->owner, 2);
}
