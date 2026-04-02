#include "EtherCAT.h"

#if CONFIGURE_EC
unsigned int off_bytes_0x6040[DRIVER_NUMBER];
unsigned int off_bits_0x6040[DRIVER_NUMBER];
unsigned int off_bytes_0x6060[DRIVER_NUMBER];
unsigned int off_bits_0x6060[DRIVER_NUMBER];
unsigned int off_bytes_0x6041[DRIVER_NUMBER];
unsigned int off_bits_0x6041[DRIVER_NUMBER];
unsigned int off_bytes_0x6061[DRIVER_NUMBER];
unsigned int off_bits_0x6061[DRIVER_NUMBER];
unsigned int off_bytes_0x6064[DRIVER_NUMBER];
unsigned int off_bits_0x6064[DRIVER_NUMBER];
unsigned int off_bytes_0x60ff[DRIVER_NUMBER];
unsigned int off_bits_0x60ff[DRIVER_NUMBER];
unsigned int off_bytes_0x606C[DRIVER_NUMBER];
unsigned int off_bits_0x606C[DRIVER_NUMBER];
unsigned int off_bytes_0x6077[DRIVER_NUMBER];
unsigned int off_bits_0x6077[DRIVER_NUMBER];

unsigned int off_bytes_cm_1[ENCODER_NUMBER];
unsigned int off_bits_cm_1[ENCODER_NUMBER];
unsigned int off_bytes_cm_2[ENCODER_NUMBER];
unsigned int off_bits_cm_2[ENCODER_NUMBER];
unsigned int off_bytes_target_angle[ENCODER_NUMBER];
unsigned int off_bits_target_angle[ENCODER_NUMBER];
unsigned int off_bytes_ssi[ENCODER_NUMBER];
unsigned int off_bits_ssi[ENCODER_NUMBER];
unsigned int off_bytes_ssi1[ENCODER_NUMBER];
unsigned int off_bits_ssi1[ENCODER_NUMBER];
unsigned int off_bytes_ssi_2[ENCODER_NUMBER];
unsigned int off_bits_ssi_2[ENCODER_NUMBER];
unsigned int off_bytes_ssi_3[ENCODER_NUMBER];
unsigned int off_bits_ssi_3[ENCODER_NUMBER];
unsigned int off_bytes_ssi_4[ENCODER_NUMBER];
unsigned int off_bits_ssi_4[ENCODER_NUMBER];
unsigned int off_bytes_ssi_5[ENCODER_NUMBER];
unsigned int off_bits_ssi_5[ENCODER_NUMBER];
unsigned int off_bytes_ssi_6[ENCODER_NUMBER];
unsigned int off_bits_ssi_6[ENCODER_NUMBER];
unsigned int off_bytes_ssi_7[ENCODER_NUMBER];
unsigned int off_bits_ssi_7[ENCODER_NUMBER];
unsigned int off_bytes_ssi_8[ENCODER_NUMBER];
unsigned int off_bits_ssi_8[ENCODER_NUMBER];
unsigned int off_bytes_ain_1[ENCODER_NUMBER];
unsigned int off_bits_ain_1[ENCODER_NUMBER];
unsigned int off_bytes_ain_2[ENCODER_NUMBER];
unsigned int off_bits_ain_2[ENCODER_NUMBER];
unsigned int off_bytes_ain_3[ENCODER_NUMBER];
unsigned int off_bits_ain_3[ENCODER_NUMBER];
unsigned int off_bytes_ain_4[ENCODER_NUMBER];
unsigned int off_bits_ain_4[ENCODER_NUMBER];
unsigned int off_bytes_ain_5[ENCODER_NUMBER];
unsigned int off_bits_ain_5[ENCODER_NUMBER];
unsigned int off_bytes_ain_6[ENCODER_NUMBER];
unsigned int off_bits_ain_6[ENCODER_NUMBER];
unsigned int off_bytes_ain_7[ENCODER_NUMBER];
unsigned int off_bits_ain_7[ENCODER_NUMBER];
unsigned int off_bytes_ain_8[ENCODER_NUMBER];
unsigned int off_bits_ain_8[ENCODER_NUMBER];

unsigned int off_bytes_0x2000[SENSOR_NUMBER];
unsigned int off_bits_0x2000[SENSOR_NUMBER];
unsigned int off_bytes_0x2001[SENSOR_NUMBER];
unsigned int off_bits_0x2001[SENSOR_NUMBER];
unsigned int off_bytes_0x2002[SENSOR_NUMBER];
unsigned int off_bits_0x2002[SENSOR_NUMBER];
unsigned int off_bytes_0x2003[SENSOR_NUMBER];
unsigned int off_bits_0x2003[SENSOR_NUMBER];
unsigned int off_bytes_0x2004[SENSOR_NUMBER];
unsigned int off_bits_0x2004[SENSOR_NUMBER];
unsigned int off_bytes_0x2005[SENSOR_NUMBER];
unsigned int off_bits_0x2005[SENSOR_NUMBER];
unsigned int off_bytes_0x2006[SENSOR_NUMBER];
unsigned int off_bits_0x2006[SENSOR_NUMBER];
unsigned int off_bytes_0x2007[SENSOR_NUMBER];
unsigned int off_bits_0x2007[SENSOR_NUMBER];
unsigned int off_bytes_0x4000[SENSOR_NUMBER];
unsigned int off_bits_0x4000[SENSOR_NUMBER];
unsigned int off_bytes_0x4001[SENSOR_NUMBER];
unsigned int off_bits_0x4001[SENSOR_NUMBER];
unsigned int off_bytes_0x4002[SENSOR_NUMBER];
unsigned int off_bits_0x4002[SENSOR_NUMBER];
unsigned int off_bytes_0x4003[SENSOR_NUMBER];
unsigned int off_bits_0x4003[SENSOR_NUMBER];
unsigned int off_bytes_0x4004[SENSOR_NUMBER];
unsigned int off_bits_0x4004[SENSOR_NUMBER];
unsigned int off_bytes_0x4005[SENSOR_NUMBER];
unsigned int off_bits_0x4005[SENSOR_NUMBER];
unsigned int off_bytes_0x4006[SENSOR_NUMBER];
unsigned int off_bits_0x4006[SENSOR_NUMBER];
unsigned int off_bytes_0x4007[SENSOR_NUMBER];
unsigned int off_bits_0x4007[SENSOR_NUMBER];
unsigned int off_bytes_0x4008[SENSOR_NUMBER];
unsigned int off_bits_0x4008[SENSOR_NUMBER];

ec_pdo_entry_info_t slave_pdo_entries[] = {
    {0x6040, 0x00, 16}, /* Controlword */
    {0x6060, 0x00, 8}, /* Modes of operation */
    {0x60ff, 0x00, 32}, /* Target velocity */
    {0x6041, 0x00, 16},/* Statusword */
    {0x6061, 0x00, 8}, /* Modes of operation display */
    {0x6064, 0x00, 32}, /* Position actual value */
    {0x606C, 0x00, 32}, /* Velocity actual value */
    {0x6077, 0x00, 16}, /* Torque actual value */
};

ec_pdo_info_t slave_pdos[] = {
    {0x1607, 3, slave_pdo_entries + 0}, /* RPDO1 Mapping */
    {0x1a07, 5, slave_pdo_entries + 3}, /* TPDO1 Mapping */
};

ec_sync_info_t slave_syncs[] = {
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
    {0x6010, 0x01, 32}, /* ain1 */
    {0x6010, 0x02, 32}, /* ain2 */
    {0x6010, 0x03, 32}, /* ain3 */
    {0x6010, 0x04, 32}, /* ain4 */
    {0x6010, 0x05, 32}, /* ain5 */
    {0x6010, 0x06, 32}, /* ain6 */
    {0x6010, 0x07, 32}, /* ain7 */
    {0x6010, 0x08, 32}, /* ain8 */
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

ec_pdo_entry_info_t slave_1_pdo_entries[] = {
    {0x2000, 0x00, 32}, /* ControlCode */
    {0x2001, 0x00, 32}, /* x */
    {0x2002, 0x00, 32}, /* y */
    {0x2003, 0x00, 32}, /* z */
    {0x2004, 0x00, 32}, /* a */
    {0x2005, 0x00, 32}, /* b */
    {0x2006, 0x00, 32}, /* c */
    {0x2007, 0x00, 32}, /* d */
    {0x4000, 0x00, 32}, /* Fx */
    {0x4001, 0x00, 32}, /* Fy */
    {0x4002, 0x00, 32}, /* Fz */
    {0x4003, 0x00, 32}, /* Mx */
    {0x4004, 0x00, 32}, /* My */
    {0x4005, 0x00, 32}, /* Mz */
    {0x4006, 0x00, 32}, /* StatusCode */
    {0x4007, 0x00, 32}, /* SampleCounter */
    {0x4008, 0x00, 32}, /* Temper */
};

ec_pdo_info_t slave_1_pdos[] = {
    {0x1600, 8, slave_1_pdo_entries + 0}, /* RxPDO 1 */
    {0x1a00, 9, slave_1_pdo_entries + 8}, /* TxPDO 1 */
};

ec_sync_info_t slave_1_syncs[] = {
    {0, EC_DIR_OUTPUT, 0, NULL, EC_WD_DISABLE},
    {1, EC_DIR_INPUT, 0, NULL, EC_WD_DISABLE},
    {2, EC_DIR_OUTPUT, 1, slave_1_pdos + 0, EC_WD_ENABLE},
    {3, EC_DIR_INPUT, 1, slave_1_pdos + 1, EC_WD_DISABLE},
    {0xff}
};

ec_master_t *master = NULL;
ec_master_state_t master_state = {};
ec_domain_t *domain[DOMAIN_NUMBER];
ec_domain_state_t domain_state[DOMAIN_NUMBER];
ec_slave_config_t *sc[DOMAIN_NUMBER];
ec_slave_config_state_t sc_ana_in_state[DOMAIN_NUMBER];
uint8_t *domain_pd[DOMAIN_NUMBER];

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
        master, BusCouplerPos16, SENSORICE)))
{
    fprintf(stderr, "Failed to get slave16 configuration.\n");
    return -1;
}     
// if (!(sc[16] = ecrt_master_slave_config(
//         master, BusCouplerPos17, SENSORICE)))
// {
//     fprintf(stderr, "Failed to get slave17 configuration.\n");
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
    for(count=DRIVER_NUMBER;count<DRIVER_NUMBER+ENCODER_NUMBER;count++){
        if (ecrt_slave_config_pdos(sc[count], EC_END, slave_0_syncs))
    {
        fprintf(stderr, "Failed to configure PDOs.\n");
        return -1;
    }
    }
    for(count=DRIVER_NUMBER+ENCODER_NUMBER;count<DOMAIN_NUMBER;count++){
        if (ecrt_slave_config_pdos(sc[count], EC_END, slave_1_syncs))
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
    //     if (ecrt_domain_reg_pdo_entry_list(domain[16], domain17_regs)) 
    // {
    //     fprintf(stderr, "PDO17 entry registration failed!\n");
    //     return -1;
    // }     
    return 0;
    #endif
}
#endif