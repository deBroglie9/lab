/**
 * \addtogroup EL9800_HW EL9800 Platform (Serial ESC Access)
 * @{
 */

/**
\file samplehw.h
\author EthercatSSC@beckhoff.com
\brief Defines to access the EL9800 specific periphery and ESC (via SPI)

\version 5.01

<br>Changes to version - :<br>
V5.01 : Start file change log
 */

#ifndef _SAMPLEHW_H_
#define _SAMPLEHW_H_


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include  "esc.h"
#include "main.h"
//#include <p24Hxxxx.h>
#include "stm32h7xx.h"
//#include "system.h"
/*-----------------------------------------------------------------------------------------
------
------    Defines and Types
------
-----------------------------------------------------------------------------------------*/
#define ESC_RD                    0x02 /**< \brief Indicates a read access to ESC or EEPROM*/
#define ESC_WR                    0x04 /**< \brief Indicates a write access to ESC or EEPROM.*/


/*---------------------------------------------
-    Microcontroller definitions
-----------------------------------------------*/

extern	uint16_t uhADCxConvertedValue;



/*---------------------------------------------
-    hardware timer settings
-----------------------------------------------*/

#define ECAT_TIMER_INC_P_MS                2000 //72000   	//0x271 /**< \brief 625 ticks per ms*/



/*---------------------------------------------
-    Interrupt and Timer defines
-----------------------------------------------*/

#ifndef DISABLE_ESC_INT
#define    DISABLE_ESC_INT()           HAL_NVIC_DisableIRQ(SPI3_IRQ_EXTI_IRQn)		// {(_INT1IE)=0;} /**< \brief Disable interrupt source INT1*/
#endif
#ifndef ENABLE_ESC_INT
#define    ENABLE_ESC_INT()           HAL_NVIC_EnableIRQ(SPI3_IRQ_EXTI_IRQn)			// {(_INT1IE)=1;} /**< \brief Enable interrupt source INT1*/
#endif

#ifndef HW_GetTimer
#define HW_GetTimer()       		TIM2->CNT		//(SysTick->LOAD - 	SysTick->VAL) //			// ((UINT16)(TMR7)) /**< \brief Access to the hardware timer*/
#endif

#ifndef HW_ClearTimer
#define HW_ClearTimer()         ((TIM2->CNT)=0); //(SysTick->VAL = SysTick->LOAD)// //{(TMR7) = 0;} /**< \brief Clear the hardware timer*/
#endif




#define HW_EscReadByte(ByteValue,Address)	HW_EscRead(((MEM_ADDR *)&(ByteValue)),((UINT16)(Address)),1) 
#define HW_EscReadWord(WordValue, Address) HW_EscRead(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief 16Bit ESC read access*/
#define HW_EscReadDWord(DWordValue, Address) HW_EscRead(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief 32Bit ESC read access*/
#define HW_EscReadMbxMem(pData,Address,Len) HW_EscRead(((MEM_ADDR *)(pData)),((UINT16)(Address)),(Len)) /**< \brief The mailbox data is stored in the local uC memory therefore the default read function is used.*/

#define HW_EscReadByteIsr(ByteValue,Address)	HW_EscRead(((MEM_ADDR *)&(ByteValue)),((UINT16)(Address)),1) 
#define HW_EscReadWordIsr(WordValue, Address) HW_EscReadIsr(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief Interrupt specific 16Bit ESC read access*/
#define HW_EscReadDWordIsr(DWordValue, Address) HW_EscReadIsr(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief Interrupt specific 32Bit ESC read access*/

#define HW_EscWriteByte(WordValue, Address) HW_EscWrite(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),1)
#define HW_EscWriteWord(WordValue, Address) HW_EscWrite(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief 16Bit ESC write access*/
#define HW_EscWriteDWord(DWordValue, Address) HW_EscWrite(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief 32Bit ESC write access*/
#define HW_EscWriteMbxMem(pData,Address,Len) HW_EscWrite(((MEM_ADDR *)(pData)),((UINT16)(Address)),(Len)) /**< \brief The mailbox data is stored in the local uC memory therefore the default write function is used.*/

#define HW_EscWriteWordIsr(WordValue, Address) HW_EscWriteIsr(((MEM_ADDR *)&(WordValue)),((UINT16)(Address)),2) /**< \brief Interrupt specific 16Bit ESC write access*/
#define HW_EscWriteDWordIsr(DWordValue, Address) HW_EscWriteIsr(((MEM_ADDR *)&(DWordValue)),((UINT16)(Address)),4) /**< \brief Interrupt specific 32Bit ESC write access*/

#endif //_EL9800HW_H_


#if _EL9800HW_
    #define PROTO
#else
    #define PROTO extern
#endif


/*-----------------------------------------------------------------------------------------
------
------    Global variables
------
-----------------------------------------------------------------------------------------*/


/*-----------------------------------------------------------------------------------------
------
------    Global functions
------
-----------------------------------------------------------------------------------------*/
PROTO UINT8 HW_Init(void);
PROTO void HW_Release(void);
PROTO UINT16 HW_GetALEventRegister(void);

PROTO UINT16 HW_GetALEventRegister_Isr(void);

PROTO void HW_ResetALEventMask(UINT16 intMask);
PROTO void HW_SetALEventMask(UINT16 intMask);
PROTO void HW_SetLed(UINT8 RunLed,UINT8 ErrLed);

PROTO void HW_EscRead( MEM_ADDR * pData, UINT16 Address, UINT16 Len );
PROTO void HW_EscReadIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

PROTO void HW_EscWrite( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

PROTO void HW_EscWriteIsr( MEM_ADDR *pData, UINT16 Address, UINT16 Len );

PROTO void HW_DisableSyncManChannel(UINT8 channel);
PROTO void HW_EnableSyncManChannel(UINT8 channel);
PROTO TSYNCMAN ESCMEM *HW_GetSyncMan(UINT8 channel);

/*---------------------------------------------
-    ESC Access macros
-----------------------------------------------*/
#if _EL9800HW_

#endif //#if _EL9800HW_
#undef    PROTO
/** @}*/
