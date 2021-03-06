//ROS
#include "ros/ros.h"
#include "sensor_msgs/Joy.h"
#include "geometry_msgs/Twist.h"
#include <iostream>
#include <signal.h>
using namespace std;


void mySigintHandler(int sig)
{
  // Do some custom action.
  // For example, publish a stop message to some other nodes.
  
  // All the default sigint handler does is call shutdown()
  ros::shutdown();
}

void joy_cb(const sensor_msgs::Joy::ConstPtr& msg){
  //std_msgs::Bool estop_msg;
  //estop_msg.data = msg->buttons[JOY_BTN_LB] > 0; // Should be 1 or zero
  //estop_pub.publish(estop_msg);

  //btn_dir_data = msg->buttons;
  //ROS_INFO("%d",msg->axes);
  //cout << msg->axes[0]<<endl;
  //joy2twist(msg);
}

geometry_msgs::Twist twist;
double w,V;

void joy2twist(const sensor_msgs::Joy::ConstPtr& msg){
  twist.angular.z = msg->axes[0]*5*3.1415926535;
  twist.linear.x = msg->axes[4]*20;
  twist.linear.y = msg->axes[3]*20;
  //cout << twist << endl;
}

int main(int argc, char **argv)
{
  cout<<"JOY2TWIST launched."<<endl;
  ros::init(argc, argv, "joy2twist",ros::init_options::NoSigintHandler);
  ros::NodeHandle nh; 
  nh.getParam("/joy2twist/V",V);
  nh.getParam("/joy2twist/w",w);
  ros::Publisher twistPub=nh.advertise<geometry_msgs::Twist>("/cmd_vel", 100);

  ros::Rate rate(150);
  ros::Subscriber joySub = nh.subscribe("/joy", 10, joy2twist);
  
  while (ros::ok)
  {
      ros::spinOnce();
      twistPub.publish(twist);
      rate.sleep();
      signal(1, mySigintHandler);
  }

    return 0;
}


