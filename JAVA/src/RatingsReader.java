import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class RatingsReader {
    public static int lerDadosPorTipo(Object estrutura, Config.TipoEstrutura tipo,
            Config.TipoDado tipoDado, int maxLines) {
        int count = 0;
        try (BufferedReader br = new BufferedReader(new FileReader(Config.ARQUIVO_ENTRADA))) {
            String linha = br.readLine(); // Pular cabeçalho
            while ((linha = br.readLine()) != null && count < maxLines) {
                String[] partes = linha.split(",");
                if (partes.length < 3)
                    continue;

                int valor;
                if (tipoDado == Config.TipoDado.MOVIE_IDS) {
                    valor = Integer.parseInt(partes[1]); // movieId
                } else {
                    valor = (int) Float.parseFloat(partes[2]); // rating como inteiro
                }

                switch (tipo) {
                    case LISTA_LINEAR:
                        ((LinearList) estrutura).append(valor);
                        break;
                    case LISTA_DINAMICA:
                        ((LinkedList) estrutura).insert(valor); // inserção no início
                        break;
                    case PILHA_LINEAR:
                        ((LinearStack) estrutura).push(valor);
                        break;
                    case PILHA_DINAMICA:
                        ((Stack) estrutura).push(valor);
                        break;
                    case FILA_LINEAR:
                        ((LinearQueue) estrutura).enqueue(valor);
                        break;
                    case FILA_DINAMICA:
                        ((Queue) estrutura).enqueue(valor);
                        break;
                    default:
                        System.out.println("Tipo de estrutura inválido.");
                        return -1;
                }
                count++;
            }
        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo: " + e.getMessage());
            return -1;
        } catch (NumberFormatException e) {
            System.err.println("Erro de formatação no arquivo CSV: " + e.getMessage());
            return -1;
        }

        System.out.printf("📥 Lidos %d valores do arquivo '%s' para %s\n",
                count, Config.ARQUIVO_ENTRADA, getNomeEstrutura(tipo));
        return count;
    }

    public static String getNomeEstrutura(Config.TipoEstrutura tipo) {
        switch (tipo) {
            case LISTA_LINEAR:
                return "Lista Linear";
            case LISTA_DINAMICA:
                return "Lista Ligada";
            case PILHA_LINEAR:
                return "Pilha Linear";
            case PILHA_DINAMICA:
                return "Pilha Dinâmica";
            case FILA_LINEAR:
                return "Fila Linear";
            case FILA_DINAMICA:
                return "Fila Dinâmica";
            default:
                return "Desconhecida";
        }
    }
}
