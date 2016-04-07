String motorExecute(){
  if(motorStatus()){
    while(true){
      if(topSensor() <= maxTopLevel){
        statusChange();
        return"Motor Turned OFF :: Water Tank Full";
      }
      else if(topSensor() > maxTopLevel){
        if(downSensor() >= minDownLevel){
          statusChange();
          return "Motor Turned OFF :: Reservior empty";
        }
        else{
          return "Motor Turned ON :: Everything Normal";
        }
      }
      else if(!motorStatus()){
        break;
      }
    }
  }
  else if(!motorStatus()){
    if(topSensor() >= minTopLevel){
      if (downSensor() < minDownLevel){
        statusChange();
        return "Motor Turned ON :: low Top water Level";
      }
      else if(downSensor() >= minDownLevel){
        return "Motor turned OFF :: Low down and top water level";
      }
    }
    else if(topSensor() < minTopLevel){
        return "Motor is OFF :: Water Tank is Full"; 
    }
  }
}
