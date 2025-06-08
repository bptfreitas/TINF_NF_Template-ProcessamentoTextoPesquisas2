#!/bin/bash

# 1a 
egrep -o '[01]+' ./bruxarias.dat  > 1a.txt

# 1b: Todas as strings representando números binários de 8 bits
egrep -o '1[01]{,7}' ./bruxarias.dat  > 1b.txt

# 1c: Todas as linhas que contém exatamente 1 número binário.
egrep -o '^1[01]{,7}$' ./bruxarias.dat  > 1c.txt

# 1d: Todos os números decimais.
egrep -wo '([1-9][0-9]+|[0-9]{1,1})' ./bruxarias.dat  > 1d.txt

# 1e: Todas as ocorrências das letras ‘u’ ou ‘e’ seguidas da sequencia de letras ‘tt’
egrep -o '[ue]tt' ./bruxarias.dat  > 1e.txt

# 1f: Uma palavra da língua inglesa.
egrep -o '[A-Za-z][a-z]{2,}' ./bruxarias.dat > 1f.txt

# 1g: Variaveis em uma linguagem de programacao
egrep -wo '[A-Za-z]+[a-zA-Z0-9_]{,}' ./bruxarias.dat > 1g.txt

# 1h: Endereco IPv4

patt="(([0-9])|([1-9][0-9])|(1[0-9][0-9])|(2[0-4][0-9])|(25[0-5]))"
egrep -wo "${patt}\.${patt}\.${patt}\.${patt}" ./bruxarias.dat > 1h.txt

# 2a: diretorios de /etc
find /etc -type d > 2a.txt

# 2b: diretorios de /etc sem subdiretorios
find /etc -maxdepth 1 -type d > 2b.txt

# 2c: arquivos regulares com +1 KiB
find /etc -size +1k -type f > 2c.txt

# 2d: arquivos modificados nos ultimos 7 dias
find /var -mtime -7 > 2d.txt

# 3a: usuarios do sistema
awk -F':' '{ print $1 }' /etc/passwd > 3a.txt

# 3b: usuarios do sistema entre as linhas 10 e 20
awk -F':' '{ if (NR>10 && NR < 20) print $1 }' /etc/passwd > 3b.txt

# 4a: mudar o nome do usuario logado para 'exercicio'
sed "s/$USER/exercicio/" /etc/passwd > 4a.txt

echo "ANTES: `whoami`"
tail /etc/passwd
echo "DEPOIS"
tail 4a.txt

# 4b: Remover a linha que contem o nome do usuario logado
sed "/`whoami`/d" /etc/passwd > 4b.txt


