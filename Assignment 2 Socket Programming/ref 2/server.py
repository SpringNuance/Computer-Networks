from socket import *
import threading

from datetime import datetime

QUIT = False

class Server:
    def __init__(self):
        self.host = "127.0.0.1"
        self.port = 9999
        self.threads = []
        self.backlog = 10
        self.clients = {} # list of clients - dict of name - socket
        self.groups = {} # list of groups - dict of group creator - group thread 

    def run(self):
        try:
            all_good = False
            self.sock = socket(AF_INET, SOCK_STREAM)
            self.sock.bind((self.host, self.port))
            self.sock.listen(self.backlog)
            all_good= True
            print("Server started at "+self.host+":"+str(self.port))
        except Exception as err:
            print('Socket connection error... ')
            self.sock.close()
        try:
            while not QUIT:
                try:
                    client, addr = self.sock.accept() #accepting incoming clients' connections
                except socket.timeout:
                    continue
                new_thread = Client(client)  #creating the client's thread
                print("Connected by ", addr)
                """msg = ("Connected by %s at %s" %(new_thread.name, addr)).encode()
                for each in self.threads:
                    each.client.send(msg)"""

                self.threads.append(new_thread) #adding the new client's thread to the thread list
                new_thread.start()

                for thread in self.threads:
                    if not thread.is_alive():
                        self.threads.remove(thread)
                        thread.join()

        except KeyboardInterrupt:
                print("Terminating by Ctrl+C")
        except Exception as err:
            print("Exception: %s\nClosing" %err)
        for thread in self.threads:
            thread.join()
        self.sock.close()


class Client(threading.Thread):
    def __init__(self, client):
        threading.Thread.__init__(self)
        self.client = client

    def run(self):
        global QUIT
        done = False

        while not done:
            try:
                cmd = self.client.recv(1024).decode()
                if cmd.startswith("/name"):
                    self.client.send("Enter your username: ".encode())
                    old_name = self.name
                    self.name = self.client.recv(1024).decode()
                    msg = "%s has changed his username to %s" %(old_name, self.name)
                    for each in server.threads:
                        if each != self and each.is_alive():
                            each.client.send(msg.encode())
                    self.client.send(("Your username has been changed to %s" %self.name).encode())
                elif cmd.startswith("/username"):
                    old_name = self.name
                    trash, self.name = cmd.split(".")
                    msg = self.name + " is connected"
                    for each in server.threads:
                        if each.is_alive():
                            each.client.send(msg.encode())
                elif cmd == "/quit":
                    self.client.send("exit".encode())
                    server.threads.remove(self)
                    for each in server.threads:
                            each.client.send(("%s Disconnected" %self.name).encode())
                    QUIT = True
                    done = True
                elif cmd.startswith("/pm"):
                    self.client.send(("Enter the username of the person you wanna send a private message: ").encode())
                    desti = self.client.recv(1024).decode()

                    sent = False
                    for each in server.threads:
                        print(each.name)
                        now = datetime.now()
                        time_message = now.strftime("%d/%m/%y %H:%M:%S")
                        if each.name == desti:
                            print("pseudo ok")

                            self.client.send(("Enter your message: ").encode())
                            mes = self.client.recv(1024).decode()
                            message = time_message + " " + self.name +"(PM) >>> "+mes
                            each.client.send(message.encode())
                            sent = True
                    if sent == False:
                        self.client.send(("this pseudo doesn't exist").encode())

                else:
                    now = datetime.now()
                    time_message = now.strftime("%d/%m/%y %H:%M:%S")
                    msg = time_message + " " + self.name+" >>> "+cmd
                    msg = msg.encode()
                    for each in server.threads:
                        if each != self:
                            each.client.send(msg)
            except Exception as e:
                print("Connection lost", e)
                self.client.close()
                done = True
                continue

        self.client.close()
        return

def broadcast(clients, msg, prefix=""):  # prefix is for name identification.
    for sock in clients:
        sock.send(bytes(prefix, "utf8") + msg)

if __name__ == "__main__":
    server = Server()
    server.run()

    print("Terminated")