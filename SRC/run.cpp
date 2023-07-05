/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "run.hpp"
#include "reception.hpp"

namespace plazza {
    run::run(int argc, char **av) : ac(argc), argv(av)
    {
        if (check_arg() == -1)
            exit(FAIL);
        std::cout << "Multiplicateur : " << multiplicateur << std::endl;
        std::cout << "Nombre de cuisiniers : " << cuisiniers << std::endl;
        std::cout << "Temps de régénération : " << regen << std::endl;
        start();
        exit(SUCESS);
    }

    run::~run()
    {

    }

    bool run::isNumberPos(const std::string& str)
    {
        if (str.empty()) {
            return false;
        }
        for (char c : str) {
            if (!isdigit(c)) {
                return false;
            }
        }
        int valeur = std::stoi(str);
        if (valeur <= 0) {
            return false;
        }
        return true;
    }

    int run::check_arg()
    {
        if (ac != 4) {
            std::cerr << "Erreur : Nombre d'arguments incorrect." << std::endl;
            return -1;
        }
        for (int i = 1; i < 4; i++) {
            std::string check = std::string(argv[i]);
            if (isNumberPos(check) == false) {
                std::cerr << "Erreur argument invalide : " << check << std::endl;
                return -1;
            }
        }
        multiplicateur = std::atof(argv[1]);
        cuisiniers = std::atoi(argv[2]);
        regen = std::atoi(argv[3]);
        if (multiplicateur <= 0 || multiplicateur > 1) {
            std::cerr << "Erreur : Le multiplicateur doit être un nombre réel entre 0 et 1." << std::endl;
            return -1;
        }

        if (cuisiniers <= 0) {
            std::cerr << "Erreur : Le nombre de cuisiniers doit être un entier positif." << std::endl;
            return -1;
        }

        if (regen <= 0) {
            std::cerr << "Erreur : Le temps de régénération doit être un entier positif." << std::endl;
            return -1;
        }
        return 0;
    }

    double run::getMultiplicateur()
    {
        return multiplicateur;

    }

    int run::getNumberCuisinier()
    {
        return cuisiniers;
    }

    int run::getRegen()
    {
        return regen;
    }

    void run::start()
    {
        reception Reception(*this);
        Reception.startShell();
        
    }

}