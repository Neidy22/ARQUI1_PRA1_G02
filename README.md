<h1 align="center">
MANUAL TECNICO PRACTICA C+ ASSEMBLER ARDUINO+ CONTROL
ASSEMBLER ENBEBIDO EN ARDUINO
</h1>

```
//Acceder a las subrutinas
{
 void start();
 void my_loop();
}

void setup(){
 start();
}

void loop(){
 my_loop();
}
```
*Para poder reconocer el archivo de assembler en arduino y embeberlo es necesario utilizar la siguiente sintaxis al nombrar el archivo que contiene el código **assembler: ASM_name.S***

#### Assembler

```
---- Definiciones de subrutinas globales para que puedan ser accedidas desde el archivo .ino ---
.global start
.globar my_loop
------------------------------------------------------------------------------------------------

```

#### Formulas importantes

**Valor para el baudrate calculado br =**

\[
((10^6)/9600)-1 =  103
\]

#### Glosario de Mnemónicos
```
//Permite la compatibilidad entre versiones AVR anteriores

#define _SFR_OFFSET 0X00

// Permite el uso de mnemónicos como PORTB, DDRB, UCSR0A, etc

#include "avr/io.h"
```

| MNEMÓNICO | SIGNIFICADO |
|:---------:|:-----------|
| *BREQ (BRANCH IF EQUAL)* | *Rama relativa condicional. Prueba la bandera Zero (Z) y realiza una rama relativa al PC si Z está activado. Si la instrucción se ejecuta inmediatamente después de cualquiera de las instrucciones CP, CPI, SUB o SUBI, la rama ocurrirá solo si el número binario sin firmar o firmado representado en Rd es igual al número binario sin firmar o firmado representado en Rr. Esta instrucción realiza una rama relativa al PC en ambas direcciones (PC - 63 ≤ destino ≤ PC + 64). El parámetro k es el desplazamiento desde el PC y está representado en forma de complemento a dos. (Equivalente a la instrucción BRBS 1, k).*|
| *BRNE (BRANCH IF NOT EQUAL)* | *Rama relativa condicional. Prueba la bandera Zero (Z) y realiza una rama relativa al PC si Z está desactivado. Si la instrucción se ejecuta inmediatamente después de cualquiera de las instrucciones CP, CPI, SUB o SUBI, la rama ocurrirá solo si el número binario sin firmar o firmado representado en Rd no fue igual al número binario sin firmar o firmado representado en Rr. Esta instrucción realiza una rama relativa al PC en ambas direcciones (PC - 63 ≤ destino ≤ PC + 64). El parámetro k es el desplazamiento desde el PC y está representado en forma de complemento a dos. (Equivalente a la instrucción BRBC 1, k).* |
| *CBI (CLEAR BIT IN I/O REGISTER)* | *Borra un bit especificado en un Registro de Entrada/Salida (I/O). Esta instrucción opera en los 32 registros de I/O más bajos, direcciones 0-31.*|
| *CLR (CLEAR REGISTER)* | *Borra un registro. Esta instrucción realiza una operación de "Exclusive OR" (OR exclusivo) entre un registro y él mismo. Esto eliminará todos los bits en el registro. (Equivalente a la instrucción EOR Rd, rd.)* | 
| *CPI (COMPARE WITH IMMEDIATE)* | *Esta instrucción realiza una comparación entre el registro RD y una constante. El registro no se modifica. Después de esta instrucción, se pueden utilizar todas las ramas condicionales.*|
| *DDRB (DATA DIRECTION REGISTER FOR PORT B)* | *Configura la dirección de los pines del Puerto B como entradas o salidas. Si el bit correspondiente es '1', el pin se configura como salida; si es '0', se configura como entrada.* |
| *DDRD (DATA DIRECTION REGISTER FOR PORT D)* | *La abreviatura "DDRD" se compone de "DDR" (Data Direction Register) y "D" que indica el puerto específico. En detalle, el registro DDRD se utiliza para determinar si cada pin individual del puerto D será utilizado como una entrada o como una salida. Cada bit en el registro DDRD corresponde a un pin específico del puerto D, y si el bit es '1', el pin se configura como una salida, mientras que si es '0', se configura como una entrada.* |
| *JMP (JUMP)* | *Saltar a una dirección dentro de toda la memoria de programa de 4M (palabras). Esta instrucción no está disponible en todos los dispositivos.* |
| *LDI (LOAD IMMEDIATE)* | *Carga una constante de 8 bits directamente en los registros 16 a 31.*|
| *LDS (LOAD DIRECT FROM DATA SPACE)* | *Carga un byte del espacio de datos a un registro. El espacio de datos generalmente incluye el Registro de Archivos, la memoria de Entrada/Salida (I/O) y la SRAM (memoria de acceso aleatorio estática)*|
| *LPM (LOAD PROGRAM MEMORY)* | *Carga un byte apuntado por el registro Z en el registro de destino Rd. Esta instrucción presenta una inicialización constante o recuperación de datos constante 100% eficaz. La memoria de programa está organizada en palabras de 16 bits, mientras que el puntero Z es una dirección de byte. Por lo tanto, el bit menos significativo del puntero Z selecciona ya sea el byte bajo (ZLSb = 0) o el byte alto (ZLSb = 1). Esta instrucción puede direccionar los primeros 64 KB (32K palabras) de la memoria de programa. El registro del Puntero Z puede dejarse sin cambios por la operación, o puede incrementarse. La incrementación no se aplica al Registro RAMPZ.* |
| *NOP (NO OPERATION)* |*Esta instrucción realiza una operación sin operación de un solo ciclo. En otras palabras, no realiza ninguna operación significativa y se utiliza comúnmente para llenar ciclos en el programa o como un espacio reservado temporal.* |
| *RCALL (RELATIVE CALL TO SUBROUTINE)* | *Llamada relativa a una dirección dentro de PC - 2K + 1 y PC + 2K (palabras). La dirección de retorno (la instrucción después de la RCALL) se almacena en la Pila. Consulta también CALL. Para microcontroladores AVR con memoria de programa que no excede las 4K palabras (8 KB), esta instrucción puede direccionar toda la memoria desde cualquier ubicación de dirección. El Puntero de Pila utiliza un esquema de post-decremento durante RCALL.*| 
| *RET (RETURN FROM SUBROUTINE)* | *Retorna de la subrutina. La dirección de retorno se carga desde la PILA. El Puntero de Pila utiliza un esquema de preincremento durante RET.*|
| *RXEN0 (Receiver Enable 0)*| *Controla la habilitación o deshabilitación del receptor (receiving) en el canal USART 0 (UART0). Su función específica es determinar si el receptor está activado o desactivado.Cuando RXEN0 está configurado en 1, el receptor de la USART está habilitado y puede recibir datos en el puerto asociado, Esto permite al microcontrolador recibir datos desde un dispositivo externo conectado al puerto de comunicación serie.* |
| *SBIC (SKIP IF BIT IN I/O REGISTER IS CLEARED)* | *Esta instrucción prueba un solo bit en un Registro de Entrada/Salida (I/O) y omite la siguiente instrucción si el bit está desactivado. Esta instrucción opera en los 32 registros de I/O más bajos, direcciones 0-31.*|
| *SBIW (SUBTRACT IMMEDIATE FROM WORD)* |  *Resta un valor inmediato (0-63) de un par de registros y coloca el resultado en el par de registros. Esta instrucción opera en los cuatro pares de registros superiores y es adecuada para operaciones en los registros de puntero. Esta instrucción no está disponible en todos los dispositivos.*|
| *SBRS (SKIP IF BIT IN REGISTER IS SET)* | *Esta instrucción prueba un solo bit en un registro y omite la siguiente instrucción si el bit está activado.*|
| *STS (STORE DIRECT TO DATA SPACE)* | *Almacena un byte de un registro en el espacio de datos. El espacio de datos generalmente incluye el Registro de Archivos, la memoria de Entrada/Salida (I/O) y la SRAM (memoria de acceso aleatorio estática).*|
| *TXEN0 (Transmitter Enable 0)* | *Controla la habilitación o deshabilitación del transmisor (transmitting) en el canal USART 0 (UART0). Su función específica es determinar si el transmisor está activado o desactivado.  Cuando TXEN0 está configurado en 1, el transmisor de la USART está habilitado, lo que permite al microcontrolador enviar datos a través del puerto de comunicación serie asociado. Esto permite la transmisión de datos desde el microcontrolador hacia un dispositivo externo conectado al puerto de comunicación serie. Cuando TXEN0 está configurado en 0, el transmisor está desactivado y no puede enviar datos, incluso si se intenta escribir en el registro de datos de transmisión. Desactivar el transmisor puede ser útil en situaciones donde la transmisión de datos no es necesaria, y puede ayudar a reducir el consumo de energía cuando la USART no está en uso.*|
|*UBRR0H(USART BAUD RATE REGISTER 0 HIGH)* | *Almacena los bits de orden superior (bits 11 a 8) del valor del divisor de baudios. El divisor de baudios se utiliza para configurar la velocidad de transmisión y recepción de datos a través del puerto USART.* |
|*UBRR0L (USART BAUD RATE REGISTER 0 LOW)*|*Almacena los bits de orden inferior (bits 7 a 0) del valor del divisor de baudios. El divisor de baudios se utiliza para configurar la velocidad de transmisión y recepción de datos a través del puerto USART.* |
| *UCSR0A (USART CONTROL AND STATUS REGISTER 0 A)* | *Tiene la función de proporcionar información sobre el estado y la configuración de la comunicación USART en el canal 0. La función específica de cada bit puede variar según el modelo exacto del microcontrolador AVR y la configuración del modo de comunicación USART.* |
| *UCSR0B (USART CONTROL AND STATUS REGISTER 0 B)* | *Controla varios aspectos de la operación de la USART (Universal Synchronous/Asynchronous Receiver/Transmitter) en el canal 0 (UART0). Este registro permite habilitar o deshabilitar diferentes funciones de la USART y configurar la generación de interrupciones asociadas*| 
| *UCSROC (USART CONTROL AND STATUS REGISTER O C)* | *Es un registro utilizado en microcontroladores AVR para configurar varios parámetros relacionados con la comunicación USART (Universal Synchronous/Asynchronous Receiver/Transmitter) en el canal 0 (UART0). Los bits en el registro UCSR0C permiten configurar aspectos como el modo de transmisión (síncrono o asíncrono), el tamaño del marco de datos, el número de bits de parada, y la configuración del bit de paridad. La configuración de estos bits es crucial para establecer la forma en que la USART interpreta y transmite los datos.*|
| *UCSZ00 (USART CHARACTER SIZE 0)* | *Contribuye a configurar el tamaño del marco de datos y, junto con otros bits relevantes, determina cuántos bits de datos se utilizan en cada transmisión o recepción de la USART. La configuración específica de estos bits dependerá de los requisitos de la aplicación y de la cantidad de bits que se deseen utilizar.*|
| *UCSZ01 (USART CHARACTER SIZE 1)* | *Junto con otros bits configura la longitud del marco de datos para la USART. La configuración específica dependerá de los requisitos de la aplicación y de la cantidad de bits que se deseen utilizar para cada carácter en la comunicación serie.*|

**Pinout Mapping del ATMega328p**

![Pinout Mapping del ATMega328p](https://www.electroallweb.com/wp-content/uploads/2020/02/FUNCIONAMIENTO-DE-TODOS-LOS-PINES-ATMEGA328P.png)

**Pines digitales utilizados**
| Pin |
|:---:|
| 2 |
| 3 |
| 4 |
| 5 |
| 6 |
| 7 |
| 8 |

#### Referencias Bibliograficas

La práctica se baso en investigaciones anteriores. Aquí hay algunas referencias clave:

- Descrption of the Arduino 8-bit and (psuedo) 16-bit registers (https://microchipdeveloper.com/xwiki/bin/view/products/mcu-mpu/8-bit-avr/structure/gpr/)

- The ENTIRE assembler language manual(http://ww1.microchip.com/downloads/en/DeviceDoc/AVR-Instruction-Set-Manual-DS40002198A.pdf)

- ATmega168/328P-Arduino Pin Mapping (https://docs.arduino.cc/hacking/hardware/PinMapping168)



