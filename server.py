import socket

# Función para leer la tabla de traducción desde un archivo de texto
def leer_txt(nombre_archivo):
    tabla = {}
    with open(nombre_archivo, "r") as file:
        for line in file:
            domain, ip = line.strip().split(',')
            tabla[domain] = ip
    return tabla

# Dirección IP y puerto del servidor
server_ip = '10.161.62.254'
server_port = 4455

# Nombre del archivo que contiene la tabla de traducción
archivo_tabla = "dns.txt"

# Cargar la tabla de traducción desde el archivo
tabla = leer_txt(archivo_tabla)

# Crear un socket TCP/IP
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Enlazar el socket al puerto
server_address = (server_ip, server_port)
print(f"Iniciando servidor en {server_ip} puerto {server_port}")
sock.bind(server_address)

while True:
    print("Esperando conexión...")
    data, client_address = sock.recvfrom(1024)
    print(f"Solicitud recibida de {client_address}: {data.decode()}")
   
    if data.decode() in tabla:
        response = tabla[data.decode()]
    elif data.decode() in tabla.values():
        for element in tabla:
            if tabla[element] == data.decode():
                response = element
    else:
        response = "No se encontró la IP o dominio en la tabla"

    sock.sendto(response.encode(), client_address)
