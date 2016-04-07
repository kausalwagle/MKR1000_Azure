
String content(){
  String returnString = "{\"deviceId\":\"WeverIoT\",\"pumpControl\":\"";
  returnString += STATUS;
  returnString += "\",\"time\":\"123456\",\"waterlevel\":\""; // Time shold be the time stamp here, ihaven't done anything relatedto time. Update will come soon.
  returnString += String(topSensor());
  returnString += "\",\"waterRes\":\"";
  returnString += String(downSensor());
  returnString += "\",\"remarks\":\"";
  returnString += motorExecute();
  returnString += "\"}";
  return returnString;
}

