#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))


int result,result1;
int buf[50];
int header;
int tail;
int flag;
int cc;
int arus,voltage;
void parsing()
{
    if(result=='#')
    {flag=1;cc=0;}
    else
    {
      cc++;
      buf[cc]=result;
      if(flag==1 && result=='%')
      {
 
          
        //kirim4byte(1234);
        cc=0;flag=0;
        }
      
      
      }
      
  }


ISR(USART0_RX_vect)  
{     
 result1 = UDR0;  // ke PC
 
  uart_send1(UDR0); 
   uart_send2(UDR0); 
    uart_send3(UDR0); 
//uart_send(UDR0); 
}


ISR(USART1_RX_vect)  
{     
 result = UDR1;
 //parsing();
// uart_send(result); 
}


ISR(USART2_RX_vect)  
{     
 result = UDR1;
 //parsing();
 //uart_send(result); 
}


ISR(USART3_RX_vect)  
{     
 result = UDR1;
 //parsing();
 uart_send(result); 
}



void setup() {
  // put your setup code here, to run once:
serial_initial();
serial_initial1();
//serial_initial2();
serial_initial3();
}

void loop() {


//uart_send('B');

uart_send3('A');
//uart_send2('A');
delay(100);


  

}

void serial_initial()
{  
  sbi(UCSR0A, U2X0);
  sbi(UCSR0B, RXCIE0);
   
  sbi(UCSR0B, RXEN0);
  sbi(UCSR0B, TXEN0);
   
  UCSR0C = B00000110;
  UBRR0H = B0;
   
//  UBRR0L = B00010000;  // tak set bUDRATE 115200 ikiy
  UBRR0L = B11001111;  // 9600
//UBRR0L = 33; // 57600

}


void serial_initial2()
{  
  sbi(UCSR2A, U2X2);
  sbi(UCSR2B, RXCIE2);
   
  sbi(UCSR2B, RXEN2);
  sbi(UCSR2B, TXEN2);
   
  UCSR2C = B00000110;
  UBRR2H = B0;
   
//  UBRR0L = B00010000;  // tak set bUDRATE 115200 ikiy
  UBRR2L = B11001111;  // 9600
//UBRR0L = 33; // 57600

}


void serial_initial3()
{  
  sbi(UCSR3A, U2X3);
  sbi(UCSR3B, RXCIE3);
   
  sbi(UCSR3B, RXEN3);
  sbi(UCSR3B, TXEN3);
   
  UCSR3C = B00000110;
  UBRR3H = B0;
   
//  UBRR0L = B00010000;  // tak set bUDRATE 115200 ikiy
  UBRR3L = B11001111;  // 9600
//UBRR0L = 33; // 57600

}


void serial_initial1()
{  
  sbi(UCSR1A, U2X1);
  sbi(UCSR1B, RXCIE1);
   
  sbi(UCSR1B, RXEN1);
  sbi(UCSR1B, TXEN1);
   
  UCSR1C = B00000110;
  UBRR1H = B0;
   
//  UBRR0L = B00010000;  // tak set bUDRATE 115200 ikiy
  UBRR1L = B11001111;  // 9600
//UBRR0L = 33; // 57600

}

void uart_send(unsigned char dat) { 
  while(! (UCSR0A & ( 1 << UDRE0))  );  
  UDR0 = dat;                          
}


void uart_send1(unsigned char dat) { 
  while(! (UCSR1A & ( 1 << UDRE1))  );  
  UDR1 = dat;                          
}

void uart_send2(unsigned char dat) { 
  while(! (UCSR2A & ( 1 << UDRE2))  );  
  UDR2 = dat;                          
}

void uart_send3(unsigned char dat) { 
  while(! (UCSR3A & ( 1 << UDRE3))  );  
  UDR3 = dat;                          
}



void kirim4byte(int xxxx)
{
 uart_send((xxxx/1000)+48);
  uart_send(((xxxx/100)%10)+48);
  uart_send(((xxxx/10)%10)+48);
  uart_send((xxxx/1)%10+48);


}
