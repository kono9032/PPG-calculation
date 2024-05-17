#include <MsTimer2.h> 

int emg= 0;
int Count=1;
void setup() {
pinMode(13,OUTPUT);
Serial.begin(19200);
MsTimer2::set(1,sampling);
MsTimer2::start();
}

void sampling(){
    Serial.println(emg);

    if(Count<70) digitalWrite(13, HIGH);
    else if(Count>=70 && Count<200) digitalWrite(13, LOW);
    else if(Count>=200 && Count<220) digitalWrite(13, HIGH);
    else if(Count>=220 && Count<768) digitalWrite(13, LOW);

    if(Count==768) Count=1;
    else Count++;
}

void loop() {}