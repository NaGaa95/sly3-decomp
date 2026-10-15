#ifndef SLY3_FACTORY_DESCRIPTOR_H
#define SLY3_FACTORY_DESCRIPTOR_H
/* Original twenty-byte class record; fields and factory arguments are proved
 * against the complete subtype query and all227 original factory bodies. */
struct FactoryDescriptor {
    struct FactoryDescriptor *parent;
    int type_id;
    int type_end;
    unsigned int instance_bytes;
    void *(*create)(void);
};
typedef char factory_descriptor_has_original_twenty_bytes[sizeof(struct FactoryDescriptor) == 20 ? 1 : -1];
extern struct FactoryDescriptor D_003409E0[249];
#endif
