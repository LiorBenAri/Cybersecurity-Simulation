/*
 * cyberexpert.h
 *
 *  Created on: Nov 12, 2015
 *      Author: benarl
 */

#ifndef CYBER_EXPERT
#define CYBER_EXPERT
#include <iostream>
#include <string>
#include <vector>
#include "../include/cyberpc.h"


class CyberExpert
{
private:
	const string cyber_expert_name_;
    const int cyber_expert_work_time_;
    const int cyber_expert_rest_time_;
    const int cyber_expert_efficiency_;
    bool is_cyber_expert_on_work_;
    int number_of_computers_cyber_expert_can_add_to_work_;
    int number_of_days_cyber_expert_can_continue_working_;
    int number_of_days_cyber_expert_can_continue_rest__;
    //int last_pc_checked;
    CyberExpert(); // Prevent the use of an empty constructor
	// Add your own variables here

public:
    CyberExpert(std::string cyber_expert_name_, int cyber_expert_work_time_, int cyber_expert_rest_time_, int cyber_expert_efficiency_);
    virtual ~CyberExpert();
 	void Clean(CyberPC & cyber_pc);
 	string get_name() const;
 	int	get_efficiency() const;
	bool is_cyber_expert_on_work();	//getter
 	int get_number_of_computers_cyber_expert_can_add_to_work();
 	int get_number_of_days_cyber_expert_can_continue_working();
 	void set_number_of_computers_cyber_expert_can_add_to_work(int number_of_computers_cyber_expert_can_add_to_work);
 	void update_number_of_days_cyber_expert_can_continue_working_();
 	void update_number_of_days_cyber_expert_can_continue_rest_();
};


#endif
