#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include "struct_file.c"

void main(){
	
	int fd = open("student.txt", O_RDWR);
	struct Student student1;
	//int i = 0;
	while(read(fd, &student1, sizeof(struct Student))){
		printf("\nStudent_id:%d\n\t1)name:%s\n\t2)age:%d\n\t3)email:%s\n\t4)address:%s\nactive_status:%d\n",student1.st_id,student1.st_name,student1.st_age,student1.st_email,student1.st_addr,student1.st_active);
	}
}