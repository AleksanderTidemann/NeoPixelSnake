# NeoPixel Snake


Play snake on your LED's. 

<p align="left">
 <img src="img/snake.gif" width=440>
</p>

* Arduino Uno (or any arduino)

  * Adafruit NeoPixel library
  * CircularBuffer library

* [Adafruit NeoPixel LED matrix](https://www.adafruit.com/product/1487) (8x8 or bigger)

  * The Adafruit matricies often need about 5v2A power to work properly, so they cant be powered by the Arduino. I bought a [mini-USB breakout board](https://www.sparkfun.com/products/9966), 100mf25v capasitor, cable and a USB-to-wall connector. this works just fine, and I can easily scale up by adding more LED boards to this rig.
    * Check out [this video] for more info on power(https://www.youtube.com/watch?v=j_VvLHZEPZ4)

FInally, I just used 4 buttons (digital pins) as controllers. Not very user-friendly, but it works.

<p align="left">
 <img src="img/button.png" width=440>
</p>
