// Copyright 2022 Intelligent Robotics Lab
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "fsm_bump_go/BumpGoProHer.h"

#include "kobuki_msgs/BumperEvent.h"
#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"

#include "ros/ros.h"
#include <cmath>    //For M_PI macro.

namespace fsm_bump_go
{

BumpGoProHer::BumpGoProHer()
{
  state_ = false;
  
  sub_laser_ = n_.subscribe("/scan",1,&BumpGoProHer::laserCallBack,this);
  pub_vel_ = n_.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 1);

}

void
BumpGoProHer::laserCallBack(const sensor_msgs::LaserScan::ConstPtr& laser)
{
  int center = 0;
  int left = 700;
  int right = 150;

  center_dist = laser->ranges[center];
  right_dist = laser->ranges[right];
  left_dist = laser->ranges[left];

  

  if (left_dist < SECURITY_DISTANCE || center_dist < SECURITY_DISTANCE)
  {
    pressed_state_ = LEFT_DETECTED;
    pressed_ = true;
  }
  else if (right_dist < SECURITY_DISTANCE)
  {
    pressed_state_ = RIGHT_DETECTED;
    pressed_ = true;
  }
  else
  {
    pressed_ = false;
  }
}

}  // namespace fsm_bump_go