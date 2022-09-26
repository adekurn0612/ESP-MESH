#include "painlessMesh.h"
#include <Arduino_JSON.h>

#define   MESH_PREFIX     "KAI Inovasi"
#define   MESH_PASSWORD   "KAI-2020"
#define   MESH_PORT       5555

Scheduler userScheduler; 
painlessMesh  mesh;

int dest = 624331425;

//int nodeId = ;
// int from;
// void sendmsg();
// unsigned long startMillis;
// unsigned long currentMillis;

//Task taskSendmsg( TASK_SECOND * 1 , TASK_FOREVER, &sendmsg );
//
//String obtain_readings () {
//  JSONVar jsonReadings;
//  jsonReadings["Node"] = Node;
//  jsonReadings["Temperature"] =  ;
//  temp_readings = JSON.stringify(jsonReadings);
//  return temp_readings;
//}

  
void receivedCallback(uint32_t from, String &msg ) {
  Serial.printf("Received from %u msg=%s\n", from, msg.c_str());
  JSONVar json_object = JSON.parse(msg);
  int node = json_object["Node"];
  Serial.println(from);
  // Serial.println(msg);
  mesh.sendSingle(dest,msg);
  Serial.print("send " + msg);
  Serial.println(" to " + String(dest));
}


// void sendMessage (uint32_t dest, String &msg ) {
// //  for ( i = 0; i <5 ; i++){
//   // String msg = getReadings(a);
//   // mesh.sendSingle(dest,msg);
//   // Serial.print("send " + msg);
//   // Serial.println(" to " + String(dest));
// //  }
//   Serial.printf("Send from %u msg=%s\n", dest, msg.c_str());
//   JSONVar json_object = JSON.parse(msg);
//   int node = json_object["Node"];
//   mesh.sendSingle(dest,msg);
  // Serial.print("send " + msg);
  // Serial.println(" to " + String(dest));
//   // Serial.println(from);
//   // Serial.println(msg);
// }

// void sendmsg(String node, String Temperature) {
// //  String msg = "NODE 2";
// //  msg += mesh.getNodeId();
// //  mesh.sendBroadcast( msg );
// //  taskSendmsg.setInterval( random( TASK_SECOND * 1, TASK_SECOND * 5 ));
//   // mesh.sendSingle(dest,msg);
//   Serial.println(node);
//   Serial.println(Temperature);
// }

void newConnectionCallback(uint32_t nodeId) {
    Serial.printf("New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
    Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

void setup() {
  Serial.begin(115200);
  mesh.setDebugMsgTypes( ERROR | STARTUP );  

  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

//  userScheduler.addTask( taskSendmsg );
//  taskSendmsg.enable();
}

void loop() {
  
   mesh.update();
//  String msg = obtain_readings();
//  sendSingle(3624435125,msg);
// delay(5000);
}
