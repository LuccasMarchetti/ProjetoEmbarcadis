#include "PID_MOTOR.h"

#include "FreeRTOS.h"
#include "task.h"
#include "board.h"
#include "debug_console_imx.h"
#include "pwm_imx.h"

#include <stdio.h>
#include "gpio_pins.h"
#include "gpio_imx.h"
#include "gpt.h"

float kp = 20, ki = 15, kd = 0;
float error, ierror, derror, preverror;
float SetPoint, RPM, dutyCycle;
float time, prevtime, deltatime;

float maxperiod = 65532, minperiod = 2, period = 1000000/60 - 2;
float minduty = 0, maxduty = 100;

int controlfreq;

pwm_config_t pwmConfig;


/* Interrupções */
void BOARD_GPIO_ENCODER_HANDLER(void)
{
    /* clear the interrupt status */
    GPIO_ClearStatusFlag(BOARD_GPIO_ENCODER_CONFIG->base, BOARD_GPIO_ENCODER_CONFIG->pin);
    prevtime = time;
    time = (1/1000)*GPT_ReadCounter(BOARD_GPTA_BASEADDR)/24000000;
    deltatime = time - prevtime;
}

void PWM2_Handler(void)
{
    /* Gets interrupt kPWM_FIFOEmptyFlag */
    if(PWM_GetStatusFlags(PWM2) & kPWM_FIFOEmptyFlag)
    {
        /* Clear kPWM_FIFOEmptyFlag */
        PWM_clearStatusFlags(PWM2, kPWM_FIFOEmptyFlag);
    }
}



/*
 Inicialiazar encoder
 */
void InitEncoderPin()
{
        /* GPIO module initialize, configure button as interrupt mode. */
    gpio_init_config_t encoderInitConfig = {
        .pin = BOARD_GPIO_ENCODER_CONFIG->pin,
        .direction = gpioDigitalInput,
        .interruptMode = gpioIntFallingEdge,
    };
    
    GPIO_Init(BOARD_GPIO_ENCODER_CONFIG->base, &encoderInitConfig);
    
    /* Enable interrupt. */
    NVIC_EnableIRQ(BOARD_GPIO_ENCODER_IRQ_NUM);
        
        
        /* Clear the interrupt state, this operation is necessary, because the GPIO module maybe confuse
        the first rising edge as interrupt*/
    GPIO_ClearStatusFlag(BOARD_GPIO_ENCODER_CONFIG->base, BOARD_GPIO_ENCODER_CONFIG->pin);
        /* Enable GPIO pin interrupt */
    GPIO_SetPinIntMode(BOARD_GPIO_ENCODER_CONFIG->base, BOARD_GPIO_ENCODER_CONFIG->pin, true);
        
    PRINTF("\n\r====================== PID MOTOR ========================\n\r");
}

void SetRPMMotor(float desiredrpm) {
	SetPoint = desiredrpm;
}

void SetPWMFrequency(float desiredfrequency) {
	period = 1000000/desiredfrequency - 2;
}

/*void SetPWMmicrosPeriod(float desiredmicrosPeriod) {
	period = microsPeriod - 2;
}*/


void PIDControl() {
	RPM = 60*1000/(deltatime*30);
    error = SetPoint - RPM;
    ierror = ierror + error;
    derror = (error - preverror)/deltatime;
    dutyCycle = kp * error + ki * ierror + kd * derror;
    dutyCycle = (dutyCycle > maxduty) ? maxduty:((dutyCycle < minduty) ? minduty:dutyCycle);
}



void Control(void *pvParameters)
{	
    while (true)
    {
    	PIDControl();
        PWM_SetSampleValue(PWM2, (int) period * 0.01 * dutyCycle);
        vTaskDelay((int) 1000/controlfreq);
    }
}

void beginControl(int freq) {
	
	PWM_GetDefaultConfig(&pwmConfig);
    
   
    /* Initialize PWM module */
    PWM_Init(PWM2, &pwmConfig);


    /* Enable FIFO empty interrupt */
    
    PWM_EnableInterrupts(PWM2, kPWM_FIFOEmptyInterruptEnable);
    

    /* Initial samples be written to the PWM Sample Register */
    PWM_SetSampleValue(PWM2, 0);
    


    /* Check and Clear interrupt status flags */
    if(PWM_GetStatusFlags(PWM2))
    {
        PWM_clearStatusFlags(PWM2, kPWM_FIFOEmptyFlag | kPWM_RolloverFlag | kPWM_CompareFlag | kPWM_FIFOWriteErrorFlag);
    }
    

    /* Write the period to the PWM Period Register */
    PWM_SetPeriodValue(PWM2, period);
    
    
    /* Set PWM Interrupt priority */
    NVIC_SetPriority(BOARD_PWM2_IRQ_NUM, 3);
  
    /* Call core API to enable the IRQ. */
    NVIC_EnableIRQ(BOARD_PWM2_IRQ_NUM);
    

    /* Start PWM Output */
    PWM_StartTimer(PWM2);


	controlfreq = freq;
	InitEncoderPin();
	/* Create a the APP main task. */
    xTaskCreate(Control, "Control", 2000, NULL, tskIDLE_PRIORITY+1, NULL);
	/* Start FreeRTOS scheduler. */
    vTaskStartScheduler();
}



