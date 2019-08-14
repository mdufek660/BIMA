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
import java.util.Arrays; 
import java.io.*;
import java.io.FileWriter;

public class HC05 {

    boolean scanFinished = false;
    RemoteDevice hc05device;
    String hc05Url;
    int input = -1;
    String messageNumber = "|0";
    String fileNumber = "0.txt";
    byte[] inputData = new byte[1023];
    byte[] oldInputData = new byte[1023];
    String inputString = "";
    String[] parsedInput;
    boolean continueRead = true;
    String logStoragePath = "E:\\BIMA\\logs\\";
    String outputString = "";

    public static void main(String[] args) {
        try {
            new HC05().go();
        } catch (Exception ex) {
            Logger.getLogger(HC05.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void go() throws Exception {
        //scan for all devices:
        scanFinished = false;
        LocalDevice.getLocalDevice().getDiscoveryAgent().startInquiry(DiscoveryAgent.GIAC, new DiscoveryListener() {
            @Override
            public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                try {
                    String name = btDevice.getFriendlyName(false);
                    System.out.format("%s (%s)\n", name, btDevice.getBluetoothAddress());
                    if (name.matches("HC.*")) {
                        hc05device = btDevice;
                        System.out.println("got it!");
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }

            @Override
            public void inquiryCompleted(int discType) {
                scanFinished = true;
            }

            @Override
            public void serviceSearchCompleted(int transID, int respCode) {
            }

            @Override
            public void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
            }
        });
        while (!scanFinished) {
            //this is easier to understand (for me) as the thread stuff examples from bluecove
            Thread.sleep(500);
        }

        //search for services:
        UUID uuid = new UUID(0x1101); //scan for btspp://... services (as HC-05 offers it)
        UUID[] searchUuidSet = new UUID[]{uuid};
        int[] attrIDs = new int[]{
            0x0100 // service name
        };
        scanFinished = false;
        LocalDevice.getLocalDevice().getDiscoveryAgent().searchServices(attrIDs, searchUuidSet,
                hc05device, new DiscoveryListener() {
                    @Override
                    public void deviceDiscovered(RemoteDevice btDevice, DeviceClass cod) {
                    }

                    @Override
                    public void inquiryCompleted(int discType) {
                    }

                    @Override
                    public void serviceSearchCompleted(int transID, int respCode) {
                        scanFinished = true;
                    }

                    @Override
                    public void servicesDiscovered(int transID, ServiceRecord[] servRecord) {
                        for (int i = 0; i < servRecord.length; i++) {
                            hc05Url = servRecord[i].getConnectionURL(ServiceRecord.NOAUTHENTICATE_NOENCRYPT, false);
                            if (hc05Url != null) {
                                break; //take the first one
                            }
                        }
                    }
                });

        while (!scanFinished) {
            Thread.sleep(500);
        }

        System.out.println(hc05device.getBluetoothAddress());
        System.out.println(hc05Url);

        //if you know your hc05Url this is all you need:
        StreamConnection streamConnection = (StreamConnection) Connector.open(hc05Url);
        OutputStream os = streamConnection.openOutputStream();
        InputStream is = streamConnection.openInputStream();
        while(continueRead == true)
        {
          System.out.println("enter");
          while(true)
          {
            System.out.println("reading");
            while(is.available() <1);
            {
              Thread.sleep(200);
            }
            System.out.println("Received");
            is.read(inputData);
            System.out.println("Checking arrays");
            if(Arrays.equals(inputData, oldInputData)==true)
            {
              System.out.println("Arrays weren't the same!");
              outputString = "";
              inputString = new String(inputData);
              parsedInput = parseInput(inputString);
              String nextBreak = "|";
              int i = 1;
              System.out.println("Parsing input");
              while(i<parsedInput[2].length())
              {
                nextBreak += parsedInput[2].charAt(i);
                i++;
              }
              
              
              String logPath = logStoragePath + parsedInput[2];
              File conversation = new File(logPath);
              
              System.out.println("Checking if file exists");
              if(conversation.exists())
              {       
                System.out.println("File");         
                BufferedReader reader = new BufferedReader(new FileReader(logPath));
                String line = reader.readLine();
                while(line!=null)
                {
                  if(parsedInput[2].equals(line))
                  {
                    while(!(nextBreak.equals(line)))
                    {
                      outputString += line;
                      line = reader.readLine();
                    }
                    System.out.println(outputString);
                  }
                }
                i = 0;
                byte[] outStringBytes = outputString.getBytes();
                while(i<outputString.length())
                {
                  os.write(outStringBytes[i]);
                  Thread.sleep(500);
                  i++;
                }
                
                
              }
              
              oldInputData = inputData.clone();
            }
            Thread.sleep(10);
           
          }
        }
        
              
              
              
//        System.out.println("printing 1");
//        os.write("1".getBytes()); //just send '1' to the device
//        System.out.println("sleepy");
//        Thread.sleep(5000);
//        System.out.println("printing 0");
//        os.write("0".getBytes());
        os.close();
        is.close();
        streamConnection.close();
    }
    
    private String[] parseInput(String in)
    {
      boolean flag = false;
      String temp = "";
      char c = '0';
      int counter=2;
      parsedInput[0] = Character.toString(in.charAt(0)); //grab the first parameter, the decision to change message or chat log
      
      temp += in.charAt(2);//begin constructing second parameter
      while(flag == false)//this loop finishes the second parameter by looking for the next space after the |
      {
        counter++;
        temp+= in.charAt(counter);
        c = in.charAt(counter+1);
        if(!((c=='0')||(c=='1')||(c=='2')||(c=='3')||(c=='4')||(c=='5')||(c=='6')||(c=='7')||(c=='8')||(c=='9')))//Exits on the space after the number
        {
          flag = true;
        }
      }
      
      flag = false;
      parsedInput[1] = temp;
      temp = "";
      
      while(flag = false)
      {
        counter++;
        temp+=in.charAt(counter);
        c = in.charAt(counter+1);
        
        if(!((c=='0')||(c=='1')||(c=='2')||(c=='3')||(c=='4')||(c=='5')||(c=='6')||(c=='7')||(c=='8')||(c=='9')))
        {
          flag = true;
          temp = temp + ".txt";
        }
      }
      
      parsedInput[2] = temp;
      return(parsedInput);
    }
}