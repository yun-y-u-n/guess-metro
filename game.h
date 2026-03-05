#include<bits/stdc++.h>
#include<windows.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<cstdio>
#include "color.h"

#define Endl putchar('\n')
#define Space putchar(' ')
#define pb push_back
#define deb(x) cerr<<__LINE__<<":"<<#x<<"="<<(x)<<endl

#define kd(VK_NONAME) ((GetAsyncKeyState(VK_NONAME)&0x8000)?1:0)

char Getc() {
	while(_kbhit())_getch();
	return _getch();
}
void say(const std::string &text,int oversleep=100,int speed=10) {
	int l=text.size();
	for (int i=0;i<l;i++) {
		putchar(text[i]);
		if(text[i]!=0)Sleep(speed);
	}
	Sleep(oversleep);
}
char get01(int r=178,int g=34,int b=34){
	char c=Getc();
	while(c!='0'&&c!='1'){
		Color(r,g,b);
		say("输入错误！请重新输入"),Endl;
		c=Getc();
	}
	return c;
}
void Middle_Print(const std::string &text, int totalWidth) {
    int textWidth = text.length();
    int leftPadding = (totalWidth - textWidth) / 2;
    int rightPadding = totalWidth - textWidth - leftPadding;
    std::cout << std::setw(leftPadding + textWidth) << std::setfill(' ') << text;
    std::cout << std::setw(rightPadding) << std::setfill(' ') << ' ';
}
char Ins(){
	char c=Getc();
	putchar(c);
	return c;
}

int randint(int l,int r){return rand()%(r-l+1)+l;}
double randf(){return (double)rand()/RAND_MAX;}

void gotoxy(int x,int y){
	COORD pos;pos.X=x,pos.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}
void clrscr(){gotoxy(0,0);}
void Cls(){Default;system("cls");}

void HideCur(){
	CONSOLE_CURSOR_INFO cur={1,0};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cur);
}
void ShowCur(){
	CONSOLE_CURSOR_INFO cur={1,1};
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE),&cur);
}
void noedit(){
	HANDLE hStdin=GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode;
	GetConsoleMode(hStdin,&mode);
	mode&=~ENABLE_QUICK_EDIT_MODE;
	mode&=~ENABLE_INSERT_MODE;
	mode&=~ENABLE_MOUSE_INPUT;
	SetConsoleMode(hStdin,mode); 
}
std::pair<int,int> GetPos(){
    POINT pt;GetCursorPos(&pt);
	HWND h=GetForegroundWindow();
	ScreenToClient(h,&pt);
	pt.x=(pt.x-15)/19;pt.y=(pt.y-95)/37;//Win11 2520*1680 200%
//	pt.x=(pt.x-10)/12;pt.y=(pt.y-61)/23;//Win11 2048*1152 125%
//	pt.x=(pt.x-12)/14;pt.y=(pt.y-72)/28;//Win11 1920*1280 150%
	return std::make_pair(pt.y,pt.x);
}
std::pair<int,int> GetMousePos(){
    POINT pt;GetCursorPos(&pt);
	HWND h=GetForegroundWindow();
	ScreenToClient(h,&pt);
	return std::make_pair(pt.y,pt.x);
}

namespace EaDC{
	std::string Key="OPraMcdstuUW-Y9e01hNRy5kKLzXA36H7IJwbvSQ+BCgijpqDEToZ8G2FlVfmnx4";
	std::string key="279Pl+S8VWpxXa1-6EFmnjGqy3eJTLMN5CYKOBkcdHIzbfghZ4roUsti0RQDuvwA";
	std::string encode(const std::string &s){
		std::mt19937 rnd(time(0));
		shuffle(Key.begin(),Key.end(),rnd);
		std::string res="";//Key=key;
		for(int i=0;i+2<(int)s.size();i+=3){
			int x=s[i],y=s[i+1],z=s[i+2];
			int a=x>>2,b=((x&0x3)<<4)|(y>>4),c=((y&0xf)<<2)|(z>>6),d=(z&0x3f);
			res+=Key[a];res+=Key[b];res+=Key[c];res+=Key[d];
		}
		if(s.size()%3==1){
			int x=s.back();
			res+=Key[x>>2];res+=Key[(x&(0x3))<<4];res+="==";
		}
		if(s.size()%3==2){
			int x=s[s.size()-2],y=s.back();
			res+=Key[x>>2];res+=Key[((x&(0x3))<<4)|(y>>4)];res+=Key[(y&0xf)<<2];res+='=';
		}
		std::string t=Key+res;res="";
		for(int i=0;i+2<(int)t.size();i+=3){
			int x=t[i],y=t[i+1],z=t[i+2];
			int a=x>>2,b=((x&0x3)<<4)|(y>>4),c=((y&0xf)<<2)|(z>>6),d=(z&0x3f);
			res+=key[a];res+=key[b];res+=key[c];res+=key[d];
		}
		if(t.size()%3==1){
			int x=t.back();
			res+=key[x>>2];res+=key[(x&(0x3))<<4];res+="==";
		}
		if(t.size()%3==2){
			int x=t[t.size()-2],y=t.back();
			res+=key[x>>2];res+=key[((x&(0x3))<<4)|(y>>4)];res+=key[(y&0xf)<<2];res+='=';
		}
		return res;
	}
	int get[128];
	std::string decode(const std::string &s){
		if(s.size()%4)return "-1";
		std::string t="",res="";
		for(int i=0;i<128;i++)get[i]=0;
		for(int i=0;i<64;i++)get[(int)key[i]]=i;;get['=']=0;
		for(int i=0;i<(int)s.size();i+=4){
			int a=get[(int)s[i]],b=get[(int)s[i+1]],c=get[(int)s[i+2]],d=get[(int)s[i+3]];
			char x=(a<<2)|(b>>4),y=((b&0xf)<<4)|(c>>2),z=((c&0x3)<<6)|d;
			t+=x;if(s[i+2]!='=')t+=y;if(s[i+3]!='=')t+=z;
		}
		for(int i=0;i<128;i++)get[i]=0;
		for(int i=0;i<64;i++)get[(int)t[i]]=i;;t=t.substr(64);
		if(t.size()%4)return "-1";
		for(int i=0;i<(int)t.size();i+=4){
			int a=get[(int)t[i]],b=get[(int)t[i+1]],c=get[(int)t[i+2]],d=get[(int)t[i+3]];
			char x=(a<<2)|(b>>4),y=((b&0xf)<<4)|(c>>2),z=((c&0x3)<<6)|d;
			res+=x;if(t[i+2]!='=')res+=y;if(t[i+3]!='=')res+=z;
		}
		return res;
	}
}
using EaDC::encode;
using EaDC::decode;

std::vector<int> stois(const std::string &s){
	std::vector<int> res;int sum=0;
	for(int i=0;i<(int)s.size();i++){
		if(isdigit(s[i]))sum=(sum<<1)+(sum<<3)+(s[i]^48);
		else if(i&&isdigit(s[i-1]))res.emplace_back(sum),sum=0;
	}
	if(isdigit(s.back()))res.pb(sum);
	return res;
}

void WriteToClipboard(const std::string &s){
    HWND hWnd=NULL;
	OpenClipboard(hWnd);
	EmptyClipboard();
	HANDLE hHandle=GlobalAlloc(GMEM_FIXED, 10000);
	char* pData=(char*)GlobalLock(hHandle);
	strcpy(pData,s.c_str());
	SetClipboardData(CF_TEXT, hHandle);
	GlobalUnlock(hHandle);
	CloseClipboard();
}


std::string ReadFromClipboard(){
    HWND hWnd=NULL;
    OpenClipboard(hWnd);
	if(IsClipboardFormatAvailable(CF_TEXT)){
		HANDLE h=GetClipboardData(CF_TEXT);
		char* p=(char*)GlobalLock(h);
		GlobalUnlock(h);
		CloseClipboard();
		return p;
	}
	return "can't read from clipboard";
}
