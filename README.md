# Modulo_GY80
Este Modulo contém quarto sensores: acelerômetro, giroscópio, magnetômetro e barômetro.

**L3G4200D** (3-Axis Angular Rate Sensor) - Giroscópio 3 eixos

**ADXL345** (3-Axis Digital Accelerometer) - Acelerômetro 3 eixos

**HMC5883L** (3-Axis Digital Compass) - Bússola digital / Magnetômetro

**BMP085** (Barometric Pressure Sensor) - Sensor de temperatura e pressão

A comunicação com o Arduino é feita pela interface I2C, e todos os sensores citados acima são endereçados individualmente. A ligação básica ao Arduino utiliza somente 4 pinos, dos 10 disponíveis no módulo. A alimentação pode ser feita tanto com 5V como com 3.3V :

**VCC_IN** - Utilize este pino para alimentar o sensor com 5V

**VCC_3.3V** - Utilize este pino para alimentar o sensor com 3.3V

**GND** - Conectado ao GND do Arduino

**SCL** - Conectado ao pino analógico A5 do Arduino Uno 

**SDA** - Conectado ao pino analógico A4 do Arduino Uno

## Descrição do projeto:
Neste projeto foi utilizado somente o sensor **ADXL345**, onde ele retorna a leitura dos eixos x, y e z.
Utilizou-se dois resistores de 1k3 nos pinos **SCL** e **SDA** para ativação de *Pull Up* e uma alimentação de 5V.

## Instalação e Execução:

### Exemplo de uso:

        
## Contribuição
* **Heloiza Martins**: 

* **Suzi Yousif**: 
