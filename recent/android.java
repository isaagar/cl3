package com.example.nikhil.mybasiccalculator;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity implements View.OnClickListener {

    private Button buttonadd, buttonsub, buttonmul, buttondiv, buttonmemp, buttonmem;
    private TextView textViewResult;
    private EditText editText1,editText2;
    int i = 0;
    float[] memory = new float[100];

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }

    private void init(){
        buttonadd = (Button)findViewById(R.id.button);
        buttonsub = (Button)findViewById(R.id.button2);
        buttondiv = (Button)findViewById(R.id.button4);
        buttonmul = (Button)findViewById(R.id.button3);
        buttonmemp = (Button)findViewById(R.id.button5);
        buttonmem = (Button)findViewById(R.id.button6);

        editText1 = (EditText)findViewById(R.id.editText);
        editText2 = (EditText)findViewById(R.id.editText2);
        textViewResult = (TextView)findViewById(R.id.textView4);

        buttonadd.setOnClickListener(this);
        buttonsub.setOnClickListener(this);
        buttonmul.setOnClickListener(this);
        buttondiv.setOnClickListener(this);
        buttonmemp.setOnClickListener(this);
        buttonmem.setOnClickListener(this);
    }
    int j;
    public void onClick(View view){
        String num1 = editText1.getText().toString();
        String num2 = editText2.getText().toString();

        float no1 = Float.parseFloat(num1);
        float no2 = Float.parseFloat(num2);

        switch (view.getId()){
            case R.id.button:
                float addition = no1 + no2;
                memory[i] = addition;
                i++;
                j = i;
                textViewResult.setText(String.valueOf(addition));
                break;
            case R.id.button2:
                float subtraction = no1 - no2;
                memory[i] = subtraction;
                i++;
                j = i;
                textViewResult.setText(String.valueOf(subtraction));
                break;
            case R.id.button3:
                float multiplication = no1 * no2;
                memory[i] = multiplication;
                i++;
                j = i;
                textViewResult.setText(String.valueOf(multiplication));
                break;
            case R.id.button4:
                try {
                    float division = no1 / no2;
                    memory[i] = division;
                    i++;
                    j = i;
                    textViewResult.setText(String.valueOf(division));
                }catch (Exception e){
                    textViewResult.setText("Divide by zero");
                }
                break;
            case R.id.button5:
                if (j < i){
                    j++;
                    textViewResult.setText(String.valueOf(memory[j]));
                }

                break;
            case R.id.button6:
                j--;
                textViewResult.setText(String.valueOf(memory[j]));
                break;
        }

    }
}
