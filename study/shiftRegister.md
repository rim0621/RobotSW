# 74HC595 shift Register

* 제한된 GPIO핀을 확장하여 더욱 많은 제어를 할수 있다. 

* 직렬,병렬로 변환하여 gpio를 확장 시켜준다.

* 많은 종류가 있지만 하나만 해도 다른 시프트레지스터도 어렵지 않게할 수 있을것이다.

* OE : output enable -칩의 온/오프를 담당한다.

* Ds : serial input data - 실제로 데이터가 들어가는 곳 이다.

* ST :  0에서 1을 해야 라이징이 발생하여 출력하는 저장소로 보내 출력한다.

* SH :  0에서 1 을해야 라이징이 발생하여 쉬프트한다.

* MR : 클리어 한다.(1을해야 쓸수 있다.)

* 9 번은 아웃풋으로 쉬프트레지스터를 추가 할때 다음 쉬프트레지스터의 인풋으로 들어간다.

![이미지](http://www.hardcopyworld.com/ngine/aduino/wp-content/uploads/sites/3/2016/05/74HC595-pinout-300x246.jpg)
