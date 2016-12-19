#ifndef PROCESSCONCURRENTTEST1_H
#define PROCESSCONCURRENTTEST1_H

#include "ProcessConcurrent.h"

namespace PW{
class LIBPWSHARED_EXPORT ProcessConcurrentTest1 : public ProcessConcurrent
{
public:
    ProcessConcurrentTest1();

protected:
    virtual void run();
};
}

#endif // PROCESSCONCURRENTTEST1_H
