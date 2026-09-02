
package buscapadraoweb;

import buscaweb.CapturaRecursosWeb;
import java.util.ArrayList;

 class Main {

    // busca char em vetor e retorna indice
    public static int get_char_ref (char[] vet, char ref ){
        for (int i=0; i<vet.length; i++ ){
            if (vet[i] == ref){
                return i;
            }
        }
        return -1;
    }

    // busca string em vetor e retorna indice
    public static int get_string_ref (String[] vet, String ref ){
        for (int i=0; i<vet.length; i++ ){
            if (vet[i].equals(ref)){
                return i;
            }
        }
        return -1;
    }

    //retorna o próximo estado, dado o estado atual e o símbolo lido
    public static int proximo_estado(char[] alfabeto, int[][] matriz,int estado_atual,char simbolo){
        int simbol_indice = get_char_ref(alfabeto, simbolo);
        if (simbol_indice != -1){
            return matriz[estado_atual][simbol_indice];
        }else{
            return -1;
        }
    }

    
    public static void ligarHex(int[][] matriz, char[] alfabeto, int origem, int destino){
        char[] hex = {'0','1','2','3','4','5','6','7','8','9',
                       'a','b','c','d','e','f',
                       'A','B','C','D','E','F'};
        for (char c : hex){
            matriz[origem][get_char_ref(alfabeto, c)] = destino;
        }
    }

    // liga o caractere ':' de um estado de origem para um estado de destino
    public static void ligarDoisPontos(int[][] matriz, char[] alfabeto, int origem, int destino){
        matriz[origem][get_char_ref(alfabeto, ':')] = destino;
    }

    /*
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        //instancia e usa objeto que captura código-fonte de páginas Web
        CapturaRecursosWeb crw = new CapturaRecursosWeb();
        crw.getListaRecursos().add("https://tecnoblog.net/responde/o-que-e-ipv6-saiba-para-que-serve-e-as-diferencas-para-o-protocolo-ipv4/");
        crw.getListaRecursos().add("https://learn.microsoft.com/pt-br/dotnet/fundamentals/networking/ipv6-overview");
        crw.getListaRecursos().add("https://www.juniper.net/documentation/br/pt/software/junos/routing-overview/topics/concept/ipv6-technology-overview.");
        ArrayList<String> listaURLs = crw.getListaRecursos();
        ArrayList<String> listaCodigos = crw.carregarRecursos();

        // ================================================================
        // MONTAGEM DO AFD DE IPv6
        // ================================================================

        //mapa do alfabeto: os caracteres reais válidos em um IPv6
        // do alfabeto, usado depois com get_char_ref, igual ao exemplo
        // dele com '0'..'9')
        char[] alfabeto = new char[23];
        alfabeto[0] = '0';
        alfabeto[1] = '1';
        alfabeto[2] = '2';
        alfabeto[3] = '3';
        alfabeto[4] = '4';
        alfabeto[5] = '5';
        alfabeto[6] = '6';
        alfabeto[7] = '7';
        alfabeto[8] = '8';
        alfabeto[9] = '9';
        alfabeto[10] = 'a';
        alfabeto[11] = 'b';
        alfabeto[12] = 'c';
        alfabeto[13] = 'd';
        alfabeto[14] = 'e';
        alfabeto[15] = 'f';
        alfabeto[16] = 'A';
        alfabeto[17] = 'B';
        alfabeto[18] = 'C';
        alfabeto[19] = 'D';
        alfabeto[20] = 'E';
        alfabeto[21] = 'F';
        alfabeto[22] = ':';

        // ----------------------------------------------------------------
        // ESTADOS
        // ----------------------------------------------------------------
        // Um IPv6 é uma sequência de até 8 "grupos" hexadecimais (1 a 4
        // dígitos cada), separados por ':'. Pode existir, no máximo, UMA
        // abreviação "::" que substitui um ou mais grupos de zeros.
        //
        // Para que o AFD (e não código externo) decida corretamente a
        // aceitação, cada estado representa 3 informações:
        //   (a) quantos grupos JÁ FORAM FECHADOS
        //   (b) quantos dígitos hex já foram lidos no grupo ATUAL
        //   (c) se a abreviação "::" já ocorreu ou não, e quantos grupos
        //       vieram ANTES dela
        //
        // Famílias de estados:
        //   q{n}_h{k}    -> SEM abreviação ainda; n grupos já fechados,
        //                   k hex lidos no grupo atual (k = 1..4)
        //   q{n}_c       -> SEM abreviação ainda; acabou de ler um ':'
        //                   logo após fechar n grupos (aguardando hex do
        //                   próximo grupo OU um segundo ':')
        //   qcc{m}       -> acabou de ler o SEGUNDO ':' (a abreviação
        //                   "::"), tendo m grupos fechados antes dela
        //   qA{m}_{n}_h{k} -> abreviação já usada (m grupos antes dela);
        //                   n grupos fechados DEPOIS da abreviação;
        //                   k hex lidos no grupo atual
        //   qAc{m}_{n}   -> abreviação já usada; acabou de ler um ':'
        //                   após fechar n grupos depois da abreviação
        //                   (aguardando hex do próximo grupo)
        //
        // Estado inicial: q0_h0 (nenhum grupo, nenhum hex lido, sem "::")
        //
        // Não existe transição para além de 8 grupos, e não existe
        // segunda abreviação "::" (isso é garantido pelos limites dos
        // laços abaixo, que simplesmente não criam essas transições).
        // ----------------------------------------------------------------

        ArrayList<String> listaEstados = new ArrayList<>();
        listaEstados.add("q0_h0"); // estado inicial: nenhum caractere lido ainda

        // Família q{n}_h{k} e q{n}_c : SEM abreviação, n = 0..7 grupos fechados
        for (int n = 0; n <= 7; n++){
            for (int k = 1; k <= 4; k++){
                listaEstados.add("q" + n + "_h" + k);
            }
            listaEstados.add("q" + n + "_c");
        }

        // Família qcc{m} : abreviação "::" ocorreu, m = 0..7 grupos antes dela
        for (int m = 0; m <= 7; m++){
            listaEstados.add("qcc" + m);
        }

        // Famílias qA{m}_{n}_h{k} e qAc{m}_{n} : após abreviação
        // m = grupos antes da abreviação, n = grupos fechados depois dela
        // (m + n não pode ultrapassar 7, pois "::" precisa representar
        // pelo menos 1 grupo de zeros omitido, então no máximo 7 grupos
        // podem ser explícitos)
        for (int m = 0; m <= 7; m++){
            for (int n = 0; n <= (7 - m); n++){
                for (int k = 1; k <= 4; k++){
                    listaEstados.add("qA" + m + "_" + n + "_h" + k);
                }
                if (m + n <= 6){
                    listaEstados.add("qAc" + m + "_" + n);
                }
            }
        }

        String[] estados = listaEstados.toArray(new String[0]);
        String estado_inicial = "q0_h0";

        // ----------------------------------------------------------------
        // ESTADOS FINAIS
        // ----------------------------------------------------------------
        ArrayList<String> listaFinais = new ArrayList<>();

        // SEM abreviação: só é final ao completar EXATAMENTE o 8º grupo,
        // isto é, estava com 7 grupos fechados e acabou de ler de 1 a 4
        // hex no grupo atual (o oitavo).
        for (int k = 1; k <= 4; k++){
            listaFinais.add("q7_h" + k);
        }

        // COM abreviação: final ao fechar um grupo válido (k>=1 hex lido)
        // depois da abreviação, desde que o total de grupos EXPLÍCITOS
        // (m antes + n depois, incluindo o grupo atual) fique MENOR que 8
        // -- assim a abreviação "::" sempre representa pelo menos 1 grupo
        // de zeros omitido, evitando ambiguidade com o IPv6 completo.
        for (int m = 0; m <= 7; m++){
            for (int n = 0; n <= (7 - m); n++){
                if (m + n < 8){
                    for (int k = 1; k <= 4; k++){
                        listaFinais.add("qA" + m + "_" + n + "_h" + k);
                    }
                }
            }
        }

        String[] estados_finais = listaFinais.toArray(new String[0]);

        // ----------------------------------------------------------------
        // MATRIZ DE TRANSIÇÃO
        // ----------------------------------------------------------------
        // matriz[estado][coluna] -> próximo estado, ou -1 se não há
        // transição válida (o que faz o autômato "resetar" na varredura).
        int[][] matriz = new int[estados.length][alfabeto.length];
        for (int[] linha : matriz){
            for (int j = 0; j < linha.length; j++){
                linha[j] = -1;
            }
        }

        // --- Transições a partir do estado inicial q0_h0 ---
        ligarHex(matriz, alfabeto, get_string_ref(estados, "q0_h0"), get_string_ref(estados, "q0_h1"));
        ligarDoisPontos(matriz, alfabeto, get_string_ref(estados, "q0_h0"), get_string_ref(estados, "q0_c")); // permite "::1" etc.

        // --- Família SEM abreviação: dentro de um grupo (q{n}_h{k}) ---
        for (int n = 0; n <= 7; n++){
            for (int k = 1; k <= 4; k++){
                int origem = get_string_ref(estados, "q" + n + "_h" + k);
                if (k < 4){
                    ligarHex(matriz, alfabeto, origem, get_string_ref(estados, "q" + n + "_h" + (k+1)));
                }
                if (n <= 6){
                    ligarDoisPontos(matriz, alfabeto, origem, get_string_ref(estados, "q" + (n+1) + "_c"));
                }
            }
        }

        // --- Família SEM abreviação: "leu ':' após n grupos" (q{n}_c) ---
        for (int n = 0; n <= 7; n++){
            int origem = get_string_ref(estados, "q" + n + "_c");
            ligarHex(matriz, alfabeto, origem, get_string_ref(estados, "q" + n + "_h1"));
            ligarDoisPontos(matriz, alfabeto, origem, get_string_ref(estados, "qcc" + n)); // forma "::"
        }

        // --- "leu '::' com m grupos antes" (qcc{m}) : só aceita hex ---
        for (int m = 0; m <= 7; m++){
            int origem = get_string_ref(estados, "qcc" + m);
            ligarHex(matriz, alfabeto, origem, get_string_ref(estados, "qA" + m + "_0_h1"));
            // ':' aqui não tem transição (evita ":::" / segunda abreviação)
        }

        // --- Família APÓS abreviação: dentro de um grupo (qA{m}_{n}_h{k}) ---
        for (int m = 0; m <= 7; m++){
            for (int n = 0; n <= (7 - m); n++){
                for (int k = 1; k <= 4; k++){
                    int origem = get_string_ref(estados, "qA" + m + "_" + n + "_h" + k);
                    if (k < 4){
                        ligarHex(matriz, alfabeto, origem, get_string_ref(estados, "qA" + m + "_" + n + "_h" + (k+1)));
                    }
                    if (m + n <= 6){
                        ligarDoisPontos(matriz, alfabeto, origem, get_string_ref(estados, "qAc" + m + "_" + n));
                    }
                }
            }
        }

        // --- Família APÓS abreviação: "leu ':' após n grupos" (qAc{m}_{n}) ---
        for (int m = 0; m <= 7; m++){
            for (int n = 0; n <= (7 - m); n++){
                if (m + n <= 6){
                    int origem = get_string_ref(estados, "qAc" + m + "_" + n);
                    ligarHex(matriz, alfabeto, origem, get_string_ref(estados, "qA" + m + "_" + (n+1) + "_h1"));
                    // ':' aqui não tem transição (evita segunda abreviação)
                }
            }
        }

        // ================================================================
        // VARREDURA DO HTML DE CADA SITE, SEPARADAMENTE
        // ================================================================
        for (int s = 0; s < listaCodigos.size(); s++){
            String url = (s < listaURLs.size()) ? listaURLs.get(s) : ("site " + (s + 1));
            String codigoHTML = listaCodigos.get(s);

            ArrayList<String> ipv6_encontrados = varrerComAFD(codigoHTML, alfabeto, matriz, estados, estado_inicial, estados_finais);

            System.out.println(url);
            if (ipv6_encontrados.isEmpty()){
                System.out.println("Nenhum IPv6 foi encontrado na página.");
            } else {
                System.out.println("Encontrados os seguintes IPv6:");
                for (String p : ipv6_encontrados){
                    System.out.println(p);
                }
            }
            System.out.println();
        }
    }

    public static ArrayList<String> varrerComAFD(String texto, char[] alfabeto, int[][] matriz,
            String[] estados, String estado_inicial, String[] estados_finais){

        int estado = get_string_ref(estados, estado_inicial);
        int estado_anterior;
        ArrayList<String> palavras_reconhecidas = new ArrayList<>();
        String palavra = "";

        for (int i = 0; i < texto.length(); i++){
            estado_anterior = estado;

            // consulta a matriz diretamente com o caractere lido
            // (get_char_ref só encontra índice para os 23 símbolos do
            // alfabeto; qualquer outro caractere do HTML retorna -1,
            // exatamente como no autômato original do professor)
            estado = proximo_estado(alfabeto, matriz, estado, texto.charAt(i));

            if (estado == -1){
                estado = get_string_ref(estados, estado_inicial);
                if (get_string_ref(estados_finais, estados[estado_anterior]) != -1){
                    if (!palavra.equals("")){
                        palavras_reconhecidas.add(palavra);
                    }
                    // se ao analisar este caractere não houve transição,
                    // teste-o novamente, considerando que o estado seja inicial
                    i--;
                }
                palavra = "";
            } else {
                palavra += texto.charAt(i);
            }
        }

        // se o texto ACABA em um estado final, a palavra também deve ser
        // reconhecida (o laço original só fecha a palavra quando encontra
        // um caractere SEM transição; se acabou o texto, tratamos aqui)
        if (get_string_ref(estados_finais, estados[estado]) != -1 && !palavra.equals("")){
            palavras_reconhecidas.add(palavra);
        }

        return palavras_reconhecidas;
    }

}