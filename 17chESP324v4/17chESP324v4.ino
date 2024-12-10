#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

//------- Replace the following! ------

char ssid[] = "Lenovo-GD888";         // your network SSID (name)
char password[] = "asdfghijk"; // your network password

#define TELEGRAM_BOT_TOKEN "6158442821:AAE_H7kh54e2XdpFmCMNvLH0VkAksmz_F5U"

WiFiClientSecure client;
UniversalTelegramBot bot(TELEGRAM_BOT_TOKEN, client);

#define PIN1 13 // Same as D4 for Wemos
#define PIN2 12 
#define PIN3 14 
#define PIN4 27 
#define PIN5 26
#define PIN6 25
#define PIN7 33
#define PIN8 32 

#define PIN9 15 
#define PIN10 2 
#define PIN11 4
#define PIN12 5
#define PIN13 18
#define PIN14 19
#define PIN15 21
#define PIN16 22
#define PIN17 23

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
  pinMode(26, OUTPUT);
  digitalWrite(26, LOW);
  pinMode(25, OUTPUT);
  digitalWrite(25, LOW);
  pinMode(33, OUTPUT);
  digitalWrite(33, LOW);
  pinMode(32, OUTPUT);
  digitalWrite(32, LOW);
  /*
  pinMode(5, OUTPUT);
  digitalWrite(5, LOW);
  pinMode(6, OUTPUT);
  digitalWrite(6, LOW);
  pinMode(7, OUTPUT);
  digitalWrite(7, LOW);
  pinMode(8, OUTPUT);
  digitalWrite(8, LOW);
  */
  pinMode(13, OUTPUT); 
  pinMode(12, OUTPUT);
  pinMode(14, OUTPUT);
  pinMode(27, OUTPUT);
  pinMode(26, OUTPUT);// Set the LED pin as output
  pinMode(25, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);
  pinMode(21, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
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

       if (text == F("ON1")) {
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
        else if (text == F("ON10")) {
        digitalWrite(PIN10, HIGH);
      } else if (text == F("OFF10")) {
        digitalWrite(PIN10, LOW);
      }
        else if (text == F("ON11")) {
        digitalWrite(PIN11, HIGH);
      } else if (text == F("OFF11")) {
        digitalWrite(PIN11, LOW);
      } 
       else if (text == F("ON12")) {
        digitalWrite(PIN12, HIGH);
      } else if (text == F("OFF12")) {
        digitalWrite(PIN12, LOW);
      }
       else if (text == F("ON13")) {
        digitalWrite(PIN13, HIGH);
      } else if (text == F("OFF13")) {
        digitalWrite(PIN13, LOW);
      }
       else if (text == F("ON14")) {
        digitalWrite(PIN14, HIGH);
      } else if (text == F("OFF14")) {
        digitalWrite(PIN14, LOW);
      }
       else if (text == F("ON15")) {
        digitalWrite(PIN15, HIGH);
      } else if (text == F("OFF15")) {
        digitalWrite(PIN15, LOW);
      }
       else if (text == F("ON16")) {
        digitalWrite(PIN16, HIGH);
      } else if (text == F("OFF16")) {
        digitalWrite(PIN16, LOW);
      }
      
    } else {
      String chat_id = String(bot.messages[i].chat_id);
      String text = bot.messages[i].text;

      if (text == F("/Room1")) {

        // Keyboard Json is an array of arrays.
        // The size of the main array is how many row options the keyboard has
        // The size of the sub arrays is how many coloums that row has

        // "The Text" property is what shows up in the keyboard
        // The "callback_data" property is the text that gets sent when pressed  
        
        String keyboardJson = F("[[{ \"text\" : \"ON1\", \"callback_data\" : \"ON1\" },{ \"text\" : \"OFF1\", \"callback_data\" : \"OFF1\" }],");
               keyboardJson += F("[{ \"text\" : \"ON2\", \"callback_data\" : \"ON2\" },{ \"text\" : \"OFF2\", \"callback_data\" : \"OFF2\" }],");
               keyboardJson += F("[{ \"text\" : \"ON3\", \"callback_data\" : \"ON3\" },{ \"text\" : \"OFF3\", \"callback_data\" : \"OFF3\" }],");              
               keyboardJson += F("[{ \"text\" : \"ON4\", \"callback_data\" : \"ON4\" },{ \"text\" : \"OFF4\", \"callback_data\" : \"OFF4\" }]]");
               
        bot.sendMessageWithInlineKeyboard(chat_id, "Home automaiton room 1", "", keyboardJson);
      }
      else if (text == F("/Room2")) {

        // Keyboard Json is an array of arrays.
        // The size of the main array is how many row options the keyboard has
        // The size of the sub arrays is how many coloums that row has

        // "The Text" property is what shows up in the keyboard
        // The "callback_data" property is the text that gets sent when pressed  
        
        String keyboardJson = F("[[{ \"text\" : \"ON5\", \"callback_data\" : \"ON5\" },{ \"text\" : \"OFF5\", \"callback_data\" : \"OFF5\" }],");
               keyboardJson += F("[{ \"text\" : \"ON6\", \"callback_data\" : \"ON6\" },{ \"text\" : \"OFF6\", \"callback_data\" : \"OFF6\" }],");
               keyboardJson += F("[{ \"text\" : \"ON7\", \"callback_data\" : \"ON7\" },{ \"text\" : \"OFF7\", \"callback_data\" : \"OFF7\" }],");
               keyboardJson += F("[{ \"text\" : \"ON8\", \"callback_data\" : \"ON8\" },{ \"text\" : \"OFF8\", \"callback_data\" : \"OFF8\" }]]");
               
        bot.sendMessageWithInlineKeyboard(chat_id, "Home automaiton room 2", "", keyboardJson);
      }
      
      else if (text == F("/Room3")) {

        // Keyboard Json is an array of arrays.
        // The size of the main array is how many row options the keyboard has
        // The size of the sub arrays is how many coloums that row has

        // "The Text" property is what shows up in the keyboard
        // The "callback_data" property is the text that gets sent when pressed  
        
        String keyboardJson = F("[[{ \"text\" : \"ON9\", \"callback_data\" : \"ON9\" },{ \"text\" : \"OFF9\", \"callback_data\" : \"OFF9\" }],");
               keyboardJson += F("[{ \"text\" : \"ON10\", \"callback_data\" : \"ON10\" },{ \"text\" : \"OFF10\", \"callback_data\" : \"OFF10\" }],");
               keyboardJson += F("[{ \"text\" : \"ON11\", \"callback_data\" : \"ON11\" },{ \"text\" : \"OFF11\", \"callback_data\" : \"OFF11\" }],");
               keyboardJson += F("[{ \"text\" : \"ON12\", \"callback_data\" : \"ON12\" },{ \"text\" : \"OFF12\", \"callback_data\" : \"OFF12\" }]]");
               
        bot.sendMessageWithInlineKeyboard(chat_id, "Home automaiton room 3", "", keyboardJson);
      }
      else if (text == F("/Room4")) {

        // Keyboard Json is an array of arrays.
        // The size of the main array is how many row options the keyboard has
        // The size of the sub arrays is how many coloums that row has

        // "The Text" property is what shows up in the keyboard
        // The "callback_data" property is the text that gets sent when pressed  
        
        String keyboardJson = F("[[{ \"text\" : \"ON13\", \"callback_data\" : \"ON13\" },{ \"text\" : \"OFF13\", \"callback_data\" : \"OFF13\" }],");
               keyboardJson += F("[{ \"text\" : \"ON14\", \"callback_data\" : \"ON14\" },{ \"text\" : \"OFF14\", \"callback_data\" : \"OFF14\" }],");
               keyboardJson += F("[{ \"text\" : \"ON15\", \"callback_data\" : \"ON15\" },{ \"text\" : \"OFF15\", \"callback_data\" : \"OFF15\" }],");
               keyboardJson += F("[{ \"text\" : \"ON16\", \"callback_data\" : \"ON16\" },{ \"text\" : \"OFF16\", \"callback_data\" : \"OFF16\" }]]");
               
        bot.sendMessageWithInlineKeyboard(chat_id, "Home automaiton room 4", "", keyboardJson);
      }


      // When a user first uses a bot they will send a "/start" command
      // So this is a good place to let the users know what commands are available
      if (text == F("/start")) {

        bot.sendMessage(chat_id, "Welcome, this is Smart Home program \n Select room to operate controls \n || /Room1 || /Room2 || /Room3 || /Room4 ||  \n");
                
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
