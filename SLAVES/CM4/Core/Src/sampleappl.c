/**
\addtogroup sampleappl sampleappl
@{
*/

/**
\file sampleappl.c
\brief Implementation

\version 1.0.0.11
*/


/*-----------------------------------------------------------------------------------------
------
------    Includes
------
-----------------------------------------------------------------------------------------*/
#include "ecat_def.h"
#include "main.h"
#include "applInterface.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"
#define _NODE1_ 1
#include "node1.h"
#undef _NODE1_
/*--------------------------------------------------------------------------------------
------
------    local types and defines
------
--------------------------------------------------------------------------------------*/
extern float angle_all[8];
static int count =0;
static float ang_float[1];
static UINT32 ang_int[1];
/*-----------------------------------------------------------------------------------------
------
------    local variables and constants
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    application specific functions
------
-----------------------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------------------
------
------    generic functions
------
-----------------------------------------------------------------------------------------*/

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \brief    The function is called when an error state was acknowledged by the master

*////////////////////////////////////////////////////////////////////////////////////////

void    APPL_AckErrorInd(UINT16 stateTrans)
{

}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from INIT to PREOP when
             all general settings were checked to start the mailbox handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
            The return code NOERROR_INWORK can be used, if the application cannot confirm
            the state transition immediately, in that case this function will be called cyclically
            until a value unequal NOERROR_INWORK is returned

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from PREEOP to INIT
             to stop the mailbox handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopMailboxHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \param    pIntMask    pointer to the AL Event Mask which will be written to the AL event Mask
                        register (0x204) when this function is succeeded. The event mask can be adapted
                        in this function
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from PREOP to SAFEOP when
           all general settings were checked to start the input handler. This function
           informs the application about the state transition, the application can refuse
           the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartInputHandler(UINT16 *pIntMask)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from SAFEOP to PREEOP
             to stop the input handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopInputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    AL Status Code (see ecatslv.h ALSTATUSCODE_....)

 \brief    The function is called in the state transition from SAFEOP to OP when
             all general settings were checked to start the output handler. This function
             informs the application about the state transition, the application can refuse
             the state transition when returning an AL Status error code.
           The return code NOERROR_INWORK can be used, if the application cannot confirm
           the state transition immediately, in that case the application need to be complete 
           the transition by calling ECAT_StateChange.
*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StartOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return     0, NOERROR_INWORK

 \brief    The function is called in the state transition from OP to SAFEOP
             to stop the output handler. This functions informs the application
             about the state transition, the application cannot refuse
             the state transition.

*////////////////////////////////////////////////////////////////////////////////////////

UINT16 APPL_StopOutputHandler(void)
{
    return ALSTATUSCODE_NOERROR;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\return     0(ALSTATUSCODE_NOERROR), NOERROR_INWORK
\param      pInputSize  pointer to save the input process data length
\param      pOutputSize  pointer to save the output process data length

\brief    This function calculates the process data sizes from the actual SM-PDO-Assign
            and PDO mapping
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GenerateMapping(UINT16 *pInputSize,UINT16 *pOutputSize)
{
    UINT16 result = ALSTATUSCODE_NOERROR;
    UINT16 InputSize = 0;
    UINT16 OutputSize = 0;

#if COE_SUPPORTED
    UINT16 PDOAssignEntryCnt = 0;
    OBJCONST TOBJECT OBJMEM * pPDO = NULL;
    UINT16 PDOSubindex0 = 0;
    UINT32 *pPDOEntry = NULL;
    UINT16 PDOEntryCnt = 0;
   
    /*Scan object 0x1C12 RXPDO assign*/
    for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sRxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
    {
        pPDO = OBJ_GetObjectHandle(sRxPDOassign.aEntries[PDOAssignEntryCnt]);
        if(pPDO != NULL)
        {
            PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
            for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
            {
                pPDOEntry = (UINT32 *)((UINT8 *)pPDO->pVarPtr + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>3));    //goto PDO entry
                // we increment the expected output size depending on the mapped Entry
                OutputSize += (UINT16) ((*pPDOEntry) & 0xFF);
            }
        }
        else
        {
            /*assigned PDO was not found in object dictionary. return invalid mapping*/
            OutputSize = 0;
            result = ALSTATUSCODE_INVALIDOUTPUTMAPPING;
            break;
        }
    }

    OutputSize = (OutputSize + 7) >> 3;

    if(result == 0)
    {
        /*Scan Object 0x1C13 TXPDO assign*/
        for(PDOAssignEntryCnt = 0; PDOAssignEntryCnt < sTxPDOassign.u16SubIndex0; PDOAssignEntryCnt++)
        {
            pPDO = OBJ_GetObjectHandle(sTxPDOassign.aEntries[PDOAssignEntryCnt]);
            if(pPDO != NULL)
            {
                PDOSubindex0 = *((UINT16 *)pPDO->pVarPtr);
                for(PDOEntryCnt = 0; PDOEntryCnt < PDOSubindex0; PDOEntryCnt++)
                {
                    pPDOEntry = (UINT32 *)((UINT8 *)pPDO->pVarPtr + (OBJ_GetEntryOffset((PDOEntryCnt+1),pPDO)>>3));    //goto PDO entry
                    // we increment the expected output size depending on the mapped Entry
                    InputSize += (UINT16) ((*pPDOEntry) & 0xFF);
                }
            }
            else
            {
                /*assigned PDO was not found in object dictionary. return invalid mapping*/
                InputSize = 0;
                result = ALSTATUSCODE_INVALIDINPUTMAPPING;
                break;
            }
        }
    }
    InputSize = (InputSize + 7) >> 3;

#else
#if _WIN32
   #pragma message ("Warning: Define 'InputSize' and 'OutputSize'.")
#else
    #warning "Define 'InputSize' and 'OutputSize'."
#endif
#endif

    *pInputSize = InputSize;
    *pOutputSize = OutputSize;
    return result;
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to input process data

\brief      This function will copies the inputs from the local memory to the ESC memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_InputMapping(UINT16* pData)
{
    UINT16 j = 0;
    UINT16 *pTmpData = (UINT16 *)pData;

    /* we go through all entries of the TxPDO Assign object to get the assigned TxPDOs */
   for (j = 0; j < sTxPDOassign.u16SubIndex0; j++)
   {
      switch (sTxPDOassign.aEntries[j])
      {
      /* TxPDO 1 */
      case 0x1A00:
		*pTmpData++ = (((UINT16 *) &SSIData0x6000)[2]);
        *pTmpData++ = (((UINT16 *) &SSIData0x6000)[3]);
		*pTmpData++ = (((UINT16 *) &SSIData0x6000)[4]);
        *pTmpData++ = (((UINT16 *) &SSIData0x6000)[5]);
		*pTmpData++ = (((UINT16 *) &SSIData0x6000)[6]);
        *pTmpData++ = (((UINT16 *) &SSIData0x6000)[7]);
		*pTmpData++ = (((UINT16 *) &SSIData0x6000)[8]);
        *pTmpData++ = (((UINT16 *) &SSIData0x6000)[9]);
		*pTmpData++ = (((UINT16 *) &SSIData0x6000)[10]);
        *pTmpData++ = (((UINT16 *) &SSIData0x6000)[11]);
		*pTmpData++ = (((UINT16 *) &SSIData0x6000)[12]);
        *pTmpData++ = (((UINT16 *) &SSIData0x6000)[13]);
		*pTmpData++ = (((UINT16 *) &SSIData0x6000)[14]);
        *pTmpData++ = (((UINT16 *) &SSIData0x6000)[15]);
		*pTmpData++ = (((UINT16 *) &SSIData0x6000)[16]);
        *pTmpData++ = (((UINT16 *) &SSIData0x6000)[17]);

         break;
	  case 0x1A05:
		*pTmpData++ = (((UINT16 *) &AINData0x6010)[1]);
        *pTmpData++ = (((UINT16 *) &AINData0x6010)[2]);
		*pTmpData++ = (((UINT16 *) &AINData0x6010)[3]);
		*pTmpData++ = (((UINT16 *) &AINData0x6010)[4]);
        *pTmpData++ = (((UINT16 *) &AINData0x6010)[5]);
		*pTmpData++ = (((UINT16 *) &AINData0x6010)[6]);
		*pTmpData++ = (((UINT16 *) &AINData0x6010)[7]);
        *pTmpData++ = (((UINT16 *) &AINData0x6010)[8]);
			break;
					
      /* TxPDO 3 */
      }
   }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\param      pData  pointer to output process data

\brief    This function will copies the outputs from the ESC memory to the local memory
            to the hardware
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_OutputMapping(UINT16* pData)
{
    UINT16 j = 0;
    UINT16 *pTmpData = (UINT16 *)pData;

    /* we go through all entries of the RxPDO Assign object to get the assigned RxPDOs */
    for (j = 0; j < sRxPDOassign.u16SubIndex0; j++)
    {
        switch (sRxPDOassign.aEntries[j])
        {
        /* RxPDO 2 */
        case 0x1601:
        	((UINT16 *) &CommondOfMoudule0x7020)[1] = SWAPWORD(*pTmpData++);
            break;
		case 0x1602:
            ((UINT16 *) &Target0x7030)[1] = SWAPWORD(*pTmpData++);
			((UINT16 *) &Target0x7030)[2] = SWAPWORD(*pTmpData++);
            break;
        }
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/**
\brief    This function will called from the synchronisation ISR 
            or from the mainloop if no synchronisation is supported
*////////////////////////////////////////////////////////////////////////////////////////
void APPL_Application(void)
{
	count++;
//	SSIData0x6000.Ssi=angle_all[0];
	ang_float[0]=angle_all[0];
	MEMCPY(ang_int, ang_float, sizeof(ang_float));
	SSIData0x6000.Ssi=ang_int[0];

	ang_float[0]=angle_all[1];
	MEMCPY(ang_int, ang_float, sizeof(ang_float));
	SSIData0x6000.Ssi2=ang_int[0];

	ang_float[0]=angle_all[2];
	MEMCPY(ang_int, ang_float, sizeof(ang_float));
	SSIData0x6000.Ssi3=ang_int[0];

	ang_float[0]=angle_all[3];
	MEMCPY(ang_int, ang_float, sizeof(ang_float));
	SSIData0x6000.Ssi4=ang_int[0];

	ang_float[0]=angle_all[5];
	MEMCPY(ang_int, ang_float, sizeof(ang_float));
	SSIData0x6000.Ssi5=ang_int[0];

	ang_float[0]=angle_all[6];
	MEMCPY(ang_int, ang_float, sizeof(ang_float));
	SSIData0x6000.Ssi6=ang_int[0];

	ang_float[0]=angle_all[7];
	MEMCPY(ang_int, ang_float, sizeof(ang_float));
	SSIData0x6000.Ssi7=ang_int[0];

//	ang_float[0]=angle_all[7];
//	MEMCPY(ang_int, ang_float, sizeof(ang_float));
	SSIData0x6000.Ssi8=12568;

//	SSIData0x6000.Ssi=Target0x7030.TargetAngle;
	AINData0x6010.Ain1=count;
	AINData0x6010.Ain2=angle_all[1];
	AINData0x6010.Ain3=angle_all[2];
	AINData0x6010.Ain4=angle_all[3];
	AINData0x6010.Ain5=angle_all[4];
	AINData0x6010.Ain6=angle_all[5];
	AINData0x6010.Ain7=angle_all[6];
	AINData0x6010.Ain8=angle_all[7];
	
//	model=CommondOfMoudule0x7020.Commond1;
//	(CommondOfMoudule0x7020.Commond1==0x01)? HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET);

//		osDelay(1);
//	Obj0x7010.BLED4==TRUE? HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_SET):HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,GPIO_PIN_RESET);

//	output=__HAL_GPIO_EXTI_GET_IT(SPI_IRQ_Pin);
//	
//	input++;
//	if(input%1000){
//		(Obj0x6000.BSwitch4==1)?(Obj0x6000.BSwitch4=0): (Obj0x6000.BSwitch4 = 1	);
//	}
}

#if EXPLICIT_DEVICE_ID
/////////////////////////////////////////////////////////////////////////////////////////
/**
 \return    The Explicit Device ID of the EtherCAT slave

 \brief     Calculate the Explicit Device ID
*////////////////////////////////////////////////////////////////////////////////////////
UINT16 APPL_GetDeviceID()
{
#if _WIN32
   #pragma message ("Warning: Implement explicit Device ID latching")
#else
    #warning "Implement explicit Device ID latching"
#endif
    /* Explicit Device 5 is expected by Explicit Device ID conformance tests*/
    return 0x5;
}
#endif



#if USE_DEFAULT_MAIN
/////////////////////////////////////////////////////////////////////////////////////////
/**

 \brief    This is the main function

*////////////////////////////////////////////////////////////////////////////////////////
//#if _PIC24
//int main(void)
//#else
//void main(void)
//#endif
//{
//    /* initialize the Hardware and the EtherCAT Slave Controller */
//#if FC1100_HW
//    if(HW_Init())
//    {
//        HW_Release();
//        return;
//    }
//#else
//    HW_Init();
//#endif
//    MainInit();

//    bRunApplication = TRUE;
//    do
//    {
//        MainLoop();
//        
//    } while (bRunApplication == TRUE);

//    HW_Release();
//#if _PIC24
//    return 0;
//#endif
//}
#endif //#if USE_DEFAULT_MAIN
/** @} */


