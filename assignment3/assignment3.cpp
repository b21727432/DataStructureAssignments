#include<string>
#include <fstream>
#include<iostream>
#include <string.h>
#include <vector>
#include <sstream>
#include<stdlib.h>
#include <set>
using namespace std;


struct footballers{
	string ateam;
	int mgoal;
	int matchid;
	struct footballers* next;
	struct footballers* prev;
	
};
struct LinkedList{
	string fname;
	string fteam;
	struct footballers* head;
	struct LinkedList* next;
	
};
//Burak Bulut,Denizli,Pamukkale,37,
LinkedList* bas;




void fekle(string fname,string fteam,string ateam,int mgoal,int matchid){
	

	LinkedList* temp2 = bas;
	LinkedList* temp4 = bas;
	LinkedList* temp5 = bas;
	
	int checker = 0;
	
	if(bas == NULL){
		LinkedList* temp = new LinkedList();
		temp -> fname = fname;
		temp -> fteam = fteam;
		temp -> head = new footballers();
		temp -> head -> ateam = ateam;
		temp -> head -> mgoal = mgoal;
		temp -> head -> matchid = matchid;
		temp -> head -> next = NULL;
		temp -> next = NULL;
		
		bas = temp;
		
		
		
		return;
		
	}
	
	else {
		while(temp2!=NULL){
		if(temp2->fname.compare(fname)==0){
			footballers* ft = temp2 -> head;
			footballers* ft2 = temp2 -> head;
		/*	while(ft -> next!=NULL){
				ft = ft->next;
			}
			
			ft -> next = new footballers();
			ft -> next -> ateam = ateam;
			ft -> next -> mgoal = mgoal;
			ft -> next -> matchid = matchid;
			ft -> next -> next = NULL;*/
			if(matchid < ft -> matchid){
				if(matchid < ft -> matchid){
					footballers* a = new footballers();
					a -> ateam = ateam;
					a -> mgoal = mgoal;
					a -> matchid = matchid;
					a -> next = ft;
					ft -> prev = a;
					ft = a;
					
					return;
				}
				footballers* b = new footballers();
				b -> ateam = ateam;
				b -> mgoal = mgoal;
				b -> matchid = matchid;
				b -> next = ft;
				b -> prev = ft2; 
				ft2 -> next = b;
				
				return;
		//		ara -> next = temp5;
		//	temp6 -> next = ara;
				
			}
			else {
				if(checker = 0){
					ft = ft -> next;
					checker++;
				}
				else if(checker = 1){
					ft = ft -> next;
					ft2 = ft2 -> next;
					
				}
			}
			
			footballers* c = new footballers();
			c -> ateam = ateam;
			c -> mgoal = mgoal;
			c -> matchid = matchid;
			c -> next = NULL;
			footballers* d = temp2 -> head;
			while(d -> next != NULL)
		{
		d = d -> next;
		}	
		d -> next = c;
		return;
		/*	while(ft!=NULL){
				ft = ft -> next;
			}*/		
		}		
			temp2 = temp2 -> next;
		
		
	} // while ends 
	LinkedList* temp6 = bas;
	int x=0;
	while(temp5!=NULL){
		if(fname < temp5 -> fname){
		//	cout << fname<<"\n";
		//	return;
			if(fname < bas -> fname){
				LinkedList* ara = new LinkedList();
				ara -> fname = fname;
				ara -> fteam = fteam;
				ara -> head = new footballers();
				ara -> head -> ateam = ateam;
				ara -> head -> mgoal = mgoal;
				ara -> head -> matchid = matchid;
				ara -> head -> next = NULL;
				ara -> next = temp5;
				
				bas = ara;
				return;
			}
			LinkedList* ara = new LinkedList();
			ara -> fname = fname;
			ara -> fteam = fteam;
			ara -> head = new footballers();
			ara -> head -> ateam = ateam;
			ara -> head -> mgoal = mgoal;
			ara -> head -> matchid = matchid;
			ara -> head -> next = NULL;
			ara -> next = temp5;
			temp6 -> next = ara;
			
		//	cout << temp6 -> next -> fname<<"\n";
			
			
			return;
		}
		else{
			if(x==0){
				temp5 = temp5 -> next;
				x++;
			}
			else if(x == 1){
				temp5 = temp5 -> next;
				temp6 = temp6 -> next;
			}
				
		}
				
	}
		
		LinkedList* temp3 = new LinkedList();
		temp3 -> fname = fname;
		temp3 -> fteam = fteam;
		temp3 -> head = new footballers();
		temp3 -> head -> ateam = ateam;
		temp3 -> head -> mgoal = mgoal;
		temp3 -> head -> matchid = matchid;
		temp3 -> head -> next = NULL;
		temp3 -> next = NULL;
		
		while(temp4 -> next != NULL)
		{
		temp4 = temp4 -> next;
		}	
		temp4 -> next = temp3;		
		return;
	} // else ends		
}

vector<string> split(string str, char delimiter) {
  vector<string> internal;
  stringstream ss(str); // Turn the string into a stream.
  string tok;
 
  while(getline(ss, tok, delimiter)) {
    internal.push_back(tok);
  }
 
  return internal;
}

int goalFinder(){
	LinkedList* x = bas;
	
	int first = 0;
	int second = 0;
	while(x!=NULL){
		footballers* y = x->head;
		while(y!=NULL){
			if(y -> mgoal > 45){
		//		cout<<y->mgoal<<"\n";
				second++;
			}
			else if (y->mgoal <=45){
			//	cout<<y->mgoal<<"\n";
				first++;
			}
			y = y->next;
		}
		x = x->next;
	}
	if(first>second){
		return 0;
	}
	else if(second > first){
		return 1;
	}
	else if(second == first){
		return -1;
	}
}
string mostScorer(){
	string mostScorer;
	string hatTricks;
	LinkedList* top = bas;
	LinkedList* holder;
	int goalt=0;
	int max=0;
	while(top != NULL){
		goalt = 0;
		footballers* ft = top -> head;
		while(ft != NULL){
			goalt++;
			ft = ft->next;
		}
		if(goalt > max){
			max = goalt;
			holder = top;
		}
		top = top -> next;
	}
	LinkedList* finder = bas;
	
	int goaltd;
	while(finder != NULL){
		goaltd = 0;
		footballers* fd = finder -> head;
		while(fd != NULL){
			goaltd++;
			fd = fd ->next;
		}
		if(goaltd == max){
			mostScorer = mostScorer + finder -> fname + "\n";
			
		}
	/*	if(goaltd >= 3){
			hatTricks = hatTricks + finder ->fname + "\n";
		}*/
		finder = finder -> next;
	}
	
	return mostScorer;
}

string hTricks(){
	string mostScorer;
	string hatTricks;
	LinkedList* top = bas;
	LinkedList* holder;
	int goalt=0;
	int max=0;
	while(top != NULL){
		goalt = 0;
		footballers* ft = top -> head;
		while(ft != NULL){
			goalt++;
			ft = ft->next;
		}
		if(goalt > max){
			max = goalt;
			holder = top;
		}
		top = top -> next;
	}
	LinkedList* finder = bas;
	int idholder = 0;
	int idholder2 = 0;
	int goaltd;
	int hat;
	while(finder != NULL){
		hat = 0;
		goaltd = 0;
		footballers* fd = finder -> head;
		idholder = fd -> matchid;
		while(fd != NULL){
			goaltd++;
			
			idholder2 = fd -> matchid;
			if(idholder == idholder2){
				hat++;
				
			}
			else{
				idholder = idholder2;
			}
			fd = fd ->next;
			
		}
		if(goaltd == max){
			mostScorer = mostScorer + finder -> fname + "\n";
			
		}
		if(hat >= 3){
			hatTricks = hatTricks + finder ->fname + "\n";
		}
		finder = finder -> next;
	}
	
	return hatTricks;
}
set<string> Teams(){
	set<string> teams;
	LinkedList* x = bas;
	while(x != NULL){
		teams.insert(x -> fteam);
		
		x = x -> next;
	}
	return teams;
}

void footballerfinder(string fname,ofstream& outputfile){
	//Footballer Name: Karim Benzema,Away Team: Municipality Sports,Min of Goal: 61,Match ID: 1

	LinkedList* x = bas;
	while(x!=NULL){
		if(x -> fname == fname){
			footballers* y = x -> head;
			while(y!=NULL){
				outputfile <<"Footballer Name: "<<x->fname<<",Away Team: "<< y -> ateam <<",Min of Goal: "<<y ->mgoal<<",Match ID: "<<y->matchid<<"\n";
				
				y = y->next;
			}
		}
		x = x->next;
	}
}
set<int> matchfinder(string fname){
	set<int> matches;
	LinkedList* x = bas;
	while(x!=NULL){
		
		if(x -> fname == fname){
			footballers* y = x -> head;
			while(y!=NULL){
				matches.insert( y -> matchid);
				y = y -> next;
			}
		}
		
		
		x = x->next;
	}
	
	return matches;
}
int main(int argc, char *argv[]){
	bas = NULL;
	string line;
	ifstream myfile (argv[1]);
	
	ofstream outputfile (argv[3]);
	
	
	
	if (myfile.is_open())
	{
    	while ( getline (myfile,line) )
		{
			
      		vector<string> sep = split(line, ',');
			fekle(sep[0],sep[1],sep[2], atoi(sep[3].c_str()), atoi(sep[4].c_str()));
			
			      							   
    	}
    	myfile.close();
    }
    
    
	int goll = goalFinder();
	outputfile << "1)THE MOST SCORED HALF"<<"\n";
	outputfile << goll<<"\n";  // ilk print yani ilk yarý ya da ikinci yarý daha fazla gol atýldýgýný söylüyor
	
	string topScorer = mostScorer();
	string hatTricks = hTricks();
	outputfile << "2)GOAL SCORER"<<"\n";
	outputfile << topScorer<<""; //en fazla golu atan / atanlar
	outputfile << "3)THE NAMES OF FOOTBALLERS WHO SCORED HAT-TRICK"<<"\n";
	outputfile << hatTricks <<""; //prints the players with 3 goals or more on same match same id

	
	
	

	set<string> teams = Teams();
	string line2;
	ifstream myfile2 (argv[2]);
	outputfile << "4)LIST OF TEAMS"<<"\n";
	for (set<string>::iterator it=teams.begin(); it!=teams.end(); ++it)
    	outputfile << *it << "\n";  // all teams 
    
    outputfile << "5)LIST OF FOOTBALLERS"<<"\n";
    LinkedList* x = bas;
    while(x!=NULL){
    	outputfile << x->fname<<"\n"; //all footballers
    	x = x->next;
	}
    
    
    
	//	cout << bas -> next ->  next -> next-> head  -> ateam << bas -> next ->next -> next-> head -> matchid<<"";
	int linenum = 1;
	if (myfile2.is_open())
	{
    	while ( getline (myfile2,line2) )
		{
			vector<string> sep2 = split(line2, ',');
			if(linenum == 1){
				outputfile<<"6)MATCHES OF GIVEN FOOTBALLER"<<"\n";
      			outputfile << "Matches of "<<sep2[0]<<"\n";
				footballerfinder(sep2[0],outputfile);
				outputfile << "Matches of "<<sep2[1]<<"\n";
				footballerfinder(sep2[1],outputfile);
				linenum++;
				
			}
			else if(linenum == 2){
				set<int> firstset = matchfinder(sep2[0]);
				outputfile << "7)ASCENDING ORDER ACCORDING TO MATCH ID"<<"\n";
				for (set<int>::iterator it2=firstset.begin(); it2!=firstset.end(); ++it2)
    				outputfile <<"footballer Name: "<<sep2[0]<<",Match ID: "<< *it2 << "\n";
    				
				set<int> secondset = matchfinder(sep2[1]);
				for (set<int>::iterator it3=secondset.begin(); it3!=secondset.end(); ++it3)
					//footballer Name: Diego Costa,Match ID:2
    				outputfile <<"footballer Name: "<<sep2[1]<<",Match ID: "<< *it3 << "\n";
    			linenum++;
    			
				
			}
			else if(linenum == 3){
				set<int> thirdset = matchfinder(sep2[0]);
				outputfile << "8)DESCENDING ORDER ACCORDING TO MATCH ID"<<"\n";
				for (set<int>::reverse_iterator it4=thirdset.rbegin(); it4!=thirdset.rend(); ++it4)
    				outputfile <<"footballer Name: "<<sep2[0]<<",Match ID: "<< *it4 << "\n";
    			set<int> fourthset = matchfinder(sep2[1]);
    			for (set<int>::reverse_iterator it5=fourthset.rbegin(); it5!=fourthset.rend(); ++it5)
    				outputfile <<"footballer Name: "<<sep2[1]<<",Match ID: "<< *it5 << "\n";
			}
      		
			
			
			      							   
    	}
    	myfile.close();
    }
    return 0;
}
