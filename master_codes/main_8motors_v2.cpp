/*****************************************************************************
 * 2025/2/8
 * 用于四自由度双臂
 * 单臂柔顺实验测试
 * 电机可以正常使能并进行运动
 * 目前接入1个编码器 8个驱动器 代码目前可连接16个从站，2个编码器+14个驱动器，需要修改 DRIVER_NUMBER ENCODER_NUMBER DOMAIN_NUMBER
 *  (EtherCAT相关参数及其他初始化函数的个数及序号移植失败，Ethercat.h暂时不用) 
 * 
 * 设置driver_enable,drivesr_disable,reading_driver，reading_ssi，control_pid函数
 * 加入逆运动学求解函数，读入X,Y,Z和R(3*3逐行读入)
 * 
 * 给定了一组轨迹，可读入并执行（已调试），注意修改轨迹时修改对应csv的数组大小 NUMBER
 * 
 *  $Id: main.c,v 6a6dec6fc806 2012/09/19 17:46:58 fp $
 *
 *  Copyright (C) 2007-2009  Florian Pose, Ingenieurgemeinschaft IgH
 *
 *  This file is part of the IgH EtherCAT Master.
 *
 *  The IgH EtherCAT Master is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public License version 2, as
 *  published by the Free Software Foundation.
 *
 *  The IgH EtherCAT Master is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
 *  Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with the IgH EtherCAT Master; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *  ---
 *
 *  The license mentioned above concerns the source code only. Using the
 *  EtherCAT technology and brand is only permitted in compliance with the
 *  industrial property and similar rights of Beckhoff Automation GmbH.
 *
 ****************************************************************************/

#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <time.h>
#include <math.h>
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>
#include "ecrt.h"
#include "EtherCAT.h"
#include "cmdpanel.h"
#include "lpf.h"
#include "poly_traj.h"
#include "Jacobian_S.h"
#include "z_transform.h"
#include "IK_1DOF.h"
#include "Dynamics_4DOF.h"
#include "IK_3DOF.h"
#include "control.h"
/****************************************************************************/

#define DRIVER_NUMBER 8
#define ENCODER_NUMBER 1
#define DOMAIN_NUMBER 9
// #define NUMBER 350014//350014

// Optional features
#define CONFIGURE_PDOS 1
// 任务周期（以 ns 为单位）

#define MAX_SAFE_STACK (8 * 1024) //保证安全访问而不会出现故障的最大堆栈大小


/****************************************************************************/

// EtherCAT
static ec_master_t *master = NULL;
static ec_master_state_t master_state = {};

static ec_domain_t *domain[DOMAIN_NUMBER];
static ec_domain_state_t domain_state[DOMAIN_NUMBER];


static ec_slave_config_t *sc[DOMAIN_NUMBER];
static ec_slave_config_state_t sc_ana_in_state[DOMAIN_NUMBER];

static uint8_t *domain_pd[DOMAIN_NUMBER];

#define BusCouplerPos1 0, 0
#define BusCouplerPos2 0, 1
#define BusCouplerPos3 0, 2
#define BusCouplerPos4 0, 3
#define BusCouplerPos5 0, 4
#define BusCouplerPos6 0, 5
#define BusCouplerPos7 0, 6
#define BusCouplerPos8 0, 7
#define BusCouplerPos9 0, 8
#define BusCouplerPos10 0, 9
#define BusCouplerPos11 0, 10
#define BusCouplerPos12 0, 11
#define BusCouplerPos13 0, 12
#define BusCouplerPos14 0, 13
#define BusCouplerPos15 0, 14
#define BusCouplerPos16 0, 15



#define DRIVERICE 0x0000009a, 0x00030924

#define ENCODERICE 0x00000b95, 0x00020310
// offsets for PDO entries


static unsigned int off_bytes_0x6040[DRIVER_NUMBER];
static unsigned int off_bits_0x6040[DRIVER_NUMBER];
static unsigned int off_bytes_0x6060[DRIVER_NUMBER];
static unsigned int off_bits_0x6060[DRIVER_NUMBER];
static unsigned int off_bytes_0x6041[DRIVER_NUMBER];
static unsigned int off_bits_0x6041[DRIVER_NUMBER];
static unsigned int off_bytes_0x6061[DRIVER_NUMBER];
static unsigned int off_bits_0x6061[DRIVER_NUMBER];
static unsigned int off_bytes_0x6064[DRIVER_NUMBER];
static unsigned int off_bits_0x6064[DRIVER_NUMBER];
static unsigned int off_bytes_0x60ff[DRIVER_NUMBER];
static unsigned int off_bits_0x60ff[DRIVER_NUMBER];
static unsigned int off_bytes_0x606C[DRIVER_NUMBER];
static unsigned int off_bits_0x606C[DRIVER_NUMBER];
static unsigned int off_bytes_0x6077[DRIVER_NUMBER];
static unsigned int off_bits_0x6077[DRIVER_NUMBER];

static unsigned int off_bytes_cm_1[ENCODER_NUMBER];
static unsigned int off_bits_cm_1[ENCODER_NUMBER];
static unsigned int off_bytes_cm_2[ENCODER_NUMBER];
static unsigned int off_bits_cm_2[ENCODER_NUMBER];
static unsigned int off_bytes_target_angle[ENCODER_NUMBER];
static unsigned int off_bits_target_angle[ENCODER_NUMBER];
static unsigned int off_bytes_ssi[ENCODER_NUMBER];
static unsigned int off_bits_ssi[ENCODER_NUMBER];
static unsigned int off_bytes_ssi1[ENCODER_NUMBER];
static unsigned int off_bits_ssi1[ENCODER_NUMBER];
static unsigned int off_bytes_ssi_2[ENCODER_NUMBER];
static unsigned int off_bits_ssi_2[ENCODER_NUMBER];
static unsigned int off_bytes_ssi_3[ENCODER_NUMBER];
static unsigned int off_bits_ssi_3[ENCODER_NUMBER];
static unsigned int off_bytes_ssi_4[ENCODER_NUMBER];
static unsigned int off_bits_ssi_4[ENCODER_NUMBER];
static unsigned int off_bytes_ssi_5[ENCODER_NUMBER];
static unsigned int off_bits_ssi_5[ENCODER_NUMBER];
static unsigned int off_bytes_ssi_6[ENCODER_NUMBER];
static unsigned int off_bits_ssi_6[ENCODER_NUMBER];
static unsigned int off_bytes_ssi_7[ENCODER_NUMBER];
static unsigned int off_bits_ssi_7[ENCODER_NUMBER];
static unsigned int off_bytes_ssi_8[ENCODER_NUMBER];
static unsigned int off_bits_ssi_8[ENCODER_NUMBER];
static unsigned int off_bytes_ain_1[ENCODER_NUMBER];
static unsigned int off_bits_ain_1[ENCODER_NUMBER];
static unsigned int off_bytes_ain_2[ENCODER_NUMBER];
static unsigned int off_bits_ain_2[ENCODER_NUMBER];
static unsigned int off_bytes_ain_3[ENCODER_NUMBER];
static unsigned int off_bits_ain_3[ENCODER_NUMBER];
static unsigned int off_bytes_ain_4[ENCODER_NUMBER];
static unsigned int off_bits_ain_4[ENCODER_NUMBER];
static unsigned int off_bytes_ain_5[ENCODER_NUMBER];
static unsigned int off_bits_ain_5[ENCODER_NUMBER];
static unsigned int off_bytes_ain_6[ENCODER_NUMBER];
static unsigned int off_bits_ain_6[ENCODER_NUMBER];
static unsigned int off_bytes_ain_7[ENCODER_NUMBER];
static unsigned int off_bits_ain_7[ENCODER_NUMBER];
static unsigned int off_bytes_ain_8[ENCODER_NUMBER];
static unsigned int off_bits_ain_8[ENCODER_NUMBER];



/*****************************************************************************/

/* Master 0, Slave 0-13
* Vendor ID:       0x0000009a
* Product code:    0x00030924
* Revision number: 0x00010420
*/
const ec_pdo_entry_reg_t domain1_regs[] = {
    {BusCouplerPos1,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[0], &off_bits_0x6040[0]},
    {BusCouplerPos1,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[0], &off_bits_0x6060[0]},
    {BusCouplerPos1,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[0], &off_bits_0x60ff[0]},
    {BusCouplerPos1,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[0], &off_bits_0x6041[0]},
    {BusCouplerPos1,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[0], &off_bits_0x6061[0]},
    {BusCouplerPos1,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[0], &off_bits_0x6064[0]},
    {BusCouplerPos1,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[0], &off_bits_0x606C[0]},
    {BusCouplerPos1,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[0], &off_bits_0x6077[0]},
    {}
};

const ec_pdo_entry_reg_t domain2_regs[] = {
    {BusCouplerPos2,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[1], &off_bits_0x6040[1]},
    {BusCouplerPos2,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[1], &off_bits_0x6060[1]},
    {BusCouplerPos2,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[1], &off_bits_0x60ff[1]},
    {BusCouplerPos2,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[1], &off_bits_0x6041[1]},
    {BusCouplerPos2,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[1], &off_bits_0x6061[1]},
    {BusCouplerPos2,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[1], &off_bits_0x6064[1]},
    {BusCouplerPos2,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[1], &off_bits_0x606C[1]},
    {BusCouplerPos2,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[1], &off_bits_0x6077[1]},
    {}
};

const ec_pdo_entry_reg_t domain3_regs[] = {
    {BusCouplerPos3,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[2], &off_bits_0x6040[2]},
    {BusCouplerPos3,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[2], &off_bits_0x6060[2]},
    {BusCouplerPos3,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[2], &off_bits_0x60ff[2]},
    {BusCouplerPos3,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[2], &off_bits_0x6041[2]},
    {BusCouplerPos3,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[2], &off_bits_0x6061[2]},
    {BusCouplerPos3,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[2], &off_bits_0x6064[2]},
    {BusCouplerPos3,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[2], &off_bits_0x606C[2]},
    {BusCouplerPos3,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[2], &off_bits_0x6077[2]},
    {}
};


const ec_pdo_entry_reg_t domain4_regs[] = {
    {BusCouplerPos4,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[3], &off_bits_0x6040[3]},
    {BusCouplerPos4,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[3], &off_bits_0x6060[3]},
    {BusCouplerPos4,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[3], &off_bits_0x60ff[3]},
    {BusCouplerPos4,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[3], &off_bits_0x6041[3]},
    {BusCouplerPos4,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[3], &off_bits_0x6061[3]},
    {BusCouplerPos4,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[3], &off_bits_0x6064[3]},
    {BusCouplerPos4,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[3], &off_bits_0x606C[3]},
    {BusCouplerPos4,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[3], &off_bits_0x6077[3]},
    {}
};

const ec_pdo_entry_reg_t domain5_regs[] = {
    {BusCouplerPos5,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[4], &off_bits_0x6040[4]},
    {BusCouplerPos5,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[4], &off_bits_0x6060[4]},
    {BusCouplerPos5,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[4], &off_bits_0x60ff[4]},
    {BusCouplerPos5,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[4], &off_bits_0x6041[4]},
    {BusCouplerPos5,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[4], &off_bits_0x6061[4]},
    {BusCouplerPos5,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[4], &off_bits_0x6064[4]},
    {BusCouplerPos5,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[4], &off_bits_0x606C[4]},
    {BusCouplerPos5,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[4], &off_bits_0x6077[4]},
    {}
};


const ec_pdo_entry_reg_t domain6_regs[] = {
    {BusCouplerPos6,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[5], &off_bits_0x6040[5]},
    {BusCouplerPos6,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[5], &off_bits_0x6060[5]},
    {BusCouplerPos6,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[5], &off_bits_0x60ff[5]},
    {BusCouplerPos6,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[5], &off_bits_0x6041[5]},
    {BusCouplerPos6,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[5], &off_bits_0x6061[5]},
    {BusCouplerPos6,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[5], &off_bits_0x6064[5]},
    {BusCouplerPos6,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[5], &off_bits_0x606C[5]},
    {BusCouplerPos6,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[5], &off_bits_0x6077[5]},
    {}
};

const ec_pdo_entry_reg_t domain7_regs[] = {
    {BusCouplerPos7,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[6], &off_bits_0x6040[6]},
    {BusCouplerPos7,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[6], &off_bits_0x6060[6]},
    {BusCouplerPos7,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[6], &off_bits_0x60ff[6]},
    {BusCouplerPos7,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[6], &off_bits_0x6041[6]},
    {BusCouplerPos7,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[6], &off_bits_0x6061[6]},
    {BusCouplerPos7,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[6], &off_bits_0x6064[6]},
    {BusCouplerPos7,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[6], &off_bits_0x606C[6]},
    {BusCouplerPos7,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[6], &off_bits_0x6077[6]},
    {}
};

const ec_pdo_entry_reg_t domain8_regs[] = {
{BusCouplerPos8,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[7], &off_bits_0x6040[7]},
{BusCouplerPos8,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[7], &off_bits_0x6060[7]},
{BusCouplerPos8,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[7], &off_bits_0x60ff[7]},
{BusCouplerPos8,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[7], &off_bits_0x6041[7]},
{BusCouplerPos8,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[7], &off_bits_0x6061[7]},
{BusCouplerPos8,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[7], &off_bits_0x6064[7]},
{BusCouplerPos8,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[7], &off_bits_0x606C[7]},
{BusCouplerPos8,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[7], &off_bits_0x6077[7]},
{}
};

// const static ec_pdo_entry_reg_t domain9_regs[] = {
// {BusCouplerPos9,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[8], &off_bits_0x6040[8]},
// {BusCouplerPos9,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[8], &off_bits_0x6060[8]},
// {BusCouplerPos9,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[8], &off_bits_0x60ff[8]},
// {BusCouplerPos9,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[8], &off_bits_0x6041[8]},
// {BusCouplerPos9,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[8], &off_bits_0x6061[8]},
// {BusCouplerPos9,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[8], &off_bits_0x6064[8]},
// {BusCouplerPos9,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[8], &off_bits_0x606C[8]},
// {}
// };

// const static ec_pdo_entry_reg_t domain10_regs[] = {
// {BusCouplerPos10,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[9], &off_bits_0x6040[9]},
// {BusCouplerPos10,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[9], &off_bits_0x6060[9]},
// {BusCouplerPos10,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[9], &off_bits_0x60ff[9]},
// {BusCouplerPos10,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[9], &off_bits_0x6041[9]},
// {BusCouplerPos10,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[9], &off_bits_0x6061[9]},
// {BusCouplerPos10,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[9], &off_bits_0x6064[9]},
// {BusCouplerPos10,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[9], &off_bits_0x606C[9]},
// {}
// };

// const static ec_pdo_entry_reg_t domain11_regs[] = {
// {BusCouplerPos11,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[10], &off_bits_0x6040[10]},
// {BusCouplerPos11,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[10], &off_bits_0x6060[10]},
// {BusCouplerPos11,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[10], &off_bits_0x60ff[10]},
// {BusCouplerPos11,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[10], &off_bits_0x6041[10]},
// {BusCouplerPos11,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[10], &off_bits_0x6061[10]},
// {BusCouplerPos11,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[10], &off_bits_0x6064[10]},
// {BusCouplerPos11,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[10], &off_bits_0x606C[10]},
// {}
// };

// const static ec_pdo_entry_reg_t domain12_regs[] = {
// {BusCouplerPos12,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[11], &off_bits_0x6040[11]},
// {BusCouplerPos12,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[11], &off_bits_0x6060[11]},
// {BusCouplerPos12,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[11], &off_bits_0x60ff[11]},
// {BusCouplerPos12,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[11], &off_bits_0x6041[11]},
// {BusCouplerPos12,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[11], &off_bits_0x6061[11]},
// {BusCouplerPos12,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[11], &off_bits_0x6064[11]},
// {BusCouplerPos12,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[11], &off_bits_0x606C[11]},
// {}
// };

// const static ec_pdo_entry_reg_t domain13_regs[] = {
// {BusCouplerPos13,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[12], &off_bits_0x6040[12]},
// {BusCouplerPos13,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[12], &off_bits_0x6060[12]},
// {BusCouplerPos13,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[12], &off_bits_0x60ff[12]},
// {BusCouplerPos13,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[12], &off_bits_0x6041[12]},
// {BusCouplerPos13,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[12], &off_bits_0x6061[12]},
// {BusCouplerPos13,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[12], &off_bits_0x6064[12]},
// {BusCouplerPos13,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[12], &off_bits_0x606C[12]},
// {}
// };

// const static ec_pdo_entry_reg_t domain14_regs[] = {
// {BusCouplerPos14,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[13], &off_bits_0x6040[13]},
// {BusCouplerPos14,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[13], &off_bits_0x6060[13]},
// {BusCouplerPos14,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[13], &off_bits_0x60ff[13]},
// {BusCouplerPos14,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[13], &off_bits_0x6041[13]},
// {BusCouplerPos14,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[13], &off_bits_0x6061[13]},
// {BusCouplerPos14,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[13], &off_bits_0x6064[13]},
// {BusCouplerPos14,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[13], &off_bits_0x606C[13]},
// {}
// };

/* Master 0, Slave 7
* Vendor ID:       0x01222222
* Product code:    0x00020310
* Revision number: 0x00020211
*/

const static ec_pdo_entry_reg_t domain9_regs[] = {
    // {Alias, Position, Vendor ID, Product Code, PDO Index, -Subindex, Offset}
    {BusCouplerPos9,ENCODERICE, 0x7020, 0x01, &off_bytes_cm_1[0], &off_bits_cm_1[0]},
    {BusCouplerPos9,ENCODERICE, 0x7020, 0x02, &off_bytes_cm_2[0], &off_bits_cm_2[0]},
    {BusCouplerPos9,ENCODERICE, 0x7030, 0x01, &off_bytes_target_angle[0], &off_bits_target_angle[0]},
    {BusCouplerPos9,ENCODERICE, 0x6000, 0x01, &off_bytes_ssi[0], &off_bits_ssi[0]},
    {BusCouplerPos9,ENCODERICE, 0x6000, 0x02, &off_bytes_ssi_2[0], &off_bits_ssi_2[0]},
    {BusCouplerPos9,ENCODERICE, 0x6000, 0x03, &off_bytes_ssi_3[0], &off_bits_ssi_3[0]},
    {BusCouplerPos9,ENCODERICE, 0x6000, 0x04, &off_bytes_ssi_4[0], &off_bits_ssi_4[0]},
    {BusCouplerPos9,ENCODERICE, 0x6000, 0x05, &off_bytes_ssi_5[0], &off_bits_ssi_5[0]},
    {BusCouplerPos9,ENCODERICE, 0x6000, 0x06, &off_bytes_ssi_6[0], &off_bits_ssi_6[0]},
    {BusCouplerPos9,ENCODERICE, 0x6000, 0x07, &off_bytes_ssi_7[0], &off_bits_ssi_7[0]},
    {BusCouplerPos9,ENCODERICE, 0x6000, 0x08, &off_bytes_ssi_8[0], &off_bits_ssi_8[0]},
    {BusCouplerPos9,ENCODERICE, 0x6010, 0x01, &off_bytes_ain_1[0], &off_bits_ain_1[0]},
    {BusCouplerPos9,ENCODERICE, 0x6010, 0x02, &off_bytes_ain_2[0], &off_bits_ain_2[0]},
    {BusCouplerPos9,ENCODERICE, 0x6010, 0x03, &off_bytes_ain_3[0], &off_bits_ain_3[0]},
    {BusCouplerPos9,ENCODERICE, 0x6010, 0x04, &off_bytes_ain_4[0], &off_bits_ain_4[0]},
    {BusCouplerPos9,ENCODERICE, 0x6010, 0x05, &off_bytes_ain_5[0], &off_bits_ain_5[0]},
    {BusCouplerPos9,ENCODERICE, 0x6010, 0x06, &off_bytes_ain_6[0], &off_bits_ain_6[0]},
    {BusCouplerPos9,ENCODERICE, 0x6010, 0x07, &off_bytes_ain_7[0], &off_bits_ain_7[0]},
    {BusCouplerPos9,ENCODERICE, 0x6010, 0x08, &off_bytes_ain_8[0], &off_bits_ain_8[0]},
    {}
};

// const static ec_pdo_entry_reg_t domain16_regs[] = {
//     // {Alias, Position, Vendor ID, Product Code, PDO Index, -Subindex, Offset}
//     {BusCouplerPos16,ENCODERICE, 0x7020, 0x01, &off_bytes_cm_1[1], &off_bits_cm_1[1]},
//     {BusCouplerPos16,ENCODERICE, 0x7020, 0x02, &off_bytes_cm_2[1], &off_bits_cm_2[1]},
//     {BusCouplerPos16,ENCODERICE, 0x7030, 0x01, &off_bytes_target_angle[1], &off_bits_target_angle[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6000, 0x01, &off_bytes_ssi[1], &off_bits_ssi[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6000, 0x02, &off_bytes_ssi_2[1], &off_bits_ssi_2[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6000, 0x03, &off_bytes_ssi_3[1], &off_bits_ssi_3[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6000, 0x04, &off_bytes_ssi_4[1], &off_bits_ssi_4[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6000, 0x05, &off_bytes_ssi_5[1], &off_bits_ssi_5[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6000, 0x06, &off_bytes_ssi_6[1], &off_bits_ssi_6[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6000, 0x07, &off_bytes_ssi_7[1], &off_bits_ssi_7[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6000, 0x08, &off_bytes_ssi_8[1], &off_bits_ssi_8[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6010, 0x01, &off_bytes_ain_1[1], &off_bits_ain_1[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6010, 0x02, &off_bytes_ain_2[1], &off_bits_ain_2[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6010, 0x03, &off_bytes_ain_3[1], &off_bits_ain_3[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6010, 0x04, &off_bytes_ain_4[1], &off_bits_ain_4[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6010, 0x05, &off_bytes_ain_5[1], &off_bits_ain_5[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6010, 0x06, &off_bytes_ain_6[1], &off_bits_ain_6[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6010, 0x07, &off_bytes_ain_7[1], &off_bits_ain_7[1]},
//     {BusCouplerPos16,ENCODERICE, 0x6010, 0x08, &off_bytes_ain_8[1], &off_bits_ain_8[1]},
//     {}
// };


static ec_pdo_entry_info_t slave_pdo_entries[] = {
    {0x6040, 0x00, 16}, /* Controlword */
    {0x6060, 0x00, 8}, /* Modes of operation */
    {0x60ff, 0x00, 32}, /* Target velocity */
    {0x6041, 0x00, 16},/* Statusword */
    {0x6061, 0x00, 8}, /* Modes of operation display */
    {0x6064, 0x00, 32}, /* Position actual value */
    {0x606C, 0x00, 32}, /* Velocity actual value */
    {0x6077, 0x00, 16}, /* Torque actual value */
};

static ec_pdo_info_t slave_pdos[] = {
    {0x1607, 3, slave_pdo_entries + 0}, /* RPDO1 Mapping */
    {0x1a07, 5, slave_pdo_entries + 3}, /* TPDO1 Mapping */
};

static ec_sync_info_t slave_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, slave_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 1, slave_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

static ec_pdo_entry_info_t slave_0_pdo_entries[] = {
    {0x7020, 0x01, 8}, /* Commond1 */
    {0x7020, 0x02, 8}, /* Commond2 */
    {0x7030, 0x01, 32}, /* Target Angle */
    {0x6000, 0x01, 32}, /* ssi */
    {0x6000, 0x02, 32}, /* ssi2 */
    {0x6000, 0x03, 32}, /* ssi3 */
    {0x6000, 0x04, 32}, /* ssi4 */
    {0x6000, 0x05, 32}, /* ssi5 */
    {0x6000, 0x06, 32}, /* ssi6 */
    {0x6000, 0x07, 32}, /* ssi7 */
    {0x6000, 0x08, 32}, /* ssi8 */
    {0x6010, 0x01, 16}, /* ain1 */
    {0x6010, 0x02, 16}, /* ain2 */
    {0x6010, 0x03, 16}, /* ain3 */
    {0x6010, 0x04, 16}, /* ain4 */
    {0x6010, 0x05, 16}, /* ain5 */
    {0x6010, 0x06, 16}, /* ain6 */
    {0x6010, 0x07, 16}, /* ain7 */
    {0x6010, 0x08, 16}, /* ain8 */
};

static ec_pdo_info_t slave_0_pdos[] = {
    {0x1601, 2, slave_0_pdo_entries + 0}, /* write commond of moulde */
    {0x1602, 1, slave_0_pdo_entries + 2}, /* write commond of moulde */
    {0x1a00, 8, slave_0_pdo_entries + 3}, /* read ssi of moudle */
    {0x1a05, 8, slave_0_pdo_entries + 11}, /* read ain of moudle */

};

static ec_sync_info_t slave_0_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 2, slave_0_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 2, slave_0_pdos + 2, EC_WD_DISABLE},
    {0xff}
};
// Application parameters
#define FREQUENCY 1000
#define PRIORITY 1
#define MAX_VELOCITY_1 90000
#define MAX_VELOCITY_2 160000
#define MAX_VELOCITY_3 112000
#define PERIODS_PER_SECOND   50
#define INIT_TIME 2
#define ERROR 0.1
#define RUNNING_TIME 300/*seconds*/

// #define DRIVER_NUMBER 14
// #define ENCODER_NUMBER 2
// #define DOMAIN_NUMBER 16
#define NUMBER 350014//350014

double Ts=PERIODS_PER_SECOND/1000.0;
double cycle_time_ns=1e9/FREQUENCY;
static double angle[48000];
static double angle1[48000];
static double angle2[48000];
// // Optional features
// #define CONFIGURE_PDOS 1
// // 任务周期（以 ns 为单位）

// #define MAX_SAFE_STACK (8 * 1024) //保证安全访问而不会出现故障的最大堆栈大小


/****************************************************************************/
//控制部分变量
//wrist  -10,10
static float Target_Position[DRIVER_NUMBER]={0,0,0,0,0,0,0,0};
static float Actual_Position[DRIVER_NUMBER];   
static float target_p[DRIVER_NUMBER];
static float actual_p[DRIVER_NUMBER];
static float target_p_last[DRIVER_NUMBER];
static float actual_p_last[DRIVER_NUMBER];
static float max_velocity[DRIVER_NUMBER]={0.9*MAX_VELOCITY_1,0.9*MAX_VELOCITY_1,0.9*MAX_VELOCITY_1,0.9*MAX_VELOCITY_1,
0.9*MAX_VELOCITY_1,0.9*MAX_VELOCITY_1,0.9*MAX_VELOCITY_1,0.9*MAX_VELOCITY_1};

static float offset_ssi[DRIVER_NUMBER];
static float constant_Kp[DRIVER_NUMBER]={40000*19.36/360,40000*19.36/360,40000*19.36/360,40000*19.36/360,
40000*19.36/360,40000*19.36/360,40000*19.36/360,40000*19.36/360};
static float rated_current[DRIVER_NUMBER]={8.49,8.49,8.49,8.49,8.49,8.49,8.49,8.49};
static float constant_Torque[DRIVER_NUMBER]={40.0/15.0,40.0/15.0,40.0/15.0,40.0/15.0,40.0/15.0,40.0/15.0,40.0/15.0,40.0/15.0};

static float Position_Kp[DRIVER_NUMBER]={15,15,15,15,15,15,15,15};
static float Position_Ki[DRIVER_NUMBER];
static float Position_Kd[DRIVER_NUMBER];
static float Error[DRIVER_NUMBER];
static float Error_Last[DRIVER_NUMBER];
static float Delta_Error[DRIVER_NUMBER];
static float Delta_Error_Last[DRIVER_NUMBER];
static float Integral[DRIVER_NUMBER];
static float Target_Velocity[DRIVER_NUMBER];
static float Actual_Velocity[DRIVER_NUMBER];
static float Actual_Torque[DRIVER_NUMBER];
static float Origin_Current[DRIVER_NUMBER];
static float Actual_Current[DRIVER_NUMBER];
static float Actual_joint_Torque[DRIVER_NUMBER];

static double values[NUMBER]; 

static CmdPanel *cmdptr = NULL;

static FILE *fp;

//程序状态变量
static unsigned int counter = 0;
static unsigned int counter1 = 0;
static unsigned int counter_slave = 0;
static unsigned int counter_domain = 0;
static unsigned int counter_loop= 0;
static unsigned int blink = 0x00;
static unsigned int flag = 0;
static unsigned int flag2 = 0;
static unsigned int stage = 0;
static unsigned int command = 0L;
static unsigned int flag_init[DRIVER_NUMBER];
static unsigned int flag_init_all;
static unsigned int flag_stop[DRIVER_NUMBER];
static unsigned int flag_stop_all;
static unsigned int flag_first[DRIVER_NUMBER];

// Timer
static unsigned int sig_alarms = 0;
static unsigned int user_alarms = 0;

static struct timeval tv1;
static struct timeval tv2;
static double time_diff;
static double time_test1;
static double time_test2;

static int ssi;
static unsigned int ain1;
static unsigned long ssi1;
static unsigned long dri;

static BiquadFilter filter[DRIVER_NUMBER];
float sampleRate = PERIODS_PER_SECOND;    // 采样率
float cutoffFreq = 1;      // 截止频率 1Hz

int fd=-1;
struct sockaddr_in saddr;
/****************************************************************************/
void check_domain_state(uint16_t slave_position)
{
    ec_domain_state_t ds;

    ecrt_domain_state(domain[slave_position], &ds);

    if (ds.working_counter != domain_state[slave_position].working_counter)
        //printf("Domain %d : WC %u.\n", slave_position, ds.working_counter);
    if (ds.wc_state != domain_state[slave_position].wc_state)
        //printf("Domain %d : State %u.\n", slave_position, ds.wc_state);

    domain_state[slave_position] = ds;
}

/*****************************************************************************/

/*****************************************************************************/

void check_master_state(void)
{
    // printf("check_master_state\n");
    ec_master_state_t ms;

    ecrt_master_state(master, &ms);

    if (ms.slaves_responding != master_state.slaves_responding)
        printf("%u slave(s).\n", ms.slaves_responding);
    if (ms.al_states != master_state.al_states)
        printf("AL states: 0x%02X.\n", ms.al_states);
    if (ms.link_up != master_state.link_up)
        printf("Link is %s.\n", ms.link_up ? "up" : "down");

    master_state = ms;
}

/*****************************************************************************/


void check_slave_config_states(int slave_position)
{
    // printf("check_slave_config_states\n");
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc[slave_position], &s);

    if (s.al_state != sc_ana_in_state[slave_position].al_state)
        printf("AnaIn%d: State 0x%02X.\n", slave_position, s.al_state);

    if (s.online != sc_ana_in_state[slave_position].online)
        printf("AnaIn%d: %s.\n", slave_position, s.online ? "online" : "offline");
    if (s.operational != sc_ana_in_state[slave_position].operational)
        printf("AnaIn%d: %soperational.\n", slave_position,
            s.operational ? "" : "Not ");

    sc_ana_in_state[slave_position] = s;
}



int config(){
    #if CONFIGURE_PDOS

if (!(sc[0] = ecrt_master_slave_config(
        master, BusCouplerPos1, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave1 configuration.\n");
    return -1;
}
if (!(sc[1] = ecrt_master_slave_config(
        master, BusCouplerPos2, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave2 configuration.\n");
    return -1;
}
if (!(sc[2] = ecrt_master_slave_config(
        master, BusCouplerPos3, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave3 configuration.\n");
    return -1;
}
if (!(sc[3]= ecrt_master_slave_config(
        master, BusCouplerPos4, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave4 configuration.\n");
    return -1;
}
if (!(sc[4] = ecrt_master_slave_config(
        master, BusCouplerPos5, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave5 configuration.\n");
    return -1;
}
if (!(sc[5] = ecrt_master_slave_config(
        master, BusCouplerPos6, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave6 configuration.\n");
    return -1;
}
if (!(sc[6] = ecrt_master_slave_config(
        master, BusCouplerPos7, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave7 configuration.\n");
    return -1;
}
if (!(sc[7] = ecrt_master_slave_config(
        master, BusCouplerPos8, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave8 configuration.\n");
    return -1;
}
if (!(sc[8] = ecrt_master_slave_config(
        master, BusCouplerPos9, ENCODERICE)))
{
    fprintf(stderr, "Failed to get slave15 configuration.\n");
    return -1;
}     
// if (!(sc[8] = ecrt_master_slave_config(
//         master, BusCouplerPos9, DRIVERICE)))
// {
//     fprintf(stderr, "Failed to get slave9 configuration.\n");
//     return -1;
// }
// if (!(sc[9] = ecrt_master_slave_config(
//         master, BusCouplerPos10, DRIVERICE)))
// {
//     fprintf(stderr, "Failed to get slave10 configuration.\n");
//     return -1;
// }
// if (!(sc[10] = ecrt_master_slave_config(
//         master, BusCouplerPos11, DRIVERICE)))
// {
//     fprintf(stderr, "Failed to get slave11 configuration.\n");
//     return -1;
// }
// if (!(sc[11] = ecrt_master_slave_config(
//         master, BusCouplerPos12, DRIVERICE)))
// {
//     fprintf(stderr, "Failed to get slave12 configuration.\n");
//     return -1;
// }     
// if (!(sc[12] = ecrt_master_slave_config(
//         master, BusCouplerPos13, DRIVERICE)))
// {
//     fprintf(stderr, "Failed to get slave13 configuration.\n");
//     return -1;
// }
// if (!(sc[13] = ecrt_master_slave_config(
//         master, BusCouplerPos14, DRIVERICE)))
// {
//     fprintf(stderr, "Failed to get slave14 configuration.\n");
//     return -1;
// }
// if (!(sc[14] = ecrt_master_slave_config(
//         master, BusCouplerPos15, ENCODERICE)))
// {
//     fprintf(stderr, "Failed to get slave15 configuration.\n");
//     return -1;
// }     
// if (!(sc[15] = ecrt_master_slave_config(
//         master, BusCouplerPos16, ENCODERICE)))
// {
//     fprintf(stderr, "Failed to get slave16 configuration.\n");
//     return -1;
// }     

    


        /* Configure AKD flexible PDO */
    // printf("Configuring AKD with flexible PDO...\n");
    // printf("Define RxPDO...\n");

    // /* Define RxPdo */

    // 设置PDOS，利⽤sc、EC_END、对⻬信息
    printf("Configuring PDOs...\n");
    int count;
    for(count=0;count<DRIVER_NUMBER;count++){
        if (ecrt_slave_config_pdos(sc[count], EC_END, slave_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }
    }   
    for(count=DRIVER_NUMBER;count<DOMAIN_NUMBER;count++){
        if (ecrt_slave_config_pdos(sc[count], EC_END, slave_0_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }
    }
    
        if (ecrt_domain_reg_pdo_entry_list(domain[0], domain1_regs)) 
    {
        fprintf(stderr, "PDO1 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[1], domain2_regs)) 
    {
        fprintf(stderr, "PDO2 entry registration failed!\n");
        return -1;
    }    
        if (ecrt_domain_reg_pdo_entry_list(domain[2], domain3_regs)) 
    {
        fprintf(stderr, "PDO3 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[3], domain4_regs)) 
    {
        fprintf(stderr, "PDO4 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[4], domain5_regs)) 
    {
        fprintf(stderr, "PDO5 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[5], domain6_regs)) 
    {
        fprintf(stderr, "PDO6 entry registration failed!\n");
        return -1;
    }    
        if (ecrt_domain_reg_pdo_entry_list(domain[6], domain7_regs)) 
    {
        fprintf(stderr, "PDO7 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[7], domain8_regs)) 
    {
        fprintf(stderr, "PDO8 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[8], domain9_regs)) 
    {
        fprintf(stderr, "PDO9 entry registration failed!\n");
        return -1;
    }    
    //     if (ecrt_domain_reg_pdo_entry_list(domain[9], domain10_regs)) 
    // {
    //     fprintf(stderr, "PDO10 entry registration failed!\n");
    //     return -1;
    // }
    //     if (ecrt_domain_reg_pdo_entry_list(domain[10], domain11_regs)) 
    // {
    //     fprintf(stderr, "PDO11 entry registration failed!\n");
    //     return -1;
    // }
    //     if (ecrt_domain_reg_pdo_entry_list(domain[11], domain12_regs)) 
    // {
    //     fprintf(stderr, "PDO12 entry registration failed!\n");
    //     return -1;
    // }
    //     if (ecrt_domain_reg_pdo_entry_list(domain[12], domain13_regs)) 
    // {
    //     fprintf(stderr, "PDO13 entry registration failed!\n");
    //     return -1;
    // }    
    //     if (ecrt_domain_reg_pdo_entry_list(domain[13], domain14_regs)) 
    // {
    //     fprintf(stderr, "PDO14 entry registration failed!\n");
    //     return -1;
    // }
    //     if (ecrt_domain_reg_pdo_entry_list(domain[14], domain15_regs)) 
    // {
    //     fprintf(stderr, "PDO15 entry registration failed!\n");
    //     return -1;
    // }     
    //     if (ecrt_domain_reg_pdo_entry_list(domain[15], domain16_regs)) 
    // {
    //     fprintf(stderr, "PDO16 entry registration failed!\n");
    //     return -1;
    // }     
    return 0;
    #endif
}

void driver_enable(uint16_t slave_position){
int i=0;
// while( (() & 0x6f) != 0x27){
if ((EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6041[slave_position]) & 0x0250) == 592)
{
    // printf("*********************Servo Power on*********************\n");
    EC_WRITE_U8(domain_pd[slave_position]+off_bytes_0x6060[slave_position], 0x03);
    EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position], 0x06);

}
if ((EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6041[slave_position]) & 0x031) == 49)
    {
        if ((EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6041[slave_position]) & 0x033) == 51)
        {   //if(EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position])==0x0f){
            //     return;
            // }
            // printf("*********************Servo Enable*********************\n");
            EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position], 0x0f);

        }
        else
        {   //if(EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position])==0x07){
            //    return;
            //}
            // printf("*********************Servo Waitting*********************\n");
            EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position], 0x07);
        }    
    }
}


void driver_disable(uint16_t slave_position)
{
    EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position],0x06);
}


/* Function Definitions */
// static double argInit_real_T(void)
// {
// return 0.0;
// }
// static void argInit_4x4_real_T(double result[16])
// {
// int i;
// /* Loop over the array to initialize each element. */
// for (i = 0; i < 16; i++) {
//     /* Set the value of the array element.
// Change this value to the value that the application requires. */
//     result[i] = argInit_real_T();
// }
// }


void reading_ssi(){
    uint32_t data_pointer[1];
    float angle_all[1];
    float angle;
    float last_angle[DRIVER_NUMBER];
    for (int i= 0; i < DRIVER_NUMBER; i++) {
        last_angle[i]=Actual_Position[i];
    }
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_4[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[0]=angle_all[0];  
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_3[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[1]=angle_all[0];
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_2[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[2]=angle_all[0];   
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[3]=angle_all[0];
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_5[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[4]=angle_all[0]; 
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_6[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[5]=angle_all[0];
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_7[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[6]=angle_all[0];
    ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER] + off_bytes_ssi_8[0]);
    data_pointer[0]=ssi;
    memcpy(angle_all, data_pointer, sizeof(data_pointer));
    Actual_Position[7]=angle_all[0];

    for (int i= 0; i < DRIVER_NUMBER; i++) {
        if(abs(last_angle[i]-Actual_Position[i])>5 && abs(last_angle[i]-Actual_Position[i])<355 &&last_angle[i]!=0){
            Actual_Position[i]=last_angle[i];
        }
    }
    // ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER+1] + off_bytes_ssi[1]);
    // data_pointer[0]=ssi;
    // memcpy(angle_all, data_pointer, sizeof(data_pointer));
    // Actual_Position[7]=angle_all[0];  
    // ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER+1] + off_bytes_ssi_2[1]);
    // data_pointer[0]=ssi;
    // memcpy(angle_all, data_pointer, sizeof(data_pointer));
    // Actual_Position[8]=angle_all[0];
    // ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER+1] + off_bytes_ssi_3[1]);
    // data_pointer[0]=ssi;
    // memcpy(angle_all, data_pointer, sizeof(data_pointer));
    // Actual_Position[9]=angle_all[0];   
    // ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER+1] + off_bytes_ssi_4[1]);
    // data_pointer[0]=ssi;
    // memcpy(angle_all, data_pointer, sizeof(data_pointer));
    // Actual_Position[10]=angle_all[0];
    // ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER+1] + off_bytes_ssi_5[1]);
    // data_pointer[0]=ssi;
    // memcpy(angle_all, data_pointer, sizeof(data_pointer));
    // Actual_Position[11]=angle_all[0]; 
    // ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER+1] + off_bytes_ssi_6[1]);
    // data_pointer[0]=ssi;
    // memcpy(angle_all, data_pointer, sizeof(data_pointer));
    // Actual_Position[12]=angle_all[0];
    // ssi=EC_READ_U32(domain_pd[DRIVER_NUMBER+1] + off_bytes_ssi_7[1]);
    // data_pointer[0]=ssi;
    // memcpy(angle_all, data_pointer, sizeof(data_pointer));
    // Actual_Position[13]=angle_all[0];
    
    

    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
            ssi=EC_READ_U32(domain_pd[counter_slave] + off_bytes_0x606C[counter_slave]);
            data_pointer[0]=ssi;
            memcpy(angle_all, data_pointer, sizeof(data_pointer));
            Actual_Velocity[counter_slave]=angle_all[0];
    }

    printf("motor position:");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        while( (Actual_Position[counter_slave]>180) || (Actual_Position[counter_slave]<-180)){
        if(Actual_Position[counter_slave]>180){
            Actual_Position[counter_slave]=Actual_Position[counter_slave]-360;
        }
        else if(Actual_Position[counter_slave]<-180){
            Actual_Position[counter_slave]=Actual_Position[counter_slave]+360;
        }
        }
        printf("%.6f  ",Actual_Position[counter_slave]);  
    }
    printf("\n");

    // printf("target position:");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        // printf("%.6f  ",Target_Position[counter_slave]);  
    }
    // printf("\n");
    // printf("motor velocity:");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        // printf("%.6f  ",Actual_Velocity[counter_slave]);  
    }
    // printf("\n");

}

void reading_driver(){
    uint32_t data_pointer[1];
    float angle_all[1];
    float angle;
    
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        ssi=EC_READ_U32(domain_pd[counter_slave] + off_bytes_0x6064[counter_slave]);
        Actual_Position[counter_slave]=(float)ssi;
        Actual_Position[counter_slave]=Actual_Position[counter_slave]/constant_Kp[counter_slave];
        // data_pointer[0]=ssi;
        // memcpy(angle_all, data_pointer, sizeof(data_pointer));
        // Actual_Position[counter_slave]=angle_all[0];  
    }

    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        ssi=EC_READ_U32(domain_pd[counter_slave] + off_bytes_0x606C[counter_slave]);
        Actual_Velocity[counter_slave]=(float)ssi;
    }

    printf("motor position:");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        while( (Actual_Position[counter_slave]>180) || (Actual_Position[counter_slave]<-180)){
        if(Actual_Position[counter_slave]>180){
            Actual_Position[counter_slave]=Actual_Position[counter_slave]-360;
        }
        else if(Actual_Position[counter_slave]<-180){
            Actual_Position[counter_slave]=Actual_Position[counter_slave]+360;
        }
        }
        printf("%.6f  ",Actual_Position[counter_slave]);  
    }
    printf("\n");
    // printf("target position:");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        printf("%.6f  ",Target_Position[counter_slave]);  
    }
    // printf("\n");
    // printf("motor velocity:");
    // for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        // printf("%.6f  ",Actual_Velocity[counter_slave]);  
    // }
    // printf("\n");

}
//力矩前馈项
double torque_ff[4];

double t1_f=0,t2_f=0,t3_f=0,t4_f=0;
double sample_counter=0;
double flag_ff=0;

static int flag_sigmoid[DRIVER_NUMBER];// state:0 low, 1 high, 2 rising, 3 down
static double t0[DRIVER_NUMBER];
static double c0[DRIVER_NUMBER];
static double c_last[DRIVER_NUMBER];
double sigmoid(double t,double t0,double constant_time){
    double result;
    double a=constant_time;//3s
    result = 1/( exp( ( -8*(t-t0)/a + 4 ) + 1 )  );
}

// 状态枚举
typedef enum {
    STATE_IN_DEAD_ZONE,      // 在死区内
    STATE_ACTIVATING,        // 正在激活
    STATE_DEACTIVATING,      // 正在衰减
    STATE_ACTIVE             // 已激活（死区外稳定状态）
} ProcessState;

// 参数结构体
typedef struct {
    double dead_zone_lower;  // 死区下限
    double dead_zone_upper;  // 死区上限
    double activation_time;  // 激活时间（秒）
    double deactivation_time; // 衰减时间（秒）
} DeadZoneSmoothParams;

// 处理上下文（记录状态）
typedef struct {
    ProcessState state;      // 当前状态
    double last_output;      // 上一时刻输出
    double last_input;       // 上一时刻输入
    double state_start_time; // 状态开始时间
    double last_time;        // 上一时刻时间
    double activation_start_value; // 激活开始时的输出值
    double deactivation_start_value; // 衰减开始时的输出值
    bool first_call;         // 首次调用标志
} DeadZoneSmoothContext;

// 初始化上下文
void dead_zone_init_context(DeadZoneSmoothContext *ctx) {
    ctx->state = STATE_IN_DEAD_ZONE;
    ctx->last_output = 0.0;
    ctx->last_input = 0.0;
    ctx->state_start_time = 0.0;
    ctx->last_time = 0.0;
    ctx->activation_start_value = 0.0;
    ctx->deactivation_start_value = 0.0;
    ctx->first_call = true;
}

// 三次平滑插值函数（在t=0和t=1处导数为0）
static double smooth_interpolate(double t) {
    if (t <= 0.0) return 0.0;
    if (t >= 1.0) return 1.0;
    
    // 三次平滑插值：3t² - 2t³
    return t * t * (3.0 - 2.0 * t);
}

// 死区平滑处理主函数
double dead_zone_smooth_process(double input, double current_time, 
                                DeadZoneSmoothParams params,
                                DeadZoneSmoothContext *ctx) {
    
    // 如果是首次调用，初始化时间
    if (ctx->first_call) {
        ctx->last_time = current_time;
        ctx->state_start_time = current_time;
        ctx->first_call = false;
    }
    
    // 计算时间增量
    double dt = current_time - ctx->last_time;
    if (dt <= 0.0) dt = 0.001; // 防止dt为0
    
    bool in_dead_zone = (input >= params.dead_zone_lower && input <= params.dead_zone_upper);
    double output = 0.0;
    
    // 状态机处理
    switch (ctx->state) {
        case STATE_IN_DEAD_ZONE:
            if (!in_dead_zone) {
                // 信号超出死区，开始激活
                ctx->state = STATE_ACTIVATING;
                ctx->state_start_time = current_time;
                ctx->activation_start_value = ctx->last_output;
                ctx->last_input = input;
                
                // 激活进度为0，从上一时刻输出开始
                output = ctx->last_output;
            } else {
                // 保持在死区内，输出为0
                output = 0.0;
            }
            break;
            
        case STATE_ACTIVATING:
            if (in_dead_zone) {
                // 信号回到死区，开始衰减
                ctx->state = STATE_DEACTIVATING;
                ctx->state_start_time = current_time;
                ctx->deactivation_start_value = ctx->last_output;
                ctx->last_input = input;
                
                // 衰减进度为0，从当前输出开始
                output = ctx->last_output;
            } else {
                // 继续激活
                double elapsed_time = current_time - ctx->state_start_time;
                
                if (elapsed_time >= params.activation_time) {
                    // 激活完成，进入激活状态
                    ctx->state = STATE_ACTIVE;
                    output = input; // 激活完成时输出等于当前输入
                } else {
                    // 正在激活过程中
                    double progress = smooth_interpolate(elapsed_time / params.activation_time);
                    
                    // 从激活开始时的值平滑过渡到当前输入值
                    double target_value = input; // 目标是当前输入值
                    output = ctx->activation_start_value + 
                            (target_value - ctx->activation_start_value) * progress;
                }
            }
            break;
            
        case STATE_DEACTIVATING:
            if (!in_dead_zone) {
                // 信号超出死区，开始激活
                ctx->state = STATE_ACTIVATING;
                ctx->state_start_time = current_time;
                ctx->activation_start_value = ctx->last_output;
                ctx->last_input = input;
                
                // 激活进度为0，从当前输出开始
                output = ctx->last_output;
            } else {
                // 继续衰减
                double elapsed_time = current_time - ctx->state_start_time;
                
                if (elapsed_time >= params.deactivation_time) {
                    // 衰减完成，回到死区状态
                    ctx->state = STATE_IN_DEAD_ZONE;
                    output = 0.0;
                } else {
                    // 正在衰减过程中
                    double progress = smooth_interpolate(elapsed_time / params.deactivation_time);
                    
                    // 从衰减开始时的值平滑衰减到0
                    output = ctx->deactivation_start_value * (1.0 - progress);
                }
            }
            break;
            
        case STATE_ACTIVE:
            if (in_dead_zone) {
                // 信号回到死区，开始衰减
                ctx->state = STATE_DEACTIVATING;
                ctx->state_start_time = current_time;
                ctx->deactivation_start_value = ctx->last_output;
                ctx->last_input = input;
                
                // 衰减进度为0，从当前输出开始
                output = ctx->last_output;
            } else {
                // 保持在激活状态，输出直接等于当前输入
                output = input;
            }
            break;
    }
    
    // 更新上下文
    ctx->last_output = output;
    ctx->last_time = current_time;
    ctx->last_input = input;
    
    return output;
}

// 重置上下文状态
void dead_zone_reset_context(DeadZoneSmoothContext *ctx) {
    ctx->state = STATE_IN_DEAD_ZONE;
    ctx->last_output = 0.0;
    ctx->last_input = 0.0;
    ctx->state_start_time = 0.0;
    ctx->last_time = 0.0;
    ctx->activation_start_value = 0.0;
    ctx->deactivation_start_value = 0.0;
    ctx->first_call = true;
}

// 简化版本：更清晰的实现
typedef struct {
    ProcessState state;
    double last_output;
    double state_start_value;
    double state_start_time;
    double last_time;
} SimpleDeadZoneContext;

double simple_dead_zone_process(double input, double current_time, 
                                DeadZoneSmoothParams params,
                                SimpleDeadZoneContext *ctx) {
    
    static bool initialized = false;
    if (!initialized) {
        ctx->state = STATE_IN_DEAD_ZONE;
        ctx->last_output = 0.0;
        ctx->state_start_value = 0.0;
        ctx->state_start_time = current_time;
        ctx->last_time = current_time;
        initialized = true;
    }
    
    double dt = current_time - ctx->last_time;
    if (dt <= 0.0) dt = 0.001;
    
    bool in_dead_zone = (input >= params.dead_zone_lower && input <= params.dead_zone_upper);
    double output = ctx->last_output;
    
    // 状态转移
    if (in_dead_zone && ctx->state != STATE_IN_DEAD_ZONE && ctx->state != STATE_DEACTIVATING) {
        // 进入死区，开始衰减
        ctx->state = STATE_DEACTIVATING;
        ctx->state_start_time = current_time;
        ctx->state_start_value = ctx->last_output;
    } else if (!in_dead_zone && ctx->state != STATE_ACTIVE && ctx->state != STATE_ACTIVATING) {
        // 离开死区，开始激活
        ctx->state = STATE_ACTIVATING;
        ctx->state_start_time = current_time;
        ctx->state_start_value = ctx->last_output;
    }
    
    // 状态处理
    switch (ctx->state) {
        case STATE_IN_DEAD_ZONE:
            output = 0.0;
            break;
            
        case STATE_ACTIVATING: {
            double elapsed = current_time - ctx->state_start_time;
            if (elapsed >= params.activation_time) {
                ctx->state = STATE_ACTIVE;
                output = input;
            } else {
                double progress = smooth_interpolate(elapsed / params.activation_time);
                output = ctx->state_start_value + (input - ctx->state_start_value) * progress;
            }
            break;
        }
            
        case STATE_DEACTIVATING: {
            double elapsed = current_time - ctx->state_start_time;
            if (elapsed >= params.deactivation_time) {
                ctx->state = STATE_IN_DEAD_ZONE;
                output = 0.0;
            } else {
                double progress = smooth_interpolate(elapsed / params.deactivation_time);
                output = ctx->state_start_value * (1.0 - progress);
            }
            break;
        }
            
        case STATE_ACTIVE:
            output = input;
            break;
    }
    
    ctx->last_output = output;
    ctx->last_time = current_time;
    return output;
}

DeadZoneSmoothParams params = {
        .dead_zone_lower = -1.0,
        .dead_zone_upper = 1.0,
        .activation_time = 0.5,     // 0.5秒激活时间
        .deactivation_time = 0.3,   // 0.3秒衰减时间
    };
    
// 初始化上下文
DeadZoneSmoothContext ctx[DRIVER_NUMBER];


void reading_current(){
    int16_t tra;
    double current;
    double input;
    double output;
    double c1, c2, c3, c4;
    double t1, t2, t3, t4;
    double tr, tp, ty;
    double cr_tmp, cp_tmp, cy_tmp;
    double Px_tmp, Py_tmp, Pz_tmp;

    double Current_threshold[4] = {3,3,3,3};
    // printf("motor current and torque:\n");
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        tra=EC_READ_S16(domain_pd[counter_slave] + off_bytes_0x6077[counter_slave]);
        current=((double)tra)/1000.0*rated_current[counter_slave];
        // printf("%.3f ",torque);         
        input = current; 
        Origin_Current[counter_slave]=current;
        output = processSample(&filter[counter_slave], input);
        //output = input;
        Actual_Current[counter_slave]=output;
        //死区+激活函数
        double constant_time=1.5;
        double t0_tmp;
        double t_tmp;
        double output1;
        // if( output <Current_threshold && output > -Current_threshold ){
        //     output1 = 0;
        // }
        // else{
        //     output1 = output;
        // }

        output1 = output;
        c_last[counter_slave]=output1;
        // if( output1 <Current_threshold && output1 > -Current_threshold ){
        //     output1=0;
        // }
        
        Actual_Torque[counter_slave]=output1*constant_Torque[counter_slave];

        

        // if(abs(Actual_Torque[counter_slave])<1){
        //     Actual_Torque[counter_slave]=0;
        // }

        // printf("Current: %.3f A , Torque: %.3f Nm ",Actual_Current[counter_slave],Actual_Torque[counter_slave]);
        // printf("\n");
    }
        // Actual_Torque[0]=Actual_Torque[0]+0.3333;
        // Actual_Torque[1]=Actual_Torque[1]+0.3333;
        // Actual_Torque[2]=Actual_Torque[2]+0.3333;
        // Actual_Torque[3]=Actual_Torque[3]+1;
        
        printf("%f %f %f %f\n",Actual_Torque[0],Actual_Torque[1],Actual_Torque[2],Actual_Torque[3]);
    // if(flag_ff){
    //     Actual_Torque[0]=Actual_Torque[0]-t1_f;
    //     Actual_Torque[1]=Actual_Torque[1]-t2_f;
    //     Actual_Torque[2]=Actual_Torque[2]-t3_f;
    //     Actual_Torque[3]=Actual_Torque[3]-t4_f;
    //     printf("ff applied t1: %.3f t2: %.3f t3: %.3f t4: %.3f\n", t1_f, t2_f, t3_f, t4_f);
    // }
    // printf("\n");
        c1 = Actual_Position[0]; c2 = Actual_Position[1]; c3 = Actual_Position[2]; c4 = Actual_Position[3];
        t1 = Actual_Torque[0]; t2 = Actual_Torque[1]; t3 = Actual_Torque[2]; t4 = Actual_Torque[3];

        Jacobian_S(c1/180*3.1415926, c2/180*3.1415926, c3/180*3.1415926, c4/180*3.1415926, t1,
                    t2, t3, &cr_tmp, &cp_tmp, &cy_tmp,
                    &Px_tmp, &Py_tmp, &Pz_tmp, &tr,
                    &tp, &ty);
        


        
        Actual_joint_Torque[0]=tr;
        Actual_joint_Torque[1]=tp;
        Actual_joint_Torque[2]=ty;
        Actual_joint_Torque[3]=t4;
        for (int i=0;i<4;i++){
            if( Actual_joint_Torque[i] < Current_threshold[i] && Actual_joint_Torque[i] > - Current_threshold[i] ){
                Actual_joint_Torque[i] = 0;
            }
            else{
                Actual_joint_Torque[i] =Actual_joint_Torque[i];
            }
        }
        Actual_joint_Torque[3] =Actual_joint_Torque[3]+1;
        Actual_joint_Torque[1] =Actual_joint_Torque[1]+1;

        c1 = Actual_Position[4];c2 = Actual_Position[5]; c3 = Actual_Position[6]; c4 = Actual_Position[7];
        t1 = Actual_Torque[4];t2 = Actual_Torque[5]; t3 = Actual_Torque[6];

        Jacobian_S(c1/180*3.1415926, c2/180*3.1415926, c3/180*3.1415926, c4/180*3.1415926, t1,
                    t2, t3, &cr_tmp, &cp_tmp, &cy_tmp,
                    &Px_tmp, &Py_tmp, &Pz_tmp, &tr,
                    &tp, &ty);

        Actual_joint_Torque[4]=tr;
        Actual_joint_Torque[5]=tp;
        Actual_joint_Torque[6]=ty;
        Actual_joint_Torque[7]=Actual_Torque[7];
        // print joint torque
        // printf("Joint Torque r : %.3f p : %.3f y : %.3f \n", Actual_joint_Torque[0], Actual_joint_Torque[1], Actual_joint_Torque[2]);
        // printf("Joint Torque r : %.3f p : %.3f y : %.3f \n", Actual_joint_Torque[4], Actual_joint_Torque[5], Actual_joint_Torque[6]);
    // printf("\n");
    // printf("%f ",(float)EC_READ_S16(domain_pd[3] + off_bytes_0x6077[3]));
}

void control_pid(uint16_t slave_position){
    if(!flag_first[slave_position]){
        target_p_last[slave_position]=Target_Position[slave_position];
        actual_p_last[slave_position]=Actual_Position[slave_position];
        flag_first[slave_position]=1;
    }

    target_p[slave_position]=Target_Position[slave_position];
    actual_p[slave_position]=Actual_Position[slave_position];


    if((abs(target_p[slave_position]-target_p_last[slave_position])>20)){
        target_p[slave_position]=target_p_last[slave_position];
    }
    if(abs(actual_p[slave_position]-actual_p_last[slave_position])>20){
        actual_p[slave_position]=actual_p_last[slave_position];
    }

    target_p_last[slave_position]=target_p[slave_position];
    actual_p_last[slave_position]=actual_p[slave_position];

    Error[slave_position]=target_p[slave_position]-actual_p[slave_position];
    if(Error[slave_position]>180){
        Error[slave_position]-=360;
    }
    else if(Error[slave_position]<-180){
        Error[slave_position]+=360;
    }
    //printf("Error = %f ,",Error[slave_position]);
    Delta_Error[slave_position]=Error[slave_position]-Error_Last[slave_position];
    Integral[slave_position]=Integral[slave_position]+Error[slave_position];
    //printf("Delta_Error = %f ,",Delta_Error[slave_position]);
    Target_Velocity[slave_position]=Position_Kp[slave_position]*Error[slave_position]+Position_Ki[slave_position]*Integral[slave_position]+Position_Kd[slave_position]*Delta_Error[slave_position];
    //速度限制
    Target_Velocity[slave_position]= constant_Kp[slave_position] * Target_Velocity[slave_position];
    if(Target_Velocity[slave_position]>max_velocity[slave_position]){
        Target_Velocity[slave_position]=max_velocity[slave_position];
    }
    else if(Target_Velocity[slave_position]<-max_velocity[slave_position]){
        Target_Velocity[slave_position]=-max_velocity[slave_position];
    }
    //printf("Target_Velocity = %f \n",Target_Velocity[slave_position]);
    
    Error_Last[slave_position]=Error[slave_position];
    Delta_Error_Last[slave_position]=Delta_Error[slave_position];
    // printf("Target_Position=%f ,",target_p[slave_position]);
    // printf("Actual_Position=%f\n ",actual_p[slave_position]);
    
    EC_WRITE_S32(domain_pd[slave_position]+off_bytes_0x60ff[slave_position],(int)Target_Velocity[slave_position]);
    // printf("Target_Velocity =%f \n",EC_READ_S32(domain_pd[6-slave_position]+off_bytes_0x60ff[6-slave_position]));
}


// void main_IK_7DOF(void)
// {
//   double R[16]={-0.0000,1.0000,0.0000,0,-0.8819,0.0000,-0.4714,0,-0.4714,-0.0000,0.8819,0,215.7621,332.6608,-20.2120,1.0000};
//   double c1;
//   double c2;
//   double c3;
//   double c4;
//   double c5;
//   double c6;
//   double c7;
//   double phi=-0.2618;
//   double l1=320;
//   double l2=235;
//   double Px=238.6386;       
//   double Py=332.6608;
//   double Pz=89.2800; 
//   /* Initialize function 'IK_7DOF' input arguments. */
//   /* Initialize function input argument 'R'. */
//   /* Call the entry-point 'IK_7DOF'. */
//   /* Call the entry-point 'IK_7DOF'. */
//   IK_7DOF(R, phi, l1, l2, Px, Py, Pz, &c1, &c2,
//           &c3, &c4, &c5, &c6, &c7);
// //   printf("theta:%lf %lf %lf %lf %lf %lf %lf \n ",c1,c2,c3,c4,c5,c6,c7);
  
// }
parameters_compliance impedance_params={.Md=0, .Kd=0, .Bd=0};
parameters_compliance admittance_params={.Md=1, .Kd=3, .Bd=5}; //3 3 5

int flag_P_init=0;

double Fe_d[3];

double alpha = 0.87266462599716477;
double beta1 = 1.5707963267948966;
double beta2 = 2.0943951023931953;
double gama = 1.0471975511965976;
double delta = 0.52359877559829882;
double twist_angle = -1.0471975511965976;
double c0LL = -1.298210328476112;
double c0RR = -1.52502572060903;
double c0MM = -0.30696770204475443;

double c1_a = 0, c2_a = 0, c3_a = 0, c4_a = 0;
double t1_a = 1, t2_a = 1, t3_a = 1;
double tr_a, tp_a, ty_a, t4_a;
double cr_a, cp_a, cy_a;
double Px_a, Py_a, Pz_a;

static double Px_r=(315)/1000.0;
static double Py_r=(343)/1000.0;
static double Pz_r=0/1000.0;
static double cy_r=0;

double c4r,crr,cpr,cyr;

double Vx_a, Vy_a, Vz_a;
double Ax_a, Ay_a, Az_a;
double Vx_r, Vy_r, Vz_r;
double Ax_r, Ay_r, Az_r;
double w4, wr, wp, wy;
double dw4, dwr, dwp, dwy;

// 状态变量（需要在多次调用之间保持）
double state_CR = 0, state_CP = 0, state_CY = 0, state_CE = 0;
double state_WR = 0, state_WP = 0, state_WY = 0, state_WE = 0;
double state_dWR = 0, state_dWP = 0, state_dWY = 0, state_dWE = 0;
int initialized = 0;

// 输出变量
double cr, cp, cy, ce, c1, c2, c3, c4;

// 假设的输入值 - 您需要根据实际情况提供这些值
double wrr = 0, wpr = 0, wyr = 0, wer = 0;
double dwrr = 0, dwpr = 0, dwyr = 0, dwer = 0;
double T_joint_r = 0, T_joint_p = 0, T_joint_y = 0, T_joint_e = 0;

DelayFilter* delay_filter[7];

DerivativeFilter* derivative_filter[20];

double A[16];
double ty_d, tr_d, tp_d,
       t4_d, B[4];

double t_joint[4];

double c[4];


//力矩前馈函数
// void torque_feedforward(double t1_ff, double t2_ff,
//                         double t3_ff,  double t4_ff, double *num_sample){
//     //计算力矩前馈
//     if (*num_sample<200){
//         t1_f=t1_f+t1_ff;
//         t2_f=t2_f+t2_ff;
//         t3_f=t3_f+t3_ff;
//         t4_f=t4_f+t4_ff;
//         printf("t1_ff:%f t2_ff:%f t3_ff:%f t4_ff:%f\n",t1_ff,t2_ff,t3_ff,t4_ff);
//     }
//     else{
//         t1_f=t1_f/200;
//         t2_f=t2_f/200;
//         t3_f=t3_f/200;
//         t4_f=t4_f/200;
//         flag_ff=1;
//     }
//     *num_sample = *num_sample + 1;
// }

void init_4DOF(){
    delay_filter[Px_filter] = create_delay_filter();
    delay_filter[Py_filter] = create_delay_filter();
    delay_filter[Pz_filter] = create_delay_filter();

    delay_filter[tr_filter] = create_delay_filter();
    delay_filter[tp_filter] = create_delay_filter();
    delay_filter[ty_filter] = create_delay_filter();
    delay_filter[t4_filter] = create_delay_filter();
    
    derivative_filter[Va_x] = create_derivative_filter(1.0, Ts);
    derivative_filter[Va_y] = create_derivative_filter(1.0, Ts);
    derivative_filter[Va_z] = create_derivative_filter(1.0, Ts);
    derivative_filter[Aa_x] = create_derivative_filter(1.0, Ts);
    derivative_filter[Aa_y] = create_derivative_filter(1.0, Ts);
    derivative_filter[Aa_z] = create_derivative_filter(1.0, Ts);
    derivative_filter[Vr_x] = create_derivative_filter(1.0, Ts);
    derivative_filter[Vr_y] = create_derivative_filter(1.0, Ts);
    derivative_filter[Vr_z] = create_derivative_filter(1.0, Ts);
    derivative_filter[Ar_x] = create_derivative_filter(1.0, Ts);
    derivative_filter[Ar_y] = create_derivative_filter(1.0, Ts);
    derivative_filter[Ar_z] = create_derivative_filter(1.0, Ts);

    derivative_filter[w_c4r] = create_derivative_filter(1.0, Ts);
    derivative_filter[w_crr] = create_derivative_filter(1.0, Ts);
    derivative_filter[w_cpr] = create_derivative_filter(1.0, Ts);
    derivative_filter[w_cyr] = create_derivative_filter(1.0, Ts);
    derivative_filter[dw_c4r] = create_derivative_filter(1.0, Ts);
    derivative_filter[dw_crr] = create_derivative_filter(1.0, Ts);
    derivative_filter[dw_cpr] = create_derivative_filter(1.0, Ts);
    derivative_filter[dw_cyr] = create_derivative_filter(1.0, Ts);


}

double loop_4DOF(double Px_r, double Py_r, double Pz_r, double cy_r,
           double c1_a, double c2_a, double c3_a, double c4_a,
           double t1_a, double t2_a, double t3_a, double t4_a, 
           double* c_out1, double* c_out2, double* c_out3, double* c_out4){
    
        //Jacobian_S test

    Jacobian_S(c1_a, c2_a, c3_a, c4_a, t1_a,
                       t2_a, t3_a, &cr_a, &cp_a, &cy_a,
                       &Px_a, &Py_a, &Pz_a, &tr_a,
                       &tp_a, &ty_a);

    double Current_threshold =1;
    if( tr_a < 3*Current_threshold && tr_a > - 3*Current_threshold ){
            tr_a = 0;
        }
        else{
            tr_a = tr_a;
        }
    
    if( tp_a < 3*Current_threshold && tp_a > - 3*Current_threshold ){
            tp_a = 0;
        }
        else{
            tp_a = tp_a;
        }
    
    if( ty_a <3* Current_threshold && ty_a > - 3*Current_threshold ){
            ty_a = 0;
        }
        else{
            ty_a = ty_a;
        }
    
    if( t4_a < 3*Current_threshold && t4_a > - 3*Current_threshold ){
            t4_a = 0;
        }
        else{
            t4_a = t4_a;
        }
    t4_a=t4_a+1;
    tp_a=tp_a+1;

    // Print the results
    // printf("Input c1: %f, c2: %f, c3: %f, c4: %f\n", c1_a, c2_a, c3_a, c4_a);
    // printf("Input t1: %f, t2: %f, t3: %f, t4: %f\n", t1_a, t2_a, t3_a, t4_a);
    // printf("cr: %f, cp: %f, cy: %f\n Px: %f, Py: %f, Pz: %f\n tr: %f, tp: %f, ty: %f\n", cr_a, cp_a, cy_a, Px_a, Py_a, Pz_a, tr_a, tp_a, ty_a);

    //filter test


    if(flag_P_init==0){
        Px_a = process_delay_filter(delay_filter[Px_filter], Px_a)/1000.0;
        Py_a = process_delay_filter(delay_filter[Py_filter], Py_a)/1000.0;
        Pz_a = process_delay_filter(delay_filter[Pz_filter], Pz_a)/1000.0;
        Px_a = Px_r;
        Py_a = Py_r;
        Pz_a = Pz_r;
        flag_P_init=1;  
    }
    else{
        Px_a = process_delay_filter(delay_filter[Px_filter], Px_a)/1000.0;
        Py_a = process_delay_filter(delay_filter[Py_filter], Py_a)/1000.0;
        Pz_a = process_delay_filter(delay_filter[Pz_filter], Pz_a)/1000.0;
    }




    Vx_a = process_derivative_filter(derivative_filter[Va_x], Px_a);
    Vy_a = process_derivative_filter(derivative_filter[Va_y], Py_a);
    Vz_a = process_derivative_filter(derivative_filter[Va_z], Pz_a);
    Ax_a = process_derivative_filter(derivative_filter[Aa_x], Vx_a);
    Ay_a = process_derivative_filter(derivative_filter[Aa_y], Vy_a);
    Az_a = process_derivative_filter(derivative_filter[Aa_z], Vz_a);
    Vx_r = process_derivative_filter(derivative_filter[Vr_x], Px_r);
    Vy_r = process_derivative_filter(derivative_filter[Vr_y], Py_r);
    Vz_r = process_derivative_filter(derivative_filter[Vr_z], Pz_r);
    Ax_r = process_derivative_filter(derivative_filter[Ar_x], Vx_r);
    Ay_r = process_derivative_filter(derivative_filter[Ar_y], Vy_r);
    Az_r = process_derivative_filter(derivative_filter[Ar_z], Vz_r);

    //impedance control

    Fe_d[0] = impedance_params.Md*(Ax_a - Ax_r) + impedance_params.Kd*(Px_a - Px_r) + impedance_params.Bd*(Vx_a - Vx_r);
    Fe_d[1] = impedance_params.Md*(Ay_a - Ay_r) + impedance_params.Kd*(Py_a - Py_r) + impedance_params.Bd*(Vy_a - Vy_r);
    Fe_d[2] = impedance_params.Md*(Az_a - Az_r) + impedance_params.Kd*(Pz_a - Pz_r) + impedance_params.Bd*(Vz_a - Vz_r);
    printf("Fe_d: [%f, %f, %f]\n", Fe_d[0], Fe_d[1], Fe_d[2]);

    //IK_1DOF test
    IK_1DOF(Px_r*1000, Py_r*1000, Pz_r*1000, cy_r, &c4r, &crr, &cpr, &cyr);
    // printf("Px: %f, Py: %f, Pz: %f, cy: %f\n", Px_r, Py_r, Pz_r, cy_r);
    // printf("c4r: %f, crr: %f, cpr: %f, cyr: %f\n", c4r, crr, cpr, cyr);

    //filter test


    w4 = process_derivative_filter(derivative_filter[w_c4r], c4r);
    wr = process_derivative_filter(derivative_filter[w_crr], crr);
    wp = process_derivative_filter(derivative_filter[w_cpr], cpr);
    wy = process_derivative_filter(derivative_filter[w_cyr], cyr);
    dw4 = process_derivative_filter(derivative_filter[dw_c4r], w4);
    dwr = process_derivative_filter(derivative_filter[dw_crr], wr);
    dwp = process_derivative_filter(derivative_filter[dw_cpr], wp);
    dwy = process_derivative_filter(derivative_filter[dw_cyr], wy);

    //dynamics test
    A[2]=1.0;
    A[5]=1.0;
    A[8]=1.0;
    A[15]=((sin(cpr)*sin(cyr) + cos(cpr)*cos(cyr)*sin(crr))*(sin(cpr)*sin(cyr) + cos(cpr)*cos(cyr)*sin(crr)) + (cos(cpr)*sin(cyr) - cos(cyr)*sin(cpr)*sin(crr))*(cos(cpr)*sin(cyr) - cos(cyr)*sin(cpr)*sin(crr)) + cos(crr)*cos(crr)*cos(cyr)*cos(cyr));
    // printf("input:cp: %f, cr: %f, cy: %f, c4: %f, wp: %f, wr: %f, wy: %f, w4: %f, dwp: %f, dwr: %f, dwy: %f, dw4: %f\n", cpr, crr, cyr, c4r, wp, wr, wy, w4, dwp, dwr, dwy, dw4);  
    Dynamics_4DOF(Fe_d, A, cpr,
                   crr, cyr, c4r, wp, wr,
                   wy, w4, dwp, dwr, dwy,
                   dw4, &ty_d, &tr_d, &tp_d,
                   &t4_d, B);
    // printf("tyaw: %f, troll: %f, tpitch: %f, ta4: %f\n", ty_d, tr_d, tp_d, t4_d);

    //filter test


    tr_a = process_delay_filter(delay_filter[tr_filter], tr_a);
    tp_a = process_delay_filter(delay_filter[tp_filter], tp_a);
    ty_a = process_delay_filter(delay_filter[ty_filter], ty_a);
    t4_a = process_delay_filter(delay_filter[t4_filter], t4_a);

    //admittance control torque output

    t_joint[0] = tr_d - tr_a;
    t_joint[1] = tp_d - tp_a;
    t_joint[2] = ty_d - ty_a;
    t_joint[3] = t4_d - t4_a;
    // printf("t_joint output: %f, %f, %f, %f\n", t_joint[0], t_joint[1], t_joint[2], t_joint[3]);

    jointController(
        crr, cpr, cyr, c4r,
        wrr, wpr, wyr, wer,
        dwrr, dwpr, dwyr, dwer,
        t_joint[0], t_joint[1], t_joint[2], t_joint[3],
        &cr, &cp, &cy, &ce,
        &state_CR, &state_CP, &state_CY, &state_CE,
        &state_WR, &state_WP, &state_WY, &state_WE,
        &state_dWR, &state_dWP, &state_dWY, &state_dWE,
        &initialized,
        admittance_params.Md, admittance_params.Kd, admittance_params.Bd, Ts);

    // printf("Joint Control Output:\n");
    // printf("cr: %f, cp: %f, cy: %f, ce: %f\n", cr, cp, cy, ce);

    //IK_3DOF test
    IK_3DOF(cr, cp, cy, &c1, &c2, &c3);
    c4=ce;
    // printf("c1: %f, c2: %f, c3: %f, c4: %f\n", c1, c2, c3, c4);

    *c_out1=c1;
    *c_out2=c2;
    *c_out3=c3;
    *c_out4=c4;
    return 0;
}
/*****************************************************************************/

void cyclic_task()
{   
    if(counter1){
        counter1--;
    }
    else{
        counter1 = 999;
        //每秒输打印时间
        gettimeofday(&tv2, NULL);
        time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
        printf("Time: %.4f s\n", time_diff);
        // printf("%x\n",cmdptr->uservalue.Starttime);
        // printf("%x\n",cmdptr->uservalue.Starttime);
    }

    // printf("%d\n",cmdptr->getUserCmd());
    // printf("%x\n",cmdptr->uservalue.Starttime);
    //逆运动学计算时间测试
    // double time1;
    // double time2;
    // gettimeofday(&tv2, NULL);
    // time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
    // time1=time_diff;
    // // printf("calculate start Time: %.4f s\n", time_diff);
    // main_IK_7DOF();
    // gettimeofday(&tv2, NULL);
    // time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
    // time2=time_diff;
    // // printf("calculate stop Time: %.4f s\n", time_diff);
    // printf("calculate time: %.6f s\n", time2-time1);
    
    // receive process data
    ecrt_master_receive(master);
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        ecrt_domain_process(domain[counter_domain]);
    }
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        check_domain_state(counter_domain);
    }

    if (counter)
    {
        counter--;
    }
    else
    {   

        counter = FREQUENCY/PERIODS_PER_SECOND-1;
        // calculate new process data
        // blink++;
        // main_IK_7DOF();


        //初始化通信
        if(time_diff < INIT_TIME){
            for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
                ecrt_domain_queue(domain[counter_domain]);
            }
            ecrt_master_send(master);
            return;
        }

        // reading_driver();
        // reading_current();

        //电机使能
        if(cmdptr->uservalue.Preparetime && !cmdptr->uservalue.Starttime && !cmdptr->uservalue.Stoptime){
        // printf("motors enabling\n");
        if((time_diff < RUNNING_TIME) && (flag_init_all!=1) ){

            //!(flag_init[0]&flag_init[1]&flag_init[2]&flag_init[3]&flag_init[4]&flag_init[5]&flag_init[6]&flag_init[7]&flag_init[8]&flag_init[9]&flag_init[10]&flag_init[11]&flag_init[12]&flag_init[13])==1

            // driver_enable(6);
            // if((EC_READ_U16(domain_pd[0]+off_bytes_0x6041[0]) & 0x037) == 55){
            // flag_init[6] = 1; 
            // }
            printf("enabled drivers: \n");
            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {   if(!flag_init[counter_slave]){
                    driver_enable(counter_slave);
                    if((EC_READ_U16(domain_pd[counter_slave]+off_bytes_0x6041[counter_slave]) & 0x037) == 55){
                        flag_init[counter_slave] = 1; 
                        EC_WRITE_U8(domain_pd[counter_slave]+off_bytes_0x6060[counter_slave], 0x03);
                    }
                    break;
                }
                printf("%d ",counter_slave);
            }
            printf("\n");

            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                if(flag_init[counter_slave]){
                    flag_init_all=1;
                }
                else{
                    flag_init_all=0;
                    break;
                }
            }

        }
        else{
            if(flag_init_all==1){
                printf("all drivers enabled\n");
            }
        }
        }
        //控制部分

        if(cmdptr->uservalue.Starttime  && !cmdptr->uservalue.Stoptime){
        // printf("control loop\n");
        if((time_diff < RUNNING_TIME)&&(flag_init_all==1)&&(flag_stop_all!=1)){
            
            //((flag_init[0]&flag_init[1]&flag_init[2]&flag_init[3]&flag_init[4]&flag_init[5]&flag_init[6]&flag_init[7]&flag_init[8]&flag_init[9]&flag_init[10]&flag_init[11]&flag_init[12]&flag_init[13])==1)
            
            float trans; 
            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {   
                EC_WRITE_U8(domain_pd[counter_slave]+off_bytes_0x6060[counter_slave], 0x03);
            }
            reading_ssi();
            reading_current();
            switch (stage){
                case 0: printf("initialization finished, start to reset the position\n");
                        // scanf("%s",command);
                        stage = 1; 
                        counter_loop=0;
                        for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                            Position_Kp[counter_slave]=2;
                            Target_Position[counter_slave]=0;
                        }
                        Target_Position[3]=90;
                        //     Target_Position[4]=Target_Position[4]+Target_Position[3];
                        //     Target_Position[5]=Target_Position[5]+Target_Position[3];
                        //     Target_Position[11]=Target_Position[11]+Target_Position[10];
                        //     Target_Position[12]=Target_Position[12]+Target_Position[10];
                        break;
                case 1: counter_loop++;
                    // EC_WRITE_S32(domain_pd[13]+off_bytes_0x60ff[13],1000);
                        // if(counter_loop>5000){
                        //     counter_loop=0;
                        //     stage = 2;
                        // }

                        
                        for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                            control_pid(counter_slave);
                        }
                        if((Error[0]<ERROR)&&(Error[1]<ERROR)&&(Error[2]<ERROR)&&(Error[3]<ERROR)&&(Error[4]<ERROR)&&(Error[5]<ERROR)&&(Error[6]<ERROR)&&(Error[7]<ERROR)&&(counter_loop/PERIODS_PER_SECOND>5)){
                            printf("reset finished, start moving\n");
                            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                Position_Kp[counter_slave]=10;

                            // Position_Kd[counter_slave]=0.3;
                            }

                            counter_loop=0;
                            stage = 2;
                        }
                        break;
                case 2: 
                        printf("stage 2: %d\n",counter_loop);
                        // if(sample_counter<201){
                        //     torque_feedforward(Actual_Torque[0], Actual_Torque[1],
                        //                     Actual_Torque[2], Actual_Torque[3], &sample_counter);
                        // }
                        // else{printf("toque feedforward: %f, %f, %f, %f\n", t1_f, t2_f, t3_f, t4_f);}
                        if(cmdptr->uservalue.Stage==1){
                            counter_loop++;
                            if(counter_loop){
                        // printf(" target %f %f %f %f %f %f %f\n",values[7*counter_loop],values[7*counter_loop+1],values[7*counter_loop+2]
                        //        ,values[7*counter_loop+3],values[7*counter_loop+4],values[7*counter_loop+5],values[7*counter_loop+6]);
                                //for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){

                                // Target_Position[counter_slave]=180/3.1415926536*values[14*counter_loop+counter_slave];
                                //}

                                    //举重
                                    // if (counter_loop<2400){
                                    //     Target_Position[3]=angle[counter_loop];
                                    //     Target_Position[7]=angle[counter_loop];
                                    // }
                                    // else if(counter_loop<4800){
                                    //     Target_Position[3]=angle[counter_loop];
                                    //     Target_Position[7]=angle[2400];
                                    // }
                                    // else if(counter_loop<7200){
                                    //     Target_Position[3]=angle[4800];
                                    //     Target_Position[7]=angle[counter_loop];
                                    // }
                                    // else if(counter_loop<9600){
                                    //     Target_Position[3]=angle[counter_loop];
                                    //     Target_Position[7]=angle[7200];
                                    // }
                                    // else if(counter_loop<12000){
                                    //     Target_Position[3]=angle[9600];
                                    //     Target_Position[7]=angle[counter_loop];
                                    // }
                                    // Target_Position[3]=angle[counter_loop];


                                    //跑步
                                    // Target_Position[3]=angle1[counter_loop];
                                    // Target_Position[7]=angle1[counter_loop];
                                    // Target_Position[0]=-angle2[counter_loop];
                                    // Target_Position[1]=-angle2[counter_loop];
                                    // Target_Position[2]=-angle2[counter_loop];
                                    // Target_Position[4]=angle2[counter_loop];
                                    // Target_Position[5]=angle2[counter_loop];
                                    // Target_Position[6]=angle2[counter_loop];

                                    // Target_Position[3]=0;
                                    // Target_Position[7]=0;
                                    
                                    // double time1;
                                    // double time2;
                                    // gettimeofday(&tv2, NULL);
                                    // time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
                                    // time1=time_diff;
                                    // printf("calculate start Time: %.4f s\n", time_diff);
                                    
                                    loop_4DOF(Px_r, Py_r, Pz_r, cy_r,
                                            Actual_Position[0]*3.1415926535/180, Actual_Position[1]*3.1415926535/180, Actual_Position[2]*3.1415926535/180, Actual_Position[3]*3.1415926535/180,
                                            Actual_Torque[0], Actual_Torque[1], Actual_Torque[2], Actual_Torque[3],
                                            &c[0], &c[1], &c[2], &c[3]);
                                    // gettimeofday(&tv2, NULL);
                                    // time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
                                    // time2=time_diff;
                                    // // printf("calculate stop Time: %.4f s\n", time_diff);
                                    // printf("calculate time: %.6f s\n", time2-time1);
                                    printf("c: [%f, %f, %f, %f]\n", c[0]*180/3.1415926536, c[1]*180/3.1415926536, c[2]*180/3.1415926536, c[3]*180/3.1415926536);
                                    // Target_Position[0]=0;
                                    // Target_Position[1]=0;
                                    // Target_Position[2]=0;
                                    // Target_Position[3]=0;
                                    // Target_Position[4]=0;
                                    // Target_Position[5]=0;
                                    // Target_Position[6]=0;
                                    // Target_Position[7]=0;
                                    Target_Position[0]=c[0]*180/3.1415926536;
                                    Target_Position[1]=c[1]*180/3.1415926536;
                                    Target_Position[2]=c[2]*180/3.1415926536;
                                    Target_Position[3]=c[3]*180/3.1415926536;

//     }
                                    // Target_Position[0]=0;
                                    // Target_Position[1]=0;
                                    // Target_Position[2]=0;
                                    // Target_Position[4]=0;
                                    // Target_Position[5]=0;
                                    // Target_Position[6]=0;



                                    // std::cout << angle[counter_loop] << std::endl;
                            }  
                            else{
                                counter_loop=0;
                                for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                // Target_Position[counter_slave]=180/3.1415926536*values[14*counter_loop+counter_slave];
                                }
                            }

                            // Target_Position[4]=Target_Position[4]+Target_Position[3];
                            // Target_Position[5]=Target_Position[5]+Target_Position[3];
                            // Target_Position[11]=Target_Position[11]+Target_Position[10];
                            // Target_Position[12]=Target_Position[12]+Target_Position[10];
                            // if(counter_loop % 10 == 0){
                            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                                control_pid(counter_slave);
                            }
                            //}
                        }
                        // else if(cmdptr->uservalue.Stage==2){
                        //     counter_loop+=2;
                        //     if(counter_loop<10000){
                        // // printf(" target %f %f %f %f %f %f %f\n",values[7*counter_loop],values[7*counter_loop+1],values[7*counter_loop+2]
                        // //        ,values[7*counter_loop+3],values[7*counter_loop+4],values[7*counter_loop+5],values[7*counter_loop+6]);
                        //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        //         Target_Position[counter_slave]=180/3.1415926536*values[14*(12000-counter_loop)+counter_slave];
                        //         }
                        //     }
                        //     else if(counter_loop<14000){
                        //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        //         Target_Position[counter_slave]=180/3.1415926536*values[14*(counter_loop-8000)+counter_slave];
                        //         }
                        //     }
                        //     else if(counter_loop<18000){
                        //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        //         Target_Position[counter_slave]=180/3.1415926536*values[14*(20000-counter_loop)+counter_slave];
                        //         }
                        //     }
                        //     else if(counter_loop<22000){
                        //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        //         Target_Position[counter_slave]=180/3.1415926536*values[14*(counter_loop-16000)+counter_slave];
                        //         }
                        //     }
                        //     else{
                        //         counter_loop=22000;
                        //         for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        //         Target_Position[counter_slave]=180/3.1415926536*values[14*(counter_loop-16000)+counter_slave];
                        //         }
                        //     }

                        //     Target_Position[4]=Target_Position[4]+Target_Position[3];
                        //     Target_Position[5]=Target_Position[5]+Target_Position[3];
                        //     Target_Position[11]=Target_Position[11]+Target_Position[10];
                        //     Target_Position[12]=Target_Position[12]+Target_Position[10];
                        //     for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        //         control_pid(counter_slave);
                        //     }
                        // }
                        else if(cmdptr->uservalue.Stage==3){
                            counter_loop=0;
                            stage = 3;
                        }
                        else
                        {
                            // printf("please set the stage correctly\n");
                        }
                        // printf("%d\n",counter_loop);
                            

                            // if ( counter_loop % 2 == 0) {
                            //     for(counter_slave=0;counter_slave<7;counter_slave++){
                            //         control_pid(counter_slave);
                            //     }
                            // }
                            // else{
                            //     for(counter_slave=7;counter_slave<14;counter_slave++){
                            //注意腕关节受肘关节自由度影响，需要额外加角度！


                            //     }
                            // }
                        
                        
                        // printf("target %f %f %f %f %f %f %f  %f %f %f %f %f %f %f\n", Target_Position[0],Target_Position[1],Target_Position[2],Target_Position[3],Target_Position[4],Target_Position[5],
                        //     Target_Position[6],Target_Position[7],Target_Position[8],Target_Position[9],Target_Position[10],Target_Position[11],Target_Position[12],Target_Position[13]);
                        

                        break;
            case 3: printf("******end******\n"); 
                    // EC_WRITE_S32(domain_pd[13]+off_bytes_0x60ff[13],0);
                    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        control_pid(counter_slave);
                    }
                    stage=4;
                    break;
            case 4:                
                    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
                        {   
                            if(Error[0]<ERROR){
                                    driver_disable(counter_slave);
                                    flag_stop[counter_slave]=1;
                                }
                            else{
                                    control_pid(counter_slave);
                                }
                        }
                    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        if(flag_stop[counter_slave]){
                            flag_stop_all=1;
                        }
                        else{
                            flag_stop_all=0;
                            break;
                        }
                    }
            default: break;


        }


        //udp通信
        char sendBuf[1024];
        sprintf(sendBuf, "d:%f,%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,%f,%f,%f,%f,  %f,%f,%f,%f,  %f,%f,%f,  %f,%f,%f,%f,%f,%f\n",
            Actual_Position[0],Actual_Position[1],Actual_Position[2],Actual_Position[3],
            Actual_Position[4],Actual_Position[5],Actual_Position[6],Actual_Position[7],//0-7
            Target_Position[0],Target_Position[1],Target_Position[2],Target_Position[3],
            Target_Position[4],Target_Position[5],Target_Position[6],Target_Position[7],//8-15
            Target_Velocity[0],Target_Velocity[1],Target_Velocity[2],Target_Velocity[3],
            Target_Velocity[4],Target_Velocity[5],Target_Velocity[6],Target_Velocity[7],//16-23
            Actual_Velocity[0],Actual_Velocity[1],Actual_Velocity[2],Actual_Velocity[3],
            Actual_Velocity[4],Actual_Velocity[5],Actual_Velocity[6],Actual_Velocity[7],//24-31
            Origin_Current[0],Origin_Current[1],Origin_Current[2],Origin_Current[3],
            Origin_Current[4],Origin_Current[5],Origin_Current[6],Origin_Current[7],//32-39
            Actual_Current[0],Actual_Current[1],Actual_Current[2],Actual_Current[3],
            Actual_Current[4],Actual_Current[5],Actual_Current[6],Actual_Current[7],//40-47
            Actual_Torque[0],Actual_Torque[1],Actual_Torque[2],Actual_Torque[3],
            Actual_Torque[4],Actual_Torque[5],Actual_Torque[6],Actual_Torque[7],//48-55
            Actual_joint_Torque[0],Actual_joint_Torque[1],Actual_joint_Torque[2],Actual_joint_Torque[3],
            Actual_joint_Torque[4],Actual_joint_Torque[5],Actual_joint_Torque[6],Actual_joint_Torque[7],//56-63
            c[0],c[1],c[2],c[3],cr,cp,cy,Px_a,Py_a,Pz_a,Px_r,Py_r,Pz_r);//64-76
        sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));


            
        }
        else if((time_diff > RUNNING_TIME) && (flag_stop_all==1)){
                // fclose(fp);
                for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {
                driver_disable(counter_slave);
                printf("%d stop\n",counter_slave);
            }
        }  
                //频率测试部分
                if(time_test1==0){
                    gettimeofday(&tv2, NULL);
                    time_test1 = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
                }
                else if((time_test1==0)){
                    gettimeofday(&tv2, NULL);
                    time_test2 = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
                }
        }

        if(cmdptr->uservalue.Stoptime){
            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {
                driver_disable(counter_slave);
                printf("%d stop\n",counter_slave);
                flag_stop[counter_slave]=1;
            }
            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
                        if(flag_stop[counter_slave]){
                            flag_stop_all=1;
                        }
                        else{
                            flag_stop_all=0;
                            break;
                        }
            }
        }

        check_master_state();
        for(counter_slave=0;counter_slave<DOMAIN_NUMBER;counter_slave++){
                check_slave_config_states(counter_slave);
            }
        }
    
    //  send process data
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        ecrt_domain_queue(domain[counter_domain]);
    }
    ecrt_master_send(master);
}

/****************************************************************************/

void signal_handler(int signum)
{
    switch (signum)
    {
    case SIGALRM:
        sig_alarms++;
        break;
    }
}


void stack_prefault(void)
{
    unsigned char dummy[MAX_SAFE_STACK];

    memset(dummy, 0, MAX_SAFE_STACK);
}
/****************************************************************************/

int main(int argc, char **argv)
{
    printf("test1\n");
    cmdptr = new KeyBoard();

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(-1);
    }
    // 服务器的地址信息
    memset(&saddr,0,sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(9999);
    if(inet_pton(AF_INET, "192.168.7.1", &saddr.sin_addr.s_addr)<0){
        perror("inet_pton");
    };

    int i;
    FILE *file;
    char line[512]; 
    char *token;

    int count = 0;
    

    for(i=0;i<48000;i++){
        if(i<2400){
            angle[i]=i/2400.0*20;
        }
        else{
            angle[i]=55-35*cos(3.1415926536*(i-2400)/1200);
        }
        angle[i]=floor(angle[i] * 1000000.000f + 0.5) / 1000000.000f;
    }
    for(i=0;i<48000;i++){
        // if(i<2400){
        //     angle1[i]=i/2400.0*60;
        // }
        // else{
        //     angle1[i]=60;
        // }
        angle1[i]=0;

    }

    for(i=0;i<48000;i++){
        // if(i<2400){
        //     angle2[i]=0;
        // }
        // else{
        //     angle2[i]=20*sin(3.1415926536*i/1200*6);
        // }
        angle2[i]=20*sin(3.1415926536*i/2400);
    }


    // 打开文件
    file = fopen("traj.csv", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // 逐行读取文件
    while (fgets(line, sizeof(line), file)) {
        // 使用strtok分割每行的字符串
        //printf("%s\n",line );
        token = strtok(line, ",");
        while (token != NULL) {
            // 将字符串转换为double
            values[count] = strtod(token, NULL);
            count++;
            token = strtok(NULL, ",");
            // printf("%f\n",count);
            if(count>NUMBER)break;
        }
        if(count>NUMBER)break;
    }
    // int j=0;
 	// printf("%d\n",sizeof(values));
    // for(i=0;i<20;i++){
    //     for(j=0;j<14;j++){
    //         printf("%f  ",values[14*i+j]);
    // }
    //     printf("\n");
    // }
    
    // 关闭文件
    fclose(file);
    printf("read finished\n");

    printf("samplerate: %f\n", sampleRate);
    struct sigaction sa;
    struct itimerval tv;
    master = ecrt_request_master(0);
    if (!master)
        return -1;
    // 建立一个域，参数是master
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        domain[counter_domain] = ecrt_master_create_domain(master);
        if (!domain[counter_domain])
            return -1;
    }

        // ⽤宏定义配置master和slave 数字信号输⼊的从站/供应商ID产品代码
    if(config()){
        printf("config fail...\n");
        return -1;
    };

    printf("Activating master...\n");
    if (ecrt_master_activate(master))
    {
        printf("ecrt_master_activate fail...\n");
        return -1;
    }
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
    if (!(domain_pd[counter_domain] = ecrt_domain_data(domain[counter_domain])))
        {
            printf("ecrt_domain%d_data fail...\n",counter_domain);
            return -1;
        }
    }



    for(i=0;i<0xffffff;i++);
    for(i=0;i<0xffffff;i++);
    for(i=0;i<0xffffff;i++);
    for (counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        butterworthLPF(&filter[counter_slave], cutoffFreq, sampleRate);
        initFilter(&filter[counter_slave]);
    }
    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
    dead_zone_init_context(&ctx[counter_slave]);
    }

    sa.sa_handler = signal_handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGALRM, &sa, 0))
    {
        fprintf(stderr, "Failed to install signal handler!\n");
        return -1;
    }

    printf("Starting timer...\n");
    tv.it_interval.tv_sec = 0;
    tv.it_interval.tv_usec = 1000000 / FREQUENCY;//启动后的定时器每隔1ms唤醒一次
    tv.it_value.tv_sec = 0;
    tv.it_value.tv_usec = 2000;//定时器在2s后启动
    if (setitimer(ITIMER_REAL, &tv, NULL))
    {
        fprintf(stderr, "Failed to start timer: %s\n", strerror(errno));
        return 1;
    }

    printf("Started.\n");
    gettimeofday(&tv1, NULL);

    init_4DOF();


    // fp = fopen("tmp.csv", "w+");
    // if (fp == NULL) {
    //     fprintf(stderr, "fopen() failed.\n");
    //     exit(EXIT_FAILURE);
    // }
    // fprintf(fp, "time,target_p,actual_p\n");
    printf("**********press p to enable**********\n");
    printf("**********press a to start**********\n");
    printf("**********press s to stop**********\n");
    while (1)
    {
        pause();
        while (sig_alarms != user_alarms)
        {       
            cyclic_task();
            user_alarms++;
            if(time_diff > RUNNING_TIME || flag_stop_all){
                delete cmdptr;
                system("stty echo");
                printf("over.\n");return 0;}
        }
        
    }
    return 0;
}

