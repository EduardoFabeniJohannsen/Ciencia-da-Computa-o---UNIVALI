#include "Arquivo.h"

static int proximoInode = 1;

Arquivo::Arquivo(string nome, string dono) {

    fcb.inode = proximoInode++;

    fcb.nome = nome;

    fcb.tamanho = 0;

    fcb.criacao = time(nullptr);

    fcb.modificacao = time(nullptr);

    fcb.dono = dono;

    fcb.permissao = 755;

    conteudo = "";
}