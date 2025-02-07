# **CSC466 Group Project: Optimal Routing Protocol and Deployment Strategy for Multi-UAV Relay Networks**
# YoungHyo Kim,Jon Edwards
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

### **3) (Optional)AI-Based Network Optimization**  
- To achieve **real-time adaptive routing and deployment**, this research will incorporate **AI-based optimization techniques**.  
- This study explores **Reinforcement Learning, Machine Learning, or Deep Learning approaches** for UAV network optimization.  
- Why AI is necessary for UAV network optimization:  
  - Traditional algorithms are **static and predefined**, while AI-based approaches can **continuously learn and adapt** to real-time changes in network topology.  
  - **Self-reconfigurable UAV Networks** enable autonomous decision-making for deployment and routing, improving **network efficiency and reliability**.  



## **3. Problems**
While multi-UAV relay networks offer a powerful alternative for establishing communication in environments lacking traditional infrastructure, they have several limitations compared to base station (BS)-based networks.

First, UAV networks suffer from capacity-limited wireless backhaul, which restricts the transmission rate when UAVs connect to a base station​The_Optimal_Placement_f…. Unlike terrestrial networks with fixed fiber-optic backhaul, UAV networks rely on wireless relays, meaning that as the number of hops increases, overall network performance may degrade due to accumulated delays and bandwidth limitations.

Second, UAV networks are more vulnerable to environmental factors such as wind, precipitation, and obstacles, unlike fixed ground base stations. These environmental challenges lead to higher path loss and increased interference, significantly affecting network performance. In urban environments with dense buildings or areas with high radio interference, signal degradation can be severe, limiting the network’s reliability.


## **4. What has been done.**

-why are they not sufficient


## **5. Expected deliverables.**
We'll have a simulator for drones that will be capable of testing different protocols and channel allocation for wifi, transmittion. 

## **6Biweekly Schedule**
#### week 2 reseach plan
#### week 4 prototype of simulator
#### week 6 fully functional simulation, plus data collection 
#### **week 8 final report**





What am I doing?
