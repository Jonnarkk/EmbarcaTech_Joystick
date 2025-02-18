# EmbarcaTech_Joystick

## Descrição
Este projeto junta os conhecimentos adquiridos em PWM, manipulação do display OLED, uso dos botões e interrupções com tratamento de debouncing e o ADC (Analogic-Digital Converter).
Com essas ferramentas, podemos controlar um quadrado no display juntamente com a intensidade dos LED's RGB através dos valores lidos do conversor, além de ativar/desativar a função
PWM com o botão A.

## Funcionalidades
- **Botão A**: Habilita/Desabilita o PWM, ou seja, o controle da intensidade dos LED's.
- **Botão B**: Habilita o modo de gravação BOOTSEL da placa (EXTRA).
- **Botão Joystick**: Liga o LED verde e altera a borda do display.

## Estrutura do Código
O código está estruturado em funções para inicilização e manuseio dos periféricos:

- `void setup_inicial()`: Inicializa os pinos necessários e também o display, faz toda a configuração básica dos periféricos.
- `void gpio_irq_handler()`: Trata da interrupção dos botões quando algum deles é pressionado.
- `gpio_set_irq_enabled_with_callback()`: Configura a interrupção para todos os botões.
- `joystick_adc_init()`: Inicializa os pinos do eixo X e Y do analógico, está modularizado na biblioteca "joystick.h".
- `gpio_pwm_config()`: Inicializa o PWM nos pinos dos LED's controlados pelo analógico, está modularizado na biblioteca "joystick.h".

## Estrutura dos arquivos
```
project/
│
├── Display_files/
│   ├── font.h
│   ├── ssd1306.c
│   ├── ssd1306.h
│
├── headers/
│   ├── joystick.h
├── EmbarcaTech_Joystick.c
├── CMakeLists.txt
└── README.md
```

## Desenvolvedor
Guiherme Miller Gama Cardoso

## Link com o vídeo explicativo
https://drive.google.com/file/d/1S8a7xSkMynjiOJx6CSPy0inAxYiMOd6f/view?usp=sharing