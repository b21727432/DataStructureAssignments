#ifndef _header_h
#define _header_h
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
typedef struct Frames{ // my frame struct 

	char** physical;
	char** network;  // layers 
	char** transport;
	char** application;
	int hop;
} Frames;
typedef struct Nodes{ // node struct 
	char ID[5];
	char IP[20];
	char MAC[20];
	char* destination;
	char* neighbor;   // attributes
	Frames* inqueue;
	Frames* outqueue;
	int isiEmpty;
	int isoEmpty;
	char ***log;
	
} Node;

Frames pop(Frames frame[],int* frameptr){ // stack pop function
	if(*frameptr>0){
		*frameptr = *frameptr -1;
		
		return frame[*frameptr];
	}
	
	
}
void popLayer(Frames frame[],int* layer,int findex){
//	return frame[findex][*layer];
}
void pushLayer(Frames frame[],char* string,char* string2,char* string3,int* layer,int findex){ // stack pushlayer function 
	
	if(*layer == 0){ // if wants the physical
		strcpy(frame[findex].physical[0],string);
		strcpy(frame[findex].physical[1],string2);
		*layer = *layer+1;
	}
	else if(*layer == 1){ // if network
		strcpy(frame[findex].network[0],string);
		strcpy(frame[findex].network[1],string2);
		*layer = *layer+1;
	}
	else if(*layer == 2){ // if transport 
		strcpy(frame[findex].transport[0],string);
		strcpy(frame[findex].transport[1],string2);
		*layer = *layer+1;
	}
	else if (*layer == 3){ // if app
		strcpy(frame[findex].application[0],string);
		strcpy(frame[findex].application[1],string2);
		strcpy(frame[findex].application[2],string3);
		*layer = 0;
	}
	
}
void push(Frames frame[],int* frameptr){
	
}
void insertq(Node array[],Node array2[],int to,int i,int from){ // inserting into queue
	array[to].inqueue[i] =array2[from].outqueue[i];
}
Frames removeq(Node array[],int from,int i){ // removing from queue 
	return array[from].outqueue[i];
	
}
void addqueue(Node array[],int indexOfFrom,int i,Frames frame[],int numOfFrame,int* frameptr){ // adding to queue which is different from insering
	array[indexOfFrom].outqueue[numOfFrame-i-1] = pop(frame,frameptr);
}

void findTarget(Node array[],int indexOfFrom,int indexOfTo,int numOfFrame,int numOfNodes,int* hopptr,int* checkptr,char message[],Frames frame[],int* frameptr,int holder){
	int i,y,temp,z,t,x,temp2,h;
	
	time_t rawtime;
   	struct tm *info;
  	time( &rawtime );
   	info = localtime( &rawtime );
	for(i=0;i<numOfNodes;i++){
		if(array[indexOfTo].ID[0]==array[indexOfFrom].destination[i]){ // * or [0] finds the receiver in routing table
			
			for(y=0;y<numOfNodes;y++){
				
					if(array[y].ID[0]==array[indexOfFrom].neighbor[i]){ // this gets b gets the helper
						
			//		printf("\n\n");
			//		printf("%c ff\n\n",array[indexOfFrom].neighbor[i]);
					if(array[y].ID[0] != array[indexOfFrom].destination[i]){  // if equal that means one stop left
						

						*hopptr = *hopptr +1;
				//	printf("%c",array[indexOfFrom].neighbor[i]); // returns b
					temp = y; // array[y] = b yi veriyo demek;
			//		printf("%s",array[indexOfFrom].ID); // works fine CB BD BDE VERÝYOR   2.nd cb bd
				//	printf("%s\n",array[y].ID);
				//	strcpy(array[indexOfTo].) tekrar bir for statement ( frameleri güncellemk için)
					if(array[y].neighbor[i]=='-'){ // if - means unreachable
						printf("Error: Unreachable destination. Packets are dropped after %d hops!\nMessage: %s\n---------------------\n",*hopptr,message);
							array[indexOfFrom].log[0] = (char**)malloc(8 * sizeof(char*));
							array[indexOfFrom].log[0][0] = (char*)malloc(strlen(asctime(info)) * sizeof(char));
							array[indexOfFrom].log[0][1] = (char*)malloc(strlen(message) * sizeof(char));
							array[indexOfFrom].log[0][2] = (char*)malloc(sizeof(numOfFrame)/4 * sizeof(char));
							array[indexOfFrom].log[0][3] = (char*)malloc(sizeof(*hopptr)/4 * sizeof(char));
							array[indexOfFrom].log[0][4] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
							array[indexOfFrom].log[0][5] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
							array[indexOfFrom].log[0][6] = (char*)malloc(20 * sizeof(char));
							array[indexOfFrom].log[0][7] = (char*)malloc(5 * sizeof(char));
							
							strcpy(array[indexOfFrom].log[0][0],asctime(info));
							strcpy(array[indexOfFrom].log[0][1],message);
							sprintf(array[indexOfFrom].log[0][2],"%d",numOfFrame);
							sprintf(array[indexOfFrom].log[0][3],"%d",*hopptr-1);
							strcpy(array[indexOfFrom].log[0][4],array[holder].ID);
							strcpy(array[indexOfFrom].log[0][5],array[indexOfTo].ID);
							strcpy(array[indexOfFrom].log[0][6],"Message Forwarded");
							strcpy(array[indexOfFrom].log[0][7],"Yes");
					
					
					
					
					
							
							array[y].log[1] = (char**)malloc(8 * sizeof(char*));
							array[y].log[1][0] = (char*)malloc(strlen(asctime(info)) * sizeof(char));
							array[y].log[1][1] = (char*)malloc(strlen(message) * sizeof(char));
							array[y].log[1][2] = (char*)malloc(sizeof(numOfFrame)/4 * sizeof(char));
							array[y].log[1][3] = (char*)malloc(sizeof(*hopptr)/4 * sizeof(char));
							array[y].log[1][4] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
							array[y].log[1][5] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
							array[y].log[1][6] = (char*)malloc(20 * sizeof(char));
							array[y].log[1][7] = (char*)malloc(5 * sizeof(char));
							
							strcpy(array[y].log[1][0],asctime(info));
							strcpy(array[y].log[1][1],message);
							sprintf(array[y].log[1][2],"%d",numOfFrame);
							sprintf(array[y].log[1][3],"%d",*hopptr);
							strcpy(array[y].log[1][4],array[holder].ID);
							strcpy(array[y].log[1][5],array[indexOfTo].ID);
							strcpy(array[y].log[1][6],"Message Received");
							strcpy(array[y].log[1][7],"Yes");
					
							array[y].log[0] = (char**)malloc(8 * sizeof(char*));
							array[y].log[0][0] = (char*)malloc(strlen(asctime(info)) * sizeof(char));
							array[y].log[0][1] = (char*)malloc(strlen(message) * sizeof(char));
							array[y].log[0][2] = (char*)malloc(sizeof(numOfFrame)/4 * sizeof(char));
							array[y].log[0][3] = (char*)malloc(sizeof(*hopptr)/4 * sizeof(char));
							array[y].log[0][4] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
							array[y].log[0][5] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
							array[y].log[0][6] = (char*)malloc(20 * sizeof(char));
							array[y].log[0][7] = (char*)malloc(5 * sizeof(char));
							
							strcpy(array[y].log[0][0],asctime(info));
							strcpy(array[y].log[0][1],message);
							sprintf(array[y].log[0][2],"%d",numOfFrame);
							sprintf(array[y].log[0][3],"%d",*hopptr);
							strcpy(array[y].log[0][4],array[holder].ID);
							strcpy(array[y].log[0][5],array[indexOfTo].ID);
							strcpy(array[y].log[0][6],"Message Dropped");
							strcpy(array[y].log[0][7],"No");
							
							
							
							*checkptr = 1;
							array[y].isoEmpty = 1; //saying that not empty
							array[y].isiEmpty = 1;
							return;
					}
					for(t=0;t<numOfNodes;t++){
						if(array[y].destination[t] == array[indexOfTo].ID[0]){
							for(x=0;x<numOfNodes;x++){
								if(array[x].ID[0] == array[y].neighbor[t]){
									temp2 = x;
								}
							}
						}
					}
					
					printf("A message received by client %s, but intended for client %s. Forwarding..\n",array[y].ID,array[temp2].ID);
					array[y].inqueue = (Frames*)malloc(numOfFrame*sizeof(Frames));
					array[y].outqueue = (Frames*)malloc(numOfFrame*sizeof(Frames));
					for(z=0;z<numOfFrame;z++){ // copying outgoing into incoming
					//	*array[z].outqueue[*frameptr] = pop(frame,frameptr);
				//		printf("%s",array[z].outqueue[*frameptr].network[0]);
					//		void insertq(Node array[],Node array2[],int to,int i,int from){
						//	array[to].inqueue[i] =array[from].outqueue[,];
						//	}
						//	removeq(Node array[],int from,int i)
							
					//		array[y].inqueue[z] = array[indexOfFrom].outqueue[z];
							insertq(array,array,y,z,indexOfFrom);
							frame[z].hop++;
							array[y].outqueue[z] = array[y].inqueue[z];
							
							
						printf("	Frame #%d MAC address change: New sender MAC %s, new receiver MAC %s\n",z+1,array[y].MAC,array[temp2].MAC);							
					} // 
					array[indexOfFrom].isoEmpty = 1;
					array[y].isiEmpty = 1;
					


					// if everything is normal updates helpers and senders
					
					array[indexOfFrom].log[0] = (char**)malloc(8 * sizeof(char*));
					array[indexOfFrom].log[0][0] = (char*)malloc(strlen(asctime(info)) * sizeof(char));
					array[indexOfFrom].log[0][1] = (char*)malloc(strlen(message) * sizeof(char));
					array[indexOfFrom].log[0][2] = (char*)malloc(sizeof(numOfFrame)/4 * sizeof(char));
					array[indexOfFrom].log[0][3] = (char*)malloc(sizeof(*hopptr)/4 * sizeof(char));
					array[indexOfFrom].log[0][4] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
					array[indexOfFrom].log[0][5] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
					array[indexOfFrom].log[0][6] = (char*)malloc(20 * sizeof(char));
					array[indexOfFrom].log[0][7] = (char*)malloc(5 * sizeof(char));
					
					strcpy(array[indexOfFrom].log[0][0],asctime(info));
					strcpy(array[indexOfFrom].log[0][1],message);
					sprintf(array[indexOfFrom].log[0][2],"%d",numOfFrame);
					sprintf(array[indexOfFrom].log[0][3],"%d",*hopptr-1);
					strcpy(array[indexOfFrom].log[0][4],array[holder].ID);
					strcpy(array[indexOfFrom].log[0][5],array[indexOfTo].ID);
					strcpy(array[indexOfFrom].log[0][6],"Message Forwarded");
					strcpy(array[indexOfFrom].log[0][7],"Yes");
					
					
					
					
					
					array[y].log[0] = (char**)malloc(8 * sizeof(char*));
					array[y].log[1] = (char**)malloc(8 * sizeof(char*));
					array[y].log[1][0] = (char*)malloc(strlen(asctime(info)) * sizeof(char));
					array[y].log[1][1] = (char*)malloc(strlen(message) * sizeof(char));
					array[y].log[1][2] = (char*)malloc(sizeof(numOfFrame)/4 * sizeof(char));
					array[y].log[1][3] = (char*)malloc(sizeof(*hopptr)/4 * sizeof(char));
					array[y].log[1][4] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
					array[y].log[1][5] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
					array[y].log[1][6] = (char*)malloc(20 * sizeof(char));
					array[y].log[1][7] = (char*)malloc(5 * sizeof(char));
					
					strcpy(array[y].log[1][0],asctime(info));
					strcpy(array[y].log[1][1],message);
					sprintf(array[y].log[1][2],"%d",numOfFrame);
					sprintf(array[y].log[1][3],"%d",*hopptr);
					strcpy(array[y].log[1][4],array[holder].ID);
					strcpy(array[y].log[1][5],array[indexOfTo].ID);
					strcpy(array[y].log[1][6],"Message Received");
					strcpy(array[y].log[1][7],"Yes");
					for(h=0;h<numOfFrame;h++){
						strcpy(frame[h].physical[0],array[indexOfFrom].MAC);
						strcpy(frame[h].physical[1],array[y].MAC);
						
					}
					
				//	printf("\n %s  %s\n",array[y].ID,array[indexOfFrom].ID); // bc db 2.nd case sadece bc
				
					findTarget(array,temp,indexOfTo,numOfFrame,numOfNodes,hopptr,checkptr,message,frame,frameptr,holder); // calls again with sender becaming helper
				} // != eends
				else if(array[y].ID[0] == array[indexOfFrom].destination[i]){ // means 1 hop left
					
					
					array[y].isiEmpty = 1;
					array[indexOfFrom].isoEmpty = 1;
					array[indexOfFrom].log[0] = (char**)malloc(8 * sizeof(char*));
					array[indexOfFrom].log[0][0] = (char*)malloc(strlen(asctime(info)) * sizeof(char));
					array[indexOfFrom].log[0][1] = (char*)malloc(strlen(message) * sizeof(char));
					array[indexOfFrom].log[0][2] = (char*)malloc(sizeof(numOfFrame)/4 * sizeof(char));
					array[indexOfFrom].log[0][3] = (char*)malloc(sizeof(*hopptr)/4 * sizeof(char));
					array[indexOfFrom].log[0][4] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
					array[indexOfFrom].log[0][5] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
					array[indexOfFrom].log[0][6] = (char*)malloc(20 * sizeof(char));
					array[indexOfFrom].log[0][7] = (char*)malloc(5 * sizeof(char));
					
					strcpy(array[indexOfFrom].log[0][0],asctime(info));
					strcpy(array[indexOfFrom].log[0][1],message);
					sprintf(array[indexOfFrom].log[0][2],"%d",numOfFrame);
					sprintf(array[indexOfFrom].log[0][3],"%d",*hopptr);
					strcpy(array[indexOfFrom].log[0][4],array[holder].ID);
					strcpy(array[indexOfFrom].log[0][5],array[indexOfTo].ID);
					strcpy(array[indexOfFrom].log[0][6],"Message Forwarded");
					strcpy(array[indexOfFrom].log[0][7],"Yes");
					
					
					
					
					
					array[y].log[0] = (char**)malloc(8 * sizeof(char*));
					array[y].log[1] = (char**)malloc(8 * sizeof(char*));
					array[y].log[1][0] = (char*)malloc(strlen(asctime(info)) * sizeof(char));
					array[y].log[1][1] = (char*)malloc(strlen(message) * sizeof(char));
					array[y].log[1][2] = (char*)malloc(sizeof(numOfFrame)/4 * sizeof(char));
					array[y].log[1][3] = (char*)malloc(sizeof(*hopptr)/4 * sizeof(char));
					array[y].log[1][4] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
					array[y].log[1][5] = (char*)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char));
					array[y].log[1][6] = (char*)malloc(20 * sizeof(char));
					array[y].log[1][7] = (char*)malloc(5 * sizeof(char));
					
					strcpy(array[y].log[1][0],asctime(info));
					strcpy(array[y].log[1][1],message);
					sprintf(array[y].log[1][2],"%d",numOfFrame);
					sprintf(array[y].log[1][3],"%d",*hopptr+1);
					strcpy(array[y].log[1][4],array[holder].ID);
					strcpy(array[y].log[1][5],array[indexOfTo].ID);
					strcpy(array[y].log[1][6],"Message Received");
					strcpy(array[y].log[1][7],"Yes");
					
					for(h=0;h<numOfFrame;h++){
						strcpy(frame[h].physical[0],array[indexOfFrom].MAC);
						strcpy(frame[h].physical[1],array[y].MAC);
						frame[h].hop++;
					}
					
					
					
					
					
				}
				
				}
				
				
				
			}
		}
		

		
		
	}
//	printf("%s %d %d %d %s %d",array[0].ID,indexOfFrom,indexOfTo,numOfFrame,otherDest,numOfNodes);
//	printf("%d",hop);

}



//Frames popLayer(Frame frame[])

#endif
