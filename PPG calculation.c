#include <MsTimer2.h>
int  nowValue, preValue, s, Value, maxValue;
int An, Tn, average, peakGap, interrupt, Pt;
int peak[2][2];
//1차 배열 : 크기 값
//2차 배열 : 시간 값
unsigned long peak1;
boolean BC,Tc = true;
//라이브러리 및 변수 지정

void setup() {
  Serial.begin(9600);
  MsTimer2::set(1, flash);
  MsTimer2::start();
}
//타임 인터럽트 설정, 샘플링 주기 0.001초

void flash() {
  Tc = !Tc;
  interrupt = 1;
  Pt ++;
} 
//플래쉬 함수 정의
//1ms 간격으로 Tc를 토글함.

void loop() {
  if ( interrupt == 1) {
    interrupt = 0;

    if (Tc == true) {
      preValue = analogRead(A0);
    }
    if (Tc == false ) {
      nowValue = analogRead(A0);
      Value = preValue - nowValue;
      //아날로그 값을 받아 변수에 저장한 후 둘의 차를 구함
    }

    if (Value < -5) { //파형이 증가 할 때
      s = 1;
    }
    if (Value > 0 && s == 1) { // Peak 검출
      // 파형이 증가하고, 감소 할 때 = peak
        s = 0;
        maxValue = analogRead(A0);
        peak[An][0] = maxValue; // peak 값 저장
        An ++;
        if (An == 2) {
            An = 0;
        }
    } else {
    maxValue = 0;
    }

    average = (peak[0][0] + peak[1][0]) / 2;
    // 연속한 2개의 peak 값의 평균

    if (maxValue > average) {
        peak1 = Pt; //1ms 단위의 시간
        peak[Tn][1] = peak1;
        // 평균보다 큰 값만 peak로 인식 후 시간 저장
        Tn ++;
        if (Tn == 2) {
            Tn = 0;
        }
    }
    if (peak[0][1] > peak[1][1]) {
      peakGap = peak[0][1] - peak[1][1];
    } else {
      peakGap = peak[1][1] - peak[0][1]; //주기 계산
    }
  }
  float bpm = (1 / (peakGap / 1000.0)) * 60; //심박수 계산
  Serial.print("심박수:");
  Serial.print(bpm);
  Serial.println("bpm");
}
