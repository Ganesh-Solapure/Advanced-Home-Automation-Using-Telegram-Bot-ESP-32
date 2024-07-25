
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "6158442821:AAE_H7kh54e2XdpFmCMNvLH0VkAksmz_F5U"  
char ssid[] = "M113";         
char password[] = "wifi8889";     
String buttons[16] = { "Door Lock/Un","Feed Pet","LED1","LED2" ,"LED3","LED4","LED5","LED6"  ,"LED7","LED8","LED9","LED10" ,"LED11","LED12","LED13","FAN"};  
int pin[16] = { 13,14,12,27 ,26,25,33,32 ,15,2,4,18 ,19,21,22,23};                      

bool protection = 0;                     
int chatID_acces[] = {6157679976 , 1120713076  };

String on_symbol="✅ ";  
String off_symbol="☑ "; 

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int quantity;
int Bot_mtbs = 1000; 
long Bot_lasttime;   
bool Start = false;
const int ledPin = 12;
int ledStatus = 0;
String keyboardJson = "";

int messageID;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String m_id = String(bot.messages[i].message_id);
    if (bot.messages[i].type == "callback_query") {
      String statusMessage;
      for (int i1=0; i1<quantity; i1++) {
        if (bot.messages[i].text == buttons[i1]) {
          digitalWrite (pin[i1], !digitalRead(pin[i1]));
        }
        digitalRead(pin[i1])?statusMessage+=on_symbol:statusMessage+=off_symbol;
        statusMessage+=buttons[i1]; 
        statusMessage+='\n';
      }
      
      bot.sendMessageWithInlineKeyboard(bot.messages[i].chat_id, statusMessage, "", keyboardJson);
      
    } else {
      String text = bot.messages[i].text;
      Serial.println(m_id);
      String from_name = bot.messages[i].from_name;
      if (from_name == "") from_name = "Guest";
      int i2=0;
      do{
        if (!protection || String(chatID_acces[i2]) == chat_id) {
          if (text == "/switch") {
            String statusMessage;
            for (int i=0; i<quantity; i++) {
              digitalRead(pin[i])?statusMessage+=on_symbol:statusMessage+=off_symbol;
              statusMessage+=buttons[i];  
              statusMessage+='\n';
            }
            bot.sendMessageWithInlineKeyboard(chat_id, statusMessage, "", keyboardJson);
          }

          if (text == "/start") {
            String welcome = "Welcome " + from_name + ".\n";
            welcome += "This is ESP smart switch, controlled via Telegram Bot Mini Project\n\n";
            welcome += "/switch : Click to open Switch Board.\n";
            welcome += "/AllShutDown : Click to turn Off all switches.\n";
            welcome += "/AllOn : Click to turn On all switches.\n";
            String keyboardStart = "smart home";
            bot.sendMessageWithInlineKeyboard(chat_id, welcome, "", keyboardStart);
          }

          if (text == "/AllShutDown") {
            for (int i = 0; i < quantity; i++) {
              digitalWrite(pin[i], LOW);
            }
          }

           if (text == "/AllOn") {
            for (int i = 0; i < quantity; i++) {
              digitalWrite(pin[i], HIGH);
            }
          }

          break;
        } else {
          if (i2 == ((sizeof(chatID_acces)/sizeof(int))-1) && text == "/start" || (sizeof(chatID_acces)/sizeof(int)) == 0 && text == "/start") {
            bot.sendMessage(chat_id, "No access, Chat ID: "+chat_id, "");
          }
        }

        i2++;
      } while (i2<(sizeof(chatID_acces)/sizeof(int)));
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
  
  quantity=sizeof(pin)/sizeof(int);
  for (int i=0; i<quantity; i++) {
  pinMode(pin[i], OUTPUT);
      }

  for (int i=0; i<quantity; i++) {
  if(i==0) keyboardJson += "[";
  keyboardJson += "[{ \"text\" : \"";
  keyboardJson += buttons[i];
  keyboardJson += "\", \"callback_data\" : \"";
  keyboardJson += buttons[i];
  keyboardJson += "\" }]";
  if(i==quantity-1){
    keyboardJson += "]";
    }else{
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
