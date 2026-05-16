#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 6, 8, 9);

const int pinLM35 = A0;
const int pinLedAzul = 2;
const int pinLedVerde = 4;
const int pinLedRojo = 7;

const float tempFriaMax = 20.0;
const float tempCalienteMin = 30.0;

unsigned long tiempoAnterior = 0;
const long intervaloLectura = 500; 

void setup() {
  Serial.begin(9600);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
  
  configurarPines();
}


void loop() {
  unsigned long tiempoActual = millis();

  if (tiempoActual < 1000) {
    return; 
  }

  if (tiempoActual - tiempoAnterior >= intervaloLectura) {
    tiempoAnterior = tiempoActual; 

    float temperatura = leerTemperatura();
    
    controlarIndicadores(temperatura);
    actualizarLCD(temperatura);
  }
}


void configurarPines() {
  pinMode(pinLedAzul, OUTPUT);
  pinMode(pinLedVerde, OUTPUT);
  pinMode(pinLedRojo, OUTPUT);
}

float leerTemperatura() {
  int lecturaAnalogica = analogRead(pinLM35);

  float voltaje = (lecturaAnalogica * 5.0) / 1024.0;
  float temperaturaCelsius = voltaje * 100.0; 

  return temperaturaCelsius;
}

void controlarIndicadores(float temp) {

  digitalWrite(pinLedAzul, LOW);
  digitalWrite(pinLedVerde, LOW);
  digitalWrite(pinLedRojo, LOW);


  if (temp < tempFriaMax) {
    digitalWrite(pinLedAzul, HIGH);
  } 
  else if (temp >= tempFriaMax && temp < tempCalienteMin) {
    digitalWrite(pinLedVerde, HIGH);
  } 
  else {
    digitalWrite(pinLedRojo, HIGH);
  }
}

void actualizarLCD(float temp) {
  // Fila 0: Mostramos la temperatura actual
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temp, 1);  
  lcd.print(" C    "); // Espacios para limpiar caracteres residuales

  // Fila 1: Mostramos Modo y Rango (Máximo 16 caracteres)
  lcd.setCursor(0, 1); 
  
  if (temp < tempFriaMax) {
    // Imprime: "Frio (<20C)     "
    lcd.print("Frio (<");
    lcd.print(tempFriaMax, 0); // El '0' quita los decimales para ahorrar espacio
    lcd.print("C)     ");      // 5 espacios al final para borrar residuos
  } 
  else if (temp >= tempFriaMax && temp < tempCalienteMin) {
    // Imprime: "Norm (20-30C)   "
    lcd.print("Norm (");
    lcd.print(tempFriaMax, 0);
    lcd.print("-");
    lcd.print(tempCalienteMin, 0);
    lcd.print("C)   ");        // 3 espacios al final
  } 
  else {
    // Imprime: "Alto (>=30C)    "
    lcd.print("Alto (>=");
    lcd.print(tempCalienteMin, 0);
    lcd.print("C)    ");       // 4 espacios al final
  }
}