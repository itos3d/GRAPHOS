#ifndef RTDISTORTION_H
#define RTDISTORTION_H

#include "RadialDistortion.h"

class RTDistortion : public RadialDistortion
{
public:
    RTDistortion();

private:
    float mP1;
    float mP2;
};

#endif // RTDISTORTION_H
