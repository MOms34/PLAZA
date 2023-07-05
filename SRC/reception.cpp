/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momo
*/

#include "reception.hpp"
#include "run.hpp"
#include <regex>


namespace plazza {
    bool reception::quit = false;

    reception::reception(run &instance) : Run(instance)
    {
        multiplicateur = Run.getMultiplicateur();
        regen = Run.getRegen();
        cuisiniers = Run.getNumberCuisinier();
        // key_t key = ftok(".", 'm');
        // messageQueueId = msgget(key, IPC_CREAT | 0666);
        // messageQueueId = msgget(IPC_PRIVATE, IPC_CREAT | 0666);
        key_t kitchenReceptionKey = ftok(".", 'A');
        kitchenReceptionMsgQueueId = msgget(kitchenReceptionKey, IPC_CREAT | 0666);
        if (messageQueueId == -1) {
            std::cerr << "Erreur lors de la création de la file de messages" << std::endl;
            exit(1);
        }
        key_t key = ftok(".", 'M');
        messsageQ = msgget(key, IPC_CREAT | 0666);
    }
    pid_t reception::getMyPid()
    {
        return getpid();
    }



    void reception::signalHandler(int signal)
    {
        if (signal == SIGINT || signal == SIGTSTP) {
            quit = true;
        }
    }
    
    reception::~reception()
    {
    }

    PizzaType reception::getPizzaType(std::string namePizza)
    {
        if (namePizza == "regina")
            return Regina;
        else if (namePizza == "margarita")
            return Margarita;
        else if (namePizza == "americana")
            return Americana;
        else if (namePizza == "fantasia")
            return Fantasia;
        return Nop;
    }

    PizzaSize reception::getPizzaSize(std::string size)
    {
        if (size == "S")
            return S;
        if (size == "M")
            return M;
        if (size == "L")
            return L;
        if (size == "XL")
            return XL;
        if (size == "XXL")
            return XXL;
        return Noop;
    }

    cmdPizza reception::getCmdSimple(std:: string namePizza, std::string size, int number)
    {
        return {getPizzaType(namePizza), getPizzaSize(size), number};
    }

    std::queue<cmdPizza> reception::getCommandParse()
    {
        return getCommandParse();
    }

    void reception::parsecmd()
    {
        std::istringstream iss(cmd.front());
        std::string subCommand;
        
        while (std::getline(iss, subCommand, ';')) {
            std::istringstream subIss(subCommand);
            std::string namePizza, sizePizza, pizzaNum;
            int pizzaNumber;
            
            if (subIss >> namePizza >> sizePizza >> pizzaNum) {
                if (pizzaNum.find('x') != std::string::npos && pizzaNum.front() == 'x') {
                    pizzaNum.erase(0, 1);
                    pizzaNumber = std::stoi(pizzaNum);
                } else {
                    std::cout << "Erreur de format dans la sous-commande : " << subCommand << std::endl;
                    return;
                }    
                std::cout << "Nom de la pizza = " << namePizza  << " taille des pizza " << sizePizza << " nombre de pizza = " << pizzaNumber << "\n";
                listCmd.push(getCmdSimple(namePizza, sizePizza, pizzaNumber));
            } else {
                std::cout << "Erreur de format dans la sous-commande : " << subCommand << std::endl;
            }
        }
    }

    int reception::checkCmd()
    {
        if (cmd.front().empty()) {
            std::cout << "La commande est invalide.\n";
            return -1;
        }
        std::regex regex("([a-zA-Z]+) (S|M|L|XL|XXL) x[1-9][0-9]*(; ([a-zA-Z]+) (S|M|L|XL|XXL) x[1-9][0-9]*)*");
        if (!std::regex_match(cmd.front(), regex)) {
            std::cout << "La commande est invalide.\n";
            return -1;
        }
        return 0;
    }
    
    void reception::listProcess()
    {
        int i = 0;
        for (const auto& pid : kitchenPids) {
            std::cout << "Processus de cuisine créé avec l'identifiant : " << pid << std::endl;
            i++;
        }

    }


    std::vector<pid_t> reception::getListPid()
    {
        return kitchenPids;
    }

    void reception::creatKitchen(int number)
    {

        for (int i = 0; i < number; ++i) {
            pid_t pid = fork();
            if (pid == -1) {
                std::cerr << "Erreur lors de la création du processus de cuisine" << std::endl;
                exit(1);
            } else if (pid == 0) {
                // Code exécuté par le processus de cuisine
                Kitchen kitchen_(*this, messageQueueId);
                kitchen_.start();
            } else {
                // Ajouter l'identifiant du processus de cuisine à la liste
                kitchenPids.push_back(pid);
            }
        }
     
    }
    void reception::killAllProcess()
    {
        for (const auto& pid : kitchenPids) {
            kill(pid, SIGTERM);
            int status;
            waitpid(pid, &status, 0);
            // Vérifiez le statut du processus terminé
            if (WIFEXITED(status)) {
                std::cout << "Le processus avec PID " << pid << " s'est terminé normalement avec le code de sortie : " << WEXITSTATUS(status) << std::endl;
            } else if (WIFSIGNALED(status)) {
                std::cout << "Le processus avec PID " << pid << " s'est terminé avec un signal : " << WTERMSIG(status) << std::endl;
            }
        }
    }

    void reception::sendCommandToKitchen(int kitchenId, const std::string& command)
    {
        Message message;
        message.type = kitchenId;
        std::memset(message.data, 0, sizeof(message.data));  // Initialiser la mémoire à 0
        std::strncpy(message.data, command.c_str(), sizeof(message.data) - 1);

        // Envoyer le message à la file de messages de la cuisine
        if (msgsnd(messsageQ, &message, sizeof(Message) - sizeof(long), 0) == -1) {
            std::cerr << "Erreur lors de l'envoi du message" << std::endl;
        }
        Message response;
        memset(response.data, 0, sizeof(response.data));
        if (msgrcv(messsageQ, &response, sizeof(Message) - sizeof(long), getpid(), 0) == -1) {
            std::cerr << "Erreur lors de la réception de la réponse" << std::endl;
        } else {
            // Traiter la réponse reçue du processus enfant
            std::cout << "Réponse reçue du processus enfant : " << response.data << std::endl;
        }
    }




    void reception::waitForChildren() {
        int status;
        while (wait(&status) != -1) {
            // Traiter les processus terminés
        }
    }
    int reception::getKeyReception()
    {
        return kitchenReceptionMsgQueueId;
    }
//     void reception::receiveMessageFromKitchen()
// {
//         Message message;

//     // Vérifier si un message est disponible dans la file de messages provenant d2es cuisines
//     if (msgrcv(kitchenReceptionMsgQueueId, &message, sizeof(message.data), 1, IPC_NOWAIT) != -1) {
//         std::lock_guard<std::mutex> lock(g_display_mutex); // Verrouillage du verrou

//         // Afficher le message provenant de la cuisine
//         std::cout << "Message reçu de la cuisine : " << message.data << std::endl;
//     }
// }

    void reception::startShell()
    {
        std::signal(SIGINT, signalHandler);
        std::signal(SIGTSTP, signalHandler);

        while (!quit) {
            std::string command;
            std::cout  << " Entrez votre commande (Ctrl+C pour quitter) et appuer sur Entrer pour terminer : ";
            std::getline(std::cin, command);
            // receiveMessageFromKitchen();

            if (command.find('\n') == std::string::npos)
                std::cout << "putin \n";
            if (!command.empty() && command.back() == '\n') {
                command.erase(command.size() - 1);
            }
            cmd.push(std::string(command));
            if (checkCmd() != -1 && quit == false) {
                std::cout << "la derniere commande c " << cmd.front() << std::endl;
                parsecmd();
                creatKitchen(1);
                listProcess();
                
                    std::cout << "dans la \n";
                    // std::lock_guard<std::mutex> lock(g_display_mutex);  // Ajouter le verrou ici
                    
                    sendCommandToKitchen(kitchenPids.front(), "regina XL 2");
                    sleep(3);

                listCmd.pop();
                cmd.pop();
            }
            if (quit) {
                killAllProcess();
                exit(SUCESS);
            }
        }
    }

}