#include "pico/stdlib.h"
#include "hardware/timer.h"
#include <stdio.h>

// Variáveis dos LEDs
#define LED_VERDE 11
//#define LED_AZUL 12
#define LED_VERMELHO 13

//variável para contar loops
uint8_t cont = 0;

//cabeçalhos das funções
void inicializar_leds();
bool semaforo_callback(struct repeating_timer *t);

int main() {
    //inicia a comunicação serial
    stdio_init_all();
    //iniciliza pinos dos leds
    inicializar_leds();

    struct repeating_timer timer;

    //temporizador que executa o callback a cada 3 segundos
    add_repeating_timer_ms(3000, semaforo_callback, NULL, &timer);

    while (true) {
        sleep_ms(1000);
        printf("Passou 1 segundo\n");
    }

    return 0;
}

void inicializar_leds(){
	gpio_init(LED_VERDE);
	//gpio_init(LED_AZUL);
	gpio_init(LED_VERMELHO);
	gpio_set_dir(LED_VERDE, GPIO_OUT);
	//gpio_set_dir(LED_AZUL, GPIO_OUT);
	gpio_set_dir(LED_VERMELHO, GPIO_OUT);
}

bool semaforo_callback(struct repeating_timer *t) {
    //conta até 3, em cada valor acende uma cor do led
    switch (cont){
        //vermelho
        case 0:
            gpio_put(LED_VERMELHO, 1);
            //gpio_put(LED_AZUL, 0);
            gpio_put(LED_VERDE, 0);
            printf("1 0");
            break;
        //amarelo
        case 1:
            gpio_put(LED_VERMELHO, 1);
            //gpio_put(LED_AZUL, 0);
            gpio_put(LED_VERDE, 1);
            printf("1 1");
            break;
        //verde
        case 2:
            gpio_put(LED_VERMELHO, 0);
            //gpio_put(LED_AZUL, 0);
            gpio_put(LED_VERDE, 1);
            printf("0 1");
            break;
        default:
            break;
    }
    
    printf(" - %u\n", cont);

    cont++;
    //limita cont a no máximo 3
    if(cont>2) cont = 0;

    return true;
}