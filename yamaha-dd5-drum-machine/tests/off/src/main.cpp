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

#define MOT_ID_LEFT  4
#define MOT_ID_RIGHT 3
#define MOT_VEL      100.0
#define MOT_TOR      0.3

double mot_pos = 0.2;
double bpm     = 480.0 * 2.0;
double f       = (bpm / 60.0);


int main()
{ 
  /* Make System Object */
  DynamixelAchClient dac = DynamixelAchClient();

  int r = 0;

  /* Turn On System */
  r = dac.cmd(DYNAMIXEL_CMD_OFF, true);
  if( r == DYNAMIXEL_CMD_OFF ){ r=0; }
  else{ printf("1\n"); return 1; }


  /* Add ID */
  r = dac.cmd(DYNAMIXEL_CMD_ID_ADD, (int16_t)MOT_ID_LEFT);
  r = dac.cmd(DYNAMIXEL_CMD_ID_ADD, (int16_t)MOT_ID_RIGHT);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ printf("1\n"); return 1; }

  /* Turn Off System */
  r = dac.cmd(DYNAMIXEL_CMD_OFF, true);
  if( r == DYNAMIXEL_CMD_OFF ){ r=0; }
  else{ printf("1\n"); return 1; }

}
