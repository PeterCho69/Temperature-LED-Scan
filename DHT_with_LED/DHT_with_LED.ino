#include "dht_nonblocking.h"
#define DHT_SENSOR_TYPE DHT_TYPE_11

int DHT_SENSOR_PIN = 12;
DHT_nonblocking dht_sensor( DHT_SENSOR_PIN, DHT_TYPE_11 );

int LED1_PIN = 10;
int LED2_PIN = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(1000);
  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

}

static bool measure_environment( float *temperature, float *humidity )
{
  static unsigned long measurement_timestamp = millis( );
  /* Measure once every four seconds. */
  if( millis( ) - measurement_timestamp > 3000ul )
  {
    if( dht_sensor.measure( temperature, humidity ) == true )
    {
      measurement_timestamp = millis( );
      return( true );
    }
  }
  return( false );
}

void loop() 
{
  // put your main code here, to run repeatedly:
  float temperature;
  float humidity;

  if( measure_environment( &temperature, &humidity ) == true )
  {
    Serial.print( "T = " );
    Serial.print( temperature, 1 );
    Serial.print( " deg. C, H = " );
    Serial.print( humidity, 1 );
    Serial.println( "%" );
  }

  delay(500);

  //Temperature --> LEDS
  //HOT
  if (temperature > 30) {
    digitalWrite(LED1_PIN, HIGH);
  }
  else {
    digitalWrite(LED1_PIN, LOW);
  }
  //COLD
  if (temperature < 30) {
    digitalWrite(LED2_PIN, HIGH);
  }
  else {
    digitalWrite(LED2_PIN, LOW);
  }
}
