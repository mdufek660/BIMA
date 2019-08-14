/*

Big shout out to haxxorsid for his basic java instant messenger at the following link:
https://github.com/haxxorsid/basic-java-instant-messenger
For setting up the framework of this IM service

*/

import javax.swing.JFrame;
public class ClientTest {
 public static void main(String[] args) {
  Client user;
  int number = 1;
  user = new Client("127.0.0." + number);
  user.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
  user.startRunning();
 }
}
