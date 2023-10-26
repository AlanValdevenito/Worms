#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H

#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>

#include "dto.h"
#include "viga.h"
#include "dead.h"

class BlockingQueue
{
private:
    std::queue<Dto *> internal;
    std::mutex mutex;
    std::condition_variable cv;

public:
    BlockingQueue();
    ~BlockingQueue();
    void push(Dto *element);
    Dto *pop();
    void clear();
};

#endif
