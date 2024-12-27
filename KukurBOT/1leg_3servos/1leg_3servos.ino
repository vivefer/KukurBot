#include<Servo.h>
#include<math.h>
Servo hip;
Servo upjoin;
Servo lowjoin;
float L1 = 13.8;
float L2 = 17.9;
float theta1 = 90;
float theta2 = 25;
double xk = L1*cos(theta1);
double yk = L1*sin(theta1);
double xf = L2*cos(theta1 + theta2);
double yf = L2*sin(theta1 + theta2);
float increment1 = 0.1;
float increment2 = 0.1;
enum State 
{
  STOPPED, STARTED, WALKING, SWALKING, DANCING, RSWALKING, RWALKING 
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
  int k = 25; // knee
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

    else if(command.equals("rwalk"))
    {
      currentState = RWALKING;
      Serial.print("Command:Reverse walk , Activated!\n");
    
    }

    else if(command.equals("swalk"))
    {
      currentState = SWALKING;
      Serial.print("Command: Side Walk, Activated!\n");
    
    }

    else if(command.equals("rswalk"))
    {
      currentState = RSWALKING;
      Serial.print("Command: Reverse Side Walking, Activated!\n");
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
        upjoin.write();
    }
   /* {
      delay(sl);
    //  hip.write(h+5); // hip in walking position
      //delay(l);

      //lowjoin.write(k);
      //delay(sl);
      upjoin.write(uj+25); // leg moving forward
      delay(l);
      lowjoin.write(k-22); // knee touchihg ground
      delay(l);
      upjoin.write(uj-22);
      lowjoin.write(k-25); // leg pushing back
      delay(l);
      lowjoin.write(k+15); // knee lifting from ground
      delay(l);
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
    }*/
  //Next is to code reverse walking, side walking and reverse side walking after making the forward walking stable
  //No work shall be done below this code until the walking is completely coded.
  while(currentState == RWALKING)
    {
      delay(sl);
      hip.write(h+5); // hip in walking position
      delay(l);
      lowjoin.write(k+15); // knee lifting from ground
      delay(l);
      upjoin.write(uj-22); // leg pushing back
      delay(l);
      lowjoin.write(k-15); // knee touchihg ground
      delay(l);
      upjoin.write(uj+20); // leg moving forward
      delay(l);
      
      
      //upjoin.write(uj);
      delay(sl);
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

  


  }
while(currentState == SWALKING)
    {
      delay(sl);
      //hip.write(h-30);
      delay(l);
      lowjoin.write(k-15);
      delay(l);
      hip.write(h-25);
      delay(l);
      lowjoin.write(k+20);
      delay(sl);
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
//reverse side walking is not working yet!
while(currentState == RSWALKING)
    {
      delay(sl);
      //hip.write(h-30);
      delay(l);
      lowjoin.write(k+20);
      delay(l);
      hip.write(h-20);
      delay(l);
      lowjoin.write(k-15);
      
      
      delay(sl);
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

  


}


void UpdateTheta()
{
  theta1 += increment1;
  if (theta1 <= 0 && theta1 >= 360)
    increment1 = -increment1;
  
  theta2 += increment2;
  if (theta2 <=0 && theta2 >= 360)
    increment2 = -increment2;



}
