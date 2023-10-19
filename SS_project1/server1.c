#include "headerfiles.h"

#define PORT 8080
#define MAX_BUFFER_SIZE 256

int main() {
    int server_socket, new_socket;
    struct sockaddr_in server_addr, new_addr;
    socklen_t addr_size;
    char buffer[MAX_BUFFER_SIZE];
    pid_t cpid;

    // Create the socket
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = PORT;
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket
    int ct;
    ct = bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if(ct < 0) 
    {
        perror("Binding failed");
        exit(1);
    }

    // Listen for incoming connections
    if (listen(server_socket, 10) == 0) {
        printf("Listening...\n");
    } else {
        perror("Listening failed");
        exit(1);
    }

    addr_size = sizeof(new_addr);

    // Read and echo data
    while (1) 
    {

        new_socket = accept(server_socket, (struct sockaddr*)&new_addr, &addr_size); // Accept connection
        if(new_socket<0)
        {
            exit(1);
        }
        // printf("Connected %s,%d",inet_ntoa(new_addr.sin_addr),ntohs(new_addr.sin_port));
        int ini = 0;
        int p=-1;
        char ans[MAX_BUFFER_SIZE];
        if((cpid=fork())==0)
        {
            close(server_socket);
            char ans1[MAX_BUFFER_SIZE];
            while(1)
            {
                
                if(p==-1)
                {
                    char *menu = "Enter the Choice :\n 1) Admin\n 2) Faculty\n 3) Student\n";
                    memset(ans,0,MAX_BUFFER_SIZE);
                    strcpy(ans,menu);
                    send(new_socket,ans,strlen(ans),0);
                    // buffer[0]='\0';
                    memset(buffer,0,MAX_BUFFER_SIZE);
                    recv(new_socket,buffer,MAX_BUFFER_SIZE,0);
                    p = (buffer[0])-48;
                    // send(new_socket,p,1,0);
                }
                if(p==1)
                {
                    char *admin = "Admin :\n 1) Add Student\n 2) View Student Details\n 3) Add Faculty\n 4) View Faculty Details\n 5) Activate Student\n 6) Deactivate Student\n 7) Update Student Details\n 8) Update Faculty Details\n 9) Exit\n";
                    memset(ans,0,MAX_BUFFER_SIZE);
                    strcpy(ans,admin);
                    send(new_socket,ans,strlen(ans),0);
                    memset(ans1,0,MAX_BUFFER_SIZE); 
                    recv(new_socket,ans1,strlen(ans1),0);
                    // printf("%s %d\n",ans1,w);
                    // ans1[w]='\0';
                    if(ans1[0]=='9')
                        p=-1;
                }
                else if(p==2)
                {
                    char *Faculty = "Faculty :\n 1) Add New Course\n 2) Remove Offered Course\n 3) View Enrollments In Courses\n 4) Update Course Details\n 5) Password Change\n 6) Exit\n";
                    memset(ans,0,MAX_BUFFER_SIZE);
                    strcpy(ans,Faculty);
                    send(new_socket,ans,strlen(ans),0);
                    memset(ans,0,MAX_BUFFER_SIZE); 
                    recv(new_socket,ans1,strlen(ans1),0);
                    if(ans1[0]=='6')
                        p=-1;
                }
                else if(p==3)
                {
                    char *student = "Student :\n 1) View All Courses\n 2) Enroll To New Course\n 3) Unenroll From Already Enrolled Courses\n 4) View Enrolled Courses\n 5) Password Change\n 6) Exit\n";
                    memset(ans,0,MAX_BUFFER_SIZE); 
                    strcpy(ans,student);
                    send(new_socket,ans,strlen(ans),0);
                    memset(ans1,0,MAX_BUFFER_SIZE); 
                    recv(new_socket,ans1,strlen(ans1),0);
                    if(ans1[0]=='6')
                        p=-1;
                }
                else
                {
                    // char tmp[9];
                    // sprintf(tmp, "%d", p);
                    // strcpy(ans,tmp);
                    // ans[9]='\0';
                    p = -1;
                }
            }
        }
        close(new_socket);
    }
    close(new_socket);
    return 0;
}