package com.glede.paint;
import java.awt.*;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;

/**
 * Created by Glede on 1/10/2019
 */
public class SerializableStroke implements Serializable,Stroke {
    public transient BasicStroke basicStroke;

    public SerializableStroke(float width, int cap, int join, float miterlimit,
                              float dash[], float dash_phase) {
        basicStroke = new BasicStroke(width, cap, join, miterlimit, dash, dash_phase);
    }

    //    float width, int cap, int join, float miterlimit,
//    float dash[], float dash_phase)
    private void writeObject(ObjectOutputStream out) throws IOException {
        out.writeFloat(basicStroke.getLineWidth());
        out.writeInt(basicStroke.getEndCap());
        out.writeInt(basicStroke.getLineJoin());
        out.writeFloat(basicStroke.getMiterLimit());
        out.writeObject(basicStroke.getDashArray());
        out.writeFloat(basicStroke.getDashPhase());
    }

    private void readObject(ObjectInputStream in) throws ClassNotFoundException, IOException {
        float width = in.readFloat();
        int cap = in.readInt();
        int join = in.readInt();
        float miterlimit = in.readFloat();
        float dash[] = (float[]) in.readObject();
        float dash_phase = in.readFloat();
        basicStroke = new BasicStroke(width, cap, join, miterlimit, dash, dash_phase);
    }

    public SerializableStroke(float width, int cap, int join, float miterlimit) {
        this(width, cap, join, miterlimit, null, 0.0f);
    }

    public SerializableStroke(float width, int cap, int join) {
        this(width, cap, join, 10.0f, null, 0.0f);
    }

    public SerializableStroke(float width) {
        this(width, CAP_ROUND, JOIN_MITER, 10.0f, null, 0.0f);
    }

    public SerializableStroke() {
        this(1.0f, CAP_SQUARE, JOIN_MITER, 10.0f, null, 0.0f);
    }

    public static final int JOIN_MITER = BasicStroke.JOIN_MITER;
    public static final int JOIN_ROUND = BasicStroke.JOIN_ROUND;
    public static final int JOIN_BEVEL = BasicStroke.JOIN_BEVEL;
    public static final int CAP_BUTT = BasicStroke.CAP_BUTT;
    public static final int CAP_ROUND = BasicStroke.CAP_ROUND;
    public static final int CAP_SQUARE = BasicStroke.CAP_SQUARE;

    @Override
    public Shape createStrokedShape(Shape p) {
        return basicStroke.createStrokedShape(p);
    }
}