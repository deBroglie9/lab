#include "EtherCAT.h"
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