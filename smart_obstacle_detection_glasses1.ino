const int trigPins[3] = {3, 5, 7};   // Left, Front, Right
const int echoPins[3] = {2, 4, 6};

const int buzzerPins[3] = {10, 11, 12};

const int dangerDistance = 100;

int distances[3] = {0, 0, 0};

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(trigPins[i], OUTPUT);
    pinMode(echoPins[i], INPUT);
    pinMode(buzzerPins[i], OUTPUT);
  }

  Serial.begin(9600);
}

void loop() {
  readSensors();
  updateBuzzers();
  printDebug();
}

void readSensors() {
  for (int i = 0; i < 3; i++) {
    distances[i] = getDistance(i);
  }
}

int getDistance(int i) {
  digitalWrite(trigPins[i], LOW);
  delayMicroseconds(2);
  digitalWrite(trigPins[i], HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPins[i], LOW);

  long duration = pulseIn(echoPins[i], HIGH, 30000);
  int distance = duration * 0.034 / 2;

  if (distance == 0) distance = 999;

  return distance;
}

void updateBuzzers() {

  for (int i = 0; i < 3; i++) {
    digitalWrite(buzzerPins[i], LOW);
  }

  // FRONT (danger priority)
  if (distances[1] < 150) {
    digitalWrite(buzzerPins[1], HIGH);
    delay(50);
    digitalWrite(buzzerPins[1], LOW);
    delay(50);
    return;
  }

  // LEFT warning
  if (distances[0] < dangerDistance) {
    digitalWrite(buzzerPins[0], HIGH);
    delay(150);
    digitalWrite(buzzerPins[0], LOW);
    delay(300);
  }

  // RIGHT warning
  if (distances[2] < dangerDistance) {
    digitalWrite(buzzerPins[2], HIGH);
    delay(300);
    digitalWrite(buzzerPins[2], LOW);
    delay(300);
  }
}

void printDebug() {
  Serial.print("L:");
  Serial.print(distances[0]);
  Serial.print(" cm | F:");
  Serial.print(distances[1]);
  Serial.print(" cm | R:");
  Serial.println(distances[2]);
}