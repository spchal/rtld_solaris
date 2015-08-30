#include<stdio.h>
#include<string.h>
#include<stdlib.h>

char *shell = "/bin/zsh";

void date() {
	printf("Today's date");
	system("/bin/date");
}

void vul(char *str){
	char  str2[10];
	strcpy(str2,str);
}

int main(int argc,char* argv[]){
	vul(argv[1]);
	return 0;
}
