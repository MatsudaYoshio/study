import java.awt.*;
import javax.swing.*;

public class Main {
  public static void main(String[] args) {
    JFrame frame = new JFrame("Login Form");
    frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    frame.setSize(400, 200);

    Container pane = frame.getContentPane();
    pane.setLayout(new GridLayout(4, 1));

    JPanel userIdPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
    JLabel userIdLabel = new JLabel("ユーザID", JLabel.TRAILING);
    userIdPanel.add(userIdLabel);
    JTextField userIdTextField = new JTextField(20);
    userIdPanel.add(userIdTextField);

    JPanel passwordPanel = new JPanel(new FlowLayout(FlowLayout.LEFT));
    JLabel passwordLabel = new JLabel("パスワード", JLabel.TRAILING);
    passwordPanel.add(passwordLabel);
    JPasswordField paswordTextField = new JPasswordField(20);
    passwordPanel.add(paswordTextField);
    frame.add(userIdPanel);
    frame.add(passwordPanel);

    JCheckBox checkBox = new JCheckBox("パスワードを隠さない");
    checkBox.addActionListener(e -> paswordTextField.setEchoChar((char) 0));
    frame.add(checkBox);

    JDialog successDialog = new JDialog(frame, "成功");
    successDialog.add(new JLabel("成功"));
    JDialog failDialog = new JDialog(frame, "失敗");
    failDialog.add(new JLabel("失敗"));

    JPanel buttonPanel = new JPanel(new FlowLayout(FlowLayout.CENTER));
    JButton loginButton = new JButton("ログイン");
    loginButton.addActionListener(e -> {
      System.out.println(userIdTextField.getText());
      System.out.println(String.valueOf(paswordTextField.getPassword()));
      if (userIdTextField.getText().equals("minato")
          && String.valueOf(paswordTextField.getPassword()).equals("yusuke")) {
        successDialog.setSize(200, 200);
        successDialog.setVisible(true);
      } else {
        failDialog.setSize(200, 200);
        failDialog.setVisible(true);
      }
    });

    JButton clearButton = new JButton("クリア");
    clearButton.addActionListener(e -> {
      userIdTextField.setText("");
      paswordTextField.setText("");
    });
    buttonPanel.add(loginButton);
    buttonPanel.add(clearButton);
    frame.add(buttonPanel);

    frame.setVisible(true);
  }
}