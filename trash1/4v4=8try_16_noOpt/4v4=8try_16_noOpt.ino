#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "6158442821:AAE_H7kh54e2XdpFmCMNvLH0VkAksmz_F5U"
char ssid[] = "Lenovo-GD888";   // Wifi SSID 
char password[] = "asdfghijk"; // Wifi Password

String buttons1[] = { "LED1", "LED2", "FAN", "Cooler" };
String buttons2[] = { "Lock Door", "UnLock Door", "Open Window", "Close Window" };
int pin1[] = {12, 13, 14,  4};
int pin2[] = {27, 2, 1, 5};

bool protection = 0;
int chatID_acces[] = {6157679976};
String on_symbol = "✅ ";  // ON Indicator
String off_symbol = "☑ "; // OFF indicator.
String text;
WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int quantity;
long Bot_lasttime;   
int Bot_mtbs = 3000;
String keyboardJson = "";

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  int i = 0;
  int j = 0;
if (text == "/start1"){
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String m_id = String(bot.messages[i].message_id);

    if (bot.messages[i].type == "callback_query") {
      String statusMessage;
      
      for (int i1 = 0; i1 < quantity; i1++) {
        if (bot.messages[i].text == buttons1[i1]) {
          digitalWrite(pin1[i1], !digitalRead(pin1[i1]));
        }
        
        digitalRead(pin1[i1]) ? statusMessage += on_symbol : statusMessage += off_symbol;
        statusMessage += buttons1[i1];
        statusMessage += '\n';
      }
      
      bot.sendMessageWithInlineKeyboard(bot.messages[i].chat_id, statusMessage, "", keyboardJson);
    } else {
      String text = bot.messages[i].text;
      Serial.println(m_id);
      String from_name = bot.messages[i].from_name;

      if (from_name == "") from_name = "Guest";
      int i2=0;
      for (int i2 = 0; i2 < (sizeof(chatID_acces) / sizeof(int)); i2++) {
        if (!protection || String(chatID_acces[i2]) == chat_id) {
          if (text == "/switch1") {
            String statusMessage;

            for (i = 0; i < quantity; i++) {
              digitalRead(pin1[i]) ? statusMessage += on_symbol : statusMessage += off_symbol;
              statusMessage += buttons1[i];
              statusMessage += '\n';
            }

            bot.sendMessageWithInlineKeyboard(chat_id, statusMessage, "", keyboardJson);
          }

          if (text == "/start1") {
            String welcome = "Welcome " + from_name + ".\n";
            welcome += "This is ESP smart switch1, controlled via Telegram.\n\n";
            welcome += "/switch1 : Click to open Switch1 Board.\n";
            String keyboardStart = "smart home";
            bot.sendMessageWithInlineKeyboard(chat_id, welcome, "", keyboardStart);
          }
          
          break;
        } else {
          if (i2 == ((sizeof(chatID_acces) / sizeof(int)) - 1) && text == "/start1" || 
              (sizeof(chatID_acces) / sizeof(int)) == 0 && text == "/start1") {
            bot.sendMessage(chat_id, "No access, Chat ID: " + chat_id, "");
          }
        }

        i2++;
      }while (i2<(sizeof(chatID_acces)/sizeof(int)));
    }
  }
}
if (text == "/start2"){
  for (int j = 0; j < numNewMessages; j++) {
    String chat_id = String(bot.messages[j].chat_id);
    String m_id = String(bot.messages[j].message_id);

    if (bot.messages[j].type == "callback_query") {
      String statusMessage;
      
      for (int j1 = 0; j1<quantity; j1++) {
        if (bot.messages[j].text == buttons2[j1]) {
          digitalWrite(pin2[j1], !digitalRead(pin2[j1]));
        }
        
        digitalRead(pin2[j1]) ? statusMessage += on_symbol : statusMessage += off_symbol;
        statusMessage += buttons2[j1];
        statusMessage += '\n';
      }
      
      bot.sendMessageWithInlineKeyboard(bot.messages[j].chat_id, statusMessage, "", keyboardJson);
    } else {
      String text = bot.messages[j].text;
      Serial.println(m_id);
      String from_name = bot.messages[j].from_name;

      if (from_name == "") from_name = "Guest";
      int j2=0;
      for (int j2 = 0; j2 < (sizeof(chatID_acces) / sizeof(int)); j2++) {
        if (!protection || String(chatID_acces[j2]) == chat_id) {
          if (text == "/switch2") {
            String statusMessage;

            for (j = 0; j < quantity; j++) {
              digitalRead(pin2[j]) ? statusMessage += on_symbol : statusMessage += off_symbol;
              statusMessage += buttons2[j];
              statusMessage += '\n';
            }

            bot.sendMessageWithInlineKeyboard(chat_id, statusMessage, "", keyboardJson);
          }

          if (text == "/start2") {
            String welcome = "Welcome " + from_name + ".\n";
            welcome += "This is ESP smart switch2, controlled via Telegram.\n\n";
            welcome += "/switch2: Click to open Switch2 Board.\n";
            String keyboardStart = "smart home";
            bot.sendMessageWithInlineKeyboard(chat_id, welcome, "", keyboardStart);
          }
          
          break;
        } else {
          if (j2 == ((sizeof(chatID_acces) / sizeof(int)) - 1) && text == "/start2" || 
              (sizeof(chatID_acces) / sizeof(int)) == 0 && text == "/start2") {
            bot.sendMessage(chat_id, "No access, Chat ID: " + chat_id, "");
          }
        }

        j2++;
      }while (j2<(sizeof(chatID_acces)/sizeof(int)));
    }
  }
}
}

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

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

  // Initialize pin1
  quantity = sizeof(pin1) / sizeof(int);
  for (int i = 0; i < quantity; i++) {
    pinMode(pin1[i], OUTPUT);
  }

  // Construct keyboardJson for buttons1
  for (int i = 0; i < quantity; i++) {
    if (i == 0) keyboardJson += "[";
    keyboardJson += "[{ \"text\" : \"";
    keyboardJson += buttons1[i];
    keyboardJson += "\", \"callback_data\" : \"";
    keyboardJson += buttons1[i];
    keyboardJson += "\" }]";
    if (i == quantity - 1) {
      keyboardJson += "]";
    } else {
      keyboardJson += ",";
    }
  }

  // Initialize pin2
  quantity = sizeof(pin2) / sizeof(int);
  for (int i = 0; i < quantity; i++) {
    pinMode(pin2[i], OUTPUT);
  }

  // Construct keyboardJson for buttons2
  for (int i = 0; i < quantity; i++) {
    if (i == 0) keyboardJson += "[";
    keyboardJson += "[{ \"text\" : \"";
    keyboardJson += buttons2[i];
    keyboardJson += "\", \"callback_data\" : \"";
    keyboardJson += buttons2[i];
    keyboardJson += "\" }]";
    if (i == quantity - 1) {
      keyboardJson += "]";
    } else {
      keyboardJson += ",";
    }
  }

  delay(10);
  client.setInsecure();
}


void loop() 
{
  if (millis() > Bot_lasttime + Bot_mtbs)  
  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while(numNewMessages) 
    {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    Bot_lasttime = millis();
  }
}
