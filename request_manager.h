#pragma once
#include<queue>
#include<vector>
#include<cstdint>
#include"ftl.h"

using namespace std;

enum class RequestType {
    READ,
    WRITE
};

struct IORequest
{
    RequestType type;
    uint64_t id;
    uint64_t lba;
    vector<uint8_t> data;

    IORequest(RequestType type, uint64_t id, uint64_t lba, const vector<uint8_t>& data={});
};

class RequestManager {
private:
    FTL& ftl;
    queue<IORequest> submission_queue;
    uint64_t next_request_id;

public:
    RequestManager(FTL& ftl);
    uint64_t submitRead(uint64_t lba);
    uint64_t submitWrite(uint64_t lba, const vector<uint8_t>& data = {});
    void processRequest();
};
