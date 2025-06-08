# TRABALHO: Processamento de texto em Terminal & Pesquisas

## Instruções

1. Os exercícios abaixo deverão ser feitos dentro do terminal do Linux
       
2. Os exercícios estão, em sua maioria, dependentes um dos outros. Ou seja, o segundo depende do primeiro, o terceiro do segundo, e assim sucessivamente. Procure fazê-los na ordem.
       
3. Os comandos executados para cada exercício deverão ser respondidos _em um único script_ chamado _trabalho.sh_!
       
4. O trabalho será corrigido automaticamente.
       
Para saber sua nota, dentro do terminal, execute o script _./corrigir.sh_.

## Enunciado

1. Crie expressões regulares para identificar os padrões abaixo no arquivo bruxarias.txt
       
       Para cada exercício abaixo, salve a saída em um arquivo cujo nome é o [número da questão][letra].txt . Exemplo: questão 1, letra a, o arquivo será 1a.txt
       
A não ser que seja explicitado na questão, utilize o parâmetro -o para listar os matches da expressão regular!
       
         a) Todas as strings contendo 0’s ou 1’s 
            ▪ Por exemplo: 0, 1, 00, 11, 10, etc, incluindo a string nula
              
         b) Todas as strings representando números binários de 8 bits
            ▪ Números de 8 bits podem ter no máximo 8 caracteres e são sempre iniciados com o número ‘1’
              
         c) Todas as linhas que contém exatamente 1 número binário.
            ▪ É a letra b) com restrição de início e uma restrição de fim
              
         d) Todos os números decimais.
            ▪ Todo número decimal possui no mínimo 1 dígito
            ▪ Se o número tem 1 dígito, ele pode ser 0
            ▪ Se o número decimal tem mais de um dígito, ele não pode começar com 0
            ▪ Nota: Números binários são decimais apenas se começarem com 1
              
         e) Todas as ocorrências das letras ‘u’ ou ‘e’ seguidas da sequencia de letras ‘tt’
           

         f) Uma palavra da língua inglesa. Considere que uma palavra da língua inglesa:
            ▪ Contém no mínimo 3 letras;
            ▪ É composta apenas por vogais e consoantes.
            ▪ Apenas aSS primeira letra pode ser maiúscula
            ▪ Não possui espaços entre si
           
         g) Variáveis em uma linguagem de programação. Considere que uma variável:
            ▪ Não pode conter espaços;
            ▪ Deve possuir no mínimo 1 caractere;
            ▪ Aceita apenas letras maiúsculas, números, e o caractere ‘_’ .
            ▪ Deve começar apenas com uma letra maiúscula ou minúscula (ou seja, não pode começar com ‘_’ ou números)
           
         h) Endereços IPv4. Endereços IPv4 contém:
            ▪ 4 sequencias de números separados por pontos
            ▪ Cada sequencia pode conter 1 dígito; 2 dígitos; ou 3 dígitos se iniciados com o número 2 seguidos de dígitos entre 0 e 5.
            
2. Usando o find, crie comandos para realizar as tarefas abaixo:
       
Assim como no exercício anterior, salve a saída em um arquivo cujo nome é o [número da questão][letra].txt . Exemplo: questão 2, letra a, o arquivo será 2a.txt
       
         a) Imprimir todos os diretórios de /etc
         b) Imprimir todos os diretórios de /etc, sem imprimir os seus subdiretórios
         c) Encontrar todos os arquivos regulares com mais de 1 KiB de tamanho na pasta /etc.
         d) Encontrar todos os arquivos modificados na última semana atrás na pasta /var
         
3. O arquivo /etc/passwd é um arquivo de configuração dentro de sistemas operacionais GNU/Linux que contém as informações de todos os usuários do sistema. Esse arquivo contém as informações de um usuário por linha, com informações separadas pelo caractere ‘:’
       
       A primeira coluna desse arquivo contém os nomes dos usuários e a terceira coluna contém os números UUID, que identificam o usuário dentro do sistema operacional de fato. Esses UUID, quando são menores do 1000, indicam que o usuário é um usuário de administração - ou seja, são usados pelos programas para implementar permissões de acesso.
       
Assim como no exercício anterior, salve a saída em um arquivo cujo nome é o [número da questão][letra].txt . Exemplo: questão 3, letra a, o arquivo será 3a.txt
       
       Utilizando o comando awk : 
         a) Imprima apenas os nomes dos usuários do sistema.
         b) Imprima os nomes dos usuaŕios entre as linhas 10 e 20
         
4. Uma maneira de se modificar informações dos usuários no arquivo /etc/passwd, além da interface gráfica, é usar o comando sed, o qual permite editar arquivos de texto pela linha de comando.
       Execute as seguintes alterações no arquivo passwd utilizando o comando sed:
         a) Mude o nome do seu usuário para ‘exercicio’
         b) Apague a linha que contém o seu usuário
         
   
         

         
         
