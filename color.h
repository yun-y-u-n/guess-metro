#include<cstdio>
#include<windows.h>

void rgb_init(){
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

void Color(int wr,int wg,int wb,int br,int bg,int bb){
	printf("\033[38;2;%d;%d;%dm\033[48;2;%d;%d;%dm",wr,wg,wb,br,bg,bb);
}
void Color(int r,int g,int b,int c=0){
	printf("\033[%d8;2;%d;%d;%dm",3+c,r,g,b);
}

void cEndl(){
	
}

#define LIGHTPINK               255, 182, 193      // 浅粉红  
#define PINK                    255, 192, 203      // 粉红  
#define CRIMSON                 220,  20,  60      // 猩红 (深红  
#define LAVENDERBLUSH           255, 240, 245      // 淡紫红  
#define PALEVIOLETRED           219, 112, 147      // 弱紫罗兰红  
#define HOTPINK                 255, 105, 180      // 热情的粉红  
#define DEEPPINK                255,  20, 147      // 深粉红  
#define MEDIUMVIOLETRED         199,  21, 133      // 中紫罗兰红  
#define ORCHID                  218, 112, 214      // 兰花紫  
#define THISTLE                 216, 191, 216      // 蓟  
#define PLUM                    221, 160, 221      // 李子紫  
#define VIOLET                  238, 130, 238      // 紫罗兰  
#define MAGENTA                 255,   0, 255      // 洋红 (品红 玫瑰红)  
#define FUCHSIA                 255,   0, 255      // 灯笼海棠(紫红色) 
#define DARKMAGENTA             139,   0, 139      // 深洋红  
#define PURPLE                  128,   0, 128      // 紫色  
#define MEDIUMORCHID            186,  85, 211      // 中兰花紫  
#define DARKVIOLET              148,   0, 211      // 暗紫罗兰  
#define DARKORCHID              153,  50, 204      // 暗兰花紫  
#define INDIGO                   75,   0, 130      // 靛青（紫兰色） 
#define BLUEVIOLET              138,  43, 226      // 蓝紫罗兰  
#define MEDIUMPURPLE            147, 112, 219      // 中紫色  
#define MEDIUMSLATEBLUE         123, 104, 238      // 中板岩蓝  
#define SLATEBLUE               106,  90, 205      // 板岩蓝  
#define DARKSLATEBLUE            72,  61, 139      // 暗板岩蓝  
#define LAVENDER                230, 230, 250      // 熏衣草淡紫  
#define GHOSTWHITE              248, 248, 255      // 幽灵白  
#define BLUE                      0,   0, 255      // 纯蓝  
#define MEDIUMBLUE                0,   0, 205      // 中蓝色  
#define MIDNIGHTBLUE             25,  25, 112      // 午夜蓝  
#define DARKBLUE                  0,   0, 139      // 暗蓝色  
#define NAVY                      0,   0, 128      // 海军蓝  
#define ROYALBLUE                65, 105, 225      // 皇家蓝 (宝蓝） 
#define CORNFLOWERBLUE          100, 149, 237      // 矢车菊蓝  
#define LIGHTSTEELBLUE          176, 196, 222      // 亮钢蓝  
#define LIGHTSLATEGRAY          119, 136, 153      // 亮石板灰  
#define SLATEGRAY               112, 128, 144      // 石板灰  
#define DODGERBLUE               30, 144, 255      // 道奇蓝  
#define ALICEBLUE               240, 248, 255      // 爱丽丝蓝  
#define STEELBLUE                70, 130, 180      // 钢蓝 (铁青） 
#define LIGHTSKYBLUE            135, 206, 250      // 亮天蓝色  
#define SKYBLUE                 135, 206, 235      // 天蓝色  
#define DEEPSKYBLUE               0, 191, 255      // 深天蓝  
#define LIGHTBLUE               173, 216, 230      // 亮蓝  
#define POWDERBLUE              176, 224, 230      // 火药青  
#define CADETBLUE                95, 158, 160      // 军服蓝  
#define AZURE                   240, 255, 255      // 蔚蓝色  
#define LIGHTCYAN               224, 255, 255      // 淡青色  
#define PALETURQUOISE           175, 238, 238      // 弱绿宝石  
#define CYAN                      0, 255, 255      // 青色  
#define AQUA                      0, 255, 255      // 水色  
#define DARKTURQUOISE             0, 206, 209      // 暗绿宝石  
#define DARKSLATEGRAY            47,  79,  79      // 暗石板灰  
#define DARKCYAN                  0, 139, 139      // 暗青色  
#define TEAL                      0, 128, 128      // 水鸭色  
#define MEDIUMTURQUOISE          72, 209, 204      // 中绿宝石  
#define LIGHTSEAGREEN            32, 178, 170      // 浅海洋绿  
#define TURQUOISE                64, 224, 208      // 绿宝石  
#define AQUAMARINE              127, 255, 212      // 宝石碧绿  
#define MEDIUMAQUAMARINE        102, 205, 170      // 中宝石碧绿  
#define MEDIUMSPRINGGREEN         0, 250, 154      // 中春绿色  
#define MINTCREAM               245, 255, 250      // 薄荷奶油  
#define SPRINGGREEN               0, 255, 127      // 春绿色  
#define MEDIUMSEAGREEN           60, 179, 113      // 中海洋绿  
#define SEAGREEN                 46, 139,  87      // 海洋绿  
#define HONEYDEW                240, 255, 240      // 蜜瓜色  
#define LIGHTGREEN              144, 238, 144      // 淡绿色  
#define PALEGREEN               152, 251, 152      // 弱绿色  
#define DARKSEAGREEN            143, 188, 143      // 暗海洋绿  
#define LIMEGREEN                50, 205,  50      // 闪光深绿  
#define LIME                      0, 255,   0      // 闪光绿  
#define FORESTGREEN              34, 139,  34      // 森林绿  
#define GREEN                     0, 128,   0      // 纯绿  
#define DARKGREEN                 0, 100,   0      // 暗绿色  
#define CHARTREUSE              127, 255,   0      // 查特酒绿 (黄绿色） 
#define LAWNGREEN               124, 252,   0      // 草坪绿  
#define GREENYELLOW             173, 255,  47      // 绿黄色  
#define DARKOLIVEGREEN           85, 107,  47      // 暗橄榄绿  
#define YELLOWGREEN             154, 205,  50      // 黄绿色  
#define OLIVEDRAB               107, 142,  35      // 橄榄褐色  
#define BEIGE                   245, 245, 220      // 米色(灰棕色）  
#define LIGHTGOLDENRODYELLOW    250, 250, 210      // 亮菊黄  
#define IVORY                   255, 255, 240      // 象牙  
#define LIGHTYELLOW             255, 255, 224      // 浅黄色  
#define YELLOW                  255, 255,   0      // 纯黄  
#define OLIVE                   128, 128,   0      // 橄榄  
#define DARKKHAKI               189, 183, 107      // 深卡叽布  
#define LEMONCHIFFON            255, 250, 205      // 柠檬绸  
#define PALEGOLDENROD           238, 232, 170      // 灰菊黄  
#define KHAKI                   240, 230, 140      // 卡叽布  
#define GOLD                    255, 215,   0      // 金色  
#define CORNSILK                255, 248, 220      // 玉米丝色  
#define GOLDENROD               218, 165,  32      // 金菊黄  
#define DARKGOLDENROD           184, 134,  11      // 暗金菊黄  
#define FLORALWHITE             255, 250, 240      // 花的白色  
#define OLDLACE                 253, 245, 230      // 旧蕾丝  
#define WHEAT                   245, 222, 179      // 小麦色  
#define MOCCASIN                255, 228, 181      // 鹿皮靴  
#define ORANGE                  255, 165,   0      // 橙色  
#define PAPAYAWHIP              255, 239, 213      // 番木瓜  
#define BLANCHEDALMOND          255, 235, 205      // 发白的杏仁色  
#define NAVAJOWHITE             255, 222, 173      // 土著白  
#define ANTIQUEWHITE            250, 235, 215      // 古董白  
#define TAN                     210, 180, 140      // 茶色  
#define BURLYWOOD               222, 184, 135      // 硬木色  
#define BISQUE                  255, 228, 196      // 陶坯黄  
#define DARKORANGE              255, 140,   0      // 深橙色  
#define LINEN                   250, 240, 230      // 亚麻布  
#define PERU                    205, 133,  63      // 秘鲁  
#define PEACHPUFF               255, 218, 185      // 桃肉色  
#define SANDYBROWN              244, 164,  96      // 沙棕色  
#define CHOCOLATE               210, 105,  30      // 巧克力  
#define SADDLEBROWN             139,  69,  19      // 马鞍棕色  
#define SEASHELL                255, 245, 238      // 海贝壳  
#define SIENNA                  160,  82,  45      // 黄土赭色  
#define LIGHTSALMON             255, 160, 122      // 浅鲑鱼肉色  
#define CORAL                   255, 127,  80      // 珊瑚  
#define ORANGERED               255,  69,   0      // 橙红色  
#define DARKSALMON              233, 150, 122      // 深鲜肉(鲑鱼色）  
#define TOMATO                  255,  99,  71      // 番茄红  
#define MISTYROSE               255, 228, 225      // 薄雾玫瑰  
#define SALMON                  250, 128, 114      // 鲜肉(鲑鱼色） 
#define SNOW                    255, 250, 250      // 雪  
#define LIGHTCORAL              240, 128, 128      // 淡珊瑚色  
#define ROSYBROWN               188, 143, 143      // 玫瑰棕色  
#define INDIANRED               205,  92,  92      // 印度红  
#define RED                     255,   0,   0      // 纯红  
#define BROWN                   165,  42,  42      // 棕色  
#define FIREBRICK               178,  34,  34      // 耐火砖  
#define DARKRED                 139,   0,   0      // 深红色  
#define MAROON                  128,   0,   0      // 栗色  
#define WHITE                   255, 255, 255      // 纯白  
#define WHITESMOKE              245, 245, 245      // 白烟  
#define GAINSBORO               220, 220, 220      // 庚斯博罗灰色  
#define LIGHTGREY               211, 211, 211      // 浅灰色  
#define SILVER                  192, 192, 192      // 银灰色  
#define DARKGRAY                169, 169, 169      // 深灰色  
#define GRAY                    128, 128, 128      // 灰色 
#define DIMGRAY                 105, 105, 105      // 暗淡的灰色  
#define BLACK                     0,   0,   0      // 纯黑  
//来自 https://blog.csdn.net/plutus_sutulp/article/details/7738455 

#define Default Color(255,255,255,0,0,0)
