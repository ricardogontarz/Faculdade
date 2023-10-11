import socket
import threading

def enviar_mensagem(cliente):
    while True:
        mensagem = input()
        cliente.send(mensagem.encode('utf-8'))

def receber_mensagem(cliente):
    while True:
        data = cliente.recv(1024).decode('utf-8')

        if data == 'tt':
            print('Conexão encerrada pelo servidor.')
            break

        print('Servidor: ',data)

def main():
    HOST = 'localhost'
    PORT = 50001

    cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    try:
        cliente.connect((HOST, PORT))
        print('Conectado ao servidor.')

        print('Digite "tt" para terminar o chat.')

        # Iniciar as threads para enviar e receber mensagens
        thread_enviar = threading.Thread(target=enviar_mensagem, args=(cliente,))
        thread_receber = threading.Thread(target=receber_mensagem, args=(cliente,))

        thread_enviar.start()
        thread_receber.start()

        # Aguardar o término das threads
        thread_enviar.join()
        thread_receber.join()

    except ConnectionRefusedError:
        print('Não foi possível conectar ao servidor.')
    except Exception as e:
        print('Ocorreu um erro:', str(e))

    cliente.close()

if __name__ == '__main__':
    main()
