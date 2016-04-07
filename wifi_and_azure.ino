/*

SPECIAL THANK YOU TO MOHAN

This code connects to Azure IoT Hub and blinks the onboard LED on the MKR1000
when there is a message for the particular device.

Written by Mohan Palanisamy (http://mohanp.com)

Instructions are here to properly set up the MKR1000 for SSL connections.
http://mohanp.com/mkr1000-azure-iot-hub-how-to/
Feb 19, 2016
*/


void updateLoop() 
{
  Serial.print("started reading azure Reply");
  Serial.println(millis());
  String response = "";
  char c;
  ///read response if WiFi Client is available
  while (client.available()) {
    c = client.read();
    response.concat(c);
  }

  if (!response.equals(""))
  {
    //if there are no messages in the IoT Hub Device queue, Azure will return 204 status code. 
    if (response.startsWith("HTTP/1.1 204"))
    {
      Serial.println("Successfully Updated");
    }
    else
    {
      Serial.println("Unsuccessful update");
    }
  }
//////////////azure HTTP
   azureHttpRequest();
   Serial.print("Stoped reading azure Reply");
  Serial.println(millis());
}

// this method makes an HTTPS connection to the Azure IOT Hub Server:
void azureHttpRequest() {

  // close any connection before send a new request.
  // This will free the socket on the WiFi shield
  client.stop();

  // if there’s a successful connection:
 if (client.connect(hostname, 443)) {
 //make the GET request to the Azure IOT device feed uri
 client.print("POST "); //Do a GET
 client.print(azurePOST_Uri); // On the feedURI
 client.println(" HTTP/1.1");
 client.print("Host: ");
 client.println(hostname); //with hostname header
 client.print("Authorization: ");
 client.println(authSAS); //Authorization SAS token obtained from Azure IoT device explorer
 client.println("Connection: close");
 client.println("Content-Type: text/plain");
 client.print("Content-Length: ");
 client.println(content().length());
 client.println();
 client.println(content());
 client.println();

    // note the time that the connection was made:
    lastConnectionTime = millis();
  }
  else {
    // if you couldn't make a connection:
    Serial.println("connection failed");
  }
}

