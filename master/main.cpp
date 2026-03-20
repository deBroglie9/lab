/*****************************************************************************
 * 2025/3/18
 * 重新修改架构，部分代码放入control文件夹下的h文件中，部分放入main.h文件
 * main.cpp仅包含初始化和循环
 * 电机可以正常使能并进行运动
 * 目前接入1个六维力 2个编码器 14个驱动器 代码目前可连接17个从站，2个六维力+1个编码器+14个驱动器，需要修改 DRIVER_NUMBER ENCODER_NUMBER SENSOR_NUMBER DOMAIN_NUMBER
 * 驱动器顺序为右臂1-7 -> 左臂1-7
 * 设置driver_enable,drivesr_disable,reading_driver，reading_ssi，control_pid函数
 * 设置模式选择函数，通过ControlMode修改控制模式（待测试）
 * 加入正逆运动学求解函数，读入X,Y,Z和R(3*3逐行读入)
 * EtherCAT.h库可使用，不使用可设置CONFIGURE_EC 0
 * 
 * 给定了一组轨迹，可读入并执行（已调试），注意修改轨迹时修改对应csv的数组大小 NUMBER
 * 轨迹中1-14依次为左臂1-7、右臂1-7的关节角
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
#include <main.h>


// // 任务周期（以 ns 为单位）
/****************************************************************************/
//控制部分变量


void cyclic_task()
{   
    // printf("%d\n",cmdptr->getUserCmd());
    // printf("%x\n",cmdptr->uservalue.Starttime);
    //计算时间测试
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

        if(counter1){
                counter1--;
        }
        else{
                counter1 = PERIODS_PER_SECOND-1;
                //每秒输打印时间
                gettimeofday(&tv2, NULL);
                time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
                printf("Time: %.4f s\n", time_diff);
                reading_force_torque();
                // reading_ssi();
                // printf("%x\n",cmdptr->uservalue.Starttime);
                // printf("%x\n",cmdptr->uservalue.Starttime);
        }



        //初始化通信
        if(time_diff < INIT_TIME){
            for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
                ecrt_domain_queue(domain[counter_domain]);
            }
            ecrt_master_send(master);
            return;
        }


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
            for(counter_slave=0;counter_slave<7;counter_slave++)
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

            for(counter_slave=0;counter_slave<7;counter_slave++){
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
        // printf("%d\n",cmdptr->uservalue.Stage);
        if((time_diff < RUNNING_TIME)&&(flag_init_all==1)&&(flag_stop_all!=1)){
            
            //((flag_init[0]&flag_init[1]&flag_init[2]&flag_init[3]&flag_init[4]&flag_init[5]&flag_init[6]&flag_init[7]&flag_init[8]&flag_init[9]&flag_init[10]&flag_init[11]&flag_init[12]&flag_init[13])==1)
            
            float trans; 
            for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
            {   
                EC_WRITE_U8(domain_pd[counter_slave]+off_bytes_0x6060[counter_slave], 0x03);
            }

            //读取反馈
            //reading_driver();
            reading_ssi();
            reading_force_torque();
            // reading_current();

            //模式选择
            switch (current_mode) {
                    case MODE_JOINT_TRAJECTORY:
                        // 关节轨迹运动
                        handle_joint_trajectory();
                        break;
                        
                    case MODE_MANUAL_JOINT:
                        // 手动关节控制
                        handle_manual_joint_control();
                        break;
                        
                    case MODE_CARTESIAN_TRAJECTORY:
                        // 末端轨迹运动
                        if(counter2){
                            counter2--;
                        }
                        else{
                            counter2 = PERIODS_PER_SECOND/PERIODS_PER_SECOND_L-1;
                            handle_cartesian_trajectory();
                        }
                        for (counter_slave = 0; counter_slave < 7; counter_slave++) {
                            control_pid(counter_slave);
                            // printf("pid %d\n",counter_slave);
                        }
                        break;
                        
                    case MODE_MANUAL_CARTESIAN:
                        // 手动末端控制
                        handle_manual_cartesian_control();
                        break;
                }
            
        // printf("%f\n",Actual_Torque[3]);
        admittance[0].update(F_ext[0], x_current[0], x_target[0], dt);
        admittance[1].update(F_ext[1], x_current[1], x_target[1], dt);
        write_all_velocity_to_ethercat();
        //udp通信
        UDP_send();


        
            
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

    // Eigen::Vector3d pos;        // x,y,z
    // Eigen::Matrix3d R;          // 旋转矩阵


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
    for(i=0;i<48000;i++){angle[i]=41-40*cos(3.1415926536*i/1200);
    angle[i]=floor(angle[i] * 1000000.000f + 0.5) / 1000000.000f;
    }

    for(i=0;i<48000;i++){
        if(i<2400){
            angle1[i]=i/2400.0*60;
        }
        else{
            angle1[i]=60;
        }

    }

    for(i=0;i<48000;i++){
        if(i<2400){
            angle2[i]=0;
        }
        else{
            angle2[i]=20*sin(3.1415926536*i/1200*6);
        }

    }

    // 打开文件
    // file = fopen("traj_lift.csv", "r");
    // if (file == NULL) {
    //     perror("Error opening file");
    //     return 1;
    // }

    // // 逐行读取文件
    // while (fgets(line, sizeof(line), file)) {
    //     // 使用strtok分割每行的字符串
    //     //printf("%s\n",line );
    //     token = strtok(line, ",");
    //     while (token != NULL) {
    //         // 将字符串转换为double
    //         values[count] = strtod(token, NULL);
    //         count++;
    //         token = strtok(NULL, ",");
    //         // printf("%f\n",count);
    //         if(count>NUMBER)break;
    //     }
    //     if(count>NUMBER)break;
    // }
    // // int j=0;
 	// // printf("%d\n",sizeof(values));
    // // for(i=0;i<20;i++){
    // //     for(j=0;j<14;j++){
    // //         printf("%f  ",values[14*i+j]);
    // // }
    // //     printf("\n");
    // // }
    
    // // 关闭文件
    // fclose(file);
    // printf("read finished\n");
    
    
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
        delete cmdptr;
        system("stty echo");
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
    // handle_cartesian_trajectory();

    for(i=0;i<0xffffff;i++);
    for(i=0;i<0xffffff;i++);
    for(i=0;i<0xffffff;i++);

    butterworthLPF(&filter, cutoffFreq, sampleRate);
    initFilter(&filter);

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

    for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++){
        pid_controller[counter_slave].setParam(5,0,0);
    }
    for(counter_slave=0;counter_slave<2;counter_slave++){
        admittance[counter_slave].setParam(0,1,3,5);
        admittance[counter_slave].setParam(1,1,3,5);
        admittance[counter_slave].setParam(2,1,3,5);

        admittance[counter_slave].setParam(3,1,3,5);
        admittance[counter_slave].setParam(4,1,3,5);
        admittance[counter_slave].setParam(5,1,3,5);
    }

    //计算时间测试
    // double time1;
    // double time2;
    // gettimeofday(&tv2, NULL);
    // time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
    // time1=time_diff;
    // // printf("calculate start Time: %.4f s\n", time_diff);
    // double phi=0*3.1415926535/180;
    // double Px=0.555;
    // double Py=0;
    // double Pz=0;
    // double flag=0;
    // // wrist roll
    // double R[3][3] = {cos(25*3.1415926535/180*0/5),    0,    -sin(25*3.1415926535/180*0/5),
    //                     0,    1,    0,
    //                     sin(25*3.1415926535/180*0/5),    0,    cos(25*3.1415926535/180*0/5)};
    // double c[7];

    // IK(RIGHT_ARM, R, phi, Px, Py, Pz, c, &flag);
    // gettimeofday(&tv2, NULL);
    // time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
    // time2=time_diff;
    // // printf("calculate stop Time: %.4f s\n", time_diff);
    // printf("calculate time: %.6f s\n", time2-time1);


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
            //handle_cartesian_trajectory();
            // reading_force_torque();
            user_alarms++;
            if(time_diff > RUNNING_TIME || flag_stop_all){
                delete cmdptr;
                system("stty echo");
                printf("over.\n");return 0;}
        }
        
    }
    return 0;
}

