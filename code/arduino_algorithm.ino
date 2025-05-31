// 1
//VARIABLES INICIALES

const int Triggerf = 12;
const int Echof = 13;

const int Triggerd = 8; 
const int Echod = 9;
         
const int Triggeri = 7; 
const int Echoi = 6; 

int sensortemp;

const int MotorI = 10; 
const int in1 = 2; 
const int in2 = 3; 

const int MotorD = 11; 
const int in3 = 4; 
const int in4 = 5; 
//FUNCION PRINCIPAL, SE EJECUTA UNA VEZ
void setup()
{
  Serial.begin(9600);
//CONFIGURACION DE PINES COMO SALIDA O ENTRADA  
  pinMode(Triggerf, OUTPUT); 
  pinMode(Echof, INPUT);
  pinMode(Triggerd, OUTPUT);
  pinMode(Echod, INPUT); 
  pinMode(Triggeri, OUTPUT); 
  pinMode(Echoi, INPUT); 
  pinMode(MotorI, OUTPUT); 
  pinMode(MotorD, OUTPUT); 
  pinMode(in1, OUTPUT); pinMode(in2, OUTPUT); 
  pinMode(in3, OUTPUT); pinMode(in4, OUTPUT); 
  pinMode(A4, OUTPUT); 
  //ESTADO INICIAL DE LOS MOTORES
  analogWrite(MotorI, 0); analogWrite(MotorD, 0);
  
  digitalWrite(in1, LOW); digitalWrite(in2, LOW);
  digitalWrite(in3, LOW); digitalWrite(in4, LOW);
}
/*FUNCIONES DE SENSORES ULTRASONICOS
  FUNCIONES LONG
  LONG USADO PARA VALORES MAYORES A 32 bits
*/
//2
long sensorfrontal()
{
 //VARIABLES DE DISTANCIA Y TIEMPO
  long distanciaf; 
  long tiempof;
  
 //CALCULOS DE DISTANCIA Y TIEMPO
  digitalWrite(Triggerf, LOW);
  delayMicroseconds(2);
  digitalWrite(Triggerf, HIGH);
  delayMicroseconds(10);
  digitalWrite(Triggerf, LOW);
  tiempof = pulseIn(Echof, HIGH);
  distanciaf = tiempof/59;
  
  //EN CASO DE QUE EL SENSOR NO EMITA ONDAS ULTRASONICAS
  if (tiempof == 0)
  {
    Serial.println("Sensor frontal, sin eco...");
    return -1;
  }
  //DEVUELVE LA DISTANCIA CADA 1 SEGUNDO (1000ms)
  Serial.print("Distancia: "); 
  Serial.print(distanciaf);
  Serial.print("cm.");
  Serial.println();
  delay(1000);
  
  return distanciaf;
}

long sensorderecho()
{
  long distanciad;
  long tiempod;
  
  digitalWrite(Triggerd, LOW);
  delayMicroseconds(2);
  digitalWrite(Triggerd, HIGH);
  delayMicroseconds(10);
  digitalWrite(Triggerd, LOW);
  tiempod = pulseIn(Echod, HIGH);
  
  distanciad = tiempod/59;
  
  if (tiempod == 0)
  {
    Serial.println("Sensor Derecho - Sin eco...");
    return -1;               
  }
  return distanciad;
}
// 3
long sensorizquierdo()
{
    long distanciai;
    long tiempoi;
  
    digitalWrite(Triggeri, LOW);
    delayMicroseconds(2);
    digitalWrite(Triggeri, HIGH);
    delayMicroseconds(10);
    digitalWrite(Triggeri, LOW);
    tiempoi = pulseIn(Echoi, HIGH);
    distanciai = tiempoi/59;
  
    if (tiempoi == 0)
    {
      Serial.println("Sensor Izquierdo, sin eco...");
      return -1;
    }
    return distanciai;
}
//VARIABLE SENSOR TEMPERATURA
//INDICA SOBRECALENTAMIENTO EN COMPONENTES O CERCA DEL VEHICULO

void temperatura()
{
  //VARIABLES TEMPERATURAS
  int ledrojo = analogRead(A4);
  sensortemp  = analogRead(A5);
  float temp  = (sensortemp - 20) / 8.45;
  
  //CONDICION ACTIVACION DE LED E IMPRESIÓN DE RESULTADOS
  if (temp > 30 || temp < 10)
  {
  digitalWrite(A4, HIGH);
  delay(500);
  digitalWrite(A4, LOW);
  Serial.println("Cuidado la temperatura no es adecuada: ");
  Serial.println("Temperatura: ");
  Serial.print(temp);
  Serial.println(" C");
  Serial.println("-----------------");
  }
  else
  {
  digitalWrite(A4, LOW);
  }
 //FUNCIONES DE CONTROL DE MOVIMIENTO DEL VEHICULO
 //DIGITAL WRITE PARA ACTIVACION O DESACTIVACION DE MOTORES
 //ANALOG WRITE PARA VELOCIDAD DE MOTORES
 //USO DE PINES PWM 
}

void avanzar()
{
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(MotorI, 255); analogWrite(MotorD, 255);
}

void retroceder()
{
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(MotorI, 150); analogWrite(MotorD, 150);
}
void girareje()
{
  digitalWrite(in1, HIGH); digitalWrite(in2,LOW);
  digitalWrite(in3, LOW);  digitalWrite(in4, HIGH);
  analogWrite(MotorI, 100); analogWrite(MotorD, 100);
}

void frenar()
{
  analogWrite(MotorI, 0); analogWrite(MotorD, 0);
}
void apagar_motores()
{
  digitalWrite(in1, LOW); digitalWrite(in2,LOW);
  digitalWrite(in3, LOW);  digitalWrite(in4, LOW);
  analogWrite(MotorI, 0); analogWrite(MotorD, 0);
}
void girarderecha()
{
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(MotorI, 230); analogWrite(MotorD, 150);
}
void girarizquierda()
{
  digitalWrite(in1, HIGH); digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH); digitalWrite(in4, LOW);
  analogWrite(MotorI, 150); analogWrite(MotorD, 230);
}
void retrocederizquierda(){
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH); 
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(MotorI, 100); analogWrite(MotorD, 150);
}
  
void retrocederderecha(){
  digitalWrite(in1, LOW); digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW); digitalWrite(in4, HIGH);
  analogWrite(MotorI, 150); analogWrite(MotorD, 100);
}

//CICLO FUNCIONAL DEL ALGORITMO
void loop()
{
  //SE INICIALIZAN LAS FUNCIONES DE LOS SENSORES 
  temperatura(); 
  long distanciaf = sensorfrontal(); 
  long distanciad = sensorderecho();
  long distanciai = sensorizquierdo();
  
  //SE LLAMA CADA FUNCION CREADA DEPENDIENDO DE LA CONDICION
  //DEPENDIENDO DE LA DISTANCIA DE CADA SENSOR SE TOMA UNA DECISION DIFERENTE
  
  //AVANZAR SI NO HAY OBSTACULOS
  if (distanciaf > 50 && distanciad > 50 && distanciai > 50)  //cambiar el orden
  {
    avanzar();
    Serial.println("Avanzando");
  }
  
  //APAGARSE SI LOS SENSORES DETECTAN OBSTACULOS DEMASIADO CERCA
  else if (distanciaf < 5 && distanciad < 5 && distanciai < 5)
  {
  apagar_motores();
  Serial.println("Apagando motores");
  }
  
  //FRENAR SI SE DETECTAN OBSTACULOS PARA LUEGO TOMAR OTRA DECISION
  else if (distanciaf < 10 && distanciad < 10 && distanciai < 10)
  {
    frenar(); //solo frena, no se apaga, cuando ya no hay espacio
    Serial.println("Frenando");
  }
  //RETROCEDER AL TENER UN OBSTACULO AL FRENTE
  else if (distanciaf < 15 && distanciad < 15 && distanciai < 15)
  {
    retroceder(); //si queda atrapado en paredes tipo "U", pero aun hay espacio para salir
    Serial.println("Retrocediendo");
  }
  //ROTAR SI SE ENCUENTRA ENTRE MEDIO DE OBSTACULOS
  else if (distanciaf < 50 && distanciai < 50 && distanciad < 50)
  {
    girareje(); 
    Serial.println("Rotando"); //hasta que no se cumpla una de las condiciones
  }  
  //RETROCEDER A LA IZQUIERDA
  else if (distanciaf < 50 && distanciai < 50 && distanciad > 50)
  {
    retrocederizquierda();
    Serial.println("Retrocediendo a la izquierda");
  }  
  //RETROCEDER A LA DERECHA
  else if (distanciaf < 50 && distanciai > 50 && distanciad < 50)
  {
    retrocederderecha();
    Serial.println("Retrocediendo a la derecha");
  }  
  //EVADIR OBSTACULOS GIRANDO A LA IZQUIERDA
  else if (distanciai > distanciad)
  {
    girarizquierda();
    Serial.println("Girando a la izquierda");
  }   
  //EVADIR OBSTACULOS GIRANDO A LA DERECHA
  else if (distanciad > distanciai)
  {
    girarderecha();
    Serial.println("Girando a la derecha");
  }
  //IMPRESIÓN DE RESULTADOS: TEMPERATURA Y PROXIMIDAD
  Serial.println("-----------------"); //separa cada intervalo
  delay(500);
}