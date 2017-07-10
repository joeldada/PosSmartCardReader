#define VCC PORTD.F1
#define RST PORTD.F0
#define VCC1 PORTD.F2
#define RST1 PORTD.F3
#define CLK_EN PORTC.F4
#define LED PORTB.F7
#define ON 1
#define OFF 0

char uart_rd;
 char error, byte_read;
 unsigned char read_count = 0;

 unsigned char atr[66] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
unsigned int count;
unsigned char i = 0;

//unsigned char uart_send1[] = {0x00,0xa4,0x04,0x00,0x08};
//unsigned char uart_send1[] = {0x00,0xa4,0x04,0x00,0x08,0xa0,0x00,0x00,0x03,0x33,0x01,0x01,0x02};
unsigned char uart_send1[] = {0x00,0xa4,0x04,0x00,0x08,0xa0,0x34,0x10,0x03,0x33,0x01,0x01,0x02};
//unsigned char uart_send1[] = {0x00,0xa4,0x00,0x00,0x02,0x7f,0x20};
unsigned char uart_send2[] = {0xa0,0x00,0x00,0x03,0x33,0x01,0x01,0x02}  ;
 unsigned char uart_send[] = {0xff,0x10,0x11,0xfe};

void main() {
  TRISD.F2 = 0;
  TRISD.F3 = 0;
  TRISD.F1 = 0;
  TRISD.F0 = 0;

  TRISC.F4 = 0;
  TRISB.F7 = 0;

RST = OFF;
VCC = OFF;
RST1 = OFF;
VCC1 = OFF;

CLK_EN = OFF;

 UART1_Init(9600);               // Initialize UART module at 9600 bps
  Delay_ms(100);                  // Wait for UART module to stabilize
   error = Soft_UART_Init(&PORTD, 5, 4, 9600, 0); // Initialize Soft UART at 14400 bps
  if (error > 0) {
    LED = ON;
    while(1) ;                            // Stop program
  }
  Delay_ms(100);

 for (i = 'z'; i >= 'A'; i--) {          // Send bytes from 'z' downto 'A'
    Soft_UART_Write(i);
    Delay_ms(50);
  }

  for (i = 0; i < 66; i++) {
   atr[i] = 0xff;
  }
Soft_UART_Write(10);
Soft_UART_Write(13);

 LED = ON;
     delay_ms(2000);
     LED = OFF;
     delay_ms(2000);
     LED = ON;
     delay_ms(1000);
     LED = OFF;
     delay_ms(3000);

VCC = ON;
VCC1 = ON;

delay_ms(10);
CLK_EN = ON;
delay_us(11200);
RST = ON;
RST1 = ON;

delay_us(90);

 read_count = 0;

    for (count = 1; count < 11175; count++) {

     if (UART1_Data_Ready()) {
      atr[read_count] = UART1_Read();
      read_count++;
      }
      delay_us(1);
    }
    
    

 read_count = read_count + 3;
 for (i= 0; i < 13; i++) {
  UART1_Write(uart_send1[i]);
  delay_us(1251);
 }


    for (count = 1; count < 11175; count++) {

     if (UART1_Data_Ready()) {
      atr[read_count] = UART1_Read();
      read_count++;
      }
      delay_us(1);
    }


  /*
 read_count = read_count + 3;
  for (i= 0; i < 8; i++) {
  UART1_Write(uart_send2[i]);
  delay_us(1251);
 }
 
   for (count = 1; count < 11175; count++) {

     if (UART1_Data_Ready()) {
      atr[read_count] = UART1_Read();
      read_count++;
      }
      delay_us(1);
    }
*/
      RST = OFF;
    RST1 = ON;

    delay_ms(5);
CLK_EN = OFF  ;
delay_ms(5);
VCC = OFF;
VCC1 = OFF;


LED = 1;
  for (i = 0; i < 66; i++) {          // Send bytes from 'z' downto 'A'
//    Soft_UART_Write(atr[i]);
   Soft_UART_Write(atr[i]);
       //   Soft_UART_Write('#');
          delay_ms(30);

  }
}
