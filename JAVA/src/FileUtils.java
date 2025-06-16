import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class FileUtils {
    public static int[] lerNotasDoArquivo(String caminhoArquivo, int limite) {
        List<Integer> notasList = new ArrayList<>();

        try (BufferedReader br = new BufferedReader(new FileReader(caminhoArquivo))) {
            String linha;
            int count = 0;
            while ((linha = br.readLine()) != null && count < limite) {
                String[] partes = linha.trim().split(",");
                if (partes.length >= 2) {
                    try {
                        double notaDouble = Double.parseDouble(partes[1].trim());
                        int nota = (int) Math.round(notaDouble * 2);
                        notasList.add(nota);
                        count++;
                    } catch (NumberFormatException e) {
                        System.err.println("Linha ignorada: formato inválido - " + linha);
                    }
                }
            }
        } catch (IOException e) {
            System.err.println("Erro ao ler o arquivo: " + e.getMessage());
        }

        int[] notas = new int[notasList.size()];
        for (int i = 0; i < notas.length; i++) {
            notas[i] = notasList.get(i);
        }
        return notas;
    }

    public static double[] converterParaDouble(int[] array) {
        double[] resultado = new double[array.length];
        for (int i = 0; i < array.length; i++) {
            resultado[i] = array[i] / 2.0;
        }
        return resultado;
    }
}