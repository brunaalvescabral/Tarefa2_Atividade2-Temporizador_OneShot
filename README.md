# Tarefa 2: Atividade 2 - Temporizador de Disparo (One Shot) 

## Descrição

Este projeto utiliza o microcontrolador Raspberry Pi Pico para controlar três LEDs (azul, vermelho e verde) e um botão (pushbutton). O acionamento dos LEDs é feito a partir do clique do botão, com temporizadores que alteram o estado dos LEDs após 3 segundos. O comportamento do sistema simula uma sequência de LEDs acesos, começando com todos os LEDs acesos, depois dois, e por fim apenas um, com um atraso de 3 segundos entre cada transição.

## Funcionalidades

1. *Controle dos LEDs:*
   - O botão, quando pressionado, acende os três LEDs (azul, vermelho e verde).
   - Após o tempo de 3 segundos (3000ms), dois LEDs são apagados, restando apenas um aceso.
   
2. *Temporização de 3 segundos:*
   - O temporizador do alarme (usando a função add_alarm_in_ms()) é configurado para acionar uma mudança no estado dos LEDs a cada 3 segundos.
   
3. *Botão (Pushbutton):*
   - O botão A (GPIO 5) aciona os LEDs. Após o acionamento, o botão não pode reiniciar o ciclo enquanto as rotinas de temporização estão em execução.
   - Implementação de *debouncing de botão* (opcional) para evitar múltiplos acionamentos indesejados.

4. *Funções Call-Back:*
   - Funções de callback são usadas para controlar a mudança de estado dos LEDs após cada temporização.

## Requisitos

- *Hardware:*
  - Raspberry Pi Pico
  - 3 LEDs (azul, vermelho e verde) conectados aos pinos GPIO 11, 12 e 13
  - 3 Resistores de 330 Ω para limitar a corrente dos LEDs
  - 1 Pushbutton (Botão A) conectado ao GPIO 5
  - Resistores de pull-up internos para o botão
  
- *Software:*
  - Raspberry Pi Pico SDK
  - Visual Studio Code com a extensão para Raspberry Pi Pico

## Configuração do Hardware

| Componente        | Conexão        |
|-------------------|----------------|
| LED Azul          | GPIO 11        |
| LED Vermelho      | GPIO 12        |
| LED Verde         | GPIO 13        |
| Botão (Pushbutton)| GPIO 5         |

## Como Executar

### 1. Configuração do Ambiente

- Certifique-se de que o SDK do Raspberry Pi Pico está corretamente configurado no seu ambiente de desenvolvimento.
- Instale o Visual Studio Code e a extensão *Raspberry Pi Pico Project*.

### 2. Compilação e Execução

1. Compile o programa no Visual Studio Code utilizando a extensão *Raspberry Pi Pico Project*.
2. Coloque o Raspberry Pi Pico em modo de boot e copie o arquivo main.uf2 para o microcontrolador conectado via USB.

### 3. Emulação com Wokwi 

1. Para emular o projeto sem hardware físico, utilize o *Wokwi*.
2. Instale a extensão *Wokwi for VS Code* e inicie a emulação.
3. Teste o funcionamento do programa no ambiente emulado.

## Licença

Este projeto está licenciado sob a [MIT License](LICENSE).
