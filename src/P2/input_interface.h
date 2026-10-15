#ifndef SLY3_PRIVATE_INPUT_INTERFACE_H
#define SLY3_PRIVATE_INPUT_INTERFACE_H
// Provisional interface: the original concrete tables establish these five
// methods, with their real argument contracts. No original class name is assigned.
struct INPUT_INTERFACE_DATA {
    float leftX,leftY,leftAmount,rightX,rightY,rightAmount;
    unsigned int held18;
    float leftStateTimes1C[2],rightStateTimes24[2];
};
class INPUT_INTERFACE : public INPUT_INTERFACE_DATA {
public:
    virtual unsigned int Query(float threshold,unsigned int mask);
    virtual void Consume(unsigned int mask);
    virtual float Analog(unsigned int index);
    virtual int FirstGate(unsigned int index);
    virtual int SecondGate(unsigned int index);
};
#endif
