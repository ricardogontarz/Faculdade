import socket
import threading #172.20.10.7

def enviar_mensagem(cliente):
    while True:
        mensagem = input()  # Aguarda a entrada do usuário
        cliente.send(mensagem.encode('utf-8'))  # Envia a mensagem para o servidor


def main():
    HOST = '172.20.10.2'  # Endereço IP do servidor
    PORT = 12222  # Porta do servidor

    cliente = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # Cria um objeto socket
    try:
        cliente.connect((HOST, PORT))  # Estabelece a conexão com o servidor
        print('Conectado ao servidor.')

        # Iniciar a thread para enviar mensagens
        thread_enviar = threading.Thread(target=enviar_mensagem, args=(cliente,))
        thread_enviar.start()

        # Aguardar o término da thread de envio
        thread_enviar.join()

    except ConnectionRefusedError:
        print('Não foi possível conectar ao servidor.')
    except Exception as e:
        print('Ocorreu um erro:', str(e))

    cliente.close()  # Fecha o socket do cliente

if __name__ == '__main__':
    main()
