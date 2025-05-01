#define p1 0
#define p2 1
#define k1 2
#define k2 3
#define k3 4
#define k4 5
#define k5 6
#define b1 7
#define b2 8
#define b3 9
#define m1 0
#define m2 1

uint8_t dat[14];

void setup() {
Serial.begin(115200);


pinMode(k1,INPUT);
pinMode(k2,INPUT);
pinMode(k3,INPUT);
pinMode(k4,INPUT);
pinMode(k5,INPUT);
pinMode(b1,INPUT);
pinMode(b2,INPUT);
pinMode(b3,INPUT);
pinMode(A0,INPUT);
pinMode(A1,INPUT);

}

void loop() {
  
int a = map(analogRead(m2),1,1023,400,-400);
int b = map(analogRead(m1),1,1023,-400,400);//jobb
int c = digitalRead(k1);
int d = digitalRead(k3);
int e = digitalRead(k5);
int f = digitalRead(b1);
int g = digitalRead(b2);
int h = digitalRead(b3);
int i = 0;//analogRead(p1);
int j = analogRead(p2);
int k;
int l;
int m=0;int n=0;int o=0;int p=0;int q=0;int r=0;int s=0;
/*
 dat[0] = map(analogRead(m2),1,1023,-400,400);
 dat[1] = map(analogRead(m1),1,1023,-400,400);//jobb
 dat[2] = digitalRead(k1);
 dat[3] = digitalRead(k3);
 dat[4] = digitalRead(k5);
 dat[5] = digitalRead(b1);
 dat[6] = digitalRead(b2);
 dat[7] = digitalRead(b3);
 dat[8] = 0;//analogRead(p1);
 dat[9] = analogRead(p2);

senderArray(dat);
*/
sender(a,b,c,d,e,f,g,h,i,j,k,l,m,n,o,p,q,r,s);
delay(20);
}

void senderArray(uint8_t arr[19]){
  Serial.write(arr, 19);
}


void sender(int a1,int b2_,int c3,int d4,int e5,int f6, int g7, int h8,
int i9,int j10,int k11,int l12,int m13,int n14,int o15,int p16,int q17,int r18,int s19)
{
String rpidata = String(a1)+" "+String(b2_)+" "+String(c3)+" "
+String(d4)+" "+String(e5)+" "+String(f6)+" "+String(g7)+" "
+String(h8)+" "+String(i9)+" "+String(j10)+" "+String(k11)+" "
+String(l12)+" "+String(m13)+" "+String(n14)+" "+String(o15)+" "
+String(p16)+" "+String(q17)+" "+String(r18)+" "+String(s19);
  Serial.println(rpidata);
}




