# ウルトラマンのカラータイマーとマリオカートの信号機  
今回自作した、ウルトラマンのカラータイマーとマリオカートの信号機を動作させるための説明を以下で行う。  
## 使用した道具  
- raspberry Pi 4 model B
- 5mm RGB LED
- 5mm LED 赤×3  
- 5mm LED 青×3
- 220Ω 抵抗器×9
- F-Mジャンパー線×12
- ブレッドボード
## 動作環境  
- OS:ubuntu 20.04.1 LTS  
## 配線方法  
[カラータイマー]:5mm RGB LEDのカソードをGNDピン、赤をGPIO25ピン、緑をGPIO24ピン、青をGPIO23ピンに接続する。  
[信号機]:5mm LED 赤×3をGPIO4・5・6ピン、青×3をGPIO14・15・16ピンにそれぞれ接続する。  
## 導入方法  
git clone https://github.com/Tqkqhqshi-Yuuki/robosys_kadai1.git  
## 実行方法  
以下のコマンドを上から順番に行う。  
`cd myled`  
`make`  
`sudo insmod myled.ko`  
`sudo chmod 666 /dev/myled0`  
- カラータイマー実行の場合  
`echo 1 > /dev/myled0`  
- 信号機実行の場合  
`echo 2 > /dev/myled0`←開始  
`echo 0 > /dev/myled0`←終了  
## 実行結果　　
- ウルトラマンのカラータイマー    
5秒間青色に点灯後、赤色に変化し、時間経過に連れて点滅の感覚が狭くなる。以下が実際に行った際の動画である。  
https://youtu.be/WNoGf5vTlzc  
- マリオカートの信号機   
赤色LEDが1秒おきに発効後、青色LEDが発行し、同時に赤色LEDが消灯する。以下は実際に行った際の動画である。  
https://youtu.be/u2dvZ_mvWVo  
## おまけ  
echo 3 > /dev/myled0を実行すると７色に発光し、echo 0 > /dev/myled0で終了する。  
https://youtu.be/f9SzlwmooI4  
