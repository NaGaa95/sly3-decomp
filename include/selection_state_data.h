#ifndef SLY3_SELECTION_STATE_DATA_H
#define SLY3_SELECTION_STATE_DATA_H
struct SelectionEntry {
    int identifier, fallback, preferred, matching, selected;
    float x, y;
    unsigned int flags;
};
extern struct SelectionEntry D_00348BE0[15];
extern struct SelectionEntry D_00348DC0[11];
extern struct SelectionEntry D_00348F20[8];
typedef char selection_entry_is_32[sizeof(struct SelectionEntry) == 32 ? 1 : -1];
#endif
