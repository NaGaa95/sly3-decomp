// SLY3_CFLAGS: -Os -G0
typedef unsigned int Quadword __attribute__((mode(TI)));
typedef struct Matrix { Quadword rows[4]; } Matrix;
typedef struct ChainLink { unsigned char opaque[160]; struct ChainLink *next; } ChainLink;
typedef struct Owner { unsigned char opaque[80]; ChainLink *parent; } Owner;
typedef struct VirtualEntry { short adjustment; short reserved; void (*call)(); } VirtualEntry;
typedef struct Object {
    unsigned char opaque0[12]; VirtualEntry *vtable;
    unsigned char opaque1[31]; unsigned char flags;
    unsigned char opaque2[16]; ChainLink *parent;
    unsigned char opaque3[12]; Matrix matrix;
} Object;
extern void func_0011D558(Matrix *out,ChainLink *parent,const Matrix *matrix);
extern void func_001C7A30(Object *,Owner *,ChainLink *,int);
typedef int FlagValue __attribute__((mode(DI)));
// Keep the observed byte-to-64-bit-to-32-bit flag conversion.
// Empty constraints preserve the conversion and emit no instructions.
static inline int converted_flags(Object *object) {
    FlagValue wide=object->flags; int narrow;
    asm("" : "+r"(wide)); narrow=(int)wide;
    asm("" : "+r"(narrow)); return narrow;
}
void func_00290280(Object *object,Owner *owner,ChainLink *parent,int flags) {
    Matrix matrix;
    if(flags & 3) {
        if(converted_flags(object) & 1) {
            VirtualEntry *entry=&object->vtable[36];
            Matrix *value=((Matrix *(*)(void *))entry->call)((char *)object+entry->adjustment);
            matrix=*value;
        } else {
            ChainLink *link=object->parent;
            matrix=object->matrix;
            while(link) {
                Matrix result;
                func_0011D558(&result,link,&matrix);
                matrix=result;
                link=link->next;
            }
        }
    }
    if(parent) object->parent=parent;
    else if(owner) object->parent=owner->parent;
    else object->parent=0;
    func_001C7A30(object,owner,parent,flags);
    if(flags & 1) {
        VirtualEntry *entry=&object->vtable[34];
        ((void (*)(void *,Quadword))entry->call)((char *)object+entry->adjustment,matrix.rows[3]);
    }
    if(flags & 2) {
        VirtualEntry *entry=&object->vtable[35];
        ((void (*)(void *,Matrix *))entry->call)((char *)object+entry->adjustment,&matrix);
    }
}
