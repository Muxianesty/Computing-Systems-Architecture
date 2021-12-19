#include "Hive.h"

Hive::Hive(int bees_count) {
    this->operations_count_ = 0;
    this->honey_amount_ = 0;
    this->bees_count_ = bees_count;
    sem_init(this->bees_outside_hive_count_, 0, 0);
    this->output_mutex_ = new std::mutex();
    this->honey_amount_mutex_ = new std::mutex();
    this->bees_ = std::vector<Bee *>(bees_count);
    for (int index = 0; index < this->bees_count_; ++index) {
        this->bees_[index] = new Bee(index + 1, this);
    }
    while (this->operations_count_ < Hive::OPERATIONS_COUNT) {
        if (this->honey_amount_ >= Hive::HONEY_CAPACITY_ / 2) {
            WinniePooh(this);
        }
    }
}

Hive::~Hive() {
    for (int index = 0; index < this->bees_count_; ++index) {
        delete this->bees_[index];
        this->bees_[index] = nullptr;
    }
    std::cout << "Hive-object destruction:" << std::endl;
    sem_close(this->bees_outside_hive_count_);
    sem_destroy(this->bees_outside_hive_count_);
    delete this->honey_amount_mutex_;
    delete this->bees_outside_hive_count_;
    std::cout << "True operation count: " << this->operations_count_;
}

bool Hive::operator++() {
    return this->operator++(1);
}

bool Hive::operator++(int delta) {
    this->honey_amount_mutex_->lock();
    if (this->honey_amount_ + delta < Hive::HONEY_CAPACITY_ &&
        this->honey_amount_ + delta >= 0 && this->operations_count_ < Hive::OPERATIONS_COUNT) {
        this->honey_amount_ += delta;
        this->honey_amount_mutex_->unlock();
        return true;
    }
    this->honey_amount_mutex_->unlock();
    return false;
}
