package Algorithms

func CountingSort(arr []int) []int {
    if len(arr) == 0 {
        return arr
    }
    
    // Para ratings: valores vão de 1 a 10 (0.5 a 5.0 multiplicado por 2)
    const MIN_RATING = 1
    const MAX_RATING = 10
    const RANGE_SIZE = MAX_RATING - MIN_RATING + 1
    
    // Criar array de contagem
    count := make([]int, RANGE_SIZE)
    
    // Contar ocorrências
    for _, v := range arr {
        // Garantir que o valor está no range esperado
        if v >= MIN_RATING && v <= MAX_RATING {
            count[v-MIN_RATING]++
        }
    }
    
    // Acumular contagens
    for i := 1; i < RANGE_SIZE; i++ {
        count[i] += count[i-1]
    }
    
    // Construir array ordenado
    output := make([]int, len(arr))
    for i := len(arr) - 1; i >= 0; i-- {
        if arr[i] >= MIN_RATING && arr[i] <= MAX_RATING {
            output[count[arr[i]-MIN_RATING]-1] = arr[i]
            count[arr[i]-MIN_RATING]--
        }
    }
    
    return output
}

// CountingSortWithRange para valores com range específico
func CountingSortWithRange(arr []int, min, max int) []int {
    if len(arr) == 0 {
        return arr
    }
    
    rangeSize := max - min + 1
    count := make([]int, rangeSize)
    
    // Contar ocorrências
    for _, v := range arr {
        count[v-min]++
    }
    
    // Reconstruir array ordenado
    index := 0
    for i := 0; i < rangeSize; i++ {
        for j := 0; j < count[i]; j++ {
            arr[index] = i + min
            index++
        }
    }
    
    return arr
}