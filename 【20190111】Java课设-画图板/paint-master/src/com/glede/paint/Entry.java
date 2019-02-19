package com.glede.paint;

public class Entry {

    private static MainForm mainForm;

    public static MainForm getMainFormInstance() {
        return mainForm;
    }

    public static void main(String[] args) {
        mainForm = new MainForm();
    }

}
