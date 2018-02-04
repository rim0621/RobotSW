# ADC(MCP3208)

* [datasheet](http://ww1.microchip.com/downloads/en/DeviceDoc/21298D.pdf)

* 2.7~5.5V 가능하지만 클 수록 샘플링 속도가 빠르다.

* ch0~7 : 아날로글 신호 넣어주는곳이다.

* SPI : 통신규격 - 라즈베리파이 (라즈베리파이에서는 2개의 핀을 제공)

> raspi-config 에서 SPI on

> 확인 : lsmmod | grep spi

> 확인 : ls /dev/spi* -l

* 스티트 1, 싱글디프 1 , 채널 설정

```c
#include <stdio.h>
#include <stdlib.h>
#include <pigpiod_if2.h>

#define BAUD_RATE	1000000
#define LOOP		1000

int main(int argc, char* argv[])
{
    int pi;
    int spi;
    uint16_t value;
    uint64_t sum = 0;
    uint16_t avg;
    int channel = 0;
    char snd_buf[3];
    char rcv_buf[LOOP][3];
    uint32_t start_tick, diff_tick;

    if(argc == 2) channel = atoi(argv[1]);

    if((pi = pigpio_start(NULL, NULL)) < 0) {
        fprintf(stderr, "pigpio_start error\n");
        return 1;
    }
    //spi 2개중 0 번 연다.
    if((spi = spi_open(pi, 0, BAUD_RATE, 0)) < 0) {
        fprintf(stderr, "spi_open error\n");
        return 2;
    }

    while(1){
        avg = sum = 0;
        snd_buf[0] = 0x18 | channel; //1-스타트, 8-싱글디프모드

        start_tick = get_current_tick(pi);

        for(int i = 0 ; i < LOOP ; i++)
            spi_xfer(pi, spi, snd_buf, rcv_buf[i], 3); //보냄과 받늠을 동시에하는 함수

        diff_tick = get_current_tick(pi) - start_tick;  //얼마나 걸리는시 시간계산

        for(int i = 0 ; i < LOOP ; i++){
            value = ((rcv_buf[i][1] & 0x3f) << 8) | (rcv_buf[i][2] & 0xff); //데이터 가져오기 (데이터가 12비트니깐 2바이트 사용하기 위해 <<8 )
            value = value >> 2;
            sum += value;
        }
        avg = sum / LOOP;

        printf("channel-%d : %4d %.1fv", channel, avg, 3.3*avg/4095);
        printf("\t%lld sps\n", 1000000LL * LOOP / diff_tick);
    }
	spi_close(pi, spi);
	pigpio_stop(pi);
	return 0;
}
```

# 링크

* [깃허브 코드](https://github.com/rim0621/RobotSW/tree/master/ADC)

* [깃허브](https://github.com/rim0621)

* [다른 내용보기](https://rim0621.tistory.com)


# 가변저항 값을 이용한 LED Dimming Mission

> 가변 저항 0~4095 점점 불빛이 강하게 하기

* 사진 클릭

[![Video Label](http://img.youtube.com/vi/e_qgJq53qBs/0.jpg)](https://youtu.be/e_qgJq53qBs)

> 컴파일 : gcc -Wall -W -pthread -lrt -lpigpiod_if2 -Wno-unused-parameter ADC_mcp.c -o outputfile
