/*=======================================================
					SENAI A. Jacob Lafer
					====================

Nome do projeto:	PWM2
Versão:				1.0x
Última revisão:		01/06/2020
Cliente:			SENAI
Desenvolvimento:	Luiz Ricardo Bitencourt

Descritivo Funcional:
Teste de funcionamento de PWM junto com ADC.

Inputs:
- RA0 - Entrada analógica

Outputs:
- RC2 - Saída do PWM
- RB2 - Display RS
- RB3 - Display E
- RB4-RB7 - Display Data
=========================================================*/

//======================================================
// Bibliotecas
//======================================================
#include <xc.h>
#include "lcd_4vias.h"
#include "adc.h"
#include "pwm.h"

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
	int          	ValorADC = 0;
    unsigned int    Luminosidade;
	// -------------------------------------------------

	// -------------------------------------------------
	// Configurações iniciais
	// -------------------------------------------------
    TRISB = 0b00000011;             // Port B, do RB0 até RB7
	INTCON2bits.NOT_RBPU = 1;       // Desliga os pull-ups internos do PORT B
    // -------------------------------------------------
    
    // ------------------------------------------------------
    // INICIALIZAÇÃO DE FUNÇÕES
    // ------------------------------------------------------
	IniciaLCD();                // Inicializa Display LCD
    LimpaLCD();                 // Limpa Display
	Inicializa_ADC();			// Inicializa módulo ADC
	Inicializa_PWM(255);		// Inicializa PWM com período de 52,1us
	// -------------------------------------------------

	// -------------------------------------------------
	// Programa principal
	// -------------------------------------------------
	PosicionaLCD(1,1);
    StringLCD("   SENAI  118   ");
   
	while(1){
    	ValorADC = LerADC();			// Lê o valor do ADC
        DutyCycle_PWM(ValorADC);		// Configura DutyCycle com o valor do ADC (ambos s?o de 10 bits)
        
        PosicionaLCD(2,1);
        StringLCD("Intensidade ");
        PosicionaLCD(2,16);
        StringLCD("%");
        PosicionaLCD(2,13);
        
        Luminosidade = ((ValorADC*5.0)/1024)*20;

		EscreveLCD((Luminosidade/100)+48);
		EscreveLCD((Luminosidade/10)%10+48);
		EscreveLCD(Luminosidade%10+48);
	}
	// -------------------------------------------------
}
//======================================================
