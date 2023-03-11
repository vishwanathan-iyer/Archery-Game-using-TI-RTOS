#define ON    1
#define OFF   0
#define GLCD_LEFT    0
#define GLCD_RIGHT   1
#define GLCD_WIDTH   128
#define GLCD_HEIGHT  64
#define BLACK    1
#define WHITE   0
#define FILL    1
#define FONT5				1
#define FONT5_1				2
#define FONT_WIDTH8			8
#define FONT_WIDTH5			6
#define TARGETX_INIT  88

//----------------------------------------
// Prototypes
//----------------------------------------
void GLCD_init(unsigned char);
void glcd_fillScreen(unsigned char);
void glcd_writeData(unsigned char, unsigned char);
void GLCD_GoTo(unsigned char, unsigned char);
void glcd_writeCmd(unsigned char, unsigned char);
void GLCD_ReadStatus(unsigned char);
void GLCD_EnableController(unsigned char);
void GLCD_DisableController(unsigned char);
unsigned char glcd_readByte(unsigned char side);
void DrawBow(signed char x,signed char y);
void DrawArrow(signed char x,signed char y );
void DrawTarget(signed char x,signed char y );
void glcd_line(unsigned char, unsigned char, unsigned char, unsigned char, unsigned char);
void glcd_pixel(unsigned char x, unsigned char y, unsigned char color);
void glcd_rect(unsigned char x1, unsigned char y1, unsigned char x2, unsigned char y2, unsigned char fill, unsigned char color);
void draw_bow(unsigned char c,unsigned char r);
void UARTSend(char *pui8Buffer);
void glcd_WriteByte(unsigned char x,unsigned char y,unsigned char val);
void GLCD_WriteString(unsigned char x, unsigned char y,unsigned char*stringToWrite,unsigned char width,unsigned char color);
void lcd_wr_char(unsigned char a,unsigned char x, unsigned char y);
void lcdInit(void);
void UpdateTarget();
void UpdateBow();
void UpdateArrow();
void GLCD_Write_Ver(unsigned char x, unsigned char y, unsigned int value, int digits);
void shootArrow();
void showScore(unsigned char *msg);

