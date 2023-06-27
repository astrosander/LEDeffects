String help = "/all to change every pixel's colour\n"
              "Send /mode and one of these rates\n"
              "2 smooth change of colours for the entire ribbon."
              "3 a spinning rainbow."
              "4 random colour change."
              "5 running LED"
              "6 a running train of LEDs."
              "7 red and blue rotating."
              "8 rotating half red and half blue"
              "9 random strobe light."
              "10 single colour pulsation"
              "11 colour changing pulsation"
              "12 smooth vertical brightness change (for ring)"
              "13 red LED madness."
              "14 random colour madness."
              "15 white blue red running in a circle\n"
              "16 radiation icon pulsating\n"
              "17 red LED running in a circle\n"
              "18 white and blue gradient."
              "19 same thing's going on."
              "20 red flashes going down"
              "21 crescent moon."
              "22 flame effect."
              "23 rainbow in the vertical plane."
              "24 Pac-Man."
              "25 random flash madness."
              "26 police flasher."
              "27 RGB propeller."
              "28 random red flashes in the vertical plane."
              "29 greens running around randomly."
              "30 greens running around randomly."
              "31 something's broken."
              "32 something's broken."
              "33 smooth colour fills"
              "34 running LEDs."
              "35 line lights."
              "36 running circle sectors (doesn't work)\n"
              "37 very smooth rotating rainbows."
              "38 random multi-coloured lights (1 - all dancing, 0 - random 1 diode)\n"
              "39 running lights."
              "40 random flashes of white"
              "41 random flashes of white on a white background\n"
              "42 running every 3 times."
              "43 running every 3 rainbows."
              "44 strobe lights."
              "45 bouncing balls."
              "46 colored bouncing balls."
              "888 long demo."
              "889 short demo."
              "999 pause."ж


#include "FastLED.h"          // библиотека для работы с лентой

#define LED_COUNT 120          // число светодиодов в кольце/ленте
#define LED_DT 2U             // пин, куда подключен DIN ленты

int max_bright = 250;         // максимальная яркость (0 - 255)
int ledMode = 3;
int f = 0;

#define WIFI_SSID "login"
#define WIFI_PASS "pass"
#define BOT_TOKEN "xxxx"

#include <FastBot.h>
#include <vector> 
FastBot bot(BOT_TOKEN);

byte ballColors[3][3] = {
  {0xff, 0, 0},
  {0xff, 0xff, 0xff},
  {0   , 0   , 0xff},
};

// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------
int BOTTOM_INDEX = 0;        // светодиод начала отсчёта
int TOP_INDEX = int(LED_COUNT / 2);
int EVENODD = LED_COUNT % 2;
struct CRGB leds[LED_COUNT];
int ledsX[LED_COUNT][3];     //-ARRAY FOR COPYING WHATS IN THE LED STRIP CURRENTLY (FOR CELL-AUTOMATA, MARCH, ETC)

int thisdelay = 20;          //-FX LOOPS DELAY VAR
int thisstep = 10;            //-FX LOOPS DELAY VAR
int thishue = 0;             //-FX LOOPS DELAY VAR
int thissat = 255;           //-FX LOOPS DELAY VAR

int thisindex = 0;
int thisRED = 0;
int thisGRN = 0;
int thisBLU = 0;

int idex = 0;                //-LED INDEX (0 to LED_COUNT-1
int ihue = 0;                //-HUE (0-255)
int ibright = 0;             //-BRIGHTNESS (0-255)
int isat = 0;                //-SATURATION (0-255)
int bouncedirection = 0;     //-SWITCH FOR COLOR BOUNCE (0-1)
float tcount = 0.0;          //-INC VAR FOR SIN LOOPS
int lcount = 0;              //-ANOTHER COUNTING VAR
// ---------------СЛУЖЕБНЫЕ ПЕРЕМЕННЫЕ-----------------

void one_color_all(int cred, int cgrn, int cblu) {       //-SET ALL LEDS TO ONE COLOR
  // Serial.println(cred);
  // Serial.println(cgrn);
  // Serial.println(cblu);

  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i].setRGB( cred, cgrn, cblu);
  }
}

void one_color_one(int cred, int cgrn, int cblu, int pos) {       //-SET ALL LEDS TO ONE COLOR
  // Serial.println(cred);
  // Serial.println(cgrn);
  // Serial.println(cblu);
  // Serial.println(pos);

  leds[pos].setRGB( cred, cgrn, cblu);
}


void one_color_allHSV(int ahue) {    //-SET ALL LEDS TO ONE COLOR (HSV)
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i] = CHSV(ahue, thissat, 255);
  }
}




void connectWiFi() {
  delay(2000);
  // Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    // Serial.print(".");
    if (millis() > 15000) ESP.restart();
  }
  // Serial.println("Connected");
}


void change_mode(int newmode) {
  thissat = 255;
  switch (newmode) {
    case 0: one_color_all(0, 0, 0); LEDS.show(); break; //---ALL OFF
    case 1: one_color_all(255, 255, 255); LEDS.show(); break; //---ALL ON
    case 2: thisdelay = 20; break;                      //---STRIP RAINBOW FADE
    case 3: thisdelay = 20; thisstep = 10; break;       //---RAINBOW LOOP
    case 4: thisdelay = 20; break;                      //---RANDOM BURST
    case 5: thisdelay = 20; thishue = 0; break;         //---CYLON v1
    case 6: thisdelay = 40; thishue = 0; break;         //---CYLON v2
    case 7: thisdelay = 40; thishue = 0; break;         //---POLICE LIGHTS SINGLE
    case 8: thisdelay = 40; thishue = 0; break;         //---POLICE LIGHTS SOLID
    case 9: thishue = 160; thissat = 50; break;         //---STRIP FLICKER
    case 10: thisdelay = 15; thishue = 0; break;        //---PULSE COLOR BRIGHTNESS
    case 11: thisdelay = 15; thishue = 0; break;        //---PULSE COLOR SATURATION
    case 12: thisdelay = 60; thishue = 180; break;      //---VERTICAL SOMETHING
    case 13: thisdelay = 100; break;                    //---CELL AUTO - RULE 30 (RED)
    case 14: thisdelay = 40; break;                     //---MARCH RANDOM COLORS
    case 15: thisdelay = 80; break;                     //---MARCH RWB COLORS
    case 16: thisdelay = 60; thishue = 95; break;       //---RADIATION SYMBOL
    //---PLACEHOLDER FOR COLOR LOOP VAR DELAY VARS
    case 19: thisdelay = 35; thishue = 180; break;      //---SIN WAVE BRIGHTNESS
    case 20: thisdelay = 100; thishue = 0; break;       //---POP LEFT/RIGHT
    case 21: thisdelay = 100; thishue = 180; break;     //---QUADRATIC BRIGHTNESS CURVE
    //---PLACEHOLDER FOR FLAME VARS
    case 23: thisdelay = 50; thisstep = 15; break;      //---VERITCAL RAINBOW
    case 24: thisdelay = 50; break;                     //---PACMAN
    case 25: thisdelay = 35; break;                     //---RANDOM COLOR POP
    case 26: thisdelay = 25; thishue = 0; break;        //---EMERGECNY STROBE
    case 27: thisdelay = 25; thishue = 0; break;        //---RGB PROPELLER
    case 28: thisdelay = 100; thishue = 0; break;       //---KITT
    case 29: thisdelay = 50; thishue = 95; break;       //---MATRIX RAIN
    case 30: thisdelay = 5; break;                      //---NEW RAINBOW LOOP
    case 31: thisdelay = 100; break;                    //---MARCH STRIP NOW CCW
    case 32: thisdelay = 100; break;                    //---MARCH STRIP NOW CCW
    case 33: thisdelay = 50; break;                     // colorWipe
    case 34: thisdelay = 50; break;                     // CylonBounce
    case 35: thisdelay = 15; break;                     // Fire
    case 36: thisdelay = 50; break;                     // NewKITT
    case 37: thisdelay = 20; break;                     // rainbowCycle
    case 38: thisdelay = 10; break;                     // rainbowTwinkle
    case 39: thisdelay = 50; break;                     // RunningLights
    case 40: thisdelay = 0; break;                      // Sparkle
    case 41: thisdelay = 20; break;                     // SnowSparkle
    case 42: thisdelay = 50; break;                     // theaterChase
    case 43: thisdelay = 50; break;                     // theaterChaseRainbow
    case 44: thisdelay = 100; break;                    // Strobe

    case 101: one_color_all(255, 0, 0); LEDS.show(); break; //---ALL RED
    case 102: one_color_all(0, 255, 0); LEDS.show(); break; //---ALL GREEN
    case 103: one_color_all(0, 0, 255); LEDS.show(); break; //---ALL BLUE
    case 104: one_color_all(255, 255, 0); LEDS.show(); break; //---ALL COLOR X
    case 105: one_color_all(0, 255, 255); LEDS.show(); break; //---ALL COLOR Y
    case 106: one_color_all(255, 0, 255); LEDS.show(); break; //---ALL COLOR Z
  }
  bouncedirection = 0;
  one_color_all(0, 0, 0);
  ledMode = newmode;
}



String removeSpaces(String inputString) {
  String outputString = "";

  for (int i = 0; i < inputString.length(); i++) {
    if (inputString.charAt(i) != ' ') outputString += inputString.charAt(i);
  }

  return outputString;
}

std::vector<String> getWordsFromString(String inputString) {
  std::vector<String> words;  // Vector to store the words
  int startIndex = 0;  // Starting index for extracting words
  int endIndex = 0;  // Ending index for extracting words
  
  // Loop through the input string
  for (int i = 0; i < inputString.length(); i++) {
    // Check if the current character is a space or the last character
    if (inputString.charAt(i) == ' ' || i == inputString.length() - 1) {
      endIndex = i;  // Set the end index to the current position
      
      // Extract the word from the string and add it to the vector
      String word = inputString.substring(startIndex, endIndex + 1);
      words.push_back(word);
      
      // Update the start index to the next position
      startIndex = i + 1;
    }
  }

  for (int i = 0; i < words.size(); i++) words[i] = removeSpaces(words[i]);
  
  return words;
}

// обработчик сообщений

bool hexToRGB(String hexColor, int pos) {
  // Remove the '#' character if present
  hexColor.replace("#", "");

  // Extract individual color components
  String redHex = hexColor.substring(0, 2);
  String greenHex = hexColor.substring(2, 4);
  String blueHex = hexColor.substring(4, 6);

  // Convert hex values to decimal values
  int red = strtol(redHex.c_str(), NULL, 16);
  int green = strtol(greenHex.c_str(), NULL, 16);
  int blue = strtol(blueHex.c_str(), NULL, 16);

  if(red < 0 or red > 255 or green < 0 or green > 255 or blue < 0 or blue > 255) return 1;

  if(pos == -1) one_color_all(red, green, blue);
  else one_color_one(red, green, blue, pos);
  LEDS.show();

  return 0;
}

String ErrorMsg = "Incorrect!\nFormat: ""#4a7044"" or ""74, 112, 68""";
String ErrorMsg1 = "Incorrect!\nFormat: '#4a7044, pos' or '74, 112, 68, pos""";

void newMsg(FB_msg& msg) {
  // выводим ID чата, имя юзера и текст сообщения

  // Serial.print(msg.chatID);     // ID чата 
  // Serial.print(", ");
  // Serial.print(msg.username);   // логин
  // Serial.print(", ");
  // Serial.println(msg.text);     // текст

  String inputString = msg.text+" ";
  std::vector<String> words = getWordsFromString(msg.text);
  
  if (msg.text == "/stop") {
    f = 0;
    change_mode(3);
    bot.sendMessage("Ready!", msg.chatID);
  }

  if (words[0] == "/all") {
    if(words.size() != 2 or words.size() != 4) bot.sendMessage("Send me color which u would like to set\nFormat: '/all #4a7044' or '/all 74 112 68'", msg.chatID);
    // bot.sendMessage("Send me color which u would like to set\nFormat: '#4a7044' or '74, 112, 68'", msg.chatID);

    // words[0] = words[0].substring(0, words[0].length() - 1);
    // words[1] = words[1].substring(0, words[1].length() - 1);

    for(int i = 1; i < 4; i++){
      int val = words[i].toInt();
      if(val < 0 or val > 255) 
      {
        bot.sendMessage("Pls enter all INTEGERS in the range [0; 255]", msg.chatID);       
        return;  
      }
    }

    change_mode(1);
    if(words[1][0] == '#')
    {
        String hexColor = words[1]; 
        hexColor.replace("#", "");

        
        String redHex = hexColor.substring(0, 2);
        String greenHex = hexColor.substring(2, 4);
        String blueHex = hexColor.substring(4, 6);

        // Convert hex values to decimal values
        int red = strtol(redHex.c_str(), NULL, 16);
        int green = strtol(greenHex.c_str(), NULL, 16);
        int blue = strtol(blueHex.c_str(), NULL, 16);
        one_color_all(red, green, blue);
        
    }
    else one_color_all(words[1].toInt(), words[2].toInt(), words[3].toInt());
    
    LEDS.show();
  }



  // if(f)
  // {
  //   // if(f == 1)
  //   // {
  //   //   if(words.size() > 3 or words.size() == 2) bot.sendMessage(ErrorMsg, msg.chatID);
  //   //   if(words.size() == 1) 
  //   //   {
  //   //     if(words[0][0] == '#')
  //   //     {
  //   //       if(hexToRGB(words[0], -1)) bot.sendMessage("Incorrect!", msg.chatID);
  //   //       else bot.sendMessage("Succefully!", msg.chatID);
  //   //     }
        
  //   //     else bot.sendMessage(ErrorMsg, msg.chatID);
  //   //   }
  //   //   else 
  //   //   {
  //   //     words[0] = words[0].substring(0, words[0].length() - 1);
  //   //     words[1] = words[1].substring(0, words[1].length() - 1);

  //   //     for(int i = 0; i < 3; i++){
  //   //       int val = words[i].toInt();
  //   //       if(val < 0 or val > 255) 
  //   //       {
  //   //         bot.sendMessage("Pls enter all INTEGERS in the range [0; 255]", msg.chatID);       
  //   //         return;  
  //   //       }
  //   //     }

  //   //     change_mode(1);

  //   //     bot.sendMessage("Lolkkk", msg.chatID); 
  //   //     one_color_all(words[0].toInt(), words[1].toInt(), words[2].toInt());
  //   //     LEDS.show();
        

  //   //     bot.sendMessage("Succefully!", msg.chatID);
  //   //   }
  //   // }

  //   // else
  //   bot.sendMessage("Lodasdsa", msg.chatID);
    
  //   // if(words.size() != 4 and words.size() != 2) bot.sendMessage(ErrorMsg1, msg.chatID);
  //   if(words.size() == 2) 
  //   {
  //     if(words[0][0] == '#')
  //     {
  //       if(hexToRGB(words[0], words[1].toInt())) bot.sendMessage(ErrorMsg1, msg.chatID);
  //       else bot.sendMessage("Succefully!", msg.chatID);
  //     }
      
  //     else bot.sendMessage(ErrorMsg1, msg.chatID);
  //   }
  //   else 
  //   {
  //     for(int i = 0; i < 3; i++) words[i] = words[i].substring(0, words[i].length() - 1);

  //     for(int i = 0; i < 3; i++){
  //       int val = words[i].toInt();
  //       if(val < 0 or val > 255) 
  //       {
  //         bot.sendMessage("Pls enter all INTEGERS in the range [0; 255]", msg.chatID);       
  //         return;  
  //       }
  //     }

  //     // one_color_all(0, 0, 0);
      
  //     one_color_one(words[0].toInt(), words[1].toInt(), words[2].toInt(), words[3].toInt());
  //     LEDS.show();
  //     bot.sendMessage("Succefully!", msg.chatID);
  //   }   
  //   // return;
  // }

  // if (words[0] == "/draw") {
    
  //   change_mode(1);
  //   one_color_all(0, 0, 0);
  //   LEDS.show();

  //   f = 2;
  // }

  if (words.size() == 2) {
    int secondWord = words[1].toInt();
    String com = words[0];
    // Serial.println(words[1]);
    // Serial.println(secondWord);

    if (com == "/mode")
    {
      change_mode(secondWord);
      bot.sendMessage("Successfully!", msg.chatID);
    }
    else{
      if (com == "/bright"){
        if(secondWord >= 0 and secondWord <= 255){
          LEDS.setBrightness(secondWord);
          bot.sendMessage("Successfully!", msg.chatID);
        } 
        else bot.sendMessage("Pls enter sth INTEGER in the range [0; 255]", msg.chatID);         
      } 
      else bot.sendMessage("May be you mean /mode or /bright", msg.chatID);
    }
  }
  
  else {
    if (msg.text == "/start" or msg.text == "/help") bot.sendMessage(help, msg.chatID);
    // else bot.sendMessage(Ans, msg.chatID);
  }

}

/*
  Стартовый режим
  0 - все выключены
  1 - все включены
  3 - кольцевая радуга
  888 - демо-режим
*/

// цвета мячиков для режима

void setup()
{
  connectWiFi();\
  bot.attach(newMsg);
  // Serial.begin(9600);              // открыть порт для связи
  LEDS.setBrightness(max_bright);  // ограничить максимальную яркость

  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT);  // настрйоки для нашей ленты (ленты на WS2811, WS2812, WS2812B)
  one_color_all(0, 0, 0);          // погасить все светодиоды
  LEDS.show();                     // отослать команду
  
}



void loop() {
  switch (ledMode) {
    case 999: bot.tick();  break;                           // пазуа
    case  2: bot.tick(); rainbow_fade(); break;            // плавная смена цветов всей ленты
    case  3: bot.tick(); rainbow_loop();  break;            // крутящаяся радуга
    case  4: bot.tick(); random_burst(); break;            // случайная смена цветов
    case  5: bot.tick(); color_bounce(); break;            // бегающий светодиод
    case  6: bot.tick(); color_bounceFADE(); break;        // бегающий паровозик светодиодов
    case  7: bot.tick(); ems_lightsONE(); break;           // вращаются красный и синий
    case  8: bot.tick(); ems_lightsALL(); break;           // вращается половина красных и половина синих
    case  9: bot.tick(); flicker(); break;                 // случайный стробоскоп
    case 10: bot.tick(); pulse_one_color_all(); break;     // пульсация одним цветом
    case 11: bot.tick(); pulse_one_color_all_rev(); break; // пульсация со сменой цветов
    case 12: bot.tick(); fade_vertical(); break;           // плавная смена яркости по вертикали (для кольца)
    case 13: bot.tick(); rule30(); break;                  // безумие красных светодиодов
    case 14: bot.tick(); random_march(); break;            // безумие случайных цветов
    case 15: bot.tick(); rwb_march(); break;               // белый синий красный бегут по кругу (ПАТРИОТИЗМ!)
    case 16: bot.tick(); radiation(); break;               // пульсирует значок радиации
    case 17: bot.tick(); color_loop_vardelay(); break;     // красный светодиод бегает по кругу
    case 18: bot.tick(); white_temps(); break;             // бело синий градиент (?)
    case 19: bot.tick(); sin_bright_wave(); break;         // тоже хрень какая то
    case 20: bot.tick(); pop_horizontal(); break;          // красные вспышки спускаются вниз
    case 21: bot.tick(); quad_bright_curve(); break;       // полумесяц
    case 22: bot.tick(); flame(); break;                   // эффект пламени
    case 23: bot.tick(); rainbow_vertical(); break;        // радуга в вертикаьной плоскости (кольцо)
    case 24: bot.tick(); pacman(); break;                  // пакман
    case 25: bot.tick(); random_color_pop(); break;        // безумие случайных вспышек
    case 26: bot.tick(); ems_lightsSTROBE(); break;        // полицейская мигалка
    case 27: bot.tick(); rgb_propeller(); break;           // RGB пропеллер
    case 28: bot.tick(); kitt(); break;                    // случайные вспышки красного в вертикаьной плоскости
    case 29: bot.tick(); matrix(); break;                  // зелёненькие бегают по кругу случайно
    case 30: bot.tick(); new_rainbow_loop(); break;        // крутая плавная вращающаяся радуга
    case 31: bot.tick(); strip_march_ccw(); break;         // чёт сломалось
    case 32: bot.tick(); strip_march_cw(); break;          // чёт сломалось
    case 33: bot.tick(); colorWipe(0x00, 0xff, 0x00, thisdelay);
      colorWipe(0x00, 0x00, 0x00, thisdelay); break;                                // плавное заполнение цветом
    case 34: bot.tick(); CylonBounce(0xff, 0, 0, 4, 10, thisdelay); break;                      // бегающие светодиоды
    case 35: bot.tick(); Fire(55, 120, thisdelay); break;                                       // линейный огонь
    case 36: bot.tick(); NewKITT(0xff, 0, 0, 8, 10, thisdelay); break;                          // беготня секторов круга (не работает)
    case 37: bot.tick(); rainbowCycle(thisdelay); break;                                        // очень плавная вращающаяся радуга
    case 38: bot.tick(); TwinkleRandom(20, thisdelay, 1); break;                                // случайные разноцветные включения (1 - танцуют все, 0 - случайный 1 диод)
    case 39: bot.tick(); RunningLights(0xff, 0xff, 0x00, thisdelay); break;                     // бегущие огни
    case 40: bot.tick(); Sparkle(0xff, 0xff, 0xff, thisdelay); break;                           // случайные вспышки белого цвета
    case 41: bot.tick(); SnowSparkle(0x10, 0x10, 0x10, thisdelay, random(100, 1000)); break;    // случайные вспышки белого цвета на белом фоне
    case 42: bot.tick(); theaterChase(0xff, 0, 0, thisdelay); break;                            // бегущие каждые 3 (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ НЕЧЁТНОЕ)
    case 43: bot.tick(); theaterChaseRainbow(thisdelay); break;                                 // бегущие каждые 3 радуга (ЧИСЛО СВЕТОДИОДОВ ДОЛЖНО БЫТЬ КРАТНО 3)
    case 44: bot.tick(); Strobe(0xff, 0xff, 0xff, 10, thisdelay, 1000); break;                  // стробоскоп

    case 45: bot.tick(); BouncingBalls(0xff, 0, 0, 3); break;                                   // прыгающие мячики
    case 46: bot.tick(); BouncingColoredBalls(3, ballColors); break;                            // прыгающие мячики цветные

    case 888: bot.tick(); demo_modeA(); break;             // длинное демо
    case 889: bot.tick(); demo_modeB(); break;             // короткое демо
    default: bot.tick();
  }
}
