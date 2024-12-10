
#include <WiFi.h>
#include <WiFiClientSecure.h>

#include <UniversalTelegramBot.h>
// Library for interacting with the Telegram API
// Search for "Telegegram" in the Library manager and install
// The universal Telegram library
// https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot


#include <ArduinoJson.h>
// install the 5.x.x version instead
// Search for "Arduino Json" in the Arduino Library manager
// https://github.com/bblanchon/ArduinoJson

//------- Replace the following! ------

char ssid[] = "Lenovo-GD888";         // your network SSID (name)
char password[] = "asdfghijk"; // your network password

#define TELEGRAM_BOT_TOKEN "6158442821:AAE_H7kh54e2XdpFmCMNvLH0VkAksmz_F5U"


//------- ---------------------- ------


// This is the Wifi client that supports HTTPS
WiFiClientSecure client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);

#define PIN1 12 // Same as D4 for Wemos
#define PIN2 13 
#define PIN3 14 
#define PIN4 27 
#define PIN5 1 
#define LED_PIN 2 
#define PIN6 3 
#define PIN7 4
#define PIN8 5 
#define PIN9 6 
#define PIN0 7
#define PIN10 8

int delayBetweenChecks = 1000;
unsigned long lastTimeChecked;   //last time messages' scan has been done

unsigned long lightTimerExpires;
boolean lightTimerActive = false;

void setup() {
  Serial.begin(115200);

  // Set WiFi to station mode and disconnect from an AP if it was Previously connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  pinMode(14, OUTPUT);
  digitalWrite(14, LOW);
  pinMode(27, OUTPUT);
  digitalWrite(27, LOW);
  pinMode(1, OUTPUT);
  digitalWrite(1, LOW);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
  pinMode(3, OUTPUT);
  digitalWrite(3, LOW);
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);


  // attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Only required on 2.5 Beta
  client.setInsecure();

  
  // longPoll keeps the request to Telegram open for the given amount of seconds if there are no messages
  // This hugely improves response time of the bot, but is only really suitable for projects
  // where the the initial interaction comes from Telegram as the requests will block the loop for
  // the length of the long poll
  bot.longPoll = 60;
}

void handleNewMessages(int numNewMessages) {

  for (int i = 0; i < numNewMessages; i++) {

    // If the type is a "callback_query", a inline keyboard button was pressed
    if (bot.messages[i].type ==  F("callback_query")) {
      String text = bot.messages[i].text;
      Serial.print("Call back button pressed with text: ");
      Serial.println(text);

      if (text == F("ON")) {
        digitalWrite(LED_PIN, HIGH);
      } else if (text == F("OFF")) {
        digitalWrite(LED_PIN, LOW);

       } else if (text == F("ON1")) {
        digitalWrite(PIN1, HIGH);
      } else if (text == F("OFF1")) {
        digitalWrite(PIN1, LOW);
      } 
        else if (text == F("ON2")) {
        digitalWrite(PIN2, HIGH);
      } else if (text == F("OFF2")) {
        digitalWrite(PIN2, LOW);
      } 
        else if (text == F("ON3")) {
        digitalWrite(PIN3, HIGH);
      } else if (text == F("OFF3")) {
        digitalWrite(PIN3, LOW);
      } 
        else if (text == F("ON4")) {
        digitalWrite(PIN4, HIGH);
      } else if (text == F("OFF4")) {
        digitalWrite(PIN4, LOW);
      } 
        else if (text == F("ON5")) {
        digitalWrite(PIN5, HIGH);
      } else if (text == F("OFF5")) {
        digitalWrite(PIN5, LOW);

      } 
        else if (text == F("ON6")) {
        digitalWrite(PIN6, HIGH);
      } else if (text == F("OFF6")) {
        digitalWrite(PIN6, LOW);
      } 
        else if (text == F("ON7")) {
        digitalWrite(PIN7, HIGH);
      } else if (text == F("OFF7")) {
        digitalWrite(PIN7, LOW);
      } 
        else if (text == F("ON8")) {
        digitalWrite(PIN8, HIGH);
      } else if (text == F("OFF8")) {
        digitalWrite(PIN8, LOW);
      } 
        else if (text == F("ON9")) {
        digitalWrite(PIN9, HIGH);
      } else if (text == F("OFF9")) {
        digitalWrite(PIN9, LOW);
      } 
        else if (text == F("ON0")) {
        digitalWrite(LED_PIN, HIGH);
      } else if (text == F("OFF0")) {
        digitalWrite(LED_PIN, LOW);

      } else if (text == F("ON10")) {
        digitalWrite(PIN1, HIGH);
      } else if (text == F("OFF10")) {
        digitalWrite(PIN1, LOW);
      } 

    } else {
      String chat_id = String(bot.messages[i].chat_id);
      String text = bot.messages[i].text;

      if (text == F("/options")) {

        // Keyboard Json is an array of arrays.
        // The size of the main array is how many row options the keyboard has
        // The size of the sub arrays is how many coloums that row has

        // "The Text" property is what shows up in the keyboard
        // The "callback_data" property is the text that gets sent when pressed  
        
        String keyboardJson = F("[[{ \"text\" : \"ON\", \"callback_data\" : \"ON\" },{ \"text\" : \"OFF\", \"callback_data\" : \"OFF\" }],");
               keyboardJson += F("[{ \"text\" : \"ON1\", \"callback_data\" : \"ON1\" },{ \"text\" : \"OFF1\", \"callback_data\" : \"OFF1\" }],");
               keyboardJson += F("[{ \"text\" : \"ON2\", \"callback_data\" : \"ON2\" },{ \"text\" : \"OFF2\", \"callback_data\" : \"OFF2\" }],");
               keyboardJson += F("[{ \"text\" : \"ON3\", \"callback_data\" : \"ON3\" },{ \"text\" : \"OFF3\", \"callback_data\" : \"OFF3\" }],");
               keyboardJson += F("[{ \"text\" : \"ON4\", \"callback_data\" : \"ON4\" },{ \"text\" : \"OFF4\", \"callback_data\" : \"OFF4\" }],");
               keyboardJson += F("[{ \"text\" : \"ON5\", \"callback_data\" : \"ON5\" },{ \"text\" : \"OFF5\", \"callback_data\" : \"OFF5\" }]]");
        bot.sendMessageWithInlineKeyboard(chat_id, "Home automaiton", "", keyboardJson);
      }
      else if (text == F("/second")) {

        // Keyboard Json is an array of arrays.
        // The size of the main array is how many row options the keyboard has
        // The size of the sub arrays is how many coloums that row has

        // "The Text" property is what shows up in the keyboard
        // The "callback_data" property is the text that gets sent when pressed  
        
        String keyboardJson = F("[[{ \"text\" : \"ON6\", \"callback_data\" : \"ON6\" },{ \"text\" : \"OFF6\", \"callback_data\" : \"OFF6\" }],");
               keyboardJson += F("[{ \"text\" : \"ON7\", \"callback_data\" : \"ON7\" },{ \"text\" : \"OFF7\", \"callback_data\" : \"OFF7\" }],");
               keyboardJson += F("[{ \"text\" : \"ON8\", \"callback_data\" : \"ON8\" },{ \"text\" : \"OFF8\", \"callback_data\" : \"OFF8\" }],");
               keyboardJson += F("[{ \"text\" : \"ON9\", \"callback_data\" : \"ON9\" },{ \"text\" : \"OFF9\", \"callback_data\" : \"OFF9\" }],");
               keyboardJson += F("[{ \"text\" : \"ON0\", \"callback_data\" : \"ON0\" },{ \"text\" : \"OFF0\", \"callback_data\" : \"OFF0\" }],");
               keyboardJson += F("[{ \"text\" : \"ON10\", \"callback_data\" : \"ON10\" },{ \"text\" : \"OFF10\", \"callback_data\" : \"OFF10\" }]]");
        bot.sendMessageWithInlineKeyboard(chat_id, "Home automaiton", "", keyboardJson);
      }

      // When a user first uses a bot they will send a "/start" command
      // So this is a good place to let the users know what commands are available
      if (text == F("/start")) {

        bot.sendMessage(chat_id, "/options : returns the inline keyboard /second : \n", "Markdown");
      }
    }
  }
}

void loop() {
  if (millis() > lastTimeChecked + delayBetweenChecks)  {

    // getUpdates returns 1 if there is a new message from Telegram
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    if (numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
    }

    lastTimeChecked = millis();

    
  }
}
