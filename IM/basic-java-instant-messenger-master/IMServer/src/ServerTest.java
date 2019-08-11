/*

Big shout out to haxxorsid for his basic java instant messenger at the following link:
https://github.com/haxxorsid/basic-java-instant-messenger
For setting up the framework of this IM service

*/

import javax.swing.JFrame;
public class ServerTest {

 public static void main(String[] args) {
  // TODO Auto-generated method stub
  Server admin = new Server();
  admin.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
  admin.startRunning();
 }

}
