# LEDeffects

<p align="center">
  <br>
  <img src="https://github.com/astrosander/LEDeffects/assets/69795340/20d35a60-9542-402f-8e23-9ebb58d57504" width="120"/><br><br>
 <b>Smart home lighting controlled remotely through Telegram</b> <img src="https://github.com/astrosander/LEDeffects/assets/69795340/13af2347-97b6-4198-a371-e7f411cfe91f" height="24"/><br><br><br>
</p>


## Demonstration
<p align="center">
  <img src="Design/Presentation.gif" height="300"/>
  <img src="https://github.com/astrosander/LEDeffects/assets/69795340/8e36ef5e-a446-415b-aa30-75997cec3612" height="300"/><br>
  Example of work on a ceiling-mounted led strip
</p>

<details>
  <summary><h1>📜Wiki</h1></summary>
  
  ### 
  <pre>
  🔸List of modes from /mode:
  2 smooth change of colours for the entire ribbon 🌈
  3 a spinning rainbow 🌪️🌈
  4 random colour change 🎲🎨
  5 running LED 🏃‍♂️💡
  6 a running train of LEDs 🚂💡
  7 red and blue rotating 🔴🔵🔄
  8 rotating half red and half blue 🔴🔵🔄
  9 random strobe light ⚡🎲
  10 single colour pulsation 💥🎨
  11 colour changing pulsation 💥🌈
  12 smooth vertical brightness change (for ring) 🔆🔼🔽
  13 red LED madness 🔴💡💥
  14 random colour madness 🎨💥
  15 white blue red running in a circle 🏃‍♂️🔵⚪🔴🔄
  16 radiation icon pulsating ☢️💥
  17 red LED running in a circle 🏃‍♂🔴🔄
  18 white and blue gradient ⚪🔵🌈
  19 same thing's going on ⏭️🔄
  20 red flashes going down 🔴⬇️💥
  21 crescent moon 🌙
  22 flame effect 🔥🔥🔥
  23 rainbow in the vertical plane 🌈🔼🔽
  24 Pac-Man 🎮😄
  25 random flash madness 💥💥💥
  26 police flasher 🚨🔵🔴
  27 RGB propeller 🔄🔴🟢🔵
  28 random red flashes in the vertical plane. 💥🎲
  29 greens running around randomly 🟢🏃‍♂️🔄
  30 greens running around randomly 🟢🏃‍♂️🔄
  31 something's broken 🔧
  32 something's broken 🔧
  33 smooth colour fills 🎨🔆
  34 running LEDs 🏃‍♂️💡
  35 line lights 🚦
  36 running circle sectors 🔴🟢🔵🔄
  37 very smooth rotating rainbows 🌈🔄
  38 random multi-coloured lights 🎨🎲
  39 running lights 🏃‍♂️💡
  40 random flashes of white 💥⚪
  41 random flashes of white on a white background 💥⚪🔳
  42 running every 3 times 🏃‍♂️🔄⏰
  43 running every 3 rainbows 🏃‍♂️🔄🌈⏰
  44 strobe lights ⚡💡💥
  45 bouncing balls 🏀
  46 colored bouncing balls 🎨🏀⬆️
  888 long demo 🎉🎮
  889 short demo 🎉🎮
  999 pause ⏸️
  
  🔸List of colors:
  ⚫️/black
  ⚪️/white
  🔴/red
  🟢/green
  🔵/blue
  🟠/orange
  🟣/lavender
  🖌️/pxl - drawing pixel-to-pixel(e.g. "/pxl #0000ff 25")
  🎨/all - to set the same color(e.g. "/all #0000ff")
  
  🔸Settings:
  /help - to get commands
  /mode - to set specific mode(e.g. "/mode 3")
  /restart - to restart ESP
  /bright - to set brightness(e.g. "/bright 255")
  /get_mode - to get current mode
  
  </pre>

</details>


# First steps🐾
<img align="center"  width="500px" src="Design/sheme.png" />

🔸Assemble according to the above scheme

🔸<a href="https://github.com/astrosander/LEDeffects/archive/refs/heads/main.zip">Download</a> repository

🔸Unarchive

🔸Open <a href="https://github.com/astrosander/LEDeffects/blob/main/libraries">./libraries</a> and copy all ones to the ```%ArduinoFolder%/libraries```

🔸Open <a href="https://github.com/astrosander/LEDeffects/blob/main/MAIN/MAIN.ino">./MAIN/MAIN.ino</a> (`Arduino IDE 1.8.9` - recommended)

🔸Edit ```8-11``` lines:

  <pre>
  8 - Enter Your WiFi login
  
  9 - Enter Your WiFi password
  
  10 - Enter Bot's Token, which You got with <a href="https://github.com/astrosander/LEDeffects/edit/main/README.md#how-to-make-telegram-bot">@BotFather</a>
  
  11 - Enter Telegram ID, which You got with <a href="https://github.com/astrosander/LEDeffects/edit/main/README.md#how-to-get-my-id">@IDBot</a>
  </pre> 
  
🔸In boards manager select ESP8266 with `3.1.2` version

🔸Upload code to Your board

🔸Go to Your bot and send 
```/start```

🔸To turn on/off press and hold ```Flash button```

<details>
  <summary><h2>How to create a bot in Telegram <img align="center"  width="40px" src="Design/bot_father.png" /></h2> </summary>
  
  1. You must have telegram
  2. Go to <a href="https://t.me/BotFather">@BotFather</a>
  3. Send ```/newbot```
  4. Then, send name You woud like to choose(Ex.: ```AstroLamp```)
  5. Send send *username*(Ex.: ```astrolamp_bot```)
  6. All right, You just created Your own bot!
</details>
<details>
  <summary><h2>How to get my Telegram ID <img align="center"  width="35px" src="Design/myid.jpg" /> </h2> </summary>
  
  1. You must have telegram
  2. Go to <a href="https://t.me/myidbot">@IDBot</a>
  3. Send ```/getid```
  4. Copy Your id!
</details>

##  Plans for future📜

🔹Add more effects ➕

🔹Create video tutorial 📺

🔹Optimise programm ⌨
