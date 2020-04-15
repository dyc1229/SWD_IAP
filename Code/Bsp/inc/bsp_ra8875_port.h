/*
*********************************************************************************************************
*
*	ģ������ : RA8875оƬ��MCU֮��Ľӿ�����
*	�ļ����� : bsp_ra8875_port.h
*	��    �� : V1.0
*	˵    �� : ͷ�ļ�
*
*	Copyright (C), 2010-2011, ���������� www.armfly.com
*
*********************************************************************************************************
*/


#ifndef _BSP_RA8875_PORT_H
#define _BSP_RA8875_PORT_H

/* ��������������Ƿ������صĴ��� */
#define	RA_HARD_SPI_EN
#define	RA_HARD_8080_16_EN

/* RA8875оƬ��WAIT���� */
#define PORT_WAIT	GPIOD
#define PIN_WAIT	GPIO_Pin_3

#ifdef RA_HARD_SPI_EN	/* Ӳ�� SPI ���� (��Ҫ�ı�RA8875���ϵ�2������λ��) */
	/*
	��1��������STM32-V5������,STM32F407IGT6
		PD3/LCD_BUSY		--- ����оƬæ       ��RA8875����RA8875оƬ��æ�ź�)
		PF6/LCD_PWM			--- LCD����PWM����  ��RA8875������˽ţ�������RA8875����)

		PI10/TP_NCS			--- ����оƬ��Ƭѡ		(RA8875������SPI�ӿڴ���оƬ��
		PB3/SPI3_SCK		--- ����оƬSPIʱ��		(RA8875������SPI�ӿڴ���оƬ��
		PB4/SPI3_MISO		--- ����оƬSPI������MISO(RA8875������SPI�ӿڴ���оƬ��
		PB5/SPI3_MOSI		--- ����оƬSPI������MOSI(RA8875������SPI�ӿڴ���оƬ��

		PC3/TP_INT			--- ����оƬ�ж� ������RA8875������RA8875������ж�)
	*/
	#define RA8875_CS_0()	GPIOI->BSRRH = GPIO_Pin_10
	#define RA8875_CS_1()	GPIOI->BSRRL = GPIO_Pin_10

	#define SPI_WRITE_DATA	0x00
	#define SPI_READ_DATA	0x40
	#define SPI_WRITE_CMD	0x80
	#define SPI_READ_STATUS	0xC0

	static uint8_t SPI_ShiftByte(uint8_t _ucByte);
#endif

#ifdef RA_HARD_8080_16_EN		/* 8080Ӳ������ ��������RA8875��ȱʡģʽ�� */
	/*
		������STM32-V5��������߷�����

		PD0/FSMC_D2
		PD1/FSMC_D3
		PD4/FSMC_NOE		--- �������źţ�OE = Output Enable �� N ��ʾ����Ч
		PD5/FSMC_NWE		--- д�����źţ�WE = Output Enable �� N ��ʾ����Ч
		PD8/FSMC_D13
		PD9/FSMC_D14
		PD10/FSMC_D15
		PD13/FSMC_A18		--- ��ַ RS
		PD14/FSMC_D0
		PD15/FSMC_D1

		PE4/FSMC_A20		--- ����Ƭѡһ������
		PE5/FSMC_A21		--- ����Ƭѡһ������
		PE7/FSMC_D4
		PE8/FSMC_D5
		PE9/FSMC_D6
		PE10/FSMC_D7
		PE11/FSMC_D8
		PE12/FSMC_D9
		PE13/FSMC_D10
		PE14/FSMC_D11
		PE15/FSMC_D12

		PG12/FSMC_NE4		--- ��Ƭѡ��TFT, OLED �� AD7606��

		PC3/TP_INT			--- ����оƬ�ж� ������RA8875������RA8875������ж�)

		---- ������ TFT LCD�ӿ������ź� ��FSMCģʽ��ʹ�ã�----
		PD3/LCD_BUSY		--- ����оƬæ       ��RA8875����RA8875оƬ��æ�ź�)
		PF6/LCD_PWM			--- LCD����PWM����  ��RA8875������˽ţ�������RA8875����)

		PI10/TP_NCS			--- ����оƬ��Ƭѡ		(RA8875������SPI�ӿڴ���оƬ��
		PB3/SPI3_SCK		--- ����оƬSPIʱ��		(RA8875������SPI�ӿڴ���оƬ��
		PB4/SPI3_MISO		--- ����оƬSPI������MISO(RA8875������SPI�ӿڴ���оƬ��
		PB5/SPI3_MOSI		--- ����оƬSPI������MOSI(RA8875������SPI�ӿڴ���оƬ��
	*/
	#define RA8875_BASE		((uint32_t)(0x6C000000 | 0x00000000))

	#define RA8875_REG		*(__IO uint16_t *)(RA8875_BASE +  (1 << (18 + 1)))	/* FSMC 16λ����ģʽ�£�FSMC_A18���߶�Ӧ������ַA19 */
	#define RA8875_RAM		*(__IO uint16_t *)(RA8875_BASE)

	#define RA8875_RAM_ADDR		RA8875_BASE
#endif

/* ����RA8875�ķ��ʽӿ����. V5�����֧�� RA_HARD_SPI �� RA_HARD_8080_16 */
enum
{
	RA_SOFT_8080_8 = 0,	/* ����8080�ӿ�ģʽ, 8bit */
	RA_SOFT_SPI,	   	/* ����SPI�ӿ�ģʽ */
	RA_HARD_SPI,	   	/* Ӳ��SPI�ӿ�ģʽ */
	RA_HARD_8080_16		/* Ӳ��8080�ӿ�,16bit */
};

void RA8875_ConfigGPIO(void);
void RA8875_Delaly1us(void);
void RA8875_Delaly1ms(void);
uint16_t RA8875_ReadID(void);
void RA8875_WriteCmd(uint8_t _ucRegAddr);
void RA8875_WriteData(uint8_t _ucRegValue);
uint8_t RA8875_ReadData(void);
void RA8875_WriteData16(uint16_t _usRGB);
uint16_t RA8875_ReadData16(void);
uint8_t RA8875_ReadStatus(void);
uint32_t RA8875_GetDispMemAddr(void);

/* ����SPI�ӿ�ģʽ */
void RA8875_InitSPI(void);
void RA8875_HighSpeedSPI(void);
void RA8875_LowSpeedSPI(void);

uint8_t RA8875_ReadBusy(void);
extern uint8_t g_RA8875_IF;

#endif

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/