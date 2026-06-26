#include "Arquivo.h"

static int proximoInode = 1;

Arquivo::Arquivo(string nome) {

    fcb.inode = proximoInode++;

    fcb.nome = nome;

    fcb.tamanho = 0;

    fcb.criacao = time(nullptr);

    fcb.modificacao = time(nullptr);

    fcb.dono = "admin";

    fcb.permissao = 755;

    conteudo = "";
}