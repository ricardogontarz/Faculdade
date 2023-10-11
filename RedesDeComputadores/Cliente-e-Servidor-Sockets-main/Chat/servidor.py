import socket
import threading

HOST = '0.0.0.0'
PORT = 50001

def handle_client(client_socket, address):
    print('Conexão estabelecida com', address)

    while True:
        data = client_socket.recv(1024).decode('utf-8')

        if data == 'tt':
            break

        print('Cliente:', data)

    print('Conexão encerrada com', address)
    client_socket.close()

def get_user_input(client_socket):
    while True:
        message = input().encode('utf-8')
        client_socket.send(message)

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind((HOST, PORT))
    server.listen(5)
    print('Aguardando conexão de um cliente')

    while True:
        client_socket, address = server.accept()
        client_thread = threading.Thread(target=handle_client, args=(client_socket, address))
        client_thread.start()

        input_thread = threading.Thread(target=get_user_input, args=(client_socket,))
        input_thread.daemon = True
        input_thread.start()

main()
