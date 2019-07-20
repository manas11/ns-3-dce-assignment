# ns-3-dce assignment
--------------------------
## Data Communication Course Assignment 
* Brief: ns-3 Direct Code Execution (DCE) is a different tool than native ns-3 and allows the user to run Linux libraries inside the ns-3 environment. In this task, the main goal is to install ns-3 DCE, run the iperf example and modify it.

### Working
* There will be n clients, 2 routers in between and 1 server 
* This topology will be implemented using point to point dumbbell helper
* The clients are connected to one of the router and server to the other router
* IP addresses of the routers are 10.1.0.1 and 10.1.0.2
* IP addresses of the clients: starting from 10.1.1.1, subnet mask is set by default as 255.255.255.240
* IP address of the server: 10.1.2.1

### topology visualization:

#### client 1    -------
#### client 2    -------
####    .                  router 1 ------------------------   router 2-----------   server 1 
####    .                  10.1.0.1                            10.1.0.2              10.1.2.1
####    . 
####    .        -------
####    .           
#### client n    -------


#### Recommended Reading:
* ns-3 DCE github repository (Link: https://github.com/direct-code-execution/ns-3-dce)
* DCE Manual (Link: https://www.nsnam.org/docs/dce/manual/html/getting-started.html)
