#include <stdlib.h>
#include <stdio.h>
#include "info.h"

int faculty();
void input1();
void modify1();
void print1();
void del1();

int faculty(void)
{
	struct subject rec;
	int sel;

	printf("\n-------------------------------------------------------------\n");
	printf("1. 과목 생성   2. 과목 수정  3. 과목 보기 4. 과목 삭제 5. 돌아가기 6. 종료\n");
	printf("-------------------------------------------------------------\n");

	printf(" 번호를 입력하세요 : ");
	scanf("%d", &sel);

	switch (sel) {
		case 1:
			printf("[과목 생성]\n");
			input1();
			break;
		case 2:
			printf("[과목 수정]\n");
			modify1();
			break;

		case 3: 
			printf("[과목 보기]\n");
			print1();
			break;
		case 4:
			printf("[과목 삭제]\n");
			del1();
			break;
		case 5:
			printf("[돌아가기]\n");
			system("clear");
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
	return 0;

}

void input1(void){
	struct subject rec;
	char c;
	FILE *fp;

	fp = fopen("./subj", "rb+");
	if (fp == NULL) {
		printf("File Open for writing Fail!\n");
		system("clear");
		main();
	}

	printf("%8s %20s %6s %5s %8s %10s %8s\n", "학수번호", "과목이름", "시간", "장소", "교수번호","교수이름","수강년도");
	do {
		scanf("%d %s %s %d %d %s %d", &rec.snum, rec.subj, rec.time, &rec.room,&rec.pid, rec.pname, &rec.year);
		fseek(fp, (rec.snum - START_SNUM)*sizeof(rec), SEEK_SET);
		if ((fread(&rec.snum, sizeof(rec.snum), 1, fp) > 0) && (rec.snum != 0)) {
			printf("데이터 존재\n");
			printf("계속하겠습니까?(Y/N)");
			scanf("%c", &c);
			getchar();
		}
		else {
			fwrite(&rec, sizeof(rec), 1, fp);
			getchar();
			printf("계속하겠습니까?(Y/N)");
			scanf("%c", &c);
		}
	} while (c == 'Y' || c == 'y');
	fclose(fp);
	system("clear");
	main();
}

void modify1(void){
	struct subject rec;
	int snum, num;
	char c;
	FILE *fp;

	fp = fopen("./subj", "rb+");

	if (fp == NULL)
	{
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	do {
		printf("수정할 과목의 학수번호  입력:");
		if (scanf("%d", &snum) == 1) {
			fseek(fp, (snum - START_SNUM) * sizeof(rec), SEEK_SET);
			if ((fread(&rec, sizeof(rec), 1, fp) > 0) && (rec.snum != 0)) {
				printf("학수번호:%8d, 과목 이름:%20s 시간:%6s 장소:%5d 교수번호:%8d 교수이름:%10s 수강년도:%8d\n", rec.snum, rec.subj, rec.time, rec.room, rec.pid, rec.pname, rec.year);
				printf("항목을 선택하세요\n");
				printf("1. 과목이름\n2. 시간\n3. 장소\n4. 교수번호\n5. 교수이름\n6. 수강년도\n7. 돌아가기\n ");
				printf("번호 입력:");
				scanf("%d", &num);
				getchar();
				switch (num) {
					case 1:
						printf("수정할 과목이름 입력");
						scanf("%s", rec.subj);
						getchar();
						break;
					case 2:
						printf("수정할 시간 입력:");
						scanf("%s", rec.time);
						getchar();
						break;
					case 3:
						printf("수정할 장소 입력:");
						scanf("%d", &rec.room);
						getchar();
						break;
					case 4:
						printf("수정할 교수번호 입력:");
						scanf("%d", &rec.pid);
						getchar();
						break;
					case 5:
						printf("수정할 교수이름 입력");
						scanf("%s", rec.pname);
						getchar();
						break;
					case 6:
						printf("수정할 수강년도 입력");
						scanf("%d",&rec.year);
						getchar();
						break;
					case 7:
						printf("돌아가기");
						main();
						break;
					default:
						break;
				}
				fseek(fp, -(int)sizeof(rec), SEEK_CUR);
				fwrite(&rec, sizeof(rec), 1, fp);
			}
			else printf("레코드 %d 없음", snum);
		}
		else printf("입력오류\n");
		printf("계속하겠습니까?(Y/N)");
		scanf("%c", &c);
	} while (c == 'Y' || c == 'y');

	fclose(fp);
	system("clear");
	main();
}

void print1(void){
	struct subject rec;
	FILE *fp;

	fp = fopen("./subj", "rb+");

	if (fp == NULL){
		printf("File Open Fail\n");
		system("clear");
		main();
	}

	printf("-----------------------------------------------------------\n");
	printf("%8s %20s %6s %5s %8s %10s %8s\n","학수번호","과목이름","시간","장소","교수번호","교수이름","수강년도");                
	printf("-----------------------------------------------------------\n");
	while(fread(&rec,sizeof(rec), 1, fp)>0)
		if(rec.snum != 0) {
			printf("%8d %20s %6s %5d %8d %10s %8d\n", rec.snum, rec.subj, rec.time, rec.room,rec.pid, rec.pname, rec.year);   

		}


	fclose(fp);
	main();
}

void del1(void){
	struct subject rec;
	struct subject op= { };
	int snum;
	char c;
	FILE *fp;

	fp = fopen("./subj", "rb+");
	if (fp == NULL) {
		printf("File Open for writing Fail!\n");
		system("clear");
		main();
	}

	do{
		printf("삭제할 과목의 학수번호 입력:");
		if(scanf("%d",&snum) ==1){
			fseek(fp,(snum-START_SNUM)*sizeof(rec),SEEK_SET);
			if((fread(&rec,sizeof(rec),1,fp)>0)&&(rec.snum !=0)){
				rec=op;
				fseek(fp, -(int)sizeof(rec), SEEK_CUR);
				fwrite(&rec, sizeof(rec), 1, fp);
			}else printf("레코드 %d 없음", snum);

			printf("계속하겠습니까?(Y/N)");
			scanf("%c", &c);
		}
	} while (c == 'Y' || c == 'y');
	fclose(fp);
	system("clear");
	main();
}
