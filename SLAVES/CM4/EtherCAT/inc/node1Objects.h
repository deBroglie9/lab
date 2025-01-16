/**
* \addtogroup node1 node1
* @{
*/

/**
\file node1Objects
\author ET9300Utilities.ApplicationHandler (Version 1.3.6.0) | EthercatSSC@beckhoff.com

\brief node1 specific objects<br>
\brief NOTE : This file will be overwritten if a new object dictionary is generated!<br>
*/

#if defined(_NODE1_) && (_NODE1_ == 1)
#define PROTO
#else
#define PROTO extern
#endif
/******************************************************************************
*                    Object 0x1601 : write commond of moulde
******************************************************************************/
/**
* \addtogroup 0x1601 0x1601 | write commond of moulde
* @{
* \brief Object 0x1601 (write commond of moulde) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
* SubIndex 2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1601[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1601[] = "write commond of moulde\000"
"SubIndex 001\000"
"SubIndex 002\000\377";
#endif //#ifdef _OBJD_

#ifndef _NODE1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
UINT32 SI2; /* Subindex2 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1601;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1601 WriteCommondOfMoulde0x1601
#if defined(_NODE1_) && (_NODE1_ == 1)
={2,0x70200108,0x70200208}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1602 : write target of moulde
******************************************************************************/
/**
* \addtogroup 0x1602 0x1602 | write target of moulde
* @{
* \brief Object 0x1602 (write target of moulde) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1602[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex1 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1602[] = "write target of moulde\000"
"SubIndex 001\000\377";
#endif //#ifdef _OBJD_

#ifndef _NODE1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 SI1; /* Subindex1 -  */
} OBJ_STRUCT_PACKED_END
TOBJ1602;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1602 WriteTargetOfMoulde0x1602
#if defined(_NODE1_) && (_NODE1_ == 1)
={1,0x70300120}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A00 : read ssi of moudle
******************************************************************************/
/**
* \addtogroup 0x1A00 0x1A00 | read ssi of moudle
* @{
* \brief Object 0x1A00 (read ssi of moudle) definition
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
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex8 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A00[] = "read ssi of moudle\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000\377";
#endif //#ifdef _OBJD_

#ifndef _NODE1_OBJECTS_H_
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
} OBJ_STRUCT_PACKED_END
TOBJ1A00;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A00 ReadSsiOfMoudle0x1A00
#if defined(_NODE1_) && (_NODE1_ == 1)
={8,0x60000120,0x60000220,0x60000320,0x60000420,0x60000520,0x60000620,0x60000720,0x60000820}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x1A05 : read ain of moudle
******************************************************************************/
/**
* \addtogroup 0x1A05 0x1A05 | read ain of moudle
* @{
* \brief Object 0x1A05 (read ain of moudle) definition
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
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x1A05[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex1 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex2 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex3 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex4 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex5 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex6 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }, /* Subindex7 */
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READ }}; /* Subindex8 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x1A05[] = "read ain of moudle\000"
"SubIndex 001\000"
"SubIndex 002\000"
"SubIndex 003\000"
"SubIndex 004\000"
"SubIndex 005\000"
"SubIndex 006\000"
"SubIndex 007\000"
"SubIndex 008\000\377";
#endif //#ifdef _OBJD_

#ifndef _NODE1_OBJECTS_H_
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
} OBJ_STRUCT_PACKED_END
TOBJ1A05;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1A05 ReadAinOfMoudle0x1A05
#if defined(_NODE1_) && (_NODE1_ == 1)
={8,0x60100110,0x60100210,0x60100310,0x60100410,0x60100510,0x60100610,0x60100710,0x60100810}
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

#ifndef _NODE1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[2];  /**< \brief Subindex 1 - 2 */
} OBJ_STRUCT_PACKED_END
TOBJ1C12;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C12 sRxPDOassign
#if defined(_NODE1_) && (_NODE1_ == 1)
={2,{0x1601,0x1602}}
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

#ifndef _NODE1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16   u16SubIndex0;  /**< \brief Subindex 0 */
UINT16 aEntries[2];  /**< \brief Subindex 1 - 2 */
} OBJ_STRUCT_PACKED_END
TOBJ1C13;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ1C13 sTxPDOassign
#if defined(_NODE1_) && (_NODE1_ == 1)
={2,{0x1A00,0x1A05}}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6000 : SSI Data
******************************************************************************/
/**
* \addtogroup 0x6000 0x6000 | SSI Data
* @{
* \brief Object 0x6000 (SSI Data) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - ssi<br>
* SubIndex 2 - ssi2<br>
* SubIndex 3 - ssi3<br>
* SubIndex 4 - ssi4<br>
* SubIndex 5 - ssi5<br>
* SubIndex 6 - ssi6<br>
* SubIndex 7 - ssi7<br>
* SubIndex 8 - ssi8<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6000[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - ssi */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ }, /* Subindex2 - ssi2 */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ }, /* Subindex3 - ssi3 */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ }, /* Subindex4 - ssi4 */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ }, /* Subindex5 - ssi5 */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ }, /* Subindex6 - ssi6 */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ }, /* Subindex7 - ssi7 */
{ DEFTYPE_REAL32 , 0x20 , ACCESS_READ }}; /* Subindex8 - ssi8 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6000[] = "SSI Data\000"
"ssi\000"
"ssi2\000"
"ssi3\000"
"ssi4\000"
"ssi5\000"
"ssi6\000"
"ssi7\000"
"ssi8\000\377";
#endif //#ifdef _OBJD_

#ifndef _NODE1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 Ssi; /* Subindex1 - ssi */
UINT32 Ssi2; /* Subindex2 - ssi2 */
UINT32 Ssi3; /* Subindex3 - ssi3 */
UINT32 Ssi4; /* Subindex4 - ssi4 */
UINT32 Ssi5; /* Subindex5 - ssi5 */
UINT32 Ssi6; /* Subindex6 - ssi6 */
UINT32 Ssi7; /* Subindex7 - ssi7 */
UINT32 Ssi8; /* Subindex8 - ssi8 */
} OBJ_STRUCT_PACKED_END
TOBJ6000;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6000 SSIData0x6000
#if defined(_NODE1_) && (_NODE1_ == 1)
={8,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x6010 : AIN Data
******************************************************************************/
/**
* \addtogroup 0x6010 0x6010 | AIN Data
* @{
* \brief Object 0x6010 (AIN Data) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - ain1<br>
* SubIndex 2 - ain2<br>
* SubIndex 3 - ain3<br>
* SubIndex 4 - ain4<br>
* SubIndex 5 - ain5<br>
* SubIndex 6 - ain6<br>
* SubIndex 7 - ain7<br>
* SubIndex 8 - ain8<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x6010[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex1 - ain1 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex2 - ain2 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex3 - ain3 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex4 - ain4 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex5 - ain5 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex6 - ain6 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }, /* Subindex7 - ain7 */
{ DEFTYPE_UNSIGNED16 , 0x10 , ACCESS_READ | OBJACCESS_TXPDOMAPPING }}; /* Subindex8 - ain8 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x6010[] = "AIN Data\000"
"ain1\000"
"ain2\000"
"ain3\000"
"ain4\000"
"ain5\000"
"ain6\000"
"ain7\000"
"ain8\000\377";
#endif //#ifdef _OBJD_

#ifndef _NODE1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT16 Ain1; /* Subindex1 - ain1 */
UINT16 Ain2; /* Subindex2 - ain2 */
UINT16 Ain3; /* Subindex3 - ain3 */
UINT16 Ain4; /* Subindex4 - ain4 */
UINT16 Ain5; /* Subindex5 - ain5 */
UINT16 Ain6; /* Subindex6 - ain6 */
UINT16 Ain7; /* Subindex7 - ain7 */
UINT16 Ain8; /* Subindex8 - ain8 */
} OBJ_STRUCT_PACKED_END
TOBJ6010;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ6010 AINData0x6010
#if defined(_NODE1_) && (_NODE1_ == 1)
={8,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7020 : Commond of moudule
******************************************************************************/
/**
* \addtogroup 0x7020 0x7020 | Commond of moudule
* @{
* \brief Object 0x7020 (Commond of moudule) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Commond1<br>
* SubIndex 2 - Commond2<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7020[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }, /* Subindex1 - Commond1 */
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex2 - Commond2 */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7020[] = "Commond of moudule\000"
"Commond1\000"
"Commond2\000\377";
#endif //#ifdef _OBJD_

#ifndef _NODE1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT8 Commond1; /* Subindex1 - Commond1 */
UINT8 Commond2; /* Subindex2 - Commond2 */
} OBJ_STRUCT_PACKED_END
TOBJ7020;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7020 CommondOfMoudule0x7020
#if defined(_NODE1_) && (_NODE1_ == 1)
={2,0x00,0x00}
#endif
;
/** @}*/



/******************************************************************************
*                    Object 0x7030 : Target
******************************************************************************/
/**
* \addtogroup 0x7030 0x7030 | Target
* @{
* \brief Object 0x7030 (Target) definition
*/
#ifdef _OBJD_
/**
* \brief Object entry descriptions<br>
* <br>
* SubIndex 0<br>
* SubIndex 1 - Target Angle<br>
*/
OBJCONST TSDOINFOENTRYDESC    OBJMEM asEntryDesc0x7030[] = {
{ DEFTYPE_UNSIGNED8 , 0x8 , ACCESS_READ },
{ DEFTYPE_UNSIGNED32 , 0x20 , ACCESS_READWRITE | OBJACCESS_RXPDOMAPPING }}; /* Subindex1 - Target Angle */

/**
* \brief Object/Entry names
*/
OBJCONST UCHAR OBJMEM aName0x7030[] = "Target\000"
"Target Angle\000\377";
#endif //#ifdef _OBJD_

#ifndef _NODE1_OBJECTS_H_
/**
* \brief Object structure
*/
typedef struct OBJ_STRUCT_PACKED_START {
UINT16 u16SubIndex0;
UINT32 TargetAngle; /* Subindex1 - Target Angle */
} OBJ_STRUCT_PACKED_END
TOBJ7030;
#endif //#ifndef _NODE1_OBJECTS_H_

/**
* \brief Object variable
*/
PROTO TOBJ7030 Target0x7030
#if defined(_NODE1_) && (_NODE1_ == 1)
={1,0x00000000}
#endif
;
/** @}*/







#ifdef _OBJD_
TOBJECT    OBJMEM ApplicationObjDic[] = {
/* Object 0x1601 */
{NULL , NULL ,  0x1601 , {DEFTYPE_PDOMAPPING , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x1601 , aName0x1601 , &WriteCommondOfMoulde0x1601, NULL , NULL , 0x0000 },
/* Object 0x1602 */
{NULL , NULL ,  0x1602 , {DEFTYPE_PDOMAPPING , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x1602 , aName0x1602 , &WriteTargetOfMoulde0x1602, NULL , NULL , 0x0000 },
/* Object 0x1A00 */
{NULL , NULL ,  0x1A00 , {DEFTYPE_PDOMAPPING , 8 | (OBJCODE_REC << 8)} , asEntryDesc0x1A00 , aName0x1A00 , &ReadSsiOfMoudle0x1A00, NULL , NULL , 0x0000 },
/* Object 0x1A05 */
{NULL , NULL ,  0x1A05 , {DEFTYPE_PDOMAPPING , 8 | (OBJCODE_REC << 8)} , asEntryDesc0x1A05 , aName0x1A05 , &ReadAinOfMoudle0x1A05, NULL , NULL , 0x0000 },
/* Object 0x1C12 */
{NULL , NULL ,  0x1C12 , {DEFTYPE_UNSIGNED16 , 2 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C12 , aName0x1C12 , &sRxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x1C13 */
{NULL , NULL ,  0x1C13 , {DEFTYPE_UNSIGNED16 , 2 | (OBJCODE_ARR << 8)} , asEntryDesc0x1C13 , aName0x1C13 , &sTxPDOassign, NULL , NULL , 0x0000 },
/* Object 0x6000 */
{NULL , NULL ,  0x6000 , {DEFTYPE_RECORD , 8 | (OBJCODE_REC << 8)} , asEntryDesc0x6000 , aName0x6000 , &SSIData0x6000, NULL , NULL , 0x0000 },
/* Object 0x6010 */
{NULL , NULL ,  0x6010 , {DEFTYPE_RECORD , 8 | (OBJCODE_REC << 8)} , asEntryDesc0x6010 , aName0x6010 , &AINData0x6010, NULL , NULL , 0x0000 },
/* Object 0x7020 */
{NULL , NULL ,  0x7020 , {DEFTYPE_RECORD , 2 | (OBJCODE_REC << 8)} , asEntryDesc0x7020 , aName0x7020 , &CommondOfMoudule0x7020, NULL , NULL , 0x0000 },
/* Object 0x7030 */
{NULL , NULL ,  0x7030 , {DEFTYPE_RECORD , 1 | (OBJCODE_REC << 8)} , asEntryDesc0x7030 , aName0x7030 , &Target0x7030, NULL , NULL , 0x0000 },
{NULL,NULL, 0xFFFF, {0, 0}, NULL, NULL, NULL, NULL}};
#endif    //#ifdef _OBJD_
#undef PROTO

/** @}*/
#define _NODE1_OBJECTS_H_
