import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import java.math.*;

public class MainActivity extends AppCompatActivity implements View.OnClickListener{
    private Button button;
    private TextView textView;
    private EditText editText1,editText2;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        init();
    }
    private void init(){
        button= (Button)findViewById(R.id.button);
        textView= (TextView)findViewById(R.id.textView);
        editText1=(EditText)findViewById(R.id.editText);
        editText2=(EditText)findViewById(R.id.editText2);
        button.setOnClickListener(this);

    }
    public void onClick(View view){
         String num1=editText1.getText().toString();
        //double protein;
        //protein=Double.valueOf(num1).doubleValue();
        //textView.setText(Double.toString(Math.sin(Math.toRadians(protein))));
        String num2=editText2.getText().toString();
        //switch(view.getId()){
           // case R.id.button:
                int addition=Integer.parseInt(num1) + Integer.parseInt(num2) ;
               // double sine= (Math.sin(Math.toRadians(addition)));
               textView.setText(String.valueOf(addition));
               // break;






        }


    }
