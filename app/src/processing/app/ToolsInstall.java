package processing.app;

import javax.swing.JPanel;
import java.awt.CardLayout;
import java.awt.BorderLayout;
import java.awt.CardLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Desktop;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.FlowLayout;
import java.awt.GridBagConstraints;
import java.awt.GridBagLayout;
import java.awt.GridLayout;
import java.awt.Insets;
import java.awt.event.ActionEvent;
import java.util.Random;
import javax.swing.AbstractAction;
import javax.swing.JButton;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;
import javax.swing.JFileChooser;
import javax.swing.WindowConstants;
import javax.swing.filechooser.FileNameExtensionFilter;
import java.io.*;
import java.util.Scanner;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.URL;

public class ToolsInstall extends JPanel {
    private static final Random random = new Random();
    
	private static JPanel cards;
	private final String name;
	private static JTextArea display;
	private static String archive;
	private static GridBagConstraints c;;
	private static JButton pbut;
	private static JButton nbut;
	private static JFrame f;
	private static JLabel finalCardLabel;

	private static AbstractAction nFinish = new AbstractAction("Finish") {
        public void actionPerformed(ActionEvent e)
        {
        	f.setVisible(false); 
        	f.dispose();
            for (Component comp : cards.getComponents() ) {
            	JPanel j = (JPanel)comp;
            	j.removeAll();
            	j = null;
            }
        }
    };

	private static AbstractAction pAction = new AbstractAction("\u22b2Prev") {
        public void actionPerformed(ActionEvent e)
        {
        	CardLayout cl = (CardLayout) cards.getLayout();
        	cl.previous(cards);
        	getCurrentCard();
        }
    };

    private static AbstractAction nAction = new AbstractAction("Next\u22b3") {
        public void actionPerformed(ActionEvent e)
        {
        	CardLayout cl = (CardLayout) cards.getLayout();
        	cl.next(cards);
        	getCurrentCard();
        }
    };

    public ToolsInstall(String name) {
    	GridBagLayout g = new GridBagLayout();    	
    	this.setLayout(g);
    	
        this.name = name;
        this.setPreferredSize(new Dimension(600, 350));
        this.setBackground(Color.white);

        //c.fill = GridBagConstraints.HORIZONTAL;
        c.anchor = GridBagConstraints.NORTH;
        c.gridwidth = 2;
    	c.gridx = 0;
    	c.gridy = 0;
    	//c.insets = new Insets(0,0,150,0);  //top padding

        
        JLabel l = new JLabel(name);

        l.setHorizontalAlignment(JLabel.CENTER);
        this.add(l, c);
    }

	public static void runDialog() {
		EventQueue.invokeLater(new Runnable() {

            @Override
            public void run() {
                create();
                System.out.println("Close");
            }
            
        });
	}
	
    @Override
    public String toString() {
        return name;
    }

    private static JPanel getCurrentCard()
    {
        JPanel card = null;

        for (Component comp : cards.getComponents() ) {
            if (comp.isVisible() == true) {
                card = (JPanel)comp;
                System.out.println(card.getName() );
                
                if(card.getName().contains("3")) {
                	nbut.setText("I Agree");
                }
                
                if(card.getName().contains("4")) {
                	Component[] comp1 = card.getComponents();
                	finalCardLabel = (JLabel) comp1[0];
                	pbut.setVisible(false);
		            Thread t1 = new Thread(new Runnable() {
		                public void run()
		                {
		                	unpack();
		                	throw new RuntimeException();
		                }});
		            
		            t1.setUncaughtExceptionHandler(new Thread.UncaughtExceptionHandler() {

		                public void uncaughtException(Thread t, Throwable e) {
				            nbut.removeActionListener(nAction);
		                	nbut.addActionListener(nFinish);
		                	nbut.setText("Finish");
		                	nbut.setVisible(true);
		                	finalCardLabel.setText("All done!");
		                	System.out.println(t + " throws exception: " + e);
		                }
		             });
		            nbut.setVisible(false);
		            t1.start();
                }
            }
        }
        return card;
    }

    private static void create() {
        cards = new JPanel(new CardLayout());
        c = new GridBagConstraints();
        
        f = new JFrame();
        f.setDefaultCloseOperation( WindowConstants.DISPOSE_ON_CLOSE );
        
        ToolsInstall p = new ToolsInstall("Download Tools");
        p.setName("1");
        cards.add(p, p.toString());
        
        JLabel t = new JLabel();
        t.setText("<HTML>Click the button below to download the C5000 compiler tools.<BR>" +
        		"On the next page you will be asked to specify the location of the downloaded file.<BR>" +
        		"To be able to download the tools you will need a my.ti.com login.<BR>If you do not have one you can create one" +
        		" on the login screen.<BR></HTML>");
        
        c.gridwidth = 1;
        c.gridx = 0;
        c.gridy = 1;
        c.ipady = 20;
        p.add(t, c);
        
        JButton b = new JButton("Download Tools");
        b.addActionListener(new ActionListener()
        {
        	  public void actionPerformed(ActionEvent ae)
        	  {
        	        try 
        	        {
        	            Desktop.getDesktop().browse(new URL("https://www-a.ti.com/downloads/sds_support/" +
        	            		"TICodegenerationTools/download.htm#C5500").toURI());
        	        }           
        	        catch (Exception e) {}
        	  }
        });
        
        c.ipady = 0;
        c.gridx = 0;
        c.gridy = 2;
        p.add(b, c);

        /* Install tools part with File Chooser */
        p = new ToolsInstall("Install tools");
        p.setName("2");
        
        cards.add(p, p.toString());
        
        t = new JLabel();
        t.setText("<HTML>Click the browse button to browse to the location of the downloaded file.<BR>" +
        		"Select the file and Click the \"Open\" Button</HTML>");
        
        c.gridx = 0;
        c.gridy = 1;
        //c.ipadx = 20;
        c.ipady = 20;
        c.gridwidth = 2;
        p.add(t, c);
        
        final JTextField textField = new JTextField(20);
        textField.setSize(30, 12);
        c.anchor = GridBagConstraints.EAST;
        c.gridwidth = 1;
        c.ipady = 0;
        c.gridx = 0;
        c.gridy = 2;
        p.add(textField, c);
        
        JButton browse = new JButton("Browse");
        c.gridx = 1;
        c.gridy = 2;
        c.anchor = GridBagConstraints.WEST;
        
        browse.addActionListener(new ActionListener() { 
        		
        	public void actionPerformed(ActionEvent e) {
			    //Handle open button action.
        		JFileChooser fc = new JFileChooser();
        		File theDirectory = new File(System.getProperty("user.home") + File.separator + "Downloads");
        		fc.setCurrentDirectory(theDirectory);
        		FileNameExtensionFilter filter = new FileNameExtensionFilter("TI Tools Installer", "sh", "sh");
        		fc.setFileFilter(filter);
        		
        		int returnVal = fc.showOpenDialog(null);
			
		        if (returnVal == JFileChooser.APPROVE_OPTION) {
		            final File file = fc.getSelectedFile();
		            System.out.println(file.getAbsolutePath());
		            textField.setText(file.getAbsolutePath());
		            Thread t1 = new Thread(new Runnable() {
		                public void run()
		                {
				            mountDiskImage(file.getAbsolutePath());
		                }});  t1.start();
		                
		        } else {
		        	System.out.println("Open cancelled by user");
		        }
        	}
        });

        p.add(browse, c);

        /* License Agreement */
        p = new ToolsInstall("License Agreement");
        
        display = new JTextArea(30,30);
        display.setEditable(false); // set textArea non-editable

        JScrollPane scroll = new JScrollPane (display, 
        		   JScrollPane.VERTICAL_SCROLLBAR_ALWAYS, JScrollPane.HORIZONTAL_SCROLLBAR_ALWAYS);
        scroll.setViewportView(display);

        c.gridx = 0;
        c.gridy = 1;
        c.ipadx = 550;
        c.ipady = 290;
        
        p.add(scroll, c);

        JLabel agree = new JLabel("Do you agree to the above license terms?");
        c.gridx = 0;
        c.gridy = 2;
        c.ipadx = 0;
        c.ipady = 0;

        p.add(agree, c);
        
        p.setName("3");
        cards.add(p, p.toString());


        /* All done */
        p = new ToolsInstall("Unpacking......");
        p.setName("4");
        cards.add(p, p.toString());

        JPanel control = new JPanel();

        pbut = new JButton("Cancel");
        pbut.setVisible(true);
        
        pbut.addActionListener(nFinish);

        nbut = new JButton("Next\u22b3");
        
        nbut.addActionListener(nAction);

        control.add(pbut);
        control.add(nbut);

        
        f.add(cards, BorderLayout.CENTER);
        f.add(control, BorderLayout.SOUTH);
        f.pack();
        f.setLocationRelativeTo(null);
        f.setVisible(true);
    }
    
    private static void mountDiskImage(String fileName) {
    	try {
//            Process p = Runtime.getRuntime().exec("hdiutil attach " + fileName);
//            p.waitFor();
//            BufferedReader reader = new BufferedReader(new InputStreamReader(p.getInputStream()));
//            String line;
//
//            System.out.println(p.exitValue());
//            if(p.exitValue() != 0)
//            	return;
//            
//            line = reader.readLine();
//            System.out.println(line);
//            String[] splited = line.split("\\t");
//            if(splited[2].contains("/Volumes"))
//            	System.out.println(splited[2]);
//        
            StringBuilder license = new StringBuilder();
            //archive = splited[2] + "/TI_CGT_C5500_4.4.2.sh";
            
            archive = fileName;
            
            BufferedReader rd = new BufferedReader(new FileReader(archive));
            String temp = rd.readLine() ;

            while (temp != null) {
                if(temp.contains("Texas Instruments License Agreement")) {
                    break;
                }
                temp = rd.readLine();
            }

            
            while (temp != null) {
                license.append(temp);
                license.append("\n");
                if(temp.contains("END OF LICENSE AGREEMENT"))
                    break;
                temp = rd.readLine();
            }
            
            if (rd != null)rd.close();
            
            display.setText(license.toString());
            display.setCaretPosition(0);
    	}
    	
        catch(IOException e1) {}
        //catch(InterruptedException e2) {}

        System.out.println("finished.");
    }
    
    private void finishUnpack() {

    }

    private static void unpack() {
    	try {
    		ProcessBuilder pb = new ProcessBuilder("mkdir", Base.getHardwarePath() + File.separator + "tools" +
	                  File.separator + "C5000");
    		Process p = pb.start();
    		
    		
    		pb = new ProcessBuilder("/bin/sh", "-c", "tail -n +642 " + "'" + archive + "'" + 
    				" | tar -C" + Base.getHardwarePath() + File.separator + 
    				"tools" + File.separator + "C5000" + " -zxf -");

    		p = pb.start();
    		BufferedReader br = new BufferedReader(new InputStreamReader(p.getErrorStream()));

    		String line = null;
    		while ( (line = br.readLine()) != null) {
    			System.out.println(line);
    		}
    		
    	}
        catch(IOException e1) {}

        System.out.println("finished.");
    }
}
