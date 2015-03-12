/* 
 * File:   MPIControl.h
 * Author: wander
 *
 * Created on March 11, 2015, 9:00 PM
 */

#ifndef MPICONTROL_H
#define	MPICONTROL_H

#include "mpi.h"
#include "NPC.h"
#include <vector>

class MPIControl {
public:
    MPIControl();
    MPIControl(bool);
    MPIControl(const MPIControl& orig);
    virtual ~MPIControl();
    
    void sendNPCs(std::vector<NPC*>);
    std::vector<NPC*> receiveNPCs();
private:
    MPI::Intercomm startServer();
    MPI::Intercomm startClient();
    
    const char* openPort();
    void writePortNameToFile(const char* portName);
    const char* readPortNameFromFile();
    MPI::Intercomm acceptConnection(const char* port_name);
    MPI::Intercomm connectToServer(const char* port_name);
    
    
    
    MPI::Intercomm intercomm;
    
};

#endif	/* MPICONTROL_H */

