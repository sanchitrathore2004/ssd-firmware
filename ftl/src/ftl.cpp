#include "ftl.h"
#include "nand_flash.h"

FTL::FTL(NandFlash& nand)
    : nand(nand), wear_leveling(nand), next_block(0), next_page(0) {
}

PhysicalAddress FTL::allocatePage() {
    size_t block = wear_leveling.getLeastWornBlock();

    for (size_t page = 0; page < nand.getPagesPerBlock(); page++) {
        if (!nand.isProgrammed(block, page)) {
            return PhysicalAddress{block, page};
        }
    }

    PhysicalAddress address{next_block, next_page};
    next_page++;

    if (next_page == nand.getPagesPerBlock()) {
        next_page = 0;
        next_block++;
    }

    return address;
}

bool FTL::write(uint64_t lba, const vector<uint8_t>& data) {
    if (data.size() != nand.getPageSize()) {
        return false;
    }

    if (mapping.find(lba) != mapping.end()) {
        PhysicalAddress old = mapping[lba];
        nand.invalidate(old.block, old.page);
    }

    PhysicalAddress address = allocatePage();

    if (!nand.program(address.block, address.page, data)) {
        return false;
    }

    mapping[lba] = address;

    return true;
}

vector<uint8_t> FTL::read(uint64_t lba) {
    if (mapping.find(lba) == mapping.end()) {
        return {};
    }

    PhysicalAddress address = mapping[lba];

    return nand.read(address.block, address.page);
}

const unordered_map<uint64_t, PhysicalAddress>& FTL::getMapping() const {
    return mapping;
}

bool FTL::updateMapping(uint64_t lba, PhysicalAddress address) {
    mapping[lba] = address;

    return true;
}

NandFlash& FTL::getNand() {
    return nand;
}

PhysicalAddress FTL::allocateForGC(size_t excluded_block) {
    for (size_t block = 0; block < nand.getNumBlocks(); block++) {
        if (block == excluded_block) {
            continue;
        }

        for (size_t page = 0; page < nand.getPagesPerBlock(); page++) {
            if (!nand.isProgrammed(block, page)) {
                return PhysicalAddress{block, page};
            }
        }
    }

    return PhysicalAddress{nand.getNumBlocks(), 0};
}

bool FTL::relocate(uint64_t lba,
                   const vector<uint8_t>& data,
                   PhysicalAddress& new_address,
                   size_t excluded_block) {
    PhysicalAddress address = allocateForGC(excluded_block);

    if (address.block >= nand.getNumBlocks()) {
        return false;
    }

    if (!nand.program(address.block, address.page, data)) {
        return false;
    }

    mapping[lba] = address;
    new_address = address;

    return true;
}