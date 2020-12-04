# #1.カラータイマー  
今回自作した、ウルトラマンのカラータイマーを動作させるための説明を以下で行う。  
# 使用した道具  
- raspberry Pi 4 model B
- 5mm RGB LED
- 220Ω 抵抗器×3
- F-Mジャンパー線×5
- ブレッドボード
# 動作環境  
- OS:ubuntu 20.04.1 LTS  
# 配線方法  
5mm RGB LEDのカソードをGNDピン、赤をGPIO25ピン、緑をGPIO24ピン、青をGPIO23ピンに接続する。  
# 導入方法  
git clone https://github.com/Tqkqhqshi-Yuuki/robosys_kadai1.git  
# 実行方法  
以下のコマンドを上から順番に行う。  
cd myled  
make  
sudo insmod myled.ko  
sudo chmod 666 /dev/myled0  
echo 1 > /dev/myled0  
# 実行結果　　
5秒間青色に点灯後、赤色に変化し、時間経過に連れて点滅の感覚が狭くなる。以下が実際に行った際の動画である。  
https://youtu.be/WNoGf5vTlzc  
# おまけ  
echo 3 > /dev/myled0を実行すると８色に発光し、echo 0 > /dev/myled0で終了する。  
https://youtu.be/f9SzlwmooI4  
  
# #2.マリオカートのスタート信号機  
次に自作した、マリオカートのレース開始時に頭上付近にある信号機を動作させるための説明を以下で行う。  
# 使用した道具  
- raspberry Pi 4 model B  
- 5mm LED 赤×3  
- 5mm LED 青×3
- 220Ω 抵抗器×6  
- F-Mジャンパー線×7  
# 動作方法  
#1と同様のため省略  
# 配線方法  
5mm LED 赤×3をGPIO4・5・6ピン、青×3をGPIO14・15・16ピンにそれぞれ接続する。  
# 実行方法  
#1と同様のため省略  
# 実行方法  
- 開始echo 2 > /dev/myled0  
- 終了echo 0 > /dev/myled0
# 実行結果  
赤色LEDが1秒おきに発効後、青色LEDが発行し、同時に赤色LEDが消灯する。以下は実際に行った際の動画である。  
https://youtu.be/u2dvZ_mvWVo  
  
