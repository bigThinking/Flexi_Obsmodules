//Class obtained by modifying Flat_NetworkConnector from INET framework, in order to work with Flexi_OBS.
//Changed bare minimum required for operation
//Assigns IP addresses to all nodes and gets k shortest paths

#include "Flexi_FlatNetworkConfigurator.h"

Define_Module(Flexi_FlatNetworkConfigurator);

void Flexi_FlatNetworkConfigurator::initialize(int stage)
{
    if (stage==2)
    {
        fillCoreNodeTables = par("fillCoreNodeTables");
        maxNumberOfShortestPaths = par("k");
        fillIpTrafGenAddresses = par("fillIpTrafGenAddresses");
        startTime = clock();
        Flexi_WeightedTopology topo("topo");
        NodeInfoVector nodeInfo; // will be of size topo.nodes[]

        // extract topology into the cTopology object, then fill in
        // isIPNode, rt and ift members of nodeInfo[]
        extractTopology(topo, nodeInfo);

        // assign addresses to IPv4 nodes, and also store result in nodeInfo[].address
        assignAddresses(topo, nodeInfo);

        // add default routes to hosts (nodes with a single attachment);
        // also remember result in nodeInfo[].usesDefaultRoute
        //addDefaultRoutes(topo, nodeInfo);

        // calculate shortest paths, and add corresponding static routes
        fillShortestPathRoutingTables(topo, nodeInfo);

        // update display string
        setDisplayString(topo, nodeInfo);

        printElapsedTime("", startTime);
    }
}

void Flexi_FlatNetworkConfigurator::extractTopology(cTopology& topo, NodeInfoVector& nodeInfo)
{
    // extract topology
    topo.extractByProperty("node");
    EV << "cTopology found " << topo.getNumNodes() << " nodes\n";

    // fill in isIPNode, ift and rt members in nodeInfo[]
    nodeInfo.resize(topo.getNumNodes());
    for (int i=0; i<topo.getNumNodes(); i++)
    {
        cModule *mod = topo.getNode(i)->getModule();


        nodeInfo[i].isIPNode = mod->getProperties()->getAsBool("networkNode");
        if (nodeInfo[i].isIPNode)
        {
            //nodeInfo[i].rt = (IRoutingTable*)L3AddressResolver().routingTableOf(mod);
            nodeInfo[i].ift = L3AddressResolver().interfaceTableOf(mod);
            //nodeInfo[i].ipForwardEnabled = mod->hasPar("forwarding") ? mod->par("forwarding").boolValue() : false;
            nodeInfo[i].ipForwardEnabled = false;
        }

        //        nodeInfo[i].ipForwardEnabled = mod->hasPar("IPForward") ? mod->par("IPForward").boolValue() : false;
        topo.getNode(i)->setWeight(nodeInfo[i].ipForwardEnabled ? 0.0 : INFINITY);
    }
}

void Flexi_FlatNetworkConfigurator::assignAddresses(cTopology& topo, NodeInfoVector& nodeInfo)
{
    // assign IPv4 addresses
    uint32 networkAddress = Ipv4Address(par("networkAddress").stringValue()).getInt();
    uint32 netmask = Ipv4Address(par("netmask").stringValue()).getInt();
    int maxNodes = (~netmask)-1;  // 0 and ffff have special meaning and cannot be used
    if (topo.getNumNodes()>maxNodes)
        error("netmask too large, not enough addresses for all %d nodes", topo.getNumNodes());

    int numIPNodes = 0;
    for (int i=0; i<topo.getNumNodes(); i++)
    {
        // skip bus types
        if (!nodeInfo[i].isIPNode)
            continue;

        uint32 addr = networkAddress | uint32(++numIPNodes);
        nodeInfo[i].address.set(addr);

        // find interface table and assign address to all (non-loopback) interfaces
        IInterfaceTable *ift = nodeInfo[i].ift;
        for (int k=0; k<ift->getNumInterfaces(); k++)
        {
            InterfaceEntry *ie = ift->getInterface(k);
            if (!ie->isLoopback())
            {
                ie->addProtocolDataIfAbsent<Ipv4InterfaceData>()->setIPAddress(Ipv4Address(addr));
                ie->getProtocolData<Ipv4InterfaceData>()->setNetmask(Ipv4Address::ALLONES_ADDRESS);    // full address must match for local delivery
            }
        }
    }

    //set IPTRAFGEN Addresses
    if(fillIpTrafGenAddresses){
        for (int i=0; i<topo.getNumNodes(); i++)
        {
            // skip bus types
            if (!nodeInfo[i].isIPNode)
                continue;

            string destAddresses = "";
            IInterfaceTable *ift = nodeInfo[i].ift;
            InterfaceEntry *ie = ift->getInterface(0);
            Ipv4Address addr = ie->addProtocolDataIfAbsent<Ipv4InterfaceData>()->getIPAddress();

            for(int j =0; j < topo.getNumNodes(); j++)
            {
                if (!nodeInfo[j].isIPNode || i ==j)
                    continue;

                IInterfaceTable *ift = nodeInfo[j].ift;
                InterfaceEntry *ie = ift->getInterface(0);
                //IPv4Address addr = ie->ipv4Data()->getIPAddress();
                Ipv4Address addr = nodeInfo[j].address;
                destAddresses = destAddresses + addr.str(false) + " ";
            }

            cModule *mod = topo.getNode(i)->getModule();
            mod->getSubmodule("iPvXTrafGen")->par("destAddresses").setStringValue(destAddresses);
        }
    }
}

void Flexi_FlatNetworkConfigurator::addDefaultRoutes(cTopology& topo, NodeInfoVector& nodeInfo)
{
    // add default route to nodes with exactly one (non-loopback) interface
    for (int i=0; i<topo.getNumNodes(); i++)
    {
        cTopology::Node *node = topo.getNode(i);

        // skip bus types
        if (!nodeInfo[i].isIPNode)
            continue;

        IInterfaceTable *ift = nodeInfo[i].ift;
        IRoutingTable *rt = nodeInfo[i].rt;

        // count non-loopback interfaces
        int numIntf = 0;
        InterfaceEntry *ie = NULL;
        for (int k=0; k<ift->getNumInterfaces(); k++)
            if (!ift->getInterface(k)->isLoopback())
            {ie = ift->getInterface(k); numIntf++;}

        nodeInfo[i].usesDefaultRoute = (numIntf==1);
        if (numIntf!=1)
            continue; // only deal with nodes with one interface plus loopback

        EV << "  " << node->getModule()->getFullName() << "=" << nodeInfo[i].address
                << " has only one (non-loopback) interface, adding default route\n";

        // add route
        Ipv4Route *e = new Ipv4Route();
        e->setDestination(Ipv4Address());
        e->setNetmask(Ipv4Address());
        e->setInterface(ie);
        e->setSourceType(IRoute::MANUAL);
        //e->getMetric() = 1;
        rt->addRoute(e);
    }
}

//see FlatNetworkConfigurator in inet framework for strict shortestpath
void Flexi_FlatNetworkConfigurator::fillShortestPathRoutingTables(cTopology& _topo, NodeInfoVector& nodeInfo)
{
    Flexi_WeightedTopology &topo = (Flexi_WeightedTopology &)_topo;
    vector<Flexi_WeightedTopology::Path*> routes;

    // fill in routing tables with shortest paths
    for (int i=0; i<topo.getNumNodes(); i++)
    {
        // skip bus types
        if (!nodeInfo[i].isIPNode)
            continue;

        cTopology::Node *srcNode = topo.getNode(i);

        if (srcNode->getNumOutLinks()==0)
            continue; // not conected

        Ipv4Address srcAddr = nodeInfo[i].address;
        std::string srcModName = srcNode->getModule()->getFullName();

        for(int j=i+1; j<topo.getNumNodes(); j++)
        {
            if (!nodeInfo[j].isIPNode)
                continue;

            cTopology::Node *destNode = topo.getNode(j);
            Ipv4Address destAddr = nodeInfo[j].address;
            std::string destModName = destNode->getModule()->getFullName();

            // calculate shortest paths from srcNode to destNode
            vector<Flexi_WeightedTopology::Path*> A  = topo.YensKShortestPathAlg(i, j, maxNumberOfShortestPaths, srcAddr.getInt(), destAddr.getInt());
            for(int k=0; k < A.size(); k++)
                routes.push_back(A[k]);
        }
    }

    for(int i = 0; i < topo.getNumNodes(); i++)
    {
        if (!nodeInfo[i].isIPNode)
            continue;

        int addr = nodeInfo[i].address.getInt();
        K_ShortestPathTable *table = check_and_cast<K_ShortestPathTable *>(topo.getNode(i)->getModule()->getSubmodule("k_ShortestPathTable"));

        for(int j = 0; j < routes.size(); j++)
        {

            Flexi_WeightedTopology::Path* path = routes[j];
            if(path->srcAddr == addr)//addr is src
            {
                K_ShortestPathTableEntry *entry = new K_ShortestPathTableEntry();
                entry->setId((std::to_string(addr) + "-" + std::to_string(j)).c_str());
                entry->setSrcAddress(addr);
                entry->setDestAddress(path->destAddr);
                entry->setCost(path->Cost);
                entry->setPathArraySize(path->pathGates.size());
                entry->setPathNodesArraySize(path->orderedNodes.size());

                int counter = 0;
                for(int k = 0; k < path->pathGates.size(); k++)
                    entry->setPath(counter++, path->pathGates[k]);

                counter = 0;
                for(int k = 0; k < path->orderedNodes.size(); k++)
                    entry->setPathNodes(counter++, path->orderedNodes[k]->getModule()->getFullName());

                table->addEntry(entry);

            }else if(path->destAddr == addr)//addr is dest
            {
                K_ShortestPathTableEntry *entry = new K_ShortestPathTableEntry();
                entry->setId((std::to_string(addr) + "-" + std::to_string(j)).c_str());
                entry->setSrcAddress(addr);
                entry->setDestAddress(path->srcAddr);
                entry->setCost(path->Cost);
                entry->setPathArraySize(path->pathGates.size());
                entry->setPathNodesArraySize(path->orderedNodes.size());

                int counter = 0;
                for(int k = path->pathGates.size()-1; k >= 0; k--)
                    entry->setPath(counter++,  path->pathGates[k]);

                counter = 0;
                for(int k = path->orderedNodes.size()-1; k >= 0; k--)
                   entry->setPathNodes(counter++,  path->orderedNodes[k]->getModule()->getFullName());

                table->addEntry(entry);
            }
        }
    }

    if(fillCoreNodeTables)
    {
        for (int i=0; i<topo.getNumNodes(); i++)
        {
            // skip ipnodes types
            if (nodeInfo[i].isIPNode)
                continue;

            cTopology::Node *srcNode = topo.getNode(i);

            if (srcNode->getNumOutLinks()==0)
                continue; // not conected

            std::string srcModName = srcNode->getModule()->getFullName();

            for(int j=0; j<topo.getNumNodes(); j++)
            {
                if (!nodeInfo[j].isIPNode)
                    continue;

                cTopology::Node *destNode = topo.getNode(j);
                Ipv4Address destAddr = nodeInfo[j].address;
                std::string destModName = destNode->getModule()->getFullName();

                if(destNode->getNumInLinks() == 0)
                    continue;

                // calculate shortest paths from srcNode to destNode
                vector<Flexi_WeightedTopology::Path*> A = topo.YensKShortestPathAlg(i, j, maxNumberOfShortestPaths, 0, destAddr.getInt());
                K_ShortestPathTable *table = check_and_cast<K_ShortestPathTable *>(topo.getNode(i)->getModule()->getSubmodule("k_ShortestPathTable"));

                //output A
                for(int k = 0; k < A.size(); k++)//for each path in A
                {
                    K_ShortestPathTableEntry *entry = new K_ShortestPathTableEntry();
                    entry->setSrcAddress(0);
                    entry->setDestAddress(destAddr.getInt());
                    entry->setCost(A[k]->Cost);
                    entry->setPathArraySize(A[k]->pathGates.size());
                    entry->setPathNodesArraySize(A[k]->orderedNodes.size());

                    int counter = 0;
                    for(int l = A[k]->pathGates.size()-1; l >= 0; l--)
                       entry->setPath(counter++,  A[k]->pathGates[l]);

                    counter = 0;
                    for(int l = A[k]->orderedNodes.size()-1; l >= 0; l--)
                        entry->setPathNodes(counter++,  A[k]->orderedNodes[l]->getModule()->getFullName());

                    table->addEntry(entry);
                }
            }
        }
    }
}

void Flexi_FlatNetworkConfigurator::handleMessage(cMessage *msg)
{
    error("this module doesn't handle messages, it runs only in initialize()");
}

void Flexi_FlatNetworkConfigurator::setDisplayString(cTopology& topo, NodeInfoVector& nodeInfo)
{
    int numIPNodes = 0;
    for (int i=0; i<topo.getNumNodes(); i++)
        if (nodeInfo[i].isIPNode)
            numIPNodes++;

    // update display string
    char buf[80];
    sprintf(buf, "%d IPv4 nodes\n%d non-IPv4 nodes", numIPNodes, topo.getNumNodes()-numIPNodes);
    getDisplayString().setTagArg("t", 0, buf);
}

void Flexi_FlatNetworkConfigurator::printTimeSpentUsingDuration(const char *name, long duration)
{
    EV << "Time spent in Flexi_FlatNetworkConfigurator::" << name << ": " << ((double)duration / CLOCKS_PER_SEC) << "s" << endl;
}

void Flexi_FlatNetworkConfigurator::printElapsedTime(const char *name, long startTime)
{
    printTimeSpentUsingDuration(name, clock() - startTime);
}

void Flexi_FlatNetworkConfigurator::fillRoutingTables(cTopology& _topo, NodeInfoVector& nodeInfo)
{
    Flexi_WeightedTopology &topo = (Flexi_WeightedTopology &)_topo;
    // fill in routing tables with static routes
    for (int i=0; i<topo.getNumNodes(); i++)
    {
        cTopology::Node *destNode = topo.getNode(i);

        // skip bus types
        if (!nodeInfo[i].isIPNode)
            continue;

        Ipv4Address destAddr = nodeInfo[i].address;
        std::string destModName = destNode->getModule()->getFullName();

        // calculate shortest paths from everywhere towards destNode
        topo.calculateWeightedSingleShortestPathsTo(destNode);

        // add route (with host=destNode) to every routing table in the network
        // (excepting nodes with only one interface -- there we'll set up a default route)
        for (int j=0; j<topo.getNumNodes(); j++)
        {
            if (i==j) continue;
            if (!nodeInfo[j].isIPNode)
                continue;

            cTopology::Node *atNode = topo.getNode(j);
            if (atNode->getNumPaths()==0)
                continue; // not connected
            if (nodeInfo[j].usesDefaultRoute)
                continue; // already added default route here

            Ipv4Address atAddr = nodeInfo[j].address;

            IInterfaceTable *ift = nodeInfo[j].ift;

            int outputGateId = atNode->getPath(0)->getLocalGate()->getId();
            InterfaceEntry *ie = ift->findInterfaceByNodeOutputGateId(outputGateId);
            if (!ie)
                error("%s has no interface for output gate id %d", ift->getFullPath().c_str(), outputGateId);

            EV << "  from " << atNode->getModule()->getFullName() << "=" << Ipv4Address(atAddr);
            EV << " towards " << destModName << "=" << Ipv4Address(destAddr) << " interface " << ie->getInterfaceName() << endl;

            // add route
            IRoutingTable *rt = nodeInfo[j].rt;
            Ipv4Route *e = new Ipv4Route();
            e->setDestination(Ipv4Address());
            e->setNetmask(Ipv4Address());
            e->setInterface(ie);
            e->setSourceType(IRoute::MANUAL);
            //e->getMetric() = 1;
            rt->addRoute(e);
        }
    }
}

//for(int j=0; j<topo.getNumNodes(); j++)
//           {
//               if (!nodeInfo[j].isIPNode)
//                   continue;
//
//               cTopology::Node *destNode = topo.getNode(j);
//               Ipv4Address destAddr = nodeInfo[j].address;
//               std::string destModName = destNode->getModule()->getFullName();
//
//               if(destNode->getNumInLinks() == 0)
//                   continue;
//
//               // calculate shortest paths from srcNode to destNode
//               vector<Flexi_WeightedTopology::Path*> A = topo.YensKShortestPathAlg(i, j, maxNumberOfShortestPaths, 0, destAddr.getInt());
//               K_ShortestPathTable *table = check_and_cast<K_ShortestPathTable *>(topo.getNode(i)->getModule()->getSubmodule("k_ShortestPathTable"));
//
//               vector<vector<double>> paths;
//               //output A
//               for(int k = 0; k < A.size(); k++)//for each path in A
//               {
//                   vector<cTopology::Node*> pathNodes = A[i]->orderedNodes;
//
//                   K_ShortestPathTableEntry *entry = new K_ShortestPathTableEntry();
//                   entry->setSrcAddress(0);
//                   entry->setDestAddress(destAddr.getInt());
//
//                   entry->setCost(A[i]->Cost);
//                   int pathPos = 0;
//
//                   entry->setPathNodesArraySize(pathNodes.size());
//
//                   for(int j =0; j < pathNodes.size()-1; j++)//for each node in pathNodes
//                   {
//                       entry->setPathArraySize(pathNodes.size()*2);
//                       cTopology::Node* node = pathNodes[j];
//                       for(int k = 0; k < node->getNumOutLinks(); k++)//for each outlink in node
//                       {
//                           if(node->getLinkOut(k)->getRemoteNode() == pathNodes[j+1])
//                           {
//                               entry->setPath(pathPos++, node->getLinkOut(k)->getLocalGateId());
//                               entry->setPath(pathPos++, node->getLinkOut(k)->getRemoteGateId());
//                           }
//                       }
//
//                       entry->setPathNodes(j, node->getModule()->getFullName());
//                   }
//
//                   table->addEntry(entry);
//               }
//           }
