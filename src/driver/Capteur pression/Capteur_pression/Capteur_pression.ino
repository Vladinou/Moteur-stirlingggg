/*####################################################################
  FILE: test_modulo_MPS20N0040D.ino
  VERSION: 1.0
  Descrizione: Programma per test modulo
  sensore di pressione tipo MPS20N0040D 

  Creato il 14/10/2018 da Adriano Gandolfo
  Sito web http://www.adrirobot.it
  Blog http://it.emcelettronica.com/author/adrirobot
  Pagina Facebook https://www.facebook.com/Adrirobot-318949048122955
  Istagram https://www.instagram.com/adrirobot/
  This example code is in the public domain.
  #################################################################### */

// Definizione dei pin di collegamento display OLED
#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8

#include "HX711.h" // libreria gestione convertitore analogico-digitale

// Definizione dei colori
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);
HX711 scale;

void setup() {
  Serial.begin(9600);
  display.begin();

  // Messaggio iniziale
  display.fillScreen(BLACK);
  display.setTextSize(1);
  display.setTextColor(BLUE);
  display.setCursor(0, 0);
  display.println(" ADRIROBOT");
  display.setTextColor(GREEN);
  display.println("   TEST  ");
  display.println(" PRESSURE ");
  display.println("  SENSOR  ");
  delay(2000);
  display.setTextColor(MAGENTA);

  Serial.println("HX711 Demo");

  Serial.println("Inizializzazione della scala");
  scale.begin(A1, A0);

  Serial.println("Prima si impostare la scala:");
  Serial.print("Lettura: \t\t");
  Serial.println(scale.read());      // stampa della lettura non elaborata dall'ADC

  Serial.print("Lettura della media \t\t");
  Serial.println(scale.read_average(20));   // stampa la media di 20 letture dall'ADC

  Serial.print("Ottiene il valore: \t\t");
  Serial.println(scale.get_value(5));
 // stampa la media di 5 letture dall'ADC meno il peso della tara (non ancora impostato)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);
// print the average of 5 readings from the ADC minus tare weight (not set) divided
// by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);
// this value is obtained by calibrating the scale with
// known weights; see the README for details
  scale.tare(); // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());
// print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));
// print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));
// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);
// print the average of 5 readings from the ADC minus tare weight, divided
  // by the SCALE parameter set with set_scale

  Serial.println("Lettura:");
}

void loop() {
  display.fillRect(0, 35, 64, 15, BLACK);
  display.setCursor(0, 35);
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  display.print(scale.get_units(), 1);
  scale.power_down(); // mette l'ADC in modalità sleep
  delay(500);
  scale.power_up();
}
