#include "../include/cyberworm.h"

using namespace std;


CyberWorm::CyberWorm(string cyber_worm_os, string cyber_worm_name, int cyber_worm_dormancy_time):cyber_worm_os_(cyber_worm_os),
	cyber_worm_name_(cyber_worm_name),cyber_worm_dormancy_time_(cyber_worm_dormancy_time){}

CyberWorm::CyberWorm(const CyberWorm& other):cyber_worm_os_(other.cyber_worm_os_),
	cyber_worm_name_(other.cyber_worm_name_),cyber_worm_dormancy_time_(other.cyber_worm_dormancy_time_){}

CyberWorm::~CyberWorm(){

}

string CyberWorm::GetWormOs(){
	return cyber_worm_os_;
}

string CyberWorm::GetWormName(){
	return cyber_worm_name_;
}

int CyberWorm::GetWormDormancyTime(){
	return cyber_worm_dormancy_time_;
}







