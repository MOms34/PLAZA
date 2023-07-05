/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#ifndef PROCESSFORK_HPP
    #define PROCESSFORK_HPP
    #include <iostream>
    #include <vector>
    #include <unistd.h>
    #include <sys/wait.h>

namespace plazza {
    class processFork {
        private:
             pid_t pid;
        public:
            void createKitchen()
            {
                pid = fork();

                if (pid < 0) {
                    std::cerr << "Erreur lors de la création de la cuisine avec fork()" << std::endl;
                }
            }

            bool isChild() const {
                return pid == 0;
            }

            pid_t getPID() const {
                return pid;
            }
        protected:

    };

}


#endif /* !PROCESSFORK_HPP */
