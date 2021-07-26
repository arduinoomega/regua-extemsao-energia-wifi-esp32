#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h> 
#include <BlynkSimpleEsp32.h> 
BlynkTimer timer;
char auth[] = "Token de Autenticação gerado";
//-------- Configurações de Wi-Fi -----------
char ssid[] = "sua rede";
char pass[] = "sua senha";
float vetCorrente[300];
float valor_medio;
float valor_Corrente;
BLYNK_CONNECTED()
{         // Se conectar com Blynk
  Blynk.syncVirtual(V3);    // Sincroniza com o pino V3
}
void sendSensor()
{
  double maior_Valor = 0;
  double valor_Corrente = 0;  
 
  float tensao = 220;
  float potencia = 0;
 
  for(int i = 0; i < 300; i++)
  {
    vetCorrente[i] = analogRead(39);
    delayMicroseconds(600);
  } 
 
  int somaTotal = 0;
 
  for(int i = 0; i < 300; i++)
  {
    somaTotal = vetCorrente[i] + somaTotal;
  }
  valor_medio = somaTotal / 300;
  valor_medio = valor_medio * 0.0012;
  valor_Corrente = (valor_medio - 2.5);
  valor_Corrente = valor_Corrente*1000;
  valor_Corrente = valor_Corrente / 66; //sensibilidade : 66mV/A para ACS712 30A
 
  Serial.print("Corrente = ");
  Serial.print(valor_Corrente);
  Serial.println(" A");
  potencia = valor_Corrente * tensao;
  Serial.print("Potência = ");
  Serial.print(potencia);
  Serial.println(" W");
  Serial.print(".");
  delay(500);
  Serial.println("");
  Blynk.virtualWrite(V3, valor_Corrente);      
  delay(100);
}
void setup()
{
  Serial.begin(115200);     
  pinMode(13, OUTPUT);           
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);           
  pinMode(27, OUTPUT);           
  Blynk.begin(auth, ssid, pass); // TOKEN+REDE+SENHA
  timer.setInterval(1000L, sendSensor);
}
void loop() 
{
  timer.run();
  Blynk.run();
}
