//#######    LCD driver for OAKS Multi I/O Board	#######
//#######             M16C/62P CPU					#######
//#######             version 1.0					#######
//#######           	By KH				        #######

typedef unsigned char uint8_t;
/*----------------------------------------------------------*/
/* 関数名	:InitLCD()										*/
/* 機能		:LCD初期化									    */
/*----------------------------------------------------------*/
void InitLCD(void);
void Init_IO(void);
void Init_TIMER(void);

/*------------------------------------------------------------*/
/* 関数名	:DisplayLCD1L(line, 文字列ポインタ)			 	  */
/* 機能		:1行分文字表示	line=0 1行目、line=1 2行目	      */
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
