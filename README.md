# **CSC466 Group Project: Optimal Routing Protocol and Deployment Strategy for Multi-UAV Relay Networks**

![](img/demo2.gif)
### This is a Simulation for FANETs, Created with OMNET++ 6.1 

## **1. Introduction**  

Communication infrastructure is a fundamental pillar of modern society, yet it remains highly vulnerable to **wars, natural disasters, and large-scale social unrest**, where traditional terrestrial networks can be easily disrupted. In the event of earthquakes, floods, or military conflicts, **ground-based cellular and wired networks may become inoperable**, severely limiting communication capabilities. While **satellite communication** can serve as an alternative, **high deployment costs, excessive latency, and the requirement for specialized terminals (Satellite Terminals) make it impractical for widespread use.**  

In contrast, **Multi-UAV Relay Networks** present a **cost-effective and rapidly deployable solution that enables seamless communication using existing smartphones—without requiring additional hardware**. These networks can be **deployed instantly in affected areas and expanded dynamically by adding more UAVs, ensuring continuous coverage with high scalability**. Furthermore, **compared to satellite communication, UAV relay networks offer significantly lower latency, enabling real-time applications such as military operations, disaster response, and remote control systems.**  

However, **to ensure the efficiency and reliability of UAV-based networks, optimizing both UAV deployment strategy and routing protocols is essential**. A well-optimized system must **maintain network connectivity, minimize frequency interference, and prevent network congestion**, all while dynamically adapting to changing conditions. We focus on **integrating optimal routing protocols and deployment strategies within Multi-UAV Relay Networks**, aiming to **deliver a high-performance, resilient communication system for disaster-stricken areas, battlefields, and regions lacking traditional network infrastructure**.  




## **2. Research Objectives**  

This study aims to **optimize the routing protocol and deployment strategy for Multi-UAV Relay Networks**, providing a **fast and reliable communication system for disaster-stricken areas, battlefields, and regions lacking traditional network infrastructure**.  

### **1) Optimizing UAV Deployment Strategy**  
- The deployment of UAVs is a **critical factor affecting network performance and sustainability**. This research explores **dynamic optimization methods** for UAV deployment.  
- Traditional studies often assume **fixed optimal placements**, but this research aims to develop a **real-time adaptive deployment strategy** where UAVs can adjust their positions dynamically.  
- Key factors considered in the deployment strategy:  
  - **Maximizing Coverage:** Optimizing UAV positions to ensure all ground users remain connected.  
  - **Maintaining Network Connectivity:** Optimizing the number of hops between UAVs to prevent network fragmentation and ensure stability.  

### **2) Developing an Optimal Routing Protocol**  
- This research focuses on **designing a routing protocol that ensures stable network connectivity and maximizes data transmission speed in a multi-hop UAV relay network**.  
- Challenges in UAV-based routing:  
  - **Dynamic Topology Changes:** UAV mobility constantly alters network structure, requiring a routing algorithm that adapts to real-time conditions.  
  - **Minimizing Frequency Interference:** Preventing data collisions and optimizing channel allocation.  
  - **Reducing Transmission Latency:** Selecting the best routing paths to minimize delays and improve network performance.  
- The proposed routing protocol will be compared with existing methods such as **AODV (Ad hoc On-Demand Distance Vector) and OLSR (Optimized Link State Routing)** to evaluate its effectiveness in UAV networks.  


## **3. Simulation**
![](img/pic4.png)
![](img/pic5.png)

We simulated a scenario in which communication infrastructure on Vancouver Island was assumed to be completely connected. In this setup, ground users were positioned in UVIC, and communication was established with a ground station located in Vancouver using 6 UAVs. All communication in the simulation was based on line-of-sight (LOS) connectivity, ensuring that data transmission only occurred when there was a direct visual link between nodes.

### Network Modeling and System Parameters
1.	Node Types and Roles:
- **Sender (user[0])**: Acts as the source node generating traffic (using PingApp) at regular 3-second intervals.
- **Receiver (gs[0])**: Serves as the ground station (GS) that receives the data, representing the backhaul connection to wider networks.
- **UAV Nodes**: These are deployed as relay nodes within the aerial network, with three main roles:
- **Gateway UAV**: Provides the critical connection between the GS and the UAV swarm by dynamically being assigned based on proximity.
- **Mesh UAVs**: Form a multi-hop relay network that ensures robust, redundant paths for packet forwarding.
- **LTE/5G Base Station UAV**: Acts as a mobile base station to provide high-speed connectivity directly to ground users.

2.	Communication Ranges:
- **User nodes**: 3 km
- **UAV nodes**: 30 km
- **Ground Station (GS)**: 50 km




## **4. Problems**
While multi-UAV relay networks offer a powerful alternative for establishing communication in environments lacking traditional infrastructure, they have several limitations compared to base station (BS)-based networks.

First, UAV networks suffer from capacity-limited wireless backhaul, which restricts the transmission rate when UAVs connect to a base station​The_Optimal_Placement_f…. Unlike terrestrial networks with fixed fiber-optic backhaul, UAV networks rely on wireless relays, meaning that as the number of hops increases, overall network performance may degrade due to accumulated delays and bandwidth limitations.

Second, UAV networks are more vulnerable to environmental factors such as wind, precipitation, and obstacles, unlike fixed ground base stations. These environmental challenges lead to higher path loss and increased interference, significantly affecting network performance. In urban environments with dense buildings or areas with high radio interference, signal degradation can be severe, limiting the network’s reliability.


## **5. What has been done.**
There are many different wireless channel allocation and different trajectory opitmizations. Asking chat gpt these are just some of the 
**Adaptive Channel Division MAC (ACD-MAC)**: This protocol dynamically adjusts the division between control and service channels based on network conditions, enhancing communication performance in high-mobility UAV networks.

**Non-Orthogonal Multiple Access (NOMA)**: NOMA allows multiple UAVs to share the same frequency band by superimposing signals at different power levels, increasing spectrum efficiency and system capacity.


**Line-of-Sight (LoS)-Based Allocation**: Channel resources can be allocated based on the probability of establishing a LoS link between UAVs and ground stations, optimizing communication quality.


**Dynamic Channel Selection**: UAVs can employ dynamic channel selection methods to mitigate interference and jamming, ensuring robust communication links during critical operations. 


## **6. Expected deliverables.**
We'll have a simulator built with **NS3** and **OMNET++** for drones that will be capable of testing different protocols and channel allocation for wireless networks. 



 
