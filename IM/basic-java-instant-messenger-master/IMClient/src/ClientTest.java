import javax.swing.JFrame;
import javax.swing.JOptionPane;
public class ClientTest {
 public static void main(String[] args) {
  Client user;
  int number = 1;
  number = Integer.parseInt(JOptionPane.showInputDialog("Input a number 1-127"));
  user = new Client("127.0.0." + number);
  user.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
  user.startRunning();
 }
}
