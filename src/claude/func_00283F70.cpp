// SLY3_CFLAGS: -Os -G0 -ffast-math -mvu0-use-vf0-vf31 -fno-exceptions
// Copies the persistent settings (loot, battle, options, joystick preferences and two of the player's values) from
// the save variables into the object's variable table, then restores the save's current level descriptor.
struct LEVEL { char bytes[0x40]; };
struct SAVE {
    char pad0[0x4084];
    void *ccoin;
    char pad4088[0x4198 - 0x4088];
    void *mixerMode, *musicVolume, *effectsVolume, *useHeadset, *dxScreenCenter, *dyScreenCenter, *autosaveWarned;
    char pad41B4[0x42C0 - 0x41B4];
    void *sunk, *captured, *highScore;
    char pad42CC[0x4390 - 0x42CC];
    int levelSet;
    int levelKind;
    LEVEL level;
    int levelSize;
};
struct JOY { void *noVibration; void *reverseHorizontal[7]; void *reverseVertical[7]; };
struct PREFS { char pad0[0x1144]; JOY left; char pad1180[0x2304 - 0x1180]; JOY right; };
struct PLAYER { char pad0[0xA8]; int fieldA8; char padAC[4]; int fieldB0; };
struct P { char pad0[0x14]; PLAYER *player; char pad18[0x1C]; void *level; char table[0x7CD0 - 0x38]; int override; };
class CRef {
public:
    short m_tag;
    int m_n;
    CRef(const CRef &ref) __asm__("func_0012AF00");
    ~CRef() { Decref(); }
    void Decref();
};
extern SAVE D_00475480;
extern PREFS D_0036E740;
extern char D_00468D30[];
extern int D_0036DBA0;
extern "C" {
int func_002852B0(P *);
void func_00284568(P *);
int func_0025AE28(SAVE *);
LEVEL *func_0025E070(void *);
void func_00289070(SAVE *, LEVEL *, int, int, int);
void *memset(void *, int, unsigned int);
}
CRef func_002BC010(void *, void *) __asm__("func_002BC010");
CRef func_002BC050(void *, const CRef &, void *) __asm__("func_002BC050");
static inline void Copy2(void *var, const CRef &value, void *table) { func_002BC050(var, value, table); }
static inline void Copy(void *var, void *table, void *source)
{
    CRef value = func_002BC010(var, source);
    Copy2(var, value, table);
}

extern "C" void func_00283F70(P *p)
{
    if (!func_002852B0(p))
        return;
    void *table = p->table;
    Copy(D_00475480.ccoin, table, D_00468D30);
    Copy(D_00475480.captured, table, D_00468D30);
    Copy(D_00475480.sunk, table, D_00468D30);
    Copy(D_00475480.highScore, table, D_00468D30);
    Copy(D_00475480.mixerMode, table, D_00468D30);
    Copy(D_00475480.musicVolume, table, D_00468D30);
    Copy(D_00475480.effectsVolume, table, D_00468D30);
    Copy(D_00475480.useHeadset, table, D_00468D30);
    Copy(D_00475480.dxScreenCenter, table, D_00468D30);
    Copy(D_00475480.dyScreenCenter, table, D_00468D30);
    Copy(D_00475480.autosaveWarned, table, D_00468D30);
    Copy(D_0036E740.left.noVibration, table, D_00468D30);
    Copy(D_0036E740.right.noVibration, table, D_00468D30);
    for (int i = 0; i < 7; i++) {
        Copy(D_0036E740.left.reverseHorizontal[i], table, D_00468D30);
        Copy(D_0036E740.right.reverseHorizontal[i], table, D_00468D30);
        Copy(D_0036E740.left.reverseVertical[i], table, D_00468D30);
        Copy(D_0036E740.right.reverseVertical[i], table, D_00468D30);
    }
    Copy(&p->player->fieldB0, table, D_00468D30);
    Copy(&p->player->fieldA8, table, D_00468D30);
    func_00284568(p);
    int kind = 0x42;
    if (p->override != -1) {
        kind = 0x46;
        D_0036DBA0 = p->override;
    }
    if (func_0025AE28(&D_00475480)) {
        D_00475480.levelSet = 1;
        memset(&D_00475480.levelKind, 0, 0x48);
        D_00475480.level = *func_0025E070(p->level);
        D_00475480.levelSize = 0x1A8;
        D_00475480.levelKind = kind;
    } else
        func_00289070(&D_00475480, func_0025E070(p->level), 0x1A8, kind, -1);
}
