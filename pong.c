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
#define PaddleTop 8

typedef enum{
    falso, truee
}boolean;


typedef struct{
    int PaddleY;
    int PaddleX; //
    int tam;
}Paddle;

typedef struct{
    int points;
    Paddle bar;
}Player;

typedef struct{
    int ballPosX;
    int ballPosY;
    int ballDirectionX;
    int ballDirectionY;
    boolean moving;
    

}Ball;

void createPlayer1(Player *player){
    player->points = 0;
    player->bar.PaddleX = 3;
    player->bar.PaddleY = 8;
    player->bar.tam = 3;
}

void createPlayer2(Player *player){
    player->points = 0;
    player->bar.PaddleX = l-4;
    player->bar.PaddleY = 8;
    player->bar.tam = 3;
}

void createBall(Ball *ball){
    ball->ballPosX = initialBallX;
    ball->ballPosY = initialBallY;
    ball->ballDirectionX = 1;
    ball->ballDirectionY = 1;
    ball->moving = falso;
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


void createCamp(char camp[h][l], Player *p1, Player *p2, Ball *ball){
    
    setCampEdges(camp);//edges

    for (int i = 0; i < p1->bar.tam; i++)
    {
        camp[i+p1->bar.PaddleY][p1->bar.PaddleX] = '*';
    }                                       //bars                  
    
     for (int i = 0; i < p2->bar.tam; i++)
    {
        camp[i+p2->bar.PaddleY][p2->bar.PaddleX] = '*';

    }

    camp[ball->ballPosY][ball->ballPosX] = 'O';//ball

}   

void pressingKeybind(char* keybind, Player *p1, Player *p2, Ball *ball){//function that will be called when the player press a keybind, and will move the bar of the player accordingly

    *keybind = getchar();
    switch (*keybind)
    {
        
        case 'w':
            if(p1->bar.PaddleY > 1){//if the bar of player 1 is not at the  top of the camp, move it up
                --p1->bar.PaddleY;
                ball->moving = truee;
                
            }

        break;
        case 's':
            if(p1->bar.PaddleY < h-4){//  if the bar of player 1 is not at the bottom of the camp, move it down
                ++p1->bar.PaddleY;
                ball->moving = truee;
              
            }       
        break;

        case '8':
            if(p2->bar.PaddleY>1){//if the bar of player 2 is not at the bottom of the camp, move it up
                --p2->bar.PaddleY;
                ball->moving = truee;
                
            }
        break;
        case '2':
            if(p2->bar.PaddleY <h-4){//if the bar of player 2 is not at the top of the camp, move it down
                ++p2->bar.PaddleY;
                ball->moving = truee;
               
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
void movimentBall( Ball *ball, Player* p1, Player* p2 ){//function that will move the ball in the camp, and will check if the ball hit the bar or the wall
    
    ball->ballPosX += ball->ballDirectionX;
    ball->ballPosY += ball->ballDirectionY;
    
    if (ball->ballPosX == 1)//if the ball hit the left wall, reset the ball position and add a point to player 2
    {
        ball->ballPosX = initialBallX; 
        ball->ballPosY = initialBallY;
        p2->points+=1;
        ball->ballDirectionX *= -1;
        ball->moving = falso;
        
    }else if(ball->ballPosX == l-2){ //if the ball hit the right wall, reset the ball position and add a point to player 1
        ball->ballPosX = initialBallX;
        ball->ballPosY = initialBallY;
        p1->points+=1;
        ball->ballDirectionX *= -1;
        ball->moving = falso;
        
    }   
    
    if(ball->ballPosY == 1 || ball->ballPosY == h-2){//if the ball hit the wall, change the direction of the ball
        ball->ballDirectionY *= -1;
    
    }

    for (int i = 0; i < 3; i++)//verify the three positions of bars
    {
        int counterP1 = p1->bar.PaddleY +i;
        int counterP2 = p2->bar.PaddleY+i;
        if ((ball->ballPosX == 3 && ball->ballPosY == counterP1)|| (ball->ballPosX == 46  && ball->ballPosY == counterP2))
        {
            ball->ballDirectionX *= -1;
            break;
        }
    }

    usleep(80000);
    //ball switch position

}

void clearScreen(){//function that will clear the console screen
    #if defined(_WIN32)|| defined(_WIN64)
        system("cls");
    #else
        system("clear");
    #endif
}

void render(char camp[h][l], Ball *ball, Player *p1, Player *p2){
    
    createCamp(camp, p1, p2, ball);
    clearScreen();
    printCamp(camp);

}


int main(){

    Ball ball;
    createBall(&ball);
    char camp[h][l] = {};
    memset(camp, ' ', sizeof(camp));
    char keybind;
    Player player1, player2;
    createPlayer1(&player1);
    createPlayer2(&player2);
    noEnter();
    boolean changed = falso;//boolean for verify if one keybind was pressed
    render(camp, &ball, &player1, &player2);
    while((player1.points < 10 && player2.points < 10)){//while the player 1 and player 2 points are less than 10, the game will continue, and if the player press 0, the game will end
        memset(camp, ' ', sizeof(camp));
       
        pressingKeybind(&keybind,&player1, &player2, &ball);  
      
        if(ball.moving == truee){ //the game start soleny someone the players input keybind
            movimentBall(&ball, &player1, &player2);
            changed = truee;
        }

        if (changed ==truee)//the render start soleny if the first condition is true
        {
            render(camp, &ball, &player1, &player2);
            printf("\n\n\n  Player 1: %d                                                                                 Player 2: %d\n", player1.points, player2.points);
            changed = falso;
        }
        
       

        if(player1.points == 10){
            printf("\n\n\n  Player 1 wins!\n");
            
        }else if(player2.points == 10){ 
           printf("\n\n\n  Player 2 wins!\n");

        }
    }   
    return 0;
}