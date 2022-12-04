/*******************************************************************************
* Copyright 2022 Daniel M. Lofaro
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*******************************************************************************/

/* Author: Daniel M. Lofaro */

#include <lofaro_dynamixel_ach_client.h>
#include <unistd.h>
#include <string.h>

#define MOT_ID_LEFT            5
#define MOT_ID_RIGHT           3
#define MOT_ID                 MOT_ID_RIGHT
#define MOT_VEL                100.0
#define MOT_TOR                0.3
#define MOT_VEL_CALIBRATE      0.5
#define MOT_TOR_CALIBRATE      0.15

double mot_pos = 0.2;
double bpm     = 480.0 * 2.0;
double f       = (bpm / 60.0);


int main()
{ 
  /* Make System Object */
  DynamixelAchClient dac = DynamixelAchClient();

  int r = 0;

  /* Turn On System */
  r = dac.cmd(DYNAMIXEL_CMD_ON, true);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ printf("1\n"); return 1; }


  /* Add ID */
  r = dac.cmd(DYNAMIXEL_CMD_ID_ADD, (int16_t)MOT_ID);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ printf("1\n"); return 1; }

  printf("Freq = %f\n", f/2.0);
  dac.rate( f );

  while(1)
  {

    /* Put all sticks up */ 
    dac.stageRefPos(MOT_ID,     -mot_pos);
    dac.stageRefVel(MOT_ID,     MOT_VEL_CALIBRATE);
    dac.stageRefTorque(MOT_ID,  MOT_TOR_CALIBRATE);
    dac.postRef();
    dac.sleep();
    printf("Putting sticks up");
    dac.sleep(5.0);


    dac.stageRefPos(MOT_ID,     mot_pos);
    dac.stageRefVel(MOT_ID,     MOT_VEL_CALIBRATE);
    dac.stageRefTorque(MOT_ID,  MOT_TOR_CALIBRATE);
    dac.postRef();
    dac.sleep();
    dac.sleep(5.0);

    dac.getState();
    int    id  = MOT_ID;
    double ref = dac.dynamixel_state.motor_ref[id].pos;
    double pos = dac.dynamixel_state.motor_state[id].pos;
    double t   = dac.time();
    printf("t %f id %d ref %f pos %f\n", t, id, ref, pos);
    break;
  }

  /* Turn Off System */
  r = dac.cmd(DYNAMIXEL_CMD_OFF, true);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ printf("1\n"); return 1; }

  return 0;
}
