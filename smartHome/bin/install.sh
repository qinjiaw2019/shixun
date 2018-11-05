#!/bin/sh

cp ../ext/mplayer /bin
cp ../ext/jpeg_show /bin
cp ../ext/libjpeg.so.9 /lib

chmod 777 /bin/mplayer
chmod 777 /bin/jpeg_show
chmod 777 /lib/libjpeg.so.9

insmod ../ext/driver/led.ko
insmod ../ext/driver/beep.ko
