#include "../include/cyberdns.h"
#include "../include/cyberpc.h"
#include <string>
#include <vector>
#include <iterator>
#include <algorithm>

using namespace std;

CyberDNS::CyberDNS(){}

CyberDNS::~CyberDNS(){//delete cyberDNS object and all the PC objects it references to in the cyber_DNS map.
	vector<string> pc_list = GetCyberPCList();
	 for(unsigned i=0; i < pc_list.size(); i++){
		 CyberPC* tmp_pc = & GetCyberPC(pc_list[i]);
		 delete tmp_pc;
	 }
}



void CyberDNS::AddPC(CyberPC & cyber_pc_){
	cyber_DNS_.insert(std::pair<const std::string, CyberPC &>(cyber_pc_.getName(), cyber_pc_));
}

CyberPC & CyberDNS::GetCyberPC(const std::string & cyber_pc_name) const{
	return cyber_DNS_.find(cyber_pc_name)->second;
}


std::vector<string> CyberDNS::GetCyberPCList(){
	vector<string>PcListVector;
	std::map<const string, CyberPC &>::iterator iterator;
	for (iterator = cyber_DNS_.begin(); iterator != cyber_DNS_.end() ; iterator++){
		PcListVector.push_back(iterator->first);
	}
	std::reverse(PcListVector.begin(), PcListVector.end());
    return PcListVector;

}


