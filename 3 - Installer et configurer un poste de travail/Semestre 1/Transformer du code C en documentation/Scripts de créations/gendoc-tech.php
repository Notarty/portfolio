<?php
// ouverture des fichiers

$version = $argv[1];
$nomSources = array();
$nomDestination = "doc-tech-".$version.".html";
$dest = fopen($nomDestination,'w');
rechercheSrc($nomSources);

head($dest,$version);
foreach($nomSources as $fichier){
    $lines = file($fichier);
    entete($dest,$fichier);
    foreach($lines as $line){
        if($line[0] == '*' ){
            $pointeur = 0;
            while(($line[$pointeur] != '\\' || $line[$pointeur] == '@') && $pointeur < strlen($line)-3){
                $pointeur += 1;
            }
            if($line[$pointeur] == '\\' || $line[$pointeur] == '@'){
                $pointeur += 1;
                if($line[$pointeur] =='a'){
                    author($dest,$line);
                }   
                elseif($line[$pointeur] == "b"){
                    brief($dest,$line);
                }
                elseif($line[$pointeur] == "d"){
                    $pointeur += 1;
                    if($line[$pointeur] == "a"){
                        fdate($dest,$line);
                    }
                    elseif($line[$pointeur] == "e"){
                        def($dest,$line);
                }
                }
                elseif($line[$pointeur] == "f"){
                    if($line[$pointeur+1] == "n"){
                        fonction($dest,$line);
                    }
                }
                elseif($line[$pointeur] == "p"){
                    $pointeur += 2;
                    if($line[$pointeur] == 'g'){
                        page($dest,$line);
                    }
                    elseif($line[$pointeur] == 'r'){
                        param($dest,$line);
                    }
                }
                elseif($line[$pointeur] == "r"){
                    retourne($dest,$line);
                }
                elseif($line[$pointeur] == "s"){
                    $pointeur += 1;
                    if($line[$pointeur] == "e"){
                        see($dest,$line);
                    }
                    elseif($line[$pointeur] == "t"){
                        struct($dest,$line); 
                    }
                }
                elseif($line[$pointeur] == "t"){
                    typedef($dest,$line);
                }
                elseif($line[$pointeur] == "v"){
                    $pointeur += 1;
                    if($line[$pointeur] == "a"){
                        variable($dest,$line);
                    }
                    elseif($line[$pointeur] == "e"){
                        version($dest,$line);
                    }
                }
            }
        }
    }
    fwrite($dest,"\n<hr>\n<hr>\n");
}
fwrite($dest,"</body>");
fwrite($dest,"</html>");

function rechercheSrc(&$nomSources){
    $dir = getcwd();
    $scan = scandir($dir);
    foreach($scan as $fichier){
        if(strpos($fichier,".c") != false){
            $dedans = false;
            foreach($nomSources as $ficInTab){
                if($ficInTab == $fichier){
                    $dedans = true;
                }
            }
            if($dedans == false){
                $nomSources[] = $fichier;
            }
        } 
    }
}

function head($dest,$version) // entête du fichier html (à changer)
{
    fwrite($dest,"<!DOCTYPE html>
<html xmlns='http://www.w3.org/1999/xhtml' xml:lang='fr' lang='fr'>
    <head>
        <meta charset='utf-8'>
        <title>Documentation technique</title>
    </head>
    <body>
    <h1> Documentation Technique</h1>
    <p> version : $version </p>");

}

function entete($dest,$fichier){
    fwrite($dest,"<h2> ". $fichier ." </h2>\n");
}

function author($dest, $line){
    $i = 0;
    fwrite($dest,"<h3> Auteur : ");
    while($line[$i] != 'r'){
        $i += 1;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</h3>\n");
}

function brief($dest,$line){
    $i = 0;
    fwrite($dest,"<p>-");
    while($line[$i] != 'f'){
        $i += 1;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</p>\n");
}

function fdate($dest,$line){
    $i = 0;
    fwrite($dest,"<h3> Fait le : ");
    while($line[$i] != 'e'){
        $i += 1;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</h3>\n");
}

function def($dest,$line){
    $i = 0;
    fwrite($dest,"<h4> Constante :");
    while($line[$i] != 'f'){
        $i += 1;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</h4>\n");
}

function fonction($dest,$line){
    $i = 1;
    fwrite($dest,"\n<hr>\n");
    fwrite($dest,"<h3> Fonction </h3>\n");
    while($line[$i] != 'f'){
        $i ++;
    }
    while($line[$i] != ' '){
        $i += 1;
    }
    $i++;
    fwrite($dest,"<p><strong> Type </strong> : ");
    while($i < strlen($line)-3 && $line[$i]!= " "){
        fwrite($dest,$line[$i]);
        $i ++;
    }
    fwrite($dest,"</p>\n<p><strong>Nom</strong> : ");
    while($line[$i] != '('){
        fwrite($dest,$line[$i]);
        $i ++;
    }
    fwrite($dest,"</p>\n");
}

function page($dest,$line){
    $i = 0;
    fwrite($dest,"<h3> Page : ");
    while($line[$i] != 'e'){
        $i += 1;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</h3>\n");
}

function param($dest,$line){
    $i =0;
    fwrite($dest,"<p><strong>paramètre</strong> :");
    while($line[$i] != 'm' && $i < strlen($line)-3){// passe après le param
        $i ++;
    }
    $i ++;
    while($line[$i] == ' '){ // arrive au début du nom
        $i++;
    }
    while(($line[$i] != ' ' && $line[$i] != ':') && $i < strlen($line)-3){ // écris le nom
        fwrite($dest,$line[$i]);
        $i++;
    }
    fwrite($dest,"</p>");
    while(($line[$i] == ' ' || $line[$i] == ':') && $i < strlen($line)-3){// arrive au début de l'explication
        $i ++;
    }
    fwrite($dest,"<p>-");
    while($i < strlen($line)-3){// écris l'explication
        fwrite($dest,$line[$i]);
        $i ++;
    }
    fwrite($dest,"</p>"); 
}

function retourne($dest,$line){
    $i = 0;
    fwrite($dest,"<p><strong> retourne</strong> : ");
    while($line[$i] != 'n'){
        $i += 1;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</p>\n");
}

function see($dest,$line){
    $i = 0;
    fwrite($dest,"<p><strong> utilise la fonction</strong> : ");
    while($line[$i] != 'e'){
        $i += 1;
    }
    $i += 2;
    while($line[$i] == ' '){
        $i ++;
    }
    while($line[$i] != '(' && $i < strlen($line)-3){
        fwrite($dest,$line[$i]);
        $i ++;
    }
    fwrite($dest,"</p>\n");
}

function struct($dest,$line){
    $i = 0;
    fwrite($dest,"<p><strong>Structure</strong> : ");
    while($line[$i] != 'c'){
        $i += 1;
    }
    while($line[$i] == ' '){
        $i ++;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</p>\n");
}

function typedef($dest,$line){
    $i = 0;
    fwrite($dest,"<p><strong>Definition du type</strong> : ");
    while($line[$i] != 'f'){
        $i += 1;
    }
    while($line[$i] == ' '){
        $i ++;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</p>\n");
}

function variable($dest,$line){
    $i = 0;
    fwrite($dest,"<p><strong>Variable</strong> : ");
    while($line[$i] != 'f'){
        $i += 1;
    }
    $i +=2;
    while($line[$i] == ' '){
        $i ++;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</p>\n");
}

function version($dest,$line){
    $i = 0;
    fwrite($dest,"<h3>Version : ");
    while($line[$i] != 'n'){
        $i += 1;
    }
    while($line[$i] == ' '){
        $i ++;
    }
    while($i < strlen($line)-3){
        $i ++;
        fwrite($dest,$line[$i]);
    }
    fwrite($dest,"</h3>\n");
}
?>