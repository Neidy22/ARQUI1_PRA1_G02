int led1 = 2;
int led2 = 3;
int led3 = 4;
const int maxCola = 100;
int queue[maxCola];
int queueHead = 0;
int queueHead2 = 0;


int estadoMaquina = 1;  // 0 = despachando, 1 = disponible, 2 = error sin stock

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
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  Serial.begin(9600);
  Serial.println("conexion exitosa");
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Serial.available() > 0) {
    char producto = Serial.read();
    if(estadoMaquina == 1){
      elegirProducto(producto);
    }else if (estadoMaquina == 0) {
      productosEncolados = productosEncolados + 1;
      enqueue(producto);
      sendOutput(3);
    }
  }
}  

void elegirProducto(char producto){
  if (producto == '1') {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
     

    //verificar el estado de la máquina, existencia producto 1, y sin producto encolado
    if ((estadoMaquina == 1 && stockProducto1 > 0) && productosEncolados == 0) {
      //mandar señal de despacho a la máquina

      estadoMaquina = 0;  // maquina despachando

        // actualizar stocks
      stockProducto1 = stockProducto1 - 1;
      stockTotal = stockTotal - 1;

       // actualizar montos
      montoProducto1 = montoProducto1 + precioProducto1;
      montoTotal = montoTotal + precioProducto1;

      sendOutput(1);

        // sensor debe detectar cuando se retira el producto para cambiar el estado de la máquina a disponible de nuevo

    } else if (estadoMaquina == 0) {
      productosEncolados = productosEncolados + 1;
      sendOutput(1);
    }
  }else if (producto == '2') {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);

            //verificar el estado de la máquina, existencia producto 1, y sin producto encolado
    if ((estadoMaquina == 1 && stockProducto2 > 0) && productosEncolados == 0) {
      //mandar señal de despacho a la máquina

      estadoMaquina = 0;  // maquina despachando

        // actualizar stocks
      stockProducto2 = stockProducto2 - 1;
      stockTotal = stockTotal - 1;

        // actualizar montos
      montoProducto2 = montoProducto2 + precioProducto2;
      montoTotal = montoTotal + precioProducto2;

      sendOutput(2);

        // sensor debe detectar cuando se retira el producto para cambiar el estado de la máquina a disponible de nuevo

    } else if (estadoMaquina == 0) {
      productosEncolados = productosEncolados + 1;
      sendOutput(1);
    }

  }else if (producto == '3') {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
     
    char producto = Serial.read();

      //verificar el estado de la máquina, existencia producto 1, y sin producto encolado
    if ((estadoMaquina == 1 && stockProducto3 > 0) && productosEncolados == 0) {
        //mandar señal de despacho a la máquina

      estadoMaquina = 0;  // maquina despachando

        // actualizar stocks
      stockProducto3 = stockProducto3 - 1;
      stockTotal = stockTotal - 1;

        // actualizar montos
      montoProducto3 = montoProducto3 + precioProducto3;
      montoTotal = montoTotal + precioProducto3;

      sendOutput(1);

        // sensor debe detectar cuando se retira el producto para cambiar el estado de la máquina a disponible de nuevo
    }  
  } 
}

//Agregar los elementos a la cola
void enqueue(int Valor){
  if (((queueHead2 + 1) % maxCola) == queueHead){
      Serial.println("La cola esta llena");
  }else{
    queue[queueHead2] = Valor;
    queueHead2 = (queueHead2 + 1) % maxCola;
  } 
}

//Eliminar los elementos de la cola de espera
void dequeue(){
  if(queueHead == queueHead2){
    Serial.println("se termino la lista de espera");
  }else{
    //Eliminar el elemento de la cabeza de la cola
    int removerValor = queue[queueHead];
    queueHead  = (queueHead + 1) % maxCola;
  }
}

//Despachar los productos e irlos eliminando de la lista
void printQueue(){
    int i = queueHead;
    while(i!= queueHead2){
      if (productosEncolados > 0){
        productosEncolados = productosEncolados - 1;
      }
      elegirProducto(queue[i]);
      dequeue();
      elegirProducto(queue[i]);
      
      i = (i + 1)% maxCola;
    }
}