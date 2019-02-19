package com.glede.paint;

import external.StrokeSample;

import java.io.Serializable;

public class StrokeLibrary {
    public static final StrokeSample[] strokes = {
            new StrokeSample(new SerializableStroke(1f)),
            new StrokeSample(new SerializableStroke(2f)),
            new StrokeSample(new SerializableStroke(3f)),
            new StrokeSample(new SerializableStroke(4f)),
            new StrokeSample(new SerializableStroke(5f)),
            new StrokeSample(new SerializableStroke(6f)),
            new StrokeSample(new SerializableStroke(7f)),
            new StrokeSample(new SerializableStroke(8f)),
            new StrokeSample(new SerializableStroke(9f)),
            new StrokeSample(new SerializableStroke(10f)),
            new StrokeSample(new SerializableStroke(11f)),
            new StrokeSample(new SerializableStroke(12f)),
            new StrokeSample(new SerializableStroke(1.5f, SerializableStroke.CAP_BUTT,
                    SerializableStroke.JOIN_ROUND, 2.5f, new float[]{15, 10,},
                    0f)),
            new StrokeSample(new SerializableStroke(2.5f, SerializableStroke.CAP_BUTT,
                    SerializableStroke.JOIN_ROUND, 3.5f, new float[]{15, 10,},
                    0f)),
            new StrokeSample(new SerializableStroke(3.5f, SerializableStroke.CAP_BUTT,
                    SerializableStroke.JOIN_ROUND, 4.5f, new float[]{15, 10,},
                    0f)),
            new StrokeSample(new SerializableStroke(4.5f, SerializableStroke.CAP_BUTT,
                    SerializableStroke.JOIN_ROUND, 5.5f, new float[]{15, 10,},
                    0f)),

            new StrokeSample(new SerializableStroke(5.5f, SerializableStroke.CAP_BUTT,
                    SerializableStroke.JOIN_ROUND, 6.5f, new float[]{15, 10,},
                    0f)),

            new StrokeSample(new SerializableStroke(6.5f, SerializableStroke.CAP_BUTT,
                    SerializableStroke.JOIN_ROUND, 7.5f, new float[]{15, 10,},
                    0f)),
    };

}
