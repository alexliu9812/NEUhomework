package com.glede.paint;

//import com.sun.codemodel.internal.JOp;

import external.JFontChooser;
import external.StrokeChooserPanel;
import external.StrokeSample;

import javax.imageio.ImageIO;
import javax.swing.*;
import javax.swing.event.DocumentEvent;
import javax.swing.event.DocumentListener;
import javax.swing.filechooser.FileNameExtensionFilter;

import org.omg.CORBA.PRIVATE_MEMBER;

import com.sun.org.apache.xml.internal.security.utils.HelperNodeList;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.awt.event.FocusEvent;
import java.awt.event.FocusListener;
import java.awt.Desktop;

/**
 * Created by Glede on 1/10/2019
 */
class JTextFieldHintListener implements FocusListener {
	private String hintText;
	private JTextField textField;
	public JTextFieldHintListener(JTextField jTextField,String hintText) {
		this.textField = jTextField;
		this.hintText = hintText;
		jTextField.setText(hintText);  //默认直接显示
		jTextField.setForeground(Color.GRAY);
	}
 
	@Override
	public void focusGained(FocusEvent e) {
		//获取焦点时，清空提示内容
		String temp = textField.getText();
		if(temp.equals(hintText)) {
			textField.setText("");
			textField.setForeground(Color.BLACK);
		}
		
	}
 
	@Override
	public void focusLost(FocusEvent e) {	
		//失去焦点时，没有输入内容，显示提示内容
		String temp = textField.getText();
		if(temp.equals("")) {
			textField.setForeground(Color.GRAY);
			textField.setText(hintText);
		}
		
	}
 
}

public class MainForm extends JFrame {
	private int BUTTONWIDTH = 32, BUTTONHEIGHT = 28;
    private DrawingBoard board;
    private JToolBar select;
    private JPanel mainPanel, history, historyMain;
    private BoardSettings settings;
    private JButton buttonOpenImg, buttonDelete,
            buttonPoints, buttonPolygon, buttonOval,
            buttonRect, buttonText, buttonLines,buttonContect,buttonLightAdjust,buttonHelp;
    private JButton buttonColor, buttonFont, buttonClear,
            buttonMove, buttonTop, buttonBottom, buttonSave, buttonSelect;
    private JCheckBox checkBoxFill;
    private JTextField textImput;
    private StrokeChooserPanel strokeChooserPanel;
    private JLabel labelModeNow;

    public JPanel getHistory() {
        return history;
    }

    public DrawingBoard getBoard() {
        return board;
    }

    public StrokeChooserPanel getStrokeChooserPanel() {
        return strokeChooserPanel;
    }

    public JButton changeIconSize(JButton button,String url,int width,int height,String tip){
        button.setBounds(0,0,width,height);
        ImageIcon buttonImg=new ImageIcon(url);
        //改变图片的大小
        Image temp=buttonImg.getImage().getScaledInstance(button.getWidth(), button.getHeight(), buttonImg.getImage().SCALE_DEFAULT);
        button=new JButton(new ImageIcon(temp));
        button.setToolTipText(tip);    //提示
        
        return button;
    }
    
    private void initChoose() {
        StrokeSample[] samples = StrokeLibrary.strokes;
        strokeChooserPanel = new StrokeChooserPanel(samples[2], samples);
        strokeChooserPanel.addSelectorListener(e -> {
            settings.setStroke(strokeChooserPanel.getSelectedStroke());
        });
    }

    private boolean asImageFile(File file) {
        String name = file.getName(), extension;
        int extBegin = name.lastIndexOf('.');
//        boolean asImageFile;
        if (extBegin == -1) return false;
        else if (extBegin == name.length() - 1) return false;
        else {
            extBegin++;
            extension = name.substring(extBegin);
            String[] exts = {"jpg", "png", "gif", "jpeg"};
            for (String ext : exts) {
                if (ext.equals(extension)) return true;
            }
        }
        return false;
    }

    
    private void initButtons() {

        buttonSelect = new JButton("调整");
        buttonSelect = changeIconSize(buttonSelect,"icon//resize.png",40,36,"调整位置");
        buttonSelect.addActionListener(e -> {
            settings.setType(BoardSettings.Type.选择);
            settings.nextResizePoint(null);
        });

        buttonLines = new JButton("折线");
        buttonLines = changeIconSize(buttonSelect,"icon//line2.png",BUTTONWIDTH,BUTTONHEIGHT,"使用鼠标左键逐个点按以绘制直线或者折线");
        buttonLines.addActionListener(e -> {
            settings.setType(BoardSettings.Type.直线折线);
            board.repaint();
        });
        
        buttonPoints = new JButton("钢笔");
        buttonPoints = changeIconSize(buttonPoints,"icon//drawfree.png",BUTTONWIDTH,BUTTONHEIGHT,"按住鼠标左键自由绘制");
        buttonPoints.addActionListener(e ->
                settings.setType(BoardSettings.Type.任意线));

        buttonOval = new JButton("椭圆");
        buttonOval = changeIconSize(buttonOval,"icon//circle.png",BUTTONWIDTH,BUTTONHEIGHT,"使用鼠标左键绘制圆形或者椭圆");
        buttonOval.addActionListener(e ->
                settings.setType(BoardSettings.Type.圆形椭圆));
        


        buttonPolygon = new JButton("多边形");
        buttonPolygon = changeIconSize(buttonPolygon, "icon//polygon.png",BUTTONWIDTH, BUTTONHEIGHT, "使用鼠标左键逐个点按以绘制多边形");
        buttonPolygon.addActionListener(e ->
                settings.setType(BoardSettings.Type.多边形));

        buttonOpenImg = new JButton("打开");
        buttonOpenImg = changeIconSize(buttonOpenImg, "icon//open.png", 32,36, "打开文件");
        buttonOpenImg.addActionListener(e -> {
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.setDialogTitle("Choose Image");
            fileChooser.setFileFilter(new FileNameExtensionFilter("Image Files", "gif", "png", "jpg", "bmp", "jpeg"));
            fileChooser.setFileFilter(new FileNameExtensionFilter("Painting Files", "pnt"));
            while (fileChooser.showOpenDialog(this) != JFileChooser.APPROVE_OPTION) {
                int confirmDialog = JOptionPane.showConfirmDialog(this, "Selection failed, continue?");
                if (confirmDialog != 0) {
                    return;
                }
            }
            File file = fileChooser.getSelectedFile();
            try {
                if (asImageFile(file)) {
                    settings.setType(BoardSettings.Type.图像);
                    settings.setImgNow(ImageIO.read(file));
                } else {
                    board.readList(ListIO.readList(this, file));
                }
            } catch (Exception ex) {
                JOptionPane.showMessageDialog(this, "Read file failed");
            }
            settings.clearPoints();

        });
        buttonRect = new JButton("Rect");
        buttonRect = changeIconSize(buttonRect, "icon//rect.png", BUTTONWIDTH, BUTTONHEIGHT, "使用鼠标左键绘制矩形");
        buttonRect.addActionListener(e -> {
            settings.setType(BoardSettings.Type.矩形);
        });
        buttonText = new JButton("Text");
        buttonText = changeIconSize(buttonText, "icon//text.png", BUTTONWIDTH, BUTTONHEIGHT, "使用鼠标左键点击位置插入文本内容");
        buttonText.addActionListener(e -> {
            settings.setType(BoardSettings.Type.文字);
        });
        
        buttonContect = new JButton("contect");
        buttonContect = changeIconSize(buttonContect, "icon//textcon.png", BUTTONWIDTH, BUTTONHEIGHT, "更改文本内容");
        buttonContect.addActionListener(e ->{
        	JOptionPane.showInputDialog(buttonContect,"Message");
        });

        buttonColor = new JButton("Color");
        buttonColor = changeIconSize(buttonColor, "icon//color.png", BUTTONWIDTH,BUTTONHEIGHT, "更换颜色");
        buttonColor.addActionListener(e -> {
            Color color = JColorChooser.showDialog(null, "Choose Color", Color.BLACK);
            settings.setColor(color);
        });

        buttonFont = new JButton("Font");
        buttonFont = changeIconSize(buttonFont, "icon//font.png", BUTTONWIDTH, BUTTONHEIGHT, "更换字体");
        buttonFont.addActionListener(e -> {
            JFontChooser fontChooser = new JFontChooser();
            fontChooser.showDialog(this);
            settings.setFont(fontChooser.getSelectedFont());
        });

        buttonClear = new JButton("Clear");
        buttonClear = changeIconSize(buttonClear, "icon//clear.png", BUTTONWIDTH, BUTTONHEIGHT, "清空所有更改");
        buttonClear.addActionListener(e -> {
            if (JOptionPane.showConfirmDialog(settings.getMainFrame(),
                    "Clear the paint board and discard all changes?") == 0) {
                board.clearBoard();
            }
        });

        textImput = new JTextField(15);
        textImput.addFocusListener(new JTextFieldHintListener(textImput, "在这里输入想要插入图片的文字..."));
        textImput.getDocument().addDocumentListener(new DocumentListener() {
            @Override
            public void insertUpdate(DocumentEvent e) {
                setText();
            }

            @Override
            public void removeUpdate(DocumentEvent e) {
                setText();
            }

            @Override
            public void changedUpdate(DocumentEvent e) {
                setText();
            }

            private void setText() {
                settings.setText(textImput.getText());
            }
        });
        
        
        buttonLightAdjust = new JButton();
        buttonLightAdjust = changeIconSize(buttonLightAdjust, "icon//light.png", BUTTONWIDTH, BUTTONHEIGHT, "调节亮度");
        buttonLightAdjust.addActionListener(e ->{
        	BufferedImage image = board.getImage();
        	File file = new File("cache.jpg");
        	try {
        	ImageIO.write(image, "jpg", file);
        	}catch (IOException ioe) {
				// TODO: handle exception
        		JOptionPane.showMessageDialog(this, "Save Failed :" + ioe.getMessage());
			}
        	LightImage li = new LightImage();
        	
        	if(li.getClosed() == 1)
        	{
        		try {
                    settings.setType(BoardSettings.Type.图像);
                    settings.setImgNow(ImageIO.read(file));
                    
            	}catch (IOException ioe) {
    				// TODO: handle exception
            		JOptionPane.showMessageDialog(this, "Save Failed :" + ioe.getMessage());
    			}
        	}
        }
        );
        
        buttonSave = new JButton("保存");
        buttonSave = changeIconSize(buttonSave, "icon//save.png", BUTTONWIDTH, BUTTONHEIGHT, "保存文件");
        buttonSave.addActionListener(e -> {
            BufferedImage image = board.getImage();
            JFileChooser fileChooser = new JFileChooser();
            fileChooser.addChoosableFileFilter
                    (new FileNameExtensionFilter("Image File", "jpg", "png", "gif", "jpeg"));
            fileChooser.setFileFilter
                    (new FileNameExtensionFilter("Paint Save File", "pnt"));
            if (fileChooser.showSaveDialog(this) == JFileChooser.APPROVE_OPTION) {
                File file = fileChooser.getSelectedFile();
                // save to file
                try {
                    String name = file.getName();
                    String path = file.getAbsolutePath();
                    String filter = fileChooser.getFileFilter().getDescription();
                    if (filter.contains("Image")) {
                        if (name.lastIndexOf('.') == -1) {
                            file = new File(path + ".jpg");
                        }
                        ImageIO.write(image, "jpg", file);
                    } else {
                        if (!name.substring(name.lastIndexOf('.') + 1).equals("pnt")) {
                            file = new File(path + ".pnt");
                        }
                        ListIO.saveList(this, board.getItemsList(), file);
                    }
                } catch (IOException ioe) {
                    JOptionPane.showMessageDialog(this, "Save Failed :" + ioe.getMessage());
                }
            }
        });
        
        
        buttonHelp = new JButton();
        buttonHelp = changeIconSize(buttonHelp, "icon//help.png", BUTTONWIDTH, BUTTONHEIGHT, "帮助");
        buttonHelp.addActionListener(e ->{
        	try {
        	Desktop.getDesktop().open(new File("help.chm"));
        	}catch (IOException ioe) {
				// TODO: handle exception
			}
        });
        

        checkBoxFill = new JCheckBox("实心模式");
        checkBoxFill.addActionListener(e -> {
            settings.setFill(checkBoxFill.isSelected());
        });
        
        

        JToolBar barSaveOpen=new JToolBar();
        JToolBar barChoose=new JToolBar();
        JToolBar barShapes=new JToolBar();
        JToolBar barText=new JToolBar();

        barSaveOpen.add(buttonSave);
        barSaveOpen.add(buttonOpenImg);

        barChoose.add(buttonSelect);
        barChoose.add(buttonClear);
        barChoose.add(buttonLightAdjust);
       
        barShapes.add(strokeChooserPanel);
        barShapes.add(buttonColor);
        barShapes.add(buttonPoints);
        barShapes.add(buttonLines);
        barShapes.add(buttonOval);
        barShapes.add(buttonRect);
        barShapes.add(buttonPolygon);
        barShapes.add(checkBoxFill);
        

        barText.add(buttonFont);
        barText.add(buttonText);
        barText.add(textImput);
       // barText.add(buttonContect);
    

        select.add(barSaveOpen);
        select.add(barChoose);
        select.add(barShapes);
        select.add(barText);

        select.add(labelModeNow);
        select.add(buttonHelp);
    }

    private void initHistory() {

        buttonTop = new JButton("顶部模式");
        buttonTop.addActionListener(e -> {
            if (settings.getType()== BoardSettings.Type.选择){
                settings.getPointNow().getItem().getRelatedButton().goTop();
                settings.getPointNow().getItem().getRelatedButton().reposition();
            }
            else {
                settings.setType(BoardSettings.Type.顶部);
            }

        });
        buttonBottom = new JButton("底部模式");
        buttonBottom.addActionListener(e -> {
            if (settings.getType() == BoardSettings.Type.选择) {
                settings.getPointNow().getItem().getRelatedButton().goBottom();
                settings.getPointNow().getItem().getRelatedButton().reposition();
            } else {
                settings.setType(BoardSettings.Type.底部);
            }
        });
        buttonDelete = new JButton("删除模式");
        buttonDelete.addActionListener(e -> {
            if (settings.getType()== BoardSettings.Type.选择){
                settings.getPointNow().getItem().getRelatedButton().delete();
                settings.getPointNow().getItem().getRelatedButton().reposition();
            }
            else {
                settings.setType(BoardSettings.Type.删除);
            }
        });
        
        buttonMove = new JButton("移动模式");
        buttonMove.addActionListener(e -> {
            if (settings.getType() == BoardSettings.Type.选择) {
                settings.getPointNow().getItem().getRelatedButton().move();
                settings.getPointNow().getItem().getRelatedButton().reposition();
            } else {
                settings.setType(BoardSettings.Type.移动);
            }
        });

        historyMain = new JPanel();
        historyMain.setLayout(new BoxLayout(historyMain, BoxLayout.PAGE_AXIS));
        JPanel historyOptions = new JPanel();
        historyOptions.setLayout(new BorderLayout());
        historyOptions.add(buttonTop, BorderLayout.NORTH);
        historyOptions.add(buttonBottom, BorderLayout.SOUTH);
        historyOptions.add(buttonMove, BorderLayout.EAST);
        historyOptions.add(buttonDelete, BorderLayout.WEST);

        historyMain.add(historyOptions);

        history = new JPanel();
        JScrollPane historyScroll = new JScrollPane(history);

        historyScroll.setBounds(0, 0, 0, 50);
        history.setAutoscrolls(true);
        historyScroll.setPreferredSize(new Dimension(50, 800));
        history.setSize(new Dimension(10, 50));
        history.setLayout(new BoxLayout(history, BoxLayout.PAGE_AXIS));
        historyMain.add(historyScroll);
    }

    public MainForm() {
        try {
            this.setUndecorated(false);
//            UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
            SwingUtilities.updateComponentTreeUI(this);
        } catch (Exception e) {
            JOptionPane.showMessageDialog(this, "LOAD UI FAILED");
        }

        Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
        this.setSize(d.width *2/3, d.height *4/5);
        this.setVisible(true);
        this.setLocationRelativeTo(null);
        this.setVisible(true);
        this.setTitle("Paint");
        addWindowListener(new WindowAdapter() {
            @Override
            public void windowClosing(WindowEvent e) {
                switch (JOptionPane.showConfirmDialog(settings.getMainFrame(),
                        "Discard all changes?")) {
                    case 0:
                        e.getWindow().dispose();
                        System.exit(0);
                        break;
                    case 1:
                        buttonSave.doClick();
                        break;
                }
            }
        });
        this.setDefaultCloseOperation(JFrame.DO_NOTHING_ON_CLOSE);
        mainPanel = new JPanel();
        mainPanel.setSize(d);
        mainPanel.setLayout(new BorderLayout(1, 1));
        select = new JToolBar();
        initHistory();
        select.setSize(new Dimension(700, 30));
        initChoose();

        labelModeNow=new JLabel("当前模式 : "+BoardSettings.INITIAL_TYPE.toString());

        settings = new BoardSettings(this);
        board = new DrawingBoard(settings,
                new Dimension(d.width - historyMain.getWidth(),
                        d.height - historyMain.getHeight()));
        initButtons();
        mainPanel.add(board);
        mainPanel.add(select, BorderLayout.NORTH);
//        mainPanel.add(history,BorderLayout.WEST);
        
        JToolBar toolBarHistory=new JToolBar(JToolBar.VERTICAL);
        toolBarHistory.add(historyMain);
        mainPanel.add(toolBarHistory, BorderLayout.WEST);
        this.add(mainPanel);
        select.revalidate();
    }

    public JLabel getLabelModeNow() {
        return labelModeNow;
    }
}
