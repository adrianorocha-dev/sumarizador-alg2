Manual do usuário.

* Para utilizar este programa em uma plataforma Linux, você deve ter instalado em sua maquina o compilador gcc.
* Para que o programa funcione da forma correta, a pasta lib, contendo as bibliotecas yolib.h e yostring.h devem estar na mesma pasta em que o codigo do programa.
* Com o terminal, navegue até o endereço do arquivo do codigo fonte, em seguida digite gcc <nome_do_arquivo> <nome_do_arquivo_de_saida>, sendo que
  o nome padrão do arquivo do codigo-fonte é trab.c, e caso não seja informado o nome do arquivo de saída, será gerado um arquivo chamado a.out.
* Após isso abra o arquivo de saída gerado pelo compilador com o comando ./<nome_do_arquivo_de_saida>
* Com o programa aberto apenas deve-se realizar as ações exigidas pelo mesmo.

ATENÇÃO:
Para que o programa funcione de forma normal, é preciso que haja um arquivo chamado stopwords.txt no mesmo diretório do seu executável.
Este arquivo pode ser configurado com stopwords de acordo com a necessidade do usuário para a sumarização.
Por padrão, este arquivo já vem preenchido com algumas stopwords em inglês e português.
