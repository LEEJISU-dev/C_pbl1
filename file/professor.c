#include <stdio.h>
#include <stdlib.h>
#include "info.h"

int professor();
void print2();//교수목록
void menu2();
void grade2();//성적입력
void sprint2();//학생성적확인
void subprint2();//교과목출력
void input2();//교수추가
void yprint2();//연도별 강의 과목 확인

int num;

int professor(void){
	int id;
	print2();

	printf("\n------------------------------------\n");
	printf("    1. 교수번호 2. 교수추가 3. 종료\n");
	printf("------------------------------------\n");

	printf(" 번호를 입력하세요 : ");
	scanf("%d", &id);
	__fpurge(stdin);
	switch(id) {
		case 1:
			printf("본인의 번호를 입력해주세요. : ");
			scanf("%d",&num);
			getchar();
			system("clear");
			menu2();
			break;
		case 2:
			input2();
			break;
		case 3:
			printf("[종료]\n");
			exit(1);
			break;        
	}

	return 0;
}

void print2(void){
	struct professor pro = {0,};
	FILE *fp3;

	fp3 = fopen("./pid", "rb+");

	if (fp3 == NULL){
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	printf("---------------------------------------\n");
	printf("%8s %10s \n","교수번호",  "교수이름");                
	printf("---------------------------------------\n");  

	while(fread(&pro, sizeof(pro), 1, fp3)>0) {
		if(pro.pid != 0) { 
			printf("%8d %10s \n", pro.pid, pro.pname);   
		}
	}
	fclose(fp3);
}

void menu2(){
	int sel;

	printf("\n----------------------------------------------------\n");
	printf("   교수");  
	printf("\n----------------------------------------------------\n");
	printf("1. 성적입력\n2. 학생성적 확인\n3. 교과목 확인\n4. 연도별 강의과목 확인\n5. 돌아가기\n6. 종료\n");
	printf("----------------------------------------------------\n");

	printf(" 번호를 입력하세요 : ");
	scanf("%d", &sel);

	switch (sel) {
		case 1:
			printf("[성적 입력]\n");
			grade2();
			//system("clear");
			//menu();
			break;

		case 2:
			printf("[학생성적 확인]\n");
			sprint2();
			break;
		case 3:
			printf("[교과목 확인]\n");
			subprint2();
			break;
		case 4:
			printf("[연도별 강의과목 확인]\n");
			//   yprint();
			break;
		case 5:
			printf("[돌아가기]\n");
			main();
			break;
		case 6:
			printf("[종료]\n");
			exit(1);
			break;
		defult:
			printf("다시 입력하세요\n");
			main();
			break;

	}
}

void grade2(void){
	struct student stu;
	struct professor pro;
	struct grade gra;

	FILE *fp1;
	FILE *fp2;
	FILE *fp3;
	char c;
	int i, j;
	int snum;
	int id;
	int sub_count;
	int cnt=0;

	fp1 = fopen("./id","rb+");
	fp2 = fopen("./grade","rb+");
	fp3 = fopen("./pid","rb+");


	printf("-----------------------------------------------\n");
	printf("%8s %10s %8s %8s %8s\n","교수번호","교수이름","담당교과목1","담당교과목2", "담당교과목3");                
	printf("-----------------------------------------------\n");

	fseek(fp3,(num-START_PID)*sizeof(pro),SEEK_SET);
	if ((fread(&pro, sizeof(pro), 1, fp3)>0) && (pro.pid != 0)){
		printf("%8d %10s", pro.pid, pro.pname);
		for (sub_count=0; sub_count<10; sub_count++) {
			if(pro.sub[sub_count] != 0) {
				printf("%6d", pro.sub[sub_count]);
			}
		}
	}
	__fpurge(stdin);

	//   fseek(fp3, (num - START_PID)*sizeof(pro), SEEK_SET);
	do {
		//   fseek(fp1, sizeof(stu), SEEK_SET);
		fseek(fp3, (num - START_PID)*sizeof(pro), SEEK_SET);
		fread(&pro,sizeof(pro),1,fp3);
		printf("\n\n성적 입력 과목의 학수번호를 입력하세요. : ");
		scanf("%d",&snum);
		printf("\n");
		printf("-----------------------------\n");
		printf("%8s %10s \n","학번","학생이름");                
		printf("-----------------------------\n");
		if(snum==pro.sub[0]) {
			while(fread(&stu,sizeof(stu),1,fp1)>0){
				if(stu.id != 0){
					for(i=0;i<6;i++){
						if (stu.sub[i] == snum){
							printf("%10d %26s \n", stu.id, stu.sname);
							cnt++;
						}
					}
				}
			}
		}
		else if(snum == pro.sub[1]) {
			while(fread(&stu,sizeof(stu),1,fp1)>0){
				if(stu.id != 0){
					for(i=0;i<6;i++){
						if (stu.sub[i] == snum){
							printf("%10d %26s \n", stu.id, stu.sname);
							cnt++;
						}
					}
				}
			}   
		}
		else if(snum == pro.sub[2]) {
			while(fread(&stu,sizeof(stu),1,fp1)>0){
				if(stu.id != 0){
					for(i=0;i<6;i++){
						if (stu.sub[i] == snum){
							printf("%10d %26s \n", stu.id, stu.sname);
							cnt++;
						}
					}
				}
			}
		}
		else {
			printf("올바른 학수번호를 입력하세요.\n");
			break;
			grade();
		}
		fseek(fp2, sizeof(gra),SEEK_SET);
		//      fread(&gra, sizeof(gra), 1, fp2);
		for(j=0;j<cnt;j++) {
			fread(&gra, sizeof(gra), 1, fp2);
			printf("\n\n성적 입력할 학생의 학번을 입력하세요. : ");
			scanf("%d",&gra.id);
			if(gra.id !=0){             
				printf("과목의 점수를 입력하세요. : ");
				scanf("%d", &gra.grade);
				gra.snum = snum;
				//               fseek(fp2, -(int)sizeof(gra), SEEK_CUR);
				printf("%d", gra.grade);
			}
			fwrite(&gra, sizeof(gra), 1, fp2);
		}
		printf("이전으로 돌아가기(Y/N)");
		scanf("%s", &c);
	}while((c == 'Y') || (c == 'y'));
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	menu2();
}

void sprint2(){

	struct professor pro;
	struct student stu;
	struct grade gra;
	char c;   
	int snum;
	int sub_count;
	FILE *fp1;
	FILE *fp2; 
	FILE *fp3;

	fp1 = fopen("./id", "rb+");
	fp2 = fopen("./grade", "rb+");
	fp3 = fopen("./pid", "rb+");

	printf("------------------------------------------------------\n");
	printf("%8s %10s %8s %8s %8s\n","교수번호","교수이름","담당교과목1","담당교과목2", "담당교과목3");                
	printf("------------------------------------------------------\n");

	fseek(fp3,(num-START_PID)*sizeof(pro),SEEK_SET);
	if ((fread(&pro, sizeof(pro), 1, fp3)>0) && (pro.pid != 0)){
		printf("%8d %10s", pro.pid, pro.pname);
		for (sub_count=0; sub_count<10; sub_count++) {
			if(pro.sub[sub_count] != 0) {
				printf("%6d", pro.sub[sub_count]);
			}
		}
	}
	__fpurge(stdin);

	fseek(fp3, (num - START_PID)*sizeof(pro), SEEK_SET);
	fread(&pro,sizeof(pro),1,fp3);
	printf("\n\n성적 확인 과목의 학수번호를 입력하세요. : ");
	scanf("%d",&snum);

	printf("--------------------------------------------------\n");
	printf("%8s %15s %8s %8s\n","학번", "학생이름", "점수", "성적");                
	printf("--------------------------------------------------\n");

	fseek(fp2, sizeof(gra), SEEK_SET);
	while(fread(&gra, sizeof(gra), 1, fp2) > 0) {
		if(gra.snum == snum) {
			printf("%8d", gra.id);
			fseek(fp1, 0L, SEEK_SET);
			while(fread(&stu, sizeof(stu), 1, fp1) > 0){
				if(gra.id == stu.id){
					if(stu.id != 0){
						printf("%8s",stu.sname);
					}   
				}
			}
			if(gra.id != 0) {
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
			//__fpurge(stdin);
		}
	}
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);

	menu2();
}

void subprint2(void){
	struct subject rec;    
	struct professor pro = { 0, };
	FILE *fp;   
	FILE *fp3;
	int i;
	int sub_count;
	fp=fopen("./subj","rb+");
	fp3 = fopen("./pid", "rb+");

	if (fp3 == NULL)
	{
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	printf("-----------------------------------------------------\n");
	printf("%8s %10s %8s %8s %8s\n","교수번호","교수이름","담당교과목1","담당교과목2", "담당교과목3");                
	printf("-----------------------------------------------------\n");

	fseek(fp3,(num-START_PID)*sizeof(pro),SEEK_SET);
	if ((fread(&pro, sizeof(pro), 1, fp3)>0) && (pro.pid != 0)){
		//printf("%8d %10s %6d %6d %6d %6d %6d %6d %6d\n", pro.pid, pro.pname, pro.sub[0],pro.sub[1], rec.snum);
		printf("%8d %10s", pro.pid, pro.pname);

		for (sub_count=0; sub_count<10; sub_count++) {
			if(pro.sub[sub_count] != 0) {
				printf("%6d", pro.sub[sub_count]);
			}
		}

		printf("\n\n");
		printf("--------------------------------------------------\n");
		printf("%15s %15s %8s %8s %15s\n","학수번호","과목이름","시간","장소","교수이름");                
		printf("--------------------------------------------------\n");
		while(fread(&rec,sizeof(rec), 1, fp)>0){
			if(rec.snum!=0){
				for(i=0;i<20;i++){       
					if(pro.sub[i] == rec.snum)
						printf("%10d %26s %8s %6d %10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);    
				}
			}
		}
		__fpurge(stdin);
	}  

	else printf("레코드 %d 없음\n", num);

	fclose(fp);
	fclose(fp3);
	menu2();


}



void input2(void){
	struct subject rec;
	struct professor pro;
	char c;
	int i=0;
	FILE *fp;
	FILE *fp3;

	fp = fopen("./subj", "rb+");
	fp3 = fopen("./pid", "rb+");
	if (fp3 == NULL) {
		printf("File Open for writing Fail!\n");
		system("clear");
		main();
	}
	printf("%8s %10s \n", "교수번호", "교수이름");
	do {
		scanf("%d %s", &pro.pid, pro.pname);

		for (i=0; i<20; i++) {
			if(pro.sub[i] != 0) {
				pro.sub[i]=0;
			}
		}


		__fpurge(stdin);
		int i=0;
		fseek(fp3, (pro.pid - START_PID)*sizeof(pro), SEEK_SET);
		printf("read 하기전 : %ld\n", ftell(fp3));  
		if ((fread(&pro, sizeof(pro), 1, fp3) > 0) && (pro.pid != 0)) {
			printf("read 후 : %ld\n", ftell(fp3));  
			printf("데이터 존재\n");
			printf("계속하겠습니까?(Y/N)");
			scanf("%c", &c);
			__fpurge(stdin);
			//getchar();
		}
		else {
			printf("read 후 : %ld\n", ftell(fp3)); 
			// 수정자
			// 2016. 12. 17. 23:45
			// 파일 전체에서 search 할 목적이므로
			// 파일의 시작으로 포인터를 변경하기 위해
			// seek_set 사용
			//fseek(fp, sizeof(rec), SEEK_CUR);
			fseek(fp, 0, SEEK_SET);       
			while(fread(&rec, sizeof(rec), 1, fp) > 0) {
				if(pro.pid == rec.pid) {
					pro.sub[i] = 0;
					pro.sub[i] = rec.snum;
					i ++;
				}
			}
			fwrite(&pro, sizeof(pro), 1, fp3);         
			printf("계속하겠습니까?(Y/N)");
			scanf("%s", &c);
			__fpurge(stdin);
			//getchar();
		}
	} while (c == 'Y' || c == 'y');
	fclose(fp);
	fclose(fp3);
	system("clear");
	menu2();
}

void yprint2(){


	struct subject rec;
	struct professor pro;
	FILE *fp3;
	FILE *fp4;

	fp3 = fopen("./pid","rb+");
	fp4 = fopen("./list","rb+");

	if (fp3 == NULL)
	{
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	fseek(fp3,(num-START_PID)*sizeof(pro),SEEK_SET);
	if ((fread(&pro, sizeof(pro), 1, fp3)>0) && (pro.pid != 0)){

		printf("\n");
		printf("---------------------------------------------------\n");
		printf("%15s %8s %8s %8s %15s\n","학수번호","과목","시간","장소","교수이름");                
		printf("---------------------------------------------------\n");
		fseek(fp4,sizeof(rec),SEEK_SET);
		while(fread(&rec,sizeof(rec),1,fp4) > 0) {
			if(pro.pid == rec.pid){
				if((rec.year >= 201300) && (rec.year < 201400)) {
					if ( (rec.year %2) !=0){ 
						printf("[2013년 1학기]");
						printf("%10d %10s %10s %-8d %-10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
					}  
					else if((rec.year %2) == 0){
						printf("[2013년 2학기]");
						printf("%10d %10s %10s %-8d %-10s\n", rec.snum, rec.subj, rec.time, rec.room, rec.pname);
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
		}
	}else printf("레코드 %d 없음\n", num);


	fclose(fp3);
	fclose(fp4);

	menu2();
}


