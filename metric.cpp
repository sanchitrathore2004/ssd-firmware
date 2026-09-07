#include "metric.h"

Metrics::Metrics(NandFlash& nand)
    : nand(nand) {
}

size_t Metrics::getProgrammedPages() const {
    size_t count = 0;

    for (size_t block = 0; block < nand.getNumBlocks(); block++) {
        for (size_t page = 0; page < nand.getPagesPerBlock(); page++) {
            if (nand.isProgrammed(block, page)) {
                count++;
            }
        }
    }

    return count;
}

size_t Metrics::getValidPages() const {
    size_t count = 0;

    for (size_t block = 0; block < nand.getNumBlocks(); block++) {
        for (size_t page = 0; page < nand.getPagesPerBlock(); page++) {
            if (nand.isValid(block, page)) {
                count++;
            }
        }
    }

    return count;
}

uint64_t Metrics::getTotalEraseCount() const {
    uint64_t count = 0;

    for (size_t block = 0; block < nand.getNumBlocks(); block++) {
        count += nand.getEraseCount(block);
    }

    return count;
}