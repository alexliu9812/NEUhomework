package com.glede.paint;

import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.geom.Ellipse2D;
import java.awt.image.BufferedImage;
import java.util.LinkedList;
import java.util.ListIterator;
import java.util.Vector;

/**
 * Created by Glede on 1/10/2019
 */

/**
 * The listener of DrawingBoard
 *
 * @author glede, xueyuan
 * @see DrawingBoard
 * @see java.awt.event.MouseListener
 * @see java.awt.event.MouseMotionListener
 */
class BoardMouseListener implements MouseListener, MouseMotionListener {

    BoardSettings settings;
    DrawingBoard drawingBoard;
    //    LinkedList<JButton> buttons;
    Point begin, now, end;

    private void setPreview() {
        drawingBoard.setPreview(null);
    }

    private void setPreview(DrawingItem item) {
        drawingBoard.setPreview(item);
    }

    /**
     * Set preview
     *
     * @param beg   The point that drawing begins
     * @param mouse The point that mouse at now
     */
    private void setPreview(Point beg, Point mouse) {
        int xx = Math.min(beg.x, mouse.x),
                yy = Math.min(beg.y, mouse.y),
                disX = Math.abs(beg.x - mouse.x),
                disY = Math.abs(beg.y - mouse.y);
        switch (settings.getType()) {
            case 矩形:
                drawingBoard.setPreview(new DrawingShape(settings.getColor(),
                        new Rectangle(xx, yy, disX, disY), settings.isFill(), settings.getStroke()));
                break;
            case 图像:
                drawingBoard.setPreview(new DrawingImage(settings.getImgNow(),
                        new Rectangle(xx, yy, disX, disY), settings.getMainFrame()));
                break;
            case 圆形椭圆:
                drawingBoard.setPreview(new DrawingShape(settings.getColor(),
                        new Ellipse2D.Double(xx, yy, disX, disY), settings.isFill(), settings.getStroke()));
                break;
            case 任意线:
                drawingBoard.setPreview(new DrawingPoints(settings.getColor(),
                        settings.getPoints(), settings.getStroke()));
                break;
            case 文字:
                drawingBoard.setPreview(new DrawingText(settings.getText(), now,
                        settings.getFont(), settings.getColor()));
                break;
        }
    }

    /**
     * Reposition current preview to pos
     * @param pos
     */
    private void repositionPreview(Point pos) {
        if (drawingBoard.getPreview() != null)
            drawingBoard.getPreview().reposition(pos);
    }

    public BoardMouseListener(BoardSettings settings,
                              DrawingBoard drawingBoard) {
        this.settings = settings;
        this.drawingBoard = drawingBoard;
    }

    @Override
    public void mouseDragged(MouseEvent e) {
        now = new Point(e.getPoint());
        if (settings.getType() == BoardSettings.Type.任意线) {
            settings.getPoints().addElement(now);
            setPreview(begin, now);
        } else if (settings.getType() == BoardSettings.Type.选择) {
            ResizePoint resizePoint = settings.getPointNow();
            if (resizePoint != null && resizePoint.valid())
                resizePoint.getItem().resize(settings.getSelectPoint(), now);
        } else if (settings.getType() != BoardSettings.Type.移动)
            setPreview(begin, now);
        else {
            repositionPreview(now);
        }
        drawingBoard.repaint();
    }

    @Override
    public void mouseMoved(MouseEvent e) {
        Point mouse = new Point(e.getPoint());
        switch (settings.getType()) {
            case 选择:
                selectResizePoint(mouse);
                break;
            case 多边形:
            case 直线折线:
                Vector<Point> previewPoints =
                        (Vector<Point>) settings.getPoints().clone();
                previewPoints.add(mouse);
                drawingBoard.setPreview(new DrawingPoints(settings.color,
                        previewPoints, settings.getStroke(), true));
                drawingBoard.repaint();
                break;
        }

    }

    @Override
    public void mouseClicked(MouseEvent e) {
        now = new Point(e.getPoint());
        if (begin != null) {
            if (settings.getType() == BoardSettings.Type.多边形) {
                settings.getPoints().addElement(now);
                setPreview(begin, now);
            } else if (settings.getType() == BoardSettings.Type.直线折线) {
                settings.getPoints().addElement(now);
                setPreview(begin, now);
            } else if (settings.getType() != BoardSettings.Type.移动)
                setPreview(begin, now);
            else {
                repositionPreview(now);
            }
        }
        drawingBoard.repaint();
    }

    private void selectResizePoint(Point point) {
        for (ListIterator<DrawingItem> iter =
             drawingBoard.getItemsList().
                     listIterator(drawingBoard.getItemsList().size()); iter.hasPrevious(); ) {
            DrawingItem item = iter.previous();
            int result;
            if ((result = item.getResizePoint().selected(point)) >= 0) {
                settings.nextResizePoint(item.getResizePoint());
                settings.setSelectPoint(result);
                drawingBoard.repaint();
                return;
            }
        }
        for (ListIterator<DrawingItem> iter =
             drawingBoard.getItemsList().
                     listIterator(drawingBoard.getItemsList().size()); iter.hasPrevious(); ) {
            DrawingItem item = iter.previous();
            if (item.contains(point)) {
                settings.nextResizePoint(item.getResizePoint());
                settings.setSelectPoint(0);
                drawingBoard.repaint();
                return;
            }
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {
        begin = new Point(e.getPoint());
        if (settings.getType() == BoardSettings.Type.选择) {
            selectResizePoint(begin);
        } else if (settings.getType() != BoardSettings.Type.多边形 &&
                settings.getType() != BoardSettings.Type.直线折线) {
            settings.getPoints().addElement(begin);
        }
    }

    @Override
    public void mouseReleased(MouseEvent e) {
        if (begin != null) {
            end = new Point(e.getPoint());
            if (settings.getType() != BoardSettings.Type.多边形 &&
                    settings.getType() != BoardSettings.Type.直线折线) {
                settings.getPoints().addElement(end);
            }
            Vector<Point> points = settings.getPoints();
            if (points.isEmpty()) return;
            double xx = Math.min(points.firstElement().x, points.lastElement().x),
                    yy = Math.min(points.firstElement().y, points.lastElement().y),
                    disX = Math.abs(points.firstElement().x - points.lastElement().x),
                    disY = Math.abs(points.firstElement().y - points.lastElement().y);
            switch (settings.getType()) {
                case 圆形椭圆:
                    addListItem(new DrawingShape(settings.color,
                            new Ellipse2D.Double(xx, yy, disX, disY),
                            settings.isFill(), settings.getStroke()));
                    setPreview();
                    break;
                case 矩形:
                    addListItem(new DrawingShape(settings.color,
                            new Rectangle((int) xx, (int) yy, (int) disX, (int) disY),
                            settings.isFill(), settings.getStroke()));
                    setPreview();
                    break;
                case 图像:
                    addListItem(new DrawingImage(settings.getImgNow(),
                            new Rectangle((int) xx, (int) yy, (int) disX, (int) disY), settings.mainFrame));
                    setPreview();
                    break;
                case 任意线:
                    addListItem(new DrawingPoints(settings.color, points, settings.getStroke()));
                    setPreview();
                    break;
                case 文字:
                    addListItem(new DrawingText(settings.getText(), end, settings.getFont(), settings.getColor()));
                    setPreview();
                    break;
                case 移动:
                    settings.replace(end);
                default:
                    break;
            }
            drawingBoard.repaint();
        }
    }

    @Override
    public void mouseEntered(MouseEvent e) {
        if (settings.getType() == BoardSettings.Type.多边形) {
            begin = null;
        }
    }


    @Override
    public void mouseExited(MouseEvent e) {
        if (drawingBoard.getPreview() != null
                && drawingBoard.getPreview().isSelectedPreview()
                && settings.getType() != BoardSettings.Type.移动) {
            setPreview();
            drawingBoard.repaint();
        }
        Vector<Point> points = settings.getPoints();
        if (points == null || points.size() <= 1) return;
        if (settings.getType() == BoardSettings.Type.多边形) {
            int[] xpoints = new int[points.size()], ypoints = new int[points.size()];
            int i = 0;
            for (Point point : points) {
                xpoints[i] = (point.x);
                ypoints[i] = (point.y);
                i++;
            }
            addListItem(new DrawingPolygon(settings.color,
                    new Polygon(xpoints, ypoints, points.size()), settings.isFill(), settings.getStroke()));
            setPreview();
            drawingBoard.repaint();
        } else if (settings.getType() == BoardSettings.Type.直线折线) {

            addListItem(new DrawingLines(settings.getColor(), points, settings.getStroke()));
            setPreview();
            drawingBoard.repaint();
        }
    }

    /**
     * Add the item to the list of all items
     * @param item
     */
    private void addListItem(DrawingItem item) {
        if (settings.getPoints() != null) {
            drawingBoard.getItemsList().add(item);
            HistoryButton button = new HistoryButton(drawingBoard, settings.getType().toString(), item);
            item.setRelatedButton(button);
            settings.getHistory().add(button);
            settings.getHistory().revalidate();
            settings.setPoints(null);
        }
    }
}

/**
 * The mighty drawing board!!!
 *
 * @author glede,xueyuan
 */
public class DrawingBoard extends JPanel {
    BoardSettings settings;
    LinkedList<DrawingItem> itemsList;
    DrawingItem preview;
    BoardMouseListener listener;

    private BufferedImage image;

    DrawingBoard(BoardSettings settings, Dimension dimension) {
        this.settings = settings;
        setSize(dimension);
        itemsList = new LinkedList<>();
        listener = new BoardMouseListener(settings, this);
        this.addMouseListener(listener);
        this.addMouseMotionListener(listener);
    }

    /**
     * Clears the drawing board
     */
    public void clearBoard() {
        itemsList.clear();
        settings.getHistory().removeAll();
        this.setPreview(null);
        this.repaint();
        if (settings.typeIsFunction())
            settings.setType(BoardSettings.Type.任意线);
        settings.getHistory().revalidate();
        settings.getHistory().repaint();
    }

    public LinkedList<DrawingItem> getItemsList() {
        return itemsList;
    }

    /**
     * Set current preview
     * @param item
     */
    void setPreview(DrawingItem item) {
        this.preview = item;
    }

    public DrawingItem getPreview() {
        return preview;
    }

    /**
     * Used when saving as image
     * @return An image of the copy of the drawing board
     */
    public BufferedImage getImage() {
        image = new BufferedImage(this.getWidth(), this.getHeight(), BufferedImage.TYPE_3BYTE_BGR);
        Graphics g = image.createGraphics();
        g.fillRect(0, 0, image.getWidth(), image.getHeight());
        this.setPreview(null);
        this.print(g);
        return image;
    }

    /**
     * Copy param list to item list
     * @param list
     */
    public void readList(LinkedList<DrawingItem> list) {
        clearBoard();
        itemsList.addAll(list);
        for (DrawingItem item : itemsList) {
            item.initResizePoint();
            item.setRelatedButton(new HistoryButton
                    (this, item.getType().toString(), item));
            settings.getHistory().add(item.getRelatedButton());
        }
        settings.getHistory().revalidate();
        settings.getHistory().repaint();
        repaint();
    }

    /**
     * Draw all item and preview on g
     * @param g
     */
    @Override
    public void paint(Graphics g) {
        super.paintComponent(g);
        g.setColor(Color.WHITE);
        g.fillRect(0, 0, getWidth(), getHeight());
        g.setColor(Color.BLACK);
        g.drawRect(0, 0, getWidth(), getHeight());
        if (itemsList != null)
            itemsList.forEach(item -> {
                item.draw(g);
                if (settings.getType() == BoardSettings.Type.选择) {
                    item.drawResizePoint(g);
                }
            });
        if (settings.getType() == BoardSettings.Type.选择 &&
                settings.getPointNow() != null) {
            settings.getPointNow().getItem().drawBounds(g);
        }
        if (preview != null) {
            preview.draw(g);
        }
//        selectBoard.repaint(new Rectangle(0,0,700,30));
    }

}
