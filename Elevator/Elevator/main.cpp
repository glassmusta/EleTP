#include "Elevator.h"

int main(void){
	int floor;
	for(int i=0;;++i){
		cout<<"����Ʈ�� �� ���� �Է����ּ��� : ";
		cin>>floor;
		if(floor <=0) cout<<"�ùٸ��� ���� �Է��Դϴ�.";
		else break;
		getchar();
	}
	Elevator e(floor);
	cout<<"������ �� ���� "<<floor<<"�̸� '<<' ǥ�ð� ���� �� q�� �Է��ϸ� �����մϴ�."<<endl;
	fflush(stdin);

	while(1){
		e.moving();
	}
}