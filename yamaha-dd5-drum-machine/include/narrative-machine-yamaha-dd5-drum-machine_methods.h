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

NarrativeMachineYamahaDD5::NarrativeMachineYamahaDD5()
{
  memset(&this->mot_calibrate, 0, sizeof(mot_calibrate));
  for(int i = 0; i < DD5_MOT_NUM; i++)
  {
    this->mot_calibrate.mot[i].dir         = 1.0;
    this->mot_calibrate.mot[i].tor         = MOT_TOR_CALIBRATE;
    this->mot_calibrate.mot[i].vel         = MOT_VEL_CALIBRATE;
    this->mot_calibrate.mot[i].pos_up      = MOT_POS_UP_CALIBRATE;
    this->mot_calibrate.mot[i].pos_down    = MOT_POS_DOWN_CALIBRATE;
    this->mot_calibrate.mot[i].offset_up   = MOT_HIT_OFFSET_UP;
    this->mot_calibrate.mot[i].offset_down = MOT_HIT_OFFSET_DOWN;
    this->dac.stageRefPos(    i, 0.0);
    this->dac.stageRefVel(    i, 0.0);
    this->dac.stageRefTorque( i, 0.0);
  }
  this->dac.postRef();

  /* Make System Object */
 // this->dac = DynamixelAchClient();

  /* Add Motors */
  this->addMotor(MOT_ID_STICK_0);
  this->addMotor(MOT_ID_STICK_1);
}

int NarrativeMachineYamahaDD5::addMotor(int mot)
{
  int r = dac.cmd(DYNAMIXEL_CMD_ID_ADD, (int16_t)mot);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ 
    if(do_debug) printf("%s ERROR - Add Motor\n", DD5_HEADER); 
    return DD5_FAIL; 
  }
  return DD5_OK;
}

int NarrativeMachineYamahaDD5::calibrate(int mot)
{
    double dir      = this->mot_calibrate.mot[mot].dir;
    double pos_up   = this->mot_calibrate.mot[mot].pos_up;
    double pos_down = this->mot_calibrate.mot[mot].pos_down;
    double vel      = this->mot_calibrate.mot[mot].vel;
    double tor      = this->mot_calibrate.mot[mot].tor;

    /* Put stick up */ 
    this->dac.stageRefPos(mot,     pos_up * dir);
    this->dac.stageRefVel(mot,     vel);
    this->dac.stageRefTorque(mot,  tor);
    this->dac.postRef();
    printf("Putting stick %d up\n", mot);
    this->dac.sleep(5.0);

    /* Put stick down */ 
    this->dac.stageRefPos(mot,     pos_down * dir);
    this->dac.stageRefVel(mot,     vel);
    this->dac.stageRefTorque(mot,  tor);
    this->dac.postRef();
    printf("Putting stick %d down\n", mot);
    this->dac.sleep(5.0);

    /* Get State */
    dac.getState();
    double ref = this->dac.dynamixel_state.motor_ref[mot].pos;
    double pos = this->dac.dynamixel_state.motor_state[mot].pos;
    double t   = this->dac.time();

    this->mot_calibrate.mot[mot].pos_down =   pos 
                                              + this->mot_calibrate.mot[mot].offset_down
                                              * this->mot_calibrate.mot[mot].dir;
    this->mot_calibrate.mot[mot].pos_up   =   pos 
                                              - this->mot_calibrate.mot[mot].offset_up
                                              * this->mot_calibrate.mot[mot].dir;

    this->mot_calibrate.mot[mot].tor      = MOT_TOR;
    this->mot_calibrate.mot[mot].vel      = MOT_VEL;

    printf("t %f id %d ref %f pos %f\n", t, mot, ref, pos);
    
    return DD5_OK;
}

int NarrativeMachineYamahaDD5::on(int mot)
{
  /* Turn On System */
  int r = this->dac.cmd(DYNAMIXEL_CMD_ON, (int16_t)mot);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ 
    if(do_debug) printf("%s ERROR - On\n", DD5_HEADER); 
    return DD5_FAIL; 
  }
  return DD5_OK;
}

int NarrativeMachineYamahaDD5::on()
{
  /* Turn On System */
  int r = this->dac.cmd(DYNAMIXEL_CMD_ON);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ 
    if(do_debug) printf("%s ERROR - On\n", DD5_HEADER); 
    return DD5_FAIL; 
  }

//  this->on(MOT_ID_STICK_0);
//  this->on(MOT_ID_STICK_1);
  this->dac.sleep(2.0);
  return DD5_OK;
}

int NarrativeMachineYamahaDD5::off()
{
  /* Turn On System */
  int r = this->dac.cmd(DYNAMIXEL_CMD_OFF);
  if( r == DYNAMIXEL_CMD_OK ){ r=0; }
  else{ 
    if(do_debug) printf("%s ERROR - Off\n", DD5_HEADER); 
    return DD5_FAIL; 
  }
  return DD5_OK;
}


int NarrativeMachineYamahaDD5::sleep(double val)
{
  return this->dac.sleep(val);
}

int NarrativeMachineYamahaDD5::hit(int mot)
{
    if( (mot < 0) | (mot > DD5_MOT_NUM) ) return DD5_FAIL;

    double dir      = this->mot_calibrate.mot[mot].dir;
    double pos_up   = this->mot_calibrate.mot[mot].pos_up;
    double pos_down = this->mot_calibrate.mot[mot].pos_down;
    double vel      = this->mot_calibrate.mot[mot].vel;
    double tor      = this->mot_calibrate.mot[mot].tor;
  
    this->dac.stageRefPos(mot,     pos_down * dir);
    this->dac.stageRefVel(mot,     vel);
    this->dac.stageRefTorque(mot,  tor);
    this->dac.postRef();
    dac.sleep(MOT_HIT_TIME);
    this->dac.stageRefPos(mot,     pos_up * dir);
    this->dac.stageRefVel(mot,     vel);
    this->dac.stageRefTorque(mot,  tor);
    this->dac.postRef();
  
    return DD5_OK;
}
