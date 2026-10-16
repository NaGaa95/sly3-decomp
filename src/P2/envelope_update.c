// SLY3_CFLAGS: -Os -G0
struct EnvelopeTarget {
    unsigned char prefix[0x10];
    float weight;
};
struct EnvelopeEntry {
    struct EnvelopeTarget *target;
    float started;
    float full_begin;
    float full_end;
    float stopped;
};
struct EnvelopeGroup {
    unsigned char parameters[0x28];
    int count;
    struct EnvelopeEntry entries[0];
};
struct EnvelopeOwner {
    unsigned char prefix[0x698];
    unsigned char groups[0];
};
extern float D_0036BB98;
typedef char EnvelopeEntrySizeMustBe20[sizeof(struct EnvelopeEntry)==20?1:-1];
typedef char EnvelopeGroupPrefixMustBe44[sizeof(struct EnvelopeGroup)==44?1:-1];

static __inline__ float ClampEnvelope(float lower, float upper, float amount)
{
    if (amount < lower)
        return lower;
    else if (upper < amount)
        return upper;
    return amount;
}

void func_0028AC30(struct EnvelopeOwner *owner, int group_index)
{
    struct EnvelopeGroup *group = (struct EnvelopeGroup *)
        (owner->groups + group_index * 0x54);
    float now = D_0036BB98;
    int i;
    for (i = 0; i < group->count; ++i) {
        struct EnvelopeEntry *entry = &group->entries[i];
        struct EnvelopeTarget *target = entry->target;
        float amount;
        if (target == 0)
            break;
        if (now < entry->full_begin)
            amount = (now - entry->started) /
                     (entry->full_begin - entry->started);
        else if (entry->full_end < now)
            amount = (entry->stopped - now) /
                     (entry->stopped - entry->full_end);
        else
            amount = 1.0f;
        amount = ClampEnvelope(0.0f, 1.0f, amount);
        target->weight = amount * amount *
                                (3.0f - (amount + amount));
    }
}
