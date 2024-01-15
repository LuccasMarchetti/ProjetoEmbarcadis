#include "PID_MOTOR.c"


int count = 0;


/******************************************************************************
*
* Nome da Função: ChangeSetPoint
* Comentários: Task usada para mudar o SetPoint a cada 5 segundos.
*
******************************************************************************/
void ChangeSetPoint(void *pvParameters) {
	
	if (count == 0) {
		SetRPMMotor(60);
		PRINTF("\r\nMudando SetPoint para 60!\n\n\r");
	}
	if (count == 1) {
		SetRPMMotor(90);
		PRINTF("\r\nMudando SetPoint para 90!\n\n\r");
	}
	if (count == 2) {
		SetRPMMotor(120);
		PRINTF("\r\nMudando SetPoint para 120!\n\n\r");
	}
	if (count == 3) {
		SetRPMMotor(180);
		PRINTF("\r\nMudando SetPoint para 180!\n\n\r");
	}
	if (count == 4) {
		SetRPMMotor(300);
		PRINTF("\r\nMudando SetPoint para 300!\n\n\r");
	}
	if (count == 5) {
		SetRPMMotor(500);
		PRINTF("\r\nMudando SetPoint para 500!\n\n\r");
	}
	if (count == 6) {
		SetRPMMotor(900);
		PRINTF("\r\nMudando SetPoint para 900!\n\n\r");
	}
	count++;
	vTaskDelay(5000);
}


/******************************************************************************
*
* Nome da Função: main
* Comentários: Código principal. Inicializa os periféricos, configura o PWM para o motor, 
* inicia o controle.
*
******************************************************************************/
int main(void)
{
    /* Initialize board specified hardware. */
    hardware_init();
    
    
    PRINTF("\r\nIniciando Controle de Motor!\n\n\r");
    xTaskCreate(ChangeSetPoint, "ChangeSetPoint", 200, NULL, tskIDLE_PRIORITY-2, NULL);
    beginControl(300);
    

    /* should never reach this point. */
    while (true);
}

/*******************************************************************************
 * EOF
 ******************************************************************************/
