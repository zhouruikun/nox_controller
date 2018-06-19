#ifndef _keydrv_h
#define _keydrv_h

#ifdef   keydrv_globals
#define  keydrv_ext
#else
#define  keydrv_ext  extern
#endif

/*------------------*
*   动 作 宏 定 义  *
*------------------*/
/*------------------*
    *   24按键  *
*------------------*/
#define up	     0x12 //上
#define down	 0x13 //下
#define pageup	 0x16 //上页
#define pagedown 0x17 //下页
#define left     0x10 //左
#define right    0x11 //右
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
#define kup      0x12
#define kdown    0x13
#define kmode    0x14
#define kreset   0x15

//#define pgup     0x16
//#define pgdw     0x17 

/*------------------*
   *   21按键  *
*------------------*/
/*
#define pageup	 0x12 //上
#define pagedown	 0x11 //下
#define left     0x0f //左
#define right    0x10 //右
#define enter    0x0b //确定
#define esc      0x14 //返回
#define point    0x0a //点

#define kesc     0x14
#define kpoint   0x0a
#define kenter   0x0b
#define kf1      0x0c
#define kf2      0x0d
#define kf3      0x0e
#define kf4      0x13
#define kleft    0x0f
#define kright   0x10
#define kup      0x12
#define kdown    0x11
*/
keydrv_ext void init_keyboard(void);
keydrv_ext unsigned char get_key(void);


#endif

