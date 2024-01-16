# Introdução

Este repósitório contém o código do projeto da disciplina de Sistemas Embarcados, tendo sido projetado para o núcleo M4 de uma Colibri iMX7D.

# Alunos

O projeto foi realizado por Jean de Oliveira, Luccas Marchetti e Vinicius Axhcar, sendo a função de cada um desses, respectivamente, pesquisar bibliotecas para o uso de PWM no núcleo M4, uso do FreeRTOS e modificação da Device Tree do Linux, e, por fim, uso de interrupções no núcleo M4. Ambos os autores pesquisaram sobre o funcionamento particular do núcleo M4 e do RDC (Resource Domain Controller), e trabalharam na escrita dos códigos, concluindo o trabalho com a criação de uma biblioteca ("PID_MOTOR") e no código principal para a entrega do projeto.

# Projeto
Por conta da complexidade de uso do núcleo M4, não se disponibilizou a Device Tree do Linux, nem todo o kit de desenvolvimento de software, mas apenas os códigos que sofreram alterações.

Em resumo, o código implementa um controlador PID de rotação de motor DC via PWM, utilizando-se de interrupções (advindas de um encoder de 30 posições), em conjunto com um GPT (General Purpose Timer) para obter a frequência de rotação.

Este repositório se utiliza de códigos e bibliotecas de terceiros, sobretudo a pwm_imx.

Todo o código é implementado usando FreeRTOS, possibilitando a criação de tasks paralelas à do controle do motor. 
O código inicia criando uma task para mudar a velocidade designada a cada 5 segundos, e utiliza de outra para manter o controle do motor com frequência definida.
Por fim, o Schedular é iniciado e as tarefas começam a rodar.

O código principal se chama "main" e se encontra no caminho '/Projetos/imx7_colibri_m4/ProjetoEmbarcados/PWM_teste/', possuindo tal localização e estrutura de pastas por conta do CMakeList, mantendo uma estrutura muito semelhante à original do SDK distribuído.

Caso deseje compilar o código, recomenda-se seguir o passo à passo do uso do núcleo M4, disponível no site da Toradex.
Todavia, basta definir o compilador que será usado e executar o arquivo build_all.sh, encontrado no caminho '/Projetos/imx7_colibri_m4/ProjetoEmbarcados/PWM_teste/armgcc/'.
O código compilado, no formato .elf, estará no caminho '/Projetos/imx7_colibri_m4/ProjetoEmbarcados/PWM_teste/armgcc/release/'.

# Considerações finais

Infelizmente nosso grupo não conseguiu realizar testes em bancada por conta de não estar em São Carlos em tempo hábil para a realização dos mesmos, mas foi capaz de absorver e desenvolver um vasto conhecimento sobre códigos em linguagem C, uso do CMake, compiladores e uso de SDKs, além da compreensão da arquitetura e funcionamento do processador M4 do módulo Colibri iMX7D e o relacionamento de núcleos dentro de uma arquitetura heterogênea rodando diferentes sistemas operacionais.
