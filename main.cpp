#include <iostream>
#include <array>
#include <cstdlib>
#include <ctime>
// int allocationCount = 0;

// void* operator new(size_t size){
//   allocationCount++;
//   std::cout << "Allocating " << size << " bytes" << std::endl;
//   return malloc(size);
// }
const int WIN_MASK[8] = {
  0b000000111, 0b000111000, 0b111000000, //across
  0b100010001, 0b001010100, //horizontal
  0b100100100, 0b010010010, 0b001001001 //vertical
};

int randomNumber(){
  return std::rand() %9;
}
bool checkWin(const std::array<char, 9>& arr, char player){ //1 = O 2 = X
  unsigned int boardMask = 0;

  for(int i = 0; i < 9; i++){
    if (arr[i] == player)
      boardMask |= (1 << i);
  }
  for(const int win : WIN_MASK){
    if((win & boardMask) == win) return true;
  }
  return false;
}
void printOut(const std::array<char, 9>& arr){
  int i = 0 ;
  for (const char element : arr){
    if(i%3 == 0 && i != 0) std::cout << std::endl;
    std::cout << element << " ";
    i++;
  }
  std::cout << std::endl;
};

void playEnemy(std::array<char, 9>& arr, char play){
  bool played = false;
  while(played == false){
    int r = randomNumber();
    if (arr[r] == '_'){
      arr[r] = play;
      played = true;
    }
  }
}

char match(std::array<char, 9>& arr, char shape, char Eshape){
  bool finish = false;
  int play{}, winner{}, turn{1};
  while(finish != true){
    turn++;
    bool skipTurn = (shape == 'O' && turn == 2);

    if (!skipTurn){
      std::cout << "Select play: (-1 to exit)" << std::endl;
      std::cin >> play;

      if (play ==-1) finish = true;
      if (arr[play-1] != 'X'&& arr[play-1] != 'O')
        arr[play-1] = shape;

      std::cout << "Play:" << std::endl;
      printOut(arr);
    }

    if (turn > 3) finish = checkWin(arr, shape);
    if (finish) return shape;

    playEnemy(arr, Eshape);
    std::cout << "Enemy Play:" << std::endl;
    printOut(arr);    
    if (turn > 3) finish = checkWin(arr, Eshape);
    if (finish) return Eshape;
  }
  return 3;
}

int main(){
  //Select mode
  int shape{};
  char winner = '-';
  std::array<char, 9> arr {'_', '_', '_', '_', '_', '_', '_', '_','_'};
  std::cout << "Select Shape, 1 = O, 2 = X " << std::endl;
  std::cin >> shape;
  std::cout << "Played by counting left to right up down, below table as an example" << std::endl;
  printOut(arr);
  switch(shape){
    case 1:
      winner = match(arr, 'O', 'X'); //user is O
      break;
    case 2:
      winner = match(arr, 'X', 'O'); //user is X
      break;
    default:
      std::cout << "Not an option" << std::endl;
  }
 // std::cout << "Total Allocations: " << allocationCount << std::endl;
  std::cout << "Winner is: " << winner << std::endl;
  return 0;
}
