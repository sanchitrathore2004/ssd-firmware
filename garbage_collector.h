#pragma once
#include "ftl.h"
#include <cstddef>
using namespace std;

class GarbageCollector {
private:
    FTL& ftl;
public:
    GarbageCollector(FTL& ftl);
    bool collect();
};
