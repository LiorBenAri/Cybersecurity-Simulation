#include "../include/cyberdns.h"
#include "../include/cyberpc.h"


using namespace std;

 CyberPC::CyberPC(string cyber_pc_os, string cyber_pc_name)
           :cyber_pc_os_(cyber_pc_os),cyber_pc_name_(cyber_pc_name),cyber_pc_time_to_infect_(0){
	 cout<<"Adding to server: "<<cyber_pc_name_<<endl;
 }

 CyberPC::~CyberPC(){
	 if (cyber_worm_!=0){
	 delete cyber_worm_;
	 }
	 cyber_worm_= 0;
 }

 const string CyberPC::getName(){
   return cyber_pc_name_;
 }

 const string CyberPC::getOS(){
   return cyber_pc_os_;
 }


 void CyberPC::AddConnection(std::string  second_pc){
     cyber_pc_connections_.push_back(second_pc);
     cout<<"        "<<getName()<<" "<<"now connected to "<<second_pc<<endl;
 }

 void CyberPC::Infect(CyberWorm & worm){
	 if (worm.GetWormOs() == getOS()){
	     if (cyber_worm_ == 0){
	    	 cyber_worm_ = & worm;
	    	 cyber_pc_time_to_infect_=worm.GetWormDormancyTime();
	    	 cout<<"                "<<getName()<<" infected by "<<worm.GetWormName()<<endl;
	     }
	     else
	     {
	    	 delete cyber_worm_;
	    	 cyber_worm_ = & worm;
	    	 cyber_pc_time_to_infect_=worm.GetWormDormancyTime();
	    	 cout<<"                "<<getName()<<" infected by "<<worm.GetWormName()<<endl;;
	     }
	 }
	 else
	 {
		 cout<<"                Worm "<<worm.GetWormName()<<" is incompatible with "<<getName()<<endl;
		 CyberWorm* ptr = & worm;
		 delete ptr;

	 }

}



 CyberWorm* CyberPC::getWorm(){
    if (cyber_worm_ != 0)
    {
    	return cyber_worm_;
    }
    else
    {
    	return 0;
    }
 }

 void CyberPC::Run(const CyberDNS & server){
	 if (cyber_worm_ != 0 && cyber_pc_time_to_infect_ == 0){
		 cout<<"        "<<getName()<<" infecting..."<<endl;
		 for(unsigned i=0; i < cyber_pc_connections_.size(); i++){
			 CyberPC *tmp_pc = &server.GetCyberPC(cyber_pc_connections_[i]);
			 CyberWorm* new_worm = new CyberWorm(*cyber_worm_);
			 tmp_pc->Infect(*new_worm);
		 }
	 }
	 else if (cyber_worm_ != 0 && cyber_pc_time_to_infect_ != 0){
		 cout<<"        "<<getName()<<": Worm "<<getWorm()->GetWormName()<<" is dormant"<<endl;
		 cyber_pc_time_to_infect_ = cyber_pc_time_to_infect_ - 1;
	 }
 }

 void CyberPC::Disinfect(){
	 string removed_worm_name = cyber_worm_->GetWormName();
	 if (cyber_worm_ != 0){
		 delete cyber_worm_;
		 cyber_worm_ = 0;
	 }
	 cout<<"                Worm "<<removed_worm_name<<" successfully removed from "<<cyber_pc_name_<<endl;
 }

 bool CyberPC::AreYouInfected(){
	 if (cyber_worm_!=0){
		return true;
	 }
	 else
	 {
	 return false;
	 }
 }

 std::vector<string> CyberPC::GetConnections(){
	 return cyber_pc_connections_;
 }


 int CyberPC::get_time_to_infect(){
 	 return cyber_pc_time_to_infect_;
  }

  void CyberPC::set_time_to_infect(int time_to_infect){
 	 cyber_pc_time_to_infect_=time_to_infect;
  }
