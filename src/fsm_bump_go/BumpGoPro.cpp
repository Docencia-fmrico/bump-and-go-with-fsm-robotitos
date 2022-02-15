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

#include "fsm_bump_go/BumpGoPro.h"

#include "kobuki_msgs/BumperEvent.h"
#include "geometry_msgs/Twist.h"

#include "ros/ros.h"
#include <cmath>    //For M_PI macro.

namespace fsm_bump_go
{

BumpGoPro::BumpGoPro()
: state_(GOING_FORWARD),
  obstacle_detected_(false)
{
  sub_laser_ = n_.subscribe("/scan",1,&BumpGoPro::laserCallBack,this);
  pub_vel_ = n_.advertise<geometry_msgs::Twist>("mobile_base/commands/velocity", 1);

}

void
BumpGoPro::laserCallBack(const sensor_msgs::LaserScan::ConstPtr& laser)
{
  int center = (0 - laser->angle_min) / laser->angle_increment;
  int right = (M_PI/5 - laser->angle_min) / laser->angle_increment;
  int left = (-M_PI/5 - laser->angle_min) / laser->angle_increment;

  center_dist = laser->ranges[center];
  right_dist = laser->ranges[right];
  left_dist = laser->ranges[left];

  if (center_dist < SECURITY_DISTANCE || right_dist < SECURITY_DISTANCE || left_dist < SECURITY_DISTANCE)
  {
    obstacle_detected_ = true;
  }
  else
  {
    obstacle_detected_ = false;
  }

  if (left_dist < SECURITY_DISTANCE)
  {
    obstacle_state_ = LEFT_DETECTED;
  }
  else if (center_dist < SECURITY_DISTANCE)
  {
    obstacle_state_ = CENTER_DETECTED;
  }
  else if (right_dist < SECURITY_DISTANCE)
  {
    obstacle_state_ = RIGHT_DETECTED;
  }
}

void
BumpGoPro::step()
{
  geometry_msgs::Twist cmd;

  switch (state_)
  {
    case GOING_FORWARD:
      cmd.linear.x = 0.1;
      cmd.angular.z = 0.0;

      if (obstacle_detected_)
      {
        detected_ts_ = ros::Time::now();
        state_ = GOING_BACK;
        ROS_INFO("GOING_FORWARD -> GOING_BACK");
      }

      break;
    case GOING_BACK:
      cmd.linear.x = -0.1;
      cmd.angular.z = 0.0;

      if ((ros::Time::now() - detected_ts_).toSec() > BACKING_TIME )
      {
        turn_ts_ = ros::Time::now();
        if (obstacle_state_ == RIGHT_DETECTED)
        {
          state_ = TURNING_LEFT;
          ROS_INFO("GOING_BACK -> TURNING_LEFT");
        }
        else
        {
          state_ = TURNING_RIGHT;
          ROS_INFO("GOING_BACK -> TURNING_RIGHT");
        }
      }

      break;
    case TURNING_LEFT:
      cmd.linear.x = 0.0;
      cmd.angular.z = 0.5;


      if ((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME )
      {
        state_ = GOING_FORWARD;
        ROS_INFO("TURNING_LEFT -> GOING_FORWARD");
      }
      break;
    case TURNING_RIGHT:
      cmd.linear.x = 0.0;
      cmd.angular.z = -0.5;


      if ((ros::Time::now()-turn_ts_).toSec() > TURNING_TIME )
      {
        state_ = GOING_FORWARD;
        ROS_INFO("TURNING_RIGHT -> GOING_FORWARD");
      }
      break;
    }

    pub_vel_.publish(cmd);
}

}  // namespace fsm_bump_go