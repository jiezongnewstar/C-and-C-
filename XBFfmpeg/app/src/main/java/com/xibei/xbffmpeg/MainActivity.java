package com.xibei.xbffmpeg;

import android.os.Environment;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.TextView;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private XBPlayer player;

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

//        player = new XBPlayer();
//        player.setDataSource(new File(Environment.getExternalStorageDirectory() + File.separator + "demo.mp4").getAbsolutePath());


        TextView tv = findViewById(R.id.sample_text);
        tv.setText(stringFromJNI());
    }


    @Override
    protected void onResume() {
        super.onResume();
//        player.prepare();
    }

    public native String stringFromJNI();
}
