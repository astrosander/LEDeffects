String help = "🔸/all to change every pixel's colour\n"
              "🔸/mode to set mode\n"
              "🔸/help to get commands\n"
              "🔸/bright to set brightness\n";



String Commands = "Enter '/mode a' where is number of mode\n📜List of modes:\n"
                  "2 smooth change of colours for the entire ribbon. 🌈\n"
                  "3 a spinning rainbow. 🌪️🌈\n"
                  "4 random colour change. 🎨\n"
                  "5 running LED 🏃‍♂️💡\n"
                  "6 a running train of LEDs. 🚂💡\n"
                  "7 red and blue rotating. 🔴🔵🔄\n"
                  "8 rotating half red and half blue 🔴🔵🔄\n"
                  "9 random strobe light. ⚡🌈\n"
                  "10 single colour pulsation 💥🌈\n"
                  "11 colour changing pulsation 🌈💥🌈\n"
                  "12 smooth vertical brightness change (for ring) 🔆🔼🔽\n"
                  "13 red LED madness. 🔴💡💥\n"
                  "14 random colour madness. 🎨💥\n"
                  "15 white blue red running in a circle 🏃‍♂️🔵⚪🔴🔄\n"
                  "16 radiation icon pulsating ☢️💥🌈\n"
                  "17 red LED running in a circle 🏃‍♂️🔴🔄\n"
                  "18 white and blue gradient. ⚪🔵🌈\n"
                  "19 same thing's going on. ⏭️🔄\n"
                  "20 red flashes going down 🔴⬇️💥\n"
                  "21 crescent moon. 🌙\n"
                  "22 flame effect. 🔥🔥🔥\n"
                  "23 rainbow in the vertical plane. 🌈🔼🔽\n"
                  "24 Pac-Man. 🎮😄\n"
                  "25 random flash madness. 💥💥💥\n"
                  "26 police flasher. 🚨🔵🔴\n"
                  "27 RGB propeller. 🔄🔴🔵⚪\n"
                  "28 random red flashes in the vertical plane. 🔴💥🔼🔽\n"
                  "29 greens running around randomly. 🟢🏃‍♂️🔄\n"
                  "30 greens running around randomly. 🟢🏃‍♂️🔄\n"
                  "31 something's broken ❌🔧\n"
                  "32 something's broken. ❌🔧\n"
                  "33 smooth colour fills 🎨🔆\n"
                  "34 running LEDs. 🏃‍♂️💡\n"
                  "35 line lights. 🚦💡\n"
                  "36 running circle sectors (doesn't work) 🔴🟢🔵🔄\n"
                  "37 very smooth rotating rainbows. 🌈🔄🌈\n"
                  "38 random multi-coloured lights (1 - all dancing, 0 - random 1 diode) 🎨💃🔴🔵🟢🌈\n"
                  "39 running lights. 🏃‍♂️💡\n"
                  "40 random flashes of white 💥⚪\n"
                  "41 random flashes of white on a white background 💥⚪🔳\n"
                  "42 running every 3 times. 🏃‍♂️🔄⏰\n"
                  "43 running every 3 rainbows. 🏃‍♂️🔄🌈⏰\n"
                  "44 strobe lights. ⚡💡💥\n"
                  "45 bouncing balls. 🏀⬆️⬇️\n"
                  "46 colored bouncing balls. 🌈🏀⬆️⬇️\n"
                  "888 long demo. 🎉🎮\n"
                  "889 short demo. 🎉🎮\n"
                  "999 pause. ⏸️";


#include "FastLED.h"          // library for working with LED strip
#include <FastBot.h>
#include <vector> 

#define LED_COUNT 120          // number of LEDs in the ring/strip
#define LED_DT 2U             // pin to which the DIN of the strip is connected

#define WIFI_SSID "login"
#define WIFI_PASS "pass"
#define BOT_TOKEN "xxxx"

int max_bright = 250;         // maximum brightness (0 - 255)
int ledMode = 3;
int f = 0;

byte ballColors[3][3] = {
  {0xff, 0, 0},
  {0xff, 0xff, 0xff},
  {0   , 0   , 0xff},
};

FastBot bot(BOT_TOKEN);

// ---------------UTILITY VARIABLES-----------------
int BOTTOM_INDEX = 0;        // start LED
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
// ---------------UTILITY VARIABLES-----------------


void blink(int t) // in miliseconds
{
    digitalWrite(LED_BUILTIN, HIGH);
    delay(t);
    digitalWrite(LED_BUILTIN, LOW);
    delay(t);
}
void one_color_all(int cred, int cgrn, int cblu) {       //-SET ALL LEDS TO ONE COLOR

  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i].setRGB( cred, cgrn, cblu);
  }
}

void one_color_one(int cred, int cgrn, int cblu, int pos) {       //-SET ONE COLOR TO ONE LED

  leds[pos].setRGB( cred, cgrn, cblu);
}

void one_color_allHSV(int ahue) {    //-SET ALL LEDS TO ONE COLOR (HSV)
  for (int i = 0 ; i < LED_COUNT; i++ ) {
    leds[i] = CHSV(ahue, thissat, 255);
  }
}


void connectWiFi() {
  delay(2000);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    for(int i = 0; i < 5; i++) blink(50);

    if (millis() > 15000) ESP.restart();
  }

  digitalWrite(LED_BUILTIN, HIGH);
  Serial.println("Connected");
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

void newMsg(FB_msg& msg) {

  blink(500);

  Serial.print(msg.chatID); // Chat ID 
  Serial.print(", ");
  Serial.print(msg.username); // login
  Serial.print(", ");
  Serial.println(msg.text); // text
  
  std::vector<String> words = getWordsFromString(msg.text);
  
  if (words[0] == "/all") {
    if(words.size() != 2 and words.size() != 4) bot.sendMessage("❗Send me color which u would like to set\nFormat: '/all #4a7044' or '/all 74 112 68'", msg.chatID);

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
    else 
    {
      for(int i = 1; i < 4; i++){
        int val = words[i].toInt();
        if(val < 0 or val > 255) 
        {
          bot.sendMessage("❗Pls enter all INTEGERS in the range [0; 255]", msg.chatID);       
          return;  
        }
        one_color_all(words[1].toInt(), words[2].toInt(), words[3].toInt());
      }
    } 
    
    LEDS.show();
    bot.sendMessage("Successfully✅", msg.chatID);

    return;
  }

  if (words[0] == "/mode" or words[0] == "/bright") {
    int secondWord = words[1].toInt();

    if (words[0] == "/mode")
    {
      if(words.size() != 2) bot.sendMessage(Commands, msg.chatID);
      else{
        change_mode(secondWord);
        bot.sendMessage("Successfully✅", msg.chatID);
      }
    }
    else{
      if(words.size() == 2 and secondWord >= 0 and secondWord <= 255){
        LEDS.setBrightness(secondWord);
        bot.sendMessage("Successfully✅", msg.chatID);
      } 
      else bot.sendMessage("❗Pls enter sth INTEGER in the range [0; 255]", msg.chatID);  
    }
    return;
  }
  
  if (msg.text == "/start" or msg.text == "/help") bot.sendMessage(help, msg.chatID);
  else bot.sendMessage("Invaid command❌\n Use /help to list available commands", msg.chatID);
}

void setup()
{
  Serial.begin(9600); // open port for communication
  pinMode(LED_BUILTIN, OUTPUT);

  connectWiFi();
  bot.attach(newMsg);
  
  LEDS.setBrightness(max_bright); // limit maximum brightness
  LEDS.addLeds<WS2811, LED_DT, GRB>(leds, LED_COUNT); // settings for our ribbon (ribbon on WS2811, WS2812, WS2812B)
  one_color_all(0, 0, 0); // extinguish all LEDs
  LEDS.show(); // send command  
}

void loop() {
  switch (ledMode) {
    case 999: bot.tick(); break; // pause
    case 2: bot.tick(); rainbow_fade(); break; // smooth colour change of the entire tape
    case 3: bot.tick(); rainbow_loop(); break; // spinning rainbow
    case 4: bot.tick(); random_burst(); break; // random colour change
    case 5: bot.tick(); color_bounce(); break; // running LED
    case 6: bot.tick(); color_bounceFADE(); break; // running LED
    case 7: bot.tick(); ems_lightsONE(); break; // red and blue running
    case 8: bot.tick(); ems_lightsALL(); break; // half red and half blue rotate
    case 9: bot.tick(); flicker(); break; // random strobe
    case 10: bot.tick(); pulse_one_color_all(); break; // single colour pulsing
    case 11: bot.tick(); pulse_one_color_all_rev(); break; // pulsation with colour change
    case 12: bot.tick(); fade_vertical(); break; // pulse_one_color_all_rev(); break; // pulse_rev (for ring)
    case 13: bot.tick(); rule30(); break; // red LED fade
    case 14: bot.tick(); random_march(); break; // random colour madness
    case 15: bot.tick(); rwb_march(); break; // white blue red run in a circle (PATRIOTISM!)
    case 16: bot.tick(); radiation(); break; // radiation icon pulses
    case 17: bot.tick(); color_loop_vardelay(); break; // red LED is running in a circle
    case 18: bot.tick(); white_temps(); break; // white_blue gradient (?)
    case 19: bot.tick(); sin_bright_wave(); break; // this is also weird
    case 20: bot.tick(); pop_horizontal(); break; // red flashes going down
    case 21: bot.tick(); quad_bright_curve(); break; // crescent
    case 22: bot.tick(); flame(); break; // flame effect
    case 23: bot.tick(); rainbow_vertical(); break; // rainbow in the vertical plane (ring)
    case 24: bot.tick(); pacman(); break; // pacman
    case 25: bot.tick(); random_color_pop(); break; // random flash madness
    case 26: bot.tick(); ems_lightsSTROBE(); break; // police flasher
    case 27: bot.tick(); rgb_propeller(); break; // RGB propeller
    case 28: bot.tick(); kitt(); break; // random red flashes in the vertical plane
    case 29: bot.tick(); matrix(); break; // green flashes randomly
    case 30: bot.tick(); new_rainbow_loop(); break; // cool smooth spinning rainbow
    case 31: bot.tick(); strip_march_ccw(); break; // something broke
    case 32: bot.tick(); strip_march_cw(); break; // something broke
    case 33: bot.tick(); colorWipe(0x00, 0xff, 0x00, thisdelay);
      colorWipe(0x00, 0x00, 0x00, thisdelay); break; // colorWipe(0x00, 0xff, 0x00, thisdelay); // colorWipe(0x00, 0x00, 0x00, thisdelay); break; // colorWipe(0x00, 0x00, 0x00, thisdelay).
    case 34: bot.tick(); CylonBounce(0xff, 0, 0, 4, 10, thisdelay); break; // running LEDs
    case 35: bot.tick(); Fire(55, 120, thisdelay); break; // linear fire
    case 36: bot.tick(); NewKITT(0xff, 0, 0, 8, 10, thisdelay); break; // running lap sectors (not working)
    case 37: bot.tick(); rainbowCycle(thisdelay); break; // a very smooth spinning rainbow
    case 38: bot.tick(); TwinkleRandom(20, thisdelay, 1); break; // random multi-colored switch-on (1 - all dancing, 0 - random 1 diode)
    case 39: bot.tick(); RunningLights(0xff, 0xff, 0x00, thisdelay); break; // running lights
    case 40: bot.tick(); Sparkle(0xff, 0xff, 0xff, thisdelay); break; // random white flashes
    case 41: bot.tick(); SnowSparkle(0x10, 0x10, 0x10, thisdelay, random(100, 1000)); break; // random white flash on white background
    case 42: bot.tick(); theaterChase(0xff, 0, 0, thisdelay); break; // running every 3 (NUMBER OF LEDs MUST BE OTHER than 0)
    case 43: bot.tick(); theaterChaseRainbow(thisdelay); break; // running every 3 rainbows (NUMBER OF LEDs MUST BE QUITE 3)
    case 44: bot.tick(); Strobe(0xff, 0xff, 0xff, 10, thisdelay, 1000); break; // strobe

    case 45: bot.tick(); BouncingBalls(0xff, 0, 0, 3); break; // bouncing balls
    case 46: bot.tick(); BouncingColoredBalls(3, ballColors); break; // bouncing colored balls

    case 888: bot.tick(); demo_modeA(); break; // long demo
    case 889: bot.tick(); demo_modeB(); break; // short demo
    default: bot.tick();
  }
}
