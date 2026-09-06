# Projeto M1.1 – Operações Pontuais e Filtragem Espacial
Disciplina: Processamento de Imagens — UNIVALI, Curso de Ciência da Computação
Professor: Felipe Viel
Autores: Eduardo F. Johannsen e Kauan D. Leal

## Link do meu Colab: https://colab.research.google.com/drive/1gy2CCCC1zCp7rinPRY5gSLe7H2zV7Wkr?usp=sharing

## Como rodar o notebook no Google Colab
### 1. Subir a pasta de imagens

Antes de rodar qualquer célula, faça upload da pasta **`FotosViel`** (contendo todas as imagens do dataset: `lena.jpg`, `lena1.jpg`, `lena2.jpg`, `lena3.jpg`, `cameraman.png`, `quantize.jpg`, `bell.jpg`, `cubes.png`, `barbara.jpg`, `sky.png`, `noir.png`, `fg.jpg`, `Clear.jpg`, `q7_2.jpg`, etc.) para dentro do ambiente do Colab.

No painel lateral esquerdo do Colab (ícone de pasta), clique em **"Fazer upload para o armazenamento da sessão"** e envie a pasta `FotosViel` inteira. Ela precisa ficar disponível no caminho:

```
/content/FotosViel
```

Esse caminho é fixo no notebook (variável `DATASET_DIR`, definida na segunda célula de código). Se você subir a pasta em outro local, ajuste essa variável antes de continuar.

> **Atenção:** o Colab não mantém arquivos enviados manualmente entre sessões — sempre que o ambiente reiniciar (nova sessão, tempo ocioso, etc.), será necessário subir a pasta `FotosViel` novamente antes de rodar o notebook.

### 2. Rodar as células em ordem

O notebook foi organizado para ser executado **de cima para baixo, célula por célula**, sem pular nenhuma. Isso é importante porque cada seção reaproveita funções e variáveis definidas em seções anteriores.

A ordem de execução segue esta lógica:

1. **Códigos base** (primeiras células do notebook): importa as bibliotecas (NumPy, OpenCV, Matplotlib), define `DATASET_DIR`, lista os arquivos da pasta `FotosViel`, e cria as funções auxiliares (`carregar_imagem`, `mostrar_imagem`, `mostrar_imagens`) usadas em todo o restante do notebook. **Rode essas células primeiro, sempre**, mesmo que você queira testar só uma seção específica depois.
2. **Seção 1 — Manipulação de Pixels**: `cor_mais_frequente` e `mergeImage`.
3. **Seção 2 — Manipulação de Bits**: `BitQuantizeImage`, planos de bits, análise das imagens lena1/lena2/lena3.
4. **Seção 3 — Questões Diversas**: respostas teóricas (MSB, LSB) e cálculo do tempo de transmissão.
5. **Seção 4 — Transformação de Histograma**: equalização e histogram matching.
6. **Seção 5 — Detecção de Bordas**: Canny, Roberts, Prewitt, Sobel, Laplaciano e o teste com ruído gaussiano.
7. **Seção 6 — Filtragem High-Boost**.
8. **Seção 7 — Filtragem Bilateral**.

Cada seção depende apenas das funções definidas na seção "Códigos base" e, em alguns casos, de funções definidas em seções anteriores (por exemplo, a Seção 5 reaproveita `convolucao_2d` para os filtros de borda e para o high-boost da Seção 6). Por isso, a forma mais segura de rodar é sempre do início ao fim, em sequência — usar **"Ambiente de execução → Executar tudo"** no menu do Colab é a opção mais prática depois de subir a pasta `FotosViel`.

### 3. Testando com outra imagem (apresentação)

Como o professor pode pedir para testar o processamento com qualquer imagem durante a apresentação, basta:

1. Subir a nova imagem para dentro da pasta `FotosViel` (ou para `/content/FotosViel` diretamente);
2. Trocar o nome do arquivo na célula de teste da seção correspondente (por exemplo, trocar `"barbara.jpg"` por outro nome de arquivo);
3. Rodar novamente a célula (e, se a imagem for colorida/tons de cinza diferente do esperado, ajustar o parâmetro `colorida=True/False` em `carregar_imagem`).

## Estrutura do notebook

| Seção | Conteúdo |
|---|---|
| Códigos base | Imports, caminho do dataset, funções auxiliares de carregar/exibir imagens |
| 1. Manipulação de Pixels | Cor mais frequente, `mergeImage(fg, bg)` |
| 2. Manipulação de Bits | `BitQuantizeImage`, planos de bits, análise lena1/lena2/lena3 |
| 3. Questões Diversas | MSB, LSB, tempo de transmissão |
| 4. Transformação de Histograma | Equalização dupla, histogram matching (3 casos) |
| 5. Detecção de Bordas | Canny, Roberts, Prewitt, Sobel, Laplaciano, ruído gaussiano |
| 6. Filtragem High-Boost | Implementação manual, variação de janela/A, comparação com bilateral |
| 7. Filtragem Bilateral | Implementação manual, variação de sigmas, distância L2 |

## Observações importantes

- Nenhuma operação pontual ou filtro pedido no enunciado usa função pronta de biblioteca — apenas NumPy/OpenCV para leitura, conversão de cor e exibição, conforme as regras do trabalho.
- As seções 5, 6 e 7 reaproveolvem a função `convolucao_2d` (convolução espacial manual), então rodá-las fora de ordem pode gerar erro de `NameError` se a célula de definição ainda não tiver sido executada.
