# PWM



* PWM은 pulse width modulation의 준말로 펄스의 폭을 컨트롤 하는 주기 제어 방법이다.

* 펄스를 생성

```c
(반복-이렇게 펄스를 생성 할 수 있지만...)
int pin=13;
gpio_mode(pin,아우풋);
gpio_write(pin,1);  // on
sleep();
gpio_write(pin,0);  //off
sleep();
```

* 한 주기(on=pulse width)-최대를 255이다.

* pigpiod_if2.h 헤더에서 함수를 제공해 준다.

```c
set_PWM_range(pi,PIN,range);  //범위 설정
get_PWM_range(pi,PIN);  //범위 가져오기
set_PWM_dutycycle(pi,PIN,i(0~range)); //불 키기, i값을 변화시켜 세기 조절

```
* 12,13 GPIO에서만 PWM을 제어할수 있지만 pigpiod에서 모든 gpio를 사용할수있도록 도와준다.

* [깃허브 코드보기](https://github.com/rim0621)

* [다른 내용보기](https://rim0621.tistory.com)

# led_mission.c 결과

[![Video Label](http://img.youtube.com/vi/N66TGzjkBcg/0.jpg)](https://youtu.be/N66TGzjkBcg)


# led_mission2.c 결과

[![Video Label](http://img.youtube.com/vi/anm_jxl03MM/0.jpg)](https://youtu.be/anm_jxl03MM)
