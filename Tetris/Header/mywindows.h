#ifndef MYWINDOWS_H_INCLUDE
#define MYWINDOWS_H_INCLUDE
#include<windows.h>   //windows系统函数

/*系统调用模块*/

// 1.初始化句柄
extern void initHandle();
// 2.设置颜色
extern void setColor(int color);
// 3.设置光标是否可见
extern void hideCursor();
// 4.设置位置
extern void setPos(int x,int y);
// 5.设置窗口大小
extern void setWindowSize(int w,int h);
// 6.设置标题
extern void setTitle(char title[40]);
// 关闭句柄
extern void closeHandle();
#endif