#include <stdio.h>
#include <stdlib.h>
#include "info.h"

void filemake();

int main() 
{
	int sel;
	filemake();

	printf("\nㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ-\n");
        printf("|       학사관리 프로그램       |\n");
        printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ-\n\n");
   printf("  1. 교직원   2. 학생  3. 교수\n\n");
	printf("해당하는 번호를 입력하세요 : ");
	scanf("%d", &sel);

	switch (sel) {
		case 1:
			printf("[교직원]\n");
			faculty();
			break;
		case 2:
			printf("[학생]\n");
			student();
			break;
		case 3:
			printf("[교수]\n");
			professor();
			break;

	}while (sel != 0);

	return 0;
}	

void filemake(){
	
	FILE *fp;
	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	FILE *fp4;

	fp = fopen("./subj", "rb+");
	fp1 = fopen("./id", "rb+");
	fp2 = fopen("./grade", "rb+");
	fp3 = fopen("./pid", "rb+");
	fp4 = fopen("./list", "rb+");

	if(fp == NULL) 
		system("touch subj; ./main");
	if(fp1 == NULL) 
		system("touch id; ./main");
	if(fp2 == NULL) 
		system("touch grade; ./main");
	if(fp3 == NULL) 
		system("touch pid; ./main");
	if(fp4 == NULL) 
		system("touch list; ./main");

	fclose(fp);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);

}
