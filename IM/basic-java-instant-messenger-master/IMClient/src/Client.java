/*

Big shout out to haxxorsid for his basic java instant messenger at the following link:
https://github.com/haxxorsid/basic-java-instant-messenger
For setting up the framework of this IM service

*/
import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.EOFException;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import javax.swing.JOptionPane;
import java.util.Calendar;
import java.text.SimpleDateFormat;
import java.io.File;
import java.io.BufferedWriter;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

public class Client extends JFrame{ 
 private JTextField userMessage;
 private JTextArea chatBox;
 private ObjectOutputStream output;
 private ObjectInputStream input;
 private String message = "";
 private String serverIP;
 private Socket connection;

 public static final String DATE_FORMAT_NOW = "yyyy_MM_dd_HH_mm_ss";
 String userName = "Default";
 long messageCount = 0;
 File chatLog = new File("E:\\BIMA\\ChatHistory\\" + now());
 BufferedWriter outputText = null;
 outputText = new BufferedWriter(new FileWriter(file));
 
 public static String now() 
 {
   Calendar cal = Calendar.getInstance();
   SimpleDateFormat sdf = new SimpleDateFormat(DATE_FORMAT_NOW);
   return sdf.format(cal.getTime());
}
 
 public Client(String host) {
  super("Client!");
  serverIP = host;
  userName = JOptionPane.showInputDialog("What is your chosen user name?");
  userMessage = new JTextField();
  userMessage.setEditable(false);
  userMessage.addActionListener(new ActionListener() {
   public void actionPerformed(ActionEvent event) {
    sendMessage(event.getActionCommand(), userName);
    userMessage.setText("");
   }
  });
  add(userMessage, BorderLayout.NORTH);
  chatBox = new JTextArea();
  add(new JScrollPane(chatBox), BorderLayout.CENTER);
  setSize(300, 180);
  setVisible(true);
 }

 public void startRunning() {

  try {
   connectToServer();
   setupStreams();
   whileChatting();
  } catch (EOFException eofException) {
   showMessage("\n Client terminated the connection");

  } catch (IOException ioException) {
   ioException.printStackTrace();
  } finally {
   closeCrap();
  }
 }

 private void connectToServer() throws IOException {
  showMessage("Attempting connection");
  connection = new Socket(InetAddress.getByName(serverIP), 6789);
  showMessage("\nConnected to" + connection.getInetAddress().getHostName());

 }

 private void setupStreams() throws IOException {
  output = new ObjectOutputStream(connection.getOutputStream());
  output.flush();
  input = new ObjectInputStream(connection.getInputStream());
  showMessage("\nStreams are now good to go!");

 }

 private void whileChatting() throws IOException {
  ableToType(true);
  do {
   try {
    message = (String) input.readObject();
    showMessage("\n" + message);
    messageCount++;

   } catch (ClassNotFoundException classNotFoundException) {
    showMessage("\nDont know ObjectType!");
   }
  } while (!message.equals("\nADMIN - END"));
 }

 private void closeCrap() {
  showMessage("\nClosing down!");
  ableToType(false);
  try {
   output.close();
   input.close();
   connection.close();
  } catch (IOException ioException) {
   ioException.printStackTrace();
  }
 }
 
 private void sendMessage(String message, String userName){
  try{
   output.writeObject(userName+ " - "+ message);
   output.flush();
   showMessage("\n" + userName+ " - "+message);
  }catch(IOException ioException){
   chatBox.append("\nSomething is messed up!");
  }
  
 }
 
 private void showMessage(final String m){
  SwingUtilities.invokeLater(new Runnable(){
   public void run(){
    chatBox.append(m);
   }
  });
 }
 private void ableToType(final boolean tof){
  SwingUtilities.invokeLater(new Runnable(){
   public void run(){
    userMessage.setEditable(tof);
   }
  });
 }
}
