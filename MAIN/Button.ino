void ButtonTick(){
  enc.tick();

  if(enc.held()){
    blink(100);
    IsOff = !IsOff;

    if(IsOff){StartOff = 0;change_mode(1000, 0); cone_color_all(0, 0, 0); LEDS.show();}
    else FirstLaunch();
  }
  
  if(!enc.hasClicks()) return;
  
  if(enc.clicks == 1){
    byte newMode = (ledMode < 256) ? (ledMode + 1) % Num_Modes : 1;
    change_mode(newMode, 1);
  }
  
  if(enc.clicks == 2){
    byte newMode = (ledMode < 256) ? (ledMode - 1 + Num_Modes) % Num_Modes : 1;
    change_mode(newMode, 1);
  }
}
/**ToDo:
 * Add changing of the brightness
 */
