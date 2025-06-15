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

// Enum para escolher qual campo ordenar
type SortField int

const (
    SortByUserID SortField = iota
	SortByMovieID
	SortByRating
	SortByTimestamp
 )
 
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
		
		// Converter rating (coluna 3) para inteiro
		// Ratings vão de 0.5 a 5.0 em incrementos de 0.5
		// Multiplicamos por 2 para ter inteiros de 1 a 10
		ratingFloat, err := strconv.ParseFloat(record[2], 64)
		if err != nil {
			continue
		}
		
		// Multiplicar por 2 para converter: 0.5→1, 1.0→2, ..., 5.0→10
		ratingInt := int(ratingFloat * 2)
		
		ratings = append(ratings, ratingInt)
		count++
		
		if limit > 0 && count >= limit {
			break
		}
	}
	
	fmt.Printf("Carregados %d ratings do CSV (valores de 1 a 10)\n", len(ratings))
	return ratings, nil
 }