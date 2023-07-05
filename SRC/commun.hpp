#ifndef COMMON_HPP
#define COMMON_HPP

#include <mutex>
#include <semaphore.h>

namespace plazza {
    extern std::mutex g_display_mutex;
    extern sem_t g_semaphore;
}

#endif  // COMMON_HPP
