#!/bin/bash

cd "$(dirname "$0")"
make
cfloader flash build/cf2.bin stm32-fw -w radio://0/80/2M/E7E7E7E715
