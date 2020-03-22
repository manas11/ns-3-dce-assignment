# Dumbbell Topology using Direct Code Execution in ns-3
- This repository contains the C++ program for creating a dumbbell topology in ns-3 DCE(Direct Code Execution)
- Performance of the topology was tested using [**iperf tool**](https://iperf.fr/)
- This assignment was done under the Data Communication course of fourth semester

## Direct Code Execution
ns-3 Direct Code Execution (DCE) is a different tool than native ns-3 and allows the user to run Linux libraries inside the ns-3 environment.


## About Dumbbell Topology
- There will be n clients, 2 routers in between and 1 server 
- This topology will be implemented using point to point dumbbell helper
* The clients are connected to one of the router and server to the other router
* IP addresses of the routers are 10.1.0.1 and 10.1.0.2
* IP addresses of the clients: starting from 10.1.1.1, subnet mask is set by default as 255.255.255.240
* IP address of the server: 10.1.2.1

### Topology Visualization:
<pre>
- client 1    -------
- client 2    -------
-    .                  router 1 ------------------------   router 2-----------   server 1 
-    .                  10.1.0.1                            10.1.0.2              10.1.2.1
-    . 
-    .        -------           
- client n    -------
</pre>
##### The file final.cc contains the code for this topology

## Team Members:

MANAS GUPTA - 171CO122 ([Github](https://github.com/manas11))
ANIMESH KUMAR - 171CO108 ([Github](https://github.com/animeshk08))
SRIVATSAN V - 171CO247 ([Github](https://github.com/SrivatsanV))


## Useful Links and References:
- ns-3 DCE GitHub Repository[Link](https://github.com/direct-code-execution/ns-3-dce)
- ns-3 DCE Manual [Link](https://www.nsnam.org/docs/dce/manual/html/getting-started.html)
- iperf Website [Link](https://iperf.fr/)

