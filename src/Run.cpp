#include "../include/cyberdns.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>
#include <iostream>
#include "../include/cyberworm.h"
#include "../include/cyberpc.h"
#include "../include/cyberexpert.h"
#include <vector>
#include <string>
#include <iterator>
#include <cstddef>


using namespace std;
using namespace boost::property_tree;

int main(int argc, char *argv[]) {



	//initiating server
	CyberDNS* server = new CyberDNS();
	std::vector<CyberExpert *> expert_list;
	ptree root;

	//extracting termination
	ptree events_tree;
	ptree events_root;
	read_xml("events.xml", events_tree);
	events_root =  events_tree.get_child("");

	string termination;
	BOOST_FOREACH(ptree::value_type const& v, events_root){
		if (v.first == "termination")
		{

			termination = v.second.get<string>("time");
		}
	}

	int termination_time;
	termination_time = std::atoi(termination.c_str());

	//adding pc's to server
	ptree computers_tree;
	read_xml("computers.xml", computers_tree);
	string os;
	string name;
	root =  computers_tree.get_child("");

	BOOST_FOREACH(ptree::value_type const& v, root){
		os = v.second.get<string>("os");
		name = v.second.get<string>("name");
		CyberPC * PC = new CyberPC(os, name);
		cout<<PC->getName()<<" "<<"connected to server"<<endl;
		server->AddPC(*PC);
	}



	//making connections
	ptree network_tree;
	read_xml("network.xml", network_tree);
	root =  network_tree.get_child("");
	string PC_1_Name;
	string PC_2_Name;

	BOOST_FOREACH(ptree::value_type const& v, root){
		PC_1_Name = v.second.get<string>("pointA");
		PC_2_Name = v.second.get<string>("pointB");
		cout<<"Connecting "<<PC_1_Name<<" "<<"to "<<PC_2_Name<<endl;
		CyberPC* PC_1;
		PC_1 = &server->GetCyberPC(PC_1_Name);
		PC_1->AddConnection(PC_2_Name);
		CyberPC* PC_2;
		PC_2 = &server->GetCyberPC(PC_2_Name);
		PC_2->AddConnection(PC_1_Name);
	}

	vector<string> pc_list = server->GetCyberPCList();
	int curr_day = 0;
	//-------------------------------------------------simulation: start--------------------------------------------------------------------


	BOOST_FOREACH(ptree::value_type const& v, events_root){
		cout<<"Day : "<<curr_day<<endl;

		if (v.first == "clock-in")
		{
			string name_ = v.second.get<string>("name");
			int workTime_= std::atoi(v.second.get<string>("workTime").c_str());
			int restTime_= std::atoi(v.second.get<string>("restTime").c_str());
			int efficiency_= std::atoi(v.second.get<string>("efficiency").c_str());

			CyberExpert * expert = new CyberExpert(name_,workTime_ ,restTime_,efficiency_);
			expert_list.push_back(expert);
			cout<<"        Clock-In: "<<expert->get_name()<<" began working"<<endl;
		}

		else if (v.first == "hack")
		{
			string computer_ = v.second.get<string>("computer");
			string worm_name_ = v.second.get<string>("wormName");
			string worm_os_ = v.second.get<string>("wormOs");
			int worm_dormancy_ = std::atoi(v.second.get<string>("wormDormancy").c_str());

			CyberPC * pc = &server->GetCyberPC(computer_);
			CyberWorm * worm = new CyberWorm(worm_os_, worm_name_, worm_dormancy_);
			cout<<"        Hack occured on "<<pc->getName()<<endl;
			pc->Infect(* worm);


		}

		//cleaning---------------------------------------------------------------------
		int curr_check=0;
		if (!(expert_list.empty())){
					int helper = 0;

					for (unsigned i=0; i < expert_list.size(); i++){
						CyberExpert * curr_expert = expert_list[i];
						if(curr_expert->is_cyber_expert_on_work() == 1){

							for (unsigned j=curr_check;
									j < pc_list.size() && curr_expert->get_number_of_computers_cyber_expert_can_add_to_work()>0 && curr_expert->get_number_of_days_cyber_expert_can_continue_working()>0;
									j++)
							{
								CyberPC * curr_PC = &server->GetCyberPC(pc_list[j]);
								curr_expert->Clean(*curr_PC);
								curr_expert->set_number_of_computers_cyber_expert_can_add_to_work((curr_expert->get_number_of_computers_cyber_expert_can_add_to_work())-1);
								helper = helper + 1;

							}
							curr_expert->update_number_of_days_cyber_expert_can_continue_working_();
							curr_expert->set_number_of_computers_cyber_expert_can_add_to_work(curr_expert->get_efficiency());
						}
						else
						{
							curr_expert->update_number_of_days_cyber_expert_can_continue_rest_();
						}
						curr_check = curr_check + helper;
						helper = 0;
					}



				}


		//infections------------------s----------------------------------

		for (unsigned i=0; i<pc_list.size(); i++){
			CyberPC *curr_pc = &server->GetCyberPC(pc_list[i]);
			curr_pc->Run(*server);
		}
		//----------------------------------------------------------------



		curr_day++;

	}

	int helper = curr_day;
	for (int i=0; i<=termination_time-helper; i++){
		cout<<"Day : "<<curr_day<<endl;

		int curr_check=0;
		//cleaning---------------------------------------------------------------------
		if (!(expert_list.empty())){
						int helper = 0;
						for (unsigned i=0; i < expert_list.size(); i++){
							CyberExpert * curr_expert = expert_list[i];
							if(curr_expert->is_cyber_expert_on_work() == 1){

								for (unsigned j=curr_check ;
										j < pc_list.size() && curr_expert->get_number_of_computers_cyber_expert_can_add_to_work()>0 && curr_expert->get_number_of_days_cyber_expert_can_continue_working()>0;
										j++)
								{
									CyberPC * curr_PC = &server->GetCyberPC(pc_list[j]);
									curr_expert->Clean(*curr_PC);
									curr_expert->set_number_of_computers_cyber_expert_can_add_to_work((curr_expert->get_number_of_computers_cyber_expert_can_add_to_work())-1);
									helper = helper + 1;

								}
								curr_expert->update_number_of_days_cyber_expert_can_continue_working_();
								curr_expert->set_number_of_computers_cyber_expert_can_add_to_work(curr_expert->get_efficiency());
							}
							else
							{
								curr_expert->update_number_of_days_cyber_expert_can_continue_rest_();
							}
							curr_check = curr_check + helper ;
							helper = 0;
						}


					}
		//infections-----------------------------------------------------

		for (unsigned i=0; i<pc_list.size(); i++){
			CyberPC *curr_pc = &server->GetCyberPC(pc_list[i]);
			curr_pc->Run(*server);
		}
		//----------------------------------------------------------------


		curr_day++;
	}

	//-------------------------------------------------simulation: end----------------------------------------------------------------------


	

	for (unsigned i=0; i<expert_list.size(); i++){
		delete expert_list[i];

	}


	delete server;




	return 0;

}


