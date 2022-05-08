int pirCheck(int pir, long *timere, long *timers){
  
  
  if (pir == 1){
      *timers = millis();
      *timere = millis();
     
      return 1;
      
      
    }
    else{
      
      
      *timere = millis();
      Serial.println(*timere - *timers);
      
        if ((*timere - *timers)>10000){
          return 0;
          
      }
      return 1;
    }
  }



int ledCheck(int* led, int ledmode, int pirstatus, int ledcntrl){
  if(ledmode == 0){
    if(pirstatus == 1){
      *led=1;
      
        
                     
      }else{
        
        *led = 0;
        
          }
        }
    
   else{
    if(ledcntrl == 1){
      *led = 1;
      
      }
      else{
       *led = 0;
        }
    }
    
  }
