/*Head files*/#include<bits/stdc++.h>
#include<windows.h>
#include<mmsystem.h>
#include <conio.h>
#include<sys/timeb.h>
/*Libs*/#pragma comment(lib,"winmm.lib")
/*Pragam*/#pragma warning(disable:0266)
/*Define*/#define key(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0)
/*Use std namespace*/using namespace std;
/*Clear stage and grass color*/bool clear,gc[30][20];
/*Any things*/int bc,zc,pc,cnt,st=50;
/*Square*/string sq="██";
/*User name*/string /*land[11][7], house[3][7],*/ username;
/*User game data*/short bigstage,smallstage,diamond,coin;
/*Set list link struct*/typedef struct pea{
    float x,oldx;
    int y;
    //peadata *inf;
    pea* next;
}pea,* pealist;
typedef struct zombie{
    float x,oldx;
    int y;
    short id;
    short live;
    bool iseat;
    float speed;
    zombie* next;
}zombie,* zombielist;
/*Main data*/
int cyspm(bool z);
int dele();
int hin();
int liste();
int mp();
int mpw();
long long sst();
POINT wm();
pea* init();
void bgm();
void blistp();
void bp();
void cls();
void cur();
void developer();
void gcs();
void logo();
void nomal(int b,int s);
void oland();
void op();
void rgb_init();
void rgbpp();
void srgb();
void ue();
void ws();
/*Unable exit*/void ue(){
    DeleteMenu(GetSystemMenu(GetConsoleWindow(),FALSE),
               SC_CLOSE,MF_DISABLED);
    DrawMenuBar(GetConsoleWindow());
}
/*???*/void tga(){
    SetWindowLongPtrA(
        GetConsoleWindow(),
        GWL_STYLE,
        GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)&~WS_CAPTION);
}
/*Move symbol*/void move(float startx,int starty,float endx,int endy,float movex,int movey){
    HANDLE outputHandle=GetStdHandle(STD_OUTPUT_HANDLE);
    // 获取屏幕缓冲区信息
    CONSOLE_SCREEN_BUFFER_INFO consoleScreenBufferInfo;
    GetConsoleScreenBufferInfo(outputHandle,&consoleScreenBufferInfo);
    // 输出被移动的文本
    //printf("Hello");
    getchar();
    // 移动文本
    // 被移动的区域
    SMALL_RECT movePos{startx*2, starty, endx*2+1, endy};
    // 移动到的新位置的左上角坐标
    //             X  Y
    COORD newPos{movex*2, movey};
    // 被移动区域填充的字符的信息
    CHAR_INFO charInfo;
    // 被移动区域留空
    charInfo.Char.AsciiChar=' ';
    // 设置被移动区域新填充的字符的属性(也可以说成颜色，但是不太准确)
    // 属性的值为当前输出的文本的属性
    charInfo.Attributes=consoleScreenBufferInfo.wAttributes;

    // 调用 API
    ScrollConsoleScreenBufferA(outputHandle,&movePos,NULL,newPos,&charInfo);
}
/*Initializer pealist*/pea* pinit(){
    pea* head=new pea;//申请一个Node类型的空间  返回一个地址 
    head->x=0;
    head->y=0;
    head->oldx=0;
    head->next=nullptr;	//头节点
    return head;
}
/*Initializer zombielist*/zombie* zinit(){
    zombie* head=new zombie;//申请一个Node类型的空间  返回一个地址 
    head->x=0;
    head->y=0;
    head->oldx=0;
    head->id=0;
    head->iseat=false;
    head->speed=0;
    head->live=-32768;
    head->next=nullptr;	//头节点
    return head;
}
/*Head insert link(old)*/void headinsert(pea* head,int x,int y){
    pea* cur=new pea();
    cur->x=x;
    cur->y=y;
    cur->next=head->next;
    head->next=cur;
}
/*System time*/long long sst(){
    timeb t;
    ftime(&t);
    return t.time*1000+t.millitm;
}
/*Outpot RGB color options*/void rgb_init(){
    HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
    HANDLE hOut=GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwInMode,dwOutMode;
    GetConsoleMode(hIn,&dwInMode);
    GetConsoleMode(hOut,&dwOutMode);
    dwInMode|=0x0200;
    dwOutMode|=0x0004;
    SetConsoleMode(hIn,dwInMode);
    SetConsoleMode(hOut,dwOutMode);
}
/*Windows options set*/void ws(){
    system("title Pvz Cmd");
    system("mode con cols=58 lines=26");
    HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode;
    GetConsoleMode(hStdin,&mode);
    mode&=~ENABLE_QUICK_EDIT_MODE; //移除快速编辑模式
    mode&=~ENABLE_INSERT_MODE; //移除插入模式
    mode&=~ENABLE_MOUSE_INPUT;
    SetConsoleMode(hStdin,mode);
    SetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE,GetWindowLongPtrA(GetConsoleWindow(),GWL_STYLE)&~WS_SIZEBOX&~WS_MAXIMIZEBOX&~WS_MINIMIZEBOX);
    CONSOLE_CURSOR_INFO cursor_info={1,0};
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cursor_info);
    rgb_init();
    HANDLE OP;
    COORD coord={0,0};
    OP=GetStdHandle(STD_OUTPUT_HANDLE);
}
/*Mouse window pos get*/POINT wm(){
    POINT p;
    int x,y;
    CONSOLE_FONT_INFO a;
    GetCursorPos(&p);
    ScreenToClient(GetForegroundWindow(),&p);
    GetCurrentConsoleFont(GetStdHandle(STD_OUTPUT_HANDLE),FALSE,&a);
    p.x=p.x/a.dwFontSize.X;
    p.y=p.y/a.dwFontSize.Y;
    return p;
}
/*Output RGB color set*/void srgb(int wr,int wg,int wb,short IO){
    if(IO==01){
        printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,wr,wg,wb);
    }
    else if(IO==0){
        printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,0,0,0);
    }
    else if(IO==2){
        printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,255-wr,255-wg,255-wb);
    }
}
/*Output RGB color plus set*/void rgbpp(int wr,int wg,int wb,int gr,int gg,int gb){
    printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,gr,gg,gb);
}
/*Set cmd cursor pos */void cur(double x,int y){
    HANDLE OP;
    short x1=x*2;
    COORD coord={x1,short(y)};
    OP=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(OP,coord);
}
/*Cls plus*/void cls(){
    cur(0,0);
    srgb(255,255,255,1);
    for(int i=0; i<26; i++){
        for(int j=0; j<29; j++){
            cout<<sq;
        }
        Sleep(st);
        cout<<""<<endl;
    }
}
/*Grass color data set*/void gcs(){
    bool x=false;
    int xcnt=0,ycnt=0;
    for(int i=0; i<9; i++){
        for(int j=0; j<3; j++){
            gc[xcnt][0]=x;
            gc[xcnt][1]=x;
            gc[xcnt][2]=x;
            gc[xcnt][3]=!x;
            gc[xcnt][4]=!x;
            gc[xcnt][5]=!x;
            gc[xcnt][6]=x;
            gc[xcnt][7]=x;
            gc[xcnt][8]=x;
            gc[xcnt][9]=!x;
            gc[xcnt][10]=!x;
            gc[xcnt][11]=!x;
            gc[xcnt][12]=x;
            gc[xcnt][13]=x;
            gc[xcnt][14]=x;
            gc[xcnt][15]=!x;
            gc[xcnt][16]=!x;
            gc[xcnt][17]=!x;
            xcnt=xcnt+1;
        }
        x=!x;
    }
}
/*Head insert pealink*/int phin(pealist head,int x,float y){
    int j=0,i=1;
    pealist p=head;
    while(j<i-1&&p){
        p=p->next;
        j++;
    }//令p指向第i-1个结点
    if(!p) return 0;
    pealist q=(pealist)malloc(sizeof(pea));
    q->x=x;
    q->y=y;
    q->next=p->next;
    p->next=q;
    return 1;
}
/*Head insert zombielink*/int zhin(zombielist head,short y,short id,float speed,short live){
    int j=0,i=1;
    zombielist p=head;
    while(j<i-1&&p){
        p=p->next;
        j++;
    }//令p指向第i-1个结点
    if(!p) return 0;
    zombielist q=(zombielist)malloc(sizeof(zombie));
    q->x=9;
    q->y=y;
    q->id=id;
    q->iseat=false;
    q->speed=speed;
    q->live=live;
    q->next=p->next;
    p->next=q;
    return 1;
}
/*Delete pealink*/  int pdel(pealist head,int i){
    int j=1;
    pealist p=head->next,q;
    while(j<i&&p){
        q=p;
        p=p->next;
        j++;
    }
    cur(2*p->x+3,p->y+7);
    if(gc[2*int(p->x+0.5)][2*p->y])srgb(0,192,0,1);
    else srgb(0,96,0,1);
    cout<<sq;
    if(!p) return 0;
    q->next=p->next;
    free(p);
    return 1;
}
/*Delete zombielink*/  int zdel(zombielist head,int i){
    int j=1;
    zombielist p=head->next,q;
    while(j<i&&p){
        q=p;
        p=p->next;
        j++;
    }
    //cur (2 * p->x + 3, p->y + 7);
    //if (gc[2 * int (p->x + 0.5)][2 * p->y])srgb (0, 192, 0, 1);
    //else srgb (0, 96, 0, 1);
    //cout << sq;
    if(!p) return 0;
    q->next=p->next;
    free(p);
    return 1;
}
/*peaLinklist size*/int plsize(pealist head){
    int i=0;
    pealist p=head->next;
    while(p!=nullptr){
        p=p->next;
        i++;
    }
    return i;
}
/*Get and print bullet pos*/void blistp(pea* head){
    pea* p=head->next;
    while(p!=nullptr){
        cout<<"X:"<<p->x<<"Y:"<<p->y<<endl;
        p=p->next;
    }
    cout<<""<<endl;
}
/*About*/void developer(float x,float y){
    cur(x*2,y);
    cout<<"B";
    Sleep(50);
    cout<<"y";
    Sleep(50);
    cout<<"_";
    Sleep(50);
    cout<<"M";
    Sleep(50);
    cout<<"I";
    Sleep(50);
    cout<<"N";
    Sleep(50);
    cout<<"E";
    Sleep(50);
    cout<<"C";
    Sleep(50);
    cout<<"R";
    Sleep(50);
    cout<<"A";
    Sleep(50);
    cout<<"F";
    Sleep(50);
    cout<<"T";
    Sleep(50);
    cout<<"0";
    Sleep(50);
    cout<<"X";
    Sleep(50);
    for(int i=0; i<6; i++){
        cout<<"0";
        Sleep(50);
    }
}
/*Game logo*/void logo(){
    srgb(0,0,0,1);
    for(int i=7; i>0; i--){
        cur(3,i+5);
        cout<<sq;
        Sleep(25);
    }
    cur(3,5);
    for(int i=0; i<4; i++){
        cout<<sq;
        Sleep(25);
    }
    cur(7,6);
    cout<<sq;
    for(int i=0; i<3; i++){
        cur(6-i,7);
        cout<<sq;
        Sleep(25);
    }
    for(int i=0; i<3; i++){
        cur(9,8+i);
        cout<<sq;
        Sleep(25);
    }
    cur(10,11);
    cout<<sq;
    Sleep(25);
    cur(11,12);
    cout<<sq;
    Sleep(25);
    cur(12,11);
    cout<<sq;
    Sleep(25);
    for(int i=0; i<3; i++){
        cur(13,10-i);
        cout<<sq;
        Sleep(25);
    }
    cur(15,8);
    for(int i=0; i<5; i++){
        cout<<sq;
        Sleep(25);
    }
    cur(18,9);
    cout<<sq;
    cur(17,10);
    cout<<sq;
    cur(16,11);
    cout<<sq;
    cur(15,12);
    for(int i=0; i<5; i++){
        cout<<sq;
        Sleep(25);
    }
    srgb(0,0,0,2);
    developer(3.5,14);
    Sleep(1000);
    srgb(255,255,255,1);
    for(int i=7; i>0; i--){
        cur(3,i+5);
        cout<<sq;
        Sleep(25);
    }
    cur(3,5);
    for(int i=0; i<4; i++){
        cout<<sq;
        Sleep(25);
    }
    cur(7,6);
    cout<<sq;
    for(int i=0; i<3; i++){
        cur(6-i,7);
        cout<<sq;
        Sleep(25);
    }
    for(int i=0; i<3; i++){
        cur(9,8+i);
        cout<<sq;
        Sleep(25);
    }
    cur(10,11);
    cout<<sq;
    Sleep(25);
    cur(11,12);
    cout<<sq;
    Sleep(25);
    cur(12,11);
    cout<<sq;
    Sleep(25);
    for(int i=0; i<3; i++){
        cur(13,10-i);
        cout<<sq;
        Sleep(25);
    }
    cur(15,8);
    for(int i=0; i<5; i++){
        cout<<sq;
        Sleep(25);
    }
    cur(18,9);
    cout<<sq;
    cur(17,10);
    cout<<sq;
    cur(16,11);
    cout<<sq;
    cur(15,12);
    for(int i=0; i<5; i++){
        cout<<sq;
        Sleep(25);
    }
    srgb(255,255,255,1);
    developer(3.5,14);
}
/*Load*/void load(){
    logo();
}
/*Game bgm player*/void bgm(short id/**/){
    int mode;
    string a="0x0001";
    if(id==-1)PlaySound(NULL,NULL,SND_FILENAME|SND_ASYNC);
    if(id==0)PlaySound(TEXT("crazy_dave.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
    if(id==1)PlaySound(TEXT("evillaugh.wav"),NULL,SND_FILENAME|SND_ASYNC);
    if(id==2)PlaySound(TEXT("choose_your_seeds.wav"),NULL,SND_FILENAME|SND_ASYNC|SND_LOOP);
}
/*Main page warnning*/int mpw(short j,short b,short s){
    if(j!=0){
        srgb(255,0,0,1);
        cur(9,10);
        for(int i=0; i<12; i++)cout<<sq;
        cur(9,11);
        for(int i=0; i<12; i++)cout<<sq;
        cur(9,12);
        for(int i=0; i<12; i++)cout<<sq;
        cur(9,13);
        for(int i=0; i<12; i++)cout<<sq;
        cur(9,14);
        for(int i=0; i<12; i++)cout<<sq;
        cur(9,15);
        for(int i=0; i<12; i++)cout<<sq;
        srgb(0,255,255,2);
        cur(12.5,10);
        cout<<"Warning!";
        cur(12,12);
        cout<<"Not Devlop.";
        cur(13,14);
        srgb(0,255,255,1);
        for(int i=0; i<3; i++)cout<<sq;
        srgb(255,0,0,2);
        cur(14,14);
        cout<<"OK";
        Sleep(100);
        POINT p=wm(),w;
        p.x=0;
        p.y=0;
        while(1){
            w=wm();
            if((w.x>=26&&w.x<32)&&w.y==14){
                cur(13,14);
                srgb(255,255,0,1);
                cout<<sq;
                cur(15,14);
                cout<<sq;
                cur(14,14);
                srgb(0,0,255,2);
                cout<<"OK";
                if(key(VK_LBUTTON)){
                    break;
                }
            }
            else{
                cur(13,14);
                srgb(0,255,255,1);
                cout<<sq;
                cur(15,14);
                cout<<sq;
                srgb(255,0,0,2);
                cur(14,14);
                cout<<"OK";
            }
        }
        cls();
        srgb(0,0,0,2);
        cur(12,10);
        cout<<"Pvz Cmd ";
        Sleep(75);
        cur(12,11);
        cout<<"Main Page";
        Sleep(75);
        cur(12,12);
        cout<<"1.Nomal["<<bigstage<<'-'<<smallstage<<']';
        Sleep(75);
        cur(12,13);
        cout<<"2.Mini Game";
        Sleep(75);
        cur(12,14);
        cout<<"3.IQ Game";
        Sleep(75);
        cur(12,15);
        cout<<"4.Suvial Mode";
        Sleep(75);
        srgb(0,255,0,1);
        cur(10,8);
        for(int i=0; i<9; i++){
            cout<<sq;
            Sleep(25);
        }
        for(int i=0; i<9; i++){
            cur(19,i+8);
            cout<<sq;
            Sleep(25);
        }
        for(int i=9; i>0; i--){
            cur(i+10,17);
            cout<<sq;
            Sleep(25);
        }
        for(int i=9; i>0; i--){
            cur(10,i+8);
            cout<<sq;
            Sleep(25);
        }
        cur(10,8);
        srgb(255,0,255,2);
        cout<<"Welcome,"<<username<<"!";
        return 0;
    }
    else{
        bgm (1);
        for(int i=0; i<40; i++){
            if(i%2==0){
                srgb(0,255,0,1);
            }
            else{
                srgb(255,0,0,1);
            }
            cur(10,8);
            for(int i=0; i<9; i++){
                cout<<sq;
            }
            for(int i=0; i<9; i++){
                cur(19,i+8);
                cout<<sq;
            }
            for(int i=9; i>0; i--){
                cur(i+10,17);
                cout<<sq;
            }
            for(int i=9; i>0; i--){
                cur(10,i+8);
                cout<<sq;
            }
            Sleep(90);
        }
        nomal(b,s);
        return 1;
    }
}
/*Main page*/int mp(short bigstage,short smallstage,bool clear,string username){
    //bgm (0);
    int u=-1;
    cls();
    srgb(0,0,0,2);
    cur(12,10);
    cout<<"Pvz Cmd ";
    Sleep(75);
    cur(12,11);
    cout<<"Main Page";
    Sleep(75);
    cur(12,12);
    cout<<"1.Nomal["<<bigstage<<'-'<<smallstage<<']';
    Sleep(75);
    cur(12,13);
    cout<<"2.Mini Game";
    Sleep(75);
    cur(12,14);
    cout<<"3.IQ Game";
    Sleep(75);
    cur(12,15);
    cout<<"4.Suvial Mode";
    Sleep(75);
    srgb(0,255,0,1);
    cur(10,8);
    for(int i=0; i<9; i++){
        cout<<sq;
        Sleep(25);
    }
    for(int i=0; i<9; i++){
        cur(19,i+8);
        cout<<sq;
        Sleep(25);
    }
    for(int i=9; i>0; i--){
        cur(i+10,17);
        cout<<sq;
        Sleep(25);
    }
    for(int i=9; i>0; i--){
        cur(10,i+8);
        cout<<sq;
        Sleep(25);
    }
    cur(10,8);
    srgb(255,0,255,2);
    cout<<"Welcome,"<<username<<"!";
    bool t=0;
    POINT p=wm(),w;
    p.x=0;
    p.y=0;
    while(1){
        w=wm();
        if(p.x/2!=w.x/2||p.y!=w.y){
            if(key(VK_LBUTTON)){
                if(u!=-1){
                    if(!t){
                        int l=mpw(u,bigstage,smallstage);
                        if(l!=0){
                            return u;
                        }
                        u=-1;
                    }
                    t=!t;
                }
            }
        }
        if(w.x>=24&&w.x<=36){
            if(w.y==12){
                u=0;
                cur(12,12);
                srgb(255,255,255,2);
                cout<<"1.Nomal["<<bigstage<<'-'<<smallstage<<']';
                cur(12,13);
                srgb(0,0,0,2);
                cout<<"2.Mini Game  ";
                cur(12,14);
                cout<<"3.IQ Game    ";
                cur(12,15);
                cout<<"4.Suvial Mode";
            }
            else if(w.y==13){
                u=1;
                cur(12,12);
                srgb(0,0,0,2);
                cout<<"1.Nomal["<<bigstage<<'-'<<smallstage<<']';
                cur(12,13);
                srgb(255,255,255,2);
                cout<<"2.Mini Game  ";
                cur(12,14);
                srgb(0,0,0,2);
                cout<<"3.IQ Game    ";
                cur(12,15);
                cout<<"4.Suvial Mode";
            }
            else if(w.y==14){
                u=2;
                cur(12,12);
                srgb(0,0,0,2);
                cout<<"1.Nomal["<<bigstage<<'-'<<smallstage<<']';
                cur(12,13);
                cout<<"2.Mini Game  ";
                cur(12,14);
                srgb(255,255,255,2);
                cout<<"3.IQ Game    ";
                cur(12,15);
                srgb(0,0,0,2);
                cout<<"4.Suvial Mode";
            }
            else if(w.y==15){
                u=3;
                cur(12,12);
                srgb(0,0,0,2);
                cout<<"1.Nomal["<<bigstage<<'-'<<smallstage<<']';
                cur(12,13);
                cout<<"2.Mini Game  ";
                cur(12,14);
                cout<<"3.IQ Game    ";
                cur(12,15);
                srgb(255,255,255,2);
                cout<<"4.Suvial Mode";
            }
            else{
                u=-1;
                cur(12,12);
                srgb(0,0,0,2);
                cout<<"1.Nomal["<<bigstage<<'-'<<smallstage<<']';
                cur(12,13);
                cout<<"2.Mini Game  ";
                cur(12,14);
                cout<<"3.IQ Game    ";
                cur(12,15);
                cout<<"4.Suvial Mode";
            }
        }
        else{
            u=-1;
            cur(12,12);
            srgb(0,0,0,2);
            cout<<"1.Nomal["<<bigstage<<'-'<<smallstage<<']';
            cur(12,13);
            cout<<"2.Mini Game  ";
            cur(12,14);
            cout<<"3.IQ Game    ";
            cur(12,15);
            cout<<"4.Suvial Mode";

        }
    }
}
/*House and map set*/void oland(bool B){
    int n=0,v=0,o=0;
    if(B){
        n=18;
        v=6;
        o=15;
    }
    else{
        n=15;
        v=9;
        o=16;
    }
    for(int i=0; i<n+2; i++){
        cur(0,v+i-1);
        srgb(185,87,50,1);
        cout<<sq;
        srgb(243,228,195,1);
        cout<<sq<<sq<<sq<<sq<<sq<<sq;
        srgb(100,100,100,1);
        cout<<sq;
        cur(27,v+i-1);
        srgb(255,255,255,2);
        //cout << "l";
        Sleep(st);
    }
    rgbpp(255,0,0,243,228,195);
    cur(1,o-1);
    Sleep(st);
    cout<<"DOOR"<<"DOOR"<<"DOOR";
    cur(1,o);
    Sleep(st);
    cout<<"DOOR"<<"DOOR"<<"DOOR";
    cur(1,o+1);
    Sleep(st);
    cout<<"DOOR"<<"DOOR"<<"DOOR";
    cur(1,o+2);
    Sleep(st);
    cout<<"DOOR"<<"DOOR"<<"DOOR";
    //Sleep(50);
    //srgb(200, 200, 200, 1);
    //cout << sq;
    //Sleep(50);
    //cur(1, o - 1);
    //cout << sq;
    //Sleep(50);
    //srgb(128, 128, 255, 1);
    //cout << sq;
    cur(8,v-1);
    rgbpp(200,130,80,0,100,0);
    for(int i=0; i<21; i++){
        cout<<"╦╦";
    }
    cur(8,v+n);
    for(int i=0; i<21; i++){
        cout<<"╦╦";
    }
    for(int i=0; i<n; i++){
        cur(8,i+v);
        for(int j=0; j<21; j++){
            if(gc[j][i]){
                srgb(0,96,0,1);
            }
            else{
                srgb(0,192,0,1);
            }
            cout<<sq;
        }
        Sleep(st);
    }
}
/*Print Plant*/void pp(int id,bool flash){
}
/*Print Zombie*/void zp(zombie* head){
    zombie* p=head->next;
    int i=0,y=0;
    while(p!=nullptr&&p->next!=nullptr){
        if(0){
            int y=p->y;
            zdel(head,i);
        }
        else{
            cur(p->x*2+1,3*p->y+1);
            if(!gc[int(p->x)][p->y])rgbpp(0,255,0,0,192,0);
            else rgbpp(0,255,0,0,96,0);
            cout<<sq;
            cur(p->x*2+2,3*p->y+1);
            if(gc[int(p->x)+1][p->y])srgb(0,192,0,1);
            else srgb(0,96,0,1);
            cout<<sq;
            p->oldx=p->x;
            p->x-=p->speed;
            p=p->next;
        }
        cur(0,0);
        srgb(255,255,255,2);
        i++;
    }
}
/*Print bullet*/void bp(pea* head){
    pea* p=head->next;
    int i=0,y=0;
    while(p!=nullptr&&p->next!=nullptr){
        if(p->x>=9.5){
            int y=p->y;
            pdel(head,i);
        }
        else{
            cur(2*p->x+8,3*p->y+7);
            if(!gc[2*int(p->x)][3*p->y])rgbpp(0,255,0,0,192,0);
            else rgbpp(0,255,0,0,96,0);
            cout<<"●";
            cur(2*p->x+9,3*p->y+7);
            if(gc[2*int(p->x+0.5)][3*p->y])srgb(0,192,0,1);
            else srgb(0,96,0,1);
            cout<<sq;
            p->oldx=p->x;
            p->x+=0.5;
            p=p->next;
        }
        cur(23,y+7);
        srgb(255,255,255,2);
        i++;
    }
}
/*Nomal game mode*/void nomal(int b,int s){
    bgm(2);
    cls();
    cur(13,25);
    srgb(0,0,0,2);
    cout<<"["<<b<<"-"<<s<<"]";
    cyspm(1);
    bgm(0);
    cls();
    mp(b,s,clear,username);
}
/*Choose your seeds page and move*/int cyspm(bool z){
    oland(z);
    Sleep(1500);
    int n=0,v=0,o=0;
    if(z){
        n=18;
        v=6;
        o=13;
    }
    else{
        n=15;
        v=9;
        o=14;
    }
    srgb(255,255,255,1);
    for(int i=0; i<10; i++){
        move(0,0,28,24,-1,0);
        Sleep(100);
    }
    //cys();
    Sleep(1000);
    for(int i=0; i<9; i++){
        move(-1,0,28,24,0,0);
        rgbpp(200,130,80,0,100,0);
        cur(0,v-1);
        cout<<"╦╦";
        cur(0,v+n);
        cout<<"╦╦";
        for(int j=0; j<n; j++){
            cur(0,j+v);
            if(gc[13-i][j]){
                srgb(0,96,0,1);
            }
            else{
                srgb(0,192,0,1);
            }
            cout<<sq;
            srgb(255,255,255,1);
        }
        Sleep(100);
    }
    srgb(128,128,128,1);
    for(int i=0; i<n+2; i++){
        cur(0.5,v+i-1);
        cout<<" ";
    }
    srgb(255,255,255,1);
    move(0,0,28,24,0,0);
    srgb(128,128,128,1);
    for(int i=0; i<n+2; i++){
        cur(0,v+i-1);
        cout<<sq;
    }
    /*
    for (int i = 0; i < 8; i++) {
        Sleep(100);
    }
    */
    Sleep(5000);
    return 0;
}
/*Main function*/int main(){
    bgm(0);//Game bgm set
    ws();//Window Set
    gcs();//Grass color data set
    freopen("data.txt","r",stdin);//File input by "data.txt"
    pea* ph=pinit();//Link init
    zombie* zh=zinit();//Link init
    cin>>clear>>bigstage>>smallstage>>diamond>>coin>>username;//Input user data
    cls();
    logo();
    //cyspm(1);
    while(1){
        /*
        w = wm();
        if (p.x / 2 != w.x / 2 || p.y != w.y) {
            cnt++;
            cur(p.x / 2, p.y);
            srgb(0, 0, 0, 1);
            cout << sq;
            p = w;
            cur(w.x / 2, w.y);
            srgb(255, 255, 255, 1);
            cout << sq;
            cur(0, 0);
            srgb(0, 0, 0, 2);
            cout << p.x << " " << p.y<<" "<<cnt<<"     ";
        }
        */
        /*zhin(zh,2,0,0.2,1000);
        zhin(zh,3,0,0.2,1000);
        for(int i=0; i<20; i++){
            zp(zh);
            Sleep(100);
        }
        */
        mp(bigstage, smallstage, 0, username);
        /*
        hin(head, 1, 0);
        for (int i = 0; i < 3;i++) {
           bp(head);
           cur(0, 21);
           srgb(255, 255, 255, 2);
           cout << "pea:" << lsize(head) << "  ";
           Sleep(1000);
        }
        */
    }
    cout<<"1";
    //cls();
    //logo();//Main logo
    //while(1) {
    //    mp(bigstage, smallstage, clear, username);//mainpage test
    //}
}