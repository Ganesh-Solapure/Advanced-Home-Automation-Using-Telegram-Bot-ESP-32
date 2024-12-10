#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

String auth_id = "5773521504";
char ssid[] = "moto"; // your network SSID (name)
char password[] = "deeeeeeee"; // your network password
#define TELEGRAM_BOT_TOKEN "7435113471:AAGT7eBACTFB-TImlXS11GX0JZXmN2F75go"


WiFiClientSecure client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);

#define LED_PIN1 27
#define LED_PIN2 14
#define LED_PIN3 12
#define LED_PIN4 13

int delayBetweenChecks = 1000;
unsigned long lastTimeChecked; // last time messages' scan has

unsigned long lightTimerExpires;
boolean lightTimerActive = false;

void setup()
{
  Serial.begin(115200);
  // Set Wifi to station mode and disconnect from an AP if it was
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  pinMode(LED_PIN1, OUTPUT);
  digitalWrite(LED_PIN1, HIGH);
  pinMode(LED_PIN2, OUTPUT);
  digitalWrite(LED_PIN2, HIGH);
  pinMode(LED_PIN3, OUTPUT);
  digitalWrite(LED_PIN3, HIGH);
  pinMode(LED_PIN4, OUTPUT);
  digitalWrite(LED_PIN4, HIGH);

  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  bot.longPoll = 60;
}

void handleNewMessages(int numNewMessages)
{
  for (int i = 0; i < numNewMessages; i++)
  {
    if (bot.messages[i].type == F("callback_query"))
    {
      String text = bot.messages[i].text;
      Serial.print("Call back button pressed with text: ");
      Serial.println(text);

      if (text == F("ON1"))
      {
        digitalWrite(LED_PIN1, LOW);
      }
      else if (text == F("OFF1"))
      {
        digitalWrite(LED_PIN1, HIGH);
      }
      if (text == F("ON2"))
      {
        digitalWrite(LED_PIN2, LOW);
      }
      else if (text == F("OFF2"))
      {
        digitalWrite(LED_PIN2, HIGH);
      }
      if (text == F("ON3"))
      {
        digitalWrite(LED_PIN3, LOW);
      }
      else if (text == F("OFF3"))
      {
        digitalWrite(LED_PIN3, HIGH);
      }
      if (text == F("ON4"))
      {
        digitalWrite(LED_PIN4, LOW);
      }
      else if (text == F("OFF4"))
      {
        digitalWrite(LED_PIN4, HIGH);
      }
    }
    else
    {
      String chat_id = String(bot.messages[i].chat_id);
      String text = bot.messages[i].text;

      // Handle other message types or do something with chat_id and text
    }
  }
}

void loop()
{
  // Check for new messages
  int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
 
  // Handle new messages
  if (numNewMessages > 0)
  {
    handleNewMessages(numNewMessages);
    lastTimeChecked = millis();
  }

  // Other loop tasks can be added here
  // ...

  // Add delay between checks
  if (millis() - lastTimeChecked > delayBetweenChecks)
  {
    // Perform periodic tasks if needed
    // ...

    // Reset the timer
    lastTimeChecked = millis();
  }
}
