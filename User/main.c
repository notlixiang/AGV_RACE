/***********************************************************************
文件名称：main.C
功    能：
编写时间：
编 写 人：
注    意：
***********************************************************************/
#include "main.h"

#define abs(x) ((x)>=0?(x):-(x))

float AGV_OUT_SPEED_K = OUT_SPEED_K;
float AGV_SHAPE_K = (LENGTH + WIDTH) / 2;

#define SPEED_MAX 1200        //	mm/s 直线速度，经过测试可以保证驱动器稳定工作最高为700
#define OMEGA_MAX SPEED_MAX/AGV_SHAPE_K        // 	mrad/s	旋转速度，保证驱动器稳定工作

#define DELTA_SPEED_MAX 100
#define DELTA_OMEGA_MAX DELTA_SPEED_MAX/AGV_SHAPE_K


#define Speed_K 5000

//install direction of motors output axis, let left direction installnation as positive.


#define msg_cnt_max  2000

/***********************************************************************
[omga1]       [1 -1 -(LENGTH+WIDTH)/2] [vx]
[omga2] = 1/r [1  1 -(LENGTH+WIDTH)/2] [vy]
[omga3]       [1 -1  (LENGTH+WIDTH)/2] [w ]
[omga4]       [1  1  (LENGTH+WIDTH)/2]
r=RADIUS_OF_WHEEL
unit of vx vy are m/s
unit of w is rad/s
unit of omga_i is rad/s
[omga1_]   [0.136419 -0.136419 -1.464286] [vx_]
[omga2_] = [0.136419  0.136419 -1.464286] [vy_]
[omga3_]   [0.136419 -0.136419  1.464286] [w_ ]
[omga4_]   [0.136419  0.136419  1.464286]
unit of omga1_ omga2_ omga3_ omga4_ are rpm
unit of vx_ vy_ are mm/s
unit of w_ is rpm
***********************************************************************/

volatile char received_data[200] = {0};
uint8_t received_len = 0;
uint8_t begin1[2] = {0x01, 0x0f}; // id=0x00;
uint8_t begin2[8] = {0x2f, 0x60, 0x60, 0x00, 0x03, 0x00, 0x00, 0x00};//2F 60 60 00 03 00 00 00 id=0x600+num:
uint8_t begin3[8] = {0x2b, 0x40, 0x60, 0x00, 0x1F, 0x00, 0x00, 0x00};//2b 40 60 00 1F 00 00 00
uint8_t init[2] = {0x01, 0x0f};

//uint8_t command1[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0x3c, 0xf6, 0xff};//23 FF 60 00 00 c4 09 00
//uint8_t command2[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0x3c, 0xf6, 0xff};
//uint8_t command3[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0x3c, 0xf6, 0xff};
//uint8_t command4[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0x3c, 0xf6, 0xff};
//uint8_t command4[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0xc4, 0x09, 0x00};

uint8_t command_test[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0xc4, 0x09, 0x00};

uint8_t command1[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};//23 FF 60 00 00 c4 09 00
uint8_t command2[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t command3[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};
uint8_t command4[8] = {0x23, 0xff, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t command_read_position[8] = {0xA0, 0x40, 0x22, 0x00, 0x7F, 0x0E, 0x00, 0x00};
uint8_t command_read_speed[8] = {0xA0, 0x69, 0x60, 0x00, 0x7F, 0x0E, 0x00, 0x00};

int32_t speed_read_value[4] = {0.0, 0.0, 0.0, 0.0};//读取的速度值
int32_t position_read_value[4] = {0.0, 0.0, 0.0, 0.0};//读取的位置值



uint8_t agv_started = 0;
uint8_t first_start = 0;

uint8_t head_index = 0;


float omega1f = 0;
float omega2f = 0;
float omega3f = 0;
float omega4f = 0;


int32_t omega1;
int32_t omega2;
int32_t omega3;
int32_t omega4;

uint16_t uvx = 0;
int16_t vx = 0;
uint16_t uvy = 0;
int16_t vy = 0;
uint16_t uwz = 0;
int16_t wz = 0;


int16_t vxPrevious = 0;
int16_t vyPrevious = 0;
int16_t wzPrevious = 0;


uint8_t ok_flag1 = 0;
uint8_t ok_flag2 = 0;
uint8_t ok_flag3 = 0;
uint8_t ok_flag4 = 0;

int lift_status = 0;


int temp_recv_omega = 0;

const char *front_cmd = "CMD";
const char *back_cmd = "cmd";
unsigned char dtu_buff[50];
extern char qr_scan_fbk[10];
extern float ultra_sound_signal_fbk[12];
extern float speed_fbk[3];
extern float a_fbk[3];
extern float g_fbk[3];
extern float speed_cmd[3];
void init_can()
{
    CAN1_WriteData(0x00, &init[0], 2);
    delay_ms(2);

}


void init_motor(uint64_t num)
{
    delay_ms(40);
    begin1[1] = num;

    CAN1_WriteData(0x00, &begin1[0], 2);
    delay_ms(40);

    CAN1_WriteData(0x600 + num, &begin2[0], 8);
    delay_ms(40);

    CAN1_WriteData(0x600 + num, &begin3[0], 8);
    delay_ms(40);
}



int main(void)
{
    /*
    ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f4xx.c 文件，主要功能是
    配置CPU系统的时钟，内部Flash访问时序，配置FSMC用于外部SRAM等。
    */
    //	uint8_t i = 0;
    int ultra_signal = 0;
    int ultrasonic_switch = 0;
    USART_Configuration();
    NVIC_Configuration();
    CAN_Configuration();
    //I2C_GPIO_Config();
    IIC_Init();
    LED_Configuration();
    delay_init(168);
    delay_ms(2);
    delay_ms(3000);
    //init_can();
    //manyou
    int16_t remember_vx = 0;
    int16_t remember_vy = 0;
    int16_t random_value;

    scanner_init();
    char led_num = 0;

    //	init_can();
    init_motor(N1);
    init_motor(N2);
    init_motor(N3);
    init_motor(N4);
    //
    command1[6] = (uint8_t)(0x0000000f);
    command2[6] = (uint8_t)(0x0000000f);
    command3[6] = (uint8_t)(0x0000000f);
    command4[6] = (uint8_t)(0x0000000f);

    delay_ms(2);
    CAN1_WriteData(0x600 + N1, &command1[0], 8);
    delay_ms(2);
    CAN1_WriteData(0x600 + N2, &command2[0], 8);
    delay_ms(2);
    CAN1_WriteData(0x600 + N3, &command3[0], 8);
    delay_ms(2);
    CAN1_WriteData(0x600 + N4, &command4[0], 8);
    //

    delay_ms(2);
    CAN1_WriteData(0x600 + N1, &command_read_speed[0], 8);
    delay_ms(2);
    CAN1_WriteData(0x600 + N2, &command_read_speed[0], 8);
    delay_ms(2);
    CAN1_WriteData(0x600 + N3, &command_read_speed[0], 8);
    delay_ms(2);
    CAN1_WriteData(0x600 + N4, &command_read_speed[0], 8);
    delay_ms(2);
    TIM3_Int_Init(ODOM_PERIOD_MS * 10 - 1, 8400 - 1); //里程计更新周期50ms

    float msg_cnt = msg_cnt_max;

    float led_on_cnt = 20.0;
    led_on_cnt = 20;
    LED_OFF();
    while (1)
    {

        //	delay_ms(20);
        //	CAN1_WriteData(0x600+N2, &command_test[0], 8);

        msg_cnt -= 1;
        if(msg_cnt < 0)
        {
            vx = 0;
            vy = 0;
            wz = 0;
        }

        if(led_on_cnt > 0)
        {
            led_on_cnt -= 1;
        }
        else
        {
            LED_OFF();
        }


        //		delay_ms_ms(1000);
        //
        //LED_ON();
        //
        //		delay_ms_ms(1000);
        //
        //LED_OFF();

        delay_ms(50);
//						g_fbk[0]=RS232_rec_counter;
        if (RS232_REC_Flag == 1&&RS232_rec_counter>= COMMAND_DATA_LENGTH + 8)       //如果串口接收到一帧数据（以“?;”结尾）
        {
            RS232_REC_Flag = 0;
            //RS232_Send_Data(RS232_buff,RS232_rec_counter);
            //int i = 0;
            uint8_t i = 0;
            for (i = 0; i < RS232_rec_counter; i++)
            {
                received_data[i] = RS232_buff[i];
            }
//            for (i = 0; i < 12; i++)
//            {
//                ultra_sound_signal_fbk[i] = (float)(uint8_t)RS232_buff[i];
//            }
            received_len = RS232_rec_counter;
            if (received_len >= COMMAND_DATA_LENGTH + 8) //Serial data are valid
            {
                const char *head = strstr((char *)received_data, front_cmd);
                if(head != NULL)
                {
                    if(head[COMMAND_DATA_LENGTH + 3 + 0] == back_cmd[0] &&
                            head[COMMAND_DATA_LENGTH + 3 + 1] == back_cmd[1] &&
                            head[COMMAND_DATA_LENGTH + 3 + 2] == back_cmd[2])
                    {
                        struct_command_data *cmd_ptr = (struct_command_data *)(head + 3);
                        struct_command_data cmd_data = *cmd_ptr;
                        if(cmd_data.check_front_cmd == CHECK_FRONT_CMD &&
                                cmd_data.check_back_cmd == CHECK_BACK_CMD)
                        {
                            if(agv_started == 0) //first start
                            {
                                init_can();
                                init_motor(N1);
                                init_motor(N2);
                                init_motor(N3);
                                init_motor(N4);
                                agv_started = 1;
                            }
                            if(agv_started == 1) //started
                            {
                                vx = cmd_data.speed_cmd[0];
//                                vx = (int16_t)uvx;
                                vy = cmd_data.speed_cmd[1];
//                                vy  = (int16_t)uvy;
                                if(DOUBLEWHEEL)
                                {
                                    vy = 0;
                                }
                                wz = cmd_data.speed_cmd[2];
//                                wz = (int16_t)uwz;
//                                temp_recv_omega = uwz;
                            }
                            msg_cnt = msg_cnt_max;
//														a_fbk[0]=cmd_data.speed_cmd[0];
//														a_fbk[1]=cmd_data.speed_cmd[1];
//														a_fbk[2]=cmd_data.speed_cmd[2];
														
														a_fbk[0]=vx;
														a_fbk[1]=vy;
														a_fbk[2]=wz;
                        }
                    }
                }
            }
        }
        RS232_rec_counter = 0;

        
        //ultra_sonic!!!******************************
        if(0)
        {
            u8 	ultrasonic_Address2[8] = {0xE2, 0xD0, 0xD4, 0xD6, 0xE0, 0xDE, 0xDA, 0xD8};
            for(int i = 0; i < 8; i++)
            {
                KS103_WriteOneByte(ultrasonic_Address2[i], 0X02, 0X71);
                delay_ms(5);
            }
            u8  CurrentAddress = 0;
            u8  OldAddress = 0;
            uint16_t distance = 0;
            //u8 	ultrasonic_Address2[8]={0xE2,0xD0,0xD4,0xD6,0xE0,0xDE,0xDA,0xD8};
            //for(int i=0;i<8;i++)
            //{
            //	KS103_WriteOneByte(ultrasonic_Address2[i],0X02,0X71);
            //}
            //	u8 	ultrasonic_Address2[8]={0x04,0x60,0xC0,0xE0,0xE4,0x80,0x40,0x20};
            //		u8 	ultrasonic_Address2[8]={0xE2,0xD0,0xD4,0xD6,0xE0,0xDE,0xDA,0xD8};
            u8 ultrasonic_enable[8] = {0, 0, 0, 0, 0, 0, 0, 0};
            u8 ultrasonic_result[8] = {0, 0, 0, 0, 0, 0, 0, 0};
            uint16_t ultrasonic_value[8] = {-1, -1, -1, -1, -1, -1, -1, -1};
            if ((vx >= 0) && (vy >= 0))
            {
                //ultrasonic_enable[0] = 1;
                ultrasonic_enable[1] = 1;
                ultrasonic_enable[2] = 1;
                ultrasonic_enable[3] = 1;

            }
            if ((vx <= 0) && (vy >= 0))
            {

                ultrasonic_enable[1] = 1;
                ultrasonic_enable[2] = 1;
                ultrasonic_enable[3] = 1;
                //ultrasonic_enable[4] = 1;
            }
            if ((vx <= 0) && (vy <= 0))
            {
                //ultrasonic_enable[0] = 1;
                ultrasonic_enable[5] = 1;
                ultrasonic_enable[6] = 1;
                ultrasonic_enable[7] = 1;
            }
            if ((vx >= 0) && (vy <= 0))
            {
                //ultrasonic_enable[4] = 1;
                ultrasonic_enable[5] = 1;
                ultrasonic_enable[6] = 1;
                ultrasonic_enable[7] = 1;
            }

            for (int i = 0; i < 8; i++)
            {
                if (ultrasonic_enable[i] == 1)
                {
                    KS103_WriteOneByte(ultrasonic_Address2[i], 0X02, 0Xb0);
                    delay_ms(10);
                    distance = KS103_ReadOneByte(ultrasonic_Address2[i], 0x02);
                    distance <<= 8;
                    distance += KS103_ReadOneByte(ultrasonic_Address2[i], 0x03);
                    //							printf("ID: %x ,distance:%d \r\n",ultrasonic_Address2[i],distance);
                    delay_ms(5);
                    ultrasonic_value[i] = distance;
                    if (distance < 150)
                    {
                        ultra_signal = 1;
                        ultrasonic_result[i] = 1;
                    }
                }
                distance = 0;
            }
            //				printf("\r\n--------------------- \r\n");
            //						vx=remember_vx;
            //						vy=remember_vy;
            //						wz=0.0;

            //			if((ultrasonic_result[1]>0)&&(ultrasonic_result[2]>0)&&(ultrasonic_result[3]>0))
            //				{
            //					direction = 1;

            //				}


            if ((vx >= 0) && (vy >= 0))
            {
                if (ultrasonic_result[1] + ultrasonic_result[2] + ultrasonic_result[3] > 0)
                {
                    vx = 0.0;
                    vy = 0.0;
                    wz = 0.0;
                    //					vx = -vx;
                    //					vy = -vy;
                    //					wz=0.0;
                    //				remember_vx = 2*(rand()%(150-50+1)+50);
                    //				remember_vy = 2*(rand()%(150-50+1)+50);
                }
            }

            if ((vx <= 0) && (vy >= 0))
            {
                if (ultrasonic_result[1] + ultrasonic_result[2] + ultrasonic_result[3] > 0)
                {
                    vx = 0.0;
                    vy = 0.0;
                    wz = 0.0;
                    //					vx = -vx;
                    //					vy = -vy;
                    //					wz=0.0;
                    //				remember_vx = 2*(rand()%(150-50+1)+50);
                    //				remember_vy = 2*(rand()%(150-50+1)+50);
                }
            }

            if ((vx <= 0) && (vy <= 0))
            {
                if (ultrasonic_result[5] + ultrasonic_result[6] + ultrasonic_result[7] > 0)
                {
                    vx = 0.0;
                    vy = 0.0;
                    wz = 0.0;
                    //					vx = -vx;
                    //					vy = -vy;
                    //					wz=0.0;
                    //				remember_vx = 2*(rand()%(150-50+1)+50);
                    //				remember_vy = 2*(rand()%(150-50+1)+50);
                }
            }

            if ((vx >= 0) && (vy <= 0))
            {
                if (ultrasonic_result[7] + ultrasonic_result[6] + ultrasonic_result[5] > 0)
                {
                    vx = 0.0;
                    vy = 0.0;
                    wz = 0.0;
                    //					vx = -vx;
                    //					vy = -vy;
                    //					wz=0.0;
                    //				remember_vx = 2*(rand()%(150-50+1)+50);
                    //				remember_vy = 2*(rand()%(150-50+1)+50);
                }
            }
            //			if((ultrasonic_value[0]>200)&&(ultrasonic_value[0]<400))
            //				{

            //					vx = vx - 100;

            //				}
            //			if((ultrasonic_value[4]>200)&&(ultrasonic_value[4]<400))
            //				{

            //					vx = vx + 100;

            //				}
        }
        //		remember_vx = vx;
        //		remember_vy = vy;

        //********************************************
        if(vx > SPEED_MAX)vx = SPEED_MAX;
        if(vx < -SPEED_MAX)vx = -SPEED_MAX;
        if(vy > SPEED_MAX)vy = SPEED_MAX;
        if(vy < -SPEED_MAX)vy = -SPEED_MAX;
        if(wz > OMEGA_MAX)wz = OMEGA_MAX;
        if(wz < -OMEGA_MAX)wz = -OMEGA_MAX;

        if(abs(vx - vxPrevious) > DELTA_SPEED_MAX) //缓慢加速，加速度与下发频率相关
        {
            vx = vxPrevious + DELTA_SPEED_MAX * abs(vx - vxPrevious) / (float)(vx - vxPrevious);
        }
        if(abs(vy - vyPrevious) > DELTA_SPEED_MAX)
        {
            vy = vyPrevious + DELTA_SPEED_MAX * abs(vy - vyPrevious) / (float)(vy - vyPrevious);
        }
        if(abs(wz - wzPrevious) > DELTA_OMEGA_MAX)
        {
            wz = wzPrevious + DELTA_OMEGA_MAX * abs(wz - wzPrevious) / (float)(wz - wzPrevious);
        }


        if(DOUBLEWHEEL)
        {
            vy = 0;
        }

        vxPrevious = vx;
        vyPrevious = vy;
        wzPrevious = wz;


        omega1f = AGV_OUT_SPEED_K * (1 * vx + 1 * vy - AGV_SHAPE_K * wz);
        omega2f = AGV_OUT_SPEED_K * (vx - 1 * vy - AGV_SHAPE_K * wz);
        omega3f = AGV_OUT_SPEED_K * (1 * vx + 1 * vy + AGV_SHAPE_K * wz);
        omega4f = AGV_OUT_SPEED_K * (vx - 1 * vy + AGV_SHAPE_K * wz);

        omega1 = (int32_t)(L_DIRECTION * 1 * omega1f);
        omega2 = (int32_t)(L_DIRECTION * 1 * omega2f);
        omega3 = (int32_t)(R_DIRECTION * 1 * omega3f);
        omega4 = (int32_t)(R_DIRECTION * 1 * omega4f); //take the installnation direction of motors into account.

        sprintf(dtu_buff, "ODOMDTU w1 %d, w2 %d ,w3 %d, w4 %d,DTUODOM\r\n\0",
                (int)omega1,
                (int)omega2,
                (int)omega3,
                (int)omega4);


        //RS232_Send_Data(dtu_buff,strlen(dtu_buff));

        //uint8_t command[6] = {0x0f, 0x00, 0x00, 0x00, 0x00, 0x00};
        command1[4] = (uint8_t)(omega1 & 0x000000ff);
        command1[5] = (uint8_t)((omega1 >> 8) & 0x000000ff);
        command1[6] = (uint8_t)((omega1 >> 16) & 0x000000ff);
        command1[7] = (uint8_t)((omega1 >> 24) & 0x000000ff);


        command2[4] = (uint8_t)(omega2 & 0x000000ff);
        command2[5] = (uint8_t)((omega2 >> 8) & 0x000000ff);
        command2[6] = (uint8_t)((omega2 >> 16) & 0x000000ff);
        command2[7] = (uint8_t)((omega2 >> 24) & 0x000000ff);

        command3[4] = (uint8_t)(omega3 & 0x000000ff);
        command3[5] = (uint8_t)((omega3 >> 8) & 0x000000ff);
        command3[6] = (uint8_t)((omega3 >> 16) & 0x000000ff);
        command3[7] = (uint8_t)((omega3 >> 24) & 0x000000ff);

        command4[4] = (uint8_t)(omega4 & 0x000000ff);
        command4[5] = (uint8_t)((omega4 >> 8) & 0x000000ff);
        command4[6] = (uint8_t)((omega4 >> 16) & 0x000000ff);
        command4[7] = (uint8_t)((omega4 >> 24) & 0x000000ff);

        omega1f = AGV_OUT_SPEED_K * (-1 * vx + 1 * vy + AGV_SHAPE_K * wz);
        omega2f = AGV_OUT_SPEED_K * (vx + 1 * vy + AGV_SHAPE_K * wz);
        omega3f = AGV_OUT_SPEED_K * (-1 * vx + 1 * vy - AGV_SHAPE_K * wz);
        omega4f = AGV_OUT_SPEED_K * (vx + 1 * vy - AGV_SHAPE_K * wz);

        omega1 = (int32_t)(L_DIRECTION * 1 * omega1f);
        omega2 = (int32_t)(L_DIRECTION * 1 * omega2f);
        omega3 = (int32_t)(R_DIRECTION * 1 * omega3f);
        omega4 = (int32_t)(R_DIRECTION * 1 * omega4f);  //take the installnation direction of motors into account.

//        delay_ms(2);
//        CAN1_WriteData(0x600 + N1, &command1[0], 8);
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N2, &command2[0], 8);
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N3, &command3[0], 8);
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N4, &command4[0], 8);


//        delay_ms(2);
//        CAN1_WriteData(0x600 + N1, &command_read_position[0], 8);
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N2, &command_read_position[0], 8);
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N3, &command_read_position[0], 8);
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N4, &command_read_position[0], 8);


//        //read speed command_read_speed
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N1, &command_read_speed[0], 8);
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N2, &command_read_speed[0], 8);
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N3, &command_read_speed[0], 8);
//        delay_ms(2);
//        CAN1_WriteData(0x600 + N4, &command_read_speed[0], 8);
//        delay_ms(2);


        //	LED_ON();
        //	delay_ms(999);
        //	LED_OFF();
        //	delay_ms(999);

        //	delay_ms(26);
        sprintf(dtu_buff, "SPEEDDTU%d,%d,%d,%dDTUSPEED\r\n\0",
                (int)(speed_read_value[0] / K_omega * 1000.0),
                (int)(speed_read_value[1] / K_omega * 1000.0),
                (int)(speed_read_value[2] / K_omega * 1000.0),
                (int)(speed_read_value[3] / K_omega * 1000.0));
        //	sprintf(dtu_buff, "SPEEDDTU%d,%d,%d,%dDTUSPEED\r\n\0",
        //	(int)(speed_read_value[0]/OUT_OMEGA_K*1000.0),
        //	(int)(speed_read_value[1]/OUT_OMEGA_K*1000.0),
        //	(int)(speed_read_value[2]/OUT_OMEGA_K*1000.0),
        //	(int)(speed_read_value[3]/OUT_OMEGA_K*1000.0));
        //		sprintf(dtu_buff, "SPEEDDTU%d,%d,%d,%dDTUSPEED\r\n\0",
        //	(int)(speed_read_value[0]),
        //	(int)(speed_read_value[1]),
        //	(int)(speed_read_value[2]),
        //	(int)(speed_read_value[3]));

        //	delay_ms(20);
        //RS232_Send_Data(dtu_buff,strlen(dtu_buff));

        //RS232_Send_Data(dtu_buff,strlen(dtu_buff));
        //50ms in total

    }
}