#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>

#define BOTtoken "6158442821:AAE_H7kh54e2XdpFmCMNvLH0VkAksmz_F5U"
// Bot token in the xxxxx format: xxxxxxxxxxxxxxx, start a conversation with the bot "BotFather" in Telegram and,
// follow the instructions to create a new bot. You will be given a secret token. Do not tell it to anyone.
char ssid[] = "Lenovo-GD888";   // Wifi SSID 
char password[] = "asdfghijk"; // Wifi Password

String buttons1[] = { "LED1","LED2" ,"FAN","Cooler" };
String buttons2[] = { "Lock Door","UnLock Door","Open Window","Close Window" };
// names of connected devices, DOES NOT WORK with Cyrillic!
int pin1[] = {12,13,14,4};
int pin2[] = {26,25,33,32};
// pin1 number to which the executing device is connected (relay, transistor, etc.)

bool protection = 0; // access rights: 0 - available to all users, 1 - access by Chat ID, if it is included in chatID_acces.
int chatID_acces[] = {6157679976};
// Chat IDs that are allowed access are ignored if protection = 0.
// Note: by the command / start in Telegram, if the user does not have permission to control the device, the bot will issue a Chat ID
// this user so that it can be added to chatID_acces. Chat ID is a unique chat number that is issued
// the user who started communicating with the bot.

String on_symbol = "✅ ";  // ON Indicator
String off_symbol = "☑ "; // OFF indicator.

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);
int quantity;
int Bot_mtbs = 3000;
long Bot_lasttime;
bool Start = false;
const int ledpin1 = 12;
int ledStatus = 0;
String keyboardJson = "";

int messageID;

void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  int i = 0;
  int j = 0;

  for (int k = 0; k < numNewMessages; k++) {
    String chat_id = String(bot.messages[k].chat_id);
    String m_id = String(bot.messages[k].message_id);
    String text = bot.messages[k].text;

    if (text == "/switch" && i == 0) {
      executeSwitch(chat_id);
      i++;
    } else if (text == "/security" && j == 0) {
      executeSecurity(chat_id);
      j++;
    }

    if (text == "/start") {
      handleStartCommand(chat_id);
    }
  }
}

void executeSwitch(String chat_id) {
  String statusMessage;
  for (int i1 = 0; i1 < quantity; i1++) {
    digitalWrite(pin1[i1], !digitalRead(pin1[i1]));
    digitalRead(pin1[i1]) ? statusMessage += on_symbol : statusMessage += off_symbol;
    statusMessage += buttons1[i1];
    statusMessage += '\n';
  }
  bot.sendMessageWithInlineKeyboard(chat_id, statusMessage, "", keyboardJson);
}

void executeSecurity(String chat_id) {
  String statusMessage;
  for (int j1 = 0; j1 < quantity; j1++) {
    digitalWrite(pin2[j1], !digitalRead(pin2[j1]));
    digitalRead(pin2[j1]) ? statusMessage += on_symbol : statusMessage += off_symbol;
    statusMessage += buttons2[j1];
    statusMessage += '\n';
  }
  bot.sendMessageWithInlineKeyboard(chat_id, statusMessage, "", keyboardJson);
}

void handleStartCommand(String chat_id) {
  String from_name = "Guest";
  String welcome = "Welcome " + from_name + ".\n";
  welcome += "This is ESP smart switch, controlled via Telegram.\n\n";
  welcome += "/switch : Click to open Switch Board.\n";
  welcome += "/security : Click to check home security.\n";
  String keyboardStart = "smart home";
  bot.sendMessageWithInlineKeyboard(chat_id, welcome, "", keyboardStart);
}

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
