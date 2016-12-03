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
		//�̰� ���� ������ �����ؾ� �ϴ� ���� Ȯ���ϴ� �˰���
		for(int j=1;j<floor;++j){
			if(Floor[j] == 1) ++i;
		}

		while((tmp = getchar()) != '\n'){
			int q = tmp-'0';
			if(tmp == ' ') continue;

			//Ż��
			if(tmp == 'q') {
				return true;
			}

			//�Է°��� floor���� ū ���
			if(q>=floor && tmp != '\n') {cout<<"�Է°��� �ʹ� Ů�ϴ�."<<endl;continue;}

			//���� ����
			if(i==0 && q<floor && curFloor!= q){
				if(tmp == '\n') Dir = Dir; //�ƹ��͵� �Է����� ���� ���
				else if(q>curFloor) Dir = 1;
				else if(q<curFloor) Dir = -1;

				++i; //�ߺ� �Է� ������
			}

			//�� ���� ����� ������ �� �� ���� ���� ������ �������� ���� ���� �ƴҶ�
			if(Floor[q] == 0 && q<floor && q!=curFloor) Floor[q] = 1;
			else{
				printf("���� %d ������ ����� �ֽ��ϴ�. �Է��� ����մϴ�.\n",q);
			}
		}
		fflush(stdin);
		//���� ��ġ���� ��ǥ�� ã��
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

			//Ż��
			if(tmp == 'q') {
				return true;
			}

			//���͸� �������
			if(tmp == '\n') {
				Button[q] += ((DifInPerson-i)>0? (DifInPerson-i) : 0);		//���� �ϳ��� �Է��� ��� ��� ����� �� ������ ���� �Ѵ�.
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
		//�����Ҵ��� ��°������ memset�� �ȵǱ⿡
		for(int i=0;i<floor;++i){
			Floor[i] = 0;
			Button[i] = 0;
		}
	}
	int getGoal(){return Goal;}
	int getCurFloor() {return curFloor;}

	void display(char* str){
		cout<<endl<<"	"<<str<<endl;
		printf("	����� �ִ� ��(0�� 1�� ����) \n");
		printf("	");
		for(int i=1;i<floor;++i)	printf("%d ",i);
		cout<<endl;
		printf("	");
		for(int i=1;i<floor;++i)	printf("%d ",Floor[i]);
		cout<<endl;
		printf("	���������� ��ư(�������� �� ����� ��) \n");
		printf("	");
		for(int i=1;i<floor;++i)	printf("%d ",i);
		cout<<endl;
		printf("	");
		for(int i=1;i<floor;++i)	printf("%d ",Button[i]);
		cout<<endl<<"	���������� �ȿ� �ִ� ���: "<<InPerson<<endl<<"	���������� ���� ��: "<<curFloor<<endl;
		cout<<"	��ǥ�� "<<Goal<<endl<<"	���������� ����(-1�̸� �Ʒ� 1�̸� �� 0�̸� ����): "<<Dir<<endl<<"	����Ʈ ��: "<<floor-1<<endl;
		cout<<endl<<"	�̿��� �ּż� �����մϴ�."<<endl<<endl;
		getchar();
		getchar();
	}
	//����� ������ �Լ�
	void leavePerson(){		
		if (Button[curFloor]>0){
			printf("\n	%d ���� ����� �����ϴ�.\n",Button[curFloor]);
			if(InPerson>0) InPerson -= Button[curFloor];
			Button[curFloor] = 0;		
		}
		//display("leavePerson");
	}

	//����� ������ �Լ�
	void getInPerson() { 
		if(Floor[curFloor]>0){
			printf("\n	����� ž�ϴ�. ��ư�� �ϳ��� �Է��� �ּ���<<");
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

		//���� �� ���
		cout<<"���� ���� "<<curFloor<<"�� �Դϴ�. \n";
		//display("whatEver");
		//��ǥ���� �����ϰ� ������ 0�� �ƴ� ó�� ��ǥ���� ����������
		if(Goal == curFloor && Dir!=0)
		{
			printf("	��ǥ���� �����Ͽ����ϴ�.");
			Dir = 0;		//��ǥ���� �����Ͽ��� ������ ������ ���̻� ����.
			
			//���������Ϳ��� ��ǥ������ ������ ����� �ִ� ���
			leavePerson();
			for(int i=0;i<floor;++i) Button[i] = 0;

			//���� �� ���� Ÿ�� ����� �ִ� ���
			if(Floor[curFloor]>0)
			{
				cout<<"����� ž�ϴ�.\n"<<endl;
				++InPerson;
				Floor[curFloor]=0;
			}

			//Ÿ�� �ִ� �������ŭ �� �Է� �޴´�.
			if(InPerson>0)	
			{
				printf("\n	%d��ŭ ��ư�� ���Է��� �ֽʽÿ� <<",InPerson);	
				if(getButton(Button,InPerson)){
					display("finish");
					exit(1);
				}
			}
				setDefaultGoal();		//���� �ٸ� �������� ���ٸ� �̰ɷ� ��ǥ�� ����
		}else{ //��ǥ���� �ƴ� ���� ������ ���
			leavePerson();
			getInPerson();
		}

		cout<<"	���������͸� Ż ���� �Է����ּ��� << ";
		if(getFloor(Floor,Dir,curFloor,Goal,floor)){ //���Է�
			display("finish");
			exit(1);
		}
		if(Dir==1 && curFloor<floor) curFloor++;
		else if(Dir==-1 && curFloor>0) curFloor--;

		//display("end");
	}
};