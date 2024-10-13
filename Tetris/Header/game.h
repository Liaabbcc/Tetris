#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include<time.h>

/*逻辑模块*/

// 方块结构体
typedef struct block{
    int x;   //所在列
    int y;   // 所在行
    int shape;  // 形状
    int status;  // 形态
    int color;  // 颜色
}Block;
// 绘制游戏边框
extern void printWindow(int x, int y);
// 初始化游戏
extern void initGame();
// 绘制界面提示信息 
extern void printInterface();
// 打印分数和等级
extern void printGL(int num);
///打印左边框
extern void borderLeft();
// 打印方快
extern void printBlock(int x, int y, int shape, int status, int color);
// 删除方块
extern void deleteBlock(int x, int y, int shape, int status);
// 方块左移
extern void blockLeft();  
// 方块右移      
extern void blockRight();
// 方块变形      
extern void blockChange(); 
// 方块加速下移          
extern int  blockDown();
// 方块直接落底
extern void blockBottom();
//游戏暂停   
extern void pause();
// 产生第一个方块
extern void startBlock();
// 随机产生下一个方块
extern void randBlock();
// 拷贝方块，将下一个方块的值拷贝给当前正在下落的方块
extern void copyBlock();
// 碰撞检测
int crash(int x, int y, int shape, int status);
// 保存方块
extern void saveBlock();
// 刷新游戏区域
extern void updateGame();
// 消行检测
extern void lineClear();
// 消行下移
extern void lineDown(int line);
// 游戏结束动画
extern void printOver();
// 重新开始提示
extern void printFinish();
// 重新开始
extern void againGame();
//打印开始界面
extern void printStart(int x, int y);
//清楚开始界面   
extern void clearStart(int x, int y); 
//动画 
extern void printAnimation();
//游戏计时
extern void gameTime(clock_t start_time);
//游戏结束界面
extern void endGame();

#endif // GAME_H_INCLUDED
