#pragma once
#include<vector>
#include<cstdint>
using namespace std;

struct FlashPage
{
    vector<uint8_t> data;
    bool programmed;
    bool valid;

    FlashPage(size_t pageSize);
};
