package com.divel.android.calendar;


import java.io.File;
import java.io.FileReader; 
import java.io.BufferedReader;
import java.io.IOException;

import android.app.ActionBar;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.DialogInterface.OnClickListener;
import android.content.Intent;
import android.net.Uri;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.view.Menu;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.DatePicker;
import android.widget.TextView;
import android.widget.Toast;

@SuppressWarnings("unused")
public class DivelCalendar extends Activity {
    /** Called when the activity is first created. */
	public DatePicker calendario;
	public TextView texto;
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.HONEYCOMB) {
        	setTheme(android.R.style.Theme_Holo);
            ActionBar actionbar=getActionBar();
            actionbar.setDisplayHomeAsUpEnabled(false);
            
        }else{
        	setTheme(android.R.style.Theme_Black);
        }
        setContentView(R.layout.main);
        final Button verevento = (Button) findViewById(R.id.button1);
        final Button addevento = (Button) findViewById(R.id.button2);
        final Button info = (Button) findViewById(R.id.button3);
        final Button divchat = (Button) findViewById(R.id.button4);
        final Button borrarevento = (Button) findViewById(R.id.button5);
        calendario = (DatePicker) findViewById(R.id.datePicker1);
        texto = (TextView) findViewById(R.id.textView2);

        //DivChat
        divchat.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent elchat=new Intent(DivelCalendar.this,DivChat.class);
				startActivity(elchat);
			}
		});
        
        
        
        //Información
        info.setOnClickListener(new View.OnClickListener(){
        	public void onClick(View a){
        		InfoAlerta();
				};
        });
        //Añadir evento
        addevento.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				boolean bien=AddEvent();

				if(bien==false){
					//se prepara la alerta creando nueva instancia
					AlertDialog.Builder dialogBuilder = new AlertDialog.Builder(DivelCalendar.this);
					//seleccionamos la cadena a mostrar
					dialogBuilder.setMessage("Ha habido un error y no ha sido posible guardar el evento");
					//elegimo un titulo y configuramos para que se pueda quitar
					dialogBuilder.setCancelable(true).setTitle("Error 101");
					//mostramos el dialogBuilder
					dialogBuilder.create().show();
					
				}
				
			}
		});
        //Borrar evento
        borrarevento.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View arg0) {
				
				
				
				
				
				
				BorrarEvento(calendario.getDayOfMonth(), calendario.getMonth(), calendario.getYear());

			}
		});
        
        //Calendario
        verevento.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				VerEvento(calendario.getDayOfMonth(), calendario.getMonth(), calendario.getYear());
				
			}
		});
        
        
        
        
      
    }
    public boolean AddEvent(){
    	//Comprobar
    	boolean mExternalStorageAvailable = false;
    	boolean mExternalStorageWriteable = false;
    	String state = Environment.getExternalStorageState();

    	if (Environment.MEDIA_MOUNTED.equals(state)) {
    	    // We can read and write the media
    	    mExternalStorageAvailable = mExternalStorageWriteable = true;
    	} else if (Environment.MEDIA_MOUNTED_READ_ONLY.equals(state)) {
    	    // We can only read the media
    	    return false;
    	} else {
    	    // Something else is wrong. It may be one of many other states, but all we need
    	    //  to know is we can neither read nor write
    	    return false;
    	}
    	//Nueva Activity y agregar datos
    	
    
    	
    	Intent addevt=new Intent(this,AddEvt.class);
    	addevt.putExtra("DIA",calendario.getDayOfMonth());
    	addevt.putExtra("MES", calendario.getMonth());
    	addevt.putExtra("ANO", calendario.getYear());
    	startActivity(addevt);
    	
    	
    	return true;
    }
    public void InfoAlerta(){
    	AlertDialog.Builder mensaje=new AlertDialog.Builder(this);
		mensaje.setTitle("Acerca de...");
		mensaje.setMessage("(C) Adrián Arroyo Calle 2012\n¿Deseas visitar la web de Adrián?");
		mensaje.setPositiveButton("Sí",new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				Uri web=Uri.parse("http://sites.google.com/site/adrianarroyocalle");
				Intent launchBrowser = new Intent(Intent.ACTION_VIEW, web);
        		startActivity(launchBrowser);
				dialog.cancel();
			}
		    });
		mensaje.setNegativeButton("No", new DialogInterface.OnClickListener(){
			public void onClick(DialogInterface dialog, int which){
				Toast mensaje2=Toast.makeText(getApplicationContext(), "Visítala otro día", Toast.LENGTH_LONG);
				mensaje2.show();
				dialog.cancel();
				
			}
		});
		mensaje.show();
    }
    public boolean VerEvento(int dia,int mes,int ano){
    	String state = Environment.getExternalStorageState();
    	if (Environment.MEDIA_MOUNTED.equals(state) || Environment.MEDIA_MOUNTED_READ_ONLY.equals(state)){
    		//Podemos leer
    		File path=Environment.getExternalStorageDirectory();
    		File archivo=new File(path,"/Android/data/com.divel.android.calendar/files/"+ano+"/"+mes+"/"+dia);
    		if(!archivo.exists()){
    			texto.setText("Ningún evento para "+dia+" de "+mes+" del "+ano);
    		}else{
    			try{
    			FileReader fr=new FileReader(archivo);
    			BufferedReader bfr=new BufferedReader(fr);
    			boolean leyendoeventos=false;
    			String myevento[][]=new String[32][32];
    			StringBuffer txt = new StringBuffer();
    			int evento=0;
    			int lectura=0;
    			if(bfr.ready()){
    				int buffer;
				while((buffer=bfr.read())!=-1){
						
    					if(leyendoeventos==false){
    						if(buffer==':' && bfr.read()==' '){leyendoeventos=true;}

    					}else{
    						//Toast.makeText(getApplicationContext(), "Hemos leído la cabecera", Toast.LENGTH_SHORT).show();
    						if(buffer!='~'){
    							if(buffer=='\n' && bfr.read()=='E'){
    								myevento[evento][lectura]=txt.toString();
    								txt.delete(0,txt.length());
    							evento++;
    							lectura=0;
    							leyendoeventos=false;
    							
    							}else{
    								
    									txt.append((char)buffer);
    									//myevento[lectura]+=(char)buffer;
    								}
    							}else{
    								//En cuanto haya ~
    								myevento[evento][lectura]=txt.toString();
    								txt.delete(0, txt.length());
    								lectura++;}
    			
    			
    			}
    					
    			}
				myevento[evento][lectura]=txt.toString();
    			//Poner el texto del evento	
    			texto.setText("Título: "+myevento[0][0]+"\nLugar: "+myevento[0][1]+"\nDuración: "+myevento[0][2]+"\nComentario: "+myevento[0][3]);	
    				if(evento>0){
    					int auxiliar=0;
    					//Iniciar bucle
    					for(auxiliar=evento;auxiliar!=0;auxiliar--){
    					AlertDialog mostrar=new AlertDialog.Builder(this).create();
    					mostrar.setTitle("Más eventos");
    					mostrar.setMessage("Título: "+myevento[auxiliar][0]+"\nLugar: "+myevento[auxiliar][1]+"\nDuración: "+myevento[auxiliar][2]+"\nComentario: "+myevento[auxiliar][3]);
    					mostrar.setButton("OK", new DialogInterface.OnClickListener() {
    						   public void onClick(DialogInterface dialog, int which) {
    						      // here you can add functions
    						   }
    						});
    					mostrar.show();
    					}
    					
    				}
    			}
    			
    			}catch(IOException e){
    				
    			}
    		}
    		
    		
    		
    	}else{
    		Toast.makeText(getApplicationContext(), "No se pudo leer la SD", Toast.LENGTH_SHORT).show();
    		
    	}
    	
    	
    	return true;
    }
    public void BorrarEvento(int dia,int mes, int ano){
    	AlertDialog.Builder confirmar=new AlertDialog.Builder(this);
    	confirmar.setTitle("Borrar evento");
    	confirmar.setMessage("¿Seguro que deseeas borrar todos los eventos de ese día?");
    	confirmar.setPositiveButton("Sí, borrar todo", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
		    	File path=Environment.getExternalStorageDirectory();
		    	File real=new File(path,"/Android/data/com.divel.android.calendar/files/"+calendario.getYear()+"/"+calendario.getMonth()+"/"+calendario.getDayOfMonth());
		    	real.delete();
			}
		    });
    	confirmar.setNegativeButton("No, no borrar", new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
		    	
			}
		    });
    	confirmar.show();
    	
    	

    	
    	
    }
    
    @Override
	public boolean onCreateOptionsMenu(Menu menu) {    
		MenuInflater inflater = getMenuInflater();    
		inflater.inflate(R.menu.menu, menu);    
		return true;
	}
 
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {    
		// Handle item selection
		switch (item.getItemId()) {    
			case R.id.acercade:{        
				InfoAlerta();
				return true;}    
			case R.id.getpc:        
				// Acciones       
				return true;
			default:
				return false;
		}
 
	}
}