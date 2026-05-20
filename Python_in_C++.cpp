#include<iostream>
#include<conio.h>
#include<string>
#include<chrono>
#include<thread>
#include<vector>
#define Row 15
#define Col 25
void control(std::vector<std::pair<int,int>> &snake,char dir){
    int x=snake[0].first,y=snake[0].second;
    if(dir=='w')
    x--;
    else if(dir=='s')
    x++;
    else if(dir=='a')
    y--;
    else if(dir=='d')
    y++;
    snake.insert(snake.begin(),{x,y});
    snake.pop_back();
}

bool condition(std::vector<std::pair<int,int>> &snake){
      int x=snake[0].first,y=snake[0].second;
if (x>=Row || x<=0 || y<=0 || y>=Col-1)
return true;
return false;
}

void screen(char canvas[Row][Col],std::vector<std::pair<int,int>> &snake){
for(int i=0;i<Row;i++){
    for(int j=0;j<Col;j++){
        if( j==0 ||  j==Col-1){ 
                canvas[i][j]='*';}
        else if((i==0 || i==Row-1)&&(j%2==0)){
                canvas[i][j]='*';}
        else 
                {canvas[i][j]=' ';}}}
           for(auto p:snake){
            canvas[p.first][p.second]='O';}}

void display(char canvas[Row][Col]){
    for(int i=0;i<Row;i++){
    for(int j=0;j<Col;j++){
        std::cout<<canvas[i][j];}
         std::cout<<std::endl;}}


void game(char canvas[Row][Col],std::vector<std::pair<int,int>> &snake){
   char dir;
  while(!condition(snake)){
    screen(canvas,snake);
    display(canvas);
    if(_kbhit())
    dir=getch();
    control(snake,dir);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    system("cls");
  }
}
int main(){
std::vector<std::pair<int,int>> snake;
snake.push_back({8,17});
snake.push_back({8,16});
snake.push_back({8,15});
char canvas[Row][Col];
game(canvas, snake);
std::cout<<"GAME OVER!!!";
return 0;}