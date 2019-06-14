void firecheck(int *buzzer, int *fbtstart, int *fbtend, int *fire, int *fire_alarm, int *logic_fire){
   Serial.println(*fire);
   if(*fire <400){
    *buzzer = 1;
    *fire_alarm = 1;
    
    }
    else{
       *buzzer = 0;
       *fire_alarm = 0;
      }
  }



void intrusioncheck(int *intrusion_set, int *intrusion_alarm, int *intrstart, int *intrend, int *intrusion_buzzer, int *alarm_logic, int pir){
  if(*intrusion_set==1){
    if(pir == 1){
      *intrusion_buzzer = 1;
      *intrusion_alarm = 1;
      
      }
      else{
        *intrusion_buzzer = 0;
        *intrusion_alarm=0;
        }
    }
    else{
      *intrusion_buzzer = 0;
      *intrusion_alarm = 0;
      }
  
  
  
  }


void alarmON(int *alarm, int *tstart, int *tend, int *tbuzzer, int *logic){
  *tend = millis();
if(*tend-*tstart < 1500&& *logic==1){
      *tbuzzer = 1;
      
      }
      if(*tend-*tstart > 1500&& *logic==1){
        *tstart =  millis();
        *tend = millis();
        *logic = 0;
        
        }
        
      if(*tend-*tstart < 1500&& *logic==0){
      *tbuzzer = 0;
      
      }
      if(*tend-*tstart > 1500&& *logic==0){
        *tstart =  millis();
        *tend = millis();
        *logic = 1;
        
        }
      *alarm = 1;
  }

void alarmOFF(int *alarm, int *tstart, int *tend, int *tbuzzer, int *logic){
      *tstart = millis();
      *tend = millis();
      *tbuzzer = 0;
      *logic = 1;
      *alarm = 0;
  }
