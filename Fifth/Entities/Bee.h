#pragma once
#include <thread>
#include "Hive.h"
#include <string>
using std::string;
using std::cout;
using std::endl;

class Hive;

class Bee {
private:
    int id_;
    Hive *hive_ptr_;
    bool is_outside_;
    std::thread *thread_;
    static void routine(Bee *);
public:
    Bee(int, Hive *);
    ~Bee();
    operator string();
};
