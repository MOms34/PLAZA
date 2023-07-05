/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#ifndef RUN_HPP
    #define RUN_HPP
    #include <iostream>
    #include <cstdlib>
    #include <string>
    #include "reception.hpp"
    #define FAIL 84
    #define SUCESS 0

namespace plazza {
    class run {
        private:
            int ac;
            char **argv;
            double multiplicateur;
            int cuisiniers;
            int regen;
        public:
            run(int argc, char **av);
            ~run();
            int check_arg();
            bool isNumberPos(const std::string &str);
            void start();
            double getMultiplicateur();
            int getNumberCuisinier();
            int getRegen();

        protected:
    };
}


#endif /* !RUN_HPP */
