/*
Courtney Ng
Period 4
*/

#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;
HANDLE color=GetStdHandle(STD_OUTPUT_HANDLE);

//prototyping
/***********************************************************************/
int compare(int a, int b);
void allfalse(bool p[]);
int getrank(int card);
int getsuit(int card);
int count(bool p[]);
int drawfromhand(bool p[]);
void shuffleintoHold(bool p[], bool hand[]);
bool win(bool p[], bool hand[]);
/***********************************************************************/


//var
/***********************************************************************/
string ranks[13] = {"Two", "Three", "Four", 
					"Five", "Six", "Seven", 
					"Eight", "Nine", "Ten", 
					"Jack", "Queen", "King", "Ace"};
					
string suits[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
bool p1hand[52], p2hand[52], p1hold[52], p2hold[52], warhold[52];
/***********************************************************************/


//MAIN
/*************************************************************************************************************************************************/
int main(){
	
		//setup
		/***********************************************************************/
		srand(time(0));
		int round = 0;
		
		allfalse(p1hand); allfalse(p2hand); allfalse(p1hold); allfalse(p2hold); allfalse(warhold);
		
		for(int i = 0; i < 26; i++){
			p1hand[i] = true;
		}
		for(int i = 26; i < 52; i++){
			p2hand[i] = true;
		}
		/***********************************************************************/
			
		/*** intro***/
		cout << "\t\t*******************************************************" << endl;
		cout << "\t\t                          WAR                          " << endl;
		cout << "\t\t              bigger number gets the cards             " << endl;
		cout << "\t\t                 place your bets now                   " << endl;
		cout << "\t\t       whoever has 0 cards loses, so don't lose        " << endl;
		cout << "\t\t*******************************************************" << endl << endl;
		/*** intro***/
		
		
		do{
			SetConsoleTextAttribute(color, 11); //light blue
			cout << "\t================================ {Round " << ++round << "} ================================" << endl << endl;
			SetConsoleTextAttribute(color, 7); //white
			shuffleintoHold(p1hand, p1hold);
			shuffleintoHold(p2hand, p2hold);
			int a = drawfromhand(p1hand);
			int b = drawfromhand(p2hand);
			
			cout << endl;
			SetConsoleTextAttribute(color, 10); //light green
			cout << "Player 1: " <<  ranks[getrank(a)] << " of " << suits[getsuit(a)] << " (" << a << ")" << endl; 
			SetConsoleTextAttribute(color, 13); //magenta
			cout << "Player 2: " <<  ranks[getrank(b)] << " of " << suits[getsuit(b)] << " (" << b << ")" << endl;
			SetConsoleTextAttribute(color, 7); //white
			//cout << "\t=============================================================================" << endl;
			
			
			//Simple comparison
			/***********************************************************************/
			if(compare(getrank(a), getrank(b)) == 1){
				SetConsoleTextAttribute(color, 14); //light green
				cout << "\n--== Player 1 won ==--" << endl;
				p1hold[a] = true; p1hold[b] = true; p1hand[a] = false;
				p2hand[b] = false;
				SetConsoleTextAttribute(color, 7);
			}
			else if(compare(getrank(a), getrank(b)) == 2){
				SetConsoleTextAttribute(color, 14);
				cout << "\n--== Player 2 won ==--" << endl;
				p2hold[a] = true; p2hold[b] = true; p2hand[b] = false;
				p1hand[a] = false;
				
				SetConsoleTextAttribute(color, 7);
			}
			/***********************************************************************/
			
			
			//war scenario
			/***********************************************************************/
			else{
				bool war = true;
				do{
					SetConsoleTextAttribute(color, 12);
					cout << "\nThe same rank was drawn.." << endl;
				    cout << endl << "--== War ==--" << endl << endl;
				    warhold[a] = true; warhold[b] = true;
				    p1hand[a] = false; p2hand[b] = false;		    
				    
				    if(count(p1hand) + count(p1hold) < 4 && war == true){
				    	SetConsoleTextAttribute(color, 4);
				    	cout << "Player 1 doesn't have enough cards for war" << endl; 
				    	for(int i = 0; i < 52; i++){
				    		if(p1hand[i] == true || p1hold[i] == true || warhold[i] == true){
								p2hold[i] = true; 
								p1hand[i] = false; p1hold[i] = false;
								warhold[i] = false;
								SetConsoleTextAttribute(color, 7);
				    		}
				    	}
				    	war = false;
				    }
				    else{
				    	if(war == true){ 
				    		cout << endl;
				    		SetConsoleTextAttribute(color, 10);
							cout << "Player 1 antes: " << endl;	
				    		for(int i = 0; i < 3; i++){	
								shuffleintoHold(p1hand, p1hold);   					
				    		    a = drawfromhand(p1hand);
				    		    cout << ranks[getrank(a)] << " of " << suits[getsuit(a)] << " (" << a << ")" << endl;
				    		    warhold[a] = true;
				    		    p1hand[a] = false;
				    		}
			    		}
			    		SetConsoleTextAttribute(color, 7);
		    		}
		    		cout << endl;
		    		if(count(p2hand) + count(p2hold) < 4 && war == true){
		    			SetConsoleTextAttribute(color, 4);
				    	cout << "Player 2 doesn't have enough cards for war" << endl;
				    	for(int i = 0; i < 52; i++){
				    		if(p2hand[i] == true || p2hold[i] == true || warhold[i] == true){
								p1hold[i] = true;
								p2hand[i] = false; p2hold[i] = false;
								warhold[i] = false;
								SetConsoleTextAttribute(color, 7);
				    		}
				    	}
				    	war = false;
				    }
		    		else{
		    			if(war == true){
		    				SetConsoleTextAttribute(color, 13);
							cout << "Player 2 antes: " << endl;	
				    		for(int i = 0; i < 3; i++){
				    			shuffleintoHold(p2hand, p2hold);
				    		    b = drawfromhand(p2hand);
				    		    cout << ranks[getrank(b)] << " of " << suits[getsuit(b)] << " (" << b << ")" << endl;
				    		    warhold[b] = true;
				    		    p2hand[b] = false;
				    		}
			    		}
			    		SetConsoleTextAttribute(color, 7);
			    	}
			        
					if(war == true){		
						shuffleintoHold(p1hand, p1hold);
						shuffleintoHold(p2hand, p2hold);
			        	a = drawfromhand(p1hand);
			        	b = drawfromhand(p2hand);
			        	
			        	cout << endl;
			        	SetConsoleTextAttribute(color, 10);
			        	cout << "Player 1: " <<  ranks[getrank(a)] << " of " << suits[getsuit(a)] << " (" << a << ")" << endl; 
			        	SetConsoleTextAttribute(color, 13);
			        	cout << "Player 2: " <<  ranks[getrank(b)] << " of " << suits[getsuit(b)] << " (" << b << ")" << endl;
			        	SetConsoleTextAttribute(color, 7);
			        	
			        	if(compare(getrank(a), getrank(b)) == 1){
			        		SetConsoleTextAttribute(color, 4);
			        		cout << "\n--== Player 1 won the war ==--" << endl;
			        		p1hold[a] = true; p1hold[b] = true; p1hand[a] = false;
			        		p2hand[b] = false;
			        		for(int i = 0; i < 52; i++){
			        		    if(warhold[i] == true)
			        		        p1hold[i] = true;
			        		}
			        		allfalse(warhold);
			        		war = false;
			        		SetConsoleTextAttribute(color, 7);
			        	}
			        	else if(compare(getrank(a), getrank(b)) == 2){
			        		SetConsoleTextAttribute(color, 4);
			        		cout << "\n--== Player 2 won the war ==--" << endl;
			        		p2hold[a] = true; p2hold[b] = true; p2hand[b] = false;
			        		p1hand[a] = false;
			        		
			        		for(int i = 0; i < 52; i++){
			        		    if(warhold[i] == true)
			        		        p2hold[i] = true;
			        		}
			        		allfalse(warhold);
			        		war = false;
			        		SetConsoleTextAttribute(color, 7);
			        	}
			        }
			    	SetConsoleTextAttribute(color, 7); //white
				}while(war == true);
			}
			/***********************************************************************/
			
			
			//figures
			/***********************************************************************/
			cout << endl;
			SetConsoleTextAttribute(color, 10);
			cout << "Player 1's hand: " << count(p1hand) << "\t" << "Player 1's hold: " << count(p1hold) << "\t" << "Player 1's total: " << count(p1hand) + count(p1hold) << endl;
			SetConsoleTextAttribute(color, 13);
			cout << "Player 2's hand: " << count(p2hand) << "\t" << "Player 2's hold: " << count(p2hold) << "\t" << "Player 2's total: " << count(p2hand) + count(p2hold) << endl;
			cout << endl;
			SetConsoleTextAttribute(color, 7);
			/***********************************************************************/
			
			
		}while(!win(p1hand, p1hold) && !win(p2hand, p2hold));
		
		//win scenario
		/***********************************************************************/
		if(win(p1hand, p1hold)){
			SetConsoleTextAttribute(color, 14);
			cout << "Player 1 won" << endl << endl;
			SetConsoleTextAttribute(color, 7);
			cout << "\t=============================================================================" << endl;
		}
		else{
			SetConsoleTextAttribute(color, 14);
			cout << "Player 2 won" << endl << endl;
			SetConsoleTextAttribute(color, 7);
			cout << "\t=============================================================================" << endl;
		}
		/***********************************************************************/
		SetConsoleTextAttribute(color, 11);
		cout << "Number of rounds played: " << round << endl;
	}

/*************************************************************************************************************************************************/
//MAIN


//prototyping
/************************************************************************************************************/
/*compares a to b
 *returns 1 if a is greater
 *returns 2 if b is greater
 *returns 0 if it is a tie
*/
int compare(int a, int b){
	if(a > b)
		return 1;
	else if(a < b)
		return 2;
	else
		return 0;
}
/************************************************************************************************************/


/************************************************************************************************************/
//sets all values to false
void allfalse(bool p[]){
	for(int i = 0; i < 52; i++){
		p[i] = false;
	}
}
/************************************************************************************************************/


/************************************************************************************************************/
//gets the rank of the card
int getrank(int card){
	return card % 13;
}
/************************************************************************************************************/


/************************************************************************************************************/
//gets the suit of the card
int getsuit(int card){
	return card / 13;
}
/************************************************************************************************************/


/************************************************************************************************************/
//count true, return # of true val
int count(bool p[]){
	int count = 0;
	for(int i = 0; i < 52; i++){
		if(p[i] == true){
			count++;
		}
	}
	return count;
}
/************************************************************************************************************/


/************************************************************************************************************/
//draw random card if val is true
int drawfromhand(bool p[]){
	int card;
	do{
		card = rand() % 52;
	}while(p[card] == false);
	return card;
}
/************************************************************************************************************/


/************************************************************************************************************/
//check # of cards in hand\
if none, puts card into hand
void shuffleintoHold(bool p[], bool hand[]){
	if(count(p) == 0){
		for(int i = 0; i < 52; i++){
			if(hand[i] == true){
				p[i] = true;
			}
		}
		allfalse(hand);
	}
}
/************************************************************************************************************/


/************************************************************************************************************/
//check if player has all cards
bool win(bool p[], bool hand[]){
	int card = 0;
	for(int i = 0; i < 52; i++){
		if(p[i] == true || hand[i] == true)
			card++;
	}
	if(card == 52)
		return true;
	else
		return false;
}
/************************************************************************************************************/
