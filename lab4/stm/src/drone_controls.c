/**
 * ,---------,       ____  _ __
 * |  ,-^-,  |      / __ )(_) /_______________ _____  ___
 * | (  O  ) |     / __  / / __/ ___/ ___/ __ `/_  / / _ \
 * | / ,--´  |    / /_/ / / /_/ /__/ /  / /_/ / / /_/  __/
 *    +------`   /_____/_/\__/\___/_/   \__,_/ /___/\___/
 *
 * Crazyflie control firmware
 *
 * Copyright (C) 2023 Bitcraze AB
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, in version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 *
 * App layer application that communicates with the GAP8 on an AI deck.
 */


#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#include "app.h"

#include "cpx.h"
#include "cpx_internal_router.h"

#include "FreeRTOS.h"
#include "task.h"

#define DEBUG_MODULE "APP"
#include "debug.h"
#include "commander.h"

#define SPEED 0.05
#define ANGLE_90 1.57
#define MAX_ANGLE 0.26 
#define MAX_SIDE 50
#define MIDDLE 127 
#define TIMOUT 2000

static void cpxPacketCallback(const CPXPacket_t* cpxRx);

static void idle(setpoint_t *setpoint);

typedef struct {
  unsigned x1;
  unsigned y1;
  unsigned x2;
  unsigned y2;
  unsigned dist;
} data_t;

static signed timout = 0;
static setpoint_t s ={};

static void cpxPacketCallback(const CPXPacket_t* cpxRx) {
  data_t* rx_commands;
  rx_commands = (data_t*)&cpxRx->data[0];
  timout = TIMOUT; 

  static double angle = 0.;
  if(angle == 0.){
    angle = atan2((double)rx_commands->y2-rx_commands->y1,(double)rx_commands->x2-rx_commands->x1);
  }else{
    angle = atan2((double)rx_commands->y2-rx_commands->y1,(double)rx_commands->x2-rx_commands->x1) * 0.1 + 0.9 * angle;
  }

  static int dist_from_center = -128;
  if(dist_from_center == -128){
    dist_from_center = rx_commands->x1 -MIDDLE; 
  }else{
    dist_from_center = (rx_commands->x1 -MIDDLE) * 0.1 + 0.9 * dist_from_center;
  }

  if(dist_from_center < (MIDDLE - MAX_SIDE)){
    DEBUG_PRINT("right\n");
    memset(&s,0,sizeof(s));
    s.mode.z = modeAbs;
    s.position.z = 0.3;
    s.mode.x = modeVelocity;
    s.mode.y = modeVelocity;
    s.velocity.x = SPEED;
    s.velocity.y = 0.;
    s.velocity_body = true;
    s.mode.yaw = modeVelocity;
    s.attitudeRate.yaw = 0;
  }else if(dist_from_center < (MIDDLE - MAX_SIDE)){
    DEBUG_PRINT("left\n");
    memset(&s,0,sizeof(s));
    s.mode.z = modeAbs;
    s.position.z = 0.3;
    s.mode.x = modeVelocity;
    s.mode.y = modeVelocity;
    s.velocity.x = -SPEED;
    s.velocity.y = 0.;
    s.velocity_body = true;
    s.mode.yaw = modeVelocity;
    s.attitudeRate.yaw = 0;
  }else if(angle < ANGLE_90 -MAX_ANGLE){
    DEBUG_PRINT("turn left\n");
    memset(&s,0,sizeof(s));
    s.mode.z = modeAbs;
    s.position.z = 0.3;
    s.mode.x = modeVelocity;
    s.mode.y = modeVelocity;
    s.velocity.x = 0;
    s.velocity.y = 0;
    s.velocity_body = true;
    s.mode.yaw = modeVelocity;
    s.attitudeRate.yaw = 3;
  }else if(angle > ANGLE_90 +MAX_ANGLE){
    DEBUG_PRINT("turn right\n");
    memset(&s,0,sizeof(s));
    s.mode.z = modeAbs;
    s.position.z = 0.3;
    s.mode.x = modeVelocity;
    s.mode.y = modeVelocity;
    s.velocity.x = 0;
    s.velocity.y = 0;
    s.velocity_body = true;
    s.mode.yaw = modeVelocity;
    s.attitudeRate.yaw = -3;
  }else{
    DEBUG_PRINT("forward\n");
    memset(&s,0,sizeof(s));
    s.mode.z = modeAbs;
    s.position.z = 0.3;
    s.mode.x = modeVelocity;
    s.mode.y = modeVelocity;
    s.velocity.x = SPEED;
    s.velocity.y = 0;
    s.velocity_body = true;
    s.mode.yaw = modeVelocity;
    s.attitudeRate.yaw = 0;
  }
}

void appMain() {
  DEBUG_PRINT("Starting drone controller\n");

  // Register a callback for CPX packets.
  // Packets sent to destination=CPX_T_STM32 and function=CPX_F_APP will arrive here
  cpxRegisterAppMessageHandler(cpxPacketCallback);
  vTaskDelay(M2T(10000));
  idle(&s);
    
  while(1) {
    vTaskDelay(M2T(10));
    timout -= 10;
    if(timout <= 0){
      DEBUG_PRINT("TIMOUT\n");
      timout = 0;
      idle(&s);
    }
    commanderSetSetpoint(&s,3);
  }
}



static void idle(setpoint_t *setpoint) {
memset(setpoint,0,sizeof(*setpoint));
setpoint->mode.z = modeAbs;
setpoint->position.z = 0.3;
setpoint->mode.x = modeVelocity;
setpoint->mode.y = modeVelocity;
setpoint->velocity.x = 0;
setpoint->velocity.y = 0;
setpoint->velocity_body = true;
setpoint->mode.yaw = modeVelocity;
setpoint->attitudeRate.yaw = 0;
}


