#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define MAX_LINE_LENGTH 1024
#define SERVER_PORT 4455

// Función para leer la tabla de traducción desde un archivo de texto
void leer_txt(char *nombre_archivo, char tabla[][MAX_LINE_LENGTH], int *num_entries) {
    FILE *file = fopen(nombre_archivo, "r");
    if (file == NULL) {
        printf("No se pudo abrir el archivo %s\n", nombre_archivo);
        exit(1);
    }
    
    *num_entries = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) != NULL) {
        char *token = strtok(line, ",");
        strcpy(tabla[*num_entries], token);
        token = strtok(NULL, ",");
        strcpy(tabla[*num_entries + 1], token);
        (*num_entries) += 2;
    }
    fclose(file);
}

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int bytes_received;
    char tabla[MAX_LINE_LENGTH][MAX_LINE_LENGTH];
    int num_entries;
    char buffer[MAX_LINE_LENGTH];

    // Leer la tabla de traducción desde el archivo
    leer_txt("dns.txt", tabla, &num_entries);

    // Create socket
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    // Prepare the sockaddr_in structure
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(SERVER_PORT);

    // Bind
    if (bind(sockfd, (const struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Error al enlazar el socket");
        exit(EXIT_FAILURE);
    }

    printf("Iniciando servidor en el puerto %d\n", SERVER_PORT);

    while (1) {
        printf("Esperando conexión...\n");

        // Receive data from client
        bytes_received = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &client_addr_len);
        if (bytes_received < 0) {
            perror("Error al recibir datos del cliente");
            continue;
        }
        buffer[bytes_received] = '\0';

        printf("Solicitud recibida de %s:%d: %s\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        // Search for translation in table
        char response[MAX_LINE_LENGTH];
        int found = 0;
        for (int i = 0; i < num_entries; i += 2) {
            if (strcmp(buffer, tabla[i + 1]) == 0) { // Buscar en las IPs
                strcpy(response, tabla[i]);
                found = 1;
                break;
            } else if (strcmp(buffer, tabla[i]) == 0) { // Buscar en los dominios
                strcpy(response, tabla[i + 1]);
                found = 1;
                break;
            } else if (strcmp(buffer, tabla[i + 1]) == 0 || strcmp(buffer, tabla[i]) == 0) { // Cambio añadido para tratar dominios e IPs directamente
                strcpy(response, tabla[i]);
                found = 1;
                break;
            }
        }
        
        if (found)
            printf("Respuesta enviada al cliente: %s\n", response);
        else
            printf("No se encontró la IP o dominio en la tabla\n");

        // Send response to client
        sendto(sockfd, response, strlen(response), 0, (const struct sockaddr *)&client_addr, client_addr_len);
    }

    // Cleanup
    close(sockfd);
    return 0;
}
