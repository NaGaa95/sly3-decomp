// Complete original Sly3 body; ordinary source/profile reconstruction.
// A0 object and A1 key reach the complete original predicate1FC1F0. A2 is a cursor containing Object**. The pointed Object* and cursor Object** have distinct source types, removing the false alias reload.
// SLY3_CFLAGS: -Os -G0
struct Object { char opaque; }; struct Cursor { struct Object **current; }; int func_001FC1F0(struct Object *,void *); void func_001FC248(struct Object *p,void *key,struct Cursor *output) { if(func_001FC1F0(p,key))*output->current++=p; }
