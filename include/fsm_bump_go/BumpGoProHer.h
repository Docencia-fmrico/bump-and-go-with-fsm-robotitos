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

#ifndef FSM_BUMP_GO_BUMPGO_PRO_HER_H
#define FSM_BUMP_GO_BUMPGO_PRO_HER_H

#include "ros/ros.h"
#include "BumpGoAdv.h"

#include "sensor_msgs/LaserScan.h"
#include "geometry_msgs/Twist.h"
#include "kobuki_msgs/BumperEvent.h"

#define SECURITY_DISTANCE 0.35

namespace fsm_bump_go
{

class BumpGoProHer : public BumpGoAdv
{
public:
    BumpGoProHer();

    void laserCallBack(const sensor_msgs::LaserScan::ConstPtr& laser);

private:

  static const int LEFT_DETECTED = 0;
  static const int RIGHT_DETECTED = 1;

  double center_dist = SECURITY_DISTANCE + 0.1;
  double right_dist = SECURITY_DISTANCE + 0.1;
  double left_dist = SECURITY_DISTANCE + 0.1;

  static constexpr double TURNING_TIME = 3.0;
  static constexpr double BACKING_TIME = 3.0;


  ros::NodeHandle n_;

  ros::Time press_ts_;
  ros::Time turn_ts_;


  ros::Subscriber sub_laser_;
  ros::Publisher pub_vel_;
};

} // namespace fsm_bump_go

#endif  // FSM_BUMP_GO_BUMPGO_PRO_HER_H