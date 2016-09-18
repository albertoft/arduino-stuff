# Bluetooth

## Info
### Raspberry
Raspberry pi 2. Raspbian.

```
$ uname -a
Linux raspberrypi 4.4.11-v7+ #888 SMP Mon May 23 20:10:33 BST 2016 armv7l GNU/Linux
```

### Bluetooth dongle
CSL Bluetooth 4.0 Stick Pico BTS23997

## Installation
```
$ sudo apt-get update
$ sudo apt-get install bluetooth blueman
```

## Configuration
### Scan, Pair & Trust device
Can be done using Raspbian graphical interface or `bluetoothctl`.


```
$ bluetoothctl
[bluetooth]# power on
[bluetooth]# discoverable on
[bluetooth]# agent on
[bluetooth]# default-agent
[bluetooth]# paireable on 
[bluetooth]# scan on 
[bluetooth]# pair XX:XX:XX:XX:XX:XX 
[bluetooth]# trust XX:XX:XX:XX:XX:XX 
[bluetooth]# quit
```

### Bind rfcom device
Serial input / output to Bluetooth.

```
$ sudo rfcomm bind /dev/rfcomm1 98:D3:33:80:82:00
$ rfcomm
rfcomm1: 98:D3:33:80:82:00 channel 1 clean 
$ echo "test" > /dev/rfcomm1
``` 
