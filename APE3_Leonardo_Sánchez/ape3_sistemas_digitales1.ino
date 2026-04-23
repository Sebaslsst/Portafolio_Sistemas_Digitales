// Estructura
struct Canal {
  bool estadoActual = LOW;
  bool estadoAnterior = LOW;
  unsigned long tiempoAnterior = 0;
  unsigned long periodo = 0;
  unsigned long tHigh = 0;
  unsigned long tLow = 0;
  unsigned long tiempoCambio = 0;
  float frecuencia = 0;
  float duty = 0;
};

// Prototipos
void procesarCanal(int pin, Canal &ch, unsigned long tiempoActual);
void calcular(Canal &ch);
void imprimir(unsigned long tiempoActual);
void graficar();

// Pines
const int canal1 = 2;
const int canal2 = 3;

Canal ch1, ch2;
unsigned long ultimoPrint = 0;

void setup() {
  pinMode(canal1, INPUT);
  pinMode(canal2, INPUT);
  Serial.begin(9600);
}

void loop() {
  unsigned long tiempoActual = millis();

  procesarCanal(canal1, ch1, tiempoActual);
  procesarCanal(canal2, ch2, tiempoActual);

  calcular(ch1);
  calcular(ch2);

  imprimir(tiempoActual);
  graficar();
}

// Funciones
//Detección de flanco
void procesarCanal(int pin, Canal &ch, unsigned long tiempoActual) {
  ch.estadoActual = digitalRead(pin);
  
//Medición de periodo
  if (ch.estadoActual == HIGH && ch.estadoAnterior == LOW) {
    ch.periodo = tiempoActual - ch.tiempoAnterior;
    ch.tiempoAnterior = tiempoActual;
  }
//Medición de duty cycle  
  if (ch.estadoActual != ch.estadoAnterior) {
    if (ch.estadoActual == HIGH) {
      ch.tLow = tiempoActual - ch.tiempoCambio;
    } else {
      ch.tHigh = tiempoActual - ch.tiempoCambio;
    }
    ch.tiempoCambio = tiempoActual;
  }

  ch.estadoAnterior = ch.estadoActual;
}
//Cálculo de frecuencia
void calcular(Canal &ch) {
  if (ch.periodo > 0) {
    ch.frecuencia = 1000.0 / ch.periodo;
  } else {
    ch.frecuencia = 0;
  }
  if ((ch.tHigh + ch.tLow) > 0) {
    ch.duty = (ch.tHigh * 100.0) / (ch.tHigh + ch.tLow);
  } else {
    ch.duty = 0;
  }
}

void imprimir(unsigned long tiempoActual) {
  if (tiempoActual - ultimoPrint >= 500) {
    ultimoPrint = tiempoActual;

    Serial.println("-----------------------");

    Serial.println("CANAL 1 (555)");
    Serial.print("Periodo (ms): ");
    Serial.println(ch1.periodo);
    Serial.print("Frecuencia (Hz): ");
    Serial.println(ch1.frecuencia);
    Serial.print("Duty (%): ");
    Serial.println(ch1.duty);

    Serial.println("CANAL 2 (Flip-Flop)");
    Serial.print("Periodo (ms): ");
    Serial.println(ch2.periodo);
    Serial.print("Frecuencia (Hz): ");
    Serial.println(ch2.frecuencia);
    Serial.print("Duty (%): ");
    Serial.println(ch2.duty);

    Serial.println("-----------------------");
  }
}

void graficar() {
  Serial.print(ch1.estadoActual);
  Serial.print(",");
  Serial.println(ch2.estadoActual + 1);
}