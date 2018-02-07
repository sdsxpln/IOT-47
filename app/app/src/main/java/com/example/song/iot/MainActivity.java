package com.example.song.iot;

import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.CompoundButton;
import android.widget.ImageView;
import android.widget.Switch;
import android.widget.TextView;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class MainActivity extends AppCompatActivity implements CompoundButton.OnCheckedChangeListener {

    ImageView led_view;
    BufferedWriter writer = null;
    BufferedReader reader = null;
    Socket socket = null;
    Switch led_switch;
    TextView temp_label;
    TextView lo_label;
    TextView la_label;
    String temp_S;
    String lo_S;
    String la_S;
    String led_state;
    boolean checkByStm = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        final ApplicationUtil appUtil = (ApplicationUtil) MainActivity.this.getApplication();
        socket = appUtil.getSocket();
        writer = appUtil.getOut();
        reader = appUtil.getIn();
        led_switch = (Switch) findViewById(R.id.led_switch);
        temp_label = (TextView) findViewById(R.id.temp_label);
        lo_label = (TextView) findViewById(R.id.lo_label);
        la_label = (TextView) findViewById(R.id.la_label);
        led_switch.setOnCheckedChangeListener(this);

        temp_S = temp_label.getText().toString();
        lo_S = lo_label.getText().toString();
        la_S = la_label.getText().toString();


        AsyncTask<Void, String, Void> read = new AsyncTask<Void, String, Void>() {
            @Override
            protected Void doInBackground(Void... params) {

                try {
                    writer.write("android_connect" + "\r\n");
                } catch (IOException e) {
                    e.printStackTrace();
                }
                try {
                    writer.flush();
                } catch (IOException e) {
                    e.printStackTrace();
                }

                String line;
                try {
                    while ((line = reader.readLine()) != null) {
                        publishProgress(line);
                    }
                } catch (IOException e) {
                    e.printStackTrace();
                }
                return null;
            }

            @Override
            protected void onProgressUpdate(String... values) {

//                if (values[0].equals("@success")) {
//                    Toast.makeText(MainActivity.this, "链接成功！", Toast.LENGTH_SHORT).show();
//                }
//                recedt.append("receive：" + values[0] + "\r\n");
//                System.out.println("--" + values[0]);
                Log.e("IOT", "onProgressUpdate: " + values[0]);

                String save[] = values[0].split("_");
                Log.e("IOT", "onProgressUpdate: " + "" + save.length);
                if (save.length == 9) {
                    temp_S = save[5];
                    lo_S = save[7];
                    la_S = save[8];
                    led_state = save[6];

//                    if (led_state.equals("on")) {
//                        checkByStm = true;
//                        led_switch.setChecked(true);
//                    } else if (led_state.equals("off")) {
//                        checkByStm = true;
//                        led_switch.setChecked(false);
//                    }

                    Float f = Float.parseFloat(lo_S);
                    f = f / 10000;
                    lo_S = f.toString();

                    f = Float.parseFloat(la_S);
                    f = f / 10000;
                    la_S = f.toString();

                    temp_label.setText(temp_S);
                    lo_label.setText(lo_S);
                    la_label.setText(la_S);
                }
//                lo_S = (Integer.parseInt(lo_S)/100)
//                for (int i = 0; i < save.length; i++) {
////                    System.out.println("--" + save[i]);
//                    Log.e("IOT", "onProgressUpdate: " + save[i]);
//
//
//                }
                super.onProgressUpdate(values);
            }
        };
        read.execute();


//        led_view = (ImageView) findViewById(R.id.led_view);
//        led_view.setOnClickListener(this);
    }

//    @Override
//    public void onClick(View v) {
//        new Thread() {
//            @Override
//            public void run() {
//                send();
//            }
//        }.start();
//    }

    private void send() {

        try {
//            if (!checkByStm) {
                writer.write("android_on" + "\r\n");
                checkByStm = false;
//            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        try {
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void onCheckedChanged(CompoundButton buttonView, boolean isChecked) {
        new Thread() {
            @Override
            public void run() {
                send();
            }
        }.start();
    }
}
