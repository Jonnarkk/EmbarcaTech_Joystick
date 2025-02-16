#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/adc.h"
#include "hardware/pwm.h"
#include "pico/bootrom.h"
#include "./headers/joystick.h"
#include "./Display_files/ssd1306.h"


// Defines
#define joyX 27
#define joyY 26
#define sense 50
#define I2C_LINK 0x3C
#define I2C_PORT i2c1
#define I2C_SDA 14
#define I2C_SCL 15
#define BOTAO_A 5
#define BOTAO_B 6
#define BOTAO_J 22
#define LED_G 11
#define LED_B 12
#define LED_R 13
#define DIV 25.0
#define WRAP 1800

// Variáveis globais
uint DUTY_C = 0;
uint sliceB; // Variável para o slice do LED azul
uint sliceR; // Variável para o slice do LED vermelho
uint32_t last_print_time = 0;
uint32_t last_timeA = 0; // Guarda a última vez que o botão A foi pressionado
uint32_t last_timeJ = 0; // Guarda a última vez que o botão Joystick foi pressionado
ssd1306_t ssd;
bool cor = true;
bool pwm_function = true; // Variável que permite o joystick controlar intensidade dos LEDs
bool ledg_state = false; // Indica estado atual do LED verde

void gpio_irq_handler(uint gpio, uint32_t eventes){
    if(gpio == BOTAO_B){
        printf("Reiniciando a palca para modo de gravação...\n");
        reset_usb_boot(0, 0);
    }

    uint32_t current_time = to_us_since_boot(get_absolute_time());

    if(current_time - last_timeA > 200e+3){
        last_timeA = current_time;

        if(gpio == BOTAO_A){
            pwm_function = !pwm_function;
            pwm_set_enabled(sliceB, pwm_function);
            pwm_set_enabled(sliceR, pwm_function);
            printf("ESTADO: %s\n", pwm_function? "PWM ATIVADO": "PWM DESATIVADO");
            
        }
    }

    if(current_time - last_timeJ > 200e+3){
        last_timeJ = current_time;

        if(gpio == BOTAO_J){
            ledg_state = !ledg_state;
            gpio_put(LED_G, ledg_state);
            printf("ESTADO: %s\n", ledg_state? "LED VERDE ATIVADO": "LED VERDE DESATIVADO");
        }
    }
}

void setup_inicial(){
    // Inicializar ADC no joystick
    joystick_adc_init(joyX, joyY);

    //Inicializa o I2C, configura a estrutura do display e limpa o display
    ssd1306_init_config_clean(&ssd,I2C_SCL,I2C_SDA,I2C_PORT,I2C_LINK);

    // Configura o pwm dos LED's vermelho e azul
    sliceB = gpio_pwm_config(LED_B, DIV, WRAP, DUTY_C);
    sliceR = gpio_pwm_config(LED_R, DIV, WRAP, DUTY_C);
    pwm_set_enabled(sliceB, pwm_function); 
    pwm_set_enabled(sliceR, pwm_function); 

    // Inicializa LED verde
    gpio_init(LED_G);
    gpio_set_dir(LED_G, GPIO_OUT);

    // Inicializa botões e interrupções
    gpio_init(BOTAO_A);
    gpio_set_dir(BOTAO_A, GPIO_OUT);
    gpio_pull_up(BOTAO_A);
    gpio_set_irq_enabled_with_callback(BOTAO_A, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_init(BOTAO_B);
    gpio_set_dir(BOTAO_B, GPIO_OUT);
    gpio_pull_up(BOTAO_B);
    gpio_set_irq_enabled_with_callback(BOTAO_B, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
    gpio_init(BOTAO_J);
    gpio_set_dir(BOTAO_J, GPIO_OUT);
    gpio_pull_up(BOTAO_J);
    gpio_set_irq_enabled_with_callback(BOTAO_J, GPIO_IRQ_EDGE_FALL, true, &gpio_irq_handler);
}

int main(){
    stdio_init_all();
    setup_inicial();

    while (true) {
        printf("Hello, world!\n");
        sleep_ms(1000);
    }
}
