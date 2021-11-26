/*
   A fájl a GitLab lerakatban található
   A fájlhoz a ../build-vezerlo-gui vezérlőfelülete tartozik
*/

//könyvtárak includálása
#include <Servo.h>
#include <dht11.h>


//pinek és konstansok definiálása
#define krittav 60 //cm
#define motorNull 1490
#define WSens 8
#define trig 27
#define echo 28
#define RAD_trig 35
#define RAD_echo 34
#define csp1 0
#define m1 3
#define m2 4
#define r1 26
#define r2 25
#define DHTPIN 12
#define TPIN1 12
#define TPIN2 13
#define OK_LED_Z 25
#define OK_LED_P 26
#define motorNullVal 0
#define raspiAkk_PIN 14
#define PWM_M1 10
#define PWM_M2 11
#define RAD_servop 2
#define PONTON_MOTOR 6
#define PONTON_KORMANY 7
#define TALCA_SERB 8
#define TALCA_SERJ 9



#define KAR_ALSO 6
#define KAR_FORGATO 7
#define KAR_BOLINTO_ALSO 40
#define KAR_BOLINTO_FELSO 41

#define BALLASZT_REL_B_B 22
#define BALLASZT_REL_B_K 23
#define BALLASZT_PRES 2


//könyvtár pédányok létrehozása
Servo sb;
Servo sj;
Servo mb;
Servo mj;
Servo RAD_s;


Servo karAlso;
Servo karForgato;
Servo karBolintoa;
Servo karBolintof;

Servo talcaBal;
Servo talcaJobb;


DHT dht(DHTPIN, DHT11); //pin, type

String rpidata;
long kommill = -10;
bool komms;
long timer2 = millis();
bool melymeresb;
int mely;
int bviz;
int errNo[5] = {0, 0, 0, 0, 0};
unsigned long timer = 0;
float timeStep = 0;
int chk;
float h1;
float h2;
float hum;
float h3;
long mtime;
long lastCom;
int motorReset;
long motorTime;
bool motorLetilt = 0;
int ledAllapot = 0;
bool ledSet_vill;
long ledTime;
bool releLetilt;
long milltime2;
int RAD_pos = 9;
int RAD_adatok[18];
long talcaTime;
int talcaFok;

long ballaszt_timer = millis();
long ballaszt_timer2 = millis();
int ballaszt_bal_toltottseg;
int ballaszt_jobb_toltottseg;
int BALLASZT_MAXPOF_L = 60;
int BALLASZT_MAXPOF = 20;

int ballasztPump = BALLASZT_MAXPOF; //max
bool ballaszt_nyitvaB_L = 0;
bool ballaszt_nyitvaB_F = 0;

bool ballaszt_nyitvaJ = 0;


//kommunikáció
int myArray[30];
byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
size_t pcDataLen = sizeof(myArray);
bool newData = false;


void setup()
{
    pinMode(BALLASZT_REL_B_B, OUTPUT);
  pinMode(BALLASZT_REL_B_K, OUTPUT);
  digitalWrite(BALLASZT_REL_B_B, 1); //relék kikapcsolása
  digitalWrite(BALLASZT_REL_B_K, 1);
  Serial.begin(115200);
  pinMode(trig, OUTPUT); pinMode(echo, INPUT);
  pinMode(RAD_trig, OUTPUT); pinMode(RAD_echo, INPUT);
  pinMode(m1, OUTPUT); pinMode(m2, OUTPUT);
  pinMode(r1, OUTPUT); pinMode(r2, OUTPUT);
  pinMode(OK_LED_Z, OUTPUT);
  pinMode(TALCA_SERB, OUTPUT);
  pinMode(TALCA_SERJ, OUTPUT);


  mb.attach(m1);
  mj.attach(m2);
  karAlso.attach(KAR_ALSO);
  karForgato.attach(KAR_FORGATO);
  karBolintoa.attach(KAR_BOLINTO_ALSO);
  karBolintof.attach(KAR_BOLINTO_FELSO);
  RAD_s.attach(RAD_servop);
  talcaBal.attach(TALCA_SERB);
  talcaJobb.attach(TALCA_SERJ);
  RAD_s.write(90);

  delay(500);

  myArray[3] = 1;

  dht.begin();
  digitalWrite(OK_LED_Z, 0);
  //motorReset=1;
}

void loop()
{
  checkForNewData();
  BALLASZT_MAXPOF_L=myArray[25];BALLASZT_MAXPOF=myArray[24];
  ballaszt(myArray[20], myArray[21]);
  if (newData == true) {
    newData = false;
    //lastCom=millis();
  }

  if (myArray[22] > 50) {
    ledAllapot = 3;
  }
  ledSet(ledAllapot);

  if (millis() - milltime2 > 50) //Robotkar beállítása
  {
    milltime2 = millis();
    if (myArray[12] == 1) {
      radar();
    }
    robotkarSet();
    if (myArray[23] == 1) {
      talcaJobb.write(180 - myArray[13]);
      talcaBal.write(myArray[13]);
    }

  }
  if (millis() - mtime > 300 || millis() % 300 == 0)
  {
    mtime = millis();
    //hő, és páratartalom mérés
    h1 = hm(TPIN1); //12-es hm
    h2 = hm(TPIN2); //13-as hm
    hum = dht.readHumidity(0); //páratartalom
    h3 = dht.readTemperature(0); // dht hőmérője
    if (hum == NAN) {
      hum = 0;
    }
    if (h3 == NAN) {
      h3 = 0;
    }
  }

  if (millis() - kommill > 15) //Kommunikáció, és adatgyűjtés
  {
    kommill = millis();

    //int mely = tavm(0);
    //mely=0;
    checkCom();
    bviz = analogRead(WSens);
    int motorBalRead = mb.readMicroseconds();
    int motorJobbRead = mj.readMicroseconds();
    //motorJobbRead=myArray[0];
    int raspiAkk = analogRead(raspiAkk_PIN);
    //kommunikáció:
    rpikom(komms, bviz, mely, err_k(), analogRead(csp1), h1, h2, h3, hum, 
      motorBalRead, motorJobbRead, raspiAkk, double(random(50,90))/10, double(random(1500,8000))/10, 
      double(random(0,100000))/150, double(random(1000,10000))/10, double(random(0,5000))/10, 
      RAD_adatok[RAD_pos],ballaszt_bal_toltottseg,ballaszt_jobb_toltottseg,pressure(),0);

    komms = 0;
    vegrehajt();

  }
}
void robotkarSet() {
  karAlso.write(myArray[12]);
  karBolintoa.write(myArray[14]);
  karBolintof.write(myArray[15]);
}
void checkCom() {
  if (millis() - lastCom > 100) {
    if (motorLetilt == 0) {
      ledAllapot = 0;
    }
    komms = 0;
  }
  else {
    if (motorLetilt == 0) {
      ledAllapot = 1;
    }
    komms = 1;
  }
  if (millis() - lastCom > 10000) {
  }
}
void radar() {
  int atlag;
  atlag = tavm(1); //atlag=atlag+tavm(1);atlag=atlag+tavm(1);atlag=atlag+tavm(1);atlag=atlag+tavm(1);

  RAD_adatok[RAD_pos] = atlag; //5;

  RAD_pos++;
  if (RAD_pos == 19) {
    RAD_pos = 0;
  }

  RAD_s.write((RAD_pos * 5) + 45);
}
void vegrehajt()
{
  //motorok beállítása
  //if (motorLetilt==0){

  mj.writeMicroseconds(myArray[10] + motorNull);
  mb.writeMicroseconds(myArray[1] + motorNull);
  //}
  //  else{
  //    ledAllapot=3;
  //  }
  analogWrite(PWM_M1, myArray[16]);
  analogWrite(PWM_M2, myArray[17]);

  melymeresb = 1;
  //mélységmérés kérése
  if (myArray[2] == 1) {
    mely = tavm(0);
  }
  //vezérsíkok beállítása - törölt

  // relék beállítása
  if (releLetilt != 1) {
    switch (myArray[3]) {
      case 1:
        digitalWrite(r1, 1); digitalWrite(r2, 1);
        break;
      case 2:
        digitalWrite(r1, 0); digitalWrite(r2, 1);
        break;
      case 3:
        digitalWrite(r1, 0); digitalWrite(r2, 0);
        break;
      case 4:
        digitalWrite(r1, 1); digitalWrite(r2, 0);
        break;
      default:
        //error!!
        error(1);
    }
  }
  //Akkuszámok: (index:[6]) 1(alap), 2(aruino másodlagos, rpi els.) 3(másodlagosok), 4(rpi masodlagos arduino elsodleges), 5(vészakku)


  //Motor újraindításának beállítása
  if (myArray[9] == 1) {
    motorReset = 1;
  }
}
/*
  float hm(int pin){
  float temp;
  temp = analogRead(pin);
  temp = temp * 0.48828125;
  return temp;
  }
*/

void ballaszt(int bal, int jobb) {
  //bal
  bal=bal;
  if (ballaszt_nyitvaB_F==0 && ballaszt_nyitvaB_L == 0) {
    int bkul = int(bal) - ballaszt_bal_toltottseg;
    if (bkul < 0) {
      //nyomás csökkentése 1-el
      digitalWrite(BALLASZT_REL_B_K, 0);
      ballaszt_nyitvaB_L = 1;
      ballaszt_timer = millis();
      ballaszt_bal_toltottseg--;
    }
    else if (bkul > 0) {
      //nyomás növelése 1-el
      digitalWrite(BALLASZT_REL_B_B, 0);
      ballaszt_nyitvaB_F = 1;
      ballaszt_timer = millis();
      ballaszt_bal_toltottseg++;
    }
    else {
      /*Ballaszt beállítás helyes*/
    }
  }

  if (ballaszt_nyitvaB_L == 1) {
    if (millis() - ballaszt_timer > BALLASZT_MAXPOF_L) {
      digitalWrite(BALLASZT_REL_B_K, 1);
      digitalWrite(BALLASZT_REL_B_B, 1);
      ballaszt_nyitvaB_L = 0;
    }
  }
  if (ballaszt_nyitvaB_F == 1) {
    if (millis() - ballaszt_timer > BALLASZT_MAXPOF) {
      digitalWrite(BALLASZT_REL_B_K, 1);
      digitalWrite(BALLASZT_REL_B_B, 1);
      ballaszt_nyitvaB_F = 0;
    }
  }

//jobb törölve
}



void talca(int fok) {

}

int pressure(){
  int val=analogRead(BALLASZT_PRES);
  return val;
}


float hm(int pin) {
  int reading = analogRead(pin);

  // converting that reading to voltage, for 3.3v arduino use 3.3
  float voltage = reading * 5.0;
  voltage /= 1024.0;

  // print out the voltage

  // now print out the temperature
  float temp = (voltage - 0.5) * 100 ;
  return temp;
}




void rpikom(int a, int b, int c, int d, int e, double f,
            double g, double h, double i, double j, double k, double l, double m, double n,
            double o, double p, int q, int r, int s, int t, int u, int v)
{
  String
  rpidata = "[" + String(a) + "," + String(b) + "," + String(c) + "," + 
  String(d) + "," + String(e) + "," + String(f) + "," + String(g) + "," + 
  String(h) + "," + String(i) + "," + String(j) + "," + String(k) + "," + 
  String(l) + "," + String(m) + "," + String(n) + "," + String(o) + "," + 
  String(p) + "," + String(q) + "," + String(r) + "," + String(s) + "," + 
  String(t) + "," + String(u) + "," + String(v) + "]";
  Serial.println(rpidata);
  delay(1);
}


void error(int kod) {
  if (errNo[0] == 0)
  {
    errNo[0] = kod;
    return;
  }
  if (errNo[1] == 0)
  {
    errNo[1] = kod;
    return;
  }
  if (errNo[2] == 0)
  {
    errNo[2] = kod;
    return;
  }
  if (errNo[3] == 0)
  {
    errNo[3] = kod;
    return;
  }
  if (errNo[4] == 0)
  {
    errNo[4] = kod;
    return;
  }
}

int err_k() {
  int ret = errNo[0];
  for (int i; i < 4; i++) {
    errNo[i] = errNo[i + 1];
  }
  errNo[5] = 0;
  return ret;
}

bool ellenorzes()
{
  int problem;
  int retlist[2];
  if (analogRead(1))
  {
    retlist[0] = 1;
    problem++;
  }
  else {
    retlist[0] = 0;
  }
  /*
    if(tavm<krittav)
    {
    retlist[0]=1;
    problem++;
    }*/
}

int tavm(int sz)
{
  if (sz == 0) {
    digitalWrite(trig, 0);
    delayMicroseconds(5);
    digitalWrite(trig, 1);
    delayMicroseconds(10);
    digitalWrite(trig, 0);
    long ido;
    ido = pulseIn(echo, HIGH, 10000);
    int tav = 0.0345 * ido / 2;
    if (tav == 0) {
      error(2);
    }
    return tav;
  }
  if (sz == 1) {
    digitalWrite(RAD_trig, 0);
    delayMicroseconds(5);
    digitalWrite(RAD_trig, 1);
    delayMicroseconds(10);
    digitalWrite(RAD_trig, 0);
    long ido;
    ido = pulseIn(RAD_echo, HIGH, 10000);
    int tav = 0.1496 * ido / 2;
    if (tav == 0) {
      error(2);
    }
    return tav;
  }
}


double fm(int Apin) { //just 12v
  int f = analogRead(Apin) * 11 / 204.6;
  return f;
}

void checkForNewData () {
  if (Serial.available() >= pcDataLen && newData == false) {
    byte inByte;
    for (byte n = 0; n < pcDataLen; n++) {
      ddata [n] = Serial.read();
    }
    while (Serial.available() > 0) { // now make sure there is no other data in the buffer
      byte dumpByte =  Serial.read();
      Serial.println(dumpByte);
    }
    newData = true;
  }
}
void ledSet(int all) {

  if (all == 0) {
    digitalWrite(OK_LED_Z, 1);
  }
  else if (all == 1) {
    digitalWrite(OK_LED_Z, 0);
  }
  else if (all == 3) {
    if (millis() - ledTime > 100) {
      ledTime = millis();
      if (ledSet_vill == 0) {
        digitalWrite(OK_LED_Z, 0);
        ledSet_vill = 1;
      } else {
        digitalWrite(OK_LED_Z, 1);
        ledSet_vill = 0;
      }
    }
  }
}
void vesz() {
  // felszínre emelkedés

  //motorok kikapcsolása
  digitalWrite(r1, 1);
  digitalWrite(r2, 1);

}

