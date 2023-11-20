# p-sensor

<h1>Projeto feito utilizando ESP32, Arduino Uno e PulseSensor</h1>
O sensor é conectado pelo arduino por 5v, gnd e a0 (para encaminhar os dados). Além disso, é utilizado 3.3v no esp32 e as portas tx2 e rx2 (portas gdi 16 e 17 respectivamente. Após isso, basta posicionar o dedo no sensor e ignorar as primeiras contagens por conta da variação da luz.

## Requerimentos
Para utilizar, é necessário um Arduíno Uno, um módulo ESP32 e um Pulse sensor</br>
É necessário utilizar o Arduino IDE para rodar o código.</br>

ESP32:
ESP32 é um único chip combinado Wi-Fi e Bluetooth de 2,4 GHz projetado com 40 nm de baixa potência da TSMC tecnologia. Ele foi projetado para alcançar o melhor desempenho de potência e RF, mostrando robustez, versatilidade e confiabilidade em uma ampla variedade de aplicações e cenários de energia.</br>
PulseSensor:
É um monitor de frequência cardíaca de código aberto considerado um dispositivo PPG usado para monitorar a frequência cardíaca não invasiva. Ele mede os batimentos cardíacos em tempo real e calcula o BPM com o auxílio de algoritmos implementados pelo Arduino. Este sensor possui dois lados, o frontal que tem formato de coração é o lado a ser fixado na pele. O sensor faz a conversão dos dados obtidos através do sensor óptico, captando as variações dos pulsos através da pele. Ao colocar o sensor próximo a pele, o ideal é que aguarde ou pule o primeiro número lido por gerar um pico inicial na primeira leitura óptica. 
</br>
Arduino uno:
Arduino UNO é uma placa microcontroladora baseada no ATmega328P. Possui 14 pinos de entrada/saída digital (dos quais 6 podem ser usados como saídas PWM), 6 entradas analógicas, um ressonador cerâmico de 16 MHz, uma conexão USB, um conector de alimentação, um conector ICSP e um botão de reset. Contém tudo o que é necessário para suportar o microcontrolador; basta conectá-lo a um computador com um cabo USB ou alimentá-lo com um adaptador CA para CC ou bateria para começar. Você pode mexer sem 3 se preocupar muito em fazer algo errado, na pior das hipóteses, é possível substituir o chip de maneira barata e recomeçar</br>
## Documentação

![scheme](https://github.com/hygor-gomes/p-sensor/assets/110134036/9d44b4fb-284a-4cc2-ba88-b2f14524bde8)</br>

Documentação MQTT: https://dojotdocs.readthedocs.io/pt-br/latest/mqtt-tls.html</br>

Documentação Arduino Uno: https://docs.arduino.cc/hardware/uno-rev3</br>

Documentação ESP32: https://docs.espressif.com/projects/esp-idf/en/latest/esp32/</br>

Documentação PulseSensor: https://pulsesensor.com/pages/code-and-guide</br>
