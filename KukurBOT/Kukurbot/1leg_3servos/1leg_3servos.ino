#include<Servo.h>
Servo hip;
Servo upjoin;
Servo lowjoin;
enum State 
{
  STOPPED, STARTED, WALKING, TROTING, DANCING, GALLOPING, RUNNING 
};
State currentState = STOPPED;
void setup() 
{
  // put your setup code here, to run once:
  Serial.begin(9600);
  hip.attach(3);
  upjoin.attach(6);
  lowjoin.attach(9);
  Serial.print("Type 'start' to move the servo, walk, run, gallop, dance, trot and 'stop' to stop it.\n");
  
}

void loop() {
  // put ur main code here, to run repeatedly:
  int l = 500; //long duration
  int s = 150; //short duration
  int sl = 1000; // super long duration
  // initial positions
  int k = 30; // knee
  int uj = 90; // upper join
  int h = 90; // hip
  hip.write(h); // The resting position of the hip servo is 90, 180 is perpendicularly up and 0 is perpendicularly down.
  upjoin.write(uj);
  lowjoin.write(k);
  if(Serial.available()>0)
  {
    String command = Serial.readStringUntil('\n');
    if(command.equals("start"))
    {
    currentState = STARTED;
    Serial.print("Starting the servos...\n");
    }
  
    else if(command.equals("walk"))
    {
      currentState = WALKING;
      Serial.print("Command: Walk, Activated!\n");
    
    }

    else if(command.equals("run"))
    {
      currentState = RUNNING;
      Serial.print("Command:Run , Activated!\n");
    
    }

    else if(command.equals("trot"))
    {
      currentState = TROTING;
      Serial.print("Command: Trot, Activated!\n");
    
    }

    else if(command.equals("gallop"))
    {
      currentState = GALLOPING;
      Serial.print("Command: Gallop, Activated!\n");
    }

    else if(command.equals("dance"))
    {
      currentState = DANCING;
      Serial.print("Command: Dancing, Activated!\n");
    
    }

  while(currentState == STARTED )
    {
      for(int p1 = 0; p1<=180; p1 = p1 + 20)
      {
        hip.write(p1);
        Serial.print("The angle of hip motor is: ");
        Serial.println(p1);
        delay(s);
        upjoin.write(p1);
        Serial.print("The angle of up motor is: ");
        Serial.println(p1);
        delay(s);
        lowjoin.write(p1);
        Serial.print("The angle of low motor is: ");
        Serial.println(p1);
        delay(s);

      }
      delay(l);
      for(int p1 = 180; p1>=0; p1 = p1 - 20)
        {
        hip.write(p1);
          Serial.print("The angle of hip motor is: ");
          Serial.println(p1);
          delay(s);
          upjoin.write(p1);
          Serial.print("The angle of up motor is: ");
          Serial.println(p1);
          delay(s);
          lowjoin.write(p1);
          Serial.print("The angle of low motor is: ");
          Serial.println(p1);
          delay(s);


        }
        if (Serial.available()>0)
        {
          String command = Serial.readStringUntil('\n');
        
          if(command.equals("stop"))
            {
              currentState = STOPPED;
              hip.write(0);
              upjoin.write(0);
              lowjoin.write(0);
              Serial.print("\nThe servos are stopped to zero\n");
              delay(s);
            
            }
          else 
          {
            currentState = STOPPED;
            Serial.println("\nUnknown command. Type 'start' or 'stop'.\n");
          }

        }
    }

  while(currentState == WALKING)
    {
      delay(l);
      hip.write(h+15); // hip in walking position
      delay(sl);

      //lowjoin.write(k);
      //delay(sl);
      upjoin.write(uj+20); // leg moving forward
      delay(sl);
      lowjoin.write(k-15); // knee touchihg ground
      delay(sl+l);
      upjoin.write(uj-20); // leg pushing back
      delay(sl);
      lowjoin.write(k+15); // knee lifting from ground
      delay(sl);
      //upjoin.write(uj);
      //delay(sl);
      hip.write(h); // hip to resting position
      //Repeat the process
      //to stop the walking
      if (Serial.available()>0)
          {
            String command = Serial.readStringUntil('\n');
          
            if(command.equals("stop"))
              {
                currentState = STOPPED;
                hip.write(0);
                upjoin.write(0);
                lowjoin.write(0);
                Serial.print("\nThe servos are stopped to zero\n");
                delay(s);
              
              }
            else 
            {
              currentState = STOPPED;
              Serial.println("\nUnknown command. Type 'start' or 'stop'.\n");
            }
          }
    }
  //Next is to code reverse walking, side walking and reverse side walking after making the forward walking stable
  //No work shall be done below this code until the walking is completely coded.
  while(currentState == RUNNING)
    {
      delay(l);
      hip.write(h+15); // 90+15 i.e. 15 degree to side
      delay(s);
      lowjoin.write(k+35);
      delay(s);
      upjoin.write(uj+30);
      delay(s);
      lowjoin.write(k+5);
      delay(l);
      lowjoin.write(k);
      delay(s);
      upjoin.write(uj);
      delay(s);
      hip.write(h);

      if (Serial.available()>0)
          {
            String command = Serial.readStringUntil('\n');
          
            if(command.equals("stop"))
              {
                currentState = STOPPED;
                hip.write(0);
                upjoin.write(0);
                lowjoin.write(0);
                Serial.print("\nThe servos are stopped to zero\n");
                delay(s);
              
              }
            else 
            {
              currentState = STOPPED;
              Serial.println("\nUnknown command. Type 'start' or 'stop'.\n");
            }
          }
    }

  


  }

}
