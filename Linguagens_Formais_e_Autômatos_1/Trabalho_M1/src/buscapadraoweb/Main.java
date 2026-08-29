/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package buscapadraoweb;

import buscaweb.CapturaRecursosWeb;
import java.util.ArrayList;

/**
 * Este projeto foi adaptado a partir do original do professor (que
 * reconhecia números de dois dígitos) para reconhecer ENDEREÇOS IPv6
 * dentro do código HTML de uma página Web, utilizando um AFD
 * (Autômato Finito Determinístico) implementado "na mão" através de:
 *
 *   - um alfabeto (vetor de char),
 *   - um vetor de estados (vetor de String),
 *   - um estado inicial,
 *   - um vetor de estados finais,
 *   - uma matriz de transição (int[][]).
 *
 * A lógica de varredura do HTML (percorrer caractere a caractere, voltar
 * ao estado inicial quando não há transição, reconhecer a palavra
 * quando o estado anterior era final, e reprocessar o mesmo caractere
 * para continuar a busca) é EXATAMENTE a lógica do projeto original.
 * Só o alfabeto, os estados e a matriz de transição foram trocados
 * para reconhecer IPv6 em vez de números de dois dígitos.
 *
 * @author Santiago (adaptado)
 */
public class Main {

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

    // ------------------------------------------------------------------
    // CATEGORIZAÇÃO DO ALFABETO
    // ------------------------------------------------------------------
    // Em vez de listar 22 caracteres (0-9, a-f, A-F) individualmente no
    // alfabeto, usamos duas categorias de símbolo:
    //   'H' -> dígito hexadecimal (0-9, a-f, A-F)
    //   ':' -> dois-pontos (separador de grupo / abreviação)
    // Isso mantém a matriz de transição pequena e legível, sem abandonar
    // o mecanismo de matriz: a categorização só decide QUAL COLUNA da
    // matriz usar; quem decide se há transição e para onde ir continua
    // sendo exclusivamente a matriz.
    public static char categoria(char c){
        if ( (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') ){
            return 'H'; // hex digit
        } else if (c == ':'){
            return ':'; // dois pontos
        } else {
            return '?'; // fora do alfabeto do IPv6 (não terá transição)
        }
    }

    /*
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        //instancia e usa objeto que captura código-fonte de páginas Web
        CapturaRecursosWeb crw = new CapturaRecursosWeb();
        // >>> ALTERE AQUI OS SITES A SEREM CONSULTADOS <<<
        // Adicione ou remova chamadas .add(...) para consultar mais ou
        // menos páginas.
        crw.getListaRecursos().add("https://tecnoblog.net/responde/o-que-e-ipv6-saiba-para-que-serve-e-as-diferencas-para-o-protocolo-ipv4/");
        crw.getListaRecursos().add("https://learn.microsoft.com/pt-br/dotnet/fundamentals/networking/ipv6-overview");
        crw.getListaRecursos().add("https://www.juniper.net/documentation/br/pt/software/junos/routing-overview/topics/concept/ipv6-technology-overview.html");
        ArrayList<String> listaURLs = crw.getListaRecursos();
        ArrayList<String> listaCodigos = crw.carregarRecursos();

        // ================================================================
        // MONTAGEM DO AFD DE IPv6
        // ================================================================

        //mapa do alfabeto: 2 colunas -> 'H' (hex) e ':' (dois pontos)
        char[] alfabeto = new char[2];
        alfabeto[0] = 'H';
        alfabeto[1] = ':';
        int colH = get_char_ref(alfabeto, 'H');
        int colC = get_char_ref(alfabeto, ':');

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
        int[][] matriz = new int[estados.length][2];
        for (int[] linha : matriz){
            linha[0] = -1;
            linha[1] = -1;
        }

        // --- Transições a partir do estado inicial q0_h0 ---
        matriz[get_string_ref(estados, "q0_h0")][colH] = get_string_ref(estados, "q0_h1");
        matriz[get_string_ref(estados, "q0_h0")][colC] = get_string_ref(estados, "q0_c"); // permite "::1" etc.

        // --- Família SEM abreviação: dentro de um grupo (q{n}_h{k}) ---
        for (int n = 0; n <= 7; n++){
            for (int k = 1; k <= 4; k++){
                int origem = get_string_ref(estados, "q" + n + "_h" + k);
                if (k < 4){
                    matriz[origem][colH] = get_string_ref(estados, "q" + n + "_h" + (k+1));
                }
                if (n <= 6){
                    matriz[origem][colC] = get_string_ref(estados, "q" + (n+1) + "_c");
                }
            }
        }

        // --- Família SEM abreviação: "leu ':' após n grupos" (q{n}_c) ---
        for (int n = 0; n <= 7; n++){
            int origem = get_string_ref(estados, "q" + n + "_c");
            matriz[origem][colH] = get_string_ref(estados, "q" + n + "_h1");
            matriz[origem][colC] = get_string_ref(estados, "qcc" + n); // forma "::"
        }

        // --- "leu '::' com m grupos antes" (qcc{m}) : só aceita hex ---
        for (int m = 0; m <= 7; m++){
            int origem = get_string_ref(estados, "qcc" + m);
            matriz[origem][colH] = get_string_ref(estados, "qA" + m + "_0_h1");
            // ':' aqui não tem transição (evita ":::" / segunda abreviação)
        }

        // --- Família APÓS abreviação: dentro de um grupo (qA{m}_{n}_h{k}) ---
        for (int m = 0; m <= 7; m++){
            for (int n = 0; n <= (7 - m); n++){
                for (int k = 1; k <= 4; k++){
                    int origem = get_string_ref(estados, "qA" + m + "_" + n + "_h" + k);
                    if (k < 4){
                        matriz[origem][colH] = get_string_ref(estados, "qA" + m + "_" + n + "_h" + (k+1));
                    }
                    if (m + n <= 6){
                        matriz[origem][colC] = get_string_ref(estados, "qAc" + m + "_" + n);
                    }
                }
            }
        }

        // --- Família APÓS abreviação: "leu ':' após n grupos" (qAc{m}_{n}) ---
        for (int m = 0; m <= 7; m++){
            for (int n = 0; n <= (7 - m); n++){
                if (m + n <= 6){
                    int origem = get_string_ref(estados, "qAc" + m + "_" + n);
                    matriz[origem][colH] = get_string_ref(estados, "qA" + m + "_" + (n+1) + "_h1");
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

    /**
     * Percorre um texto usando o AFD (alfabeto, matriz, estados, estado
     * inicial e estados finais) e retorna a lista de palavras
     * reconhecidas. Esta é a MESMA lógica de varredura do projeto
     * original (apenas extraída para um método, para poder reutilizá-la
     * tanto na página baixada quanto nos testes).
     */
    public static ArrayList<String> varrerComAFD(String texto, char[] alfabeto, int[][] matriz,
            String[] estados, String estado_inicial, String[] estados_finais){

        int estado = get_string_ref(estados, estado_inicial);
        int estado_anterior;
        ArrayList<String> palavras_reconhecidas = new ArrayList<>();
        String palavra = "";

        for (int i = 0; i < texto.length(); i++){
            estado_anterior = estado;

            // traduz o caractere para a categoria do alfabeto ('H' ou ':')
            char cat = categoria(texto.charAt(i));
            estado = proximo_estado(alfabeto, matriz, estado, cat);

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