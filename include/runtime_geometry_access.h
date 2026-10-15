#ifndef SLY3_RUNTIME_GEOMETRY_ACCESS_H
#define SLY3_RUNTIME_GEOMETRY_ACCESS_H

/* Observed Sly 3 byte views, not recovered historical class identities.
 * A geometry allocation is 256 bytes aligned to 16. The loader discriminator
 * at 0x10 is separate from the matrix representation tag at 0x04. The whole
 * 64-byte record at 0xC0 has property and value views with distinct tag offsets. */
typedef int RuntimeGeometryQuad __attribute__((mode(TI)));
typedef struct RuntimeGeometryMatrix {
    RuntimeGeometryQuad vector[4];
} RuntimeGeometryMatrix;
typedef struct RuntimeGeometryVector2 { float value[2]; } RuntimeGeometryVector2;
typedef struct RuntimeGeometryVector3 { float value[3]; } RuntimeGeometryVector3;
typedef struct RuntimeGeometryVector4 { float value[4]; } RuntimeGeometryVector4;

typedef struct RuntimeGeometryPropertyRecord {
    union {
        int scalar;
        RuntimeGeometryVector2 pair;
        RuntimeGeometryVector3 triple;
    } value;
    unsigned char opaque0c[0x10];
    int kind;
} RuntimeGeometryPropertyRecord;

typedef struct RuntimeGeometryValueRecord {
    int kind;
    unsigned char opaque04[0x2c];
    union {
        float scalar;
        RuntimeGeometryVector4 vector;
    } value;
} RuntimeGeometryValueRecord;

typedef union RuntimeGeometryRecord {
    RuntimeGeometryMatrix whole_matrix;
    RuntimeGeometryPropertyRecord property;
    RuntimeGeometryValueRecord value;
} RuntimeGeometryRecord;

typedef struct RuntimeGeometry {
    int references;
    int matrix_kind;
    unsigned char opaque08[8];
    int loader_kind;
    unsigned char opaque14[0x1c];
    void *loader_detail;
    unsigned char opaque34[0x8c];
    RuntimeGeometryRecord record;
} RuntimeGeometry;

typedef struct RuntimeOwner {
    unsigned char opaque00[0xd0];
    int writable;
    RuntimeGeometry *geometry;
} RuntimeOwner;

#define SLY3_RUNTIME_GEOMETRY_OFFSET(type, field) ((unsigned int)&(((type *)0)->field))
typedef char RuntimeGeometryPointer32[(sizeof(void *) == 4) ? 1 : -1];
typedef char RuntimeGeometryWhole256[(sizeof(RuntimeGeometry) == 256) ? 1 : -1];
typedef char RuntimeGeometryAlignment16[(__alignof__(RuntimeGeometry) == 16) ? 1 : -1];
typedef char RuntimeGeometryWholeRecord64[(sizeof(RuntimeGeometryRecord) == 64) ? 1 : -1];
typedef char RuntimeGeometryRecordAtC0[(SLY3_RUNTIME_GEOMETRY_OFFSET(RuntimeGeometry, record) == 0xc0) ? 1 : -1];
typedef char RuntimeGeometryLoaderKindAt10[(SLY3_RUNTIME_GEOMETRY_OFFSET(RuntimeGeometry, loader_kind) == 0x10) ? 1 : -1];
typedef char RuntimeGeometryLoaderDetailAt30[(SLY3_RUNTIME_GEOMETRY_OFFSET(RuntimeGeometry, loader_detail) == 0x30) ? 1 : -1];
typedef char RuntimeGeometryPropertyKindAt1C[(SLY3_RUNTIME_GEOMETRY_OFFSET(RuntimeGeometryPropertyRecord, kind) == 0x1c) ? 1 : -1];
typedef char RuntimeGeometryValueAt30[(SLY3_RUNTIME_GEOMETRY_OFFSET(RuntimeGeometryValueRecord, value) == 0x30) ? 1 : -1];
typedef char RuntimeOwnerWritableAtD0[(SLY3_RUNTIME_GEOMETRY_OFFSET(RuntimeOwner, writable) == 0xd0) ? 1 : -1];
typedef char RuntimeOwnerGeometryAtD4[(SLY3_RUNTIME_GEOMETRY_OFFSET(RuntimeOwner, geometry) == 0xd4) ? 1 : -1];
#undef SLY3_RUNTIME_GEOMETRY_OFFSET

/* Match the already maintained allocator tags and initializer endpoint types.
 * C++ users obtain the ALLOCREQ definition from src/P2/heap.h when needed;
 * these C recovery files need its same two-field definition directly. */
#ifdef __cplusplus
struct ALLOCREQ;
extern "C" {
#else
struct ALLOCREQ { int cb; int cbAlign; };
#endif
struct MSG { int cb; int nKind; };
struct S;
struct X;
void *func_001D2470(struct ALLOCREQ *request);
void *func_001D24D0(struct MSG *request, void *original);
void func_00177488(struct S *geometry);
void func_001775B8(void *detail, void *stream);
void func_0028FDE0(void *owner, void *stream);
void func_002BC928(struct X *owner, void *stream);
void func_002BD398(struct X *owner, void *stream);

void func_002BCA18(RuntimeOwner *owner, void *stream);
void func_002BD488(RuntimeOwner *owner, void *stream);
RuntimeGeometry *func_002BCAD8(RuntimeOwner *owner, int operation);
RuntimeGeometry *func_002BD548(RuntimeOwner *owner, int operation);
void *func_002BCCF0(RuntimeOwner *owner, int operation);
void *func_002BCD78(RuntimeOwner *owner, int operation);
void *func_002BD760(RuntimeOwner *owner, int operation);
void *func_002BD7E8(RuntimeOwner *owner, int operation);
void func_002BDA38(RuntimeOwner *owner, int kind);
void func_002BDC60(RuntimeOwner *owner, int kind);
void *func_002BDB28(RuntimeOwner *owner, int operation);
void *func_002BDB90(RuntimeOwner *owner, int operation);
void *func_002BDBF8(RuntimeOwner *owner, int operation);
void *func_002BDD28(RuntimeOwner *owner, int operation);
void *func_002BDD90(RuntimeOwner *owner, int operation);

extern RuntimeGeometryMatrix D_00321320;
extern RuntimeGeometryMatrix D_00321380;
extern unsigned char D_0036BEC0[];
extern unsigned char D_0036BEF0[];
#ifdef __cplusplus
}
#endif
#endif
