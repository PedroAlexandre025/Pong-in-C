#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

#define h 20 //height
#define l 50 //largure
#define initialBallX l/2
#define initialBallY h/2


int PosBarPlayer1 = 8;
int PosBarPlayer2 = 8;

typedef struct{
    int points;
}Player;

typedef struct{
    int ballPosX;
    int ballPosY;
    int ballDirectionX;
    int ballDirectionY;

}Ball;

void createPlayer(Player *player){
    player->points = 0;
   
}

void createBall(Ball *ball){
    ball->ballPosX = initialBallX;
    ball->ballPosY = initialBallY;
    ball->ballDirectionX = 1;
    ball->ballDirectionY = 1;
}

void setCampEdges(char camp[h][l]){ //set the edges of the camp with '*'
    
    for (int i = 0; i < h; i++)
    {
        camp[i][0] = '*';
        camp[i][l-1]= '*';
       
    }

    for (int j = 0; j < l; j++)
    {
        camp[0][j]= '*';
        camp[h-1][j] = '*';
        
    }

}

void movimentBarPlayer1(char camp[h][l], int actualPositrionbar1, int beforeValue){//set the position of the bars in the camp, after the player press 1 the keybind to move the bar

    for (int i = 0; i < 3; i++)
    {
        camp[i+beforeValue][2] = ' ';
       
    }
    for (int i = 0; i < 3; i++)
    {
        camp[i+actualPositrionbar1][2] = '*';
        
    }
}
void movimentBarPlayer2(char camp[h][l], int actualPositrionbar2, int beforeValue){//set the position of the bars in the camp, after the player 2 press the keybind to move the bar

    for (int i = 0; i < 3; i++)
    {
        camp[i+beforeValue][l-3] = ' ';

    }
    for (int i = 0; i < 3; i++)
    {
        camp[i+actualPositrionbar2][l-3] = '*';
    }
    
}

void createCamp(char camp[h][l]){
    
    setCampEdges(camp);//edges

    for (int i = 0; i < 3; i++)
    {
        camp[i+PosBarPlayer1][2] = '*';
    }                                       //bars                  
    
     for (int i = 0; i < 3; i++)
    {
        camp[i+PosBarPlayer2][l-3] = '*';

    }

    camp[initialBallY][initialBallX] = 'O';//ball


  
}   



void pressingKeybind(char* keybind, char camp[h][l]){//function that will be called when the player press a keybind, and will move the bar of the player accordingly
    switch (*keybind)
    {
        
        case 'w':
            if(PosBarPlayer1 > 1){//if the bar of player 1 is not at the  top of the camp, move it up
                --PosBarPlayer1;
                movimentBarPlayer1(camp, PosBarPlayer1, PosBarPlayer1+1);
            }

        break;
        case 's':
            if(PosBarPlayer1 < h-4){//  if the bar of player 1 is not at the bottom of the camp, move it down
                ++PosBarPlayer1;
                movimentBarPlayer1(camp, PosBarPlayer1, PosBarPlayer1-1);
            }
        
        break;

        case '8':
            if(PosBarPlayer2 >1){//if the bar of player 2 is not at the bottom of the camp, move it down
                --PosBarPlayer2;
                movimentBarPlayer2(camp, PosBarPlayer2, PosBarPlayer2+1);
            }
        break;
        case '2':
            if(PosBarPlayer2 <h-4){//if the bar of player 2 is not at the top of the camp, move it up
                ++PosBarPlayer2;
                movimentBarPlayer2(camp, PosBarPlayer2, PosBarPlayer2-1);
            }
        break;
        default:
            break;
            
    }

}
void noEnter(){//function that will disable the enter key, so the player can press the keybind without having to press enter
    struct termios novo;

    tcgetattr(STDIN_FILENO, &novo);

    novo.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSANOW, &novo);

    fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);

}

void printCamp(char camp[h][l]){//function that will print the camp in the console
    for (int i = 0; i < h; i++)
    {
        for (int j = 0; j < l; j++)
        {
            printf("%c ",camp[i][j]);
        }
        printf("\n");
    }
    
}
void movimentBall(char camp[h][l], Ball *ball, Player* p1, Player* p2 ){//function that will move the ball in the camp, and will check if the ball hit the bar or the wall
    
    int beforeX = ball->ballPosX;
    int beforeY = ball->ballPosY;

    ball->ballPosX += ball->ballDirectionX;
    ball->ballPosY += ball->ballDirectionY;
    
    if (ball->ballPosX == 0)
    {
        ball->ballPosX = initialBallX;
        ball->ballPosY = initialBallY;
        p2->points+=1;
        ball->ballDirectionX *= -1;
        
    
    }else if(ball->ballPosX == l-1){
        ball->ballPosX = initialBallX;
        ball->ballPosY = initialBallY;
        p1->points+=1;
        ball->ballDirectionX *= -1;
        
    }   
    
   
    
    if(ball->ballPosY == 0 || ball->ballPosY == h-1){//if the ball hit the wall, change the direction of the ball
        ball->ballDirectionY *= -1;
    
    }


    for (int i = 0; i < 3; i++)//verify the three positions of bars
    {
        int counterP1 = PosBarPlayer1 +i;
        int counterP2 = PosBarPlayer2 +i;
        if ((ball->ballPosX == 2 && ball->ballPosY == counterP1)|| ball->ballPosX == 47  && ball->ballPosY == counterP2)
        {
            ball->ballDirectionX *= -1;
            break;
        }
    }
    for (int i = 0; i < 3; i++)
    {   int counterP1 = PosBarPlayer1+i;
        int counterP2 = PosBarPlayer2+i;
        if ((beforeY == counterP1 && beforeX == 2)||(beforeY == counterP2 && beforeX == 47))
        {
            camp[beforeY][beforeX] = '*';
            break;
        }
        
    }
    
    
    
    if ((beforeX == 49 || beforeX == 0) ||( beforeY == 19 || beforeY == 0)) //switch char in icon
    {
        camp[beforeY][beforeX] = '*';
    }else{
        camp[beforeY][beforeX] = ' ';
    }
        
    
    
    camp[ball->ballPosY][ball->ballPosX] = 'O'; 
    usleep(50000);
    //ball switch position
    
}

void clearScreen(){//function that will clear the console screen
    #if defined(_WIN32)|| defined(_WIN64)
        system("cls");

    #else
        system("clear");
    #endif
}


int main(){

    Ball ball;
    createBall(&ball);

    char camp[h][l] = {};
    memset(camp, ' ', sizeof(camp));

    char keybind;

    Player player1, player2;
    createPlayer(&player1);
    createPlayer(&player2);

    createCamp(camp);
    printCamp(camp);
    
    noEnter();

    while((player1.points < 10 && player2.points < 10)){//while the player 1 and player 2 points are less than 10, the game will continue, and if the player press 0, the game will end
        
        keybind = getchar();

        pressingKeybind(&keybind, camp);
          
        movimentBall(camp, &ball, &player1, &player2);

        clearScreen();

        printCamp(camp);

        printf("\n\n\n  Player 1: %d                                                                                 Player 2: %d\n", player1.points, player2.points);


    }
    return 0;
}