#include <Servo.h>

int ledtg = 11, ledtr = 12, ledpg = 13, ledbp = 6, ledbr = 7;
Servo brushA;
Servo brushB;
Servo pill;
int pillPos, pos = 0;
long int operation, day = 0;
bool UPS = false; // Default state for TB position, up or down;

void setup() {
  Serial.begin(9600);
  Serial.println();
  Serial.println(" =====================================================================");
  Serial.println("       Welcome, Automated Toothbrush & Pill Dispenser v1.");
  Serial.println("   Internet Of Things, by Kyle T & Jody B, copyright 2020.");
  Serial.println(" =====================================================================");

  pinMode(ledtg, OUTPUT);
  pinMode(ledtr, OUTPUT);
  pinMode(ledpg, OUTPUT);
  pinMode(ledbp, OUTPUT);
  pinMode(ledbr, OUTPUT);

  brushA.attach(9);
  brushB.attach(10);
  pill.attach(6);

  // Asks for day and sets day as number of the week 1 to 7!
  Serial.print(" 1. Enter Day [1 = Mon to 7 = Sun] : ");
  while (Serial.available() == 0) {}
  day = Serial.read() - '0'; delay(10);
  if (day == 1)Serial.print("Monday");
  else if (day == 2)Serial.print("Tuesday\n");
  else if (day == 3)Serial.print("Wednesday\n");
  else if (day == 4)Serial.print("Thursday\n");
  else if (day == 5)Serial.print("Friday\n");
  else if (day == 6)Serial.print("Saturday\n");
  else if (day == 7)Serial.print("Sunday\n");
  else {
    Serial.print("VOID ENTRY\n");
    setup();
  };
  Serial.println();
}

void ponLights() {
  digitalWrite(ledbp, HIGH);
  digitalWrite(ledbr, HIGH);
  digitalWrite(ledpg, HIGH);
}

void poffLights() {
  digitalWrite(ledbp, LOW);
  digitalWrite(ledbr, LOW);
  digitalWrite(ledpg, LOW);
}

void upup() {

  Serial.println("Running UPUP() function\n");

  for (pos = 0; pos <= 90; pos += 1) {
    digitalWrite(ledtr, LOW);
    digitalWrite(ledtg, HIGH);
    brushA.write(pos);
    delay(15);
  }
  for (pos = 90; pos <= 180; pos += 1) {
    brushB.write(pos);
    delay(15);
  }
}

void down() {

  Serial.println("Running DOWN() function\n");

  for (pos = 90; pos >= 0; pos -= 1) { //Rotates first toothbrush servo down.
    digitalWrite(ledtg, LOW);
    digitalWrite(ledtr, HIGH);
    brushA.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 90; pos -= 1) {
    brushB.write(pos);
    delay(15);
  }
}


void loop() {

  Serial.println();
  Serial.print(" 2. Enter Operation [1 = Up, 2 = Down, 3 = Dispense, 4 = OFF] : ");
  while (Serial.available() == 0) {}
  operation = Serial.read() - '0'; delay(50);
  Serial.print("Operation = "); Serial.println(operation);
  Serial.println(); Serial.flush();

  // do something different depending on the range value:
  switch (operation) {

    case 1:
      Serial.println("Sending Toothbrush up\n");

      if (UPS == false) {

        Serial.print("TOOTHBRUSH IS ALREADY UP!  ");
        Serial.println(UPS);
        return;
      };

      upup();
      delay(100);
      UPS = false;
      Serial.print("TOOTHBRUSH IS UP!  ");
      Serial.println(UPS);
      Serial.println();
      break;

    case 2:
      Serial.println("Sending Toothbrush down\n");

      down();
      delay(100);
      UPS = true;
      Serial.print("TOOTHBRUSH IS DOWN!  ");
      Serial.println(UPS);
      Serial.println();
      break;

    case 3:
      Serial.println("Dispensing PILLS\n");

      ponLights();
      delay(3000);

      if (day == 1) {

        for (pillPos = 0; pillPos <= 35; pillPos += 1)
          pill.write(pillPos);
        delay(1000);
        for (pillPos = 35; pillPos <= 0; pillPos += 1)
          pill.write(pillPos);
        delay(100);
      }

      else if (day == 2) {
        for (pillPos = 0; pillPos <= 70; pillPos += 1)
          pill.write(pillPos);
        delay(1000);
        for (pillPos = 70; pillPos <= 0; pillPos += 1)
          pill.write(pillPos);
        delay(100);
      }

      else if (day == 3) {
        for (pillPos = 0; pillPos <= 105; pillPos += 1)
          pill.write(pillPos);
        delay(1000);
        for (pillPos = 105; pillPos <= 0; pillPos += 1)
          pill.write(pillPos);
        delay(100);
      }

      else if (day == 4) {
        for (pillPos = 0; pillPos <= 140; pillPos += 1)
          pill.write(pillPos);
        delay(1000);
        for (pillPos = 140; pillPos <= 0; pillPos += 1)
          pill.write(pillPos);
        delay(100);
      }

      else if (day == 5) {
        for (pillPos = 0; pillPos <= 175; pillPos += 1)
          pill.write(pillPos);
        delay(1000);
        for (pillPos = 175; pillPos <= 0; pillPos += 1)
          pill.write(pillPos);
        delay(100);
      }
      else if (day == 6) {
        for (pillPos = 0; pillPos <= 0; pillPos += 1)
          pill.write(pillPos);
        delay(1000);
        for (pillPos = 0; pillPos <= 0; pillPos += 1)
          pill.write(pillPos);
        delay(100);
        Serial.println("Prototype Function!\n");
      }
      else
        for (pillPos = 0; pillPos <= 0; pillPos += 1)
          pill.write(pillPos);
      delay(1000);
      for (pillPos = 0; pillPos <= 0; pillPos += 1)
        pill.write(pillPos);
      delay(100);
      Serial.println("Prototype Function!\n");
      poffLights();
      delay(5000);
      break;

    case 4:
      Serial.println("\t\t### CLOSE ###");
      pill.write(0);
      delay(100);
      setup();     
      break;
      
    default:
      break;
  }
  delay(20);

  Serial.println("");
  Serial.println("============= ^^End of loop^^ ============= ");
  Serial.println("=========================================== ");
}
