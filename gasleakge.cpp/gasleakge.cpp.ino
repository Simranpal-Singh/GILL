#include <SoftwareSerial.h>
SoftwareSerial mySerial(9, 10);

int sensor=7;
int speaker=2;
int gasvalue,Gas, Gas_shut_val;
int GasLeakStatus;
int sms=0;
int valve=13;
int x=0;

void setup()
{

pinMode(sensor,INPUT);
pinMode(speaker,OUTPUT);
pinMode(valve,OUTPUT);
mySerial.begin(9600);   
Serial.begin(9600);

}

void loop()
{
CheckGas();
CheckShutDown();
if(x=0)
{
  digitalWrite(valve, HIGH);//switching on the valve
}
}

void CheckGas()
{

Gas=Scan();
if(Gas==LOW)
{
 SetAlert(); // Function to send SMS Alerts
 digitalWrite(valve,LOW);//shutting down valve 
 x=1;
}}

int Scan()
{
gasvalue=digitalRead(sensor); // reads the sensor output (Vout of LM35)

return gasvalue; // returns temperature value in degree celsius
}

void SetAlert()
{
digitalWrite(speaker,HIGH);  
while(sms<1) //Number of SMS Alerts to be sent
{  
SendTextMessage(); // Function to send AT Commands to GSM module
}
GasLeakStatus=1; 
}

void CheckShutDown()
{
if(GasLeakStatus==1)
{

Gas_shut_val=Scan();
if(Gas_shut_val==HIGH)
{


digitalWrite(speaker,LOW);
sms=0;
GasLeakStatus=0;
}}}

void SendTextMessage()
{
  mySerial.println("AT+CMGF=1");    //To send SMS in Text Mode
  delay(1000);
  mySerial.println("AT+CMGS=\"+918607809200\"\r"); // change to the phone number you using 
  delay(1000);
  mySerial.println("Alert \n Gas Leakage Detected !");//the content of the message
  delay(200);
  mySerial.println((char)26);//the stopping character
  delay(1000);
  sms++;
}

