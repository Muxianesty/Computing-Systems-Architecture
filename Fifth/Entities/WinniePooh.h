#pragma once
#include "Hive.h"
#include <thread>
#include "semaphore.h"
class Hive;

class WinniePooh {
private:
    Hive *hive_ptr_;
    std::thread *thread_;

public:
    explicit WinniePooh(Hive *);
    ~WinniePooh();

private:
    static void routine(WinniePooh *);
};
