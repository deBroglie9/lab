/**
* \addtogroup sampleappl sampleappl
* @{
*/

/**
\file sampleapplObjects
\author ET9300Utilities.ApplicationHandler (Version 1.3.6.0) | EthercatSSC@beckhoff.com

\brief sampleappl specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_SAMPLEAPPL_) && (_SAMPLEAPPL_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1601 : Obj0x1601
******************************************************************************/
/**
* \addtogroup 0x1601 0x1601 | Obj0x1601
* @{
* \brief Object 0x1601 (Obj0x1601) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
* SubIndex 3<br>
* SubIndex 4<br>
* SubIndex 5<br>
* SubIndex 6<br>
* SubIndex 7<br>
* SubIndex 8<br>
* SubIndex 9<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1601[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex9 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1601[] = "Obj0x1601\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000\377";
#endif //#ifdef _OBJD_

#ifndef _SAMPLEAPPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
UINT32 SI6; /* Subindex6 -  */
UINT32 SI7; /* Subindex7 -  */
UINT32 SI8; /* Subindex8 -  */
UINT32 SI9; /* Subindex9 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1601;
#endif //#ifndef _SAMPLEAPPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1601 Obj0x1601
#if defined(_SAMPLEAPPL_) && (_SAMPLEAPPL_ == 1)
={9,0x70100101,0x70100201,0x70100301,0x70100401,0x70100501,0x70100601,0x70100701,0x70100801,0x00000008}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : Obj0x1A00
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | Obj0x1A00
* @{
* \brief Object 0x1A00 (Obj0x1A00) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
* SubIndex 3<br>
* SubIndex 4<br>
* SubIndex 5<br>
* SubIndex 6<br>
* SubIndex 7<br>
* SubIndex 8<br>
* SubIndex 9<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A00[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex8 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex9 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "Obj0x1A00\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000"
"SubIndex 009\000\377";
#endif //#ifdef _OBJD_

#ifndef _SAMPLEAPPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
UINT32 SI3; /* Subindex3 -  */
UINT32 SI4; /* Subindex4 -  */
UINT32 SI5; /* Subindex5 -  */
UINT32 SI6; /* Subindex6 -  */
UINT32 SI7; /* Subindex7 -  */
UINT32 SI8; /* Subindex8 -  */
UINT32 SI9; /* Subindex9 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _SAMPLEAPPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 Obj0x1A00
#if defined(_SAMPLEAPPL_) && (_SAMPLEAPPL_ == 1)
={9,0x60000101,0x60000201,0x60000301,0x60000401,0x60000501,0x60000601,0x60000701,0x60000801,0x00000008}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C12 : RxPDO assign
******************************************************************************/
/**
* \addtogroup 0x1C12 0x1C12 | RxPDO assign
* @{
* \brief Object 0x1C12 (RxPDO assign) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C12[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ | ACCESS_WRITE_PREOP },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | ACCESS_WRITE_PREOP }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C12[] = "RxPDO assign\000\377";
#endif //#ifdef _OBJD_

#ifndef _SAMPLEAPPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _SAMPLEAPPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_SAMPLEAPPL_) && (_SAMPLEAPPL_ == 1)
={1,{0x1601}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1C13 : TxPDO assign
******************************************************************************/
/**
* \addtogroup 0x1C13 0x1C13 | TxPDO assign
* @{
* \brief Object 0x1C13 (TxPDO assign) definition
*/
#ifdef _OBJD_
/**
* \brief Entry descriptions<br>
* 
* Subindex 0<br>
* Subindex 1 - n (the same entry description is used)<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1C13[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ | ACCESS_WRITE_PREOP },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | ACCESS_WRITE_PREOP }};

/**
* \brief Object name definition<br>
* For Subindex 1 to n the syntax 'Subindex XXX' is used
*/
OBJCONST UCHAR OBJMEM aName0x1C13[] = "TxPDO assign\000\377";
#endif //#ifdef _OBJD_

#ifndef _SAMPLEAPPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[1];  /**< \brief Subindex 1 - 1 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _SAMPLEAPPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_SAMPLEAPPL_) && (_SAMPLEAPPL_ == 1)
={1,{0x1A00}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : Obj0x6000
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | Obj0x6000
* @{
* \brief Object 0x6000 (Obj0x6000) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - bSwitch1<br>
* SubIndex 2 - bSwitch2<br>
* SubIndex 3 - bSwitch3<br>
* SubIndex 4 - bSwitch4<br>
* SubIndex 5 - bSwitch5<br>
* SubIndex 6 - bSwitch6<br>
* SubIndex 7 - bSwitch7<br>
* SubIndex 8 - bSwitch8<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - bSwitch1 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - bSwitch2 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - bSwitch3 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - bSwitch4 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex5 - bSwitch5 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex6 - bSwitch6 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex7 - bSwitch7 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex8 - bSwitch8 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "Obj0x6000\000"
"bSwitch1\000"
"bSwitch2\000"
"bSwitch3\000"
"bSwitch4\000"
"bSwitch5\000"
"bSwitch6\000"
"bSwitch7\000"
"bSwitch8\000\377";
#endif //#ifdef _OBJD_

#ifndef _SAMPLEAPPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
BOOLEAN(BSwitch1); /* Subindex1 - bSwitch1 */
BOOLEAN(BSwitch2); /* Subindex2 - bSwitch2 */
BOOLEAN(BSwitch3); /* Subindex3 - bSwitch3 */
BOOLEAN(BSwitch4); /* Subindex4 - bSwitch4 */
BOOLEAN(BSwitch5); /* Subindex5 - bSwitch5 */
BOOLEAN(BSwitch6); /* Subindex6 - bSwitch6 */
BOOLEAN(BSwitch7); /* Subindex7 - bSwitch7 */
BOOLEAN(BSwitch8); /* Subindex8 - bSwitch8 */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _SAMPLEAPPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 Obj0x6000
#if defined(_SAMPLEAPPL_) && (_SAMPLEAPPL_ == 1)
={8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7010 : Obj0x7010
******************************************************************************/
/**
* \addtogroup 0x7010 0x7010 | Obj0x7010
* @{
* \brief Object 0x7010 (Obj0x7010) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - bLED1<br>
* SubIndex 2 - bLED2<br>
* SubIndex 3 - bLED3<br>
* SubIndex 4 - bLED4<br>
* SubIndex 5 - bLED5<br>
* SubIndex 6 - bLED6<br>
* SubIndex 7 - bLED7<br>
* SubIndex 8 - bLED8<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7010[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - bLED1 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex2 - bLED2 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex3 - bLED3 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex4 - bLED4 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex5 - bLED5 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex6 - bLED6 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex7 - bLED7 */
{ DEFTYPE_BOOLEAN , 0x1 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex8 - bLED8 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7010[] = "Obj0x7010\000"
"bLED1\000"
"bLED2\000"
"bLED3\000"
"bLED4\000"
"bLED5\000"
"bLED6\000"
"bLED7\000"
"bLED8\000\377";
#endif //#ifdef _OBJD_

#ifndef _SAMPLEAPPL_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
BOOLEAN(BLED1); /* Subindex1 - bLED1 */
BOOLEAN(BLED2); /* Subindex2 - bLED2 */
BOOLEAN(BLED3); /* Subindex3 - bLED3 */
BOOLEAN(BLED4); /* Subindex4 - bLED4 */
BOOLEAN(BLED5); /* Subindex5 - bLED5 */
BOOLEAN(BLED6); /* Subindex6 - bLED6 */
BOOLEAN(BLED7); /* Subindex7 - bLED7 */
BOOLEAN(BLED8); /* Subindex8 - bLED8 */
} OBJ_STRUCT_PACKED_END
TOBJ7010;
#endif //#ifndef _SAMPLEAPPL_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7010 Obj0x7010
#if defined(_SAMPLEAPPL_) && (_SAMPLEAPPL_ == 1)
={8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1601 */
{NULL , NULL ,  0x1601 , {DEFTYPE_PDOMAPPING , 9 | (OBJCODE_REC << 8)} , asEntryDesc0x1601 , aName0x1601 , &Obj0x1601, NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 9 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &Obj0x1A00, NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 1 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 8 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &Obj0x6000, NULL , NULL , 0x0000 },
/* Object 0x7010 */
{NULL , NULL ,  0x7010 , {DEFTYPE_RECORD , 8 | (OBJCODE_REC << 8)} , asEntryDesc0x7010 , aName0x7010 , &Obj0x7010, NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_
#undef PROTO

/** @}*/
#define _SAMPLEAPPL_OBJECTS_H_
