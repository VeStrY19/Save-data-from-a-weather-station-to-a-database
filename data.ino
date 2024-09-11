#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <HTTPClient.h>


const char auth[] = "8E-fM2CEOxMkhiteQlEhQvx42K7O4XkY";

const char* ssid = "SFR_94F8";
const char* pass =  "82pggv6rmb62xqfv7wbq";

String HOST_NAME = "http://192.168.1.21"; // change to your PC's IP address
String PATH_NAME   = "/test.php";
String queryString = "?temperature=30.5";


void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("\n");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Blynk.begin(auth, ssid, pass, "Blynk.cloud", 80);

  Serial.print("Tentativie de connexion...");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(100);
  }

  Serial.println("\n");
  Serial.println("Connexion etablie !!");
  Serial.print("Adresse IP: ");
  Serial.println(WiFi.localIP());

  HTTPClient http;
  http.begin(HOST_NAME + PATH_NAME + queryString);
  int httpCode = http.GET();

  if(httpCode > 0) {
    // file found at server
    if(httpCode == HTTP_CODE_OK) {
      String payload = http.getString();
      Serial.println(payload);
    } else {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
    }
  } else {
    Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }

  http.end();
}

void loop()
{
  Blynk.run();
  
    

}
