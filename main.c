#include <stdio.h>
#include <pico/stdlib.h>
#include <hardware/timer.h>
#include <hardware/gpio.h>

// Definição dos pinos dos LEDs e do botão
#define LED_AZUL_PIN 11
#define LED_VERMELHO_PIN 12
#define LED_VERDE_PIN 13
#define BOTAO_PIN 5

// Intervalo em milissegundos (3 segundos)
#define TEMPORIZADOR_LED 3000

// Variáveis de controle
static bool processo_ativo = false; // Controla o estado do processo
static int estado = 0; // Controla a sequência de desligamento dos LEDs

// Função de callback do temporizador para gerenciar os LEDs
long long int repetir_temporizador_callback(long int alarm_id, void *user_data)
{
    // Estados de desligamento progressivo
    int combinacoes[4][3] = {
        {1, 1, 1}, // Estado 0: Todos os LEDs acesos
        {0, 1, 1}, // Estado 1: Apaga o LED Azul
        {0, 0, 1}, // Estado 2: Apaga o LED Azul e Vermelho
        {0, 0, 0}  // Estado 3: Apaga todos os LEDs
    };

    // Aplicação do estado de desligamento dos LEDs
    gpio_put(LED_AZUL_PIN, combinacoes[estado][0]);
    gpio_put(LED_VERMELHO_PIN, combinacoes[estado][1]);
    gpio_put(LED_VERDE_PIN, combinacoes[estado][2]);

    // Apresentando mensagem no terminal a cada mudança de estado
    switch (estado) {
        case 0:
            printf("LEDs Azul, Vermelho e Verde acesos\n");
            break;
        case 1:
            printf("LED Vermelho e Verde acesos\n");
            break;
        case 2:
            printf("LED Verde aceso\n");
            break;
        case 3:
            printf("Todas as LEDs apagadas\n");
            break;
    }

    // Muda para o próximo o estado
    estado++;

    // Quando a sequência é concluída, o sistema encerra a execução até ser ativado novamente
    if (estado == 4)
    {
        processo_ativo = false;
        return 0; // Finaliza o alarme
    }

    // Inicia o próximo alarme (próximo estado)
    add_alarm_in_ms(TEMPORIZADOR_LED, repetir_temporizador_callback, NULL, false);
    return 0; // Retorno necessário, o alarme continuará funcionando
}

// Callback do botão
void callback_botao(uint gpio, uint32_t events)
{
    if (!processo_ativo) // Só inicia se não estiver rodando
    { 
        processo_ativo = true; //Marca o processo como ativo
        estado = 0;

        // Ativa todos os LEDs inicialmente
        gpio_put(LED_AZUL_PIN, 1); //Acende o LED Azul
        gpio_put(LED_VERMELHO_PIN, 1); //Acende o LED Vermelho
        gpio_put(LED_VERDE_PIN, 1); //Acende o LED Verde
        printf("LEDs Azul, Vermelho e Verde acesos\n");
        // A sequência dos LEDs começa com o disparo do temporizador
        add_alarm_in_ms(TEMPORIZADOR_LED, repetir_temporizador_callback, NULL, false);
    }
}

// Inicialização dos pinos e interrupções
void inicia_sistema()
{ // Inicialização dos pinos dos LEDs
    gpio_init(LED_AZUL_PIN);
    gpio_init(LED_VERMELHO_PIN);
    gpio_init(LED_VERDE_PIN);
    gpio_init(BOTAO_PIN); // Inicialização do botão
// Configuração dos pinos como saída
    gpio_set_dir(LED_AZUL_PIN, GPIO_OUT); 
    gpio_set_dir(LED_VERMELHO_PIN, GPIO_OUT);
    gpio_set_dir(LED_VERDE_PIN, GPIO_OUT);
    gpio_set_dir(BOTAO_PIN, GPIO_IN); // Configura o botão como entrada
    gpio_pull_up(BOTAO_PIN); // Habilita o pull-up no botão

    gpio_set_irq_enabled_with_callback(BOTAO_PIN, GPIO_IRQ_EDGE_FALL, true, &callback_botao); // Configura a interrupção do botão (queda de borda) 
}

int main()
{
    stdio_init_all(); // Inicializa o sistema de entrada e saida (I/O)
    printf("Sistema iniciado...\n"); // Mensagem inicial

    inicia_sistema(); // Inicializa o sistema de pinos e interrupções
    
    while (1)
    { // Loop principal
        tight_loop_contents(); // Executa o loop
    }
}
