<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
</head>
<body>
    <h1>Jogo de Labirinto</h1>
    <p>
        Este é um jogo de labirinto simples implementado em linguagem C, onde o jogador deve navegar por um tabuleiro, evitar paredes, e encontrar a saída antes de esgotar o número de passos disponíveis. O jogo contém várias fases, e o jogador acumula pontuação conforme avança.
    </p>
    <hr>
    <h2>🎮 Como Jogar</h2>
    <ol>
        <ul>O jogador será posicionado em uma posição inicial aleatória dentro do tabuleiro.</ul>
        <li>O objetivo de cada fase é encontrar a saída do labirinto, representada pela letra <code>S</code> no tabuleiro.</li>
        <li>Utilize as seguintes teclas para se movimentar:
            <ul>
                <li><code>W</code>: Move para cima.</li>
                <li><code>S</code>: Move para baixo.</li>
                <li><code>A</code>: Move para a esquerda.</li>
                <li><code>D</code>: Move para a direita.</li>
            </ul>
        </li>
        <li>O jogador precisa completar a fase dentro de <b>30 passos</b>. Caso contrário, ele perde a fase.<br>
            Depois de finalizar o jogo, a contagem de passos diminui para <b>25 passos</b>, tornando o jogo mais complexo.</li>
        <li>Cada fase completada aumenta a pontuação do jogador em <b>100 pontos</b>.</li>
    </ol>
    <hr>
    <h2>🗺️ Estrutura do Tabuleiro</h2>
    <p>O tabuleiro tem dimensões fixas de 10x10 e é composto por:</p>
    <ul>
        <li><b>J</b>: Representa a posição do jogador.</li>
        <li><b>|</b>: Representa paredes (bloqueiam o movimento).</li>
        <li><b>-</b>: Espaços vazios (onde o jogador pode se mover).</li>
        <li><b>S</b>: Representa a saída.</li>
    </ul>
    <hr>
    <h2>🏆 Regras de Pontuação</h2>
    <ul>
        <li><b>Completar uma fase</b>: +100 pontos.</li>
        <li><b>Esgotar os passos disponíveis</b>: Game over.</li>
        <li><b>Progresso máximo</b>: O jogo possui <b>5 fases</b>, e ao completar todas, o jogador recebe a pontuação final.</li>
    </ul>
    <hr>
    <h2>⚙️ Como Executar</h2>
    <ol>
        <li>Certifique-se de ter um compilador C instalado, como <code>gcc</code>.</li>
        <li>Clone este repositório:
            <pre>
git clone &lt;URL-DO-SEU-REPOSITORIO&gt;
cd &lt;PASTA-DO-REPOSITORIO&gt;
            </pre>
        </li>
        <li>Compile o código com o seguinte comando:
            <pre>
gcc -o labirinto main.c -Wall
            </pre>
        </li>
        <li>Execute o jogo:
            <pre>
./labirinto
            </pre>
        </li>
    </ol>
    <hr>
    <h2>📁 Estrutura do Repositório</h2>
    <ul>
        <li><b>main.c</b>: Arquivo principal que inicia o jogo.</li>
        <li><b>game.h</b> / <b>score.h</b>: Cabeçalhos com definições de funções e estruturas.</li>
        <li><b>faseN.txt</b>: Arquivos contendo a configuração de cada fase. Substitua <code>N</code> pelo número da fase correspondente.
            <ul>
                <li><code>0</code>: Espaço vazio.</li>
                <li><code>1</code>: Parede.</li>
            </ul>
        </li>
    </ul>
    <hr>
    <h2>🛠️ Funcionalidades do Código</h2>
    <ul>
        <li><b>Tabuleiro Dinâmico</b>: O tabuleiro é alocado dinamicamente para maior flexibilidade.</li>
        <li><b>Carregamento de Fases</b>: As fases são carregadas de arquivos externos, permitindo personalização dos labirintos.</li>
        <li><b>Movimentação do Jogador</b>: O jogador só pode se mover para espaços válidos (sem paredes).</li>
        <li><b>Controle de Limite de Passos</b>: Cada fase tem um número fixo de passos (30).</li>
        <li><b>Posicionamento Aleatório</b>: O jogador e a saída são posicionados aleatoriamente em posições válidas.</li>
    </ul>
    <hr>
    <h2>🚀 Personalização</h2>
    <ul>
        <li><b>Adicionar Novas Fases</b>: Crie novos arquivos <code>faseN.txt</code> com as configurações desejadas e ajuste o valor de <code>NUM_PHASES</code> no código para incluir novas fases.</li>
        <li><b>Alterar Dimensões</b>: Para mudar o tamanho do tabuleiro, ajuste os valores de <code>MAX_LINHAS</code> e <code>MAX_COLUNAS</code> no código. Certifique-se de atualizar os arquivos das fases para refletir o novo tamanho.</li>
    </ul>
    <hr>
    <h2>🤝 Contribuição</h2>
    <p>
        Sinta-se à vontade para contribuir com melhorias ou novas funcionalidades. Faça um fork do repositório, implemente as mudanças e envie um pull request!
    </p>
    <hr>
    <h2>📄 Licença</h2>
    <p>
        Este projeto está licenciado sob a licença MIT. Consulte o arquivo <code>LICENSE</code> para mais detalhes.
    </p>
    <hr>
    <p>Divirta-se explorando os labirintos! 😊</p>
</body>
</html>
