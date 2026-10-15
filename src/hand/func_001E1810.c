// SLY3_CFLAGS: -Os -G0
/* Only consumed fields are declared; conditionWord1AA8 is read as a raw
   four-byte zero/nonzero condition, without asserting a complete flag schema. */
typedef struct CONTROL_VIEW { char opaque[8]; float scalar8; } CONTROL_VIEW;
typedef struct ACTOR_VIEW {
    char opaque0[0x134]; CONTROL_VIEW *controller;
    char opaque138[0x113C-0x138]; void *resource;
    char opaque1140[0x18C0-0x1140]; int state; float stateStart;
    char opaque18C8[0x18D8-0x18C8]; int pending;
    char opaque18DC[0x1AA8-0x18DC]; int conditionWord1AA8;
} ACTOR_VIEW;
typedef char ActorViewPrefix[(sizeof(ACTOR_VIEW) == 0x1AAC) ? 1 : -1];
typedef char ControllerScalarView[(sizeof(CONTROL_VIEW) == 12) ? 1 : -1];

struct CLOCK_VIEW { float time, delta; };
extern struct CLOCK_VIEW D_0036BB98;


int func_00138AC8(void *p);
void func_001DE690(ACTOR_VIEW *p, int s);
void func_001E16E8(ACTOR_VIEW *p, int s);
int func_001F4350(ACTOR_VIEW *p, int playerSlot);

void func_001E1810(ACTOR_VIEW *p)
{
    int s;
    for (;;) {
        s = p->state;
        switch (s) {
        case 0:
            if (!p->resource || func_00138AC8(p->resource)) func_001E16E8(p, 1);
            break;
        case 1:
            if (!p->resource || func_00138AC8(p->resource)) {
                func_001DE690(p, 0);
            } else if (p->pending) {
                func_001E16E8(p, 2);
            } else if (!p->conditionWord1AA8 && D_0036BB98.time - p->stateStart > 0.66f) {
                func_001E16E8(p, 3);
            }
            break;
        case 2:
            if (!p->resource || func_00138AC8(p->resource)) {
                if (p->conditionWord1AA8) func_001E16E8(p, 0);
                else func_001DE690(p, 0);
            }
            break;
        case 3:
            if (!p->resource || func_00138AC8(p->resource)) {
                func_001DE690(p, 0);
            } else if (D_0036BB98.time - p->stateStart > 0.15f && func_001F4350(p, -1) && 0.0f < p->controller->scalar8) {
                func_001DE690(p, 0);
            }
            break;
        }
        if (p->state == s || p->state == -1) break;
    }
}
