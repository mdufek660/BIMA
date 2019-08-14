import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.bluetooth.DeviceClass;
import javax.bluetooth.DiscoveryAgent;
import javax.bluetooth.DiscoveryListener;
import javax.bluetooth.LocalDevice;
import javax.bluetooth.RemoteDevice;
import javax.bluetooth.ServiceRecord;
import javax.bluetooth.UUID;
import javax.microedition.io.Connector;
import javax.microedition.io.StreamConnection;


public class TextParser 
{

  boolean scanFinished = false;
  String hc05url = "btspp://98D341FD44FD:1;authenticae=false;encrypt=false;master=false";
  String logLocation = "E\\BIMA\\logs\\";
  boolean inputDetected=false;
  String textToSend="";
  int logNumber = 0;
  int messageNumber = 0;
  byte[] inputFromArduino = new byte[200];
  

public static void main(String[] args) 
{
  try 
  {
    new TextParser().go();
  } 
  catch (Exception ex) 
  {
    Logger.getLogger(TextParser.class.getName()).log(Level.SEVERE, null, ex);
  }
}

private void go() throws Exception 
{
  StreamConnection streamConnection = (StreamConnection) Connector.open(hc05url);
  OutputStream os = streamConnection.openOutputStream();
  InputStream is = streamConnection.openInputStream();
  //while(!(is.available()==)
  {
    Thread.sleep(200);
  }
  /*os.write("1".getBytes()); //'1' means ON and '0' means OFF
  os.close();
  byte[] b = new byte[200];
  Thread.sleep(200);
  is.read(b);
  is.close();
  streamConnection.close();
  System.out.println("received " + new String(b));*/
}

private String[] inputParser(String in)
{
  
}


}
