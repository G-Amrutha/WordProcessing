/*

Amrutha Ginkala
816117625
amrutha_ginkala@yahoo.com
COMP 1602 Assignment 2

*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <string.h>

using namespace std;

/*Concept of running game:

AlphaKey:
 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|
 a| b| c| d| e| f| g| h| i| j| k| l| m| n| o| p| q| r| s| t| u| v| w| x| y| z|---Just for imagining purposes
-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|---These are replaced only on the first instance of the character index position

GameWord: GalaXy -->(tolower)--> galaxy
(int)g-96= 7	 -->(index position)--> 0
(int)a-96= 1	 -->(index position)--> 1
(int)l-96= 12	 -->(index position)--> 2
(int)a-96= 1	 -->(index position)--> 3---'a' appeared once before so it was not changed in the AlphaKey
(int)x-96= 24	 -->(index position)--> 4
(int)y-96= 25	 -->(index position)--> 5

 1| 2| 3| 4| 5| 6| 7| 8| 9|10|11|12|13|14|15|16|17|18|19|20|21|22|23|24|25|26|
 a| b| c| d| e| f| g| h| i| j| k| l| m| n| o| p| q| r| s| t| u| v| w| x| y| z| 
 1|-1|-1|-1|-1|-1| 0|-1|-1|-1|-1| 2|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1|-1| 4| 5|-1|---character first instances after replacing some of the -1

In order to prevent looking for a particular character in word from start to end. 
I thought of a way to have all the same chars map each in an array so that they can be easily switched from 
being invisible to visble 
Next_Similar_GameWord_Character(NSGWC)
 0| 1| 2| 3| 4| 5|---Index 
-1|-1|-1|-1|-1|-1|---Maps the index of the next similar character eg g[a]l[a]xy 'a' appears at position 1 and 3 

Next_Similar_GameWord_Character(NSGWC) of "galaxy"
 0| 1| 2| 3| 4| 5|---Index 
-1| 3|-1|-1|-1|-1|---(-1) intidcates that there is no next similar character


*/


int BinarySearch(char[][25],int, char*);
void Insertion(char [][25], char*, int, int);
char* NewGame(int,char[][25]);

void GameProgress (int lives,int WordLength, bool Visible[], char GameWord[]){
	int i=0;
	
	cout<<"\nLIVES: ";
	for(int x=1;x<=lives;x++){
		if(x%2==0)
			cout<<"3 ";
		else
			cout<<"<";	
	}
	cout<<endl;
	
	if(lives==0){//Left Leg
		cout<<"___________"<<endl
			<<"|	 |"<<endl
			<<"|	 O"<<endl
			<<"|	 |"<<endl
			<<"|	\\ /"<<endl	
			<<"|	 |"<<endl
			<<"|	/ \\"	<<endl<<"HANGED!!!...GAME OVER"<<endl;
			cout<<"Word:"<<GameWord<<endl<<"Good Game\n\n";
			return;
	}
	
	//cout<<GameWord<<endl;//see game word to show that the letters and '*' mirror each other 
	
	for(i=0;i<WordLength;i++){
		if(!Visible[i])
			cout<<"* ";
		else
			cout<<GameWord[i]<<" ";
	}
	cout<<endl;
	
}

void GameMenu(int ListSize,char WordList[][25]){
	char PlayerName[25];
	/* initialize random seed: */
  	srand (time(NULL));//for consistent random word to be chosen 
	int lives=12,i,AlphaKey[27],pos;
	char GameWord[25], guess='-';
	int WordLength=0,win,quit,completed=0;
	cout<<"**********************************WELLCOME TO HANGMAN**********************************"<<endl
		<<"A word consisting of a number of letters is choosen randomly and you\nthe player, will have 12 chances to solve the word by entering one character at a time.\n"
		<<"A correct entry will cause the letter to become visible while\nan incorrect entry costs one of your chances."<<endl
		<<"The 12 chances represent\nLives: <3 <3 <3 <3 <3 <3 \n'<' -this symbol only indicates 1 life \n'3' -this symbol only indicates 1 life \n'<3' -this symbol indicates 2 lives"<<endl
		<<"If you wish to continue please push 1 to start game or 0 to quit"<<endl;
		cin>>quit;
		while(quit!=0&&quit!=1){
			cout<<"Error: Bad entry please try again"<<endl
				<<"If you wish to continue please push 1 to start game or 0 to quit"<<endl;
			cin>>quit;
		}
		if(quit==0)
			return;
		else{
			system("cls");//Clear the screen
			while(lives>=0 && quit!=0){//Lets play .........
				win=0;
				strcpy(GameWord,NewGame(ListSize,WordList));//Loads the random new GameWord
				WordLength=0;
				while(GameWord[WordLength]!='\0')
					WordLength++;
				
				for(i=1;i<=26;i++){//Resets the AlphaKey
					AlphaKey[i]=-1;
				}	
				int NSGWC[WordLength];
				for(i=0;i<WordLength;i++){//Resets the NSGWC 
					NSGWC[i]=-1;
				}
				
				i=0;
				int curr;
				while(GameWord[i]){//loads in each character of the GameWord into the AlphaKey and NSGWC
					GameWord[i]=tolower(GameWord[i]);//ensures that the word is in common letters
					pos=(int)GameWord[i]-96;//cast it into integer
					if(AlphaKey[pos]==-1)
						AlphaKey[pos]=i;
						
					pos=i;//Finished using above recycling the variable here
					curr=i+1;//starts at position 1 aka the 2nd character of the GameWord
						
					while(GameWord[curr]){//---Nested loop traverses through the rest of the word seeking matching chars
						GameWord[curr]=tolower(GameWord[curr]);//Strangly enough actualy had to do this for some reason some of the characters were still capitalized 
						//cout<<GameWord[curr]<<" vs "<<GameWord[i]<<endl;
						if(GameWord[curr]==GameWord[i]){
							NSGWC[pos]=curr;//Mapping system
							pos=curr;
						}
						curr++;
					}
					
					i++;
				}

				/*for(int x=0;x<WordLength;x++){//Double check the NSGWC
					cout<<NSGWC[x]<<" ";
				}*/
				
				bool Visible[WordLength];//Array which handles which characters can be seen on screen
				for(i=0;i<WordLength;i++)
					Visible[i]=false;//Setting all letters of that word to be invisible at start of game 
						
				while(lives>0 && win!=1){//Guts of the game occurs here
					GameProgress(lives,WordLength,Visible,GameWord);
					cout<<"Please enter your single letter guess or 0 to quit: ";
					cin>>guess;
					
					if(guess=='0'){
						quit=0;
						break;
					}
					
					guess=tolower(guess);
					while((int)guess<97||(int)guess>122){
						cout<<"ERROR:\nPlease enter your single letter guess or 0 to quit: ";
						cin>>guess;
					}
					pos=(int)guess-96;
					system("cls");
					if(AlphaKey[pos]==-1){
						lives--;
						cout<<"Thats incorrect sorry try again!!"<<endl;
						
					}else{
						curr=AlphaKey[pos];
						if(Visible[curr]!=true){
							Visible[curr]=true;
							cout<<"Thats correct good guess!!"<<endl;
						}
						else{
							lives--;
							cout<<"PAY ATTENTION!! that letter is already visible"<<endl;
						}
						while(NSGWC[curr]!=-1){//cycle through the NSGWC for this same character
							Visible[NSGWC[curr]]=true;
							curr=NSGWC[curr];
						}
						
					}
			
					pos=0;
					for(curr=0;curr<WordLength;curr++){//check to see if solved
						if(Visible[curr]==true)
							pos++;
					}
					if(pos==WordLength){
						win=1;
						completed++;
						cout<<"Congratulations on figuring out:\n"<<GameWord;
						
						cout<<endl;
					}	
				}
				if(lives==0){//Player to choose if GameOver or restart
					system("cls");
					GameProgress(lives,WordLength,Visible,GameWord);
					cout<<"GAMEOVER...\nYour score is: "<<completed
						<<"\nPlease press 1 to restart or 0 to quit game"<<endl;
					cin>>quit;
					while(quit!=0&&quit!=1){
						cout<<"Error: Bad entry please try again"<<endl
							<<"Please press 1 to restart or 0 to quit game"<<endl;
						cin>>quit;
					}
					if(quit==0)
						return;
					else{
						system("cls");
						completed=0;
						lives=12;
					}		
				}

			}
			
		}
					
}

char* NewGame(int Size, char WordList[][25]){//Collects a randomly choosen word for the game
	int random;
	srand (time(NULL));
	random=rand() % Size +1;
	return WordList[random];
}

int main(){
	ifstream inFile ("C:\\comp1602\\asg2\\input.txt");
	char sample[25];
	char WordList[101][25];
	int counter=0,pos;
	
	if(inFile.is_open()){
		inFile>>sample;
		while(strcmpi(sample,"@@@@@")&&counter<101){
			pos=BinarySearch(WordList,counter,sample);
			if(pos!=-1){
				Insertion(WordList,sample,pos,counter);
				counter++;
			}
			inFile>>sample;
		}
		
		/*for(int x=1;x<=counter;x++){//**********************************************************Check to see the alphabetical order of word array no changes are done to capitalized letters 
			cout<<WordList[x]<<endl;
		}*/
		
		GameMenu(counter,WordList);
		cout<<"Good Game Thanks for playing goodbye"<<endl;
	}else
		cout<<"Unable to locate input.txt";
	
	
	return 0;
	
}

int BinarySearch(char WordList[][25],int counter, char* sample){//combined the sorting with the binary search a sort-of Binary insertion Sort
	int pos=-1;//-1 indicates match has been found in WordList
	int first=1, last=counter;
	int  mid= (first+last)/2;
		while(first<=last){
			if(strcmpi(WordList[mid],sample)<0){//acending
				first=mid+1;
			}else if(strcmpi(WordList[mid],sample)==0)//found similar words
				return pos;
			else
				last=mid-1;
			mid=(first+last)/2;
		}
	return mid+1;//word isnt in the WordList therefore add at this index
}

void Insertion(char Wordlist[][25], char* sample, int pos, int counter){
	if(counter<1){//first word to be added
		strcpy(Wordlist[pos],sample);
	}else{
		counter++;//creates the idea of space for new word;
		for(int i=counter-1;i>=pos;i--){
			strcpy(Wordlist[i+1],Wordlist[i]);//shuffel all other words down
		}
		strcpy(Wordlist[pos],sample);
	}
	
	
		
}


