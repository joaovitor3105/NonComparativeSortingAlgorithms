#ifndef CSVREADER_HPP
#define CSVREADER_HPP

#include <vector>
#include <string>
#include <fstream>

/**
 * Classe responsável por ler dados do arquivo CSV
 * Agora extrai movieIds do arquivo ratings.csv (userId,movieId,rating,timestamp)
 */
class CSVReader
{
private:
    std::string filename;

public:
    explicit CSVReader(const std::string &file);

    /**
     * Lê os movieIds do arquivo ratings.csv
     * @param maxRecords Número máximo de registros a ler (0 = todos)
     * @return Vetor com os movieIds
     */
    std::vector<int> readMovieIds(size_t maxRecords = 0);

    /**
     * Verifica se o arquivo existe e pode ser aberto
     * @return true se o arquivo for válido
     */
    bool isValidFile() const;

    /**
     * Conta o número total de linhas no arquivo
     * @return Número de linhas (excluindo header)
     */
    size_t countLines() const;

private:
    /**
     * Faz o parsing de uma linha CSV do ratings.csv e retorna o movieId
     * @param line Linha do CSV
     * @return movieId (segunda coluna)
     */
    int parseMovieId(const std::string &line) const;

    /**
     * Remove espaços em branco das extremidades
     * @param str String a ser processada
     * @return String sem espaços nas extremidades
     */
    std::string trim(const std::string &str) const;

    /**
     * Divide uma linha CSV em campos
     * @param line Linha do CSV
     * @return Vetor com os campos
     */
    std::vector<std::string> splitCSVLine(const std::string &line) const;
};

#endif // CSVREADER_HPP