#include"request_manager.h"

IORequest::IORequest(RequestType type, uint64_t id, uint64_t lba, const vector<uint8_t>& data) {
    this->type = type;
    this->lba = lba;
    this->id = id;
    this->data = data;
}

RequestManager::RequestManager(FTL& ftl): ftl(ftl){}

uint64_t RequestManager::submitRead(uint64_t lba) {
    uint64_t id = next_request_id++;
    submission_queue.emplace(RequestType::READ, id, lba);
    return id;
}

uint64_t RequestManager::submitWrite(uint64_t lba, const vector<uint8_t>& data) {
    uint64_t id = next_request_id++;
    submission_queue.emplace(RequestType::WRITE, id, lba, data);
    return id;
}

void RequestManager::processRequest() {
    while(!submission_queue.empty()){
        IORequest request = submission_queue.front();
        submission_queue.pop();

        if(request.type == RequestType::READ) {
            request.data = ftl.read(request.lba);
        }

        else {
            ftl.write(request.lba, request.data);
        }
    }
}