package com.divel.android.calendar;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;

import android.app.Activity;
import android.app.AlertDialog;
import android.content.DialogInterface;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.text.Editable;
import android.widget.EditText;
import android.widget.TextView;

public class DivChat extends Activity{
	
	public void onCreate(Bundle savedInstanceState)
	{
		super.onCreate(savedInstanceState);
		setContentView(R.layout.divchat);
		
		AlertDialog.Builder mensaje=new AlertDialog.Builder(this);
		mensaje.setTitle("DivChat");
		mensaje.setMessage("¿Deseas crear una sala o unirse a una?");
		mensaje.setPositiveButton("Crear sala",new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				Servidor();
			}
		    } );
		
		
		mensaje.setNegativeButton("Unirse a sala",new DialogInterface.OnClickListener() {
			public void onClick(DialogInterface dialog, int which) {
				Cliente();
			}
		    } );
		
		
		
		mensaje.show();
		
		
		
	}
	public boolean Servidor(){
		
		try {
			ServerSocket DivServer = new ServerSocket(6997);
			Socket DivCliente = DivServer.accept();
			String first="Todos conectados";
			InputStream input = DivCliente.getInputStream();
			OutputStream output = DivCliente.getOutputStream();
			DataInputStream recv = new DataInputStream (input);
			DataOutputStream send= new DataOutputStream (output);
			send.writeUTF(first);
			String buffer=recv.readUTF();
			int algo=0;
			final boolean escrito=false;
			while(algo==0){
			    buffer=recv.readUTF();
			    
			       AlertDialog.Builder alert = new AlertDialog.Builder(this);  
			       alert.setTitle("DivChat");  
			       alert.setMessage("Contesta a:");
			       final TextView respuesta=new TextView(this);
			       respuesta.setText(buffer);
			       final EditText texto = new EditText(this);
			       alert.setView(texto);  
			       alert.setPositiveButton("Enviar", new DialogInterface.OnClickListener() {  
			             public void onClick(DialogInterface dialog, int whichButton) {
			                //Ha pulsado aceptar 
			            	 
			            	 
			            	
			             }
			       });
			       alert.show();
			       send.writeUTF(texto.getText().toString());
				

				}

			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		return true;
	}
	public boolean Cliente(){
	       AlertDialog.Builder alert = new AlertDialog.Builder(this);  
	       alert.setTitle("DivChat");  
	       alert.setMessage("Introduce la IP");
	       final EditText texto = new EditText(this);
	       alert.setView(texto);  
	       alert.setPositiveButton("Enviar", new DialogInterface.OnClickListener() {  
	             public void onClick(DialogInterface dialog, int whichButton) {
	                //Ha pulsado aceptar 
	            	 
	            	 
	            	
	             }
	       });
	       alert.show();
		try {
			Socket DivCliente = new Socket (texto.getText().toString(),6997);
			InputStream input = DivCliente.getInputStream();
			OutputStream output = DivCliente.getOutputStream();
			DataInputStream recv = new DataInputStream (input);
			DataOutputStream send= new DataOutputStream (output);
			String buffer=recv.readUTF();
			send.writeUTF("Estoy conectado");
			int algo=0;
			while(algo==0){
				
				buffer=recv.readUTF();
			       AlertDialog.Builder alerta = new AlertDialog.Builder(this);  
			       alerta.setTitle("DivChat");  
			       alerta.setMessage("Contesta a:");
			       TextView larespuesta=new TextView(this);
			       larespuesta.setText(buffer);
			       final EditText textual = new EditText(this);
			       alerta.setView(textual);  
			       alerta.setPositiveButton("Enviar", new DialogInterface.OnClickListener() {  
			             public void onClick(DialogInterface dialog, int whichButton) {
			                //Ha pulsado aceptar 
			            	 
			            	 
			            	
			             }
			       });
			       alerta.show();
				
				
				
				send.writeUTF(textual.getText().toString());
				}
			
			
			
			
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		
		
		return true;
	}

	
	
	
	

}
