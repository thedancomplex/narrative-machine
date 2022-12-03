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

#include <narrative-machine-yamaha-dd5-drum-machine.h>
#include <unistd.h>
#include <string.h>

#define MOT_ID STICK_0

int main()
{ 
  /* Make System Object */
  NarrativeMacineYamahaDD5 dd5 = NarrativeMachineYamahaDD5();

  int r = 0;

  /* Turn On System */
  r = dd5.on(true);

  /* Calibrate */
  r = dd5.calibrate(MOT_ID);
}
