# GPIO

* 입력, 출력 동시에 불가능 하다.(2가지 모드중 한가지를 선택)

* 핀은 한가지 이상의 기능을 하기도 한다.(데이터 시트 참조)

* [참고자료](https://pinout.xyz/)

* 제어

  1. 직접 레지스터에 접근 하여 사용하는 방법이 있다.

  2. 리눅스에서 제공하는 sysfs를 사용하는 방법이 있다.

  3. 라이브러리를 활용해서 제어할수 있다.

* 레지스터를 다루기 위해 먼저 출력/입력 모드를 설정한다.

## 1. 직접 레지스터에 접근하여

* [데이터 시트](https://www.raspberrypi.org/documentation/hardware/raspberrypi/bcm2835/BCM2835-ARM-Peripherals.pdf)

* 가상주소 - 물리주소 - 버스주소가 있다.

* 리눅스의 응용 프로그램은 가상주소 접근만 가능하다.

* /dev/mem파일 을 사용하여 물리주소를 사용한다.(루트권한)

* 0핀~9 = 레지스터 0 , 10~19 = 레지스터 1 ..... 레지스터 6까지 있다.(데이터시트 참조)

```c
<stdio.h> <stdlib.h> <fcntl.h>
<unistd.h> <stdint.h> <sys/mman.h> 선언

define MMAP_SIZE 4096
define GPIO_PHY_BASE_ADDRESS 0x3F200000 //물리주소 시작

INPUT 0b000
OUTPUT 0b001
HIGH 1
LOW 0
typedef struct TAG_GPIO_REGS{
  uint32_t GPFSEL[6];   //핀 선택
  uint32_t reserved1;
  uint32_t GPSET[2];  // 핀 아웃풋 셋 레지스터 1=set / 0 = no effect 레지스터[0]의 범위와[1]범위 데이터 시트에서 확인!!!
  uint32_t reserved2;
  uint32_t GPCLR[2];  //핀 아웃풋 클리어 레지스터  1=clear GPIO / 0=no effect
} GPIO_REGS, *pGPIO_REGS;

pGPIO_REGS pGpio;
int fd;
int main()
{
  int i;
  int gpio = 13;
  open_devmem();
  gpio_pinMode(gpio,OUTPUT);
  printf("gpio:%d\n",gpio);

  for(i=0;i<10;i++){
    sleep(1); gpio_digitalWrite(gpio, HIGH); //on
    sleep(1); gpio_digitalWrite(gpio, Low); //off
  }
  close_devmem();
  return 0;
}

void open_devmem()
{
  fd=open("/dev/mem", O_RDWR | O_SYNC);   //read and write
  if(fd<0)
  {
    printf("error");
    exit(-1);
  }
  void * mmaped = mmap(NULL,MMAP_SIZE,PROT_READ | PORT_WRITE, MAP_SHARED,fd,GPIO_PHY_BASE_ADDRESS);

  if(mmaped==MAP_FAILED){
    printf("mmap error");
    perror("");
    exit(-1);
  }
  pGpio = mmaped; //레지스터로 연결!!!
}
void gpio_pinMode(int pin,int mode){
  int registerIdx = pin / 10; //13이므로 1 로 되므로 1번 레지스터(10~19)를 사용한다.
  int bitOffset=(pin % 10) * 3;  // 9

  uint32_t oldGpfsel = pGpio->GPFSEL[registerIdx];
  uint32_t mask = 0b111 << bitOffset;

  pGpio->GPFSL[registerIdx]=(oldGpfsel & ~mask) | ((mode << bitOffset) & mask); //초기화와 모드를 or연산 GPIO 13번 use 하기위해 9~11번을 (001)으로 바꾼것이다.
}
void gpio_digitalWrite(int pin, int value)
{
  if(value)
    pGpio->GPSET[pin/32]=(1<<(pin%32)); //1 키는 것이 들어오면  
  else
    pGpio->GPCLR[pin/32]=(1<<(pin%32)); // 0 끄는 것이들어오면
}
void close_devmem()
{
  close(fd);
}
```
## 2. sysfs를 사용하여

* 리눅스 커널이 제공하는 가상 파일 시스템

* 쉘 스크립트를 사용한다. (사용안할 것 같아서 여기서는 패스)

## 3. 라이브러리를 사용하여 (pigpio사용)

* lpthread : 링커에서 링크할 때 처리한다.

* pthread : 컴파일 단계에서 처리 한다.+링커에서

* pigpoio 대몬 실행 : sudo pigpiod / sudo killall pigpiod (소켓, 파이프인터페이스 제공) - 씨,파이썬 또는 다른 언어를 할 때 데몬에다 요청해야...(외부에서 가능?)- #### 해보기!!!
```
데몬 - (통신)- 씨 I/F
            - 파이썬 모듈 I/F
로 할 수 있고

pigpio i/f를 사용 할 수도 있다.(데몬 없이 사용할 때)

```
##### gpio에서 입력 받기

* level = gpio_read(pi, PIN);

#### 예제 코드

```c
/*
        스위치 1 led on
        스위치 2 led off

*/
include<stdio.h>
include<pigpiod_if2.h>
define PINNO1 23
define PINNO2 16
define LED 13

int count;
void cb_falling_on(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
        gpio_write(pi,LED,1);
        printf("on\n");
}
void cb_falling_off(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
         gpio_write(pi,LED,0);
         printf("off\n");
}
// bouncing이 발생하여 스위치를 누를 때 여러번  눌리는 현상의 경우
// 올라올때 tick - 내려갈때 tick 가 10000보다(thredhold 값) 클때만 실행하게..
int main()
{
    int pi;
    if(pi=pigpio_start(NULL,NULL)<0)
    {
        fprintf(stderr, "%s\n",pigpio_error(pi));
        return 1;
    }
    set_mode(pi, PINNO1, PI_INPUT);
    set_mode(pi, PINNO2, PI_INPUT);
    set_mode(pi, LED, PI_OUTPUT);
    set_pull_up_down(pi,PINNO1, PI_PUD_UP);
    set_pull_up_down(pi,PINNO2, PI_PUD_UP);
    callback(pi,PINNO1,FALLING_EDGE, cb_falling_on);
    callback(pi,PINNO2,FALLING_EDGE, cb_falling_off);

    getchar();

    pigpio_stop(pi);
}

```
#### 결과 (그림클릭)

[![Video Label](https://img.youtube.com/vi/2C8V1nFGtlQ/0.jpg)](https://youtu.be/2C8V1nFGtlQ)

#### 예제 코드

```c
/*
스위치 버튼 여러번 누르고 enter키 led가 누른횟수 블린킹
*/

include<stdio.h>
include<pigpiod_if2.h>
define PINNO 23
define LED 13

int count;
uint32_t falling_tick, rising_tick;
void cb_falling_func(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
    falling_tick=tick;
}
void cb_rising_func(int pi, unsigned user_gpio, unsigned level, uint32_t tick)
{
if(tick-falling_tick>10000)
    count++;
}
int main()
{
int pi;
if(pi=pigpio_start(NULL,NULL)<0)
{
    fprintf(stderr, "%s\n",pigpio_error(pi));
    return 1;
}
set_mode(pi, PINNO, PI_INPUT);
set_mode(pi, LED, PI_OUTPUT);
set_pull_up_down(pi,PINNO, PI_PUD_UP); //풀 다운-> 누르면 1 아니면 0 // 풀 업-> 누르면 0 안누르면 1
callback(pi,PINNO,FALLING_EDGE, cb_falling_func);
callback(pi, PINNO, RISING_EDGE, cb_rising_func);

getchar();
printf("Blink : %d\n",count);
time_sleep(1);
for(int i=0;i<count;i++)
{
    gpio_write(pi,LED,1);
    time_sleep(0.5);
    gpio_write(pi,LED,0);
    time_sleep(0.5);
    printf("%d\n",i+1);
}

pigpio_stop(pi);
}

```
#### 결과 (그림클릭)

[![Video Label](https://img.youtube.com/vi/rb6PiczLL60/0.jpg)](https://youtu.be/rb6PiczLL60)
