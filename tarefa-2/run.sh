#!/bin/bash

# Força o uso de ponto decimal independente da linguagem do sistema
export LC_NUMERIC=C

REPETICOES=10
PROGRAMAS=("prog0" "prog1" "prog2")
NIVEIS=("O0" "O2" "O3")

for i in "${!PROGRAMAS[@]}"; do
    prog=${PROGRAMAS[$i]}
    nivel=${NIVEIS[$i]}
    
    echo "-------------------------------------------"
    echo "Avaliando Nível de Otimização $nivel ($prog)"
    echo "Executando $REPETICOES vezes..."

    soma_init=0
    soma_dep=0
    soma_ilp=0

    for ((j=1; j<=REPETICOES; j++)); do
        # Executa e filtra apenas as linhas de tempo para evitar capturar o "Resultado: ..."
        saida=$(./$prog)
        
        # O grep agora busca especificamente pelo rótulo e captura o número logo após
        t_init=$(echo "$saida" | grep "Inicializacao" | awk '{print $3}')
        t_dep=$(echo "$saida" | grep "Soma (Dependente)" | awk '{print $4}')
        # Se o seu programa imprime "Soma:" sem o (Dependente), ajuste o grep abaixo:
        if [ -z "$t_dep" ]; then t_dep=$(echo "$saida" | grep "Soma:" | awk '{print $3}'); fi
        
        t_ilp=$(echo "$saida" | grep "ILP" | awk '{print $4}')

        # Acumula
        soma_init=$(echo "$soma_init + $t_init" | bc -l)
        soma_dep=$(echo "$soma_dep + $t_dep" | bc -l)
        soma_ilp=$(echo "$soma_ilp + $t_ilp" | bc -l)
    done

    # Calcula médias
    media_init=$(echo "scale=6; $soma_init / $REPETICOES" | bc -l)
    media_dep=$(echo "scale=6; $soma_dep / $REPETICOES" | bc -l)
    media_ilp=$(echo "scale=6; $soma_ilp / $REPETICOES" | bc -l)

    echo "Médias para $nivel:"
    echo "  - Inicialização: $media_init s"
    echo "  - Soma (Dep):    $media_dep s"
    echo "  - Soma (ILP):    $media_ilp s"
done

echo "-------------------------------------------"
echo "Análise finalizada!"