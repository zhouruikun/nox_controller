
#ifndef _DAC_h
#define _DAC_h

#ifdef   DAC_globals
#define  DAC_ext
#else
#define  DAC_ext  extern
#endif

//???MCP4822??,SPI,???
#define MCP4822_SHDN_ON		0		//MCP4822	Shutdown
#define MCP4822_SHDN_OFF	1		

#define MCP4822_CH_A			0
#define MCP4822_CH_B			1		//A NOX£¬bAUX£¬cREF£¬dO2
#define MCP4822_CH_C			2
#define MCP4822_CH_D			3		//????
#define MCP4822_GATE_ON		0		//????
#define MCP4822_GATE_OFF	1		

 #define MCP48221_CS  PBout(0)
 #define MCP48221_SCK  PBout(1)
 #define MCP48221_SI  PBout(2)
 #define MCP48221_L  PBout(3)
 #define MCP48222_CS  PBout(4)
 #define MCP48222_SCK  PBout(5)
 #define MCP48222_SI  PBout(6)
 #define MCP48222_L  PBout(7)
 void MCP4822_WriteValue(u8 ch,bool gate,bool shdn,uint16 dat);
 void INIT_MCP4822(void);
 void CtrLineInit(void);
 void CtrlUpdata(void);
 
 #endif

