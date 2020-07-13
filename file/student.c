#include <stdio.h>
#include <stdlib.h>
#include "info.h"

int student();
void print3();//학번이름출력
void input3();//학생추가
void menu3();
void sugang3();//수강신청 
void print_sugang3();//수강확인
void modify3();//수강변경&취소
void list3();//학기별 수강내역
void grade_print3();
void allgrade_print3();//전체성적확인
void del3();
void grade_input3();//이전과목 성적입력
void list_input3();//이전수강과목입력  

int num;

int student(void)
{   
	struct student stu;
	struct subject rec;

	int id;
	print3();

	printf("\n------------------------------------\n");
	printf("    1.학번선택  2.학생추가 3. 종료\n");
	printf("------------------------------------\n");

	printf(" 번호를 입력하세요 : ");
	scanf("%d", &id);
	switch(id) {
		case 1:
			printf("본인의 학번을 입력해주세요. : ");
			scanf("%d",&num);
			getchar();
			system("clear");
			menu3();
			break;
		case 2:
			input3();
			break;
		case 3:
			printf("[종료]\n");
			exit(1);
			break;
	}
	return 0;
}

void print3(void){
	struct student stu;
	FILE *fp1;

	fp1 = fopen("./id", "ab+");

	if (fp1 == NULL)
	{
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	printf("ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	printf("|\t %8s %10s\t   | \n|\t\t\t\t   |\n","학번","이름");                
	while(fread(&stu,sizeof(stu), 1, fp1)>0) 
		if(stu.id != 0) { 
			printf("|\t %8d %10s\t   |\n", stu.id, stu.sname);   

		}
	printf("|\t\t\t\t   |\nㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n");
	fclose(fp1);
}

void input3(void){
	struct student stu;
	char c;
	FILE *fp1;

	fp1 = fopen("./id", "rb+");
	if (fp1 == NULL) {
		printf("File Open for writing Fail!\n");
		system("clear");
		main();
	}

	printf("%8s %10s\n", "학번", "이름");
	do {
		scanf("%d %s", &stu.id, stu.sname);
		fseek(fp1, (stu.id - START_ID)*sizeof(stu),SEEK_SET);
		if ((fread(&stu.id, sizeof(stu.id), 1, fp1) > 0) && (stu.id != 0)) {
			printf("데이터 존재\n");
			printf("계속하겠습니까?(Y/N)");
			scanf("%s", &c);
			getchar();
		}
		else {
			fwrite(&stu, sizeof(stu), 1, fp1);
			getchar();
			printf("계속하겠습니까?(Y/N)");
			scanf("%s", &c);
		}
	} while ((c == 'Y') || (c == 'y'));
	fclose(fp1);
	system("clear");
	main();
} 


void menu3(){
	int sel;

	printf("\n--------------------------------------------------------\n");
	printf("   학생");
	printf("\n--------------------------------------------------------\n");
	printf("1. 수강신청\n2. 수강확인\n3. 수강변경 및 취소\n4. 학기별 수강내역\n5. 성적확인\n6. 전체성적확인\n7. 자퇴\n8. grade input\n9. list_input\n10. 돌아가기\n11. 종료\n");
	printf("--------------------------------------------------------\n\n");

	printf(" 번호를 입력하세요 : ");
	scanf("%d", &sel);

	switch (sel) {
		case 1:
			printf("[수강신청]\n");
			sugang3();
			break;
		case 2:
			printf("[수강확인]\n");
			print_sugang3();
			break;

		case 3: 
			printf("[수강변경 및 취소]\n");
			modify3();
			break;
		case 4: 
			printf("[학기별 수강내역]\n");
			list3();
			break;
		case 5: 
			printf("[성적확인]\n");
			grade_print3();
			break;
		case 6: 
			printf("[전체성적확인]\n");
			allgrade_print3();
			break;
		case 7: 
			printf("[자퇴]");
			del3();
			break;
		case 8:
			printf("grade input\n");
			grade_input3();
			break;
		case 9:
			printf("[이전수강과목입력]\n");
			list_input3();
			break;
		case 10:
			printf("[돌아가기]\n");
			main();
			break;
		case 11:
			printf("[종료]\n");
			exit(1);
			break;      
		default:
			printf("다시 입력하세요\n");
			main();
			break;
	}
}   
void sugang3() {
	struct subject rec;
	struct student stu;
	FILE *fp;
	FILE *fp1;
	char c;
	int i;

	fp = fopen("./subj", "rb+");

	if (fp == NULL)
	{
		printf("File Open Fail\n");
		system("clear");
		main();
	}


	printf("--------------------------------------------------------------\n");
	printf("%15s %15s %8s %8s %15s %15s\n","학수번호","과목이름","시간","장소","교수이름","수강년도");                
	printf("--------------------------------------------------------------\n");
	while(fread(&rec,sizeof(rec), 1, fp)>0)
		if(rec.snum != 0) {
			printf("%10d %-26s %8s %6d %10s %10d\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname, rec.year);   
		}

	fp1 = fopen("./id", "rb+");

	do {
		if(num != 0) {
			fseek(fp1, (num -START_ID)*sizeof(stu),SEEK_SET);
			if ((fread(&stu,sizeof(stu),1,fp1)>0)&&(stu.id!=0)) {
				for(i=0;i<6;i++){
					printf("수강할 과목의 학수번호를 입력하세요.\n");
					scanf("%d",&stu.sub[i]);
					fseek(fp1, -(int)sizeof(stu), SEEK_CUR);
					fwrite(&stu, sizeof(stu), 1, fp1);
				}
			}
			else printf("레코드 %d 없음\n",num);
		}   
		else printf("입력 오류\n");
		printf("계속하겠습니까?(Y/N)");
		scanf("%s", &c);
	} while (c == 'Y' || c == 'y');

	fclose(fp);
	fclose(fp1);
	system("clear");
	menu3(); 
}

void print_sugang3() {
	struct subject rec;    
	struct student stu;
	FILE *fp;   
	FILE *fp1;
	int i;
	fp = fopen("./subj","rb+");
	fp1 = fopen("./id", "rb+");

	if (fp1 == NULL)
	{
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	printf("----------------------------------------------------------\n");
	printf("%8s %10s %8s %8s %8s %8s %8s %8s\n","학번","이름","과목1","과목2", "과목3", "과목4", "과목5", "과목6");                
	printf("----------------------------------------------------------\n");

	fseek(fp1,(num-START_ID)*sizeof(stu),SEEK_SET);
	if ((fread(&stu, sizeof(stu), 1, fp1)>0) && (stu.id != 0)){
		printf("%8d %10s %6d %6d %6d %6d %6d %6d\n", stu.id, stu.sname, stu.sub[0],stu.sub[1],stu.sub[2],stu.sub[3],stu.sub[4],stu.sub[5]);

		printf("\n");
		printf("---------------------------------------------------\n");
		printf("%15s %15s %8s %8s %15s\n","학수번호","과목이름","시간","장소","교수이름");                
		printf("---------------------------------------------------\n");
		while(fread(&rec,sizeof(rec), 1, fp)>0){
			if(rec.snum!=0){
				for(i=0;i<6;i++){       
					if(stu.sub[i] == rec.snum)
						printf("%10d %-26s %8s %6d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);    
				}
			}
		}

	}   
	else printf("레코드 %d 없음\n", num);


	fclose(fp);
	fclose(fp1);

	menu3();

}

void modify3(void){
	struct student stu;
	int snum, i;
	char c;
	FILE *fp1;
	fp1 = fopen("./id", "rb+");

	if (fp1 == NULL)
	{
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	do {
		fseek(fp1,(num-START_ID)*sizeof(stu),SEEK_SET);
		while(fread(&stu,sizeof(stu), 1, fp1)>0){
			printf("수강변경할 과목의 학수번호  입력하세요 : ");
			scanf("%d", &snum);
			if(snum!=0){
				for(i=0;i<6;i++){       
					if(stu.sub[i] == snum){
						printf("\n\n수강할 과목의 학수번호를 입력하세요. : ");
						scanf("%d",&stu.sub[i]);
						fseek(fp1, -(int)sizeof(stu), SEEK_CUR);
						fwrite(&stu, sizeof(stu), 1, fp1); 
						getchar(); }
				}
			}
		}

		printf("계속하겠습니까?(Y/N)");
		scanf("%s", &c);
	} while (c == 'Y' || c == 'y');   

	fclose(fp1);
	system("clear");
	menu3();
}



void list3(void){
	struct subject rec;
	struct student stu;
	FILE *fp4;
	FILE *fp1;

	fp4 = fopen("./list","rb+");
	fp1 = fopen("./id","rb+");

	if (fp1 == NULL)
	{
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	fseek(fp1,(num-START_ID)*sizeof(stu),SEEK_SET);
	if ((fread(&stu, sizeof(stu), 1, fp1)>0) && (stu.id != 0)){

		printf("\n");
		printf("--------------------------------------------------------\n");
		printf("%15s %8s %8s %8s %15s\n","학수번호","과목","시간","장소","교수이름");                
		printf("--------------------------------------------------------\n");
		fseek(fp4,sizeof(rec),SEEK_SET);
		while(fread(&rec,sizeof(rec),1,fp4) > 0) {
			if((rec.year >= 201300) && (rec.year < 201400)) {
				if ( (rec.year %2) !=0){ 
					printf("[2013년 1학기]");
					printf("%10d %10s %10s %8d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
				}  
				else if((rec.year %2) == 0){
					printf("[2013년 2학기]");
					printf("%10d %10s %10s %8d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
				}
			}
			else if((rec.year >= 201400) && (rec.year < 201500)) {
				if ( (rec.year %2) !=0){ 
					printf("[2014년 1학기]");
					printf("%10d %10s %-10s %-8d %-10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
				}  
				else if((rec.year %2) == 0){
					printf("[2014년 2학기]");
					printf("%10d %10s %-10s %-8d %-10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
				}
			}
			else if((rec.year >= 201500) && (rec.year < 201600)) {
				if ( (rec.year %2) !=0){ 
					printf("[2015년 1학기]");
					printf("%10d %10s %10s %8d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
				}  
				else if((rec.year %2) == 0){
					printf("[2015년 2학기]");
					printf("%10d %10s %10s %8d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
				}
			}
			else if((rec.year >= 201600) && (rec.year < 201700)) {
				if ( (rec.year %2) !=0){ 
					printf("[2016년 1학기]");
					printf("%10d %10s %10s %8d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
				}  
			}

		}     
	}else printf("레코드 %d 없음\n", num);


	fclose(fp4);
	fclose(fp1);

	menu3();

}

void grade_print3(void) {

	struct subject rec;
	struct student stu;
	struct grade gra;
	int i;
	char c;	
	FILE *fp;
	FILE *fp1; 
	FILE *fp2;

	fp = fopen("./subj", "rb+");
	fp1 = fopen("./id", "rb+");
	fp2 = fopen("./grade", "rb+");

	printf("==================================================\n");
	printf("%8s %15s %8s %8s %8s %8s\n","학번", "학수번호","과목","교수이름", "점수", "성적");                
	printf("==================================================\n");


	fseek(fp2, sizeof(gra), SEEK_SET);
	while(fread(&gra, sizeof(gra), 1, fp2) > 0) {
		//		fseek(fp, sizeof(rec), SEEK_SET);
		if( num == gra.id) {
			//	fseek(fp, sizeof(rec), SEEK_SET);
			while(fread(&rec, sizeof(rec), 1, fp) > 0) {
				if(gra.snum == rec.snum) {
					if(rec.snum != 0) {
						printf("%d %d", gra.id, gra.snum);
						printf("%s %s", rec.subj, rec.pname); 
					}	
				}
			}

			if(gra.grade != 0) {
				printf("%8d      ", gra.grade);
				if(gra.grade >= 97 && gra.grade <= 100)
					printf("A+\n");
				else if(gra.grade >= 94 && gra.grade <= 96)
					printf("A0\n");
				else if(gra.grade >= 90 && gra.grade <= 93)
					printf("A-\n");
				else if(gra.grade >= 87 && gra.grade <= 89)
					printf("B+\n");
				else if(gra.grade >= 84 && gra.grade <= 86)
					printf("B0\n");
				else if(gra.grade >= 80 && gra.grade <= 83)
					printf("B-\n");
				else if(gra.grade >= 77 && gra.grade <= 79)
					printf("C+\n");
				else if(gra.grade >= 74 && gra.grade <= 76)
					printf("C0\n");
				else if(gra.grade >= 70 && gra.grade <= 73)
					printf("C-\n");
				else if(gra.grade >= 67 && gra.grade <= 69)
					printf("D+\n");
				else if(gra.grade >= 64 && gra.grade <= 66)	
					printf("D0\n");
				else if(gra.grade >= 60 && gra.grade <= 63)
					printf("D-\n");
				else
					printf("F\n");
			}
		}  
	}
	fclose(fp);
	fclose(fp1);
	fclose(fp2);

	menu3();
}


void allgrade_print3(void){

	struct subject rec;
	struct student stu;
	struct grade gra;
	int i;
	char c;   
	FILE *fp1; 
	FILE *fp2;
	FILE *fp4;

	fp1 = fopen("./id", "rb+");
	fp2 = fopen("./grade", "rb+");
	fp4 = fopen("./list", "rb+");

	printf("--------------------------------------------------\n");
	printf("%8s %15s %8s %8s %8s %8s\n","학번", "학수번호","과목","교수이름", "점수", "성적");                
	printf("--------------------------------------------------\n");
	fseek(fp2, sizeof(gra), SEEK_SET);
	while(fread(&gra, sizeof(gra), 1, fp2) > 0) {
		if(gra.id==num){
			printf("%8d %8d", gra.id, gra.snum);
			fseek(fp4, sizeof(rec), SEEK_SET);
			while(fread(&rec, sizeof(rec), 1, fp4) > 0) {
				if(gra.snum == rec.snum){
					if(rec.snum != 0) {
						printf("%26s %10s",rec.subj, rec.pname);
					}   
				}
			}}
		printf("%8d      ", gra.grade);
		if(gra.grade >= 97 && gra.grade <= 100)
			printf("A+\n");
		else if(gra.grade >= 94 && gra.grade <= 96)
			printf("A0\n");
		else if(gra.grade >= 90 && gra.grade <= 93)
			printf("A-\n");
		else if(gra.grade >= 87 && gra.grade <= 89)
			printf("B+\n");
		else if(gra.grade >= 84 && gra.grade <= 86)
			printf("B0\n");
		else if(gra.grade >= 80 && gra.grade <= 83)
			printf("B-\n");
		else if(gra.grade >= 77 && gra.grade <= 79)
			printf("C+\n");
		else if(gra.grade >= 74 && gra.grade <= 76)
			printf("C0\n");
		else if(gra.grade >= 70 && gra.grade <= 73)
			printf("C-\n");
		else if(gra.grade >= 67 && gra.grade <= 69)
			printf("D+\n");
		else if(gra.grade >= 64 && gra.grade <= 66)   
			printf("D0\n");
		else if(gra.grade >= 60 && gra.grade <= 63)
			printf("D-\n");
		else
			printf("F\n");
	}

	fclose(fp1);
	fclose(fp2);
	fclose(fp4);

	menu3();
}   

void del3(void){
	struct student stu;
	struct student op = { };
	char c;
	FILE *fp1;

	fp1 = fopen("./id", "rb+");

	if (fp1 == NULL){
		printf("File Open Fail\n");
		system("clear");
		main();
	}
	do{
		if(num != 0){
			fseek(fp1,(num-START_ID)*sizeof(stu),SEEK_SET);
			if((fread(&stu,sizeof(stu),1,fp1)>0)&&(stu.id !=0)){
				stu = op;
				fseek(fp1,-(int)sizeof(stu),SEEK_CUR);
				fwrite(&stu,sizeof(stu),1,fp1);
			}else printf("레코드 %d 없음", num);
			printf("계속하겠습니까?(Y/N)");
			scanf("%c", &c);
		}
	} while (c == 'Y' || c == 'y');
	fclose(fp1);
	system("clear");
	main();
}


void grade_input3(void){

	struct subject rec;
	struct student stu;
	struct grade gra;
	int i;
	char c;   
	FILE *fp1; 
	FILE *fp2;
	FILE *fp4;


	fp1 = fopen("./id", "rb+");
	fp2 = fopen("./grade", "rb+");
	fp4 = fopen("./list", "rb+");

	fseek(fp1,(num-START_ID)*sizeof(stu),SEEK_SET);
	if ((fread(&stu, sizeof(stu), 1, fp1)>0) && (stu.id != 0)){

		printf("\n");
		printf("--------------------------------------------------\n");
		printf("%15s %15s %8s %8s %15s\n","학수번호","과목이름","시간","장소","교수이름");
		printf("--------------------------------------------------\n");

		while(fread(&rec,sizeof(rec), 1, fp4)>0){
			if(rec.snum!=0){
				for(i=0;i<20;i++){
					if(stu.lsub[i] == rec.snum)
						printf("%10d %26s %8s %6d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
				}
			}
		}
	}
	fseek(fp2,sizeof(gra),SEEK_SET);
	do {
		if(num != 0) {
			gra.id = num;
			printf("성적 입력할 학수번호를 입력하세요. : ");
			scanf("%d", &gra.snum);

			printf("과목의 점수를 입력하세요. : ");
			scanf("%d",&gra.grade);

			fwrite(&gra, sizeof(gra), 1, fp2);
		}

		printf("계속하겠습니까?(Y/N)");
		scanf("%s", &c);

	} while ((c == 'Y') || (c == 'y'));

	fclose(fp1);
	fclose(fp2);
	fclose(fp4);

	menu3();
}

void list_input3(void){
	struct subject rec;
	struct student stu;
	FILE *fp1;
	FILE *fp4;
	char c;
	int i;

	fp4 = fopen("./list", "rb+");

	if (fp4 == NULL)
	{
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	printf("---------------------------------------------------\n");
	printf("%15s %15s %8s %8s %15s\n","학수번호","과목이름","시간","장소","교수이름");                
	printf("---------------------------------------------------\n");
	while(fread(&rec,sizeof(rec), 1, fp4)>0)
		if(rec.snum != 0) {
			printf("%10d %26s %8s %6d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);   
		}

	fp1 = fopen("./id", "rb+");

	do {
		if(num != 0) {
			fseek(fp1, (num -START_ID)*sizeof(stu),SEEK_SET);
			if ((fread(&stu,sizeof(stu),1,fp1)>0)&&(stu.id!=0)) {
				for(i=0;i<20;i++){
					printf("수강한 과목의 학수번호를 입력하세요.\n");
					scanf("%d",&stu.lsub[i]);
					fseek(fp1, -(int)sizeof(stu), SEEK_CUR);
					fwrite(&stu, sizeof(stu), 1, fp1);
				}
			}
			else printf("레코드 %d 없음\n",num);
		}   
		else printf("입력 오류\n");
		printf("계속하겠습니까?(Y/N)");
		scanf("%s", &c);
	} while (c == 'Y' || c == 'y');

	fclose(fp4);
	fclose(fp1);
	system("clear");
	menu3(); 
}


/*void list(void){
  struct subject rec;
  struct student stu;
  FILE *fp4;
  FILE *fp1;
  int i;
  fp4 = fopen("./list","rb+");
  fp1= fopen("./id","rb+");

  if (fp1 == NULL)
  {
  printf("File Open Fail\n");
  system("clear");
  main();
  }


  fseek(fp1,(num-START_ID)*sizeof(stu),SEEK_SET);
  if ((fread(&stu, sizeof(stu), 1, fp1)>0) && (stu.id != 0)){

  printf("\n");
  printf("==================================================\n");
  printf("%15s %15s %8s %8s %15s\n","학수번호","과목이름","시간","장소","교수이름");                
  printf("==================================================\n");

  while(fread(&rec,sizeof(rec), 1, fp4)>0){
  if(rec.snum!=0){
  for(i=0;i<20;i++){       
  if(stu.lsub[i] == rec.snum)
  printf("%10d %26s %8s %6d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);    
  }
  }
  }
  }   

  else printf("레코드 %d 없음\n", num);
  fclose(fp4);
  fclose(fp1);
  menu();

  }*/
