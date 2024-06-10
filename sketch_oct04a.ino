#include <Wire.h>
#include <Adafruit_SH1106.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SH1106 display(OLED_RESET);

const int motionPin = 2;  // Pin del sensor de movimiento HC-SR501
const int relayPin = 3;   // Pin del relé
bool ledState = LOW;      // Estado inicial del LED

void setup() {
  pinMode(motionPin, INPUT); // Configurar el pin del sensor de movimiento como entrada
  pinMode(relayPin, OUTPUT); // Configurar el pin del relé como salida
  digitalWrite(relayPin, ledState); // Apagar el LED inicialmente2 222

  Serial.begin(9600); // Iniciar la comunicación serial
  display.begin(SH1106_I2C_ADDRESS); // Inicializar el display OLED
  display.display(); // Mostrar pantalla en blanco inicial
  // delay(2000); // Esperar 2 segundos
  // display.clearDisplay(); // Borrar la pantalla
}

void loop() {
  int motionState = digitalRead(motionPin); // Leer el estado del sensor de movimiento

  if (motionState == HIGH) {
    // El sensor de movimiento detectó movimiento
    ledState = HIGH; // Encender el LED
    digitalWrite(relayPin, ledState);
    display.clearDisplay(); // Borrar la pantalla antes de mostrar un nuevo mensaje
    display.setTextSize(1); // Tamaño del texto
    display.setTextColor(WHITE); // Color del texto (blanco)
    display.setCursor(0, 0); // Posición del cursor
    display.println("ACTIVIDAD DE MOVIMIENTO"); // Mostrar "Movimiento Detectado" en el display
    display.display(); // Mostrar en pantalla
    Serial.println("ACTIVIDAD DE MOVIMIENTO"); // Mostrar "Movimiento Detectado" en el monitor serial
  } else {
    ledState = LOW; // Apagar el LED si no se detecta movimiento
    digitalWrite(relayPin, ledState);
    display.clearDisplay(); // Borrar la pantalla antes de mostrar un nuevo mensaje
    display.setTextSize(1); // Tamaño del texto
    display.setTextColor(WHITE); // Color del texto (blanco)
    display.setCursor(0, 0); // Posición del cursor
    display.println("SIN ACTIVIDAD"); // Mostrar "Sin Movimiento" en el display
    display.display(); // Mostrar en pantalla
    Serial.println("SIN ACTIVIDAD"); // Mostrar "Sin Movimiento" en el monitor serial
  }
}
