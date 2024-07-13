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
  int l = 500;
  int s = 150;
  int sl = 1000;
  hip.write(90); // The resting position of the hip servo is 90, 180 is perpendicularly up and 0 is perpendicularly down.
  upjoin.write(0);
  lowjoin.write(0);
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
      hip.write(100); // 90+10 i.e. 10 degree to side
      delay(sl);
      lowjoin.write(25);
      delay(sl);
      upjoin.write(45);
      delay(sl);
      lowjoin.write(5);
      delay(sl+l);
      lowjoin.write(25);
      delay(sl);
      upjoin.write(5);
      delay(sl);
      hip.write(90);
      

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
  
  while(currentState == RUNNING)
    {
      delay(l);
      hip.write(100);
      delay(sl);
      lowjoin.write(25);
      delay(s);
      upjoin.write(45);
      delay(s);
      lowjoin.write(5);
      delay(l);
      lowjoin.write(25);
      delay(s);
      upjoin.write(5);
      delay(s);
      hip.write(90);
      

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
