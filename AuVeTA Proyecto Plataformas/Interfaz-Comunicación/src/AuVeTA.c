/**
 * @file AuVeTA.ino
 * @author Jorge Isaac Fallas Mejía B62562
 * @author Esteban Rodríguez Quintana B66076
 * @brief Archivo de código en arduino para el proyecto final de Programación Bajo Plataformas Abiertas.
 * @version 1.3
 * @date 2019-06-14
 */


/**********include de bibliotecas:************/
#include <Servo.h>          //Servo lib
#include <SoftwareSerial.h> //Bluetooh lib

/******************************************/

/********** Definición de variables: ************/
int RX_bluetooh = 0;
int TX_bluetooh = 1;
int servo_pin = 11;
int obstacle_pin = 8;
int track1_pin = 12;
int final_pin = 7;
int motorR_forward = 9;
int motorR_reverse = 5;
int motorL_forward = 10;
int motorL_reverse = 6;
int buzzer = 13;
int R = 2;
int G = 3;
int B = 4;
int servo_open = 125;  //revisar valores para los grados del servo
int servo_close = 10;  //revisar valores para los grados del servo
int adjustM_delay = 1; //valor cercano a cero
int stopD = 40;        //valor cercano 50
int reactionD = 15;    //entre 10 y 20
int motorPower = 254;

/*  Valores de PWM para variable motorPower:
     _______________________________
    |   Valor   |  Ciclo de trabajo |
    |===============================|
    |    0      |       0%          |
    |    63     |       25%         |
    |    127    |       50%         |
    |    190    |       75%         |
    |    255    |       100%        |
    |_______________________________|
*/

///////////////////////////////////////////////////////
bool obstacle_presence = digitalRead(obstacle_pin); //detección de objeto frontal             // detect = 0 //  no detect = 1  //
bool track1 = digitalRead(track1_pin);              //detección de pista                      // detect = 1 //  no detect = 0  //
bool final_sensor = digitalRead(final_pin);         //detección de objeto lateral             // detect = 0 //  no detect = 1  //


Servo myServo;
SoftwareSerial mySerial(RX_bluetooh, TX_bluetooh); // (RX,TX)

/******************************************/
/*************** SETUP: *******************/
/******************************************/
void setup()
{
  //Seteo para comunicación serial USB:
  Serial.begin(9600);

  ////Seteo para comunicación serial Bluetooth:
  mySerial.begin(115200);

  //Set for digital pins:
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(servo_pin, OUTPUT);
  pinMode(obstacle_pin, INPUT);
  pinMode(track1_pin, INPUT);
  pinMode(final_sensor, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(motorL_forward, OUTPUT);
  pinMode(motorL_reverse, OUTPUT);
  pinMode(motorR_forward, OUTPUT);
  pinMode(motorR_reverse, OUTPUT);

  //Seteo para servo
  myServo.attach(servo_pin);
  myServo.write(servo_close);
  delay(500);
  myServo.detach();
  
  //Seteo inicial de motores en cero
  digitalWrite(motorR_forward, 0);
  digitalWrite(motorL_forward, 0);
  digitalWrite(motorR_reverse, 0);
  digitalWrite(motorL_reverse, 0);
}

/******************************************/
/**************** LOOP: *******************/
/******************************************/
void loop()
{   
//luz roja en "Waiting Mode":
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  digitalWrite(B, LOW);
//Revisión de puerto serial disponible
  if (mySerial.available())
  {
//Lectura Serial para selección de modo: 3 -> "Trackig Mode" || 2 -> "Waiting Mode" || 3 -> "Control Mode"
    if (mySerial.read() == '3') //trackin mode
    { //Luz azul para "Tracking Mode":
      digitalWrite(R, LOW);
      digitalWrite(G, HIGH);
      digitalWrite(B, LOW);
      while (1) // "Tracking Mode" hasta cuando el puerto serial recibe un carácter '2' para luego ir a "Waiting Mode"
      {
        tracking_mode_func();
        if (mySerial.read() == '2') //Leer puerto serial para ir a "Waiting Mode"
        {
          break;
        };
      }
    }
    if (mySerial.read() == '1') //Control mode
    { 
      digitalWrite(R, LOW);
      digitalWrite(G, LOW);
      digitalWrite(B, HIGH);
      control_mode_func();    //"Control Mode" hasta cuando el puerto serial recibe un carácter '2' para luego ir a "Waiting Mode"
    }
  }
  else
  {
    while (mySerial.available() == false)
    {
      digitalWrite(R, HIGH);
      delay(100);
      digitalWrite(R, LOW);
      delay(100);
    };
  };

  no_move(); //detener movimiento cuando se esté en modo control y no se precionen teclas.
}

//****************FUNCTIONS: **********************

/**
 * @brief Esta función da movimiento de rueda izquierda y por tanto un giro hacia la derecha del vehículo para el modo de tracking.
 * @param int para potencia deseada en el motor.
 * @return no retorna valores, solo ejecuta acciones.
*/
void goR(int PW)
{
  while (track1 != 1)
  {
    track1 = digitalRead(track1_pin);
    analogWrite(motorR_forward, 0);
    analogWrite(motorL_forward, 0);
    analogWrite(motorR_reverse, 0);
    analogWrite(motorL_reverse, PW);
    delay(adjustM_delay);
    if (mySerial.read() == '2')
    {
      break;
    }
  };

  analogWrite(motorR_forward, 0);
  analogWrite(motorL_forward, 0);
  analogWrite(motorR_reverse, 0);
  analogWrite(motorL_reverse, 0);
  delay(stopD);
};


/**
 * @brief Esta función da movimiento de rueda derecha y por tanto un giro hacia la izquierda del vehículo para el modo de tracking.
 * @param int para potencia deseada en el motor.
 * @return no retorna valores, solo ejecuta acciones.
*/
void goL(int PW)
{
  while (track1 != 0)
  {
    track1 = digitalRead(track1_pin);
    analogWrite(motorR_forward, 0);
    analogWrite(motorL_forward, 0);
    analogWrite(motorR_reverse, PW);
    analogWrite(motorL_reverse, 0);
    delay(adjustM_delay);
    if (mySerial.read() == '2')
    {
      break;
    }
  };
  analogWrite(motorR_forward, 0);
  analogWrite(motorL_forward, 0);
  analogWrite(motorR_reverse, 0);
  analogWrite(motorL_reverse, 0);
  delay(stopD);
}

/**
 * @brief Esta función da movimiento de rueda izquierda y por tanto un giro hacia la derecha del vehículo para el modo de control.
 * @param no recibe parámetros
 * @return no retorna valores, solo ejecuta acciones.
*/
void goR_control()
{
  digitalWrite(motorL_reverse, motorPower);
  digitalWrite(motorL_forward, 0);
  digitalWrite(motorR_reverse, 0);
  digitalWrite(motorR_forward, 0);
  delay(reactionD);
};

/**
 * @brief Esta función da movimiento de rueda derecha y por tanto un giro hacia la izquierda del vehículo para el modo de control.
 * @param no recibe parámetros.
 * @return no retorna valores, solo ejecuta acciones.
*/
void goL_control()
{
  digitalWrite(motorL_reverse, 0);
  digitalWrite(motorL_forward, 0);
  digitalWrite(motorR_reverse, motorPower);
  digitalWrite(motorR_forward, 0);
  delay(reactionD);
};

/**
 * @brief Esta función da movimiento de ambas ruedas en dirección de avance del vehículo para el modo de control.
 * @param no recibe parámetros.
 * @return no retorna valores, solo ejecuta acciones.
*/
void forward_control()
{
  digitalWrite(motorL_reverse, 0);
  digitalWrite(motorL_forward, motorPower);
  digitalWrite(motorR_reverse, 0);
  digitalWrite(motorR_forward, motorPower);
  delay(reactionD);
};

/**
 * @brief Esta función da movimiento de ambas ruedas en dirección contraria al avance del vehículo para el modo de control.
 * @param no recibe parámetros.
 * @return no retorna valores, solo ejecuta acciones.
*/
void reverse_control()
{
  digitalWrite(motorL_reverse, motorPower);
  digitalWrite(motorL_forward, 0);
  digitalWrite(motorR_reverse, motorPower);
  digitalWrite(motorR_forward, 0);
  delay(reactionD);
};

/**
 * @brief Esta función apaga motores del vehículo para el modo de control.
 * @param no recibe parámetros.
 * @return no retorna valores, solo ejecuta acciones.
*/
void no_move()
{
  digitalWrite(motorL_reverse, 0);
  digitalWrite(motorL_forward, 0);
  digitalWrite(motorR_reverse, 0);
  digitalWrite(motorR_forward, 0);
};

/**
 * @brief Esta función determina si se detecta el final del recorrido gracias a la condición recibida de un sensor de tracking y otro de obstáculo.
 * @param Recibe el valor del sensor de tracking.
 * @param Recibe el valor del sensor de obstáculo lateral.
 * @return Retorna un bool que indica si el final de la pista ha sido alcanzado.
*/
bool end_detection(int _track1, int _track2)
{
  bool FINAL_DE_PISTA = false;
  if ((_track1 == 1) && (_track2 == 0))
  {
    FINAL_DE_PISTA = true;
  }
  return FINAL_DE_PISTA;
};



/**
 * @brief Esta función determina si se detecta un obstáculo frontal gracias al sensor de obstáculo, en caso de presencia de obstáculo activa el servomotor para removerlo..
 * @param Recibe el valor de un sensor de obstáculo frontal.
 * @return No retorna valores, solo activa el servomotor.
*/
void obstacle_detection(bool _obstacle_presence)
{
  if (_obstacle_presence == 0)
  {
    myServo.attach(servo_pin);
    myServo.write(servo_open);
    delay(700);
    myServo.write(servo_close);
    delay(700);
  };
  myServo.detach();
}



/**
 * @brief Esta función solo enciende las luces en una determinada secuencia para indicar el final del recorrido.
 * @param No recibe parámetros.
 * @return No retorna, solo acciona LED RGB.
*/
void final_track_indicator()
{
  digitalWrite(R, HIGH);
  delay(100);
  digitalWrite(R, HIGH);
  delay(50);
  digitalWrite(G, HIGH);
  delay(100);
  digitalWrite(G, LOW);
  delay(50);
  digitalWrite(B, HIGH);
  delay(100);
  digitalWrite(B, LOW);
  delay(50);
  digitalWrite(R, HIGH);
  delay(100);
  digitalWrite(R, HIGH);
  delay(50);
  digitalWrite(G, LOW);
  delay(100);
  digitalWrite(G, LOW);
  delay(50);
  digitalWrite(B, HIGH);
  delay(100);
  digitalWrite(B, LOW);
  digitalWrite(R, LOW);
  digitalWrite(G, LOW);
  delay(100);
};


/**
 * @brief Esta función hace que se activen las ruedas de manera que el vehíulo gire sobre su propio eje horizontal para el modo tracking.
 * @param No recibe parámetros.
 * @return No retorna.
*/
void trompo()
{
  digitalWrite(motorL_reverse, motorPower);
  digitalWrite(motorL_forward, 0);
  digitalWrite(motorR_reverse, 0);
  digitalWrite(motorR_forward, motorPower);
  delay(reactionD);
};

/**
 * @brief Esta función hace que se activen las ruedas de manera que el vehíulo gire sobre su propio eje horizontal para el modo control.
 * @param Recibe la potencia que se desea usar para los motores.
 * @return No retorna.
*/
void trompo_final(int power)
{
  digitalWrite(motorL_reverse, power);
  digitalWrite(motorL_forward, 0);
  digitalWrite(motorR_reverse, 0);
  digitalWrite(motorR_forward, power);
};

/**
 * @brief Esta función implementa y ejecuta las acciones y funciones necesarias para el funcionamiento durante el modo tracking.
 * @param No recibe parámetros.
 * @return No retorna.
*/
void tracking_mode_func()
{
  goL(235);
  goR(235);
  obstacle_detection(digitalRead(obstacle_pin));
  if (end_detection(digitalRead(track1_pin), digitalRead(final_pin)) == 1)      // if structure to check final of track
  {
    delay(1000);
    while (1)
    {
      trompo_final(200);
      delay(300);
      trompo_final(0);
      delay(100);
      final_track_indicator();
      if (mySerial.read() == '2')   //break cuando el puerto serial recibe un carácter '2' y luego se va a "Waiting Mode"
      {
        break;
      };
    }
  };
};


/**
 * @brief Esta función implementa y ejecuta las acciones y funciones necesarias para el funcionamiento durante el modo de control.
 * @param No recibe parámetros.
 * @return No retorna.
*/
void control_mode_func()
{
  char c;
  while (1)
  {
    no_move();
    c = mySerial.read();    //actualización constante para valor recibido en puerto serial
    if (c == 's') //Reverse
    {
      forward_control();
    };
    if (c == 'w') //forward
    {
      reverse_control();
    };
    if (c == 'a') //Turn left
    {
      goL_control();
    };
    if (c == 'd') //Turn rigth
    {
      goR_control();
    };
    if (c == 'b') //buzzer sound
    {
      digitalWrite(buzzer, HIGH);
      delay(1);
      digitalWrite(buzzer, LOW);
      delay(1);
      digitalWrite(buzzer, HIGH);
      delay(1);
    };
    if (c == 't') //trompo
    {
      trompo();
    };
    if (c == '2') //break cuando el puerto serial recibe un carácter '2' y luego se va a "Waiting Mode"
    {
      break;
    };
    if (c == 'y') //Obstacle remove
    {
      myServo.attach(servo_pin);
      myServo.write(servo_open);
      delay(700);
      myServo.write(servo_close);
      delay(700);
      myServo.detach();
    };
  }
};