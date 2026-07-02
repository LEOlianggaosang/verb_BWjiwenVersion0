/**
 *******************************************************************************
 * Copyright (c) 2025.4.26
 * 
 * @file    product_config.h
 * @author  lianggaosang@qq.com
 * @brief   
 *
 *******************************************************************************
 */

#ifndef _PRODUCT_CONFIG_H_
#define _PRODUCT_CONFIG_H_

#include "user_define.h"

// System configuration
#define VERSION_NUMBER	2//b02
#define INIT_MENU       MENU_STANDARD   /* Initial menu */
#define INIT_STATE      STATE_RESET   /* Initial system state */
// #define	C_LITER         1029//0.1L
#define	C_LITER         917//1n=0.109ml, 100ml=917n
#define	C_ERR_LITER     (C_LITER*10)		//1L
#define NEWTPE1         1
#define NEWFORM0        1//20251110 NEWFORM0
//MOD**************************************************************************
#define CONFIG_FM_TIMERCHECK                1
#define CONFIG_WASH_IN_TURN                 0
#define CONFIG_AUTO_DOOR                    0
#define CONFIG_AUTO_WASH                    0
#define CONFIG_BLAM_ENABLE                  0
#define CONFIG_DELAY_ENABLE                 0  
#define CONFIG_SOFT_ENABLE                  0
#define CONFIG_FORCE_DRAIN                  1
#define CONFIG_STEAM_ENABLE                 1
#define CONFIG_DRY_ENABLE                   1//保管合并  
#define CONFIG_HALF_ENABLE                  0
#define CONFIG_LOCK_ENABLE                  0
#define CONFIG_IV_ENABLE                    0//进水阀模式
#define CONFIG_IP_ENABLE                    1//水箱模式
#define CONFIG_MP_ENABLE                    0
#define CONFIG_FAN2_ENABLE                  0
#define CONFIG_FM2_ENABLE                   0
#define CONFIG_O3_ENABLE                    1//20260421 版本0 臭氧功能
//FUNCTION*********************************************************************
#define CONFIG_OTA                          0
#define CONFIG_BRZZER                       1
#define CONFIG_WIFI                         0
#define CONFIG_PUMP_ADCHECK                 0//过流保护
#define CONFIG_MENORYENABLE                 1//掉电记忆
#define CONFIG_IAPADDR_DEVICE               1//循环使用EEPROM空间模块
#define CONFIG_MENORY_WASHDATA              0//20251105 更新
#define CONFIG_FLOW_CHECK                   0
#define CONFIG_INLET_MODE                   0//进水模式切换
#define CONFIG_NIGHT_LIGHT                  1//串口控制多色夜灯
#define CONFIG_FCT_UART                     1//烧录口串口通信进入
#define CONFIG_FB_CHECK                     1//20251204
//APP_DEAL*********************************************************************
#define CONFIG_DISPLAY_FLESH                1
#define CONFIG_KEYACTION_DIVICE             1
#define CONFIG_TESTENTER_CHECK              1
#define CONFIG_WATERLEVEL_CHECK             0//补水与低水位开关关联
#define CONFIG_END_ERROR                    0//洗涤结束报警    
#define CONFIG_TEST_ERROR                   1//正常屏蔽，厂测报警
#define CONFIG_STEAM_FAN                   	0//20251211 蒸汽风机与PTC是否动作
#define CONFIG_T2_STANDARD                  0//20251211 T2调试标准洗//20260421 版本0
#define CONFIG_T2_STEAMDRY                  0//20251211 T2调试干燥效果//20260421 版本0
//DEBUG***********************************************************************
#define CONFIG_DISPLAY_DEBUG                0
#define CONFIG_TK_NG_DEBUG                  0
#define CONFIG_TK_DEBUG                     0
#define CONFIG_DEBUG_PRINT                  0
#define EMC_TEST_NO_INLET                   0
#define CONFIG_UART_MORE                    0 
#define CONFIG_EXTRA_INFORMATION            1//20251105 更新
#define CONFIG_DISPLAY_INLET                1//20251110 NEWFORM0
#define CONFIG_STATE_FLESH                  1//20251110 NEWFORM0
#define CONFIG_LIFE_TEST                    0//20251204
#define CONFIG_IQC_TEST                    	0//20260117
#define CONFIG_POWER_TEST                   1//20260509
//*****************************************************************************
#endif
//更改记录
// 2025.4.26 奶瓶机初版程序
// 2025.5.10 时序表clearStepDataEnable/Mask/Switch
// 2025.5.13 电源键长按0.5秒生效
// 2025.5.20 通信协议与掉电记忆
/*MenuList,fnIndex,FunctionOption,HalfMode,functionTable,functionTableMask,Work_CurrentHalfMode*/
// 2025.5.21 MENU_NULL
/*
1. 关机重开默认无程序，只记忆进水模式
2. 待机重复按键取消，判断是否变成无程序
3. 运行时附加功能键的增加取消总时间变化处理
*/
// 2025.5.28 显示 COM口需要设置为强推挽输出
/*
2025.6.16
1.开机不响蜂鸣器，延时响应蜂鸣，上电蜂鸣两次 BeepState
2.LED菜单状态 Work_CurrentMenu
*/
/*
//2025.9.18 显示 NEWTPE1
1. 触摸通道变动S_TouchKeyCFG，按键键值变动TKDrv，按键定义变动，TestKeyAction_Flags/FctKeyAction_Flags
    key1 TK21/key2 TK20/key3 TK19/key4 TK18/key5 TK17/key6 16/key7 TK15
    key2 TK23/key1 TK22/key4 TK21/key6 TK20/key3 TK18/key8 TK17/key7 TK16/key5 TK15
2. 显示对应IO变动LedRamDrv，显存位置变动Light，图标定义变动，Led_Testting/Led_ProgramDisplay/Leds_Test
    COM5=C7//ng
    PIN4=COM4=C6
    PIN3=COM3=C5
    PIN2=COM2=C4
    PIN1=COM1=C3
    LED6=PIN10=SEG3=S6
    LED4=PIN8=SEG4=S4
    LED8=PIN9=SEG5=S3
    LED7=PIN5=SEG1=S9
    LED2=PIN11=SEG7=S1
    LED5=SEG8=S10
    LED3=PIN6=SEG2=S8//ng
    LED1=PIN7=SEG6=S2//ng
3. NightLight_Control/NightLight_ColorType/NightLight_ActionType
    #if(CONFIG_NIGHT_LIGHT&&(0==CONFIG_IO_UARTSIMULATE)) 做在电源板
4. 电源键是否长按，出厂保管打开，开机强排保留，出厂默认程序标准洗烘干打开
5. 取消功能的菜单显示与时间计算，附加功能的能否选择与能否计算
6. 增加自清洁程序与按键与对应显示
7. 洗涤结束关机，程序运行过程中，每运行完一个阶段，则相应的按键指示灯熄灭
//2025.9.20 时序 NEWTPE1
8. 蒸汽功能需要同时打开PTC，单独蒸汽功能不打开PTC//HEAT_TIMER//HEAT_STEAM//FAN_PTC_TIMER
9. 预洗增加温度补偿采样，预洗增加判断步骤、实现时间补偿//Pre_Temp_Check//Dry_Temp_Work
10.改写时序表温度与消毒对应步骤，增加自清洁时序表
11.只要开PTC,最后30s只开风机checkPTC30s(arg)，保管时序更改
*/
/*
//20250921
1、电源板显示板联调通信 OK
2、数码管显示 SEGC/SEF LED显示 COM5 OK
3、蜂鸣器反馈 OK
4、半亮设置
5、变量F_Light10ms/Output_UV OK
//20250922
6、EMC_TEST_NO_INLET
7、输入测试 OK
8、时序启动测试，配对路径原则，步骤启动函数Work_NextStep()，洗涤时序指针Work_NextStepHandler OK
9、故障 switch(Work_CurrentState) case STATE_ERROR: OK
ps：厂测（指针、上电、记忆）、掉电记忆、洗涤时序入口（启动，掉电记忆，故障恢复）
//20250923
10、故障状态恢复 OK
11、开机吞蜂鸣音
//20250925
12、进水脉冲917
    800进1100，-208.4g
    100进134
    200进268
    进水流量没有重置 ok
    第一声吃掉
    进水量是1.34倍 ok
    917/4*3=687
13、门开关失效
//20250926
14、烘干总时间温度补偿，总时间倒计时处理 OK
15、时序表功能叠加与倒计时，运行过程中开关
16、三种加热时序、蒸汽与烘干功能特殊时序
17、保管状态的按键与显示，保管暂停功能与开门处理
18、电源板夜灯功能 OK
19、洗涤完成增加排空水箱功能
20、增加加热延时功能 OK
*/
/*
//20250927
11.开机吞蜂鸣音 BUZZ_SILENCE OK
15.时序表功能叠加与倒计时，运行过程中开关 OK
//20250929
1、附加功能时序、计时、叠加//温度检测减时间的顺序
2、保管、结束状态显示//STATE_SAVING//STATE_FINISHED
3、蒸汽不结束//STAGE_COMPLETE//DRAIN_STEAM--等待小于60度
//20250930
4、排水状态处理（掉电记忆，洗涤恢复、厂测、特殊功能宏定义化）
4.2、增加退出排空按键
4.3、增加排空水箱时序与电磁阀进水处理
//DrainCnt//F_IsInLetting//FlowMCntSet//FlowMCnt//FlowMCntBuf//LackTimer
*/
/*
//20251007
1、进水报警处理，不排水重新进，继续进。进水取消报E1 ok
2、缺水流量记忆、进水流量判断、缺水报警机制 ok
//checkLackError//checkStepRotationIsReach
//P_FlowMCnt//FlowMCntSet//FlowMCntBuf//FlowMCnt
3、蒸汽阶段水量不足判断，改为执行短程时序//Work_SteamLack
4、关机排水，分离排水时序步骤为干燥前开启，单干燥不增加//DRAIN_ALL
5、60度水温等待，改成烘干步骤4+1+40，排水放在静置后面//FAN_PTC_TIMER
路线：
洗涤+蒸汽+烘干：蒸汽开风机PTC，静置开风机PTC，排空开风机PTC，烘干开风机PTC
洗涤+蒸汽：蒸汽不开风机PTC，没有静置，排空不开风机PTC，没有烘干
洗涤+烘干：没有蒸汽，静置开风机PTC，排空开风机PTC，烘干开风机PTC
洗涤：没有蒸汽，没有静置，排空不开风机PTC，没有烘干
蒸汽+烘干：蒸汽开风机PTC，静置开风机PTC，排空开风机PTC，烘干开风机PTC
蒸汽：蒸汽不开风机PTC，没有静置，排空不开风机PTC，没有烘干
烘干：没有蒸汽，没有静置，没有排空，烘干开风机PTC
条件：
有蒸汽时，有烘干蒸汽才开风机PTC
有烘干时，才有静置必然开风机PTC
都有排空，有烘干排空才开风机PTC
PS：PTC提前30s关闭，温度补偿烘干处理
//20251008
1、关机不排水if(Work_TimerTick1s){DrainCnt++;}
2、缺水恢复不进水
step_info = steps[(UCHAR)Work_CurrentMenu][Work_CurrentStep];
Work_CurrentFnIndex = step_info.fnIndex;
Work_CurrentArg = step_info.arg;
currentStepMaxDuationSecond = step_info.maxDuration;
//20251010 
//1、更新保管显示
//2、修复自洁查表跑飞，修复烘干补时卡死
*/

/*
//20251011 厂测模式
//20251014 烘干时间从45改为35
1、显示版本、按键测试、正式步骤
2、按键、显示、查表、跳步、按键跳步，共用系统，时序，按键跳步，完成与清清理数据，恢复出厂设置
*/

/*
//20251020 问题点
1、开门后风扇不转，信号反馈线定义为上拉输入 OK
2、面板灵敏度 OK
3、模拟串口波形，只完成发送功能 OK
4、蒸汽阶段取消排水 OK
*/

/*
//20251025 增加功能
1、蒸汽是否开PTC风机判断，是否静置判断，是否排空判断，静置与排空是否开PTC风机判断 OK
2、FCT模式，电源板显示板初始化串口启用(初始化，命名，主循环收发处理) OK
ps：因为显示驱动的初始化更改寄存器导致USCI1失效
3、上电1分钟限制增长，增加进水故障最长时间判断，延长上电全亮时间为2s，静置4分钟算入烘干 OK
*/
//20251031 显示驱动初始化影响USCI1功能
/*
//20251029 增加功能
1、增加寿命测试程序版本 OK
2、显示测试特殊模式 OK
3、风扇规格书，加入风扇信号开关反馈(方波信号，外部中断)
4、电源板IO口模拟串口波特率200，完善接收功能 NG
5、洗涤、厂测、故障数据掉电记忆 NG
6、模式切换使能模块 NG
7、同步寿命程序 ing---显示板
8、显示板特殊模式待更新 ing---显示板
9、加TDS的显示规则与检测规则 nox
10、电源板负载延时启动 NG
*/
//---------------------------------------------------------------------------------
/*
//20251118 正美竞品样机差异性参考
1、开机00，但是选择洗涤自动点亮附加功能
2、未关门无法启动//---暂停---继续
3、待机、保管关机没有强排
4、运行对应图标闪烁
5、暂停与开门闪烁数码管与启停键
6、强退半秒有强排
7、保管没有暂停，开门没有反应
8、蒸汽缺水显示10/29，红色缺水灯与启停键闪烁
*/

/*
//20251110 NEWFORM0
（OK）1、按键调试功能增加关机、待机、故障状态的信息显示
    （OK）1.1烘干菜单点亮自清洁不灭，不用判断按键类型
（OK）2、屏蔽掉电记忆
    2.1排查选区，恢复复现
    2.2读写校验改成i=0，EEP数据校验不影响，对比净水器//CONFIG_MENORYENABLE
    2.3暂时屏蔽选区模块，完善模式记忆，能否正常记忆//CONFIG_IAPADDR_DEVICE
    2.4归纳记忆数据//CONFIG_MENORY_WASHDATA
（OK）3、配置初始化，待机按键选择功能
    3.1待机按键//不允许MENU_STEAM与MENU_DRY//取消选择
    3.2启动处理不记忆//写记忆卡顿(//20251126 关机不写记忆)
    3.3恢复数据预留未用，进入待机无需读取//Work_MemoryRead
    3.4仅在恢复出厂设置、洗涤结束//Work_MemoryWrite(//20251126 关机不写记忆)            //规格书定义确认
（OK）4、启动洗涤时开门暂停处理去除//Work_IsPaused//Power_DoorIsOpend//Work_DoorOpenDelaySecondCount
（OK）5、烘干开门处理//Work_IsPaused//Power_DoorIsOpend//Work_DoorOpenDelaySecondCount
（OK）6、开门故障缺水故障不能关机//Error.c//Key.c
（OK）7、强排状态报开门故障//Error.c
8、新资料更改//#if NEWFORM0
（OK）8.1数码管倒计时三位数，小时两点
（OK）8.2强排---，待机、保管关机没有强排
（OK）8.3保管不能退到待机，不能暂停
（OK）8.4步骤最大延时改为2分钟
（OK）8.5缺水显示
（OK）8.6保管参数
（OK）8.7加热延时取消,时间到达跳步
（OK）8.8蒸汽不执行短时序
（OK）8.9取消夜灯呼吸(//20251126 夜灯呼吸闪烁)
（OK）8.9自洁可选烘干按键与待机显示(//20251126 洗涤时显示与熄灭)
9、图标
（OK）9.1不亮进水图标宏定义//#if CONFIG_DISPLAY_INLET ok
（OK）9.2蒸汽与排空进水使能图标
（OK）9.3运行对应图标闪烁//#if CONFIG_STATE_FLESH
（OK）9.4洗涤时开加热管图标常亮，蒸汽烘干开PTC图标常亮，保管开PTC图标闪烁，厂测常亮负载图标
    #if (CONFIG_STATE_FLESH&&CONFIG_EXTRA_INFORMATION&&NEWTPE1)
    (// 20251110 NEWFORM0 20251127 9.4)
10、变更点
（OK）10.1排空步骤不判断温度，改为先排水的时间设定 ok
        (1)不调用二漂进水步骤
        (2)不调用Work_SpecialSecondInCurrentStage
        (3)有无参数调用两次(//20251126 改为标志位30s后缀// Work_DrainAllFail 对标Work_SteamLack清零)
（OK）10.2开门筒灯熄灭最大延时10分钟计时
（OK）10.3蒸汽与烘干开头增加排水环节
    10.4无论有无选烘干都过一遍室温判断，以方便增减烘干功能 ok
（OK）10.5卡时002修正，若0显1
        //Work_StageStartTimeMode
        //Work_NextStep()//clearStepDataEnable
（OK）10.6延时机制统一
        //wash_heat_temp2()//定温加热延时600s
            //原//Work_EndConditionIsTemperature
            //原//runMinCountDown()//if (Work_LeftMinToEnd > lowerRangeTimeInCurrentStage)
            //原//Work_ExtraHeatSecondCount
            //改//转移Work_Control()处理，延时最大300s预留，不调用定温加热温达跳步
        //wash_heat_temp1()//未完成加热延时300s
            //原//Work_HeatOk
            //原//currentStepMaxDuationSecond
            //原//checkStepTimerIsReach()
            //改//更改跳步条件，定温加热温达剩洗不进行延时
        //Work_Control()case STATE_WASHING://步骤与组合步骤配时最大时间延时300s
            //原//Work_TimeHaltEnable//超过配时不倒计时标志位
            //原//runMinCountDown()//if (Work_LeftMinToEnd > lowerRangeTimeInCurrentStage)
            //原//currentFunctionUnitUsedSeconds//组合清零
            //原//Work_UsedSecondInCurrentStep//跳步清零
            //原//currentStepMaxDuationSecond//组合步骤
            //改//延时120
            //改//进水不算延时不强行跳步
（OK）10.7缺水故障代码改为E7 ok
（OK）10.8排空气泡E2屏蔽报警//#if CONFIG_TEST_ERROR//确定只在厂测报
11、时序表
（OK）11.1额外附加定时处理：排空补偿30s,单风机30s                                 //确认时序表差异 
    11.2排空与静置的处理：不分阶段不改位置                                        //确认时序表差异 
（OK）11.3烘干时间改为40min//Work_StageStartTimeMode[]+时序表更改
（OK）11.4蒸汽与单烘干启动开头排水
（OK）11.5取消温度保护静置与排空
（OK）11.6自清洁可选烘干//MenuList[]+时序表更改                                    //确认自清洁是否自带保管
    11.7所有热洗加入冷洗20s不算入热洗时间
（OK）11.8热洗不允许延时，调整热洗温度与分配时间
（OK）11.9进水允许从故障恢复无限延时
    11.10 CAD设定：快速洗自清洁不设温度补偿(有)，二漂进水600ml与蒸汽跳过(无)         //确认旧时序表差异 
（OK）11.11 进水排水配时不为0仅卡阶段时间，使用阶段排水格式，不使用阶段排空格式         //确认时序表差异 
（OK）11.12 查表mod配置在蒸汽与烘干菜单中的处理
12、保管
（OK）12.1倒计时时间72H保管，
（OK）12.2同时保管一个167一个168（数据遗留）
    12.3加强烘干改为不算保管时间，先10冷风后20热风
（OK）12.4加强烘干显示满时间
    12.5保管不能暂停，不用局部静态变量定义ret
//--------------
13、试产
    (1)蒸汽时是否选烘干可以实时控制PTC继电器的开关
（OK）(2)13.2总时间显示失常
            (//20251126 少于配时扣足配时，大于配时不再走时，非进水最大延时跳步，阶段走时上下限)
            (//20251126 结尾时间显示异常Work_NextStep=>Work_LeftMinToEnd负数)
（OK）(3)13.3保管计时显示异常(//20251126 39-1-0-40-224)
    (4)验证厂测模式与时序，
    （OK）@50min蒸烘：排水34+进水15//确认加强烘干10+20，烘干最后30s冷ok
    （OK）@50min自洁烘：多5m30s(//20251126 WASH_TIMER=>WASH_HEAT_TEMP1)//20冷ok，5+2+3ok
    （OK）@10min单蒸：排水32s+进水14s+单风机30s+排空(最大150+选择性补偿30)不算时间//(20251127 1-0-1-66-end)
    （OK）@40单烘：40分钟走时跳过(20251127 更改runMinCountDown位置)
    （OK）@厂测：32+43+12m(增不延)+6m(冷)+150(max)+30(max)
        @单自洁:/34+43+20+5m/+34+35+20+2m/+34+35+20+3m/4m(热风)+150(max)+30(max)+35m+30(冷)
        @保管：30分钟不算，10+20，110+10，570s+30s，72h结束
（OK）(5)厂测：进入厂测按键测试不能按灭开灯键、显示进水与正常流量、缺水故障//(20251127 更改)
    (6)夜灯呼吸闪烁，夜灯通信或呼吸算法
    (7)排空流量尿不尽
（OK）(8)加热效率与配时//(20251127 厂测热洗72从9延时到12)                          //确认时序表差异 
（OK）(9) #if NEWFORM0 反相检查 #if (0==NEWFORM0) //(20251127 更改)
（OK）(10)排空步骤：延长延时至90，没有执行附加30s(缺水判断120改为排空步骤不生效)，厂测不开风机//(20251127 更改最大延时60->90)
    (11)倒计时40，取消1,增加41
    14、试产：
（OK）(1)上电60s通信
（OK）(2)端子E5E1故障代码
（OK）(3)更新试产样机
    (4)整理测试样机（风机，风机上拉电阻，蜂鸣器，流量计，流量计上拉电阻）
（OK）15、流量计//(671/917)*1000=730//(671 = (((917/4)*3)-16))
    (1)上拉电阻//新旧板影响不大
    (2)内部上拉//无流量时0==>5v，有流量时影响不大
    (3)滤波//示波器波形5-0-短暂上升脉冲
    (4)零部件偏差//影响不符1.25
    (5)安装位置//朝向影响不大，每次装配现象不同（2号：1l--1.25/1.16，T0机800--870）
    (6)定时中断or脉冲//半波与缺波
16、电源板//20251203
（OK）(1)检开门立即停止负载
（OK）(2)流量外部中断，显示板改设定流量
（OK）(3)反馈外部中断，显示实时反馈数值//220
    (4)风机反馈逻辑，风机电路处理、故障判断机制？//#if CONFIG_FB_CHECK//20251204
17、重新派生寿命测试程序 
（OK）(1)开门暂停，暂停开门呼吸
（OK）(2)加热管故障屏蔽
（OK）(3)结束和退出洗涤需要清除Work_TempCompensation
    //#if CONFIG_LIFE_TEST//20251204 使能特殊条件切换
    //#if (0 == CONFIG_LIFE_TEST)//20251204 屏蔽功能按键与故障
（OK）(4)电源板重连可以自动恢复，显示板非关机状态E5无法自动恢复，未重连无法操作，重连只能强行关机//与RT故障处理错位
18、选区//20251206
    (1)打开选区显示数据//IapSectorCnt
    (2)使能关机写一次数据//CONFIG_IAPADDR_DEVICE
    //未全擦开机11计数正常//重写0-1-2正常//启动后关机超过11-4-死机
    (3)Iap_Address_Device_Write() 
    //校验data_buffer_restore[i] = IAPRead(IAP_FLASH_START_ADDR+i,IAP_AREA_VALUE);
    //IAP_FLASH_START_ADDR==>addrbuf
    (4)上电检索有数据的扇区，写数据时校验失败才增加选区，识别无数据
//--------------
#define CONFIG_IAPADDR_DEVICE               1
#define CONFIG_TEST_ERROR                   1
#define CONFIG_END_ERROR                    0
#define CONFIG_EXTRA_INFORMATION            1
#define CONFIG_DISPLAY_INLET                1
#define CONFIG_STATE_FLESH                  1
#define CONFIG_LIFE_TEST                    0//20251204
#define CONFIG_FB_CHECK                     1//20251204
//--------------
94、差异：分立时序表、滤芯规格书
    (1)长按自清洁进入自清洁专属处理步骤
    (2)特殊模式？(排空，显示测试，恢复出厂)
96、9、9.4图标闪烁影响亮暗
    (1)确认是否与正美保持一致                                                   //确认正美差异
*/

//20251211 蒸汽风机与PTC是否动作//#if CONFIG_STEAM_FAN//heat_timer()/heat_steam()
//20251211 更改标准洗时序//#if CONFIG_T2_STANDARD//主洗-1漂洗-1热漂+5总时+3热漂加热到82度
//20251216 更改蒸汽与烘干时长//#if CONFIG_T2_STEAMDRY//
/*
//20260117 来料检工装//#elif CONFIG_IQC_TEST//20260117
1、程序结束回到第0步并暂停
2、更改菜单时间
3、标准洗按键无法进入
//#if ((0 == CONFIG_LIFE_TEST)&&(0 == CONFIG_IQC_TEST))//20251204//20260117
//#if (0 == CONFIG_IQC_TEST)//20260117
//#if (CONFIG_LIFE_TEST||CONFIG_IQC_TEST)//20251204//20260117
4、风机使能报警
5、夜灯使能特殊处理
6、更改运行显示，显示步骤时间//Work_UsedSecondInCurrentStep
*/

/*
//20260421 版本0
1、显示参数： //Display_Screen_888(P_FeedBackCnt//P_FlowMCnt)，DigitalShowTemperature()
2、抽象：//DigitalShowTemperature()//DigitalShowTheSame(UCHAR same)
3、臭氧驱动： //CONFIG_O3_ENABLE//不共用IV
4、检查时序： //CONFIG_STEAM_FAN//CONFIG_T2_STANDARD//CONFIG_T2_STEAMDRY//CONFIG_MP_ENABLE//currentStepMaxDuationSecond
*/

//20260506 版本1直接派生暂时够用
//应用层的抽象需求
//1、特殊数据显示按键调试功能抽象，显示绑定，拓展按键//CONFIG_EXTRA_INFORMATION
//2、状态维度//switch(Work_CurrentState)
//3、状态共用体，使能真值表，按键使能，状态转换使能
//业务层
//1、串口环形队列
//2、按键订阅
//消化与应用：函数回调，注册，查表，状态机
//重构：系统可操作性，构架可拓展性
//1、按键、显示、工作模块重构
//2、测试模式分离接口抽象到main，订阅，状态机

//20260509 按键驱动负载工装//#if CONFIG_POWER_TEST//20260509
//仅提供进水、排水、洗涤负载驱动的按键与显示，保留电源板通信（其中开门停止洗涤泵为底层逻辑）
//20260701 按键驱动负载工装增加功能
//1、样机增加负载，按键增加加热与风机键
//2、控制逻辑增加功能键切换
//2.1、一直进水-进水800ml(亮白水滴)
//2.2、一直排水-排水箱(亮红水滴)
//2.3、一直洗涤-加热洗涤到设定温度一次(亮洗涤)
//2.4、一直加热-进水250ml(亮蒸汽)
//2.5、一直风机-PTC与臭氧检测转速(亮烘干)
//3、增加流量检测，温度检测，风机检测，所有动作不会自动停止
//4、进水时显示流量，加热时显示温度，风机时显示转速
//5、按键优化：连续响应两次键值
//20260702 按键驱动负载工装更改实现
//1、按键优化会话更改方案
//1.1、工程文件编码全部改成UTF-8
//1.2、执行建议：键值变更清空计数，注释更新时间阈值，计数具体值抽象为宏
//1.3、降低灵敏度
//2、处理逻辑：未按功能键简单驱动，加了功能键条件驱动
