/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package buscaweb;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Inet4Address;
import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.Socket;
import java.net.URL;
import java.net.URLConnection;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import java.util.logging.SocketHandler;

/**
 *
 * @author Santiago
 */
public class CapturaRecursosWeb {
    private ArrayList<String> listaRecursos = new ArrayList();
    

    public ArrayList<String> carregarRecursos(){
        ArrayList<String> resultado = new ArrayList();
        for (String stringURL: listaRecursos){
            String resposta = "";

            try {
                URL url = new URL(stringURL);
                URLConnection connection = url.openConnection();
                BufferedReader in = new BufferedReader(
                        new InputStreamReader(
                        connection.getInputStream()));

                String inputLine;

                StringBuffer sb = new StringBuffer();
                while ((inputLine = in.readLine()) != null) sb.append(inputLine+"\n");
                resposta = sb.toString();
                in.close();
            } catch (MalformedURLException ex) {
                ex.printStackTrace();
            } catch (IOException ex) {
                ex.printStackTrace();
            }

            // Adiciona sempre uma entrada por URL (mesmo vazia, em caso de
            // falha), para manter o índice de "resultado" alinhado com o
            // índice de "listaRecursos". Sem isso, se um site falhar, os
            // resultados dos sites seguintes ficam deslocados.
            resultado.add(resposta);
        }
        return resultado;
    }

    /**
     * @return the listaRecursos
     */
    public ArrayList<String> getListaRecursos() {
        return listaRecursos;
    }
}