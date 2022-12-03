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


#define NM_YAMAHA_DD5_METHODS 1

#include <lofaro_dynamixel_ach_client.h>
#include <unistd.h>
#include <string.h>

#define MOT_ID_LEFT            4
#define MOT_ID_RIGHT           3
#define MOT_ID                 MOT_ID_LEFT
#define MOT_VEL                100.0
#define MOT_TOR                0.3
#define MOT_VEL_CALIBRATE      0.5
#define MOT_TOR_CALIBRATE      0.15

double mot_pos = 0.2;
double bpm     = 480.0 * 2.0;
double f       = (bpm / 60.0);

NarrativeMachineYamahaDD5::NarrativeMachineYamahaDD5()
{
  memset(&this->mot_calibrate, 0, sizeof(mot_calibrate));
  for(int i = 0; i < DD5_MOT_NUM; i++)
  {
    this->mot_calibrate.mot[i].dir = 1.0;
  }

  /* Make System Object */
  this->dac = DynamixelAchClient();

  /* Add Motors */
  this->addMotor(STICK_0);
}

int NarrativeMachineYamahaDD5::addMotor(int mot)
{
  int r = dac.cmd(DYNAMIXEL_CMD_ID_ADD, (int16_t)mot);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ 
    if(do_debut) printf("%s ERROR - Add Motor\n", DD5_HEADER); 
    return DD5_FAIL; 
  }
  return DD5_OK;
}

int NarrativeMachineYamahaDD5::calibrate(mot_def_t *data, int mot)
{
    double dir      = data->mot[mot].dir;
    double pos_up   = data->mot[mot].pos_up;
    double pos_down = data->mot[mot].pos_down;
    double vel      = data->mot[mot].vel;
    double tor      = data->mot[mot].tor;

    /* Put stick up */ 
    this->dac.stageRefPos(mot,     pos_up * dir);
    this->dac.stageRefVel(mot,     vel);
    this->dac.stageRefTorque(mot,  tor);
    this->dac.postRef();
    printf("Putting sticks up");
    this->dac.sleep(5.0);

    /* Put stick down */ 
    this->dac.stageRefPos(mot,     pos_down * dir);
    this->dac.stageRefVel(mot,     vel);
    this->dac.stageRefTorque(mot,  tor);
    this->dac.postRef();
    printf("Putting sticks up");
    this->dac.sleep(5.0);

    /* Get State */
    dac.getState();
    double ref = this->dac.dynamixel_state.motor_ref[mot].pos;
    double pos = this->dac.dynamixel_state.motor_state[mot].pos;
    double t   = this->dac.time();
    printf("t %f id %d ref %f pos %f\n", t, mot, ref, pos);
    
    return DD5_OK;
}

int NarrativeMachineYamahaDD5::on()
{
  return this->on(true);
}

int NarrativeMachineYamahaDD5::on( bool low-latency )
{
  /* Turn On System */
  r = this->dac.cmd(DYNAMIXEL_CMD_ON, true);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ 
    if(do_debut) printf("%s ERROR - On\n", DD5_HEADER); 
    return DD5_FAIL; 
  }
  return DD5_OK;
}

int NarrativeMachineYamahaDD5::off()
{
  /* Turn On System */
  r = this->dac.cmd(DYNAMIXEL_CMD_OFF);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ 
    if(do_debut) printf("%s ERROR - Off\n", DD5_HEADER); 
    return DD5_FAIL; 
  }
  return DD5_OK;
}

