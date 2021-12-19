#include "Bee.h"

Bee::Bee(int id, Hive *hive_ptr) {
    this->id_ = id;
    this->hive_ptr_ = hive_ptr;
    this->is_outside_ = false;
    this->thread_ = new std::thread{routine, this};
}

Bee::~Bee() {
    this->thread_->join();
    delete this->thread_;
    this->thread_ = nullptr;
}

Bee::operator string() {
    return "Bee#" + std::to_string(this->id_) + ((this->is_outside_) ? "(outside)" : "(inside)");
}

void Bee::routine(Bee *bee_ptr) {
    int *buf = new int(0);
    while (bee_ptr->hive_ptr_->operations_count_ < Hive::OPERATIONS_COUNT) {
        sem_getvalue(bee_ptr->hive_ptr_->bees_outside_hive_count_, buf);
        bee_ptr->hive_ptr_->output_mutex_->lock();
        if (bee_ptr->hive_ptr_->bees_count_ - *buf > 1) {
            sem_post(bee_ptr->hive_ptr_->bees_outside_hive_count_);
            cout << static_cast<string>(*bee_ptr) << " went outside to gather some honey" << endl;
            bee_ptr->is_outside_ = true;
            bool flag = false;
            cout << static_cast<string>(*bee_ptr)
                 << ((flag = bee_ptr->hive_ptr_->operator++()) ? " managed" : " didn't manage")
                 << " to gather the honey" << endl;
            sem_wait(bee_ptr->hive_ptr_->bees_outside_hive_count_);
            bee_ptr->is_outside_ = false;
            bee_ptr->hive_ptr_->operations_count_ += ((flag) ? 1 : 0);
        } else {
            cout << static_cast<string>(*bee_ptr) << " can't leave the hive unprotected" << endl;
        }
        bee_ptr->hive_ptr_->output_mutex_->unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
    delete buf;
}
