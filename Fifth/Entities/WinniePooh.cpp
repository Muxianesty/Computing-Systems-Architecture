#include "WinniePooh.h"

WinniePooh::WinniePooh(Hive *hive_ptr) {
    this->hive_ptr_ = hive_ptr;
    this->thread_ = new std::thread{routine, this};
}

WinniePooh::~WinniePooh() {
    this->thread_->join();
    delete this->thread_;
    this->thread_ = nullptr;
}

void WinniePooh::routine(WinniePooh *winnie_ptr) {
    winnie_ptr->hive_ptr_->output_mutex_->lock();
    std::cout << "Winnie Pooh is awake and eager to go for the honey" << std::endl;
    winnie_ptr->hive_ptr_->output_mutex_->unlock();
    int *buf = new int(0);
    sem_getvalue(winnie_ptr->hive_ptr_->bees_outside_hive_count_, buf);
    while (winnie_ptr->hive_ptr_->operations_count_ < Hive::OPERATIONS_COUNT &&
           winnie_ptr->hive_ptr_->bees_count_ - *buf <= Hive::MAX_BEES_COUNT_TO_STEAL) {
        winnie_ptr->hive_ptr_->output_mutex_->lock();
        std::cout << "There were " << *buf << " bees - Winnie was bitten and has to heal";
        winnie_ptr->hive_ptr_->output_mutex_->unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        ++(winnie_ptr->hive_ptr_->operations_count_);
        sem_getvalue(winnie_ptr->hive_ptr_->bees_outside_hive_count_, buf);
    }
    if (winnie_ptr->hive_ptr_->operations_count_ < Hive::OPERATIONS_COUNT) {
        winnie_ptr->hive_ptr_->output_mutex_->lock();
        std::cout << "Winnie steals all the honey from the hive and goes back to sleep" << std::endl;
        winnie_ptr->hive_ptr_->output_mutex_->unlock();
        ++(winnie_ptr->hive_ptr_->operations_count_);
        winnie_ptr->hive_ptr_->operator++((-1) * winnie_ptr->hive_ptr_->honey_amount_);
    } else {
        winnie_ptr->hive_ptr_->output_mutex_->lock();
        std::cout << "Winnie didn't get to steal the honey in time and went to sleep" << std::endl;
        winnie_ptr->hive_ptr_->output_mutex_->unlock();
    }
    delete buf;
}

