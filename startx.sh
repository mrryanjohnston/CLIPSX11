#!/bin/sh
export DISPLAY=:17
Xorg :17 vt1 &
sleep 2
xhost +local:$(whoami)
