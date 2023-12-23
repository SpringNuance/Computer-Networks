from socket import AF_INET, getaddrinfo, socket, SOCK_STREAM
from threading import Thread

localhost_IPv4 = "127.0.0.1"
# 192.168.1.208
# public ipv4 address of my local computer 78.27.114.0 Disable firewall
# punch a hole through my router 
# client would run on any laptop
port_IPv4 = 34000
buffer = 1024
backlog = 5

def receive():
    while True:
        message = clientSocketIPv4.recv(buffer).decode("utf8")
        if message.startswith("The file has been successfully saved"):
            fileData = message.split("\n")[1]
            fileName = message.split("\n")[2]
            newFile = open(fileName, "a")
            newFile.write(fileData)
            newFile.close()
        else:
            print(message)

def send():
    message = input(">>> ")
    while message != "/quit":
        clientSocketIPv4.send(bytes(message, "utf8"))
        message = input(">>> ")
    print("You have quitted from the server. See you again")
    clientSocketIPv4.send(bytes(message, "utf8"))

if __name__ == "__main__":
    clientSocketIPv4 = socket(AF_INET, SOCK_STREAM)
    address_IPv4 = (localhost_IPv4, port_IPv4)
    clientSocketIPv4.connect(address_IPv4)
    # instead of connecting local host ipv4, actually connect to the public ipv4 of this local computer
    receive_thread = Thread(target=receive)
    send_thread = Thread(target=send)
    receive_thread.start()
    send_thread.start()