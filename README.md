# LEDeffects

<p align="center">
  <br>
  <img src="https://github.com/astrosander/LEDeffects/assets/69795340/20d35a60-9542-402f-8e23-9ebb58d57504" width="120"/><br><br>
 <b>Smart home lighting controlled remotely through Telegram</b> <img src="https://github.com/astrosander/LEDeffects/assets/69795340/13af2347-97b6-4198-a371-e7f411cfe91f" height="18"/><br><br>
</p>
<p>
  This repository comprises a collection of effects designed for an addressable LED strip based on ESP8266, with remote control capabilities through a Telegram bot. The following sections will outline the instructions for managing the LED strip and the steps to establish its connection for operation.
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
  '\mode 2' smooth change of colours for the entire ribbon 🌈
  '\mode 3' a spinning rainbow 🌪️🌈
  '\mode 4' random colour change 🎲🎨
  '\mode 5' running LED 🏃‍♂️💡
  '\mode 6' a running train of LEDs 🚂💡
  '\mode 7' red and blue rotating 🔴🔵🔄
  '\mode 8' rotating half red and half blue 🔴🔵🔄
  '\mode 9' random strobe light ⚡🎲
  '\mode 10' single colour pulsation 💥🎨
  '\mode 11' colour changing pulsation 💥🌈
  '\mode 12' smooth vertical brightness change (for ring) 🔆🔼🔽
  '\mode 13' red LED madness 🔴💡💥
  '\mode 14' random colour madness 🎨💥
  '\mode 15' white blue red running in a circle 🏃‍♂️🔵⚪🔴🔄
  '\mode 16' radiation icon pulsating ☢️💥
  '\mode 17' red LED running in a circle 🏃‍♂🔴🔄
  '\mode 18' white and blue gradient ⚪🔵🌈
  '\mode 19' same thing's going on ⏭️🔄
  '\mode 20' red flashes going down 🔴⬇️💥
  '\mode 21' crescent moon 🌙
  '\mode 22' flame effect 🔥🔥🔥
  '\mode 23' rainbow in the vertical plane 🌈🔼🔽
  '\mode 24' Pac-Man 🎮😄
  '\mode 25' random flash madness 💥💥💥
  '\mode 26' police flasher 🚨🔵🔴
  '\mode 27' RGB propeller 🔄🔴🟢🔵
  '\mode 28' random red flashes in the vertical plane. 💥🎲
  '\mode 29' greens running around randomly 🟢🏃‍♂️🔄
  '\mode 30' greens running around randomly 🟢🏃‍♂️🔄
  '\mode 31' something's broken 🔧
  '\mode 32' something's broken 🔧
  '\mode 33' smooth colour fills 🎨🔆
  '\mode 34' running LEDs 🏃‍♂️💡
  '\mode 35' line lights 🚦
  '\mode 36' running circle sectors 🔴🟢🔵🔄
  '\mode 37' very smooth rotating rainbows 🌈🔄
  '\mode 38' random multi-coloured lights 🎨🎲
  '\mode 39' running lights 🏃‍♂️💡
  '\mode 40' random flashes of white 💥⚪
  '\mode 41' random flashes of white on a white background 💥⚪🔳
  '\mode 42' running every 3 times 🏃‍♂️🔄⏰
  '\mode 43' running every 3 rainbows 🏃‍♂️🔄🌈⏰
  '\mode 44' strobe lights ⚡💡💥
  '\mode 45' bouncing balls 🏀
  '\mode 46' colored bouncing balls 🎨🏀⬆️
  '\mode 888' long demo 🎉🎮
  '\mode 889' short demo 🎉🎮
  '\mode 999' pause ⏸️
  
  🔸List of colors:
  ⚫️'/black'
  ⚪️'/white'
  🔴'/red'
  🟢'/green'
  🔵'/blue'
  🟠'/orange'
  🟣'/lavender'
  🖌️'/pxl #0000ff 25' - drawing pixel-to-pixel(25 pixel has a #0000ff colour)
  🎨'/all #0000ff' - to set the same color(all pixels have a #0000ff colour)
  
  🔸Settings:
  '/help' - to get commands
  '/mode' - to set specific mode(e.g. "/mode 3")
  '/restart' - to restart ESP
  '/bright 255' - to set brightness(all pixels have a 255 brightness)
  '/get_mode' - to get current mode
  
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
