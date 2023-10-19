# include "headerfiles.h"
# include "handle_admin.c"
# include "handle_faculty.c"
# include "handle_student.c"
#define PORT 8081
#define MAX_BUFFER_SIZE 1024
void handle_msgs(int client_socket)
{
    char buffer[MAX_BUFFER_SIZE];
    char ans[30];
    // buffer[0]='\0';
    // printf("%s\n %ld\n", buffer,strlen(buffer));
    // memset(buffer,0,MAX_BUFFER_SIZE);
    // printf("%s\n %ld\n", buffer,strlen(buffer));
    memset(&buffer,0,MAX_BUFFER_SIZE);
    int n = recv(client_socket, buffer, MAX_BUFFER_SIZE, 0);
    // printf("buffer = %s\n",buffer);
    if(n< 0)
    {
        perror("Connection closed by server");
        exit(1);
    }
    else if(buffer=="")
    {
        printf("here = %s\n",buffer);
        perror("Done");
        exit(0);
    }
    // system("clear");
    printf("%s", buffer);
    // fgets(ans,sizeof(ans),stdin);
    memset(&ans,0,sizeof(ans));
    scanf("%s",ans);
    // printf("%s\n",ans);
    // if(buffer)
    n = send(client_socket, ans, sizeof(ans), 0);
    if(n==-1)
    {
        // perror("Msg didn't send");
        // exit(0);
    }
}
int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    // char buffer[MAX_BUFFER_SIZE];

    // Create the socket
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
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
        handle_msgs(client_socket);
    }

    close(client_socket);
    return 0;
}
