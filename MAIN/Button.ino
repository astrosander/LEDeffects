void ButtonTick(){
  enc.tick();

//  if (enc.held()) mode = 0;
    
  if(!enc.hasClicks()) return;
  
  if(enc.clicks == 1){
    blink(100);
    IsOff = !IsOff;

    if(IsOff){StartOff = 0;change_mode(1000, 0); cone_color_all(0, 0, 0); LEDS.show();}
    else FirstLaunch();
  }

//  
//  if(enc.clicks == 2){lcd.clear(); mode = (mode + NumMode - 1) % NumMode;} 
//  if(enc.clicks == 3) SpeedFormat = !SpeedFormat;
//  
//  if(enc.clicks == 4) MaxSpeed=0;
//  if(enc.clicks >= 10) {BackReset();resetFunc();}
}
//
// if (enc.press())
//  {
//    IsOff = !IsOff;
//
//    if(IsOff){StartOff = 0;change_mode(1000, 0); cone_color_all(0, 0, 0); LEDS.show();}
//    else FirstLaunch();
//  }
