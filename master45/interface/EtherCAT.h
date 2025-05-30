#include "ecrt.h"
#include <stdio.h>

// #define FREQUENCY 1000
// #define PRIORITY 1
// #define MAX_VELOCITY_1 900000
// #define MAX_VELOCITY_2 160000
// #define MAX_VELOCITY_3 112000
// #define PERIODS_PER_SECOND   1000
// #define INIT_TIME 2
// #define ERROR 0.1
// #define RUNNING_TIME 150/*seconds*/

#define DRIVER_NUMBER 14
#define ENCODER_NUMBER 2
#define DOMAIN_NUMBER 16
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

const static ec_pdo_entry_reg_t domain3_regs[] = {
    {BusCouplerPos3,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[2], &off_bits_0x6040[2]},
    {BusCouplerPos3,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[2], &off_bits_0x6060[2]},
    {BusCouplerPos3,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[2], &off_bits_0x60ff[2]},
    {BusCouplerPos3,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[2], &off_bits_0x6041[2]},
    {BusCouplerPos3,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[2], &off_bits_0x6061[2]},
    {BusCouplerPos3,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[2], &off_bits_0x6064[2]},
    {BusCouplerPos3,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[2], &off_bits_0x606C[2]},
    {}
};


const static ec_pdo_entry_reg_t domain4_regs[] = {
    {BusCouplerPos4,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[3], &off_bits_0x6040[3]},
    {BusCouplerPos4,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[3], &off_bits_0x6060[3]},
    {BusCouplerPos4,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[3], &off_bits_0x60ff[3]},
    {BusCouplerPos4,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[3], &off_bits_0x6041[3]},
    {BusCouplerPos4,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[3], &off_bits_0x6061[3]},
    {BusCouplerPos4,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[3], &off_bits_0x6064[3]},
    {BusCouplerPos4,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[3], &off_bits_0x606C[3]},
    {}
};

const static ec_pdo_entry_reg_t domain5_regs[] = {
    {BusCouplerPos5,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[4], &off_bits_0x6040[4]},
    {BusCouplerPos5,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[4], &off_bits_0x6060[4]},
    {BusCouplerPos5,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[4], &off_bits_0x60ff[4]},
    {BusCouplerPos5,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[4], &off_bits_0x6041[4]},
    {BusCouplerPos5,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[4], &off_bits_0x6061[4]},
    {BusCouplerPos5,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[4], &off_bits_0x6064[4]},
    {BusCouplerPos5,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[4], &off_bits_0x606C[4]},
    {}
};


const static ec_pdo_entry_reg_t domain6_regs[] = {
    {BusCouplerPos6,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[5], &off_bits_0x6040[5]},
    {BusCouplerPos6,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[5], &off_bits_0x6060[5]},
    {BusCouplerPos6,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[5], &off_bits_0x60ff[5]},
    {BusCouplerPos6,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[5], &off_bits_0x6041[5]},
    {BusCouplerPos6,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[5], &off_bits_0x6061[5]},
    {BusCouplerPos6,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[5], &off_bits_0x6064[5]},
    {BusCouplerPos6,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[5], &off_bits_0x606C[5]},
    {}
};

const static ec_pdo_entry_reg_t domain7_regs[] = {
    {BusCouplerPos7,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[6], &off_bits_0x6040[6]},
    {BusCouplerPos7,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[6], &off_bits_0x6060[6]},
    {BusCouplerPos7,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[6], &off_bits_0x60ff[6]},
    {BusCouplerPos7,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[6], &off_bits_0x6041[6]},
    {BusCouplerPos7,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[6], &off_bits_0x6061[6]},
    {BusCouplerPos7,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[6], &off_bits_0x6064[6]},
    {BusCouplerPos7,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[6], &off_bits_0x606C[6]},
    {}
};

const static ec_pdo_entry_reg_t domain8_regs[] = {
{BusCouplerPos8,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[7], &off_bits_0x6040[7]},
{BusCouplerPos8,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[7], &off_bits_0x6060[7]},
{BusCouplerPos8,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[7], &off_bits_0x60ff[7]},
{BusCouplerPos8,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[7], &off_bits_0x6041[7]},
{BusCouplerPos8,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[7], &off_bits_0x6061[7]},
{BusCouplerPos8,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[7], &off_bits_0x6064[7]},
{BusCouplerPos8,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[7], &off_bits_0x606C[7]},
{}
};

const static ec_pdo_entry_reg_t domain9_regs[] = {
{BusCouplerPos9,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[8], &off_bits_0x6040[8]},
{BusCouplerPos9,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[8], &off_bits_0x6060[8]},
{BusCouplerPos9,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[8], &off_bits_0x60ff[8]},
{BusCouplerPos9,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[8], &off_bits_0x6041[8]},
{BusCouplerPos9,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[8], &off_bits_0x6061[8]},
{BusCouplerPos9,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[8], &off_bits_0x6064[8]},
{BusCouplerPos9,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[8], &off_bits_0x606C[8]},
{}
};

const static ec_pdo_entry_reg_t domain10_regs[] = {
{BusCouplerPos10,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[9], &off_bits_0x6040[9]},
{BusCouplerPos10,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[9], &off_bits_0x6060[9]},
{BusCouplerPos10,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[9], &off_bits_0x60ff[9]},
{BusCouplerPos10,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[9], &off_bits_0x6041[9]},
{BusCouplerPos10,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[9], &off_bits_0x6061[9]},
{BusCouplerPos10,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[9], &off_bits_0x6064[9]},
{BusCouplerPos10,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[9], &off_bits_0x606C[9]},
{}
};

const static ec_pdo_entry_reg_t domain11_regs[] = {
{BusCouplerPos11,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[10], &off_bits_0x6040[10]},
{BusCouplerPos11,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[10], &off_bits_0x6060[10]},
{BusCouplerPos11,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[10], &off_bits_0x60ff[10]},
{BusCouplerPos11,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[10], &off_bits_0x6041[10]},
{BusCouplerPos11,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[10], &off_bits_0x6061[10]},
{BusCouplerPos11,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[10], &off_bits_0x6064[10]},
{BusCouplerPos11,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[10], &off_bits_0x606C[10]},
{}
};

const static ec_pdo_entry_reg_t domain12_regs[] = {
{BusCouplerPos12,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[11], &off_bits_0x6040[11]},
{BusCouplerPos12,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[11], &off_bits_0x6060[11]},
{BusCouplerPos12,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[11], &off_bits_0x60ff[11]},
{BusCouplerPos12,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[11], &off_bits_0x6041[11]},
{BusCouplerPos12,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[11], &off_bits_0x6061[11]},
{BusCouplerPos12,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[11], &off_bits_0x6064[11]},
{BusCouplerPos12,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[11], &off_bits_0x606C[11]},
{}
};

const static ec_pdo_entry_reg_t domain13_regs[] = {
{BusCouplerPos13,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[12], &off_bits_0x6040[12]},
{BusCouplerPos13,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[12], &off_bits_0x6060[12]},
{BusCouplerPos13,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[12], &off_bits_0x60ff[12]},
{BusCouplerPos13,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[12], &off_bits_0x6041[12]},
{BusCouplerPos13,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[12], &off_bits_0x6061[12]},
{BusCouplerPos13,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[12], &off_bits_0x6064[12]},
{BusCouplerPos13,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[12], &off_bits_0x606C[12]},
{}
};

const static ec_pdo_entry_reg_t domain14_regs[] = {
{BusCouplerPos14,DRIVERICE, 0x6040, 0, &off_bytes_0x6040[13], &off_bits_0x6040[13]},
{BusCouplerPos14,DRIVERICE, 0x6060, 0, &off_bytes_0x6060[13], &off_bits_0x6060[13]},
{BusCouplerPos14,DRIVERICE, 0x60ff, 0, &off_bytes_0x60ff[13], &off_bits_0x60ff[13]},
{BusCouplerPos14,DRIVERICE, 0x6041, 0, &off_bytes_0x6041[13], &off_bits_0x6041[13]},
{BusCouplerPos14,DRIVERICE, 0x6061, 0, &off_bytes_0x6061[13], &off_bits_0x6061[13]},
{BusCouplerPos14,DRIVERICE, 0x6064, 0, &off_bytes_0x6064[13], &off_bits_0x6064[13]},
{BusCouplerPos14,DRIVERICE, 0x606C, 0, &off_bytes_0x606C[13], &off_bits_0x606C[13]},
{}
};

/* Master 0, Slave 7
* Vendor ID:       0x01222222
* Product code:    0x00020310
* Revision number: 0x00020211
*/

const static ec_pdo_entry_reg_t domain15_regs[] = {
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

const static ec_pdo_entry_reg_t domain16_regs[] = {
    // {Alias, Position, Vendor ID, Product Code, PDO Index, -Subindex, Offset}
    {BusCouplerPos16,ENCODERICE, 0x7020, 0x01, &off_bytes_cm_1[1], &off_bits_cm_1[1]},
    {BusCouplerPos16,ENCODERICE, 0x7020, 0x02, &off_bytes_cm_2[1], &off_bits_cm_2[1]},
    {BusCouplerPos16,ENCODERICE, 0x7030, 0x01, &off_bytes_target_angle[1], &off_bits_target_angle[1]},
    {BusCouplerPos16,ENCODERICE, 0x6000, 0x01, &off_bytes_ssi[1], &off_bits_ssi[1]},
    {BusCouplerPos16,ENCODERICE, 0x6000, 0x02, &off_bytes_ssi_2[1], &off_bits_ssi_2[1]},
    {BusCouplerPos16,ENCODERICE, 0x6000, 0x03, &off_bytes_ssi_3[1], &off_bits_ssi_3[1]},
    {BusCouplerPos16,ENCODERICE, 0x6000, 0x04, &off_bytes_ssi_4[1], &off_bits_ssi_4[1]},
    {BusCouplerPos16,ENCODERICE, 0x6000, 0x05, &off_bytes_ssi_5[1], &off_bits_ssi_5[1]},
    {BusCouplerPos16,ENCODERICE, 0x6000, 0x06, &off_bytes_ssi_6[1], &off_bits_ssi_6[1]},
    {BusCouplerPos16,ENCODERICE, 0x6000, 0x07, &off_bytes_ssi_7[1], &off_bits_ssi_7[1]},
    {BusCouplerPos16,ENCODERICE, 0x6000, 0x08, &off_bytes_ssi_8[1], &off_bits_ssi_8[1]},
    {BusCouplerPos16,ENCODERICE, 0x6010, 0x01, &off_bytes_ain_1[1], &off_bits_ain_1[1]},
    {BusCouplerPos16,ENCODERICE, 0x6010, 0x02, &off_bytes_ain_2[1], &off_bits_ain_2[1]},
    {BusCouplerPos16,ENCODERICE, 0x6010, 0x03, &off_bytes_ain_3[1], &off_bits_ain_3[1]},
    {BusCouplerPos16,ENCODERICE, 0x6010, 0x04, &off_bytes_ain_4[1], &off_bits_ain_4[1]},
    {BusCouplerPos16,ENCODERICE, 0x6010, 0x05, &off_bytes_ain_5[1], &off_bits_ain_5[1]},
    {BusCouplerPos16,ENCODERICE, 0x6010, 0x06, &off_bytes_ain_6[1], &off_bits_ain_6[1]},
    {BusCouplerPos16,ENCODERICE, 0x6010, 0x07, &off_bytes_ain_7[1], &off_bits_ain_7[1]},
    {BusCouplerPos16,ENCODERICE, 0x6010, 0x08, &off_bytes_ain_8[1], &off_bits_ain_8[1]},
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
        master, BusCouplerPos9, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave9 configuration.\n");
    return -1;
}
if (!(sc[9] = ecrt_master_slave_config(
        master, BusCouplerPos10, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave10 configuration.\n");
    return -1;
}
if (!(sc[10] = ecrt_master_slave_config(
        master, BusCouplerPos11, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave11 configuration.\n");
    return -1;
}
if (!(sc[11] = ecrt_master_slave_config(
        master, BusCouplerPos12, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave12 configuration.\n");
    return -1;
}     
if (!(sc[12] = ecrt_master_slave_config(
        master, BusCouplerPos13, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave13 configuration.\n");
    return -1;
}
if (!(sc[13] = ecrt_master_slave_config(
        master, BusCouplerPos14, DRIVERICE)))
{
    fprintf(stderr, "Failed to get slave14 configuration.\n");
    return -1;
}
if (!(sc[14] = ecrt_master_slave_config(
        master, BusCouplerPos15, ENCODERICE)))
{
    fprintf(stderr, "Failed to get slave15 configuration.\n");
    return -1;
}     
if (!(sc[15] = ecrt_master_slave_config(
        master, BusCouplerPos16, ENCODERICE)))
{
    fprintf(stderr, "Failed to get slave16 configuration.\n");
    return -1;
}     

    


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
        if (ecrt_domain_reg_pdo_entry_list(domain[9], domain10_regs)) 
    {
        fprintf(stderr, "PDO10 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[10], domain11_regs)) 
    {
        fprintf(stderr, "PDO11 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[11], domain12_regs)) 
    {
        fprintf(stderr, "PDO12 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[12], domain13_regs)) 
    {
        fprintf(stderr, "PDO13 entry registration failed!\n");
        return -1;
    }    
        if (ecrt_domain_reg_pdo_entry_list(domain[13], domain14_regs)) 
    {
        fprintf(stderr, "PDO14 entry registration failed!\n");
        return -1;
    }
        if (ecrt_domain_reg_pdo_entry_list(domain[14], domain15_regs)) 
    {
        fprintf(stderr, "PDO15 entry registration failed!\n");
        return -1;
    }     
        if (ecrt_domain_reg_pdo_entry_list(domain[15], domain16_regs)) 
    {
        fprintf(stderr, "PDO16 entry registration failed!\n");
        return -1;
    }     
    return 0;
    #endif
}
