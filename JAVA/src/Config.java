public class Config {
    public static final String ARQUIVO_ENTRADA = "datasets/ratings.csv";

    public enum TipoDado {
        MOVIE_IDS, RATINGS
    }

    public enum TipoEstrutura {
        LISTA_LINEAR, LISTA_DINAMICA, PILHA_LINEAR,
        PILHA_DINAMICA, FILA_LINEAR, FILA_DINAMICA
    }

    public static final TipoDado TIPO_DADO = TipoDado.RATINGS;
}