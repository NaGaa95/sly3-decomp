// SLY3_CFLAGS: -Os -G0 -fno-exceptions
struct CollectedOwner { unsigned char unaccessed00[0x18]; int identifier; };
struct CollectedSubject {
    unsigned char unaccessed00[0x18];
    int identifier;
    unsigned char unaccessed1C[0x50];
    CollectedOwner *owner;
    unsigned char unaccessed70[0x14];
    int incoming_count;
    unsigned char unaccessed88[0x7C];
    int visited;
    int depth;
    int rank;
};

extern "C" int func_0018A890(const void *first_element, const void *second_element)
{
    CollectedSubject *first = *(CollectedSubject *const *)first_element;
    CollectedSubject *second = *(CollectedSubject *const *)second_element;
    int first_owner, second_owner;
    if (first->rank != second->rank)
        return (int)((unsigned int)first->rank - (unsigned int)second->rank);
    first_owner = first->owner ? first->owner->identifier : -1;
    second_owner = second->owner ? second->owner->identifier : -1;
    if (first_owner != second_owner)
        return (int)((unsigned int)first_owner - (unsigned int)second_owner);
    if (first->depth != second->depth)
        return (int)((unsigned int)first->depth - (unsigned int)second->depth);
    return (int)((unsigned int)first->identifier - (unsigned int)second->identifier);
}
