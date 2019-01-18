#include <stdlib.h>
#include <stdio.h>
#include <string.h>

FILE *ofile;

typedef struct Trie { // struct
	
	char character;
	char password[10];
	struct Trie* childs[26];
	
	
} agac;

agac* head;


struct Trie* nodeMaker(){ // to create head node
	agac* node = (agac*)malloc(sizeof(agac));
	
	
	
	int i;
	for(i = 0; i<26 ; i++){ // assigning all e lements to null
		node -> childs[i] = 0;
	}
	node->password[0] = '\0';
	return node;
}

void ekle(agac* head,char* str,char* password){ // insert function
	
	agac* temp = head;
	
	
	int i;
	for(i = 0; i<strlen(str) ; i++){ // len i kadar dön
		if(temp -> childs[str[i] - 'a'] == NULL){
			temp -> childs[str[i] - 'a'] = nodeMaker();
		}
		
		temp = temp -> childs[str[i] - 'a'];
		temp -> character = str[i];
		if(i == strlen(str)-1){ // eger coktan o isim varsa
			if(temp -> password[0] != '\0'){
				fprintf(ofile,"'%s' reserved username\n",str);
			}
			else{ // passwordu son nota ekle
			//	temp -> password = password;
				strcpy(temp->password,password);
				fprintf(ofile,"'%s' was added\n",str);
			}
			
			
			
		}
	}
	
	
}

int search(agac* head,char* str){ // search func
	if (head == NULL)
		return 0;

	agac* temp = head;
	agac* temp2 = head;
	str = strtok(str,"\n");
	int i;
	for(i=0;i<strlen(str);i++){ // boyu kadar ilerle
		
		temp = temp -> childs[str[i]-'a'];
	
		if(temp == NULL){
			if(temp2 -> childs[str[0]-'a'] == NULL){ // if there is no such noode no record
				str = strtok(str,"\n");
				fprintf(ofile,"'%s' no record\n",str);
				return -3;
			}
			if(temp2 -> childs[str[0]-'a'] -> character == str[0]){ // if only first char is same
				str = strtok(str,"\n");
				fprintf(ofile,"'%s' incorrect username\n",str);
				return -2; // incorrect username
				}
			return 0; //olmama durumu
		}
		else{
			
		
		if(i == strlen(str)-1){ // last node da ise 
			if(temp -> password[0] == '\0'){ // not enough username
				str = strtok(str,"\n");
				fprintf(ofile,"'%s' not enough username\n",str);
				return -1; // not enough 
			}
			else { // user found
				str = strtok(str,"\n");
				
				fprintf(ofile,"'%s' password ",str);
				
				fprintf(ofile,"%s",temp->password);
			}
			
		}
		}
	}
	return 0;
/*	if(temp2 -> childs[str[0]-'a'] -> character == str[0]){
		return -2; // incorrect username
	}*/
	
}

void searchOut(int x){
	if(x == -3){
	//	printf("no record\n");
	}
	else if(x == -1){
	//	printf("not enough\n");
	}
	else if(x == -2){
//		printf("incorrect\n");
	}
}

void query(agac* head,char* str,char* password){ // login system
	if (head == NULL)
		return ;
	agac* temp = head;
	agac* temp2 = head;
	int i;
	for(i=0;i<strlen(str);i++){ // str sayýsý kadar dönücek
		
		temp = temp -> childs[str[i]-'a'];
		
		if(temp == NULL){ // if null we found no record
			if(temp2 -> childs[str[0]-'a'] == NULL){
				fprintf(ofile,"'%s' no record\n",str);
				return;
			}
			if(temp2 -> childs[str[0]-'a'] -> character == str[0]){ // some char exist others not
				fprintf(ofile,"'%s' incorrect username\n",str);
				return ; // incorrect username
				}
			
		}
		if(i == strlen(str)-1){
			if(temp -> password[0] == '\0'){ // if there is no password
				
				fprintf(ofile,"'%s' not enough username\n",str);
				return; // not enough 
			}
			else { // if we found the user and we will check password 
				if(strcmp(temp->password,password)==0){
					fprintf(ofile,"'%s' successful login\n",str); // sifreler aynýysa
					return;
				}
				else{
					fprintf(ofile,"'%s' incorrect password\n",str); // sifre farklýysa
					return;
				}
			}
			
		}
	}
}
void delete(agac* head,char* str){
	agac* temp = head;
	agac* temp2 = head;
	

	int i;
	for(i=0;i<strlen(str)-1;i++){ // len kadar dön
		
		temp = temp -> childs[str[i]-'a'];
		
		if(temp == NULL){ // no record 
			if(temp2 -> childs[str[0]-'a'] == NULL){
				str = strtok(str,"\n");
				fprintf(ofile,"'%s' no record\n",str);
				return;
			}
			if(temp2 -> childs[str[0]-'a'] -> character == str[0]){ // if first n exist
				str = strtok(str,"\n");
				fprintf(ofile,"'%s' incorrect username\n",str);
				return ; // incorrect username
				}
			
		}
		if(i == strlen(str)-2){ // sifre yok demek ki eksik
			if(temp -> password[0] == '\0'){
				str = strtok(str,"\n");
				fprintf(ofile,"'%s' not enough username\n",str);
				return; // not enough 
			}
			else {
				if(temp -> password[0] != '\0'){ // silecegimizi buldul
					
					
					int len = strlen(str)-1;
					int b;
					for(b=0;b<strlen(str)-1;b++){ // nodelarý teker teker gezicek
						
						int a;
						agac* temp3 = head;
						agac* temp4 = head;
						for(a=0;a<len;a++){
							temp3 = temp3 -> childs[str[a]-'a']; // gets last node
						}
				//		printf("%c",temp3 -> character);
						int c,count=0;
						for(c=0;c<26;c++){
							if(temp3 -> childs[c] != NULL){
								count++;
							}
						} // sount sayýsýný aldýk ona göre iþlem
						if(count == 0){
						//	printf("%c",temp3 -> character);
							int d;
							for(d=0;d<len-1;d++){
								temp4 = temp4 -> childs[str[d]-'a'];
							}
							temp4->childs[temp3->character-'a'] = NULL;
							len = len -1;
							
						}
						else{
							temp3 -> password[0] = '\0';
							str = strtok(str,"\n");
							fprintf(ofile,"'%s' deletion is succesful\n",str);
							break;
						}
						
					}
					
				}
				
			}
			
		}
	}
}


/*void list(agac* temp){
	
	int i;
	if(temp == NULL){
		return;
	}
	for(i=0;i<26;i++){
		if(temp -> childs[i] != NULL){
			
			
			printf("%c \n",temp -> childs[i] -> character);
			
			
		}
		
		
	}
	
}*/
void display(agac* root, char str[], int level,int dal) 
{ 
    int a,count=0;
    for(a=0;a<26;a++){
    	if(root -> childs[a] != NULL){
    		count++; // child sayýsýný al
		}
	}
	if(count > 1 && dal ==0){ // ortak kelimeyi yaz
		if(level!=0){
			dal = 1;
			str[level] = '\0';
			fprintf(ofile,"-%s\n",str);
		}
	}
	if(count == 0){ // son node 
		if(dal == 1){ // dallanma var bosluk býrakarak yaz
			str[level]= '\0';
			fprintf(ofile,"\t-%s\n",str);
		}
		if(dal == 0){
			str[level]= '\0';
			fprintf(ofile,"-%s\n",str); // hic dal yok ayrý bir isim
		}
	}
	else if(root -> password[0] != '\0'){
		if(dal == 1){
			str[level] = '\0';
			fprintf(ofile,"\t-%s\n",str); // bu küçükleri yazmak için
		}
	}
    int i; 
    for (i = 0; i < 26; i++)  
    {
        if (root->childs[i])  
        { 
            str[level] = i + 'a'; 
            display(root->childs[i], str, level + 1,dal); // recursive call child girip calllucak
        } 
    } 
} 

int main(int argc,char* argv[]){
	
	head = nodeMaker();
	char line[999];
	char* subline;
	char* person;
	char* password;
	FILE *file;
	file = fopen(argv[1], "r");
	ofile = fopen("output.txt","w");
	while(fgets(line,999,file)){
		subline = strtok(line," \n");
		if(strcmp(subline,"-a")==0){
			agac* temp = head;
			person = strtok(NULL," ");
			password = (strtok(NULL," "));
			ekle(temp,person,password);
		}
		else if(strcmp(subline,"-s")==0){
			agac* temp = head;
			person = strtok(NULL," ");
			search(temp,person);
		}
		else if(strcmp(subline,"-q")==0){
			agac* temp = head;
			person = strtok(NULL," ");
			password = (strtok(NULL," "));
			query(temp,person,password);
		}
		else if(strcmp(subline,"-d")==0){
			agac* temp = head;
			person = strtok(NULL," ");
			delete(temp,person);
		}
		else if(strcmp(subline,"-l")==0){
			agac* temp = head;
			char str[999];
			display(temp,str,0,0);
			
	//	printf("%c",head -> childs[])
		//	list(temp);
		}
	}
//	delete(head,"selma");
//	list(head);

	
//	printf("%d",head -> childs['a'-'a'] -> childs['l' - 'a'] -> childs['m' - 'a'] ->  password);
//	searchOut(search(head,"a"));
//	query(head,"ba",12);
	
//	delete(head,"ali");
//	searchOut(search(head,"alm"));
	return 0;
}
