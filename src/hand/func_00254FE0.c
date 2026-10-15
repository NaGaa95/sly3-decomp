// Clone the original kind3 payload into a new fixed-pool block and replace its pointer.
// Complete original inputs, return boundary and initialized sections are independently verified.
// SLY3_CFLAGS: -Os -G0
struct Command {
    int kind;
    void *payload;
};
void *func_00259590(unsigned int bytes);
void func_001D2898(void *destination,const void *source,unsigned int bytes);
void func_00254FE0(struct Command *p) {
    if(p->kind==3) {
        void *copy=func_00259590(0x110);
        func_001D2898(copy,p->payload,0x110);
        p->payload=copy;
    }
}
