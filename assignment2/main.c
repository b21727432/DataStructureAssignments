#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"header.h"


int main(int argc,char* argv[]){
	int indexOfFrom,indexOfTo,hop=0;
	int check=0;
	int* checkptr = &check;
	int* hopptr = &hop;
//	char frames[4][4][3][25];	
	FILE *clients = fopen(argv[1],"rb+");
	int numOfNodes;
	fscanf(clients,"%d",&numOfNodes);
	Node array[numOfNodes];
	int i=0,y=0,z=0;

	for(i=0;i<numOfNodes;i++){ // this updates id,mac,ip's also creates some memory
		fscanf(clients,"%s",array[i].ID); // updating id
		fscanf(clients,"%s",array[i].IP); // updating ip 	
		fscanf(clients,"%s",array[i].MAC); // updating mac
		array[i].isiEmpty = 0;
		array[i].isoEmpty = 0;
		array[i].log = (char***)malloc(2*sizeof(char**));
		array[i].destination = (char*)malloc(numOfNodes*sizeof(char)); // creating memory
		array[i].neighbor = (char*)malloc(numOfNodes*sizeof(char));
		

	}
	
	FILE *routing = fopen(argv[2],"rb+"); // opening routings
	char temp[10];
	char *temp2;
	i=0;
	while(fgets(temp,10,routing)){  //updating routing table
		temp2 = strtok(temp," ");
		if(*temp2 == '-'){ // if the target is - continue
			i++;
			y=0;
			continue;
		}
		array[i].destination[y] = temp2[0];
		temp2 = strtok(NULL," ");
		array[i].neighbor[y] = temp2[0];
		y++;
	}
	int messagesize = atoi(argv[4]); // getting the message size
	FILE *commands2 = fopen(argv[3],"rb+"); // reading the 3rd file
	char holderline[1000],cpholderline[1000];
	char* holderpart;
	char* messageholder;
	char* messagecalar;
	int numOfFrame;
	while(fgets(holderline,1000,commands2)){ // getting the message,messagesize,Frame size
		strcpy(cpholderline,holderline);
		holderpart = strtok(holderline," ");
		if(strcmp(holderpart,"MESSAGE")==0){
			messageholder = strtok(cpholderline,"#");
			messageholder = strtok(NULL,"#");
			messagecalar = (char*)malloc(strlen(messageholder) * sizeof(char)+1);
			strcpy(messagecalar,messageholder); // copies the message size
			
			numOfFrame = strlen(messageholder)/messagesize;
			if((strlen(messageholder)%messagesize)!=0){
				numOfFrame++; // gets the frame number 
			}
		}
	}
	fclose(commands2); // closing because we will open again

	
	FILE *commands = fopen(argv[3],"rb+"); // r opening
	
	char* outgoingport = argv[5];
	char* incomingport = argv[6];
	char line[1000],cpline[1000];
	char *partline,*message;
	fgets(line,1000,commands);
	int numOfCommands = atoi(line);
	numOfCommands++;
	numOfCommands = numOfCommands -1;
	
	

	char* from;
	char* to;


	
	

	
	y=0,z=0;
	int n=0;


	int layerx;
	int* layer;


	int framesize;
	int *frameptr;

	
	Frames frame[numOfFrame]; // creating array of frames
	char chunkmessage[numOfFrame][messagesize+1]; // creating small message parts
	// this loads c's outgoing
	for(i=0;i<numOfFrame;i++){
		frame[i].hop = 0;
	}
	
	while(fgets(line,1000,commands)){  // reading the commands
		strcpy(cpline,line); // we need another copy to use in message part

		partline = strtok(line," ");
		if(strcmp(partline,"MESSAGE")==0){ // if command is message 
			
			printf("----------\n%s----------",cpline); // printing the line 
			
			from = strtok(NULL," "); // splitting 
			to = strtok(NULL," ");
			for(i=0;i<numOfNodes;i++){ // getting the sender and reciever
				if(strcmp(array[i].ID,from)==0){
					indexOfFrom = i;
			
				}
				if(strcmp(array[i].ID,to)==0){
					indexOfTo = i;
				}
			}
			
			message = strtok(cpline,"#"); // spliting the message 
			message = strtok(NULL,"#");	
			
		
			
			y=0,z=0;
			n=0;
			
			for(i=0;i<=strlen(message);i++){ // updating message parts from the original
				chunkmessage[y][z] = message[i];
				z++;	
				if(i == messagesize-1+(messagesize*n)){
					chunkmessage[y][z] = '\0'; // adding null to the last char
					y++;
					z=0;
					n++;
							
				}				
			}
		
			
					layerx = 0;
					layer = &layerx;
				
				int helper,loop;
				for(i=0;i<numOfNodes;i++){
					if(array[indexOfFrom].destination[i] == array[indexOfTo].ID[0]){
						for(loop = 0;loop<numOfNodes;loop++){
							if(array[loop].ID[0] == array[indexOfFrom].neighbor[i]){
								helper = loop;
								
							}
						}
					}
				}
				for(i=0;i<numOfFrame;i++){ //allocating and updating frame
					
					
					frame[i].physical = (char **)malloc(2 * sizeof(char*)); 
					frame[i].physical[0] = (char *)malloc(sizeof(array[indexOfFrom].MAC) * sizeof(char)+1);
					frame[i].physical[1] = (char *)malloc(sizeof(array[indexOfFrom].MAC) * sizeof(char)+1);
				
					pushLayer(frame,array[indexOfFrom].MAC,array[helper].MAC,NULL,layer,i);  // pushing layer into stack
				
					frame[i].network = (char **)malloc(2 * sizeof(char*)); 
					frame[i].network[0] = (char *)malloc(sizeof(array[indexOfFrom].IP) * sizeof(char)+1);
					frame[i].network[1] = (char *)malloc(sizeof(array[indexOfFrom].IP) * sizeof(char)+1);
			
					pushLayer(frame,array[indexOfFrom].IP,array[indexOfTo].IP,NULL,layer,i);  // pushing layer into stack
					
					frame[i].transport = (char **)malloc(2 * sizeof(char*));
					frame[i].transport[0] = (char *)malloc(sizeof(outgoingport) * sizeof(char)+1);
					frame[i].transport[1] = (char *)malloc(sizeof(incomingport) * sizeof(char)+1);
			
					pushLayer(frame,outgoingport,incomingport,NULL,layer,i);   // pushing layer into stack
					
					frame[i].application = (char **)malloc(3 * sizeof(char*));
					frame[i].application[0] = (char *)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char)+1);
					frame[i].application[1] = (char *)malloc(sizeof(array[indexOfFrom].ID) * sizeof(char)+1);
					frame[i].application[2] = (char *)malloc(sizeof(chunkmessage[i]) * sizeof(char)+1);
			
					pushLayer(frame,array[indexOfFrom].ID,array[indexOfTo].ID,chunkmessage[i],layer,i); // pushing layer into stack
					
					
				}
				
				
				
				array[indexOfFrom].outqueue = (Frames*)malloc(numOfFrame*sizeof(Frames)); // allocating memory
				array[indexOfFrom].isoEmpty = 1;
				printf("\nMessage to be sent %s\n",message); // printing the message
				
				for(i=0;i<numOfFrame;i++){ // printing the created frames
					printf("\nFrame #%d\n",i+1);
					printf("Sender MAC address: %s, Receiver MAC address: %s\n",array[indexOfFrom].MAC,array[helper].MAC);
					printf("Sender IP address: %s, Receiver IP address: %s\n",array[indexOfFrom].IP,array[indexOfTo].IP);
					printf("Sender port number: %s, Receiver port number: %s\n",outgoingport,incomingport);
					printf("Sender ID: %s, Receiver ID: %s\n",array[indexOfFrom].ID,array[indexOfTo].ID);
					printf("Message chunk carried: %s",frame[i].application[2]);
					printf("\n---------");
			//		printf("%s",frame[i].physical[0]);
					
				}
			
			//	array[indexOfFrom].outqueue[0] = frame[2];
				framesize = numOfFrame;
				frameptr = &framesize;
				for(i=0;i<numOfFrame;i++){
				//	array[indexOfFrom].outqueue[i] = frame[i];
					//array[indexOfFrom].outqueue[numOfFrame-i-1] = pop(frame,frameptr);
					addqueue(array,indexOfFrom,i,frame,numOfFrame,frameptr); // adding my frames into queue
					
				}
				} // message ends
		else if(strcmp(partline,"SHOW_FRAME_INFO")==0){ // if showframe info command comes
			
			char* target = strtok(NULL," "); // getting target ( sender
		//	printf("%s",target); // prints c 
			char* temp = strtok(NULL," "); // in or out
			int index = atoi(strtok(NULL," ")); // which frame
			
			
			for(i=0;i<numOfNodes;i++){
				if(strcmp(array[i].ID,target)==0){ // found the wanted id
					
					if(strcmp("out",temp)==0){ // if the command is out 
						if(array[i].isoEmpty == 1){ // if queue is not empty
						
							if(index<=numOfFrame){
								printf("\n---------------------------------\nCommand: SHOW_FRAME_INFO %s out %d\n---------------------------------",target,index);
								printf("\nCurrent Frame #%d on the outgoing queue of client %s\n",index,target);
								printf("Carried Message: %s\n",frame[index-1].application[2]);
								printf("Layer 0 info: Sender ID: %s, Receiver ID: %s\n",frame[index-1].application[0],frame[index-1].application[1]);
								printf("Layer 1 info: Sender port number: %s, Receiver port number: %s\n",outgoingport,incomingport);
								printf("Layer 2 info: Sender IP address %s, Receiver IP address: %s\n",frame[index-1].network[0],frame[index-1].network[1]);
								printf("Layer 3 info: Sender MAC address: %s, Receiver MAC address: %s",frame[index-1].physical[0],frame[index-1].physical[1]);
								if(frame[index-1].hop == 0){
									
							
								printf("\nNumber of hops so far = %d",frame[index-1].hop);
									}
								else if(frame[index-1].hop !=0){
									printf("\nNumber of hops so far = %d",frame[index-1].hop-1);
								}
							}
							else if(index>numOfFrame){ // if out of bounds
								printf("\n--------------------------------\nCommand: SHOW_FRAME_INFO %s %d\n--------------------------------\nNo such frame",target,index);
							}
						}
						else if(array[i].isoEmpty == 0){ // if empty
							printf("\n--------------------------------\nCommand: SHOW_FRAME_INFO %s %d\n--------------------------------\nNo such frame",target,index);
						}
					}
					else if(strcmp("in",temp)==0){ // if wants the incoming queue
						if(array[i].isiEmpty == 1){
						
						if(index<=numOfFrame){
								printf("\n---------------------------------\nCommand: SHOW_FRAME_INFO %s in %d\n---------------------------------",target,index);
								printf("\nCurrent Frame #%d on the incoming queue of client %s\n",index,target);
								printf("Carried Message: %s\n",frame[index-1].application[2]);
								printf("Layer 0 info: Sender ID: %s, Receiver ID: %s\n",frame[index-1].application[0],frame[index-1].application[1]);
								printf("Layer 1 info: Sender port number: %s, Receiver port number: %s\n",outgoingport,incomingport);
								printf("Layer 2 info: Sender IP address %s, Receiver IP address: %s\n",frame[index-1].network[0],frame[index-1].network[1]);
								printf("Layer 3 info: Sender MAC address: %s, Receiver MAC address: %s",frame[index-1].physical[0],frame[index-1].physical[1]);
								if(frame[index-1].hop == 0){
									
							
								printf("\nNumber of hops so far = %d",frame[index-1].hop);
									}
								else if(frame[index-1].hop !=0){
									printf("\nNumber of hops so far = %d",frame[index-1].hop-1);
								}
						}
						else if(index>numOfFrame){ // out of bounds
						//	printf("invalid");
							
							printf("\n--------------------------------\nCommand: SHOW_FRAME_INFO %s %d\n--------------------------------\nNo such frame",target,index);
						}
					}
					else if(array[i].isiEmpty == 0){
						
						printf("\n--------------------------------\nCommand: SHOW_FRAME_INFO %s %d\n--------------------------------\nNo such frame",target,index);			
							}
				}
				}
			}
		} // SHOW FRAME INFO ENDSSS
		else if(strcmp(partline,"SHOW_Q_INFO")==0){ // if the command is show q
			
			char* target = strtok(NULL," "); // wanted client 
			char* inout = strtok(NULL," \n"); // in our out
	//		printf("%s %s\n",inout,target); c out c in works perfect 
			if(strcmp("in",inout)==0){ // no problem entering this part 
				printf("\n--------------------------\nCommand: SHOW_Q_INFO %s in\n--------------------------\n",target);
				if(array[indexOfFrom].isiEmpty == 0){
					printf("Client C Incoming Queue Status \nCurrent total number of frames: 0");
				}
				else if(array[indexOfFrom].isiEmpty == 1){
					printf("Client %s Incoming Queue Status \nCurrent total number of frames: %d",target,numOfFrame);
				}
				
				
			}
			if(strcmp("out",inout)==0){
				printf("\n---------------------------\nCommand: SHOW_Q_INFO C out\n---------------------------\n");
				if(array[indexOfFrom].isoEmpty == 0){
					printf("Client %s Outgoing Queue Status \nCurrent total number of frames: 0",target);
				}
				else if(array[indexOfFrom].isoEmpty == 1){
					printf("Client %s Outgoing Queue Status\nCurrent total number of frames: %d",target,numOfFrame);
				}
				
			}
		//	printf("%d",sizeof(array[2].incoming)); burayý malloc ile düzenle þuan 4 4 3 25 oldugundan 1200 bastýrýyor
		}
		else if(strcmp(partline,"SEND")==0){ // if command is send 
			
			printf("\n----------------\nCommand: SEND %s\n----------------\n",array[indexOfFrom].ID);
			findTarget(array,indexOfFrom,indexOfTo,numOfFrame,numOfNodes,hopptr,checkptr,messagecalar,frame,frameptr,indexOfFrom); // call my recursive function
			
			
			
		/*	printf("%d\n",*array[3].log[1][2]);
			return;*/
			if(*checkptr ==0){ // if failed
			
			printf("A message received by client %s from client %s after a total of %d hops.\n",array[indexOfFrom].ID,array[indexOfTo].ID,*hopptr+1);
			printf("Message:%s",messagecalar);
		}

			
			
		}
		else if(strcmp(partline,"PRINT_LOG")==0){ 
			char* target = strtok(NULL," \n"); // which client
			int sayac=1;
			printf("\n---------------------\nCommand: PRINT_LOG %s\n---------------------",target);
			printf("\nClient %s Logs\n--------------",target);
			for(i=0;i<numOfNodes;i++){
				if(array[i].ID[0] == target[0]){ // found the wanted client 
					
					if(array[i].isiEmpty == 1){ // if not empty
						
						
						printf("\nLog Entry #%d:\nTimestamp:%sMessage:%s\nNumber of frames: %s\nNumber of hops: %s\nSender ID: %s\nReceiver ID: %s\nActivity: %s\nSuccess: %s\n--------------",sayac,array[i].log[1][0],array[i].log[1][1],array[i].log[1][2],array[i].log[1][3],array[i].log[1][4],array[i].log[1][5],array[i].log[1][6],array[i].log[1][7]);
						sayac++;
						
						
					}
					if(array[i].isoEmpty == 1){ // if not empty
						
						printf("\nLog Entry #%d:\nTimestamp:%sMessage:%s\nNumber of frames: %s\nNumber of hops: %s\nSender ID: %s\nReceiver ID: %s\nActivity: %s\nSuccess: %s\n--------------",sayac,array[i].log[0][0],array[i].log[0][1],array[i].log[0][2],array[i].log[0][3],array[i].log[0][4],array[i].log[0][5],array[i].log[0][6],array[i].log[0][7]);
						
					}
					
				
					
				}
			}
		}
		else{
		
			char* unknown = strtok(NULL," \n");
			printf("\n---------------------\nCommand: %s %s\n---------------------\nInvalid command.",partline,unknown);
	}
			
		
	} // reading commands
	
//	printf("%s  %s  %s",array[4].ID,array[4].IP,array[4].MAC); //works fine
//	printf("%s\n",array[2].outgoing[3][3][2]); // works fine
//	printf("%s",frame[0].application[0]);
    return 0;
} // main ends



