# Modulo_GY80
Este Modulo contém quarto sensores: acelerômetro, giroscópio, magnetômetro e barômetro.

* **L3G4200D** (3-Axis Angular Rate Sensor) - Giroscópio 3 eixos

* **ADXL345** (3-Axis Digital Accelerometer) - Acelerômetro 3 eixos

* **HMC5883L** (3-Axis Digital Compass) - Bússola digital / Magnetômetro

* **BMP085** (Barometric Pressure Sensor) - Sensor de temperatura e pressão

A comunicação com o Arduino é feita pela interface I2C, e todos os sensores citados acima são endereçados individualmente. A ligação básica ao Arduino utiliza somente 4 pinos, dos 10 disponíveis no módulo. A alimentação pode ser feita tanto com 5V como com 3.3V :

- **VCC_IN** - Utilize este pino para alimentar o sensor com 5V

- **VCC_3.3V** - Utilize este pino para alimentar o sensor com 3.3V

- **GND** - Conectado ao GND do Arduino

- **SCL** - Conectado ao pino analógico A5 do Arduino Uno 

- **SDA** - Conectado ao pino analógico A4 do Arduino Uno

## Descrição do projeto:
Neste projeto foi utilizado somente o sensor **ADXL345**, onde ele retorna a leitura dos eixos x, y e z.
Utilizou-se dois resistores de 1k3 nos pinos **SCL** e **SDA** para ativação de *Pull Up* e uma alimentação de 5V.

A comunicação I2C do sensor foi feita no arquivo `ADXL345.c` junto com a biblioteca avr_twi_master.c fornecida pela Atmel. Primeiro foi inicializada a comunicação I2C e foram enviados os endereços de inicialização do sensor ( escrita, controle de energia e ativação do bit de medição). Após disso, realizou-se a leitura dos eixos (x, y e z).

Os testes da comunicação I2C foram feitos pela função `print_axis`, a qual envia os valores dos eixos para o terminal serial USART.

### Exemplo de exibição dos dados atráves do terminal serial:

```
x= 1007, y= 16, z= 36
```

:red_circle: Os valores dos eixos foram multiplicados por 1000 para aumetar a precisão.

Após o condicionamento dos dados do sensor, estes valores foram enviados ao módulo **WiFi ESP-01**, que enviará os dados do sensor à Internet através do protocolo MQTT (*Message Queuing Telemetry Transport*). Para isso, utilizou-se o arquivo `modbus.c`, onde foi enviado o pacote RTU contendo (*addr, cmd, reg, data, crc*) 

* **addr**: endereço do dispositivo que se deseja enviar uma mensagem (0x15) (1 byte)

* **cmd**: comando que se deseja enviar, geralmente escrita (0x01) ou leitura (0x02). (1 byte)

* **reg**: qual registrador do dispositivo deseja-se escrever ou ler. (2 bytes)

* **data**: dado que se deseja escrever no registrador ou número de registradores que se deseja ler. (2 bytes)

* **crc**: verificação cíclica de redundância. (2 bytes)

:red_circle: Para o envio dos dados que são de 2 bytes, foi necessário trocar os primeiros dois bytes com os dois últimos, pois o Modbus é do tipo big endian.

## Instalação e Execução:

Inicialmente é montado a placa que vai estar conectada com o arduino, contendo o módulo GY-80, um conversor de nível (5V - 3.3V), pois o arduino fornece uma alimentação de 5V e o módulo ESP-01 necessita de 3.3V

        
## Colaboradores
* Heloiza Martins

* Suzi Yousif
