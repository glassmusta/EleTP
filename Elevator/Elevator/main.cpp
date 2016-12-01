#include "Elevator.h"

int main(void){
	int floor;
	for(int i=0;;++i){
		cout<<"아파트의 층 수를 입력해주세요 : ";
		cin>>floor;
		if(floor <=0) cout<<"올바르지 않은 입력입니다.";
		else break;
		getchar();
	}
	Elevator e(floor);
	cout<<"빌딩의 층 수는 "<<floor<<"이며 '<<' 표시가 떳을 때 q를 입력하면 종료합니다."<<endl;
	fflush(stdin);

	while(1){
		e.moving();
	}
}