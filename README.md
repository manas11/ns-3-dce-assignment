# ns-3-dce assignments
--------------------------
## Data Communication Course Assignment 
* Brief: ns-3 Direct Code Execution (DCE) is a different tool than native ns-3 and allows the user to run Linux libraries inside the ns-3 environment. In this task, the main goal is to install ns-3 DCE and successfully run the iperf example.

### dce-iperf 
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


#### Recommended Reading:
* ns-3 DCE github repository (Link: https://github.com/direct-code-execution/ns-3-dce)
* DCE Manual (Link: https://www.nsnam.org/docs/dce/manual/html/getting-started.html)
