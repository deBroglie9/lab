#ifndef _ETHERCAT_H_
#define _ETHERCAT_H_

#include "ecrt.h"
#include <stdio.h>
#define DRIVER_NUMBER 14
#define ENCODER_NUMBER 1
#define SENSOR_NUMBER 2
#define DOMAIN_NUMBER 17

// #define FREQUENCY 1000
// #define PRIORITY 1
// #define MAX_VELOCITY_1 900000
// #define MAX_VELOCITY_2 160000
// #define MAX_VELOCITY_3 112000
// #define PERIODS_PER_SECOND   1000
// #define INIT_TIME 2
// #define ERROR 0.1
// #define RUNNING_TIME 150/*seconds*/

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
#define BusCouplerPos17 0, 16


// Optional features
#define CONFIGURE_PDOS 1
#define CONFIGURE_EC 1
#define DRIVERICE 0x0000009a, 0x00030924
#define ENCODERICE 0x00000b95, 0x00020310
#define SENSORICE 0x000000a1, 0x00008081
// offsets for PDO entries

#if CONFIGURE_EC
extern unsigned int off_bytes_0x6040[DRIVER_NUMBER];
extern unsigned int off_bits_0x6040[DRIVER_NUMBER];
extern unsigned int off_bytes_0x6060[DRIVER_NUMBER];
extern unsigned int off_bits_0x6060[DRIVER_NUMBER];
extern unsigned int off_bytes_0x6041[DRIVER_NUMBER];
extern unsigned int off_bits_0x6041[DRIVER_NUMBER];
extern unsigned int off_bytes_0x6061[DRIVER_NUMBER];
extern unsigned int off_bits_0x6061[DRIVER_NUMBER];
extern unsigned int off_bytes_0x6064[DRIVER_NUMBER];
extern unsigned int off_bits_0x6064[DRIVER_NUMBER];
extern unsigned int off_bytes_0x60ff[DRIVER_NUMBER];
extern unsigned int off_bits_0x60ff[DRIVER_NUMBER];
extern unsigned int off_bytes_0x606C[DRIVER_NUMBER];
extern unsigned int off_bits_0x606C[DRIVER_NUMBER];
extern unsigned int off_bytes_0x6077[DRIVER_NUMBER];
extern unsigned int off_bits_0x6077[DRIVER_NUMBER];

extern unsigned int off_bytes_cm_1[ENCODER_NUMBER];
extern unsigned int off_bits_cm_1[ENCODER_NUMBER];
extern unsigned int off_bytes_cm_2[ENCODER_NUMBER];
extern unsigned int off_bits_cm_2[ENCODER_NUMBER];
extern unsigned int off_bytes_target_angle[ENCODER_NUMBER];
extern unsigned int off_bits_target_angle[ENCODER_NUMBER];
extern unsigned int off_bytes_ssi[ENCODER_NUMBER];
extern unsigned int off_bits_ssi[ENCODER_NUMBER];
extern unsigned int off_bytes_ssi1[ENCODER_NUMBER];
extern unsigned int off_bits_ssi1[ENCODER_NUMBER];
extern unsigned int off_bytes_ssi_2[ENCODER_NUMBER];
extern unsigned int off_bits_ssi_2[ENCODER_NUMBER];
extern unsigned int off_bytes_ssi_3[ENCODER_NUMBER];
extern unsigned int off_bits_ssi_3[ENCODER_NUMBER];
extern unsigned int off_bytes_ssi_4[ENCODER_NUMBER];
extern unsigned int off_bits_ssi_4[ENCODER_NUMBER];
extern unsigned int off_bytes_ssi_5[ENCODER_NUMBER];
extern unsigned int off_bits_ssi_5[ENCODER_NUMBER];
extern unsigned int off_bytes_ssi_6[ENCODER_NUMBER];
extern unsigned int off_bits_ssi_6[ENCODER_NUMBER];
extern unsigned int off_bytes_ssi_7[ENCODER_NUMBER];
extern unsigned int off_bits_ssi_7[ENCODER_NUMBER];
extern unsigned int off_bytes_ssi_8[ENCODER_NUMBER];
extern unsigned int off_bits_ssi_8[ENCODER_NUMBER];
extern unsigned int off_bytes_ain_1[ENCODER_NUMBER];
extern unsigned int off_bits_ain_1[ENCODER_NUMBER];
extern unsigned int off_bytes_ain_2[ENCODER_NUMBER];
extern unsigned int off_bits_ain_2[ENCODER_NUMBER];
extern unsigned int off_bytes_ain_3[ENCODER_NUMBER];
extern unsigned int off_bits_ain_3[ENCODER_NUMBER];
extern unsigned int off_bytes_ain_4[ENCODER_NUMBER];
extern unsigned int off_bits_ain_4[ENCODER_NUMBER];
extern unsigned int off_bytes_ain_5[ENCODER_NUMBER];
extern unsigned int off_bits_ain_5[ENCODER_NUMBER];
extern unsigned int off_bytes_ain_6[ENCODER_NUMBER];
extern unsigned int off_bits_ain_6[ENCODER_NUMBER];
extern unsigned int off_bytes_ain_7[ENCODER_NUMBER];
extern unsigned int off_bits_ain_7[ENCODER_NUMBER];
extern unsigned int off_bytes_ain_8[ENCODER_NUMBER];
extern unsigned int off_bits_ain_8[ENCODER_NUMBER];

extern unsigned int off_bytes_0x2000[SENSOR_NUMBER];
extern unsigned int off_bits_0x2000[SENSOR_NUMBER];
extern unsigned int off_bytes_0x2001[SENSOR_NUMBER];
extern unsigned int off_bits_0x2001[SENSOR_NUMBER];
extern unsigned int off_bytes_0x2002[SENSOR_NUMBER];
extern unsigned int off_bits_0x2002[SENSOR_NUMBER];
extern unsigned int off_bytes_0x2003[SENSOR_NUMBER];
extern unsigned int off_bits_0x2003[SENSOR_NUMBER];
extern unsigned int off_bytes_0x2004[SENSOR_NUMBER];
extern unsigned int off_bits_0x2004[SENSOR_NUMBER];
extern unsigned int off_bytes_0x2005[SENSOR_NUMBER];
extern unsigned int off_bits_0x2005[SENSOR_NUMBER];
extern unsigned int off_bytes_0x2006[SENSOR_NUMBER];
extern unsigned int off_bits_0x2006[SENSOR_NUMBER];
extern unsigned int off_bytes_0x2007[SENSOR_NUMBER];
extern unsigned int off_bits_0x2007[SENSOR_NUMBER];
extern unsigned int off_bytes_0x4000[SENSOR_NUMBER];
extern unsigned int off_bits_0x4000[SENSOR_NUMBER];
extern unsigned int off_bytes_0x4001[SENSOR_NUMBER];
extern unsigned int off_bits_0x4001[SENSOR_NUMBER];
extern unsigned int off_bytes_0x4002[SENSOR_NUMBER];
extern unsigned int off_bits_0x4002[SENSOR_NUMBER];
extern unsigned int off_bytes_0x4003[SENSOR_NUMBER];
extern unsigned int off_bits_0x4003[SENSOR_NUMBER];
extern unsigned int off_bytes_0x4004[SENSOR_NUMBER];
extern unsigned int off_bits_0x4004[SENSOR_NUMBER];
extern unsigned int off_bytes_0x4005[SENSOR_NUMBER];
extern unsigned int off_bits_0x4005[SENSOR_NUMBER];
extern unsigned int off_bytes_0x4006[SENSOR_NUMBER];
extern unsigned int off_bits_0x4006[SENSOR_NUMBER];
extern unsigned int off_bytes_0x4007[SENSOR_NUMBER];
extern unsigned int off_bits_0x4007[SENSOR_NUMBER];
extern unsigned int off_bytes_0x4008[SENSOR_NUMBER];
extern unsigned int off_bits_0x4008[SENSOR_NUMBER];

extern ec_master_t *master;
extern ec_master_state_t master_state;
extern ec_domain_t *domain[DOMAIN_NUMBER];
extern ec_domain_state_t domain_state[DOMAIN_NUMBER];
extern ec_slave_config_t *sc[DOMAIN_NUMBER];
extern ec_slave_config_state_t sc_ana_in_state[DOMAIN_NUMBER];
extern uint8_t *domain_pd[DOMAIN_NUMBER];

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

const ec_pdo_entry_reg_t domain9_regs[] = {
{BusCouplerPos9,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[8], &off_bits_0x6040[8]},
{BusCouplerPos9,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[8], &off_bits_0x6060[8]},
{BusCouplerPos9,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[8], &off_bits_0x60ff[8]},
{BusCouplerPos9,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[8], &off_bits_0x6041[8]},
{BusCouplerPos9,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[8], &off_bits_0x6061[8]},
{BusCouplerPos9,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[8], &off_bits_0x6064[8]},
{BusCouplerPos9,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[8], &off_bits_0x606C[8]},
{BusCouplerPos9,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[8], &off_bits_0x6077[8]},
{}
};

const ec_pdo_entry_reg_t domain10_regs[] = {
{BusCouplerPos10,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[9], &off_bits_0x6040[9]},
{BusCouplerPos10,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[9], &off_bits_0x6060[9]},
{BusCouplerPos10,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[9], &off_bits_0x60ff[9]},
{BusCouplerPos10,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[9], &off_bits_0x6041[9]},
{BusCouplerPos10,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[9], &off_bits_0x6061[9]},
{BusCouplerPos10,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[9], &off_bits_0x6064[9]},
{BusCouplerPos10,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[9], &off_bits_0x606C[9]},
{BusCouplerPos10,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[9], &off_bits_0x6077[9]},
{}
};

const ec_pdo_entry_reg_t domain11_regs[] = {
{BusCouplerPos11,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[10], &off_bits_0x6040[10]},
{BusCouplerPos11,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[10], &off_bits_0x6060[10]},
{BusCouplerPos11,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[10], &off_bits_0x60ff[10]},
{BusCouplerPos11,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[10], &off_bits_0x6041[10]},
{BusCouplerPos11,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[10], &off_bits_0x6061[10]},
{BusCouplerPos11,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[10], &off_bits_0x6064[10]},
{BusCouplerPos11,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[10], &off_bits_0x606C[10]},
{BusCouplerPos11,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[10], &off_bits_0x6077[10]},
{}
};

const ec_pdo_entry_reg_t domain12_regs[] = {
{BusCouplerPos12,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[11], &off_bits_0x6040[11]},
{BusCouplerPos12,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[11], &off_bits_0x6060[11]},
{BusCouplerPos12,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[11], &off_bits_0x60ff[11]},
{BusCouplerPos12,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[11], &off_bits_0x6041[11]},
{BusCouplerPos12,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[11], &off_bits_0x6061[11]},
{BusCouplerPos12,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[11], &off_bits_0x6064[11]},
{BusCouplerPos12,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[11], &off_bits_0x606C[11]},
{BusCouplerPos12,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[11], &off_bits_0x6077[11]},
{}
};

const ec_pdo_entry_reg_t domain13_regs[] = {
{BusCouplerPos13,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[12], &off_bits_0x6040[12]},
{BusCouplerPos13,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[12], &off_bits_0x6060[12]},
{BusCouplerPos13,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[12], &off_bits_0x60ff[12]},
{BusCouplerPos13,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[12], &off_bits_0x6041[12]},
{BusCouplerPos13,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[12], &off_bits_0x6061[12]},
{BusCouplerPos13,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[12], &off_bits_0x6064[12]},
{BusCouplerPos13,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[12], &off_bits_0x606C[12]},
{BusCouplerPos13,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[12], &off_bits_0x6077[12]},
{}
};

const ec_pdo_entry_reg_t domain14_regs[] = {
{BusCouplerPos14,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[13], &off_bits_0x6040[13]},
{BusCouplerPos14,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[13], &off_bits_0x6060[13]},
{BusCouplerPos14,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[13], &off_bits_0x60ff[13]},
{BusCouplerPos14,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[13], &off_bits_0x6041[13]},
{BusCouplerPos14,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[13], &off_bits_0x6061[13]},
{BusCouplerPos14,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[13], &off_bits_0x6064[13]},
{BusCouplerPos14,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[13], &off_bits_0x606C[13]},
{BusCouplerPos14,DRIVERICE, 0x6077, 0, &off_bytes_0x6077[13], &off_bits_0x6077[13]},
{}
};

/* Master 0, Slave 7
* Vendor ID:       0x01222222
* Product code:    0x00020310
* Revision number: 0x00020211
*/

const ec_pdo_entry_reg_t domain15_regs[] = {
    // {Alias, Position, Vendor ID, Product Code, PDO Index, -Subindex, Offset}
    {BusCouplerPos15,ENCODERICE, 0x7020, 0x01, &off_bytes_cm_1[0], &off_bits_cm_1[0]},
    {BusCouplerPos15,ENCODERICE, 0x7020, 0x02, &off_bytes_cm_2[0], &off_bits_cm_2[0]},
    {BusCouplerPos15,ENCODERICE, 0x7030, 0x01, &off_bytes_target_angle[0], &off_bits_target_angle[0]},
    {BusCouplerPos15,ENCODERICE, 0x6000, 0x01, &off_bytes_ssi[0], &off_bits_ssi[0]},
    {BusCouplerPos15,ENCODERICE, 0x6000, 0x02, &off_bytes_ssi_2[0], &off_bits_ssi_2[0]},
    {BusCouplerPos15,ENCODERICE, 0x6000, 0x03, &off_bytes_ssi_3[0], &off_bits_ssi_3[0]},
    {BusCouplerPos15,ENCODERICE, 0x6000, 0x04, &off_bytes_ssi_4[0], &off_bits_ssi_4[0]},
    {BusCouplerPos15,ENCODERICE, 0x6000, 0x05, &off_bytes_ssi_5[0], &off_bits_ssi_5[0]},
    {BusCouplerPos15,ENCODERICE, 0x6000, 0x06, &off_bytes_ssi_6[0], &off_bits_ssi_6[0]},
    {BusCouplerPos15,ENCODERICE, 0x6000, 0x07, &off_bytes_ssi_7[0], &off_bits_ssi_7[0]},
    {BusCouplerPos15,ENCODERICE, 0x6000, 0x08, &off_bytes_ssi_8[0], &off_bits_ssi_8[0]},
    {BusCouplerPos15,ENCODERICE, 0x6010, 0x01, &off_bytes_ain_1[0], &off_bits_ain_1[0]},
    {BusCouplerPos15,ENCODERICE, 0x6010, 0x02, &off_bytes_ain_2[0], &off_bits_ain_2[0]},
    {BusCouplerPos15,ENCODERICE, 0x6010, 0x03, &off_bytes_ain_3[0], &off_bits_ain_3[0]},
    {BusCouplerPos15,ENCODERICE, 0x6010, 0x04, &off_bytes_ain_4[0], &off_bits_ain_4[0]},
    {BusCouplerPos15,ENCODERICE, 0x6010, 0x05, &off_bytes_ain_5[0], &off_bits_ain_5[0]},
    {BusCouplerPos15,ENCODERICE, 0x6010, 0x06, &off_bytes_ain_6[0], &off_bits_ain_6[0]},
    {BusCouplerPos15,ENCODERICE, 0x6010, 0x07, &off_bytes_ain_7[0], &off_bits_ain_7[0]},
    {BusCouplerPos15,ENCODERICE, 0x6010, 0x08, &off_bytes_ain_8[0], &off_bits_ain_8[0]},
    {}
};


const ec_pdo_entry_reg_t domain16_regs[] = {
    {BusCouplerPos16,SENSORICE, 0x2000, 0, &off_bytes_0x2000[0], &off_bits_0x2000[0]},
    {BusCouplerPos16,SENSORICE, 0x2001, 0, &off_bytes_0x2001[0], &off_bits_0x2001[0]},
    {BusCouplerPos16,SENSORICE, 0x2002, 0, &off_bytes_0x2002[0], &off_bits_0x2002[0]},
    {BusCouplerPos16,SENSORICE, 0x2003, 0, &off_bytes_0x2003[0], &off_bits_0x2003[0]},
    {BusCouplerPos16,SENSORICE, 0x2004, 0, &off_bytes_0x2004[0], &off_bits_0x2004[0]},
    {BusCouplerPos16,SENSORICE, 0x2005, 0, &off_bytes_0x2005[0], &off_bits_0x2005[0]},
    {BusCouplerPos16,SENSORICE, 0x2006, 0, &off_bytes_0x2006[0], &off_bits_0x2006[0]},
    {BusCouplerPos16,SENSORICE, 0x2007, 0, &off_bytes_0x2007[0], &off_bits_0x2007[0]},
    {BusCouplerPos16,SENSORICE, 0x4000, 0, &off_bytes_0x4000[0], &off_bits_0x4000[0]},
    {BusCouplerPos16,SENSORICE, 0x4001, 0, &off_bytes_0x4001[0], &off_bits_0x4001[0]},
    {BusCouplerPos16,SENSORICE, 0x4002, 0, &off_bytes_0x4002[0], &off_bits_0x4002[0]},
    {BusCouplerPos16,SENSORICE, 0x4003, 0, &off_bytes_0x4003[0], &off_bits_0x4003[0]},
    {BusCouplerPos16,SENSORICE, 0x4004, 0, &off_bytes_0x4004[0], &off_bits_0x4004[0]},
    {BusCouplerPos16,SENSORICE, 0x4005, 0, &off_bytes_0x4005[0], &off_bits_0x4005[0]},
    {BusCouplerPos16,SENSORICE, 0x4006, 0, &off_bytes_0x4006[0], &off_bits_0x4006[0]},
    {BusCouplerPos16,SENSORICE, 0x4007, 0, &off_bytes_0x4007[0], &off_bits_0x4007[0]},
    {BusCouplerPos16,SENSORICE, 0x4008, 0, &off_bytes_0x4008[0], &off_bits_0x4008[0]},
    {}
};

const ec_pdo_entry_reg_t domain17_regs[] = {
    {BusCouplerPos17,SENSORICE, 0x2000, 0, &off_bytes_0x2000[1], &off_bits_0x2000[1]},
    {BusCouplerPos17,SENSORICE, 0x2001, 0, &off_bytes_0x2001[1], &off_bits_0x2001[1]},
    {BusCouplerPos17,SENSORICE, 0x2002, 0, &off_bytes_0x2002[1], &off_bits_0x2002[1]},
    {BusCouplerPos17,SENSORICE, 0x2003, 0, &off_bytes_0x2003[1], &off_bits_0x2003[1]},
    {BusCouplerPos17,SENSORICE, 0x2004, 0, &off_bytes_0x2004[1], &off_bits_0x2004[1]},
    {BusCouplerPos17,SENSORICE, 0x2005, 0, &off_bytes_0x2005[1], &off_bits_0x2005[1]},
    {BusCouplerPos17,SENSORICE, 0x2006, 0, &off_bytes_0x2006[1], &off_bits_0x2006[1]},
    {BusCouplerPos17,SENSORICE, 0x2007, 0, &off_bytes_0x2007[1], &off_bits_0x2007[1]},
    {BusCouplerPos17,SENSORICE, 0x4000, 0, &off_bytes_0x4000[1], &off_bits_0x4000[1]},
    {BusCouplerPos17,SENSORICE, 0x4001, 0, &off_bytes_0x4001[1], &off_bits_0x4001[1]},
    {BusCouplerPos17,SENSORICE, 0x4002, 0, &off_bytes_0x4002[1], &off_bits_0x4002[1]},
    {BusCouplerPos17,SENSORICE, 0x4003, 0, &off_bytes_0x4003[1], &off_bits_0x4003[1]},
    {BusCouplerPos17,SENSORICE, 0x4004, 0, &off_bytes_0x4004[1], &off_bits_0x4004[1]},
    {BusCouplerPos17,SENSORICE, 0x4005, 0, &off_bytes_0x4005[1], &off_bits_0x4005[1]},
    {BusCouplerPos17,SENSORICE, 0x4006, 0, &off_bytes_0x4006[1], &off_bits_0x4006[1]},
    {BusCouplerPos17,SENSORICE, 0x4007, 0, &off_bytes_0x4007[1], &off_bits_0x4007[1]},
    {BusCouplerPos17,SENSORICE, 0x4008, 0, &off_bytes_0x4008[1], &off_bits_0x4008[1]},
    {}
};




extern ec_pdo_entry_info_t slave_pdo_entries[];

extern ec_pdo_info_t slave_pdos[];

extern ec_sync_info_t slave_syncs[];

extern ec_pdo_entry_info_t slave_0_pdo_entries[];

extern ec_pdo_info_t slave_0_pdos[];

extern ec_sync_info_t slave_0_syncs[];

extern ec_pdo_entry_info_t slave_1_pdo_entries[];

extern ec_pdo_info_t slave_1_pdos[];

extern ec_sync_info_t slave_1_syncs[];


extern void check_domain_state(uint16_t slave_position);
extern void check_master_state(void);
extern void check_slave_config_states(int slave_position);
int config();

#endif

#endif
