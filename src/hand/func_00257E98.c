// Complete packed setter consumes receiver A0, all128 bits of vectors A1/A2/A3, and A4 pointer to eight-byte record. Natural aligned packed members and four-byte-aligned pair preserve all original stores at16F0/1700/1710/1720.
// Parent-reviewed independent original function boundary; orphan fragments remain excluded.
// SLY3_CFLAGS: -Os -G0
typedef int QWORD __attribute__((mode(TI)));
struct Pair {unsigned int words[2];};
struct Object {char prefix[0x16F0];QWORD first;QWORD second;QWORD third;struct Pair pair;};
void func_00257E98(struct Object *object,QWORD first,QWORD second,QWORD third,const struct Pair *pair){object->first=first;object->second=second;object->third=third;object->pair=*pair;}
