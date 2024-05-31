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

#include "app.h"

#include "cpx.h"
#include "cpx_internal_router.h"

#include "FreeRTOS.h"
#include "task.h"

#define DEBUG_MODULE "APP"
#include "debug.h"
#include "commander.h"


static void cpxPacketCallback(const CPXPacket_t* cpxRx);
static void move_to(setpoint_t *setpoint, float x,float y,unsigned time_ms);
static void rotate(setpoint_t *setpoint,float degree ,unsigned time_ms);
static void idle(setpoint_t *setpoint,unsigned time_ms);

//static CPXPacket_t txPacket;

static setpoint_t s ={};

void appMain() {
  DEBUG_PRINT("Starting drone controller\n");

  // Register a callback for CPX packets.
  // Packets sent to destination=CPX_T_STM32 and function=CPX_F_APP will arrive here
  cpxRegisterAppMessageHandler(cpxPacketCallback);
  vTaskDelay(M2T(2000));
  idle(&s,5000);
  move_to(&s,0,0.3,2000);
  rotate(&s,90,2000);
  move_to(&s,0,0.3,2000);
  rotate(&s,90,2000);
  move_to(&s,0,0.3,2000);
  rotate(&s,90,2000);
  move_to(&s,0,0.3,2000);
  rotate(&s,90,2000);
  idle(&s,5000);
    
  while(1) {
    vTaskDelay(M2T(10));
    /*
    cpxInitRoute(CPX_T_STM32, CPX_T_GAP8, CPX_F_APP, &txPacket.route);
    txPacket.data[0] = 1;
    txPacket.dataLength = 1;
    cpxSendPacketBlocking(&txPacket);
    */
  }
}

static void cpxPacketCallback(const CPXPacket_t* cpxRx) {
  DEBUG_PRINT("Got packet from GAP8 (%u)\n", cpxRx->data[0]);
}


static void move_to(setpoint_t *setpoint, float x,float y,unsigned time_ms) {
float scale = 1000. / time_ms;
memset(setpoint,0,sizeof(*setpoint));
setpoint->mode.z = modeAbs;
setpoint->position.z = 0.2;
setpoint->mode.x = modeVelocity;
setpoint->mode.y = modeVelocity;
setpoint->velocity.x = y*scale;
setpoint->velocity.y = x*scale;
setpoint->velocity_body = true;

time_ms/=10;
while(time_ms--) {
    vTaskDelay(M2T(10));
    commanderSetSetpoint(setpoint,3);
}
}


static void idle(setpoint_t *setpoint,unsigned time_ms) {
memset(setpoint,0,sizeof(*setpoint));
setpoint->mode.z = modeAbs;
setpoint->position.z = 0.2;
setpoint->mode.x = modeVelocity;
setpoint->mode.y = modeVelocity;
setpoint->velocity.x = 0;
setpoint->velocity.y = 0;
setpoint->velocity_body = true;
setpoint->mode.yaw = modeVelocity;
setpoint->attitudeRate.yaw = 0;
time_ms/=10;
while(time_ms--) {
    vTaskDelay(M2T(10));
    commanderSetSetpoint(setpoint,3);
}
}

static void rotate(setpoint_t *setpoint,float degree ,unsigned time_ms) {
float scale = 1000. / time_ms;
memset(setpoint,0,sizeof(*setpoint));
setpoint->mode.z = modeAbs;
setpoint->position.z = 0.2;
setpoint->mode.x = modeVelocity;
setpoint->mode.y = modeVelocity;
setpoint->velocity.x = 0;
setpoint->velocity.y = 0;
setpoint->mode.yaw = modeVelocity;
setpoint->attitudeRate.yaw = degree * scale;
setpoint->velocity_body = true;
time_ms/=10;
while(time_ms--) {
    vTaskDelay(M2T(10));
    commanderSetSetpoint(setpoint,3);
}
}

