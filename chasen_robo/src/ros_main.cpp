#include <ros/ros.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <limits>
#include <math.h>

#include <boost/asio.hpp>
#include <std_msgs/Int16.h>
#include <ros/console.h>

#include <boost/thread.hpp>

using namespace::boost::asio;
using namespace std;

//boost::mutex mtx;

int read_cnt = 0;
char fbuf[1024] = {0};
boost::array<char, 256> rbuf;
string serial_port_name;


void mySigintHandler(int sig){
  printf("shutdown catch signal %d \n", sig);
  ros::shutdown();
}
/*
void read_callback(const boost::system::error_code& e, std::size_t size){
// boost::mutex::scoped_lock lk(mtx);

  for(unsigned int i=0;i<size;i++){
    char c = rbuf.at(i);
    fbuf[read_cnt++] = c;
    if(c == '\n'){
      string read_str=fbuf;
        cout<<fbuf<<endl;
      //sscanf(read_str.c_str(),"%d",&panunit_read  );
      // cout<<panunit_read<<endl;

      read_cnt = 0;
    }
  }
  usleep(30*1000);
  port.async_read_some( buffer(rbuf), boost::bind(&read_callback, _1, _2 ));
}
*/


void panspeed_Callback(const std_msgs::Int16::ConstPtr &bottom_msg){
	int data_read = bottom_msg->data;
	
    //1,2     茶筅
    //3,4,5   リフト
    //6,7,8   ターンテーブル
    //9,0     柄杓
    //q,w     ARM1 茶さじ根本
    //e,r     ARM2
    //t,y     ARM3
    //s,d   　ARM4 茶さじ先端  "a"は不要のため、削除
    //f,g     茶さじ動作
    //i,o,m   シーケンス　i(in)：動作、m(max):動作、o(out):戻り動作

  	string init_cmd01;
	if(data_read==1){
	ROS_DEBUG("rosbridge_1_push\n");
	printf("rosbridge_1_push\n");
	init_cmd01= "i\n";
	}
	else if(data_read==2){
	ROS_DEBUG("rosbridge_2_push\n");
	printf("rosbridge_2_push\n");
	init_cmd01= "o\n";
	}
	else if(data_read==3){
	ROS_DEBUG("rosbridge_3_push\n");
	printf("rosbridge_3_push\n");
	init_cmd01= "m\n";
	}

	else if(data_read==4){
	ROS_DEBUG("rosbridge_4_push\n");
	printf("rosbridge_4_push\n");
	init_cmd01= "1\n";
	}
	else if(data_read==5){
	ROS_DEBUG("rosbridge_5_push\n");
	printf("rosbridge_5_push\n");
	init_cmd01= "2\n";
	}
	else if(data_read==6){
	ROS_DEBUG("rosbridge_6_push\n");
	printf("rosbridge_6_push\n");
	init_cmd01= "3\n";
	}
	else if(data_read==7){
	ROS_DEBUG("rosbridge_7_push\n");
	printf("rosbridge_7_push\n");
	init_cmd01= "4\n";
	}
	else if(data_read==8){
	ROS_DEBUG("rosbridge_8_push\n");
	printf("rosbridge_8_push\n");
	init_cmd01= "5\n";

	}
	else if(data_read==9){
	ROS_DEBUG("rosbridge_9_push\n");
	printf("rosbridge_9_push\n");
	init_cmd01= "6\n";
	}
	else if(data_read==10){
	ROS_DEBUG("rosbridge_10_push\n");
	printf("rosbridge_10_push\n");
	init_cmd01= "7\n";
	}
	else if(data_read==11){
	ROS_DEBUG("rosbridge_11_push\n");
	printf("rosbridge_11_push\n");
	init_cmd01= "8\n";
	}
	else if(data_read==12){
	ROS_DEBUG("rosbridge_12_push\n");
	printf("rosbridge_12_push\n");
	init_cmd01= "9\n";
	}
	else if(data_read==13){
	ROS_DEBUG("rosbridge_13_push\n");
	printf("rosbridge_13_push\n");
	init_cmd01= "0\n";
	}
	else if(data_read==14){
	ROS_DEBUG("rosbridge_14_push\n");
	printf("rosbridge_14_push\n");
	init_cmd01= "f\n";
	}
	else if(data_read==15){
	ROS_DEBUG("rosbridge_15_push\n");
	printf("rosbridge_15_push\n");
	init_cmd01= "g\n";
	
	}

	if(init_cmd01!=""){
		//const char *PORT = "/dev/ttyACM0";
		io_service io;
		serial_port port( io, serial_port_name.c_str() );
		port.set_option(serial_port_base::baud_rate(9600));
		port.set_option(serial_port_base::character_size(8));
		port.set_option(serial_port_base::flow_control(serial_port_base::flow_control::none));
		port.set_option(serial_port_base::parity(serial_port_base::parity::none));
		port.set_option(serial_port_base::stop_bits(serial_port_base::stop_bits::one));

		cout<<"send:"<<init_cmd01<<endl;
		write(port, buffer(init_cmd01));
	}

	usleep(100*1000);
}



int main(int argc, char **argv){

  //boost::thread thr_io(boost::bind(&io_service::run, &io));
  //port.async_read_some( buffer(rbuf), boost::bind(&read_callback, _1, _2 ));

  ros::init(argc, argv, "robot_rot");
  ros::NodeHandle nh;
  ros::NodeHandle private_nh("~");

  private_nh.param("serial_port", serial_port_name, std::string ("/dev/ttyACM0"));

  ros::Subscriber switch_sub = nh.subscribe<std_msgs::Int16>("start", 10, &panspeed_Callback);

  boost::asio::streambuf response_buf;
  
  
  ros::Rate r(50.0);

  signal(SIGINT, mySigintHandler);


  ros::spin();

  return 0;

}
