package com.example.song.iot;

import android.content.Intent;
import android.os.AsyncTask;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;

import java.io.BufferedReader;
import java.io.BufferedWriter;


public class LoginActivity extends AppCompatActivity implements View.OnClickListener {
    EditText ip;
    EditText port;
    Button conbtn;
    BufferedWriter writer = null;
    BufferedReader reader = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login);
        findView();
        conbtn.setOnClickListener(this);
    }

    @Override
    public void onClick(View v) {
        final String ips = ip.getText().toString();
        final String ports = port.getText().toString();
        final ApplicationUtil appUtil = (ApplicationUtil) LoginActivity.this.getApplication();

        AsyncTask<Void, String, Void> read = new AsyncTask<Void, String, Void>() {

            @Override
            protected Void doInBackground(Void... params) {
                try {
                    appUtil.init(ips, ports);
                } catch (Exception e) {
                    publishProgress("@fail");
                    e.printStackTrace();
                }
                writer = appUtil.getOut();
                reader = appUtil.getIn();
                publishProgress("@success");
                return null;
            }

            @Override
            protected void onProgressUpdate(String... values) {

                if (values[0].equals("@success")) {
//                    Toast.makeText(LoginActivity.this, "链接成功！", Toast.LENGTH_SHORT).show();
                    Intent intent = new Intent(LoginActivity.this,MainActivity.class);
                    startActivity(intent);
                } else if (values[0].equals("@fail")) {
                    Toast.makeText(LoginActivity.this, "链接失败！", Toast.LENGTH_SHORT).show();
                }
                super.onProgressUpdate(values);
            }

        };
        read.execute();


    }

    void findView() {
        ip = (EditText) findViewById(R.id.ip_edit);
        port = (EditText) findViewById(R.id.port_edit);
        conbtn = (Button) findViewById(R.id.conn_btn);
    }
}
