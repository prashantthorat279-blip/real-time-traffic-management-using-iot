// ================= IR Sensors =================
#define IR1 34
#define IR2 35
#define IR3 32

// ================= Sound Sensor =================
#define SOUND_SENSOR 4

// ================= LEDs =================
#define RED1 12
#define GREEN1 14

#define RED2 27
#define GREEN2 13

// ================= Seven Segment =================
#define a 18
#define b 19
#define c 21
#define d 22
#define e 23
#define f 25
#define g 26

// ================= Setup =================
void setup() {

  pinMode(IR1, INPUT);
  pinMode(IR2, INPUT);
  pinMode(IR3, INPUT);

  pinMode(SOUND_SENSOR, INPUT);

  pinMode(RED1, OUTPUT);
  pinMode(GREEN1, OUTPUT);

  pinMode(RED2, OUTPUT);
  pinMode(GREEN2, OUTPUT);

  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

// ================= Display Function =================
void displayNumber(int num) {

  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);

  switch(num) {

    case 0:
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,HIGH);
      digitalWrite(f,HIGH);
      break;

    case 1:
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      break;

    case 2:
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,HIGH);
      digitalWrite(g,HIGH);
      break;

    case 3:
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(g,HIGH);
      break;

    case 4:
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;

    case 5:
      digitalWrite(a,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;

    case 6:
      digitalWrite(a,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,HIGH);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;

    case 7:
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      break;

    case 8:
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(e,HIGH);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;

    case 9:
      digitalWrite(a,HIGH);
      digitalWrite(b,HIGH);
      digitalWrite(c,HIGH);
      digitalWrite(d,HIGH);
      digitalWrite(f,HIGH);
      digitalWrite(g,HIGH);
      break;
  }
}

// ================= Countdown Function =================
void countdown(int timeValue) {

  for(int i = timeValue; i >= 0; i--) {

    displayNumber(i % 10);

    delay(1000);
  }
}

// ================= Main Loop =================
void loop() {

  // ================= Ambulance Detection =================
  int ambulance = digitalRead(SOUND_SENSOR);

  // If ambulance sound detected
  if(ambulance == HIGH) {

    // Road 1 GREEN immediately
    digitalWrite(GREEN1, HIGH);
    digitalWrite(RED1, LOW);

    // Road 2 RED
    digitalWrite(GREEN2, LOW);
    digitalWrite(RED2, HIGH);

    // Emergency countdown
    countdown(9);

    return;
  }

  // ================= Read IR Sensors =================
  int sensor1 = !digitalRead(IR1);
  int sensor2 = !digitalRead(IR2);
  int sensor3 = !digitalRead(IR3);

  // ================= Density Calculation =================
  int densityRoad1 = sensor1 + sensor2;

  // ================= HIGH DENSITY ROAD 1 =================
  if(densityRoad1 >= 1) {

    // Road 1 GREEN
    digitalWrite(GREEN1, HIGH);
    digitalWrite(RED1, LOW);

    // Road 2 RED
    digitalWrite(GREEN2, LOW);
    digitalWrite(RED2, HIGH);

    // Show stop time for Road 2
    countdown(9);

    // Change Signals
    digitalWrite(GREEN1, LOW);
    digitalWrite(RED1, HIGH);

    digitalWrite(GREEN2, HIGH);
    digitalWrite(RED2, LOW);

    delay(5000);
  }

  // ================= ROAD 2 ACTIVE =================
  else if(sensor3 == 1) {

    // Road 2 GREEN
    digitalWrite(GREEN2, HIGH);
    digitalWrite(RED2, LOW);

    // Road 1 RED
    digitalWrite(GREEN1, LOW);
    digitalWrite(RED1, HIGH);

    // Stop time for Road 1
    countdown(5);

    // Change Signals
    digitalWrite(GREEN2, LOW);
    digitalWrite(RED2, HIGH);

    digitalWrite(GREEN1, HIGH);
    digitalWrite(RED1, LOW);

    delay(5000);
  }

  // ================= DEFAULT CONDITION =================
  else {

    // Road 1 GREEN
    digitalWrite(GREEN1, HIGH);
    digitalWrite(RED1, LOW);

    digitalWrite(GREEN2, LOW);
    digitalWrite(RED2, HIGH);

    countdown(5);

    // Switch
    digitalWrite(GREEN1, LOW);
    digitalWrite(RED1, HIGH);

    digitalWrite(GREEN2, HIGH);
    digitalWrite(RED2, LOW);

    countdown(5);
  }
}