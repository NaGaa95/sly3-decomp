// SLY3_CFLAGS: -Os -G0
/* Prefix view of the selection object; the layout follows include/selection_types.h
   except that the original compares the count signed and reads word40. */
typedef struct SelectionRow {
    int id;
    int event;
} SelectionRow;

typedef struct SelectionMenu {
    char reserved0[0x34];
    void *child;
    char reserved38[0x40 - 0x38];
    int word40;
    char reserved44[0x50 - 0x44];
    int state;
    float changed_at;
    int count;
    SelectionRow rows[67];
    int index;
    int first;
    int selected;
    int value280;
    int value284;
    int value288;
} SelectionMenu;

typedef struct SoundTransform {
    float row0[4];
    float row1[4];
} SoundTransform __attribute__((aligned(16)));

typedef struct SoundKind {
    int reserved0;
    int type;
    char reserved8[0x3C - 8];
} SoundKind;

extern int D_0046FD40;
extern float D_00349398;
extern int D_00349370[];
extern SoundKind D_00343098[];

void *func_00292034(void *destination, int byte, unsigned int bytes);
int func_00220080(SelectionMenu *);
void func_002628B8(void *child, int event, SoundTransform *transform);
void func_00262B60(void *child, int event, int *current);
void func_00262540(void *child, int event, int slot);
void func_00262370(void *child, int event, int slot);
void func_00262450(void *child, int event);
void func_00262280(void *child, int event);

void func_002202A0(SelectionMenu *menu)
{
    SoundTransform transform;
    int visible;
    int i;
    int event;
    func_00292034(&transform, 0, sizeof(transform));
    transform.row0[3] = 1.0f;
    transform.row0[0] = 1.0f;
    visible = func_00220080(menu);
    if (menu->first > 0) {
        event = menu->state == 0 ? 0x567 : 0x52E;
        if (D_0046FD40) {
            func_002628B8(menu->child, event, &transform);
            transform.row1[1] += D_00349398;
        }
        func_00262B60(menu->child, event, &menu->value284);
    } else {
        func_00262B60(menu->child, -1, &menu->value284);
    }
    for (i = menu->first; i < visible; i++) {
        SelectionRow *row = &menu->rows[i];
        int slot = D_00349370[i - menu->first];
        if (menu->state == 0) {
            int id = row->id;
            if (id != -1) {
                switch (D_00343098[id].type) {
                case 0x18:
                    row->event = 0x4E3;
                    break;
                case 0x19:
                    row->event = 0x4E4;
                    break;
                case 0x1A:
                    row->event = 0x4E5;
                    break;
                }
                func_00262540(menu->child, 0x4E2, slot);
                func_00262540(menu->child, row->event, slot);
            } else {
                func_00262370(menu->child, 0x4E2, slot);
                func_00262370(menu->child, row->event, slot);
                row->event = id;
            }
        }
    }
    if (menu->index >= 0) {
        func_00262450(menu->child, 0x4C4);
        func_00292034(&transform, 0, sizeof(transform));
        transform.row0[3] = 1.0f;
        transform.row0[0] = 1.0f;
        transform.row1[1] = D_00349398 * (float)(menu->index - menu->first);
        func_002628B8(menu->child, 0x4C4, &transform);
    } else {
        func_00262280(menu->child, 0x4C4);
    }
    if (visible < menu->count) {
        event = menu->state == 0 ? 0x56A : 0x531;
        if (D_0046FD40) {
            func_002628B8(menu->child, event, &transform);
            transform.row1[1] += D_00349398;
        }
        func_00262B60(menu->child, event, &menu->value288);
    } else {
        func_00262B60(menu->child, -1, &menu->value288);
    }
    func_00262B60(menu->child, menu->word40 != -1 ? 0x4C8 : 0x4C6, &menu->value280);
}
