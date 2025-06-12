package Algorithms

func CountingSort(arr []int) []int {
    if len(arr) == 0 {
        return arr
    }
    
    // Encontrar o valor máximo
    max := arr[0]
    for _, v := range arr {
        if v > max {
            max = v
        }
    }
    
    // Criar array de contagem
    count := make([]int, max+1)
    
    // Contar ocorrências
    for _, v := range arr {
        count[v]++
    }
    
    // Acumular contagens
    for i := 1; i <= max; i++ {
        count[i] += count[i-1]
    }
    
    // Construir array ordenado
    output := make([]int, len(arr))
    for i := len(arr) - 1; i >= 0; i-- {
        output[count[arr[i]]-1] = arr[i]
        count[arr[i]]--
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