Este repósitório contém o código do projeto da disciplina de Sistemas Embarcados, tendo sido projetado para o núcleo M4 de uma Colibri iMX7D.
Por conta da não simplicidade de uso do núcleo M4, não se disponibilizou a Device Tree do Linux, nem todo o kit de desenvolvimento de software, 
mas apenas os códigos que sofreram alterações.

Em resumo, o código implementa um controlador PID de rotação de motor DC via PWM, utilizando-se de interrupções (advindas de um encoder de 30 posições),
em conjunto com um GPT (General Purpose Timer) para obter a frequência de rotação.

Todo o código é implementado usando FreeRTOS, possibilitando a criação de tasks paralelas à do controle do motor. 
O código inicia criando uma task para mudar a velocidade designada a cada 5 segundos, e utiliza de outra para manter o controle do motor com frequência definida.
Por fim, o Schedular é iniciado e as tarefas começam a rodar.
