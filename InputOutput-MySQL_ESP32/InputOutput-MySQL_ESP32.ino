#include <WiFi.h>
 
char ssid[] = "FiryanulRizky";        // Isi dengan nama profil Wifi
char pass[] = "12345678";            // password wifi
char server[] = "192.168.1.107";     // alamat access point yang telah terinstall XAMPP local host
//char server[] = "firyan.000webhostapp.com";     // alamat web hosting

char namaVariabel[] = "Variabel";
String text = "";
String Respon = "";
bool responDariServer = false;
 
bool statusKomunikasiWifi = false;
long waktuMulai;
long waktuMintaData = 5000; //minta data setiap 5000ms
int LED_BUILTIN = 2;
 
WiFiClient client;
int status = WL_IDLE_STATUS;
 
void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.println("Koneksi arduino dengan mySql menggunakan ESp32 dan XAMPP");
  Serial.println("Ketik pesan yang akan dikirim (pastikan setting serial ke \"both NL & CR\")");
  
  status = WiFi.begin(ssid, pass);
  // you're connected now, so print out the data
  Serial.println("You're connected to the network");
   //print the SSID of the network you're attached to
   
}
 
void loop()
{
  //tunggu imputan nilai dari untuk dikirim ke server
  while(Serial.available())
  {
    char c = Serial.read();
    if((c != '\r') && (c != '\n'))
    {
      text += c;
    }
    if(c == '\n')
    {
      statusKomunikasiWifi = kirimKeDatabase("dataDariSerial",text);
      text = "";
      waktuMulai = millis();
    }
  }
 
  if(waktuMintaData < millis() - waktuMulai)
  {
    statusKomunikasiWifi = ambilDatabase("perintah");
    waktuMulai = millis();
  }
   
  // periksa respon dari server
  if(statusKomunikasiWifi)
  {
    // if there are incoming bytes available
    // from the server, read them and print them
    while (client.available()) 
    {
      char c = client.read();
      Respon += c;
    }
   
    // if the server's disconnected, stop the client
    if (!client.connected()) {
      client.stop();
      statusKomunikasiWifi = false;
      responDariServer = true;
    }
  }
 
  // penanganan data yang diretima dari server
  if(responDariServer)
  {
    responDariServer = false;
    //Serial.println(Respon);
    int posisiData = Respon.indexOf("\r\n\r\n");
    String Data = Respon.substring(posisiData+4);
    Data.trim();
 
    String variabel;
    String nilai;
 
    Serial.println("\n-- [BERIKUT ADALAH DATA DARI SERVER] --\n");
    posisiData = Data.indexOf('=');
    if(posisiData > 0)
    {
      variabel = Data.substring(0,posisiData);
      nilai = Data.substring(posisiData+1);
   
      //===========Penanganan respon disini
      Serial.print(variabel);
      Serial.print(" = ");
      Serial.println(nilai);


    }
    Respon = "";
  }
}
bool ambilDatabase(String variabel)
{
        digitalWrite(LED_BUILTIN, HIGH);
        delay(750);
        digitalWrite(LED_BUILTIN, LOW);
        delay(300);
  Serial.println();
  // print your WiFi shield's IP address
  Serial.print("Tulis IP Address ini di browser: ");
  Serial.println(server);
  Serial.println("Memulai koneksi ke server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println("Berhasil terkoneksi ke server");
    // Make a HTTP request
    client.print("GET /UAS_IOTL_06/keArduino.php?variabel=");
    client.print(variabel);;
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
 
    long _startMillis = millis();
    while (!client.available() and (millis() - _startMillis < 2000));
 
    return true;
  }
  return false;
}
 
bool kirimKeDatabase(String namaVariabel, String nilai)
{
  Serial.println();
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 80)) {
    Serial.println("Connected to server");
    // Make a HTTP request
 
    // parameter 1
    client.print("GET /UAS_IOTL_06/dariArduino.php?");
    client.print("variabel=");
    client.print(namaVariabel);
     
    // parameter 2 dan selanjutnya
    client.print("&");
    client.print("nilai=");
    client.print(nilai);
     
    client.println(" HTTP/1.1");
    client.print("Host: ");
    client.println(server);
    client.println("Connection: close");
    client.println();
 
    return true;
  }
  return false;
}
