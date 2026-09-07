#include"nand_flash.h"
#include<cassert>
#include<vector>
#include<bits/stdc++.h>
using namespace std;

int main () {
    NandFlash nand(4, 4, 8);

    vector<uint8_t> data(8, 42);

    assert(nand.program(0, 0, data));
    assert(nand.read(0, 0) == data);
    assert(!nand.program(0, 0, data));
    assert(nand.erase(0));
    assert(nand.program(0, 0, data));
    assert(!nand.program(0, 1, vector<uint8_t>(7, 42)));
    cout<<"All NAND tests passed successfully!\n";
    return 0;
}