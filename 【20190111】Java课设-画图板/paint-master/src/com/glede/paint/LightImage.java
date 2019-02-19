package com.glede.paint;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Component;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Dictionary;
import java.util.Hashtable;
 
import javax.imageio.ImageIO;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import java.awt.event.*;
import javax.swing.*; 

public class LightImage extends JFrame
{
    private JPanel panel = null;
    private JSlider slider = null;
    private BufferedImage img = null;
    private int value = 0;
    public int isClosed = 0;
 
    public LightImage()
    {
        initComponent();
        this.setVisible(true);
    }
 
    public int getClosed() {
    	return isClosed;
    }
    
    private void initComponent()
    {
        this.setTitle("Brightness Adjustment");
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setSize(550, 450);
        this.setLocationRelativeTo(null);
 
        initImg(new File("cache.jpg"));
 
        panel = new JPanel()
        {
            @Override
            protected void paintComponent(Graphics g)
            {
                super.paintComponent(g);
                Graphics2D g2 = (Graphics2D) g;
                g2.drawImage(img, 0, 0, this.getWidth(), this.getHeight(), null);
            }
        };
 
        this.add(panel, BorderLayout.CENTER);
		
		this.addWindowListener(new WindowAdapter(){  
			public void windowClosing(WindowEvent e){  
				
	        	File file = new File("cache.jpg");
	        	try {
	        	ImageIO.write(img, "jpg", file);
	        	}catch (IOException ioe) {
					// TODO: handle exception
	        		
				}
	        	
				isClosed = 1;
			}  
		}
		);
        
        setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);
        
        
        panel.setLayout(new BorderLayout());
        slider = new JSlider();
        slider.setValue(50);
        slider.setPaintLabels(true);
        slider.setPaintTicks(true);
        slider.setMajorTickSpacing(100);
        slider.setMinorTickSpacing(5);
        Dictionary<Integer, Component> labels = new Hashtable<Integer, Component>();
        for (int i = 0; i <= 100; i += 5)
        {
            labels.put(i, new JLabel("" + i));
        }
        slider.setLabelTable(labels);
 
        value = slider.getValue();
 
        slider.addChangeListener(new ChangeListener()
        {
            @Override
            public void stateChanged(ChangeEvent e)
            {
                if (slider.getValueIsAdjusting())
                {
                    int changeValue = slider.getValue() - value;
                    processImg(changeValue);
                    value = slider.getValue();
                }
            }
        });
 
        Box box = new Box(BoxLayout.X_AXIS);
        box.add(new JLabel("BrightnessAdjustment:"));
        box.add(slider);
        this.add(box, BorderLayout.NORTH);
        
        
    }
 
    private void initImg(File file)
    {
        try
        {
            img = ImageIO.read(file);
        } catch (IOException e)
        {
            JOptionPane.showMessageDialog(null, "NO IMAGE!");
        }
    }
 

    private void processImg(int changeValue)
    {
        for (int x = 0; x < img.getWidth(); x++)
        {
            for (int y = 0; y < img.getHeight(); y++)
            {
                int rgb = img.getRGB(x, y);
                Color color = new Color(rgb);
                int r = color.getRed() + changeValue;
                int g = color.getGreen() + changeValue;
                int b = color.getBlue() + changeValue;
                if (r > 255)
                {
                    r = 255;
                } else if (r < 0)
                {
                    r = 0;
                }
 
                if (g > 255)
                {
                    g = 255;
                } else if (g < 0)
                {
                    g = 0;
                }
 
                if (b > 255)
                {
                    b = 255;
                } else if (b < 0)
                {
                    b = 0;
                }
 
                color = new Color(r, g, b);
                img.setRGB(x, y, color.getRGB());
            }
        }
        panel.repaint();
    }
 /*
    public static void main(String[] args)
    {
        new LightImage();
    }
 */
}