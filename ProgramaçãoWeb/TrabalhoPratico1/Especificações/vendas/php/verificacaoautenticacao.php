<?php
// Inicia a seção
session_start();

// Importa página base para operações com o banco de dados
//require "/php/base.php";
include ('../php/base.php');

// Atribui os valores digitados no formulário aos campos correspondentes
$email = isset($_POST["tf_email"]) ? addslashes(trim($_POST["tf_email"])) : false;
$senha = (strlen($_POST["tf_senha"]) > 0) ? md5(trim($_POST["tf_senha"])) : false;

// Procura pelo usuário no banco de dados
$usuario = executar_SQL("SELECT idusuario, nomeusuario, email FROM Usuario WHERE email = '$email' AND Senha = '$senha'");

// Verifica se o usuário existe
if(verifica_resultado($usuario)){
	// Joga o resultado em um array associativo
	$us = retorna_linha($usuario);
	
	// Libera o resultado da consulta
	libera_consulta($usuario);
	
	// Atribui o nome e a id de usuário à variáveis de sessão
	$_SESSION["sidusuario"] = $us["idusuario"];
	$_SESSION["snomeusuario"] = $us["email"];
	$_SESSION["snome"] = $us["nomeusuario"];
}
// Se não recarrega a página com erro de usuário ou senha incorretos.
else{
	header("Location: login.php?erro=0");
	exit;
}

// Redireciona para a página de confirmação de Login (Dashboard)
echo "<META HTTP-EQUIV=REFRESH CONTENT='0;URL=../html/dashboard.html'>
            <script type=\"text/javascript\">
                alert(\"Login Efetuado com Sucesso!\");
            </script>"; 

?>