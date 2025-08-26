/*******************************************************
 * Proyecto: Sistema de medición de distancia con sensor ultrasónico HC-SR04
 * Plataforma: Arduino UNO (ATmega328P, 5 V, 16 MHz)
 * Autores: Franco Cstro Chaves y Marco Vásquez Ovares
 * Curso: IE0528 - Laboratorio de Transmisión de Datos
 *
 * Descripción general:
 * Este programa implementa la conexión entre dos circuitos integrados:
 *  - Microcontrolador ATmega328P (Arduino UNO)
 *  - Sensor ultrasónico HC-SR04 (periférico específico de medición)
 *
 * El sistema mide la distancia a un objeto dentro del rango de 30 cm a 310 cm
 * y proporciona una salida visual mediante cuatro LEDs:
 *   - Rojo: distancia demasiado cercana (< 30 cm).
 *   - Amarillo: distancia media (30–150 cm).
 *   - Verde: distancia lejana (150–310 cm).
 *   - Azul: condición de no detección o fuera de rango (> 310 cm).
 *******************************************************/

/// --- Definición de pines del sensor ultrasónico HC-SR04 ---
const int trigger = 7;   // Pin digital para señal de disparo (Trigger)
const int echo = 8;      // Pin digital para señal de recepción del eco (Echo)

/// --- Variables globales ---
float dist;              // Variable que almacena la distancia medida en cm

/// --- Definición de pines para los indicadores LED ---
const int LED_AZUL = 2;      // LED azul → no detección / fuera de rango
const int LED_ROJO = 3;      // LED rojo → distancia demasiado cercana (< 30 cm)
const int LED_AMARILLO = 4;  // LED amarillo → distancia media (30–150 cm)
const int LED_VERDE = 5;     // LED verde → distancia lejana (150–310 cm)

void setup() {
  Serial.begin(9600);        // Inicializa puerto serie a 9600 bps

  pinMode(trigger, OUTPUT);  // Pin "trigger" como salida digital
  pinMode(echo, INPUT);      // Pin "echo" como entrada digital

  // Configuración de LEDs como salidas
  pinMode(LED_AZUL, OUTPUT);
  pinMode(LED_ROJO, OUTPUT);
  pinMode(LED_AMARILLO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
}

void loop() {
  // --- Etapa 1: Generación del pulso de disparo ---
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);

  // --- Etapa 2: Medición del eco ---
  dist = pulseIn(echo, HIGH);   // Tiempo en µs que el pin echo permanece en alto
  dist = dist / 58;             // Conversión a centímetros (aprox. a 20–25 °C)

  // --- Etapa 3: Mostrar resultado ---
  Serial.print("Distancia = ");
  Serial.print(dist);
  Serial.println(" cm");

  // --- Etapa 4: Control de LEDs ---
  // Apagar todos para garantizar exclusión mutua
  digitalWrite(LED_AZUL, LOW);
  digitalWrite(LED_ROJO, LOW);
  digitalWrite(LED_AMARILLO, LOW);
  digitalWrite(LED_VERDE, LOW);

  // Encender según el rango de distancia
  if (dist == 0 || dist > 310) {
    // Sin eco detectado o fuera del rango especificado
    digitalWrite(LED_AZUL, HIGH);
  }
  else if (dist < 30) {
    digitalWrite(LED_ROJO, HIGH);       // Muy cerca
  } 
  else if (dist >= 30 && dist <= 150) {
    digitalWrite(LED_AMARILLO, HIGH);   // Rango medio
  } 
  else if (dist > 150 && dist <= 310) {
    digitalWrite(LED_VERDE, HIGH);      // Rango lejano
  }

  delay(200); // Retardo de 200 ms entre lecturas
}

/*******************************************************
 * Notas técnicas:
 * - El LED azul (pin 2) proporciona un estado de diagnóstico:
 *   • Se enciende cuando pulseIn() devuelve 0 (no eco) o
 *     cuando la distancia calculada excede 310 cm.
 * - Todos los LEDs usan resistencias limitadoras de ~220 Ω.
 *******************************************************/

/*
// lab #1

#define trigPin 10
#define echoPin 9

int counter;
float duration;
float distance;
unsigned long time;


void setup() 
{
  Serial.begin (9600);
  pinMode( trigPin, OUTPUT );
  pinMode( echoPin, INPUT );
}

void loop() 
{
  digitalWrite( trigPin, LOW ); 
  delayMicroseconds( 2 );
 
  digitalWrite( trigPin, HIGH );
  delayMicroseconds( 10 );
  digitalWrite( trigPin, LOW );
  
  //duration = pulseIn( echoPin, HIGH ); 

  // Get Pulse duration with more accuracy than pulseIn()
  duration = 0;
  counter = 0;
  while(  --counter!=0  )
  {
	if( PINB & 2 ) 
	{
	  time = micros();
	  break;
	}
  }
  while( --counter!=0 )
  {
	if( (PINB & 2)==0 ) 
	{
	  duration = micros()-time;
	  break;
	}
  }

  distance = ( duration/2 ) * 0.0344;
  
  Serial.print("Distance: ");

  if     ( distance > 400 ) Serial.print("> 400");
  else if( distance < 2 )   Serial.print("< 2");
  else                      Serial.print( distance );

  Serial.println( " cm" );

  delay( 1000 );
}
*/

/*
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
*/






