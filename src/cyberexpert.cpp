#include "../include/cyberexpert.h"
#include "../include/cyberpc.h"

using namespace std;

CyberExpert::CyberExpert(string cyber_expert_name_, int cyber_expert_work_time_,
						int cyber_expert_rest_time_, int cyber_expert_efficiency_):
								cyber_expert_name_(cyber_expert_name_ ),cyber_expert_work_time_(cyber_expert_work_time_),
								cyber_expert_rest_time_(cyber_expert_rest_time_),cyber_expert_efficiency_(cyber_expert_efficiency_),
								is_cyber_expert_on_work_(true),
								number_of_computers_cyber_expert_can_add_to_work_(cyber_expert_efficiency_),
								number_of_days_cyber_expert_can_continue_working_(cyber_expert_work_time_),
								number_of_days_cyber_expert_can_continue_rest__(cyber_expert_rest_time_){}


CyberExpert::~CyberExpert(){};

void CyberExpert::Clean(CyberPC & cyber_pc){
	cout<<"        "<<cyber_expert_name_<<" examining "<<cyber_pc.getName()<<endl;
	if(cyber_pc.AreYouInfected()==true){
		if(is_cyber_expert_on_work_==true
				&& number_of_computers_cyber_expert_can_add_to_work_>0){
			cyber_pc.Disinfect();
		}
	}
	return;
}

string CyberExpert::get_name() const{
	return cyber_expert_name_;
}

int	CyberExpert::get_efficiency() const{
	return cyber_expert_efficiency_;
}
bool CyberExpert::is_cyber_expert_on_work(){
	return is_cyber_expert_on_work_;
}
int CyberExpert::get_number_of_computers_cyber_expert_can_add_to_work(){
	return number_of_computers_cyber_expert_can_add_to_work_;
}

int CyberExpert::get_number_of_days_cyber_expert_can_continue_working(){
	return number_of_days_cyber_expert_can_continue_working_;
}

void CyberExpert::set_number_of_computers_cyber_expert_can_add_to_work(int number_of_computers_cyber_expert_can_add_to_work){
	number_of_computers_cyber_expert_can_add_to_work_=number_of_computers_cyber_expert_can_add_to_work;
}

void CyberExpert::update_number_of_days_cyber_expert_can_continue_working_(){
	if (cyber_expert_rest_time_ != 0){
	number_of_days_cyber_expert_can_continue_working_=number_of_days_cyber_expert_can_continue_working_-1;
	if(number_of_days_cyber_expert_can_continue_working_==0){
		is_cyber_expert_on_work_=false;
		cout<<"        "<<cyber_expert_name_<<" is taking a break"<<endl;
		number_of_days_cyber_expert_can_continue_working_= cyber_expert_work_time_;
	}
	}
	else
		{
			is_cyber_expert_on_work_  = 1;
			number_of_days_cyber_expert_can_continue_working_= cyber_expert_work_time_;
		}

}
void CyberExpert::update_number_of_days_cyber_expert_can_continue_rest_(){
	if (cyber_expert_rest_time_ != 0){
	number_of_days_cyber_expert_can_continue_rest__=number_of_days_cyber_expert_can_continue_rest__-1;
	if(number_of_days_cyber_expert_can_continue_rest__ == 0){
		is_cyber_expert_on_work_=true;
		cout<<"        "<<cyber_expert_name_<<" is back to work"<<endl;
		number_of_days_cyber_expert_can_continue_rest__= cyber_expert_rest_time_;
	}
	}
	else
	{
		is_cyber_expert_on_work_  = 1;
		number_of_days_cyber_expert_can_continue_working_= cyber_expert_work_time_;
	}
}

