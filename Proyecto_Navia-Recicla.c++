//cables que van conectados al arduino

//Definición de pines por etapa
//Mesofilia                              Definiciones:
#define PIN_TEMPERATURA_MESOFILIA A0      //Sensor de Temperatura
#define PIN_VENTILADOR_MESOFILIA 2       //Activador Sistema de Ventilación

//Termofilia                                   Definiciones:
#define PIN_TEMPERATURA_TERMOFILIA A2          //Sensor de Temperatura
#define PIN_HUMEDAD_TERMOFILIA A1             //Sensor de Humedad
#define PIN_ELECTROVALVULA_TERMOFILIA 3      //Activador Sistema de Riego
#define PIN_VENTILADOR_TERMOFILIA 4          //Activador Sistema de Ventilación

//ENFRIAMIENTO                                  SENSORES:
#define PIN_TEMPERATURA_ENFRIAMIENTO A3               //Temperatura
#define PIN_HUMEDAD_ENFRIAMIENTO A4                  //Humedad
#define PIN_ELECTROVALVULA_ENFRIAMIENTO 5           //Dispensador
#define PIN_VENTILADOR_ENFRIAMIENTO 6              //Ventilador

//Recolección                                     Definiciones:
#define PIN_TRIGGER_ULTRASONIDO_RECOLECCION 7     //Para dectectar/prender si hay algo en la trituradora
#define PIN_ECHO_ULTRASONIDO_RECOLECCION 8        //Para dectectar/apagar si no hay nada en la trituradora
#define PIN_LICUADORA_RECOLECCION 9              //es la trituradora

//SEGUNDOS EN LO QUE TARDA EN REVISAR(lo maneja por milisegundos)

unsigned long currentMillis;     //Define que estos numeros son milisegundos
unsigned long startMillis;      //inicia los milisegundos
const int INTERVALO_SENSAR_TEMPERATURA = 5000; //5 segundos
const int INTERVALO_SENSAR_HUMEDAD = 1000; //1 segundo
const float MINIMO_TEMPERATURA_MESOFILIA = 20;//0,02 segundos
const float MAXIMO_TEMPERATURA_MESOFILIA = 45;//0,045 segundos
const float MINIMO_TEMPERATURA_TERMOFILIA = 60;//0,06 segundos
const float MAXIMO_TEMPERATURA_TERMOFILIA = 70;//0,07 segundos
const float MINIMO_TEMPERATURA_ENFRIAMIENTO = 40;//0,04 segundos
const float MAXIMO_TEMPERATURA_ENFRIAMIENTO = 45;// 0,045 segundos
const float MINIMO_HUMEDAD_TERMOFILIA = 60; //0,06 segundos
const float MAXIMO_HUMEDAD_TERMOFILIA = 60; //0,06 segundos
const float MINIMO_HUMEDAD_ENFRIAMIENTO = 60;//0,06 segundos
const float MAXIMO_HUMEDAD_ENFRIAMIENTO = 60;//0,06segundos


// MESOFILIA //

int LECTURA_TEMPERATURA_MESOFILIA;            // 
float VOLTAJE_TEMPERATURA_MESOFILIA;         //  VARIABLES 
float TEMPERATURA_MESOFILIA;

// TERMOFILIA //

int LECTURA_TEMPERATURA_TERMOFILIA;
float VOLTAJE_TEMPERATURA_TERMOFILIA;
float TEMPERATURA_TERMOFILIA;               //variables
int LECTURA_HUMEDAD_TERMOFILIA;
float VOLTAJE_HUMEDAD_TERMOFILIA;
float HUMEDAD_TERMOFILIA;

// ENFRIAMIENTO //

int LECTURA_TEMPERATURA_ENFRIAMIENTO;
float VOLTAJE_TEMPERATURA_ENFRIAMIENTO;
float TEMPERATURA_ENFRIAMIENTO;
int LECTURA_HUMEDAD_ENFRIAMIENTO;         //variables
float VOLTAJE_HUMEDAD_ENFRIAMIENTO;
float HUMEDAD_ENFRIAMIENTO;

void setup()  //bucle de <
{
 Serial.begin(9600); 
 configurarPinMode(); 
 startMillis = millis(); 
}

void loop() 
{
   currentMillis = millis();
  
    //MESOFILIA

   LECTURA_TEMPERATURA_MESOFILIA = analogRead(PIN_TEMPERATURA_MESOFILIA); 
   VOLTAJE_TEMPERATURA_MESOFILIA = LECTURA_TEMPERATURA_MESOFILIA * (5.0 / 1023.0);  // TEMPERATURA EN MESOFILIA // 
   TEMPERATURA_MESOFILIA = VOLTAJE_TEMPERATURA_MESOFILIA * 100.0;

    //TERMOFILIA

  LECTURA_TEMPERATURA_TERMOFILIA = analogRead(PIN_TEMPERATURA_TERMOFILIA);
  VOLTAJE_TEMPERATURA_TERMOFILIA = LECTURA_TEMPERATURA_TERMOFILIA * (5.0 / 1023.0); // temperatura termofilia //
  TEMPERATURA_TERMOFILIA = VOLTAJE_TEMPERATURA_TERMOFILIA * 100.0;
  LECTURA_HUMEDAD_TERMOFILIA = analogRead(PIN_HUMEDAD_TERMOFILIA);
  VOLTAJE_HUMEDAD_TERMOFILIA = LECTURA_HUMEDAD_TERMOFILIA * (5.0 / 1023.0);  //humedad termofilia //
  HUMEDAD_TERMOFILIA = (VOLTAJE_HUMEDAD_TERMOFILIA - 0.8) * (100.0 / 3.4);

  //ENFRIAMIENTO

  LECTURA_TEMPERATURA_ENFRIAMIENTO = analogRead(PIN_TEMPERATURA_ENFRIAMIENTO);
  VOLTAJE_TEMPERATURA_ENFRIAMIENTO = LECTURA_TEMPERATURA_ENFRIAMIENTO * (5.0 / 1023.0); // enfriamiento tempertura //
  TEMPERATURA_ENFRIAMIENTO = VOLTAJE_TEMPERATURA_ENFRIAMIENTO * 100.0;
  LECTURA_HUMEDAD_ENFRIAMIENTO = analogRead(PIN_HUMEDAD_ENFRIAMIENTO);
  VOLTAJE_HUMEDAD_ENFRIAMIENTO = LECTURA_HUMEDAD_ENFRIAMIENTO * (5.0 / 1023.0); // humedad enfriamiento
  HUMEDAD_ENFRIAMIENTO = (VOLTAJE_HUMEDAD_ENFRIAMIENTO - 0.8) * (100.0 / 3.4);
  
  // lectura sensores // 
   
  // MESOFILIA //
  
  controlTemperatura(INTERVALO_SENSAR_TEMPERATURA,TEMPERATURA_MESOFILIA,MAXIMO_TEMPERATURA_MESOFILIA,MINIMO_TEMPERATURA_MESOFILIA,PIN_VENTILADOR_MESOFILIA);

  // TERMOFILIA //
  
  controlTemperatura(INTERVALO_SENSAR_TEMPERATURA,TEMPERATURA_TERMOFILIA,MAXIMO_TEMPERATURA_TERMOFILIA,MINIMO_TEMPERATURA_TERMOFILIA,PIN_VENTILADOR_TERMOFILIA);
  
  controlHumedad(INTERVALO_SENSAR_HUMEDAD,HUMEDAD_TERMOFILIA,MAXIMO_HUMEDAD_TERMOFILIA,MINIMO_HUMEDAD_TERMOFILIA,PIN_ELECTROVALVULA_TERMOFILIA);

  // ENFRIAMIENTO //
  
  controlTemperatura(INTERVALO_SENSAR_TEMPERATURA,TEMPERATURA_ENFRIAMIENTO,MAXIMO_TEMPERATURA_ENFRIAMIENTO,MINIMO_TEMPERATURA_ENFRIAMIENTO,PIN_VENTILADOR_ENFRIAMIENTO);

  //MADURACIÒN//

  controlHumedad(INTERVALO_SENSAR_HUMEDAD,HUMEDAD_ENFRIAMIENTO,MAXIMO_HUMEDAD_ENFRIAMIENTO,MINIMO_HUMEDAD_ENFRIAMIENTO,PIN_ELECTROVALVULA_ENFRIAMIENTO);
} 
// DEFINICIONES DE ENTRADA Y SALIDA
void configurarPinMode() {
  pinMode(PIN_TEMPERATURA_MESOFILIA, INPUT);
  pinMode(PIN_VENTILADOR_MESOFILIA, OUTPUT);
  pinMode(PIN_TEMPERATURA_TERMOFILIA, INPUT);
  pinMode(PIN_HUMEDAD_TERMOFILIA, INPUT);
  pinMode(PIN_ELECTROVALVULA_TERMOFILIA, OUTPUT);
  pinMode(PIN_VENTILADOR_TERMOFILIA, OUTPUT);
  pinMode(PIN_TEMPERATURA_ENFRIAMIENTO, INPUT);
  pinMode(PIN_HUMEDAD_ENFRIAMIENTO, INPUT);    
  pinMode(PIN_ELECTROVALVULA_ENFRIAMIENTO, OUTPUT);
  pinMode(PIN_VENTILADOR_ENFRIAMIENTO, OUTPUT);
  pinMode(PIN_TRIGGER_ULTRASONIDO_RECOLECCION, OUTPUT);
  pinMode(PIN_ECHO_ULTRASONIDO_RECOLECCION, INPUT);
  pinMode(PIN_LICUADORA_RECOLECCION, OUTPUT);
}
//INTENGRA TODO LO ANTERIOR PARA HACERLO 1 SOLO EN TEMPERATURA Y MANDARLO A LA PLACA O AL ARDUINO
void controlTemperatura(int intervalo, float valorSensado, float rangoMaximo, float rangoMinimo, uint8_t pin) { 
 if (valorSensado > rangoMaximo && (currentMillis - startMillis >= intervalo)) {
    digitalWrite(pin, HIGH); 
    startMillis = currentMillis;  
  } else if (valorSensado <= rangoMinimo) { 
    digitalWrite(pin, LOW); 
  }
}
// LO MISMO DE ARRIBA PERO CON HUMEDAD
void controlHumedad(int intervalo, float valorSensado, float rangoMaximo, float rangoMinimo, uint8_t pin){
 if (valorSensado < rangoMinimo && (currentMillis - startMillis >= intervalo)) {
    digitalWrite(pin, HIGH); 
    startMillis = currentMillis;  
  } else if (valorSensado >= rangoMaximo) { 
    digitalWrite(pin, LOW);
  } 
}
