#include <stdio.h>       
#include "pico/stdlib.h" 
#include "pico/time.h"   

#define LED_BLUE 11   // Define o pino GPIO 11 para o LED azul.
#define LED_RED 12    // Define o pino GPIO 12 para o LED vermelho.
#define LED_GREEN 13  // Define o pino GPIO 13 para o LED verde.
#define BUTTON_PIN 5  // Define o pino GPIO 5 para o botão.

volatile bool led_active = false;    // Indica se os LEDs estão acesos.
volatile int led_state = 0;          // Controla o estado de qual LED deve ser desligado.


// Função de callback para desligar os LEDs em sequência.
int64_t turn_off_callback(alarm_id_t id, void *user_data) {
    if (led_state == 1) {
        gpio_put(LED_GREEN, false);  // Desliga o LED verde.
    } else if (led_state == 2) {
        gpio_put(LED_RED, false);    // Desliga o LED vermelho.
    } else if (led_state == 3) {
        gpio_put(LED_BLUE, false);   // Desliga o LED azul.
        led_active = false;          // Libera o botão para nova execução.
        return 0;                    // Encerra a sequência de LEDs.
    }

    led_state++; // Move para o próximo LED.
    // Agenda o próximo desligamento após 3 segundos (3000ms).
    add_alarm_in_ms(3000, turn_off_callback, NULL, false);

    return 0;
}

// Callback acionado ao pressionar o botão.
void button_callback(uint gpio, uint32_t events) {
    if (!led_active) {
        led_active = true; // Indica que os LEDs estão em execução.
        led_state = 1;     // Começa com o LED verde.

        printf("Botão pressionado! Iniciando sequência de LEDs.\n");

        // Acende todos os LEDs (verde, vermelho e azul).
        gpio_put(LED_GREEN, true);
        gpio_put(LED_RED, true);
        gpio_put(LED_BLUE, true);

        // Agenda o desligamento do LED verde após 3 segundos.
        add_alarm_in_ms(3000, turn_off_callback, NULL, false);
    }
}

int main() {
    stdio_init_all();

    // Configuração dos LEDs como saída.
    gpio_init(LED_BLUE);
    gpio_set_dir(LED_BLUE, GPIO_OUT);
    gpio_init(LED_RED);
    gpio_set_dir(LED_RED, GPIO_OUT);
    gpio_init(LED_GREEN);
    gpio_set_dir(LED_GREEN, GPIO_OUT);

    // Configuração do botão como entrada com pull-up.
    gpio_init(BUTTON_PIN);
    gpio_set_dir(BUTTON_PIN, GPIO_IN);
    gpio_pull_up(BUTTON_PIN);

    // Habilita interrupção no botão para detectar pressionamento.
    gpio_set_irq_enabled_with_callback(BUTTON_PIN, GPIO_IRQ_EDGE_FALL, true, &button_callback);

    while (1) {
        tight_loop_contents(); // Mantém o loop ativo.
    }

    return 0;
}
