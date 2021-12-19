#pragma once
#include <iostream>
#include <vector>
#include "Bee.h"
#include "WinniePooh.h"
#include "fcntl.h"
#include <mutex>
#include "semaphore.h"

class Bee;

class WinniePooh;

class Hive {
public:
    int operations_count_;
    int honey_amount_;
    int bees_count_;
    sem_t *bees_outside_hive_count_;
    std::mutex *honey_amount_mutex_;
    std::mutex *output_mutex_;
    std::vector<Bee *> bees_;
    static const int HONEY_CAPACITY_ = 30;
    static const int BEES_COUNT = 30;
    static const int MAX_BEES_COUNT_TO_STEAL = 3;
    static const int OPERATIONS_COUNT = 200;
    explicit Hive(int);
    ~Hive();
    bool operator++();
    bool operator++(int);
};