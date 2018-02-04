
# 초음파 센서


* [data sheet](http://www.micropik.com/PDF/HCSR04.pdf)

* 한쪽은 송신하는 부분 한쪽은 받는부분으로 구별되있다.

* trig 핀 -쏘는 부분 / echo 핀 - 받는 부분

* 트리거에 10마이크로초를 주면 초음파(8개) 발생한다. 다시돌아오면 에코에서 받는다.

* 최대 한텀은 50마이크로 세컨드이다.

```c
// 10 마이크로세컨드를 만들자!
include <stdio.h>
include <unistd.h>
include <pigpiod_if2.h>

define TRIG_PINNO 16
define ECHO_PINNO 6

void cb_func_echo(int pi, unsigned gpio, unsigned level, uint32_t tick);
//시간값저장(시작,끝)
uint32_t start_tick_, dist_tick_;

int main()
{
    float distance;
    int pi;

    if ((pi = pigpio_start(NULL, NULL)) < 0) return 1;
    // 초기화
    set_mode(pi, TRIG_PINNO, PI_OUTPUT);
    set_mode(pi, ECHO_PINNO, PI_INPUT);
    callback(pi, ECHO_PINNO, EITHER_EDGE, cb_func_echo);
    gpio_write(pi, TRIG_PINNO, PI_OFF);
    time_sleep(1);     // delay 1 second

    printf("Raspberry Pi HC-SR04 UltraSonic sensor\n" );

    while(1){
        start_tick_ = dist_tick_ = 0;
        gpio_trigger(pi, TRIG_PINNO, 10, PI_HIGH);  // 10 = 펄스길이 = 마이크로세컨드
        time_sleep(0.05);

        if(dist_tick_ && start_tick_){
            //distance = (float)(dist_tick_) / 58.8235;
            distance = dist_tick_ / 1000000. * 340 / 2 * 100; //m -> cm로
            if(distance < 2 || distance > 400)
                printf("range error\n");
            else
                printf("interval : %6dus, Distance : %6.1f cm\n", dist_tick_, distance);
        }
        else
            printf("sense error\n");

        time_sleep(0.1);
    }
    pigpio_stop(pi);

    return 0;
}

void cb_func_echo(int pi, unsigned gpio, unsigned level, uint32_t tick)
{
    if(level == PI_HIGH)
        start_tick_ = tick;
    else if(level == PI_LOW)
        dist_tick_ = tick - start_tick_;  //갔다가 돌아오는 시간
}
```
# 링크

* [깃허브 코드](https://github.com/rim0621/RobotSW/tree/master/DistanceSensor)

* [깃허브](https://github.com/rim0621)

* [다른 내용보기](https://rim0621.tistory.com)

# Mission Result 클릭

> 5cm 이하면 LED ON

> 5cm 초과면 LED OFF

[![Video Label](http://img.youtube.com/vi/UOParMlHYMs/0.jpg)](https://youtu.be/UOParMlHYMs)
