# README - Temporizador de Disparo Único para LEDs

## Descrição

Este projeto utiliza um **Raspberry Pi Pico W** para controlar três LEDs (azul, vermelho e verde) e um botão (pushbutton). Quando o botão é pressionado, os três LEDs acendem simultaneamente, e, após um atraso de 3 segundos, os LEDs vão apagando um a um, seguindo a ordem: todos acesos, dois acesos e, por fim, apenas um. Esse comportamento é gerenciado por temporizadores e funções de callback usando o **Pico SDK**.

A funcionalidade é baseada na função `add_alarm_in_ms()`, que permite a configuração de alarmes temporizados. O objetivo é criar um sistema de temporização para acionar os LEDs de forma controlada e sequencial, com a interação do usuário via botão.

## Requisitos

- **Hardware**:
  - 1 Raspberry Pi Pico W
  - 3 LEDs (Azul, Vermelho e Verde)
  - 3 Resistores de 330 Ω
  - 1 Pushbutton (Botão)
  
- **Software**:
  - Pico SDK
  - Ambiente de desenvolvimento para o Raspberry Pi Pico (como o Wokwi ou um ambiente local de C/C++ com o compilador adequado)

## Descrição do Funcionamento

1. **Acionamento do Botão**: 
   - Quando o botão é pressionado, todos os LEDs (azul, vermelho e verde) acendem simultaneamente.
   
2. **Temporizador**:
   - A cada 3 segundos (3.000ms), os LEDs começam a apagar um a um:
     1. Primeiramente, todos os LEDs estão acesos.
     2. Após 3 segundos, o LED verde é apagado.
     3. Após outros 3 segundos, o LED vermelho é apagado.
     4. Após mais 3 segundos, o LED azul é apagado.
   
3. **Controle com o Botão**:
   - O botão só pode iniciar o processo de temporização (sequência de LEDs) quando todos os LEDs estiverem apagados. Durante o processo de temporização (em que os LEDs estão acesos e apagando sequencialmente), o botão é ignorado para evitar interrupções indesejadas.

## Componentes Utilizados

- **Microcontrolador**: Raspberry Pi Pico W
- **LEDs**: Azul, Vermelho e Verde
- **Resistores**: 3 resistores de 330 Ω
- **Botão (Pushbutton)**

## Diagrama do Circuito

O circuito consiste em três LEDs, cada um conectado a um pino GPIO (11, 12 e 13) do Raspberry Pi Pico. Cada LED tem um resistor de 330 Ω em série. O botão é conectado ao pino GPIO 5, com um resistor de pull-up ativo.

### Conexões:

- **LED Verde**: GPIO 11
- **LED Vermelho**: GPIO 12
- **LED Azul**: GPIO 13
- **Botão**: GPIO 5
- **Resistor de 330 Ω**: Conectado em série com cada LED.

## Código

O código implementa o funcionamento descrito acima utilizando funções de temporização (`add_alarm_in_ms()`), onde cada estado de acionamento dos LEDs é gerenciado por uma função de callback chamada `turn_off_callback()`.

## Instruções para Execução

1. **Carregar o código** no seu Raspberry Pi Pico usando o ambiente de desenvolvimento adequado.
2. **Conectar o circuito** conforme o diagrama descrito.
3. **Pressionar o botão** para iniciar a sequência de LEDs. O sistema vai ligar todos os LEDs, e após 3 segundos, os LEDs vão apagar um a um até que todos estejam apagados.
4. **Reiniciar o processo**: O botão só vai ser útil para reiniciar o processo quando todos os LEDs estiverem apagados.

## Conclusão

Este projeto simula um controle de LEDs com temporização sequencial usando o Raspberry Pi Pico e a função de temporização do Pico SDK. Ele é uma boa introdução ao uso de interrupções, temporizadores e controle de hardware em sistemas embarcados.