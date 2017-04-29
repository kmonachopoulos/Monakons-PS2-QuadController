/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  University of Patras - Electronics and information processing Division of Electronics and Computers (Department of physics) 
  ------------------------------------------------------------------------------------------------------------------------------------------
*/
/*
  ------------------------------------------------------------------------------------------------------------------------------------------
  Project       : Monakons Quadcopter
  File          : PS2X_QuadCpterController.ino
  Description   : This code implements PS2 controller functionallity
  Author        : Monachopoulos Konstantinos
  ------------------------------------------------------------------------------------------------------------------------------------------

                LOOKING AT THE PLUG
           -------------------------------
 PS PIN  ->| o  o  o | o  o  o | o  o  o |
           \_____________________________/
    
PIN # USAGE
DATA
COMMAND
N/C (9 Volts unused)
GND
VCC
ATT
CLOCK
N/C
ACK
*/
/*
  --------------------------------------------------------------------------------------------------
  Includes
  --------------------------------------------------------------------------------------------------
*/

#include "PS2X_lib.h"  //for v1.6

/*
  --------------------------------------------------------------------------------------------------
  Assign Classes
  --------------------------------------------------------------------------------------------------
*/ 
PS2X ps2x; // create PS2 Controller Class

/*
  --------------------------------------------------------------------------------------------------
  Global Variables
  --------------------------------------------------------------------------------------------------
*/
int error = 0; 
byte type = 0;
byte vibrate[8] = {0};
int PsStatusFlag=0;
int SumOfVibration=0;
double kp=0;
/*
  --------------------------------------------------------------------------------------------------
  Main Code
  --------------------------------------------------------------------------------------------------
*/ 

void setup(){
  Serial.begin(9600);

  error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error

  if(ps2x.readType()==1 && error == 0){  
    
    /*If conroller type is PS2 controller && controller
    configured set PsStatusFlag = 1, the quadcopter get this value in initialization*/
    PsStatusFlag=1;
    Serial.println(PsStatusFlag);
  }  
}

void loop(){

  /*you should call this at least once a second*/

  if(PsStatusFlag == 1){                          // skip loop if Controller Status Flag=0
                                                  // DualShock Controller Configuration OK
    
      for(int i=0;i<8;i++){                       // This will vibrate the controller for any of the selected  buttons pressed 
      SumOfVibration+=vibrate[i];      
      if(SumOfVibration>255)
      SumOfVibration=255;
    }
    
    ps2x.read_gamepad(false, SumOfVibration);     // read controller and set large motor to spin at 'vibrate' speed
    SumOfVibration=0;                             // Re-initialize 
    
    if(ps2x.Button(PSB_PAD_UP)) {                 // will be TRUE as long as button is pressed      
      Serial.print("UP\n");
    }
    if(ps2x.Button(PSB_PAD_RIGHT)){
      Serial.print("RIGHT\n");
    }
    if(ps2x.Button(PSB_PAD_LEFT)){
      Serial.print("LEFT\n");
    }
    if(ps2x.Button(PSB_PAD_DOWN)){
      Serial.print("DOWN\n");
    }
    
    if(ps2x.Button(PSB_PINK)){                 // will be TRUE as long as button is pressed
      Serial.print("SQUARE\n"); 
    }             
      
    if(ps2x.Button(PSB_GREEN)){
      Serial.print("TRIANGLE\n"); 
    }   

    if(ps2x.Button(PSB_RED)){
      Serial.print("CIRCLE\n"); 
    }              

    if(ps2x.Button(PSB_BLUE)){
      Serial.print("X\n"); 
    } 

    if(ps2x.Button(PSB_L1))               
      Serial.print("L1\n"); 

    if(ps2x.Button(PSB_R1))               
      Serial.print("R1\n"); 

    if(ps2x.Button(PSB_L2))              
       Serial.print("L2\n");
        
    if(ps2x.Button(PSB_R2))
       Serial.print("R2\n");
       
    if (ps2x.NewButtonState())                  // will be TRUE if any button changes state (on to off, or off to on)          
    {
      
    if(ps2x.Button(PSB_L3))
      Serial.print("L3\n");
      
    if(ps2x.Button(PSB_R3))
      Serial.print("R3\n");

    if(ps2x.Button(PSB_START))                   
      Serial.print("START\n");
      
    if(ps2x.Button(PSB_SELECT))
      Serial.print("SELECT\n");         
    }  
  
    /*this will set the large motor vibrate speed based on 
    how hard you press the Quadcopter Movements..  */
    
    vibrate[0] = ps2x.Analog(PSAB_PAD_UP);
    vibrate[1] = ps2x.Analog(PSAB_PAD_RIGHT);
    vibrate[2] = ps2x.Analog(PSAB_PAD_LEFT);
    vibrate[3] = ps2x.Analog(PSAB_PAD_DOWN);   
    vibrate[4] = ps2x.Analog(PSAB_PINK);
    vibrate[5] = ps2x.Analog(PSAB_GREEN);   
    vibrate[6] = ps2x.Analog(PSAB_RED);   
    vibrate[7] = ps2x.Analog(PSAB_BLUE);

  }
  delay(50);
}



