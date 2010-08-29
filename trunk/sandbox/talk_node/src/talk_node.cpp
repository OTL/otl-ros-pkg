/**********************************************************************
	SampleTalk.c - AquesTalk2 Linux ��§�������� ����ץ�ץ����

	ɸ�����Ϥ��鲻��������򣱹��ɤ߹��ߡ�
	ɸ����Ϥ˲����ȷ�(.wav�ե����ޥåȡˤ����

	COPYRIGHT (C) 2010 AQUEST CORP.

	������ˡ�ϡ�readme.txt �򻲾Ȥ���������
	
	2010/01/23	N.Yamazaki	Creation
**********************************************************************/
#include <stdio.h>
#include "talk_node/AquesTalk2.h"
#include <ros/ros.h>
#include <std_msgs/String.h>

void CommandCB(const std_msgs::String::ConstPtr& talk)
{
  int 	size;
  FILE *play;

  // ��������
  unsigned char *wav = AquesTalk2_Synthe_Roman(talk->data.c_str(), 100, &size, NULL);

  if(wav==0){
    ROS_ERROR("ERR:%d",size);
  }
  
  // �����ǡ���(wav�ե����ޥå�)�ν���
  //fwrite(wav, 1, size, stdout);
  play = popen("/usr/bin/play -t wav -", "w");

  if (play < 0)
    {
      ROS_ERROR("popen fail");
    }
  fwrite(wav, 1, size, play);
  
  // �����ǡ����Хåե��γ���
  AquesTalk2_FreeWave(wav);
  pclose(play);
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "talk_node");
  ros::NodeHandle node;
  ros::Subscriber sub = node.subscribe("talk", 10, &CommandCB);
  ros::spin();
  return 0;
}
