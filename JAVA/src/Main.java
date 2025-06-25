import java.util.Arrays;
import java.util.LinkedHashMap;
import java.util.Map;

public class Main {
    // Volumes de teste a serem executados automaticamente
    private static final int[] VOLUMES_TESTE = { 100, 1000, 10000, 100000, 1000000 };
    private static final String CAMINHO_ARQUIVO = "/home/john/Desktop/NonComparativeSortingAlgorithms/ml-25m/ratings.csv";

    // Estruturas para armazenar todos os resultados para a tabela final.
    // Usamos LinkedHashMap para manter a ordem de inserção.
    private static final Map<String, Map<Integer, Double>> resultadosTempo = new LinkedHashMap<>();
    private static final Map<String, Map<Integer, Long>> resultadosMemoria = new LinkedHashMap<>();
    private static final String[] NOMES_ESTRUTURAS = {
            "Pilha Estática", "Pilha Dinâmica", "Lista Estática",
            "Lista Dinâmica", "Fila Estática", "Fila Dinâmica"
    };

    public static void main(String[] args) {
        System.out.println("=".repeat(80));
        System.out.println("TESTE AUTOMATIZADO DE ESTRUTURAS DE DADOS COM COUNTING SORT");
        System.out.println("(Medições de Tempo e Memória separadas para maior precisão)");
        System.out.println("=".repeat(80));
        System.out.println("Volumes de teste: " + Arrays.toString(VOLUMES_TESTE));
        System.out.println("Arquivo de dados: " + CAMINHO_ARQUIVO);
        System.out.println("=".repeat(80));

        // Inicializa as estruturas de armazenamento de resultados
        for (String nome : NOMES_ESTRUTURAS) {
            resultadosTempo.put(nome, new LinkedHashMap<>());
            resultadosMemoria.put(nome, new LinkedHashMap<>());
        }

        // --- INÍCIO DO WARM-UP DA JVM ---
        System.out.println("\n" + "=".repeat(80));
        System.out.println("INICIANDO WARM-UP DA JVM...");
        System.out.println("=".repeat(80));

        // Executa operações de aquecimento para todas as estruturas
        // Isso ajuda a JVM a compilar o código JIT e aquecer caches.
        int warmUpVolume = 10000; // Um volume razoável para aquecimento
        int[] warmUpDados = FileUtils.lerNotasDoArquivo(CAMINHO_ARQUIVO, warmUpVolume);

        // Loop de aquecimento para cada tipo de estrutura
        for (int i = 0; i < 20; i++) { // Várias iterações para garantir o aquecimento
            // Warm-up da Pilha Estática
            if (warmUpVolume <= 1000000) { // Evita erro de capacidade se warmUpVolume for muito grande
                PilhaEstatica dummyPilhaE = new PilhaEstatica(warmUpVolume);
                for (int nota : warmUpDados)
                    dummyPilhaE.empilhar(nota);
                SortUtils.countingSort(dummyPilhaE.toArray());
            }

            // Warm-up da Pilha Dinâmica
            PilhaDinamica dummyPilhaD = new PilhaDinamica();
            for (int nota : warmUpDados)
                dummyPilhaD.empilhar(nota);
            SortUtils.countingSort(dummyPilhaD.toArray());

            // Warm-up da Lista Estática
            if (warmUpVolume <= 1000000) {
                ListaEstatica dummyListaE = new ListaEstatica(warmUpVolume);
                for (int nota : warmUpDados)
                    dummyListaE.inserir(nota);
                SortUtils.countingSort(dummyListaE.toArray());
            }

            // Warm-up da Lista Dinâmica
            ListaDinamica dummyListaD = new ListaDinamica();
            for (int nota : warmUpDados)
                dummyListaD.inserir(nota);
            SortUtils.countingSort(dummyListaD.toArray());

            // Warm-up da Fila Estática
            if (warmUpVolume <= 1000000) {
                FilaEstatica dummyFilaE = new FilaEstatica(warmUpVolume);
                for (int nota : warmUpDados)
                    dummyFilaE.enfileirar(nota);
                SortUtils.countingSort(dummyFilaE.toArray());
            }

            // Warm-up da Fila Dinâmica
            FilaDinamica dummyFilaD = new FilaDinamica();
            for (int nota : warmUpDados)
                dummyFilaD.enfileirar(nota);
            SortUtils.countingSort(dummyFilaD.toArray());

            System.gc(); // Sugere coleta de lixo para limpar a memória do warm-up
            try {
                Thread.sleep(100); // Pequena pausa para permitir a execução de GC
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
        System.out.println("Warm-up da JVM concluído. Iniciando testes reais.");
        System.out.println("=".repeat(80) + "\n");
        // --- FIM DO WARM-UP DA JVM ---

        // Executar testes para cada volume
        for (int volume : VOLUMES_TESTE) {
            System.out.println("\n" + "=".repeat(80));
            System.out.println("TESTANDO COM " + volume + " ENTRADAS");
            System.out.println("=".repeat(80));

            int[] dadosOriginais = FileUtils.lerNotasDoArquivo(CAMINHO_ARQUIVO, volume);
            System.out.println("Dados carregados: " + dadosOriginais.length + " elementos");

            testarTodasEstruturas(dadosOriginais, volume);

            System.gc(); // Força a coleta de lixo após cada volume de teste
            try {
                Thread.sleep(200); // Pequena pausa para estabilização
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }

        System.out.println("\n" + "=".repeat(80));
        System.out.println("TODOS OS TESTES CONCLUÍDOS!");
        System.out.println("=".repeat(80));

        // Chama o método que imprime a tabela de resumo final
        exibirTabelaResumoFinal();
    }

    private static void testarTodasEstruturas(int[] dadosOriginais, int volume) {
        // Clonar dadosOriginais para cada teste para garantir que cada teste comece com
        // os mesmos dados
        TesteRunnable[] testes = {
                () -> { // Teste 1: Pilha Estática
                    PilhaEstatica pilha = new PilhaEstatica(volume); //
                    for (int nota : dadosOriginais)
                        pilha.empilhar(nota); //
                    int[] array = pilha.toArray(); //
                    SortUtils.countingSort(array); //
                    pilha.fromArray(array); //
                    return verificarOrdenacao(pilha.toArray()); //
                },
                () -> { // Teste 2: Pilha Dinâmica
                    PilhaDinamica pilha = new PilhaDinamica(); //
                    for (int nota : dadosOriginais)
                        pilha.empilhar(nota); //
                    int[] array = pilha.toArray(); //
                    SortUtils.countingSort(array); //
                    pilha.fromArray(array); //
                    return verificarOrdenacao(pilha.toArray()); //
                },
                () -> { // Teste 3: Lista Estática
                    ListaEstatica lista = new ListaEstatica(volume); //
                    for (int nota : dadosOriginais)
                        lista.inserir(nota); //
                    int[] array = lista.toArray(); //
                    SortUtils.countingSort(array); //
                    lista.fromArray(array); //
                    return verificarOrdenacao(lista.toArray()); //
                },
                () -> { // Teste 4: Lista Dinâmica
                    ListaDinamica lista = new ListaDinamica(); //
                    for (int nota : dadosOriginais)
                        lista.inserir(nota); //
                    int[] array = lista.toArray(); //
                    SortUtils.countingSort(array); //
                    lista.fromArray(array); //
                    return verificarOrdenacao(lista.toArray()); //
                },
                () -> { // Teste 5: Fila Estática
                    FilaEstatica fila = new FilaEstatica(volume); //
                    for (int nota : dadosOriginais)
                        fila.enfileirar(nota); //
                    int[] array = fila.toArray(); //
                    SortUtils.countingSort(array); //
                    fila.fromArray(array); //
                    return verificarOrdenacao(fila.toArray()); //
                },
                () -> { // Teste 6: Fila Dinâmica
                    FilaDinamica fila = new FilaDinamica(); //
                    for (int nota : dadosOriginais)
                        fila.enfileirar(nota); //
                    int[] array = fila.toArray(); //
                    SortUtils.countingSort(array); //
                    fila.fromArray(array); //
                    return verificarOrdenacao(fila.toArray()); //
                }
        };

        for (int i = 0; i < testes.length; i++) {
            String nomeEstrutura = NOMES_ESTRUTURAS[i];
            System.out.println("\n--- Testando " + nomeEstrutura + " ---");

            ResultadoTempo resTempo = medirTempoDeExecucao(testes[i]); //
            long memoriaUsada = medirUsoDeMemoria(testes[i]); //

            // Armazena os resultados nas estruturas de dados globais
            if (resTempo.ordenadoCorreto) {
                resultadosTempo.get(nomeEstrutura).put(volume, resTempo.tempoMs); //
                resultadosMemoria.get(nomeEstrutura).put(volume, memoriaUsada); //
            } else {
                // Se der erro, armazena um valor negativo para indicar falha
                resultadosTempo.get(nomeEstrutura).put(volume, -1.0); //
                resultadosMemoria.get(nomeEstrutura).put(volume, -1L); //
            }
        }
    }

    // Método para exibir a tabela de resumo final
    private static void exibirTabelaResumoFinal() {
        System.out.println("\n");
        System.out.println(" ".repeat(25) + "TABELA RESUMO FINAL" + " ".repeat(25));
        System.out.println("=".repeat(90));

        // Cabeçalho da tabela
        System.out.printf("%-22s | %-10s |", "Estrutura", "Tipo"); //
        for (int volume : VOLUMES_TESTE) {
            System.out.printf(" %10d |", volume); //
        }
        System.out.println("\n" + "-".repeat(90)); //

        // Seção de TEMPO
        System.out.println("\nTEMPO (ms):"); //
        for (String nome : NOMES_ESTRUTURAS) {
            String tipo = nome.contains("Estática") ? "estático" : "dinâmico"; //
            System.out.printf("%-22s | %-10s |", nome, tipo); //
            for (int volume : VOLUMES_TESTE) {
                double tempo = resultadosTempo.get(nome).getOrDefault(volume, -1.0); //
                if (tempo < 0) {
                    System.out.printf(" %10s |", "FALHA"); //
                } else {
                    System.out.printf(" %10.2f |", tempo); //
                }
            }
            System.out.println(); //
        }

        // Seção de MEMÓRIA
        System.out.println("\nMEMÓRIA (MB):"); //
        for (String nome : NOMES_ESTRUTURAS) {
            String tipo = nome.contains("Estática") ? "estático" : "dinâmico"; //
            System.out.printf("%-22s | %-10s |", nome, tipo); //
            for (int volume : VOLUMES_TESTE) {
                long memoriaBytes = resultadosMemoria.get(nome).getOrDefault(volume, -1L); //
                if (memoriaBytes < 0) {
                    System.out.printf(" %10s |", "FALHA"); //
                } else {
                    // Converte bytes para megabytes
                    double memoriaMb = memoriaBytes / (1024.0 * 1024.0); //
                    System.out.printf(" %10.2f |", memoriaMb); //
                }
            }
            System.out.println(); //
        }
        System.out.println("=".repeat(90)); //
    }

    // --- Métodos de medição, verificação e classes auxiliares (sem alterações) ---

    private static ResultadoTempo medirTempoDeExecucao(TesteRunnable estruturaTeste) {
        long tempoInicio = System.nanoTime(); //
        boolean ordenadoCorreto = false; //
        try {
            ordenadoCorreto = estruturaTeste.run(); //
        } catch (Exception e) {
            System.err.println("ERRO durante medição de tempo: " + e.getMessage()); //
        }
        long tempoFim = System.nanoTime(); //

        double tempoMs = (tempoFim - tempoInicio) / 1_000_000.0; //
        System.out.printf("Medição de Tempo: %.3f ms | Status: %s%n",
                tempoMs, ordenadoCorreto ? "ORDENADO" : "NÃO ORDENADO"); //

        return new ResultadoTempo(tempoMs, ordenadoCorreto); //
    }

    private static long medirUsoDeMemoria(TesteRunnable estruturaTeste) {
        System.gc(); //
        try {
            Thread.sleep(200); //
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt(); //
        }

        long memoriaInicio = MemoryUtils.getMemoryUsage(); //
        try {
            estruturaTeste.run(); //
        } catch (Exception e) {
            System.err.println("ERRO durante medição de memória: " + e.getMessage()); //
        }
        long memoriaFim = MemoryUtils.getMemoryUsage(); //

        long memoriaUsada = memoriaFim - memoriaInicio; //
        System.out.printf("Medição de Memória: %d bytes%n", memoriaUsada); //

        return memoriaUsada; //
    }

    private static boolean verificarOrdenacao(int[] array) {
        if (array == null || array.length <= 1)
            return true; //
        for (int i = 0; i < array.length - 1; i++) {
            if (array[i] > array[i + 1])
                return false; //
        }
        return true; //
    }

    @FunctionalInterface
    private interface TesteRunnable {
        boolean run() throws Exception; //
    }

    private static class ResultadoTempo {
        final double tempoMs;
        final boolean ordenadoCorreto;

        ResultadoTempo(double tempoMs, boolean ordenadoCorreto) {
            this.tempoMs = tempoMs;
            this.ordenadoCorreto = ordenadoCorreto;
        }
    }
}