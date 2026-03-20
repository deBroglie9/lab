/*****************************************************************************
 * 2025/1/7
 * 目前接入1个编码器 2个驱动器 代码目前可连接8个从站，1个编码器+7个驱动器，需要修改
 * DRIVER_NUMBER 
 * ENCODER_NUMBER 
 * DOMAIN_NUMBER 
 * 以及其他初始化函数的个数及序号
 * 加入逆运动学求解函数，读入X,Y,Z和R(3*3逐行读入)
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
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<time.h>
#include<math.h>
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>
#include "IK_7DOF.h"
#include "IK_7DOF_terminate.h"
#include "rt_nonfinite.h"


/****************************************************************************/

#include "ecrt.h"

/****************************************************************************/

// Application parameters
#define FREQUENCY 1000
#define PRIORITY 1
#define MAX_VELOCITY 500000/*target velocity*/
#define PERIODS_PER_SECOND   1000
#define RUNNING_TIME 20 /*seconds*/
#define INIT_TIME 0.5

#define DRIVER_NUMBER 2
#define ENCODER_NUMBER 1
#define DOMAIN_NUMBER 3

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


static ec_slave_config_t *sc1;
static ec_slave_config_state_t sc1_ana_in_state = {};

static ec_slave_config_t *sc2;
static ec_slave_config_state_t sc2_ana_in_state = {};

static ec_slave_config_t *sc3;
static ec_slave_config_state_t sc3_ana_in_state = {};

static ec_slave_config_t *sc4;
static ec_slave_config_state_t sc4_ana_in_state = {};

static ec_slave_config_t *sc5;
static ec_slave_config_state_t sc5_ana_in_state = {};

static ec_slave_config_t *sc6;
static ec_slave_config_state_t sc6_ana_in_state = {};

static ec_slave_config_t *sc7;
static ec_slave_config_state_t sc7_ana_in_state = {};

static ec_slave_config_t *sc8;
static ec_slave_config_state_t sc8_ana_in_state = {};

float Target_Position=0;
float Actual_Position=0;   
float target_p=0;
float actual_p=0;
float target_p_last=0;
float actual_p_last=0;

float Actual_Position2=0;   
float actual_p2=0;
float actual_p_last2=0;

static float Position_Kp=10000,Position_Ki=0,Position_Kd=0;
static float offset_actual_position=0;
static float offset_actual_position2=0;
static float offset_target_position=0;
static float Error[DRIVER_NUMBER];
static float Error_Last[DRIVER_NUMBER];
static float Delta_Error[DRIVER_NUMBER];
static float Delta_Error_Last[DRIVER_NUMBER];
static float Integral[DRIVER_NUMBER];
static float Target_Velocity[DRIVER_NUMBER];

static FILE *fp;

static unsigned int counter = 0;
static unsigned int counter1 = 0;
static unsigned int counter_slave = 0;
static unsigned int counter_domain = 0;
static unsigned int blink = 0x00;
static unsigned int flag = 0;
static unsigned int flag2 = 0;

// Timer
static unsigned int sig_alarms = 0;
static unsigned int user_alarms = 0;

static struct timeval tv1;
static struct timeval tv2;
static double time_diff;

static int ssi;
static unsigned int ain1;
static unsigned long ssi1;
static unsigned long dri;
/****************************************************************************/

// process data
static uint8_t *domain_pd[DOMAIN_NUMBER];

#define BusCouplerPos1 0, 0
#define BusCouplerPos2 0, 1
#define BusCouplerPos3 0, 7
#define BusCouplerPos4 0, 3
#define BusCouplerPos5 0, 4
#define BusCouplerPos6 0, 5
#define BusCouplerPos7 0, 6
#define BusCouplerPos8 0, 2



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

/* Master 0, Slave 0
 * Vendor ID:       0x0000009a
 * Product code:    0x00030924
 * Revision number: 0x00010420
 */
const static ec_pdo_entry_reg_t domain1_regs[] = {
    {BusCouplerPos1,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[0], &off_bits_0x6040[0]},
    {BusCouplerPos1,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[0], &off_bits_0x6060[0]},
    {BusCouplerPos1,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[0], &off_bits_0x60ff[0]},
    {BusCouplerPos1,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[0], &off_bits_0x6041[0]},
    {BusCouplerPos1,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[0], &off_bits_0x6061[0]},
    {BusCouplerPos1,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[0], &off_bits_0x6064[0]},
    {BusCouplerPos1,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[0], &off_bits_0x606C[0]},
    {}
};

/* Master 0, Slave 1
 * Vendor ID:       0x0000009a
 * Product code:    0x00030924
 * Revision number: 0x00010420
 */

const static ec_pdo_entry_reg_t domain2_regs[] = {
    {BusCouplerPos2,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[1], &off_bits_0x6040[1]},
    {BusCouplerPos2,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[1], &off_bits_0x6060[1]},
    {BusCouplerPos2,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[1], &off_bits_0x60ff[1]},
    {BusCouplerPos2,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[1], &off_bits_0x6041[1]},
    {BusCouplerPos2,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[1], &off_bits_0x6061[1]},
    {BusCouplerPos2,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[1], &off_bits_0x6064[1]},
    {BusCouplerPos2,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[1], &off_bits_0x606C[1]},
    
    {}
};

/* Master 0, Slave 2
 * Vendor ID:       0x0000009a
 * Product code:    0x00030924
 * Revision number: 0x00010420
 */
const static ec_pdo_entry_reg_t domain3_regs[] = {
    {BusCouplerPos1,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[2], &off_bits_0x6040[2]},
    {BusCouplerPos1,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[2], &off_bits_0x6060[2]},
    {BusCouplerPos1,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[2], &off_bits_0x60ff[2]},
    {BusCouplerPos1,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[2], &off_bits_0x6041[2]},
    {BusCouplerPos1,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[2], &off_bits_0x6061[2]},
    {BusCouplerPos1,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[2], &off_bits_0x6064[2]},
    {BusCouplerPos1,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[2], &off_bits_0x606C[2]},
    {}
};

/* Master 0, Slave 3
 * Vendor ID:       0x0000009a
 * Product code:    0x00030924
 * Revision number: 0x00010420
 */

const static ec_pdo_entry_reg_t domain4_regs[] = {
    {BusCouplerPos2,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[3], &off_bits_0x6040[3]},
    {BusCouplerPos2,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[3], &off_bits_0x6060[3]},
    {BusCouplerPos2,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[3], &off_bits_0x60ff[3]},
    {BusCouplerPos2,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[3], &off_bits_0x6041[3]},
    {BusCouplerPos2,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[3], &off_bits_0x6061[3]},
    {BusCouplerPos2,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[3], &off_bits_0x6064[3]},
    {BusCouplerPos2,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[3], &off_bits_0x606C[3]},
    
    {}
};

/* Master 0, Slave 4
 * Vendor ID:       0x0000009a
 * Product code:    0x00030924
 * Revision number: 0x00010420
 */
const static ec_pdo_entry_reg_t domain5_regs[] = {
    {BusCouplerPos1,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[4], &off_bits_0x6040[4]},
    {BusCouplerPos1,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[4], &off_bits_0x6060[4]},
    {BusCouplerPos1,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[4], &off_bits_0x60ff[4]},
    {BusCouplerPos1,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[4], &off_bits_0x6041[4]},
    {BusCouplerPos1,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[4], &off_bits_0x6061[4]},
    {BusCouplerPos1,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[4], &off_bits_0x6064[4]},
    {BusCouplerPos1,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[4], &off_bits_0x606C[4]},
    {}
};

/* Master 0, Slave 5
 * Vendor ID:       0x0000009a
 * Product code:    0x00030924
 * Revision number: 0x00010420
 */

const static ec_pdo_entry_reg_t domain6_regs[] = {
    {BusCouplerPos2,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[5], &off_bits_0x6040[5]},
    {BusCouplerPos2,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[5], &off_bits_0x6060[5]},
    {BusCouplerPos2,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[5], &off_bits_0x60ff[5]},
    {BusCouplerPos2,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[5], &off_bits_0x6041[5]},
    {BusCouplerPos2,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[5], &off_bits_0x6061[5]},
    {BusCouplerPos2,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[5], &off_bits_0x6064[5]},
    {BusCouplerPos2,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[5], &off_bits_0x606C[5]},
    
    {}
};

/* Master 0, Slave 6
 * Vendor ID:       0x0000009a
 * Product code:    0x00030924
 * Revision number: 0x00010420
 */
const static ec_pdo_entry_reg_t domain7_regs[] = {
    {BusCouplerPos1,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[6], &off_bits_0x6040[6]},
    {BusCouplerPos1,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[6], &off_bits_0x6060[6]},
    {BusCouplerPos1,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[6], &off_bits_0x60ff[6]},
    {BusCouplerPos1,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[6], &off_bits_0x6041[6]},
    {BusCouplerPos1,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[6], &off_bits_0x6061[6]},
    {BusCouplerPos1,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[6], &off_bits_0x6064[6]},
    {BusCouplerPos1,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[6], &off_bits_0x606C[6]},
    {}
};


/* Master 0, Slave 7
 * Vendor ID:       0x01222222
 * Product code:    0x00020310
 * Revision number: 0x00020211
 */

const static ec_pdo_entry_reg_t domain8_regs[] = {
    // {Alias, Position, Vendor ID, Product Code, PDO Index, -Subindex, Offset}
    {BusCouplerPos8,ENCODERICE, 0x7020, 0x01, &off_bytes_cm_1[0], &off_bits_cm_1[0]},
    {BusCouplerPos8,ENCODERICE, 0x7020, 0x02, &off_bytes_cm_2[0], &off_bits_cm_2[0]},
    {BusCouplerPos8,ENCODERICE, 0x7030, 0x01, &off_bytes_target_angle[0], &off_bits_target_angle[0]},
    {BusCouplerPos8,ENCODERICE, 0x6000, 0x01, &off_bytes_ssi[0], &off_bits_ssi[0]},
    {BusCouplerPos8,ENCODERICE, 0x6000, 0x02, &off_bytes_ssi_2[0], &off_bits_ssi_2[0]},
    {BusCouplerPos8,ENCODERICE, 0x6000, 0x03, &off_bytes_ssi_3[0], &off_bits_ssi_3[0]},
    {BusCouplerPos8,ENCODERICE, 0x6000, 0x04, &off_bytes_ssi_4[0], &off_bits_ssi_4[0]},
    {BusCouplerPos8,ENCODERICE, 0x6000, 0x05, &off_bytes_ssi_5[0], &off_bits_ssi_5[0]},
    {BusCouplerPos8,ENCODERICE, 0x6000, 0x06, &off_bytes_ssi_6[0], &off_bits_ssi_6[0]},
    {BusCouplerPos8,ENCODERICE, 0x6000, 0x07, &off_bytes_ssi_7[0], &off_bits_ssi_7[0]},
    {BusCouplerPos8,ENCODERICE, 0x6000, 0x08, &off_bytes_ssi_8[0], &off_bits_ssi_8[0]},
    {BusCouplerPos8,ENCODERICE, 0x6010, 0x01, &off_bytes_ain_1[0], &off_bits_ain_1[0]},
    {BusCouplerPos8,ENCODERICE, 0x6010, 0x02, &off_bytes_ain_2[0], &off_bits_ain_2[0]},
    {BusCouplerPos8,ENCODERICE, 0x6010, 0x03, &off_bytes_ain_3[0], &off_bits_ain_3[0]},
    {BusCouplerPos8,ENCODERICE, 0x6010, 0x04, &off_bytes_ain_4[0], &off_bits_ain_4[0]},
    {BusCouplerPos8,ENCODERICE, 0x6010, 0x05, &off_bytes_ain_5[0], &off_bits_ain_5[0]},
    {BusCouplerPos8,ENCODERICE, 0x6010, 0x06, &off_bytes_ain_6[0], &off_bits_ain_6[0]},
    {BusCouplerPos8,ENCODERICE, 0x6010, 0x07, &off_bytes_ain_7[0], &off_bits_ain_7[0]},
    {BusCouplerPos8,ENCODERICE, 0x6010, 0x08, &off_bytes_ain_8[0], &off_bits_ain_8[0]},
    {}
};

static ec_pdo_entry_info_t slave_pdo_entries[] = {
    {0x6040, 0x00, 16}, /* Controlword */
    {0x6060, 0x00, 8}, /* Modes of operation */
    {0x60ff, 0x00, 32}, /* Target velocity */
    {0x6041, 0x00, 16},/* Statusword */
    {0x6061, 0x00, 8}, /* Modes of operation display */
    {0x6064, 0x00, 32}, /* Position actual value */
    {0x606C, 0x00, 32}, /* Velocity actual value */
};

static ec_pdo_info_t slave_pdos[] = {
    {0x1607, 3, slave_pdo_entries + 0}, /* RPDO1 Mapping */
    {0x1a07, 4, slave_pdo_entries + 3}, /* TPDO1 Mapping */
};

static ec_sync_info_t slave_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, slave_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 1, slave_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

ec_pdo_entry_info_t slave_0_pdo_entries[] = {
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

ec_pdo_info_t slave_0_pdos[] = {
    {0x1601, 2, slave_0_pdo_entries + 0}, /* write commond of moulde */
    {0x1602, 1, slave_0_pdo_entries + 2}, /* write commond of moulde */
    {0x1a00, 8, slave_0_pdo_entries + 3}, /* read ssi of moudle */
    {0x1a05, 8, slave_0_pdo_entries + 11}, /* read ain of moudle */

};

ec_sync_info_t slave_0_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 2, slave_0_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 2, slave_0_pdos + 2, EC_WD_DISABLE},
    {0xff}
};


/*****************************************************************************/


int fd=-1;
struct sockaddr_in saddr;

void check_domain_state(uint16_t slave_position)
{
    ec_domain_state_t ds;

    ecrt_domain_state(domain[slave_position], &ds);

    if (ds.working_counter != domain_state[slave_position].working_counter)
        printf("Domain %d : WC %u.\n", slave_position, ds.working_counter);
    if (ds.wc_state != domain_state[slave_position].wc_state)
        printf("Domain %d : State %u.\n", slave_position, ds.wc_state);

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



void check_slave1_config_states(void)
{
    // printf("check_slave_config_states\n");
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc1, &s);

    if (s.al_state != sc1_ana_in_state.al_state)
        printf("AnaIn1: State 0x%02X.\n", s.al_state);

    if (s.online != sc1_ana_in_state.online)
        printf("AnaIn1: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc1_ana_in_state.operational)
        printf("AnaIn1: %soperational.\n",
               s.operational ? "" : "Not ");

    sc1_ana_in_state = s;
}

void check_slave2_config_states(void)
{
    // printf("check_slave_config_states\n");
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc2, &s);

    if (s.al_state != sc2_ana_in_state.al_state)
        printf("AnaIn2: State 0x%02X.\n", s.al_state);

    if (s.online != sc2_ana_in_state.online)
        printf("AnaIn2: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc2_ana_in_state.operational)
        printf("AnaIn2: %soperational.\n",
               s.operational ? "" : "Not ");

    sc2_ana_in_state = s;
}

void check_slave3_config_states(void)
{
    // printf("check_slave_config_states\n");
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc3, &s);

    if (s.al_state != sc3_ana_in_state.al_state)
        printf("AnaIn3: State 0x%02X.\n", s.al_state);

    if (s.online != sc3_ana_in_state.online)
        printf("AnaIn3: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc3_ana_in_state.operational)
        printf("AnaIn2: %soperational.\n",
               s.operational ? "" : "Not ");

    sc3_ana_in_state = s;
}

void check_slave4_config_states(void)
{
    // printf("check_slave_config_states\n");
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc4, &s);

    if (s.al_state != sc4_ana_in_state.al_state)
        printf("AnaIn4: State 0x%02X.\n", s.al_state);

    if (s.online != sc4_ana_in_state.online)
        printf("AnaIn4: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc4_ana_in_state.operational)
        printf("AnaIn4: %soperational.\n",
               s.operational ? "" : "Not ");

    sc4_ana_in_state = s;
}

void check_slave5_config_states(void)
{
    // printf("check_slave_config_states\n");
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc5, &s);

    if (s.al_state != sc5_ana_in_state.al_state)
        printf("AnaIn5: State 0x%02X.\n", s.al_state);

    if (s.online != sc5_ana_in_state.online)
        printf("AnaIn5: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc5_ana_in_state.operational)
        printf("AnaIn5: %soperational.\n",
               s.operational ? "" : "Not ");

    sc5_ana_in_state = s;
}

void check_slave6_config_states(void)
{
    // printf("check_slave_config_states\n");
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc6, &s);

    if (s.al_state != sc6_ana_in_state.al_state)
        printf("AnaIn6: State 0x%02X.\n", s.al_state);

    if (s.online != sc6_ana_in_state.online)
        printf("AnaIn6: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc6_ana_in_state.operational)
        printf("AnaIn6: %soperational.\n",
               s.operational ? "" : "Not ");

    sc6_ana_in_state = s;
}

void check_slave7_config_states(void)
{
    // printf("check_slave_config_states\n");
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc7, &s);

    if (s.al_state != sc7_ana_in_state.al_state)
        printf("AnaIn7: State 0x%02X.\n", s.al_state);

    if (s.online != sc7_ana_in_state.online)
        printf("AnaIn7: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc7_ana_in_state.operational)
        printf("AnaIn7: %soperational.\n",
               s.operational ? "" : "Not ");

    sc7_ana_in_state = s;
}

void check_slave8_config_states(void)
{
    // printf("check_slave_config_states\n");
    ec_slave_config_state_t s;

    ecrt_slave_config_state(sc8, &s);

    if (s.al_state != sc8_ana_in_state.al_state)
        printf("AnaIn8: State 0x%02X.\n", s.al_state);

    if (s.online != sc8_ana_in_state.online)
        printf("AnaIn8: %s.\n", s.online ? "online" : "offline");
    if (s.operational != sc8_ana_in_state.operational)
        printf("AnaIn8: %soperational.\n",
               s.operational ? "" : "Not ");

    sc8_ana_in_state = s;
}

/*****************************************************************************/
void sdo_write_driver(uint16_t slave_position){
    uint32_t *abort_code;              // 用于存储中止代码
    int i;
    int ret ;   
    uint8_t data1[1] = {0x03};
    uint8_t data2[1] = {0x06};
    uint8_t data3[1] = {0x07};
    uint8_t data4[1] = {0x0f};
    ret= ecrt_master_sdo_download(master, slave_position, 0x6060, 0x00, data1, (size_t)8, abort_code);
    if (ret == 0) {
        printf("SDO download succeeded.\n");
        } else {
        printf("SDO download failed with abort code: 0x%08X\n", abort_code);
    }
    for(i=0;i<0xffffff;i++);    
    ret= ecrt_master_sdo_download(master, slave_position, 0x6040, 0x00, data2, (size_t)16, abort_code);
    if (ret == 0) {
        printf("SDO download succeeded.\n");
        } else {
        printf("SDO download failed with abort code: 0x%08X\n", abort_code);
    }
    for(i=0;i<0xffffff;i++);    
    ret= ecrt_master_sdo_download(master, slave_position, 0x6040, 0x00, data3, (size_t)16, abort_code);
    if (ret == 0) {
        printf("SDO download succeeded.\n");
        } else {
        printf("SDO download failed with abort code: 0x%08X\n", abort_code);
    }    
    for(i=0;i<0xffffff;i++);    
    ret= ecrt_master_sdo_download(master, slave_position, 0x6040, 0x00, data4, (size_t)16, abort_code);
    if (ret == 0) {
        printf("SDO download succeeded.\n");
        } else {
        printf("SDO download failed with abort code: 0x%08X\n", abort_code);
    }
}

/*****************************************************************************/

void driver_enable(uint16_t slave_position){
/*从站1使能*/
if(EC_READ_U8(domain_pd[slave_position]+off_bytes_0x6061[slave_position])!=0x03){
//     printf("0x6060 0x03 finished\n");
    while (EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position])!=0x06)
    {
        EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position],0x06);
        EC_WRITE_U8(domain_pd[slave_position]+off_bytes_0x6060[slave_position],0x03);
        // for(i=0;i<0xffffff;i++);
        // printf("0x6040 = %x\n",EC_READ_U16(domain1_pd+off_bytes_0x6040));
    }
    // for(i=0;i<0xffffff;i++);
    // printf("0x6040 0x06 finished\n");
    while (EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position])!=0x07)
    {
        EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position],0x07);
        // for(i=0;i<0xffffff;i++);
        // printf("0x6040 = %x\n",EC_READ_U16(domain1_pd+off_bytes_0x6040));                
    }
    // for(i=0;i<0xffffff;i++);
    // printf("0x6040 0x07 finished\n");
    while (EC_READ_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position])!=0x0f)
    {
        EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position],0x0f); 
        // for(i=0;i<0xffffff;i++);
        // printf("0x6040 = %x\n",EC_READ_U16(domain1_pd+off_bytes_0x6040));                
    }
    // printf("0x6040 0x0f finished\n");
    }     
    else{
        if (time_diff > RUNNING_TIME){
            EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position],0x06);
        }
    }  
}

void driver_disable(uint16_t slave_position)
{
    EC_WRITE_U16(domain_pd[slave_position]+off_bytes_0x6040[slave_position],0x06);
}


/* Function Definitions */
static double argInit_real_T(void)
{
  return 0.0;
}
static void argInit_4x4_real_T(double result[16])
{
  int i;
  /* Loop over the array to initialize each element. */
  for (i = 0; i < 16; i++) {
    /* Set the value of the array element.
Change this value to the value that the application requires. */
    result[i] = argInit_real_T();
  }
}




void main_IK_7DOF(void)
{
  double R[16]={-0.0000,1.0000,0.0000,0,-0.8819,0.0000,-0.4714,0,-0.4714,-0.0000,0.8819,0,215.7621,332.6608,-20.2120,1.0000};
  double c1;
  double c2;
  double c3;
  double c4;
  double c5;
  double c6;
  double c7;
  double phi=-0.2618;
  double l1=320;
  double l2=235;
  double Px=238.6386;       
  double Py=332.6608;
  double Pz=89.2800; 
  /* Initialize function 'IK_7DOF' input arguments. */
  /* Initialize function input argument 'R'. */
  /* Call the entry-point 'IK_7DOF'. */
  /* Call the entry-point 'IK_7DOF'. */
  IK_7DOF(R, phi, l1, l2, Px, Py, Pz, &c1, &c2,
          &c3, &c4, &c5, &c6, &c7);
//   printf("theta:%lf %lf %lf %lf %lf %lf %lf \n ",c1,c2,c3,c4,c5,c6,c7);
  
}

/*****************************************************************************/

void cyclic_task()
{
    // receive process data
    ecrt_master_receive(master);
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        ecrt_domain_process(domain[counter_domain]);
    }
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        check_domain_state(counter_domain);
    }


    // // check process data state (optional)
    // check_domain_state(0);
    // check_domain_state(1);
    // check_domain_state(2);
    // check_domain_state(3);
    // check_domain_state(4);
    // check_domain_state(5);
    // check_domain_state(6);
    // check_domain_state(2);

    if (counter)
    {
        counter--;
    }
    else
    {   
        
        counter = FREQUENCY/PERIODS_PER_SECOND-1;
        // calculate new process data
        blink++;

        check_master_state();

        check_slave1_config_states();
        check_slave2_config_states();
        // check_slave3_config_states();
        // check_slave4_config_states();
        // check_slave5_config_states();
        // check_slave6_config_states();
        // check_slave7_config_states();
        check_slave3_config_states();
        main_IK_7DOF();
        unsigned long ssi;
        unsigned long ssi1;
        unsigned long dri;


        

        // printf("0x6041_1 = %x\n",EC_READ_U16(domain1_pd+off_bytes_0x6041[0]));
        // printf("0x6041_2 = %x\n",EC_READ_U16(domain2_pd+off_bytes_0x6041[1]));
        
        /*驱动器使能*/
        for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
        {
            driver_enable(counter_slave);
        }
        // /*从站1使能*/
        // if(EC_READ_U8(domain1_pd+off_bytes_0x6061[0])!=0x03){
        // //     printf("0x6060 0x03 finished\n");
        //     while (EC_READ_U16(domain1_pd+off_bytes_0x6040[0])!=0x06)
        //     {
        //         EC_WRITE_U16(domain1_pd+off_bytes_0x6040[0],0x06);
        //         EC_WRITE_U8(domain1_pd+off_bytes_0x6060[0],0x03);
        //         // for(i=0;i<0xffffff;i++);
        //         // printf("0x6040 = %x\n",EC_READ_U16(domain1_pd+off_bytes_0x6040));
        //     }
        //     // for(i=0;i<0xffffff;i++);
        //     // printf("0x6040 0x06 finished\n");
        //     while (EC_READ_U16(domain1_pd+off_bytes_0x6040[0])!=0x07)
        //     {
        //         EC_WRITE_U16(domain1_pd+off_bytes_0x6040[0],0x07);
        //         // for(i=0;i<0xffffff;i++);
        //         // printf("0x6040 = %x\n",EC_READ_U16(domain1_pd+off_bytes_0x6040));                
        //     }
        //     // for(i=0;i<0xffffff;i++);
        //     // printf("0x6040 0x07 finished\n");
        //     while (EC_READ_U16(domain1_pd+off_bytes_0x6040[0])!=0x0f)
        //     {
        //         EC_WRITE_U16(domain1_pd+off_bytes_0x6040[0],0x0f); 
        //         // for(i=0;i<0xffffff;i++);
        //         // printf("0x6040 = %x\n",EC_READ_U16(domain1_pd+off_bytes_0x6040));                
        //     }
        //     // printf("0x6040 0x0f finished\n");
        //     }     
        //     else{
        //         if (time_diff > RUNNING_TIME){
        //             EC_WRITE_U16(domain1_pd+off_bytes_0x6040[0],0x06);
        //         }
        //     }  

        /*从站2使能*/
        // if(EC_READ_U8(domain2_pd+off_bytes_0x6061[1])!=0x03){
        // //     printf("0x6060 0x03 finished\n");
        //     while (EC_READ_U16(domain2_pd+off_bytes_0x6040[1])!=0x06)
        //     {
        //         EC_WRITE_U16(domain2_pd+off_bytes_0x6040[1],0x06);
        //         EC_WRITE_U8(domain2_pd+off_bytes_0x6060[1],0x03);
        //         // for(i=0;i<0xffffff;i++);
        //         // printf("0x6040 = %x\n",EC_READ_U16(domain_pd+off_bytes_0x6040));
        //     }
        //     // for(i=0;i<0xffffff;i++);
        //     while (EC_READ_U16(domain2_pd+off_bytes_0x6040[1])!=0x07)
        //     {
        //         EC_WRITE_U16(domain2_pd+off_bytes_0x6040[1],0x07);
        //         // for(i=0;i<0xffffff;i++);
        //         // printf("0x6040 = %x\n",EC_READ_U16(domain_pd+off_bytes_0x6040));                
        //     }
        //     // for(i=0;i<0xffffff;i++);
        //     while (EC_READ_U16(domain2_pd+off_bytes_0x6040[1])!=0x0f)
        //     {
        //         EC_WRITE_U16(domain2_pd+off_bytes_0x6040[1],0x0f); 
        //         // for(i=0;i<0xffffff;i++);
        //         // printf("0x6040 = %x\n",EC_READ_U16(domain_pd+off_bytes_0x6040));                
        //     }
        //     }     
        //     else{
        //         if (time_diff > RUNNING_TIME){
        //             EC_WRITE_U16(domain2_pd+off_bytes_0x6040[1],0x06);
        //         }
        //     } 


	
        if(time_diff < RUNNING_TIME){

            //从站数据处理     
            float trans; 
            uint32_t data_pointer[1];
            float angle_all[1];
            ssi=EC_READ_U32(domain_pd[2] + off_bytes_ssi[0]);
            data_pointer[0]=ssi;
            memcpy(angle_all, data_pointer, sizeof(data_pointer));
            Target_Position=angle_all[0];
            // printf("ssi=%f\n",Target_Position);
            ssi=EC_READ_U32(domain_pd[2] + off_bytes_ssi_2[0]);
            data_pointer[0]=ssi;
            memcpy(angle_all, data_pointer, sizeof(data_pointer));
            Actual_Position=angle_all[0];
            // printf("motor ssi1=%f\n",Actual_Position);

            ssi=EC_READ_U32(domain_pd[2] + off_bytes_ssi_3[0]);
            data_pointer[0]=ssi;
            memcpy(angle_all, data_pointer, sizeof(data_pointer));
            Actual_Position2=angle_all[0];
            // printf("motor ssi2=%f\n",Actual_Position2);


            if(flag2==0 && Actual_Position!=0 && Actual_Position2!=0 && Target_Position!=0){
                if((abs(Target_Position)>360 || abs(Actual_Position)>360) || abs(Actual_Position2)>360){
                    Target_Position=0;
                    Actual_Position=0;
                    Actual_Position2=0;
                }
                else
                {
                offset_target_position=Target_Position;
                offset_actual_position=Actual_Position;
                offset_actual_position2=Actual_Position2;
                // printf("offset_Target_Position=%f ,",offset_target_position);
                // printf("offset_Actual_Position=%f\n ",offset_actual_position);
                flag2=1;
                }
            }


            float target_p=Target_Position-offset_target_position;
            float actual_p=Actual_Position-offset_actual_position;
            float actual_p2=Actual_Position2-offset_actual_position2;
            if(abs(target_p)>360||(abs(target_p-target_p_last)<280&&abs(target_p-target_p_last)>20)){
                target_p=target_p_last;
            }
            else if(target_p>180){
                target_p-=360;
            }
            else if(target_p<-180){
                target_p+=360;
            }

            if(abs(actual_p)>360||(abs(actual_p-actual_p_last)<280&&abs(actual_p-actual_p_last)>20)){
                actual_p=actual_p_last;
            }
            else if(actual_p>180){
                actual_p-=360;
            }
            else if(actual_p<-180){
                actual_p+=360;
            }

            if(abs(actual_p2)>360||(abs(actual_p2-actual_p_last2)<280&&abs(actual_p2-actual_p_last2)>20)){
                actual_p2=actual_p_last2;
            }
            else if(actual_p2>180){
                actual_p2-=360;
            }
            else if(actual_p2<-180){
                actual_p2+=360;
            }
            target_p_last=target_p;
            actual_p_last=actual_p;
            actual_p_last2=actual_p2;
            //pid
            Error[0]=actual_p-target_p;
            if(Error[0]>240){
                Error[0]-=360;
            }
            else if(Error[0]<-240){
                Error[0]+=360;
            }
            // printf("Error = %f ,",Error[0]);
            Delta_Error[0]=Error[0]-Error_Last[0];
            Integral[0]=Integral[0]+Error[0];
            // printf("Delta_Error = %f ,",Delta_Error[0]);
            Target_Velocity[0]=Position_Kp*Error[0]+Position_Ki*Integral[0]+Position_Kd*Delta_Error[0];
            if(Target_Velocity[0]>MAX_VELOCITY){
                Target_Velocity[0]=MAX_VELOCITY;
            }
            else if(Target_Velocity[0]<-MAX_VELOCITY){
                Target_Velocity[0]=-MAX_VELOCITY;
            }
            // printf("Target_Velocity = %f \n",Target_Velocity[0]);
            EC_WRITE_S32(domain_pd[0]+off_bytes_0x60ff[0],(int)Target_Velocity[0]);

            Error_Last[0]=Error[0];
            Delta_Error_Last[0]=Delta_Error[0];



           Error[1]=actual_p2-target_p;
            if(Error[1]>240){
                Error[1]-=360;
            }
            else if(Error[1]<-240){
                Error[1]+=360;
            }
            // printf("Error = %f ,",Error[0]);
            Delta_Error[1]=Error[1]-Error_Last[1];
            Integral[1]=Integral[1]+Error[1];
            // printf("Delta_Error = %f ,",Delta_Error[0]);
            Target_Velocity[1]=Position_Kp*Error[1]+Position_Ki*Integral[1]+Position_Kd*Delta_Error[1];
            if(Target_Velocity[1]>MAX_VELOCITY){
                Target_Velocity[1]=MAX_VELOCITY;
            }
            else if(Target_Velocity[1]<-MAX_VELOCITY){
                Target_Velocity[1]=-MAX_VELOCITY;
            }
            // printf("Target_Velocity = %f \n",Target_Velocity[0]);
            EC_WRITE_S32(domain_pd[1]+off_bytes_0x60ff[1],(int)Target_Velocity[1]);

            Error_Last[1]=Error[1];
            Delta_Error_Last[1]=Delta_Error[1];
            if(counter1){
                counter1--;
            }
            else{
                counter1 = 1;
                // printf("offset_Target_Position=%f ,",offset_target_position);
                // printf("offset_Actual_Position=%f\n ",offset_actual_position);
                // printf("Target_Position=%f ,",target_p);
                // printf("Actual_Position=%f\n ",actual_p);
                // printf("Target_Velocity = %f \n",Target_Velocity[0]);

                // printf("offset_Target_Position=%f ,",offset_target_position);
                // printf("offset_Actual_Position=%f\n ",offset_actual_position2);
                // printf("Target_Position=%f ,",target_p);
                // printf("Actual_Position=%f\n ",actual_p2);
                // printf("Target_Velocity = %f \n",Target_Velocity[1]);


            }



            char sendBuf[128];
            sprintf(sendBuf, "d:%f,%f,%f\n",target_p,actual_p,actual_p2);
            sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));
            // printf("Actual Postion_1 = %d \n",EC_READ_S32(domain1_pd+off_bytes_0x6064[0]));
            // trans=U32ToFloat(ssi);



            // printf("ssi:%x\n",ssi);
            // printf("ssi:%u\n",ssi);

            // printf("ain:%u\n",ain1);

            // printf("Target_Position=%f ,",target_p);
            // printf("Actual_Position=%f\n ",actual_p);
            // if(flag == 0&&time_diff <0.5* RUNNING_TIME){
            //     Target_Postion[0]=(float)0;
            //     flag=1;
            // }
            // else if(flag == 1&&time_diff >0.5* RUNNING_TIME){
            //     Target_Postion[0]=(float)10;
            //     flag=2;
            // }

            

            gettimeofday(&tv2, NULL);
            time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
            printf("Time: %.4f s\n", time_diff);
            // printf("sec = %ld\tusec = %ld\n",tv2.tv_sec, tv2.tv_usec);

            // EC_WRITE_U32(domain_pd+off_bytes_0x60ff[0],-TARGET_VELOCITY/2*cos(time_diff)+TARGET_VELOCITY/2);
            // EC_WRITE_U32(domain2_pd+off_bytes_0x60ff[1],-TARGET_VELOCITY/2*cos(time_diff)+TARGET_VELOCITY/2);

            // printf("Target Velocity_1 = %d ,",EC_READ_S32(domain1_pd+off_bytes_0x60ff[0]));
            // printf("Actual Velocity_1 = %d \n",EC_READ_S32(domain1_pd+off_bytes_0x606C[0]));
            // printf("Target Velocity_2 = %d ,",EC_READ_U32(domain2_pd+off_bytes_0x60ff[1]));
            // printf("Actual Velocity_2 = %d \n",EC_READ_U32(domain2_pd+off_bytes_0x606C[1]));

            // printf("Actual Postion_1 = %d \n",EC_READ_S32(domain1_pd+off_bytes_0x6064[0]));

            // /*位置环1*/
            // Error[0]=actual_p-target_p;
            // if(Error[0]>240){
            //     Error[0]-=360;
            // }
            // else if(Error[0]<-240){
            //     Error[0]+=360;
            // }
            // // printf("Error = %f ,",Error[0]);
            // Delta_Error[0]=Error[0]-Error_Last[0];
            // Integral[0]=Integral[0]+Error[0];
            // // printf("Delta_Error = %f ,",Delta_Error[0]);
            // Target_Velocity[0]=Position_Kp*Error[0]+Position_Ki*Integral[0]+Position_Kd*Delta_Error[0];
            // if(Target_Velocity[0]>MAX_VELOCITY){
            //     Target_Velocity[0]=MAX_VELOCITY;
            // }
            // else if(Target_Velocity[0]<-MAX_VELOCITY){
            //     Target_Velocity[0]=-MAX_VELOCITY;
            // }
            // // printf("Target_Velocity = %f \n",Target_Velocity[0]);
            // EC_WRITE_S32(domain1_pd+off_bytes_0x60ff[0],(int)Target_Velocity[0]);

            // Error_Last[0]=Error[0];
            // Delta_Error_Last[0]=Delta_Error[0];
            // if(counter1){
            //     counter1--;
            // }
            // else{
            //     counter1 = 1;
            //     printf("offset_Target_Position=%f ,",offset_target_position);
            //     printf("offset_Actual_Position=%f\n ",offset_actual_position);
            //     printf("Target_Position=%f ,",target_p);
            //     printf("Actual_Position=%f\n ",actual_p);
            //     printf("Target_Velocity = %f \n",Target_Velocity[0]);

            // }

        

            // sprintf(sendBuf, "d:%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n", RJDES[5], *TR_data[4], *TR_data[5],
            //         PID_ptr_M[4].output, PID_ptr_M[5].output, L4real, L5real,Deg[0],Deg[1],Deg[2]);
            // char sendBuf[128];
            // sprintf(sendBuf, "d:%f,%f\n",target_p,actual_p);
            // sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));
            

            // fprintf(fp, "%lf,%f,%f\n",time_diff,target_p,actual_p);



            // /*位置环2*/
            // Actual_Postion[1] = EC_READ_U32(domain2_pd+off_bytes_0x6064[1]);
            // Error[1]=Target_Postion[1]-Actual_Postion[1];
            // Delta_Error[1]=Error[1]-Error_Last[1];
            // Target_Velocity[1]=Target_Velocity[1]+Position_Kp*Delta_Error[1]+Position_Ki*Error[1]+Position_Kd*(Delta_Error[1]-Delta_Error_Last[1]);
            // EC_WRITE_U32(domain2_pd+off_bytes_0x60ff[1],Target_Velocity[1]);
            
            // Error_Last[1]=Error[1];
            // Delta_Error_Last[1]=Delta_Error[1];
            

            
        }
        else{
                // fclose(fp);
                for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {
                driver_disable(counter_slave);
            }
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
    // char sendBuf[128];
    // int send_length = 0;
    // while(1){
    //     bzero(sendBuf,sizeof(sendBuf));
    //     printf("Input:");
    //     fgets(sendBuf,127,stdin);
    //     send_length = sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));
    //     if(send_length < 0 ){
    //         perror("sendto() error");
    //         exit(1);
    //     }
    //     printf("%d\n",send_length);
    // }

    
    // char sendBuf[128];
    // sprintf(sendBuf, "hello,world\n");
    // sendto(fd, sendBuf, strlen(sendBuf) + 1, 0, (struct sockaddr *)&saddr, sizeof(saddr));

    // struct sockaddr_in sender;
    // socklen_t sender_len = sizeof(sender);
    // char buffer[1024];

    // int bytes_received = recvfrom(fd, buffer, sizeof(buffer), 0,
    //                             (struct sockaddr*)&sender, &sender_len);
    // if (bytes_received < 0) {
    // perror("recvfrom failed");
    // // handle error
    // }

    // printf("%d",bytes_received);
    


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
#if CONFIGURE_PDOS

    if (!(sc1 = ecrt_master_slave_config(
              master, BusCouplerPos1, DRIVERICE)))
    {
        fprintf(stderr, "Failed to get slave1 configuration.\n");
        return -1;
    }
    if (!(sc2 = ecrt_master_slave_config(
              master, BusCouplerPos2, DRIVERICE)))
    {
        fprintf(stderr, "Failed to get slave2 configuration.\n");
        return -1;
    }
    // if (!(sc3 = ecrt_master_slave_config(
    //           master, BusCouplerPos3, DRIVERICE)))
    // {
    //     fprintf(stderr, "Failed to get slave3 configuration.\n");
    //     return -1;
    // }
    // if (!(sc4 = ecrt_master_slave_config(
    //           master, BusCouplerPos4, DRIVERICE)))
    // {
    //     fprintf(stderr, "Failed to get slave4 configuration.\n");
    //     return -1;
    // }
    // if (!(sc5 = ecrt_master_slave_config(
    //           master, BusCouplerPos5, DRIVERICE)))
    // {
    //     fprintf(stderr, "Failed to get slave5 configuration.\n");
    //     return -1;
    // }
    // if (!(sc6 = ecrt_master_slave_config(
    //           master, BusCouplerPos6, DRIVERICE)))
    // {
    //     fprintf(stderr, "Failed to get slave6 configuration.\n");
    //     return -1;
    // }
    // if (!(sc7 = ecrt_master_slave_config(
    //           master, BusCouplerPos7, DRIVERICE)))
    // {
    //     fprintf(stderr, "Failed to get slave7 configuration.\n");
    //     return -1;
    // }
    if (!(sc3 = ecrt_master_slave_config(
              master, BusCouplerPos8, ENCODERICE)))
    {
        fprintf(stderr, "Failed to get slave8 configuration.\n");
        return -1;
    }
    


          /* Configure AKD flexible PDO */
    // printf("Configuring AKD with flexible PDO...\n");
       // printf("Define RxPDO...\n");

    // /* Define RxPdo */

    // 设置PDOS，利⽤sc、EC_END、对⻬信息
    printf("Configuring PDOs...\n");

    if (ecrt_slave_config_pdos(sc1, EC_END, slave_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }
    if (ecrt_slave_config_pdos(sc2, EC_END, slave_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }
    // if (ecrt_slave_config_pdos(sc3, EC_END, slave_syncs))
    // {
    //     fprintf(stderr, "Failed to configure PDOs.\n");
    //     return -1;
    // }
    // if (ecrt_slave_config_pdos(sc4, EC_END, slave_syncs))
    // {
    //     fprintf(stderr, "Failed to configure PDOs.\n");
    //     return -1;
    // }
    // if (ecrt_slave_config_pdos(sc5, EC_END, slave_syncs))
    // {
    //     fprintf(stderr, "Failed to configure PDOs.\n");
    //     return -1;
    // }
    // if (ecrt_slave_config_pdos(sc6, EC_END, slave_syncs))
    // {
    //     fprintf(stderr, "Failed to configure PDOs.\n");
    //     return -1;
    // }
    // if (ecrt_slave_config_pdos(sc7, EC_END, slave_syncs))
    // {
    //     fprintf(stderr, "Failed to configure PDOs.\n");
    //     return -1;
    // }
    if (ecrt_slave_config_pdos(sc3, EC_END, slave_0_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
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
    //     if (ecrt_domain_reg_pdo_entry_list(domain[2], domain3_regs)) 
    // {
    //     fprintf(stderr, "PDO3 entry registration failed!\n");
    //     return -1;
    // }
    //     if (ecrt_domain_reg_pdo_entry_list(domain[3], domain4_regs)) 
    // {
    //     fprintf(stderr, "PDO4 entry registration failed!\n");
    //     return -1;
    // }
    //     if (ecrt_domain_reg_pdo_entry_list(domain[4], domain5_regs)) 
    // {
    //     fprintf(stderr, "PDO5 entry registration failed!\n");
    //     return -1;
    // }
    //     if (ecrt_domain_reg_pdo_entry_list(domain[5], domain6_regs)) 
    // {
    //     fprintf(stderr, "PDO6 entry registration failed!\n");
    //     return -1;
    // }    
    //     if (ecrt_domain_reg_pdo_entry_list(domain[6], domain7_regs)) 
    // {
    //     fprintf(stderr, "PDO7 entry registration failed!\n");
    //     return -1;
    // }
        if (ecrt_domain_reg_pdo_entry_list(domain[2], domain8_regs)) 
    {
        fprintf(stderr, "PDO8 entry registration failed!\n");
        return -1;
    }


    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
    {
        sdo_write_driver(counter_slave);
        // sdo_write_driver(1);
        // sdo_write_driver(2);
        // sdo_write_driver(3);
        // sdo_write_driver(4);
        // sdo_write_driver(5);
        // sdo_write_driver(6);
    }


    int i;
    for(i=0;i<0xffffff;i++);
    for(i=0;i<0xffffff;i++);
    for(i=0;i<0xffffff;i++);


#endif

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
    tv.it_value.tv_usec = 2000;//定时器在2ms后启动
    if (setitimer(ITIMER_REAL, &tv, NULL))
    {
        fprintf(stderr, "Failed to start timer: %s\n", strerror(errno));
        return 1;
    }

    printf("Started.\n");
    gettimeofday(&tv1, NULL);

    // fp = fopen("tmp.csv", "w+");
    // if (fp == NULL) {
    //     fprintf(stderr, "fopen() failed.\n");
    //     exit(EXIT_FAILURE);
    // }
    // fprintf(fp, "time,target_p,actual_p\n");

    while (1)
    {
        pause();
        while (sig_alarms != user_alarms)
        {       
            cyclic_task();
            user_alarms++;
        }
        if(time_diff > RUNNING_TIME){printf("timeout.\n");break;}
    }
    return 0;
}

