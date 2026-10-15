#ifndef SLY3_P2_SESSION_H
#define SLY3_P2_SESSION_H

// Names are provisional. Fields and record strides are established by the
// original session transition, callbacks and selection methods.
struct SESSION_CONTROL_DATA;

struct SESSION_CONTROL_NODE {
    char prefix[0x40];
    int nameId,descriptionId;
    char pad48[8];
    int mode,flags,unknown58,id;
    char pad60[0x9C-0x60];
    float value9C,valueA0,valueA4;
};

struct SESSION_CONTROL_ROW {
    int kind;
    SESSION_CONTROL_NODE *node;
    int available;
};

struct SESSION_CONTROL_PARENT {
    char prefix[0x18];
    int textId;
    char pad1C[0x40-0x1C];
    int mode,index,count;
    SESSION_CONTROL_ROW *rows;
    int selected;
    void *textOwner,*itemOwner;
    int enabled;
};

struct SESSION_CONTROL_VTABLE {
    char prefix[0x1A8];
    short delta,pad;
    void (*SetFeedback)(void *,int);
};

struct SESSION_CONTROL_GROUP { SESSION_CONTROL_PARENT *slots[3]; };

struct SESSION_CONTROL_DATA {
    char prefix[0xC];
    SESSION_CONTROL_VTABLE *vtable;
    char pad10[0x6C-0x10];
    int feedback;
    char pad70[0x124-0x70];
    int index,maximum,selected;
    SESSION_CONTROL_PARENT *parent;
    float elapsed;
    int field138,field13C,state,nextState;
    SESSION_CONTROL_GROUP groups[9];
    char pad1B4[0x1E8-0x1B4];
    int previousIndex,previousState;
};

struct SESSION_CONTROL_OPTION {
    int kind,labelId,selectedId,disabledId,unknown10,scriptTag;
};

struct SESSION_CONTROL_MENU { int count; SESSION_CONTROL_OPTION *options; };

struct SESSION_CONTROL_GAME {
    char prefix[0x42C8];
    int valueTag;
    char pad42CC[0x4F68-0x42CC];
    SESSION_CONTROL_DATA *session;
};

#endif
