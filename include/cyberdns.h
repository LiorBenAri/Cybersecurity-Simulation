
#ifndef CYBERDNS_H
#define CYBERDNS_H
#include <iostream>
#include <string>
#include <map>
#include "../include/cyberpc.h"

class CyberPC; //Forward deceleration

class CyberDNS
{
private:
    std::map<const std::string, CyberPC &> cyber_DNS_;	//Hash map to hold the PC objects names and reference to each one of them.


public:
    CyberDNS();
    virtual ~CyberDNS();
	void AddPC(CyberPC & cyber_pc_); //add pc to the cyber_DNS_ map.
	CyberPC & GetCyberPC(const std::string & cyber_pc_name) const;
	std::vector<std::string> GetCyberPCList(); 		// Return list of PC's as a vector of strings.
													// All access to PC objects should use this function
													// Do not store pointers elsewhere!

};

#endif
