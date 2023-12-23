"""Server for multithreaded (asynchronous) chat application."""
from socket import AF_INET, AF_INET6, socket, SOCK_STREAM
from threading import Thread


def accept_incoming_connections():
    while True:
        client, client_address = SERVER.accept()
        print("%s:%s has connected." % client_address)
        client.send(bytes("Please enter your name and start chatting", "utf8"))
        addresses[client] = client_address
        Thread(target=handle_client, args=(client,)).start()


def handle_client(client):  # Takes client socket as argument.
    name = client.recv(BUFSIZ).decode("utf8")
    welcome = 'Hello %s! If you want to quit, type "quit" to exit' % name
    client.send(bytes(welcome, "utf8"))
    msg = "%s has enter the group chat" % name
    broadcast(bytes(msg, "utf8"))
    clients[client] = name

    while True:
        msg = client.recv(BUFSIZ)
        if msg != bytes("quit", "utf8"):
            broadcast(msg, name + ": ")
        if msg == bytes("connect", "utf8"):
            client.send(bytes("Who do you want to connect to?", "utf8"))
            otherClientName = client.recv(BUFSIZ).decode("utf8")
            otherClient = None
            for sock in clients:
                if clients[sock] == otherClientName:
                    otherClient = sock
                    break
            otherClient.send("Do you want to receive a connect request?")
            print(otherClient)
            while True:
                p2p = client.recv(BUFSIZ)
                otherClient.send(p2p)
        if msg == bytes("Do you want to receive a connect request?", "utf8"):
            confirmation = client.recv(BUFSIZ)
            if confirmation == bytes("yes", "utf8"):
                otherClientName = client.recv(BUFSIZ).decode("utf8")
                otherClient = None
                for sock in clients:
                    if clients[sock] == otherClientName:
                        otherClient = sock
                        break
                while True:
                    p2p = client.recv(BUFSIZ)
                    otherClient.send(p2p)

        else:
            client.send(bytes("{quit}", "utf8"))
            client.close()
            del clients[client]
            broadcast(bytes("%s has exitted the group chat" % name, "utf8"))
            break


def broadcast(msg, prefix=""):  # prefix is for name identification.
    for sock in clients:
        sock.send(bytes(prefix, "utf8") + msg)


clients = {}
addresses = {}
groups = {}

HOST = ''
PORT = 33000
BUFSIZ = 1024
ADDR = (HOST, PORT)

SERVER = socket(AF_INET, SOCK_STREAM)
SERVER.bind(ADDR)

if __name__ == "__main__":
    SERVER.listen(5)
    print("Waiting for the clients to connect...")
    ACCEPT_THREAD = Thread(target=accept_incoming_connections)
    ACCEPT_THREAD.start()
    ACCEPT_THREAD.join()
    SERVER.close()