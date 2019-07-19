/*

Data Communication Assignment
SIM-1 dce-iperf example 
implemented using point to point dumbbell helper

there are n clients and 2 routers in between and 1 server(Dumbell Topology) 
the clients are connected to one router and the server to other


routers : ip addresses are 10.1.0.1 and 10.1.0.2

left nodes: clients: ip addreses are starting from 10.1.1.1 and so on according to the number of clients
                     as the subnet mask by default is 255.255.255.240 so the ip will be in interval of 16

right nodes: server: ip address is 10.1.2.1

topology is: 

client 1    -------
client 2    -------
  .                    router 1 ------------------------   router 2-----------   server 1 
  .                    10.1.0.1                            10.1.0.2              10.1.2.1
  . 
  .         -------
  .
               
client n    -------


/////////////////////////////////
Team Members
MANAS GUPTA - 171CO122
ANIMESH KUMAR - 171CO108
SRIVATSAN V - 171CO247

BTech IV Semester, 2nd Year
/////////////////////////////////
*/


//header files
#include<string>
#include<sstream>
#include "ns3/point-to-point-helper.h"
#include "ns3/ipv4-address-helper.h"
#include "ns3/ipv6-address-helper.h"
#include "ns3/internet-stack-helper.h"
#include "ns3/ipv4-interface-container.h"
#include "ns3/ipv6-interface-container.h"
#include "ns3/point-to-point-dumbbell.h"
#include "ns3/network-module.h"
#include "ns3/point-to-point-layout-module.h"
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/dce-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/applications-module.h"
#include "ns3/netanim-module.h"
#include "ns3/constant-position-mobility-model.h"
#include "ccnx/misc-tools.h"

//namespaces used
using namespace ns3 ;
using namespace std;
NS_LOG_COMPONENT_DEFINE ("DceIperf");

int main(int argc, char *argv[]){

        //initialize the variables for udp, no. of clients
        //by default no. of clients is 1 and udp usage is false
        bool useUdp=0;
        uint32_t nLeftLeaf=1, nRightLeaf=1;

        std::string bandWidth = "10m";
        

        //for command line arguments
        CommandLine cmd;

        //take useudp as 0 or 1
        cmd.AddValue("useUdp","0 - false, 1 - True",useUdp);
        
        //take number of clients
        cmd.AddValue("nleaf","number of leaves",nLeftLeaf);
        cmd.Parse(argc,argv);

        //create 3 helpers : left(clients) , bottleneck(between routers), right (server)
        PointToPointHelper leftHelper, rightHelper, bottleneckHelper;

        //set attributes for left helper
        leftHelper.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
        leftHelper.SetChannelAttribute ("Delay", StringValue ("1ms"));

        //set attributes for right helper
        rightHelper.SetDeviceAttribute ("DataRate", StringValue ("5Mbps"));
        rightHelper.SetChannelAttribute ("Delay", StringValue ("1ms"));

        //set attributes for bottleneck helper
        bottleneckHelper.SetDeviceAttribute ("DataRate", StringValue ("3Mbps"));
        bottleneckHelper.SetChannelAttribute ("Delay", StringValue ("1ms"));


        //initialize the point to point dumbel helper for the topology to be implemented
        PointToPointDumbbellHelper p= PointToPointDumbbellHelper(nLeftLeaf,leftHelper,nRightLeaf,rightHelper,bottleneckHelper);

        //install internetstackhelper and dcemanager
        InternetStackHelper stack;
        p.InstallStack(stack);

        //dce manager
        DceManagerHelper dceManager;
        dceManager.SetTaskManagerAttribute ("FiberManagerType", StringValue ("UcontextFiberManager"));

        //installing nodes on dce manager
        dceManager.Install (p.GetLeft());
        dceManager.Install (p.GetRight());
       
        for(uint32_t i=0;i<nLeftLeaf; ++i){
                dceManager.Install (p.GetLeft(i));
        }
        dceManager.Install (p.GetRight(0));
    

        //set base for ip ipv4 helpers for each helper
        Ipv4AddressHelper leftIp,rightIp,routerIp;
        routerIp.SetBase ("10.1.0.0", "255.255.255.252");
        rightIp.SetBase ("10.1.2.0", "255.255.255.252");
        leftIp.SetBase ("10.1.1.0", "255.255.255.240");

        //assign ip addresses to the nodes
        p.AssignIpv4Addresses(leftIp,rightIp,routerIp);
 
        //populate the routing tables
        Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

        //initialize the dceaplicationhelper and the application container
        DceApplicationHelper dce;
        ApplicationContainer apps;

        //set stack size for the dcemanager
        dce.SetStackSize (1 << 20);


        //run iperf client on the clients
        uint32_t st=0.7;
        for(uint32_t j=0;j<nLeftLeaf;++j){

                dce.SetBinary ("iperf");
                dce.ResetArguments ();
                dce.ResetEnvironment ();
                dce.AddArgument ("-c");
                dce.AddArgument ("10.1.2.1");
                if(!useUdp){
                      dce.AddArgument ("-i");
                      dce.AddArgument ("1");
                }
                dce.AddArgument ("--time");
                dce.AddArgument ("10");
                /* if tcp window size needs to be changed from default 128kb then can be specified here like 2000
                dce.AddArgument ("-w");
                dce.AddArgument ("2000");
                */
                if (useUdp)
                {
                        dce.AddArgument ("-u");
                        dce.AddArgument ("-b");
                        dce.AddArgument (bandWidth);
                }

                apps = dce.Install (p.GetLeft(j));
                apps.Start (Seconds(st) );
                apps.Stop (Seconds(st+20) );
                st+=30;
        }

        string zz;
        stringstream ss;
        ss << nLeftLeaf;
        zz = ss.str();
        cout<<zz;


        // Launch iperf client on server
        dce.SetBinary ("iperf");
        dce.ResetArguments ();
        dce.ResetEnvironment ();
        dce.AddArgument("-i");
        dce.AddArgument("1");
        dce.AddArgument("-s");
        dce.AddArgument ("-P");
        dce.AddArgument (zz);
        if (useUdp)
        {
            dce.AddArgument ("-u");
        }

        apps = dce.Install (p.GetRight(0));
        apps.Start (Seconds (0.6));
        rightHelper.EnablePcapAll ("iperf-ns3", false);
        Simulator::Stop (Seconds (400.0));
        //start the simulator
        Simulator::Run ();
        Simulator::Destroy ();

return 0;
}

