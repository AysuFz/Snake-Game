#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include "clui.h"
using namespace std;

int userNum, gameOver, k, speed, second, minute, mSecond, updateTime;
int playerN1, playerN2;
char key;
const int height = 20, width = 20;

enum direction{
   STOP, RIGHT, LEFT, UP, DOWN
};

struct point{
    int x, y;
} pizza, bomb1, bomb2, tool1[350], tool2[350];

struct ply{
    int x, y, score, nTool;
    direction drc;
} player1, player2; 

struct info{
    char name[30];
    int score;
} user[50];

void setup(){
    player1 = {2 , 14 , 0 , 3 , STOP};
    player2 = {17 , 6 , 0 , 3 , STOP};
    tool1[0].x = 2 , tool1[0].y = 15;
    tool1[1].x = 2 , tool1[1].y = 16;
    tool1[2].x = 2 , tool1[2].y = 17;

    tool2[0].x = 17 , tool2[0].y = 5;
    tool2[1].x = 17 , tool2[1].y = 4;
    tool2[2].x = 17 , tool2[2].y = 3;

    second = 59, minute = 1, mSecond = 2;
    updateTime = 20;
    do{
        k=0;
        pizza.x = (rand() % (width-2)) + 1;
        pizza.y = (rand() % (height-2)) + 1;
        for(int i=0; i<player1.nTool; i++)
            if(tool1[i].x == pizza.x && tool1[i].y == pizza.y)
               k++;
        if(player1.x == pizza.x && player1.y == pizza.y)
            k++;
        for(int i=0; i<player2.nTool; i++)
            if(tool2[i].x == pizza.x && tool2[i].y == pizza.y)
               k++;
        if(player2.x == pizza.x && player2.y == pizza.y)
            k++;
    }while(k != 0);

    do{
        k=0;
        bomb1.x = (rand() % (width-2)) + 1;
        bomb1.y = (rand() % (height-2)) + 1;
        bomb2.x = (rand() % (width-2)) + 1;
        bomb2.y = (rand() % (height-2)) + 1;
        for(int i=0; i<player1.nTool; i++){
            if(tool1[i].x==bomb1.x && tool1[i].y==bomb1.y)
               k++;
            else if(tool1[i].x==bomb2.x && tool1[i].y==bomb2.y)
               k++;
        }
        if(player1.x==bomb1.x && player1.y==bomb1.y)
            k++;
        else if(player1.x==bomb2.x && player1.y==bomb2.y)
            k++;
        for(int i=0; i<player2.nTool; i++){
            if(tool2[i].x==bomb1.x && tool2[i].y==bomb1.y)
               k++;
            else if(tool2[i].x==bomb2.x && tool2[i].y==bomb2.y)
               k++;
        }
        if(player2.x==bomb1.x && player2.y==bomb1.y)
            k++;
        else if(player2.x==bomb2.x && player2.y==bomb2.y)
            k++;
        if(pizza.x==bomb1.x && pizza.y==bomb1.y)
            k++;
        else if(pizza.x==bomb2.x && pizza.y==bomb2.y)
            k++;
    }while(k!=0);

    gameOver = 0;
}

void draw(){
    system("cls");
    change_color_rgb(247, 181, 94);
    cout << "Time: ";
    change_color_rgb(130, 230, 232);
    if(second >= 10)
       cout << "0" << minute << " : " << second << endl;
    else{
        cout << "0" << minute << " : " << "0" << second << endl;
    }

    for(int i=0; i<width; i++){
        for(int j=0; j<height; j++){
            change_color_rgb(173, 89, 40);
            if(i==0 || i==width-1)  cout << "_";
            else if(j==0 || j==height-1)  cout << "|";

            else if(player1.x==j && player1.y==i){
               change_color_rgb(83, 199, 60);
               cout << "O";}
            else if(player2.x==j && player2.y==i){
               change_color_rgb(245, 236, 76);
               cout << "O";}
            else if(pizza.x==j && pizza.y==i){
               change_color_rgb(242, 68, 68);
               cout << "@";}
            else if(bomb1.x==j && bomb1.y==i){
               change_color_rgb(201, 201, 187);
               cout << "B";}
            else if(bomb2.x==j && bomb2.y==i){
               change_color_rgb(201, 201, 187);
               cout << "B";}

            else{
                int k=0;
                change_color_rgb(83, 199, 60);
                for(int p=0; p<player1.nTool; p++)
                    if(tool1[p].x==j && tool1[p].y==i){
                        cout << "#";
                        k=1;
                        break;
                    }
                change_color_rgb(245, 236, 76);
                if(k == 0){
                    for(int p=0; p<player2.nTool; p++)
                    if(tool2[p].x==j && tool2[p].y==i){
                        cout << "#";
                        k=1;
                        break;
                    }
                }
                
                if(k == 0) cout << " ";
            }
        }
        cout << endl;
    }
    change_color_rgb(83, 199, 60);
    cout << "player1:" << player1.score << endl;
    change_color_rgb(245, 236, 76);
    cout << "player2:" << player2.score << endl;
    reset_color();
}

void input(){
    if(kbhit()){
        int c = getch();
        if(c==0 || c==224){
            c = getch();
            int k = c;
            switch(k){
                case 72:
                   if(player2.drc!= DOWN)
                   player2.drc = UP;
                   break;
                case 80:
                   if(player2.drc!= UP)
                   player2.drc = DOWN;
                   break;
                case 75:
                   if(player2.drc!= RIGHT)
                   player2.drc = LEFT;
                   break;
                case 77:
                   if(player2.drc!= LEFT)
                   player2.drc = RIGHT;
                   break;
                default:
                   break;
            }
        }
        switch (c){
            case 'a':
               if(player1.drc!= RIGHT)
               player1.drc = LEFT;
               break;
            case 's':
               if(player1.drc!= UP)
               player1.drc = DOWN;
               break;
            case 'd':
               if(player1.drc!= LEFT)
               player1.drc = RIGHT;
               break;
            case 'w':
               if(player1.drc!= DOWN)
               player1.drc = UP;
               break;
            default:
               break;
        }
    }
}

void logic(){
    mSecond--;
    if(mSecond==-1){
        second--;
        mSecond = 9;
    }
    if(second == -1){
        minute--;
        mSecond = 59;
    }
    if(minute == -1){
       gameOver = 3;}

    if(player1.drc!=STOP){
        for(int i=player1.nTool-1; i>0; i--){
        tool1[i].x = tool1[i-1].x;
        tool1[i].y = tool1[i-1].y;
    }
    tool1[0].x = player1.x;
    tool1[0].y = player1.y;
    }
    
    if(player2.drc!=STOP){
        for(int i=player2.nTool-1; i>0; i--){
        tool2[i].x = tool2[i-1].x;
        tool2[i].y = tool2[i-1].y;
    }
    tool2[0].x = player2.x;
    tool2[0].y = player2.y;
    }


    switch(player1.drc){
        case LEFT:
           player1.x--;
           break;
        case RIGHT:
           player1.x++;
           break;
        case UP:
           player1.y--;
           break;
        case DOWN:
           player1.y++;
           break;
        default:
           break;
    }

    switch(player2.drc){
        case LEFT:
           player2.x--;
           break;
        case RIGHT:
           player2.x++;
           break;
        case UP:
           player2.y--;
           break;
        case DOWN:
           player2.y++;
           break;
        default:
           break;
    }

    if(player1.x==0 || player1.x==width || player1.y==0 || player1.y==height)
       gameOver = 1;
    else if(player2.x==0 || player2.x==width || player2.y==0 || player2.y==height)
       gameOver = 1;

    if((player1.x==bomb1.x&&player1.y==bomb1.y) || (player1.x==bomb2.x&&player1.y==bomb2.y))
       gameOver = 2;
    else if((player2.x==bomb1.x&&player2.y==bomb1.y) || (player2.x==bomb2.x&&player2.y==bomb2.y))
       gameOver = 2;

    for(int i=1; i<player1.nTool; i++)
        if(tool1[i].x==player1.x && tool1[i].y==player1.y)
           gameOver = 1;
    for(int i=1; i<player2.nTool; i++)
        if(tool2[i].x==player2.x && tool2[i].y==player2.y)
           gameOver = 1;

    for(int i=0; i<player1.nTool; i++)
        if(tool1[i].x==player2.x && tool1[i].y==player2.y)
           gameOver = 1;
    for(int i=0; i<player2.nTool; i++)
        if(tool2[i].x==player1.x && tool2[i].y==player1.y)
           gameOver = 1;
    

    if(player1.x == pizza.x && player1.y == pizza.y){
        Beep(523,50);
        player1.nTool++;
        player1.score += 10;
        do{
        k=0;
        pizza.x = (rand() % (width-2)) + 1;
        pizza.y = (rand() % (height-2)) + 1;
        for(int i=0; i<player1.nTool; i++)
            if(tool1[i].x==pizza.x && tool1[i].y==pizza.y)
               k++;
        if(player1.x==pizza.x && player1.y==pizza.y)
            k++;
        for(int i=0; i<player2.nTool; i++)
            if(tool2[i].x==pizza.x && tool2[i].y==pizza.y)
               k++;
        if(player2.x==pizza.x && player2.y==pizza.y)
            k++;
        if(pizza.x==bomb1.x && pizza.y==bomb1.y)
            k++;
        else if(pizza.x==bomb2.x && pizza.y==bomb2.y)
            k++;
    }while(k!=0);
    }

    updateTime--;
    if(updateTime == 0){
        do{
        k=0;
        bomb1.x = (rand() % (width-2)) + 1;
        bomb1.y = (rand() % (height-2)) + 1;
        bomb2.x = (rand() % (width-2)) + 1;
        bomb2.y = (rand() % (height-2)) + 1;
        for(int i=0; i<player1.nTool; i++){
            if(tool1[i].x==bomb1.x && tool1[i].y==bomb1.y)
               k++;
            else if(tool1[i].x==bomb2.x && tool1[i].y==bomb2.y)
               k++;
        }
        if(player1.x==bomb1.x && player1.y==bomb1.y)
            k++;
        else if(player1.x==bomb2.x && player1.y==bomb2.y)
            k++;
        for(int i=0; i<player2.nTool; i++){
            if(tool2[i].x==bomb1.x && tool2[i].y==bomb1.y)
               k++;
            else if(tool2[i].x==bomb2.x && tool2[i].y==bomb2.y)
               k++;
        }
        if(player2.x==bomb1.x && player2.y==bomb1.y)
            k++;
        else if(player2.x==bomb2.x && player2.y==bomb2.y)
            k++;
        if(pizza.x==bomb1.x && pizza.y==bomb1.y)
            k++;
        else if(pizza.x==bomb2.x && pizza.y==bomb2.y)
            k++;
    }while(k!=0);
    updateTime = 20;
    }
    
    else if(player2.x == pizza.x && player2.y == pizza.y){
        Beep(523,50);
        player2.nTool++;
        player2.score += 10;
        do{
        k=0;
        pizza.x = (rand() % (width-2)) + 1;
        pizza.y = (rand() % (height-2)) + 1;
        for(int i=0; i<player1.nTool; i++)
            if(tool1[i].x==pizza.x && tool1[i].y==pizza.y)
               k++;
        if(player1.x==pizza.x && player1.y==pizza.y)
            k++;
        for(int i=0; i<player2.nTool; i++)
            if(tool2[i].x==pizza.x && tool2[i].y==pizza.y)
               k++;
        if(player2.x==pizza.x && player2.y==pizza.y)
            k++;
    }while(k!=0);
    }
}

void bubble(){
    for(int i=0; i<userNum-1; i++)
       for(int j=0; j<userNum-1-i;j++)
           if(user[j].score < user[j+1].score){
            info temp = user[j];
            user[j] = user[j+1];
            user[j+1] = temp;
           }
}


void newUser(){
    system("cls");
    Beep(523,50);
    change_color_rgb(232, 222, 130);
    cout << "New User's Name Is:" << endl;
    change_color_rgb(130, 230, 232);
    cin.getline(user[userNum].name, 30);
    userNum++;
    return;
}

void startGame(){
    Beep(523,50);
    system("cls");
    if(userNum == 0){
        change_color_rgb(247, 181, 94);
        cout << "There Are No Users!" << endl;
        delay(1500);
        return;
    }
    else if(userNum == 1){
      change_color_rgb(247, 181, 94);
        cout << "The Number Of Users Must Be More Than 1!" << endl;
        delay(1500);
        return;
    }
    else{
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(232, 222, 130);
        cout << "Select User1 :" << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(130, 230, 232);
        for(int i=0; i<userNum; i++)
           cout << i+1 << ". " << user[i].name << endl;
         change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(39, 214, 44);
        cin >> playerN1;
        system("cls");
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(232, 222, 130);
        cout << "Select User2 :" << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(130, 230, 232);
        for(int i=0; i<userNum; i++)
           if(i+1!=playerN1)
              cout << i+1 << ". " << user[i].name << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(39, 214, 44);
        Beep(523,50);
        cin >> playerN2;

        system("cls");
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(39, 214, 44);
        cout << "Select Difficulty:" << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(130, 230, 232);
        cout << "1. Easy" << endl;
        cout << "2. Medium" << endl;
        cout << "3. Hard" << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        Beep(523,50);
        switch(getch()){
            case '1':
               speed = 80;
               break;
            case '2':
               speed = 50;
               break;
            case '3':
               speed = 20;
               break;
            default:
               system("cls");
               change_color_rgb(247, 181, 94);
               cout << "Invalid Key!";
               delay(1500);
               startGame();
               break;
        }

        setup();
        Beep(523,50);
        while(gameOver==0){
        draw();
        input();
        logic();
        Sleep(speed);
        }
        Beep(990,900);
        system("cls");
        change_color_rgb(247, 181, 94);
        switch(gameOver){
            case 1:
               cout << "Accident!";
               break;
            case 2:
               cout << "Boom!";
               break;
            case 3:
               cout << "Time Is Over!";
            default:
               break;
        } 
        delay(1500);
        if(player1.score > user[playerN1-1].score)
           user[playerN1-1].score = player1.score;
        if(player2.score > user[playerN2-1].score)
           user[playerN2-1].score = player2.score;
        system("cls");
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(247, 181, 94);
        cout << "    Game Over!" << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(83, 199, 60);
        cout << user[playerN1-1].name << " : " << player1.score << endl;
        change_color_rgb(245, 236, 76);
        cout << user[playerN2-1].name << " : " << player2.score << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(130, 230, 232);
        cout << "Press b To Back!" << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        Beep(523,50);
        delay(1500);
        if(getch() == 'b')
           return;
    }
}


void scoreBoard(){
    Beep(523,50);
    system("cls");
    if(userNum == 0){
       change_color_rgb(247, 181, 94);
       cout << "There Are No Users!" << endl;
       delay(1500);
       return;}
    else{
    change_color_rgb(214, 39, 214);
    cout << "---------------------" << endl;
    change_color_rgb(39, 214, 44);
    cout << "     ScoreBoard    " << endl;
    change_color_rgb(214, 39, 214);
    cout << "---------------------" << endl;
    bubble();
    change_color_rgb(232, 222, 130);
    for(int i=0; i<userNum; i++){
        cout << i+1 <<". "<< user[i].name << "(" << user[i].score << ")" << endl;
    }
    change_color_rgb(214, 39, 214);
    cout << "---------------------" << endl;
    change_color_rgb(130, 230, 232);
    cout << "Press (b) to Back!" << endl;
    change_color_rgb(214, 39, 214);
    cout << "---------------------" << endl;
    key = getch();
    if(key == 'b') return;
    else{
        system("cls");
        change_color_rgb(247, 181, 94);
        cout << "Invalid Key!" << endl;
        delay(1500);
        scoreBoard();}
    }
}


void changeUser(){
    Beep(523,50);
    system("cls");
    if(userNum == 0){
       change_color_rgb(214, 39, 214);
       cout << "---------------------" << endl;
       change_color_rgb(247, 181, 94);
       cout << "There Are No Users!" << endl;}
    else if(userNum == 1){
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(39, 214, 44);
        cout << userNum << " User found!" << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(232, 222, 130);
        for(int i=0; i<userNum; i++)
           cout << i+1 << ". " << user[i].name << endl;
    }
    else{
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(39, 214, 44);
        cout << userNum << " Users found!" << endl;
        change_color_rgb(214, 39, 214);
        cout << "---------------------" << endl;
        change_color_rgb(232, 222, 130);
        for(int i=0; i<userNum; i++)
           cout << i+1 << ". " << user[i].name << endl;
    }
    change_color_rgb(214, 39, 214);
    cout << "---------------------" << endl;
    change_color_rgb(130, 230, 232);
    cout << "1. Add A New User" << endl;
    cout << "2. Back" << endl;
    change_color_rgb(214, 39, 214);
    cout << "---------------------" << endl;
    key = getch();
    if(key == '1'){
       newUser();
       changeUser();
    }
    else if(key == '2')
       return;
    else{
        system("cls");
        change_color_rgb(247, 181, 94);
        cout << "Invalid Key!" << endl;
        delay(1500);
        changeUser();
    }
}


void exit(){
    system("cls");
    change_color_rgb(214, 39, 214);
    cout << "---------------------" << endl;
    change_color_rgb(247, 181, 94);
    cout << "      GoodBye!       " << endl;
    change_color_rgb(214, 39, 214);
    cout << "---------------------" << endl;
    Beep(900,900);
    delay(500);
    quit();
}

void menu(){
    Beep(523,50);
    system("cls");
    change_color_rgb(214, 39, 214);
    cout << "----------------------" << endl ;
    change_color_rgb(39, 214, 44);
    cout << "     Snake Game     " << endl;
    change_color_rgb(214, 39, 214);
    cout << "----------------------" << endl;
    change_color_rgb(232, 222, 130);
    cout << " Choose An Option:  " <<endl;
    change_color_rgb(130, 230, 232);
    cout << "1) Start Game       " << endl;
    cout << "2) Score Board      " << endl;
    cout << "3) Change User      " << endl;
    cout << "4) Exit             " << endl;
    change_color_rgb(214, 39, 214);
    cout << "----------------------" << endl;
    switch(getch()){
         case '1':
            startGame();
            menu();
            break;
         case '2':
           scoreBoard();
           menu();
            break;
         case '3':
            changeUser();
            menu();
            break;
         case '4':
            exit();
            break;
         default:
            system("cls");
            change_color_rgb(247, 181, 94);
            cout << "Invalid Key!";
            delay(1500);
            menu();
            break;
     }
}


int main(){
    menu();
    return 0;
}