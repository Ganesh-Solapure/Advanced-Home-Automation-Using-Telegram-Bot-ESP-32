#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "6158442821:AAE_H7kh54e2XdpFmCMNvLH0VkAksmz_F5U"
char ssid[] = "Lenovo-GD888";
char password[] = "asdfghijk";

String buttons1[] = {"LED1", "LED2", "FAN", "Cooler"};
String buttons2[] = {"Lock Door", "UnLock Door", "Open Window", "Close Window"};
int pin1[] = {12, 13, 14, 4};
int pin2[] = {27, 2, 1, 5};
bool protection = 0;
int chatID_acces[] = {6157679976};
String on_symbol = "✅ ";
String off_symbol = "☑ ";

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int quantity;
int Bot_mtbs = 3000;
long Bot_lasttime;
String keyboardJson = "";

void handleNewMessages(int numNewMessages);

void startCommand(String chat_id, String from_name);

void setup() {
  Serial.begin(115200);

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

  quantity = sizeof(pin1) / sizeof(int);
  for (int i = 0; i < quantity; i++) {
    pinMode(pin1[i], OUTPUT);
  }

  for (int i = 0; i < quantity; i++) {
    if (i == 0)
      keyboardJson += "[";
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
  delay(10);
  client.setInsecure();
}

void loop() {
  if (millis() > Bot_lasttime + Bot_mtbs) {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

    while (numNewMessages) {
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    Bot_lasttime = millis();
  }
}

void handleNewMessages(int numNewMessages) {
  for (int i = 0; i < numNewMessages; i++) {
    String chat_id = String(bot.messages[i].chat_id);
    String text = bot.messages[i].text;

    if (text == "/start") {
      startCommand(chat_id, bot.messages[i].from_name);
    }
  }
}

void startCommand(String chat_id, String from_name) {
  String welcome = "Welcome " + from_name + ".\n";
  welcome += "This is ESP smart switch, controlled via Telegram.\n\n";
  welcome += "/switch : Click to open Switch Board.\n";
  String keyboardStart = "smart home";
  bot.sendMessageWithInlineKeyboard(chat_id, welcome, "", keyboardStart);
}
