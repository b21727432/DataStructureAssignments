#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void searchTreasure(int **map,int **key,int x,int y,int z,int row,int column,FILE *f); // my recursive search treasure function
int **createMap(int len1,int len2); // my creating matrix function for key and map
void setMatrix(FILE *mapinput,int **map,int row,int column); // my function to load data to matrix
void freefile(int **map,int len1); // my free function
int main( int argc, char *argv[]){
	char *str,*str2; // all char variables to store lines , argv[1] and argv[2]
	str = strtok(argv[1],"x"); // split from the x we get first integer
	int len1 = atoi(str); // len1 first integer
	str2 = strtok(NULL,"x"); // second integer
	int len2 = atoi(str2);
	int keysize = atoi(argv[2]); // getting integer keysize from argv[3]
	FILE *mapinput = fopen(argv[3],"r"); // to read mapmatrix using argv[4]
	FILE *keyinput = fopen(argv[4],"r"); // to read keymatrix using argv[5]
    int **map = createMap(len1,len2); // creating map function call
    int **key = createMap(keysize,keysize);
 	setMatrix(mapinput,map,len1,len2);	
 	setMatrix(keyinput,key,keysize,keysize);
	FILE *output = fopen(argv[5], "w"); // to write  fprintf ( f, " asdaadasd %d", 15) opening output file to write into
	int x = keysize / 2; // starting indexes
	int y = keysize / 2; // start,mg indexes
	searchTreasure(map,key,x,y,keysize,len1,len2,output); // recursive function call 
	freefile(map,len1);
	freefile(key,keysize);
	fclose(output); // closing output file
	fclose(mapinput);
	fclose(keyinput);
	return 0;	 // code ends here 
}
void searchTreasure(int **map,int **key,int x,int y,int z,int row,int column,FILE *output){ // void function call because we need to return value
		int sum = 0,mid = z/2,tempx,tempy,loop=0,loop1=0; // needed integer variables 
		for(tempy = y - mid ;tempy < y + mid+1;tempy++){ // to search through rows of  map and key
			for(tempx = x - mid;tempx < x + mid+1; tempx++){ // loop in column
				sum += map[tempy][tempx] * key[loop][loop1]; // increasing sum by the dot product
				loop1++; // increasing the index
			}
			loop1 = 0; // reseting column index
			loop++; // increasing row index
		}	
		int final = sum % 5; // taking mod of our sum
		fprintf(output,"%d,%d:%d",y,x,sum); // writing indexes and sum
		if(final == 0){ // if final is zero means we have found the treasure
		}
		if(final == 1){ // if final is 1 means we need to move up which is row
			if((y-z)<=0){ // if row is out of bounds go reverse
				fprintf(output,"\n");
				searchTreasure(map,key,x,y+z,z,row,column,output); //reverse case		
			}
			else{
				fprintf(output,"\n");
				searchTreasure(map,key,x,y-z,z,row,column,output); // normal case		
			}
		} // 1st case
		if(final == 2){ // if final is 2 means we need to go down
			if((y+z)>=row){ // if out of bounds go reverse
				fprintf(output,"\n");			
				searchTreasure(map,key,x,y-z,z,row,column,output); // reverse				
			}
			else{
				fprintf(output,"\n");
				searchTreasure(map,key,x,y+z,z,row,column,output); // normal
			}
		} // 2nd case
		if(final == 3){ // if final is 3 go right
			if((x+z)>=column){
				fprintf(output,"\n");
				searchTreasure(map,key,x-z,y,z,row,column,output); // reverse if out of bounds
			}
			else{
				fprintf(output,"\n");
				searchTreasure(map,key,x+z,y,z,row,column,output); // normal
			}			
		} // 3rd case
		if (final == 4){ // if final is 4 go left
			if((x-z)<=0){
				fprintf(output,"\n");
				searchTreasure(map,key,x+z,y,z,row,column,output); // if out of bounds reverse
			}
			else{
				fprintf(output,"\n");
				searchTreasure(map,key,x-z,y,z,row,column,output); // normal
			}
		} // 4th case
	} // funcion ends
int **createMap(int len1,int len2){
	int **map = (int **)malloc(len1 * sizeof(int *)); // creating 2d dynamic map matrics
	int i;
    for (i=0; i<len1; i++)
         map[i] = (int *)malloc(len2 * sizeof(int)); 
    return map;
}
void setMatrix(FILE *mapinput,int **map,int row,int column){ // getting the values in inputs into my 2d arrays
	int i=0,j=0;
	for(i=0;i<row;i++){
		for(j=0;j<column;j++){
			fscanf(mapinput,"%d",&map[i][j]); // scaning and assigning to matrix
		}
	}
}
void freefile(int **map,int len1){
	int i=0;
	for(i=0;i<len1;i++){ // freeing dynamic memory
		free(map[i]); // freeing rows
	}
	free(map); // freeing the pointer
}

