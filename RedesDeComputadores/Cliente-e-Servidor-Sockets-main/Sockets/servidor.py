import socket
import threading

HOST = '0.0.0.0'  # Endereço IP do host local
PORT = 50001  # Porta para escutar as conexões

def handle_client(client_socket, address):
    print('Conexão estabelecida com', address)

    while True:
        data = client_socket.recv(1024).decode('utf-8')  # Recebe dados do cliente

        if data == 'tt':  # Se o cliente enviar 'tt', encerra a conexão
            break

        print('Cliente:', data)  # Exibe a mensagem recebida do cliente

    print('Conexão encerrada com', address)
    client_socket.close()  # Fecha o socket do cliente

def main():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Cria um objeto socket
    server.bind((HOST, PORT))  # Associa o socket ao endereço e porta especificados
    server.listen(5)  # Inicia a escuta por conexões
    print('Aguardando conexão de um cliente')

    while True:
        client_socket, address = server.accept()  # Aceita a conexão de um cliente
        client_thread = threading.Thread(target=handle_client, args=(client_socket, address))  # Cria uma nova thread para lidar com o cliente
        client_thread.start()  # Inicia a thread

# Início do programa
main()
