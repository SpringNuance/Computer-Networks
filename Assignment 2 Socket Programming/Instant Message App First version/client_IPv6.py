from socket import AF_INET6, socket, SOCK_STREAM
from threading import Thread


localhost_IPv6 = "0:0:0:0:0:0:0:1"
port_IPv6 = 36000
buffer = 1024
backlog = 5

def receive():
    while True:
        message = clientSocketIPv6.recv(buffer).decode("utf8")
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
        clientSocketIPv6.send(bytes(message, "utf8"))
        message = input(">>> ")
    print("You have quitted from the server. See you again")
    clientSocketIPv6.send(bytes(message, "utf8"))

if __name__ == "__main__":
    clientSocketIPv6 = socket(AF_INET6, SOCK_STREAM)
    address_IPv6 = (localhost_IPv6, port_IPv6)
    clientSocketIPv6.connect(address_IPv6)
        
    receive_thread = Thread(target=receive)
    send_thread = Thread(target=send)
    receive_thread.start()
    send_thread.start()