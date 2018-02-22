# 자율주행자동차

## 1. 개요

> 자율주행자동차 키트와 센서를 사용하여 아래와 같은 트랙을 빠져나오는 프로젝트


## 2. 개발 과정

> 자동차 키트를 사용하고 초음파 센서 3개를 사용했다.

### 하드웨어 조립

* 조립

  <img src="https://github.com/rim0621/RobotSW/blob/master/autonomousVehicle/img/making.jpg?raw=true" width="300" height="300"></img>

* 측면

  <img src="https://raw.githubusercontent.com/rim0621/RobotSW/master/autonomousVehicle/img/left.jpg" width="300" height="300"></img>

* 앞

  <img src="https://raw.githubusercontent.com/rim0621/RobotSW/master/autonomousVehicle/img/front.jpg" width="300" height="300"></img>

> 처음에는 앞과 왼쪽에 초음파 센서를 사용하여 left hand알고리즘을 사용하려고 하였으나 오른쪽에 부딪힐 경우 예외처리로 빠져나오기 위해서 오른쪽도 센서를 달아 3개를 사용하였다.

### PID제어

```c
float ki,kp,kd;
int speed=0,pre_speed=0,cnt=0;
float err=0;
float i=0;
float d=0,p=0;
float lsterr=0;
float pivot;

p=kp*err;
i=i+ki*err;
d=(err-lsterr) * kd;
```

<img src="https://github.com/rim0621/RobotSW/blob/master/autonomousVehicle/img/PID1.png?raw=true" width="300" height="300"></img>

> PID제어 데이터를 뽑은 결과 다음과 같이 나왔다.

> 초흠파거리센서가 0.001초 마다 가져와서 제대로된 제어가 안되는 거라고 판단해서 0.1초마다 가져오기위해 메인에 슬립을 주었다.

<img src="https://github.com/rim0621/RobotSW/blob/master/autonomousVehicle/img/PID2.png?raw=true" width="300" height="300"></img>

> 그 결과 제어가 좀더 가능해 졌다.

> 처음에는 제어를 잘했지만 뒤쪽에는 직선 구간이 부딪히는 상황이 생겨서 값이 뛰어 제어가 잘 안되는 것을 볼 수 있다.

> 게인값 -> kp=4 ki=0.0002 kd=25

### 코드

> 코드 부분은 모터 동작(직진,후진,왼쪽,오른쪽턴)을 함수로 구현하였다.

> 모터의 하드웨어적 문제가 발생하여(왼 바퀴가 더 센데 초기값을 주면 굴러가지가 않음) 순간적으로 255의 값을 PWM을 주어서 왼쪽 바퀴를 굴길 수 있게 하였다.

> 쓰레드를 3개 사용하여 각각의 초음파센서의 값을 받아오도록 하였다.

> 메인에는 발생할 상황을 조건문으로 나누어서 각각의 상황에 맞에 구현하였다.

> 초음파 센서가 받아오는 값이 너무 빨라서 제어를 좀더 정확하게 하기위해서 0.1초의 딜레이를 주었다.

* [코드 링크](https://github.com/rim0621/RobotSW/blob/master/autonomousVehicle/Last_project.c)

* [깃허브](https://github.com/rim0621)

* [다른 내용보기](https://rim0621.tistory.com)

### 시연 동영상 (클릭)

> 제어 처음 부분

[![Video Label](http://img.youtube.com/vi/N2R50nhmHQM/0.jpg)](https://youtu.be/N2R50nhmHQM)

## 3. 결과

### 최종 시연 동영상 (클릭)

[![Video Label](http://img.youtube.com/vi/Ha9_MP4FB44/0.jpg)](https://youtu.be/Ha9_MP4FB44)

## 4. 사용기술

* C

* 라즈베리파이 & 초음파 센서

* pigpiod 라이브러리

* PID 제어
