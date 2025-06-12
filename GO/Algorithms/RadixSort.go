package Algorithms

func getMax(arr []int) int {
    max := arr[0]
    for _, v := range arr {
        if v > max {
            max = v
        }
    }
    return max
}

func countingSortForRadix(arr []int, exp int) {
    n := len(arr)
    output := make([]int, n)
    count := make([]int, 10)
    
    // Contar ocorrências de cada dígito
    for i := 0; i < n; i++ {
        index := (arr[i] / exp) % 10
        count[index]++
    }
    
    // Calcular posições acumuladas
    for i := 1; i < 10; i++ {
        count[i] += count[i-1]
    }
    
    // Construir array ordenado
    for i := n - 1; i >= 0; i-- {
        index := (arr[i] / exp) % 10
        output[count[index]-1] = arr[i]
        count[index]--
    }
    
    // Copiar de volta para o array original
    copy(arr, output)
}

func RadixSort(arr []int) []int {
    if len(arr) == 0 {
        return arr
    }
    
    // Fazer cópia para não modificar original
    result := make([]int, len(arr))
    copy(result, arr)
    
    // Encontrar o número máximo
    max := getMax(result)
    
    // Aplicar counting sort para cada dígito
    for exp := 1; max/exp > 0; exp *= 10 {
        countingSortForRadix(result, exp)
    }
    
    return result
}