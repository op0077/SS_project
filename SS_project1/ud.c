# include "headerfiles.h"

#define PORT 8080
#define MAX_BUFFER_SIZE 256

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[MAX_BUFFER_SIZE];

    // Create the socket
    client_socket = socket(AF_INET, SOCK_DGRAM, 0);
    if (client_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Connect to the server
    int ct;
    ct = connect(client_socket,(struct sockaddr*)&server_addr,sizeof(server_addr));
    if (ct < 0) {
        perror("Connection failed");
        exit(1);
    }
    int n;
    while (1) {
        char ans[MAX_BUFFER_SIZE];
        // buffer[0]='\0';
        // printf("%s\n %ld\n", buffer,strlen(buffer));
        memset(buffer,0,MAX_BUFFER_SIZE);
        // printf("%s\n %ld\n", buffer,strlen(buffer));
        n = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
        // printf("%s\n",buffer);
        if(n< 0)
        {
            perror("Connection closed by server");
            exit(1);
        }
        // system("clear");
        printf("%s\n %ld\n", buffer,strlen(buffer));
        fgets(ans, MAX_BUFFER_SIZE, stdin);
        // printf("%s\n",ans);
        n = send(client_socket, ans, strlen(buffer), 0);
        if(n< 0)
        {
            perror("Msg didn't send");
            exit(1);
        }
    }

    close(client_socket);
    return 0;
}
