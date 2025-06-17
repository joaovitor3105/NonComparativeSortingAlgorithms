#include "CSVReader.hpp"
#include <iostream>
#include <sstream>
#include <algorithm>

CSVReader::CSVReader(const std::string &file) : filename(file) {}

std::vector<int> CSVReader::readMovieIds(size_t maxRecords)
{
    std::vector<int> movieIds;
    std::ifstream file(filename);

    if (!file.is_open())
    {
        std::cerr << "Erro: Não foi possível abrir o arquivo " << filename << std::endl;
        return movieIds;
    }

    std::string line;
    bool firstLine = true;
    size_t recordCount = 0;

    while (std::getline(file, line) && (maxRecords == 0 || recordCount < maxRecords))
    {
        // Pula o cabeçalho
        if (firstLine)
        {
            firstLine = false;
            continue;
        }

        try
        {
            int movieId = parseMovieId(line);
            movieIds.push_back(movieId);
            recordCount++;
        }
        catch (const std::exception &e)
        {
            std::cerr << "Erro ao processar linha: " << line << std::endl;
            std::cerr << "Erro: " << e.what() << std::endl;
        }
    }

    file.close();

    std::cout << "Lidos " << movieIds.size() << " movieIds do arquivo " << filename << std::endl;
    return movieIds;
}

bool CSVReader::isValidFile() const
{
    std::ifstream file(filename);
    return file.good();
}

size_t CSVReader::countLines() const
{
    std::ifstream file(filename);
    if (!file.is_open())
    {
        return 0;
    }

    size_t lineCount = 0;
    std::string line;
    bool firstLine = true;

    while (std::getline(file, line))
    {
        if (firstLine)
        {
            firstLine = false;
            continue; // Pula o cabeçalho
        }
        lineCount++;
    }

    return lineCount;
}

std::vector<std::string> CSVReader::splitCSVLine(const std::string &line) const
{
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    
    while (std::getline(ss, field, ','))
    {
        fields.push_back(trim(field));
    }
    
    return fields;
}

int CSVReader::parseMovieId(const std::string &line) const
{
    // Para ratings.csv: userId,movieId,rating,timestamp
    // movieId é a segunda coluna (índice 1)
    
    auto fields = splitCSVLine(line);
    
    if (fields.size() < 2)
    {
        throw std::runtime_error("Linha CSV inválida: formato esperado userId,movieId,rating,timestamp");
    }
    
    std::string movieIdStr = fields[1]; // Segunda coluna = movieId
    
    // Remove aspas se existirem
    if (!movieIdStr.empty() && movieIdStr.front() == '"' && movieIdStr.back() == '"')
    {
        movieIdStr = movieIdStr.substr(1, movieIdStr.length() - 2);
    }

    // Converte para inteiro
    try
    {
        return std::stoi(movieIdStr);
    }
    catch (const std::exception &e)
    {
        throw std::runtime_error("Não foi possível converter movieId para inteiro: " + movieIdStr);
    }
}

std::string CSVReader::trim(const std::string &str) const
{
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos)
    {
        return "";
    }

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}