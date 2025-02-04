#include <stdio.h>
#include "pico/stdlib.h"

// Definição dos pinos
#define LED_AZUL_PIN 11
#define LED_VERMELHO_PIN 12
#define LED_PINO_VERDE_PIN 13
#define BOTAO_PIN 5

int main()
{
    stdio_init_all();

    gpio_init(LED_AZUL_PIN);
    gpio_init(LED_VERMELHO_PIN);
    gpio_init(LED_PINO_VERDE_PIN);
    gpio_init(BOTAO_PIN);

    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT);
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    gpio_set_dir(LED_PINO_VERDE_PIN, GPIO_OUT);
    gpio_set_dir(BOTAO_PIN, GPIO_IN);
    gpio_pull_up(BOTAO_PIN);

    while (true) {
        if (gpio_get(BOTAO_PIN) == 0) {
            printf("Botão foi pressionado!\n");
            gpio_put(LED_AZUL_PIN, 1);
            gpio_put(LED_VERMELHO_PIN, 1);  
            gpio_put(LED_PINO_VERDE_PIN, 1);
            sleep_ms(500);
            gpio_put(LED_AZUL_PIN, 0);
            gpio_put(LED_VERMELHO_PIN, 0);
            gpio_put(LED_PINO_VERDE_PIN, 0);
        }

        sleep_ms(1000);
    }
}
