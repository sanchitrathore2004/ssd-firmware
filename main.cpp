#include "ftl.h"
#include "metric.h"
#include "wear_leveling.h"
#include "garbage_collector.h"
#include <iostream>
#include <vector>

using namespace std;

int main() {
    NandFlash nand(4, 4, 8);

    FTL ftl(nand);

    Metrics metrics(nand);

    WearLeveling wear_leveling(nand);

    GarbageCollector gc(ftl);

    vector<uint8_t> data(8, 42);

    ftl.write(0, data);
    ftl.write(1, data);
    ftl.write(2, data);

    ftl.write(0, vector<uint8_t>(8, 99));

    cout << "Before GC:" << endl;

    cout << "Programmed pages: "
         << metrics.getProgrammedPages() << endl;

    cout << "Valid pages: "
         << metrics.getValidPages() << endl;

    cout << "Total erase count: "
         << metrics.getTotalEraseCount() << endl;

    cout << "Least worn block: "
         << wear_leveling.getLeastWornBlock() << endl;

    cout << "GC: "
         << (gc.collect() ? "SUCCESS" : "NOT NEEDED") << endl;

    cout << "After GC:" << endl;

    cout << "Programmed pages: "
         << metrics.getProgrammedPages() << endl;

    cout << "Valid pages: "
         << metrics.getValidPages() << endl;

    cout << "Total erase count: "
         << metrics.getTotalEraseCount() << endl;

    cout << "SSD firmware simulation completed!" << endl;

    return 0;
}