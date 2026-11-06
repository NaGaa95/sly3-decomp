// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Binds the save-game variables to their script paths (func_0021CCD0 takes a 0-terminated list of path names),
// marks the acquired power-ups, then applies the settings.
struct SAVE {
    char pad0[0x406C];
    int dt, widCurrent, episodeCurrent, episodeBest, oidCheckpointForce, widCheckpointForce, ccoin;
    int powerUps[67];
    int lang, mixerMode, musicVolume, effectsVolume, useHeadset, dxScreenCenter, dyScreenCenter, autosaveWarned;
    int worlds[40];
    int episodes[9], episodeDt[9], treasure[9];
    int sunk, captured, highScore;
};
struct JOY { int noVibration; int reverseHorizontal[7]; int reverseVertical[7]; };
struct PREFS { char pad0[0x1144]; JOY left; char pad1180[0x2304 - 0x1180]; JOY right; };
class CRef {
public:
    short m_tag;
    int m_n;
    CRef(int tag, int n) { m_tag = tag; m_n = n; }
    CRef(const CRef &ref) __asm__("func_0012AF00");
    ~CRef() { Decref(); }
    void Decref();
};
extern SAVE D_00475480;
extern PREFS D_0036E740;
extern int D_00349938[];
extern char D_00468D30[], D_0036C700[];
extern "C" {
int func_0021CCD0(const char *, ...);
void func_00271448(char *, const char *, int);
const char *func_001505D0(int);
const char *func_00150600(int);
int func_0025E150(void);
void func_0025DFB0(SAVE *, int);
void func_00184A60(void *);
}
CRef func_002BC050(int, const CRef &, void *) __asm__("func_002BC050");
static inline void SetVar(void *table, int var, const CRef &value) { CRef v(value); func_002BC050(var, v, table); }
extern "C" void func_0025B1B8(SAVE *p)
{
    char buf[0x20];
    p->dt = func_0021CCD0("dt", 0);
    p->widCurrent = func_0021CCD0("widCurrent", 0);
    p->episodeCurrent = func_0021CCD0("episodeCurrent", 0);
    p->episodeBest = func_0021CCD0("episodeBest", 0);
    p->oidCheckpointForce = func_0021CCD0("oidCheckpointForce", 0);
    p->widCheckpointForce = func_0021CCD0("widCheckpointForce", 0);
    p->ccoin = func_0021CCD0("loot", "ccoin", 0);
    for (int i = 0; i < 67; i++) {
        func_00271448(buf, "%d", i);
        p->powerUps[i] = func_0021CCD0("powerUps", "mppukfAcquired", buf, 0);
    }
    p->lang = func_0021CCD0("flags", "lang", 0);
    p->mixerMode = func_0021CCD0("flags", "nMixerMode", 0);
    p->musicVolume = func_0021CCD0("flags", "uMusicVolume", 0);
    p->effectsVolume = func_0021CCD0("flags", "uEffectsVolume", 0);
    p->useHeadset = func_0021CCD0("flags", "fUseHeadset", 0);
    p->dxScreenCenter = func_0021CCD0("flags", "dxScreenCenter", 0);
    p->dyScreenCenter = func_0021CCD0("flags", "dyScreenCenter", 0);
    p->autosaveWarned = func_0021CCD0("flags", "fAutosaveWarned", 0);
    D_0036E740.left.noVibration = func_0021CCD0("flags", "joyLeft", "fNoVibration", 0);
    D_0036E740.right.noVibration = func_0021CCD0("flags", "joyRight", "fNoVibration", 0);
    for (int j = 0; j < 7; j++) {
        func_00271448(buf, "%d", j);
        D_0036E740.left.reverseHorizontal[j] = func_0021CCD0("flags", "joyLeft", "mpcamprefkfReverseHorizontal", buf, 0);
        D_0036E740.right.reverseHorizontal[j] = func_0021CCD0("flags", "joyRight", "mpcamprefkfReverseHorizontal", buf, 0);
        D_0036E740.left.reverseVertical[j] = func_0021CCD0("flags", "joyLeft", "mpcamprefkfReverseVertical", buf, 0);
        D_0036E740.right.reverseVertical[j] = func_0021CCD0("flags", "joyRight", "mpcamprefkfReverseVertical", buf, 0);
    }
    for (int w = 0; w < 40; w++)
        p->worlds[w] = func_0021CCD0("world", func_001505D0(w), 0);
    for (int e = 0; e < 9; e++) {
        p->episodes[e] = func_0021CCD0("episode", func_00150600(e), 0);
        p->episodeDt[e] = func_0021CCD0("episode", func_00150600(e), "dt", 0);
        p->treasure[e] = func_0021CCD0("episode", func_00150600(e), "found_treasure", 0);
    }
    p->sunk = func_0021CCD0("battle", "cSunk", 0);
    p->captured = func_0021CCD0("battle", "cCaptured", 0);
    p->highScore = func_0021CCD0("hack_multi", "nHighScore", 0);
    for (unsigned int k = 0; k < 9; k++) {
        int var = D_00475480.powerUps[D_00349938[k]];
        if (var) {
            CRef value(0x15, 1);
            SetVar(D_00468D30, var, value);
        }
    }
    func_0025DFB0(p, func_0025E150());
    func_00184A60(D_0036C700);
}
