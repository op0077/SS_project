#include "headerfiles.h"
#include "handle_admin.c"

#define PORT 8081 
#define MAX_BUFFER_SIZE 1024

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
        if ((cpid = fork()) == 0) { // Child process

            int p= -1; // Initialize userChoice
            char response[MAX_BUFFER_SIZE];
            char *menu = "Enter the Choice:\n1) Admin\n2) Faculty\n3) Student\n";
            strcpy(response, menu);
            // response[strlen(menu)]='\0';
            send(new_socket, response, strlen(response), 0);
            
            memset(buffer, '\0', MAX_BUFFER_SIZE);
            int k = recv(new_socket, buffer, MAX_BUFFER_SIZE, 0);
            if(k<0)
            {
                send(new_socket,"not",3,0);
            }
            p= buffer[0] - '0';
            
            // Implement menu options for different user types
            switch (p) 
            {
                case 1:
                    char *admin = "Admin :\n 1) Add Student\n 2) View Student Details\n 3) Add Faculty\n 4) View Faculty Details\n 5) Activate Student\n 6) Deactivate Student\n 7) Update Student Details\n 8) Update Faculty Details\n 9) Exit\n";
                    send(new_socket,admin,strlen(admin),0);
                    char ans1;
                    recv(new_socket,&ans1,sizeof(ans1),0);
                    admin_init();
                    int k = ans1 - '0';
                    
                    switch(k)
                    {
                        case 1: // Add studnet
                            add_student(new_socket);
                            // recv(new_socket,&ans1,sizeof(ans1),0);
                            // char op[10];
                            // sprintf(op,"%d",kc);
                            // close(server_socket);
                            exit(1);
                            break;
                        case 2: // View stundet details
                            view_student_details(new_socket);
                            
                            // char op1[] = "\nwe have it,server";

                            // send(new_socket,op1,sizeof(op1),0);
                            // recv(new_socket,op1,sizeof(op1),0);
                            exit(0);
                            break;
                        // case '3': // Add Faculty
                        //     // add_faculty();
                        //     break;
                        // case '4': // View faculty details  
                        //     // view_faculty_details();
                        //     break;
                        // case '5': // Activate student
                        //     // activate_student();
                        //     break; 
                        // case '6': // Deavtivate Student
                        //     // deactivate_student();
                        //     break;
                        case 7: // Update studnet details
                            update_student_details(new_socket);
                            char op2[] = "Student updated sucessfully";

                            send(new_socket,op2,sizeof(op2),0);
                            // // exit(1);
                            // close(new_socket);
                            // exit(0);
                            break;
                        // case '8': // Passowrd change
                        //     // password_change();
                        //     break;
                        // case '9': // Exit
                        //     close(new_socket);
                        //     exit(1);
                        //     break;
                        default:
                            break;
                    }
                    break;
                case 2:
                    
                    break;
                case 3: 
                    // Student menu
                    // Implement student menu options
                    break;
                default:
                    p = -1; // Return to the main menu
                    break;
            }

            
            close(new_socket); // Close the client socket in the child process
            exit(0); // Terminate the child process
        }
        
        close(new_socket); // Close the client socket in the parent process
    }
    
    close(server_socket); // Close the server socket in the parent process
    return 0;
}