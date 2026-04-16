// Definición de pines
int LED_PINS[] = {2, 3, 4, 5, 6, 7};
int BOTON_PIN = 8;
int patronActual = 0;
int numLeds = 6; 
bool estadoAnterior = LOW;

void setup() {
  // Configurar LEDs como salida
  for (int i = 0; i < numLeds; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  // Configurar botón como entrada
  pinMode(BOTON_PIN, INPUT);
}

void loop() {
  leerBoton();

  switch (patronActual) {
    case 0:
      patronSecuencia();
      break;
    case 1:
      patronPersecucion();
      break;
    case 2:
      patronParpadeo();
      break;
    case 3:
      patronAleatorio();
      break;
    case 4:
      patronOnda();
      break;
  }
}

//  FUNCIONES
void leerBoton() {
  bool estadoActual = digitalRead(BOTON_PIN);
  if (estadoActual == HIGH && estadoAnterior == LOW) {
    patronActual = (patronActual + 1) % 5;
    delay(100); // anti-rebote
  }
  estadoAnterior = estadoActual;
}

// Primer Patrón Secuencia
void patronSecuencia() {
  int i = 0;
  while (patronActual == 0) {
    for (int j = 0; j < numLeds; j++) {
      digitalWrite(LED_PINS[j], LOW);
    }
    digitalWrite(LED_PINS[i], HIGH);
    delay(100);
    i = (i + 1) % numLeds;
    leerBoton();
  }
}

// Segundo Patrón Persecución
void patronPersecucion() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(100);
    digitalWrite(LED_PINS[i], LOW);
  }
}

// Tercer Patrón Parpadeo
void patronParpadeo() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(LED_PINS[i], HIGH);
  }
  delay(100);

  for (int i = 0; i < numLeds; i++) {
    digitalWrite(LED_PINS[i], LOW);
  }
  delay(200);
}

// Cuarto Patrón Aleatorio
void patronAleatorio() {
  int led = random(0, numLeds);
  digitalWrite(LED_PINS[led], HIGH);
  delay(100);
  digitalWrite(LED_PINS[led], LOW);
}

// Quinto Patrón Onda
void patronOnda() {
  for (int i = 0; i < numLeds; i++) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(80);
    digitalWrite(LED_PINS[i], LOW);
  }
  for (int i = numLeds - 1; i >= 0; i--) {
    digitalWrite(LED_PINS[i], HIGH);
    delay(80);
    digitalWrite(LED_PINS[i], LOW);
  }
}