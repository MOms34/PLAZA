/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#ifndef KITCHEN_HPP
    #define KITCHEN_HPP
    #include "reception.hpp"
    #include <pthread.h>
    #include <mutex>
    #include "commun.hpp"

namespace plazza {
    struct Message;
    class reception;
    class Kitchen {
        private:
            int messageQueueId;
            reception& recep;
            pid_t pid;
            int messageQ;
            int kitchenReceptionMsgQueueId;
        protected:
        public:
        Kitchen(reception& recept, int msgQueueId);
        ~Kitchen();
        void sendMessageToReception(const std::string& message);
        void start();

        };
}

#endif /* !KITCHEN_HPP */
