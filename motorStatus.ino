
bool motorStatus(){
  int sensePin = A1;
  int statusValue = analogRead(sensePin);
  if (statusValue > 605){
    Serial.println("Motor is on");
    STATUS = "ON";
    return true;
  }
  else if(statusValue <= 605){
    Serial.println("Motor is off");
    STATUS = "OFF";
    return false;
  }
}

void statusChange(){
  digitalWrite(relayPin,!change);
  //wait for relay to be turned off
  delay(5000);
  change = !change; 
}
