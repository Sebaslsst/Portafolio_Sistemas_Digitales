#define LED_PIN 13

byte estadoLed = 0;
int contador = 0;

void printBinary(byte num) {
  for (int i = 7; i >= 0; i--) {
    Serial.print((num >> i) & 1);
  }
  Serial.println();
}
void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(9600);

  byte a = 5;
  byte b = 3; 
  int entero = 10;
  long numeroGrande = 100000;
  float decimal = 3.14;
  bool bandera = true;

  Serial.println("Operaciones Bitwise");
  Serial.print("int: ");
  Serial.println(entero);
  Serial.print("long: ");
  Serial.println(numeroGrande);
  Serial.print("float: ");
  Serial.println(decimal);
  Serial.print("bool: ");
  Serial.println(bandera);
  Serial.print("AND: ");
  printBinary(a & b);
  Serial.print("OR: ");
  printBinary(a | b);
  Serial.print("XOR: ");
  printBinary(a ^ b);
  Serial.print("NOT: ");
  printBinary(~a);
  Serial.print("SHIFT IZQ: ");
  printBinary(a << 1);
  estadoLed = estadoLed | (1 << 0);
}
void loop() {
  estadoLed = estadoLed ^ 0b00000001;
  if ((estadoLed & 1) == 1) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
  delay(500);
  contador = (contador + 1) % 8;
  Serial.print("Valor: ");
  printBinary(1 << contador);

  delay(500);
}