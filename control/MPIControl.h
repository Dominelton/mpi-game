/* 
 * File:   MPIControl.h
 * Author: wander
 *
 * Created on March 11, 2015, 9:00 PM
 */

#ifndef MPICONTROL_H
#define	MPICONTROL_H

#include "mpi.h"
#include "../model/NPC.h"
#include <vector>

#include "../include/rapidjson/document.h"
#include "../include/rapidjson/writer.h"
#include "../include/rapidjson/stringbuffer.h"

class MPIControl {
public:
    MPIControl();
    MPIControl(bool);
    MPIControl(const MPIControl& orig);
    virtual ~MPIControl();
    
    void sendNPCs(std::vector<NPC*>);
    std::vector<NPC*> receiveNPCs();
    
    void sendLoopTime(long int, long int);
    long int receiveLoopTimeSec();
    long int receiveLoopTimeNSec();
    
private:
    const static int DEFAULT_PROCESS_RANK = 0;
    const static int NPCS_MESSAGE_ID = 1;
    const static int LOOPTIME_SEC_MESSAGE_ID = 2;
    const static int LOOPTIME_NSEC_MESSAGE_ID = 3;
    
    MPI::Intercomm startServer();
    MPI::Intercomm startClient();
    
    const char* openPort();
    void writePortNameToFile(const char*);
    const char* readPortNameFromFile();
    
    MPI::Intercomm acceptConnection(const char*);
    MPI::Intercomm connectToServer(const char*);
    
    void serializeNPCs(std::vector<NPC*>, rapidjson::Writer<rapidjson::StringBuffer>&);
    std::vector<NPC*> deserializeNPCs(rapidjson::Document&);
    
    std::string receiveMPIStringMessage(int);
    void sendMPIStringMessage(std::string, int);
    
    long int receiveMPILongMessage(int);
    void sendMPILongMessage(long int, int);
    
    MPI::Intercomm intercomm;
    
};

#endif	/* MPICONTROL_H */

