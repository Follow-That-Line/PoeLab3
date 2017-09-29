int cmd_id;

void setup()

{

Serial.begin(9600);

pinMode(4,OUTPUT);
digitalWrite(4,HIGH);


}

void loop(){
if(Serial.available() >= 0) {
    cmd_id = Serial.read();
  }
  else{
    cmd_id = 0;
  }
switch(cmd_id){
  case 1:
    
    delayMicroseconds(500);
    
    int a=analogRead(A0);
    
    Serial.println(a); 

   break;
}
 
}
