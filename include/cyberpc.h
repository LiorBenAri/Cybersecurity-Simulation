

#ifndef CYBER_PC
#define CYBER_PC
#include <iostream>
#include <string>
#include "../include/cyberdns.h"
#include "../include/cyberworm.h"


using namespace std;

class CyberDNS; // Forward decleration

class CyberPC

{
private:

    const std::string cyber_pc_os_;
    const std::string cyber_pc_name_;
    std::vector<std::string> cyber_pc_connections_;
    CyberWorm * cyber_worm_ = NULL; //pointer the a worm currently on the PC.
    int cyber_pc_time_to_infect_;
    CyberPC(); // Prevent the use of an empty constructor

public:
    CyberPC(std::string cyber_pc_os, std::string cyber_pc_name);// Only use this constructor
	virtual ~CyberPC();
    const  string getName();
    const  string getOS();
	void AddConnection(std::string  second_pc);					// Add a connection to this PC
	void Infect(CyberWorm & worm); 								// Add a worm to this PC
	void Run(const CyberDNS & server); 							// Activate PC and infect others if worm is active
	void Disinfect();											// called by cyber expert, disinfect PC
	bool AreYouInfected();
	CyberWorm* getWorm();
	vector<string> GetConnections();
	int get_time_to_infect();
	void set_time_to_infect(int time_to_infect);


	//Add additional functions here if necessary

};


#endif
