//pines de sensor
int trigPin = A5;
int echoPin = A4;

//pines motor1
int pin1M1 = 22;
int pin2M1 = 23;
int pin3M1 = 24;
int pin4M1 = 25;

//pines motor2
int pin1M2 = 26;
int pin2M2 = 27;
int pin3M2 = 28;
int pin4M2 = 29;

//pines motor3
int pin1M3 = 30;
int pin2M3 = 31;
int pin3M3 = 32;
int pin4M3 = 33;

//pines de leds
int led1 = 2;
int led2 = 3;
int led3 = 4;

//encolamiento
int queue[7];
int queueHead = 0;
int queueHead2 = 0;
bool ocupado = true;
int estado_cola = 0;

int estadoMaquina = 1;  // 0 = despachando, 1 = disponible, 2 = error sin stock
int contCola = 0;

//productos
int stockProducto1 = 3;
float precioProducto1 = 1.50;
float montoProducto1 = 0;

int stockProducto2 = 3;
float montoProducto2 = 0;
float precioProducto2 = 2.00;

int stockProducto3 = 3;
float montoProducto3 = 0;
float precioProducto3 = 2.50;

int stockTotal = 9;
float montoTotal = 0;

int productosEncolados = 0;

String salida = "";

void sendOutput(int id) {
  salida = "";
  salida.concat(estadoMaquina);
  salida.concat("-");
  salida.concat(id);
  salida.concat(";");
  salida.concat(stockProducto1);
  salida.concat(";");
  salida.concat(montoProducto1);
  salida.concat(";");
  salida.concat(stockProducto2);
  salida.concat(";");
  salida.concat(montoProducto2);
  salida.concat(";");
  salida.concat(stockProducto3);
  salida.concat(";");
  salida.concat(montoProducto3);
  salida.concat(";");
  salida.concat(stockTotal);
  salida.concat(";");
  salida.concat(montoTotal);
  salida.concat(";");
  salida.concat(productosEncolados);
  Serial.println(salida);
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  pinMode(pin1M1, OUTPUT);
  pinMode(pin2M1, OUTPUT);
  pinMode(pin3M1, OUTPUT);
  pinMode(pin4M1, OUTPUT);

  pinMode(pin1M2, OUTPUT);
  pinMode(pin2M2, OUTPUT);
  pinMode(pin3M2, OUTPUT);
  pinMode(pin4M2, OUTPUT);

  pinMode(pin1M3, OUTPUT);
  pinMode(pin2M3, OUTPUT);
  pinMode(pin3M3, OUTPUT);
  pinMode(pin4M3, OUTPUT);

  digitalWrite(trigPin, LOW);
}

void loop() {
  // Revisa si hay habilitado la conexión a bluetooth
  if (Serial.available() > 0) {
    char producto = Serial.read();
    if (estadoMaquina == 1) {
      elegirProducto(producto);
    } else if (estadoMaquina == 0) {
      productosEncolados = productosEncolados + 1;
      enqueue(producto);
    }
  }
}

void elegirProducto(char producto) {
  // Metodo Prod 1
  if (producto == '1') {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    //verificar el estado de la máquina, existencia producto 1, y sin producto encolado
    if (estadoMaquina == 1 && stockProducto1 > 0) {
      //mandar señal de despacho a la máquina

      estadoMaquina = 0;  // maquina despachando

      // actualizar stocks
      stockProducto1 = stockProducto1 - 1;
      stockTotal = stockTotal - 1;

      // actualizar montos
      montoProducto1 = montoProducto1 + precioProducto1;
      montoTotal = montoTotal + precioProducto1;

      sendOutput(1);
      while (ocupado) {
        moverProd1();
        sacarDulce();
      }
      if (ocupado == false) {
        estado_cola = estado_cola + 1;
        productosEncolados = productosEncolados - 1;
        elegirProducto(queue[estado_cola - 1]);
      }

    } else if (estadoMaquina == 0) {
      productosEncolados = productosEncolados + 1;
      sendOutput(1);
    }
  } else if (producto == '2') {  // Metodo Prod 2
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);

    //verificar el estado de la máquina, existencia producto 2, y sin producto encolado
    if (estadoMaquina == 1 && stockProducto2 > 0) {
      //mandar señal de despacho a la máquina

      estadoMaquina = 0;  // maquina despachando

      // actualizar stocks
      stockProducto2 = stockProducto2 - 1;
      stockTotal = stockTotal - 1;

      // actualizar montos
      montoProducto2 = montoProducto2 + precioProducto2;
      montoTotal = montoTotal + precioProducto2;

      sendOutput(2);
      while (ocupado) {
        moverProd2();
        sacarDulce();
      }
      if (ocupado == false) {
        estado_cola = estado_cola + 1;
        productosEncolados = productosEncolados - 1;
        elegirProducto(queue[estado_cola - 1]);
      }
    } else if (estadoMaquina == 0) {
      productosEncolados = productosEncolados + 1;
      sendOutput(2);
    }

  } else if (producto == '3') {  // Metodo Prod 3
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);

    //verificar el estado de la máquina, existencia producto 3, y sin producto encolado
    if (estadoMaquina == 1 && stockProducto3 > 0) {
      //mandar señal de despacho a la máquina

      estadoMaquina = 0;  // maquina despachando

      // actualizar stocks
      stockProducto3 = stockProducto3 - 1;
      stockTotal = stockTotal - 1;

      // actualizar montos
      montoProducto3 = montoProducto3 + precioProducto3;
      montoTotal = montoTotal + precioProducto3;

      sendOutput(3);
      while (ocupado) {
        moverProd3();
        sacarDulce();
      }
      if (ocupado == false) {
        estado_cola = estado_cola + 1;
        productosEncolados = productosEncolados - 1;
        elegirProducto(queue[estado_cola - 1]);
      }
    } else if (estadoMaquina == 0) {
      productosEncolados = productosEncolados + 1;
      sendOutput(3);
    }
  }
}

void moverProd1() {
  digitalWrite(pin1M1, HIGH);
  digitalWrite(pin2M1, LOW);
  digitalWrite(pin3M1, LOW);
  digitalWrite(pin4M1, LOW);
  delay(150);
  digitalWrite(pin1M1, LOW);
  digitalWrite(pin2M1, HIGH);
  digitalWrite(pin3M1, LOW);
  digitalWrite(pin4M1, LOW);
  delay(150);
  digitalWrite(pin1M1, LOW);
  digitalWrite(pin2M1, LOW);
  digitalWrite(pin3M1, HIGH);
  digitalWrite(pin4M1, LOW);
  delay(150);
  digitalWrite(pin1M1, LOW);
  digitalWrite(pin2M1, LOW);
  digitalWrite(pin3M1, LOW);
  digitalWrite(pin4M1, HIGH);
  delay(150);
}

void moverProd2() {
  digitalWrite(pin1M2, HIGH);
  digitalWrite(pin2M2, LOW);
  digitalWrite(pin3M2, LOW);
  digitalWrite(pin4M2, LOW);
  delay(150);
  digitalWrite(pin1M2, LOW);
  digitalWrite(pin2M2, HIGH);
  digitalWrite(pin3M2, LOW);
  digitalWrite(pin4M2, LOW);
  delay(150);
  digitalWrite(pin1M2, LOW);
  digitalWrite(pin2M2, LOW);
  digitalWrite(pin3M2, HIGH);
  digitalWrite(pin4M2, LOW);
  delay(150);
  digitalWrite(pin1M2, LOW);
  digitalWrite(pin2M2, LOW);
  digitalWrite(pin3M2, LOW);
  digitalWrite(pin4M2, HIGH);
  delay(150);
}

void moverProd3() {
  digitalWrite(pin1M3, HIGH);
  digitalWrite(pin2M3, LOW);
  digitalWrite(pin3M3, LOW);
  digitalWrite(pin4M3, LOW);
  delay(150);
  digitalWrite(pin1M3, LOW);
  digitalWrite(pin2M3, HIGH);
  digitalWrite(pin3M3, LOW);
  digitalWrite(pin4M3, LOW);
  delay(150);
  digitalWrite(pin1M3, LOW);
  digitalWrite(pin2M3, LOW);
  digitalWrite(pin3M3, HIGH);
  digitalWrite(pin4M3, LOW);
  delay(150);
  digitalWrite(pin1M3, LOW);
  digitalWrite(pin2M3, LOW);
  digitalWrite(pin3M3, LOW);
  digitalWrite(pin4M3, HIGH);
  delay(150);
}
// aqui valida el movimiento
void sacarDulce() {
  if (estado_cola < 8) {

    estadoMaquina = 0;

    //validar cuando el producto sea entregado
    bool entregado = detectarProducto();

    if (entregado) {
      ocupado = false;
      estadoMaquina = 1;
    }
  }
}

// se encola el producto
void enqueue(int Valor){
  queue[contCola] = Valor;
  contCola = contCola + 1;
}

// función del sensor
bool detectarProducto(){
  bool detectado = false;
  long time;
  long distance;
  long dl;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  time = pulseIn(echoPin, HIGH);
  distance = (time / 59);
  dl = distance / 3;

  if (dl <= 5) {
    detectado = true;
  }

  return detectado;
}