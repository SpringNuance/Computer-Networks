from socket import *
import sys
import threading
host = "127.0.0.1"
port = 9999


class listen(threading.Thread):

    def __init__(self, client):
        threading.Thread.__init__(self)
        self.client = client
    

    def run(self):
        while True:
            data = self.client.recv(1024)
            if data.decode() == "exit":
                sys.exit(1)
            print(data.decode())


if __name__ == "__main__":
    try:
        clientSocket = socket(AF_INET, SOCK_STREAM)
        clientSocket.connect((host, port))
    except error as e:
            if clientSocket:
                clientSocket.close()
            print("Could not open a socket: "+ str(e))
            sys.exit(1)
    l = listen(clientSocket)
    l.start()

    print("Welcome to chat!")
    print("Type your message and press 'Enter' to send.")
    print("Send '/pm' command to send a private message.")
    print("Send '/rename' command to change your username.")
    print("Type '/exit' command to exit the current chat or group.")
    print("Type '/create' command to create a new chat group")
    print()

    print("Send '/quit' command to quit from the server.")

    message = input("Please enter your username: ")
    message = str("/username."+message)


    while message!="/quit":
        message = message.encode()
        clientSocket.send(message)
        message = input(">>> ")

    clientSocket.close()