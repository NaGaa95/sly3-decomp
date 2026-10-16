// SLY3_CFLAGS: -Os -G0
struct SceneRange { float lower, upper; };
struct SceneRangeState {
    char prefix[0x3C];
    unsigned int flags;
    int unaccessed40;
    float range_value;
    struct SceneRange range;
    float step;
};
extern struct SceneRange D_00321150;
void func_001C7340(void *receiver);

void func_00173710(struct SceneRangeState *p)
{
    func_001C7340(p);
    p->range_value = 1500.0f;
    p->range = D_00321150;
    p->step = 0.25f;
    p->flags |= 0x80;
}

struct PairCandidateKey { char prefix[0xDC]; int key; };
struct PairAssociatedState {
    char prefix[0x1F8];
    struct PairCandidateKey *associated;
};
struct ScenePairQueryState;
int func_0013B500(char *receiver, int kind);
int func_0023E178(struct ScenePairQueryState *first,
                  struct ScenePairQueryState *second);

int func_0019CC40(struct PairAssociatedState *first,
                  struct PairCandidateKey *candidate)
{
    if (first->associated && candidate->key == first->associated->key)
        return 3;
    if (func_0013B500((char *)candidate, 0x4C))
        return 3;
    return func_0023E178((struct ScenePairQueryState *)first,
                         (struct ScenePairQueryState *)candidate);
}
