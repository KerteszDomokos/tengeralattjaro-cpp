//könyvtárak includálása
#include <Servo.h>
#include <DHT.h>



//pinek és konstansok definiálása
#define krittav 60 //cm
#define WSens 15
#define trig 30
#define echo 31
#define csp1 0
#define m1 4
#define m2 5
#define r1 26
#define r2 25
#define DHTPIN 24
#define TPIN1 12
#define TPIN2 13
#define OK_LED_Z 22
#define OK_LED_P 23
#define motorNullVal 0
#define raspiAkk_PIN 14
#define PWM_M1 10
#define PWM_M2 11

#define KAR_ALSO 6
#define KAR_FORGATO 7
#define KAR_BOLINTO_ALSO 8
#define KAR_BOLINTO_FELSO 9

//könyvtár: pédányok létrehozása
Servo sb;
Servo sj;
Servo mb;
Servo mj;

Servo karAlso;
Servo karForgato;
Servo karBolintoa;
Servo karBolintof;

DHT dht(DHTPIN, DHT11); //pin, type

String rpidata;
long kommill=-10;
bool komms;
long timer2=millis();
bool melymeresb;
int mely;
int bviz;
int errNo[5]={0,0,0,0,0};
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
bool motorLetilt=0;
int ledAllapot=0;
bool ledSet_vill;
long ledTime;
bool releLetilt;
long milltime2;

//kommunikáció
int myArray[20];
byte* ddata = reinterpret_cast<byte*>(&myArray); // pointer for transferData()
size_t pcDataLen = sizeof(myArray);
bool newData=false;


void setup() 
{
Serial.begin(115200);
pinMode(trig,OUTPUT);pinMode(echo,INPUT);
pinMode(m1,OUTPUT); pinMode(m2, OUTPUT);
pinMode(r1,OUTPUT); pinMode(r2, OUTPUT);
pinMode(OK_LED_Z,OUTPUT);

mb.attach(m1);
mj.attach(m2);
karAlso.attach(KAR_ALSO);
karForgato.attach(KAR_FORGATO);
karBolintoa.attach(KAR_BOLINTO_ALSO);
karBolintof.attach(KAR_BOLINTO_FELSO);

myArray[3]=1;

dht.begin();
digitalWrite(OK_LED_Z,0);
//motorReset=1;
}

void loop() 
{
  if (motorLetilt==1){
    ledAllapot=3;
  }
  ledSet(ledAllapot);
  motorReset=motorSet(0,motorReset);
  
  if (millis()-milltime2>20)    //Robotkar beállítása
  {
    robotkarSet();
  }
    if (millis()-mtime>300 || millis()%300==0)    
  {
    mtime=millis();
    //hő, és páratartalom mérés
     h1=hm(TPIN1);//12-es hm
     h2=hm(TPIN2);//13-as hm
     hum=dht.readHumidity(0);//páratartalom
     h3=dht.readTemperature(0); // dht hőmérője
     if (hum==NAN){hum=0;}
     if (h3==NAN){h3=0;}
  }

    checkForNewData();
  if (newData == true) {
    newData = false;
    lastCom=millis();
    }

if (millis()-kommill>10) //Kommunikáció, és adatgyűjtés
{
  kommill=millis();
  //int mely = tavm();
  //mely=0;
  checkCom();
  bviz=analogRead(WSens);
  int motorBalRead = mb.read();
  int motorJobbRead= mj.read();
  //motorJobbRead=myArray[0];
  int raspiAkk = analogRead(raspiAkk_PIN);
  //kommunikáció:
  rpikom(komms,bviz,mely,err_k(),analogRead(csp1),h1,h2,h3,hum,motorBalRead,motorJobbRead,raspiAkk,12,13,14,15,16,17,18);
  
  komms=0;
  vegrehajt();
  
}
}
void robotkarSet(){
  karAlso.write(myArray[12]);
  karForgato.write(myArray[13]);
  karBolintoa.write(myArray[14]);
  karBolintof.write(myArray[15]);
}
void checkCom(){
if (millis()-lastCom>100){
  if (motorLetilt==0){
  ledAllapot=0;}
  komms=0;
}
else{
  if (motorLetilt==0){
  ledAllapot=1;}
  komms=1;
}
if (millis()-lastCom>10000){
  vesz();
}
}

void vegrehajt()
{
  //motorok beállítása
  if (motorLetilt==0){
  
  mj.writeMicroseconds(myArray[10]+motorNullVal);
  mb.writeMicroseconds(myArray[1]+motorNullVal);
  }
  else{
    ledAllapot=3;
  }
  analogWrite(PWM_M1,myArray[16]);
  analogWrite(PWM_M2,myArray[17]);

  melymeresb=1;
//mélységmérés kérése
  if (myArray[2]==1){
    mely = tavm();
  }
//vezérsíkok beállítása - törölt

// relék beállítása
if (releLetilt!=1){
switch(myArray[3]){
  case 1:
  digitalWrite(r1,1);digitalWrite(r2,1);
  break;
  case 2:
  digitalWrite(r1,0);digitalWrite(r2,1);
  break;
  case 3:
  digitalWrite(r1,0);digitalWrite(r2,0);
  break;
  case 4:
  digitalWrite(r1,1);digitalWrite(r2,0);
  break;
  default:
  //error!!
  error(1);
}
}
//Akkuszámok: (index:[6]) 1(alap), 2(aruino másodlagos, rpi els.) 3(másodlagosok), 4(rpi masodlagos arduino elsodleges), 5(vészakku)


//Motor újraindításának beállítása
  if (myArray[9]==1){
    motorReset=1;
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
float hm(int pin){
int reading = analogRead(pin);  
 
 // converting that reading to voltage, for 3.3v arduino use 3.3
 float voltage = reading * 5.0;
 voltage /= 1024.0; 
 
 // print out the voltage
 
 // now print out the temperature
 float temp = (voltage - 0.5) * 100 ;
 return temp;
}

int motorSet(bool dela,int motorR){
  if (dela==1){
    delay(5000);
    mb.write(0);
    mj.write(0);
    delay(3000);
    mb.write(motorNullVal);
    mj.write(motorNullVal);
    delay(4000);
    mb.write(0);
    mj.write(0);
    delay(3000);
    motorLetilt=0;
  }
  if (dela==0) {
      if (motorR==1){
        mb.write(0);
        mj.write(0);
          motorTime = millis();
        digitalWrite(r1,1);
        digitalWrite(r2,1);
        releLetilt=1;
        motorLetilt=1;
        motorR=2;
      }
       if (motorR==2){
        if (millis()-motorTime>4000){
          digitalWrite(r1,1);
        mb.write(motorNullVal);
        mj.write(motorNullVal);
        digitalWrite(r1,0);
        digitalWrite(r2,0);
        motorR=3;
        motorTime=millis();
        }
      }
       if (motorR==3){
        if (millis()-motorTime>5000){
        mb.write(0);
        mj.write(0);
        motorR=4;
        motorTime=millis();
        }
      }
       if (motorR==4){
        if (millis()-motorTime>4000){
          motorLetilt=0;
          motorR=0;
          releLetilt=0;
        }
      }
    }
return motorR;
}


void rpikom(int a,int b,int c,int d,int e,double f,
double g,double h,int i,int j,int k,int l,int m,int n,
int o,int p,int q,int r,double s)
{
  String
rpidata="["+String(a)+","+String(b)+","+String(c)+","+String(d)+","+String(e)+","+String(f)+","+String(g)+","+String(h)+","+String(i)+","+
String(j)+","+String(k)+","+String(l)+","+String(m)+","+String(n)+","+String(o)+","+String(p)+","+String(q)+","+String(r)+","+String(s)+"]";
  Serial.println(rpidata);
  delay(1);
}


void error(int kod){
  if (errNo[0]==0)
  {
    errNo[0]=kod;
    return;
  }
    if (errNo[1]==0)
  {
    errNo[1]=kod;
    return;
  }
    if (errNo[2]==0)
  {
    errNo[2]=kod;
    return;
  }
    if (errNo[3]==0)
  {
    errNo[3]=kod;
    return;
  }
    if (errNo[4]==0)
  {
    errNo[4]=kod;
    return;
  }
}

int err_k(){
int ret=errNo[0];
for (int i; i<4; i++){
  errNo[i]=errNo[i+1];
}
errNo[5]=0;
return ret;
}

bool ellenorzes()
{
  int problem;
  int retlist[2];
  if(analogRead(1))
  {
    retlist[0]=1;
    problem++;
  }
  else{retlist[0]=0;}
  if(tavm<krittav)
  {
    retlist[0]=1;
    problem++;
  }
}

int tavm()
{
  digitalWrite(trig,0);
  delayMicroseconds(5);
  digitalWrite(trig,1);
  delayMicroseconds(10);
  digitalWrite(trig,0);
  long ido;
  ido = pulseIn(echo,HIGH,10000);
  int tav = 0.0345*ido/2;
  if (tav==0){error(2);}
  return tav;
}

double fm(int Apin){ //just 12v 
  int f=analogRead(Apin)*11/204.6;
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
void ledSet(int all){

  if (all==0){
    digitalWrite(OK_LED_Z,1);
  }
  else if (all==1){
    digitalWrite(OK_LED_Z,0);
  }
  else if (all==3){
    if (millis()-ledTime>100){
    ledTime=millis();
    if (ledSet_vill==0){
    digitalWrite(OK_LED_Z,0);
    ledSet_vill=1;
    }else{
      digitalWrite(OK_LED_Z,1);
      ledSet_vill=0;
    }
    }
  }
}
void vesz(){
  // felszínre emelkedés

  //motorok kikapcsolása
  digitalWrite(r1,1);
  digitalWrite(r2,1);
  
}

