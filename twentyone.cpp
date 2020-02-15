#include <iostream>
#include <cstdlib>

using namespace std;

/* Prototypes */
void shuffle(int cards[]);
void printCard(int id);
int cardValue(int id);
void printHand(int hand[], int numCards);
int getBestScore(int hand[], int numCards);

const int NUM_CARDS = 52;

/**
 * Global arrays to be used as look-up tables, if desired.
 * It is up to you if and how you want to use these 
 */
const char suit[4] = {'H','S','D','C'}; // didn't use
const char* type[13] = 
  {"2","3","4","5","6","7",
   "8","9","10","J","Q","K","A"};
const int value[13] = {2,3,4,5,6,7,8,9,10,10,10,10,11};

/**
 * Should permute the deck of cards, effectively shuffling it.
 * You must use the Fisher-Yates / Durstenfeld shuffle algorithm
 *  described in the assignment writeup.
 */
void shuffle(int cards[])
{
  // use algorithm 
  for (int i = 51; i>0; i--) {
      int temp; 
      int j = rand()%(i+1); 
      temp = cards[i];
      cards[i] = cards[j];
      cards[j] = temp; 

}
}

/**
 * Prints the card in a "pretty" format:   "type-suit"
 *  Examples:  K-C  (King of clubs), 2-H (2 of hearts)
 *  Valid Types are: 2,3,4,5,6,7,8,9,10,J,Q,K,A
 *  Valid Suits are: H, D, C, S
 */
void printCard(int id)
{
  // id ranges from 0 to 51, corresponds to pg.3 
    if (id >= 0 && id <= 12) {
         cout << type[id%13] << "-" << "H"; 
    }
    else if (id >= 13 && id <= 25) {
        cout << type[id%13] << "-" << "S"; 
    }
    else if (id >= 26 && id <= 38) {
        cout << type[id%13] << "-" << "D"; 
    }
    else if (id >= 39 && id <= 51) {
        cout << type[id%13] << "-" << "C"; 
    }
    
}

/**
 * Returns the numeric value of the card.
 *  Should return 11 for an ACE and can then
 *  be adjusted externally based on the sum of the score.
 */
int cardValue(int id) //use of value array 
{
    int num = id%13; 
    return value[num]; 
}

/**
 * Should print out each card in the hand separated by a space and
 * then print a newline at the end.  
 * Should use printCard() to print out each card.
 */
void printHand(int hand[], int numCards)
{
    for (int i = 0; i<numCards; i++){
        printCard(hand[i]);
        cout << " "; 
    }
    cout << endl;
}

/**
 * Should return the total score of the provided hand.  
 * ACES should be treated as 11s to make the highest possible hand
 *  and only being reduced to 1s as needed to avoid busting.
 */
int getBestScore(int hand[], int numCards) //get score 
{
  int sum = 0;
  
  int numofaces; 
  for (int i = 0; i<numCards; i++) {
     if (hand[i]%13 != 12) 
         sum += value[hand[i]%13]; 
     if (hand[i]%13 == 12 && sum>=11) {
         sum++; 
         numofaces++;
         
     }
     if (hand[i]%13 == 12 && sum<11) {
         sum += 11; 
         numofaces++; 
     }
  }
  if (sum > 21 && numofaces) { // aces involve
      sum = 0; 
      for (int j = 0; j<numCards; j++) {
          if (hand[j]%13 == 12) {
              sum++;
          }
          else {
              sum += value[hand[j]%13]; 
          }
      }
  }
    
      
  
     
  return sum; 
}

/**
 * Main program logic for the game of 21
 */
int main(int argc, char* argv[])
{


  int cards[52];
  int dhand[9];
  int phand[9];
 -----------------------------------

   bool done = false;  
  
  while (!done) { 
  char decision; 
  int dhandsize = 2; 
  int phandsize = 2; 
      
   
      
      for(int i=0; i<NUM_CARDS;i++){
  		cards[i]=i;
  	  } 
      shuffle(cards); 
      
      phand[0] = cards[0];                    // initialization
      dhand[0] = cards[1];
      phand[1] = cards[2];
      dhand[1] = cards[3]; 
      
      cout << "Dealer:  ? "; 
  
      printCard(dhand[1]);
         
      cout<<endl;
      cout<< "Player:  "; 
      printHand(phand, phandsize); //
       
      
      
      while (getBestScore(phand, phandsize) < 21) { //hit or stay
          cout << "Type 'h' to hit or 's' to stay: "<<endl; 
          cin>>decision; 
          if (decision =='h') { // hit
              phand[phandsize] = cards[phandsize+2]; 
              phandsize++; 
              cout << "Player: ";
              printHand(phand, phandsize);          
          }
          else //stay
             break;   
      }
     
      if (getBestScore(phand, phandsize) > 21) { //bust

          
          cout<<"Player busts"<< endl; 
          cout<<"Lose "<<getBestScore(phand, phandsize)
              << " "<< getBestScore(dhand, dhandsize)<< endl; 
      }
      
      if (getBestScore(phand, phandsize) <= 21) {
          while (getBestScore(dhand, dhandsize) < 17) {
              dhand[dhandsize] = cards[phandsize+dhandsize]; 
              dhandsize++; 
          }
          cout << "Dealer: ";
          printHand(dhand, dhandsize); 
          
          
          if (getBestScore(dhand, dhandsize) > 21) {
             // cout<< "Dealer: ";
              //printHand(dhand, dhandsize); 
              cout<<"Dealer busts" <<endl;
              cout<<"Win "<<getBestScore(phand, phandsize)
                  <<" "<<getBestScore(dhand, dhandsize); 
          }
              
          else {
              if (getBestScore(phand, phandsize) 
                  < getBestScore(dhand, dhandsize)) { //lost
                  //cout<<"Dealer: ";
                 // printHand(dhand, dhandsize); 
                  cout<<"Lose "<<getBestScore(phand, phandsize)<< 
                      " "<<getBestScore(dhand, dhandsize)<<endl;
                  
              }
              else if(getBestScore(phand, phandsize) == 
                      getBestScore(dhand, dhandsize)) { // tie
                 // cout<<"Dealer: ";
                 // printHand(dhand, dhandsize); 
                  cout<<"Tie "<<getBestScore(phand, phandsize)
                      << " "<<getBestScore(dhand, dhandsize)<<endl;
              }
              else {
                 // cout<<"Dealer: ";
                 // printHand(dhand, dhandsize);
                  cout<<"Win "<<getBestScore(phand, phandsize) // won
                      << " "<<getBestScore(dhand, dhandsize)<<endl;
              }
              
              
          }
      }
          
      cout<<endl;
      cout<<"Play again?"<<" "<<"[y/n]"<<endl; 
      cin >> decision; 
      
      if (decision == 'y') { // play again
          done = false;
      }
      else {
          done = true;
          break; 
      }
     
    
  }

  return 0;
}
