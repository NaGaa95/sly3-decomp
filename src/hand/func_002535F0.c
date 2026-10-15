// Construct the explicit reference mask, initialize all four command values, and update the selected command.
// Original accessed layouts and complete argument flow are independently verified; nominal type names remain provisional.
// SLY3_CFLAGS: -Os -G0
struct Reference;
struct Mask {
    int words[4];
};
struct Command;
struct Mask *func_00252D80(struct Mask *out,struct Reference *reference);
struct Command *func_002554C0(void *receiver,const struct Mask *mask);
void func_00253540(void *receiver,struct Reference *reference,int a,int b,int c,int d);
void func_00254C00(struct Command *command,void *owner);
void func_002535F0(void *p,struct Reference *reference,int a,int b,int c,int d) {
    struct Mask mask;
    struct Command *command;
    func_00252D80(&mask,reference);
    command=func_002554C0(p,&mask);
    func_00253540(p,reference,a,b,c,d);
    func_00254C00(command,p);
}
