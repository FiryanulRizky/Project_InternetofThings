#include <ESPmDNS.h>
#include <ESPAsyncWebServer.h>
#include <AsyncTCP.h>
#include <SPIFFS.h>

AsyncWebServer server(80); // server port 80

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>Database via SPIFFS</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <script>
    function PesanSubmit() {
      alert("Data akan disimpan");
      setTimeout(function(){ document.location.reload(false); }, 500);   
    }
  </script></head><body>

  <H2><b><center>(Projek 2)<br>PENYIMPANAN DATA ke DIREKTORI ESP32 via SPIFFS</center></b></H2>
  <hr>
  
   <form action="/get" target="hidden-form" class="center">
    huruf: <input type="text" name="huruf">
    <input type="submit" placeholder="Masukkan Data Huruf" value="Submit" onclick="PesanSubmit()">
  </form><br>
  <form action="/get" target="hidden-form" class="center">
    angka : <input type="number " name="angka">
    <input type="submit" placeholder="Masukkan Data Angka" value="Submit" onclick="PesanSubmit()">
  </form><br>
  <iframe style="display:none" name="hidden-form"></iframe>
  <hr>
   
  <table border="1" class="center">
    <tr>
      <td colspan="2"><H3><b><center>Data yang berhasil di input</center></b></H3></td>
    </tr>
      <td>Data Huruf</td>
      <td>%huruf%</td>
    </tr>
    <tr>
      <td>Data Angka</td>
      <td>%angka%</td>
  </table>
  
</body></html>)rawliteral";

const char* INPUT_STRING = "huruf";
const char* INPUT_INT = "angka";
int LED_BUILTIN = 2;
String readFile(fs::FS &fs, const char * path){
  File file = fs.open(path, "r");
  if(!file || file.isDirectory()){
    Serial.println("- File kosong atau tidak ditemukan");
    return String();
  }
  String fileContent;
  while(file.available()){
    fileContent+=String((char)file.read());
  }
  Serial.println(fileContent);
  return fileContent;
}

void writeFile(fs::FS &fs, const char * path, const char * message){
  Serial.printf("Writing file: %s\r\n", path);
  File file = fs.open(path,"a+");
  if(!file){
    Serial.println("- failed to open file for writing");
    return;
  }
  if(file.print(message)){
    Serial.println("- isi file berhasil ditulis");
  } else {
    Serial.println("- Penulisan Gagal");
  }
}

// Replaces placeholder with stored values
String processor(const String& var){
  //Serial.println(var);
  if(var == "huruf"){
    return readFile(SPIFFS, "/huruf.txt");
  }
  else if(var == "angka"){
    return readFile(SPIFFS, "/angka.txt");
  }
  return String();
}

void notFound(AsyncWebServerRequest *request)
{
  request->send(404, "text/plain", "not found");
}

void setup(void)
{
  
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  WiFi.softAP("FiryanulRizky ESP Wifi", "");
  Serial.println("FiryanulRizky ESP Wifi");
  Serial.println(WiFi.softAPIP());


  if (MDNS.begin("esp")) { //esp.local/
    Serial.println("MDNS responder started");
  }

  if(!SPIFFS.begin(true)){
      Serial.println("Error saat memuat SPIFFS");
      return;
    }

  // Membuka file HTML ke client
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  server.on("/get", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // Mengakses data <ESP_IP>/get?huruf=<inputMessage>
    if (request->hasParam(INPUT_STRING)) {
      inputMessage = request->getParam(INPUT_STRING)->value();
      writeFile(SPIFFS, "/huruf.txt", inputMessage.c_str());
      digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
      delay(500);                       // wait for a second
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
      delay(500);                       // wait for a second
    }
    // Mengakses data <ESP_IP>/get?angka=<inputMessage>
    else if (request->hasParam(INPUT_INT)) {
      inputMessage = request->getParam(INPUT_INT)->value();
      writeFile(SPIFFS, "/angka.txt", inputMessage.c_str());
       digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
       delay(500);                       // wait for a second
       digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
       delay(500);                       // wait for a second
    }
    else {
      inputMessage = "Pesan gagal";
      digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    }
    Serial.println(inputMessage);
    request->send(200, "text/text", inputMessage);
  });

  server.onNotFound(notFound);

  server.begin();  // it will start webserver
}


void loop(void)
{
  
  String datahuruf = readFile(SPIFFS, "/huruf.txt");
  Serial.print("*** Data huruf: ");
  Serial.println(datahuruf);
  
  int dataangka = readFile(SPIFFS, "/angka.txt").toInt();
  Serial.print("*** Data angka: ");
  Serial.println(dataangka);
  delay(5000);
}
