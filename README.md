# Telematica

Miguel Martínez García
Camilo Enrique Soto
Simón Botero Villarraga

## 1. Introducción:
Mediante el siguiente proyecto se busca implementar un servidor DNS (Domain Name System), con el fin de demostrar y aplicar algunos de los conocimientos obtenidos en clase. El objetivo del proyecto es desarrollar un código servidor que reciba peticiones a través de un socket UDP, que le permitirá recibir, procesar y retornar la solicitud de manera correcta, simulando un DNS. Además de esto, se tiene un código cliente que envía las peticiones al servidor por medio del socket, el cual recibe el retorno del servidor, obteniendo respuesta a la solicitud enviada.

## 2. Desarrollo
En un primer momento, se investigó la manera en que funciona un DNS. Además de esto, se creó una instancia EC2 en AWS, la cuál permite compilar y correr el código servidor. 
Por otro lado, se procedió con el desarrollo del cliente en Python (client.py). El servidor cliente se encuentra programado para pedir una consulta al usuario, y a través de la API de socket, se encarga de enviar la solicitud por medio de un puerto UDP al servidor DNS que se encuentra en la instancia EC2 de AWS.
Continuando con el desarrollo del proyecto, se procedió a implementar el servidor (server.c) teniendo en cuenta el manejo que este le debe dar a cada una de las solicitudes del cliente, ya que en caso de recibir un dominio web, este debe de retornar su correspondiente IP, y viceversa. 
Antes de finalizar, se procede a realizar la conexión entre cliente y servidor por medio del socket UDP y a través de la IP en la que se ejecute el servidor.  
Por último, se reestructuran los códigos con el fin de leer los datos de dominios e IP y con el fin de escribir en un archivo .txt la consulta y respuesta de cada una de las peticiones enviadas por el cliente.

Comandos para ejecutar código en Python:
1. python server.py
2. python client.py

Comandos para ejecutar código en C:
1. gcc -o server server.c -lws2_32 
2. ./server <port>
3. python client.py

*Nota:* Se necesita tener un programa que compile los códigos en C. En nuestro caso, usamos MinGW.

Para conectarse a la instancia, ejecutar los siguientes comandos: 
1. ssh -i "Ruta par de clave .pem" ubuntu@"IP instancia"
2. sudo apt-get update
3. sudo apt-get upgrade
4. git clone url repositorio
5. cd repositorio
6. Descargar python
7. python3 server.py

## 3. Aspectos logrados
-	Se implementó el servidor en lenguaje C
-	Se implementó el cliente en lenguaje Python
-	Se realizó la conexión de servidor – cliente por medio del socket UDP definido
-	El cliente envía la solicitud correctamente al servidor
-	El servidor recibe y da respuesta correctamente a la petición del cliente
-   Se guarda cada una de las peticiones realizadas en el archivo registro.txt

## 4. Aspectos no logrados
-	Respuesta correcta del servidor al cliente a través de la instancia EC2 de AWS.


## 5. Conclusiones
A través de la realización del proyecto, se identificó el rol de la comunicación a través de un socket UDP, pues este protocolo ligero permite una mejor implementación del servidor DNS tal y como funciona en la vida real. 
Además de esto, se comprendió la forma en la que funcionan los sockets en la programación, los cuales permiten la comunicación entre procesos. En este caso, se usaron datagram sockets para implementar el protocolo UDP.
En conclusión, se logró entender y aplicar los conceptos fundamentales del funcionamiento de un servidor DNS, así como la comunicación cliente-servidor mediante sockets en lenguajes como C y Python mediante sockets UDP. Sin embargo, se identificaron dificultades en la correcta configuración y respuesta del servidor a través de la instancia EC2 de AWS, lo cuál se debe mejorar para implementaciones futuras. 
A pesar de los aspectos no logrados, el proyecto ha cumplido con el objetivo principal de desarrollar un servidor DNS funcional capaz de recibir, procesar y responder adecuadamente a las solicitudes del cliente. La reestructuración de los códigos para leer y escribir datos de dominios e IP en archivos .txt permitió una mejor organización y documentación del proyecto

## 6. Referencias
- https://www.geeksforgeeks.org/tcp-server-client-implementation-in-c/
- https://www.youtube.com/watch?v=1Tdr9LcJt0I&t=136s&ab_channel=IdiotDeveloper
- https://www.youtube.com/watch?v=io2G2yW1Qk8&ab_channel=IdiotDeveloper
- https://www.geeksforgeeks.org/socket-programming-cc/
- https://www.geeksforgeeks.org/tcp-and-udp-server-using-select/
- https://www.geeksforgeeks.org/udp-server-client-implementation-c/
- https://www.youtube.com/watch?v=U28svzb1WUs&ab_channel=DarrellRoot
- https://csperkins.org/teaching/2007-2008/networked-systems/lecture04.pdf

## 7. Video
Este es link del video presentando el funcionamienot del proyecto: https://youtu.be/dTOEWrmdI5Y?si=Y9D_oKylOxvdY6Xz