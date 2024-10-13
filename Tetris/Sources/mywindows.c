#include"../Header/mywindows.h" // 里面导入了windows.h
HANDLE handle;  //全局变量

// 1.初始化句柄 ,初始化接口
void initHandle()
{
    handle = GetStdHandle(STD_OUTPUT_HANDLE);
    hideCursor();
}
// 2.设施颜色
void setColor(int color)
{
    SetConsoleTextAttribute(handle,color); //
}
//隐藏光标
void hideCursor()
{
    CONSOLE_CURSOR_INFO info;
    info.bVisible = FALSE;      //设置光标是否可见
    info.dwSize = 1;           //光标的宽度(1-100)
    SetConsoleCursorInfo(handle,&info);

}
 
// 4.设置位置
void setPos(int x, int y)
{
    COORD pos = {x*2,y};
    SetConsoleCursorPosition(handle,pos);
}
// 5.设置窗口大小
void setWindowSize(int w,int h)
{
    COORD coord = {w,h};
    SetConsoleScreenBufferSize(handle,coord);
    SMALL_RECT rect = {0, 0, w-1,h-1};
    SetConsoleWindowInfo(handle,1,&rect);
}
// 6.设置标题
void setTitle(char title[40])
{
    SetConsoleTitle(title);
}
// 关闭句柄
void closeHandle()
{
    closeHandle();
}