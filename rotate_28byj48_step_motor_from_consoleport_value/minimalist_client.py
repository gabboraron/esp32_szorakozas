#! /usr/bin/env python3

import serial

MAX_BUFF_LEN = 255
#                    /dev/ttyUSB0
port = serial.Serial("COM3", 115200, timeout=1)

def read_ser(num_char = 1):
	string = port.read(num_char)
	return string.decode()

def write_ser(cmd):
	cmd = cmd + '\n'
	port.write(cmd.encode())

while(1):
	string = read_ser(MAX_BUFF_LEN)
	if(len(string)):
		print(string)

	cmd = input()
	if(cmd):
		write_ser(cmd)
