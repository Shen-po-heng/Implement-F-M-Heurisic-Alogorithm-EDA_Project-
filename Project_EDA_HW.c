#include<stdio.h>
#include <stdlib.h>
typedef struct cell{//record Cell information 

	char group;//decide cell in which group
	int cell_size;//decide the size of the cell
	int number;//record the number of the cell
	int gain;//count the gain of the cell
	int pin_number;//record the number of the cell pins
	int net_A,net_B,net_C;//record what net of the cell
	struct cell* link;//I use link-list to save data,so I need this to connecet data
}Cell;
typedef struct net{//record Cell information 
	int Net_number;//record the number of the net
	int Net_connect_cell_num[5];//record which cell connect net
	int Net_connect_cell_number;//record how many cells connect the net
	int Net_before_from,Net_before_to;//before swap cell,net_from record how many cell in the "from" part or "to" part
	int Net_after_from,Net_after_to;//before swap cell,net_from record how many cell in the "from" part or "to" part
	struct net* link;//I use link-list to save data,so I need this to connecet data
}Net;
Cell *NewCell(void);//it can create a new data(cell) space in the memory
Net  *NewNet(void);//it can create a new data(net) space in the memory

void printlist(Cell*,Net*);//it can print what user input the information of the cell, after analyze the cell, it will print the information of the net
void gain_initial(Cell*,Net*);//it can count the initial gain of every cell at the beginning
void swap(Cell*,Net*,int);//it will deal with all swap behavior of the data, and it will end until the total gain<=0
int main(){
	
	unsigned int Cell_num,Net_num;//count how many of the cell and net
	int i,j,k;//when I want to use for-loop, I will use this
	Cell *Head,*temp;//pointers are used in the cell to control the behavior of the cell
	Net *Net_Head,*Net_temp;;//pointers are used in the net to control the behavior of the net

	Net_Head=NewNet();
	Net_temp=Net_Head;
	Head=NewCell();
	temp=Head;
////////////////////////////////////////////////////////////////////////////////
///////////////input the information of the cell between 41th line and 94th line////////////////////////////////
////////////////////////////////////////////////////////////////////////////////	
	printf("Please input the number of the cell:");
	scanf("%d",&Cell_num);
	printf("Please input the number of the net:");
	scanf("%d",&Net_num);
	Head->number=1;
	printf("Input the Cell_number=1:\n");
	printf("Cell_size= ");
	scanf("%d",&Head->cell_size);
	printf("Group= ");
	fflush(stdin);
	scanf("%c",&Head->group);
	printf("Pin_number= ");
	scanf("%d",&Head->pin_number);
	printf("Cell_pin01 connect the net= ");
	scanf("%d",&Head->net_A);
	if(Head->pin_number == 2){
	printf("Cell_pin02 connect the net= ");
	scanf("%d",&Head->net_B);
	}
	
	if( Head->pin_number >= 3){
		printf("Cell_pin02 connect the net= ");
		scanf("%d",&Head->net_B);
		printf("Cell_pin0 %d connect the net= ",Head->pin_number);
		scanf("%d",&Head->net_C);
	}
	Head->gain=0;
	for(i=2;i<=Cell_num;i++){
		temp->link=NewCell();
		temp->link->number=i;
		printf("\nInput the Cell_number=%d:\n",temp->link->number);
		printf("Cell_size= ");
		scanf("%d",&temp->link->cell_size);
		printf("Pin_number= ");
		scanf("%d",&temp->link->pin_number);
		printf("Group= ");
		fflush(stdin);
		scanf("%c",&temp->link->group);
		printf("Cell_pin01 connect the net= ");
		scanf("%d",&temp->link->net_A);
		if(temp->link->pin_number==2){
			printf("Cell_pin02 connect the net= ");
			scanf("%d",&temp->link->net_B);
		}
		else if(temp->link->pin_number>=3){
			printf("Cell_pin02 connect the net= ");
			scanf("%d",&temp->link->net_B);
			printf("Cell_pin0%d connect the net= ",temp->link->pin_number);
			scanf("%d",&temp->link->net_C);
		}
		temp->link->gain=0;
		temp=temp->link;
	}
	temp->link=NULL;
	////////////////////////////////////////////////
	////record which cell connect the net between 98th line and 133rd line
	/////////////////////////////////////////////////
	for(i=1;i<=Net_num;i++){
		temp=Head;//run the while in the for
		Net_temp->Net_number=i;
		j=1;
		k=0;
		while(temp!=NULL){
			if(temp->pin_number==1){
			
				if(temp->net_A==i){
					Net_temp->Net_connect_cell_num[k]=j;
					k++;
				}
			}
			else if(temp->pin_number==2){
				if(temp->net_A==i || temp->net_B==i){
					Net_temp->Net_connect_cell_num[k]=j;
					k++;
				}
			}
			else {
				if(temp->net_A==i || temp->net_B==i || temp->net_C==i){
					Net_temp->Net_connect_cell_num[k]=j;
					k++;
				}
			}
			temp=temp->link;
			j++;
		}
		Net_temp->Net_connect_cell_number=k;
		if(i==Net_num){
			Net_temp->link=NULL;
			break;
		}
		Net_temp->link=NewNet();
		Net_temp=Net_temp->link;	
	}
////////////////////////////////////////////////////////
/////////////use the function to demonstrate the result
////////////////////////////////////////////////////////	
	printf("\nNow, the situation is :\n");
	printlist(Head,Net_Head);
	gain_initial(Head,Net_Head);
	swap(Head,Net_Head,Cell_num);
	system("pause");
	return 0;
} 

Cell *NewCell(void){	//it declare a new data(cell) space in the memory
	Cell *pt;
	pt = (Cell*)malloc(sizeof(Cell));
	if(pt==NULL){
		printf("Memory is not sufficient!!");
		exit(1);
	}
	return pt;
}

Net *NewNet(void){		//it declare a new data(cell) space in the memory
	Net *pt;
	pt = (Net*)malloc(sizeof(Net));
	if(pt==NULL){
		printf("Memory is not sufficient!!");
		exit(1);
	}
	return pt;
}
void printlist(Cell* head,Net* net_head){  //after analyze the cell about what user input the information of the cell, it will print the information of the net
	Cell* temp=head;
	Net* net_temp=net_head;
	int i;
	while(temp!=NULL){
		printf("\nCell_number=%d:\t",temp->number);
		printf("Group=%c\t",temp->group);
		printf("Size=%d\t",temp->cell_size);
		if(temp->pin_number>=3){
			printf("net: net%d,net%d,net%d \n",temp->net_A,temp->net_B,temp->net_C);
		}
		else if(temp->pin_number==2){
			printf("net: net%d,net%d\n",temp->net_A,temp->net_B);
		}	
		else
			printf("net: net%d\n",temp->net_A);
		temp=temp->link;	
	}
	printf("\n\ninput format(like the example in problem):\n");
	while(net_temp!=NULL){
		printf("Net_number=%d:\t",net_temp->Net_number);
		printf("Net_connect_Cell_num:%d\t",net_temp->Net_connect_cell_number);
		printf("Connect Cell: ");
		for(i=0;i<net_temp->Net_connect_cell_number;i++)
			printf("Cell %d \t",net_temp->Net_connect_cell_num[i]);
		net_temp=net_temp->link;
		printf("\n");
	}
}
void gain_initial(Cell* head,Net* net_head){//count the gain of the cell at the beginning
	Cell* temp=head;
	Net* net_temp=net_head;
	int i,j,k;
	while(net_temp!=NULL){
		net_temp->Net_before_from=0;
		net_temp->Net_before_to=0;	
		for(i=0;i<net_temp->Net_connect_cell_number;i++){
			temp=head;
			k=net_temp->Net_connect_cell_num[i];
			for(j=1;j<k;j++)
				temp=temp->link;
			if(temp->group=='A')
				net_temp->Net_before_from++;
			else
				net_temp->Net_before_to++;	
		}
		net_temp=net_temp->link;		
	}
	net_temp=net_head;
	while(net_temp!=NULL){
		printf("\nNet%d: from %d to %d",net_temp->Net_number,net_temp->Net_before_from,net_temp->Net_before_to);
		net_temp=net_temp->link;
	}		
}
void swap(Cell* head,Net* net_head, int cell_num ){ 
	Cell* temp=head;
	Net* net_temp=net_head;
	int Gain_total=0;
	int Changed_Cell[cell_num];
	int count_change=0;
	int i,j,k;
	int size_A=0,size_B=0;
	int Max,Max_num=0;
	int cut_size;
	int KEY=0;
	while(net_temp!=NULL){
		for(i=0;i<net_temp->Net_connect_cell_number;i++){
			temp=head;
			k=net_temp->Net_connect_cell_num[i];
			for(j=1;j<k;j++)
				temp=temp->link;
			
			if(temp->group=='A'){
				if(net_temp->Net_before_from==1)
					temp->gain++;
				if(net_temp->Net_before_to==0)
					temp->gain--;
			}
			else if(temp->group=='B'){
				if(net_temp->Net_before_to==1)//Group=B inverse from to
					temp->gain++;
				if(net_temp->Net_before_from==0)
					temp->gain--;
			}			
		}
		net_temp=net_temp->link;
	}
		temp=head;
		Max=temp->gain;
		while(temp!=NULL){//compare gain
			if(temp->group=='A')
				size_A+=temp->cell_size;
			else if(temp->group=='B')
				size_B+=temp->cell_size;
			
			if(temp->gain>=Max){
				Max = temp->gain;
				if(temp->group=='A')
					if(abs((size_A-temp->cell_size)-size_B)<(0.01*cell_num))
						Max_num=temp->number;
				else if(temp->group=='B')
					if(abs(size_A-temp->cell_size-(size_B-temp->cell_size))<(0.01*cell_num))
						Max_num=temp->number;
			}
			printf("\nCell%d gain: %d",temp->number,temp->gain);
			temp=temp->link;
		}
		temp=head;
		if(Max>=0 && Max_num!=0){
			for(i=1;i<Max_num;i++)
				temp=temp->link;
			Changed_Cell[count_change]=temp->number;
			count_change++;
			if(temp->group=='A')
				temp->group='B';
			else
				temp->gain='A';
			printf("\nMax gain=%d belongs to Cell %d",Max,Max_num);
			printf("\naftre change, the group of Cell%d:%c",temp->number,temp->group);
			printf("\nSwap %d times:\n",count_change);
			printf("\n\nOutput format:");
			printf("\nGroup A:");
			while(temp!=NULL){
				if(temp->group=='A')
					printf(" cell%d ",temp->number);
				temp=temp->link;
			}
			temp=head;
			printf("\nGroup B:");
			while(temp!=NULL){
				if(temp->group=='B')
					printf(" cell%d ",temp->number);
				temp=temp->link;
			}
		}
		else{
			
			printf("\nIt's not necessary to change");
			printf("\n\nOutput format:");
			printf("\nGroup A:");
			while(temp!=NULL){
				if(temp->group=='A')
					printf(" cell%d ",temp->number);
				temp=temp->link;
			}
			temp=head;
			printf("\nGroup B:");
			while(temp!=NULL){
				if(temp->group=='B')
					printf(" cell%d ",temp->number);
				temp=temp->link;
			}
			KEY++;
		}
		net_temp=net_head;
		cut_size=0;
		while(net_temp!=NULL){
			if((net_temp->Net_before_from!=0)&&(net_temp->Net_before_to!=0))
				cut_size++;
			net_temp=net_temp->link;
		}
		printf("\nCutsize=%d\n",cut_size);
		if(KEY==1)
			return;
////////////////////////////////////////////////////except 1st,//////////////////////////////////////////////////////// 
		int ii;	
		for(ii=0;ii<cell_num-1;ii++){	
			if(i==0);
			else {//PASS AFTER TO BEFORE
				net_temp=net_head;
				while(net_temp!=NULL){
					net_temp->Net_before_from=net_temp->Net_after_from;	
					net_temp->Net_before_to=net_temp->Net_after_to;
					net_temp=net_temp->link;
				}				
			}
			net_temp=net_head;
			while(net_temp!=NULL){//key NEW net_next_to&from~
		
				net_temp->Net_after_from=0;
				net_temp->Net_after_to=0;	
				for(i=0;i<net_temp->Net_connect_cell_number;i++){
			
					temp=head;
					k=net_temp->Net_connect_cell_num[i];
			
				for(j=1;j<k;j++)
					temp=temp->link;
			
				if(temp->group=='A')
					net_temp->Net_after_from++;
				else
					net_temp->Net_after_to++;
				}
				net_temp=net_temp->link;		
			}
			
			while(net_temp!=NULL){
				for(i=0;i<net_temp->Net_connect_cell_number;i++){
			
					temp=head;
					k=net_temp->Net_connect_cell_num[i];
			
				for(j=1;j<k;j++)
					temp=temp->link;
			
				if(net_temp->Net_before_to==0)
					temp->gain++;
				else if(net_temp->Net_before_to==1)
					temp->gain--;
				if(net_temp->Net_after_from==1)//Group=B inverse from to
						temp->gain++;
				else if(net_temp->Net_after_to==0)
						temp->gain--;
							
				}
				net_temp=net_temp->link;
			}
				temp=head;
				Max=temp->gain;
				while(temp!=NULL){//compare gain
					if(temp->group=='A')
						size_A+=temp->cell_size;
					else if(temp->group=='B')
						size_B+=temp->cell_size;
					for(k=0;k<cell_num;k++)
						if(temp->number==Changed_Cell[k])
							temp=temp->link;
					if(temp->gain>=Max){
						Max = temp->gain;
					if(temp->group=='A')
						if(abs((size_A-temp->cell_size)-size_B)<(0.01*cell_num))
							Max_num=temp->number;
					else if(temp->group=='B')
						if(abs(size_A-temp->cell_size-(size_B-temp->cell_size))<(0.01*cell_num))
							Max_num=temp->number;
					}
					printf("\nCell%d gain: %d",temp->number,temp->gain);
					temp=temp->link;
				}
			if(Max>=0 && Max_num!=0){
				temp=head;
				for(i=1;i<Max_num;i++)
					temp=temp->link;
				count_change++;
				Changed_Cell[count_change]=temp->number;
				if(temp->group=='A')
					temp->group='B';
				else
					temp->gain='A';
			
				printf("\nMax gain=%d belongs to Cell %d",Max,Max_num);
				printf("\naftre change, the group of Cell%d:%c",temp->number,temp->group);
				printf("\nSwap %d times:\n",count_change);
				printf("\n\nOutput format:");
				printf("\nGroup A:");
				
				while(temp!=NULL){
					if(temp->group=='A')
						printf(" cell%d ",temp->number);
					temp=temp->link;
				}
				temp=head;
				printf("\nGroup B:");
				while(temp!=NULL){
					if(temp->group=='B')
						printf(" cell%d ",temp->number);
					temp=temp->link;
				}
		}
		else{	
			printf("\nIt's not necessary to change");
			printf("\n\nOutput format:");
			printf("\nGroup A:");
			temp=head;
			while(temp!=NULL){
				if(temp->group=='A')
					printf(" cell%d ",temp->number);
				temp=temp->link;
			}
			temp=head;
			printf("\nGroup B:");
			while(temp!=NULL){
				if(temp->group=='B')
					printf(" cell%d ",temp->number);
				temp=temp->link;
			}	
		}
		net_temp=net_head;
		cut_size=0;
		while(net_temp!=NULL){
		
			if((net_temp->Net_after_from!=0)&&(net_temp->Net_after_to!=0))
				cut_size++;
			net_temp=net_temp->link;
		}
		printf("\nCutsize=%d\n",cut_size);
		system("pause");	
		}
}
