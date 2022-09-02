#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Sep  2 10:44:43 2022

@author: tuan
"""
import serial
import time
import array

HEADER = b'\xFE'
NUM = b'\x04'
FOOTER = b'\xAA'
HEADER_POS = 0
NUM_POS = 1
msg_pos = 0

buffer = array.array('B',[0, 0, 0, 0, 0, 0])
buff_pos = 0

ser_port = '/dev/ttyUSB0'
ser_baud = 19200

x_i = 0
y_i = 0

filter_x_i = 0
filter_y_i = 0

with serial.Serial(ser_port, ser_baud, timeout = 5) as ser:
    ser.reset_input_buffer()
    while 1:
        
        cur_byte = ser.read()
        if msg_pos == HEADER_POS and cur_byte == HEADER:
            msg_pos += 1;
            
        if msg_pos == NUM_POS and cur_byte == NUM:
            msg_pos += 0;
            x_mot_byte = ser.read(2)
            y_mot_byte = ser.read(2)

            x_mot = int.from_bytes(x_mot_byte,'little', signed = True)
            y_mot = int.from_bytes(y_mot_byte,'little', signed = True)
            
            x_i += x_mot;
            y_i += y_mot;
            
            filter_x_i += (x_i - filter_x_i) * 0.2
            filter_y_i += (y_i - filter_y_i) * 0.2
            
            chk = ser.read()
            sur_qual = int.from_bytes(ser.read(), 'little')
            print (filter_x_i)