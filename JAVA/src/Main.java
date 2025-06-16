import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Escolha a estrutura para testar:");
        System.out.println("1 - Pilha Estática");
        System.out.println("2 - Pilha Dinâmica");
        System.out.println("3 - Lista Estática");
        System.out.println("4 - Lista Dinâmica");
        System.out.println("5 - Fila Estática");
        System.out.println("6 - Fila Dinâmica");
        System.out.print("Opção: ");
        
        int opcao = scanner.nextInt();
        
        System.out.print("Digite o volume de dados a ser testado: ");
        int volume = scanner.nextInt();
        
        String caminhoArquivo = "ratings.csv";
        
        // Ler dados do arquivo (já multiplicados por 2)
        int[] dadosOriginais = FileUtils.lerNotasDoArquivo(caminhoArquivo, volume);
        System.out.println("\nDados lidos do arquivo: " + dadosOriginais.length);
        
        switch (opcao) {
            case 1:
                testarEstrutura("Pilha Estática", () -> {
                    PilhaEstatica pilha = new PilhaEstatica(volume);
                    
                    for (int nota : dadosOriginais) {
                        pilha.empilhar(nota);
                    }
                    
                    int[] array = pilha.toArray();
                    SortUtils.countingSort(array);
                    pilha.fromArray(array);
                    
                    verificarOrdenacao(pilha.toArray());
                });
                break;
                
            case 2:
                testarEstrutura("Pilha Dinâmica", () -> {
                    PilhaDinamica pilha = new PilhaDinamica();
                    
                    for (int nota : dadosOriginais) {
                        pilha.empilhar(nota);
                    }
                    
                    int[] array = pilha.toArray();
                    SortUtils.countingSort(array);
                    pilha.fromArray(array);
                    
                    verificarOrdenacao(pilha.toArray());
                });
                break;
                
            case 3:
                testarEstrutura("Lista Estática", () -> {
                    ListaEstatica lista = new ListaEstatica(volume);
                    
                    for (int nota : dadosOriginais) {
                        lista.inserir(nota);
                    }
                    
                    int[] array = lista.toArray();
                    SortUtils.countingSort(array);
                    lista.fromArray(array);
                    
                    verificarOrdenacao(lista.toArray());
                });
                break;
                
            case 4:
                testarEstrutura("Lista Dinâmica", () -> {
                    ListaDinamica lista = new ListaDinamica();
                    
                    for (int nota : dadosOriginais) {
                        lista.inserir(nota);
                    }
                    
                    int[] array = lista.toArray();
                    SortUtils.countingSort(array);
                    lista.fromArray(array);
                    
                    verificarOrdenacao(lista.toArray());
                });
                break;
                
            case 5:
                testarEstrutura("Fila Estática", () -> {
                    FilaEstatica fila = new FilaEstatica(volume);
                    
                    for (int nota : dadosOriginais) {
                        fila.enfileirar(nota);
                    }
                    
                    int[] array = fila.toArray();
                    SortUtils.countingSort(array);
                    fila.fromArray(array);
                    
                    verificarOrdenacao(fila.toArray());
                });
                break;
                
            case 6:
                testarEstrutura("Fila Dinâmica", () -> {
                    FilaDinamica fila = new FilaDinamica();
                    
                    for (int nota : dadosOriginais) {
                        fila.enfileirar(nota);
                    }
                    
                    int[] array = fila.toArray();
                    SortUtils.countingSort(array);
                    fila.fromArray(array);
                    
                    verificarOrdenacao(fila.toArray());
                });
                break;
                
            default:
                System.out.println("Opção inválida!");
        }
    }
    
    public static void testarEstrutura(String nome, Runnable estruturaTeste) {
        System.out.println("\n=== Testando " + nome + " ===");
        
        long memoriaInicio = MemoryUtils.getMemoryUsage();
        long tempoInicio = System.nanoTime();
        
        estruturaTeste.run();
        
        long tempoFim = System.nanoTime();
        long memoriaFim = MemoryUtils.getMemoryUsage();
        
        double tempoMs = (tempoFim - tempoInicio) / 1_000_000.0;
        long memoriaUsada = memoriaFim - memoriaInicio;
        
        System.out.printf("Tempo total: %.3f ms%n", tempoMs);
        System.out.println("Memória usada: " + memoriaUsada + " bytes");
    }
    
    private static void verificarOrdenacao(int[] array) {
        double[] arrayOrdenado = FileUtils.converterParaDouble(array);
        boolean ordenado = true;
        for (int i = 0; i < arrayOrdenado.length - 1; i++) {
            if (arrayOrdenado[i] > arrayOrdenado[i + 1]) {
                ordenado = false;
                break;
            }
        }
        System.out.println("Verificação: " + (ordenado ? "ORDENADO" : "NÃO ORDENADO"));
    }

    
}