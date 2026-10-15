// Test the optional linked resource against the actual integer identifier, accepting the original -1 wildcard. Both actual incoming inputs and pointer nesting are explicit.
// Reference algorithm: src/hand/func_00209A28.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
struct Resource {char prefix[0x40];int identifier;};
struct Link {char prefix[0x60];struct Resource *resource;};
struct S { char unknown_0[0x210]; struct Link * link; };
int func_00248858(struct S *p,int identifier){if(p->link){struct Resource *resource=p->link->resource;int result=0;if(identifier==-1||resource->identifier==identifier)result=1;return result;}return 0;}
