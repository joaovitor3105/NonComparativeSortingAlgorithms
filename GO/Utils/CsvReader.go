package Utils

import (
    "encoding/csv"
    "fmt"
    "io"
    "os"
    "strconv"
)

type Rating struct {
    UserID    int
    MovieID   int
    Rating    float64
    Timestamp int64
}

func LoadRatingsCSV(filename string, limit int) ([]int, error) {
    file, err := os.Open(filename)
    if err != nil {
        return nil, err
    }
    defer file.Close()
    
    reader := csv.NewReader(file)
    
    // Pular cabeçalho
    _, err = reader.Read()
    if err != nil {
        return nil, err
    }
    
    var ratings []int
    count := 0
    
    for {
        record, err := reader.Read()
        if err == io.EOF {
            break
        }
        if err != nil {
            return nil, err
        }
        
        // Usar o movieId como valor inteiro para ordenar
        movieID, err := strconv.Atoi(record[1])
        if err != nil {
            continue
        }
        
        ratings = append(ratings, movieID)
        count++
        
        if limit > 0 && count >= limit {
            break
        }
    }
    
    fmt.Printf("Carregados %d registros do CSV\n", len(ratings))
    return ratings, nil
}