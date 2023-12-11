#include <Stepper.h>
//VELOCIDAD MOTOR
double stepsPerRevolution = 2048;

//pines de sensor
int trigPin = A5;
int echoPin = A4;

//pines motor1
Stepper motor1(stepsPerRevolution, 22, 24, 23, 25);

//pines motor2
Stepper motor2(stepsPerRevolution, 26, 28, 27, 29);

//pines motor3
Stepper motor3(stepsPerRevolution, 30, 32, 31, 33);

//pines de leds
int led1 = 2;
int led2 = 3;
int led3 = 4;

bool ocupado = true;
int maquina = 1;
bool freno = true;

void setup() {
  Serial.begin(9600);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  motor1.setSpeed(10);
  motor2.setSpeed(10);
  motor3.setSpeed(10);

  digitalWrite(trigPin, LOW);
}

void loop() {
  if (Serial.available() > 0) {
    char producto = Serial.read();
    elegirProducto(producto);
  }
}

void elegirProducto(char producto) {
  ocupado = true;
  if (producto == '1') {
        maquina = 0;
        while (ocupado) {
          motor1.step(stepsPerRevolution);
          sacarDulce();
        }
        if (!ocupado) {
          Serial.println("0");
        }
      } else if (producto == '2') {
        while (ocupado) {
          motor2.step(stepsPerRevolution);
          sacarDulce();
        }
        if (!ocupado) {
          Serial.println(0);
        }
      } else if (producto == '3') {
        while (ocupado) {
          motor3.step(stepsPerRevolution);
          sacarDulce();
        }
        if (!ocupado) {
          Serial.println(0);
          }
      }
}

void sacarDulce() {
  bool entregado = detectarProducto();
  if (entregado) {
    ocupado = false;
    maquina = 1;
  }
}

bool detectarProducto() {
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

  if (dl <= 7) {
    detectado = true;
  }

  return detectado;
}