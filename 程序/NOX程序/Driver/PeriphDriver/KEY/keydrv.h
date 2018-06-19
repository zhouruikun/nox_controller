#ifndef _keydrv_h
#define _keydrv_h

#ifdef   keydrv_globals
#define  keydrv_ext
#else
#define  keydrv_ext  extern
#endif

/*------------------*
*   �� �� �� �� ��  *
*------------------*/
/*------------------*
    *   24����  *
*------------------*/
#define up	     0x12 //��
#define down	 0x13 //��
#define pageup	 0x16 //��ҳ
#define pagedown 0x17 //��ҳ
#define left     0x10 //��
#define right    0x11 //��
#define enter    0x0b //ȷ��
#define esc      0x0a //����

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
   *   21����  *
*------------------*/
/*
#define pageup	 0x12 //��
#define pagedown	 0x11 //��
#define left     0x0f //��
#define right    0x10 //��
#define enter    0x0b //ȷ��
#define esc      0x14 //����
#define point    0x0a //��

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

