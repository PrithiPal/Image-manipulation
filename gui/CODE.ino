//Servos pins//
int ser1p = 2;
int ser2p = 3;
int ser3p = 15;
int ser4p = 14;
int ser5p = 19;
int ser6p = 18;
Servo ser1, ser2, ser3, ser4, ser5, ser6; //Servos//

//Stepper one//
#define X_STE 54
#define X_DIR 55
#define X_ENA 38

//Stepper two//
#define Y_STE 60
#define Y_DIR 61
#define Y_ENA 56

//Switches//
int X_end_switch = 37;
int Y_end_switch = 17;
int Start_switch = 23;
int on_led = 11;
int reset_led = 12; 

void setup()
{
  Serial.begin(9600);//BTU

  ser1.attach(ser1p);
  ser1.write(140);
  ser2.attach(ser2p);
  ser2.write(140);
  ser3.attach(ser3p);
  ser3.write(140);
  ser4.attach(ser4p);
  ser4.write(140);
  ser5.attach(ser5p);
  ser5.write(140);
  ser6.attach(ser6p);
  ser6.write(140);

  pinMode(X_STE, OUTPUT);
  pinMode(X_DIR, OUTPUT);
  pinMode(X_ENA, OUTPUT);
  digitalWrite(X_ENA, LOW);
  pinMode(Y_STE, OUTPUT);
  pinMode(Y_DIR, OUTPUT);
  pinMode(Y_ENA, OUTPUT);
  digitalWrite(Y_ENA, LOW);

  pinMode(X_end_switch, INPUT);
  pinMode(Y_end_switch, INPUT_PULLUP); //USING PULLUP INTERNAL RESISTOR
  pinMode(Start_switch, INPUT_PULLUP); //USING PULLUP INTERNLA RESISTOR
  pinMode(on_led, OUTPUT);
  pinMode(reset_led, OUTPUT);
}


//==========================================================================//
int switchs (int number)
{
  int return_hl;
  if (number == 1)
  {
    return_hl = digitalRead(X_end_switch);
  }
  if (number == 2)
  {
    return_hl = digitalRead(Y_end_switch);
  }
  if (number == 3)
  {
    digitalWrite(on_led,HIGH);
    return_hl = digitalRead(Start_switch);
    delay(10);
    digitalWrite(on_led,LOW);
  }
  return return_hl;
}

//==========================================================================//
void stepper_move_x(int delay_time, int position_mm, int movement, int rotation)
{
  int mm = 400;
  int steppes = 400 * position_mm;
  int count;
  int count1;
  if (movement == 1)
  {
    digitalWrite(X_DIR, HIGH); //positive
  }
  if (movement == 0)
  {
    digitalWrite(X_DIR, LOW); //negative
  }
  for (count1 = 0; count1 < rotation; count1++)
  {
    for (count = 0; count < steppes; count++)
    {
      digitalWrite(X_STE, HIGH);
      delayMicroseconds(200);
      digitalWrite(X_STE, LOW);
    }
    delay(delay_time);
  }
}

//==========================================================================//
void stepper_move_y(int delay_time, int position_mm, int movement, int rotation)
{
  int mm = 400;
  int steppes = 400 * position_mm;
  int count;
  int count1;
  if (movement == 1)
  {
    digitalWrite(Y_DIR, HIGH); //positive
  }
  if (movement == 0)
  {
    digitalWrite(Y_DIR, LOW); //negative
  }
  for (count1 = 0; count1 < rotation; count1++)
  {
    for (count = 0; count < steppes; count++)
    {
      digitalWrite(Y_STE, HIGH);
      delayMicroseconds(200);
      digitalWrite(Y_STE, LOW);
    }
    delay(delay_time);
  }
}

//==========================================================================//
void sd_servo (long point1, int point2, int servo_cont, int file)
{
  int y_coor;
  int x_coor = point2;
  int color;
  
  int d_time = 100;
  int angle_max = 220;
  int angle_min = 140;
  
  if (file == 1){
    Serial.println("File 1 is read");
    if (servo_cont == 1)
    {
      Serial.println("Pen one is functioning");
      y_coor = (y_max - 125 - 30 - 30)-point1;
      color = arr1[y_coor][x_coor];
      Serial.println(color);
      if (color == 1){
        ser1.write(angle_max);
        delay(d_time);
        ser1.write(angle_min);
        delay(d_time);
      }
     }
     if (servo_cont == 2)
     {
       y_coor = (y_max - 125 - 30)-point1;
       Serial.println("Pen two is functioning");
       color = arr1[y_coor][x_coor];
       Serial.println(color);
       if (color == 1){
         ser2.write(angle_max);
         delay(d_time);
         ser2.write(angle_min);
         delay(d_time);
       }
     }
     if (servo_cont == 3)
     {
        y_coor = (y_max-125)-point1;
        Serial.println("Pen three is functioning");
        color = arr1[y_coor][x_coor];
        Serial.println(color);
        if (color == 1){
        ser3.write(angle_max);
        delay(d_time);
        ser3.write(angle_min);
        delay(d_time);
       }
     }
    }
    if (file == 2){
      if (servo_cont == 6)
      {
        y_coor = 125-point1;
        Serial.println("Pen six is functioning");
        color = arr2[y_coor][x_coor];
        Serial.println(color);
        if (color == 1){
          ser6.write(angle_max);
          delay(d_time);
          ser6.write(angle_min);
          delay(d_time);
        }
      }
      if (servo_cont == 5)
      {
        y_coor = 95-point1;
        Serial.println("Pen five is functioning");
        color = arr2[y_coor][x_coor];
        Serial.println(color);
        if (color == 1){
          ser5.write(angle_max);
          delay(d_time);
          ser5.write(angle_min);
          delay(d_time);
        }
      }
      if (servo_cont == 4)
      {
        y_coor = 65-point1;
        Serial.println("Pen four is functioning");
        color = arr2[y_coor][x_coor];
        Serial.println(color);
        if (color == 1){
          ser4.write(angle_max);
          delay(d_time);
          ser4.write(angle_min);
          delay(d_time);
        }
      }
    }
}

//==========================================================================//
void move_pos_back (int pointy)
{
  int n = x_max-1;
  int j = pointy;
  int file;
  
  while (n >= 0) //n starts from x_max
  {
    int x = 1;
    while (x < 7)
    {
      if ((x>0) && (x<=3))
      {
        file = 1;
      }
      else if ((x>3) && (x<=6))
      {
        file = 2;
      }
      sd_servo(j,n,x,file);
      x++;
    }
    stepper_move_x(0, 1, 0, 1);
    n--;
  }
}

//==========================================================================//
void move_pos_for(int pointy)
{
  int n = 0;
  int j = pointy;
  int file;
  
  while (n < x_max) //n starts from 1
  {
    int x = 1;
    while (x < 7)
    {
      if ((x>0) && (x<=3))
      {
        file = 1;
      }
      else if ((x>3) && (x<=6))
      {
        file = 2;
      }
      sd_servo(j,n,x,file);
      x++;
     }
    stepper_move_x(0, 1, 1, 1);
    n++;  
   }
    
}

//==========================================================================//
void move_pos_for_pen14(int pointy)
{
  int n = 0;
  int j = pointy;
  int file;
  int x;
  while (n < x_max)
  {
    x = 1;
    file = 1;
    sd_servo(j,n,x,file);

    x = 4;
    file = 2;
    sd_servo(j,n,x,file);
    stepper_move_x(0, 1, 1, 1);
    n++;  
  }
}

//==========================================================================//
void move_pos_back_pen14 (int pointy)
{
  int n = x_max-1;
  int j = pointy;
  int file;
  int x;
  while(n>=0)
  {
    x = 1;
    file = 1;
    sd_servo(j,n,x,file);
    x = 4;
    file = 4;
    sd_servo(j,n,x,file);
    stepper_move_x(0, 1, 0, 1);
    n--;
  }
}

//==========================================================================//
void move_pos_for_pen4only(int pointy)
{
  int n = 0;
  int j = pointy;
  int file;
  int x;
  while (n < x_max)
  {
    x = 4;
    file = 2;
    sd_servo(j,n,x,file);
    stepper_move_x(0, 1, 1, 1);
    n++;  
  }
}

//==========================================================================//
void move_pos_back_pen4only (int pointy)
{
  int n = x_max-1;
  int j = pointy;
  int file;
  int x;
  while(n>=0)
  {
    x = 4;
    file = 4;
    sd_servo(j,n,x,file);
    stepper_move_x(0, 1, 0, 1);
    n--;
  }
}

//==========================================================================//
void stepper_move_x_stop(int delay_time, int position_mm, int movement, int rotation)
{
  int mm = 400;
  int steppes = 400 * position_mm;
  int count;
  int count1;
  if (movement == 1)
  {
    digitalWrite(X_DIR, HIGH); //positive
  }
  if (movement == 0)
  {
    digitalWrite(X_DIR, LOW); //negative
  }
  for (count1 = 0; count1 < rotation; count1++)
  {
    if (switchs(1) == 1)
    {
      break;
    }
    if (switchs(1) == 0)
    {
      for (count = 0; count < steppes; count++)
      {
        if (switchs(1) == 1)
        {
          break;
        }
        if (switchs(1) == 0)
        {
          digitalWrite(X_STE, HIGH);
          delayMicroseconds(100);
          digitalWrite(X_STE, LOW);
        }
      }
      delay(delay_time);
    }
  }
}

//==========================================================================//
void stepper_move_y_stop(int delay_time, int position_mm, int movement, int rotation)
{
  int mm = 400;
  int steppes = 400 * position_mm;
  int count;
  int count1;
  if (movement == 1)
  {
    digitalWrite(Y_DIR, HIGH); //positive
  }
  if (movement == 0)
  {
    digitalWrite(Y_DIR, LOW); //negative
  }
  for (count1 = 0; count1 < rotation; count1++)
  {
    if (switchs(2) == 0)
    {
      break;
    }
    if (switchs(2) == 1)
    {
      for (count = 0; count < steppes; count++)
      {
        if (switchs(2) == 0)
        {
          break;
        }
        if (switchs(2) == 1)
        {
          digitalWrite(Y_STE, HIGH);
          delayMicroseconds(100);
          digitalWrite(Y_STE, LOW);
        }
      }
      delay(delay_time);
    }
  }
}

//==========================================================================//



void start ()
{
  stepper_move_x_stop(0, 8, 0, 264);
  stepper_move_y_stop(0, 8, 0, 264);
  stepper_move_x(0, 30, 1, 1); // 10 is ok ok////////////////////////////
  stepper_move_y(0, 50, 1, 1); //80 is perfect
}
//==========================================================================//
void loop()
{
  int row = 0;
  int p;
  if (switchs(3) == 0)
  {
    start();
    while ( row < 30)
    {
      p = row + 1;
      if ( (p % 2) == 0)
      {
        move_pos_back(row);
      }
      else if ((p % 2) == 1)
      {
        move_pos_for(row);
      }
      stepper_move_y(0, 1, 1, 1);
      row++;
    }
    while (row < (y_max-65-30-30-30-30))
    {
      p = row + 1;
      if ( (p % 2) == 0)
      {
        move_pos_back_pen14(row);
      }
      else if ((p % 2) == 1)
      {
        move_pos_for_pen14(row);
      }
      stepper_move_y(0, 1, 1, 1);
      row++;
    }
    while (row < 65)
    {
      p = row + 1;
      if ( (p % 2) == 0)
      {
        move_pos_back_pen4only(row);
      }
      else if ((p % 2) == 1)
      {
        move_pos_for_pen4only(row);
      }
      stepper_move_y(0, 1, 1, 1);
      row++;
    }
    exit(0);
  }
}