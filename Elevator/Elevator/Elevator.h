#pragma once
#include <iostream>
#include <string>
#include <time.h>
#include <stdlib.h>
using namespace std;

class Input{
public:
	bool getFloor(int* Floor, int& Dir,const int& curFloor,int& Goal,const int floor){
		char tmp;
		int i=0;
		//이게 과연 방향을 설정해야 하는 건지 확인하는 알고리즘
		for(int j=1;j<floor;++j){
			if(Floor[j] == 1) ++i;
		}

		while((tmp = getchar()) != '\n'){
			int q = tmp-'0';
			if(tmp == ' ') continue;

			//탈출
			if(tmp == 'q') {
				return true;
			}

			//입력값이 floor보다 큰 경우
			if(q>=floor && tmp != '\n') {cout<<"입력값이 너무 큽니다."<<endl;continue;}

			//방향 설정
			if(i==0 && q<floor && curFloor!= q){
				if(tmp == '\n') Dir = Dir; //아무것도 입력하지 않은 경우
				else if(q>curFloor) Dir = 1;
				else if(q<curFloor) Dir = -1;

				++i; //중복 입력 방지용
			}

			//그 층에 사람이 없으며 총 층 수를 넘지 않으며 현재층과 같은 값이 아닐때
			if(Floor[q] == 0 && q<floor && q!=curFloor) Floor[q] = 1;
			else{
				printf("현재 %d 층에는 사람이 있습니다. 입력을 취소합니다.\n",q);
			}
		}
		fflush(stdin);
		//현재 위치에서 목표점 찾기
		for(int tmpGoal=(curFloor+Dir);tmpGoal>0 && tmpGoal < floor && Dir!=0;tmpGoal+=Dir){
			if(Floor[tmpGoal] == 1) Goal = tmpGoal;
		}
		return false;
	}
	bool getButton(int*Button,int DifInPerson){
		char tmp;
		int q=0;

		for(int i=0;i<DifInPerson;++i){
			tmp = getchar();

			//탈출
			if(tmp == 'q') {
				return true;
			}

			//엔터를 누른경우
			if(tmp == '\n') {
				Button[q] += ((DifInPerson-i)>0? (DifInPerson-i) : 0);		//숫자 하나만 입력한 경우 모든 사람이 그 곳으로 가게 한다.
				break;
			}
			q = tmp-'0';
			Button[q] +=1;
		}
		fflush(stdin);
		return false;
	}
};

class Elevator : Input{
private:
	int *Floor;
	int *Button;
	int curFloor;
	int Goal;
	int Dir;
	int InPerson;
	int floor;
public:
	Elevator(int f=0) : curFloor(1),Goal(1),Dir(0),InPerson(0),floor(f+1){
		Floor = new int[floor];
		Button = new int[floor];
		//동적할당은 어째서인지 memset이 안되기에
		for(int i=0;i<floor;++i){
			Floor[i] = 0;
			Button[i] = 0;
		}
	}
	int getGoal(){return Goal;}
	int getCurFloor() {return curFloor;}

	void display(char* str){
		cout<<endl<<"	"<<str<<endl;
		printf("	사람이 있는 층(0과 1로 구분) \n");
		printf("	");
		for(int i=1;i<floor;++i)	printf("%d ",i);
		cout<<endl;
		printf("	");
		for(int i=1;i<floor;++i)	printf("%d ",Floor[i]);
		cout<<endl;
		printf("	엘리베이터 버튼(그쪽으로 갈 사람의 수) \n");
		printf("	");
		for(int i=1;i<floor;++i)	printf("%d ",i);
		cout<<endl;
		printf("	");
		for(int i=1;i<floor;++i)	printf("%d ",Button[i]);
		cout<<endl<<"	엘리베이터 안에 있는 사람: "<<InPerson<<endl<<"	엘리베이터 현재 층: "<<curFloor<<endl;
		cout<<"	목표층 "<<Goal<<endl<<"	엘리베이터 방향(-1이면 아래 1이면 위 0이면 정지): "<<Dir<<endl<<"	아파트 총: "<<floor-1<<endl;
		cout<<endl<<"	이용해 주셔서 감사합니다."<<endl<<endl;
		getchar();
		getchar();
	}
	//사람이 나가는 함수
	void leavePerson(){		
		if (Button[curFloor]>0){
			printf("\n	%d 명의 사람이 내립니다.\n",Button[curFloor]);
			if(InPerson>0) InPerson -= Button[curFloor];
			Button[curFloor] = 0;		
		}
		//display("leavePerson");
	}

	//사람이 들어오는 함수
	void getInPerson() { 
		if(Floor[curFloor]>0){
			printf("\n	사람이 탑니다. 버튼을 하나만 입력해 주세요<<");
			if(getButton(Button,(++InPerson-(InPerson-1)))){
				display("finish");
				exit(1);
			}
			Floor[curFloor] = 0;	
		}
		//display("getInPerson");
	}

	void setDefaultGoal(){
		bool isGoalExist = false;
		for(int i=1;i<floor;++i){
			if(Floor[i] ==1) {
				isGoalExist = true;
				break;
			}
		}
		if(!isGoalExist){
			for(int srchFloor = curFloor-1;srchFloor>0;--srchFloor){
				if(Button[srchFloor]>0){
					Dir = -1;
					Goal = srchFloor;
				}
			}
			for(int srchFloor = curFloor+1;srchFloor<floor;++srchFloor){
				if(Dir == -1) break;
				if(Button[srchFloor]>0){
					Dir = 1;
					Goal = srchFloor;
				}
			}
		}
		//display("setDefaultGoal");
	}

	void moving(){

		//현재 층 출력
		cout<<"현재 층은 "<<curFloor<<"층 입니다. \n";
		//display("whatEver");
		//목표층에 도착하고 방향이 0인 아닌 처음 목표층에 도착했을때
		if(Goal == curFloor && Dir!=0)
		{
			printf("	목표층에 도착하였습니다.");
			Dir = 0;		//목표층에 도착하였기 때문에 방향은 더이상 없다.
			
			//엘리베이터에서 목표층에서 내리는 사람이 있는 경우
			leavePerson();
			for(int i=0;i<floor;++i) Button[i] = 0;

			//만약 그 층에 타는 사람이 있는 경우
			if(Floor[curFloor]>0)
			{
				cout<<"사람이 탑니다.\n"<<endl;
				++InPerson;
				Floor[curFloor]=0;
			}

			//타고 있는 사람수만큼 재 입력 받는다.
			if(InPerson>0)	
			{
				printf("\n	%d만큼 버튼을 재입력해 주십시오 <<",InPerson);	
				if(getButton(Button,InPerson)){
					display("finish");
					exit(1);
				}
			}
				setDefaultGoal();		//만약 다른 가는층이 없다면 이걸로 목표층 설정
		}else{ //목표층이 아닌 층에 도착한 경우
			leavePerson();
			getInPerson();
		}

		cout<<"	엘리베이터를 탈 층을 입력해주세요 << ";
		if(getFloor(Floor,Dir,curFloor,Goal,floor)){ //층입력
			display("finish");
			exit(1);
		}
		if(Dir==1 && curFloor<floor) curFloor++;
		else if(Dir==-1 && curFloor>0) curFloor--;

		//display("end");
	}
};