/*****************************************************************************
 * 2025/4/7
 * EtherCAT.h库可使用，不使用可设置CONFIGURE_EC 0，修改节点需要对应修改
 * 重新修改架构，部分代码放入control文件夹下的h文件中，部分放入main.h文件，main.cpp仅包含初始化和循环
 * 加入admittance_controller导纳控制，目前可以实现末端位置导纳
 * 加入示教的读取和复现函数
 * 
 * 
 * 目前接入1个六维力 2个编码器 14个驱动器 代码目前可连接17个从站，2个六维力+1个编码器+14个驱动器，需要修改 DRIVER_NUMBER ENCODER_NUMBER SENSOR_NUMBER DOMAIN_NUMBER
 * 驱动器顺序为右臂1-7 -> 左臂1-7 -> 采集模块 -> 左臂六维力
 *
 * 电机可以正常使能并进行运动
 * 设置函数
 * driver_enable:电机使能函数
 * drivesr_disable:电机去使能函数
 * reading_driver:读取电机端编码器（无记忆），转换为角度degree
 * reading_ssi:读取输出端编码器（有记忆，零位提前确定），转换为角度
 * control_pid:PID控制，输出角度信号
 * teaching_record:示教法读入关节轨迹，停止时储存到csv文件下
 * replay_record:读取示教csv文件中关节轨迹并进行跟踪
 * write_all_velocity_to_ethercat:将速度指令输出到从站驱动器
 * 设置模式选择，通过ControlMode修改控制模式
 * 加入正逆运动学求解函数FK IK（rad）
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
    // printf("calculate start Time: %.4f s\n", time_diff);


    // receive process data
    ecrt_master_receive(master);
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        ecrt_domain_process(domain[counter_domain]);
    }
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        check_domain_state(counter_domain);
    }

    //循环部分
    if (counter)
    {
        counter--;
    }
    else
    {   

        counter = FREQUENCY/PERIODS_PER_SECOND-1;
        // calculate new process data
        // main_IK_7DOF();

        //每秒输打印时间
        if(counter1){
                counter1--;
        }
        else{
                counter1 = PERIODS_PER_SECOND-1;
                
                gettimeofday(&tv2, NULL);
                time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
                printf("Time: %.4f s\n", time_diff);
                //reading_force_torque();
                // reading_ssi();
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
            flag_init_all=1;
            if((time_diff < RUNNING_TIME)&&(flag_stop_all!=1)){
                //printf("test2\n");
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
                reading_current();

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
                            handle_cartesian_trajectory();
                            break;
                            
                        case MODE_MANUAL_CARTESIAN:
                            // 手动末端控制
                            handle_manual_cartesian_control();
                            break;

                        case MODE_TEACH_REPLAY:
                            // 示教轨迹复现
                            replay_record();
                            break;
                    }
                
                // printf("%f\n",Actual_Torque[3]);
                write_all_velocity_to_ethercat();
                //udp通信
                UDP_send();
            }

            else if((time_diff > RUNNING_TIME) || (flag_stop_all==1)){
                    // fclose(fp);
                for(counter_slave=0;counter_slave<DRIVER_NUMBER;counter_slave++)
                {
                    driver_disable(counter_slave);
                    printf("%d stop\n",counter_slave);
                }
            }  
        }
        //示教部分
        if(cmdptr->uservalue.Teachingtime && !cmdptr->uservalue.Stoptime){
            reading_ssi();
            teaching_record();
        }
        if(cmdptr->uservalue.Stoptime){
            if(cmdptr->uservalue.Teachingtime){
                saveTrajectoryToCSV(joint_trajectory, "trajectory.csv");
            }

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

        
    }
    
    //  send process data
    check_master_state();
    for(counter_slave=0;counter_slave<DOMAIN_NUMBER;counter_slave++){
        check_slave_config_states(counter_slave);
    }
    for(counter_domain=0;counter_domain<DOMAIN_NUMBER;counter_domain++){
        ecrt_domain_queue(domain[counter_domain]);
    }
    ecrt_master_send(master);

    // gettimeofday(&tv2, NULL);
    // time_diff = (double)( tv2.tv_sec - tv1.tv_sec + (double)(tv2.tv_usec - tv1.tv_usec)/ 1000000);
    // time2=time_diff;
    // // printf("calculate stop Time: %.4f s\n", time_diff);
    // printf("calculate time: %.6f s\n", time2-time1);
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

    Eigen::Vector3d posture_test={0,0,0};        // x,y,z
    Eigen::Matrix3d R_test;          // 旋转矩阵
    Eigen::Vector3d posture_verify;
    R_test=axis_itrans(posture_test);
    posture_verify=axis_trans(R_test);
    std::cout << R_test << std::endl;
    std::cout << posture_test << std::endl;
    std::cout << posture_verify << std::endl;

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
    // for(i=0;i<48000;i++){angle[i]=41-40*cos(3.1415926536*i/1200);
    // angle[i]=floor(angle[i] * 1000000.000f + 0.5) / 1000000.000f;
    // }
    for(i=0;i<48000;i++){angle[i]=60-30*cos(3.1415926536*i/3000);
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

    //示教轨迹读取
    loadTrajectoryFromCSV(joint_trajectory, "trajectory.csv");
    printf("%d\n",joint_trajectory.size());
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
        pid_controller[counter_slave].setParam(2,0,0);
    }
    for(counter_slave=0;counter_slave<2;counter_slave++){
        admittance[counter_slave].setParam(0,2,5,250);
        admittance[counter_slave].setParam(1,2,5,250);
        admittance[counter_slave].setParam(2,2,5,250);

        admittance[counter_slave].setParam(3,99999999999,0,0);
        admittance[counter_slave].setParam(4,99999999999,0,0);
        admittance[counter_slave].setParam(5,99999999999,0,0);
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
    printf("**********press t to teach**********\n");
    //handle_cartesian_trajectory();
    while (1)
    {
        pause();
        while (sig_alarms != user_alarms)
        {       
            cyclic_task();
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

