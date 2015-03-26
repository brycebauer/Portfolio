/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */


/**
 *
 * @author Mitchell
 */
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.*;
import javax.swing.JOptionPane;

public class ButtonDemo_Extended implements ActionListener {

    // Definition of global values and items that are part of the GUI.
    int redScoreAmount = 0;
    int blueScoreAmount = 0;
    String team1, team2;
    JPanel titlePanel, scorePanel, buttonPanel;
    JLabel team1Label, team2Label, redScore, blueScore;
    JButton redButton1, blueButton1, resetButton, redButton4, blueButton4;
    JButton redButton2, blueButton2, redButton3, blueButton3;

    public JPanel createContentPane() {

        // We create a bottom JPanel to place everything on.
        JPanel totalGUI = new JPanel();
        totalGUI.setLayout(null);


        team1 = JOptionPane.showInputDialog("Enter in team 1's name", team1);
        team2 = JOptionPane.showInputDialog("Enter in team 2's name", team2);
        // Creation of a Panel to contain the title labels
        titlePanel = new JPanel();
        titlePanel.setLayout(null);
        titlePanel.setLocation(10, 0);
        titlePanel.setSize(250, 500);
        totalGUI.add(titlePanel);

        team1Label = new JLabel(team1);
        team1Label.setLocation(0, 0);
        team1Label.setSize(120, 30);
        team1Label.setHorizontalAlignment(0);
        team1Label.setForeground(Color.RED);
        titlePanel.add(team1Label);

        team2Label = new JLabel(team2);
        team2Label.setLocation(150, 0);
        team2Label.setSize(120, 30);
        team2Label.setHorizontalAlignment(0);
        team2Label.setForeground(Color.GREEN);
        titlePanel.add(team2Label);

        // Creation of a Panel to contain the score labels.
        scorePanel = new JPanel();
        scorePanel.setLayout(null);
        scorePanel.setLocation(10, 40);
        scorePanel.setSize(260, 30);
        totalGUI.add(scorePanel);

        redScore = new JLabel("" + redScoreAmount);
        redScore.setLocation(0, 0);
        redScore.setSize(120, 30);
        redScore.setHorizontalAlignment(0);
        scorePanel.add(redScore);

        blueScore = new JLabel("" + blueScoreAmount);
        blueScore.setLocation(150, 0);
        blueScore.setSize(120, 30);
        blueScore.setHorizontalAlignment(0);
        scorePanel.add(blueScore);

        // Creation of a Panel to contain all the JButtons.
        buttonPanel = new JPanel();
        buttonPanel.setLayout(null);
        buttonPanel.setLocation(0, 80);
        buttonPanel.setSize(300, 400);
        totalGUI.add(buttonPanel);

        // We create a button and manipulate it using the syntax we have
        // used before. Now each button has an ActionListener which posts 
        // its action out when the button is pressed.
        redButton1 = new JButton("1 point");
        redButton1.setLocation(0, 0);
        redButton1.setSize(120, 30);
        redButton1.addActionListener(this);
        buttonPanel.add(redButton1);

        redButton2 = new JButton("2 points");
        redButton2.setLocation(0, 40);
        redButton2.setSize(120, 30);
        redButton2.addActionListener(this);
        buttonPanel.add(redButton2);

        redButton3 = new JButton("3 points");
        redButton3.setLocation(0, 80);
        redButton3.setSize(120, 30);
        redButton3.addActionListener(this);
        buttonPanel.add(redButton3);

        blueButton1 = new JButton("1 point");
        blueButton1.setLocation(160, 0);
        blueButton1.setSize(120, 30);
        blueButton1.addActionListener(this);
        buttonPanel.add(blueButton1);
        
        blueButton2 = new JButton("2 points");
        blueButton2.setLocation(160, 40);
        blueButton2.setSize(120, 30);
        blueButton2.addActionListener(this);
        buttonPanel.add(blueButton2);
        
        blueButton3 = new JButton("3 points");
        blueButton3.setLocation(160, 80);
        blueButton3.setSize(120, 30);
        blueButton3.addActionListener(this);
        buttonPanel.add(blueButton3);
        
        redButton4 = new JButton("-1 point");
        redButton4.setLocation(0, 120);
        redButton4.setSize(120, 30);
        redButton4.addActionListener(this);
        buttonPanel.add(redButton4);
        
        blueButton4 = new JButton("-1 point");
        blueButton4.setLocation(160, 120);
        blueButton4.setSize(120, 30);
        blueButton4.addActionListener(this);
        buttonPanel.add(blueButton4);
        
        resetButton = new JButton("Reset Score");
        resetButton.setLocation(20, 180);
        resetButton.setSize(250, 30);
        resetButton.addActionListener(this);
        buttonPanel.add(resetButton);
        
        totalGUI.setOpaque(true);
        return totalGUI;
    }

    // This is the new ActionPerformed Method.
    // It catches any events with an ActionListener attached.
    // Using an if statement, we can determine which button was pressed
    // and change the appropriate values in our GUI.
    @Override
    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == redButton1) 
        {
            redScoreAmount = redScoreAmount + 1;
            redScore.setText("" + redScoreAmount);
        } 
        else if (e.getSource() == redButton2) 
        {
            redScoreAmount = redScoreAmount + 2;
            redScore.setText("" + redScoreAmount);
        } 
        else if (e.getSource() == redButton3) 
        {
            redScoreAmount = redScoreAmount + 3;
            redScore.setText("" + redScoreAmount);
        } 
        else if (e.getSource() == blueButton1) 
        {
            blueScoreAmount = blueScoreAmount + 1;
            blueScore.setText("" + blueScoreAmount);
        } 
        else if (e.getSource() == blueButton2) 
        {
            blueScoreAmount = blueScoreAmount + 2;
            blueScore.setText("" + blueScoreAmount);
        } 
        else if (e.getSource() == blueButton3) 
        {
            blueScoreAmount = blueScoreAmount + 3;
            blueScore.setText("" + blueScoreAmount);
        } 
        else if (e.getSource() == redButton4)
        {
            redScoreAmount = redScoreAmount - 1;
            redScore.setText("" + redScoreAmount);
        }
        else if (e.getSource() == blueButton4)
        {
            blueScoreAmount = blueScoreAmount - 1;
            blueScore.setText("" + blueScoreAmount);
        }
        else if (e.getSource() == resetButton) 
        {
            redScoreAmount = 0;
            blueScoreAmount = 0;
            redScore.setText("" + redScoreAmount);
            blueScore.setText("" + blueScoreAmount);
        }
    }

    private static void createAndShowGUI() {

        JFrame.setDefaultLookAndFeelDecorated(true);
        JFrame frame = new JFrame("[=] JButton Scores! [=]");

        //Create and set up the content pane.
        ButtonDemo_Extended demo = new ButtonDemo_Extended();
        frame.setContentPane(demo.createContentPane());

        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(400, 400);
        frame.setVisible(true);
    }

    public void startButtonExtended() {
        //Schedule a job for the event-dispatching thread:
        //creating and showing this application's GUI.
        SwingUtilities.invokeLater(new Runnable() {

            @Override
            public void run() {
                createAndShowGUI();
            }
        });
    }
}