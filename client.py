import socket
import webbrowser
import datetime

def search(url):

    webbrowser.open("https://" + url)

def get_ip():
    hostname = socket.gethostname()
    ip_address = socket.gethostbyname(hostname)
    return ip_address

# Dirección IP y puerto del servidor
server_ip = '10.161.47.238'  # Cambiar por la IP del servidor
server_port = 53  # Cambiar por el puerto del servidor

# Crear un socket UDP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

try:
    # Enviar solicitud al servidor
    message = input("Ingrese dominio o IP: ")
    sock.sendto(message.encode(), (server_ip, server_port))
    
    # Recibir respuesta del servidor
    response, _ = sock.recvfrom(1024)
    response = response.decode()
    
    ip = get_ip()
    time = datetime.datetime.now()
    date = time.strftime("%Y-%m-%d %H:%M:%S")
    print(f"Respuesta del servidor: {response}")

    # Actualizar archivo con la solicitud y la respuesta
    with open("registro.txt", "a") as file:
        file.write(f"Fecha y hora: {date}, IP_Cliente: {ip}, Puerto: {server_port}, Solicitud: {message}, Respuesta: {response}\n")

    print(f"Redirigiendo a {response}")
    
    search(response)

finally:
    print("Cerrando conexión")
    sock.close()
