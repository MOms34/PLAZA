/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#ifndef RECEPTION_HPP
    #define RECEPTION_HPP
    #include <queue>
    #include <iostream>
    #include <string>
    #include <csignal>
    #include <pthread.h>
    #include <thread>
    #include <chrono>
    #include <sys/msg.h>

    #include "kitchen.hpp"
    #include "processfork.hpp"
    #include "commun.hpp"

namespace plazza {
    struct Message {
    long type;
    char data[1024];
};
    enum PizzaType
    {
        Regina = 1,
        Margarita = 2,
        Americana = 4,
        Fantasia = 8,
        Nop = -1
    };

    enum PizzaSize
    {
        S = 1,
        M = 2,
        L = 4,
        XL = 8,
        XXL = 16,
        Noop = -1


    };

    struct cmdPizza {
        PizzaType type;
        PizzaSize size;
        int number;
    };

    class run;
    class reception {
    private:
        double multiplicateur;
        int cuisiniers;
        int regen;
        run& Run;
        static bool quit;
        std::queue<std::string> cmd;
        std::queue<cmdPizza> listCmd;
        processFork Fork_;
        std::vector<pid_t> kitchenPids;
        int messageQueueId;
        int kitchenReceptionMsgQueueId;
        int messsageQ;
    protected:
    public:
        reception(run& instance);
        ~reception();
        static void signalHandler(int signal);
        void startShell();
        int checkCmd();
        void parsecmd();
        PizzaType getPizzaType(std::string namePizza);
        PizzaSize getPizzaSize(std::string size);
        cmdPizza getCmdSimple(std:: string namePizza, std::string size, int number);
        std::queue<cmdPizza> getCommandParse();
        std::vector<pid_t> getListPid();
        void killAllProcess();
        void creatKitchen(int number);
        void listProcess();
        void sendCommandToKitchen(int kitchenId, const std::string &command);
        void waitForChildren();
        void receiveMessageFromKitchen();
        int getKeyReception();
        pid_t getMyPid();


    }; 
}

#endif /* !RECEPTION_HPP */
