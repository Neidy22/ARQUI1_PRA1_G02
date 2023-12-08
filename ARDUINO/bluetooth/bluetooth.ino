int led1 = '2';
int led2 = '3';
int led3 = '4';
int led4 = '5';

void setup() {
  // put your setup code here, to run once:
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(led3,OUTPUT);
  pinMode(led4,OUTPUT);
  
  Serial.begin(9600);
  Serial.println("conexion exitosa");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){

    char producto = Serial.read();

    if (producto == '1'){
      digitalWrite(led1, HIGH);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);

    }else if(producto == '2'){
      digitalWrite(led1, LOW);
      digitalWrite(led2, HIGH);
      digitalWrite(led3, LOW);
      digitalWrite(led4, LOW);

    }else if(producto == '3'){
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, HIGH);
      digitalWrite(led4, LOW);

    }else if(producto == '4'){
      digitalWrite(led1, LOW);
      digitalWrite(led2, LOW);
      digitalWrite(led3, LOW);
      digitalWrite(led4, HIGH);
    }
  }
}