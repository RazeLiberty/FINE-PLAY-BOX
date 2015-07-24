//#######    LCD driver for OAKS Multi I/O Board	#######
//#######             M16C/62P CPU					#######
//#######             version 1.0					#######
//#######           	By KH				        #######

typedef unsigned char uint8_t;
/*----------------------------------------------------------*/
/* �֐���	:InitLCD()										*/
/* �@�\		:LCD������									    */
/*----------------------------------------------------------*/
void InitLCD(void);
void Init_IO(void);
void Init_TIMER(void);

/*------------------------------------------------------------*/
/* �֐���	:DisplayLCD1L(line, ������|�C���^)			 	  */
/* �@�\		:1�s�������\��	line=0 1�s�ځAline=1 2�s��	      */
/*------------------------------------------------------------*/
void DisplayLCD1L(char data,char * row);

void SetCursol(int x, int y);

void DisplayLCD1C(char c);

void DisplayLCD(char * row);




void Motor1(uint8_t);
void Motor2(uint8_t);
void Motor3(uint8_t);
void Motor4(uint8_t);



///////////////////////////////end
