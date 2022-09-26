#include "painlessMesh.h"
#include <Arduino_JSON.h>

#define   MESH_PREFIX     "Ade" 
#define   MESH_PASSWORD   "Ade123" 
#define   MESH_PORT       5555 

int dest = 2128163901;
int Node = 1;
//int i = 0;
String temp_readings;

Scheduler userScheduler; 
painlessMesh  mesh;

//void sendMessage() ; 
String obtain_readings(); 

unsigned long startMillis;
unsigned long currentMillis;
//Task taskSendMessage(TASK_SECOND * 5 , TASK_FOREVER, &sendMessage);

String obtain_readings (int i) {
  JSONVar jsonReadings; 
  jsonReadings["Node"] = Node;
  jsonReadings["Temperature"] = i ;
  temp_readings = JSON.stringify(jsonReadings);
  return temp_readings;
}

void sendMessage (int i) {
//  for ( i = 0; i <5 ; i++){
  String msg = obtain_readings(i);
  mesh.sendSingle(dest,msg);
  Serial.print("send " + msg);
  Serial.println(" to " + String(dest));
//  }
}


void receivedCallback( uint32_t dest, String &msg ) {
//  Serial.printf("Received from %u msg=%s\n", dest, msg.c_str());
//  JSONVar json_object = JSON.parse(obtain_readings());
//  int node = json_object["Node"];
//  double temp = json_object["Temperature"];
//  Serial.print("Node: ");
//  Serial.println(node);
//  Serial.print("Temperature: ");
//  Serial.print(temp);
//  Serial.println(" C");
}

void newConnectionCallback(uint32_t nodeId) {
  Serial.printf("New Connection, nodeId = %u\n", nodeId);
}

void changedConnectionCallback() {
  Serial.printf("Changed connections\n");
}

void nodeTimeAdjustedCallback(int32_t offset) {
  Serial.printf("Adjusted time %u. Offset = %d\n", mesh.getNodeTime(),offset);
}

//void sendSingle(uint32_t dest, String &msg){
//if(dest == 3624435125){
//sendSingle (dest, msg);
//Serial.println("destination node 3");
//}else{
//  Serial.println("unknown destination");
//  //Message is for this nodeID so process it
//}
//
//}



void setup() {
  Serial.begin(115200);

  int i = 0;
  
  
  mesh.setDebugMsgTypes( ERROR | STARTUP );  
  mesh.init( MESH_PREFIX, MESH_PASSWORD, &userScheduler, MESH_PORT );
  mesh.onReceive(&receivedCallback);
  mesh.onNewConnection(&newConnectionCallback);
  mesh.onChangedConnections(&changedConnectionCallback);
  mesh.onNodeTimeAdjusted(&nodeTimeAdjustedCallback);

//  userScheduler.addTask(taskSendMessage);
//  taskSendMessage.enable();
startMillis = millis();
}

int i = 0;

void loop() {
  
   mesh.update();
//  String msg = obtain_readings();
//  sendSingle(3624435125,msg);
currentMillis = millis();
if(i < 1000){
  if (currentMillis - startMillis >= 1000){
    sendMessage(i);
    i++;
    startMillis = currentMillis;
  }
Serial.printf("New Connection, nodeId = %u\n", nodeId);

// delay(5000);
}
}
