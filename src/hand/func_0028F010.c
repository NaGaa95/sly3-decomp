// Classify the original twenty-one resource types through the complete original dispatch table.
// Reference algorithm: src/hand/func_001B8180.c.
// Sly 3 record layouts, event IDs, and virtual slots recovered from original operands.
// SLY3_CFLAGS: -Os -G0
// SLY3_AS: gnu-2.9
int func_0028F010(unsigned int type){static void *const targets[] __attribute__((aligned(4)))={&&true_type,&&false_type,&&false_type,&&true_type,&&false_type,&&false_type,&&false_type,&&false_type,&&false_type,&&false_type,&&false_type,&&true_type,&&false_type,&&true_type,&&false_type,&&false_type,&&false_type,&&false_type,&&false_type,&&false_type,&&true_type};if(type>=21)goto false_type;goto *targets[type];true_type:return 1;false_type:return 0;}
