// P1 - Anemometro
// Lucas Pandian, Eduardo, Daniel Hideo, Lucas Mateus, Bernardo, Enrico.
// 27/09/2023
// 1.0

//definição das portas e estados de cada item a ser usado

// --- Constantes ---
const float pi = 3.14159265;     //Número de pi
int period = 5000;               //Tempo de medida(miliseconds)
int delaytime = 1000;            //Invervalo entre as amostras (miliseconds)
int radius = 147;                //Raio do anemometro(mm)

int pin=A2;
float valor =0;
int Winddir =0;
String direcao;

// --- Variáveis Globais ---
unsigned int Sample  = 0;        //Armazena o número de amostras
unsigned int counter = 0;        //Contador para o sensor  
unsigned int RPM = 0;            //Rotações por minuto
float speedwind = 0;             //Velocidade do vento (m/s)
float windspeed = 0;             //Velocidade do vento (km/h)


void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);        //configura o digital 2 como entrada
  digitalWrite(2, HIGH);    //internall pull-up active
    
   
  Serial.begin(9600);       //inicia serial em 9600 baud rate
}

void loop() {
    
  valor = analogRead(pin)* (5.0 / 1023.0);
  
  Serial.print("leitura do sensor :");
  Serial.print(valor);
  Serial.println(" volt");

  if (valor <= 0.27) {
  Winddir = 315;
  direcao = "Noroeste";
  }
  else if (valor <= 0.32) { 
  Winddir = 270;
  direcao = "Oeste";
  }
  else if (valor <= 0.38) { 
  Winddir = 225;
  direcao = "Sudoeste";
  }
  else if (valor <= 0.45) { 
  Winddir = 180;
  direcao = "Sul";
  }
  else if (valor <= 0.57) { 
  Winddir = 135;
  direcao = "Sudeste";
  }
  else if (valor <= 0.75) { 
  Winddir = 90;
  direcao = "Leste";
  }
  else if (valor <= 1.25) {  
  Winddir = 45;
  direcao = "Nordeste";
  }
  else {  
  Winddir = 000;
  direcao = "Norte";
  }
  Serial.print("Direção: ");
  Serial.print(direcao);
  Serial.print(" / ");
  Serial.print(Winddir);
  Serial.println(" graus");
  
  Serial.println("\n");
  delay (1000);

    Sample++;
    Serial.print(Sample);
    Serial.print(": Inicio da medição... ");
    windvelocity();
    Serial.println("   fim.");
    Serial.print("Counter: ");
    Serial.print(counter);
    Serial.print("\nRPM: ");
    RPMcalc();
    Serial.print(RPM);
    Serial.println("\nVelocidade do vento: ");
    
  //*****************************************************************
  //print m/s  
    WindSpeed();
    Serial.print(windspeed);
    Serial.println(" [m/s] ");              
    
  //*****************************************************************
  //print km/h  
    SpeedWind();
    Serial.print(speedwind);
    Serial.print(" [km/h] ");  
    Serial.println();


    delay(delaytime);    //taxa de atualização
}

//Função para medir velocidade do vento
void windvelocity()
{
  speedwind = 0;
  windspeed = 0;
  
  counter = 0;  
  attachInterrupt(0, addcount, RISING);
  unsigned long millis();       
  long startTime = millis();
  while(millis() < startTime + period) {}
}


//Função para calcular o RPM
void RPMcalc()
{
  RPM=((counter)*60)/(period/1000);  // Calculate revolutions per minute (RPM)
}


//Velocidade do vento em m/s
void WindSpeed()
{
  windspeed = ((4 * pi * radius * RPM)/60) / 1000;  //Calcula a velocidade do vento em m/s
 
} //end WindSpeed


//Velocidade do vento em km/h
void SpeedWind()
{
  speedwind = (((4 * pi * radius * RPM)/60) / 1000)*3.6;  //Calcula velocidade do vento em km/h
 
} //end SpeedWind


//Incrementa contador
void addcount()
{
  counter++;
} 
