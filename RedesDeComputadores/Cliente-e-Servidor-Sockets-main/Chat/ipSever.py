import socket
def get_server_ip():
    hostname = socket.gethostname()
    ip_address = socket.gethostbyname(hostname)
    return ip_address

server_ip = get_server_ip()
print("Endereço IP do servidor:", server_ip)