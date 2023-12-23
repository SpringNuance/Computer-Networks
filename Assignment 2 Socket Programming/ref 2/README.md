# Chat Application avec Python

## Présentation de l'application

Côté Serveur :
* Le but principal du serveur est d'écouter le port et de gérer les informations entrantes (envoi de message + nouveau client qui souhaite se connecter au serveur de chat).
* Le serveur accepte le nouveau client et chaque client qui se connecte au chat, le serveur gère la création des threads clients et ajoute ensuite le thread à la liste des threads clients.
* Le serveur décode toutes les informations reçues qui proviennent du bon fil client.
* En fonction des messages reçus par le serveur, le serveur exécute une tâche particulière. Le serveur gère les discussions privées lorsque l'utilisateur spécifie le nom de l'utilisateur à qui il veut envoyer un message privé.
* Le serveur peut gérer 10 clients connectés en même temps au salon de discussion.
* Le serveur notifie à tous les utilisateurs qu'un nouvel utilisateur est connecté au chat.

Côté Client : 

* L'utilisateur peut via l'aide de certaines commandes effectuer diverses actions comme envoyer un message privé à un utilisateur en particulier ou bien envoyé un message à plusieurs personnes en même temps.

## Lancement de l'application

1. Lancer un serveur 
2. Lancez le client et tapez le nom d'utilisateur 
3. Exécutez un autre client et tapez le nom d'utilisateur 
4. Exécutez un autre client et tapez le nom d'utilisateur
...
5. Exécutez jusqu'à 10 clients

## Fonctionnalités

* Envoyer un message normal et montrer que toutes les personnes connectées au salon de discussion reçoivent le message.
* Envoyer un message privé à un utilisateur en particulier 

Par défaut, toutes les personnes connectées au chat reçoivent le message.

## Usage

`/pm` : Envoyer un message privé en spécifiant le nom de l'utilisateur

`/name` : Changer le nom d'utilisateur

`/quit` : Quitter le salon de discussion

## Snapshot de l'application

**Client 1**

![](https://github.com/hugo-mi/Chat_Application/blob/main/Images/Client_log2.png)

**Client 2**

![](https://github.com/hugo-mi/Chat_Application/blob/main/Images/Client_Log1.png)

**Server log**

![](https://github.com/hugo-mi/Chat_Application/blob/main/Images/Server_log.png)

