# include "headerfiles.h"
# include "struct_file.c"


int stfd;
int ftfd;
struct Student student;
struct Faculty faculty;
char buf[256];
int st_id=0;
int ft_id=0;

void admin_init()
{
    stfd = open("student.txt",O_RDWR|O_CREAT,0777);
    ftfd = open("faculty.txt",O_RDWR|O_CREAT,0777);
    if(stfd<0)
    {
        char op[] = "not read";
        // send(cl_st,op,sizeof(op),0);
        printf("%s",op);
    }
    
    st_id = lseek(stfd,0,SEEK_END)/sizeof(struct Student);
    lseek(stfd,0,SEEK_SET);
    st_id+=1;
}

void add_student(int cl_st)
{
    int w = sizeof(struct Student);
    student.st_id = st_id; // assigning availabel studnet id
    char dop[30];
    char dop1[30];
    char age[30];
    char addr[100];
    char email[30];
    char pass[30];

    char tmp0[] = "Enter Your Name : ";
    send(cl_st,tmp0,sizeof(tmp0),0);
    memset(dop,0,30);
    recv(cl_st,&dop,30,0);
    // strcpy(student.st_name,dop);
    student.st_active = 0;
    char tmp[] = "Enter Your Name : ";
    send(cl_st,tmp,sizeof(tmp),0);
    memset(dop1,0,30);
    recv(cl_st,&dop1,30,0);
    strcpy(student.st_name,dop1);
    
    char tmp1[] = "Enter Your Age : ";
    send(cl_st,tmp1,sizeof(tmp1),0);
    memset(age,0,30);
    recv(cl_st,&age,30,0);
    student.st_age = abs(atoi(age));

    char tmp2[] = "Enter Your Address : ";
    send(cl_st,tmp2,sizeof(tmp2),0);
    memset(addr,0,30);
    recv(cl_st,&addr,30,0);
    strcpy(student.st_addr,addr);

    char tmp3[] = "Enter Your Email : ";
    send(cl_st,tmp3,sizeof(tmp3),0);
    memset(email,0,30);
    recv(cl_st,&email,30,0);
    strcpy(student.st_email,email);

    // char tmp4[] = "Enter Your  Password: ";
    // send(cl_st,tmp4,sizeof(tmp4),0);
    // memset(pass,0,30);
    // recv(cl_st,&pass,30,0);
    // strcpy(student.st_pass,pass);
    strcpy(student.st_pass,"pass");

    lseek(stfd,0,SEEK_END);
    student.st_active = 1;
    write(stfd,&student,sizeof(struct Student));
    // write(stfd,&student,w);
    // struct Student tmp_st;
    // lseek(stfd,0,SEEK_SET);
    // read(stfd,&tmp_st,sizeof(tmp_st));
    char response[6*w];
    sprintf(response,"\nstudentname=%s\nstudentage=%s\nstudentaddress=%s\nstudentEmail=%s\nid = %d\n\nstudent added successfully",dop1,age,addr,email,student.st_id);
    // sprintf(response,"studentname=%s\n",dop);
    // char response[] = "its working";
    send(cl_st,response,sizeof(response),0);  
    // char ans3[30];
    // recv(cl_st,ans3,30,0);
    close(cl_st);
    // return;
    // close(cl_st);
    // close(stfd);
}
void view_student_details(int cl_st)
{
    // int file=open("student.txt",O_RDONLY|O_CREAT,0744);
    
    char mg[]="enter student id : ";
    send(cl_st,&mg,sizeof(mg),0);
    char jk[30];
    recv(cl_st,&jk,sizeof(jk),0);
    char mg1[]="enter student id : ";
    send(cl_st,&mg1,sizeof(mg1),0);
    char uk[30];
    int p = recv(cl_st,&uk,sizeof(uk),0);
    if(p<0)
    {
        char msg[] = "msg didn't recived";
        send(cl_st,msg,sizeof(msg),0);
        char tmp[20];
        recv(cl_st,tmp,sizeof(tmp),0);
    }
    char msg1[] = "msg op recived";
    send(cl_st,msg1,sizeof(msg1),0);
    char tmp1[20];
    recv(cl_st,tmp1,sizeof(tmp1),0);
    //reaching end of the previous record
    int id1 = abs(atoi(jk));
    int id2 = abs(atoi(uk));
    int id = id1;
    if(id2>id1)
        id = id2;
    int pointer=(id-1)*sizeof(struct Student);
    struct Student student_detail;


    lseek(stfd,pointer,SEEK_SET);
    read(stfd,&student_detail,sizeof(struct Student));
    if(student_detail.st_active==1)
    {
        char tmp[10*sizeof(struct Student)];
        sprintf(tmp,"\nStudent id:%d\nname:%s\nage:%d\nemail:%s\naddress:%s\nactive_status:%d\n",student_detail.st_id,student_detail.st_name,student_detail.st_age,student_detail.st_email,student_detail.st_addr,student_detail.st_active);
        send(cl_st,&tmp,sizeof(tmp),0);
        char ok[20];
        recv(cl_st,ok,sizeof(ok),0);
        char op[] = "";
        send(cl_st,&op,sizeof(op),0);
        close(cl_st);
    }
    else
    {
        char error_msg[]="No Data Avilable..\n";
        send(cl_st,error_msg,sizeof(error_msg),0);
    }
    close(cl_st);
    return;
}
void update_student_details(int cl_socket)
{
    char kg[]="enter student id : ";
    send(cl_socket,&kg,sizeof(kg),0);
    char kj[30];
    recv(cl_socket,kj,sizeof(kj),0);
    char kg1[]="enter student id : ";
    send(cl_socket,kg1,sizeof(kg1),0);
    char ku[30];
    int p = recv(cl_socket,ku,sizeof(ku),0);
    int id1 =1;
    id1 = abs(atoi(kj));
    int id = id1;
    int id2 = abs(atoi(ku));
    if(id2>id1)
        id = id2;

    int pointer=(id-1)*sizeof(struct Student);
    struct Student student1;


    lseek(stfd,pointer,SEEK_SET);
    read(stfd,&student1,sizeof(struct Student));
    char tmp8[10*sizeof(struct Student)];
    // char tmp8[]="hello";
    sprintf(tmp8,"\nStudent_id:%d\n\t1)name:%s\n\t2)age:%d\n\t3)email:%sn\n\t4)address:%s\nactive_status:%d\n\nselect_between=1-4_:\n",student1.st_id,student1.st_name,student1.st_age,student1.st_email,student1.st_addr,student1.st_active);
    send(cl_socket,tmp8,sizeof(tmp8),0);
    char tk[20];
    recv(cl_socket,tk,sizeof(tk),0);

    
    // char rt[] = "here_name";
    // send(cl_socket,&rt,sizeof(rt),0);
    // // char pq[30];
    // recv(cl_socket,&rt,sizeof(rt),0);
    // strcpy(student1.st_name,pq);
    int k = abs(atoi(tk));
    // student1.st_age = 23;

    // switch (k)
    // {
    //     case 1:
    //         char tmp[] = "Enter Your Name : ";
    //         send(cl_socket,tmp,sizeof(tmp),0);
    //         // memset(dop2,0,30);
    //         char dop2[30];
    //         recv(cl_socket,&dop2,30,0);
    //         strcpy(student1.st_name,dop2);
    //         lseek(stfd,pointer,SEEK_SET);
    //         write(stfd,&student1,sizeof(struct Student));
    //         break;
    //     case 2:
    //         char tmp1[] = "Enter Your Age : ";
    //         send(cl_socket,tmp1,sizeof(tmp1),0);
    //         // memset(age,0,30);
    //         char age1[4];
    //         recv(cl_socket,&age1,30,0);
    //         student1.st_age = abs(atoi(age1));
    //         lseek(stfd,pointer,SEEK_SET);
    //         write(stfd,&student1,sizeof(struct Student));
    //         break;
    //     case 3:
    //         char tmp3[] = "Enter Your Email : ";
    //         send(cl_socket,tmp3,sizeof(tmp3),0);
    //         // memset(email,0,30);
    //         char email1[30];
    //         recv(cl_socket,&email1,30,0);
    //         strcpy(student1.st_email,email1);
    //         lseek(stfd,pointer,SEEK_SET);
    //         write(stfd,&student1,sizeof(struct Student));
    //         break;
    //     case 4:
    //         char tmp2[] = "Enter Your Address : ";
    //         send(cl_socket,tmp2,sizeof(tmp2),0);
    //         // memset(addr,0,30);
    //         char addr1[100];
    //         recv(cl_socket,&addr1,30,0);
    //         strcpy(student1.st_addr,addr1);
    //         lseek(stfd,pointer,SEEK_SET);
    //         write(stfd,&student1,sizeof(struct Student));
    //         break;
    //     default:
    //         break;
    // }
    if(k==1)
    {
        char tmp3[] = "Enter new name";
        send(cl_socket,&tmp3,sizeof(tmp3),0);
        char name1[30];
        recv(cl_socket,&name1,sizeof(name1),0);

        char tmp4[] = "Enter new name";
        send(cl_socket,&tmp4,sizeof(tmp4),0);
        char name2[30];
        recv(cl_socket,&name2,sizeof(name2),0);
        // printf("name 1 : %s",name1);
        // printf("name 2 :%s",name2);
        memset(&student1.st_name,0,sizeof(student1.st_name));
        // strcpy(student1.st_name,name1);
        // sprintf(student1.st_name);
        // char name2[]="dart@3345";
        if(strlen(name1)>strlen(name2))
            strcpy(student1.st_name,name1);
        else
            strcpy(student1.st_name,name2);
        // memcpy(&student1.st_name,&name1,strlen(name1));
        lseek(stfd,pointer,SEEK_SET);
        write(stfd,&student1,sizeof(struct Student));
    }
    else if(k==2)
    {
        char tmp1[] = "Enter new Age : ";
        send(cl_socket,&tmp1,sizeof(tmp1),0);
        // memset(age,0,30);
        char age1[4];
        recv(cl_socket,&age1,sizeof(age1),0);

        char tmp2[]= "Enter new Age : ";
        send(cl_socket,&tmp1,sizeof(tmp1),0);
        char age2[4];
        recv(cl_socket,&age2,sizeof(age2),0);;
        int m = 2;
        int k1 = atoi(age1);
        int k2 = atoi(age2);
        m = k2;
        // m = abs(atoi(age1));
        // if(m<abs(atoi(age2)));
        // {
        //     m = abs(atoi(age2));
        // }
        student1.st_age = m;
        lseek(stfd,pointer,SEEK_SET);
        write(stfd,&student1,sizeof(struct Student));
    }
    else if(k==3)
    {
        char tmp3[] = "Enter New email";
        send(cl_socket,&tmp3,sizeof(tmp3),0);
        char email1[30];
        recv(cl_socket,&email1,sizeof(email1),0);

        char tmp4[] = "";
        send(cl_socket,&tmp4,sizeof(tmp4),0);
        char email2[30];
        recv(cl_socket,&email2,sizeof(email2),0);
        // printf("email 1 : %s",email1);
        // printf("email 2 :%s",email2);
        memset(&student1.st_email,0,sizeof(student1.st_email));
        // strcpy(student1.st_email,email1);
        // sprintf(student1.st_email);
        // charemail2[]="dart@3345";
        if(strlen(email1)>strlen(email2))
            strcpy(student1.st_email,email1);
        else
            strcpy(student1.st_email,email2);
        // memcpy(&student1.st_email,&email1,strlen(email1));
        lseek(stfd,pointer,SEEK_SET);
        write(stfd,&student1,sizeof(struct Student));
    }
    else if(k==4)
    {
        char tmp3[] = "Enter new Address";
        send(cl_socket,&tmp3,sizeof(tmp3),0);
        char addr1[30];
        recv(cl_socket,&addr1,sizeof(addr1),0);

        char tmp4[] = "Enter new Address";
        send(cl_socket,&tmp4,sizeof(tmp4),0);
        char addr2[30];
        recv(cl_socket,&addr2,sizeof(addr2),0);
        // printf("addr 1 : %s",addr1);
        // printf("addr 2 :%s",addr2);
        memset(&student1.st_addr,0,sizeof(student1.st_addr));
        // strcpy(student1.st_addr,addr1);
        // sprintf(student1.st_addr);
        // char addr2[]="neardart";
        if(strlen(addr1)>strlen(addr2))
            strcpy(student1.st_addr,addr1);
        else
            strcpy(student1.st_addr,addr2);
        // memcpy(&student1.st_addr,&addr1,strlen(addr1));
        lseek(stfd,pointer,SEEK_SET);
        write(stfd,&student1,sizeof(struct Student));
    }
    char t2[] = "written";
    send(cl_socket,&t2,sizeof(t2),0);
    char j1[10];
    recv(cl_socket,j1,sizeof(j1),0);
}