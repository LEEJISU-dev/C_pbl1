#define START_SNUM 20000
#define START_ID 20130000
#define START_PID 7000

struct subject {
	char subj[100]; // 과목이름
	char pname[100]; // 강의교수님
	int  room; // 강의실장소
	char time[100]; // 강의시간
	int  snum; // 학수번호
	int pid;//교수번호
	int year;//연도
};

struct student {
	int id;//학번
	char sname[100];//학생이름
	int sub[6];//과목
	int lsub[20];//이전과목
};

struct professor {
	int pid;//교수번호
	char pname[100];//교수이름
	int sub[3];//과목
	int lsub[15];//이전과목
};

struct grade {
	int id;//학번
	int snum;// 학수번호
	int grade;//점수
};

int faculty();
void input1();
void modify1();
void print1();
void del1();
int professor();
void print2();//교수목록
void menu2();
void grade2();//성적입력
void sprint2();//학생성적확인
void subprint2();//교과목출력
void input2();//교수추가
void yprint2();//연도별 강의 과목 확인
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


	
