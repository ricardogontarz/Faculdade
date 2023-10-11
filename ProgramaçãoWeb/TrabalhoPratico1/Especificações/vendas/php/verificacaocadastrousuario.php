<?php
// Inicia a seção
session_start();

// Verifica se o usuário está logado e se é o diretor
//require "logadodiretor.php";

// Importa página base para operações com o banco de dados
include ('../php/base.php');

// Atribui os valores digitados no formulário aos campos correspondentes
$nomeusuario = isset($_POST["tf_nome"]) ? addslashes(trim($_POST["tf_nome"])) : false;
$email = isset($_POST["tf_nomeusuario"]) ? addslashes(trim($_POST["tf_nomeusuario"])) : false;
$senha = (strlen($_POST["tf_senha"]) > 0) ? md5(trim($_POST["tf_senha"])) : false;
$confirmasenha = (strlen($_POST["tf_confirmasenha"]) > 0) ? md5(trim($_POST["tf_confirmasenha"])) : false;

// Se os valores dos campos senha e confirmação de senha forem diferentes
if($senha != $confirmasenha){
	echo "<META HTTP-EQUIV=REFRESH CONTENT='0;URL=../html/form_cadastro_usuario.html'>
            <script type=\"text/javascript\">
                alert(\"A senha digitada não é igual a confirmada!\");
            </script>"; 
	//header("Location: form_cadastro_usuario.php");
	//header("Location: form_cadastro_usuario.php?erro=1");
	exit;
}

/*
// Se o usuário não preencheu um dos campos é redirecionado à pagina de login
if(!$nomeusuario || !$senha || !$confirmasenha || !$nome || !$sobrenome){
	header("Location: cadastrousuario.php?erro=0");
	exit;
}
*/

// Procura por um usuário com o mesmo nome de usuário
$usuario = executar_SQL("SELECT idusuario FROM Usuario WHERE email = '$email'");

// Verifica se não existe outro usuário com esse nome
if(!verifica_resultado($usuario)){
	// Libera a consulta
	libera_consulta($usuario);

	// Executa a consulta de inserção
	$inserir = executar_SQL("INSERT INTO Usuario(nomeusuario, email, senha) VALUES ('$nomeusuario', '$email', '$senha')");
}
// Se já existe usuário com esse nome
else{
	header("Location: cadastrousuario.php?erro=2");
	exit;
}

// Redireciona para a página de confirmação de Login (Dashboard)
echo "<META HTTP-EQUIV=REFRESH CONTENT='0;URL=../html/dashboard.html'>
            <script type=\"text/javascript\">
                alert(\"Usuário Cadastrado com Sucesso!\");
            </script>"; 
?>
