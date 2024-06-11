#!/usr/bin/env python3
# -*- coding: utf-8 -*-
#
#     ||          ____  _ __
#  +------+      / __ )(_) /_______________ _____  ___
#  | 0xBC |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
#  +------+    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
#   ||  ||    /_____/_/\__/\___/_/   \__,_/ /___/\___/
#
#  Copyright (C) 2021 Bitcraze AB
#
#  AI-deck demo
#
#  This program is free software; you can redistribute it and/or
#  modify it under the terms of the GNU General Public License
#  as published by the Free Software Foundation; either version 2
#  of the License, or (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#  You should have received a copy of the GNU General Public License along with
#  this program; if not, write to the Free Software Foundation, Inc., 51
#  Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
#
#  Demo for showing streamed JPEG images from the AI-deck example.
#
#  By default this demo connects to the IP of the AI-deck example when in
#  Access point mode.
#
#  The demo works by opening a socket to the AI-deck, downloads a stream of
#  JPEG images and looks for start/end-of-frame for the streamed JPEG images.
#  Once an image has been fully downloaded it's rendered in the UI.
#
#  Note that the demo firmware is continously streaming JPEG files so a single
#  JPEG image is taken from the stream using the JPEG start-of-frame (0xFF 0xD8)
#  and the end-of-frame (0xFF 0xD9).

import argparse
import time
import socket,os,struct, time
import numpy as np
import torch
from torch import nn
from torch.nn import Module
import torch.nn.functional as F
from PathFinder import PathFinder

def send_to_stm(socket,x1,y1,x2,y2,dist):
  size = 22 # 2 -> CPX_HEADER + 5 * sizeof(int)
  route = 0xd9 # HOST to STM
  function = 5 # CPX_F_APP
  packet = struct.pack('<HBBiiiii',size,route,function,x1,y1,x2,y2,dist)
  socket.sendall(packet)

def predict(model , image):
    model.eval()
    with torch.no_grad():
        image = torch.from_numpy(np.expand_dims(image,axis=1)).float()
        image = image.to(device)
        outputs = model(image)
    return outputs

def denormalize(coords):   
    return coords

device = torch.device('cuda' if torch.cuda.is_available() else 'cpu')
device

model = PathFinder.init()
model.load('./pathfinder3.pth') 

# Args for setting IP/port of AI-deck. Default settings are for when
# AI-deck is in AP mode.
parser = argparse.ArgumentParser(description='Connect to AI-deck JPEG streamer example')
parser.add_argument("-n",  default="192.168.4.1", metavar="ip", help="AI-deck IP")
parser.add_argument("-p", type=int, default='5000', metavar="port", help="AI-deck port")
args = parser.parse_args()

deck_port = args.p
deck_ip = args.n

print("Connecting to socket on {}:{}...".format(deck_ip, deck_port))
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect((deck_ip, deck_port))
print("Socket connected")

imgdata = None
data_buffer = bytearray()

def rx_bytes(size):
  data = bytearray()
  while len(data) < size:
    data.extend(client_socket.recv(size-len(data)))
  return data

import cv2

start = time.time()
count = 0
send_to_stm(client_socket,1,2,0,0,0)
while(1):
    
    # First get the info
    packetInfoRaw = rx_bytes(4)
    #print(packetInfoRaw)
    [length, routing, function] = struct.unpack('<HBB', packetInfoRaw)


    imgHeader = rx_bytes(length - 2)
    [magic, width, height, depth, format, size] = struct.unpack('<BHHBBI', imgHeader)

    if magic == 0xBC:
      # Now we start rx the image, this will be split up in packages of some size
      imgStream = bytearray()

      while len(imgStream) < size:
          packetInfoRaw = rx_bytes(4)
          [length, dst, src] = struct.unpack('<HBB', packetInfoRaw)
          chunk = rx_bytes(length - 2)
          imgStream.extend(chunk)
     
      count = count + 1
      meanTimePerImage = (time.time()-start) / count
      
      bayer_img = np.frombuffer(imgStream, dtype=np.uint8) 
      
      
         
      bayer_img.shape = (244, 324)
      bayer_img = cv2.cvtColor(bayer_img,cv2.COLOR_BayerBG2GRAY)
      bayer_img = cv2.flip(bayer_img,0)
      output = model.get_line_coords(model.preprocess(bayer_img.astype(np.float32)))
      send_to_stm(client_socket,int(output[0]),0,int(output[1]),int(output[2]),5)
      
      bayer_img = cv2.line(bayer_img,(int(output[0]),0),(int(output[1]),int(output[2])),(255,0,0),5)
      bayer_img = cv2.flip(bayer_img,0)
      cv2.imshow('Raw', bayer_img)
      cv2.waitKey(1)
