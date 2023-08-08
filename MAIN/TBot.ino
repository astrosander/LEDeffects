String help = "🔸/all to change every pixel's colour\n"
              "🔸/mode to set mode\n"
              "🔸/help to get commands\n"
              "🔸/restart to restart ESP\n"
              "🔸/bright to set brightness\n"
              "🔸/get_mode to get mode\n\n"
              "🎨Custom colours\n"
              "⚫/black\n"
              "⚪️/white\n"
              "🔴/red\n"
              "🟢/green\n"
              "🔵/blue\n"
              "🟠/orange\n"
              "🟣/lavender\n"
              "🖌️/start_drawing drawing pixel-to-pixel\n";



String Commands = "Enter /mode a where a is number of mode\n📜List of modes:\n"
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
                  "46 colored bouncing balls. 🎨🏀⬆️⬇️\n"
                  "888 long demo. 🎉🎮\n"
                  "889 short demo. 🎉🎮\n"
                  "999 pause. ⏸️";



String removeSpaces(String inputString) {
  String outputString = "";
  for (int i = 0; i < inputString.length(); i++) {
    if (inputString[i] != ' ') outputString += inputString[i];
  }
  return outputString;
}


std::vector<String> getWordsFromString(String inputString) {
  std::vector<String> words;  // Vector to store the words
  int startIndex = 0;         // Starting index for extracting words
  int endIndex = 0;           // Ending index for extracting words

  for (int i = 0; i < inputString.length(); i++) {
    if (inputString.charAt(i) == ' ' || i == inputString.length() - 1) {
      endIndex = i;  // Set the end index to the current position

      String word = inputString.substring(startIndex, endIndex + 1);
      words.push_back(word);

      startIndex = i + 1;
    }
  }

  for (int i = 0; i < words.size(); i++) words[i] = removeSpaces(words[i]);

  return words;
}


void connectWiFi() {
  delay(2000);
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");

    for (int i = 0; i < 5; i++) blink(50);

    if (millis() > 15000) ESP.restart();
  }

  change_mode(1, 0);

  digitalWrite(LED_BUILTIN, LOW);

  one_color_all(0, 255, 0);
  LEDS.show();

  Serial.println("Connected");

  digitalWrite(LED_BUILTIN, HIGH);

  FirstLaunch();

  bot.sendMessage("⚡ " + String(WiFi.hostname().c_str()) + " is connected", MyId);
}



void newMsg(FB_msg& msg) {

  String review = msg.chatID + ", " + msg.username + ", " + msg.text;

  if(MyId != msg.chatID) bot.sendMessage(review, MyId);
  
  Serial.println(review); 
  
  std::vector<String> words = getWordsFromString(msg.text);

  if (msg.text == "/reset" or msg.text == "/restart") {bot.sendMessage("Proccecing🔁", msg.chatID);rst = 1;return;}

  if (msg.text == "/start_drawing")
  {
    f = 1;

    change_mode(1000, 0); cone_color_all(0, 0, 0); LEDS.show(); 

    bot.sendMessage("Successfully✅", msg.chatID);
    bot.sendMessage("Send me color which u would like to set\nFormat: '/pxl #4a7044 pos' or '/pxl 74 112 68 pos'\n❗Type /stop_drawing to stop drawing", msg.chatID);
    return;
  }

  if (msg.text == "/stop_drawing")
  {
    f = 0;
    change_mode(2, 0);
    bot.sendMessage("Successfully✅", msg.chatID);
    return;
  }

  if (words[0] == "/pxl") {
    if (!f) {
          f = 1;
          change_mode(1000, 0); cone_color_all(0, 0, 0); LEDS.show(); 
          bot.sendMessage("🖌Drawing mode is enable", msg.chatID);
    }

    if(words.size() != 3 and words.size() != 5) {bot.sendMessage("❗Send me color and position which u would like to set\nFormat: '/pxl #4a7044 pos' or '/pxl 74 112 68 pos'", msg.chatID);return;}
    
    if(words[1][0] == '#')
    {
        int pos = words[2].toInt();
        if(pos < 0 or pos >= LED_COUNT) 
        {
          bot.sendMessage("❗Pls enter all INTEGERS in the range [0; "+ String(LED_COUNT - 1) +"]", msg.chatID);       
          return;  
        }

        String hexColor = words[1]; 
        hexColor.replace("#", "");
        
        String redHex = hexColor.substring(0, 2);
        String greenHex = hexColor.substring(2, 4);
        String blueHex = hexColor.substring(4, 6);

        CurCol[pos].r = strtol(redHex.c_str(), NULL, 16);
        CurCol[pos].g = strtol(greenHex.c_str(), NULL, 16);
        CurCol[pos].b = strtol(blueHex.c_str(), NULL, 16);
    }
    else 
    {
      int pos = words[4].toInt();
      if(pos < 0 or pos >= LED_COUNT) 
      {
        bot.sendMessage("❗Pls enter all INTEGERS in the range [0; "+ String(LED_COUNT - 1) +"]", msg.chatID);       
        return;  
      }
      
      for(int i = 1; i < 4; i++){
        int val = words[i].toInt();

        if(val < 0 or val > 255) 
        {
          bot.sendMessage("❗Pls enter all INTEGERS in the range [0; 255]", msg.chatID);       
          return;  
        }
        
        CurCol[pos].r = words[1].toInt();
        CurCol[pos].g = words[2].toInt();
        CurCol[pos].b = words[3].toInt();
      }
    } 
    
    LEDS.show();
    bot.sendMessage("Successfully✅", msg.chatID);

    return;
  }
  
  if(f) {bot.sendMessage("You are currently drawing\n❗Send /stop_drawing to stop drawing", msg.chatID); return; }

  int val = ledMode;  

  digitalWrite(LED_BUILTIN, LOW);
  change_mode(1, 0);

  for(int i = 0; i <= 255; i+=5) {one_color_all(i, 0, 0); LEDS.show();delay(5);}
  for(int i = 255; i >= 0; i-=5) {one_color_all(i, 0, 0); LEDS.show();delay(5);}

  change_mode(val, 0);
  digitalWrite(LED_BUILTIN, HIGH);

  if (words[0] == "/all") {
    if(words.size() != 2 and words.size() != 4) bot.sendMessage("❗Send me color which u would like to set\nFormat: '/all #4a7044' or '/all 74 112 68'", msg.chatID);

    
    if(words[1][0] == '#')
    {
        String hexColor = words[1]; 
        hexColor.replace("#", "");
        
        String redHex = hexColor.substring(0, 2);
        String greenHex = hexColor.substring(2, 4);
        String blueHex = hexColor.substring(4, 6);

        int red = strtol(redHex.c_str(), NULL, 16);
        int green = strtol(greenHex.c_str(), NULL, 16);
        int blue = strtol(blueHex.c_str(), NULL, 16);

        cone_color_all(red, green, blue);
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
        cone_color_all(words[1].toInt(), words[2].toInt(), words[3].toInt());
      }
    } 
    change_mode(1000, 1);
    bot.sendMessage("Successfully✅", msg.chatID);

    return;
  }

  if (words[0] == "/mode" or words[0] == "/bright") {
    int secondWord = words[1].toInt();

    if (words[0] == "/mode")
    {
      if(words.size() != 2) bot.sendMessage(Commands, msg.chatID);
      else{
        change_mode(secondWord, 1);
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
  
  if(words[0] == "/send")
  {
    String s = "";
    for(int i = 2; i < words.size(); i++) s = s + words[i] + " ";
    bot.sendMessage(s, words[1]);
    bot.sendMessage("Successfully✅", msg.chatID);
    return;
  }

  if (msg.text == "/get"){bot.sendMessage(String(EEPROM.read(0)), msg.chatID);return;}
  
  if (msg.text == "/start" or msg.text == "/help") bot.sendMessage(help, msg.chatID);
  else if(msg.text == "/get_mode") {
    String ans = "The mode is " + String(val) + "\n";
    ans += "The number of leds: " + String(LED_COUNT) + "\n\n";
    ans += "Value of each pixel:\n{0; " + String(CurCol[0].r) + "; " + String(CurCol[0].g) + "; " + String(CurCol[0].b) + "}";
    for (int i = 1; i < CurCol.size(); i++) ans += ",\n{" + String(i) + "; " + String(CurCol[i].r) + "; " + String(CurCol[i].g) + "; " + String(CurCol[i].b) + "}";
  
    bot.sendMessage( ans , msg.chatID);
    
  }
  else if(msg.text == "/black") {change_mode(1000, 1); cone_color_all(0, 0, 0); LEDS.show(); bot.sendMessage("⚫Successfully✅", msg.chatID);}
  else if(msg.text == "/off") {change_mode(1000, 0); cone_color_all(0, 0, 0); LEDS.show(); bot.sendMessage("📴Successfully✅", msg.chatID);}
  else if(msg.text == "/white") { cone_color_all(255, 255, 255); change_mode(1000, 1);LEDS.show(); bot.sendMessage("⚪️Successfully✅", msg.chatID);}
  else if(msg.text == "/green") { cone_color_all(0, 255, 0); change_mode(1000, 1);LEDS.show(); bot.sendMessage("🟢Successfully✅", msg.chatID);}
  else if(msg.text == "/red") { cone_color_all(255, 0, 0); change_mode(1000, 1);LEDS.show(); bot.sendMessage("🔴Successfully✅", msg.chatID);}
  else if(msg.text == "/blue") { cone_color_all(0, 0, 255); change_mode(1000, 1);LEDS.show(); bot.sendMessage("🔵Successfully✅", msg.chatID);}
  else if(msg.text == "/lavender") { cone_color_all(197, 0, 255); change_mode(1000, 1);LEDS.show(); bot.sendMessage("🔵Successfully✅", msg.chatID);}
  else if(msg.text == "/orange") { cone_color_all(255, 70, 0); change_mode(1000, 1);LEDS.show(); bot.sendMessage("🔵Successfully✅", msg.chatID);}
  else if(msg.text == "/on") { FirstLaunch(); bot.sendMessage("🔛Successfully✅", msg.chatID);}
  
  else bot.sendMessage("Invaid command❌\n Use /help to list available commands", msg.chatID);
}
