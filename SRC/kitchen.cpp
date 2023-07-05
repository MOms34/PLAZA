/*
** EPITECH PROJECT, 2023
** epitech
** File description:
** momoo
*/

#include "kitchen.hpp"
#include <cstring>


namespace plazza {

    std::mutex coutMutex;
    Kitchen::Kitchen(reception &Reception, int msgQueueId) : pid(getpid()), recep(Reception), messageQueueId(msgQueueId)
    {
        // std::lock_guard<std::mutex> lock(coutMutex);
        // std::cout << "cuisine with identifiant " << pid << " is creat" << "\n";
        key_t key = ftok(".", 'M');
        messageQ = msgget(key, 0666);
        key_t kitchenReceptionKey = ftok(".", 'A');
        kitchenReceptionMsgQueueId = msgget(kitchenReceptionKey, 0666);

    }


    Kitchen::~Kitchen()
    {

    }
    void Kitchen::sendMessageToReception(const std::string& message) {
        Message response;
        response.type = getppid();
        std::memset(response.data, 0, sizeof(response.data));
        std::strncpy(response.data, "La regina est prete", sizeof(response.data) - 1);

        if (msgsnd(messageQ, &response, sizeof(Message) - sizeof(long), 0) == -1) {
            std::cerr << "Erreur lors de l'envoi de la réponse de l'enfant vers le parent" << std::endl;
        }
    }
    void Kitchen::start()
{
    while (true) {
        // Recevoir un message du processus parzent
        Message message;
        if (msgrcv(messageQ, &message, sizeof(Message) - sizeof(long), getpid(), 0) == -1) {
            std::cerr << "Erreur lors de la réception du message du parent vers l'enfant" << std::endl;
        }

        // Traiter le message
        if (message.data != nullptr) {
            // std::lock_guard<std::mutex> lock(g_display_mutex); // Verrouillage du verrou
            std::cout << "Cuisine " << getpid() << " a reçu la commande : " << message.data << std::endl;
        }

        // Envoyer une réponse au processus parent
        sendMessageToReception("commande est prete");
    }
}

}