#ifndef _PID_H_
#define _PID_H_


typedef struct {
	short PumpO2;  //µÿ÷∑00
	short I_PumpO2; //µÿ÷∑01
	short PumpRef;
	short I_PumpRef;
	short Ref_VPO2_Set;
	short I_PumpAux;
	short I_PumpNox;
	short Ref_VPAUX_Set;
	short Ref_VPNO2_Set;
	short PWM;
	short Temperture;
	short PID_P_AUX;
	short PID_I_AUX;
	short PID_D_AUX;
	short AUX_I_Set;
	short PID_P_REF;
	short PID_I_REF;
	short PID_D_REF;
	short Ref_I_Set;
	short PID_P_Heater;
	short PID_I_Heater;
	short PID_D_Heater;
	short Heater_Set;
	short PID_flag;
	short NOX_PPM;
	short O2PP;
	short status_on;
	short status_off;
	short NOX_ratio;
	short O2_ratio;
	short	offset_I_NOX;//(I_pump[3]*0.80566);
	short	offset_I_O2;
	short	offset_I_AUX;//(I_pump[1]*0.80566);
	short	auto_adj_th;//(I_pump[1]*0.80566);
	short	err_code;//(I_pump[1]*0.80566);
}arg_all;

void Send_TFT(void);
extern arg_all Arg_all;
void Init_PID_Arg(void);
int PID_Heater(int get_r);
int PID_AUX(int get_r);
int PID_REF(int get_r);
void Init_PID_Arg(void);
void Save_PID_Arg(void);
#endif
