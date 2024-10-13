#include "../Header/game.h"
#include "../Header/mywindows.h"
#include "../Header/data.h"
#include<stdio.h>
#include<conio.h>
#include<time.h>


// 定义当前的方块和下一个方块
Block block_cur;
Block block_next;

// 碰撞检测
int crash(int x, int y, int shape, int status)
{
    int i, j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            if(blockShape[shape][status][i][j] == 1)
            {
                if(windowShape[i+y][j+x-15] == 1)
                {
                    // 发生碰撞
                    if(block_cur.x == 22 && block_cur.y == 1)
                    {
                        // 方块一产生就发生碰撞
                        return -2;
                    }
                    return -1;
                }
            }
        }
    }
    return 0;
}

// 产生第一个方块
void startBlock()
{
    srand((unsigned)time(NULL));  // 随机生成
    block_cur.x = 22;
    block_cur.y = 1;
    block_cur.shape = rand()%7;  // 0 1 2 3 4 5 6
    block_cur.status = rand()%4;  // 0 1 2 3
    block_cur.color = rand()%0x10;  // 十六进制16
    if(block_cur.color == 0x00)
    {
        block_cur.color = 0x0f;
    }
    printBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status, block_cur.color);
}

// 随机产生下一个方块
void randBlock()
{
    // 删除已生成的下一个方块
    deleteBlock(block_next.x, block_next.y, block_next.shape, block_next.status);
    block_next.x = 33;
    block_next.y = 2;
    block_next.shape = rand()%7;  // 0 1 2 3 4 5 6
    block_next.status = rand()%4;  // 0 1 2 3
    block_next.color = rand()%0x10;  // 十六进制16
    if(block_next.color == 0x00)
    {
        block_next.color = 0x0f;
    }
    printBlock(block_next.x, block_next.y, block_next.shape, block_next.status, block_next.color);
}

// 拷贝方块，将下一个方块的值拷贝给当前正在下落的方块
void copyBlock()
{
    deleteBlock(block_next.x, block_next.y, block_next.shape, block_next.status);
    block_cur = block_next;
    block_cur.x = 22;
    block_cur.y = 1;
    printBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status, block_cur.color);
    randBlock();
}

// 定义分数和等级两个变量，用于保存游戏中的等级和分数
int level = 1;
int grade = 0;
int one = 0,two= 0,three = 0,four = 0;  ///消得行数
clock_t start_time1;

// 绘制游戏边框
void printWindow(int x, int y)
{
    int i, j;
    for(i=0; i<25; i++)
    {
        for(j=0; j<26; j++)
        {
            if(windowShape[i][j] == 1)
            {
                setColor(0xc0);
                setPos(j+x, i+y);
                printf("%2s","");
                // printf("□");
            }
        } 
    }
    setColor(0x0);
}

//初始化游戏
void initGame()
{
    initHandle(); //初始化句柄
    printAnimation();
    hideCursor();
    setTitle("俄罗斯方块儿");
    borderLeft();
    printWindow(15,0);
    printInterface();
    printGL(0);
    startBlock();
    randBlock();
    
    clock_t startTime = clock();
    clock_t stopTime;
    clock_t start_time1 = clock();

    
    while(1)
    {
        // 检测是否有按键按下
        if(kbhit())
        {
        // 判断按键
           switch(getch())
           {
           case 'w':
           case 'W':
           case 72:  //上建
               blockChange();
               break;
           case 'a':
           case 'A':
           case 75:  //左键
               blockLeft();
               break;
           case 'd':
           case 'D':
           case 77:  //右键
               blockRight();
               break;
           case 's':
           case 'S':
           case 80:  //下键
               blockDown();
               break;
           case 32:  //空格
               pause();
               break;
           case 13:  //回车
               blockBottom();
               break;

           }
        }
        stopTime = clock();
        if (stopTime - startTime > 0.65 * CLOCKS_PER_SEC)
        {
            // 判断是否游戏结束
            gameTime(start_time1);
            if(blockDown() == -2)
            {
                break;
            }
            startTime = stopTime;
        }
    }
    printOver();
    printFinish();
}
 

// 绘制界面提示信息
void printInterface()
{
    setColor(0x0a);
    // 打印操作说明
    setColor(0xc0);
    setPos(32,12);
    printf("经典模式");
    setColor(0x0f);
    setPos(32,14);
    printf("操作说明");
    setColor(0x0b);
    setPos(32,16);
    printf("按 a 或 A 左移");
    setPos(32,17);
    printf("按 d 或 D 右移");
    setPos(32,18);
    printf("按 w 或 W 变形");
    setPos(32,19);
    printf("按 s 或 S 下落");
    setPos(32,20);
    printf("按 空格 暂停");
    setPos(32,21);
    printf("按 回车 直接下落");
}

// 打印分数和等级  num：一次消得行数
void printGL(int num)
{
    switch(num)
    {
    case 0:
        break;
    case 1:
        grade+=10; one++; break;
    case 2:
        grade+=30; two++; break;
    case 3:
        grade+=50; three++; break;
    case 4:
        grade+=80; four++; break;
    }

    setColor(0x09);
    setPos(3, 6);
    printf("分数：%d",grade);

    if(grade < 10)
        level = 1;
    else if(grade >= 10 && grade < 50)
        level = 2;
    else if(grade >=50 && grade < 100)
        level =3;
    else if(grade >=100 && grade <200)
        level = 4;
    else if(grade >=200 && grade <400)
        level = 5;
    else if(grade >= 400 && grade <800 )
        level = 6;
    else if(grade >= 800 && grade <1600)
        level = 7;
    else if(grade >=1600)
        level = 8;
    
    setPos(3, 7);
    switch(level)
    {
    case 1:
        printf("段位: 倔强青铜"); break;
    case 2:
        printf("段位: 秩序白银"); break;
    case 3:
        printf("段位: 荣耀黄金"); break;
    case 4:
        printf("段位: 尊贵铂金"); break;
    case 5:
        printf("段位: 永恒钻石"); break;
    case 6:
        printf("段位: 至尊星耀"); break;
    case 7:
        printf("段位: 最强王者"); break;
    case 8:
        printf("段位: 荣耀王者"); break;
    }
    setPos(3,11);
    printf("消除一行 %d次",one);
    setPos(3,12);
    printf("消除两行 %d次",two);
    setPos(3,13);
    printf("消除三行 %d次",three);
    setPos(3,14);
    printf("消除四行 %d次",four);

    time_t timep;
    struct tm *p;
    time (&timep);
    p=gmtime(&timep);

    setColor(0x02);
    setPos(3,18);
    printf("日期：%d/%d/%d\n",1900+p->tm_year,1+p->tm_mon,p->tm_mday);
    setPos(3,19);
    printf("时间：%d:%d:%d",8+p->tm_hour,p->tm_min,p->tm_sec);

}

//游戏计时
void gameTime(clock_t start_time)
{
    setColor(0x06);
    setPos(3,3);
    printf("游戏时间 %d s",(clock() - start_time) / CLOCKS_PER_SEC);
}

//打印左边框
void borderLeft()
{
    setColor(0x09);
    setPos(0,0);
    printf("□ □ □ □ □ □ □ □ □ □ □ □ □  □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□                          □\n");
    printf("□ □ □ □ □ □ □ □ □ □ □ □ □  □\n");
}
// 打印方块
void printBlock(int x, int y, int shape, int status, int color)
{
    int i, j;
    setColor(color);
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            if(blockShape[shape][status][i][j] == 1)
            {
                setPos(x+j, y+i);
                printf("■");
            }
        }
    }
}
// 删除方块儿
void deleteBlock(int x, int y, int shape, int status)
{
    int i, j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            if(blockShape[shape][status][i][j] == 1)
            {
                setPos(x+j, y+i);
                printf("  "); //两个空格
            }
        }
    }
}

// 方块左移
void blockLeft()
{
    if(crash(block_cur.x - 1, block_cur.y, block_cur.shape, block_cur.status) == -1)
    {
        return;
    }
    // 删除方块
    deleteBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status);
    // 改变坐标
    block_cur.x -= 1;
    // 重新打印方块
    printBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status, block_cur.color);
} 
// 方块右移      
void blockRight()
{
     if(crash(block_cur.x + 1, block_cur.y, block_cur.shape, block_cur.status) == -1)
    {
        return;
    }
    // 删除方块
    deleteBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status);
    // 改变坐标
    block_cur.x += 1;
    // 重新打印方块
    printBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status, block_cur.color);
}
// 方块变形      
void blockChange()
{
    if(crash(block_cur.x, block_cur.y, block_cur.shape, (block_cur.status + 1)%4) == -1)
    {
        return;
    }
    else
    {
        // 删除方块
        deleteBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status);
        // 改变形态
        block_cur.status = (block_cur.status+1)%4; // 0 1 2 3 -> 0 1 2 3   1 2 3 4 -> 1 2 3 0
        // 重新打印方块
        printBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status, block_cur.color);
    }
}
// 方块下移          
int blockDown()
{
    if(crash(block_cur.x, block_cur.y + 1, block_cur.shape,block_cur.status) == -1)
    {
        // 重新生成下一个方块
        saveBlock();
        lineClear();
        copyBlock();
        updateGame();
        return -1;
    }else if(crash(block_cur.x, block_cur.y + 1, block_cur.shape,block_cur.status) == -2)
    {
        // 游戏结束 游戏结束画面/继续游戏-结束游戏提示
        return -2;
    }
    deleteBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status);  // 删除方块
    block_cur.y += 1;  // 方块下移
    printBlock(block_cur.x, block_cur.y, block_cur.shape, block_cur.status, block_cur.color);
}
// 方块直接落底
void blockBottom()
{
      while(1)
    {
        if(crash(block_cur.x, block_cur.y + 1, block_cur.shape, block_cur.status) == -1)
        {
            // 重新生成下一个方块
            saveBlock();
            lineClear();
            copyBlock();
            updateGame();
            randBlock(32,3);
            return;
        }else if(crash(block_cur.x, block_cur.y + 1, block_cur.shape,block_cur.status) == -2)
        {
            // 游戏结束 游戏结束画面/继续游戏-结束游戏提示
            return;
        }
        else
        {
            ++ block_cur.y;
        }
    }
}
//游戏暂停   
void pause()
{
         while(1)
    {
        if(getch() == 32)   // vs2022   if(_getch() == 32)
        {
            break;
        }
    }
} 
// 保存方块
void saveBlock()
{
    int i,j;
    for(i=0; i<4; i++)
    {
        for(j=0; j<4; j++)
        {
            if(blockShape[block_cur.shape][block_cur.status][i][j] == 1)
            {
                windowShape[i+block_cur.y][j+block_cur.x-15] = 1;
            }
        }
    }
}

// 刷新游戏区域
void updateGame()
{
    int i,j;
    for(i=1; i<24; i++)
    {
        for(j = 1; j < 15; j++)
        {
            if(windowShape[i][j] == 1)
            {
                setColor(0x0e);
                setPos(j+15, i);
                printf("■");
            }
            else
            {
                setColor(0x00);
                setPos(j+15, i);
                printf("%2s","");
            }
        }
    }
}
// 消行检测
void lineClear()
{
    int i, j;
    int number = 0;
    for (i = 23; i > 1; i--)
    {
        int total = 0;
        for( j=1; j<15;j++ )
        {
            total += windowShape[i][j];
        }
        if(total == 14)
        {
            lineDown(i);
            i += 1;
            number += 1;//统计一次消了多少行
        }
    }
    printGL(number);   //调用计分函数
}
// 消行下移
void lineDown(int line)
{
    int i,j;
    for(i=line; i>1; i--)
    {
        for(j=1; j<15; j++)
        {
            windowShape[i][j] = windowShape[i-1][j];  // 下移
        }
    }
}
//游戏结束动画
void printOver()
{
    int i, j;
    for(i=23; i>0; i--)
    {
        for(j=14; j>0; j--)
        {
            setColor(0X76);
            setPos(j+15, i);
            printf("★");
            Sleep(5);
        }
    }
}

//重新开始提示
void printFinish()
{
    setColor(0x0d);
    setPos(20,8);
    printf("游戏结束\n");
    setPos(20,10);
    printf("按“Y”重新开始!\n");
    setPos(20,11);
    printf("按“N”打开结算画面");

    switch(getch())  // vs2022  switch(_getch())
    {
    case 'Y':
    case 'y':
        againGame();break;
    case 'N':
    case 'n':
        endGame();break;
    case 13:
        printFinish();break;
    default:
        printFinish();break;
    }
}

// 重新开始
void againGame()
{
    setColor(0x00);
    system("cls"); //清屏
    // 初始化游戏吃
    int i,j;
    for(i=1; i<24; i++)
    {
        for(j=1; j<15; j++)
        {
            windowShape[i][j] = 0;
        }
    }
    initGame();
}
//打印开始界面
void printStart(int x, int y)
{
    int color = rand()%0x10;
    if(color == 0x00)
    {
        color = 0x0f;
    }
    setColor(color);
    setPos(x, y);
    printf("★★★★★★★★★★  ★★★★★★★★★★  ★★★★★★★★★★  ★★★★★★★★  ★★★★★★    ★★★★★★★★");
    setPos(x, y+1);
    printf("    ★★      ★★              ★★      ★★    ★★    ★★    ★★");
    setPos(x, y+2);
    printf("    ★★      ★★★★★★★★        ★★      ★★★★★★★★    ★★      ★★★★★★");
    setPos(x, y+3);
    printf("    ★★      ★★              ★★      ★★  ★★      ★★            ★★");
    setPos(x, y+4);
    printf("    ★★      ★★★★★★★★★★      ★★      ★★    ★★  ★★★★★★   ★★★★★★★★");

    setPos(20, 15);
    printf("按任意键开始游戏");
}

//清除开始动画
void clearStart(int x, int y)
{
    int i,j;
    for(i=y; i<=y+4; i++)
    {
        for(j=x; j<=x+33; j++)
        {
            setPos(j, i);
            printf("  "); 
        }
    }
}

// 动画
void printAnimation()
{
    clock_t time1, time2;
    time1 = clock();
    int x=5;
    printStart(x, 5);

    while(1)
    {
        time2 = clock();
        if(time2-time1 > 300)
        {
            time1 = time2;
            clearStart(x,5);
            printStart(++x, 5);
            if(x == 25)
            {
                clearStart(x, 5);
                x = 0;
            }
        }
        if(kbhit()){
            break;
        }
    }
    system("cls");
}

///游戏结束界面边框
void endGame()
{
    system("cls");

    setPos(20,6);
    setColor(12);
    printf("游戏运行时间：%d s", (clock() - start_time1) / CLOCKS_PER_SEC);

    setPos(20,8);
    setColor(12);
    printf("Game  Over!");

    setPos(20,10);
    printf("分数: %d",grade);

    setPos(20,12);
    switch(level)
    {
    case 1:
        printf("段位: 倔强青铜"); break;
    case 2:
        printf("段位: 秩序白银"); break;
    case 3:
        printf("段位: 荣耀黄金"); break;
    case 4:
        printf("段位: 尊贵铂金"); break;
    case 5:
        printf("段位: 永恒钻石"); break;
    case 6:
        printf("段位: 至尊星耀"); break;
    case 7:
        printf("段位: 最强王者"); break;
    case 8:
        printf("段位: 荣耀王者"); break;
    }

    setPos(20,14);
    printf("消除一行 %d次",one);
    setPos(20,16);
    printf("消除两行 %d次",two);
    setPos(20,18);
    printf("消除三行 %d次",three);
    setPos(20,20);
    printf("消除四行 %d次",four);

    setPos(20,22);
    printf("按“Esc”退出游戏");
    switch(getch())  // vs2022  switch(_getch())
    { 
    case 27:
        break;
    }
}






