#include"flash_page.h"

FlashPage::FlashPage(size_t pageSize){
    data.resize(pageSize, 0);
    programmed = false;
    valid = false;
}