package com.divel.android.calendar;


import java.io.*;

import com.divel.android.calendar.R;
import android.app.Activity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

@SuppressWarnings("unused")
public class AddEvt extends Activity {
	private int dia;
	private int mes;
	private int ano;
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.addevt);
		final Button ok = (Button) findViewById(R.id.ok);
		final EditText titulo = (EditText) findViewById(R.id.editText1);
		final EditText lugar = (EditText) findViewById(R.id.editText2);
		final EditText duracion = (EditText) findViewById(R.id.editText3);
		final EditText comentario = (EditText) findViewById(R.id.editText4);
		
		Toast unmensaje=Toast.makeText(getApplicationContext(), "Obteniendo fecha...", Toast.LENGTH_SHORT);
		Bundle extra = this.getIntent().getExtras();
		dia = extra.getInt("DIA");
		mes = extra.getInt("MES");
		ano = extra.getInt("ANO");
		Toast mensaje=Toast.makeText(getApplicationContext(), "Fecha: "+dia+"/"+mes+"/"+ano, Toast.LENGTH_SHORT);
		mensaje.show();
		
		ok.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				guardar();
				
			}
		});
		
		
		
        
	}
	public void guardar(){
		String state = Environment.getExternalStorageState();
		if (Environment.MEDIA_MOUNTED.equals(state)){
			//Podemos escribir
			File path= Environment.getExternalStorageDirectory();
			File carpeta=new File(path,"/Android/data/com.divel.android.calendar/files/");
			File carpetames=new File(carpeta,ano+"/"+mes+"/");
			File evento=new File(carpetames,""+dia);
		    try {
		        path.mkdirs();
		        carpeta.mkdirs();
		        carpetames.mkdirs();
		        //Toast.makeText(getApplicationContext(),"DEBUG 0" , Toast.LENGTH_SHORT).show();
		        if(!evento.exists()){
		        	Writer writer = new BufferedWriter(new FileWriter(evento));
		        	writer.write("DivelCalendar:DiaFile\n");
		        	writer.close();
		        	
		        }
		        //Toast.makeText(getApplicationContext(),"DEBUG 1" , Toast.LENGTH_SHORT).show();
				final EditText titulo = (EditText) findViewById(R.id.editText1);
				final EditText lugar = (EditText) findViewById(R.id.editText2);
				final EditText duracion = (EditText) findViewById(R.id.editText3);
				final EditText comentario = (EditText) findViewById(R.id.editText4);
				//Toast.makeText(getApplicationContext(),"DEBUG 2" , Toast.LENGTH_SHORT).show();
		        Writer writer = new BufferedWriter(new FileWriter(evento, true));
		        writer.write("Event: "+titulo.getText().toString()+"~"+lugar.getText().toString()+"~"+duracion.getText().toString()+"~"+comentario.getText().toString()+"\n");
		        writer.close();
		        finish();
		        Toast.makeText(getApplicationContext(),"Guardado correctamente" , Toast.LENGTH_SHORT).show();
		        
		    } catch (IOException e) {
		        // Unable to create file, likely because external storage is
		        // not currently mounted.
		    	Toast.makeText(getApplicationContext(),"Hubo problemas para guardar" , Toast.LENGTH_SHORT).show();
		    }
			
		}else{
			Toast.makeText(getApplicationContext(),"No se ha detectado tarjeta SD" , Toast.LENGTH_SHORT).show();
			
			
		}
		
		
	}
	
	
}
