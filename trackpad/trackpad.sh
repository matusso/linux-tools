#!/bin/bash
list=$(xinput --list | grep -i 'mouse')

if [ ${#list} -eq 0 ]; then
	state=$(synclient -l | awk '/TouchpadOff/ {print $3}')
	if [ "$state" -eq 0 ]; then
		synclient TouchpadOff=1
		notify-send -t 1500 "touchpad disabled"
	else
		synclient TouchpadOff=0
		notify-send -t 1500 "touchpad enabled" 
	fi
else
	notify-send -t 1500 "touchpad disabled"
fi
