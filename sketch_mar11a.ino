const int pinBuz = 3; //Buzzer Pin
const int pinSwi = 2; 
const int intA = 2500;   
const int intB = 5000;   
volatile int ggyy = 1;  
int ledPin = 13;
int led8 = 8;  
int botao;
const int myTOP = 24;  
volatile unsigned long ms;
String income;
String setElement;
int Set = -1;
int aSet = -1;
ISR(TIMER1_COMPA_vect)
{
   static unsigned int aaa = 0;
   static unsigned int bbb = 0;
   ms = millis( );
   ++aaa; bbb++;
   if(aaa == intA){
      aaa=0; myJobOne( );
   }
   if(bbb == intB){
      bbb=0; myJobTwo( );
   }
}
void setup( ) {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(led8, OUTPUT);  
  pinMode(pinBuz,OUTPUT); 
  pinMode(pinSwi,INPUT);  
  digitalWrite(led8, 1); 
  digitalWrite(ledPin, LOW);
  delay(1);
  setMyTimerOne( ); 

}
unsigned long doP = 0; 
void loop() {
    if (Serial.available() > 0) {
    int index = 0;
    income = Serial.readString();
    index = income.indexOf(" ");
    setElement = income.substring(0, index);
    income = income.substring(index + 1);
    index = income.indexOf(" ");
    Set = income.substring(0, index).toInt();
    if (setElement.equals("alarm")) {
      aSet == Set;
    }
  }
  if(doP) {
     doP = 0; 
  int secs = ms/500;
  Serial.print("Time is : ");
  Serial.println(secs);
  Serial.println(botao);
  Serial.println("Alarm Time is : ");
  Serial.println(Set);
  botao = digitalRead(pinSwi); 
      if (secs==aSet) 
      {
      digitalWrite(pinBuz,0); 
      }else if (botao=1)
      { 
      digitalWrite(pinBuz,1);
      } 
      delay(1000); 

  }
}

void myJobOne( ) {
  digitalWrite(ledPin, ggyy);  
  ggyy = 1 - ggyy; 
  doP = 1;
}
void myJobTwo( ) {
  digitalWrite(led8, ! digitalRead(led8));  
}
void setMyTimerOne( ){
  cli();  
  TCCR1A = 0;
  TCCR1B = (1<<WGM12);  
  TCCR1B |= (1<<CS10) | (1<<CS11);  
  OCR1A = myTOP;  
  TCNT1=0;  
  TIMSK1 |= (1 << OCIE1A);
  sei(); 
}
