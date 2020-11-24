/*
 ============================================================================
 Name        : NBt.c
 Author      : Eray Okutay
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
//#include <conio.h>


int N = 3;
int M = 7;
int Z ;
int s;


//Start potIndex with 0 and root with main root
//https://www.geeksforgeeks.org/tree-traversals-inorder-preorder-and-postorder/ (I've took the recursion idea)
//Appends elements to preorderTree in preorder sequence with recursion
void printInorder(int arr[M][N],int preorderTree[M],int root,FILE *out,int M,int N) {

    if (root!=0) {


        //Recursion of left child
        int element_index = findElementIndex(arr, root,M,N);

        printInorder(arr,preorderTree,arr[element_index][0],out,M,N) ;

        //append root
        int lastIndex = findLastEmptyInorderTreeIndex(preorderTree,M);
        appendToFile(out,root);
        printf("%d",root);
        printf(" ");


      //  arr[element_index][1]
        //Recursion of right child
        printInorder(arr,preorderTree,arr[element_index][2],out,M,N) ;



}
}



// http://www.program99.com/2012/10/bubble-sort-without-pointer.html
// I've been using this before the latest version
void sort(int a[s],int s)
{
    int i,j;
    int temp;
    for(i=1;i<s;i++)
    {
        for(j=0;j<s-i;j++)
        {
            if(a[j]>a[j+1])
            {
                temp=a[j];
                a[j]=a[j+1];
                a[j+1]=temp;
            }
        }
    }
}
//Initializes the Tree with full of 0
void initializeInorderTree(int preInorderTree[M],int M){
    for(int i = 0;i<M;i++) {
        preInorderTree[M] = 0;
        }
    }

int findLastEmptyInorderTreeIndex(int preInorderTree[M],int M){
    for(int i = 0;i<M;i++){
        if(preInorderTree[i]==0) {
            return i;
        }
    }
    return 0;
}

//Initializes the Tree with full of 0
void initializeTree(int arr[M][N],int M,int N){
    for(int i = 0;i<M;i++) {
        for(int b = 0;i<N;i++){
            arr[i][b] = 0;
        }
    }

}

//Finds Last Empty Index
int findLastEmptyIndex(int arr[M][N],int M,int N){
    for(int i = 0;i<M;i++){
        if(arr[i][1]==0) {
            return i;
        }
    }
    return 0;
}

//Sets root value and sets childs to 0
void setRoot(int arr[7][3],int element,int M,int N){
    arr[0][0] = 0; //m
    arr[0][1] = element;
    arr[0][2] = 0; //m
    //arr[0][3] = 0;

}

//Finds the given element index
int findElementIndex(int arr[M][N], int element, int M,int N){
    for(int i = 0;i<M;i++){
        if (arr[i][1] == element) {
            return i;
        }
    }
    return 0;
}

//Checks if left child is empty
int isLeftEmpty(int arr[M][N],int element_index, int M,int N){
    if(arr[element_index][0] == 0) {
        return 1;}
    else{
        return 0;}
}

//Checks if right child is empty
int isRightEmpty(int arr[M][N],int element_index,int M,int N){
    if(arr[element_index][2] == 0) {
        return 1;}
    else{
        return 0;}
}


//Sets the left child and adds an extra root value to list
void setLeft(int arr[M][N], int element_index, int child, int M,int N){
    arr[element_index][0]  = child;
    int lastIndex = findLastEmptyIndex(arr,M,N);

    arr[lastIndex][0] = 0;
    arr[lastIndex][1] = child;
    arr[lastIndex][2] = 0;
    //arr[lastIndex][3] = arr[element_index][3]+1;
}

//Sets the right child and adds an extra root value to list
void setRight(int arr[M][N], int element_index, int child,int M, int N){
    arr[element_index][2]  = child;

    int lastIndex = findLastEmptyIndex(arr,M,N);
    arr[lastIndex][0] = 0;
    arr[lastIndex][1] = child;
    arr[lastIndex][2] = 0;
    //arr[lastIndex][3] = arr[element_index][3]+1; //Modified
}

//Integrates the functions and build the tree in format of {{leftChild,rootValue,rightChild},...} with recursion
void putItCorrect(int arr[M][N], int element_index, int child , int M,int N) {
    if(arr[element_index][1] > child){

        if(isLeftEmpty(arr, element_index,M,N) == 1){
            setLeft(arr, element_index, child,M,N);}
        else{
            putItCorrect(arr, findElementIndex(arr, arr[element_index][0],M,N), child,M,N) ;
        } }
    else if(arr[element_index][1] < child){

        if(isRightEmpty(arr, element_index,M,N) == 1) {
            setRight(arr, element_index, child,M,N); }
        else {
            putItCorrect(arr, findElementIndex(arr, arr[element_index][2],M,N), child,M,N);
        }
    }
}


void process_a_list(int numberList[M],FILE *out,int M){
	clock_t start;
	clock_t end;
	double cpu_time_used;

    // M = size
	start = clock();
	sleep(1);
    int child;
    int element_index = 0; //Modified
    int N = 3; // 3 or 4?
    int potIndex = 0;
    int root = numberList[0];
    int arr[M][N];
    int preorderTree[M];
    initializeInorderTree(preorderTree,M);
    memset(arr, 0, sizeof(arr[0][0]) * M * N); //Modified
    setRoot(arr,root,M,N);
    for (int i=1;i<M;i++){
        element_index = 0;
        child = numberList[i];
        putItCorrect(arr, element_index, child,M,N);   }

    printInorder(arr,preorderTree,root,out,M,N);

    printf("\nBuilding the tree took ");
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC -1;
    fprintf(out, "%s", "\n");
	fprintf(out, "%s","Building the tree took ");
	appendDoubleToFile(out, cpu_time_used);
	fprintf(out, "%s"," seconds.\n");

	fprintf(out, "%s", "--------------------------------------------------------------\n");
    printf("%f",cpu_time_used);
    printf(" seconds.\n");







/*//The function I no longer use
    int coolestRootIndex = 0;
    int howCool = 0;
    for(int i=0;i<M;i++) {
        if(coolestRootIndex <= arr[i][3] ) {
            coolestRootIndex = arr[i][3];   } }
    for(int i=0;i<M;i++) {
        if(coolestRootIndex == arr[i][3] ) {
            howCool =+ 1;   } }
    int coolTree[coolestRootIndex][howCool];
    initializeTree(coolTree,coolestRootIndex,howCool);
    int i;
    int b;
    for(i=0;i<coolestRootIndex+1;i++) {
        int coolTreeModule[howCool];
        int c = 0;
        for(b = 0; b<M ; b++) {
            if (arr[b][3] == i){
                coolTreeModule[c] = arr[b][1];
                c++; } }
        sort(coolTreeModule,c);
        for(int k; k<c;k++){
            coolTree[i][k] = coolTreeModule[k];
        }
        int j;
        for(i=0; i<coolestRootIndex; i++) {
            for(j=0;j<howCool;j++) {
                printf("%d ", coolTree[i][j]);
                if(j==coolestRootIndex){
                    printf("\n");
                }}}  }*/


}
void appendDoubleToFile(FILE *out, double data){
	char str[50];
	sprintf(str, "%lf", data);
	fprintf(out, "%s", str);
}
void appendToFile(FILE *out,int data){

	char str[20];
	sprintf(str, "%d", data);

	fprintf(out, "%s", str);
	fprintf(out, "%s", " ");

	//fprintf(out, "%c", " ");
	//fprintf(pFile2, str);
}


//to count numbers in lines by format {number of ints first line, number of ints second line, number of ints third line}
void howManyNumbers(const char *fileName,int howManyElementInLists[M],int M) {
	//might change file input with a file name and close the file inside to restart fgetc function
	FILE *in = fopen(fileName, "r");

	int counter = 1;
	int lineNumber= M;

	initializeInorderTree(howManyElementInLists,lineNumber);

	int listIndex = 0;
    if (in == NULL) {
        printf("ERROR: File does not exist.");

    }
    char c = (char) fgetc(in);
    if (c == EOF || c == '\n') {
        printf("Error2");
    }

while(c!=EOF) {
	if(c!='\n'){
    do {
        c = (char) fgetc(in);
        if (c == ' ') {
            counter++;
        }

    } while (c != '\n' && c != EOF);
    howManyElementInLists[listIndex]  = counter;
	}
	else{
		listIndex +=1;
		counter = 1;
	}

}
    fclose(in);
    }

//returns the numbers on the flag line by integer list from the text file
void get_numbers(const char *fileName, int howManyIntegers,int flag,int numberList[howManyIntegers]) {
	FILE *in = fopen(fileName, "r");

	initializeInorderTree(numberList,howManyIntegers);
	int line=0;
    if (in == NULL) {
        printf("error");
    }
    char c;


    while(flag != line){
    	c = (char) fgetc(in);
    	    if (c=="\n"){    // if c = \n it increases the line by 1
    	    	line+=1;}
    }
    int strInt;
    for (int i = 0; i < howManyIntegers - 1; i++) {
        fscanf(in, "%d ", &strInt);
        numberList[i] = strInt;
    }
    fscanf(in, "%d\n", &strInt);
    numberList[howManyIntegers - 1] = strInt;
    fclose(in);

}








/*char * readFile(FILE *in){ //not finished
	int howManyNumbersInLines[3] = howManyNumbers(in);
	int lineIndex = 0;

	if (in == NULL){
	        printf("Could not open file ");
	        return 1;
	    }
	for(int i=0;i<2;i++){

	}
	    return 0;
	}
*/
//Counts how many integers in a file by counting spaces
int howManyInt(const char *fileName) {
    FILE *in = fopen(fileName, "r");
    if (in == NULL) {
        printf("ERROR: File does not exist.");
        return 1;
    }
    char c = (char) fgetc(in);
    if (c == EOF || c == '\n') {
        return 0;
    }
    int howManyInt = 1;
    do {
        c = (char) fgetc(in);
        if (c == ' ') {
        	howManyInt++;
        }
    } while (c != '\n' && c != EOF);
    fclose(in);
    return howManyInt;
}


int *returnNumberList(const char *fileName){
	 int intCounter = howManyInt(fileName);
	 int numberList[intCounter];
	 initializeInorderTree(numberList,intCounter);
	 numberListReturns(fileName,numberList,intCounter);
	 return numberList;
}

//Fills the given numberlist with the integers in the given file
void numberListReturns(const char *fileName,int numberList[M],int M) {
    FILE *file = fopen(fileName, "r");
    int integerCount = M;
    if (file == NULL) {
        exit(1);
    }
    int temp;
    for (int i = 0; i < integerCount - 1; i++) {
        fscanf(file, "%d ", &temp);
        numberList[i] = temp;
    }
    fscanf(file, "%d\n", &temp);
    numberList[integerCount - 1] = temp;
    fclose(file);
 }

//initialized process_a_list function
void inputOutput(int numberList[M],FILE *out,int M ){

	//int lineNumber;
	int size_tree;

	size_tree = M;//sizeof numberList / sizeof numberList[0];
	//printf("%d",size_tree);
	process_a_list(numberList,out,size_tree);

}

void printListsForTest(int testList[M],int M){
	printf("list: ");
	for(int i=0;i<M;i++){
		printf("%d",testList[i]);
		printf(" ");

	}
	printf("\n");
}


//reads data from the given file, appends that to a list and uses inputOutpu function
void compile(const char *fileName,FILE *out){
	int listSize = howManyInt(fileName);
	int numberList[listSize];
	numberListReturns(fileName,numberList,listSize);
	//printListsForTest(numberList,listSize);
	inputOutput(numberList,out,listSize );
}
int main()			{

  //  FILE *in = fopen("data.txt","r");



	//char txtFilePath[] = "src/data.txt";
	FILE *out = fopen("src/TreeData.txt", "w");
	compile("src/data1.txt",out);
	compile("src/data2.txt",out);
	compile("src/data3.txt",out);






	fclose(out);

    return 0;
}

