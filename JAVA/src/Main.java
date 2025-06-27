// Classe principal para testes de desempenho
public class Main {
    private static final int[] VOLUMES_TESTE = { 100, 1000, 10000, 100000, 1000000 };
    private static final int NUM_REPETICOES = 10;

    static class ResultadoMedicao {
        double tempoTotal;
        int numElementos;
        boolean ordenadoCorretamente;

        ResultadoMedicao(double tempo, int elementos, boolean ordenado) {
            this.tempoTotal = tempo;
            this.numElementos = elementos;
            this.ordenadoCorretamente = ordenado;
        }
    }

    private static long calculateMemoryUsage(Config.TipoEstrutura tipo, int numElementos) {
        // Estimativa de uso de memória em bytes
        switch (tipo) {
            case LISTA_LINEAR:
                return (numElementos * 4L) + 32; // int array + overhead
            case LISTA_DINAMICA:
                return (numElementos * 16L) + 32; // Node objects + overhead
            case PILHA_LINEAR:
                return (numElementos * 4L) + 32;
            case PILHA_DINAMICA:
                return (numElementos * 16L) + 32;
            case FILA_LINEAR:
                return (numElementos * 4L) + 32;
            case FILA_DINAMICA:
                return (numElementos * 16L) + 32;
            default:
                return 0;
        }
    }

    private static ResultadoMedicao medirDesempenho(Config.TipoEstrutura tipoEstrutura, int maxLines) {
        Object estrutura = null;
        int[] array = null;
        long inicio, fim;

        try {
            // 1. Criar estrutura
            switch (tipoEstrutura) {
                case LISTA_LINEAR:
                    estrutura = new LinearList(maxLines);
                    break;
                case LISTA_DINAMICA:
                    estrutura = new LinkedList();
                    break;
                case PILHA_LINEAR:
                    estrutura = new LinearStack(maxLines);
                    break;
                case PILHA_DINAMICA:
                    estrutura = new Stack();
                    break;
                case FILA_LINEAR:
                    estrutura = new LinearQueue(maxLines);
                    break;
                case FILA_DINAMICA:
                    estrutura = new Queue();
                    break;
            }

            // 2. Leitura de dados
            int numElementos = RatingsReader.lerDadosPorTipo(estrutura, tipoEstrutura, Config.TIPO_DADO, maxLines);
            if (numElementos <= 0) {
                return new ResultadoMedicao(0, 0, false);
            }

            inicio = System.currentTimeMillis();
            // 3. Conversão para Array
            switch (tipoEstrutura) {
                case LISTA_LINEAR:
                    array = Converters.linearListToArray((LinearList) estrutura);
                    break;
                case LISTA_DINAMICA:
                    array = Converters.listToArray((LinkedList) estrutura);
                    break;
                case PILHA_LINEAR:
                    array = Converters.linearStackToArray((LinearStack) estrutura);
                    break;
                case PILHA_DINAMICA:
                    array = Converters.stackToArray((Stack) estrutura);
                    break;
                case FILA_LINEAR:
                    array = Converters.linearQueueToArray((LinearQueue) estrutura);
                    break;
                case FILA_DINAMICA:
                    array = Converters.queueToArray((Queue) estrutura);
                    break;
            }

            if (array == null) {
                return new ResultadoMedicao(0, 0, false);
            }

            // 4. Ordenação
            CountingSort.countingSort(array);
            boolean ordenado = CountingSort.isArraySorted(array);

            // 5. Reconversão (opcional)
            switch (tipoEstrutura) {
                case LISTA_LINEAR:
                    estrutura = Converters.arrayToLinearList(array);
                    break;
                case LISTA_DINAMICA:
                    estrutura = Converters.arrayToList(array);
                    break;
                case PILHA_LINEAR:
                    estrutura = Converters.arrayToLinearStack(array);
                    break;
                case PILHA_DINAMICA:
                    estrutura = Converters.arrayToStack(array);
                    break;
                case FILA_LINEAR:
                    estrutura = Converters.arrayToLinearQueue(array);
                    break;
                case FILA_DINAMICA:
                    estrutura = Converters.arrayToQueue(array);
                    break;
            }

            fim = System.currentTimeMillis();
            double tempoTotal = fim - inicio;

            return new ResultadoMedicao(tempoTotal, numElementos, ordenado);

        } catch (Exception e) {
            System.err.println("Erro durante medição: " + e.getMessage());
            e.printStackTrace(); // Print stack trace for debugging
            return new ResultadoMedicao(0, 0, false);
        }
    }

    private static void exibirTabelaResumoFinal(double[][] tempos, long[][] memorias, String[] nomes) {
        System.out.println("\n\n");
        System.out.println("                                         TABELA RESUMO FINAL");
        System.out.println(
                "============================================================================================================");

        // Cabeçalho
        System.out.printf("%-22s | %-10s |", "Estrutura", "Tipo");
        for (int volume : VOLUMES_TESTE) {
            System.out.printf(" %10d |", volume);
        }
        System.out.println(
                "\n------------------------------------------------------------------------------------------------------------");

        // Seção de Tempo
        System.out.println("\nTEMPO (ms):");
        for (int i = 0; i < nomes.length; i++) {
            String tipo = nomes[i].contains("Linear") ? "linear" : "dynamic";
            System.out.printf("%-22s | %-10s |", nomes[i], tipo);
            for (int j = 0; j < VOLUMES_TESTE.length; j++) {
                if (tempos[i][j] < 0) {
                    System.out.printf(" %10s |", "FALHA");
                } else {
                    System.out.printf(" %10.2f |", tempos[i][j]);
                }
            }
            System.out.println();
        }

        // Seção de Memória
        System.out.println("\nMEMORIA (MB):");
        for (int i = 0; i < nomes.length; i++) {
            String tipo = nomes[i].contains("Linear") ? "linear" : "dynamic";
            System.out.printf("%-22s | %-10s |", nomes[i], tipo);
            for (int j = 0; j < VOLUMES_TESTE.length; j++) {
                if (memorias[i][j] == 0) {
                    System.out.printf(" %10s |", "N/A");
                } else {
                    double memoriaMb = memorias[i][j] / (1024.0 * 1024.0);
                    System.out.printf(" %10.2f |", memoriaMb);
                }
            }
            System.out.println();
        }
        System.out.println(
                "============================================================================================================");
    }

    public static void main(String[] args) {
        System.out.println("\n");
        System.out.println("╔═══════════════════════════════════════════════════════════════════════════════════════╗");
        System.out.println(
                "║                 ANÁLISE DE DESEMPENHO - ESTRUTURAS DE DADOS (LINGUAGEM JAVA)              ║");
        System.out.println("║                                     COUNTING SORT                                     ║");
        System.out.println("╚═══════════════════════════════════════════════════════════════════════════════════════╝");
        System.out.printf("📁 Simulando arquivo: %s\n", Config.ARQUIVO_ENTRADA);
        System.out.print("📊 Volumes de teste: ");
        for (int volume : VOLUMES_TESTE) {
            System.out.print(volume + " ");
        }
        System.out.println();
        System.out.printf("🔄 Repetições por teste: %d\n\n", NUM_REPETICOES);

        Config.TipoEstrutura[] estruturas = {
                Config.TipoEstrutura.LISTA_LINEAR, Config.TipoEstrutura.LISTA_DINAMICA,
                Config.TipoEstrutura.PILHA_LINEAR, Config.TipoEstrutura.PILHA_DINAMICA,
                Config.TipoEstrutura.FILA_LINEAR, Config.TipoEstrutura.FILA_DINAMICA
        };

        String[] nomesEstruturas = {
                "Lista Linear", "Lista Dinamica", "Pilha Linear",
                "Pilha Dinamica", "Fila Linear", "Fila Dinamica"
        };

        double[][] resultadosTempo = new double[estruturas.length][VOLUMES_TESTE.length];
        long[][] resultadosMemoria = new long[estruturas.length][VOLUMES_TESTE.length];

        for (int i = 0; i < estruturas.length; i++) {
            for (int j = 0; j < VOLUMES_TESTE.length; j++) {
                int volumeAtual = VOLUMES_TESTE[j];
                double somaTempos = 0.0;
                int testesBemSucedidos = 0;
                long memoriaAmostra = 0;

                System.out.printf("⏳ Testando %s com %d elementos (%d repetições)...",
                        nomesEstruturas[i], volumeAtual, NUM_REPETICOES);
                System.out.flush();

                for (int k = 0; k < NUM_REPETICOES; k++) {
                    ResultadoMedicao res = medirDesempenho(estruturas[i], volumeAtual);

                    if (res.ordenadoCorretamente) {
                        somaTempos += res.tempoTotal;
                        testesBemSucedidos++;
                        if (k == 0) { // Only calculate memory for the first run to avoid repeated GC impact
                            memoriaAmostra = calculateMemoryUsage(estruturas[i], res.numElementos);
                        }
                    } else {
                        System.out.printf(" ❌ Erro na ordenação em uma das repetições para %s com %d elementos!\n",
                                nomesEstruturas[i], volumeAtual);
                        somaTempos = -1.0;
                        memoriaAmostra = 0;
                        break;
                    }
                }

                if (somaTempos != -1.0 && testesBemSucedidos > 0) {
                    resultadosTempo[i][j] = somaTempos / testesBemSucedidos;
                    resultadosMemoria[i][j] = memoriaAmostra;
                    System.out.printf(" ✅ Concluído! Média: (%.2f ms)\n", resultadosTempo[i][j]);
                } else {
                    resultadosTempo[i][j] = -1.0; // Indica falha
                    resultadosMemoria[i][j] = 0; // Indica falha
                    System.out.printf(" ❌ Falha na execução para %s com %d elementos!\n",
                            nomesEstruturas[i], volumeAtual);
                }
            }
        }

        // Exibir tabela resumo final
        exibirTabelaResumoFinal(resultadosTempo, resultadosMemoria, nomesEstruturas);
        System.out.println("\nAnálise de desempenho concluída!");
    }
}