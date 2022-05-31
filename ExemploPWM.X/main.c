/*=======================================================
					SENAI A. Jacob Lafer
					====================

Nome do projeto:	PWM
Versão:				1.0x
Última revisão:		01/06/2020
Cliente:			SENAI
Desenvolvimento:	Luiz Ricardo Bitencourt

Descritivo Funcional:
Teste de funcionamento de PWM controlando o brilho de uma fita de LEDs.

Outputs:
- RC1 - Saída do PWM
- RB2 - Display RS
- RB3 - Display E
- RB4-RB7 - Display Data
=========================================================*/

//=======================================================
// Bibliotecas
//=======================================================
#include <xc.h>
#include "lcd_4vias.h"
#include "pwm.h"
//======================================================

// =====================================================
// CONFIGURAÇÕES DO MICROCONTROLADOR
// =====================================================
#pragma config  FOSC    = HS
#pragma config  PLLDIV  = 1
#pragma config  CPUDIV  = OSC1_PLL2
#pragma config  USBDIV  = 1
#pragma config  BORV    = 0
#pragma config  WDTPS   = 1
#pragma config  MCLRE   = ON
#pragma config	PWRT=ON, LVP=OFF, IESO=OFF, WDT=OFF, PBADEN=OFF, BOR=OFF
#pragma config  CCP2MX=ON, LPT1OSC=OFF, ICPRT=OFF, XINST=OFF, VREGEN=OFF
#pragma config  CP0=OFF, CP1=OFF, CP2=OFF, CP3=OFF, CPB=OFF, CPD=OFF, WRTD = OFF
#pragma config  WRT0=OFF, WRT1=OFF, WRT2=OFF, WRT3=OFF, WRTC = OFF, WRTB = OFF
#pragma config  EBTR0=OFF, EBTR1=OFF, EBTR2=OFF, EBTR3=OFF, EBTRB=OFF
// =====================================================

//======================================================
// Definições de Hardware
//======================================================
#define _XTAL_FREQ  4000000         // Valor constante usado nas funções de delay
//======================================================

//======================================================
// Programa Principal
//======================================================
void main (void){
	// -------------------------------------------------
	// Declaração de variáveis locais
	// -------------------------------------------------
    int    Brilho = 0;
    char   vaivolta = 0;
	// -------------------------------------------------

	// -------------------------------------------------
	// Configurações iniciais
	// -------------------------------------------------
    TRISB = 0b00000011;             // Port B, do RB0 até RB7
	INTCON2bits.NOT_RBPU = 1;       // Desliga os pull-ups internos do PORT B
    // -------------------------------------------------
    
    // -------------------------------------------------
    // INICIALIZAÇÃO DE FUNÇÕES
    // -------------------------------------------------
	IniciaLCD();                // Inicializa Display LCD
    LimpaLCD();                 // Limpa Display
	Inicializa_PWM(255);		// Inicializa PWM com período de 52,1us
	// -------------------------------------------------

	// -------------------------------------------------
	// Programa principal
	// -------------------------------------------------
	PosicionaLCD(1,1);
    StringLCD("   SENAI  118   ");
	PosicionaLCD(2,1);
    StringLCD(" PWM Automatico ");
   
	while(1){
        if(vaivolta == 0)   Brilho = Brilho+1;
        else                Brilho = Brilho-1;
        
        if(Brilho>1023 && vaivolta == 0){
            Brilho = 1023;
            vaivolta = 1;
        }
        if(Brilho<0 && vaivolta == 1){
            Brilho = 0;
            vaivolta = 0;
        }
        
		DutyCycle_PWM(Brilho);		// Configura DutyCycle (largura do pulso)
               
        __delay_ms(1);
	}
	// -------------------------------------------------
}
//======================================================
