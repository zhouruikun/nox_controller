 #ifndef _keydrv24_h
#define _keydrv24_h

#ifdef   keydrv24_globals
#define  keydrv24_ext
#else
#define  keydrv24_ext  extern
#endif

/*------------------*
*   动 作 宏 定 义  *
*------------------*/
/*------------------*
    *   24按键  *
*------------------*/

#define pageup	 0x13 //上页
#define pagedown 0x12 //下页
//#define left     0x10 //左
//#define right    0x11 //右
#define enter    0x0b //确定
#define esc      0x0a //返回

#define kesc     0x0a
#define kenter   0x0b
#define kf1      0x0c
#define kf2      0x0d
#define kf3      0x0e
#define kf4      0x0f
#define kleft    0x10
#define kright   0x11
#define kpattern 0x14
#define kfeeder  0x15
#define kset     0x16
#define kxin     0x17
#define bu       0x0




keydrv24_ext void init_keyboard(void);
keydrv24_ext unsigned char get_key(void);


#endif

